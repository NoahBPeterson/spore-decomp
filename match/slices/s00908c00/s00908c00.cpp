// 00908c00 doProlog: expat 2.0.1 prolog/DTD state machine (lib/xmlparse.c), as linked into SporeApp.exe.
#include "s00908c00.h"

enum XML_Error
doProlog(XML_Parser parser,
         const ENCODING *enc,
         const char *s,
         const char *end,
         int tok,
         const char *next,
         const char **nextPtr,
         XML_Bool haveMore)
{
#ifdef XML_DTD
  static const XML_Char externalSubsetName[] = { ASCII_HASH , '\0' };
#endif /* XML_DTD */
  static const XML_Char atypeCDATA[] = 
      { ASCII_C, ASCII_D, ASCII_A, ASCII_T, ASCII_A, '\0' };
  static const XML_Char atypeID[] = { ASCII_I, ASCII_D, '\0' };
  static const XML_Char atypeIDREF[] =
      { ASCII_I, ASCII_D, ASCII_R, ASCII_E, ASCII_F, '\0' };
  static const XML_Char atypeIDREFS[] =
      { ASCII_I, ASCII_D, ASCII_R, ASCII_E, ASCII_F, ASCII_S, '\0' };
  static const XML_Char atypeENTITY[] =
      { ASCII_E, ASCII_N, ASCII_T, ASCII_I, ASCII_T, ASCII_Y, '\0' };
  static const XML_Char atypeENTITIES[] = { ASCII_E, ASCII_N,
      ASCII_T, ASCII_I, ASCII_T, ASCII_I, ASCII_E, ASCII_S, '\0' };
  static const XML_Char atypeNMTOKEN[] = {
      ASCII_N, ASCII_M, ASCII_T, ASCII_O, ASCII_K, ASCII_E, ASCII_N, '\0' };
  static const XML_Char atypeNMTOKENS[] = { ASCII_N, ASCII_M, ASCII_T,
      ASCII_O, ASCII_K, ASCII_E, ASCII_N, ASCII_S, '\0' };
  static const XML_Char notationPrefix[] = { ASCII_N, ASCII_O, ASCII_T,
      ASCII_A, ASCII_T, ASCII_I, ASCII_O, ASCII_N, ASCII_LPAREN, '\0' };
  static const XML_Char enumValueSep[] = { ASCII_PIPE, '\0' };
  static const XML_Char enumValueStart[] = { ASCII_LPAREN, '\0' };

  /* save one level of indirection */
  DTD * const dtd = _dtd; 

  const char **eventPP;
  const char **eventEndPP;
  enum XML_Content_Quant quant;

  if (enc == encoding) {
    eventPP = &eventPtr;
    eventEndPP = &eventEndPtr;
  }
  else {
    eventPP = &(openInternalEntities->internalEventPtr);
    eventEndPP = &(openInternalEntities->internalEventEndPtr);
  }

  for (;;) {
    int role;
    XML_Bool handleDefault = XML_TRUE;
    *eventPP = s;
    *eventEndPP = next;
    if (tok <= 0) {
      if (haveMore && tok != XML_TOK_INVALID) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      switch (tok) {
      case XML_TOK_INVALID:
        *eventPP = next;
        return XML_ERROR_INVALID_TOKEN;
      case XML_TOK_PARTIAL:
        return XML_ERROR_UNCLOSED_TOKEN;
      case XML_TOK_PARTIAL_CHAR:
        return XML_ERROR_PARTIAL_CHAR;
      case XML_TOK_NONE:
#ifdef XML_DTD
        /* for internal PE NOT referenced between declarations */
        if (enc != encoding && !openInternalEntities->betweenDecl) {
          *nextPtr = s;
          return XML_ERROR_NONE;
        }
        /* WFC: PE Between Declarations - must check that PE contains
           complete markup, not only for external PEs, but also for
           internal PEs if the reference occurs between declarations.
        */
        if (isParamEntity || enc != encoding) {
          if (XmlTokenRole(&prologState, XML_TOK_NONE, end, end, enc)
              == XML_ROLE_ERROR)
            return XML_ERROR_INCOMPLETE_PE;
          *nextPtr = s;
          return XML_ERROR_NONE;
        }
#endif /* XML_DTD */
        return XML_ERROR_NO_ELEMENTS;
      default:
        tok = -tok;
        next = end;
        break;
      }
    }
    role = XmlTokenRole(&prologState, tok, s, next, enc);
    switch (role) {
    case XML_ROLE_XML_DECL:
      {
        enum XML_Error result = processXmlDecl(parser, 0, s, next);
        if (result != XML_ERROR_NONE)
          return result;
        enc = encoding;
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_DOCTYPE_NAME:
      if (startDoctypeDeclHandler) {
        doctypeName = poolStoreString(&tempPool, enc, s, next);
        if (!doctypeName)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&tempPool);
        doctypePubid = NULL;
        handleDefault = XML_FALSE;
      }
      doctypeSysid = NULL; /* always initialize to NULL */
      break;
    case XML_ROLE_DOCTYPE_INTERNAL_SUBSET:
      if (startDoctypeDeclHandler) {
        startDoctypeDeclHandler(handlerArg, doctypeName, doctypeSysid,
                                doctypePubid, 1);
        doctypeName = NULL;
        poolClear(&tempPool);
        handleDefault = XML_FALSE;
      }
      break;
#ifdef XML_DTD
    case XML_ROLE_TEXT_DECL:
      {
        enum XML_Error result = processXmlDecl(parser, 1, s, next);
        if (result != XML_ERROR_NONE)
          return result;
        enc = encoding;
        handleDefault = XML_FALSE;
      }
      break;
#endif /* XML_DTD */
    case XML_ROLE_DOCTYPE_PUBLIC_ID:
#ifdef XML_DTD
      useForeignDTD = XML_FALSE;
      declEntity = (ENTITY *)lookup(&dtd->paramEntities,
                                    externalSubsetName,
                                    sizeof(ENTITY));
      if (!declEntity)
        return XML_ERROR_NO_MEMORY;
#endif /* XML_DTD */
      dtd->hasParamEntityRefs = XML_TRUE;
      if (startDoctypeDeclHandler) {
        if (!XmlIsPublicId(enc, s, next, eventPP))
          return XML_ERROR_PUBLICID;
        doctypePubid = poolStoreString(&tempPool, enc,
                                       s + enc->minBytesPerChar,
                                       next - enc->minBytesPerChar);
        if (!doctypePubid)
          return XML_ERROR_NO_MEMORY;
        normalizePublicId((XML_Char *)doctypePubid);
        poolFinish(&tempPool);
        handleDefault = XML_FALSE;
        goto alreadyChecked;
      }
      /* fall through */
    case XML_ROLE_ENTITY_PUBLIC_ID:
      if (!XmlIsPublicId(enc, s, next, eventPP))
        return XML_ERROR_PUBLICID;
    alreadyChecked:
      if (dtd->keepProcessing && declEntity) {
        XML_Char *tem = poolStoreString(&dtd->pool,
                                        enc,
                                        s + enc->minBytesPerChar,
                                        next - enc->minBytesPerChar);
        if (!tem)
          return XML_ERROR_NO_MEMORY;
        normalizePublicId(tem);
        declEntity->publicId = tem;
        poolFinish(&dtd->pool);
        if (entityDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_DOCTYPE_CLOSE:
      if (doctypeName) {
        startDoctypeDeclHandler(handlerArg, doctypeName,
                                doctypeSysid, doctypePubid, 0);
        poolClear(&tempPool);
        handleDefault = XML_FALSE;
      }
      /* doctypeSysid will be non-NULL in the case of a previous
         XML_ROLE_DOCTYPE_SYSTEM_ID, even if startDoctypeDeclHandler
         was not set, indicating an external subset
      */
#ifdef XML_DTD
      if (doctypeSysid || useForeignDTD) {
        XML_Bool hadParamEntityRefs = dtd->hasParamEntityRefs;
        dtd->hasParamEntityRefs = XML_TRUE;
        if (paramEntityParsing && externalEntityRefHandler) {
          ENTITY *entity = (ENTITY *)lookup(&dtd->paramEntities,
                                            externalSubsetName,
                                            sizeof(ENTITY));
          if (!entity)
            return XML_ERROR_NO_MEMORY;
          if (useForeignDTD)
            entity->base = curBase;
          dtd->paramEntityRead = XML_FALSE;
          if (!externalEntityRefHandler(externalEntityRefHandlerArg,
                                        0,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId))
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          if (dtd->paramEntityRead) {
            if (!dtd->standalone && 
                notStandaloneHandler && 
                !notStandaloneHandler(handlerArg))
              return XML_ERROR_NOT_STANDALONE;
          }
          /* if we didn't read the foreign DTD then this means that there
             is no external subset and we must reset dtd->hasParamEntityRefs
          */
          else if (!doctypeSysid)
            dtd->hasParamEntityRefs = hadParamEntityRefs;
          /* end of DTD - no need to update dtd->keepProcessing */
        }
        useForeignDTD = XML_FALSE;
      }
#endif /* XML_DTD */
      if (endDoctypeDeclHandler) {
        endDoctypeDeclHandler(handlerArg);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_INSTANCE_START:
#ifdef XML_DTD
      /* if there is no DOCTYPE declaration then now is the
         last chance to read the foreign DTD
      */
      if (useForeignDTD) {
        XML_Bool hadParamEntityRefs = dtd->hasParamEntityRefs;
        dtd->hasParamEntityRefs = XML_TRUE;
        if (paramEntityParsing && externalEntityRefHandler) {
          ENTITY *entity = (ENTITY *)lookup(&dtd->paramEntities,
                                            externalSubsetName,
                                            sizeof(ENTITY));
          if (!entity)
            return XML_ERROR_NO_MEMORY;
          entity->base = curBase;
          dtd->paramEntityRead = XML_FALSE;
          if (!externalEntityRefHandler(externalEntityRefHandlerArg,
                                        0,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId))
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          if (dtd->paramEntityRead) {
            if (!dtd->standalone &&
                notStandaloneHandler &&
                !notStandaloneHandler(handlerArg))
              return XML_ERROR_NOT_STANDALONE;
          }
          /* if we didn't read the foreign DTD then this means that there
             is no external subset and we must reset dtd->hasParamEntityRefs
          */
          else
            dtd->hasParamEntityRefs = hadParamEntityRefs;
          /* end of DTD - no need to update dtd->keepProcessing */
        }
      }
#endif /* XML_DTD */
      processor = contentProcessor;
      return contentProcessor(parser, s, end, nextPtr);
    case XML_ROLE_ATTLIST_ELEMENT_NAME:
      declElementType = getElementType(parser, enc, s, next);
      if (!declElementType)
        return XML_ERROR_NO_MEMORY;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_NAME:
      declAttributeId = getAttributeId(parser, enc, s, next);
      if (!declAttributeId)
        return XML_ERROR_NO_MEMORY;
      declAttributeIsCdata = XML_FALSE;
      declAttributeType = NULL;
      declAttributeIsId = XML_FALSE;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_CDATA:
      declAttributeIsCdata = XML_TRUE;
      declAttributeType = atypeCDATA;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_ID:
      declAttributeIsId = XML_TRUE;
      declAttributeType = atypeID;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_IDREF:
      declAttributeType = atypeIDREF;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_IDREFS:
      declAttributeType = atypeIDREFS;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_ENTITY:
      declAttributeType = atypeENTITY;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_ENTITIES:
      declAttributeType = atypeENTITIES;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_NMTOKEN:
      declAttributeType = atypeNMTOKEN;
      goto checkAttListDeclHandler;
    case XML_ROLE_ATTRIBUTE_TYPE_NMTOKENS:
      declAttributeType = atypeNMTOKENS;
    checkAttListDeclHandler:
      if (dtd->keepProcessing && attlistDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ATTRIBUTE_ENUM_VALUE:
    case XML_ROLE_ATTRIBUTE_NOTATION_VALUE:
      if (dtd->keepProcessing && attlistDeclHandler) {
        const XML_Char *prefix;
        if (declAttributeType) {
          prefix = enumValueSep;
        }
        else {
          prefix = (role == XML_ROLE_ATTRIBUTE_NOTATION_VALUE
                    ? notationPrefix
                    : enumValueStart);
        }
        if (!poolAppendString(&tempPool, prefix))
          return XML_ERROR_NO_MEMORY;
        if (!poolAppend(&tempPool, enc, s, next))
          return XML_ERROR_NO_MEMORY;
        declAttributeType = tempPool.start;
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_IMPLIED_ATTRIBUTE_VALUE:
    case XML_ROLE_REQUIRED_ATTRIBUTE_VALUE:
      if (dtd->keepProcessing) {
        if (!defineAttribute(declElementType, declAttributeId,
                             declAttributeIsCdata, declAttributeIsId,
                             0, parser))
          return XML_ERROR_NO_MEMORY;
        if (attlistDeclHandler && declAttributeType) {
          if (*declAttributeType == XML_T(ASCII_LPAREN)
              || (*declAttributeType == XML_T(ASCII_N)
                  && declAttributeType[1] == XML_T(ASCII_O))) {
            /* Enumerated or Notation type */
            if (!poolAppendChar(&tempPool, XML_T(ASCII_RPAREN))
                || !poolAppendChar(&tempPool, XML_T('\0')))
              return XML_ERROR_NO_MEMORY;
            declAttributeType = tempPool.start;
            poolFinish(&tempPool);
          }
          *eventEndPP = s;
          attlistDeclHandler(handlerArg, declElementType->name,
                             declAttributeId->name, declAttributeType,
                             0, role == XML_ROLE_REQUIRED_ATTRIBUTE_VALUE);
          poolClear(&tempPool);
          handleDefault = XML_FALSE;
        }
      }
      break;
    case XML_ROLE_DEFAULT_ATTRIBUTE_VALUE:
    case XML_ROLE_FIXED_ATTRIBUTE_VALUE:
      if (dtd->keepProcessing) {
        const XML_Char *attVal;
        enum XML_Error result =
          storeAttributeValue(parser, enc, declAttributeIsCdata,
                              s + enc->minBytesPerChar,
                              next - enc->minBytesPerChar,
                              &dtd->pool);
        if (result)
          return result;
        attVal = poolStart(&dtd->pool);
        poolFinish(&dtd->pool);
        /* ID attributes aren't allowed to have a default */
        if (!defineAttribute(declElementType, declAttributeId,
                             declAttributeIsCdata, XML_FALSE, attVal, parser))
          return XML_ERROR_NO_MEMORY;
        if (attlistDeclHandler && declAttributeType) {
          if (*declAttributeType == XML_T(ASCII_LPAREN)
              || (*declAttributeType == XML_T(ASCII_N)
                  && declAttributeType[1] == XML_T(ASCII_O))) {
            /* Enumerated or Notation type */
            if (!poolAppendChar(&tempPool, XML_T(ASCII_RPAREN))
                || !poolAppendChar(&tempPool, XML_T('\0')))
              return XML_ERROR_NO_MEMORY;
            declAttributeType = tempPool.start;
            poolFinish(&tempPool);
          }
          *eventEndPP = s;
          attlistDeclHandler(handlerArg, declElementType->name,
                             declAttributeId->name, declAttributeType,
                             attVal,
                             role == XML_ROLE_FIXED_ATTRIBUTE_VALUE);
          poolClear(&tempPool);
          handleDefault = XML_FALSE;
        }
      }
      break;
    case XML_ROLE_ENTITY_VALUE:
      if (dtd->keepProcessing) {
        enum XML_Error result = storeEntityValue(parser, enc,
                                            s + enc->minBytesPerChar,
                                            next - enc->minBytesPerChar);
        if (declEntity) {
          declEntity->textPtr = poolStart(&dtd->entityValuePool);
          declEntity->textLen = (int)(poolLength(&dtd->entityValuePool));
          poolFinish(&dtd->entityValuePool);
          if (entityDeclHandler) {
            *eventEndPP = s;
            entityDeclHandler(handlerArg,
                              declEntity->name,
                              declEntity->is_param,
                              declEntity->textPtr,
                              declEntity->textLen,
                              curBase, 0, 0, 0);
            handleDefault = XML_FALSE;
          }
        }
        else
          poolDiscard(&dtd->entityValuePool);
        if (result != XML_ERROR_NONE)
          return result;
      }
      break;
    case XML_ROLE_DOCTYPE_SYSTEM_ID:
#ifdef XML_DTD
      useForeignDTD = XML_FALSE;
#endif /* XML_DTD */
      dtd->hasParamEntityRefs = XML_TRUE;
      if (startDoctypeDeclHandler) {
        doctypeSysid = poolStoreString(&tempPool, enc,
                                       s + enc->minBytesPerChar,
                                       next - enc->minBytesPerChar);
        if (doctypeSysid == NULL)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&tempPool);
        handleDefault = XML_FALSE;
      }
#ifdef XML_DTD
      else
        /* use externalSubsetName to make doctypeSysid non-NULL
           for the case where no startDoctypeDeclHandler is set */
        doctypeSysid = externalSubsetName;
#endif /* XML_DTD */
      if (!dtd->standalone
#ifdef XML_DTD
          && !paramEntityParsing
#endif /* XML_DTD */
          && notStandaloneHandler
          && !notStandaloneHandler(handlerArg))
        return XML_ERROR_NOT_STANDALONE;
#ifndef XML_DTD
      break;
#else /* XML_DTD */
      if (!declEntity) {
        declEntity = (ENTITY *)lookup(&dtd->paramEntities,
                                      externalSubsetName,
                                      sizeof(ENTITY));
        if (!declEntity)
          return XML_ERROR_NO_MEMORY;
        declEntity->publicId = NULL;
      }
      /* fall through */
#endif /* XML_DTD */
    case XML_ROLE_ENTITY_SYSTEM_ID:
      if (dtd->keepProcessing && declEntity) {
        declEntity->systemId = poolStoreString(&dtd->pool, enc,
                                               s + enc->minBytesPerChar,
                                               next - enc->minBytesPerChar);
        if (!declEntity->systemId)
          return XML_ERROR_NO_MEMORY;
        declEntity->base = curBase;
        poolFinish(&dtd->pool);
        if (entityDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_ENTITY_COMPLETE:
      if (dtd->keepProcessing && declEntity && entityDeclHandler) {
        *eventEndPP = s;
        entityDeclHandler(handlerArg,
                          declEntity->name,
                          declEntity->is_param,
                          0,0,
                          declEntity->base,
                          declEntity->systemId,
                          declEntity->publicId,
                          0);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_ENTITY_NOTATION_NAME:
      if (dtd->keepProcessing && declEntity) {
        declEntity->notation = poolStoreString(&dtd->pool, enc, s, next);
        if (!declEntity->notation)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&dtd->pool);
        if (unparsedEntityDeclHandler) {
          *eventEndPP = s;
          unparsedEntityDeclHandler(handlerArg,
                                    declEntity->name,
                                    declEntity->base,
                                    declEntity->systemId,
                                    declEntity->publicId,
                                    declEntity->notation);
          handleDefault = XML_FALSE;
        }
        else if (entityDeclHandler) {
          *eventEndPP = s;
          entityDeclHandler(handlerArg,
                            declEntity->name,
                            0,0,0,
                            declEntity->base,
                            declEntity->systemId,
                            declEntity->publicId,
                            declEntity->notation);
          handleDefault = XML_FALSE;
        }
      }
      break;
    case XML_ROLE_GENERAL_ENTITY_NAME:
      {
        if (XmlPredefinedEntityName(enc, s, next)) {
          declEntity = NULL;
          break;
        }
        if (dtd->keepProcessing) {
          const XML_Char *name = poolStoreString(&dtd->pool, enc, s, next);
          if (!name)
            return XML_ERROR_NO_MEMORY;
          declEntity = (ENTITY *)lookup(&dtd->generalEntities, name,
                                        sizeof(ENTITY));
          if (!declEntity)
            return XML_ERROR_NO_MEMORY;
          if (declEntity->name != name) {
            poolDiscard(&dtd->pool);
            declEntity = NULL;
          }
          else {
            poolFinish(&dtd->pool);
            declEntity->publicId = NULL;
            declEntity->is_param = XML_FALSE;
            /* if we have a parent parser or are reading an internal parameter
               entity, then the entity declaration is not considered "internal"
            */
            declEntity->is_internal = !(parentParser || openInternalEntities);
            if (entityDeclHandler)
              handleDefault = XML_FALSE;
          }
        }
        else {
          poolDiscard(&dtd->pool);
          declEntity = NULL;
        }
      }
      break;
    case XML_ROLE_PARAM_ENTITY_NAME:
#ifdef XML_DTD
      if (dtd->keepProcessing) {
        const XML_Char *name = poolStoreString(&dtd->pool, enc, s, next);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        declEntity = (ENTITY *)lookup(&dtd->paramEntities,
                                           name, sizeof(ENTITY));
        if (!declEntity)
          return XML_ERROR_NO_MEMORY;
        if (declEntity->name != name) {
          poolDiscard(&dtd->pool);
          declEntity = NULL;
        }
        else {
          poolFinish(&dtd->pool);
          declEntity->publicId = NULL;
          declEntity->is_param = XML_TRUE;
          /* if we have a parent parser or are reading an internal parameter
             entity, then the entity declaration is not considered "internal"
          */
          declEntity->is_internal = !(parentParser || openInternalEntities);
          if (entityDeclHandler)
            handleDefault = XML_FALSE;
        }
      }
      else {
        poolDiscard(&dtd->pool);
        declEntity = NULL;
      }
#else /* not XML_DTD */
      declEntity = NULL;
#endif /* XML_DTD */
      break;
    case XML_ROLE_NOTATION_NAME:
      declNotationPublicId = NULL;
      declNotationName = NULL;
      if (notationDeclHandler) {
        declNotationName = poolStoreString(&tempPool, enc, s, next);
        if (!declNotationName)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&tempPool);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_NOTATION_PUBLIC_ID:
      if (!XmlIsPublicId(enc, s, next, eventPP))
        return XML_ERROR_PUBLICID;
      if (declNotationName) {  /* means notationDeclHandler != NULL */
        XML_Char *tem = poolStoreString(&tempPool,
                                        enc,
                                        s + enc->minBytesPerChar,
                                        next - enc->minBytesPerChar);
        if (!tem)
          return XML_ERROR_NO_MEMORY;
        normalizePublicId(tem);
        declNotationPublicId = tem;
        poolFinish(&tempPool);
        handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_NOTATION_SYSTEM_ID:
      if (declNotationName && notationDeclHandler) {
        const XML_Char *systemId
          = poolStoreString(&tempPool, enc,
                            s + enc->minBytesPerChar,
                            next - enc->minBytesPerChar);
        if (!systemId)
          return XML_ERROR_NO_MEMORY;
        *eventEndPP = s;
        notationDeclHandler(handlerArg,
                            declNotationName,
                            curBase,
                            systemId,
                            declNotationPublicId);
        handleDefault = XML_FALSE;
      }
      poolClear(&tempPool);
      break;
    case XML_ROLE_NOTATION_NO_SYSTEM_ID:
      if (declNotationPublicId && notationDeclHandler) {
        *eventEndPP = s;
        notationDeclHandler(handlerArg,
                            declNotationName,
                            curBase,
                            0,
                            declNotationPublicId);
        handleDefault = XML_FALSE;
      }
      poolClear(&tempPool);
      break;
    case XML_ROLE_ERROR:
      switch (tok) {
      case XML_TOK_PARAM_ENTITY_REF:
        /* PE references in internal subset are
           not allowed within declarations. */  
        return XML_ERROR_PARAM_ENTITY_REF;
      case XML_TOK_XML_DECL:
        return XML_ERROR_MISPLACED_XML_PI;
      default:
        return XML_ERROR_SYNTAX;
      }
#ifdef XML_DTD
    case XML_ROLE_IGNORE_SECT:
      {
        enum XML_Error result;
        if (defaultHandler)
          reportDefault(parser, enc, s, next);
        handleDefault = XML_FALSE;
        result = doIgnoreSection(parser, enc, &next, end, nextPtr, haveMore);
        if (result != XML_ERROR_NONE)
          return result;
        else if (!next) {
          processor = ignoreSectionProcessor;
          return result;
        }
      }
      break;
#endif /* XML_DTD */
    case XML_ROLE_GROUP_OPEN:
      if (prologState.level >= groupSize) {
        if (groupSize) {
          char *temp = (char *)REALLOC(groupConnector, groupSize *= 2);
          if (temp == NULL)
            return XML_ERROR_NO_MEMORY;
          groupConnector = temp;
          if (dtd->scaffIndex) {
            int *temp = (int *)REALLOC(dtd->scaffIndex,
                          groupSize * sizeof(int));
            if (temp == NULL)
              return XML_ERROR_NO_MEMORY;
            dtd->scaffIndex = temp;
          }
        }
        else {
          groupConnector = (char *)MALLOC(groupSize = 32);
          if (!groupConnector)
            return XML_ERROR_NO_MEMORY;
        }
      }
      groupConnector[prologState.level] = 0;
      if (dtd->in_eldecl) {
        int myindex = nextScaffoldPart(parser);
        if (myindex < 0)
          return XML_ERROR_NO_MEMORY;
        dtd->scaffIndex[dtd->scaffLevel] = myindex;
        dtd->scaffLevel++;
        dtd->scaffold[myindex].type = XML_CTYPE_SEQ;
        if (elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;
    case XML_ROLE_GROUP_SEQUENCE:
      if (groupConnector[prologState.level] == ASCII_PIPE)
        return XML_ERROR_SYNTAX;
      groupConnector[prologState.level] = ASCII_COMMA;
      if (dtd->in_eldecl && elementDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_GROUP_CHOICE:
      if (groupConnector[prologState.level] == ASCII_COMMA)
        return XML_ERROR_SYNTAX;
      if (dtd->in_eldecl
          && !groupConnector[prologState.level]
          && (dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel - 1]].type
              != XML_CTYPE_MIXED)
          ) {
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel - 1]].type
            = XML_CTYPE_CHOICE;
        if (elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      groupConnector[prologState.level] = ASCII_PIPE;
      break;
    case XML_ROLE_PARAM_ENTITY_REF:
#ifdef XML_DTD
    case XML_ROLE_INNER_PARAM_ENTITY_REF:
      dtd->hasParamEntityRefs = XML_TRUE;
      if (!paramEntityParsing)
        dtd->keepProcessing = dtd->standalone;
      else {
        const XML_Char *name;
        ENTITY *entity;
        name = poolStoreString(&dtd->pool, enc,
                                s + enc->minBytesPerChar,
                                next - enc->minBytesPerChar);
        if (!name)
          return XML_ERROR_NO_MEMORY;
        entity = (ENTITY *)lookup(&dtd->paramEntities, name, 0);
        poolDiscard(&dtd->pool);
        /* first, determine if a check for an existing declaration is needed;
           if yes, check that the entity exists, and that it is internal,
           otherwise call the skipped entity handler
        */
        if (prologState.documentEntity &&
            (dtd->standalone
             ? !openInternalEntities
             : !dtd->hasParamEntityRefs)) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal)
            return XML_ERROR_ENTITY_DECLARED_IN_PE;
        }
        else if (!entity) {
          dtd->keepProcessing = dtd->standalone;
          /* cannot report skipped entities in declarations */
          if ((role == XML_ROLE_PARAM_ENTITY_REF) && skippedEntityHandler) {
            skippedEntityHandler(handlerArg, name, 1);
            handleDefault = XML_FALSE;
          }
          break;
        }
        if (entity->open)
          return XML_ERROR_RECURSIVE_ENTITY_REF;
        if (entity->textPtr) {
          enum XML_Error result;
          XML_Bool betweenDecl = 
            (role == XML_ROLE_PARAM_ENTITY_REF ? XML_TRUE : XML_FALSE);
          result = processInternalEntity(parser, entity, betweenDecl);
          if (result != XML_ERROR_NONE)
            return result;
          handleDefault = XML_FALSE;
          break;
        }
        if (externalEntityRefHandler) {
          dtd->paramEntityRead = XML_FALSE;
          entity->open = XML_TRUE;
          if (!externalEntityRefHandler(externalEntityRefHandlerArg,
                                        0,
                                        entity->base,
                                        entity->systemId,
                                        entity->publicId)) {
            entity->open = XML_FALSE;
            return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
          }
          entity->open = XML_FALSE;
          handleDefault = XML_FALSE;
          if (!dtd->paramEntityRead) {
            dtd->keepProcessing = dtd->standalone;
            break;
          }
        }
        else {
          dtd->keepProcessing = dtd->standalone;
          break;
        }
      }
#endif /* XML_DTD */
      if (!dtd->standalone &&
          notStandaloneHandler &&
          !notStandaloneHandler(handlerArg))
        return XML_ERROR_NOT_STANDALONE;
      break;

    /* Element declaration stuff */

    case XML_ROLE_ELEMENT_NAME:
      if (elementDeclHandler) {
        declElementType = getElementType(parser, enc, s, next);
        if (!declElementType)
          return XML_ERROR_NO_MEMORY;
        dtd->scaffLevel = 0;
        dtd->scaffCount = 0;
        dtd->in_eldecl = XML_TRUE;
        handleDefault = XML_FALSE;
      }
      break;

    case XML_ROLE_CONTENT_ANY:
    case XML_ROLE_CONTENT_EMPTY:
      if (dtd->in_eldecl) {
        if (elementDeclHandler) {
          XML_Content * content = (XML_Content *) MALLOC(sizeof(XML_Content));
          if (!content)
            return XML_ERROR_NO_MEMORY;
          content->quant = XML_CQUANT_NONE;
          content->name = NULL;
          content->numchildren = 0;
          content->children = NULL;
          content->type = ((role == XML_ROLE_CONTENT_ANY) ?
                           XML_CTYPE_ANY :
                           XML_CTYPE_EMPTY);
          *eventEndPP = s;
          elementDeclHandler(handlerArg, declElementType->name, content);
          handleDefault = XML_FALSE;
        }
        dtd->in_eldecl = XML_FALSE;
      }
      break;

    case XML_ROLE_CONTENT_PCDATA:
      if (dtd->in_eldecl) {
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel - 1]].type
            = XML_CTYPE_MIXED;
        if (elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;

    case XML_ROLE_CONTENT_ELEMENT:
      quant = XML_CQUANT_NONE;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_OPT:
      quant = XML_CQUANT_OPT;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_REP:
      quant = XML_CQUANT_REP;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_PLUS:
      quant = XML_CQUANT_PLUS;
    elementContent:
      if (dtd->in_eldecl) {
        ELEMENT_TYPE *el;
        const XML_Char *name;
        int nameLen;
        const char *nxt = (quant == XML_CQUANT_NONE
                           ? next
                           : next - enc->minBytesPerChar);
        int myindex = nextScaffoldPart(parser);
        if (myindex < 0)
          return XML_ERROR_NO_MEMORY;
        dtd->scaffold[myindex].type = XML_CTYPE_NAME;
        dtd->scaffold[myindex].quant = quant;
        el = getElementType(parser, enc, s, nxt);
        if (!el)
          return XML_ERROR_NO_MEMORY;
        name = el->name;
        dtd->scaffold[myindex].name = name;
        nameLen = 0;
        for (; name[nameLen++]; );
        dtd->contentStringLen +=  nameLen;
        if (elementDeclHandler)
          handleDefault = XML_FALSE;
      }
      break;

    case XML_ROLE_GROUP_CLOSE:
      quant = XML_CQUANT_NONE;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_OPT:
      quant = XML_CQUANT_OPT;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_REP:
      quant = XML_CQUANT_REP;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_PLUS:
      quant = XML_CQUANT_PLUS;
    closeGroup:
      if (dtd->in_eldecl) {
        if (elementDeclHandler)
          handleDefault = XML_FALSE;
        dtd->scaffLevel--;
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel]].quant = quant;
        if (dtd->scaffLevel == 0) {
          if (!handleDefault) {
            XML_Content *model = build_model(parser);
            if (!model)
              return XML_ERROR_NO_MEMORY;
            *eventEndPP = s;
            elementDeclHandler(handlerArg, declElementType->name, model);
          }
          dtd->in_eldecl = XML_FALSE;
          dtd->contentStringLen = 0;
        }
      }
      break;
      /* End element declaration stuff */

    case XML_ROLE_PI:
      if (!reportProcessingInstruction(parser, enc, s, next))
        return XML_ERROR_NO_MEMORY;
      handleDefault = XML_FALSE;
      break;
    case XML_ROLE_COMMENT:
      if (!reportComment(parser, enc, s, next))
        return XML_ERROR_NO_MEMORY;
      handleDefault = XML_FALSE;
      break;
    case XML_ROLE_NONE:
      switch (tok) {
      case XML_TOK_BOM:
        handleDefault = XML_FALSE;
        break;
      }
      break;
    case XML_ROLE_DOCTYPE_NONE:
      if (startDoctypeDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ENTITY_NONE:
      if (dtd->keepProcessing && entityDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_NOTATION_NONE:
      if (notationDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ATTLIST_NONE:
      if (dtd->keepProcessing && attlistDeclHandler)
        handleDefault = XML_FALSE;
      break;
    case XML_ROLE_ELEMENT_NONE:
      if (elementDeclHandler)
        handleDefault = XML_FALSE;
      break;
    } /* end of big switch */

    if (handleDefault && defaultHandler)
      reportDefault(parser, enc, s, next);

    switch (ps_parsing) {
    case XML_SUSPENDED: 
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_FINISHED:
      return XML_ERROR_ABORTED;
    default:
      s = next;
      tok = XmlPrologTok(enc, s, end, &next);
    }
  }
  /* not reached */
}
