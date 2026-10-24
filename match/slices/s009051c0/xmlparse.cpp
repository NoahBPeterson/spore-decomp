// expat 2.0.1 lib/xmlparse.c, compiled verbatim as linked into SporeApp.exe
// (expat object built with XML_UNICODE, XML_NS, XML_DTD, XML_CONTEXT_BYTES=1024).
//
// VA map:
//   009051c0  dtdDestroy
//   009053b0  poolAppend
//   00905410  poolCopyString
//   00905450  poolCopyStringN
//   009054b0  poolAppendString
//   00905500  poolStoreString
//   00905540  getElementType
//   009055d0  XML_ParserFree
//   00905870  cdataSectionProcessor
//   00905930  ignoreSectionProcessor
//   00905990  processXmlDecl
//   00905bd0  appendAttributeValue      -- local override, see below
//
// Flags: /O2 /MD /Gy /TC -DXML_NS=1 -DXML_DTD=1 -DXML_CONTEXT_BYTES=1024
//        -DBYTEORDER=1234 -DHAVE_MEMMOVE -DXML_STATIC -DXML_UNICODE
//
// The upstream translation unit is shared with the sibling expat slices; it is included
// verbatim from slice s00906030's untouched copy.  Eleven of the twelve targets are then
// byte-identical to the pristine file.  The exception is appendAttributeValue: in the Spore
// build the call to reportDefault() that upstream keeps commented out in the
// `else if (!entity)` arm of the XML_TOK_ENTITY_REF case is live code (the binary tests
// `pool == &parser->m_tempPool && parser->m_defaultHandler` and calls reportDefault), so that
// one function is compiled from a local override below while the rest of the TU stays as-is.
//
// @ 0x009051c0 dtdDestroy
// @ 0x009053b0 poolAppend
// @ 0x00905410 poolCopyString
// @ 0x00905450 poolCopyStringN
// @ 0x009054b0 poolAppendString
// @ 0x00905500 poolStoreString
// @ 0x00905540 getElementType
// @ 0x009055d0 XML_ParserFree
// @ 0x00905870 cdataSectionProcessor
// @ 0x00905930 ignoreSectionProcessor
// @ 0x00905990 processXmlDecl
#define appendAttributeValue appendAttributeValueAsUpstream
#include "../s00906030/expat/xmlparse.c"
#undef appendAttributeValue

/* appendAttributeValue (0x00905bd0): expat 2.0.1 lib/xmlparse.c verbatim, except that the
   reportDefault() call documented and commented out by upstream in the `else if (!entity)`
   arm of the XML_TOK_ENTITY_REF case is enabled, which is what the linked Spore object does. */
