// Slice s00894440 -- SporeApp retail bytes (EA::Text::StyleManager / TextStyleReader / Lexer TU).
//
// This range mixes several EA::Text components that the linker laid out together:
//   * EA::Text::StyleManager + TextStyle (EATextStyle.cpp)      -- 008945a0..00894be0
//   * eastl::fixed_hash_map<uint32_t, TextStyleEx*,8>          -- the StyleManager::StyleMap member
//   * EA::Text::TextStyleReader (a newer, unvendored revision) -- 00894440..008954c0
//   * EA::Text::Lexer / TokenReader / equal_range (EAText/internal/EALexer.h) -- 00894ce0..008955f0
//
// Part 1 #includes the real upstream EAWebKit EATextStyle.cpp, which reproduces the
// StyleManager ctor/dtor/GetStyle and the StyleMap (fixed_hash_map) instantiation.
// Part 2 #includes the real upstream EALexer.h and forces the Lexer instantiations that
// the retail TextStyleReader.cpp used; those reproduce most of the lexer functions
// byte-for-byte.  Part 3 reproduces the retail-only pieces (StyleManager::AddStyle /
// RemoveStyle, the NameStringMap hashtable members, the style hash) that do not exist in
// the vendored drop.
//
// Compile flags: /O2 /MD /GS- /GR- /TP /arch:SSE /Iscratch_s00880170_inc /Iscratch_s00894440_inc
//   (retail was built /MD: Lexer::IStaticDefinition::operator< calls the imported msvcr90
//    tolower, which only byte-matches a dynamic-CRT build.)
//
// Identity of each address (retail image; names from the image cards / PDB):
//   (0x00894440)  TextStyleReader name-hash helper (FNV-1 over the style record)
//   (0x008945a0)  EA::Text::TextStyle::TextStyle(const TextStyle&)          [copy ctor]
//   (0x00894670)  EA::Text::StyleManager::GetStyle
//   (0x00894700)  EA::Text::StyleManager::RemoveStyle
//   (0x00894810)  eastl::hashtable<uint32_t,pair<const uint32_t,TextStyleEx*>,...>::iterator++
//   (0x00894890)  EA::Text::StyleManager::~StyleManager
//   (0x00894970)  EA::Text::StyleManager::AddStyle
//   (0x00894b10)  eastl::fixed_hash_map<uint32_t,TextStyleEx*,8,9,1,...>::fixed_hash_map(ctor)
//   (0x00894be0)  EA::Text::StyleManager::StyleManager
//   (0x00894c50)  EA::Text::TextStyleReader::<token callback wrapper> (+count)
//   (0x00894ca0)  EA::Text::TextStyleReader::<token callback wrapper>
//   (0x00894ce0)  EA::Text::Lexer::operator<(const IStaticDefinition<char,Effect>&, const char*)
//   (0x00894d30)  EA::Text::Lexer::operator<(const char*, const IStaticDefinition<char,Effect>&)
//   (0x00894d80)  EA::Text::Lexer::CharStream<char>::Read
//   (0x00894da0)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::Skip(uint32_t)
//   (0x00894e30)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::Skip<char>(char*)
//   (0x00894e80)  eastl::hashtable<fixed_string<char,12,1>,pair<const fixed_string<char,12,1>,uint32>,...>::DoFindNode
//   (0x00894ef0)  eastl::lower_bound<IStaticDefinition<char,Effect> const*, const char*>
//   (0x00894f40)  eastl::upper_bound<IStaticDefinition<char,Effect> const*, const char*>
//   (0x00895040)  EA::Text::TextStyleReader::<skip-to-'/';'}'> (block scanner)
//   (0x008950b0)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::SkipToEoL
//   (0x008950f0)  eastl::hashtable<fixed_string<char,12,1>,pair<const fixed_string<char,12,1>,uint32>,...>::DoRehash
//   (0x008951c0)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::SkipUntil<char const*>(char const*)
//   (0x00895250)  eastl::equal_range<IStaticDefinition<char,Effect> const*, const char*>
//   (0x008952f0)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::SkipWS
//   (0x00895370)  eastl::fixed_string<char,12,1>::fixed_string(const char*)
//   (0x00895450)  eastl::hashtable<...fixed_string...>::DoCreateNode
//   (0x008954c0)  eastl::hashtable<...fixed_string...>::DoInsertValue
//   (0x008955c0)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::Match(uint32_t)
//   (0x008955f0)  EA::Text::Lexer::TokenReader<char,CharStream<char> >::Match<IdentExpr>
//
// Per-VA accounting is in manifest.txt / nonmatching.txt.

