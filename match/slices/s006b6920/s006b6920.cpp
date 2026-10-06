// slice s006b6920: SP::cStringManager and its neighbours (string table loader + EASTL vector instances).
// Flags: /O2 /MD /Gy /EHsc /GS- /TP
#include "types.h"
#include <string.h>
#include <intrin.h>
#include <ctype.h>

typedef unsigned short wchar16;

// EA operator new (size, name, flags, align?, file, line): 6-arg cdecl allocator hook used by EASTL.
void* __cdecl operator new(unsigned int n, const char* name, int a, int b, const char* file, int line);
void* __cdecl operator new(unsigned int n, const char* name, int a, int b, int c, int d);
extern "C" void* __cdecl EA_ZoneObject_new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0x00926020

#define EASTL_ALLOC(n) ::operator new((n), "App", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)

namespace SP {

struct cString { bool Load(int a, int b, int c); };   // 0x006b54b0
struct cStringDetokenizer {
    cStringDetokenizer();                     // 0x006b6490
    virtual ~cStringDetokenizer();
};

struct Pair8 { uint32_t a, b; };

// Intrusive-refcounted base (vptr, count at +4 zeroed with xchg).
struct RefObj {
    virtual void AddRef();
    virtual void Release();
    int mnRefCount;
    RefObj() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
};

// EASTL vector with SP's allocator (a header word precedes each block).
template <typename T>
struct SPVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;

    static void Free(T* p) {
        if (p && ((int*)p)[-1])
            delete[] (char*)p;
    }
    void reserve(uint32_t n);
    void insert(T* pos, const T& val);
    void insert(T* pos, uint32_t n, const T& val);
    void resize(uint32_t n);
    void erase(T* first, T* last) {
        T* const pEnd = mpEnd;
        memcpy(first, last, (char*)pEnd - (char*)last);
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }
};

template <> void SPVector<Pair8>::erase(Pair8* first, Pair8* last);   // 0x00530c80 (out of line)

Pair8* __cdecl UninitCopy8(Pair8* first, Pair8* last, Pair8* dest);   // 0x004554f0

// ---- reserve ----
// @ 0x006b6a70
template <>
void SPVector<Pair8>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        Pair8* pNew = n ? (Pair8*)EASTL_ALLOC(n * 8) : 0;
        UninitCopy8(mpBegin, mpEnd, pNew);
        if (mpBegin)
            delete[] (char*)mpBegin;
        uint32_t sz = mpEnd - mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + sz;
        mpCapacity = pNew + n;
    }
}

// @ 0x006b6af0
template <>
void SPVector<uint16_t>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        uint16_t* pNew = n ? (uint16_t*)EASTL_ALLOC(n * 2) : 0;
        memcpy(pNew, mpBegin, (char*)mpEnd - (char*)mpBegin);
        Free(mpBegin);
        uint32_t sz = mpEnd - mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + sz;
        mpCapacity = pNew + n;
    }
}

// @ 0x006b6b70
template <>
void SPVector<uint8_t>::reserve(uint32_t n)
{
    if (n > (uint32_t)(mpCapacity - mpBegin)) {
        uint8_t* pNew = n ? (uint8_t*)EASTL_ALLOC(n) : 0;
        memcpy(pNew, mpBegin, mpEnd - mpBegin);
        Free(mpBegin);
        uint32_t sz = mpEnd - mpBegin;
        mpBegin = pNew;
        mpEnd = pNew + sz;
        mpCapacity = pNew + n;
    }
}

// ---- insert(pos, val) (single element) ----
// @ 0x006b6e80
template <>
void SPVector<uint8_t>::insert(uint8_t* pos, const uint8_t& val)
{
    if (mpEnd != mpCapacity) {
        const uint8_t* pv = &val;
        if (pv >= pos && pv < mpEnd)
            ++pv;
        if (mpEnd)
            *mpEnd = mpEnd[-1];
        uint8_t* pLast = mpEnd - 1;
        memmove(pos + (mpEnd - pLast), pos, pLast - pos);
        *pos = *pv;
        ++mpEnd;
    } else {
        uint32_t nPrev = mpEnd - mpBegin;
        uint32_t nNew = nPrev ? nPrev * 2 : 1;
        uint8_t* pNew = nNew ? (uint8_t*)EASTL_ALLOC(nNew) : 0;
        uint32_t nBefore = pos - mpBegin;
        uint8_t* p = (uint8_t*)memcpy(pNew, mpBegin, nBefore) + nBefore;
        if (p)
            *p = val;
        uint32_t nAfter = mpEnd - pos;
        uint8_t* pEndNew = (uint8_t*)memcpy(p + 1, pos, nAfter) + nAfter;
        Free(mpBegin);
        mpBegin = pNew;
        mpEnd = pEndNew;
        mpCapacity = pNew + nNew;
    }
}

