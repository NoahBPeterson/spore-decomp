// src/game/SPEngine/SPStringManager.cpp -- migrated from slice(s) s006b6920, s006b5770, s004553b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPStringManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"
#include <string.h>
#include <intrin.h>
#include <ctype.h>

// ---- items of slice s006b5770 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Factory {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual void f7();
    virtual void f8();
    virtual void f9();
    virtual void f10();
    virtual void f11();
};
}
namespace SP {
class cStringTableResourceFactory : public Factory { public:
    virtual int GetSupportedTypes(uint32_t* pTypes, int count);
};
}
// ---- items of slice s006b5770 end

// ---- items of slice s006b6920 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_ZoneObject_new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0x00926020
typedef unsigned short wchar16;
void* __cdecl operator new(unsigned int n, const char* name, int a, int b, const char* file, int line);   // 0x00f473a0
void* __cdecl operator new(unsigned int n, const char* name, int a, int b, int c, int d);   // 0x00f473a0
#define EASTL_ALLOC(n) ::operator new((n), "App", 0, 0, \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
namespace SP {
struct cString_s006b_6920 { bool Load(int a, int b, int c); };   // 0x006b54b0
}
namespace SP {
class cStringDetokenizer { public:
    cStringDetokenizer();                     // 0x006b6490
    virtual ~cStringDetokenizer();
};
}
namespace SP {
struct Pair8 { uint32_t a, b; };
}
namespace SP {
struct RefObj {
    virtual void AddRef();
    virtual void Release();
    int mnRefCount;
    RefObj() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
};
}
namespace SP {
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
}
namespace SP {
template <> void SPVector<Pair8>::erase(Pair8* first, Pair8* last);   // 0x00530c80 (out of line)
}
namespace SP {
Pair8* __cdecl UninitCopy8(Pair8* first, Pair8* last, Pair8* dest);   // 0x004554f0
}
namespace SP {
struct IdOffset { uint32_t id; uint32_t offset; };
}
namespace SP {
IdOffset* __cdecl LowerBoundId(IdOffset* first, IdOffset* last, const uint32_t* key, uint8_t sorted);   // 0x00d01260
}
namespace SP {
struct IdMap : SPVector<IdOffset> {
    uint32_t pad[2];
    uint8_t mbSorted;
    uint32_t& operator[](const uint32_t& key);   // 0x00564a10
};
}
namespace SP {
extern const wchar16 gEmptyString[];   // 0x01409be8
}
namespace SP {
struct ResourceKey { uint32_t instance, type, group; };
}
namespace SP {
struct ResourceObjectST : RefObj {
    ResourceKey mKey;               // +0x08
    uint32_t mPad14;
    ResourceObjectST() { mKey.instance = 0; mKey.type = 0; mKey.group = 0; mPad14 = 0; }
};
}
namespace SP {
struct StringTable : ResourceObjectST {
    SPVector<uint16_t> mChars;      // +0x18
    uint32_t mPad24[2];
    IdMap mMap;                     // +0x2c (begin,end,cap) ... flag at +0x40
    uint32_t mPad44[0];

    StringTable() {
        mChars.mpBegin = 0; mChars.mpEnd = 0; mChars.mpCapacity = 0;
        mMap.mpBegin = 0; mMap.mpEnd = 0; mMap.mpCapacity = 0;
    }
    virtual void AddRef();
    virtual void Release();
    const wchar16* GetString(uint32_t id);
};
}
namespace SP {
struct IStreamSize { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                     virtual void s4(); virtual void s5(); virtual void s6(); virtual uint32_t GetSize(); };
}
namespace SP {
struct IKeyStream  { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                     virtual void s4(); virtual void s5(); virtual IStreamSize* GetStream(); };
}
namespace SP {
struct IResKeySrc  { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
                     virtual ResourceKey* GetKey(); };
}
namespace SP {
struct IResMan {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16();
    virtual void RegisterFactory(int on, void* factory, int zero);   // +0x44
};
}
namespace SP {
IResMan* __cdecl GetResourceManager();   // 0x0067dcd0
}
namespace SP {
struct FactoryBase {
    virtual void s0();
    virtual void AddRef();
    virtual void Release();
    int mnRefCount;
    FactoryBase() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
};
}
namespace SP {
struct cStringTableResourceFactory_s006b_6920 : FactoryBase {
    // slots 3..8 padding, 9 = ReadResource (see 6b6bf0)
    virtual void f3(); virtual void f4(); virtual void f5(); virtual void f6(); virtual void f7(); virtual void f8();
    virtual bool ReadResource(IKeyStream* pIn, StringTable* pTable, uint32_t arg3, uint32_t type);
    uint32_t m_bytes_to_read;       // +0x08
    uint32_t m_pos;                 // +0x0c
    uint32_t m_bytes_read;          // +0x10
    char* mp_read_buffer;           // +0x14
    IStreamSize* mp_read_stream;    // +0x18

