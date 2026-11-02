// src/game/SPGonzago/_at_00ff0000.cpp -- migrated from slice(s) s00ff4d50, s00ff3190, s00ff21d0, s00feff80 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00ff0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPVector3.h"
#include "SP/cBuildingData.h"
#include "SP/cCityData.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cSpatialObject.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include "SP/cTribe.h"
#include "SP/cTribeData.h"
#include "SP/cVarListSerializer.h"
#include "SP/cVehicleData.h"
#include <math.h>
#include <intrin.h>
#include <xmmintrin.h>
#include "SP/cCity.h"
#include "SP/cPlayer.h"
#include "SP/cDataSerializationInfo.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPropertyList.h"

// ---- items of slice s00feff80 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace IO {
class IStream_s00fe_ff80;
}
}
namespace SP {
struct Vec3 { float x, y, z; };
}
namespace SP {
struct cInt3 {
    int32_t x;    // +0x00
    int32_t y;    // +0x04
    int32_t z;    // +0x08
};
}
namespace SP {
class cStreamWriter {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual void v5();
    virtual EA::IO::IStream_s00fe_ff80* GetStream();                     // +0x18
};
}
namespace SP {
class cOutStream {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual bool End();                                       // +0x1c
    virtual cStreamWriter* GetWriter();                       // +0x20
};
}
namespace SP {
class cBuildingThing {
public:
    char mPad00[0x30];
    float mField30;           // +0x30
};
}
namespace SP {
class cCityBlock {
public:
    char mPad00[0x3c];
    cBuildingThing** mpThingsBegin;   // +0x3c
    cBuildingThing** mpThingsEnd;     // +0x40
};
}
namespace SP {
class cBuildingData_s00fe_ff80 {
public:
    Vec3 mPosition;           // +0x00
    char mPad0c[0x38 - 0x0c];
};
}
namespace SP {
class cCityData_s00fe_ff80 {
public:
    cInt3    mKey;                     // +0x00
    char     mPad0c[0x10];             // +0x0c
    float    mValue;                   // +0x1c
    int32_t  mField20;                 // +0x20
    int32_t  mNumBuildings;            // +0x24
    uint8_t  mTurretMask;              // +0x28
    char     mPad29[0x07];             // +0x29
    float    mThreatLevel;             // +0x30
    char     mPad34[0x2c];             // +0x34
    uint16_t mName[14];                // +0x60
    cBuildingData_s00fe_ff80* mpBuildingsBegin;   // +0x7c
    cBuildingData_s00fe_ff80* mpBuildingsEnd;     // +0x80
    char     mPad84[0x15c - 0x84];     // +0x84
    cCityBlock** mpBlocksBegin;        // +0x15c
    cCityBlock** mpBlocksEnd;          // +0x160

    bool TestNameBit(int nIndex, uint32_t nBit) const;     // 0x00ff0330
    void AddValue(float fDelta);                           // 0x00ff0350
    int  GetPercent() const;                               // 0x00ff0400
    void SetKey(const cInt3* pKey);                        // 0x00ff0430
    void Write(cOutStream* pStream);                       // 0x00ff0450
    void WriteRaw(cOutStream* pStream);                    // 0x00ff04d0
    int  GetNumTurrets() const;                            // 0x00ff0760
    cBuildingData_s00fe_ff80* GetBuilding(int nIndex);                // 0x00ff07a0
    void RemoveTurret();                                   // 0x00ff07e0
    int  GetNumBuildings() const;                          // 0x00ff0870
    void SetThreatLevel(float fLevel, cCityData_s00fe_ff80* pCity);   // 0x00ff08b0
    void SetAlert(bool bAlert);                            // 0x00b8d980
    bool IsAlerted();                                      // 0x00b8d9a0
};
}
// ---- items of slice s00feff80 end