// ---- insert(pos, n, val) ----
// @ 0x006b6f80
template <>
void SPVector<uint16_t>::insert(uint16_t* pos, uint32_t n, const uint16_t& val)
{
    if ((uint32_t)(mpCapacity - mpEnd) >= n) {
        if (n > 0) {
            const uint16_t temp = val;
            uint16_t* const pEndOld = mpEnd;
            const uint32_t nElementsAfter = pEndOld - pos;
            if (n < nElementsAfter) {
                uint16_t* pMoved = pEndOld - n;
                memcpy(mpEnd, pMoved, (char*)pEndOld - (char*)pMoved);
                mpEnd += n;
                memmove(pEndOld - (pMoved - pos), pos, (char*)pMoved - (char*)pos);
                for (uint16_t* p = pos; p != pos + n; ++p)
                    *p = temp;
            } else {
                uint32_t nExtra = n - nElementsAfter;
                uint16_t* p;
                if (nExtra) {
                    for (p = pEndOld; p != pEndOld + nExtra; ++p)
                        *p = temp;
                }
                mpEnd += nExtra;
                memcpy(mpEnd, pos, (char*)pEndOld - (char*)pos);
                mpEnd += nElementsAfter;
                for (p = pos; p != pEndOld; ++p)
                    *p = temp;
            }
        }
    } else {
        uint32_t nPrev = mpEnd - mpBegin;
        uint32_t nGrow = nPrev ? nPrev * 2 : 1;
        uint32_t nNew = nPrev + n;
        if (nNew < nGrow)
            nNew = nGrow;
        uint16_t* pNew = nNew ? (uint16_t*)EASTL_ALLOC(nNew * 2) : 0;
        uint32_t nBefore = (char*)pos - (char*)mpBegin;
        uint16_t* p = (uint16_t*)((char*)memcpy(pNew, mpBegin, nBefore) + (((int)nBefore >> 1) * 2));
        uint16_t v = val;
        for (uint32_t i = 0; i < n; ++i)
            p[i] = v;
        uint32_t nAfter = (char*)mpEnd - (char*)pos;
        uint16_t* pEndNew = (uint16_t*)((char*)memcpy(p + n, pos, nAfter) + (((int)nAfter >> 1) * 2));
        Free(mpBegin);
        mpBegin = pNew;
        mpEnd = pEndNew;
        mpCapacity = pNew + nNew;
    }
}

// @ 0x006b7180
template <>
void SPVector<uint8_t>::insert(uint8_t* pos, uint32_t n, const uint8_t& val)
{
    if ((uint32_t)(mpCapacity - mpEnd) >= n) {
        if (n > 0) {
            const uint8_t temp = val;
            uint8_t* const pEndOld = mpEnd;
            const uint32_t nElementsAfter = pEndOld - pos;
            if (n < nElementsAfter) {
                uint8_t* pMoved = pEndOld - n;
                memcpy(mpEnd, pMoved, pEndOld - pMoved);
                mpEnd += n;
                memmove(pEndOld - (pMoved - pos), pos, pMoved - pos);
                memset(pos, temp, n);
            } else {
                uint32_t nExtra = n - nElementsAfter;
                if (nExtra)
                    memset(pEndOld, temp, nExtra);
                mpEnd += nExtra;
                memcpy(mpEnd, pos, pEndOld - pos);
                mpEnd += nElementsAfter;
                memset(pos, temp, pEndOld - pos);
            }
        }
    } else {
        uint32_t nPrev = mpEnd - mpBegin;
        uint32_t nGrow = nPrev ? nPrev * 2 : 1;
        uint32_t nNew = nPrev + n;
        if (nNew < nGrow)
            nNew = nGrow;
        uint8_t* pNew = nNew ? (uint8_t*)EASTL_ALLOC(nNew) : 0;
        uint32_t nBefore = pos - mpBegin;
        uint8_t* p = (uint8_t*)memcpy(pNew, mpBegin, nBefore) + nBefore;
        uint8_t v = val;
        if (n)
            memset(p, v, n);
        uint32_t nAfter = mpEnd - pos;
        uint8_t* pEndNew = (uint8_t*)memcpy(p + n, pos, nAfter) + nAfter;
        Free(mpBegin);
        mpBegin = pNew;
        mpEnd = pEndNew;
        mpCapacity = pNew + nNew;
    }
}