    cStringTableResourceFactory_s006b_6920() {}
    static void* operator new(unsigned int n, const char* name, int a, int b, int c, int d) {
        return EA_ZoneObject_new(n, name, a, b, c, d);
    }
    char Read();                    // 0x006b6620
    bool Create(IResKeySrc* pSrc, StringTable** ppOut, uint32_t arg3, uint32_t type);   // 0x006b6bf0
};
}
namespace SP {
struct InsertTag {};
}
namespace SP {
struct StringSetNode { cString_s006b_6920* value; StringSetNode* next; };
}
namespace SP {
struct StringSet {
    uint32_t mAlloc;                // +0x00
    StringSetNode** mpBucketArray;  // +0x04
    uint32_t mnBucketCount;         // +0x08
    uint32_t mnElementCount;        // +0x0c
    float mfMaxLoadFactor;          // +0x10
    float mfGrowthFactor;           // +0x14
    uint32_t mnNextResize;          // +0x18
    uint32_t mPad;                  // +0x1c

    int erase(cString_s006b_6920** key);
    void insert(char* out, cString_s006b_6920** key, InsertTag tag);
    void DoFreeNodes(StringSetNode** buckets, uint32_t nBuckets);   // 0x006b6570
    ~StringSet() {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            delete[] (char*)mpBucketArray;
    }
};
}
namespace SP {
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
}
namespace SP {
class cStringManager { public:
    virtual ~cStringManager();               // vtable slot 0
    virtual bool AddString(cString_s006b_6920* p);      // vtable slot 1
    virtual bool RemoveString(cString_s006b_6920* p);   // vtable slot 2 (see 6b5240)

    StringSet mStringList;                                   // +0x04
    AutoRefCount<cStringTableResourceFactory_s006b_6920> mpFactory;     // +0x24
    cStringDetokenizer* mpDetokenizer;                       // +0x28

    cStringManager();
    bool LoadAll();
};
}
namespace EA {
namespace Text {
int __cdecl GetCharacterAsUTF16(wchar16* dst, uint32_t dstCap, const char* src, int srcLen);   // 0x0093cf60
}
}
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s006b6920 end

// @ 0x004554f0
void* DoFreeNodes(void* first, void* last, void* dest)
{
    char* d = (char*)dest;
    for (char* f = (char*)first; f != (char*)last; f += 8, d += 8) {
        if (dest != 0) {
            *(int*)(d + 0) = *(int*)(f + 0);
            *(int*)(d + 4) = *(int*)(f + 4);
        }
    }
    for (char* f = (char*)first; f != (char*)last; f += 8) {
    }
    return d;
}

// @ 0x006b6540
int SP::cStringTableResourceFactory::GetSupportedTypes(uint32_t* pTypes, int count)
{
    if (pTypes == 0)
        return 1;
    if (count != 0) {
        *pTypes = 0x2fac0b6;
        return 1;
    }
    return 0;
}

// @ 0x006b65d0
void FUN_006b65d0()
{}

// @ 0x006b6620
void FUN_006b6620()
{}

// @ 0x006b6740
void FUN_006b6740()
{}

// @ 0x006b67b0
void FUN_006b67b0()
{}

// @ 0x006b68a0
void FUN_006b68a0()
{}

// @ 0x006b6920
SP::cStringManager::~cStringManager()
{
    if (GetResourceManager())
        GetResourceManager()->RegisterFactory(0, mpFactory.mp, 0);
    mpFactory = 0;
    delete mpDetokenizer;
    // members (AutoRefCount, StringSet) are destroyed by the compiler-generated epilogue
}

// @ 0x006b69e0
bool SP::cStringManager::RemoveString(SP::cString_s006b_6920* p)
{
    mStringList.erase(&p);
    return true;
}

// @ 0x006b6a00
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

// @ 0x006b6a70
namespace SP {
template <> void SPVector<Pair8>::reserve(uint32_t n)
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
}  // namespace SP

// @ 0x006b6bf0
bool SP::cStringTableResourceFactory_s006b_6920::Create(IResKeySrc* pSrc, StringTable** ppOut, uint32_t arg3, uint32_t type)
{
    bool ok = false;
    AutoRefCount<StringTable> ref;
    StringTable* pTable = 0;
    if (type == 0x2fac0b6) {
        ref = new ("UI/SP::cString", 0, 0, 0, 0) StringTable();
        pTable = ref.mp;
        if (ReadResource((IKeyStream*)pSrc, pTable, arg3, 0x2fac0b6)) {
            *ppOut = pTable;
            pTable->AddRef();
            const ResourceKey* pKey = pSrc->GetKey();
            StringTable* pOut = *ppOut;
            pOut->mKey.instance = pKey->instance;
            pOut->mKey.type = pKey->type;
            pOut->mKey.group = pKey->group;
            ok = true;
        }
    }
    return ok;
}

// @ 0x006b6e50
bool SP::cStringManager::AddString(SP::cString_s006b_6920* p)
{
    char result[12];
    mStringList.insert(result, &p, InsertTag());
    return true;
}

// @ 0x006b7320
namespace SP {
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
}  // namespace SP

// @ 0x006b7430
bool SP::cStringTableResourceFactory_s006b_6920::ReadResource(IKeyStream* pIn, StringTable* pTable, uint32_t arg3, uint32_t type)
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
