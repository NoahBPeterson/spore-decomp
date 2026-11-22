// src/game/SPGonzago/SPCommunity.cpp -- migrated from slice(s) s013329c0, s00c01310, s00c011c0, s00c00b00, s00c015e0, s00bffad0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCommunity.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1570f10[];
extern "C" char g_1571000[];

#include "game/types.h"
#include "SP/cLaneInfo.h"
#include "cSPVector3.h"
#include "SP/cActionCircle.h"
#include "SP/cCity.h"
#include "SP/cCommunity.h"
#include "SP/cEmptyBubble.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <stdlib.h>
#include <new>
#include "SP/cSPTimer.h"
#include <intrin.h>
#include "SP/cGameData.h"
#include "SP/cISPEditorNameProvider.h"
#include <intrin.h>   // _ReadWriteBarrier (scheduling barrier, emits no code)
#include <float.h>

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_168d228[8];           // 0x0168d228  cached four-byte ids, seven entries used
extern "C" void EA_IO_WriteUint32(void* stream, const uint32_t& value, int count, int flags); // 0x0093aa70
extern char DAT_015710b8;               // 0x015710b8  cVarList descriptor passed to the serializer

// ---- items of slice s00bffad0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VT(obj, off) ((*(void***)(obj))[(off) / 4])
typedef bool     (__thiscall *FnBool)(void*);
typedef void     (__thiscall *FnVoid_Rel)(void*);
void* SP_PropertyManager();             // 0x0067de30
typedef void* (__thiscall *FnVp)(void*);
typedef bool  (__thiscall *FnBool2)(void*, uint32_t, void**);
typedef bool  (__thiscall *FnGetProps)(void*, uint32_t, int, void**);
struct cProperty {
    uint8_t  mPad0[0xc];                // +0 is the vtable pointer
    uint16_t mFlags;                    // 0x10
    uint16_t mType;                     // 0x12
    virtual int AddRef();
    virtual int Release();              // vtable slot 1 (+4)
    const char* GetString8();           // 0x0041e990
};
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    void Reset() { if (mp) { T* p = mp; mp = 0; p->Release(); } }
    void** AsPPTypeParam() { Reset(); return (void**)&mp; }
    ~AutoRef() { if (mp) mp->Release(); }
};
struct CommunityStreamHolder {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
    virtual void* GetStream(); // +0x18
};
struct CommunityOutputStream {
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
    virtual CommunityStreamHolder* GetStreamHolder(); // +0x20
};
struct Elem20 {
    float f0, f1, f2, f3, f4, f5, f6;
    uint32_t u;
};
// ---- items of slice s00bffad0 end

// ---- items of slice s00c015e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct PointVec {
    Vec3* mpBegin; Vec3* mpEnd; Vec3* mpCap;
    PointVec() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    ~PointVec() { if (mpBegin) free(mpBegin); }
};
struct Zone {
    uint32_t pad[0x258 / 4];
    float rMin;     // +0x258
    float rMax;     // +0x25c
    void FillPoints(PointVec* v);
};
struct IRefCounted {                  // vtable: +0x00 v0, +0x04 Release
    virtual void v0();
    virtual void Release();
};
struct IntIdxVec {                    // eastl::vector<unsigned int>
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    void DoInsertValueI(int* pos, const int& value);            // 0x004558a0
};
struct SpatialRefVec {                // vector<AutoRefCount<cSpatialObject>>
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void erase(void* first, void* last);                        // 0x00b48e40
};
struct LogReporterRefVec {            // vector<AutoRefCount<ILogReporter>>
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
    void erase(void* first, void* last);                        // 0x00e25bd0
};
struct ILaneObject {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
    virtual Zone* GetZone();                                   // slot 27 (+0x6c)
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
    virtual void v32();                                        // slot 32 (+0x80)
    virtual void v33();
    virtual void v34();                                        // slot 34 (+0x88)

    uint32_t pad04[(0x2c - 0x04) / 4];                         // +0x04
    IRefCounted* mpAt2c;                                       // +0x2c
    uint32_t pad30[(0x50 - 0x30) / 4];                         // +0x30
    float mInnerRadius;                                        // +0x50  zone rMin
    float mOuterRadius;                                        // +0x54  zone rMax
    uint32_t pad58[(0x6c - 0x58) / 4];                         // +0x58
    uint8_t mZoneValid;                                        // +0x6c
    uint32_t pad70[(0xd0 - 0x70) / 4];                         // +0x70
    SpatialRefVec mObjects;                                    // +0xd0
    uint32_t padDc[(0xe4 - 0xdc) / 4];                         // +0xdc
    LogReporterRefVec mReporters;                              // +0xe4
    uint32_t padF0[(0x11c - 0xf0) / 4];                        // +0xf0
    IRefCounted* mpAt11c;                                      // +0x11c

    void FUN_00c014c0();                                       // 0x00c014c0
    void UpdateZone(bool force);                               // 0x00c01e20
    void ClearLanes();                                         // 0x00c01e80
};
struct IStreamHolder {                // object returned by ISerializable::Open()
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void* GetStream();                                 // slot 6 (+0x18)
};
struct ISerializableObject {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
    virtual void Close();                                      // slot 7 (+0x1c)
    virtual IStreamHolder* Open();                             // slot 8 (+0x20)
};
void ReadInt32(void* stream, uint32_t* value, int count, int flags);  // 0x0093a780
void FreeAllocBlock(void* block);                                     // 0x00f47380
void* EAAllocate(unsigned int size, const char* name, int a, int b,
                 const char* file, int line);                         // 0x00f473a0
struct cVarListSerializer_s00c0_15e0 {
    uint8_t mStorage[0xa14];
    void Construct(void* record, uint32_t key, uint32_t type);  // 0x00692f90
    void Serialize(void* object);                               // 0x00693e10
};
struct cEmptyBubble {
    float mX, mY, mZ, mW;
    uint32_t mFlags;
};
struct EmptyBubbleVec {
    cEmptyBubble* mpBegin;
    cEmptyBubble* mpEnd;
    cEmptyBubble* mpCap;
    void Reserve(int n);                                              // 0x00c00fb0
    void DoInsertValue(cEmptyBubble* pos, const cEmptyBubble* value); // 0x00bde910
};
cEmptyBubble* CopyBubbleRange(cEmptyBubble* first, cEmptyBubble* last,
                              cEmptyBubble* dst);                     // 0x00951bf0
