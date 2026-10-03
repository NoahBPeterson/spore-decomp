// Slice s00417d60: constructor/destructor pair of a large tool-state object (outer object
// 0xdd0 bytes with an embedded 0xccc-byte sub-state at +0xfc), a property-key comparison
// helper, and a loader that fills a vector of ref-counted objects.
//
// Unoptimized module (no EH tables): compile with /Od /Ob1 /MD /Gy /TP /arch:SSE
#include "types.h"

struct PhantomTemps { PhantomTemps() {} uint32_t pad[16]; };
struct AllocTag { AllocTag() {} };
extern const float kZero;

class RefCounted {
public:
    virtual int AddRef();
    virtual int Release();
};

template <class T> class intrusive_ptr {
public:
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    void Reset()
    {
        if (mpObject) { T* pOld = mpObject; mpObject = 0; pOld->Release(); }
    }
    T* mpObject;
};

// Pointer that destroys its pointee through a non-virtual Destroy() (out of line).
template <class T> class owned_ptr {
public:
    owned_ptr() : mpValue(0) {}
    ~owned_ptr() { if (mpValue) mpValue->Destroy(); }
    T* mpValue;
};
template <int ID> struct Owned { void Destroy(); };

// Pointer to an object with a DefaultRefCounted sub-object at +4.
struct DefaultRefCounted { void Release(); };
struct RcObject { int vptrPad; DefaultRefCounted rc; };
class rc_ptr {
public:
    rc_ptr() : mpObject(0) {}
    ~rc_ptr() { if (mpObject) mpObject->rc.Release(); }
    RcObject* mpObject;
};

// Allocator-like member constructed out of line.
struct Alloc8 {
    Alloc8(const AllocTag&);
    uint32_t pad[2];
};

// Members built by an out-of-line init taking the allocator tag; destructor out of line.
template <int ID> struct Init20 {
    Init20(const AllocTag& a = AllocTag()) { Init(a); }
    void Init(const AllocTag&);
    ~Init20();
    uint32_t pad[5];
};

// Three zeroed pointers plus an allocator constructed out of line; dtor out of line.
template <int ID> struct Vec20 {
    Vec20(const AllocTag& a = AllocTag()) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(a) {}
    ~Vec20();
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCap;
    Alloc8 mAlloc;
};

// Out-of-line ctor taking the tag, inline trivial-range destruction, out-of-line free.
template <int ELEM, int ID, int SIZE> struct RangeVecTag {
    RangeVecTag(const AllocTag& a = AllocTag()) { Init(a); }
    void Init(const AllocTag&);
    void Free();
    ~RangeVecTag()
    {
        for (char* p = (char*)mpBegin; p < (char*)mpEnd; p += ELEM) {}
        Free();
    }
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t pad[(SIZE - 8) / 4];
};

// Same, but with a default (no-argument) out-of-line ctor.
template <int ELEM, int ID, int SIZE> struct RangeVec {
    RangeVec();
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t pad[(SIZE - 8) / 4];
    void Free();
    ~RangeVec()
    {
        for (char* p = (char*)mpBegin; p < (char*)mpEnd; p += ELEM) {}
        Free();
    }
};

// Same, with an out-of-line destructor.
template <int ID, int SIZE> struct OutVec {
    OutVec();
    ~OutVec();
    uint32_t pad[SIZE / 4];
};

// Member constructed with the tag; dtor out of line.
struct TagMember {
    TagMember(const AllocTag& a = AllocTag());
    ~TagMember();
    uint32_t pad[8];
};

// 16-byte string-like member: inline ctor pointing at a shared empty buffer.
extern uint16_t gEmptyString;
struct SmallString {
    SmallString() : mpBegin(0), mpEnd(0), mpCap(0)
    {
        mpBegin = &gEmptyString;
        mpEnd = mpBegin;
        mpCap = mpBegin + 1;
    }
    ~SmallString();
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCap;
    uint32_t mAlloc;
};

// Three zeroed pointers; dtor out of line.
struct PtrTriple {
    PtrTriple() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~PtrTriple();
    uint32_t mpBegin, mpEnd, mpCap;
    uint32_t pad[2];
};

struct PtrPair {
    PtrPair() : mpBegin(0), mpEnd(0) {}
    uint32_t mpBegin, mpEnd;
};

// ---------------------------------------------------------------------------
// Embedded sub-state (at +0xfc of the tool state), 0xccc bytes.
// ---------------------------------------------------------------------------
struct SubState {
    SubState();
    ~SubState();

    uint8_t mFlag;                                   // +0x000
    float mScale;                                    // +0x004
    intrusive_ptr<RefCounted> mpRef;                 // +0x008
    RangeVec<12, 0, 0xd8> mListA;                    // +0x00c
    RangeVec<0x38, 1, 0x398> mListB;                 // +0x0e4
    RangeVec<12, 0, 0xd8> mListC;                    // +0x47c
    RangeVec<0x38, 1, 0x398> mListD;                 // +0x554
    RangeVec<4, 2, 0x58> mListE;                     // +0x8ec
    int mCount;                                      // +0x944
    float mValueA;                                   // +0x948
    float mValueB;                                   // +0x94c
    int mPad950;                                     // +0x950
    int mFieldA;                                     // +0x954
    int mFieldB;                                     // +0x958
    int mFieldC;                                     // +0x95c
    RangeVec<4, 3, 0x118> mIdsA;                     // +0x960
    OutVec<4, 0x118> mIdsB;                          // +0xa78
    RangeVec<4, 3, 0x118> mIdsC;                     // +0xb90
    TagMember mTable;                                // +0xca8
    uint32_t mPadCC8;                                // +0xcc8 (assigned below)
};

