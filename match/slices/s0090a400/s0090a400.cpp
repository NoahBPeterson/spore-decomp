// Slice s0090a400: expat 2.0.1 xmlparse.c parser lifecycle (parserCreate/parserInit/
// XML_ParserReset/XML_ParserCreate_MM/XML_ParserCreate/XML_ExternalEntityParserCreate and the
// prolog/external-PE processor entry points) plus the xmlrole.c handlers prolog2/entity5/
// condSect1/condSect2/declClose/entity6/notation3/notation4, as linked into SporeApp.exe.
// MIT license: Copyright (c) 1998-2000 Thai Open Source Software Center Ltd and Clark Cooper.
#include "types.h"
#include "../s00908c00/s00908c00.h"

// The XML namespace binding the original build keeps in .rdata at 0x0143ac78 (implicitContext).
// Declared extern so the address is materialised with `mov reg, offset` (5 bytes) as in the
// original, rather than folded into a direct load of the array's first dword.
extern const XML_Char g_xmlNamespace[];

// ---- prolog state handlers that live outside this slice ----
// internalSubset (0x90c240) is defined by slice s0090c240; externalSubset1 (0x90c3d0) and the
// terminal `error` handler (0xe31100, mislabelled as UTFWin::IWinProc::GetPriority by Ghidra)
// are defined by the neighbouring xmlrole.c build.
int PTRCALL internalSubset(PROLOG_STATE *state, int tok, const char *ptr,
                           const char *end, const ENCODING *enc);
int PTRCALL externalSubset1(PROLOG_STATE *state, int tok, const char *ptr,
                            const char *end, const ENCODING *enc);
int PTRCALL prologError(PROLOG_STATE *state, int tok, const char *ptr,
                        const char *end, const ENCODING *enc);

// xmlrole.c's setTopLevel():
//   ((state)->handler = ((state)->documentEntity ? internalSubset : externalSubset1))
static void PTRCALL setTopLevel(PROLOG_STATE *state)
{
  state->handler = state->documentEntity ? internalSubset : externalSubset1;
}

static const char KW_NDATA[] =
  { ASCII_N, ASCII_D, ASCII_A, ASCII_T, ASCII_A, '\0' };

// ---- whole-program register-convention helpers --------------------------------------------
// LTCG gave the small xmlparse.c internals register calling conventions in the original build.
// cl 15 (without whole-program optimization) puts the leading pointer arguments of a TU-local
// function in eax/ecx/edx, so these thin TU-static wrappers reproduce the original call sites.

static enum XML_Error __declspec(noinline)
FA_initializeEncoding(XML_Parser parser)
{
  return initializeEncoding(parser);
}

__declspec(noinline) static XML_Bool
FA_setContext(const XML_Char *context, XML_Parser parser)
{
  return setContext(parser, context);
}

__declspec(noinline) static const XML_Char *
FA_poolCopyString(const XML_Char *s, STRING_POOL *pool)
{
  return poolCopyString(pool, s);
}

__declspec(noinline) static DTD *
FA_dtdCreate(const XML_Memory_Handling_Suite *ms)
{
  return dtdCreate(ms);
}

static int FASTCALL common(PROLOG_STATE *state, int tok);

int PTRCALL prolog2(PROLOG_STATE *state, int tok, const char *ptr,
                    const char *end, const ENCODING *enc);
int PTRCALL entity5(PROLOG_STATE *state, int tok, const char *ptr,
                    const char *end, const ENCODING *enc);
int PTRCALL entity6(PROLOG_STATE *state, int tok, const char *ptr,
                    const char *end, const ENCODING *enc);
int PTRCALL condSect1(PROLOG_STATE *state, int tok, const char *ptr,
                      const char *end, const ENCODING *enc);
int PTRCALL condSect2(PROLOG_STATE *state, int tok, const char *ptr,
                      const char *end, const ENCODING *enc);
