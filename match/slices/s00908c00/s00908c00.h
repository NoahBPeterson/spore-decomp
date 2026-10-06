// expat 2.0.1 internals (lib/xmlparse.c, xmltok.h, xmlrole.h, expat.h; MIT license,
// Copyright (c) 1998-2000 Thai Open Source Software Center Ltd and Clark Cooper).
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

// ---- ascii.h ----
/* Copyright (c) 1998, 1999 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

#define ASCII_A 0x41
#define ASCII_B 0x42
#define ASCII_C 0x43
#define ASCII_D 0x44
#define ASCII_E 0x45
#define ASCII_F 0x46
#define ASCII_G 0x47
#define ASCII_H 0x48
#define ASCII_I 0x49
#define ASCII_J 0x4A
#define ASCII_K 0x4B
#define ASCII_L 0x4C
#define ASCII_M 0x4D
#define ASCII_N 0x4E
#define ASCII_O 0x4F
#define ASCII_P 0x50
#define ASCII_Q 0x51
#define ASCII_R 0x52
#define ASCII_S 0x53
#define ASCII_T 0x54
#define ASCII_U 0x55
#define ASCII_V 0x56
#define ASCII_W 0x57
#define ASCII_X 0x58
#define ASCII_Y 0x59
#define ASCII_Z 0x5A

#define ASCII_a 0x61
#define ASCII_b 0x62
#define ASCII_c 0x63
#define ASCII_d 0x64
#define ASCII_e 0x65
#define ASCII_f 0x66
#define ASCII_g 0x67
#define ASCII_h 0x68
#define ASCII_i 0x69
#define ASCII_j 0x6A
#define ASCII_k 0x6B
#define ASCII_l 0x6C
#define ASCII_m 0x6D
#define ASCII_n 0x6E
#define ASCII_o 0x6F
#define ASCII_p 0x70
#define ASCII_q 0x71
#define ASCII_r 0x72
#define ASCII_s 0x73
#define ASCII_t 0x74
#define ASCII_u 0x75
#define ASCII_v 0x76
#define ASCII_w 0x77
#define ASCII_x 0x78
#define ASCII_y 0x79
#define ASCII_z 0x7A

#define ASCII_0 0x30
#define ASCII_1 0x31
#define ASCII_2 0x32
#define ASCII_3 0x33
#define ASCII_4 0x34
#define ASCII_5 0x35
#define ASCII_6 0x36
#define ASCII_7 0x37
#define ASCII_8 0x38
#define ASCII_9 0x39

#define ASCII_TAB 0x09
#define ASCII_SPACE 0x20
#define ASCII_EXCL 0x21
#define ASCII_QUOT 0x22
#define ASCII_AMP 0x26
#define ASCII_APOS 0x27
#define ASCII_MINUS 0x2D
#define ASCII_PERIOD 0x2E
#define ASCII_COLON 0x3A
#define ASCII_SEMI 0x3B
#define ASCII_LT 0x3C
#define ASCII_EQUALS 0x3D
#define ASCII_GT 0x3E
#define ASCII_LSQB 0x5B
#define ASCII_RSQB 0x5D
#define ASCII_UNDERSCORE 0x5F
#define ASCII_LPAREN 0x28
#define ASCII_RPAREN 0x29
#define ASCII_FF 0x0C
#define ASCII_SLASH 0x2F
#define ASCII_HASH 0x23
#define ASCII_PIPE 0x7C
#define ASCII_COMMA 0x2C

// ---- expat_external.h ----
/* Copyright (c) 1998, 1999, 2000 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

#ifndef Expat_External_INCLUDED
#define Expat_External_INCLUDED 1

/* External API definitions */

#if defined(_MSC_EXTENSIONS) && !defined(__BEOS__) && !defined(__CYGWIN__)
#define XML_USE_MSC_EXTENSIONS 1
#endif

/* Expat tries very hard to make the API boundary very specifically
   defined.  There are two macros defined to control this boundary;
   each of these can be defined before including this header to
   achieve some different behavior, but doing so it not recommended or
   tested frequently.

   XMLCALL    - The calling convention to use for all calls across the
                "library boundary."  This will default to cdecl, and
                try really hard to tell the compiler that's what we
                want.

   XMLIMPORT  - Whatever magic is needed to note that a function is
                to be imported from a dynamically loaded library
                (.dll, .so, or .sl, depending on your platform).

   The XMLCALL macro was added in Expat 1.95.7.  The only one which is
   expected to be directly useful in client code is XMLCALL.

   Note that on at least some Unix versions, the Expat library must be
   compiled with the cdecl calling convention as the default since
   system headers may assume the cdecl convention.
*/
#ifndef XMLCALL
#if defined(_MSC_VER)
#define XMLCALL __cdecl
#elif defined(__GNUC__) && defined(__i386) && !defined(__INTEL_COMPILER)
#define XMLCALL __attribute__((cdecl))
#else
/* For any platform which uses this definition and supports more than
   one calling convention, we need to extend this definition to
   declare the convention used on that platform, if it's possible to
   do so.

   If this is the case for your platform, please file a bug report
   with information on how to identify your platform via the C
   pre-processor and how to specify the same calling convention as the
   platform's malloc() implementation.
*/
#define XMLCALL
#endif
#endif  /* not defined XMLCALL */


#if !defined(XML_STATIC) && !defined(XMLIMPORT)
#ifndef XML_BUILDING_EXPAT
/* using Expat from an application */

#ifdef XML_USE_MSC_EXTENSIONS
#define XMLIMPORT __declspec(dllimport)
#endif

#endif
#endif  /* not defined XML_STATIC */


/* If we didn't define it above, define it away: */
#ifndef XMLIMPORT
#define XMLIMPORT
#endif


#define XMLPARSEAPI(type) XMLIMPORT type XMLCALL

#ifdef __cplusplus
extern "C" {
#endif

#ifdef XML_UNICODE_WCHAR_T
#define XML_UNICODE
#endif

#ifdef XML_UNICODE     /* Information is UTF-16 encoded. */
#ifdef XML_UNICODE_WCHAR_T
typedef wchar_t XML_Char;
typedef wchar_t XML_LChar;
#else
typedef unsigned short XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE_WCHAR_T */
#else                  /* Information is UTF-8 encoded. */
typedef char XML_Char;
typedef char XML_LChar;
#endif /* XML_UNICODE */

#ifdef XML_LARGE_SIZE  /* Use large integers for file/stream positions. */
#if defined(XML_USE_MSC_EXTENSIONS) && _MSC_VER < 1400
typedef __int64 XML_Index; 
typedef unsigned __int64 XML_Size;
#else
typedef long long XML_Index;
typedef unsigned long long XML_Size;
#endif
#else
typedef long XML_Index;
typedef unsigned long XML_Size;
#endif /* XML_LARGE_SIZE */

#ifdef __cplusplus
}
#endif

#endif /* not Expat_External_INCLUDED */

// ---- expat.h ----
/* Copyright (c) 1998, 1999, 2000 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

#ifndef Expat_INCLUDED
#define Expat_INCLUDED 1

#ifdef __VMS
/*      0        1         2         3      0        1         2         3
        1234567890123456789012345678901     1234567890123456789012345678901 */
#define XML_SetProcessingInstructionHandler XML_SetProcessingInstrHandler
#define XML_SetUnparsedEntityDeclHandler    XML_SetUnparsedEntDeclHandler
#define XML_SetStartNamespaceDeclHandler    XML_SetStartNamespcDeclHandler
#define XML_SetExternalEntityRefHandlerArg  XML_SetExternalEntRefHandlerArg
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

struct XML_ParserStruct;
typedef struct XML_ParserStruct *XML_Parser;

/* Should this be defined using stdbool.h when C99 is available? */
typedef unsigned char XML_Bool;
#define XML_TRUE   ((XML_Bool) 1)
#define XML_FALSE  ((XML_Bool) 0)

/* The XML_Status enum gives the possible return values for several
   API functions.  The preprocessor #defines are included so this
   stanza can be added to code that still needs to support older
   versions of Expat 1.95.x:

   #ifndef XML_STATUS_OK
   #define XML_STATUS_OK    1
   #define XML_STATUS_ERROR 0
   #endif

   Otherwise, the #define hackery is quite ugly and would have been
   dropped.
*/
enum XML_Status {
  XML_STATUS_ERROR = 0,
#define XML_STATUS_ERROR XML_STATUS_ERROR
  XML_STATUS_OK = 1,
#define XML_STATUS_OK XML_STATUS_OK
  XML_STATUS_SUSPENDED = 2
#define XML_STATUS_SUSPENDED XML_STATUS_SUSPENDED
};