// ---------------------------------------------------------------------------
// Tool state
// ---------------------------------------------------------------------------
struct ToolState {
    ToolState();
    ~ToolState();

    owned_ptr<Owned<0> > mpOwnedA;                   // +0x000
    rc_ptr mpRc;                                     // +0x004
    Init20<0> mA;                                    // +0x008
    Init20<1> mB;                                    // +0x01c
    Init20<2> mC;                                    // +0x030
    Init20<3> mD;                                    // +0x044
    Vec20<0> mV0;                                    // +0x058
    Vec20<1> mV1;                                    // +0x06c
    RangeVecTag<8, 0, 0x18> mV2;                     // +0x080
    Vec20<2> mV3;                                    // +0x098
    Vec20<3> mV4;                                    // +0x0ac
    owned_ptr<Owned<1> > mpOwnedB;                   // +0x0c0
    owned_ptr<Owned<2> > mpOwnedC;                   // +0x0c4
    int mCountA;                                     // +0x0c8
    int mCapacity;                                   // +0x0cc
    SmallString mName;                               // +0x0d0
    PtrTriple mItems;                                // +0x0e0
    uint8_t mFlagA;                                  // +0x0f4
    uint8_t mFlagB;                                  // +0x0f5
    int mMode;                                       // +0x0f8
    SubState mSub;                                   // +0x0fc
    PtrPair mTail;                                   // +0xdc8
};

// @ 0x00417d60
ToolState::ToolState()
    : mCountA(0), mCapacity(0x10), mFlagA(0), mFlagB(0), mMode(0)
{
}

// @ 0x00417fe0
ToolState::~ToolState()
{
}

// @ 0x00418120
SubState::SubState()
    : mFlag((PhantomTemps(), 0)), mScale(kZero), mCount(0), mValueA(kZero), mValueB(kZero),
      mFieldA(0), mFieldB(0), mFieldC(0), mPadCC8(0xffffffff)
{
}

// @ 0x00418240
SubState::~SubState()
{
}

// ---------------------------------------------------------------------------
// Property lookup helper
// ---------------------------------------------------------------------------
struct PropEntry {                                   // 0x20 bytes
    uint32_t pad[4];
    uint32_t mValue;                                 // +0x10
    uint32_t pad2[3];
};
struct PropList {
    uint32_t pad[2];
    PropEntry* mpEntries;                            // +0x08
};
uint32_t* FindProp(PropList* list, int id, int a, int b, int c);   // FUN_0071de40
int FindPropIndex(PropList* list, int id, int a, int b, int c);    // FUN_0071ddc0

// @ 0x00418440
bool CheckMatchingProps(PropList* list)
{
    uint32_t* pKey = FindProp(list, 1, -1, 0, 14);
    int idx1 = FindPropIndex(list, 9, -1, 0, 14);
    if (idx1 < 0)
        return false;
    PropEntry* pEntry1 = &list->mpEntries[idx1];
    uint32_t keyA = *pKey;
    uint32_t valA = pEntry1->mValue;
    if (keyA != valA)
        return false;
    int idx2 = FindPropIndex(list, 10, -1, 0, 14);
    if (idx1 < 0)
        return true;
    PropEntry* pEntry2 = &list->mpEntries[idx2];
    uint32_t keyB = *pKey;
    uint32_t valB = pEntry2->mValue;
    if (keyB != valB)
        return false;
    return true;
}

// ---------------------------------------------------------------------------
// Loader
// ---------------------------------------------------------------------------
struct PropKey { uint32_t a, b, c; };

class Manager1 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool Load(int a, int b, RefCounted** out);          // slot 11 (+0x2c)
};
class Manager2 {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual bool Find(const PropKey* key, RefCounted** out);    // slot 5 (+0x14)
};
Manager1* GetManager1();                                         // FUN_0067de30
Manager2* GetManager2();                                         // FUN_0067dcd0
bool GetPropKey(RefCounted* obj, int id, PropKey* out);          // FUN_006a1250

struct RefVector {
    void push_back(const intrusive_ptr<RefCounted>& p);           // FUN_004b54b0
    uint32_t pad[5];
};

struct Loader {
    uint32_t pad[3];
    RefVector mRefs;                                             // +0x0c
    void LoadAll(int a, int b);
};

// @ 0x00418500
void Loader::LoadAll(int a, int b)
{
    intrusive_ptr<RefCounted> obj;
    Manager1* mgr = GetManager1();
    obj.Reset();
    if (mgr->Load(a, b, &obj.mpObject)) {
        {
            intrusive_ptr<RefCounted> ref(obj.get());
            mRefs.push_back(ref);
        }
        for (int i = 0; i < 4; ++i) {
            PropKey key;
            key.a = 0; key.b = 0; key.c = 0;
            if (GetPropKey(obj.get(), i + 0xf9efbb, &key)) {
                intrusive_ptr<RefCounted> found;
                Manager2* mgr2 = GetManager2();
                found.Reset();
                if (mgr2->Find(&key, &found.mpObject)) {
                    intrusive_ptr<RefCounted> ref2(found.get());
                    mRefs.push_back(ref2);
                }
            }
        }
    }
}
