// Slice s00612270: SP::cPollinator tick (transaction scheduling), the cPollinatorCheat flood handler,
// Editor::cPropertyList helpers (serialization, find/lookup) and the EASTL vector<pair<uint32,Variant>>
// / vector<Constraint> template pieces they use.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).
#include "types.h"

extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
inline void* operator new(unsigned int, void* p) { return p; }

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);  // 0x00f473a0
void __cdecl EASTL_allocator_deallocate(void* p);                                                                                  // 0x00f47380

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
bool WriteUint32(IStream* pStream, const uint32_t* pData, uint32_t count, int endian);  // 0x0093aa70
bool WriteUint64(IStream* pStream, const uint64_t* pData, uint32_t count, int endian);  // 0x0093ab10
}  // namespace IO
}  // namespace EA

namespace eastl {
template <class T1, class T2>
struct pair {
    T1 first;
    T2 second;
    pair() : second() {}
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
}  // namespace eastl

typedef eastl::pair<uint32_t, EA::Variant> PropPair;

// ---------------------------------------------------------------------------------------------
// Intrusive-refcounted object with AddRef in slot 0 and Release in slot 1.
struct IRefObj {
    virtual int AddRef();
    virtual int Release();
};

// 16-byte element: two words and an intrusive pointer at +8 (padding word at +0xc).
struct Elem16 {
    uint32_t a;
    uint32_t b;
    IRefObj* p;
    uint32_t pad;
    Elem16(const Elem16& x) : a(x.a), b(x.b), p(x.p) {
        if (p) p->AddRef();
    }
    ~Elem16() {
        IRefObj* const pObj = p;
        if (pObj) pObj->Release();
    }
};

// ---------------------------------------------------------------------------------------------
// Helpers over ranges of PropPair (24 bytes: uint32 key + Variant).
struct GenIter {
    PropPair* mIterator;
    GenIter() {}
    GenIter(PropPair* p) : mIterator(p) {}
    GenIter(const GenIter& x) : mIterator(x.mIterator) {}
};

// @ 0x00612a90: destroys [first,last) and returns dest advanced by the same count.
__declspec(noinline) PropPair* DestructRange(PropPair* first, PropPair* last, PropPair* dest) {
    for (; first != last; ++first, ++dest) first->~PropPair();
    return dest;
}

// @ 0x00612d50: copy-constructs [first,last) into raw storage at dest, returns the end.
__declspec(noinline) PropPair* UninitializedCopy(const PropPair* first, const PropPair* last, PropPair* dest) {
    for (; first != last; ++first, ++dest) ::new (dest) PropPair(*first);
    return dest;
}

// @ 0x00612e00: same through a generic_iterator returned by hidden pointer.
struct CGenIter {
    const PropPair* mIterator;
    CGenIter() {}
    CGenIter(const PropPair* p) : mIterator(p) {}
    CGenIter(const CGenIter& x) : mIterator(x.mIterator) {}
};
GenIter UninitializedCopyIter(CGenIter first, CGenIter last, GenIter dest) {
    GenIter result(dest);
    for (; first.mIterator != last.mIterator; ++first.mIterator) {
        ::new (result.mIterator) PropPair(*first.mIterator);
        ++result.mIterator;
    }
    return result;
}

// @ 0x00612db0: eastl::lower_bound over pair<uint32,Variant> with map_value_compare<less>.
const PropPair* LowerBound(const PropPair* first, const PropPair* last, const uint32_t& value) {
    int length = (int)(last - first);
    while (length > 0) {
        const int half = length >> 1;
        const PropPair* const middle = first + half;
        if (middle->first < value) {
            first = middle;
            ++first;
            length = length - half - 1;
        } else {
            length = half;
        }
    }
    return first;
}

// @ 0x00612ad0: copy [first,last) of Elem16 into raw storage (a, b copied, p add-ref'd).
Elem16* UninitializedCopyElem16(const Elem16* first, const Elem16* last, Elem16* dest) {
    for (; first != last; ++first, ++dest) ::new (dest) Elem16(*first);
    return dest;
}

namespace eastl {
// vector<PropPair, fixed_vector_allocator>
struct PropVector {
    PropPair* mpBegin;
    PropPair* mpEnd;
    PropPair* mpCapacity;
    fixed_vector_allocator mAllocator;
    void reserve(size_t n);                                             // 0x00613020
    PropPair* DoRealloc(size_t n, const PropPair* first, int tag);        // 0x00612ea0
    void DestructRangeV(PropPair* first, PropPair* last);                 // 0x00685a30
    void assign(const PropPair* first, const PropPair* last, int tag);  // 0x00613140
};
}  // namespace eastl
PropPair* __cdecl CopyPairs(const PropPair* first, const PropPair* last, PropPair* dest);  // 0x00612b20

// @ 0x00613020
void eastl::PropVector::reserve(size_t n) {
    if (n > (size_t)(mpCapacity - mpBegin)) {
        PropPair* const pNewData = n ? (PropPair*)mAllocator.allocate(n * sizeof(PropPair)) : 0;
        PropPair* const pOldEnd = mpEnd;
        PropPair* const pOldBegin = mpBegin;
        UninitializedCopy(pOldBegin, pOldEnd, pNewData);
        DestructRange(pOldBegin, pOldEnd, pNewData);
        if (mpBegin) mAllocator.deallocate(mpBegin);
        mpEnd = pNewData + (mpEnd - mpBegin);
        mpBegin = pNewData;
        mpCapacity = pNewData + n;
    }
}

// @ 0x00613140
void eastl::PropVector::assign(const PropPair* first, const PropPair* last, int tag) {
    const size_t n = (size_t)(last - first);
    PropPair* const pBegin = mpBegin;
    if (n > (size_t)(mpCapacity - pBegin)) {
        PropPair* const pNewData = DoRealloc(n, first, tag);
        DestructRangeV(mpBegin, mpEnd);
        if (mpBegin) mAllocator.deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = mpCapacity = pNewData + n;
    } else if (n <= (size_t)(mpEnd - pBegin)) {
        PropPair* const pNewEnd = CopyPairs(first, last, pBegin);
        DestructRangeV(pNewEnd, mpEnd);
        mpEnd = pNewEnd;
    } else {
        const PropPair* pMid = first + (mpEnd - pBegin);
        CopyPairs(first, pMid, pBegin);
        mpEnd = UninitializedCopyIter(pMid, last, mpEnd).mIterator;
    }
}

// @ 0x006130e0: vector<Elem16>::erase(first, last)
struct Elem16Vector {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* erase(Elem16* first, Elem16* last);
};
Elem16* __cdecl CopyElem16(Elem16* first, Elem16* last, Elem16* dest);  // 0x007c7e10
inline void DestructElem16(Elem16* first, Elem16* last) {
    for (; first < last; ++first) first->~Elem16();
}
Elem16* Elem16Vector::erase(Elem16* first, Elem16* last) {
    Elem16* const pNewEnd = CopyElem16(last, mpEnd, first);
    DestructElem16(pNewEnd, mpEnd);
    mpEnd -= (last - first);
    return first;
}

// @ 0x00612d10: ~vector<Elem16>
struct Elem16VectorD {
    Elem16* mpBegin;
    Elem16* mpEnd;
    ~Elem16VectorD() {
        Elem16* const pEnd = mpEnd;
        for (Elem16* p = mpBegin; p < pEnd; ++p) p->~Elem16();
        if (mpBegin) EASTL_allocator_deallocate(mpBegin);
    }
};
void DestroyElem16VectorD(Elem16VectorD* v) { v->~Elem16VectorD(); }

// ---------------------------------------------------------------------------------------------
template struct eastl::pair<uint32_t, EA::Variant>;

// ---------------------------------------------------------------------------------------------
namespace SP {
namespace Pollen {
struct cAssetDirectory {
    void Flush();  // 0x0054efb0
    uint32_t GetLastRefreshTime(uint32_t key);  // 0x0054e9a0 (returns 64-bit in edx:eax)
};
}  // namespace Pollen

struct cPollinator {
    virtual void v0();
    virtual bool HandleMessage(uint32_t id, void* msg);
    char pad[0x54];
    Pollen::cAssetDirectory* mpAsssetDirectory;  // +0x58
    void FUN_006103d0(uint32_t lo, uint32_t hi);  // 0x006103d0
    void ProcessTransactionTick();                // 0x00612270
};
cPollinator* GetPollinator();  // 0x0067cb30
}  // namespace SP

struct cMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void SetHandlerPriority(void* pHandler, uint32_t id, int priority);  // +0x2c
};
cMessageServer* GetMessageServer();  // 0x0067dcc0