// ---- resize ----
// @ 0x006b7380
template <>
void SPVector<uint16_t>::resize(uint32_t n)
{
    uint16_t* pEnd = mpEnd;
    uint32_t nSize = pEnd - mpBegin;
    if (n > nSize) {
        uint16_t zero = 0;
        insert(pEnd, n - nSize, zero);
    } else {
        erase(mpBegin + n, pEnd);
    }
}

// @ 0x006b73e0
template <>
void SPVector<uint8_t>::resize(uint32_t n)
{
    uint8_t* pEnd = mpEnd;
    uint8_t* pBegin = mpBegin;
    if (n > (uint32_t)(pEnd - pBegin)) {
        uint8_t zero = 0;
        insert(pEnd, n - (pEnd - pBegin), zero);
    } else {
        erase(pBegin + n, pEnd);
    }
}

// ---- helpers for the string table ----
struct IdOffset { uint32_t id; uint32_t offset; };

IdOffset* __cdecl LowerBoundId(IdOffset* first, IdOffset* last, const uint32_t* key, uint8_t sorted);   // 0x00d01260

struct IdMap : SPVector<IdOffset> {
    uint32_t pad[2];
    uint8_t mbSorted;
    uint32_t& operator[](const uint32_t& key);   // 0x00564a10
};

extern const wchar16 gEmptyString[];   // 0x01409be8

// The string table resource object created by the factory (size 0x44).
struct StringTable : RefObj {
    uint32_t mKey[3];               // +0x08 ResourceKey
    uint32_t mPad14;
    SPVector<uint16_t> mChars;      // +0x18
    uint32_t mPad24[2];
    IdMap mMap;                     // +0x2c (begin,end,cap) ... flag at +0x40
    uint32_t mPad44[0];

    StringTable() {
        mKey[0] = mKey[1] = mKey[2] = 0;
        mPad14 = 0;
        mChars.mpBegin = mChars.mpEnd = mChars.mpCapacity = 0;
        mMap.mpBegin = mMap.mpEnd = mMap.mpCapacity = 0;
        AddRef();
    }
    virtual void AddRef();
    virtual void Release();
    const wchar16* GetString(uint32_t id);
};

// @ 0x006b7320
const wchar16* SP::StringTable::GetString(uint32_t id)
{
    IdOffset* const pEnd = mMap.mpEnd;
    IdOffset* it = LowerBoundId(mMap.mpBegin, pEnd, &id, mMap.mbSorted);
    if (it == pEnd || id < it->id)
        it = pEnd;
    else if (it == it + 1)
        it = pEnd;
    if (it != pEnd && it->offset < (uint32_t)(mChars.mpEnd - mChars.mpBegin))
        return mChars.mpBegin + it->offset;
    return gEmptyString;
}

struct IStreamSize { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                     virtual void s4(); virtual void s5(); virtual void s6(); virtual uint32_t GetSize(); };
struct IKeyStream  { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                     virtual void s4(); virtual void s5(); virtual IStreamSize* GetStream(); };
struct IResKeySrc  { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                     virtual uint32_t* GetKey(); };
struct IResMan {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16();
    virtual void RegisterFactory(int on, void* factory, int zero);   // +0x44
};
IResMan* __cdecl GetResourceManager();   // 0x0067dcd0

struct FactoryBase {
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
    int mnRefCount;
    FactoryBase() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
};

struct cStringTableResourceFactory : FactoryBase {
    // slots 3..8 padding, 9 = ReadResource (see 6b6bf0)
    virtual void f3(); virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7(); virtual void f8();
    virtual bool ReadResource(IKeyStream* pIn, StringTable* pTable, uint32_t arg3, uint32_t type);
    uint32_t m_bytes_to_read;       // +0x08
    uint32_t m_pos;                 // +0x0c
    uint32_t m_bytes_read;          // +0x10
    char* mp_read_buffer;           // +0x14
    IStreamSize* mp_read_stream;    // +0x18

    cStringTableResourceFactory() {}
    static void* operator new(unsigned int n, const char* name, int a, int b, int c, int d) {
        return EA_ZoneObject_new(n, name, a, b, c, d);
    }
    char Read();                    // 0x006b6620
    bool Create(IResKeySrc* pSrc, StringTable** ppOut, uint32_t arg3, uint32_t type);   // 0x006b6bf0
};

// Hash-set header of the string manager (retail layout at cStringManager+0x04, size 0x20).
struct InsertTag {};
struct StringSetNode { cString* value; StringSetNode* next; };
void __cdecl FreeNodes(uint32_t first, uint32_t count);   // 0x006b6570 (hashtable DoFreeNodes)

