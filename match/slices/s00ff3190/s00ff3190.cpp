// Slice s00ff3190 -- Simulator helpers: the cCitySummary model map, the
// cCubeImage sample modifier, and the cSpaceInventory / cSPPlayerInventory
// serialization + tool-list helpers.
//
// Flags: /O2 /MD /Gy /TP
//
// The classes below are local stubs with role-named fields at the retail
// offsets read off the disassembly (the migrated headers carry the 2008
// dev-PDB layout, which is shifted and wrong for retail).
#include "types.h"
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// small value types
// ---------------------------------------------------------------------------
struct Vector3 { u32 x, y, z; };            // 0xc-byte map value / vector element
struct CubeSample { float u, v; int face; };// argument block for SampleBilinear

// ---------------------------------------------------------------------------
// globals / cdecl callees
// ---------------------------------------------------------------------------
extern u32  _sStoredModelKeys[16];          // 0x015b4df8 .. 0x015b4e38
extern char g_16daddc;                      // 0x016daddc

extern "C" {
void* __cdecl FUN_00f473a0(u32 size, const char* file, int a, int b, int c, int d); // operator new
void  __cdecl FUN_00f47380(void* p);        // operator delete[]
void* __cdecl FUN_00ac0d80(void* begin, void* end, const void* key); // eastl::find<Key_*,Key>
void* __cdecl FUN_00b3d2a0();               // SP::StarManager() -> global singleton
void* __cdecl FUN_00b3d390();               // global tool manager (0x0167eb08)
void* __cdecl FUN_0102f810();               // SP::GetSpaceEconomyTuning()
void* __cdecl FUN_0067dcc0();               // MessageServer() -> global singleton
void  __cdecl FUN_0093aa70(void* stream, const void* src, int count, int a); // EA::IO::WriteUint32
}

// ---------------------------------------------------------------------------
// SP::cCityData -- only the two tallied fields.
// ---------------------------------------------------------------------------
struct cCityData
{
    u8  pad00[0x24];
    int mField24;                                // +0x24
    u8  mFlags;                                  // +0x28
};

// ---------------------------------------------------------------------------
// cVarListSerializer (0xa14 bytes) -- reflection serializer.
// ---------------------------------------------------------------------------
struct cVarListSerializer
{
    u32  mData[0xa14 / 4];                          // +0x000
    void Ctor(void* inst, void* dat, int tag);      // 0x692f90
    char Serialize(void* stream);                   // 0x692900
    int  GetFields(void* fieldVec);                 // 0x695960
};

// ---------------------------------------------------------------------------
// eastl rbtree<u32, Vector3>: header node at +0x04, root at header +0x08.
// ---------------------------------------------------------------------------
struct RBNode
{
    RBNode* mpLeft;      // +0x00
    RBNode* mpRight;     // +0x04
    RBNode* mpParent;    // +0x08
    u8      mColor;      // +0x0c
    u8      pad0d[3];
    int     mKey;        // +0x10
    u32     mValue[3];   // +0x14  (Vector3)
};

struct KeyMap
{
    u32     mField00;                            // +0x00
    RBNode  mHeader;                             // +0x04  (root = mHeader.mpParent)

    u32* Insert(const int* pKey);                // 0xbf3cb0 (ret 4)
    void NukeSubtree(RBNode* pNode);             // 0x9a9600 (ret 4)
};

// ---------------------------------------------------------------------------
// a self-managing begin/end/cap vector (allocator state at +0x0c).
// ---------------------------------------------------------------------------
struct SpVector { void* mBegin; void* mEnd; void* mCap; void* mAlloc; u32 mExtra;
                  void AssignVec(void* other); };   // 0xebf480 (ret 4)

// ---------------------------------------------------------------------------
// SP::cCity -- the members touched here.
// ---------------------------------------------------------------------------
struct cCityData;
struct cCity;

struct CityArray { cCity** mBegin; cCity** mEnd; };  // +0x9c

struct cCity
{
    void*      mpVtbl;                            // +0x00
    u8         pad04[0x40 - 0x04];
    u32        mField40;                          // +0x40
    u8         pad44[0x6c - 0x44];
    KeyMap     mModelMap;                         // +0x6c
    u8         pad90[0x98 - 0x90];
    float      mField98;                          // +0x98
    CityArray  mCities;                           // +0x9c
    u8         padA4[4];
    CityArray* GetCityArray();                    // 0xbef6c0
    int        GetCityCount();                    // 0xbf01e0
};