// ---- items of slice s00ff21d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00f47380(void* p);                     // ??3 operator delete
extern "C" void  __cdecl FUN_0093a780(void* stream, void* dst, int count, int a);  // EA::IO::ReadInt32
#pragma warning(disable : 4100)
typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;
struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };
extern "C" void* __cdecl FUN_00f473a0(u32 size, const char* file, int a, int b, int c, int d);  // EAAllocate
extern u32  g_16dad08;   // 0x016dad08  (float bits)
extern u32  g_16dad0c;   // 0x016dad0c
extern u32  g_16dad10;   // 0x016dad10
struct cVarListSerializer
{
    u32  mData[0x280];                                   // +0x000
    int  mSerializableVarCount;                          // +0xa00
    int  mSerializedVarCount;                            // +0xa04
    u32  mSignature;                                     // +0xa08
    void* mpObject;                                      // +0xa0c
    void* mpSerializerList;                              // +0xa10
    void Ctor(void* inst, void* dat, int tag);           // 0x692f90
    char Serialize(void* stream);                        // 0x693e10
};
struct VectorEC
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Erase();                       // 0x00e25bd0 vector::erase(begin,end) (general)
    void EraseBld();                    // 0x00f28dd0 eastl::vector<cBuildingData>::erase
    void EraseOrn();                    // 0x00ff1840 eastl::vector<cOrnamentData>::erase
    void InsertSlow(void* pos, const void* val);            // 0x00b96600 (ret 8)
    void InsertBld(void* pos, const void* val);             // 0x00ff1650 (ret 8)
    void InsertOrn(void* pos, const void* val);             // 0x00ff18a0 (ret 8)
};
struct HeapNode
{
    int mSizeOrCookie;                  // +0x00 (payload starts at +0x04)
};
struct VecU32
{
    void* mBegin;                       // +0x00
    void* mEnd;                         // +0x04
    void* mCap;                         // +0x08
    void Resize(u32 n);                             // 0x00ff1450 (ret 4)
    void InsertSlow(void* pos, const void* val);    // 0x00ff19c0 (ret 8)
};
struct cCityData
{
    void Destroy();                 // 0x00ff13c0 (thiscall dtor)
    void Init();                    // 0x00ff1cb0 (thiscall ctor helper)
    void ReadFrom(void* stream);    // 0x00ff04d0 (thiscall, ret 4)

    Float3 mPos;                    // 0x00
    Float4 mOri;                    // 0x0c
    float f1c;                      // 0x1c
    u32   u20;                      // 0x20
    u32   u24;                      // 0x24
    u8    mFlags;                   // 0x28
    u8    pad29[0x2c - 0x29];
    u32   u2c;                      // 0x2c
    float f30;                      // 0x30
    u32   u34;                      // 0x34
    u32   u38;                      // 0x38
    float f3c;                      // 0x3c
    u16*  mBeg;                     // 0x40
    u16*  mEnd;                     // 0x44
    u16*  mCap;                     // 0x48
    u32   pad4c;                    // 0x4c
    u16*  m2Beg;                    // 0x50
    u16*  m2End;                    // 0x54
    u16*  m2Cap;                    // 0x58
    u8    pad5c[0x60 - 0x5c];       // 0x5c..0x60
    u16   mSummary[0x0e];           // 0x60 (14 u16 groups for the 196-bitmap)
    VectorEC mBuildings;            // 0x7c (vector of cBuildingData, 0x38 elems)
    u8    pad88[0x90 - 0x88];       // 0x88..0x90
    VectorEC mOrnaments;            // 0x90 (vector of cOrnamentData, 0x34 elems)
    u8    pad9c[0xa4 - 0x9c];       // 0x9c..0xa4
    VectorEC m4;                    // 0xa4 (vector, 0xc-size elems)
    u8    padB0[0xb8 - 0xb0];       // 0xb0..0xb8
    u32   uB8;                      // 0xb8
    u32   uBC;                      // 0xbc
    u32   uC0;                      // 0xc0
};
struct cVehicleData
{
    u32 m00;                        // +0x00
    u32 m04;                        // +0x04
    u32 m08;                        // +0x08
    u32 m0c;                        // +0x0c
    u32 m10;                        // +0x10
};
struct cCitySummary
{
    VectorEC mPacked;               // 0x00  (vector of cCityData*)
    VectorEC mVehicles;             // 0x0c  (vector of cVehicleData*)
    u8       pad18[0x20 - 0x18];
    int      mPackCnt20;            // 0x20  running popcount tally
    int      mPackSum24;            // 0x24  running (u24 - popcount) tally
    VectorEC mCityData;             // 0x28  (vector of cCityData*, owned by l28)
    u8       pad34[0x3c - 0x34];
    VectorEC mBuildingList;         // 0x3c  (vector of cCityData*)
    u32      pad48[0x60 - 0x48];

