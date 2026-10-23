// Slice s008590d0 -- IJG libjpeg 6a decompression: colour conversion, Huffman
// entropy decoding and the inverse-DCT manager, linked into SporeApp.exe.
//
// Eleven functions, all byte-exact (manifest.txt):
//
//   jdcolor.c  008590d0 build_ycc_rgb_table      008591a0 ycc_rgb_convert
//              008592c0 null_convert             00859350 grayscale_convert
//              00859380 ycck_cmyk_convert        008594d0 jinit_color_deconverter
//   jdhuff.c   008599f0 jpeg_make_d_derived_tbl  00859bb0 jpeg_fill_bit_buffer
//              00859cc0 jpeg_huff_decode         00859db0 process_restart
//   jddctmgr.c 00859980 jinit_inverse_dct
//
// Each module is a vendored upstream translation unit (work/third_party/src/
// jpeg-6a) pulled in by a thin wrapper under this directory that compiles it
// verbatim as C (/TC).  No source was reconstructed by hand.
//
// Two things about the retail build are needed to reproduce the bytes:
//
//  1. The retail jpeglib.h is patched (see the local jpeglib.h, shared with
//     slices s00858190 / s0085bb90).  jpeg_decompress_struct inserts
//     `unsigned char retail_comment[1024]; int retail_comment_flag;` right
//     after CCIR601_sampling, so every field from max_h_samp_factor on is
//     shifted +0x404 versus stock 6a: sample_range_limit +0x544,
//     unread_marker +0x5a0, marker +0x5b8, entropy +0x5bc, idct +0x5c0,
//     upsample +0x5c4, cconvert +0x5c8, cquantize +0x5cc, plus a trailing
//     read_dht flag at +0x5d0.  The error manager's msg_parm union is 80 bytes
//     (JMSG_LENGTH_MAX 80).  Without this header the colour-conversion bodies
//     differ only in the cconvert displacement (cinfo+0x1c4 instead of
//     +0x5c8), i.e. two bytes.
//
//  2. The module was compiled with the buffer-security check OFF: /GS-.  With
//     /GS on, jpeg_make_d_derived_tbl grows a stack cookie (sub esp,0x520 +
//     `mov eax,fs:[0] / xor eax,esp / mov [esp+0x51c],eax`) and a different
//     frame layout; with /GS- it matches exactly.
//
// Other details worth recording:
//
//  * jinit_color_deconverter is the one function whose image symbol extent is
//    wrong: SporeApp's symbol table runs 008594d0 for 1192 bytes, spanning into
//    the next function (jddctmgr.c start_pass at 00859660).  The real body is
//    392 bytes -- 368 bytes of code, three bytes of `lea ecx,[ecx]` padding and
//    the 20-byte switch jump table -- and it is byte-exact over that extent.
//
//  * /O2 reproduces the retail compiler's static-function calling convention
//    for build_ycc_rgb_table (cinfo arrives in EAX) and its idiom recognition
//    in jpeg_make_d_derived_tbl, where `while (i--) huffsize[p++] = l;` becomes
//    a memset call, exactly as in the image.
//
//  * jdcolor.c's start_pass_dcolor and jdhuff.c/jddctmgr.c helpers outside this
//    slice's VAs are compiled along with the units but are not claimed here.
//
// Flags: /O2 /arch:SSE /MD /Gy /TC /GS- /Iwork/third_party/src/jpeg-6a
//        /Iwork/third_party/build/jpeg-6a-inc
//
// This file is documentation only; it is not compiled and is not in the
// manifest.