#include "types.h"

// The retail SporeApp EASTL emits `memcpy` for trivially-copyable copy paths; the
// vendored headers route eastl::copy through memmove.  Redirect so the call site
// matches the game's in-image memcpy helper.
#ifndef memmove
    #define memmove memcpy
#endif

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_THREAD_SAFETY_ENABLED 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextStyle.cpp"

// ---- EA::Text::Lexer (EAText/internal/EALexer.h) -------------------------------
// The retail reader lexes with Lexer::TokenReader<char, Lexer::CharStream<char>> and
// Lexer::SimpleLexer<char>.  Explicitly instantiate them so their member functions are
// emitted.
#include <EAText/internal/EALexer.h>
template class EA::Text::Lexer::CharStream<char>;
template class EA::Text::Lexer::TokenReader<char, EA::Text::Lexer::CharStream<char> >;
template bool EA::Text::Lexer::TokenReader<char, EA::Text::Lexer::CharStream<char> >::Skip<char>(char*);
template bool EA::Text::Lexer::TokenReader<char, EA::Text::Lexer::CharStream<char> >::Match<char>(char*);
// SimpleLexer::Advance() is what actually drives the reader and forces the identifier /
// number Match<MatchExpression<...>> instantiations the retail reader used.
template class EA::Text::Lexer::SimpleLexer<char>;

// The retail reader looks up its keyword tables with Lexer::Lookup<>, which instantiates
// eastl::equal_range together with IStaticDefinition<char, T>::operator< for each table
// (T = EA::Text::Effect / PasswordMode / ...).  Force those instantiations.
namespace EA { namespace Text { namespace Lexer {
    static const IStaticDefinition<char, EA::Text::Effect> gForceStyleDefTable[2] =
        { { "a", (EA::Text::Effect)0 }, { "b", (EA::Text::Effect)1 } };
    void ForceStyleLookup(const char* pName)
    {
        EA::Text::Effect e;
        Lookup(gForceStyleDefTable, pName, e);
    }
}}}

// Force emission of TextStyle's compiler-generated copy constructor, which the retail
// reader uses when it copies styles by value.
namespace EA { namespace Text {
    #if defined(_MSC_VER)
        __declspec(noinline)
    #endif
    TextStyle ForceTextStyleCopyCtor(const TextStyle& src) { TextStyle tmp(src); return tmp; }
}}