struct LanePayload;
struct LaneRec {
    Vec3 mPos;                 // +0x00
    union {
        Vec3      mDir;        // +0x0c  lane point
        IntIdxVec mNext;       // +0x0c  lane-graph node
    };
    float mRadius;             // +0x18
    int   mIndex;              // +0x1c

    void Construct(const LanePayload* src);                            // 0x00be0d70
};
struct AllocBlockHeader {
    uint32_t mRefCount;
};
struct LanePayload {
    Vec3          mPos;        // +0x00  written by the serializer
    IRefCounted*  mpData;      // +0x0c
    uint32_t      mPad10[2];   // +0x10
    uint32_t      mPad18[2];   // +0x18
};
struct LaneRecVec {
    LaneRec* mpBegin;
    LaneRec* mpEnd;
    LaneRec* mpCap;
    LaneRec* end() const { return mpEnd; }
    void ReservePoints(int n);                                    // 0x00c00f20
    void ReserveNodes(int n);                                     // 0x00c01ef0
    void DoInsertPoint(LaneRec* pos, const LaneRec* value);       // 0x00c01060
    void DoInsertNode(LaneRec* pos, const LanePayload* value);    // 0x00be7aa0
    void DoInsertNodeRec(LaneRec* pos, const LaneRec* value);     // 0x00be7aa0
    void DoDestroy(LaneRec* first, LaneRec* last);                // 0x00bdc770
};
LaneRec* CopyLaneRange(LaneRec* first, LaneRec* last, LaneRec* dst);  // 0x00be0e80
struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
};
struct ILaneZone {
    bool Contains(const Vec3* point);                     // 0x00bec0f0
};
struct ILaneSource {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
virtual void s06();
virtual void s07();
virtual void s08();
virtual void s09();
virtual void s10();
    virtual Vec3* GetPosition();                          // slot 11 (+0x2c)
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual Vec3* GetFacing(Vec3* out);                   // slot 23 (+0x5c)
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                            // slot 29 (+0x74)
};
struct cCityHall {
    void UpdateFromSubobject(const Vec3* pos, float* value);   // 0x00bcdd00
};
struct cCity {
    cCityHall* GetCityHall();                                  // 0x00bd9b40
    cCityHall* GetCityHall(Vec3* pos, float* radius);          // 0x00bd9b40
};
void PlanetModel();                                            // 0x00b3d350
struct CircleSpoke {
    uint32_t mPad[3];
    Vec3     mDir;              // +0x0c
};
struct cActionCircle {
    uint32_t pad00[(0x50) / 4];
    CircleSpoke* mpSpokes;      // +0x50
    cActionCircle();                                           // 0x00afba10
    ~cActionCircle();                                          // 0x00afbad0
    void SetAtCenter(const Vec3* center, float radius, const Vec3* facing,
                     float altitude);                          // 0x00af9cf0
    void FUN_00afd6d0(float a, float b, int count);            // 0x00afd6d0
};
static const float kLaneLinkDistance = 6.0f;
struct cCommunity {
virtual void v00();
virtual void v01();
virtual void v02();
    virtual void* Cast(uint32_t typeId);                       // slot 3  (+0x0c)
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
    virtual Vec3* GetPosition(Vec3* out);                      // slot 22 (+0x58)
virtual void v23();
virtual void v24();
virtual void v25();
    virtual void* GetSourceList();                             // slot 26 (+0x68)
    virtual void* GetLaneZone();                               // slot 27 (+0x6c)

    uint32_t pad04[(0x84 - 0x04) / 4];
    LaneRecVec mOut;                                           // +0x84

    void UpdateLanes();                                        // 0x00c01f90
};
// ---- items of slice s00c015e0 end

