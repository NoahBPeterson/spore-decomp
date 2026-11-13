// Link-time lane for f_013c1b90 (0x013c1b90), tools/matching/ltcg.py: the retail function's
// 33-byte fingerprint extent does not end at its own `ret` -- it runs over the linker's int3
// padding (9 bytes, to the next 16-byte boundary) and the `ret` of the 1-byte empty function
// the retail link placed next to it at 0x013c1bb0 (absent from the retail function list).
// No single C++ function can emit those trailing bytes, so this row is built the way the
// retail image was laid out: the slice and this file are compiled /GL and linked with /LTCG,
// and the 33 bytes at the function are cut out of the linked image. The empty function
// a07_link_pad_ret (s013bed20.cpp, directly after f_013c1b90) supplies the adjacent 1-byte
// `ret`; the function body itself is unchanged C++. The original is a cdecl void atexit
// teardown registered with the CRT, i.e. called from outside this /GL set, hence the export.
#pragma comment(linker, "/EXPORT:?f_013c1b90@@YAXXZ")

extern "C" void a07_ltcg_stub_anchor() {}
