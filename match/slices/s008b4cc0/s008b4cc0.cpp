// Slice s008b4cc0 -- T2K / PFR font engine glyph accessors.
#include "types.h"
typedef unsigned char uint8; typedef signed char int8; typedef unsigned short uint16;
typedef short int16; typedef unsigned int uint; typedef unsigned int uint32;
typedef int int32;

struct tsiMemObject;
struct InputStream;
struct GlyphBuilder;

// ---------------------------------------------------------------------------
// Shared object layouts (see slice s008b3ae0). All extern callees are ordinary
// cdecl unless noted.
// ---------------------------------------------------------------------------

// PFR glyph record returned by FUN_008b0480.
struct PFRGlyph {
    char      pad00[0x34];
    int16     w34;                 // 0x34  command/contour tag
    int16     w36;                 // 0x36  open-contour flag
    int16     cnt;                 // 0x38  point count
    char      pad3a[0x44 - 0x3a];
    int16*    px;                  // 0x44  x coordinate array
    int16*    py;                  // 0x48  y coordinate array
};

extern "C" PFRGlyph* FUN_008b0480(tsiMemObject* mem, int, int, int, int);
extern "C" void     Seek_InputStream(InputStream* s, int off);                    // 0x008cc580
extern "C" void*    tsi_AllocMem(tsiMemObject* mem, int size);                    // 0x008d1260
extern "C" void     PeekInt16(InputStream* s, void* dst, int n);                  // 0x008cc220
extern "C" void     PFRBuildChar(...);                                            // 0x008b3ae0
extern "C" void     tsi_DeAllocMem(tsiMemObject* mem, void* p);                   // 0x008d1440
extern "C" void     glyph_CloseContour(PFRGlyph* g);                              // 0x008afde0
extern "C" int      FUN_008b1b80(PFRGlyph* g);                                    // 0x008b1b80
// FUN_008b19e0(handle20 /*ecx*/, handle24, id, outA, outB, outC): the id-th
// record; reads/writes three adjacent int16 out-slots. `this` (handle20) uses
// the MSVC __thiscall convention, which is what the call sites emit.
struct H19e0;
struct HRec {
    int FUN_008b19e0(void* h24, int id, int16* a, int16* b, int16* c); // 0x008b19e0
};
extern "C" void     Delete_GlyphClass(PFRGlyph* g);                               // 0x008b0280

struct PFRClass;
// FUN_008b1c70 takes its object in eax, its key in edi, and one stack slot out.
extern "C" void     FUN_008b1c70(PFRClass* o, int key, int16* out);               // 0x008b1c70

// FUN_008b1c70 leaves the found index in the stack out-slot; the two accessors
// below read the *last* values it produced through the same slot the original
// reused (see the note in nonmatching.txt). Modelled here as globals so the
// source stays behaviour-complete; the original threads them through locals.
static int16 g_foundKey = 0;
static uint  FoundIdx() { return (uint)(uint16)g_foundKey; }
static uint16 KeyIdx()  { return (uint16)g_foundKey; }

// The PFR "class" object (this is the same structure used across the module).
struct PFRClass {
    tsiMemObject* mem;             // 0x00
    InputStream*  stream;          // 0x04
    char          pad08[0x0c - 0x08];
    char*         charTable;       // 0x0c  entries of 8 bytes: [+2] size, [+4] offset
    char          pad10[0x1c - 0x10];
    uint8         b1c;             // 0x1c  char-code signedness / vertical flag
    char          pad1d[0x2c - 0x1d];
    uint32        baseOff;         // 0x2c  added to each char offset
    char          pad30[0x34 - 0x30];
    uint8         inContour;       // 0x34  a contour is currently open
    char          pad35[0x90 - 0x35];
    uint32        metX;            // 0x90
    uint32        metY;            // 0x94
    char          pad98[0xa6 - 0x98];
    int16         haveChar;        // 0xa6
    char          pada8[0xac - 0xa8];
    uint8         fAc;             // 0xac
    uint8         fAd;             // 0xad
    char          padae[0xfc - 0xae];
    PFRGlyph*     glyph;           // 0xfc  current glyph (FUN_008b0480 result)
    char          pad100[0x104 - 0x100];
    char*         metricsTable;    // 0x104  [+0x10] -> uint16 per char index
    int16         numChars;        // 0x108
    char          pad10a[0x10c - 0x10a];
    uint16        width;           // 0x10c
    // BuildPFRMetricsEtc (0x008b4f00) reads 0x108/0x10c as 32-bit ints.
    uint32        f110;            // 0x110
    int32         f114;            // 0x114
    int32         f118;            // 0x118
    int32         f11c;            // 0x11c
    int32         f120;            // 0x120
    uint32        f124;            // 0x124
    char          pad128[0x1ec - 0x128];
    uint32        f1ec;            // 0x1ec
};