struct StringSet {
    uint32_t mAlloc;                // +0x00
    StringSetNode** mpBucketArray;  // +0x04
    uint32_t mnBucketCount;         // +0x08
    uint32_t mnElementCount;        // +0x0c
    float mfMaxLoadFactor;          // +0x10
    float mfGrowthFactor;           // +0x14
    uint32_t mnNextResize;          // +0x18
    uint32_t mPad;                  // +0x1c

    int erase(cString** key);
    void insert(char* out, cString** key, InsertTag tag);
    void DoFreeNodes(StringSetNode** buckets, uint32_t nBuckets);   // 0x006b6570
    ~StringSet() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            delete[] (char*)mpBucketArray;
    }
};

template <class T>
struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    ~AutoRefCount() { if (mp) mp->Release(); }
    AutoRefCount& operator=(T* p) {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
};

struct cStringManager {
    virtual ~cStringManager();               // vtable slot 0
    virtual bool AddString(cString* p);      // vtable slot 1
    virtual bool RemoveString(cString* p);   // vtable slot 2 (see 6b5240)

    StringSet mStringList;                                   // +0x04
    AutoRefCount<cStringTableResourceFactory> mpFactory;     // +0x24
    cStringDetokenizer* mpDetokenizer;                       // +0x28

    cStringManager();
    bool LoadAll();
};

} // namespace SP

// @ 0x006b69e0
bool SP::cStringManager::RemoveString(SP::cString* p)
{
    mStringList.erase(&p);
    return true;
}

// @ 0x006b6e50
bool SP::cStringManager::AddString(SP::cString* p)
{
    char result[12];
    mStringList.insert(result, &p, InsertTag());
    return true;
}

// ---------------------------------------------------------------------------
// Remaining functions.
// ---------------------------------------------------------------------------

// @ 0x006b6920
SP::cStringManager::~cStringManager()
{
    if (GetResourceManager())
        GetResourceManager()->RegisterFactory(0, mpFactory.mp, 0);
    mpFactory = 0;
    delete mpDetokenizer;
    // members (AutoRefCount, StringSet) are destroyed by the compiler-generated epilogue
}

// @ 0x006b6a00  load every string in the set (result sticks at false after the first failure)
bool SP::cStringManager::LoadAll()
{
    bool ok = true;
    StringSetNode** pBucket = mStringList.mpBucketArray;
    StringSetNode* pNode = *pBucket;
    if (!pNode) {
        ++pBucket;
        while (!*pBucket)
            ++pBucket;
        pNode = *pBucket;
    }
    StringSetNode* const pEnd = mStringList.mpBucketArray[mStringList.mnBucketCount];
    while (pNode != pEnd) {
        if (ok && pNode->value->Load(-1, -1, 0))
            ok = true;
        else
            ok = false;
        pNode = pNode->next;
        while (!pNode)
            pNode = *++pBucket;
    }
    return ok;
}

extern const float kOne;     // 0x01485720
extern const float kTwo;     // 0x01470f1c
extern SP::StringSetNode* gEmptyBucketArray[];   // 0x0154df28

// @ 0x006b6d10
SP::cStringManager::cStringManager()
{
    mStringList.mfMaxLoadFactor = 1.0f;
    mStringList.mfGrowthFactor = 2.0f;
    mStringList.mnBucketCount = 1;
    mStringList.mpBucketArray = gEmptyBucketArray;
    mStringList.mnElementCount = 0;
    mStringList.mnNextResize = 0;
    mpFactory.mp = 0;
    mpFactory = new ("UI/SP::cString", 0, 0, 0, 0) cStringTableResourceFactory();
    GetResourceManager()->RegisterFactory(1, mpFactory.mp, 0);
    mpDetokenizer = new ("App/cStringDetokenizer", 0, 0, 0, 0) cStringDetokenizer();
}

// @ 0x006b6bf0
bool SP::cStringTableResourceFactory::Create(IResKeySrc* pSrc, StringTable** ppOut, uint32_t arg3, uint32_t type)
{
    bool ok = false;
    AutoRefCount<StringTable> ref;
    StringTable* pTable = 0;
    if (type == 0x2fac0b6) {
        pTable = new ("UI/SP::cString", 0, 0, 0, 0) StringTable();
        ref.mp = pTable;
        if (ReadResource((IKeyStream*)pSrc, pTable, arg3, 0x2fac0b6)) {
            *ppOut = pTable;
            pTable->AddRef();
            uint32_t* pKey = pSrc->GetKey();
            (*ppOut)->mKey[0] = pKey[0];
            (*ppOut)->mKey[1] = pKey[1];
            (*ppOut)->mKey[2] = pKey[2];
            ok = true;
        }
    }
    return ok;
}