int PTRCALL declClose(PROLOG_STATE *state, int tok, const char *ptr,
                      const char *end, const ENCODING *enc);
int PTRCALL notation3(PROLOG_STATE *state, int tok, const char *ptr,
                      const char *end, const ENCODING *enc);
int PTRCALL notation4(PROLOG_STATE *state, int tok, const char *ptr,
                      const char *end, const ENCODING *enc);

// ============================================================================
// prologProcessor
// ============================================================================

// @ 0x0090a400
static enum XML_Error PTRCALL
prologProcessor(XML_Parser parser,
                const char *s,
                const char *end,
                const char **nextPtr)
{
  const char *next = s;
  int tok = XmlPrologTok(encoding, s, end, &next);
  return doProlog(parser, encoding, s, end, tok, next,
                  nextPtr, (XML_Bool)(ps_finalBuffer == 0));
}

// ============================================================================
// internalEntityProcessor
// ============================================================================

// @ 0x0090a460
static enum XML_Error PTRCALL
internalEntityProcessor(XML_Parser parser,
                        const char *s,
                        const char *end,
                        const char **nextPtr)
{
  ENTITY *entity;
  const char *textStart, *textEnd;
  const char *next;
  enum XML_Error result;
  OPEN_INTERNAL_ENTITY *openEntity = openInternalEntities;
  if (!openEntity)
    return XML_ERROR_UNEXPECTED_STATE;

  entity = openEntity->entity;
  textStart = ((char *)entity->textPtr) + entity->processed;
  textEnd = (char *)(entity->textPtr + entity->textLen);

  if (entity->is_param) {
    int tok = XmlPrologTok(internalEncoding, textStart, textEnd, &next);
    result = doProlog(parser, internalEncoding, textStart, textEnd, tok,
                      next, &next, XML_FALSE);
  }
  else
    result = doContent(parser, openEntity->startTagLevel, internalEncoding,
                       textStart, textEnd, &next, XML_FALSE);

  if (result != XML_ERROR_NONE)
    return result;
  else if (textEnd != next && ps_parsing == XML_SUSPENDED) {
    entity->processed = (int)(next - (char *)entity->textPtr);
    return result;
  }
  else {
    entity->open = XML_FALSE;
    openInternalEntities = openEntity->next;
    /* put openEntity back in list of free instances */
    openEntity->next = freeInternalEntities;
    freeInternalEntities = openEntity;
  }

  if (entity->is_param) {
    int tok;
    processor = prologProcessor;
    tok = XmlPrologTok(encoding, s, end, &next);
    return doProlog(parser, encoding, s, end, tok, next, nextPtr,
                    (XML_Bool)(ps_finalBuffer == 0));
  }
  else {
    processor = contentProcessor;
    /* see externalEntityContentProcessor vs contentProcessor */
    return doContent(parser, parentParser ? 1 : 0, encoding, s, end,
                     nextPtr, (XML_Bool)(ps_finalBuffer == 0));
  }
}

// ============================================================================
// prologInitProcessor
// ============================================================================

// @ 0x0090a5e0
static enum XML_Error PTRCALL
prologInitProcessor(XML_Parser parser,
                    const char *s,
                    const char *end,
                    const char **nextPtr)
{
  enum XML_Error result = FA_initializeEncoding(parser);
  if (result != XML_ERROR_NONE)
    return result;
  processor = prologProcessor;
  return prologProcessor(parser, s, end, nextPtr);
}

// ============================================================================
// externalParEntProcessor
// ============================================================================