// @ 0x00612980: message handler subobject of the "pollen" cheat (flood test).
struct FloodHandler {
    void* mVtbl;
    int mnFlood;  // cheat + 0x14
    bool HandleMessage(uint32_t id, void* pMessage);
};

bool FloodHandler::HandleMessage(uint32_t id, void* pMessage) {
    SP::cPollinator* pPollinator = SP::GetPollinator();
    if (id == 0x269c832) {
        if (mnFlood != 0) {
            pPollinator->mpAsssetDirectory->Flush();
            pPollinator->HandleMessage(0x632d709, 0);
            --mnFlood;
            return true;
        }
        FloodHandler* const pCheat = ((uint32_t)this - 0x10) ? this : 0;
        cMessageServer* const pServer = GetMessageServer();
        pServer->SetHandlerPriority(pCheat, 0x269c832, -10000);
        pPollinator->ProcessTransactionTick();
    }
    return true;
}

// @ 0x00612a20: resource factory GetSupportedTypes for property lists.
struct cPropertyListFactory {
    virtual int GetSupportedTypes(uint32_t* pTypes, uint32_t count) const;
};
int cPropertyListFactory::GetSupportedTypes(uint32_t* pTypes, uint32_t count) const {
    if (pTypes) {
        if (count < 1) return 0;
        pTypes[0] = 0xfd60f0c1;
    }
    return 1;
}