// ---- items of slice s00c00b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_Milli;   // 0x013f9428  0.001f (ticks -> seconds)
extern const float g_Sixty;   // 0x013ebc4c  60.0f
extern const float g_One;     // 0x01485720  1.0f
extern "C" char g_13eb90c[];  // 0x013eb90c  vtbl_UI::BehaviorMessage (symbols/vtable_names.txt)
extern "C" char g_13eb844[];  // 0x013eb844
extern "C" char g_1469ca8[];  // 0x01469ca8  (s00c011c0's constructor installs g_1469cc0/g_1469cd8 next to it)
typedef unsigned int u32;
typedef unsigned __int64 u64;
u32  SP_GetCurrentGameMode();                        // 0x00b5b800
void* SP_GetServer();                                // 0x00883860 EA::Messaging::GetServer
void* SP_NounManager();                              // 0x00b3d300
void* SP_GameTimeManager();                          // 0x00b3d380
void* SP_GetActivePlanetRecord();                    // 0x010212a0
void* SP_GetSpaceCombatTuning();                     // 0x01029940
void* SP_ConfigManager();                            // 0x0067dd30
void* SP_GetAudioSystem();                           // 0x00a206f0
u32   FNV1_String16(const wchar_t*, u32, int);       // 0x00932f30
void  FUN_00435ed0(u32, u32);                        // 0x00435ed0 (audio event post)
u32   FUN_00435e90();                                // 0x00435e90
void  FUN_0040cf10(void* mgr, u32 id, float* out);   // 0x0040cf10 GetPropertyT
void* FUN_00ac86d0(void*);                           // 0x00ac86d0
void* FUN_00b3d4d0();                                // 0x00b3d4d0 (message manager)
struct Vec4 {
    float x, y, z, w;
    Vec4(float fx, float fy, float fz, float fw) { x = fx; y = fy; z = fz; w = fw; }
};
void* FUN_00cf74c0();                                // 0x00cf74c0 cCivModeStrategy::Get()
void  FUN_00cf9040();                                // 0x00cf9040, thiscall warning on the strategy
void  FUN_00ae09b0();                                // 0x00ae09b0, thiscall send
void  FUN_00ae0930();                                // 0x00ae0930, thiscall send
void  FUN_00ad7a30();                                // 0x00ad7a30, thiscall ctor
void  FUN_00ad7ad0();                                // 0x00ad7ad0, thiscall dtor
void FUN_00b316c0();   // GameTimeManager::Ticks -> u64
void FUN_00b1f9d0();   // noun manager -> player civilization
void FUN_00b25f40();   // noun manager -> noun for an id
void FUN_00b25fb0();   // noun manager -> player civilization noun
void FUN_00b8dab0();   // active planet record -> type
void FUN_00f67d90();   // noun manager -> terrain object
void FUN_00bd9b40();   // cCity::GetCityHall
void FUN_00c772c0();   // bool (terrain object, id)
void FUN_00c77bf0();   // void (terrain object, id)
bool FUN_00c004c0();                                               // 0x00c004c0
#define VTABLE(obj)         (*(void***)(obj))
#define VSLOT(obj, off)     (VTABLE(obj)[(off) / 4])
struct SlotMessage {
    void** vtbl;                    // +0x00
    u32    mRefCount;               // +0x04
    void*  mpObject;                // +0x08
    u32    m0c;                     // +0x0c
    u32    m10;                     // +0x10
    u32    m14;                     // +0x14
    u32    m18;                     // +0x18
    u32    m1c;                     // +0x1c
    u32    m20;                     // +0x20
    u32    m24;                     // +0x24
    u32    m28;                     // +0x28
    u32    m2c;                     // +0x2c
    u32    mKind;                   // +0x30
    u32    m34;                     // +0x34
    u32    m38;                     // +0x38
    u32    m3c;                     // +0x3c
    void Destruct();                // 0x00421cf0
};
namespace SP {
struct cSPTimer_s00c0_0b00 {
    unsigned char mData[0x20];
    void Restart();                          // 0x00bc3130
    u64  GetElapsedTime() const;             // 0x00bc3190
};
}
namespace SP {
struct Marker {
    float v[3];
};
}
namespace SP {
class cCommunity_s00c0_0b00 {
 public:
    enum eAttackTrackingType {
        kMilitaryAttack = 0,
        kCulturalAttack = 1,
        kDiplomaticAttack = 2,
        kAttackTypeCount = 3,
    };
    enum eCommunityMessages {
        kUnderAttack = 51027995,             // 0x030aa01b
    };

    void NotifyAttack(eAttackTrackingType, unsigned int);  // 0x00c00b00 (SP::cCommunity::NotifyAttack)

    unsigned char mPad0[0x98];
    u64   mLastAttack[3];                    // 0x98
    cSPTimer_s00c0_0b00 mPlayerWarningTimer;            // 0xb0
};
}
using SP::cCommunity_s00c0_0b00;
// ---- items of slice s00c00b00 end

// ---- items of slice s00c011c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_13ef63c[];
extern "C" char g_1469cc0[];
extern "C" char g_1469cd8[];
extern "C" char g_1469ce8[];
extern "C" char g_1667bac[];
extern "C" char g_1667bae[];
#pragma pack(push, 4)
#pragma pack(pop)
struct cGameData {
    void* mpVtbl0;                                           // +0x000
    void* mpVtbl1;                                           // +0x004
    unsigned char mRaw008[0x34 - 0x08];                      // +0x008..+0x033
    cGameData();                                             // 0x00b18660
};
struct cISPEditorNameProvider {
    void* mpVtbl;                                            // +0x034
};
struct cVector {
    void*          mpBegin;                                  // +0x00
    void*          mpEnd;                                    // +0x04
    void*          mpCapacity;                               // +0x08
    unsigned char  mAllocator[8];                            // +0x0c
};
struct cStr16 {
    void*          mpBegin;                                  // +0x00
    void*          mpEnd;                                    // +0x04
    void*          mpCapacity;                               // +0x08
    unsigned char  mAllocator[4];                            // +0x0c
};
struct cTimer {
    unsigned char mRaw[0x20];
    void Construct();
    void Restart();
};
struct cCommunity_s00c0_11c0 : cGameData, cISPEditorNameProvider {
    int            mCommunitySize;                           // +0x038
    cVector        mStructureLines;                          // +0x03c
    float          mInnerWallRadius;                         // +0x050
    float          mOuterWallRadius;                         // +0x054
    cVector        mGateInfo;                                // +0x058
    bool           mbNeedsNavigationUpdate;                  // +0x06c
    unsigned char  mPad06d[3];                               // +0x06d
    cVector        mAssemblyBubbles;                         // +0x070
    cVector        mLanes;                                   // +0x084
    unsigned __int64 mLastAttack[3];                         // +0x098
    cTimer         mPlayerWarningTimer;                      // +0x0b0
    cVector        mStructures;                              // +0x0d0
    cVector        mInhabitants;                             // +0x0e4
    cStr16         mName;                                    // +0x0f8
    cStr16         mDescription;                             // +0x108
    unsigned int   mGODPoliticalID;                          // +0x118
    void*          mpLeader;                                 // +0x11c

    cCommunity_s00c0_11c0();
};
// ---- items of slice s00c011c0 end

// ---- items of slice s00c01310 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Elem20_s00c0_1310 { char mBytes[20]; };
void MoveRange(Elem20_s00c0_1310* first, Elem20_s00c0_1310* last, Elem20_s00c0_1310* dest); // 0x00951bf0
struct Vec20 {
    char mPad00[0x70];
    Elem20_s00c0_1310* mpBegin; // +0x70
    Elem20_s00c0_1310* mpEnd;   // +0x74
    void FUN_00c01310();
};
// ---- items of slice s00c01310 end