// ---------------------------------------------------------------------------
// SP::cCitySummary -- 16-slot Vector3 table + owning vectors + tallies.
// ---------------------------------------------------------------------------
struct CitySummary
{
    Vector3*        mEntries;                     // +0x00  (0x10 x 0xc table)
    Vector3*        mEntriesEnd;                  // +0x04
    Vector3*        mEntriesCap;                  // +0x08
    u32             mField0C;                     // +0x0c
    u32             mField10;                     // +0x10
    int             mId;                          // +0x14
    u32             mOwner;                       // +0x18
    float           mRadius;                      // +0x1c
    int             mTallyA;                      // +0x20
    int             mTallyB;                      // +0x24
    SpVector        mV28;                         // +0x28
    SpVector        mV3C;                         // +0x3c

    void ResizeEntries(u32 n);                    // 0x4548d0 (ret 4)
    void AddRecord(cCityData* rec);               // 0x00ff2c70 (ret 4)
};

// ---------------------------------------------------------------------------
// cCityData ctor (other slice, 0x00ff23b0).
// ---------------------------------------------------------------------------
cCityData* __fastcall FUN_00ff23b0(cCityData* pThis, void* edx, cCity* src);

// ---------------------------------------------------------------------------
// SP::cCubeImage -- the cube-face image sampled by the modifier.
// ---------------------------------------------------------------------------
struct cCubeImage
{
    void* mpVtbl;                        // +0x00
    int   mRefCount;                     // +0x04
    int   mSize;                         // +0x08
    u8    pad0c[0x10 - 0x0c];
    u8*   mpData;                        // +0x10
    float SampleBilinear(const CubeSample* pCoord);   // 0xf8de70 (ret 4)
};

// ---------------------------------------------------------------------------
// the cube-image modifier (derived from Audio::IEventModifier).
// ---------------------------------------------------------------------------
struct ImageModifier
{
    void*       mpVtbl0;             // +0x00
    void*       mpVtbl1;             // +0x04
    u32         mField08;            // +0x08
    float       mMinX;               // +0x0c
    float       mMinY;               // +0x10
    float       mMinZ;               // +0x14
    float       mMaxX;               // +0x18
    float       mMaxY;               // +0x1c
    float       mMaxZ;               // +0x20
    u32         mField24;            // +0x24
    cCubeImage* mpImage;             // +0x28
    float       mAdd;                // +0x2c
    float       mScale;              // +0x30
    float       mThreshold;          // +0x34
};

// ---------------------------------------------------------------------------
// shared inventory / tool stubs.
// ---------------------------------------------------------------------------
struct VecPtr { void* mBegin; void* mEnd; void* mCap; void Destroy(); };   // 0x5c7f10

struct ToolObj                                     // ref-counted tool instance
{
    void* mpVtbl;                     // +0x00
    u8    pad04[0x28 - 0x04];
    u8    mb28;                       // +0x28
};

struct ToolInst                                    // cSPToolInstance-like
{
    void* mpVtbl;                     // +0x00
    u8    pad04[0x7c - 0x04];
    int   m7C;                        // +0x7c
    int   GetCount();                 // 0x104c110 (ret 0)
    char  HasFlag();                  // 0x104cbc0 (ret 0)
};

struct InvItem                                     // a sub-object with a +0x0c vtable
{
    void* mpVtbl0;                    // +0x00
    u8    pad04[0x0c - 0x04];
    void* mpVtblC;                    // +0x0c
};

struct Inv
{
    void*   mpVtbl0;                  // +0x00
    void*   mpVtbl1;                  // +0x04
    u8      pad08[0x34 - 0x08];
    VecPtr  m34;                      // +0x34
    u8      pad40[0x4c - 0x40];
    VecPtr  m4C;                      // +0x4c
    u8      pad58[0x60 - 0x58];
    VecPtr  m60;                      // +0x60
    u8      pad6c[0x74 - 0x6c];
    void*   m74;                      // +0x74
    void*   m78;                      // +0x78
    u8      pad7c[0x88 - 0x7c];
    ToolObj* m88;                     // +0x88
    ToolObj* m8c;                     // +0x8c
    ToolObj* m90;                     // +0x90

    char BaseWrite(void* host);       // 0xc874f0 (ret 4)
    void BaseDestroy();               // 0xc87be0 (ret 0)
    void BaseAddCargoSlots(int n);    // 0xc88310 (ret 4)
    void BaseFunc54h();               // 0xc86fe0 (ret 0)
};

struct ToolSet { void* mpVtbl; };     // receiver with vtable slots 0x68 / 0x74
struct Tuning  { int GetMaxCargo(); };// 0x102ff00
struct ToolMgr { void Remove(void* obj); };   // 0x104fc10 (ret 4)
struct StarMgr { int GetTerrainSphere(int flag); };  // 0xba6630 (ret 4)

