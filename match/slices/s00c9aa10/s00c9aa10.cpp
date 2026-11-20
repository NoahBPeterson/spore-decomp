// Slice s00c9aa10 -- SP::HotSpotMap::operator[] (look a hot spot up by its dense
// key and, when it is missing, insert a default 30-food spot at the hinted row).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (tribe module: no exceptions)
#include "types.h"
#include <new>

// 0x014853bc -- default hot-spot food and maximum food (30.0f).
extern const float kHotSpotFood;

// 0x00f47380 -- operator delete[] for the array owned by the pointer vector.
extern "C" void __cdecl operator_delete__(void* p);

struct IRef {
    virtual void AddRef();
    virtual void Release();
};

struct Vector3 {
    float x, y, z;
};

// 0x18-byte EASTL pointer vector (the owned array at +0x40 of a hot spot).
struct PtrVector {
    void*    mpBegin;        // +0x00
    void*    mpEnd;          // +0x04
    void*    mpCapacity;     // +0x08
    uint32_t mAllocator[3];  // +0x0c
};

// 0x58-byte hot-spot record; it sits at +0x08 of each 0x60-byte map row.
struct HotSpot {
    Vector3      mPos;          // +0x00
    float        mFood;         // +0x0c
    float        mMaxFood;      // +0x10
    float        mResupply;     // +0x14
    int          mCubeIndex[3]; // +0x18
    IRef*        mpEffect;      // +0x24
    IRef*        mpHitSphere;   // +0x28
    uint32_t     mUnused2c;     // +0x2c
    unsigned long long mStartTime; // +0x30
    bool         mbActive;      // +0x38
    bool         mbRemove;      // +0x39
    uint8_t      mPad3a[2];     // +0x3a
    IRef*        mpOrnament;    // +0x3c
    PtrVector    mPointers;     // +0x40

    HotSpot()
        : mFood(kHotSpotFood), mMaxFood(kHotSpotFood), mResupply(0.0f),
          mpEffect(0), mpHitSphere(0), mStartTime(0), mbActive(false),
          mbRemove(false), mpOrnament(0)
    {
        mPointers.mpBegin = 0;
        mPointers.mpEnd = 0;
        mPointers.mpCapacity = 0;
    }

    // 0x00c93dc0 -- copy constructor (another translation unit).
    HotSpot(const HotSpot& src);

    ~HotSpot()
    {
        if (mPointers.mpBegin && ((int*)mPointers.mpBegin)[-1] != 0)
            operator_delete__(mPointers.mpBegin);
        if (mpOrnament)
            mpOrnament->Release();
        if (mpHitSphere)
            mpHitSphere->Release();
        if (mpEffect)
            mpEffect->Release();
    }
};

// 0x60-byte map row: dense key, padding, then the value.
struct HotSpotElem {
    uint32_t mKey;    // +0x00
    uint32_t mPad;    // +0x04
    HotSpot  mValue;  // +0x08

    HotSpotElem(uint32_t key, const HotSpot& value) : mKey(key), mValue(value) {}
};

// 0x00c92d50 -- lower_bound over the dense row array (cdecl, 4 arguments).
extern "C" HotSpotElem* __cdecl HotSpotLowerBound(HotSpotElem* first, HotSpotElem* last,
                                                  const uint32_t* key, uint8_t lessFlag);

struct HotSpotMap {
    HotSpotElem* mpBegin;                // +0x00
    HotSpotElem* mpEnd;                  // +0x04
    uint8_t      mPad08[0xc18 - 0x08];   // +0x08
    uint8_t      mField0c18;             // +0xc18

    HotSpot* at(const uint32_t* key);   // 0x00c9aa10 (declared operator[] in the game)

    // 0x00c9a9b0 -- hinted insert of a whole row (thiscall, ret 8).
    HotSpotElem* Insert(HotSpotElem* pos, const HotSpotElem* row);
};

// Scratch storage for the default spot.  Retail never destroys this object:
// the default spot owns nothing, and only the row's copied value gets a
// destructor, so the default spot is built with placement new in raw storage.
struct SpotScratch {
    __declspec(align(4)) char mRaw[sizeof(HotSpot)];

    SpotScratch() {}
};

// @ 0x00c9aa10  SP::HotSpotMap::at (operator[])
HotSpot* HotSpotMap::at(const uint32_t* key)
{
    HotSpotElem* end = mpEnd;
    HotSpotElem* pos = HotSpotLowerBound(mpBegin, end, key, mField0c18);

    // A row already holding this key wins; otherwise a default spot is inserted
    // at the hinted position and the new row is returned instead.
    if (pos == end || *key < pos->mKey)
    {
        SpotScratch scratch;
        new (scratch.mRaw) HotSpot;
        HotSpotElem row(*key, *reinterpret_cast<HotSpot*>(scratch.mRaw));
        pos = Insert(pos, &row);
    }
    return &pos->mValue;
}