// ---------------------------------------------------------------------------------------------
// Property list (fixed storage vector_map of key -> Variant) and its serialization.
struct cStreamWriter {
    EA::IO::IStream* mpStream;
    int mEndian;
    bool mbOk;
    char pad[7];
    cStreamWriter(EA::IO::IStream* pStream, bool bBigEndian);  // 0x006b4f60
    void Accumulate(bool bResult);                              // 0x006b4f90
    void WriteVariant(const EA::Variant* v);                    // 0x006b4fa0
    ~cStreamWriter();                                           // 0x006b5000
};

struct RefCountBase {
    virtual ~RefCountBase() {}
    volatile long mRefCount;
    RefCountBase() { _InterlockedExchange(&mRefCount, 0); }
};
struct PropertyBagBase : public RefCountBase {
    uint32_t pad8, padC, pad10, pad14;
    uint32_t mField18;
    PropertyBagBase(uint32_t a) : pad8(0), padC(0), pad10(0), pad14(0), mField18(a) {}
};
struct cPropertyBag : public PropertyBagBase {
    uint32_t mField1C;
    PropPair* mpBegin;       // +0x20
    PropPair* mpEnd;         // +0x24
    PropPair* mpCapacity;    // +0x28
    uint32_t mAllocName;     // +0x2c
    void* mpPoolBegin;       // +0x30
    char pad34[4];
    char mFixedBuffer[0xf0]; // +0x38
    cPropertyBag(uint32_t a, uint32_t b);  // 0x00612f00
    virtual ~cPropertyBag() {}
};

struct cPropertyListWriter {
    bool Write(EA::IO::IStream* pStream, const cPropertyBag* pBag);  // 0x00612ba0
    bool WriteResource(void* pObject, void* pStreamHolder, int unused, uint32_t typeId);  // 0x00612e50
};

// @ 0x00612ba0
bool cPropertyListWriter::Write(EA::IO::IStream* pStream, const cPropertyBag* pBag) {
    cStreamWriter w(pStream, true);
    uint32_t version = 3;
    if (w.mbOk) w.Accumulate(EA::IO::WriteUint32(w.mpStream, &version, 1, w.mEndian));
    uint64_t id = *(const uint64_t*)&pBag->mField18;
    if (w.mbOk) w.Accumulate(EA::IO::WriteUint64(w.mpStream, &id, 1, w.mEndian));
    uint32_t count = (uint32_t)(pBag->mpEnd - pBag->mpBegin);
    if (w.mbOk) w.Accumulate(EA::IO::WriteUint32(w.mpStream, &count, 1, w.mEndian));
    for (const PropPair* it = pBag->mpBegin; it != pBag->mpEnd; ++it) {
        PropPair tmp;
        tmp = *it;
        if (w.mbOk) w.Accumulate(EA::IO::WriteUint32(w.mpStream, &tmp.first, 1, w.mEndian));
        w.WriteVariant(&tmp.second);
    }
    return w.mbOk;
}

// @ 0x00612e50
struct IObjectLike {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual cPropertyBag* Cast(uint32_t typeId);  // +0xc
};
struct IStreamHolder {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual EA::IO::IStream* GetStream();  // +0x18
};
bool cPropertyListWriter::WriteResource(void* pObject, void* pStreamHolder, int, uint32_t typeId) {
    IObjectLike* pObj = (IObjectLike*)pObject;
    if (typeId == 0xfd60f0c1 && pObj) {
        cPropertyBag* pBag = pObj->Cast(0xaaff1cde);
        if (pBag) {
            if (Write(((IStreamHolder*)pStreamHolder)->GetStream(), pBag)) return true;
        }
    }
    return false;
}