namespace EA { namespace Text {
int __cdecl GetCharacterAsUTF16(wchar16* dst, uint32_t dstCap, const char* src, int srcLen);   // 0x0093cf60
}}

// @ 0x006b7430
bool SP::cStringTableResourceFactory::ReadResource(IKeyStream* pIn, StringTable* pTable, uint32_t arg3, uint32_t type)
{
    char buffer[512];
    bool ok = false;
    if (type == 0x2fac0b6) {
    IStreamSize* pSize = pIn->GetStream();
    SPVector<uint16_t>& chars = pTable->mChars;
    chars.reserve(pSize->GetSize() >> 1);
    chars.clear();
    SPVector<Pair8>& idMap = *(SPVector<Pair8>*)&pTable->mMap;
    idMap.reserve(0x10);
    idMap.clear();

    mp_read_stream = pIn->GetStream();
    m_bytes_to_read = mp_read_stream->GetSize();
    mp_read_buffer = buffer;
    m_pos = 0x200;
    m_bytes_read = 0x200;
    if (!mp_read_stream)
        goto end;

    {
    char ch = Read();
    if (ch == (char)0xef) {
        char b1 = Read();
        char b2 = Read();
        if (b1 != (char)0xbb || b2 != (char)0xbf)
            goto fail;
        ch = Read();
    }
    {
        struct TextVec : SPVector<uint8_t> { ~TextVec() { Free(mpBegin); } } text;
        text.mpBegin = text.mpEnd = text.mpCapacity = 0;
        text.reserve(20000);
        uint32_t curId = 0xffffffff;
        uint32_t lastId = 0xffffffff;
        int state = 2;
        while (ch != 0) {
            switch (state) {
            case 0:
                if (ch == '0') {
                    char c = Read();
                    if (c != 'x' && c != 'X')
                        goto fail;
                    curId = 0;
                    ch = Read();
                    for (int i = 0; i < 8; ++i) {
                        if (!isxdigit((unsigned char)ch))
                            break;
                        curId <<= 4;
                        if ((unsigned char)(ch - '0') <= 9)
                            curId += ch - '0';
                        else if ((unsigned char)(ch - 'a') <= 5)
                            curId += ch - 'a' + 10;
                        else if ((unsigned char)(ch - 'A') <= 5)
                            curId += ch - 'A' + 10;
                        ch = Read();
                    }
                } else {
                    curId = lastId + 1;
                }
                state = 2;
                break;
            case 1: {
                uint32_t off = chars.mpEnd - chars.mpBegin;
                text.clear();
                while (ch != 0 && ch != '\n' && ch != '\r') {
                    if (text.mpEnd < text.mpCapacity) {
                        if (text.mpEnd)
                            *text.mpEnd = (uint8_t)ch;
                        ++text.mpEnd;
                    } else {
                        text.insert(text.mpEnd, (uint8_t&)ch);
                    }
                    ch = Read();
                }
                uint8_t nul = 0;
                if (text.mpEnd < text.mpCapacity) {
                    if (text.mpEnd)
                        *text.mpEnd = 0;
                    ++text.mpEnd;
                } else {
                    text.insert(text.mpEnd, nul);
                }
                uint32_t len = text.mpEnd - text.mpBegin;
                chars.resize(off + len);
                int n = EA::Text::GetCharacterAsUTF16(chars.mpBegin + off,
                                                     (chars.mpEnd - chars.mpBegin) - off,
                                                     (const char*)text.mpBegin, len - 1);
                chars.mpBegin[off + n] = 0;
                chars.erase(chars.mpBegin + off + n + 1, chars.mpEnd);
                pTable->mMap.operator[](curId) = off;
                lastId = curId;
                curId = 0xffffffff;
                state = 2;
                break;
            }
            case 2:
                while (ch != 0 && ((ch >= 9 && ch <= 13) || ch == ' '))
                    ch = Read();
                if (ch == 0)
                    goto done;
                if (ch == '#') {
                    while (ch != '\r' && ch != '\n') {
                        ch = Read();
                        if (ch == 0)
                            goto done;
                    }
                } else {
                    state = (curId != 0xffffffff);
                }
                break;
            }
        }
    done:
        ok = true;
        goto end;
    }
    }
fail:
    chars.clear();
    idMap.clear();
    }
end:
    return ok;
}
