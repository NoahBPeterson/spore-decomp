// expat 2.0.1 internals (lib/xmlparse.c, xmltok.h, xmlrole.h, expat.h;
// Spore links expat built with winconfig.h settings: XML_NS, XML_DTD, XML_CONTEXT_BYTES=1024, char XML_Char.
#pragma once
#include <stddef.h>
#include <string.h>
#define XML_NS 1
#define XML_DTD 1
#define XML_CONTEXT_BYTES 1024
#define BYTEORDER 1234
#define HAVE_MEMMOVE
#define XML_STATIC
#define XML_BUILDING_EXPAT 1

// Upstream headers, included from the published release (tools/ci/setup_oss.sh unpacks it under work/).
#include "../../../work/third_party/src/expat-2.0.1/lib/ascii.h"
#include "../../../work/third_party/src/expat-2.0.1/lib/expat_external.h"
#include "../../../work/third_party/src/expat-2.0.1/lib/expat.h"
#include "../../../work/third_party/src/expat-2.0.1/lib/internal.h"
#include "../../../work/third_party/src/expat-2.0.1/lib/xmltok.h"
#include "../../../work/third_party/src/expat-2.0.1/lib/xmlrole.h"

// ---- xmlparse.c (internal types and helper declarations) ----

#ifdef XML_UNICODE
#define XML_ENCODE_MAX XML_UTF16_ENCODE_MAX
#define XmlConvert XmlUtf16Convert
#define XmlGetInternalEncoding XmlGetUtf16InternalEncoding
#define XmlGetInternalEncodingNS XmlGetUtf16InternalEncodingNS
#define XmlEncode XmlUtf16Encode
/* Using pointer subtraction to convert to integer type. */
#define MUST_CONVERT(enc, s) (!(enc)->isUtf16 || (((char *)(s) - (char *)NULL) & 1))
typedef unsigned short ICHAR;
#else
#define XML_ENCODE_MAX XML_UTF8_ENCODE_MAX
#define XmlConvert XmlUtf8Convert
#define XmlGetInternalEncoding XmlGetUtf8InternalEncoding
#define XmlGetInternalEncodingNS XmlGetUtf8InternalEncodingNS
#define XmlEncode XmlUtf8Encode
#define MUST_CONVERT(enc, s) (!(enc)->isUtf8)
typedef char ICHAR;
#endif


#ifndef XML_NS

#define XmlInitEncodingNS XmlInitEncoding
#define XmlInitUnknownEncodingNS XmlInitUnknownEncoding
#undef XmlGetInternalEncodingNS
#define XmlGetInternalEncodingNS XmlGetInternalEncoding
#define XmlParseXmlDeclNS XmlParseXmlDecl

#endif

#ifdef XML_UNICODE

#ifdef XML_UNICODE_WCHAR_T
#define XML_T(x) (const wchar_t)x
#define XML_L(x) L ## x
#else
#define XML_T(x) (const unsigned short)x
#define XML_L(x) x
#endif

#else

#define XML_T(x) x
#define XML_L(x) x

#endif

/* Round up n to be a multiple of sz, where sz is a power of 2. */
#define ROUND_UP(n, sz) (((n) + ((sz) - 1)) & ~((sz) - 1))

/* Handle the case where memmove() doesn't exist. */
#ifndef HAVE_MEMMOVE
#ifdef HAVE_BCOPY
#define memmove(d,s,l) bcopy((s),(d),(l))
#else
#error memmove does not exist on this platform, nor is a substitute available
#endif /* HAVE_BCOPY */
#endif /* HAVE_MEMMOVE */




typedef const XML_Char *KEY;

typedef struct {
  KEY name;
} NAMED;

typedef struct {
  NAMED **v;
  unsigned char power;
  size_t size;
  size_t used;
  const XML_Memory_Handling_Suite *mem;
} HASH_TABLE;

/* Basic character hash algorithm, taken from Python's string hash:
   h = h * 1000003 ^ character, the constant being a prime number.

*/
#ifdef XML_UNICODE
#define CHAR_HASH(h, c) \
  (((h) * 0xF4243) ^ (unsigned short)(c))
