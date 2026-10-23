// expat 2.0.1 lib/xmlparse.c, compiled verbatim as linked into SporeApp.exe
// (expat object built with XML_UNICODE, XML_NS, XML_DTD, XML_CONTEXT_BYTES=1024).
//
// VA map:
//   00906030  storeEntityValue
//   009064c0  reportProcessingInstruction
//   009065e0  reportComment
//   00906680  getAttributeId
//   00906890  setContext                 (non-byte-exact, see nonmatching.txt)
//   00906b10  copyEntityTable
//   00906c60  externalEntityInitProcessor3
//   00906d60  entityValueProcessor
//
// Flags: /O2 /MD /Gy /TC -DXML_NS=1 -DXML_DTD=1 -DXML_CONTEXT_BYTES=1024
//        -DBYTEORDER=1234 -DHAVE_MEMMOVE -DXML_STATIC -DXML_UNICODE  (see manifest.txt)
//
// XML_UNICODE is what the original build used: XML_Char is a 16-bit character there, which is
// why the temp-pool helpers store `mov word ptr [...], ax` and advance the pool pointer by 2.

// @ 0x00906030 storeEntityValue
// @ 0x009064c0 reportProcessingInstruction
// @ 0x009065e0 reportComment
// @ 0x00906680 getAttributeId
// @ 0x00906890 setContext
// @ 0x00906b10 copyEntityTable
// @ 0x00906c60 externalEntityInitProcessor3
// @ 0x00906d60 entityValueProcessor
#include "expat/xmlparse.c"