enum XML_Error {
  XML_ERROR_NONE,
  XML_ERROR_NO_MEMORY,
  XML_ERROR_SYNTAX,
  XML_ERROR_NO_ELEMENTS,
  XML_ERROR_INVALID_TOKEN,
  XML_ERROR_UNCLOSED_TOKEN,
  XML_ERROR_PARTIAL_CHAR,
  XML_ERROR_TAG_MISMATCH,
  XML_ERROR_DUPLICATE_ATTRIBUTE,
  XML_ERROR_JUNK_AFTER_DOC_ELEMENT,
  XML_ERROR_PARAM_ENTITY_REF,
  XML_ERROR_UNDEFINED_ENTITY,
  XML_ERROR_RECURSIVE_ENTITY_REF,
  XML_ERROR_ASYNC_ENTITY,
  XML_ERROR_BAD_CHAR_REF,
  XML_ERROR_BINARY_ENTITY_REF,
  XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF,
  XML_ERROR_MISPLACED_XML_PI,
  XML_ERROR_UNKNOWN_ENCODING,
  XML_ERROR_INCORRECT_ENCODING,
  XML_ERROR_UNCLOSED_CDATA_SECTION,
  XML_ERROR_EXTERNAL_ENTITY_HANDLING,
  XML_ERROR_NOT_STANDALONE,
  XML_ERROR_UNEXPECTED_STATE,
  XML_ERROR_ENTITY_DECLARED_IN_PE,
  XML_ERROR_FEATURE_REQUIRES_XML_DTD,
  XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING,
  /* Added in 1.95.7. */
  XML_ERROR_UNBOUND_PREFIX,
  /* Added in 1.95.8. */
  XML_ERROR_UNDECLARING_PREFIX,
  XML_ERROR_INCOMPLETE_PE,
  XML_ERROR_XML_DECL,
  XML_ERROR_TEXT_DECL,
  XML_ERROR_PUBLICID,
  XML_ERROR_SUSPENDED,
  XML_ERROR_NOT_SUSPENDED,
  XML_ERROR_ABORTED,
  XML_ERROR_FINISHED,
  XML_ERROR_SUSPEND_PE,
  /* Added in 2.0. */
  XML_ERROR_RESERVED_PREFIX_XML,
  XML_ERROR_RESERVED_PREFIX_XMLNS,
  XML_ERROR_RESERVED_NAMESPACE_URI
};

enum XML_Content_Type {
  XML_CTYPE_EMPTY = 1,
  XML_CTYPE_ANY,
  XML_CTYPE_MIXED,
  XML_CTYPE_NAME,
  XML_CTYPE_CHOICE,
  XML_CTYPE_SEQ
};

enum XML_Content_Quant {
  XML_CQUANT_NONE,
  XML_CQUANT_OPT,
  XML_CQUANT_REP,
  XML_CQUANT_PLUS
};

/* If type == XML_CTYPE_EMPTY or XML_CTYPE_ANY, then quant will be
   XML_CQUANT_NONE, and the other fields will be zero or NULL.
   If type == XML_CTYPE_MIXED, then quant will be NONE or REP and
   numchildren will contain number of elements that may be mixed in
   and children point to an array of XML_Content cells that will be
   all of XML_CTYPE_NAME type with no quantification.

   If type == XML_CTYPE_NAME, then the name points to the name, and
   the numchildren field will be zero and children will be NULL. The
   quant fields indicates any quantifiers placed on the name.

   CHOICE and SEQ will have name NULL, the number of children in
   numchildren and children will point, recursively, to an array
   of XML_Content cells.

   The EMPTY, ANY, and MIXED types will only occur at top level.
*/

typedef struct XML_cp XML_Content;

struct XML_cp {
  enum XML_Content_Type         type;
  enum XML_Content_Quant        quant;
  XML_Char *                    name;
  unsigned int                  numchildren;
  XML_Content *                 children;
};


/* This is called for an element declaration. See above for
   description of the model argument. It's the caller's responsibility
   to free model when finished with it.
*/
typedef void (XMLCALL *XML_ElementDeclHandler) (void *userData,
                                                const XML_Char *name,
                                                XML_Content *model);

XMLPARSEAPI(void)
XML_SetElementDeclHandler(XML_Parser parser,
                          XML_ElementDeclHandler eldecl);

/* The Attlist declaration handler is called for *each* attribute. So
   a single Attlist declaration with multiple attributes declared will
   generate multiple calls to this handler. The "default" parameter
   may be NULL in the case of the "#IMPLIED" or "#REQUIRED"
   keyword. The "isrequired" parameter will be true and the default
   value will be NULL in the case of "#REQUIRED". If "isrequired" is
   true and default is non-NULL, then this is a "#FIXED" default.
*/
typedef void (XMLCALL *XML_AttlistDeclHandler) (
                                    void            *userData,
                                    const XML_Char  *elname,
                                    const XML_Char  *attname,
                                    const XML_Char  *att_type,
                                    const XML_Char  *dflt,
                                    int              isrequired);

XMLPARSEAPI(void)
XML_SetAttlistDeclHandler(XML_Parser parser,
                          XML_AttlistDeclHandler attdecl);

/* The XML declaration handler is called for *both* XML declarations
   and text declarations. The way to distinguish is that the version
   parameter will be NULL for text declarations. The encoding
   parameter may be NULL for XML declarations. The standalone
   parameter will be -1, 0, or 1 indicating respectively that there
   was no standalone parameter in the declaration, that it was given
   as no, or that it was given as yes.
*/
typedef void (XMLCALL *XML_XmlDeclHandler) (void           *userData,
                                            const XML_Char *version,
                                            const XML_Char *encoding,
                                            int             standalone);

XMLPARSEAPI(void)
XML_SetXmlDeclHandler(XML_Parser parser,
                      XML_XmlDeclHandler xmldecl);


typedef struct {
  void *(*malloc_fcn)(size_t size);
  void *(*realloc_fcn)(void *ptr, size_t size);
  void (*free_fcn)(void *ptr);
} XML_Memory_Handling_Suite;

/* Constructs a new parser; encoding is the encoding specified by the
   external protocol or NULL if there is none specified.
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreate(const XML_Char *encoding);

/* Constructs a new parser and namespace processor.  Element type
   names and attribute names that belong to a namespace will be
   expanded; unprefixed attribute names are never expanded; unprefixed
   element type names are expanded only if there is a default
   namespace. The expanded name is the concatenation of the namespace
   URI, the namespace separator character, and the local part of the
   name.  If the namespace separator is '\0' then the namespace URI
   and the local part will be concatenated without any separator.
   It is a programming error to use the separator '\0' with namespace
   triplets (see XML_SetReturnNSTriplet).
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreateNS(const XML_Char *encoding, XML_Char namespaceSeparator);


/* Constructs a new parser using the memory management suite referred to
   by memsuite. If memsuite is NULL, then use the standard library memory
   suite. If namespaceSeparator is non-NULL it creates a parser with
   namespace processing as described above. The character pointed at
   will serve as the namespace separator.

   All further memory operations used for the created parser will come from
   the given suite.
*/
XMLPARSEAPI(XML_Parser)
XML_ParserCreate_MM(const XML_Char *encoding,
                    const XML_Memory_Handling_Suite *memsuite,
                    const XML_Char *namespaceSeparator);

/* Prepare a parser object to be re-used.  This is particularly
   valuable when memory allocation overhead is disproportionatly high,
   such as when a large number of small documnents need to be parsed.
   All handlers are cleared from the parser, except for the
   unknownEncodingHandler. The parser's external state is re-initialized
   except for the values of ns and ns_triplets.

   Added in Expat 1.95.3.
*/
XMLPARSEAPI(XML_Bool)
XML_ParserReset(XML_Parser parser, const XML_Char *encoding);

/* atts is array of name/value pairs, terminated by 0;
   names and values are 0 terminated.
*/
typedef void (XMLCALL *XML_StartElementHandler) (void *userData,
                                                 const XML_Char *name,
                                                 const XML_Char **atts);

typedef void (XMLCALL *XML_EndElementHandler) (void *userData,
                                               const XML_Char *name);


/* s is not 0 terminated. */
typedef void (XMLCALL *XML_CharacterDataHandler) (void *userData,
                                                  const XML_Char *s,
                                                  int len);

/* target and data are 0 terminated */
typedef void (XMLCALL *XML_ProcessingInstructionHandler) (
                                                void *userData,
                                                const XML_Char *target,
                                                const XML_Char *data);

/* data is 0 terminated */
typedef void (XMLCALL *XML_CommentHandler) (void *userData,
                                            const XML_Char *data);

typedef void (XMLCALL *XML_StartCdataSectionHandler) (void *userData);
typedef void (XMLCALL *XML_EndCdataSectionHandler) (void *userData);