#else
#define CHAR_HASH(h, c) \
  (((h) * 0xF4243) ^ (unsigned char)(c))
#endif

/* For probing (after a collision) we need a step size relative prime
   to the hash table size, which is a power of 2. We use double-hashing,
   since we can calculate a second hash value cheaply by taking those bits
   of the first hash value that were discarded (masked out) when the table
   index was calculated: index = hash & mask, where mask = table->size - 1.
   We limit the maximum step size to table->size / 4 (mask >> 2) and make
   it odd, since odd numbers are always relative prime to a power of 2.
*/
#define SECOND_HASH(hash, mask, power) \
  ((((hash) & ~(mask)) >> ((power) - 1)) & ((mask) >> 2))
#define PROBE_STEP(hash, mask, power) \
  ((unsigned char)((SECOND_HASH(hash, mask, power)) | 1))

typedef struct {
  NAMED **p;
  NAMED **end;
} HASH_TABLE_ITER;

#define INIT_TAG_BUF_SIZE 32  /* must be a multiple of sizeof(XML_Char) */
#define INIT_DATA_BUF_SIZE 1024
#define INIT_ATTS_SIZE 16
#define INIT_ATTS_VERSION 0xFFFFFFFF
#define INIT_BLOCK_SIZE 1024
#define INIT_BUFFER_SIZE 1024

#define EXPAND_SPARE 24

typedef struct binding {
  struct prefix *prefix;
  struct binding *nextTagBinding;
  struct binding *prevPrefixBinding;
  const struct attribute_id *attId;
  XML_Char *uri;
  int uriLen;
  int uriAlloc;
} BINDING;

typedef struct prefix {
  const XML_Char *name;
  BINDING *binding;
} PREFIX;

typedef struct {
  const XML_Char *str;
  const XML_Char *localPart;
  const XML_Char *prefix;
  int strLen;
  int uriLen;
  int prefixLen;
} TAG_NAME;

/* TAG represents an open element.
   The name of the element is stored in both the document and API
   encodings.  The memory buffer 'buf' is a separately-allocated
   memory area which stores the name.  During the XML_Parse()/
   XMLParseBuffer() when the element is open, the memory for the 'raw'
   version of the name (in the document encoding) is shared with the
   document buffer.  If the element is open across calls to
   XML_Parse()/XML_ParseBuffer(), the buffer is re-allocated to
   contain the 'raw' name as well.

   A parser re-uses these structures, maintaining a list of allocated
   TAG objects in a free list.
*/
typedef struct tag {
  struct tag *parent;           /* parent of this element */
  const char *rawName;          /* tagName in the original encoding */
  int rawNameLength;
  TAG_NAME name;                /* tagName in the API encoding */
  char *buf;                    /* buffer for name components */
  char *bufEnd;                 /* end of the buffer */
  BINDING *bindings;
} TAG;

typedef struct {
  const XML_Char *name;
  const XML_Char *textPtr;
  int textLen;                  /* length in XML_Chars */
  int processed;                /* # of processed bytes - when suspended */
  const XML_Char *systemId;
  const XML_Char *base;
  const XML_Char *publicId;
  const XML_Char *notation;
  XML_Bool open;
  XML_Bool is_param;
  XML_Bool is_internal; /* true if declared in internal subset outside PE */
} ENTITY;

typedef struct {
  enum XML_Content_Type         type;
  enum XML_Content_Quant        quant;
  const XML_Char *              name;
  int                           firstchild;
  int                           lastchild;
  int                           childcnt;
  int                           nextsib;
} CONTENT_SCAFFOLD;

#define INIT_SCAFFOLD_ELEMENTS 32

typedef struct block {
  struct block *next;
  int size;
  XML_Char s[1];
} BLOCK;

typedef struct {
  BLOCK *blocks;
  BLOCK *freeBlocks;
  const XML_Char *end;
  XML_Char *ptr;
  XML_Char *start;
  const XML_Memory_Handling_Suite *mem;
} STRING_POOL;