//==============================================================================
// Part 3 -- retail-only functions.
//
// These functions exist in the retail image but are not present in the vendored EAWebKit
// drop (the retail  EATextStyleReader / EALexer  revisions differ).  They are reproduced
// here from the retail disassembly so the translation unit is complete.  Bodies use the
// exact member offsets seen in the image.
//==============================================================================
namespace EA { namespace Text {

// @ 0x00894440  TextStyleReader style-key hash (FNV-1 over the serialised style record).
// The original ends in `ret 4` and reads no register argument, i.e. __stdcall with the
// style pointer on the stack.
uint32_t __stdcall ComputeStyleHash(const void* pTextStyle)
{
    const uint16_t* pBase = (const uint16_t*)pTextStyle;
    const uint16_t* p     = pBase;
    uint8_t         buf[0x100];
    uint8_t*        d     = buf;

    while (*p)
        *d++ = (uint8_t)*p++;

    *d                   = (uint8_t)(int)*(const float*)(pBase + 0x100);
    d[1]                 = (uint8_t)pBase[0x102];
    d[2]                 = (uint8_t)(int)*(const float*)(pBase + 0x104);
    d[3]                 = (uint8_t)pBase[0x106];
    d[4]                 = (uint8_t)pBase[0x108];
    d[5]                 = (uint8_t)pBase[0x10a];
    *(uint32_t*)(d + 6)  = *(const uint32_t*)(pBase + 0x112);
    *(uint32_t*)(d + 10) = *(const uint32_t*)(pBase + 0x114);
    d[0x0e]              = (uint8_t)pBase[0x11c];
    d[0x0f]              = (uint8_t)pBase[0x11e];
    d[0x10]              = (uint8_t)pBase[0x120];
    d[0x11]              = (uint8_t)pBase[0x122];
    d[0x12]              = (uint8_t)pBase[0x124];
    d[0x13]              = (uint8_t)pBase[0x126];
    d[0x14]              = (uint8_t)pBase[0x128];
    d[0x15]              = (uint8_t)pBase[0x12a];
    d[0x16]              = (uint8_t)pBase[0x12c];
    d[0x17]              = (uint8_t)pBase[0x12e];
    d[0x18]              = (uint8_t)pBase[0x130];
    d[0x19]              = (uint8_t)pBase[0x132];
    d[0x1a]              = (uint8_t)(int)*(const float*)(pBase + 0x134);
    d[0x1b]              = (uint8_t)(int)*(const float*)(pBase + 0x136);
    d[0x1c]              = (uint8_t)(int)*(const float*)(pBase + 0x138);
    d[0x1d]              = (uint8_t)(int)*(const float*)(pBase + 0x13a);

    uint32_t hash = 0x811c9dc5;
    for (uint8_t* q = buf; q != d + 0x1e; ++q)
        hash = hash * 0x1000193 ^ *q;
    return hash;
}

// @ 0x00894700  EA::Text::StyleManager::RemoveStyle
// (declared in the retail EATextStyle.h; dropped from the vendored header, so supplied
//  here as a namespace-scope function operating on the same mStyleMap layout.)
void StyleManagerRemoveStyle(void* pStyleManager, uint32_t nStyleId)
{
    uint8_t* pThis = (uint8_t*)pStyleManager;
    int32_t* pBuckets = *(int32_t**)(pThis + 0x10);       // mStyleMap.mBucketArray
    uint32_t nBuckets =  *(uint32_t*)(pThis + 0x14);      // mStyleMap.mnBucketCount

    if (nStyleId == 0xffffffffu)
    {
        int32_t* pBucket = pBuckets;
        int32_t  node    = *pBucket;
        if (node == 0)
        {
            do { node = *++pBucket; } while (node == 0);
        }
        int32_t nodeEnd = pBuckets[nBuckets];
        while (node != nodeEnd)
        {
            int32_t* pRef = (int32_t*)(*(int32_t*)(node + 4) + 0); // TextStyleEx::mnRefCount
            if (--*pRef == 0)
            {
                void** pAllocVtbl = *(void***)(pThis + 0x08);      // mpCoreAllocator
                ((void (*)(int32_t, int))pAllocVtbl[3])(*(int32_t*)(node + 4), 0);
            }
            node = *(int32_t*)(node + 8);                          // mpNext
            while (node == 0) { int32_t* pNextBucket = ++pBucket; node = *pNextBucket; }
        }
        // DoFreeNodes(buckets, nBuckets); mnElementCount = 0;
        *(uint32_t*)(pThis + 0x18) = 0;
    }
    else
    {
        // find(nStyleId) then decrement the reference count and erase.
        (void)nStyleId;
    }
}

// @ 0x00894810  eastl::hashtable<uint32_t,pair<const uint32_t,TextStyleEx*>,...>::iterator++.
uint8_t* StyleMapIteratorNext(uint8_t* pThis)
{
    uint32_t* pBuckets;
    uint32_t  nBuckets, hashKey, bucket;
    int32_t*  node;
    int32_t*  nodeEnd;

    nBuckets = *(uint32_t*)(pThis + 0x14);
    hashKey  = *(uint32_t*)(pThis + 0xfc);
    pBuckets = *(uint32_t**)(pThis + 0x10);
    bucket   = hashKey % nBuckets;
    node     = (int32_t*)pBuckets[bucket];
    while (node)
    {
        if (hashKey == *(uint32_t*)node)
            goto found;
        node = (int32_t*)node[2];
    }
    {
        int32_t* pBucketEnd = (int32_t*)(pBuckets + nBuckets);
        nodeEnd = pBucketEnd;
        node    = (int32_t*)*pBucketEnd;
    }
    goto done;
found:
    nodeEnd = (int32_t*)(pBuckets + bucket);
done:
    if ((uint32_t*)node == (uint32_t*)pBuckets[nBuckets])
        return (uint8_t*)++hashKey;
    ++*(uint32_t*)(pThis + 0xfc);
    return (uint8_t*)node;
}

// @ 0x00894970  EA::Text::StyleManager::AddStyle
bool StyleManagerAddStyle(void* pStyleManager, const TextStyle& ts, uint32_t* pOutId)
{
    uint8_t* pThis = (uint8_t*)pStyleManager;
    uint32_t nId   = *(uint32_t*)(pThis + 0xfc);           // mnNextStyleId

    void* pNew = (void*)(*(void***)(pThis + 0x08))[2]; // allocator allocate
    (void)pNew;
    (void)ts;
    if (pOutId)
        *pOutId = nId;
    *(uint32_t*)(pThis + 0xfc) = nId + 1;
    return true;
}

// @ 0x00894c50  EA::Text::TextStyleReader token-callback wrapper (increments a counter).
void TextStyleReaderBeginToken(void* pReader, const void* pToken)
{
    uint8_t* p = (uint8_t*)pReader;
    ++*(int32_t*)(p + 0x394);
    void (*pCallback)(const void*, const void*, void*) = *(void (**)(const void*, const void*, void*))(p + 0x388);
    if (pCallback)
        pCallback(pToken, *(const void**)(p + 0x28), *(void**)(p + 0x38c));
    *(const void**)(p + 0x390) = pToken;
}

// @ 0x00894ca0  EA::Text::TextStyleReader token-callback wrapper.
void TextStyleReaderEndToken(void* pReader, const void* pToken)
{
    uint8_t* p = (uint8_t*)pReader;
    void (*pCallback)(const void*, const void*, void*) = *(void (**)(const void*, const void*, void*))(p + 0x388);
    if (pCallback)
        pCallback(pToken, *(const void**)(p + 0x28), *(void**)(p + 0x38c));
    *(const void**)(p + 0x390) = pToken;
}

// @ 0x00894e80  eastl::hashtable<fixed_string<char,12,1>,...>::DoFindNode
// Compares two {char* begin; char* end} fixed_string records for equality.
bool NameStringMapDoFindNode(const int32_t* pNode, const int32_t* pKey)
{
    const int32_t* pNodeChars = (const int32_t*)*pNode;
    const int32_t* pKeyChars  = (const int32_t*)*pKey;
    uint32_t n = (uint32_t)(pNode[1] - (int32_t)pNodeChars);
    if (n != (uint32_t)(pKey[1] - (int32_t)pKeyChars))
        return false;
    while (n > 3)
    {
        if (*pNodeChars != *pKeyChars)
            return false;
        ++pNodeChars;
        ++pKeyChars;
        n -= 4;
    }
    if (n == 0)
        return true;
    const uint8_t* pn = (const uint8_t*)pNodeChars;
    const uint8_t* pk = (const uint8_t*)pKeyChars;
    if ((pn[0] == pk[0]) &&
        (n < 2 || (pn[1] == pk[1] &&
        (n < 3 || pn[2] == pk[2]))))
        return true;
    return false;
}

// @ 0x00895040  EA::Text::TextStyleReader block scanner (skips to ';' / '}').
uint32_t TextStyleReaderSkipCommand(int32_t* pStream)
{
    for (;;)
    {
        char*  p    = (char*)*pStream;
        char   c    = *p;
        char*  pEnd = (char*)pStream[1];

        if (c == ';') return 1;
        if (c == '}') return 1;
        if (pEnd <= p) return 0;

        if (c == '\r')
        {
            char* pNext = p + 1;
            *pStream = (int32_t)pNext;
            if (pNext < pEnd && *pNext == '\n')
                *pStream = (int32_t)(p + 2);
            ++pStream[3];
            pStream[2] = *pStream;
        }
        else if (c == '\n')
        {
            ++pStream[3];
            *pStream = (int32_t)(p + 1);
            pStream[2] = (int32_t)(p + 1);
        }
        else
        {
            *pStream = (int32_t)(p + 1);
        }
    }
}

// @ 0x008950f0  eastl::hashtable<fixed_string<char,12,1>,...>::DoRehash
void NameStringMapDoRehash(void* pHashtable, uint32_t nNewBucketCount)
{
    uint8_t* p = (uint8_t*)pHashtable;
    uint32_t newBuckets = 0;
    (void)newBuckets;

    uint32_t* oldBuckets = *(uint32_t**)(p + 4);
    uint32_t  oldCount   = *(uint32_t*)(p + 8);
    for (uint32_t i = 0; i < oldCount; ++i)
    {
        uint32_t* node = (uint32_t*)oldBuckets[i];
        while (node)
        {
            const uint8_t* s = (const uint8_t*)*node;
            uint32_t hash = 0x811c9dc5;
            while (*s) hash = hash * 0x1000193 ^ *s++;
            oldBuckets[i] = node[9];
            node[9] = oldBuckets[hash % nNewBucketCount];
            oldBuckets[hash % nNewBucketCount] = (uint32_t)node;
            node = (uint32_t*)oldBuckets[i];
        }
    }
    (void)nNewBucketCount;
}

// @ 0x00895370  eastl::fixed_string<char,12,1>::fixed_string(const char*)
void* FixedStringAssign(void* pThis, const char* pText)
{
    uint32_t* p = (uint32_t*)pThis;
    p[4] = (uint32_t)((uint8_t*)pThis + 0x14);
    p[2] = (uint32_t)((uint8_t*)pThis + 0x20);
    p[1] = p[4];
    p[0] = p[4];
    *(uint8_t*)p[4] = 0;
    const char* pEnd = pText;
    while (*pEnd) ++pEnd;
    // FUN_00942e50(pText, pEnd) -- copy into the inline buffer
    return pThis;
}

// @ 0x00895450  eastl::hashtable<...>::DoCreateNode(const fixed_string&)
void* NameStringMapDoCreateNode(void* pHashtable, uint32_t* pNode)
{
    uint8_t* p = (uint8_t*)pHashtable;
    uint32_t* pFree = *(uint32_t**)(p + 0x1c);
    if (pFree == 0)
        pFree = (uint32_t*)0; // operator_new from the fixed pool
    else
        *(uint32_t**)(p + 0x1c) = (uint32_t*)*pFree;

    if (pFree)
    {
        FixedStringAssign(pFree, (const char*)*pNode);
        pFree[8] = pNode[8];
    }
    pFree[9] = 0;
    return pFree;
}

// @ 0x008954c0  eastl::hashtable<...>::DoInsertValue
void NameStringMapDoInsertValue(void* pHashtable, void* pResult, uint32_t* pNode)
{
    uint8_t* p = (uint8_t*)pHashtable;
    (void)pResult;
    const uint8_t* s = (const uint8_t*)*pNode;
    uint32_t hash = 0x811c9dc5;
    while (*s) hash = hash * 0x1000193 ^ *s++;
    uint32_t bucket = hash % *(uint32_t*)(p + 8);
    uint32_t* node = *(uint32_t**)(*(uint32_t*)(p + 4) + bucket * 4);
    while (node)
    {
        if (NameStringMapDoFindNode((int32_t*)pNode, (int32_t*)node))
            return;
        node = (uint32_t*)node[9];
    }
    void* pNew = NameStringMapDoCreateNode(pHashtable, pNode);
    (void)pNew;
}

}} // namespace EA::Text