struct CbObj                                        // object with a scene hook at +0x20
{
    u8    pad00[0x20];
    void* mpFn;                       // +0x20
};

struct MsgServer { void* mpVtbl; };                 // MessageServer instance
struct GameData  { int GetFieldValues(void* host); };// 0xb18420 (ret 4)

// ---------------------------------------------------------------------------
// 0x4548d0 -- SpVector<Vector3>::resize (external; ecx = the vector).
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// 0x00ff3190 -- fill the 16-entry table from a city's model map.
// ---------------------------------------------------------------------------
// @ 0x00ff3190 FUN_00ff3190
__declspec(noinline)
void __fastcall FUN_00ff3190(CitySummary* ecx_this, void* edx, KeyMap* pMap)
{
    ecx_this->ResizeEntries(0x10);

    u32  off  = 0;
    int* pKey = (int*)_sStoredModelKeys;
    do {
        RBNode* pNode  = pMap->mHeader.mpParent;
        int key = *pKey;
        RBNode* pFound = &pMap->mHeader;
        if (pNode != 0) {
            do {
                if (pNode->mKey < key) {
                    pNode = pNode->mpLeft;
                } else {
                    pFound = pNode;
                    pNode  = pNode->mpRight;
                }
            } while (pNode != 0);
            if (pFound != &pMap->mHeader && key >= pFound->mKey) {
                Vector3* pRec = (Vector3*)((char*)ecx_this->mEntries + off);
                pRec->x = pFound->mValue[0];
                pRec->y = pFound->mValue[1];
                pRec->z = pFound->mValue[2];
                ++pKey;
                off += 0xc;
                continue;
            }
        }
        *(u32*)((char*)ecx_this->mEntries + off) = 0xffffffff;
        ++pKey;
        off += 0xc;
    } while (pKey < (int*)_sStoredModelKeys + 16);
}

// ---------------------------------------------------------------------------
// 0x00ff3220 -- cCitySummary(cCity*, const Vec&, const Vec&)
// ---------------------------------------------------------------------------
static __forceinline int PopCount8(u8 b)
{
    u32 v = b;
    v = v - ((v >> 1) & 0x55555555);
    v = ((v >> 2) & 0x33333333) + (v & 0x33333333);
    v = ((v >> 4) + v) & 0x0f0f0f0f;
    return (int)((v * 0x01010101) >> 24);
}

// @ 0x00ff3220 FUN_00ff3220
CitySummary* __fastcall FUN_00ff3220(CitySummary* ecx_this, void* edx, cCity* pCity, void* pV28, void* pV3C)
{
    ecx_this->mEntries = 0;
    ecx_this->mEntriesEnd = 0;
    ecx_this->mEntriesCap = 0;
    ecx_this->mId = -1;
    ecx_this->mOwner = 0x53dbcf2;
    ecx_this->mRadius = 0.0f;
    ecx_this->mV28.mBegin = 0;
    ecx_this->mV28.mEnd = 0;
    ecx_this->mV28.mCap = 0;
    ecx_this->mV3C.mBegin = 0;
    ecx_this->mV3C.mEnd = 0;
    ecx_this->mV3C.mCap = 0;

    if (pCity != 0) {
        FUN_00ff3190(ecx_this, 0, &pCity->mModelMap);
        ecx_this->mId = (int)((u32(__thiscall*)(void*))(*(void***)pCity)[0x4c / 4])(pCity);
        ecx_this->mOwner = pCity->mField40;
        ecx_this->mRadius = pCity->mField98;
        ecx_this->mV28.AssignVec(pV28);
        ecx_this->mV3C.AssignVec(pV3C);

        ecx_this->mTallyB = 0;
        ecx_this->mTallyA = 0;

        int n = (int)(((char*)ecx_this->mV3C.mEnd - (char*)ecx_this->mV3C.mBegin) >> 2);
        for (int i = 0; i < n; ++i) {
            cCityData* rec = ((cCityData**)ecx_this->mV3C.mBegin)[i];
            u8  flags = (u8)(*(u8*)((char*)rec + 0x28));
            int u24   = *(int*)((char*)rec + 0x24);
            ecx_this->mTallyB += u24 - PopCount8(flags);
            ecx_this->mTallyA += PopCount8(flags);
        }
    }
    return ecx_this;
}