/* The XML_Char before the name is used to determine whether
   an attribute has been specified. */
typedef struct attribute_id {
  XML_Char *name;
  PREFIX *prefix;
  XML_Bool maybeTokenized;
  XML_Bool xmlns;
} ATTRIBUTE_ID;

typedef struct {
  const ATTRIBUTE_ID *id;
  XML_Bool isCdata;
  const XML_Char *value;
} DEFAULT_ATTRIBUTE;

typedef struct {
  unsigned long version;
  unsigned long hash;
  const XML_Char *uriName;
} NS_ATT;

typedef struct {
  const XML_Char *name;
  PREFIX *prefix;
  const ATTRIBUTE_ID *idAtt;
  int nDefaultAtts;
  int allocDefaultAtts;
  DEFAULT_ATTRIBUTE *defaultAtts;
} ELEMENT_TYPE;

typedef struct {
  HASH_TABLE generalEntities;
  HASH_TABLE elementTypes;
  HASH_TABLE attributeIds;
  HASH_TABLE prefixes;
  STRING_POOL pool;
  STRING_POOL entityValuePool;
  /* false once a parameter entity reference has been skipped */
  XML_Bool keepProcessing;
  /* true once an internal or external PE reference has been encountered;
     this includes the reference to an external subset */
  XML_Bool hasParamEntityRefs;
  XML_Bool standalone;
#ifdef XML_DTD
  /* indicates if external PE has been read */
  XML_Bool paramEntityRead;
  HASH_TABLE paramEntities;
#endif /* XML_DTD */
  PREFIX defaultPrefix;
  /* === scaffolding for building content model === */
  XML_Bool in_eldecl;
  CONTENT_SCAFFOLD *scaffold;
  unsigned contentStringLen;
  unsigned scaffSize;
  unsigned scaffCount;
  int scaffLevel;
  int *scaffIndex;
} DTD;

typedef struct open_internal_entity {
  const char *internalEventPtr;
  const char *internalEventEndPtr;
  struct open_internal_entity *next;
  ENTITY *entity;
  int startTagLevel;
  XML_Bool betweenDecl; /* WFC: PE Between Declarations */
} OPEN_INTERNAL_ENTITY;

typedef enum XML_Error PTRCALL Processor(XML_Parser parser,
                                         const char *start,
                                         const char *end,
                                         const char **endPtr);

Processor prologProcessor;
Processor prologInitProcessor;
Processor contentProcessor;
Processor cdataSectionProcessor;
#ifdef XML_DTD
Processor ignoreSectionProcessor;
Processor externalParEntProcessor;
Processor externalParEntInitProcessor;
Processor entityValueProcessor;
Processor entityValueInitProcessor;
#endif /* XML_DTD */
Processor epilogProcessor;
Processor errorProcessor;
Processor externalEntityInitProcessor;
Processor externalEntityInitProcessor2;
Processor externalEntityInitProcessor3;
Processor externalEntityContentProcessor;
Processor internalEntityProcessor;

enum XML_Error
handleUnknownEncoding(XML_Parser parser, const XML_Char *encodingName);
enum XML_Error
processXmlDecl(XML_Parser parser, int isGeneralTextEntity,
               const char *s, const char *next);   // 0x00905990 (equiv t2)
enum XML_Error
initializeEncoding(XML_Parser parser);
enum XML_Error
doProlog(XML_Parser parser, const ENCODING *enc, const char *s, 
         const char *end, int tok, const char *next, const char **nextPtr, 
         XML_Bool haveMore);
enum XML_Error
processInternalEntity(XML_Parser parser, ENTITY *entity, 
                      XML_Bool betweenDecl);   // 0x00903a10 (equiv t2)
enum XML_Error
doContent(XML_Parser parser, int startTagLevel, const ENCODING *enc,
          const char *start, const char *end, const char **endPtr, 
          XML_Bool haveMore);
enum XML_Error
doCdataSection(XML_Parser parser, const ENCODING *, const char **startPtr,
               const char *end, const char **nextPtr, XML_Bool haveMore);