// ---------------------------------------------------------------------------
// @ 0x008b4cc0
// tsi_PFRGetGlyphByIndex: build the glyph for character index `idx` and return
// it; writes the advance width through param_3 and the advance height through
// param_4.
// ---------------------------------------------------------------------------
extern "C" int FUN_008b4cc0(PFRClass* o, uint16 idx, int16* outW, uint16* outH, int reserved)
{
    int16  count = o->numChars;
    uint16 uWidth;
    int16* psx;
    int16  maxx;
    int    i, n, y0, y1, adv;
    void*  buf;
    uint16 size;
    char*  e;

    if (o->haveChar != 0 && o->fAd != 0 && o->fAc == 0)
        o->fAc = 1;

    buf = FUN_008b0480(o->mem, 0, 0, 0, 0);
    o->glyph = (PFRGlyph*)buf;
    ((PFRGlyph*)buf)->w34 = 3;

    if ((int)idx < (int)count) {
        e = o->charTable + idx * 8;
        size = *(uint16*)(e + 2);
        Seek_InputStream(o->stream, *(int*)(e + 4) + o->baseOff);
        buf = tsi_AllocMem(o->mem, size);
        if (buf != 0) {
            PeekInt16(o->stream, buf, size);
            PFRBuildChar(o, buf, *(int*)(e + 4), size, 0x10000, 0x10000, 0, 0, reserved);
            if (o->b1c == 0) {
                o->metX = *(uint16*)(*(int*)(o->metricsTable + 0x10) + idx * 2);
                o->metY = 0;
            } else {
                o->metX = 0;
                o->metY = *(uint16*)(*(int*)(o->metricsTable + 0x10) + idx * 2);
            }
            if (o->glyph->w36 == 0 || o->inContour != 0) {
                glyph_CloseContour(o->glyph);
                o->inContour = 0;
            }
            tsi_DeAllocMem(o->mem, buf);
        }
    }

    {
        PFRGlyph* g = o->glyph;
        n = g->cnt;
        g->py[n]    = 0;
        g->px[n]    = 0;
        g->py[n + 1] = (int16)o->metY;
        g->px[n + 1] = (int16)o->metX;
        *outW = (int16)o->metX;

        y0 = g->px[n];
        y1 = g->px[n + 1];
        psx = g->py;
        maxx = psx[0];
        i = 1;
        while (i < n) {
            if (maxx < psx[i]) maxx = psx[i];
            i++;
        }
        uWidth = o->width;
        psx[n + 2] = (int16)((int)uWidth / 10 + maxx);
        adv = (int16)((y1 + y0) >> 1);
        g->px[n + 2] = adv;
        psx[n + 3] = (int16)(psx[n + 2] - uWidth);
        g->px[n + 3] = adv;
        *outH = uWidth;
        o->glyph = 0;
        FUN_008b1b80(g);
        return (int)g;
    }
}

// ---------------------------------------------------------------------------
// @ 0x008b4f00
// BuildPFRMetricsEtc: compute the four side bearings (0x110/0x114/0x118/0x11c)
// from the "2"/"7" string records and, when a bearing is still unset, from the
// extreme of the corresponding glyph; 0x10c is the glyph height.
// ---------------------------------------------------------------------------
extern "C" int16 FUN_008b4f00(PFRClass* o)
{
    int16 l10, lc, l8, l4;

    o->f110 = 0;
    o->f114 = 0x7fff;
    o->f118 = 0xffff8001;
    o->f11c = 0x7fff;

    // FUN_008b19e0(handle20, handle24, id, a, b, c): fetch the record with the id.
    if (((HRec*)*(void**)((char*)o + 0x20))->FUN_008b19e0(*(void**)((char*)o + 0x24), 2, &l10, &lc, &l4) != 0 &&
        ((HRec*)*(void**)((char*)o + 0x20))->FUN_008b19e0(*(void**)((char*)o + 0x24), 7, &l10, &lc, &l4) != 0)
        goto after_records;

    o->f114 = l10;
    o->f118 = -(int)lc;
    o->f11c = l8;
    o->f120 = l4;

after_records:
    o->f124 = *(uint32*)((char*)o + 0xb8);

    {
        uint16 i = 0;
        if ((int16)o->numChars > 0) {
            do {
                int16* p = *(int16**)(*(int*)((char*)o + 0x100) + 0xc);
                p[i] = 0;
                i = (uint16)(i + 1);
            } while ((int)i < (int)(int16)o->numChars);
        }
    }

    if (o->f114 == 0x7fff) {
        l4 = 0;
        FUN_008b1c70(o, 0x66, &l4);
        g_foundKey = l4;
        *(uint*)((char*)o + 0x1ec) = (uint)(FoundIdx() & 0xff);
        if (l4 != 0) {
            PFRGlyph* g = (PFRGlyph*)FUN_008b4cc0(o, (uint)KeyIdx(), &l10, (uint16*)&lc, 0);
            if (g != 0) {
                int16* py = g->py;
                int16  mx = py[0];
                for (int i = 1; i < g->cnt; i++)
                    if (mx < py[i]) mx = py[i];
                o->f114 = mx;
                Delete_GlyphClass(g);
            }
        }
    }

    if (o->f118 == 0xffff8001) {
        l4 = 0;
        FUN_008b1c70(o, 0x67, &l4);
        g_foundKey = l4;
        *(uint*)((char*)o + 0x1ec) = (uint)(FoundIdx() & 0xff);
        if (l4 != 0) {
            PFRGlyph* g = (PFRGlyph*)FUN_008b4cc0(o, (uint)KeyIdx(), &l10, (uint16*)&lc, 0);
            if (g != 0) {
                int16* py = g->py;
                int16  mn = py[0];
                for (int i = 1; i < g->cnt; i++)
                    if (py[i] < mn) mn = py[i];
                o->f118 = mn;
                Delete_GlyphClass(g);
            }
        }
    }

    o->f110 = 0x20;
    if (o->f114 == 0x7fff) {
        int t = (int)o->width * 3;
        o->f114 = (int)(t + ((uint32)t >> 31 & 3)) >> 2;
    }
    if (o->f118 == 0xffff8001) {
        int w = (int)o->width;
        o->f118 = -(int)(w + ((uint32)w >> 31 & 3)) >> 2;
    }
    if (o->f11c == 0x7fff)
        o->f11c = (o->width - o->f114) + o->f118;
    if (o->f11c < 0)
        o->f11c = 0;
    return 0;
}

// ---------------------------------------------------------------------------