// @ 0x0090a620
static enum XML_Error PTRCALL
externalParEntProcessor(XML_Parser parser,
                        const char *s,
                        const char *end,
                        const char **nextPtr)
{
  const char *next = s;
  int tok;

  tok = XmlPrologTok(encoding, s, end, &next);
  if (tok <= 0) {
    if (!ps_finalBuffer && tok != XML_TOK_INVALID) {
      *nextPtr = s;
      return XML_ERROR_NONE;
    }
    switch (tok) {
    case XML_TOK_INVALID:
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      return XML_ERROR_UNCLOSED_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_NONE:   /* start == end */
    default:
      break;
    }
  }
  /* This would cause the next stage, i.e. doProlog to be passed XML_TOK_BOM.
     However, when parsing an external subset, doProlog will not accept a BOM
     as valid, and report a syntax error, so we have to skip the BOM
  */
  else if (tok == XML_TOK_BOM) {
    s = next;
    tok = XmlPrologTok(encoding, s, end, &next);
  }

  processor = prologProcessor;
  return doProlog(parser, encoding, s, end, tok, next,
                  nextPtr, (XML_Bool)(ps_finalBuffer == 0));
}

// ============================================================================
// parserInit
// ============================================================================

// @ 0x0090a6f0
static void
parserInit(XML_Parser parser, const XML_Char *encodingName)
{
  processor = prologInitProcessor;
  XmlPrologStateInit(&prologState);
  protocolEncodingName = (encodingName != NULL
                          ? FA_poolCopyString(encodingName, &tempPool)
                          : NULL);
  curBase = NULL;
  XmlInitEncoding(&initEncoding, &encoding, 0);
  userData = NULL;
  handlerArg = NULL;
  startElementHandler = NULL;
  endElementHandler = NULL;
  characterDataHandler = NULL;
  processingInstructionHandler = NULL;
  commentHandler = NULL;
  startCdataSectionHandler = NULL;
  endCdataSectionHandler = NULL;
  defaultHandler = NULL;
  startDoctypeDeclHandler = NULL;
  endDoctypeDeclHandler = NULL;
  unparsedEntityDeclHandler = NULL;
  notationDeclHandler = NULL;
  startNamespaceDeclHandler = NULL;
  endNamespaceDeclHandler = NULL;
  notStandaloneHandler = NULL;
  externalEntityRefHandler = NULL;
  externalEntityRefHandlerArg = parser;
  skippedEntityHandler = NULL;
  elementDeclHandler = NULL;
  attlistDeclHandler = NULL;
  entityDeclHandler = NULL;
  xmlDeclHandler = NULL;
  bufferPtr = buffer;
  bufferEnd = buffer;
  parseEndByteIndex = 0;
  parseEndPtr = NULL;
  declElementType = NULL;
  declAttributeId = NULL;
  declEntity = NULL;
  doctypeName = NULL;
  doctypeSysid = NULL;
  doctypePubid = NULL;
  declAttributeType = NULL;
  declNotationName = NULL;
  declNotationPublicId = NULL;
  declAttributeIsCdata = XML_FALSE;
  declAttributeIsId = XML_FALSE;
  memset(&position, 0, sizeof(POSITION));
  errorCode = XML_ERROR_NONE;
  eventPtr = NULL;
  eventEndPtr = NULL;
  positionPtr = NULL;
  openInternalEntities = NULL;
  defaultExpandInternalEntities = XML_TRUE;
  tagLevel = 0;
  tagStack = NULL;
  inheritedBindings = NULL;
  nSpecifiedAtts = 0;
  unknownEncodingMem = NULL;
  unknownEncodingRelease = NULL;
  unknownEncodingData = NULL;
  parentParser = NULL;
  ps_parsing = XML_INITIALIZED;
#ifdef XML_DTD
  isParamEntity = XML_FALSE;
  useForeignDTD = XML_FALSE;
  paramEntityParsing = XML_PARAM_ENTITY_PARSING_NEVER;
#endif
}

// moves list of bindings to freeBindingList
static void FASTCALL
moveToFreeBindingList(XML_Parser parser, BINDING *bindings)
{
  while (bindings) {
    BINDING *b = bindings;
    bindings = bindings->nextTagBinding;
    b->nextTagBinding = freeBindingList;
    freeBindingList = b;
  }
}