/* This is called for any characters in the XML document for which
   there is no applicable handler.  This includes both characters that
   are part of markup which is of a kind that is not reported
   (comments, markup declarations), or characters that are part of a
   construct which could be reported but for which no handler has been
   supplied. The characters are passed exactly as they were in the XML
   document except that they will be encoded in UTF-8 or UTF-16.
   Line boundaries are not normalized. Note that a byte order mark
   character is not passed to the default handler. There are no
   guarantees about how characters are divided between calls to the
   default handler: for example, a comment might be split between
   multiple calls.
*/
typedef void (XMLCALL *XML_DefaultHandler) (void *userData,
                                            const XML_Char *s,
                                            int len);

/* This is called for the start of the DOCTYPE declaration, before
   any DTD or internal subset is parsed.
*/
typedef void (XMLCALL *XML_StartDoctypeDeclHandler) (
                                            void *userData,
                                            const XML_Char *doctypeName,
                                            const XML_Char *sysid,
                                            const XML_Char *pubid,
                                            int has_internal_subset);

/* This is called for the start of the DOCTYPE declaration when the
   closing > is encountered, but after processing any external
   subset.
*/
typedef void (XMLCALL *XML_EndDoctypeDeclHandler)(void *userData);

/* This is called for entity declarations. The is_parameter_entity
   argument will be non-zero if the entity is a parameter entity, zero
   otherwise.

   For internal entities (<!ENTITY foo "bar">), value will
   be non-NULL and systemId, publicID, and notationName will be NULL.
   The value string is NOT nul-terminated; the length is provided in
   the value_length argument. Since it is legal to have zero-length
   values, do not use this argument to test for internal entities.

   For external entities, value will be NULL and systemId will be
   non-NULL. The publicId argument will be NULL unless a public
   identifier was provided. The notationName argument will have a
   non-NULL value only for unparsed entity declarations.

   Note that is_parameter_entity can't be changed to XML_Bool, since
   that would break binary compatibility.
*/
typedef void (XMLCALL *XML_EntityDeclHandler) (
                              void *userData,
                              const XML_Char *entityName,
                              int is_parameter_entity,
                              const XML_Char *value,
                              int value_length,
                              const XML_Char *base,
                              const XML_Char *systemId,
                              const XML_Char *publicId,
                              const XML_Char *notationName);

XMLPARSEAPI(void)
XML_SetEntityDeclHandler(XML_Parser parser,
                         XML_EntityDeclHandler handler);

/* OBSOLETE -- OBSOLETE -- OBSOLETE
   This handler has been superceded by the EntityDeclHandler above.
   It is provided here for backward compatibility.

   This is called for a declaration of an unparsed (NDATA) entity.
   The base argument is whatever was set by XML_SetBase. The
   entityName, systemId and notationName arguments will never be
   NULL. The other arguments may be.
*/
typedef void (XMLCALL *XML_UnparsedEntityDeclHandler) (
                                    void *userData,
                                    const XML_Char *entityName,
                                    const XML_Char *base,
                                    const XML_Char *systemId,
                                    const XML_Char *publicId,
                                    const XML_Char *notationName);

/* This is called for a declaration of notation.  The base argument is
   whatever was set by XML_SetBase. The notationName will never be
   NULL.  The other arguments can be.
*/
typedef void (XMLCALL *XML_NotationDeclHandler) (
                                    void *userData,
                                    const XML_Char *notationName,
                                    const XML_Char *base,
                                    const XML_Char *systemId,
                                    const XML_Char *publicId);

/* When namespace processing is enabled, these are called once for
   each namespace declaration. The call to the start and end element
   handlers occur between the calls to the start and end namespace
   declaration handlers. For an xmlns attribute, prefix will be
   NULL.  For an xmlns="" attribute, uri will be NULL.
*/
typedef void (XMLCALL *XML_StartNamespaceDeclHandler) (
                                    void *userData,
                                    const XML_Char *prefix,
                                    const XML_Char *uri);

typedef void (XMLCALL *XML_EndNamespaceDeclHandler) (
                                    void *userData,
                                    const XML_Char *prefix);

/* This is called if the document is not standalone, that is, it has an
   external subset or a reference to a parameter entity, but does not
   have standalone="yes". If this handler returns XML_STATUS_ERROR,
   then processing will not continue, and the parser will return a
   XML_ERROR_NOT_STANDALONE error.
   If parameter entity parsing is enabled, then in addition to the
   conditions above this handler will only be called if the referenced
   entity was actually read.
*/
typedef int (XMLCALL *XML_NotStandaloneHandler) (void *userData);

/* This is called for a reference to an external parsed general
   entity.  The referenced entity is not automatically parsed.  The
   application can parse it immediately or later using
   XML_ExternalEntityParserCreate.

   The parser argument is the parser parsing the entity containing the
   reference; it can be passed as the parser argument to
   XML_ExternalEntityParserCreate.  The systemId argument is the
   system identifier as specified in the entity declaration; it will
   not be NULL.

   The base argument is the system identifier that should be used as
   the base for resolving systemId if systemId was relative; this is
   set by XML_SetBase; it may be NULL.

   The publicId argument is the public identifier as specified in the
   entity declaration, or NULL if none was specified; the whitespace
   in the public identifier will have been normalized as required by
   the XML spec.

   The context argument specifies the parsing context in the format
   expected by the context argument to XML_ExternalEntityParserCreate;
   context is valid only until the handler returns, so if the
   referenced entity is to be parsed later, it must be copied.
   context is NULL only when the entity is a parameter entity.

   The handler should return XML_STATUS_ERROR if processing should not
   continue because of a fatal error in the handling of the external
   entity.  In this case the calling parser will return an
   XML_ERROR_EXTERNAL_ENTITY_HANDLING error.

   Note that unlike other handlers the first argument is the parser,
   not userData.
*/
typedef int (XMLCALL *XML_ExternalEntityRefHandler) (
                                    XML_Parser parser,
                                    const XML_Char *context,
                                    const XML_Char *base,
                                    const XML_Char *systemId,
                                    const XML_Char *publicId);

/* This is called in two situations:
   1) An entity reference is encountered for which no declaration
      has been read *and* this is not an error.
   2) An internal entity reference is read, but not expanded, because
      XML_SetDefaultHandler has been called.
   Note: skipped parameter entities in declarations and skipped general
         entities in attribute values cannot be reported, because
         the event would be out of sync with the reporting of the
         declarations or attribute values
*/
typedef void (XMLCALL *XML_SkippedEntityHandler) (
                                    void *userData,
                                    const XML_Char *entityName,
                                    int is_parameter_entity);

/* This structure is filled in by the XML_UnknownEncodingHandler to
   provide information to the parser about encodings that are unknown
   to the parser.

   The map[b] member gives information about byte sequences whose
   first byte is b.

   If map[b] is c where c is >= 0, then b by itself encodes the
   Unicode scalar value c.

   If map[b] is -1, then the byte sequence is malformed.

   If map[b] is -n, where n >= 2, then b is the first byte of an
   n-byte sequence that encodes a single Unicode scalar value.

   The data member will be passed as the first argument to the convert
   function.

   The convert function is used to convert multibyte sequences; s will
   point to a n-byte sequence where map[(unsigned char)*s] == -n.  The
   convert function must return the Unicode scalar value represented
   by this byte sequence or -1 if the byte sequence is malformed.

   The convert function may be NULL if the encoding is a single-byte
   encoding, that is if map[b] >= -1 for all bytes b.

   When the parser is finished with the encoding, then if release is
   not NULL, it will call release passing it the data member; once
   release has been called, the convert function will not be called
   again.

   Expat places certain restrictions on the encodings that are supported
   using this mechanism.

   1. Every ASCII character that can appear in a well-formed XML document,
      other than the characters

      $@\^`{}~

      must be represented by a single byte, and that byte must be the
      same byte that represents that character in ASCII.

   2. No character may require more than 4 bytes to encode.

   3. All characters encoded must have Unicode scalar values <=
      0xFFFF, (i.e., characters that would be encoded by surrogates in
      UTF-16 are  not allowed).  Note that this restriction doesn't
      apply to the built-in support for UTF-8 and UTF-16.

   4. No Unicode character may be encoded by more than one distinct
      sequence of bytes.
*/
typedef struct {
  int map[256];
  void *data;
  int (XMLCALL *convert)(void *data, const char *s);
  void (XMLCALL *release)(void *data);
} XML_Encoding;