// ---------------------------------------------------------------------------
// 0x00ff3360 -- cCitySummary(cCity*)
// ---------------------------------------------------------------------------
// @ 0x00ff3360 FUN_00ff3360
CitySummary* __fastcall FUN_00ff3360(CitySummary* ecx_this, void* edx, cCity* pCity)
{
    ecx_this->mEntries = 0;
    ecx_this->mEntriesEnd = 0;
    ecx_this->mEntriesCap = 0;
    ecx_this->mId = -1;
    ecx_this->mOwner = 0x53dbcf2;
    ecx_this->mRadius = 0.0f;
    ecx_this->mV28.mBegin = 0;
    ecx_this->mV28.mEnd = 0;
    ecx_this->mV28.mCap = 0;
    ecx_this->mV3C.mBegin = 0;
    ecx_this->mV3C.mEnd = 0;
    ecx_this->mV3C.mCap = 0;

    if (pCity == 0) {
        return ecx_this;
    }

    FUN_00ff3190(ecx_this, 0, &pCity->mModelMap);
    ecx_this->mId = (int)((u32(__thiscall*)(void*))(*(void***)pCity)[0x4c / 4])(pCity);
    ecx_this->mOwner = pCity->mField40;
    ecx_this->mRadius = pCity->mField98;
    ecx_this->mTallyB = 0;
    ecx_this->mTallyA = 0;

    CityArray* pArr = pCity->GetCityArray();
    int n = pCity->GetCityCount();
    for (int i = 0; i < n; ++i) {
        cCityData* pNew = (cCityData*)FUN_00f473a0(0xc4, "Simulator", 0, 0, 0, 0);
        if (pNew != 0) {
            pNew = FUN_00ff23b0(pNew, 0, pArr->mBegin[i]);
        }
        ecx_this->AddRecord(pNew);
    }
    return ecx_this;
}

// ---------------------------------------------------------------------------
// 0x00ff3440 -- cCitySummary()  (default)
// ---------------------------------------------------------------------------
// @ 0x00ff3440 FUN_00ff3440
CitySummary* __fastcall FUN_00ff3440(CitySummary* ecx_this)
{
    __m128 z = _mm_setzero_ps();
    ecx_this->mId = -1;
    ecx_this->mOwner = 0x53dbcf2;
    _mm_store_ss((float*)&ecx_this->mRadius, z);
    ecx_this->mEntries = 0;
    ecx_this->mEntriesEnd = 0;
    ecx_this->mEntriesCap = 0;
    ecx_this->mTallyA = 0;
    ecx_this->mTallyB = 0;
    ecx_this->mV28.mBegin = 0;
    ecx_this->mV28.mEnd = 0;
    ecx_this->mV28.mCap = 0;
    ecx_this->mV3C.mBegin = 0;
    ecx_this->mV3C.mEnd = 0;
    ecx_this->mV3C.mCap = 0;

    ecx_this->ResizeEntries(0x10);
    u32 off = 0;
    do {
        *(u32*)((char*)ecx_this->mEntries + off) = 0xffffffff;
        off += 0xc;
    } while (off < 0xc0);

    ecx_this->mId = ((StarMgr*)FUN_00b3d2a0())->GetTerrainSphere(0);
    return ecx_this;
}

// ---------------------------------------------------------------------------
// 0x00ff34c0 -- cCitySummary(float radius)
// ---------------------------------------------------------------------------
// @ 0x00ff34c0 FUN_00ff34c0
CitySummary* __fastcall FUN_00ff34c0(CitySummary* ecx_this, void* edx, float radius)
{
    ecx_this->mId = -1;
    ecx_this->mOwner = 0x53dbcf2;
    _mm_store_ss((float*)&ecx_this->mRadius, _mm_load_ss(&radius));
    ecx_this->mEntries = 0;
    ecx_this->mEntriesEnd = 0;
    ecx_this->mEntriesCap = 0;
    ecx_this->mTallyA = 0;
    ecx_this->mTallyB = 0;
    ecx_this->mV28.mBegin = 0;
    ecx_this->mV28.mEnd = 0;
    ecx_this->mV28.mCap = 0;
    ecx_this->mV3C.mBegin = 0;
    ecx_this->mV3C.mEnd = 0;
    ecx_this->mV3C.mCap = 0;

    ecx_this->ResizeEntries(0x10);
    u32 off = 0;
    do {
        *(u32*)((char*)ecx_this->mEntries + off) = 0xffffffff;
        off += 0xc;
    } while (off < 0xc0);

    ecx_this->mId = ((StarMgr*)FUN_00b3d2a0())->GetTerrainSphere(0);
    return ecx_this;
}

