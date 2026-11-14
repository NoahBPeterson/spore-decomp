// Link-time lane for f_013c3550 (0x013c3550), tools/matching/ltcg.py: the retail function's
// 49-byte fingerprint extent does not end at its own `ret` -- it runs over the linker's int3
// padding (14 bytes, to the next 16-byte boundary) and the `ret` of a 1-byte empty COMDAT
// that the retail link folded next to it. No single C++ function can emit those trailing
// bytes, so this row is built the way the retail image was laid out: the slice and this file
// are compiled /GL and linked with /LTCG, and the 49 bytes at the function are cut out of
// the linked image. The empty function a08_link_pad_ret (s013c31a0.cpp, directly after
// f_013c3550) supplies the adjacent 1-byte `ret`; the slice source itself is unchanged
// C++ for the function body. The original is a cdecl void atexit teardown registered by
// the CRT, i.e. called from outside this /GL set, hence the export.
#pragma comment(linker, "/EXPORT:?f_013c3550@@YAXXZ")

extern "C" void a08_ltcg_stub_anchor() {}