// ---- items of slice s013329c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0133_29c0; 
}
typedef eastl::string8_s0133_29c0 string8_s0133_29c0;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0133_29c0&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
void* StaticOffset(Attribute* pAttr);    // 0x011874d0: (void*)pAttr->offset (class statics)
}
namespace Simulator {
struct Attribute
{
    // Member attribute: offset is relative to the current object.
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    // Static attribute: the offset field holds the static's address; no ToXml callback.
    Attribute(const char* pName, uint32_t nID, void* pStatic,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = 0;
        offsetFunction = StaticOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = 0;
        offset = (uint32_t)pStatic;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
#define DECL_FAMILY(S) \
    void WriteText_00694fc0_##S(char* pBuffer, void* pData);                 /* 0x00694fc0 */ \
    bool Write_00572840_##S(ISerializerWriteStream* pStream, void* pData);   /* 0x00572840 */ \
    void ReadText_006930b0_##S(const string8_s0133_29c0& text, void* pData);            /* 0x006930b0 */ \
    void ReadText_00693090_##S(const string8_s0133_29c0& text, void* pData);            /* 0x00693090 */ \
    bool Write_00ac88f0_##S(ISerializerWriteStream* pStream, void* pData);   /* 0x00ac88f0 */ \
    void ReadText_00692ff0_##S(const string8_s0133_29c0& text, void* pData);            /* 0x00692ff0 */ \
    bool Read_00572810_##S(ISerializerReadStream* pStream, void* pData);     /* 0x00572810 */ \
    void WriteText_00694f00_##S(char* pBuffer, void* pData);                 /* 0x00694f00 */ \
    bool Validate_00b1fbf0_##S();                                            /* 0x00b1fbf0 */ \
    bool ToXml_00675ca0_##S(void* pData, const char* pName, int depth);      /* 0x00675ca0 */ \
    bool ToXml_00acbb80_##S(void* pData, const char* pName, int depth);      /* 0x00acbb80 */
}
namespace Simulator {
DECL_FAMILY(s)
}
namespace Simulator {
DECL_FAMILY(r0) DECL_FAMILY(r1) DECL_FAMILY(r2) DECL_FAMILY(r3) DECL_FAMILY(r4)
}
namespace Simulator {
DECL_FAMILY(r5) DECL_FAMILY(r6) DECL_FAMILY(r7) DECL_FAMILY(r8) DECL_FAMILY(r9)
}
namespace Simulator {
DECL_FAMILY(r10) DECL_FAMILY(r11) DECL_FAMILY(r12) DECL_FAMILY(r13) DECL_FAMILY(r14)
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0133_29c0& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool Read_00c01ce0(ISerializerReadStream* pStream, void* pData);      // 0x00c01ce0
}
namespace Simulator {
bool Write_00c006a0(ISerializerWriteStream* pStream, void* pData);    // 0x00c006a0
}
namespace Simulator {
bool Validate_00c00740();                                             // 0x00c00740
}
namespace Simulator {
bool ToXml_00c51440(void* pData, const char* pName, int depth);       // 0x00c51440
}
namespace Simulator {
bool Read_00c024f0(ISerializerReadStream* pStream, void* pData);      // 0x00c024f0
}
namespace Simulator {
bool Write_00c00780(ISerializerWriteStream* pStream, void* pData);    // 0x00c00780
}
namespace Simulator {
bool Validate_00c00810();                                             // 0x00c00810
}
namespace Simulator {
bool ToXml_00f29650(void* pData, const char* pName, int depth);       // 0x00f29650
}
namespace Simulator {
bool Read_00ac87c0(ISerializerReadStream* pStream, void* pData);      // 0x00ac87c0
}
namespace Simulator {
bool Write_00ac87f0(ISerializerWriteStream* pStream, void* pData);    // 0x00ac87f0
}
namespace Simulator {
void ReadText_00694c80(const string8_s0133_29c0& text, void* pData);             // 0x00694c80
}
namespace Simulator {
void WriteText_00694c10(char* pBuffer, void* pData);                  // 0x00694c10
}
namespace Simulator {
bool ToXml_00acbbc0(void* pData, const char* pName, int depth);       // 0x00acbbc0
}
namespace Simulator {
bool Read_00b02540(ISerializerReadStream* pStream, void* pData);      // 0x00b02540
}
namespace Simulator {
struct AttrSlot { uint32_t d[15]; };
}
namespace Simulator {
extern AttrSlot cCommunity_sAttributes[6];        // 0x015710b8
}
namespace Simulator {
#define ADD_TO(TABLE, IDX, ...) { Attribute a(__VA_ARGS__); *(Attribute*)&TABLE[IDX] = a; }
}
// ---- items of slice s013329c0 end

// @ 0x00c00590
int __fastcall FUN_00c00590(void* ecx_this, void* edx)
{
    int* v = (int*)((FnVp)VT(ecx_this, 0x70))(ecx_this);
    return (v[1] - v[0]) >> 2;
}

// @ 0x00c005b0
void __fastcall FUN_00c005b0(void* ecx_this, void* edx, void* stream)
{
    CommunityStreamHolder* __restrict holder =
        static_cast<CommunityOutputStream*>(stream)->GetStreamHolder();
    uint32_t tag = 0x17f243b;
    void* io = holder->GetStream();
    EA_IO_WriteUint32(io, tag, 1, 0);

    void* p = *(void**)((char*)ecx_this + 0x11c);
    if (p != 0 && ((FnBool)VT(p, 0x2c))(p)) {
        p = *(void**)((char*)ecx_this + 0x11c);
        if (p != 0) {
            *(void**)((char*)ecx_this + 0x11c) = 0;
            ((FnVoid_Rel)VT(p, 4))(p);
        }
    }

    SP::cVarListSerializer ser(ecx_this,
        reinterpret_cast<SP::cDataSerializerGeneric*>(&DAT_015710b8),
        SP::cVarListSerializer::kSignature);
    ser.Serialize(*static_cast<SP::cIObjectDatabaseOStream*>(stream));
}

// @ 0x00c00850
void FUN_00c00850(Elem20* first, Elem20* last, Elem20* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst) {
            dst->f0 = first->f0;
            dst->f1 = first->f1;
            dst->f2 = first->f2;
            dst->f3 = first->f3;
            dst->f4 = first->f4;
            dst->f5 = first->f5;
            dst->f6 = first->f6;
            dst->u = first->u;
        }
    }
}