// ---------------------------------------------------------------------------
// 0x00ff3540 -- rebuild the city's model map from the 16-entry table.
// ---------------------------------------------------------------------------
// @ 0x00ff3540 FUN_00ff3540
void __fastcall FUN_00ff3540(CitySummary* ecx_this, void* edx, KeyMap* pMap)
{
    pMap->NukeSubtree(pMap->mHeader.mpParent);
    pMap->mHeader.mpLeft = &pMap->mHeader;
    pMap->mHeader.mpRight = &pMap->mHeader;
    pMap->mHeader.mpParent = 0;
    pMap->mHeader.mColor = 0;
    pMap->mHeader.mKey = 0;

    u32* pKey = _sStoredModelKeys;
    Vector3* pRec = ecx_this->mEntries;
    while (pKey < _sStoredModelKeys + 16) {
        if (pRec->x != 0xffffffff) {
            u32 key = *pKey;
            u32* pVal = pMap->Insert((const int*)&key);
            pVal[0] = pRec->x;
            pVal[1] = pRec->y;
            pVal[2] = pRec->z;
        }
        ++pKey;
        ++pRec;
    }
}

// ---------------------------------------------------------------------------
// 0x00ff35e0 -- accumulate the running u24 tally.
// ---------------------------------------------------------------------------
// @ 0x00ff35e0 FUN_00ff35e0
void __fastcall FUN_00ff35e0(CitySummary* ecx_this, void* edx, int n)
{
    ecx_this->mTallyB += n;
}

