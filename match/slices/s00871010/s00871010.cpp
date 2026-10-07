// s00871010: png_init_read_transformations (libpng 1.2.25, pngrtran.c).
//
// Upstream libpng 1.2.25 source, byte-exact when compiled with /arch:SSE /fp:fast.
// The shared third-party build compiled pngrtran.c without those flags, so this one
// function (the only one in pngrtran.c with float compares/pow) failed to match there.
// Self-contained: png_struct is declared below up to the last field this function uses,
// with the layout of Spore's libpng configuration (offsets checked against the asm:
// transformations +0x70, palette +0x114, color_type +0x126, background +0x13a,
// background_1 +0x144, gamma +0x15c, screen_gamma +0x160, trans +0x188).
#include <math.h>

typedef unsigned long png_uint_32;
typedef unsigned short png_uint_16;
typedef unsigned char png_byte;
typedef png_byte* png_bytep;
typedef png_uint_16* png_uint_16p;
typedef png_uint_16** png_uint_16pp;
typedef void* png_voidp;
typedef unsigned int png_size_t;

struct png_color { png_byte red, green, blue; };
typedef png_color* png_colorp;
struct png_color_16 { png_byte index; png_uint_16 red, green, blue, gray; };
struct png_color_8 { png_byte red, green, blue, gray, alpha; };
struct png_row_info { png_uint_32 width, rowbytes; png_byte color_type, bit_depth, channels, pixel_depth; };

// zlib 1.2.3 z_stream (56 bytes)
struct z_stream_s {
    png_bytep next_in; unsigned avail_in; png_uint_32 total_in;
    png_bytep next_out; unsigned avail_out; png_uint_32 total_out;
    char* msg; void* state; void* zalloc; void* zfree; void* opaque;
    int data_type; png_uint_32 adler; png_uint_32 reserved;
};

struct png_struct_def;
typedef png_struct_def* png_structp;
typedef void (*png_fnptr)(void);

struct png_struct_def {
    int jmpbuf[16];
    png_fnptr error_fn, warning_fn;
    png_voidp error_ptr;
    png_fnptr write_data_fn, read_data_fn;
    png_voidp io_ptr;
    png_fnptr read_user_transform_fn, write_user_transform_fn;
    png_voidp user_transform_ptr;
    png_byte user_transform_depth, user_transform_channels;
    png_uint_32 mode;              // +0x68
    png_uint_32 flags;
    png_uint_32 transformations;   // +0x70
    z_stream_s zstream;
    png_bytep zbuf;
    png_size_t zbuf_size;
    int zlib_level, zlib_method, zlib_window_bits, zlib_mem_level, zlib_strategy;
    png_uint_32 width, height, num_rows, usr_width, rowbytes, irowbytes, iwidth, row_number;
    png_bytep prev_row, row_buf, sub_row, up_row, avg_row, paeth_row;
    png_row_info row_info;
    png_uint_32 idat_size, crc;
    png_colorp palette;            // +0x114
    png_uint_16 num_palette;       // +0x118
    png_uint_16 num_trans;         // +0x11a
    png_byte chunk_name[5];
    png_byte compression, filter, interlaced, pass, do_filter;
    png_byte color_type;           // +0x126
    png_byte bit_depth;            // +0x127
    png_byte usr_bit_depth, pixel_depth, channels, usr_channels, sig_bytes;
    png_uint_16 filler;
    png_byte background_gamma_type;  // +0x130
    float background_gamma;          // +0x134
    png_color_16 background;         // +0x138
    png_color_16 background_1;       // +0x142
    png_fnptr output_flush_fn;
    png_uint_32 flush_dist, flush_rows;
    int gamma_shift;
    float gamma;                     // +0x15c
    float screen_gamma;              // +0x160
    png_bytep gamma_table;           // +0x164
    png_bytep gamma_from_1;          // +0x168
    png_bytep gamma_to_1;            // +0x16c
    png_uint_16pp gamma_16_table, gamma_16_from_1, gamma_16_to_1;
    png_color_8 sig_bit;             // +0x17c
    png_color_8 shift;
    png_bytep trans;                 // +0x188
    png_color_16 trans_values;       // +0x18c
};