// @ 0x00c008c0
void FUN_00c008c0(uint32_t* out)
{
    void* val;
    if (out[0] != 0) {
        return;
    }
    AutoRef<cProperty> prop;
    void* pm = SP_PropertyManager();
    if (((FnGetProps)VT(pm, 0x2c))(pm, 0x16d4dff8, 0, prop.AsPPTypeParam())) {
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e43, &val) &&
            ((cProperty*)val)->mType == 9)
            out[0] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e44, &val) &&
            ((cProperty*)val)->mType == 9)
            out[1] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e45, &val) &&
            ((cProperty*)val)->mType == 9)
            out[2] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e46, &val) &&
            ((cProperty*)val)->mType == 9)
            out[3] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e47, &val) &&
            ((cProperty*)val)->mType == 9)
            out[4] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e48, &val) &&
            ((cProperty*)val)->mType == 9)
            out[5] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e49, &val) &&
            ((cProperty*)val)->mType == 9)
            out[6] = *(const uint32_t*)((cProperty*)val)->GetString8();
    }
}

// @ 0x00c00aa0
int FUN_00c00aa0(int value)
{
    FUN_00c008c0(g_168d228);
    for (int i = 0; i < 7; ++i) {
        if (value <= (int)g_168d228[i]) {
            return i;
        }
    }
    return 0;
}

// @ 0x00c00ad0
uint32_t FUN_00c00ad0(int index)
{
    if (index < 8) {
        FUN_00c008c0(g_168d228);
        return g_168d228[index];
    }
    return 0;
}

// @ 0x00c00b00
void SP::cCommunity_s00c0_0b00::NotifyAttack(eAttackTrackingType type, unsigned int attackerId)
{
    unsigned char* const self = (unsigned char*)this;

    // The slot message and the later city-hall marker share one stack slot in retail.
    union Scratch {
        SlotMessage msg;
        SP::Marker marker;
    };
    Scratch scratch;

    bool isCivilizationMode = SP_GetCurrentGameMode() == 0x1654c02;
    bool isSpaceMode        = SP_GetCurrentGameMode() == 0x1654c04;

    if (isCivilizationMode ||
        !((bool (__thiscall*)(void*, int))FUN_00c004c0)(self, (int)type)) {
        scratch.msg.mKind = 0;
        scratch.msg.vtbl = (void**)g_13eb90c;
        _InterlockedExchange((long*)&scratch.msg.mRefCount, 0);
        scratch.msg.vtbl = (void**)g_13eb844;
        scratch.msg.m38 = 0;
        scratch.msg.mKind = kUnderAttack;
        scratch.msg.mpObject = self;
        scratch.msg.m10 = 0xffff0000;
        scratch.msg.m18 = (u32)type;
        scratch.msg.m20 = attackerId;

        void* server = SP_GetServer();
        ((void (__thiscall*)(void*, u32, void*, int))VSLOT(server, 0x14))
            (server, scratch.msg.mKind, &scratch.msg, 0);
        scratch.msg.Destruct();
    }

    mLastAttack[type] = ((u64 (__thiscall*)(void*))FUN_00b316c0)(SP_GameTimeManager());

    if (type != kDiplomaticAttack && isSpaceMode) {
        int playerCiv = ((int (__thiscall*)(void*))FUN_00b1f9d0)(SP_NounManager());
        if (((int (__thiscall*)(void*))VSLOT(self, 0x4c))(self) == playerCiv) {
            if (mPlayerWarningTimer.GetElapsedTime() > 15000) {
                void* attacker = ((void* (__thiscall*)(void*, u32))FUN_00b25f40)
                    (SP_NounManager(), attackerId);
                if (attacker == 0) {
                    attacker = ((void* (__thiscall*)(void*))FUN_00b25fb0)(SP_NounManager());
                }

                float communityPos[3];
                ((void (__thiscall*)(void*, float*))VSLOT(self, 0x5c))(self, communityPos);

                void* nameProvider = self + 0x34;
                const wchar_t* name = ((const wchar_t* (__thiscall*)(void*))
                                       VSLOT(nameProvider, 0x04))(nameProvider);
                u32 nameHash = FNV1_String16(name, 0x811c9dc5u, 1);

                void* iface = ((void* (__thiscall*)(void*, u32))VSLOT(self, 0x0c))
                    (self, 0xee9b2232u);

                ((void (__thiscall*)(void*, void*, u32, u32, const float*,
                                     const Vec4&, int, u32))FUN_00cf9040)
                    (FUN_00cf74c0(), iface, 0x38320b95u, 0xaa9a8ed7u, communityPos,
                     Vec4(*(float*)((unsigned char*)attacker + 0xc4),
                          *(float*)((unsigned char*)attacker + 0xc8),
                          *(float*)((unsigned char*)attacker + 0xcc),
                          g_One),
                     0, nameHash);
                FUN_00435ed0(0xb3f166fdu, 0x387cfa0u);

                void* cfg = SP_ConfigManager();
                if (((int (__thiscall*)(void*, u32))VSLOT(cfg, 0x30))(cfg, 0x4ea96cbu) != 0) {
                    void* terrain = ((void* (__thiscall*)(void*))FUN_00f67d90)
                        (SP_NounManager());
                    if (!((bool (__thiscall*)(void*, u32))FUN_00c772c0)
                            (terrain, 0x5b86eb6u)) {
                        ((void (__thiscall*)(void*, u32))FUN_00c77bf0)(terrain, 0x5b86eb6u);

                        void* cityHall = ((void* (__thiscall*)(void*))FUN_00bd9b40)
                            (FUN_00ac86d0(self));
                        unsigned char* markerPos = cityHall
                            ? (unsigned char*)cityHall + 0x34 : 0;

                        ((void (__thiscall*)(void*, void*))FUN_00ad7a30)
                            (&scratch.marker, markerPos);

                        ((void (__thiscall*)(void*, u32, void*, int))FUN_00ae09b0)
                            (FUN_00b3d4d0(), 0x48ecbb8au, &scratch.marker, 0);

                        ((void (__thiscall*)(void*, u32, int, int, int, int, int))
                         FUN_00ae0930)
                            (FUN_00b3d4d0(), (u32)g_1469ca8, 1, 0, 0, 0, 0);

                        ((void (__thiscall*)(void*))FUN_00ad7ad0)(&scratch.marker);
                    }
                }
            }
            mPlayerWarningTimer.Restart();
        }
    }

    if (SP_GetCurrentGameMode() == 0x1654c05) {
        void* record = SP_GetActivePlanetRecord();
        if (((int (__thiscall*)(void*))FUN_00b8dab0)(record) == 5) {
            float now = (float)(((u64 (__thiscall*)(void*))FUN_00b316c0)
                               (SP_GameTimeManager())) * g_Milli;
            float* field = (float*)((unsigned char*)record + 0x12c);

            if (*field == 0.0f) {
                *field = now;
                void* audio = SP_GetAudioSystem();
                u32 value = audio
                    ? ((u32 (__thiscall*)(void*))VSLOT(audio, 0x20))(audio) : 0;
                FUN_00435ed0(0xe00c599au, value);
            } else if (*field < 0.0f) {
                float limit = g_Sixty;
                void* tuning = SP_GetSpaceCombatTuning();
                void** sub = (void**)((unsigned char*)tuning + 8);
                FUN_0040cf10(*sub, 0x5c2cbea, &limit);
                if (*field + now > limit) {
                    *field = now;
                    FUN_00435ed0(0xe00c599au, FUN_00435e90());
                }
            }
        }
    }
}