// @ 0x00905bd0 appendAttributeValue
static enum XML_Error
appendAttributeValue(XML_Parser parser, const ENCODING *enc, XML_Bool isCdata,
                     const char *ptr, const char *end,
                     STRING_POOL *pool)
{
  DTD * const dtd = _dtd;  /* save one level of indirection */
  for (;;) {
    const char *next;
    int tok = XmlAttributeValueTok(enc, ptr, end, &next);
    switch (tok) {
    case XML_TOK_NONE:
      return XML_ERROR_NONE;
    case XML_TOK_INVALID:
      if (enc == encoding)
        eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (enc == encoding)
        eventPtr = ptr;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_CHAR_REF:
      {
        XML_Char buf[XML_ENCODE_MAX];
        int i;
        int n = XmlCharRefNumber(enc, ptr);
        if (n < 0) {
          if (enc == encoding)
            eventPtr = ptr;
          return XML_ERROR_BAD_CHAR_REF;
        }
        if (!isCdata
            && n == 0x20 /* space */
            && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
          break;
        n = XmlEncode(n, (ICHAR *)buf);
        if (!n) {
          if (enc == encoding)
            eventPtr = ptr;
          return XML_ERROR_BAD_CHAR_REF;
        }
        for (i = 0; i < n; i++) {
          if (!poolAppendChar(pool, buf[i]))
            return XML_ERROR_NO_MEMORY;
        }
      }
      break;
    case XML_TOK_DATA_CHARS:
      if (!poolAppend(pool, enc, ptr, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_TRAILING_CR:
      next = ptr + enc->minBytesPerChar;
      /* fall through */
    case XML_TOK_ATTRIBUTE_VALUE_S:
    case XML_TOK_DATA_NEWLINE:
      if (!isCdata && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
        break;
      if (!poolAppendChar(pool, 0x20))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_ENTITY_REF:
      {
        const XML_Char *name;
        ENTITY *entity;
        char checkEntityDecl;
        XML_Char ch = (XML_Char) XmlPredefinedEntityName(enc,
                                              ptr + enc->minBytesPerChar,
                                              next - enc->minBytesPerChar);
        if (ch) {
          if (!poolAppendChar(pool, ch))
                return XML_ERROR_NO_MEMORY;
          break;
        }
        name = poolStoreString(&temp2Pool, enc,
                               ptr + enc->minBytesPerChar,
                               next - enc->minBytesPerChar);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        entity = (ENTITY *)lookup(&dtd->generalEntities, name, 0);
        poolDiscard(&temp2Pool);
        /* First, determine if a check for an existing declaration is needed;
           if yes, check that the entity exists, and that it is internal.
        */
        if (pool == &dtd->pool)  /* are we called from prolog? */
          checkEntityDecl =
#ifdef XML_DTD
              prologState.documentEntity &&
#endif /* XML_DTD */
              (dtd->standalone
               ? !openInternalEntities
               : !dtd->hasParamEntityRefs);
        else /* if (pool == &tempPool): we are called from content */
          checkEntityDecl = !dtd->hasParamEntityRefs || dtd->standalone;
        if (checkEntityDecl) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal)
            return XML_ERROR_ENTITY_DECLARED_IN_PE;
        }
        else if (!entity) {
          /* Cannot report skipped entity here - see comments on
             skippedEntityHandler.
          if (skippedEntityHandler)
            skippedEntityHandler(handlerArg, name, 0);
          */
          /* Upstream keeps this call commented out ("Cannot call the default handler
             because this would be out of sync with the call to the startElementHandler");
             the linked Spore object has it enabled. */
          if ((pool == &tempPool) && defaultHandler)
            reportDefault(parser, enc, ptr, next);
          break;
        }
        if (entity->open) {
          if (enc == encoding)
            eventPtr = ptr;
          return XML_ERROR_RECURSIVE_ENTITY_REF;
        }
        if (entity->notation) {
          if (enc == encoding)
            eventPtr = ptr;
          return XML_ERROR_BINARY_ENTITY_REF;
        }
        if (!entity->textPtr) {
          if (enc == encoding)
            eventPtr = ptr;
              return XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF;
        }
        else {
          enum XML_Error result;
          const XML_Char *textEnd = entity->textPtr + entity->textLen;
          entity->open = XML_TRUE;
          result = appendAttributeValue(parser, internalEncoding, isCdata,
                                        (char *)entity->textPtr,
                                        (char *)textEnd, pool);
          entity->open = XML_FALSE;
          if (result)
            return result;
        }
      }
      break;
    default:
      if (enc == encoding)
        eventPtr = ptr;
      return XML_ERROR_UNEXPECTED_STATE;
    }
    ptr = next;
  }
  /* not reached */
}

/* The compiler drops a static function that nothing references, and in this TU the only
   caller of the upstream-named appendAttributeValue is storeAttributeValue; keep this
   override in the object (as the linked object keeps it) by pinning its address. */
enum XML_Error (* const SporeAppendAttributeValueOverride)(XML_Parser, const ENCODING *,
                                                           XML_Bool, const char *,
                                                           const char *, STRING_POOL *)
  = appendAttributeValue;