// ============================================================================
// XML_ParserReset
// ============================================================================

// @ 0x0090a870
XML_Bool XMLCALL
XML_ParserReset(XML_Parser parser, const XML_Char *encodingName)
{
  TAG *tStk;
  OPEN_INTERNAL_ENTITY *openEntityList;

  if (parentParser)
    return XML_FALSE;
  /* move tagStack to freeTagList */
  tStk = tagStack;
  while (tStk) {
    TAG *tag = tStk;
    tStk = tStk->parent;
    tag->parent = freeTagList;
    moveToFreeBindingList(parser, tag->bindings);
    tag->bindings = NULL;
    freeTagList = tag;
  }
  /* move openInternalEntities to freeInternalEntities */
  openEntityList = openInternalEntities;
  while (openEntityList) {
    OPEN_INTERNAL_ENTITY *openEntity = openEntityList;
    openEntityList = openEntity->next;
    openEntity->next = freeInternalEntities;
    freeInternalEntities = openEntity;
  }
  moveToFreeBindingList(parser, inheritedBindings);
  FREE(unknownEncodingMem);
  if (unknownEncodingRelease)
    unknownEncodingRelease(unknownEncodingData);
  poolClear(&tempPool);
  poolClear(&temp2Pool);
  parserInit(parser, encodingName);
  dtdReset(_dtd, &parser->m_mem);
  return FA_setContext(g_xmlNamespace, parser);
}

// ============================================================================
// externalParEntInitProcessor
// ============================================================================

// @ 0x0090a990
static enum XML_Error PTRCALL
externalParEntInitProcessor(XML_Parser parser,
                            const char *s,
                            const char *end,
                            const char **nextPtr)
{
  enum XML_Error result = FA_initializeEncoding(parser);
  if (result != XML_ERROR_NONE)
    return result;

  /* we know now that XML_Parse(Buffer) has been called,
     so we consider the external parameter entity read */
  _dtd->paramEntityRead = XML_TRUE;

  if (prologState.inEntityValue) {
    processor = entityValueInitProcessor;
    return entityValueInitProcessor(parser, s, end, nextPtr);
  }
  else {
    processor = externalParEntProcessor;
    return externalParEntProcessor(parser, s, end, nextPtr);
  }
}

// ============================================================================
// parserCreate
// ============================================================================