/* This is called for an encoding that is unknown to the parser.

   The encodingHandlerData argument is that which was passed as the
   second argument to XML_SetUnknownEncodingHandler.

   The name argument gives the name of the encoding as specified in
   the encoding declaration.

   If the callback can provide information about the encoding, it must
   fill in the XML_Encoding structure, and return XML_STATUS_OK.
   Otherwise it must return XML_STATUS_ERROR.

   If info does not describe a suitable encoding, then the parser will
   return an XML_UNKNOWN_ENCODING error.
*/
typedef int (XMLCALL *XML_UnknownEncodingHandler) (
                                    void *encodingHandlerData,
                                    const XML_Char *name,
                                    XML_Encoding *info);

XMLPARSEAPI(void)
XML_SetElementHandler(XML_Parser parser,
                      XML_StartElementHandler start,
                      XML_EndElementHandler end);

XMLPARSEAPI(void)
XML_SetStartElementHandler(XML_Parser parser,
                           XML_StartElementHandler handler);

XMLPARSEAPI(void)
XML_SetEndElementHandler(XML_Parser parser,
                         XML_EndElementHandler handler);

XMLPARSEAPI(void)
XML_SetCharacterDataHandler(XML_Parser parser,
                            XML_CharacterDataHandler handler);

XMLPARSEAPI(void)
XML_SetProcessingInstructionHandler(XML_Parser parser,
                                    XML_ProcessingInstructionHandler handler);
XMLPARSEAPI(void)
XML_SetCommentHandler(XML_Parser parser,
                      XML_CommentHandler handler);

XMLPARSEAPI(void)
XML_SetCdataSectionHandler(XML_Parser parser,
                           XML_StartCdataSectionHandler start,
                           XML_EndCdataSectionHandler end);

XMLPARSEAPI(void)
XML_SetStartCdataSectionHandler(XML_Parser parser,
                                XML_StartCdataSectionHandler start);

XMLPARSEAPI(void)
XML_SetEndCdataSectionHandler(XML_Parser parser,
                              XML_EndCdataSectionHandler end);

/* This sets the default handler and also inhibits expansion of
   internal entities. These entity references will be passed to the
   default handler, or to the skipped entity handler, if one is set.
*/
XMLPARSEAPI(void)
XML_SetDefaultHandler(XML_Parser parser,
                      XML_DefaultHandler handler);

/* This sets the default handler but does not inhibit expansion of
   internal entities.  The entity reference will not be passed to the
   default handler.
*/
XMLPARSEAPI(void)
XML_SetDefaultHandlerExpand(XML_Parser parser,
                            XML_DefaultHandler handler);

XMLPARSEAPI(void)
XML_SetDoctypeDeclHandler(XML_Parser parser,
                          XML_StartDoctypeDeclHandler start,
                          XML_EndDoctypeDeclHandler end);

XMLPARSEAPI(void)
XML_SetStartDoctypeDeclHandler(XML_Parser parser,
                               XML_StartDoctypeDeclHandler start);

XMLPARSEAPI(void)
XML_SetEndDoctypeDeclHandler(XML_Parser parser,
                             XML_EndDoctypeDeclHandler end);

XMLPARSEAPI(void)
XML_SetUnparsedEntityDeclHandler(XML_Parser parser,
                                 XML_UnparsedEntityDeclHandler handler);

XMLPARSEAPI(void)
XML_SetNotationDeclHandler(XML_Parser parser,
                           XML_NotationDeclHandler handler);

XMLPARSEAPI(void)
XML_SetNamespaceDeclHandler(XML_Parser parser,
                            XML_StartNamespaceDeclHandler start,
                            XML_EndNamespaceDeclHandler end);

XMLPARSEAPI(void)
XML_SetStartNamespaceDeclHandler(XML_Parser parser,
                                 XML_StartNamespaceDeclHandler start);

XMLPARSEAPI(void)
XML_SetEndNamespaceDeclHandler(XML_Parser parser,
                               XML_EndNamespaceDeclHandler end);

XMLPARSEAPI(void)
XML_SetNotStandaloneHandler(XML_Parser parser,
                            XML_NotStandaloneHandler handler);

XMLPARSEAPI(void)
XML_SetExternalEntityRefHandler(XML_Parser parser,
                                XML_ExternalEntityRefHandler handler);

/* If a non-NULL value for arg is specified here, then it will be
   passed as the first argument to the external entity ref handler
   instead of the parser object.
*/
XMLPARSEAPI(void)
XML_SetExternalEntityRefHandlerArg(XML_Parser parser,
                                   void *arg);

XMLPARSEAPI(void)
XML_SetSkippedEntityHandler(XML_Parser parser,
                            XML_SkippedEntityHandler handler);

XMLPARSEAPI(void)
XML_SetUnknownEncodingHandler(XML_Parser parser,
                              XML_UnknownEncodingHandler handler,
                              void *encodingHandlerData);

/* This can be called within a handler for a start element, end
   element, processing instruction or character data.  It causes the
   corresponding markup to be passed to the default handler.
*/
XMLPARSEAPI(void)
XML_DefaultCurrent(XML_Parser parser);

/* If do_nst is non-zero, and namespace processing is in effect, and
   a name has a prefix (i.e. an explicit namespace qualifier) then
   that name is returned as a triplet in a single string separated by
   the separator character specified when the parser was created: URI
   + sep + local_name + sep + prefix.

   If do_nst is zero, then namespace information is returned in the
   default manner (URI + sep + local_name) whether or not the name
   has a prefix.

   Note: Calling XML_SetReturnNSTriplet after XML_Parse or
     XML_ParseBuffer has no effect.
*/

XMLPARSEAPI(void)
XML_SetReturnNSTriplet(XML_Parser parser, int do_nst);

/* This value is passed as the userData argument to callbacks. */
XMLPARSEAPI(void)
XML_SetUserData(XML_Parser parser, void *userData);

/* Returns the last value set by XML_SetUserData or NULL. */
#define XML_GetUserData(parser) (*(void **)(parser))

/* This is equivalent to supplying an encoding argument to
   XML_ParserCreate. On success XML_SetEncoding returns non-zero,
   zero otherwise.
   Note: Calling XML_SetEncoding after XML_Parse or XML_ParseBuffer
     has no effect and returns XML_STATUS_ERROR.
*/
XMLPARSEAPI(enum XML_Status)
XML_SetEncoding(XML_Parser parser, const XML_Char *encoding);

/* If this function is called, then the parser will be passed as the
   first argument to callbacks instead of userData.  The userData will
   still be accessible using XML_GetUserData.
*/
XMLPARSEAPI(void)
XML_UseParserAsHandlerArg(XML_Parser parser);

/* If useDTD == XML_TRUE is passed to this function, then the parser
   will assume that there is an external subset, even if none is
   specified in the document. In such a case the parser will call the
   externalEntityRefHandler with a value of NULL for the systemId
   argument (the publicId and context arguments will be NULL as well).
   Note: For the purpose of checking WFC: Entity Declared, passing
     useDTD == XML_TRUE will make the parser behave as if the document
     had a DTD with an external subset.
   Note: If this function is called, then this must be done before
     the first call to XML_Parse or XML_ParseBuffer, since it will
     have no effect after that.  Returns
     XML_ERROR_CANT_CHANGE_FEATURE_ONCE_PARSING.
   Note: If the document does not have a DOCTYPE declaration at all,
     then startDoctypeDeclHandler and endDoctypeDeclHandler will not
     be called, despite an external subset being parsed.
   Note: If XML_DTD is not defined when Expat is compiled, returns
     XML_ERROR_FEATURE_REQUIRES_XML_DTD.
*/
XMLPARSEAPI(enum XML_Error)
XML_UseForeignDTD(XML_Parser parser, XML_Bool useDTD);


/* Sets the base to be used for resolving relative URIs in system
   identifiers in declarations.  Resolving relative identifiers is
   left to the application: this value will be passed through as the
   base argument to the XML_ExternalEntityRefHandler,
   XML_NotationDeclHandler and XML_UnparsedEntityDeclHandler. The base
   argument will be copied.  Returns XML_STATUS_ERROR if out of memory,
   XML_STATUS_OK otherwise.
*/
XMLPARSEAPI(enum XML_Status)
XML_SetBase(XML_Parser parser, const XML_Char *base);

XMLPARSEAPI(const XML_Char *)
XML_GetBase(XML_Parser parser);

/* Returns the number of the attribute/value pairs passed in last call
   to the XML_StartElementHandler that were specified in the start-tag
   rather than defaulted. Each attribute/value pair counts as 2; thus
   this correspondds to an index into the atts array passed to the
   XML_StartElementHandler.
*/
XMLPARSEAPI(int)
XML_GetSpecifiedAttributeCount(XML_Parser parser);

/* Returns the index of the ID attribute passed in the last call to
   XML_StartElementHandler, or -1 if there is no ID attribute.  Each
   attribute/value pair counts as 2; thus this correspondds to an
   index into the atts array passed to the XML_StartElementHandler.
*/
XMLPARSEAPI(int)
XML_GetIdAttributeIndex(XML_Parser parser);

