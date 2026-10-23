// Slice s00906030 -- expat 2.0.1 lib/xmlparse.c as statically linked into SporeApp.exe,
// reproduced by compiling the upstream translation unit verbatim (same route as the
// s0090a400 / s0090e9f0 expat slices).
//
//   xmlparse.cpp  expat/lib/xmlparse.c  (copied verbatim into expat/ next to it)
//     00906030  storeEntityValue
//     009064c0  reportProcessingInstruction
//     009065e0  reportComment
//     00906680  getAttributeId
//     00906890  setContext                    -- not byte-exact, see nonmatching.txt
//     00906b10  copyEntityTable
//     00906c60  externalEntityInitProcessor3
//     00906d60  entityValueProcessor
//
// Identification: the binary's build used XML_UNICODE (XML_Char is 16-bit), which shows up as
// `mov word ptr [pool->ptr], ax` / `add pool->ptr, 2` in the pool helpers; with that define
// seven of the eight targets are byte-identical to the pristine upstream file.  Build macros:
// XML_NS=1 XML_DTD=1 XML_CONTEXT_BYTES=1024 BYTEORDER=1234 HAVE_MEMMOVE XML_STATIC XML_UNICODE
// (the same set as winconfig.h, plus the 16-bit character mode).  Flags /O2 /MD /Gy /TC.
//
// No function bodies live here; they are emitted by xmlparse.cpp, which carries the
// `// @ 0x... <name>` markers.

// @ 0x00906030 storeEntityValue
// @ 0x009064c0 reportProcessingInstruction
// @ 0x009065e0 reportComment
// @ 0x00906680 getAttributeId
// @ 0x00906890 setContext
// @ 0x00906b10 copyEntityTable
// @ 0x00906c60 externalEntityInitProcessor3
// @ 0x00906d60 entityValueProcessor