#define PNG_COLOR_MASK_PALETTE 1
#define PNG_COLOR_MASK_COLOR 2
#define PNG_COLOR_TYPE_PALETTE (PNG_COLOR_MASK_COLOR | PNG_COLOR_MASK_PALETTE)

#define PNG_BACKGROUND_IS_GRAY 0x800
#define PNG_GAMMA_THRESHOLD 0.05

#define PNG_SHIFT 0x0008
#define PNG_BACKGROUND 0x0080
#define PNG_BACKGROUND_EXPAND 0x0100
#define PNG_EXPAND 0x1000
#define PNG_GAMMA 0x2000
#define PNG_GRAY_TO_RGB 0x4000
#define PNG_FILLER 0x8000L
#define PNG_STRIP_ALPHA 0x40000L
#define PNG_INVERT_ALPHA 0x80000L
#define PNG_RGB_TO_GRAY_ERR 0x200000L
#define PNG_RGB_TO_GRAY_WARN 0x400000L
#define PNG_RGB_TO_GRAY 0x600000L
#define PNG_EXPAND_tRNS 0x2000000L

#define PNG_BACKGROUND_GAMMA_UNKNOWN 0
#define PNG_BACKGROUND_GAMMA_SCREEN 1
#define PNG_BACKGROUND_GAMMA_FILE 2
#define PNG_BACKGROUND_GAMMA_UNIQUE 3

#define png_composite(composite, fg, alpha, bg)                               \
     { png_uint_16 temp = (png_uint_16)((png_uint_16)(fg) * (png_uint_16)(alpha) \
                        +        (png_uint_16)(bg)*(png_uint_16)(255 -       \
                        (png_uint_16)(alpha)) + (png_uint_16)128);           \
       (composite) = (png_byte)((temp + (temp >> 8)) >> 8); }

extern "C" void png_build_gamma_table(png_structp png_ptr);  // 0x008705a0 (same TU)

/* Initialize everything needed for the read.  This includes modifying
 * the palette.
 */