/* Parses some input. Returns XML_STATUS_ERROR if a fatal error is
   detected.  The last call to XML_Parse must have isFinal true; len
   may be zero for this call (or any other).

   Though the return values for these functions has always been
   described as a Boolean value, the implementation, at least for the
   1.95.x series, has always returned exactly one of the XML_Status
   values.
*/
XMLPARSEAPI(enum XML_Status)
XML_Parse(XML_Parser parser, const char *s, int len, int isFinal);

XMLPARSEAPI(void *)
XML_GetBuffer(XML_Parser parser, int len);

XMLPARSEAPI(enum XML_Status)
XML_ParseBuffer(XML_Parser parser, int len, int isFinal);

/* Stops parsing, causing XML_Parse() or XML_ParseBuffer() to return.
   Must be called from within a call-back handler, except when aborting
   (resumable = 0) an already suspended parser. Some call-backs may
   still follow because they would otherwise get lost. Examples:
   - endElementHandler() for empty elements when stopped in
     startElementHandler(), 
   - endNameSpaceDeclHandler() when stopped in endElementHandler(), 
   and possibly others.

   Can be called from most handlers, including DTD related call-backs,
   except when parsing an external parameter entity and resumable != 0.
   Returns XML_STATUS_OK when successful, XML_STATUS_ERROR otherwise.
   Possible error codes: 
   - XML_ERROR_SUSPENDED: when suspending an already suspended parser.
   - XML_ERROR_FINISHED: when the parser has already finished.
   - XML_ERROR_SUSPEND_PE: when suspending while parsing an external PE.

   When resumable != 0 (true) then parsing is suspended, that is, 
   XML_Parse() and XML_ParseBuffer() return XML_STATUS_SUSPENDED. 
   Otherwise, parsing is aborted, that is, XML_Parse() and XML_ParseBuffer()
   return XML_STATUS_ERROR with error code XML_ERROR_ABORTED.

   *Note*:
   This will be applied to the current parser instance only, that is, if
   there is a parent parser then it will continue parsing when the
   externalEntityRefHandler() returns. It is up to the implementation of
   the externalEntityRefHandler() to call XML_StopParser() on the parent
   parser (recursively), if one wants to stop parsing altogether.

   When suspended, parsing can be resumed by calling XML_ResumeParser(). 
*/
XMLPARSEAPI(enum XML_Status)
XML_StopParser(XML_Parser parser, XML_Bool resumable);

/* Resumes parsing after it has been suspended with XML_StopParser().
   Must not be called from within a handler call-back. Returns same
   status codes as XML_Parse() or XML_ParseBuffer().
   Additional error code XML_ERROR_NOT_SUSPENDED possible.   

   *Note*:
   This must be called on the most deeply nested child parser instance
   first, and on its parent parser only after the child parser has finished,
   to be applied recursively until the document entity's parser is restarted.
   That is, the parent parser will not resume by itself and it is up to the
   application to call XML_ResumeParser() on it at the appropriate moment.
*/
XMLPARSEAPI(enum XML_Status)
XML_ResumeParser(XML_Parser parser);

enum XML_Parsing {
  XML_INITIALIZED,
  XML_PARSING,
  XML_FINISHED,
  XML_SUSPENDED
};

typedef struct {
  enum XML_Parsing parsing;
  XML_Bool finalBuffer;
} XML_ParsingStatus;

/* Returns status of parser with respect to being initialized, parsing,
   finished, or suspended and processing the final buffer.
   XXX XML_Parse() and XML_ParseBuffer() should return XML_ParsingStatus,
   XXX with XML_FINISHED_OK or XML_FINISHED_ERROR replacing XML_FINISHED
*/
XMLPARSEAPI(void)
XML_GetParsingStatus(XML_Parser parser, XML_ParsingStatus *status);

/* Creates an XML_Parser object that can parse an external general
   entity; context is a '\0'-terminated string specifying the parse
   context; encoding is a '\0'-terminated string giving the name of
   the externally specified encoding, or NULL if there is no
   externally specified encoding.  The context string consists of a
   sequence of tokens separated by formfeeds (\f); a token consisting
   of a name specifies that the general entity of the name is open; a
   token of the form prefix=uri specifies the namespace for a
   particular prefix; a token of the form =uri specifies the default
   namespace.  This can be called at any point after the first call to
   an ExternalEntityRefHandler so longer as the parser has not yet
   been freed.  The new parser is completely independent and may
   safely be used in a separate thread.  The handlers and userData are
   initialized from the parser argument.  Returns NULL if out of memory.
   Otherwise returns a new XML_Parser object.
*/
XMLPARSEAPI(XML_Parser)
XML_ExternalEntityParserCreate(XML_Parser parser,
                               const XML_Char *context,
                               const XML_Char *encoding);

enum XML_ParamEntityParsing {
  XML_PARAM_ENTITY_PARSING_NEVER,
  XML_PARAM_ENTITY_PARSING_UNLESS_STANDALONE,
  XML_PARAM_ENTITY_PARSING_ALWAYS
};

/* Controls parsing of parameter entities (including the external DTD
   subset). If parsing of parameter entities is enabled, then
   references to external parameter entities (including the external
   DTD subset) will be passed to the handler set with
   XML_SetExternalEntityRefHandler.  The context passed will be 0.

   Unlike external general entities, external parameter entities can
   only be parsed synchronously.  If the external parameter entity is
   to be parsed, it must be parsed during the call to the external
   entity ref handler: the complete sequence of
   XML_ExternalEntityParserCreate, XML_Parse/XML_ParseBuffer and
   XML_ParserFree calls must be made during this call.  After
   XML_ExternalEntityParserCreate has been called to create the parser
   for the external parameter entity (context must be 0 for this
   call), it is illegal to make any calls on the old parser until
   XML_ParserFree has been called on the newly created parser.
   If the library has been compiled without support for parameter
   entity parsing (ie without XML_DTD being defined), then
   XML_SetParamEntityParsing will return 0 if parsing of parameter
   entities is requested; otherwise it will return non-zero.
   Note: If XML_SetParamEntityParsing is called after XML_Parse or
      XML_ParseBuffer, then it has no effect and will always return 0.
*/
XMLPARSEAPI(int)
XML_SetParamEntityParsing(XML_Parser parser,
                          enum XML_ParamEntityParsing parsing);

/* If XML_Parse or XML_ParseBuffer have returned XML_STATUS_ERROR, then
   XML_GetErrorCode returns information about the error.
*/
XMLPARSEAPI(enum XML_Error)
XML_GetErrorCode(XML_Parser parser);

/* These functions return information about the current parse
   location.  They may be called from any callback called to report
   some parse event; in this case the location is the location of the
   first of the sequence of characters that generated the event.  When
   called from callbacks generated by declarations in the document
   prologue, the location identified isn't as neatly defined, but will
   be within the relevant markup.  When called outside of the callback
   functions, the position indicated will be just past the last parse
   event (regardless of whether there was an associated callback).
   
   They may also be called after returning from a call to XML_Parse
   or XML_ParseBuffer.  If the return value is XML_STATUS_ERROR then
   the location is the location of the character at which the error
   was detected; otherwise the location is the location of the last
   parse event, as described above.
*/
XMLPARSEAPI(XML_Size) XML_GetCurrentLineNumber(XML_Parser parser);
XMLPARSEAPI(XML_Size) XML_GetCurrentColumnNumber(XML_Parser parser);
XMLPARSEAPI(XML_Index) XML_GetCurrentByteIndex(XML_Parser parser);

/* Return the number of bytes in the current event.
   Returns 0 if the event is in an internal entity.
*/
XMLPARSEAPI(int)
XML_GetCurrentByteCount(XML_Parser parser);

/* If XML_CONTEXT_BYTES is defined, returns the input buffer, sets
   the integer pointed to by offset to the offset within this buffer
   of the current parse position, and sets the integer pointed to by size
   to the size of this buffer (the number of input bytes). Otherwise
   returns a NULL pointer. Also returns a NULL pointer if a parse isn't
   active.

   NOTE: The character pointer returned should not be used outside
   the handler that makes the call.
*/
XMLPARSEAPI(const char *)
XML_GetInputContext(XML_Parser parser,
                    int *offset,
                    int *size);

/* For backwards compatibility with previous versions. */
#define XML_GetErrorLineNumber   XML_GetCurrentLineNumber
#define XML_GetErrorColumnNumber XML_GetCurrentColumnNumber
#define XML_GetErrorByteIndex    XML_GetCurrentByteIndex