    // 0x00ff2c70 -- account for one record's bit count into the summary tallies.
    void AddRecord(cCityData* rec);                     // ret 4
    // 0x00ff2d50 -- remove the record at index (frees and pops).
    void RemoveAt(int index);                           // ret 8
    // 0x00ff2d80 -- release all records and both vectors.
    void ResetForward();
    // 0x00ff2e30 -- release everything plus the three owning vectors.
    void Destroy();
};
struct SerObj
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
    void* Channel();                                        // +0x18
};
struct SerHost
{
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    void Close();                                           // +0x1c
    SerObj* Stream();                                       // +0x20
};
// ---- items of slice s00ff21d0 end

// ---- items of slice s00ff3190 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d2a0();               // SP::StarManager() -> global singleton
struct Vector3 { u32 x, y, z; };            // 0xc-byte map value / vector element
struct CubeSample { float u, v; int face; };// argument block for SampleBilinear
extern u32  _sStoredModelKeys[16];          // 0x015b4df8 .. 0x015b4e38
struct cCityData_s00ff_3190
{
    u8  pad00[0x24];
    int mField24;                                // +0x24
    u8  mFlags;                                  // +0x28
};
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
struct SpVector { void* mBegin; void* mEnd; void* mCap; void* mAlloc; u32 mExtra;
                  void AssignVec(void* other); };   // 0xebf480 (ret 4)
struct cCityData_s00ff_3190;
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
    void AddRecord(cCityData_s00ff_3190* rec);               // 0x00ff2c70 (ret 4)
};
cCityData_s00ff_3190* __fastcall FUN_00ff23b0(cCityData_s00ff_3190* pThis, void* edx, cCity* src);
struct cCubeImage
{
    void* mpVtbl;                        // +0x00
    int   mRefCount;                     // +0x04
    int   mSize;                         // +0x08
    u8    pad0c[0x10 - 0x0c];
    u8*   mpData;                        // +0x10
    float SampleBilinear(const CubeSample* pCoord);   // 0xf8de70 (ret 4)
};
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
struct StarMgr { int GetTerrainSphere(int flag); };  // 0xba6630 (ret 4)
__declspec(noinline)
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
// ---- items of slice s00ff3190 end

// ---- items of slice s00ff4d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern int  g_16db738;      // [0x016db738] planet-embassy presence marker
extern void* g_vtbl_cColonySimulator;    // [0x01494ee4]
struct cGonzagoTimer {
    void __thiscall ctor();                    // 0x00b63890
    void __thiscall dtor();                    // 0x00b638b0
    void __thiscall Start();                   // 0x00bc30f0
    void __thiscall Restart();                 // 0x00bc3130
    long long __thiscall GetElapsedTime();     // 0x00bc3190
    char pad[0x40];
};
struct cColonySimulator {
    void* mpVtbl;                            // +0x00
    int   m04;                               // +0x04
    cGonzagoTimer mTimer;                    // +0x08

    cColonySimulator* __thiscall ctor();                       // 0x00ff54e0
    void* __thiscall scalarDeletingDtor(char flags);           // 0x00ff5810
    void __thiscall DoGrowthSim(void* city);                   // 0x00ff5720
    void __thiscall OnTick(int a, int b, int c);               // 0x00ff5840
};
void* __cdecl NounManager();                      // 0x00b3d300  SP::NounManager
struct CNounManagerC {
    void __thiscall RemoveNoun(void* noun);                       // 0x00b225d0
    void* __thiscall GetCurrentTerrainSphere();                   // 0x00f67d90
};
struct CObjB8E7D0 {
    void __thiscall FUN_00b8e7d0(int v);                          // 0x00b8e7d0
};
struct CTerrainSphere {
    void __thiscall RemoveEmbassyFromPlanet(void* planet);        // 0x00c77450
};
struct CGetter10666a0 {
    int __thiscall FUN_01067e60();                                // 0x01067e60
};
struct CToolNoun {
    char pad00[0x64c];
    int  mPlaceRef;                        // +0x64c
};
void* __cdecl FUN_010666a0();                     // 0x010666a0
void  __cdecl FUN_01041c30(void* a, int b);       // 0x01041c30
// ---- items of slice s00ff4d50 end