// @ 0x00612f00
cPropertyBag::cPropertyBag(uint32_t a, uint32_t b) : PropertyBagBase(a), mField1C(b) {
    mpBegin = mpEnd = (PropPair*)(mpPoolBegin = mFixedBuffer);
    mpCapacity = (PropPair*)((char*)mpBegin + 0xf0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00612f50: SP::cPollinator lookup in a sorted vector of (64-bit key -> object).
struct KeyEntry {
    uint64_t key;
    IRefObj* pObject;  // +8
    uint32_t pad;
};
struct cAuthManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool IsLoggedIn();  // +0x24
};
cAuthManager* GetAuthManager();  // 0x00607a60
const KeyEntry* __cdecl FindKey(const KeyEntry* first, const KeyEntry* last, const uint64_t* pKey, bool bFlag);  // 0x007c8160

struct cPollinatorLookup {
    char pad[0x88];
    const KeyEntry* mpBegin;   // +0x88
    const KeyEntry* mpEnd;     // +0x8c
    char pad2[0x0c];
    bool mbFlag;               // +0x9c
    bool Lookup(uint64_t key, IRefObj** ppOut, bool bTouch);  // 0x00612f50
};
bool cPollinatorLookup::Lookup(uint64_t key, IRefObj** ppOut, bool bTouch) {
    const KeyEntry* pEnd = mpEnd;
    const KeyEntry* it = FindKey(mpBegin, pEnd, &key, mbFlag);
    if (it != pEnd) {
        if (!(key < it->key)) pEnd = it;
    }
    if (pEnd == mpEnd) {
        if (!bTouch) return false;
    } else if (!bTouch) {
        goto store;
    }
    if (GetAuthManager()->IsLoggedIn()) return true;
    if (!*((char*)SP::GetPollinator() + 0xf1)) return true;
store:
    if (ppOut) {
        IRefObj* pObj = pEnd->pObject;
        if (pObj) pObj->AddRef();
        *ppOut = pObj;
    }
    if (bTouch) SP::GetPollinator()->FUN_006103d0((uint32_t)key, (uint32_t)(key >> 32));
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00612270  SP::cPollinator::ProcessTransactionTick   (PARTIAL: only the three queue-scan loops and
// the call into ProcessTransactionQueue are transcribed; the FunctionalMatch constraint section at
// 0x006124f5..0x00612944 is a documented stub.)
//
// Structure of the original:
//  1. Return unless mbPollinationEnabled(+0xf1) and the global application state allows it.
//  2. now = DateTime(1) - mRefreshInterval(+0x10c)  (a 64-bit time stamp).
//  3. For each of three vectors of 0x70-byte records (+0xc8, +0xb4, +0xdc): if the record has a pending
//     entry (+0x44 != +0x48) and cAssetDirectory::GetLastRefreshTime(record+0x64) < now, create a job
//     object (0xf0 bytes) and push it (add-ref'd) on the message deque at this+8.
//  4. If the directory's refresh time for key 0xa86067e7 is older than now, build a FunctionalMatch
//     constraint list from the object template database, collect the matching server ids into an
//     8-byte-element vector, wrap them in a second job and push it on the same deque.
//  5. Finally call ProcessTransactionQueue().
struct JobRecord {
    char pad[0x44];
    uint32_t mPendingBegin;  // +0x44
    uint32_t mPendingEnd;    // +0x48
    char pad2[0x18];
    uint32_t mKey;           // +0x64
    uint32_t mState;         // +0x68
    char pad3[4];
};
void* __cdecl NewJobObject(uint32_t size);                                   // 0x006158b0
void CreateJob(void* pJob, int kind, uint32_t pending, uint32_t key);        // 0x00618da0
void QueueJob(void* pQueue, void* pJob, bool bLast);                         // 0x0060eaf0

static void ScanRecords(SP::cPollinator* p, JobRecord* first, JobRecord* last, uint32_t nowLo, uint32_t nowHi) {
    for (JobRecord* r = first; r != last; ++r) {
        if (r->mPendingBegin != r->mPendingEnd) {
            // if (p->mpAsssetDirectory->GetLastRefreshTime(r->mKey) < now) { create + queue the job }
            (void)nowLo; (void)nowHi;
            void* pJob = NewJobObject(0xf0);
            if (pJob) CreateJob(pJob, 2, r->mPendingBegin, r->mKey);
            QueueJob((char*)p + 8, pJob, r->mState == 0xb);
        }
    }
}

void SP::cPollinator::ProcessTransactionTick() {
    // (partial) see the comment above; the three scans use ScanRecords on the vectors at +0xc8/+0xb4/+0xdc.
    ScanRecords(this, *(JobRecord**)((char*)this + 0xc8), *(JobRecord**)((char*)this + 0xcc), 0, 0);
    ScanRecords(this, *(JobRecord**)((char*)this + 0xb4), *(JobRecord**)((char*)this + 0xb8), 0, 0);
    ScanRecords(this, *(JobRecord**)((char*)this + 0xdc), *(JobRecord**)((char*)this + 0xe0), 0, 0);
}