/* Frees the content model passed to the element declaration handler */
XMLPARSEAPI(void)
XML_FreeContentModel(XML_Parser parser, XML_Content *model);

/* Exposing the memory handling functions used in Expat */
XMLPARSEAPI(void *)
XML_MemMalloc(XML_Parser parser, size_t size);

XMLPARSEAPI(void *)
XML_MemRealloc(XML_Parser parser, void *ptr, size_t size);

XMLPARSEAPI(void)
XML_MemFree(XML_Parser parser, void *ptr);

/* Frees memory used by the parser. */
XMLPARSEAPI(void)
XML_ParserFree(XML_Parser parser);

/* Returns a string describing the error. */
XMLPARSEAPI(const XML_LChar *)
XML_ErrorString(enum XML_Error code);

/* Return a string containing the version number of this expat */
XMLPARSEAPI(const XML_LChar *)
XML_ExpatVersion(void);

typedef struct {
  int major;
  int minor;
  int micro;
} XML_Expat_Version;

/* Return an XML_Expat_Version structure containing numeric version
   number information for this version of expat.
*/
XMLPARSEAPI(XML_Expat_Version)
XML_ExpatVersionInfo(void);

/* Added in Expat 1.95.5. */
enum XML_FeatureEnum {
  XML_FEATURE_END = 0,
  XML_FEATURE_UNICODE,
  XML_FEATURE_UNICODE_WCHAR_T,
  XML_FEATURE_DTD,
  XML_FEATURE_CONTEXT_BYTES,
  XML_FEATURE_MIN_SIZE,
  XML_FEATURE_SIZEOF_XML_CHAR,
  XML_FEATURE_SIZEOF_XML_LCHAR,
  XML_FEATURE_NS,
  XML_FEATURE_LARGE_SIZE
  /* Additional features must be added to the end of this enum. */
};

typedef struct {
  enum XML_FeatureEnum  feature;
  const XML_LChar       *name;
  long int              value;
} XML_Feature;

XMLPARSEAPI(const XML_Feature *)
XML_GetFeatureList(void);


/* Expat follows the GNU/Linux convention of odd number minor version for
   beta/development releases and even number minor version for stable
   releases. Micro is bumped with each release, and set to 0 with each
   change to major or minor version.
*/
#define XML_MAJOR_VERSION 2
#define XML_MINOR_VERSION 0
#define XML_MICRO_VERSION 1

#ifdef __cplusplus
}
#endif

#endif /* not Expat_INCLUDED */

// ---- internal.h ----
/* internal.h

   Internal definitions used by Expat.  This is not needed to compile
   client code.

   The following calling convention macros are defined for frequently
   called functions:

   FASTCALL    - Used for those internal functions that have a simple
                 body and a low number of arguments and local variables.

   PTRCALL     - Used for functions called though function pointers.

   PTRFASTCALL - Like PTRCALL, but for low number of arguments.

   inline      - Used for selected internal functions for which inlining
                 may improve performance on some platforms.

   Note: Use of these macros is based on judgement, not hard rules,
         and therefore subject to change.
*/

#if defined(__GNUC__) && defined(__i386__) && !defined(__MINGW32__)
/* We'll use this version by default only where we know it helps.

   regparm() generates warnings on Solaris boxes.   See SF bug #692878.

   Instability reported with egcs on a RedHat Linux 7.3.
   Let's comment out:
   #define FASTCALL __attribute__((stdcall, regparm(3)))
   and let's try this:
*/
#define FASTCALL __attribute__((regparm(3)))
#define PTRFASTCALL __attribute__((regparm(3)))
#endif

/* Using __fastcall seems to have an unexpected negative effect under
   MS VC++, especially for function pointers, so we won't use it for
   now on that platform. It may be reconsidered for a future release
   if it can be made more effective.
   Likely reason: __fastcall on Windows is like stdcall, therefore
   the compiler cannot perform stack optimizations for call clusters.
*/

/* Make sure all of these are defined if they aren't already. */

#ifndef FASTCALL
#define FASTCALL
#endif

#ifndef PTRCALL
#define PTRCALL
#endif

#ifndef PTRFASTCALL
#define PTRFASTCALL
#endif

#ifndef XML_MIN_SIZE
#if !defined(__cplusplus) && !defined(inline)
#ifdef __GNUC__
#define inline __inline
#endif /* __GNUC__ */
#endif
#endif /* XML_MIN_SIZE */

#ifdef __cplusplus
#define inline inline
#else
#ifndef inline
#define inline
#endif
#endif

// ---- xmltok.h ----
/* Copyright (c) 1998, 1999 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

#ifndef XmlTok_INCLUDED
#define XmlTok_INCLUDED 1

#ifdef __cplusplus
extern "C" {
#endif

/* The following token may be returned by XmlContentTok */
#define XML_TOK_TRAILING_RSQB -5 /* ] or ]] at the end of the scan; might be
                                    start of illegal ]]> sequence */
/* The following tokens may be returned by both XmlPrologTok and
   XmlContentTok.
*/
#define XML_TOK_NONE -4          /* The string to be scanned is empty */
#define XML_TOK_TRAILING_CR -3   /* A CR at the end of the scan;
                                    might be part of CRLF sequence */
#define XML_TOK_PARTIAL_CHAR -2  /* only part of a multibyte sequence */
#define XML_TOK_PARTIAL -1       /* only part of a token */
#define XML_TOK_INVALID 0

/* The following tokens are returned by XmlContentTok; some are also
   returned by XmlAttributeValueTok, XmlEntityTok, XmlCdataSectionTok.
*/
#define XML_TOK_START_TAG_WITH_ATTS 1
#define XML_TOK_START_TAG_NO_ATTS 2
#define XML_TOK_EMPTY_ELEMENT_WITH_ATTS 3 /* empty element tag <e/> */
#define XML_TOK_EMPTY_ELEMENT_NO_ATTS 4
#define XML_TOK_END_TAG 5
#define XML_TOK_DATA_CHARS 6
#define XML_TOK_DATA_NEWLINE 7
#define XML_TOK_CDATA_SECT_OPEN 8
#define XML_TOK_ENTITY_REF 9
#define XML_TOK_CHAR_REF 10               /* numeric character reference */

/* The following tokens may be returned by both XmlPrologTok and
   XmlContentTok.
*/
#define XML_TOK_PI 11                     /* processing instruction */
#define XML_TOK_XML_DECL 12               /* XML decl or text decl */
#define XML_TOK_COMMENT 13
#define XML_TOK_BOM 14                    /* Byte order mark */

/* The following tokens are returned only by XmlPrologTok */
#define XML_TOK_PROLOG_S 15
#define XML_TOK_DECL_OPEN 16              /* <!foo */
#define XML_TOK_DECL_CLOSE 17             /* > */
#define XML_TOK_NAME 18
#define XML_TOK_NMTOKEN 19
#define XML_TOK_POUND_NAME 20             /* #name */
#define XML_TOK_OR 21                     /* | */
#define XML_TOK_PERCENT 22
#define XML_TOK_OPEN_PAREN 23
#define XML_TOK_CLOSE_PAREN 24
#define XML_TOK_OPEN_BRACKET 25
#define XML_TOK_CLOSE_BRACKET 26
#define XML_TOK_LITERAL 27
#define XML_TOK_PARAM_ENTITY_REF 28
#define XML_TOK_INSTANCE_START 29

/* The following occur only in element type declarations */
#define XML_TOK_NAME_QUESTION 30          /* name? */
#define XML_TOK_NAME_ASTERISK 31          /* name* */
#define XML_TOK_NAME_PLUS 32              /* name+ */
#define XML_TOK_COND_SECT_OPEN 33         /* <![ */
#define XML_TOK_COND_SECT_CLOSE 34        /* ]]> */
#define XML_TOK_CLOSE_PAREN_QUESTION 35   /* )? */
#define XML_TOK_CLOSE_PAREN_ASTERISK 36   /* )* */
#define XML_TOK_CLOSE_PAREN_PLUS 37       /* )+ */
#define XML_TOK_COMMA 38

/* The following token is returned only by XmlAttributeValueTok */
#define XML_TOK_ATTRIBUTE_VALUE_S 39

/* The following token is returned only by XmlCdataSectionTok */
#define XML_TOK_CDATA_SECT_CLOSE 40

/* With namespace processing this is returned by XmlPrologTok for a
   name with a colon.
*/
#define XML_TOK_PREFIXED_NAME 41

#ifdef XML_DTD
#define XML_TOK_IGNORE_SECT 42
#endif /* XML_DTD */

#ifdef XML_DTD
#define XML_N_STATES 4
#else /* not XML_DTD */
#define XML_N_STATES 3
#endif /* not XML_DTD */