// @ 0x00ff0330
namespace SP {
bool cCityData_s00fe_ff80::TestNameBit(int nIndex, uint32_t nBit) const
{
    return (mName[nIndex] & (1u << nBit)) != 0;
}
}  // namespace SP

// @ 0x00ff0350
namespace SP {
void cCityData_s00fe_ff80::AddValue(float fDelta)
{
    float fValue = fDelta + mValue;
    mValue = fValue;
    if (fValue < 0.0f)
        mValue = 0.0f;
}
}  // namespace SP

// @ 0x00ff2e30
void __fastcall FUN_00ff2e30(cCitySummary* ecx_this, void* edx)
{
    ecx_this->ResetForward();

    void* v = ecx_this->mBuildingList.mBegin;
    if (v != 0 && ((HeapNode*)v - 1)->mSizeOrCookie != 0) {
        FUN_00f47380(v);
    }
    void* w = ecx_this->mCityData.mBegin;
    if (w != 0 && ((HeapNode*)w - 1)->mSizeOrCookie != 0) {
        FUN_00f47380(w);
    }
    void* u = ecx_this->mPacked.mBegin;
    if (u != 0 && ((HeapNode*)u - 1)->mSizeOrCookie != 0) {
        FUN_00f47380(u);
    }
}

// @ 0x00ff2e80
void __fastcall FUN_00ff2e80(cCitySummary* ecx_this, void* edx, void* stream)
{
    cVarListSerializer ser;
    ser.Ctor(ecx_this, (void*)0x015b59c0, 0x1a80d26);

    SerObj* s = ((SerHost*)stream)->Stream();
    void* str = s->Channel();
    u32 count = 0;
    FUN_0093a780(str, &count, 1, 0);

    for (u32 i = 0; i < count; ++i) {
        cCityData* rec = (cCityData*)FUN_00f473a0(0xc4, "Simulator/cCityData", 0, 0, 0, 0);
        if (rec != 0) {
            rec->Init();
        } else {
            rec = 0;
        }
        rec->ReadFrom(stream);
        VectorEC* v = &ecx_this->mBuildingList;
        cCityData** pos = (cCityData**)v->mEnd;
        if (pos < (cCityData**)v->mCap) {
            v->mEnd = (char*)pos + 4;
            if (pos != 0) {
                *pos = rec;
            }
        } else {
            v->InsertSlow(pos, &rec);
        }
    }

    SerObj* s2 = ((SerHost*)stream)->Stream();
    void* str2 = s2->Channel();
    u32 count2 = 0;
    FUN_0093a780(str2, &count2, 1, 0);

    for (u32 i = 0; i < count2; ++i) {
        cVehicleData* rec = (cVehicleData*)FUN_00f473a0(0x14, "Simulator/cVehicleData", 0, 0, 0, 0);
        void* pv = 0;
        if (rec != 0) {
            rec->m00 = g_16dad08;
            rec->m04 = g_16dad0c;
            rec->m08 = g_16dad10;
            rec->m0c = 0;
            rec->m10 = 0xffffffff;
            pv = rec;
        }
        cVarListSerializer ser2;
        ser2.Ctor(pv, (void*)0x015b4f28, 0x1a80d26);
        ser2.Serialize(stream);
        VectorEC* v = &ecx_this->mCityData;
        void** pos = (void**)v->mEnd;
        if (pos < (void**)v->mCap) {
            v->mEnd = (char*)pos + 4;
            if (pos != 0) {
                *pos = pv;
            }
        } else {
            v->InsertSlow(pos, &pv);
        }
    }

    int n = (int)(((long long)((int)ecx_this->mPacked.mEnd - (int)ecx_this->mPacked.mBegin) * -0x2aaaaaab) >> 32);
    ecx_this->mPacked.mEnd = (void*)((int)ecx_this->mPacked.mEnd + ((n >> 1) - (n >> 31)) * 0xc);

    ser.Serialize(stream);
}

