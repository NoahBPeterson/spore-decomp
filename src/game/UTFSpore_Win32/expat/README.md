# expat 2.0.1 (as linked into SporeApp.exe)

These files are `#include` wrappers around the published expat 2.0.1 sources (expat is MIT-licensed; its notice stays in
the release, which `tools/ci/setup_oss.sh` unpacks to `work/third_party/src/expat-2.0.1`). Do not edit them; anything Spore's bytes need
differently belongs in `../xmltok.cpp`.

Used by `../xmltok.cpp`, which follows expat's `xmltok.c`: `xmltok_impl.c` is included once for each of the `normal_`,
`little2_` and `big2_` encodings, with the encoding macros defined around each include exactly as `xmltok.c` does.

Build defines (the `winconfig.h` set plus what the slices use): `XML_STATIC`, `XML_UNICODE` (so `XML_Char` is `unsigned short`),
`XML_NS 1`, `XML_DTD 1`, `XML_CONTEXT_BYTES 1024`, `BYTEORDER 1234`, `HAVE_MEMMOVE`. `FASTCALL`, `PTRCALL` and `PTRFASTCALL`
stay empty (`internal.h` default), `XMLCALL` is `__cdecl`.

| File | Used for |
| --- | --- |
| `xmltok_impl.c` | the scanners, instantiated per encoding |
| `xmltok_impl.h`, `xmltok.h` | `BT_*`, `XML_TOK_*`, `ENCODING`, `POSITION`, `ATTRIBUTE` |
| `ascii.h` | `ASCII_*` constants |
| `expat_external.h`, `internal.h` | `XML_Char`, `XMLCALL`, `FASTCALL`/`PTRCALL` |