#define XML_PROLOG_STATE 0
#define XML_CONTENT_STATE 1
#define XML_CDATA_SECTION_STATE 2
#ifdef XML_DTD
#define XML_IGNORE_SECTION_STATE 3
#endif /* XML_DTD */

#define XML_N_LITERAL_TYPES 2
#define XML_ATTRIBUTE_VALUE_LITERAL 0
#define XML_ENTITY_VALUE_LITERAL 1

/* The size of the buffer passed to XmlUtf8Encode must be at least this. */
#define XML_UTF8_ENCODE_MAX 4
/* The size of the buffer passed to XmlUtf16Encode must be at least this. */
#define XML_UTF16_ENCODE_MAX 2

typedef struct position {
  /* first line and first column are 0 not 1 */
  XML_Size lineNumber;
  XML_Size columnNumber;
} POSITION;

typedef struct {
  const char *name;
  const char *valuePtr;
  const char *valueEnd;
  char normalized;
} ATTRIBUTE;

struct encoding;
typedef struct encoding ENCODING;

typedef int (PTRCALL *SCANNER)(const ENCODING *,
                               const char *,
                               const char *,
                               const char **);

struct encoding {
  SCANNER scanners[XML_N_STATES];
  SCANNER literalScanners[XML_N_LITERAL_TYPES];
  int (PTRCALL *sameName)(const ENCODING *,
                          const char *,
                          const char *);
  int (PTRCALL *nameMatchesAscii)(const ENCODING *,
                                  const char *,
                                  const char *,
                                  const char *);
  int (PTRFASTCALL *nameLength)(const ENCODING *, const char *);
  const char *(PTRFASTCALL *skipS)(const ENCODING *, const char *);
  int (PTRCALL *getAtts)(const ENCODING *enc,
                         const char *ptr,
                         int attsMax,
                         ATTRIBUTE *atts);
  int (PTRFASTCALL *charRefNumber)(const ENCODING *enc, const char *ptr);
  int (PTRCALL *predefinedEntityName)(const ENCODING *,
                                      const char *,
                                      const char *);
  void (PTRCALL *updatePosition)(const ENCODING *,
                                 const char *ptr,
                                 const char *end,
                                 POSITION *);
  int (PTRCALL *isPublicId)(const ENCODING *enc,
                            const char *ptr,
                            const char *end,
                            const char **badPtr);
  void (PTRCALL *utf8Convert)(const ENCODING *enc,
                              const char **fromP,
                              const char *fromLim,
                              char **toP,
                              const char *toLim);
  void (PTRCALL *utf16Convert)(const ENCODING *enc,
                               const char **fromP,
                               const char *fromLim,
                               unsigned short **toP,
                               const unsigned short *toLim);
  int minBytesPerChar;
  char isUtf8;
  char isUtf16;
};

/* Scan the string starting at ptr until the end of the next complete
   token, but do not scan past eptr.  Return an integer giving the
   type of token.

   Return XML_TOK_NONE when ptr == eptr; nextTokPtr will not be set.

   Return XML_TOK_PARTIAL when the string does not contain a complete
   token; nextTokPtr will not be set.

   Return XML_TOK_INVALID when the string does not start a valid
   token; nextTokPtr will be set to point to the character which made
   the token invalid.

   Otherwise the string starts with a valid token; nextTokPtr will be
   set to point to the character following the end of that token.

   Each data character counts as a single token, but adjacent data
   characters may be returned together.  Similarly for characters in
   the prolog outside literals, comments and processing instructions.
*/


#define XmlTok(enc, state, ptr, end, nextTokPtr) \
  (((enc)->scanners[state])(enc, ptr, end, nextTokPtr))

#define XmlPrologTok(enc, ptr, end, nextTokPtr) \
   XmlTok(enc, XML_PROLOG_STATE, ptr, end, nextTokPtr)

#define XmlContentTok(enc, ptr, end, nextTokPtr) \
   XmlTok(enc, XML_CONTENT_STATE, ptr, end, nextTokPtr)

#define XmlCdataSectionTok(enc, ptr, end, nextTokPtr) \
   XmlTok(enc, XML_CDATA_SECTION_STATE, ptr, end, nextTokPtr)

#ifdef XML_DTD

#define XmlIgnoreSectionTok(enc, ptr, end, nextTokPtr) \
   XmlTok(enc, XML_IGNORE_SECTION_STATE, ptr, end, nextTokPtr)

#endif /* XML_DTD */

/* This is used for performing a 2nd-level tokenization on the content
   of a literal that has already been returned by XmlTok.
*/
#define XmlLiteralTok(enc, literalType, ptr, end, nextTokPtr) \
  (((enc)->literalScanners[literalType])(enc, ptr, end, nextTokPtr))

#define XmlAttributeValueTok(enc, ptr, end, nextTokPtr) \
   XmlLiteralTok(enc, XML_ATTRIBUTE_VALUE_LITERAL, ptr, end, nextTokPtr)

#define XmlEntityValueTok(enc, ptr, end, nextTokPtr) \
   XmlLiteralTok(enc, XML_ENTITY_VALUE_LITERAL, ptr, end, nextTokPtr)

#define XmlSameName(enc, ptr1, ptr2) (((enc)->sameName)(enc, ptr1, ptr2))

#define XmlNameMatchesAscii(enc, ptr1, end1, ptr2) \
  (((enc)->nameMatchesAscii)(enc, ptr1, end1, ptr2))

#define XmlNameLength(enc, ptr) \
  (((enc)->nameLength)(enc, ptr))

#define XmlSkipS(enc, ptr) \
  (((enc)->skipS)(enc, ptr))

#define XmlGetAttributes(enc, ptr, attsMax, atts) \
  (((enc)->getAtts)(enc, ptr, attsMax, atts))

#define XmlCharRefNumber(enc, ptr) \
  (((enc)->charRefNumber)(enc, ptr))

#define XmlPredefinedEntityName(enc, ptr, end) \
  (((enc)->predefinedEntityName)(enc, ptr, end))

#define XmlUpdatePosition(enc, ptr, end, pos) \
  (((enc)->updatePosition)(enc, ptr, end, pos))

#define XmlIsPublicId(enc, ptr, end, badPtr) \
  (((enc)->isPublicId)(enc, ptr, end, badPtr))

#define XmlUtf8Convert(enc, fromP, fromLim, toP, toLim) \
  (((enc)->utf8Convert)(enc, fromP, fromLim, toP, toLim))

#define XmlUtf16Convert(enc, fromP, fromLim, toP, toLim) \
  (((enc)->utf16Convert)(enc, fromP, fromLim, toP, toLim))

typedef struct {
  ENCODING initEnc;
  const ENCODING **encPtr;
} INIT_ENCODING;

int XmlParseXmlDecl(int isGeneralTextEntity,
                    const ENCODING *enc,
                    const char *ptr,
                    const char *end,
                    const char **badPtr,
                    const char **versionPtr,
                    const char **versionEndPtr,
                    const char **encodingNamePtr,
                    const ENCODING **namedEncodingPtr,
                    int *standalonePtr);

int XmlInitEncoding(INIT_ENCODING *, const ENCODING **, const char *name);
const ENCODING *XmlGetUtf8InternalEncoding(void);
const ENCODING *XmlGetUtf16InternalEncoding(void);
int FASTCALL XmlUtf8Encode(int charNumber, char *buf);
int FASTCALL XmlUtf16Encode(int charNumber, unsigned short *buf);
int XmlSizeOfUnknownEncoding(void);


typedef int (XMLCALL *CONVERTER) (void *userData, const char *p);

ENCODING *
XmlInitUnknownEncoding(void *mem,
                       int *table,
                       CONVERTER convert,
                       void *userData);

int XmlParseXmlDeclNS(int isGeneralTextEntity,
                      const ENCODING *enc,
                      const char *ptr,
                      const char *end,
                      const char **badPtr,
                      const char **versionPtr,
                      const char **versionEndPtr,
                      const char **encodingNamePtr,
                      const ENCODING **namedEncodingPtr,
                      int *standalonePtr);

int XmlInitEncodingNS(INIT_ENCODING *, const ENCODING **, const char *name);
const ENCODING *XmlGetUtf8InternalEncodingNS(void);
const ENCODING *XmlGetUtf16InternalEncodingNS(void);
ENCODING *
XmlInitUnknownEncodingNS(void *mem,
                         int *table,
                         CONVERTER convert,
                         void *userData);
#ifdef __cplusplus
}
#endif

#endif /* not XmlTok_INCLUDED */

// ---- xmlrole.h ----
/* Copyright (c) 1998, 1999 Thai Open Source Software Center Ltd
   See the file COPYING for copying permission.
*/

#ifndef XmlRole_INCLUDED
#define XmlRole_INCLUDED 1