// @ 0x00ff3090
void __cdecl FUN_00ff3090(SerHost* host, VecU32* vec)
{
    u32* it = (u32*)vec->mBegin;
    u32* end = (u32*)vec->mEnd;
    u32* d = it;
    while (it != end) {
        *d++ = *it++;
    }
    vec->mEnd = (char*)vec->mEnd + -(((int)((char*)end - (char*)vec->mBegin) >> 2) * 4);

    SerObj* s = host->Stream();
    void* str = s->Channel();
    u32 count = 0;
    FUN_0093a780(str, &count, 1, 0);
    vec->Resize(count);

    for (u32 i = 0; i < count; ++i) {
        u32 val = 0;
        cVarListSerializer ser;
        ser.Ctor((void*)0x015b5458, &val, 0x1a80d26);
        ser.Serialize(host);
        u32* pos = (u32*)vec->mEnd;
        if ((char*)pos < (char*)vec->mCap) {
            vec->mEnd = (char*)pos + 4;
            if (pos != 0) {
                *pos = val;
            }
        } else {
            vec->InsertSlow(pos, &val);
        }
    }

    host->Close();
}

// @ 0x00ff3190
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

// @ 0x00ff3220
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
            cCityData_s00ff_3190* rec = ((cCityData_s00ff_3190**)ecx_this->mV3C.mBegin)[i];
            u8  flags = (u8)(*(u8*)((char*)rec + 0x28));
            int u24   = *(int*)((char*)rec + 0x24);
            ecx_this->mTallyB += u24 - PopCount8(flags);
            ecx_this->mTallyA += PopCount8(flags);
        }
    }
    return ecx_this;
}

// @ 0x00ff3360
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
        cCityData_s00ff_3190* pNew = (cCityData_s00ff_3190*)FUN_00f473a0(0xc4, "Simulator", 0, 0, 0, 0);
        if (pNew != 0) {
            pNew = FUN_00ff23b0(pNew, 0, pArr->mBegin[i]);
        }
        ecx_this->AddRecord(pNew);
    }
    return ecx_this;
}

// @ 0x00ff3440
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

// @ 0x00ff34c0
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

// @ 0x00ff3540
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

// @ 0x00ff35e0
void __fastcall FUN_00ff35e0(CitySummary* ecx_this, void* edx, int n)
{
    ecx_this->mTallyB += n;
}

// @ 0x00ff35f0
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

// @ 0x00ff3810
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

// @ 0x00ff38a0
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

// @ 0x00ff38e0
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

// @ 0x00ff3ab0
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

// @ 0x00ff53f0
int __cdecl FUN_00ff53f0(int param_1)
{
    param_1 = param_1 * 5;
    if (param_1 > 100)
        param_1 = 100;
    return param_1;
}

// @ 0x00ff54e0
cColonySimulator* __thiscall cColonySimulator::ctor()
{
    m04 = 0;
    mpVtbl = &g_vtbl_cColonySimulator;
    mTimer.ctor();
    mTimer.Start();
    return this;
}

// @ 0x00ff5a10
void __cdecl FUN_00ff5a10(void* param_1, void* param_2)
{
    ((CNounManagerC*)NounManager())->RemoveNoun(param_1);
    ((CObjB8E7D0*)param_2)->FUN_00b8e7d0(((CToolNoun*)param_1)->mPlaceRef);
    if (((CToolNoun*)param_1)->mPlaceRef == g_16db738) {
        ((CTerrainSphere*)((CNounManagerC*)NounManager())->GetCurrentTerrainSphere())
            ->RemoveEmbassyFromPlanet(param_2);
    }
    CGetter10666a0* g = (CGetter10666a0*)FUN_010666a0();
    FUN_01041c30(param_1, g->FUN_01067e60());
}