extern "C" void
png_init_read_transformations(png_structp png_ptr)
{
  {
   int color_type = png_ptr->color_type;

   /* Detect gray background and attempt to enable optimization
    * for gray --> RGB case */
   if ((png_ptr->transformations & PNG_BACKGROUND_EXPAND) &&
       !(color_type & PNG_COLOR_MASK_COLOR))
   {
          png_ptr->mode |= PNG_BACKGROUND_IS_GRAY;
   } else if ((png_ptr->transformations & PNG_BACKGROUND) &&
              !(png_ptr->transformations & PNG_BACKGROUND_EXPAND) &&
              (png_ptr->transformations & PNG_GRAY_TO_RGB) &&
              png_ptr->background.red == png_ptr->background.green &&
              png_ptr->background.red == png_ptr->background.blue)
   {
          png_ptr->mode |= PNG_BACKGROUND_IS_GRAY;
          png_ptr->background.gray = png_ptr->background.red;
   }

   if ((png_ptr->transformations & PNG_BACKGROUND_EXPAND) &&
       (png_ptr->transformations & PNG_EXPAND))
   {
      if (!(color_type & PNG_COLOR_MASK_COLOR))  /* i.e., GRAY or GRAY_ALPHA */
      {
         /* expand background and tRNS chunks */
         switch (png_ptr->bit_depth)
         {
            case 1:
               png_ptr->background.gray *= (png_uint_16)0xff;
               png_ptr->background.red = png_ptr->background.green
                 =  png_ptr->background.blue = png_ptr->background.gray;
               if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
               {
                 png_ptr->trans_values.gray *= (png_uint_16)0xff;
                 png_ptr->trans_values.red = png_ptr->trans_values.green
                   = png_ptr->trans_values.blue = png_ptr->trans_values.gray;
               }
               break;
            case 2:
               png_ptr->background.gray *= (png_uint_16)0x55;
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
               if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
               {
                 png_ptr->trans_values.gray *= (png_uint_16)0x55;
                 png_ptr->trans_values.red = png_ptr->trans_values.green
                   = png_ptr->trans_values.blue = png_ptr->trans_values.gray;
               }
               break;
            case 4:
               png_ptr->background.gray *= (png_uint_16)0x11;
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
               if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
               {
                 png_ptr->trans_values.gray *= (png_uint_16)0x11;
                 png_ptr->trans_values.red = png_ptr->trans_values.green
                   = png_ptr->trans_values.blue = png_ptr->trans_values.gray;
               }
               break;
            case 8:
            case 16:
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
               break;
         }
      }
      else if (color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_ptr->background.red   =
            png_ptr->palette[png_ptr->background.index].red;
         png_ptr->background.green =
            png_ptr->palette[png_ptr->background.index].green;
         png_ptr->background.blue  =
            png_ptr->palette[png_ptr->background.index].blue;

        if (png_ptr->transformations & PNG_INVERT_ALPHA)
        {
           if (!(png_ptr->transformations & PNG_EXPAND_tRNS))
           {
           /* invert the alpha channel (in tRNS) unless the pixels are
              going to be expanded, in which case leave it for later */
              int i,istop;
              istop=(int)png_ptr->num_trans;
              for (i=0; i<istop; i++)
                 png_ptr->trans[i] = (png_byte)(255 - png_ptr->trans[i]);
           }
        }
      }
   }

   png_ptr->background_1 = png_ptr->background;

   if ((color_type == PNG_COLOR_TYPE_PALETTE && png_ptr->num_trans != 0)
       && (fabs(png_ptr->screen_gamma * png_ptr->gamma - 1.0)
         < PNG_GAMMA_THRESHOLD))
   {
    int i,k;
    k=0;
    for (i=0; i<png_ptr->num_trans; i++)
    {
      if (png_ptr->trans[i] != 0 && png_ptr->trans[i] != 0xff)
        k=1; /* partial transparency is present */
    }
    if (k == 0)
      png_ptr->transformations &= ~PNG_GAMMA;
   }

   if ((png_ptr->transformations & (PNG_GAMMA | PNG_RGB_TO_GRAY)) &&
        png_ptr->gamma != 0.0)
   {
      png_build_gamma_table(png_ptr);
      if (png_ptr->transformations & PNG_BACKGROUND)
      {
         if (color_type == PNG_COLOR_TYPE_PALETTE)
         {
           /* could skip if no transparency and
           */
            png_color back, back_1;
            png_colorp palette = png_ptr->palette;
            int num_palette = png_ptr->num_palette;
            int i;
            if (png_ptr->background_gamma_type == PNG_BACKGROUND_GAMMA_FILE)
            {
               back.red = png_ptr->gamma_table[png_ptr->background.red];
               back.green = png_ptr->gamma_table[png_ptr->background.green];
               back.blue = png_ptr->gamma_table[png_ptr->background.blue];

               back_1.red = png_ptr->gamma_to_1[png_ptr->background.red];
               back_1.green = png_ptr->gamma_to_1[png_ptr->background.green];
               back_1.blue = png_ptr->gamma_to_1[png_ptr->background.blue];
            }
            else
            {
               double g, gs;

               switch (png_ptr->background_gamma_type)
               {
                  case PNG_BACKGROUND_GAMMA_SCREEN:
                     g = (png_ptr->screen_gamma);
                     gs = 1.0;
                     break;
                  case PNG_BACKGROUND_GAMMA_FILE:
                     g = 1.0 / (png_ptr->gamma);
                     gs = 1.0 / (png_ptr->gamma * png_ptr->screen_gamma);
                     break;
                  case PNG_BACKGROUND_GAMMA_UNIQUE:
                     g = 1.0 / (png_ptr->background_gamma);
                     gs = 1.0 / (png_ptr->background_gamma *
                                 png_ptr->screen_gamma);
                     break;
                  default:
                     g = 1.0;    /* back_1 */
                     gs = 1.0;   /* back */
               }

               if ( fabs(gs - 1.0) < PNG_GAMMA_THRESHOLD)
               {
                  back.red   = (png_byte)png_ptr->background.red;
                  back.green = (png_byte)png_ptr->background.green;
                  back.blue  = (png_byte)png_ptr->background.blue;
               }
               else
               {
                  back.red = (png_byte)(pow(
                     (double)png_ptr->background.red/255, gs) * 255.0 + .5);
                  back.green = (png_byte)(pow(
                     (double)png_ptr->background.green/255, gs) * 255.0 + .5);
                  back.blue = (png_byte)(pow(
                     (double)png_ptr->background.blue/255, gs) * 255.0 + .5);
               }

               back_1.red = (png_byte)(pow(
                  (double)png_ptr->background.red/255, g) * 255.0 + .5);
               back_1.green = (png_byte)(pow(
                  (double)png_ptr->background.green/255, g) * 255.0 + .5);
               back_1.blue = (png_byte)(pow(
                  (double)png_ptr->background.blue/255, g) * 255.0 + .5);
            }
            for (i = 0; i < num_palette; i++)
            {
               if (i < (int)png_ptr->num_trans && png_ptr->trans[i] != 0xff)
               {
                  if (png_ptr->trans[i] == 0)
                  {
                     palette[i] = back;
                  }
                  else /* if (png_ptr->trans[i] != 0xff) */
                  {
                     png_byte v, w;

                     v = png_ptr->gamma_to_1[palette[i].red];
                     png_composite(w, v, png_ptr->trans[i], back_1.red);
                     palette[i].red = png_ptr->gamma_from_1[w];

                     v = png_ptr->gamma_to_1[palette[i].green];
                     png_composite(w, v, png_ptr->trans[i], back_1.green);
                     palette[i].green = png_ptr->gamma_from_1[w];

                     v = png_ptr->gamma_to_1[palette[i].blue];
                     png_composite(w, v, png_ptr->trans[i], back_1.blue);
                     palette[i].blue = png_ptr->gamma_from_1[w];
                  }
               }
               else
               {
                  palette[i].red = png_ptr->gamma_table[palette[i].red];
                  palette[i].green = png_ptr->gamma_table[palette[i].green];
                  palette[i].blue = png_ptr->gamma_table[palette[i].blue];
               }
            }
            /* Prevent the transformations being done again, and make sure
             * that the now spurious alpha channel is stripped - the code
             * has just reduced background composition and gamma correction
             * to a simple alpha channel strip.
             */
            png_ptr->transformations &= ~PNG_BACKGROUND;
            png_ptr->transformations &= ~PNG_GAMMA;
            png_ptr->transformations |= PNG_STRIP_ALPHA;
         }
         /* if (png_ptr->background_gamma_type!=PNG_BACKGROUND_GAMMA_UNKNOWN) */
         else
         /* color_type != PNG_COLOR_TYPE_PALETTE */
         {
            double m = (double)(((png_uint_32)1 << png_ptr->bit_depth) - 1);
            double g = 1.0;
            double gs = 1.0;

            switch (png_ptr->background_gamma_type)
            {
               case PNG_BACKGROUND_GAMMA_SCREEN:
                  g = (png_ptr->screen_gamma);
                  gs = 1.0;
                  break;
               case PNG_BACKGROUND_GAMMA_FILE:
                  g = 1.0 / (png_ptr->gamma);
                  gs = 1.0 / (png_ptr->gamma * png_ptr->screen_gamma);
                  break;
               case PNG_BACKGROUND_GAMMA_UNIQUE:
                  g = 1.0 / (png_ptr->background_gamma);
                  gs = 1.0 / (png_ptr->background_gamma *
                     png_ptr->screen_gamma);
                  break;
            }

            png_ptr->background_1.gray = (png_uint_16)(pow(
               (double)png_ptr->background.gray / m, g) * m + .5);
            png_ptr->background.gray = (png_uint_16)(pow(
               (double)png_ptr->background.gray / m, gs) * m + .5);

            if ((png_ptr->background.red != png_ptr->background.green) ||
                (png_ptr->background.red != png_ptr->background.blue) ||
                (png_ptr->background.red != png_ptr->background.gray))
            {
               /* RGB or RGBA with color background */
               png_ptr->background_1.red = (png_uint_16)(pow(
                  (double)png_ptr->background.red / m, g) * m + .5);
               png_ptr->background_1.green = (png_uint_16)(pow(
                  (double)png_ptr->background.green / m, g) * m + .5);
               png_ptr->background_1.blue = (png_uint_16)(pow(
                  (double)png_ptr->background.blue / m, g) * m + .5);
               png_ptr->background.red = (png_uint_16)(pow(
                  (double)png_ptr->background.red / m, gs) * m + .5);
               png_ptr->background.green = (png_uint_16)(pow(
                  (double)png_ptr->background.green / m, gs) * m + .5);
               png_ptr->background.blue = (png_uint_16)(pow(
                  (double)png_ptr->background.blue / m, gs) * m + .5);
            }
            else
            {
               /* GRAY, GRAY ALPHA, RGB, or RGBA with gray background */
               png_ptr->background_1.red = png_ptr->background_1.green
                 = png_ptr->background_1.blue = png_ptr->background_1.gray;
               png_ptr->background.red = png_ptr->background.green
                 = png_ptr->background.blue = png_ptr->background.gray;
            }
         }
      }
      else
      /* transformation does not include PNG_BACKGROUND */
      if (color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_colorp palette = png_ptr->palette;
         int num_palette = png_ptr->num_palette;
         int i;

         for (i = 0; i < num_palette; i++)
         {
            palette[i].red = png_ptr->gamma_table[palette[i].red];
            palette[i].green = png_ptr->gamma_table[palette[i].green];
            palette[i].blue = png_ptr->gamma_table[palette[i].blue];
         }

         /* Done the gamma correction. */
         png_ptr->transformations &= ~PNG_GAMMA;
      }
   }
   else
   /* No GAMMA transformation */
   if ((png_ptr->transformations & PNG_BACKGROUND) &&
       (color_type == PNG_COLOR_TYPE_PALETTE))
   {
      int i;
      int istop = (int)png_ptr->num_trans;
      png_color back;
      png_colorp palette = png_ptr->palette;

      back.red   = (png_byte)png_ptr->background.red;
      back.green = (png_byte)png_ptr->background.green;
      back.blue  = (png_byte)png_ptr->background.blue;

      for (i = 0; i < istop; i++)
      {
         if (png_ptr->trans[i] == 0)
         {
            palette[i] = back;
         }
         else if (png_ptr->trans[i] != 0xff)
         {
            /* The png_composite() macro is defined in png.h */
            png_composite(palette[i].red, palette[i].red,
               png_ptr->trans[i], back.red);
            png_composite(palette[i].green, palette[i].green,
               png_ptr->trans[i], back.green);
            png_composite(palette[i].blue, palette[i].blue,
               png_ptr->trans[i], back.blue);
         }
      }

      /* Handled alpha, still need to strip the channel. */
      png_ptr->transformations &= ~PNG_BACKGROUND;
      png_ptr->transformations |= PNG_STRIP_ALPHA;
   }

   if ((png_ptr->transformations & PNG_SHIFT) &&
      (color_type == PNG_COLOR_TYPE_PALETTE))
   {
      png_uint_16 i;
      png_uint_16 istop = png_ptr->num_palette;
      int sr = 8 - png_ptr->sig_bit.red;
      int sg = 8 - png_ptr->sig_bit.green;
      int sb = 8 - png_ptr->sig_bit.blue;

      if (sr < 0 || sr > 8)
         sr = 0;
      if (sg < 0 || sg > 8)
         sg = 0;
      if (sb < 0 || sb > 8)
         sb = 0;
      for (i = 0; i < istop; i++)
      {
         png_ptr->palette[i].red >>= sr;
         png_ptr->palette[i].green >>= sg;
         png_ptr->palette[i].blue >>= sb;
      }
   }
  }
}
