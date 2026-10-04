// Slice s00613240: vector<pair<uint32,Variant>> / vector<pair<uint64,intrusive ptr>> insertion helpers,
// the property bag (Editor property list resource) constructor / destructor / typed getters /
// deserializer, its resource factory, and a small message-handler class with a vector_set<uint32>
// and a vector_map<uint64, intrusive ptr>.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "types.h"

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
inline void* operator new(unsigned int, void* p) { return p; }

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380
extern "C" void* __cdecl memmove(void*, const void*, size_t);

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace EA {
struct Variant {
    char mData[16];
    uint16_t mFlags;
    uint16_t mTypeId;
    Variant& operator=(const Variant& x);  // 0x00542b80
    void Destruct(int);                    // 0x0093db80
    Variant() : mFlags(0), mTypeId(0) {}
    Variant(const Variant& x) : mFlags(0), mTypeId(0) { *this = x; }
    ~Variant() {
        if (mFlags & 4) Destruct(0);
    }
};
namespace IO {
struct IStream;
bool ReadInt32(IStream* pStream, int32_t* pData, uint32_t count, int endian);    // 0x0093a780
bool ReadUint64(IStream* pStream, uint64_t* pData, uint32_t count, int endian);  // 0x0093a800
}  // namespace IO
namespace Messaging {
void RemoveHandler(void* a, void* b, void* c, void* d, void* e);  // 0x00571db0
}
}  // namespace EA

namespace eastl {
template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;
    pair() : second() {}
    pair(const T1& a, const T2& b) : first(a), second(b) {}
    pair(const pair& x) : first(x.first), second(x.second) {}
    pair& operator=(const pair& x) {
        first = x.first;
        second = x.second;
        return *this;
    }
};

struct fixed_vector_allocator {
    const char* mpName;
    void* mpPoolBegin;
    void deallocate(void* p) {
        if (p != mpPoolBegin) EASTL_allocator_deallocate(p);
    }
    void* allocate(size_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
};
struct MapCompare {};  // empty comparator (1 byte member)
}  // namespace eastl

typedef eastl::pair<uint32_t, EA::Variant> PropPair;

struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};
struct Elem16 {  // pair<uint64, intrusive_ptr<IRefObj>> (16 bytes)
    uint32_t a;
    uint32_t b;
    IRefObj* p;
    uint32_t pad;
    Elem16(const uint64_t& key, IRefObj* ptr) : a(((const uint32_t*)&key)[0]), b(((const uint32_t*)&key)[1]), p(ptr) {}
    Elem16(const Elem16& x) : a(x.a), b(x.b), p(x.p) {
        if (p) p->AddRef();
    }
    Elem16& operator=(const Elem16& x) {
        a = x.a;
        b = x.b;
        IRefObj* const pNew = x.p;
        if (pNew != p) {
            IRefObj* const pTemp = p;
            if (pNew) pNew->AddRef();
            p = pNew;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    ~Elem16() {
        IRefObj* const pObj = p;
        if (pObj) pObj->Release();
    }
};

void* operator new(size_t, const char*, int, int, const char*, int);
void operator delete(void* p);

// External helpers (other slices).
PropPair* __cdecl UninitializedCopy(const PropPair*, const PropPair*, PropPair*);   // 0x00612d50
PropPair* __cdecl DestructRange(PropPair*, PropPair*, PropPair*);                   // 0x00612a90
PropPair* __cdecl CopyPairs(const PropPair*, const PropPair*, PropPair*);           // 0x00612b20
PropPair* __cdecl CopyBackward(PropPair*, PropPair*, PropPair*);                    // 0x00612b60
const PropPair* __cdecl LowerBound(const PropPair*, const PropPair*, const uint32_t&, eastl::MapCompare);  // 0x00612db0
Elem16* __cdecl UninitializedCopyElem16(const Elem16*, const Elem16*, Elem16*);     // 0x00612ad0
Elem16* __cdecl DestructElem16Range(Elem16*, Elem16*, Elem16*);                     // 0x007cddf0
Elem16* __cdecl CopyBackwardElem16(Elem16*, Elem16*, Elem16*);                      // 0x007cde80
Elem16* __cdecl CopyElem16(Elem16*, Elem16*, Elem16*);                              // 0x007c7e10
const Elem16* __cdecl LowerBoundKey64(const Elem16*, const Elem16*, const uint64_t*, eastl::MapCompare);  // 0x007c8160
const uint32_t* __cdecl LowerBoundSet(const uint32_t*, const uint32_t*, const uint32_t*, eastl::MapCompare);  // 0x00555a20

inline PropPair* RelocatePairs(PropPair* first, PropPair* last, PropPair* dest) {
    PropPair* const pEnd = UninitializedCopy(first, last, dest);
    DestructRange(first, last, dest);
    return pEnd;
}
inline Elem16* RelocateElem16(Elem16* first, Elem16* last, Elem16* dest) {
    Elem16* const pEnd = UninitializedCopyElem16(first, last, dest);
    DestructElem16Range(first, last, dest);
    return pEnd;
}

// ---------------------------------------------------------------------------------------------
namespace eastl {
struct PropVector {
    PropPair* mpBegin;
    PropPair* mpEnd;
    PropPair* mpCapacity;
    fixed_vector_allocator mAllocator;

    PropPair* DoAllocate(size_t n) { return n ? (PropPair*)mAllocator.allocate(n * sizeof(PropPair)) : 0; }
    void DoInsertValue(PropPair* position, const PropPair& value);   // 0x00613240
    PropPair* insert(PropPair* position, const PropPair& value);     // 0x00613920
    void DestructRangeV(PropPair* first, PropPair* last);            // 0x00685a30
    void reserve(size_t n);                                          // 0x00613020 (other slice)
    PropPair* erase(PropPair* first, PropPair* last) {
        PropPair* const pNewEnd = CopyPairs(last, mpEnd, first);
        DestructRangeV(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
};
}  // namespace eastl

// @ 0x00613240
void eastl::PropVector::DoInsertValue(PropPair* position, const PropPair& value) {
    if (mpEnd != mpCapacity) {
        const PropPair* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
        ::new (mpEnd) PropPair(*(mpEnd - 1));
        CopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        PropPair* const pNewData = DoAllocate(nNewSize);
        PropPair* pNewEnd = RelocatePairs(mpBegin, position, pNewData);
        ::new (pNewEnd) PropPair(value);
        ++pNewEnd;
        pNewEnd = RelocatePairs(position, mpEnd, pNewEnd);
        if (mpBegin && mpBegin != mAllocator.mpPoolBegin) EASTL_allocator_deallocate(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00613920
PropPair* eastl::PropVector::insert(PropPair* position, const PropPair& value) {
    const int n = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        ::new (mpEnd++) PropPair(value);
    } else {
        DoInsertValue(position, value);
    }
    return mpBegin + n;
}

// ---------------------------------------------------------------------------------------------
// Elem16 vectors (vector<pair<uint64, intrusive_ptr>> with fixed storage allocator).
struct Elem16Vector {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    eastl::fixed_vector_allocator mAllocator;
    eastl::MapCompare mCompare;  // +0x14

    Elem16Vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~Elem16Vector();
    Elem16* DoAllocate(size_t n) { return n ? (Elem16*)mAllocator.allocate(n * sizeof(Elem16)) : 0; }
    void DoInsertValue(Elem16* position, const Elem16& value);       // 0x006133b0
    Elem16* insert(Elem16* position, const Elem16& value);           // 0x006139a0
    Elem16* insertHint(Elem16* hint, const Elem16& value);           // 0x00613bf0
    size_t erase(const uint64_t& key);                                // 0x00613b10
    Elem16* erase(Elem16* first, Elem16* last) {
        Elem16* const pNewEnd = CopyElem16(last, mpEnd, first);
        for (Elem16* p = pNewEnd; p < mpEnd; ++p) p->~Elem16();
        mpEnd -= (last - first);
        return first;
    }
    IRefObj** FindOrInsert(const uint64_t& key);                     // 0x00613dd0
};

// @ 0x006133b0
void Elem16Vector::DoInsertValue(Elem16* position, const Elem16& value) {
    if (mpEnd != mpCapacity) {
        const Elem16* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd)) ++pValue;
        ::new (mpEnd) Elem16(*(mpEnd - 1));
        CopyBackwardElem16(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
        const size_t nNewSize = (nPrevSize > 0) ? (2 * nPrevSize) : 1;
        Elem16* const pNewData = DoAllocate(nNewSize);
        Elem16* pNewEnd = RelocateElem16(mpBegin, position, pNewData);
        ::new (pNewEnd) Elem16(value);
        ++pNewEnd;
        pNewEnd = RelocateElem16(position, mpEnd, pNewEnd);
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
        mpEnd = pNewEnd;
        mpBegin = pNewData;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x006139a0
Elem16* Elem16Vector::insert(Elem16* position, const Elem16& value) {
    const int n = (int)(position - mpBegin);
    if (position == mpEnd && mpEnd != mpCapacity) {
        ::new (mpEnd++) Elem16(value);
    } else {
        DoInsertValue(position, value);
    }
    return mpBegin + n;
}

// @ 0x00613b10
size_t Elem16Vector::erase(const uint64_t& key) {
    Elem16* const pEnd = mpEnd;
    Elem16* position = (Elem16*)LowerBoundKey64(mpBegin, pEnd, &key, mCompare);
    if (position == pEnd || key < *(const uint64_t*)position) position = pEnd;
    else if (position == position + 1) position = pEnd;
    if (position != pEnd) {
        if (position + 1 < pEnd) CopyElem16(position + 1, pEnd, position);
        --mpEnd;
        mpEnd->~Elem16();
        return 1;
    }
    return 0;
}

// @ 0x00613bf0
Elem16* Elem16Vector::insertHint(Elem16* hint, const Elem16& value) {
    Elem16* const pEnd = mpEnd;
    const uint64_t& key = *(const uint64_t*)&value;
    const Elem16* it;
    if (hint != pEnd && key < *(const uint64_t*)hint)
        it = LowerBoundKey64(mpBegin, hint, &key, mCompare);
    else
        it = LowerBoundKey64(hint, pEnd, &key, mCompare);
    if (it == pEnd || key < *(const uint64_t*)it) it = insert((Elem16*)it, value);
    return (Elem16*)it;
}

// @ 0x00613dd0
IRefObj** Elem16Vector::FindOrInsert(const uint64_t& key) {
    Elem16* const pEnd = mpEnd;
    const Elem16* it = LowerBoundKey64(mpBegin, pEnd, &key, mCompare);
    if (it == pEnd || key < *(const uint64_t*)it) {
        Elem16 value(key, 0);
        it = insertHint((Elem16*)it, value);
    }
    return &((Elem16*)it)->p;
}

// ---------------------------------------------------------------------------------------------
// Property bag: vptr, refcount, fixed-storage vector_map<uint32, Variant> at +0x20.
struct RefCountBase {
    virtual int AddRef();
    virtual int Release();
    virtual ~RefCountBase() {}
    volatile long mRefCount;
    RefCountBase() { _InterlockedExchange(&mRefCount, 0); }
};
struct PropertyBagBase : public RefCountBase {
    uint32_t pad8, padC, pad10, pad14;
    uint64_t mId;
    PropertyBagBase(uint64_t id) : pad8(0), padC(0), pad10(0), pad14(0), mId(id) {}
};

extern const float kDefaultFloat;  // 0x015d1168
extern const int kDefaultInt;      // 0x015d1160

struct PropMap {
    eastl::PropVector mVec;      // +0x00
    char pad14[4];
    char mBuffer[0xf0];          // +0x18
    eastl::MapCompare mCompare;  // +0x108

    PropMap() {
        mVec.mpBegin = mVec.mpEnd = (PropPair*)(mVec.mAllocator.mpPoolBegin = mBuffer);
        mVec.mpCapacity = (PropPair*)((char*)mVec.mpBegin + 0xf0);
    }
    EA::Variant& operator[](const uint32_t& key);             // 0x00613d20
    PropPair* insertHint(PropPair* hint, const PropPair& value);  // 0x00613b90
    ~PropMap() {
        mVec.DestructRangeV(mVec.mpBegin, mVec.mpEnd);
        if (mVec.mpBegin && mVec.mpBegin != mVec.mAllocator.mpPoolBegin) EASTL_allocator_deallocate(mVec.mpBegin);
    }
    const PropPair* find(const uint32_t& key) const {
        const PropPair* const itEnd = mVec.mpEnd;
        const PropPair* it = LowerBound(mVec.mpBegin, itEnd, key, mCompare);
        if (it != itEnd && !(key < it->first)) return it;
        return itEnd;
    }
};

struct cPropertyBag : public PropertyBagBase {
    PropMap mMap;  // +0x20
    char pad12c[4];
    cPropertyBag();  // 0x00613530
    bool GetFloat(uint32_t key, float* pOut);     // 0x006135d0
    bool GetInt32(uint32_t key, int32_t* pOut);   // 0x00613660
};

// @ 0x00613530
cPropertyBag::cPropertyBag() : PropertyBagBase((uint64_t)-1) {}
// (the implicit virtual destructor provides the scalar deleting destructor at 0x00613580)
void DeletePropertyBag(cPropertyBag* p) { delete p; }

// @ 0x00613d20
EA::Variant& PropMap::operator[](const uint32_t& key) {
    const PropPair* const itEnd = mVec.mpEnd;
    const PropPair* it = LowerBound(mVec.mpBegin, itEnd, key, mCompare);
    if (it == itEnd || key < it->first) {
        it = insertHint((PropPair*)it, PropPair(key, EA::Variant()));
    }
    return ((PropPair*)it)->second;
}

// @ 0x006135d0
bool cPropertyBag::GetFloat(uint32_t key, float* pOut) {
    const PropPair* const itEnd = mMap.mVec.mpEnd;
    const PropPair* it = LowerBound(mMap.mVec.mpBegin, itEnd, key, mMap.mCompare);
    if (it == itEnd || key < it->first) it = itEnd;
    else if (it == it + 1) it = itEnd;
    if (it != itEnd) {
        if (pOut) {
            const EA::Variant& v = it->second;
            if (v.mTypeId == 0xd || v.mTypeId == 0x10) {
                if (v.mFlags & 0x30)
                    *pOut = **(float**)v.mData;
                else
                    *pOut = *(const float*)(v.mTypeId ? (const void*)v.mData : 0);
            } else {
                *pOut = kDefaultFloat;
            }
        }
        return true;
    }
    return false;
}

// @ 0x00613660
bool cPropertyBag::GetInt32(uint32_t key, int32_t* pOut) {
    const PropPair* const itEnd = mMap.mVec.mpEnd;
    const PropPair* it = LowerBound(mMap.mVec.mpBegin, itEnd, key, mMap.mCompare);
    if (it == itEnd || key < it->first) it = itEnd;
    else if (it == it + 1) it = itEnd;
    if (it != itEnd) {
        if (pOut) {
            const EA::Variant& v = it->second;
            if (v.mTypeId == 9 || v.mTypeId == 0x10) {
                if (v.mFlags & 0x30)
                    *pOut = **(int**)v.mData;
                else
                    *pOut = *(const int*)(v.mTypeId ? (const void*)v.mData : 0);
            } else {
                *pOut = kDefaultInt;
            }
        }
        return true;
    }
    return false;
}

// @ 0x006136f0: resource factory CreateResource for property bags.
struct IStreamLike;
struct cPropertyListFactory {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool ReadResource(IStreamLike* pStream, cPropertyBag* pBag, int unused, uint32_t typeId);  // +0x24
    bool CreateResource(IStreamLike* pStream, cPropertyBag** ppOut, int unused, uint32_t typeId);
};
bool cPropertyListFactory::CreateResource(IStreamLike* pStream, cPropertyBag** ppOut, int unused, uint32_t typeId) {
    cPropertyBag* pBag = 0;
    if (typeId == 0xfd60f0c1) {
        pBag = new ("Pollinator", 0, 0, 0, 0) cPropertyBag();
        if (pBag) pBag->AddRef();
        if (pStream) {
            if (ReadResource(pStream, pBag, unused, 0xfd60f0c1)) {
                *ppOut = pBag;
                return true;
            }
            if (pBag) pBag->Release();
            return false;
        }
        *ppOut = pBag;
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// Message-listener set: handler handle at +4, vector_set<uint32,5> at +0x1c (fixed), Elem16 vector at +0x88.
struct MsgHandle {
    void* a;
    void* b;
    void* c;
    void* d;
    void* e;
    MsgHandle() : a(0), b(0), c(0), d(0), e(0) {}
    ~MsgHandle() { Reset(); }
    void Reset() {
        if (a) {
            void* const pa = a;
            a = 0;
            EA::Messaging::RemoveHandler(pa, b, c, d, e);
        }
    }
};

struct FixedUIntSet {
    uint32_t* mpBegin;   // +0x1c
    uint32_t* mpEnd;     // +0x20
    uint32_t* mpCapacity;// +0x24
    const char* mpName;  // +0x28
    void* mpPoolBegin;   // +0x2c
    char pad[4];         // +0x30
    uint32_t mBuffer[20];// +0x34
    eastl::MapCompare mCompare;  // +0x84

    FixedUIntSet() {
        mpBegin = mpEnd = (uint32_t*)(mpPoolBegin = mBuffer);
        mpCapacity = mpBegin + 20;
    }
    void DoInsertValue(uint32_t* position, const uint32_t& value);  // 0x0060a600
    bool contains(uint32_t key) const {
        const uint32_t* const itEnd = mpEnd;
        const uint32_t* it = LowerBoundSet(mpBegin, itEnd, &key, mCompare);
        if (it == itEnd || key < *it) it = itEnd;
        else if (it == it + 1) it = itEnd;
        return it != itEnd;
    }
    void insert(uint32_t key) {
        uint32_t* const pEnd = mpEnd;
        const uint32_t* it = LowerBoundSet(mpBegin, pEnd, &key, mCompare);
        if (it != pEnd && !(key < *it)) return;
        if (it == pEnd && pEnd != mpCapacity) {
            *mpEnd++ = key;
        } else {
            DoInsertValue((uint32_t*)it, key);
        }
    }
    void erase(uint32_t* pFirst, uint32_t* pLast) {
        memmove(pFirst, pLast, (size_t)((char*)mpEnd - (char*)pLast));
        mpEnd -= (pLast - pFirst);
    }
    void clear() { erase(mpBegin, mpEnd); }
    ~FixedUIntSet() {
        if (mpBegin && mpBegin != mpPoolBegin) EASTL_allocator_deallocate(mpBegin);
    }
};

struct Elem16VectorD {
    Elem16* mpBegin;
    Elem16* mpEnd;
    ~Elem16VectorD();  // 0x00612d10
};
inline Elem16Vector::~Elem16Vector() { ((Elem16VectorD*)this)->~Elem16VectorD(); }

struct cMessageBase {
    virtual ~cMessageBase() {}
};
struct cEntry {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual void Method16(void* pKey);  // +0x40
};
struct cManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual bool Query(void* pKey, IRefObj** ppOut);       // +0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual void SetDefault(IRefObj* pObj, uint32_t flags, uint32_t id);  // +0x44
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual struct cEntry* Lookup(void* pKey);             // +0x58
    virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26();
    virtual void Apply(IRefObj* pObj, int flag);           // +0x6c
};
cManager* GetManager();  // 0x0067dcd0
struct IRefObj3 {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
};
extern IRefObj3* g_pDefaultObject;  // 0x015f4ccc

struct cListenerSet : public cMessageBase {
    MsgHandle mHandle;       // +4
    uint32_t mField18;
    FixedUIntSet mSet;       // +0x1c
    Elem16Vector mListeners; // +0x88

    cListenerSet();                               // 0x00613790
    void DestroyBody();                           // 0x006137e0
    void Shutdown();                              // 0x00613a10
    bool HandleMessage(char* pMsg);               // 0x00613c60
    bool contains(uint32_t key);                  // 0x00613860
    void insertKey(uint32_t key);                 // 0x00613ab0
};

// @ 0x00613790
cListenerSet::cListenerSet() : mField18(0) {}

// @ 0x006137e0 (destructor body; the base-class vptr store is explicit here)
void cListenerSet::DestroyBody() {
    mListeners.~Elem16Vector();
    mSet.~FixedUIntSet();
    mHandle.~MsgHandle();
    this->cMessageBase::~cMessageBase();
}

// @ 0x00613860
bool cListenerSet::contains(uint32_t key) {
    const uint32_t* const itEnd = mSet.mpEnd;
    const uint32_t* it = LowerBoundSet(mSet.mpBegin, itEnd, &key, mSet.mCompare);
    if (it == itEnd || key < *it) it = itEnd;
    else if (it == it + 1) it = itEnd;
    return it != itEnd;
}

// @ 0x00613ab0
void cListenerSet::insertKey(uint32_t key) {
    uint32_t* const pEnd = mSet.mpEnd;
    const uint32_t* it = LowerBoundSet(mSet.mpBegin, pEnd, &key, mSet.mCompare);
    if (it != pEnd && !(key < *it)) return;
    if (it == pEnd && pEnd != mSet.mpCapacity) {
        *mSet.mpEnd++ = key;
    } else {
        mSet.DoInsertValue((uint32_t*)it, key);
    }
}

// @ 0x00613a10
void cListenerSet::Shutdown() {
    mListeners.erase(mListeners.mpBegin, mListeners.mpEnd);
    mSet.clear();
    mHandle.Reset();
    if (cManager* pMgr = GetManager()) {
        pMgr->SetDefault(0, (uint32_t)g_pDefaultObject, 0);
        if (IRefObj3* pOld = g_pDefaultObject) {
            g_pDefaultObject = 0;
            pOld->Release();
        }
    }
    mField18 = 0;
}

// @ 0x00613c60
bool cListenerSet::HandleMessage(char* pMsg) {
    uint64_t key = *(uint64_t*)(pMsg + 0x18);
    mListeners.erase(key);
    void* const pField = pMsg + 8;
    if (*(uint32_t*)pField != 0) {
        cManager* pMgr = GetManager();
        if (cEntry* pEntry = pMgr->Lookup(pField)) pEntry->Method16(pField);
        IRefObj* pObj = 0;
        cManager* pMgr2 = GetManager();
        if (pObj) {
            IRefObj* const pOld = pObj;
            pObj = 0;
            pOld->Release();
        }
        if (pMgr2->Query(pField, &pObj)) GetManager()->Apply(pObj, 0);
        if (pObj) pObj->Release();
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00613e50: property bag deserializer.
struct cStreamReader {
    EA::IO::IStream* mpStream;
    int mEndian;
    bool mbOk;
    char pad[7];
    cStreamReader(EA::IO::IStream* pStream, bool bBigEndian);  // 0x006b4f60
    void Accumulate(bool bResult);                              // 0x006b4f90
    void ReadVariant(EA::Variant* v);                           // 0x006b4fd0
    ~cStreamReader();                                           // 0x006b5000
};
struct cPropertyReader {
    bool Read(EA::IO::IStream* pStream, cPropertyBag* pBag);
};
bool cPropertyReader::Read(EA::IO::IStream* pStream, cPropertyBag* pBag) {
    cStreamReader r(pStream, true);
    int32_t version = 0;
    if (r.mbOk) r.Accumulate(EA::IO::ReadInt32(r.mpStream, &version, 1, r.mEndian));
    if (!r.mbOk || (uint32_t)version < 3) return false;
    if (r.mbOk) r.Accumulate(EA::IO::ReadUint64(r.mpStream, &pBag->mId, 1, r.mEndian));
    int32_t count = 0;
    if (r.mbOk) r.Accumulate(EA::IO::ReadInt32(r.mpStream, &count, 1, r.mEndian));
    if (!r.mbOk) return false;
    pBag->mMap.mVec.reserve((size_t)count);
    for (uint32_t i = 0; i < (uint32_t)count; ++i) {
        uint32_t key = 0;
        EA::Variant v;
        *(int*)v.mData = 0;
        v.mTypeId = 9;
        v.mFlags = 0;
        if (r.mbOk) r.Accumulate(EA::IO::ReadInt32(r.mpStream, (int32_t*)&key, 1, r.mEndian));
        r.ReadVariant(&v);
        if (!r.mbOk) goto fail;
        pBag->mMap[key] = v;
    }
    if (r.mbOk) return true;
fail:
    pBag->mMap.mVec.erase(pBag->mMap.mVec.mpBegin, pBag->mMap.mVec.mpEnd);
    return false;
}

// ---------------------------------------------------------------------------------------------
// @ 0x006138b0: SP::cPollinator lookup by resource key (resolves the server id through the asset directory).
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};
struct cAssetMetadata {
    virtual int AddRef();
    virtual int Release();
    const uint32_t* GetServerId();  // 0x005507a0
};
bool GetAssetMetadata(const ResourceKey& key, cAssetMetadata** ppMetadata);  // 0x00552450
struct cPollinatorLookup {
    bool Lookup(uint64_t key, IRefObj** ppOut, bool bTouch);  // 0x00612f50
    bool LookupByKey(const ResourceKey* pKey, IRefObj** ppOut, bool bTouch);
};
struct MetaRef {
    cAssetMetadata* mpObject;
    MetaRef() : mpObject(0) {}
    ~MetaRef() {
        if (mpObject) mpObject->Release();
    }
};
bool cPollinatorLookup::LookupByKey(const ResourceKey* pKey, IRefObj** ppOut, bool bTouch) {
    MetaRef metadata;
    if (GetAssetMetadata(*pKey, &metadata.mpObject)) {
        const uint32_t* pId = metadata.mpObject->GetServerId();
        return Lookup(*(const uint64_t*)pId, ppOut, bTouch);
    }
    return false;
}
