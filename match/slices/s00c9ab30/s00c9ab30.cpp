// @ 0x00c9ab30  Simulator reader for SP::HotSpotMap (bulk load of the hot-spot grid).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int   u32;
typedef unsigned char  u8;

// --------------------------------------------------------------------- ref counting
struct IRef {
    virtual void AddRef();
    virtual void Release();
};
void operator_delete__(void* p);

// --------------------------------------------------------------------- value type
struct Vector3 { float x, y, z; };

struct PtrVector {
    void* mpBegin;        // +0x00
    void* mpEnd;          // +0x04
    void* mpCapacity;     // +0x08
    u32   mAllocator[3];  // +0x0c
};

// 0x58-byte value stored in each map row.  The default constructor
// deliberately leaves mPos alone (retail never writes the position here:
// it is read from the stream by cVarListSerializer).
struct cFishingHotSpot {
    Vector3  mPos;              // +0x00
    float    mFood;             // +0x0c
    float    mMaxFood;          // +0x10
    float    mResupply;         // +0x14
    int      mCubeIndex[3];     // +0x18
    IRef*    mpEffect;          // +0x24
    IRef*    mpHitSphere;       // +0x28
    u32      mPad2c;            // +0x2c
    unsigned long long mStartTime;  // +0x30
    bool     mbActive;          // +0x38
    bool     mbRemove;          // +0x39
    u8       mPad3a[2];         // +0x3a
    IRef*    mpOrnament;        // +0x3c
    PtrVector mPointers;        // +0x40

    cFishingHotSpot()
        : mFood(30.0f), mMaxFood(30.0f), mResupply(0.0f),
          mpEffect(0), mpHitSphere(0), mStartTime(0),
          mbActive(false), mbRemove(false), mpOrnament(0)
    {
        mPointers.mpBegin = 0;
        mPointers.mpEnd = 0;
        mPointers.mpCapacity = 0;
    }

    cFishingHotSpot(const cFishingHotSpot& src);              // 0x00c93dc0
    cFishingHotSpot& operator=(const cFishingHotSpot& x);     // 0x00c95010

    ~cFishingHotSpot()
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

// 0x60-byte map row: dense sort key, then the value.  Only the key and the
// value are ever written here; mPad is layout, not state.
struct HotSpotElem {
    u32              mKey;      // +0x00
    u32              mPad;      // +0x04
    cFishingHotSpot  mValue;    // +0x08

    HotSpotElem(u32 key, const cFishingHotSpot& value)
        : mKey(key), mValue(value) {}
};

extern "C" HotSpotElem* __cdecl
HotSpotLowerBound(HotSpotElem* first, HotSpotElem* last, u32* key, u8 less);  // 0x00c92d50

// Moves [first, last) to dest, assigning the values (0x00c95a70).
extern "C" HotSpotElem* __cdecl
HotSpotRowCopy(HotSpotElem* first, HotSpotElem* last, HotSpotElem* dest);

// What the map's insert returns: the row it found or created, and whether
// that row is new (the value still has to be assigned) or already present.
struct HotSpotInsertResult {
    HotSpotElem* first;
    bool         second;
};

// --------------------------------------------------------------------- the map
struct HotSpotMap {
    HotSpotElem* mpBegin;                 // +0x00
    HotSpotElem* mpEnd;                   // +0x04
    HotSpotElem* mpCapacity;              // +0x08
    u8           mPad0c[0xc18 - 0x0c];    // +0x0c
    u8           mField0c18;              // +0xc18

    void FreeRange(HotSpotElem* first, HotSpotElem* last);                  // 0x00c93690
    HotSpotElem* Insert(HotSpotElem* pos, const HotSpotElem* row);          // 0x00c9a000
};

// --------------------------------------------------------------------- serialization
struct IOStream;
extern "C" bool __cdecl
ReadUint32(IOStream* pStream, void* pDst, int count, int flags);            // 0x0093a780

struct ReadSerializer {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual IOStream* GetStream();                                          // +0x18
};

struct ISerializerReadStream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool BeginObject();                                             // +0x1c
    virtual ReadSerializer* GetSerializer();                                // +0x20
};

// Variable-list serializer used to read one cFishingHotSpot.  The object
// occupies 0xa14 bytes: retail reserves exactly that much frame for it
// (frame 0xae0 = locals 0xc..0xaec, the object being the top 0xa14).
struct cVarListSerializer {
    u8 mStorage[0xa14];
    cVarListSerializer(void* pObject, void* pType, u32 id);                 // 0x00692f90
    char Serialize(ISerializerReadStream* pStream);                         // 0x00693e10
};

// Type/owner object passed to the serializer constructor.
extern char g_hotSpotListType;                                              // 0x0157b7d0

// @ 0x00c9ab30
bool HotSpotMap_Read(ISerializerReadStream* pStream, HotSpotMap* pMap)
{
    // Drop whatever the map held before deserializing (erase(begin(), end())).
    {
        HotSpotElem* first = pMap->mpBegin;
        HotSpotElem* last = pMap->mpEnd;
        HotSpotElem* newFirst = HotSpotRowCopy(last, last, first);
        pMap->FreeRange(newFirst, pMap->mpEnd);
        pMap->mpEnd -= last - first;
    }

    u32 count = 0;
    IOStream* pIn = pStream->GetSerializer()->GetStream();
    ReadUint32(pIn, &count, 1, 0);

    for (u32 i = 0; i < count; ++i) {
        cFishingHotSpot spot;

        u32 key;
        pIn = pStream->GetSerializer()->GetStream();
        ReadUint32(pIn, &key, 1, 0);

        pStream->BeginObject();

        cVarListSerializer serializer(&spot, &g_hotSpotListType, 0x1a80d26);
        serializer.Serialize(pStream);

        pStream->BeginObject();

        HotSpotInsertResult res;
        {
            HotSpotElem row(key, spot);
            HotSpotElem* end = pMap->mpEnd;
            HotSpotElem* pos = HotSpotLowerBound(pMap->mpBegin, end, &row.mKey,
                                                 pMap->mField0c18);
            if (pos != end && row.mKey >= pos->mKey) {
                res.second = false;
                res.first = pos;
            } else {
                res.first = pMap->Insert(pos, &row);
                res.second = true;
            }
        }
        if (!res.second)
            res.first->mValue = spot;
    }

    return pStream->BeginObject();
}
