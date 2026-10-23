// Slice s00c947d0 — cTribe chat-bubble popups, tool layout reset, fishing hotspot copy,
// EASTL vector/deque helpers and a bubble-list teardown helper.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <math.h>
#include <stddef.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

inline void* operator new(unsigned int, void* p) throw() { return p; }
void __cdecl operator_delete__(void* p);                                  // 0xf47380 (operator delete[])
void* __cdecl operator_new(unsigned size, const char* file, int a, int b, int c, int d);   // 0xf473a0

// ---------------------------------------------------------------------------
// math
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Quaternion { float x, y, z, w; };
struct Matrix3 { Vector3 mRow[3]; };

inline float AbsFloat(float f) { return f < 0.0f ? -f : f; }

// ---------------------------------------------------------------------------
// refcounted objects
// ---------------------------------------------------------------------------
struct IRefCounted {
    virtual void AddRef();     // +0x00
    virtual void Release();    // +0x04
};
struct cToolObject : IRefCounted {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc();
    virtual void Unload();     // +0xc0
};

struct sp_vector_allocator {
    const char* mpName;
    uint32_t mFlags;
    sp_vector_allocator() {}
    void deallocate(void* p) { if (((uint32_t*)p)[-1]) operator_delete__(p); }
};

template <class T> inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

template <class T> T* __cdecl copy_impl(const T* first, const T* last, T* dest);     // 0xa7a930
template <class T> T* __cdecl uninitialized_copy(const T* first, const T* last, T* dest);  // 0xc92ce0
template <class T> T* __cdecl grow_copy(unsigned n, const T* first, const T* last);  // 0xc93d60