// ---------------------------------------------------------------------------
// 0x00ff35f0 -- sample the cube image (bilinear) thresholded.
// ---------------------------------------------------------------------------
// @ 0x00ff35f0 FUN_00ff35f0
float __fastcall FUN_00ff35f0(ImageModifier* ecx_this, void* edx, const float* p)
{
    float x = p[0];
    float y = p[1];
    float z = p[2];
    float ax = (float)fabs(x);
    float ay = (float)fabs(y);
    float az = (float)fabs(z);

    CubeSample c;
    if (az >= ax && az >= ay) {
        c.u = (x / z + 1.0f) * 0.5f;
        c.v = (y / az + 1.0f) * 0.5f;
        c.face = (z < 0.0f) ? 1 : 0;
    } else if (ay >= ax) {
        c.u = (z / y + 1.0f) * 0.5f;
        c.v = (x / ay + 1.0f) * 0.5f;
        c.face = (y < 0.0f) ? 5 : 4;
    } else {
        c.u = (y / x + 1.0f) * 0.5f;
        c.v = (z / ax + 1.0f) * 0.5f;
        c.face = (x < 0.0f) ? 3 : 2;
    }

    float s = ecx_this->mpImage->SampleBilinear(&c);
    if (s * ecx_this->mScale + ecx_this->mAdd >= ecx_this->mThreshold) {
        return 1.0f;
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00ff37c0 -- point-in-box test.
// ---------------------------------------------------------------------------
// @ 0x00ff37c0 FUN_00ff37c0
bool __fastcall FUN_00ff37c0(ImageModifier* ecx_this, void* edx, const float* p)
{
    if ((((ecx_this->mMinX <= p[0]) && (p[0] <= ecx_this->mMaxX)) &&
         ((ecx_this->mMinY <= p[1]) && (p[1] <= ecx_this->mMaxY))) &&
        (((ecx_this->mMinZ <= p[2]) && (p[2] <= ecx_this->mMaxZ)))) {
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00ff3810 -- ImageModifier(cCubeImage*, float, float)
// ---------------------------------------------------------------------------
// @ 0x00ff3810 FUN_00ff3810
ImageModifier* __fastcall FUN_00ff3810(ImageModifier* ecx_this, void* edx, cCubeImage* pImage, float fA, float fB)
{
    ecx_this->mpVtbl1 = (void*)0x13ef094;
    ecx_this->mField08 = 0;
    ecx_this->mMinX = -1000.0f;
    ecx_this->mMinY = -1000.0f;
    ecx_this->mMinZ = -1000.0f;
    ecx_this->mMaxX = 1000.0f;
    ecx_this->mMaxY = 1000.0f;
    ecx_this->mMaxZ = 1000.0f;
    ecx_this->mField24 = 0;
    ecx_this->mpVtbl0 = (void*)0x1494d08;
    ecx_this->mpVtbl1 = (void*)0x1494d04;
    ecx_this->mpImage = pImage;
    if (pImage != 0) {
        ++pImage->mRefCount;
    }
    ecx_this->mAdd = fA;
    ecx_this->mScale = fB - fA;
    return ecx_this;
}

// ---------------------------------------------------------------------------
// 0x00ff38a0 -- ImageModifier destructor.
// ---------------------------------------------------------------------------
// @ 0x00ff38a0 FUN_00ff38a0
void __fastcall FUN_00ff38a0(ImageModifier* ecx_this)
{
    ecx_this->mpVtbl0 = (void*)0x1494d08;
    ecx_this->mpVtbl1 = (void*)0x1494d04;
    _ReadWriteBarrier();
    cCubeImage* pImg = ecx_this->mpImage;
    if (pImg != 0) {
        int rc = pImg->mRefCount;
        pImg->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            pImg->mRefCount = 1;
            _ReadWriteBarrier();
            ((void(__thiscall*)(void*, int))(*(void***)pImg)[0])(pImg, 1);
        }
    }
    ecx_this->mpVtbl0 = (void*)0x1494cd4;
    ecx_this->mpVtbl1 = (void*)0x13ef094;
}

// ---------------------------------------------------------------------------
// 0x00ff38e0 -- nearest-neighbour cube image sample.
// ---------------------------------------------------------------------------
// @ 0x00ff38e0 FUN_00ff38e0
float __fastcall FUN_00ff38e0(ImageModifier* ecx_this, void* edx, const float* p)
{
    float x = p[0];
    float y = p[1];
    float z = p[2];
    cCubeImage* pImg = ecx_this->mpImage;
    int n = pImg->mSize;
    float half = (float)n * 0.5f;
    float ax = (float)fabs(x);
    float ay = (float)fabs(y);
    float az = (float)fabs(z);

    int i;
    int j;
    int face;
    if (az >= ax && az >= ay) {
        i = (int)((x / z + 1.0f) * half);
        j = (int)((y / az + 1.0f) * half);
        face = (z < 0.0f) ? 1 : 0;
    } else if (ay >= ax) {
        i = (int)((z / y + 1.0f) * half);
        j = (int)((x / ay + 1.0f) * half);
        face = (y < 0.0f) ? 5 : 4;
    } else {
        i = (int)((y / x + 1.0f) * half);
        j = (int)((z / ax + 1.0f) * half);
        face = (x < 0.0f) ? 3 : 2;
    }
    if (i == n) --i;
    if (j == n) --j;

    n = pImg->mSize;
    u8 b = pImg->mpData[(n * face + j) * n + i];
    return ((float)b * ecx_this->mScale) * 0.003921569f + ecx_this->mAdd;
}

// ---------------------------------------------------------------------------
// 0x00ff3ab0 -- ImageModifier deleting destructor.
// ---------------------------------------------------------------------------
// @ 0x00ff3ab0 FUN_00ff3ab0
ImageModifier* __fastcall FUN_00ff3ab0(ImageModifier* ecx_this, void* edx, u8 flags)
{
    ecx_this->mpVtbl0 = (void*)0x1494d08;
    ecx_this->mpVtbl1 = (void*)0x1494d04;
    _ReadWriteBarrier();
    cCubeImage* pImg = ecx_this->mpImage;
    if (pImg != 0) {
        int rc = pImg->mRefCount;
        pImg->mRefCount = rc - 1;
        if (rc - 1 == 0) {
            pImg->mRefCount = 1;
            _ReadWriteBarrier();
            ((void(__thiscall*)(void*, int))(*(void***)pImg)[0])(pImg, 1);
        }
    }
    ecx_this->mpVtbl0 = (void*)0x1494cd4;
    ecx_this->mpVtbl1 = (void*)0x13ef094;
    if ((flags & 1) != 0) {
        FUN_00f47380(ecx_this);
    }
    return ecx_this;
}

// ---------------------------------------------------------------------------
// 0x00ff3b30 -- cSpaceInventory::AddCargoSlots override.
// ---------------------------------------------------------------------------
// @ 0x00ff3b30 FUN_00ff3b30
void __fastcall FUN_00ff3b30(Inv* ecx_this, void* edx, int n)
{
    ecx_this->BaseAddCargoSlots(n);
    int count = (int)((u32(__thiscall*)(void*))(*(void***)ecx_this)[0x88 / 4])(ecx_this);
    int local = count;
    MsgServer* ms = (MsgServer*)FUN_0067dcc0();
    ((void(__thiscall*)(void*, u32, void*, int))(*(void***)ms)[0x14 / 4])(ms, 0x5e793b4, &local, 0);
}

// ---------------------------------------------------------------------------
// 0x00ff3b70 -- cSpaceInventory::func54h override.
// ---------------------------------------------------------------------------
// @ 0x00ff3b70 FUN_00ff3b70
void __fastcall FUN_00ff3b70(Inv* ecx_this)
{
    ecx_this->BaseFunc54h();
    void** pVtbl = *(void***)ecx_this;
    Tuning* t = (Tuning*)FUN_0102f810();
    int max = t->GetMaxCargo();
    ((void(__thiscall*)(void*, int))pVtbl[0x58 / 4])(ecx_this, max);
}

// ---------------------------------------------------------------------------
// 0x00ff3bb0 -- has-tool-with-flag test.
// ---------------------------------------------------------------------------
// @ 0x00ff3bb0 FUN_00ff3bb0
int __fastcall FUN_00ff3bb0(ToolSet* ecx_this, void* edx, void* pId)
{
    ToolObj* r = (ToolObj*)((void*(__thiscall*)(void*, void*))(*(void***)ecx_this)[0x68 / 4])(ecx_this, pId);
    if (r != 0 && r->mb28 != 0) {
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00ff3bf0 -- has any of the 11 interstellardrive keys.
// ---------------------------------------------------------------------------
// @ 0x00ff3bf0 FUN_00ff3bf0
bool __fastcall FUN_00ff3bf0(ToolSet* ecx_this)
{
    return ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae04)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae10)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae1c)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae28)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae34)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae40)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae4c)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae58)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae64)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae70)
        || ((char(__thiscall*)(void*, const void*))(*(void***)ecx_this)[0x74 / 4])(ecx_this, (const void*)0x16dae7c);
}