// @ 0x00c01060
void LaneRecVec::DoInsertPoint(LaneRec* pos, const LaneRec* value)
{
    if (mpEnd != mpCap) {
        // in place: keep the value valid when it points into the shifted range
        const LaneRec* v = value;
        if (v >= pos && v < mpEnd)
            ++v;
        if (mpEnd != 0) {
            // copy-construct the last element past the end, then shift down
            LaneRec* last = mpEnd;
            last->mPos.x = last[-1].mPos.x;
            last->mPos.y = last[-1].mPos.y;
            last->mPos.z = last[-1].mPos.z;
            last->mDir.x = last[-1].mDir.x;
            last->mDir.y = last[-1].mDir.y;
            last->mDir.z = last[-1].mDir.z;
            last->mRadius = last[-1].mRadius;
            _ReadWriteBarrier();
            last->mIndex = last[-1].mIndex;
        }
        // move the tail one slot up, back to front
        LaneRec* d = mpEnd;
        for (LaneRec* s = mpEnd - 1; s != pos; ) {
            --s;
            --d;
            *d = *s;
        }
        *pos = *v;
        ++mpEnd;
        return;
    }

    {
        // grow: capacity = count ? count * 2 : 1, copy prefix, the new element
        // and the suffix into the new block, then release the old one
        unsigned int count = (unsigned int)(mpEnd - mpBegin);
        unsigned int newCount = count > 0 ? count * 2 : 1;
        LaneRec* newBegin;
        if (newCount != 0)
            newBegin = (LaneRec*)EAAllocate(newCount * 0x20, "LaneRec", 0, 0,
                                            "SPCommunity.cpp", 209);
        else
            newBegin = 0;
        LaneRec* mid = CopyLaneRange(mpBegin, pos, newBegin);
        if (mid != 0) {
            // construct the new element member by member (the copy helper is inlined)
            mid->mPos.x = value->mPos.x;
            mid->mPos.y = value->mPos.y;
            mid->mPos.z = value->mPos.z;
            mid->mDir.x = value->mDir.x;
            mid->mDir.y = value->mDir.y;
            mid->mDir.z = value->mDir.z;
            mid->mRadius = value->mRadius;
            mid->mIndex = value->mIndex;
        }
        LaneRec* newEnd = CopyLaneRange(pos, end(), mid + 1);
        if (mpBegin != 0 && ((uint32_t*)mpBegin)[-1] != 0)
            FreeAllocBlock(mpBegin);
        mpBegin = newBegin;
        mpCap = newBegin + newCount;
        mpEnd = newEnd;
    }
}

// @ 0x00c011c0
cCommunity_s00c0_11c0::cCommunity_s00c0_11c0()
{
    // The interface sub-object's base vftable is installed first, then the two
    // primary vftables, then the community's own interface vftable.
    mpVtbl   = (void*)g_13ef63c;                             // +0x034
    _ReadWriteBarrier();   // retail keeps this base vftable store, dead as it is
    mpVtbl0  = (void*)g_1469ce8;                             // +0x000
    mpVtbl1  = (void*)g_1469cd8;                             // +0x004
    mpVtbl   = (void*)g_1469cc0;                             // +0x034

    mCommunitySize = 0;                                      // +0x038
    mStructureLines.mpBegin = 0;                             // +0x03c
    mStructureLines.mpEnd = 0;                               // +0x040
    mStructureLines.mpCapacity = 0;                          // +0x044

    mGateInfo.mpBegin = 0;                                   // +0x058
    mGateInfo.mpEnd = 0;                                     // +0x05c
    mGateInfo.mpCapacity = 0;                                // +0x060

    mbNeedsNavigationUpdate = false;                         // +0x06c

    mAssemblyBubbles.mpBegin = 0;                            // +0x070
    mAssemblyBubbles.mpEnd = 0;                              // +0x074
    mAssemblyBubbles.mpCapacity = 0;                         // +0x078

    _ReadWriteBarrier();   // pins the timer's `lea edi,[esi+0xb0]` below these stores
    mLanes.mpBegin = 0;                                      // +0x084
    mLanes.mpEnd = 0;                                        // +0x088
    mLanes.mpCapacity = 0;                                   // +0x08c

    mPlayerWarningTimer.Construct();                         // +0x0b0

    mStructures.mpBegin = 0;                                 // +0x0d0
    mStructures.mpEnd = 0;                                   // +0x0d4
    mStructures.mpCapacity = 0;                              // +0x0d8

    mInhabitants.mpBegin = 0;                                // +0x0e4
    mInhabitants.mpEnd = 0;                                  // +0x0e8
    mInhabitants.mpCapacity = 0;                             // +0x0ec

    // Empty strings: begin == end == the shared empty buffer at 0x01667bac and
    // capacity == one past it, 0x01667bae.
    _ReadWriteBarrier();
    mName.mpBegin = (void*)g_1667bac;                            // +0x0f8
    mName.mpEnd = (void*)g_1667bac;                              // +0x0fc
    _ReadWriteBarrier();   // the two capacities are materialised below 0x1667bac's stores
    mName.mpCapacity = (void*)g_1667bae;                         // +0x100
    mDescription.mpCapacity = (void*)g_1667bae;                  // +0x110
    mDescription.mpBegin = (void*)g_1667bac;                     // +0x108
    mDescription.mpEnd = (void*)g_1667bac;                       // +0x10c

    mGODPoliticalID = 0xffffffff;                            // +0x118
    mpLeader = 0;                                            // +0x11c

    _ReadWriteBarrier();   // pins the second `mov ecx,edi` after +0x11c
    mLastAttack[0] = 0;                                      // +0x098
    mLastAttack[1] = 0;                                      // +0x0a0
    mLastAttack[2] = 0;                                      // +0x0a8

    mPlayerWarningTimer.Restart();                           // +0x0b0
}

