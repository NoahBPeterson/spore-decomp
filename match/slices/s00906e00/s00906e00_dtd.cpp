// Slice s00906e00 -- expat 2.0.1 lib/xmlparse.c compiled verbatim (same route as s00906030).
// XML_UNICODE build: XML_Char is 16-bit, which is why the pool helpers store `mov word`.
//
// Flags: /O2 /MD /Gy /TC -DXML_NS=1 -DXML_DTD=1 -DXML_CONTEXT_BYTES=1024
//        -DBYTEORDER=1234 -DHAVE_MEMMOVE -DXML_STATIC -DXML_UNICODE
//
// @ 0x00907070 dtdCopy
#include "expat/xmlparse.c"