#ifdef __VMS
/*      0        1         2         3      0        1         2         3
        1234567890123456789012345678901     1234567890123456789012345678901 */
#define XmlPrologStateInitExternalEntity    XmlPrologStateInitExternalEnt
#endif


#ifdef __cplusplus
extern "C" {
#endif

enum {
  XML_ROLE_ERROR = -1,
  XML_ROLE_NONE = 0,
  XML_ROLE_XML_DECL,
  XML_ROLE_INSTANCE_START,
  XML_ROLE_DOCTYPE_NONE,
  XML_ROLE_DOCTYPE_NAME,
  XML_ROLE_DOCTYPE_SYSTEM_ID,
  XML_ROLE_DOCTYPE_PUBLIC_ID,
  XML_ROLE_DOCTYPE_INTERNAL_SUBSET,
  XML_ROLE_DOCTYPE_CLOSE,
  XML_ROLE_GENERAL_ENTITY_NAME,
  XML_ROLE_PARAM_ENTITY_NAME,
  XML_ROLE_ENTITY_NONE,
  XML_ROLE_ENTITY_VALUE,
  XML_ROLE_ENTITY_SYSTEM_ID,
  XML_ROLE_ENTITY_PUBLIC_ID,
  XML_ROLE_ENTITY_COMPLETE,
  XML_ROLE_ENTITY_NOTATION_NAME,
  XML_ROLE_NOTATION_NONE,
  XML_ROLE_NOTATION_NAME,
  XML_ROLE_NOTATION_SYSTEM_ID,
  XML_ROLE_NOTATION_NO_SYSTEM_ID,
  XML_ROLE_NOTATION_PUBLIC_ID,
  XML_ROLE_ATTRIBUTE_NAME,
  XML_ROLE_ATTRIBUTE_TYPE_CDATA,
  XML_ROLE_ATTRIBUTE_TYPE_ID,
  XML_ROLE_ATTRIBUTE_TYPE_IDREF,
  XML_ROLE_ATTRIBUTE_TYPE_IDREFS,
  XML_ROLE_ATTRIBUTE_TYPE_ENTITY,
  XML_ROLE_ATTRIBUTE_TYPE_ENTITIES,
  XML_ROLE_ATTRIBUTE_TYPE_NMTOKEN,
  XML_ROLE_ATTRIBUTE_TYPE_NMTOKENS,
  XML_ROLE_ATTRIBUTE_ENUM_VALUE,
  XML_ROLE_ATTRIBUTE_NOTATION_VALUE,
  XML_ROLE_ATTLIST_NONE,
  XML_ROLE_ATTLIST_ELEMENT_NAME,
  XML_ROLE_IMPLIED_ATTRIBUTE_VALUE,
  XML_ROLE_REQUIRED_ATTRIBUTE_VALUE,
  XML_ROLE_DEFAULT_ATTRIBUTE_VALUE,
  XML_ROLE_FIXED_ATTRIBUTE_VALUE,
  XML_ROLE_ELEMENT_NONE,
  XML_ROLE_ELEMENT_NAME,
  XML_ROLE_CONTENT_ANY,
  XML_ROLE_CONTENT_EMPTY,
  XML_ROLE_CONTENT_PCDATA,
  XML_ROLE_GROUP_OPEN,
  XML_ROLE_GROUP_CLOSE,
  XML_ROLE_GROUP_CLOSE_REP,
  XML_ROLE_GROUP_CLOSE_OPT,
  XML_ROLE_GROUP_CLOSE_PLUS,
  XML_ROLE_GROUP_CHOICE,
  XML_ROLE_GROUP_SEQUENCE,
  XML_ROLE_CONTENT_ELEMENT,
  XML_ROLE_CONTENT_ELEMENT_REP,
  XML_ROLE_CONTENT_ELEMENT_OPT,
  XML_ROLE_CONTENT_ELEMENT_PLUS,
  XML_ROLE_PI,
  XML_ROLE_COMMENT,
#ifdef XML_DTD
  XML_ROLE_TEXT_DECL,
  XML_ROLE_IGNORE_SECT,
  XML_ROLE_INNER_PARAM_ENTITY_REF,
#endif /* XML_DTD */
  XML_ROLE_PARAM_ENTITY_REF
};

typedef struct prolog_state {
  int (PTRCALL *handler) (struct prolog_state *state,
                          int tok,
                          const char *ptr,
                          const char *end,
                          const ENCODING *enc);
  unsigned level;
  int role_none;
#ifdef XML_DTD
  unsigned includeLevel;
  int documentEntity;
  int inEntityValue;
#endif /* XML_DTD */
} PROLOG_STATE;

void XmlPrologStateInit(PROLOG_STATE *);
#ifdef XML_DTD
void XmlPrologStateInitExternalEntity(PROLOG_STATE *);
#endif /* XML_DTD */

#define XmlTokenRole(state, tok, ptr, end, enc) \
 (((state)->handler)(state, tok, ptr, end, enc))

#ifdef __cplusplus
}
#endif

#endif /* not XmlRole_INCLUDED */

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
               const char *s, const char *next);
enum XML_Error
initializeEncoding(XML_Parser parser);
enum XML_Error
doProlog(XML_Parser parser, const ENCODING *enc, const char *s, 
         const char *end, int tok, const char *next, const char **nextPtr, 
         XML_Bool haveMore);
enum XML_Error
processInternalEntity(XML_Parser parser, ENTITY *entity, 
                      XML_Bool betweenDecl);
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
                const char *end, const char **nextPtr, XML_Bool haveMore);
#endif /* XML_DTD */

enum XML_Error
storeAtts(XML_Parser parser, const ENCODING *, const char *s,
          TAG_NAME *tagNamePtr, BINDING **bindingsPtr);
enum XML_Error
addBinding(XML_Parser parser, PREFIX *prefix, const ATTRIBUTE_ID *attId,
           const XML_Char *uri, BINDING **bindingsPtr);
int
defineAttribute(ELEMENT_TYPE *type, ATTRIBUTE_ID *, XML_Bool isCdata, 
                XML_Bool isId, const XML_Char *dfltValue, XML_Parser parser);
enum XML_Error
storeAttributeValue(XML_Parser parser, const ENCODING *, XML_Bool isCdata,
                    const char *, const char *, STRING_POOL *);
enum XML_Error
appendAttributeValue(XML_Parser parser, const ENCODING *, XML_Bool isCdata,
                     const char *, const char *, STRING_POOL *);
ATTRIBUTE_ID *
getAttributeId(XML_Parser parser, const ENCODING *enc, const char *start,
               const char *end);
int
setElementTypePrefix(XML_Parser parser, ELEMENT_TYPE *);
enum XML_Error
storeEntityValue(XML_Parser parser, const ENCODING *enc, const char *start,
                 const char *end);
int
reportProcessingInstruction(XML_Parser parser, const ENCODING *enc,
                            const char *start, const char *end);
int
reportComment(XML_Parser parser, const ENCODING *enc, const char *start,
              const char *end);
void
reportDefault(XML_Parser parser, const ENCODING *enc, const char *start,
              const char *end);

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
lookup(HASH_TABLE *table, KEY name, size_t createSize);
void FASTCALL
hashTableInit(HASH_TABLE *, const XML_Memory_Handling_Suite *ms);
void FASTCALL hashTableClear(HASH_TABLE *);
void FASTCALL hashTableDestroy(HASH_TABLE *);
void FASTCALL
hashTableIterInit(HASH_TABLE_ITER *, const HASH_TABLE *);
NAMED * FASTCALL hashTableIterNext(HASH_TABLE_ITER *);

void FASTCALL
poolInit(STRING_POOL *, const XML_Memory_Handling_Suite *ms);
void FASTCALL poolClear(STRING_POOL *);
void FASTCALL poolDestroy(STRING_POOL *);
XML_Char *
poolAppend(STRING_POOL *pool, const ENCODING *enc,
           const char *ptr, const char *end);
XML_Char *
poolStoreString(STRING_POOL *pool, const ENCODING *enc,
                const char *ptr, const char *end);
XML_Bool FASTCALL poolGrow(STRING_POOL *pool);
const XML_Char * FASTCALL
poolCopyString(STRING_POOL *pool, const XML_Char *s);
const XML_Char *
poolCopyStringN(STRING_POOL *pool, const XML_Char *s, int n);
const XML_Char * FASTCALL
poolAppendString(STRING_POOL *pool, const XML_Char *s);

int FASTCALL nextScaffoldPart(XML_Parser parser);
XML_Content * build_model(XML_Parser parser);
ELEMENT_TYPE *
getElementType(XML_Parser parser, const ENCODING *enc,
               const char *ptr, const char *end);

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