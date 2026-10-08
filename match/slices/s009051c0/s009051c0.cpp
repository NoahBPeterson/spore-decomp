// 00905740 XML_Parse: expat 2.0.1 entry point (lib/xmlparse.c), as linked into SporeApp.exe.
// Shares the expat 2.0.1 declarations (struct XML_ParserStruct, ENCODING, Processor) of slice s00908c00.
#define XML_UNICODE_WCHAR_T
#include "../s00908c00/s00908c00.h"

enum XML_Status XMLCALL
XML_Parse(XML_Parser parser, const char *s, int len, int isFinal)
{
  switch (ps_parsing) {
  case XML_FINISHED:
    errorCode = XML_ERROR_FINISHED;
    return XML_STATUS_ERROR;
  case XML_SUSPENDED:
    errorCode = XML_ERROR_SUSPENDED;
    return XML_STATUS_ERROR;
  }
  ps_parsing = XML_PARSING;
  if (len == 0) {
    ps_finalBuffer = (XML_Bool)isFinal;
    if (!isFinal)
      return XML_STATUS_OK;
    positionPtr = bufferPtr;
    parseEndPtr = bufferEnd;
    errorCode = processor(parser, bufferPtr, bufferEnd, &bufferPtr);
    if (errorCode == XML_ERROR_NONE) {
      switch (ps_parsing) {
      case XML_SUSPENDED:
        XmlUpdatePosition(encoding, positionPtr, bufferPtr, &position);
        positionPtr = bufferPtr;
        return XML_STATUS_SUSPENDED;
      case XML_INITIALIZED:
      case XML_PARSING:
        ps_parsing = XML_FINISHED;
        return XML_STATUS_OK;
      default:
        return XML_STATUS_OK;
      }
    }
    eventEndPtr = eventPtr;
    processor = errorProcessor;
    return XML_STATUS_ERROR;
  }
  {
    void *buff = XML_GetBuffer(parser, len);
    if (buff == NULL)
      return XML_STATUS_ERROR;
    memcpy(buff, s, len);
    return XML_ParseBuffer(parser, len, isFinal);
  }
}