// ---------------------------------------------------------------------------
// 0x00ff3cf0 -- write a global byte through a scene hook.
// ---------------------------------------------------------------------------
// @ 0x00ff3cf0 FUN_00ff3cf0
void __cdecl FUN_00ff3cf0(CbObj* pObj)
{
    char* p = ((char*(__cdecl*)(CbObj*))pObj->mpFn)(pObj);
    *p = g_16daddc;
}

// ---------------------------------------------------------------------------
// 0x00ff3d10 -- is the resource key present?
// ---------------------------------------------------------------------------
// @ 0x00ff3d10 FUN_00ff3d10
bool __fastcall FUN_00ff3d10(Inv* ecx_this, void* edx, const void* pKey)
{
    void* end   = ecx_this->m78;
    void* found = FUN_00ac0d80(ecx_this->m74, end, pKey);
    return found != end;
}

// ---------------------------------------------------------------------------
// 0x00ff3d40 -- cSPPlayerInventory::GetToolFromToolID
// ---------------------------------------------------------------------------
// @ 0x00ff3d40 FUN_00ff3d40
void* __fastcall FUN_00ff3d40(Inv* ecx_this, void* edx, const u32* pId)
{
    for (void** p = (void**)ecx_this->m34.mBegin; p != (void**)ecx_this->m34.mEnd; ++p) {
        InvItem* o = (InvItem*)*p;
        u32* pid = ((u32*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        if (pid[0] == pId[0] && pid[1] == pId[1] && pid[2] == pId[2]) {
            if (o == 0) {
                return 0;
            }
            return ((void*(__thiscall*)(void*, u32))((void**)o->mpVtblC)[0xc / 4])(&o->mpVtblC, 0x707459f0);
        }
    }
    for (void** p = (void**)ecx_this->m4C.mBegin; p != (void**)ecx_this->m4C.mEnd; ++p) {
        InvItem* o = (InvItem*)*p;
        u32* pid = ((u32*(__thiscall*)(void*))(*(void***)o)[0x18 / 4])(o);
        if (pid[0] == pId[0] && pid[1] == pId[1] && pid[2] == pId[2]) {
            if (o == 0) {
                return 0;
            }
            return ((void*(__thiscall*)(void*, u32))((void**)o->mpVtblC)[0xc / 4])(&o->mpVtblC, 0x707459f0);
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00ff3df0 -- initialise each owned tool instance.
// ---------------------------------------------------------------------------
// @ 0x00ff3df0 FUN_00ff3df0
void __fastcall FUN_00ff3df0(Inv* ecx_this)
{
    void** end = (void**)ecx_this->m60.mEnd;
    for (void** p = (void**)ecx_this->m60.mBegin; p != end; ++p) {
        InvItem* o = (InvItem*)*p;
        ToolInst* t = 0;
        if (o != 0) {
            t = (ToolInst*)((void*(__thiscall*)(void*, u32))((void**)o->mpVtblC)[0xc / 4])(&o->mpVtblC, 0x707459f0);
            if (t != 0) {
                ((void(__thiscall*)(void*))(*(void***)t)[0x04 / 4])(t);
            }
        }
        if (t->GetCount() > 0) {
            if (t->HasFlag() != 0) {
                t->m7C = t->GetCount();
            }
            ((void(__thiscall*)(void*, void*, int, int))(*(void***)ecx_this)[0x80 / 4])(ecx_this, t, 0, 1);
        }
        if (t != 0) {
            ((void(__thiscall*)(void*))(*(void***)t)[0x08 / 4])(t);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00ff3e80 -- cSPPlayerInventory::SetActiveTool
// ---------------------------------------------------------------------------
// @ 0x00ff3e80 FUN_00ff3e80
void __fastcall FUN_00ff3e80(Inv* ecx_this)
{
    ToolObj* p = ecx_this->m90;
    if (p != 0) {
        p->mb28 = 0;
        ToolObj* q = ecx_this->m90;
        if (q != 0) {
            ecx_this->m90 = 0;
            ((void(__thiscall*)(void*))(*(void***)q)[0x08 / 4])(q);
        }
    }
    if (ecx_this->m8c != 0) {
        MsgServer* ms = (MsgServer*)FUN_0067dcc0();
        ((void(__thiscall*)(void*, u32, void*, int))(*(void***)ms)[0x14 / 4])(ms, 0x61dae65, ecx_this->m8c, 0);
        ToolObj* q = ecx_this->m8c;
        if (q != 0) {
            ecx_this->m8c = 0;
            ((void(__thiscall*)(void*))(*(void***)q)[0x08 / 4])(q);
        }
        ((ToolMgr*)FUN_00b3d390())->Remove(q);
        q->mb28 = 0;
    }
}

// ---------------------------------------------------------------------------
// 0x00ff3f20 -- cSPPlayerInventory::Write
// ---------------------------------------------------------------------------
// @ 0x00ff3f20 FUN_00ff3f20
bool __fastcall FUN_00ff3f20(Inv* ecx_this, void* edx, void* host)
{
    void* obj = ((void*(__thiscall*)(void*))(*(void***)host)[0x20 / 4])(host);
    void* fn = ((void**)*(void***)obj)[0x18 / 4];
    u32 tag = 0x9073163b;
    void* ch = ((void*(__thiscall*)(void*))fn)(obj);
    FUN_0093aa70(ch, &tag, 1, 0);

    char ok = ecx_this->BaseWrite(host);
    cVarListSerializer ser;
    ser.Ctor(ecx_this, (void*)0x15b5ed8, 0x1a80d26);
    if (ok != 0) {
        if (ser.Serialize(host) != 0) {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00ff3fb0 -- resolve a serialised reference.
// ---------------------------------------------------------------------------
// @ 0x00ff3fb0 FUN_00ff3fb0
u32 __fastcall FUN_00ff3fb0(Inv* ecx_this, void* edx, void* host)
{
    char c = ((char(__thiscall*)(void*))(*(void***)host)[0x20 / 4])(host);
    if (c != 0) {
        return (u32)ecx_this->m88;
    }
    return ((u32(__thiscall*)(void*, u32))(*(void***)((char*)host + 0xc))[0xc / 4])((char*)host + 0xc, 0x707459f0);
}

// ---------------------------------------------------------------------------
// 0x00ff3ff0 -- cSPPlayerInventory destructor.
// ---------------------------------------------------------------------------
// @ 0x00ff3ff0 FUN_00ff3ff0
void __fastcall FUN_00ff3ff0(Inv* ecx_this)
{
    ecx_this->mpVtbl0 = (void*)0x1494d68;
    ecx_this->mpVtbl1 = (void*)0x1494d54;
    _ReadWriteBarrier();
    ToolObj* p;
    p = ecx_this->m90;
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x08 / 4])(p);
    }
    p = ecx_this->m8c;
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x08 / 4])(p);
    }
    p = ecx_this->m88;
    if (p != 0) {
        ((void(__thiscall*)(void*))(*(void***)p)[0x08 / 4])(p);
    }
    void* buf = ecx_this->m74;
    if (buf != 0) {
        if (*(int*)((char*)buf - 4) != 0) {
            FUN_00f47380(buf);
        }
    }
    ecx_this->m60.Destroy();
    ecx_this->m4C.Destroy();
    ecx_this->BaseDestroy();
}

// ---------------------------------------------------------------------------
// 0x00ff4090 -- Simulator::cGameData::WriteAsText
// ---------------------------------------------------------------------------
// @ 0x00ff4090 FUN_00ff4090
int __fastcall FUN_00ff4090(GameData* ecx_this, void* edx, void* host)
{
    int a = ecx_this->GetFieldValues(host);

    cVarListSerializer s1;
    s1.Ctor(ecx_this, (void*)0x1579ed8, 0x1a80d26);
    int b = s1.GetFields(host);
    int ab = a + b;

    cVarListSerializer s2;
    s2.Ctor(ecx_this, (void*)0x15b5ed8, 0x1a80d26);
    int c = s2.GetFields(host);

    return c + ab;
}