// @ 0x00c01310
void Vec20::FUN_00c01310()
{
    Elem20_s00c0_1310* begin = mpBegin;
    Elem20_s00c0_1310* end = mpEnd;
    MoveRange(end, end, begin);
    mpEnd -= end - begin;
}

// @ 0x00c01ce0
void FUN_00c01ce0(ISerializableObject* object, EmptyBubbleVec* vec)
{
    cEmptyBubble* begin = vec->mpBegin;
    cEmptyBubble* end = vec->mpEnd;
    // Inlined vector bookkeeping: the tail copy is an empty range, the end
    // pointer then rewinds onto the begin pointer.
    CopyBubbleRange(end, end, begin);
    vec->mpEnd -= (end - begin);

    uint32_t count = 0;
    IStreamHolder* holder = object->Open();
    void* stream = holder->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec->Reserve((int)count);

    for (uint32_t i = 0; i < count; ++i) {
        cEmptyBubble value;
        value.mW = 0.0f;
        value.mFlags = 0;
        cVarListSerializer_s00c0_15e0 serializer;
        serializer.Construct(&value, (int)g_1570f10, 0x1a80d26);
        serializer.Serialize(object);

        if (vec->mpEnd < vec->mpCap) {
            cEmptyBubble* slot = vec->mpEnd;
            vec->mpEnd = slot + 1;
            if (slot != 0) {
                slot->mX = value.mX;
                slot->mY = value.mY;
                slot->mZ = value.mZ;
                slot->mW = value.mW;
                slot->mFlags = value.mFlags;
            }
        } else {
            vec->DoInsertValue(vec->mpEnd, &value);
        }
    }
    object->Close();
}

// @ 0x00c01e20
void ILaneObject::UpdateZone(bool force)
{
    if (mZoneValid == 0 && !force)
        return;

    FUN_00c014c0();
    Zone* zone = GetZone();
    if (zone == 0) {
        mOuterRadius = 0.0f;
        mInnerRadius = 0.0f;
    } else {
        mInnerRadius = zone->rMin;
        mOuterRadius = zone->rMax;
    }
    v32();
    v34();
}

// @ 0x00c01e80
void ILaneObject::ClearLanes()
{
    mObjects.erase(mObjects.mpBegin, mObjects.mpEnd);
    mReporters.erase(mReporters.mpBegin, mReporters.mpEnd);

    IRefCounted* p = mpAt11c;
    if (p != 0) {
        mpAt11c = 0;
        p->Release();
    }

    p = mpAt2c;
    if (p != 0) {
        mpAt2c = 0;
        p->Release();
    }
}