#ifdef XML_DTD
enum XML_Error
doIgnoreSection(XML_Parser parser, const ENCODING *, const char **startPtr,
                const char *end, const char **nextPtr, XML_Bool haveMore);   // 0x009049e0 (equiv t2)
#endif /* XML_DTD */

enum XML_Error
storeAtts(XML_Parser parser, const ENCODING *, const char *s,
          TAG_NAME *tagNamePtr, BINDING **bindingsPtr);
enum XML_Error
addBinding(XML_Parser parser, PREFIX *prefix, const ATTRIBUTE_ID *attId,
           const XML_Char *uri, BINDING **bindingsPtr);   // 0x009037a0 (equiv t2)
int
defineAttribute(ELEMENT_TYPE *type, ATTRIBUTE_ID *, XML_Bool isCdata, 
                XML_Bool isId, const XML_Char *dfltValue, XML_Parser parser);
enum XML_Error
storeAttributeValue(XML_Parser parser, const ENCODING *, XML_Bool isCdata,
                    const char *, const char *, STRING_POOL *);   // 0x00907000 (equiv t2)
enum XML_Error
appendAttributeValue(XML_Parser parser, const ENCODING *, XML_Bool isCdata,
                     const char *, const char *, STRING_POOL *);
ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc, const char *start,
               const char *end);   // 0x00906680 (equiv t2)
int
setElementTypePrefix(XML_Parser parser, ELEMENT_TYPE *);   // 0x00904be0 (equiv t2)
enum XML_Error
storeEntityValue(XML_Parser parser, const ENCODING *enc, const char *start,
                 const char *end);
int
reportProcessingInstruction(XML_Parser parser, const ENCODING *enc,
                            const char *start, const char *end);   // 0x009064c0 (equiv t2)
int
reportComment(XML_Parser parser, const ENCODING *enc, const char *start,
              const char *end);   // 0x009065e0 (equiv t2)
void
reportDefault(XML_Parser parser, const ENCODING *enc, const char *start,
              const char *end);   // 0x00903bb0 (equiv t2)

const XML_Char * getContext(XML_Parser parser);
XML_Bool
setContext(XML_Parser parser, const XML_Char *context);

void FASTCALL normalizePublicId(XML_Char *s);

DTD * dtdCreate(const XML_Memory_Handling_Suite *ms);
/* do not call if parentParser != NULL */
void dtdReset(DTD *p, const XML_Memory_Handling_Suite *ms);
void
dtdDestroy(DTD *p, XML_Bool isDocEntity, const XML_Memory_Handling_Suite *ms);
int
dtdCopy(DTD *newDtd, const DTD *oldDtd, const XML_Memory_Handling_Suite *ms);
int
copyEntityTable(HASH_TABLE *, STRING_POOL *, const HASH_TABLE *);

NAMED *
lookup(HASH_TABLE *table, KEY name, size_t createSize);   // 0x00903dd0 (equiv t2)
void FASTCALL
hashTableInit(HASH_TABLE *, const XML_Memory_Handling_Suite *ms);
void FASTCALL hashTableClear(HASH_TABLE *);
void FASTCALL hashTableDestroy(HASH_TABLE *);
void FASTCALL
hashTableIterInit(HASH_TABLE_ITER *, const HASH_TABLE *);
NAMED * FASTCALL hashTableIterNext(HASH_TABLE_ITER *);

void FASTCALL
poolInit(STRING_POOL *, const XML_Memory_Handling_Suite *ms);
void FASTCALL poolClear(STRING_POOL *);   // 0x009040f0 (equiv t2)
void FASTCALL poolDestroy(STRING_POOL *);
XML_Char *
poolAppend(STRING_POOL *pool, const ENCODING *enc,
           const char *ptr, const char *end);   // 0x009053b0 (equiv t2)
XML_Char *
poolStoreString(STRING_POOL *pool, const ENCODING *enc,
                const char *ptr, const char *end);   // 0x00905500 (equiv t2)