// @ 0x0090a9f0
static XML_Parser
parserCreate(const XML_Char *encodingName,
             const XML_Memory_Handling_Suite *memsuite,
             const XML_Char *nameSep,
             DTD *dtd)
{
  XML_Parser parser;

  if (memsuite) {
    XML_Memory_Handling_Suite *mtemp;
    parser = (XML_Parser)
      memsuite->malloc_fcn(sizeof(struct XML_ParserStruct));
    if (parser != NULL) {
      mtemp = (XML_Memory_Handling_Suite *)&(parser->m_mem);
      mtemp->malloc_fcn = memsuite->malloc_fcn;
      mtemp->realloc_fcn = memsuite->realloc_fcn;
      mtemp->free_fcn = memsuite->free_fcn;
    }
  }
  else {
    XML_Memory_Handling_Suite *mtemp;
    parser = (XML_Parser)malloc(sizeof(struct XML_ParserStruct));
    if (parser != NULL) {
      mtemp = (XML_Memory_Handling_Suite *)&(parser->m_mem);
      mtemp->malloc_fcn = malloc;
      mtemp->realloc_fcn = realloc;
      mtemp->free_fcn = free;
    }
  }

  if (!parser)
    return parser;

  buffer = NULL;
  bufferLim = NULL;

  attsSize = INIT_ATTS_SIZE;
  atts = (ATTRIBUTE *)MALLOC(attsSize * sizeof(ATTRIBUTE));
  if (atts == NULL) {
    FREE(parser);
    return NULL;
  }
  dataBuf = (XML_Char *)MALLOC(INIT_DATA_BUF_SIZE * sizeof(XML_Char));
  if (dataBuf == NULL) {
    FREE(atts);
    FREE(parser);
    return NULL;
  }
  dataBufEnd = dataBuf + INIT_DATA_BUF_SIZE;

  if (dtd)
    _dtd = dtd;
  else {
    _dtd = FA_dtdCreate(&parser->m_mem);
    if (_dtd == NULL) {
      FREE(dataBuf);
      FREE(atts);
      FREE(parser);
      return NULL;
    }
  }

  freeBindingList = NULL;
  freeTagList = NULL;
  freeInternalEntities = NULL;

  groupSize = 0;
  groupConnector = NULL;

  unknownEncodingHandler = NULL;
  unknownEncodingHandlerData = NULL;

  namespaceSeparator = ASCII_EXCL;
  ns = XML_FALSE;
  ns_triplets = XML_FALSE;

  nsAtts = NULL;
  nsAttsVersion = 0;
  nsAttsPower = 0;

  poolInit(&tempPool, &(parser->m_mem));
  poolInit(&temp2Pool, &(parser->m_mem));
  parserInit(parser, encodingName);

  if (encodingName && !protocolEncodingName) {
    XML_ParserFree(parser);
    return NULL;
  }

  if (nameSep) {
    ns = XML_TRUE;
    internalEncoding = XmlGetInternalEncodingNS();
    namespaceSeparator = *nameSep;
  }
  else {
    internalEncoding = XmlGetInternalEncoding();
  }

  return parser;
}

// ============================================================================
// XML_ExternalEntityParserCreate
// ============================================================================