// @ 0x00c01f90
void cCommunity::UpdateLanes()
{
    LaneRec* begin = mOut.mpBegin;
    LaneRec* end = mOut.mpEnd;
    LaneRec* it = CopyLaneRange(end, end, begin);
    mOut.DoDestroy(it, mOut.mpEnd);
    mOut.mpEnd -= (end - begin);

    PtrVec* sources = (PtrVec*)GetSourceList();
    PlanetModel();
    if (sources->mpBegin == sources->mpEnd)
        return;

    ILaneZone* zone = (ILaneZone*)GetLaneZone();

    LaneRecVec points;
    points.mpBegin = 0;
    points.mpEnd = 0;
    points.mpCap = 0;
    points.ReservePoints((int)(sources->mpEnd - sources->mpBegin) + 1);

    int sourceCount = (int)(sources->mpEnd - sources->mpBegin);
    int index = 0;
    int i = 0;
    while (i < sourceCount) {
        ILaneSource* source = (ILaneSource*)sources->mpBegin[i];
        bool keep = true;
        if (zone != 0)
            keep = zone->Contains(source->GetPosition());
        if (keep) {
            LaneRec* entry;
            if (points.mpEnd < points.mpCap) {
                entry = points.mpEnd++;
            } else {
                LaneRec scratch;
                points.DoInsertPoint(points.mpEnd, &scratch);
                entry = points.mpEnd - 1;
            }
            entry->mPos = *source->GetPosition();
            entry->mRadius = source->GetRadius();
            Vec3 facing;
            source->GetFacing(&facing);
            entry->mDir = facing;
            entry->mIndex = index;
        }
        ++i;
        index += 6;
    }

    cCity* city = (cCity*)Cast(0xee9b2232);
    if (city != 0 && city->GetCityHall() != 0) {
        Vec3 hallPos;
        float hallRadius;
        cCityHall* hall = city->GetCityHall(&hallPos, &hallRadius);
        hall->UpdateFromSubobject(&hallPos, &hallRadius);

        LaneRec* entry;
        if (points.mpEnd < points.mpCap) {
            entry = points.mpEnd++;
        } else {
            LaneRec scratch;
            points.DoInsertPoint(points.mpEnd, &scratch);
            entry = points.mpEnd - 1;
        }
        entry->mPos = hallPos;
        entry->mRadius = hallRadius;

        Vec3 self;
        GetPosition(&self);
        float dx = hallPos.x - self.x;
        float dy = hallPos.y - self.y;
        float dz = hallPos.z - self.z;
        float inv = 1.0f / sqrtf(dz * dz + dy * dy + dx * dx + 1e-8f);
        entry->mDir.x = dx * inv;
        entry->mDir.y = dy * inv;
        entry->mDir.z = dz * inv;
        entry->mIndex = i * 6;
    }

    cActionCircle circle;
    int laneCount = (int)(points.mpEnd - points.mpBegin);
    for (int lane = 0; lane < laneCount; ++lane) {
        LaneRec* point = points.mpBegin + lane;
        int laneIndex = point->mIndex;
        circle.SetAtCenter(&point->mPos, point->mRadius + 2.0f, &point->mDir, 0.0f);
        circle.FUN_00afd6d0(1.0f, 1.0f, 6);

        for (int spoke = 0; spoke < 6; ++spoke) {
            LaneRec* node;
            if (mOut.mpEnd < mOut.mpCap) {
                node = mOut.mpEnd++;
                node->mNext.mpBegin = 0;
                node->mNext.mpEnd = 0;
                node->mNext.mpCap = 0;
            } else {
                LaneRec scratch;
                scratch.mNext.mpBegin = 0;
                scratch.mNext.mpEnd = 0;
                scratch.mNext.mpCap = 0;
                mOut.DoInsertNodeRec(mOut.mpEnd, &scratch);
                node = mOut.mpEnd - 1;
            }
            node->mPos = circle.mpSpokes[spoke].mDir;

            int next = laneIndex + spoke + 1;
            if (spoke == 5)
                next = laneIndex;
            node->mNext.DoInsertValueI(node->mNext.mpEnd, next);

            int prev = laneIndex + spoke - 1;
            if (spoke == 0)
                prev = laneIndex + 5;
            node->mNext.DoInsertValueI(node->mNext.mpEnd, prev);
        }
    }

    int nodeCount = (int)(mOut.mpEnd - mOut.mpBegin);
    if (nodeCount - 6 > 0) {
        int window = 6;
        int a = 0;
        do {
            LaneRec* pa = mOut.mpBegin + a;
            Vec3 posA = pa->mPos;
            int b = a + window;
            if (b < nodeCount) {
                do {
                    LaneRec* pb = mOut.mpBegin + b;
                    float dx = posA.x - pb->mPos.x;
                    float dy = posA.y - pb->mPos.y;
                    float dz = posA.z - pb->mPos.z;
                    if (sqrtf(dz * dz + dy * dy + dx * dx) < kLaneLinkDistance) {
                        pa->mNext.DoInsertValueI(pa->mNext.mpEnd, b);
                        pb->mNext.DoInsertValueI(pb->mNext.mpEnd, a);
                    }
                    ++b;
                } while (b < nodeCount);
            }
            --window;
            if (window == 0)
                window = 6;
            ++a;
        } while (a < nodeCount - 6);
    }

    if (points.mpBegin != 0)
        FreeAllocBlock(points.mpBegin);
}

// @ 0x00c024f0
void FUN_00c024f0(ISerializableObject* object, LaneRecVec* vec)
{
    LaneRec* begin = vec->mpBegin;
    LaneRec* end = vec->mpEnd;
    // Inlined eastl::vector::erase(begin, end): copy the (empty) tail range,
    // destroy the live range and rewind the end pointer.
    LaneRec* it = CopyLaneRange(end, end, begin);
    vec->DoDestroy(it, vec->mpEnd);
    vec->mpEnd -= (end - begin);

    uint32_t count = 0;
    IStreamHolder* holder = object->Open();
    void* stream = holder->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec->ReserveNodes((int)count);

    for (uint32_t i = 0; i < count; ++i) {
        LanePayload value;
        value.mpData = 0;
        value.mPad10[0] = 0;
        value.mPad10[1] = 0;
        cVarListSerializer_s00c0_15e0 serializer;
        serializer.Construct(&value, (int)g_1571000, 0x1a80d26);
        serializer.Serialize(object);

        if (vec->mpEnd < vec->mpCap) {
            LaneRec* slot = vec->mpEnd;
            vec->mpEnd = slot + 1;
            if (slot != 0)
                slot->Construct(&value);
        } else {
            vec->DoInsertNode(vec->mpEnd, &value);
        }
        if (value.mpData != 0 && ((AllocBlockHeader*)value.mpData)[-1].mRefCount != 0)
            FreeAllocBlock(value.mpData);
    }
    object->Close();
}

// @ 0x013342f0
namespace Simulator {
void InitCommunityAttributes()
{
#undef DECL_FAMILY  // the callback names below come from the slice's macro block
    ADD_TO(cCommunity_sAttributes, 0, "mCommunitySize", 0x03223734, 0x38,
           Read_00572810_s, Write_00572840_s, ReadText_00692ff0_s, WriteText_00694ee0,
           Validate_00b1fbf0_s, ToXml_0057cde0)
    ADD_TO(cCommunity_sAttributes, 1, "mAssemblyBubbles", 0x03223735, 0x70,
           Read_00c01ce0, Write_00c006a0, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00c00740, ToXml_00c51440)
    ADD_TO(cCommunity_sAttributes, 2, "mLanes", 0x03223736, 0x84,
           Read_00c024f0, Write_00c00780, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00c00810, ToXml_00f29650)
    ADD_TO(cCommunity_sAttributes, 3, "mName", 0x042c8cee, 0xf8,
           Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
           Validate_00b1fbf0_s, ToXml_00acbbc0)
    ADD_TO(cCommunity_sAttributes, 4, "mDescription", 0x042e213c, 0x108,
           Read_00ac87c0, Write_00ac87f0, ReadText_00694c80, WriteText_00694c10,
           Validate_00b1fbf0_s, ToXml_00acbbc0)
    ADD_TO(cCommunity_sAttributes, 5, "mpLeader", 0x04bd34fb, 0x11c,
           Read_00b02540, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
           Validate_00b6f550, ToXml_00ac8050)
}
}  // namespace Simulator