XML_Bool FASTCALL poolGrow(STRING_POOL *pool);   // 0x00904170 (equiv t2)
const XML_Char * FASTCALL
poolCopyString(STRING_POOL *pool, const XML_Char *s);   // 0x00905410 (equiv t2)
const XML_Char *
poolCopyStringN(STRING_POOL *pool, const XML_Char *s, int n);
const XML_Char * FASTCALL
poolAppendString(STRING_POOL *pool, const XML_Char *s);   // 0x009054b0 (equiv t2)

int FASTCALL nextScaffoldPart(XML_Parser parser);
XML_Content * build_model(XML_Parser parser);
ELEMENT_TYPE *
getElementType(XML_Parser parser, const ENCODING *enc,
               const char *ptr, const char *end);   // 0x00905540 (equiv t2)

XML_Parser
parserCreate(const XML_Char *encodingName,
             const XML_Memory_Handling_Suite *memsuite,
             const XML_Char *nameSep,
             DTD *dtd);
void
parserInit(XML_Parser parser, const XML_Char *encodingName);

#define poolStart(pool) ((pool)->start)
#define poolEnd(pool) ((pool)->ptr)
#define poolLength(pool) ((pool)->ptr - (pool)->start)
#define poolChop(pool) ((void)--(pool->ptr))
#define poolLastChar(pool) (((pool)->ptr)[-1])
#define poolDiscard(pool) ((pool)->ptr = (pool)->start)
#define poolFinish(pool) ((pool)->start = (pool)->ptr)
#define poolAppendChar(pool, c) \
  (((pool)->ptr == (pool)->end && !poolGrow(pool)) \
   ? 0 \
   : ((*((pool)->ptr)++ = c), 1))

