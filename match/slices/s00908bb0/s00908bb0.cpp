// Slice s00908bb0: expat 2.0.1 xmlparse.c -- contentProcessor (the content
// Processor entry that runs doContent and then stores the raw names).
// MIT license: Copyright (c) 1998-2000 Thai Open Source Software Center Ltd
// and Clark Cooper.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include "../s00908c00/s00908c00.h"

// 0x009036b0
int storeRawNames(char *parser);

// @ 0x00908bb0
enum XML_Error PTRCALL
contentProcessor(XML_Parser parser,
                 const char *start,
                 const char *end,
                 const char **endPtr)
{
  enum XML_Error result = doContent(parser, 0, encoding, start, end,
                                    endPtr, (XML_Bool)(ps_finalBuffer == 0));
  if (result == XML_ERROR_NONE) {
    if (!(XML_Bool)storeRawNames((char *)parser))
      return XML_ERROR_NO_MEMORY;
  }
  return result;
}