// @ 0x0090ac10
XML_Parser XMLCALL
XML_ExternalEntityParserCreate(XML_Parser oldParser,
                               const XML_Char *context,
                               const XML_Char *encodingName)
{
  XML_Parser parser = oldParser;
  DTD *newDtd = NULL;
  DTD *oldDtd = _dtd;
  XML_StartElementHandler oldStartElementHandler = startElementHandler;
  XML_EndElementHandler oldEndElementHandler = endElementHandler;
  XML_CharacterDataHandler oldCharacterDataHandler = characterDataHandler;
  XML_ProcessingInstructionHandler oldProcessingInstructionHandler
      = processingInstructionHandler;
  XML_CommentHandler oldCommentHandler = commentHandler;
  XML_StartCdataSectionHandler oldStartCdataSectionHandler
      = startCdataSectionHandler;
  XML_EndCdataSectionHandler oldEndCdataSectionHandler
      = endCdataSectionHandler;
  XML_DefaultHandler oldDefaultHandler = defaultHandler;
  XML_UnparsedEntityDeclHandler oldUnparsedEntityDeclHandler
      = unparsedEntityDeclHandler;
  XML_NotationDeclHandler oldNotationDeclHandler = notationDeclHandler;
  XML_StartNamespaceDeclHandler oldStartNamespaceDeclHandler
      = startNamespaceDeclHandler;
  XML_EndNamespaceDeclHandler oldEndNamespaceDeclHandler
      = endNamespaceDeclHandler;
  XML_NotStandaloneHandler oldNotStandaloneHandler = notStandaloneHandler;
  XML_ExternalEntityRefHandler oldExternalEntityRefHandler
      = externalEntityRefHandler;
  XML_SkippedEntityHandler oldSkippedEntityHandler = skippedEntityHandler;
  XML_UnknownEncodingHandler oldUnknownEncodingHandler
      = unknownEncodingHandler;
  XML_ElementDeclHandler oldElementDeclHandler = elementDeclHandler;
  XML_AttlistDeclHandler oldAttlistDeclHandler = attlistDeclHandler;
  XML_EntityDeclHandler oldEntityDeclHandler = entityDeclHandler;
  XML_XmlDeclHandler oldXmlDeclHandler = xmlDeclHandler;
  ELEMENT_TYPE * oldDeclElementType = declElementType;

  void *oldUserData = userData;
  void *oldHandlerArg = handlerArg;
  XML_Bool oldDefaultExpandInternalEntities = defaultExpandInternalEntities;
  XML_Parser oldExternalEntityRefHandlerArg = externalEntityRefHandlerArg;
#ifdef XML_DTD
  enum XML_ParamEntityParsing oldParamEntityParsing = paramEntityParsing;
  int oldInEntityValue = prologState.inEntityValue;
#endif
  XML_Bool oldns_triplets = ns_triplets;

#ifdef XML_DTD
  if (!context)
    newDtd = oldDtd;
#endif /* XML_DTD */

  /* Note that the magical uses of the pre-processor to make field
     access look more like C++ require that `parser' be overwritten
     here.  This makes this function more painful to follow than it
     would be otherwise.
  */
  if (ns) {
    XML_Char tmp[2];
    *tmp = namespaceSeparator;
    parser = parserCreate(encodingName, &parser->m_mem, tmp, newDtd);
  }
  else {
    parser = parserCreate(encodingName, &parser->m_mem, NULL, newDtd);
  }

  if (!parser)
    return NULL;

  startElementHandler = oldStartElementHandler;
  endElementHandler = oldEndElementHandler;
  characterDataHandler = oldCharacterDataHandler;
  processingInstructionHandler = oldProcessingInstructionHandler;
  commentHandler = oldCommentHandler;
  startCdataSectionHandler = oldStartCdataSectionHandler;
  endCdataSectionHandler = oldEndCdataSectionHandler;
  defaultHandler = oldDefaultHandler;
  unparsedEntityDeclHandler = oldUnparsedEntityDeclHandler;
  notationDeclHandler = oldNotationDeclHandler;
  startNamespaceDeclHandler = oldStartNamespaceDeclHandler;
  endNamespaceDeclHandler = oldEndNamespaceDeclHandler;
  notStandaloneHandler = oldNotStandaloneHandler;
  externalEntityRefHandler = oldExternalEntityRefHandler;
  skippedEntityHandler = oldSkippedEntityHandler;
  unknownEncodingHandler = oldUnknownEncodingHandler;
  elementDeclHandler = oldElementDeclHandler;
  attlistDeclHandler = oldAttlistDeclHandler;
  entityDeclHandler = oldEntityDeclHandler;
  xmlDeclHandler = oldXmlDeclHandler;
  declElementType = oldDeclElementType;
  userData = oldUserData;
  if (oldUserData == oldHandlerArg)
    handlerArg = userData;
  else
    handlerArg = parser;
  if (oldExternalEntityRefHandlerArg != oldParser)
    externalEntityRefHandlerArg = oldExternalEntityRefHandlerArg;
  defaultExpandInternalEntities = oldDefaultExpandInternalEntities;
  ns_triplets = oldns_triplets;
  parentParser = oldParser;
#ifdef XML_DTD
  paramEntityParsing = oldParamEntityParsing;
  prologState.inEntityValue = oldInEntityValue;
  if (context) {
#endif /* XML_DTD */
    if (!dtdCopy(_dtd, oldDtd, &parser->m_mem)
      || !FA_setContext(context, parser)) {
      XML_ParserFree(parser);
      return NULL;
    }
    processor = externalEntityInitProcessor;
#ifdef XML_DTD
  }
  else {
    /* The DTD instance referenced by _dtd is shared between the document's
       root parser and external PE parsers, therefore one does not need to
       call setContext. In addition, one also *must* not call setContext,
       because this would overwrite existing prefix->binding pointers in
       _dtd with ones that get destroyed with the external PE parser.
       This would leave those prefixes with dangling pointers.
    */
    isParamEntity = XML_TRUE;
    XmlPrologStateInitExternalEntity(&prologState);
    processor = externalParEntInitProcessor;
  }
#endif /* XML_DTD */
  return parser;
}