struct XML_ParserStruct {
  /* The first member must be userData so that the XML_GetUserData
     macro works. */
  void *m_userData;
  void *m_handlerArg;
  char *m_buffer;
  const XML_Memory_Handling_Suite m_mem;
  /* first character to be parsed */
  const char *m_bufferPtr;
  /* past last character to be parsed */
  char *m_bufferEnd;
  /* allocated end of buffer */
  const char *m_bufferLim;
  XML_Index m_parseEndByteIndex;
  const char *m_parseEndPtr;
  XML_Char *m_dataBuf;
  XML_Char *m_dataBufEnd;
  XML_StartElementHandler m_startElementHandler;
  XML_EndElementHandler m_endElementHandler;
  XML_CharacterDataHandler m_characterDataHandler;
  XML_ProcessingInstructionHandler m_processingInstructionHandler;
  XML_CommentHandler m_commentHandler;
  XML_StartCdataSectionHandler m_startCdataSectionHandler;
  XML_EndCdataSectionHandler m_endCdataSectionHandler;
  XML_DefaultHandler m_defaultHandler;
  XML_StartDoctypeDeclHandler m_startDoctypeDeclHandler;
  XML_EndDoctypeDeclHandler m_endDoctypeDeclHandler;
  XML_UnparsedEntityDeclHandler m_unparsedEntityDeclHandler;
  XML_NotationDeclHandler m_notationDeclHandler;
  XML_StartNamespaceDeclHandler m_startNamespaceDeclHandler;
  XML_EndNamespaceDeclHandler m_endNamespaceDeclHandler;
  XML_NotStandaloneHandler m_notStandaloneHandler;
  XML_ExternalEntityRefHandler m_externalEntityRefHandler;
  XML_Parser m_externalEntityRefHandlerArg;
  XML_SkippedEntityHandler m_skippedEntityHandler;
  XML_UnknownEncodingHandler m_unknownEncodingHandler;
  XML_ElementDeclHandler m_elementDeclHandler;
  XML_AttlistDeclHandler m_attlistDeclHandler;
  XML_EntityDeclHandler m_entityDeclHandler;
  XML_XmlDeclHandler m_xmlDeclHandler;
  const ENCODING *m_encoding;
  INIT_ENCODING m_initEncoding;
  const ENCODING *m_internalEncoding;
  const XML_Char *m_protocolEncodingName;
  XML_Bool m_ns;
  XML_Bool m_ns_triplets;
  void *m_unknownEncodingMem;
  void *m_unknownEncodingData;
  void *m_unknownEncodingHandlerData;
  void (XMLCALL *m_unknownEncodingRelease)(void *);
  PROLOG_STATE m_prologState;
  Processor *m_processor;
  enum XML_Error m_errorCode;
  const char *m_eventPtr;
  const char *m_eventEndPtr;
  const char *m_positionPtr;
  OPEN_INTERNAL_ENTITY *m_openInternalEntities;
  OPEN_INTERNAL_ENTITY *m_freeInternalEntities;
  XML_Bool m_defaultExpandInternalEntities;
  int m_tagLevel;
  ENTITY *m_declEntity;
  const XML_Char *m_doctypeName;
  const XML_Char *m_doctypeSysid;
  const XML_Char *m_doctypePubid;
  const XML_Char *m_declAttributeType;
  const XML_Char *m_declNotationName;
  const XML_Char *m_declNotationPublicId;
  ELEMENT_TYPE *m_declElementType;
  ATTRIBUTE_ID *m_declAttributeId;
  XML_Bool m_declAttributeIsCdata;
  XML_Bool m_declAttributeIsId;
  DTD *m_dtd;
  const XML_Char *m_curBase;
  TAG *m_tagStack;
  TAG *m_freeTagList;
  BINDING *m_inheritedBindings;
  BINDING *m_freeBindingList;
  int m_attsSize;
  int m_nSpecifiedAtts;
  int m_idAttIndex;
  ATTRIBUTE *m_atts;
  NS_ATT *m_nsAtts;
  unsigned long m_nsAttsVersion;
  unsigned char m_nsAttsPower;
  POSITION m_position;
  STRING_POOL m_tempPool;
  STRING_POOL m_temp2Pool;
  char *m_groupConnector;
  unsigned int m_groupSize;
  XML_Char m_namespaceSeparator;
  XML_Parser m_parentParser;
  XML_ParsingStatus m_parsingStatus;
#ifdef XML_DTD
  XML_Bool m_isParamEntity;
  XML_Bool m_useForeignDTD;
  enum XML_ParamEntityParsing m_paramEntityParsing;
#endif
};

#define MALLOC(s) (parser->m_mem.malloc_fcn((s)))
#define REALLOC(p,s) (parser->m_mem.realloc_fcn((p),(s)))
#define FREE(p) (parser->m_mem.free_fcn((p)))

#define userData (parser->m_userData)
#define handlerArg (parser->m_handlerArg)
#define startElementHandler (parser->m_startElementHandler)
#define endElementHandler (parser->m_endElementHandler)
#define characterDataHandler (parser->m_characterDataHandler)
#define processingInstructionHandler \
        (parser->m_processingInstructionHandler)
#define commentHandler (parser->m_commentHandler)
#define startCdataSectionHandler \
        (parser->m_startCdataSectionHandler)
#define endCdataSectionHandler (parser->m_endCdataSectionHandler)
#define defaultHandler (parser->m_defaultHandler)
#define startDoctypeDeclHandler (parser->m_startDoctypeDeclHandler)
#define endDoctypeDeclHandler (parser->m_endDoctypeDeclHandler)
#define unparsedEntityDeclHandler \
        (parser->m_unparsedEntityDeclHandler)
#define notationDeclHandler (parser->m_notationDeclHandler)
#define startNamespaceDeclHandler \
        (parser->m_startNamespaceDeclHandler)
#define endNamespaceDeclHandler (parser->m_endNamespaceDeclHandler)
#define notStandaloneHandler (parser->m_notStandaloneHandler)
#define externalEntityRefHandler \
        (parser->m_externalEntityRefHandler)
#define externalEntityRefHandlerArg \
        (parser->m_externalEntityRefHandlerArg)
#define internalEntityRefHandler \
        (parser->m_internalEntityRefHandler)