template <class T> struct SpVector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    SpVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SpVector() { destruct(mpBegin, mpEnd); if (mpBegin) mAllocator.deallocate(mpBegin); }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    unsigned capacity() const { return (unsigned)(mpCapacity - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    T& operator[](unsigned i) { return mpBegin[i]; }
    T& back() { return *(mpEnd - 1); }

    void reserve(unsigned n);                       // out-of-line instance
    T* erase(T* first, T* last);                    // out-of-line instance (0x50f740 / 0xc83c90)
    void DoInsertValue(T* pos, const T& value);     // out-of-line instance
    SpVector& operator=(const SpVector& x);
    void resize(unsigned n);

    T* EraseInline(T* first, T* last)
    {
        T* const pNewEnd = copy_impl(last, mpEnd, first);
        destruct(pNewEnd, mpEnd);
        mpEnd -= (last - first);
        return first;
    }
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void push_back()
    {
        if (mpEnd < mpCapacity)
            ::new ((void*)mpEnd++) T();
        else
            DoInsertValue(mpEnd, T());
    }
};

struct AutoRef {                                        // 4-byte EASTL AutoRefCount
    IRefCounted* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(const AutoRef& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(const AutoRef& x)
    {
        IRefCounted* const pObject = x.mpObject;
        if (pObject != mpObject) {
            IRefCounted* const pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Release();
        }
        return *this;
    }
};

struct cToolSlot {                                      // 4-byte tool reference
    cToolObject* mpObject;
    cToolSlot() : mpObject(0) {}
    cToolSlot(const cToolSlot& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~cToolSlot() { if (mpObject) mpObject->Unload(); }
    cToolSlot& operator=(const cToolSlot& x)
    {
        cToolObject* const pObject = x.mpObject;
        if (pObject != mpObject) {
            cToolObject* const pOld = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pOld)
                pOld->Unload();
        }
        return *this;
    }
};

// ---------------------------------------------------------------------------
// spatial objects
// ---------------------------------------------------------------------------
struct cSpatial {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3& GetPosition();            // +0x2c
    virtual const Quaternion& GetOrientation();      // +0x30
    virtual void v34();
    virtual void SetPosition(const Vector3& p);      // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54();
    virtual bool IsVisible();                        // +0x58
    virtual bool GetFacing(Vector3* out);            // +0x5c
};

struct cToolNode {                                   // cTribe + 0x260 target
    uint32_t pad00[13];
    cSpatial mSpatial;                               // +0x34
};
struct cActionCircle {
    uint8_t mData[0x64];
    void SetAtCenter(const Vector3& center, float altitude, const Vector3* facing, float radius);  // 0xaf9cf0
    void EmitCopy(const Vector3& pos, float radius);                                              // 0xafec00
    void Execute();                                                                                // 0xafaec0
};
struct cEmptyBubble {                                // 20 bytes
    Vector3 mPosition;
    float mAmount;                                   // +0x0c
    uint32_t mUnused;                                // +0x10
    cEmptyBubble() : mAmount(0.0f), mUnused(0) {}
};
struct cTribeChatArea { uint32_t mData[5]; };         // 20 bytes
struct cLocaleSeparators {                           // cTribe + 0x18cc target
    uint32_t pad00[0x182];
    uint32_t mDecimalSep;                            // +0x608
    uint32_t mThousandSep;                           // +0x60c
};

// ---------------------------------------------------------------------------
// the tribe
// ---------------------------------------------------------------------------
struct cTribe {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();

    uint8_t pad00[0x120 - 0x004];                    // +0x004 .. +0x120
    cSpatial mSpatial;                               // +0x120 (vftable only)
    uint8_t pad184[0x260 - 0x124];                   // +0x124 .. +0x260
    cToolNode* mpToolNode;                           // +0x260
    uint8_t pad264[0x2a8 - 0x264];                   // +0x264 .. +0x2a8
    SpVector<cEmptyBubble> mEmptyBubbles;            // +0x2a8 (0x14 bytes)
    uint8_t pad2bc[0x2d4 - 0x2bc];                   // +0x2bc .. +0x2d4
    void* mpToolLayoutKey;                           // +0x2d4
    uint8_t pad2d8[0x340 - 0x2d8];                   // +0x2d8 .. +0x340
    SpVector<AutoRef> mRefObjects;                   // +0x340 (0x14 bytes)
    SpVector<cToolSlot> mToolSlots;                  // +0x354 (0x14 bytes)
    void* mpToolLayout;                              // +0x368
    uint8_t pad36c[0x3b4 - 0x36c];                   // +0x36c .. +0x3b4
    cActionCircle mActionCircle;                     // +0x3b4 (0x64 bytes)
    SpVector<Vector3> mHutLocations;                 // +0x418 (0x14 bytes)
    uint8_t pad42c[0x18cc - 0x42c];                  // +0x42c .. +0x18cc
    cLocaleSeparators* mpLocaleSeparators;           // +0x18cc

    void ShowFishingString(float amount, const Vector3* pos);            // 0xc947d0
    void DoShowFishingString(uint32_t effectID, const wchar_t* format,
                             wchar_t sign, wchar_t thousandSep,
                             float amount, const Vector3* pos);
    void SquirtFishingSplash(float radius);                              // 0xc94b50
    void ResetToolLayout();                                              // 0xc951d0
    void AddPanicBubble(const Vector3& pos, float amount, int empireID); // 0xc95540
    void RemoveRefObject(void* key);                                     // 0xc950f0
    void RemoveToolSlot(void* key);                                      // 0xc95150
};

struct cFishingHotSpot {
    Vector3 mCenter;                                 // +0x00
    float mRadius;                                   // +0x0c
    float mScale;                                    // +0x10
    float mFacing;                                   // +0x14
    Vector3 mDirection;                              // +0x18
    AutoRef mpFirst;                                 // +0x24
    AutoRef mpSecond;                                // +0x28
    uint32_t mCachedCost;                            // +0x2c (derived, not copied)
    uint32_t mField30;                               // +0x30
    uint32_t mField34;                               // +0x34
    bool mbFlag38;                                   // +0x38
    bool mbFlag39;                                   // +0x39
    uint8_t pad3a[2];                                // +0x3a
    AutoRef mpThird;                                 // +0x3c
    SpVector<Vector3> mPoints;                       // +0x40 (0x14 bytes)

    cFishingHotSpot& operator=(const cFishingHotSpot& x);   // 0xc95010
};

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------
namespace SP {
struct cEffectsManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateEffect(uint32_t effectID, int flags, void** out);   // +0x2c
};
cEffectsManager* __cdecl EffectsManager();                      // 0x67ddd0

struct cEffect {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void SendMessage(const void* msg);                  // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void SetText(int slot, void* object);               // +0x4c
};
int __cdecl PlayerEmpireID();                                   // 0x1021090 cSPLivingUniverse::GetPlayerEmpireID
}

struct cCheatObject2 : IRefCounted {
    virtual void v08();            // +0x08
    cCheatObject2();               // 0x57a6d0
    wchar_t mText[8];              // +0x0c
};
struct cXformMsg {                 // 0x38
    uint16_t mFlags;
    uint16_t mVersion;
    Vector3 mTranslation;
    void SetTranslation(const Vector3& t) { mTranslation = t; mFlags |= 4; ++mVersion; }
};
void __cdecl cXformMsg_ctor(cXformMsg* self);                                // 0x434040
namespace EA { namespace Locale {
void __cdecl SetNumberString(int value, int high, wchar_t* out, int size);   // 0x881ae0
}}
int __cdecl WStr_Format(wchar_t* out, const wchar_t* format, ...);           // 0x41e050

bool __cdecl ResolveToolData(void* key, uint32_t code, int* count, const Vector3** data);  // 0x6a0990
Vector3 __cdecl XformVector(const Vector3& v, const Quaternion& q);          // 0x59aed0
cToolSlot* __cdecl FindToolSlot(cToolSlot* first, cToolSlot* last, const void* key);  // 0xc93640
void __cdecl InsertFillChatAreas(cTribeChatArea* end, unsigned n, const cTribeChatArea& v);      // 0xc93e60
cTribeChatArea* __cdecl copy_Rec20(const cTribeChatArea* first, const cTribeChatArea* last,
                                   cTribeChatArea* dest);                    // 0x951bf0
void __cdecl FUN_00abf900(void* p);                                          // 0xabf900

// ---------------------------------------------------------------------------
// helpers used by the cTribe bodies
// ---------------------------------------------------------------------------
void __thiscall cTribe::DoShowFishingString(uint32_t effectID, const wchar_t* format,
                                            wchar_t sign, wchar_t thousandSep,
                                            float amount, const Vector3* pos)
{
    void* pEffect = 0;
    if (!SP::EffectsManager()->CreateEffect(effectID, 0, &pEffect))
        return;

    cXformMsg msg;
    cXformMsg_ctor(&msg);
    msg.SetTranslation(*pos);
    ((SP::cEffect*)pEffect)->SendMessage(&msg);

    cCheatObject2* pCheat = (cCheatObject2*)operator_new(sizeof(cCheatObject2), "Simulator", 0, 0, 0, 0);
    if (pCheat) {
        new (pCheat) cCheatObject2();
        pCheat->AddRef();
    }

    const float magnitude = AbsFloat(amount);
    int value = (int)magnitude;
    if (magnitude < (float)value)
        --value;

    wchar_t text[0x40];
    EA::Locale::SetNumberString(value, value >> 31, text, 0x40);

    cLocaleSeparators* pSeparators = mpLocaleSeparators;
    if (pSeparators && pSeparators->mThousandSep != 0 && pSeparators->mDecimalSep != 0)
        WStr_Format(pCheat->mText, format, thousandSep, sign, text);
    else if (pSeparators && pSeparators->mThousandSep != 0)
        WStr_Format(pCheat->mText, format, 0x268e, sign, text);
    else
        WStr_Format(pCheat->mText, format, 0x268d, sign, text);

    ((SP::cEffect*)pEffect)->SetText(8, pCheat);
    ((SP::cEffect*)pEffect)->v08();

    if (pCheat)
        pCheat->Release();
    if (pEffect)
        ((SP::cEffect*)pEffect)->v04();
}

// ---------------------------------------------------------------------------
// @ 0x00c947d0
void __thiscall cTribe::ShowFishingString(float amount, const Vector3* pos)
{
    if (!mSpatial.IsVisible())
        return;

    if (amount > 0.0f)
        DoShowFishingString(0xdbf1ae1f, L"%lc%lc%s", L'+', 0x268f, amount, pos);
    else
        DoShowFishingString(0xd2bf5747, L"%lc%lc%ls", L'-', 0x268f, amount, pos);
}

// ---------------------------------------------------------------------------
// @ 0x00c94b50
void __thiscall cTribe::SquirtFishingSplash(float radius)
{
    if (!mSpatial.IsVisible())
        return;

    cSpatial* pCasting = &mpToolNode->mSpatial;
    const Vector3& facing = pCasting->GetPosition();
    const float x = facing.x;
    const float y = facing.y;
    const float z = facing.z;
    const float invLen = 1.0f / sqrtf(y * y + (z * z + x * x) + 1e-08f);

    Vector3 pos;
    pos.x = invLen * x * 2.0f + x;
    pos.y = invLen * y * 2.0f + y;
    pos.z = invLen * z * 2.0f + z;
    ShowFishingString(radius, &pos);
}

// ---------------------------------------------------------------------------
// @ 0x00c94c30
template <> SpVector<Vector3>& SpVector<Vector3>::operator=(const SpVector<Vector3>& x)
{
    if (this != &x) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (capacity() < n) {
            Vector3* pNew = grow_copy(n, x.mpBegin, x.mpEnd);
            if (mpBegin && ((uint32_t*)mpBegin)[-1])
                operator_delete__(mpBegin);
            mpBegin = pNew;
            mpCapacity = pNew + n;
        } else if (size() < n) {
            copy_impl(x.mpBegin, x.mpBegin + size(), mpBegin);
            uninitialized_copy(x.mpBegin + size(), x.mpEnd, mpEnd);
        } else {
            copy_impl(x.mpBegin, x.mpEnd, mpBegin);
        }
        mpEnd = mpBegin + n;
    }
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x00c94ec0
namespace SP {
namespace {
struct ComparePositions {
    Vector3 mCenter;
    bool operator()(const Vector3& a, const Vector3& b) const;
};
}
}
Vector3* __cdecl SelectPivot(Vector3* first, Vector3* mid, Vector3* last,
                             SP::ComparePositions compare);                  // 0xc90b40
Vector3* __cdecl PartitionRange(Vector3* first, Vector3* last, const Vector3& pivot,
                                SP::ComparePositions compare);               // 0xc940d0
void __cdecl InsertionSort(Vector3* first, Vector3* last, SP::ComparePositions compare);   // 0xc94270

namespace eastl {
Vector3* quick_sort_impl(Vector3* first, Vector3* last, int depth, SP::ComparePositions compare)
{
    while (last - first > 0x1c && depth > 0) {
        Vector3* pPivot = SelectPivot(first, first + (last - first) / 2, last - 1, compare);
        const Vector3 pivot = *pPivot;
        Vector3* pCut = PartitionRange(first, last, pivot, compare);
        --depth;
        quick_sort_impl(pCut, last, depth, compare);
        last = pCut;
    }
    if (depth == 0)
        InsertionSort(first, last, compare);
    return first;
}
}

// ---------------------------------------------------------------------------
// @ 0x00c95010
cFishingHotSpot& cFishingHotSpot::operator=(const cFishingHotSpot& x)
{
    mCenter = x.mCenter;
    mRadius = x.mRadius;
    mScale = x.mScale;
    mFacing = x.mFacing;
    mDirection = x.mDirection;

    mpFirst = x.mpFirst;
    mpSecond = x.mpSecond;
    mField30 = x.mField30;
    mField34 = x.mField34;
    mbFlag38 = x.mbFlag38;
    mbFlag39 = x.mbFlag39;
    mpThird = x.mpThird;
    mPoints = x.mPoints;
    return *this;
}

// ---------------------------------------------------------------------------
// @ 0x00c950f0
void __thiscall cTribe::RemoveRefObject(void* key)
{
    cToolSlot* const pFound = FindToolSlot(mToolSlots.mpBegin, mToolSlots.mpEnd, &key);
    if (pFound != mToolSlots.mpEnd) {
        if (pFound + 1 < mToolSlots.mpEnd)
            copy_impl<cToolSlot>(pFound + 1, mToolSlots.mpEnd, pFound);
        mToolSlots.mpEnd -= 1;
        mToolSlots.mpEnd->~cToolSlot();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00c95150
void __thiscall cTribe::RemoveToolSlot(void* key)
{
    AutoRef* pSlot = mRefObjects.mpBegin;
    AutoRef* const pEnd = mRefObjects.mpEnd;
    while (pSlot != pEnd && pSlot->mpObject != key)
        ++pSlot;
    if (pSlot != pEnd)
        mRefObjects.EraseInline(pSlot, pSlot + 1);
}

// ---------------------------------------------------------------------------
// @ 0x00c951d0
void __thiscall cTribe::ResetToolLayout()
{
    int count = 0;
    const Vector3* pData = 0;
    if (!mpToolLayout)
        return;

    if (mpToolLayoutKey && ResolveToolData(mpToolLayoutKey, 0x73326b2, &count, &pData)) {
        SpVector<Vector3> offsets;
        for (int i = 0; i < count; ++i) {
            Vector3 pos = XformVector(pData[i], mSpatial.GetOrientation());
            const Vector3& origin = mSpatial.GetPosition();
            pos.x += origin.x;
            pos.y += origin.y;
            pos.z += origin.z;
            if (i == 0)
                mpToolNode->mSpatial.SetPosition(pos);
            else
                offsets.push_back(pos);
        }

        Vector3 center;
        float facing = 0.0f;
        if (mSpatial.GetFacing(&center))
            facing = center.x;
        const Vector3& origin = mSpatial.GetPosition();
        mActionCircle.SetAtCenter(origin, 0.0f, &center, 10.0f);
        mActionCircle.EmitCopy(origin, 3.0f);
        mActionCircle.Execute();
    }

    if (mpToolLayoutKey && ResolveToolData(mpToolLayoutKey, 0x6303995, &count, &pData)) {
        mHutLocations.erase(mHutLocations.mpBegin, mHutLocations.mpEnd);
        const int limit = count > 15 ? 15 : count;
        for (int i = 0; i < limit; ++i) {
            Vector3 pos = XformVector(pData[i], mpToolNode->mSpatial.GetOrientation());
            const Vector3& origin = mpToolNode->mSpatial.GetPosition();
            pos.x += origin.x;
            pos.y += origin.y;
            pos.z += origin.z;
            mHutLocations.push_back(pos);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00c95540
void __thiscall cTribe::AddPanicBubble(const Vector3& pos, float amount, int empireID)
{
    if (empireID != SP::PlayerEmpireID())
        return;
    mEmptyBubbles.push_back();
    mEmptyBubbles.back().mPosition = pos;
    mEmptyBubbles.back().mAmount = amount;
}

// ---------------------------------------------------------------------------
// @ 0x00c955e0
template <> void SpVector<cTribeChatArea>::resize(unsigned n)
{
    const unsigned current = size();
    if (current < n) {
        InsertFillChatAreas(mpEnd, n - current, cTribeChatArea());
        return;
    }
    cTribeChatArea* const pNewEnd = mpBegin + n;
    copy_Rec20(mpEnd, mpEnd, pNewEnd);
    mpEnd = pNewEnd;
}

// ---------------------------------------------------------------------------
// deque iterators used by the texture-async queue
// ---------------------------------------------------------------------------
struct DequeIter2 {
    void* mpBlock;       // +0x00
    void* mpCurrent;     // +0x04
    void* mpFirst;       // +0x08
    void* mpLast;        // +0x0c
    DequeIter2& operator+=(int n);     // 0x7a9a80
};
struct cTextureAsyncQueueEntry { uint32_t mData[4]; };     // 16 bytes
struct cTextureAsyncQueue {
    uint32_t pad00[2];
    cTextureAsyncQueueEntry* mpBegin;        // +0x08
    cTextureAsyncQueueEntry* mpEnd;          // +0x0c
    cTextureAsyncQueueEntry* mpCapacity;     // +0x10
    cTextureAsyncQueueEntry** mpBlocks;      // +0x14
    cTextureAsyncQueueEntry** mpBlockEnd;    // +0x18
    cTextureAsyncQueueEntry** mpBlockBegin;  // +0x1c
    cTextureAsyncQueueEntry** mpFreeBlock;   // +0x20
    cTextureAsyncQueueEntry** mpLastBlock;   // +0x24

    cTextureAsyncQueueEntry* Insert(DequeIter2* pResult, DequeIter2 pos,
                                    const cTextureAsyncQueueEntry& value);   // 0xc95660
};
void __cdecl DequeInsertFront(cTextureAsyncQueueEntry* pos, const cTextureAsyncQueueEntry* value,
                              cTextureAsyncQueueEntry* first);      // 0xbff1b0
void __cdecl DequeInsertBack(cTextureAsyncQueueEntry* pos, const cTextureAsyncQueueEntry* value,
                             cTextureAsyncQueueEntry* last);        // 0xc94e50
void __cdecl DequeOnInsertFront();                                  // 0xc92b70
void __cdecl DequeOnInsertBack();                                   // 0xabf980

// ---------------------------------------------------------------------------
// @ 0x00c95660
cTextureAsyncQueueEntry* __thiscall cTextureAsyncQueue::Insert(DequeIter2* pResult, DequeIter2 pos,
                                                              const cTextureAsyncQueueEntry& value)
{
    if (pos.mpCurrent == pos.mpLast) {
        // the iterator sits past the end of its block: move to the start of the next one
        pos.mpBlock = *(void**)pos.mpBlock;
        pos.mpFirst = pos.mpBlock;
        pos.mpCurrent = pos.mpBlock;
        pos.mpLast = (char*)pos.mpBlock + 0x100;
    }

    const int index = ((int)((char*)mpBlocks - (char*)mpBlockEnd) >> 2) * 0x40
                    + ((int)((char*)mpEnd - (char*)mpBegin) >> 2) - 0x40
                    + ((int)((char*)pos.mpCurrent - (char*)pos.mpBlock) >> 2);

    const int lastIndex = ((int)((char*)mpLastBlock - (char*)mpBlockEnd) >> 2) * 0x40
                        + ((int)((char*)mpBlockBegin - (char*)mpBlocks) >> 2)
                        + ((int)((char*)mpEnd - (char*)mpBegin) >> 2);

    if (index < lastIndex / 2) {
        DequeInsertFront((cTextureAsyncQueueEntry*)pos.mpCurrent, &value, mpBegin);
        DequeOnInsertFront();
    } else {
        cTextureAsyncQueueEntry first = *mpBegin;
        DequeInsertBack((cTextureAsyncQueueEntry*)pos.mpCurrent, &value, mpEnd);
        DequeOnInsertBack();
        (void)first;
    }

    DequeIter2 result;
    result.mpBlock = mpBegin;
    result.mpFirst = mpCapacity;
    result.mpCurrent = mpEnd;
    result.mpLast = mpBlocks;
    result += index;
    pResult->mpBlock = result.mpBlock;
    pResult->mpCurrent = result.mpCurrent;
    pResult->mpFirst = result.mpFirst;
    pResult->mpLast = result.mpLast;
    return (cTextureAsyncQueueEntry*)pResult;
}

// ---------------------------------------------------------------------------
// resource stream reading
// ---------------------------------------------------------------------------
struct cResourceReader {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c();                    // +0x1c (finish read)
    virtual void* GetStream();             // +0x20
    virtual void* GetStreamOwner();        // +0x24
    void ReadPositions(SpVector<Vector3>* pOut);      // 0xc95780
};
void __cdecl ReadInt32(void* pStream, int* pValue, int count, int async);   // 0x93a780
void __cdecl Vec3Vec_Reserve(SpVector<Vector3>* pVector, unsigned n);       // 0x41e4d0
void __cdecl ReadPositionValue(cResourceReader* pReader, Vector3* pOut);    // 0xae2ed0

// ---------------------------------------------------------------------------
// @ 0x00c95780
void __thiscall cResourceReader::ReadPositions(SpVector<Vector3>* pOut)
{
    pOut->erase(pOut->mpBegin, pOut->mpEnd);

    int count = 0;
    ReadInt32(GetStream(), &count, 1, 0);
    Vec3Vec_Reserve(pOut, count);

    const unsigned n = (unsigned)count;
    for (unsigned i = 0; i < n; ++i) {
        Vector3 pos(0.0f, 0.0f, 0.0f);
        ReadPositionValue(this, &pos);
        pOut->push_back(pos);
    }

    v1c();      // finish the read (tail call in the original)
}

// ---------------------------------------------------------------------------
struct cBubbleOwner {                 // sub-object at +0 of every bubble node
    void Destroy();                   // 0xabf900 (thiscall, no arguments)
};
struct cBubbleNode {
    uint32_t mType;                    // +0x00
    cBubbleOwner mOwner;               // +0x04
    uint8_t pad08[0x30 - 0x08];        // +0x08 .. +0x30
    cBubbleNode* mpNext;               // +0x30
};

// @ 0x00c95930
void __stdcall FreeBubbleLists(cBubbleNode** pLists, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        cBubbleNode* pNode = pLists[i];
        while (pNode) {
            cBubbleNode* const pFree = pNode;
            pNode = pNode->mpNext;
            pFree->mOwner.Destroy();
            operator_delete__(pFree);
        }
        pLists[i] = 0;
    }
}