// ============================================================================
// XML_ParserCreate_MM
// ============================================================================

// @ 0x0090aed0
XML_Parser XMLCALL
XML_ParserCreate_MM(const XML_Char *encodingName,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *nameSep)
{
  XML_Parser parser = parserCreate(encodingName, memsuite, nameSep, NULL);
  if (parser != NULL && ns) {
    /* implicit context only set for root parser, since child
       parsers (i.e. external entity parsers) will inherit it
    */
    if (!FA_setContext(g_xmlNamespace, parser)) {
      XML_ParserFree(parser);
      return NULL;
    }
  }
  return parser;
}

// ============================================================================
// XML_ParserCreate
// ============================================================================

// @ 0x0090af20
XML_Parser XMLCALL
XML_ParserCreate(const XML_Char *encodingName)
{
  return XML_ParserCreate_MM(encodingName, NULL, NULL);
}

// ============================================================================
// xmlrole.c handlers
// ============================================================================

// xmlrole.c's common() (the original build inlines it at every use site).
static int FASTCALL
common(PROLOG_STATE *state, int tok)
{
#ifdef XML_DTD
  if (!state->documentEntity && tok == XML_TOK_PARAM_ENTITY_REF)
    return XML_ROLE_INNER_PARAM_ENTITY_REF;
#endif
  state->handler = prologError;
  return XML_ROLE_ERROR;
}

// @ 0x0090af70
int PTRCALL
prolog2(PROLOG_STATE *state,
        int tok,
        const char *ptr,
        const char *end,
        const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_PI:
    return XML_ROLE_PI;
  case XML_TOK_COMMENT:
    return XML_ROLE_COMMENT;
  case XML_TOK_INSTANCE_START:
    state->handler = prologError;
    return XML_ROLE_INSTANCE_START;
  }
  return common(state, tok);
}

// @ 0x0090b040
int PTRCALL
entity5(PROLOG_STATE *state,
        int tok,
        const char *ptr,
        const char *end,
        const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ENTITY_NONE;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return XML_ROLE_ENTITY_COMPLETE;
  }
  return common(state, tok);
}

// @ 0x0090b0e0
int PTRCALL
condSect1(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_OPEN_BRACKET:
    state->handler = externalSubset1;
    state->includeLevel += 1;
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}

// @ 0x0090b120
int PTRCALL
condSect2(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_OPEN_BRACKET:
    state->handler = externalSubset1;
    return XML_ROLE_IGNORE_SECT;
  }
  return common(state, tok);
}

// @ 0x0090b160
int PTRCALL
declClose(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return state->role_none;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return state->role_none;
  }
  return common(state, tok);
}

// @ 0x0090b1c0
int PTRCALL
entity6(PROLOG_STATE *state,
        int tok,
        const char *ptr,
        const char *end,
        const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ENTITY_NONE;
  case XML_TOK_NAME:
    state->handler = declClose;
    state->role_none = XML_ROLE_ENTITY_NONE;
    return XML_ROLE_ENTITY_NOTATION_NAME;
  }
  return common(state, tok);
}

// @ 0x0090b250
int PTRCALL
notation3(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NOTATION_NONE;
  case XML_TOK_LITERAL:
    state->handler = declClose;
    state->role_none = XML_ROLE_NOTATION_NONE;
    return XML_ROLE_NOTATION_SYSTEM_ID;
  }
  return common(state, tok);
}

// @ 0x0090b2a0
int PTRCALL
notation4(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NOTATION_NONE;
  case XML_TOK_LITERAL:
    state->handler = declClose;
    state->role_none = XML_ROLE_NOTATION_NONE;
    return XML_ROLE_NOTATION_SYSTEM_ID;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return XML_ROLE_NOTATION_NO_SYSTEM_ID;
  }
  return common(state, tok);
}