#define skippedEntityHandler (parser->m_skippedEntityHandler)
#define unknownEncodingHandler (parser->m_unknownEncodingHandler)
#define elementDeclHandler (parser->m_elementDeclHandler)
#define attlistDeclHandler (parser->m_attlistDeclHandler)
#define entityDeclHandler (parser->m_entityDeclHandler)
#define xmlDeclHandler (parser->m_xmlDeclHandler)
#define encoding (parser->m_encoding)
#define initEncoding (parser->m_initEncoding)
#define internalEncoding (parser->m_internalEncoding)
#define unknownEncodingMem (parser->m_unknownEncodingMem)
#define unknownEncodingData (parser->m_unknownEncodingData)
#define unknownEncodingHandlerData \
  (parser->m_unknownEncodingHandlerData)
#define unknownEncodingRelease (parser->m_unknownEncodingRelease)
#define protocolEncodingName (parser->m_protocolEncodingName)
#define ns (parser->m_ns)
#define ns_triplets (parser->m_ns_triplets)
#define prologState (parser->m_prologState)
#define processor (parser->m_processor)
#define errorCode (parser->m_errorCode)
#define eventPtr (parser->m_eventPtr)
#define eventEndPtr (parser->m_eventEndPtr)
#define positionPtr (parser->m_positionPtr)
#define position (parser->m_position)
#define openInternalEntities (parser->m_openInternalEntities)
#define freeInternalEntities (parser->m_freeInternalEntities)
#define defaultExpandInternalEntities \
        (parser->m_defaultExpandInternalEntities)
#define tagLevel (parser->m_tagLevel)
#define buffer (parser->m_buffer)
#define bufferPtr (parser->m_bufferPtr)
#define bufferEnd (parser->m_bufferEnd)
#define parseEndByteIndex (parser->m_parseEndByteIndex)
#define parseEndPtr (parser->m_parseEndPtr)
#define bufferLim (parser->m_bufferLim)
#define dataBuf (parser->m_dataBuf)
#define dataBufEnd (parser->m_dataBufEnd)
#define _dtd (parser->m_dtd)
#define curBase (parser->m_curBase)
#define declEntity (parser->m_declEntity)
#define doctypeName (parser->m_doctypeName)
#define doctypeSysid (parser->m_doctypeSysid)
#define doctypePubid (parser->m_doctypePubid)
#define declAttributeType (parser->m_declAttributeType)
#define declNotationName (parser->m_declNotationName)
#define declNotationPublicId (parser->m_declNotationPublicId)
#define declElementType (parser->m_declElementType)
#define declAttributeId (parser->m_declAttributeId)
#define declAttributeIsCdata (parser->m_declAttributeIsCdata)
#define declAttributeIsId (parser->m_declAttributeIsId)
#define freeTagList (parser->m_freeTagList)
#define freeBindingList (parser->m_freeBindingList)
#define inheritedBindings (parser->m_inheritedBindings)
#define tagStack (parser->m_tagStack)
#define atts (parser->m_atts)
#define attsSize (parser->m_attsSize)
#define nSpecifiedAtts (parser->m_nSpecifiedAtts)
#define idAttIndex (parser->m_idAttIndex)
#define nsAtts (parser->m_nsAtts)
#define nsAttsVersion (parser->m_nsAttsVersion)
#define nsAttsPower (parser->m_nsAttsPower)
#define tempPool (parser->m_tempPool)
#define temp2Pool (parser->m_temp2Pool)
#define groupConnector (parser->m_groupConnector)
#define groupSize (parser->m_groupSize)
#define namespaceSeparator (parser->m_namespaceSeparator)
#define parentParser (parser->m_parentParser)
#define ps_parsing (parser->m_parsingStatus.parsing)
#define ps_finalBuffer (parser->m_parsingStatus.finalBuffer)
#ifdef XML_DTD
#define isParamEntity (parser->m_isParamEntity)
#define useForeignDTD (parser->m_useForeignDTD)
#define paramEntityParsing (parser->m_paramEntityParsing)
#endif /* XML_DTD */