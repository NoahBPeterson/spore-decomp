// src/game/SPGonzago/_at_01040000.cpp -- migrated from slice(s) s0104bcc0, s01049040, s01044360, s0103fe90 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_01040000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCivData.h"
#include "SP/cGameNounManager.h"
#include "SP/cPropertyManager.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include "EA/Variant.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorVerbIconTray.h"
#include "SP/cSPSpaceInventoryItem.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cSPTimer.h"
#include "SP/cString.h"
#include "SP/cTerrainSphere.h"
#include "EA/COM/IUnknown32.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void _ReadWriteBarrier(void);
extern float     DAT_014853bc;               // 0x014853bc
extern float     _HK_REAL_ONE;               // 0x01485720
extern float     DAT_01473c70;               // 0x01473c70
#pragma intrinsic(_ReadWriteBarrier)

// ---- items of slice s0103fe90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float     DAT_014853bc;               // 0x014853bc
extern float     _HK_REAL_ONE;               // 0x01485720
extern float     DAT_01473c70;               // 0x01473c70
class cSpaceTuningInit {
public:
    uint32_t m00;                // +0x00
    uint32_t m04;                // +0x04
    uint32_t m08;                // +0x08
    uint32_t m0c;                // +0x0c
    uint32_t m10;                // +0x10
    uint32_t m14;                // +0x14
    float    m18;                // +0x18
    float    m1c;                // +0x1c
    float    m20;                // +0x20
    float    m24;                // +0x24
    float    m28;                // +0x28
    float    m2c;                // +0x2c
    float    m30;                // +0x30
    float    m34;                // +0x34
    float    m38;                // +0x38
    uint8_t  m3c;                // +0x3c
    uint8_t  m3d;                // +0x3d
    uint8_t  m3e[2];             // +0x3e
    float    m40;                // +0x40
    float    m44;                // +0x44
    float    m48;                // +0x48
    float    m4c;                // +0x4c
    uint8_t  m50;                // +0x50
    uint8_t  m51;                // +0x51
    uint8_t  m52;                // +0x52

    cSpaceTuningInit* __thiscall FUN_01040730();
};
// ---- items of slice s0103fe90 end

// ---- items of slice s01044360 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float __cdecl SqrtF(float);
extern "C" float __cdecl FabsF(float);
namespace SP {
struct Vector3 { float x, y, z; };
}
namespace SP {
struct Quaternion { float w, x, y, z; };
}
namespace SP {
extern const float gForwardX;      // 0x015b8528
}
namespace SP {
extern const float gForwardY;      // 0x015b852c
}
namespace SP {
extern const float gForwardZ;      // 0x015b8530
}
namespace SP {
extern const float gAltX;          // 0x015b8534
}
namespace SP {
extern const float gAltY;          // 0x015b8538
}
namespace SP {
extern const float gAltZ;          // 0x015b853c
}
namespace SP {
extern const float gEpsilon;       // 0x013ec4b8
}
namespace SP {
extern const float gDotThreshold;  // 0x013eb960
}
namespace SP {
extern const char  gBannerName;    // 0x016e0688
}
namespace SP {
struct GameDataVec {
    void* mpBegin;                                         // +0x00
    void* mpEnd;                                           // +0x04
};
}
namespace SP {
struct NounQueryResult {
    uint32_t mPad00;                                       // +0x00
    GameDataVec mVector;                                   // +0x04
};
}
namespace SP {
struct cEmbeddedSource {
    void* mpVtable;                                        // +0x00
    void* GetKey() {
        return ((void* (__thiscall*)(cEmbeddedSource*))((void**)mpVtable)[0x2c / 4])(this);
    }
    Vector3* GetPosition() {
        return ((Vector3* (__thiscall*)(cEmbeddedSource*))((void**)mpVtable)[0x2c / 4])(this);
    }
};
}
namespace SP {
struct cItemOwner {
    void* mpVtable;                                        // +0x00
    bool HasItem(const void* id) {
        return ((bool (__thiscall*)(cItemOwner*, const void*))
            ((void**)mpVtable)[0x74 / 4])(this, id);
    }
};
}
namespace SP {
struct cPlayerInventory {
    cItemOwner* mpOwner;                                   // +0x00
    uint32_t mPad04[0x30 / 4];                             // +0x04
    cEmbeddedSource mKeySource;                            // +0x34
};
}
namespace SP {
struct cLocatedNoun {
    uint32_t mPad00[0x120 / 4];                            // +0x00
    cEmbeddedSource mPositionSource;                       // +0x120
};
}
namespace SP {
struct SubsystemVec {
    void** mpBegin;                                        // +0x00
    void** mpEnd;                                          // +0x04
};
}
namespace SP {
struct cGameNounManager_s0104_4360 {
    NounQueryResult* __thiscall GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340 (SP::cGameNounManager::GetGameDataVector)
    SubsystemVec* GetSubsystemVec(void* id);               // 0x00ae7200
};
}
namespace SP {
struct cPlanetView {
    void* mpVtable;                                        // +0x00
    void* FindObject(uint32_t id) {
        return ((void* (__thiscall*)(cPlanetView*, uint32_t))((void**)mpVtable)[0x0c / 4])(this, id);
    }
};
}
namespace SP {
struct cCameraController {
    void* mpVtable;                                        // +0x00
    cPlanetView* GetPlanetView() {
        return ((cPlanetView* (__thiscall*)(cCameraController*))((void**)mpVtable)[0x38 / 4])(this);
    }
};
}
namespace SP {
struct cApp {
    void* mpVtable;                                        // +0x00
    cCameraController* GetCameraController() {
        return ((cCameraController* (__thiscall*)(cApp*))((void**)mpVtable)[0x50 / 4])(this);
    }
};
}
namespace SP {
struct cActionTarget {
    uint32_t mData[9];                                     // 0x24 bytes
    ~cActionTarget();
};
}
namespace SP {
struct CamInfo {
    uint32_t mData[0x10];                                  // 0x40 bytes
    void __thiscall init(const Vector3* position, const Quaternion* orientation);
};
}
namespace SP {
struct cTriggerMgr {
    void* mpVtable;                                        // +0x00
    void __thiscall PostAction(uint32_t actionId, cActionTarget* target, int flags);
};
}
namespace SP {
cGameNounManager_s0104_4360* __cdecl NounManager();                   // 0x00b3d300
}
namespace SP {
void* __cdecl GetUFOSimulator();                           // 0x00ffbe50
}
namespace SP {
void* __cdecl FUN_00ac9310(GameDataVec* vec, void* key, char flag); // 0x00ac9310
}
namespace SP {
Quaternion* __cdecl QuaternionFromFacingAndUp(Quaternion* out, const Vector3* facing,
                                              const Vector3* up); // 0x0069b600
}
namespace SP {
cTriggerMgr* __cdecl GetTriggerMgr();                      // 0x00b3d4d0
}
namespace SP {
cApp* __cdecl App();                                       // 0x0067dd10
}
namespace SP {
void* __cdecl FUN_00b3d4a0();                              // 0x00b3d4a0
}
namespace SP {
char __cdecl FUN_00ae9390();                               // 0x00ae9390
}
namespace SP {
void* __cdecl GameTimeManager();                           // 0x00b3d3d0
}
namespace SP {
void* __cdecl SpaceGameGet();                              // 0x00b1e500
}
namespace SP {
struct cSPSimulatorSpaceGame {
    void* mpVtable;                                        // +0x00
    cPlayerInventory* GetPlayerInventory();                // 0x00a1ad60
    float GetMaxZ();                                       // 0x00ffbfd0
};
}
namespace SP {
static bool TravelToSystem(uint32_t actionId)
{
    cGameNounManager_s0104_4360* nouns = NounManager();
    NounQueryResult* result = nouns->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00acdff0,
        (void*)0x00b1e500, (void*)0x018c43e8);
    if (result->mVector.mpBegin == result->mVector.mpEnd)
        return false;

    void* simulator = GetUFOSimulator();
    cPlayerInventory* inventory = ((cSPSimulatorSpaceGame*)simulator)->GetPlayerInventory();
    void* key = inventory->mKeySource.GetKey();
    cLocatedNoun* noun = (cLocatedNoun*)FUN_00ac9310(&result->mVector, key, 0);
    if (!noun)
        return false;

    Vector3 pos = *noun->mPositionSource.GetPosition();

    float invLen = 1.0f / SqrtF(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z + gEpsilon);
    Vector3 forward;
    forward.x = pos.x * invLen;
    forward.y = pos.y * invLen;
    forward.z = pos.z * invLen;

    float axisX = gForwardX;
    float axisY = gForwardY;
    float axisZ = gForwardZ;
    if (FabsF(axisZ * forward.z + (axisY * forward.y + axisX * forward.x) - 1.0f)
        < gDotThreshold) {
        axisX = -gAltX;
        axisY = -gAltY;
        axisZ = -gAltZ;
    }

    Vector3 right;
    right.x = axisZ * forward.y - axisY * forward.z;
    right.y = axisY * forward.x - axisX * forward.y;
    right.z = axisX * forward.z - axisZ * forward.x;
    float rightLen = 1.0f / SqrtF(right.x * right.x + right.y * right.y
                                            + right.z * right.z + gEpsilon);
    right.x *= rightLen;
    right.y *= rightLen;
    right.z *= rightLen;

    Vector3 up;
    up.x = right.z * forward.y - right.y * forward.z;
    up.y = right.y * forward.x - right.x * forward.y;
    up.z = right.x * forward.z - right.z * forward.x;
    float upLen = 1.0f / SqrtF(up.x * up.x + up.y * up.y + up.z * up.z + gEpsilon);
    up.x *= upLen;
    up.y *= upLen;
    up.z *= upLen;

    Quaternion orientation;
    QuaternionFromFacingAndUp(&orientation, &right, &forward);

    CamInfo info;
    cActionTarget target;
    info.init(noun->mPositionSource.GetPosition(), &orientation);
    GetTriggerMgr()->PostAction(actionId, &target, 0);
    return true;
}
}
// ---- items of slice s01044360 end

// ---- items of slice s01049040 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t kEmptyString16[];                          // 0x013ec468 (L"")
struct Property
{
	uint8_t pad[0x12];
	uint16_t mType;                                            // +0x12
	int* GetInt();                                             // 0x0041e990
};
struct cPropertyList
{
	virtual int AddRef();                                      // +0x00
	virtual int Release();                                     // +0x04
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
	virtual bool GetProperty(uint32_t hash, Property** out);   // +0x24
};
namespace EA {
template <typename T>
class AutoRefCount_s0104_9040
{
public:
	T* mpObject;
	AutoRefCount_s0104_9040() : mpObject(0) {}
	~AutoRefCount_s0104_9040() { if (mpObject) mpObject->Release(); }
	T* operator->() const { return mpObject; }
	operator T*() const { return mpObject; }
	AutoRefCount_s0104_9040& operator=(T* p)
	{
		if (p != mpObject)
		{
			T* const old = mpObject;
			if (p)
				p->AddRef();
			mpObject = p;
			if (old)
				old->Release();
		}
		return *this;
	}
};  // namespace EA
}
class cPropertyManager
{
public:
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
	virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID,
	                             EA::AutoRefCount_s0104_9040<cPropertyList>& out);   // +0x2c
};
cPropertyManager* PropertyManager();                          // 0x0067de30
struct cTerraformTuning
{
	EA::AutoRefCount_s0104_9040<cPropertyList> mPropList;                 // +0x00
	void Init();                                               // 0x01049a20
	int GetMaxBuildingsForT1Colony();                          // 0x01049e70
	int GetMaxBuildingsForT2Colony();                          // 0x01049eb0
	int GetMaxBuildingsForT3Colony();                          // 0x01049ef0
};
struct WString
{
	wchar_t* mpBegin;
	wchar_t* mpEnd;
	wchar_t* mpCapacity;
	WString& Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
	WString& operator=(const WString& other);                     // 0x0057cb60
};
struct cString
{
	uint32_t data[5];
	cString();                                                  // 0x006b5060
	~cString();                                                 // 0x006b5240
	bool Load(uint32_t tableID, uint32_t instanceID, int flags);// 0x006b54b0
	const wchar_t* GetText();                                   // 0x006b55c0
};
void operator delete(void* p);                                  // 0x00f47380
struct cStringVector
{
	cString* mpBegin;                                           // +0x00
	cString* mpEnd;                                             // +0x04
	cString* mpCapacity;                                        // +0x08
	uint32_t mField0C;                                          // +0x0c
	uint32_t mField10;                                          // +0x10

	cStringVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
	~cStringVector()
	{
		cString* end = mpEnd;
		for (cString* p = mpBegin; p < end; ++p)
			p->~cString();
		if (mpBegin && ((int*)mpBegin)[-1] != 0)
			operator delete(mpBegin);
	}
	int Size() const { return (int)(mpEnd - mpBegin); }
	void Index(uint32_t count);                                 // 0x00e2ca70
};
uint32_t FNVHash(const char* text, uint32_t seed, int mode);    // 0x00932e80
extern const uint32_t kTechLevelStringIds[];                    // 0x015b86d4, 7 entries
extern const uint32_t kTerraformingLevelStringIds[];            // 0x015b86f0, 4 entries
extern const uint32_t kAnimalTypeStringIds[];                   // 0x015b8700, 4 entries
extern const uint32_t kPlantTypeStringIds[];                    // 0x015b8710, 3 entries
extern const uint32_t kMoneyFormatInstanceId;                   // 0x015b871c
extern const uint32_t kUiSpaceNameInstanceId;                   // 0x015b8720
namespace Simulator {
class cCivTokenTranslator
{
public:
	cCivTokenTranslator();                                      // 0x00b32470
	virtual ~cCivTokenTranslator();                             // 0x00b32490
	virtual void v04();                                         // slot 1
	virtual void v08();                                         // slot 2
	virtual void v0c();                                         // slot 3
	virtual bool TranslateToken(const wchar_t* token, WString* out);   // slot 4
	uint32_t mField04;                                          // +0x04
	uint32_t mField08;                                          // +0x08
};  // namespace Simulator
}
class cSpaceTokenTranslator : public Simulator::cCivTokenTranslator
{
public:
	virtual void v14();                                         // slot 5 (0x010829f0)

	void* mpPlanet;                                             // +0x0c
	void* mpStar;                                               // +0x10
	void* mpItem;                                               // +0x14
	void* mpMission;                                            // +0x18
	void* mpEmpire;                                             // +0x1c
	void* mpEmpire2;                                            // +0x20
	void* mpSpeciesProfile;                                     // +0x24
	void* mpBuilding;                                           // +0x28
	void* mpVehicle;                                            // +0x2c
	void* mpUFO;                                                // +0x30
	void* mpGenericName;                                        // +0x34
	int mCount;                                                 // +0x38
	int mField3C;                                               // +0x3c
	float mField40;                                             // +0x40
	uint32_t mField44;                                          // +0x44
	int mField48;                                               // +0x48
	cStringVector mTechLevelString;                             // +0x4c
	cStringVector mTerraformingLevelString;                     // +0x60
	cStringVector mAnimalTypeString;                            // +0x74
	cStringVector mPlantTypeString;                             // +0x88
	cString mMoneyFormatString;                                 // +0x9c
	cString mUiSpaceName;                                       // +0xb0

	cSpaceTokenTranslator();                                    // 0x0104a020
	virtual ~cSpaceTokenTranslator();                           // 0x0104a210

	const wchar_t* FUN_01049f50(int index);                     // 0x01049f50
	void FUN_01049f90(WString* out);                            // 0x01049f90
};
// ---- items of slice s01049040 end

// ---- items of slice s0104bcc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef int                i32;
typedef unsigned long long u64;
typedef float              f32;
typedef double             f64;
struct cString_s0104_bcc0 {
    u8 mData[0x14];
    void ctorRaw();                       // 0x006b5060
    void dtorRaw();                       // 0x006b5240
    const unsigned short* GetText();      // 0x006b55c0
    bool Load(u32 group, u32 id, int flag);// 0x006b54b0
};
struct cSPTimer_s0104_bcc0 {
    u8 mData[0x20];
    bool IsRunning();                     // 0x00feba90
    u64  GetElapsedTime();                // 0x00bc3190
};
struct cGonzagoTimer_s0104_bcc0 : cSPTimer_s0104_bcc0 {
    void ctorRaw();                       // 0x00b63890
    void dtorRaw();                       // 0x00b638b0
};
struct Property_s0104_bcc0 {
    void*  mpValue;                       // +0x00
    u8     pad04[0x0c];
    u8     mFlags10;                      // +0x10
    u8     pad11;
    u16    mType12;                       // +0x12
    float* GetFloat();                    // 0x0041ea70
    u32*   GetUInt();                     // 0x0041ea00
    bool*  GetBool();                     // 0x0041e920
};
struct cPropertyList_s0104_bcc0 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool FindProperty(u32 id, Property_s0104_bcc0** ppOut);  // +0x24
};
struct cItemID { u32 instanceID; u32 typeID; u32 groupID; };
struct cToolRef {
    void** mpVftbl;                                            // +0x00
    __forceinline void RefCountRelease()                        // vtable +0x04
    { ((void (__thiscall*)(void*))mpVftbl[0x04 / 4])(this); }
    __forceinline void EffectRelease()                          // vtable +0xc0
    { ((void (__thiscall*)(void*))mpVftbl[0xc0 / 4])(this); }
    __forceinline void* ActivateVfx(void* arg)                  // vtable +0xb8
    { return ((void* (__thiscall*)(void*, void*))mpVftbl[0xb8 / 4])(this, arg); }
    __forceinline u32 ActivateFlag(u32 flag)                    // 0x00c38990
    { return ((u32 (__thiscall*)(void*, u32))mpVftbl[-1])(this, flag); }
    // Only the low byte (AL) is consumed here, exactly as the original u8 flag does.
    bool OnActivate(u32 flag);                                  // 0x00c38990
};
struct cIface {
    void** mpVftbl;                                             // +0x00
    __forceinline void* Call(u32 byteOff)
    { return ((void* (__thiscall*)(void*))mpVftbl[byteOff / 4])(this); }
    __forceinline void* Call1(u32 byteOff, u32 a)
    { return ((void* (__thiscall*)(void*, u32))mpVftbl[byteOff / 4])(this, a); }
};
typedef cIface cOutStream;
namespace SP {
struct cSPSpaceToolData_s0104_bcc0 {
    void*              mpVftable0;         // +0x00
    u32                mPad04;             // +0x04
    void*              mpVftable8;         // +0x08
    void*              mpVftableC;         // +0x0c
    u8                 mPad10[0x20];       // +0x10 .. +0x2f
    cPropertyList_s0104_bcc0*     mpPropList30;       // +0x30
    u8                 mPad34[0x28];       // +0x34 .. +0x5b
    cItemID            mItemID;            // +0x5c
    u8                 mPad68[0x14];       // +0x68 .. +0x7b
    i32                mAmmo7c;            // +0x7c
    u8                 mFlag80;            // +0x80
    u8                 mPad81[7];          // +0x81 .. +0x87
    cGonzagoTimer_s0104_bcc0      mIsInUse;           // +0x88
    cGonzagoTimer_s0104_bcc0      mRechargeTimer;     // +0xa8
    cGonzagoTimer_s0104_bcc0      mAutoFireTimer;     // +0xc8
    cGonzagoTimer_s0104_bcc0      mChargeTimer;       // +0xe8
    cToolRef*          mEffect108;         // +0x108
    cToolRef*          mEffect10c;         // +0x10c
    cToolRef*          mEffect110;         // +0x110
    cToolRef*          mEffect114;         // +0x114
    cToolRef*          mEffect118;         // +0x118
    i32                mField11c;          // +0x11c
    cToolRef*          mField120;          // +0x120
    cToolRef*          mField124;          // +0x124
    cToolRef*          mField128;          // +0x128
    cToolRef*          mField12c;          // +0x12c
    u8                 mPad130[0x10];      // +0x130 .. +0x13f
    cToolRef*          mField140;          // +0x140
    f32                mField144;          // +0x144
    f32                mField148;          // +0x148
    f32                mField14c;          // +0x14c
    u8                 mField150;          // +0x150
    u8                 mPad151[3];         // +0x151 .. +0x153
    f32                mField154;          // +0x154
    f32                mField158;
    f32                mField15c;
    f32                mField160;
    f32                mField164;
    f32                mField168;
    cToolRef*          mField16c;          // +0x16c
    cToolRef*          mField170;          // +0x170
    union {
        u32 mFlags174;                     // +0x174 (bit flags)
        struct { u16 mFlagsLow174; u8 mByte176; u8 mByte177; } mFlagsBytes;
    };
    u32                mField178;          // +0x178
    u32                mField17c;          // +0x17c
    i32                mField180;          // +0x180
    i32                mField184;          // +0x184
    u32                mField188;          // +0x188
    u32                mUpgradeInstance;   // +0x18c
    u32                mField190;          // +0x190
    u32                mField194;          // +0x194
    u32                mField198;          // +0x198
    i32                mField19c;          // +0x19c
    i32                mLimit1a0;          // +0x1a0
    u32                mField1a4;          // +0x1a4
    f32                mField1a8;          // +0x1a8
    f32                mField1ac;
    f32                mField1b0;
    f32                mField1b4;
    f32                mField1b8;
    f32                mField1bc;          // +0x1bc
    f32                mField1c0;          // +0x1c0
    f32                mField1c4;          // +0x1c4
    f32                mField1c8;          // +0x1c8
    f32                mField1cc;          // +0x1cc
    f32                mField1d0;          // +0x1d0
    f32                mField1d4;          // +0x1d4
    f32                mField1d8;
    f32                mField1dc;
    f32                mField1e0;
    f32                mField1e4;
    f32                mField1e8;
    f32                mField1ec;
    f32                mField1f0;          // +0x1f0
    f32                mField1f4;
    f32                mField1f8;
    f32                mField1fc;
    f32                mField200;
    u32                mField204;          // +0x204
    u32                mField208;
    u32                mField20c;
    u32                mField210;
    f32                mField214;          // +0x214
    u32                mField218;          // +0x218
    u32                mField21c;
    u32                mField220;
    u32                mField224;
    u32                mField228;
    u32                mField22c;
    u32                mField230;
    u32                mField234;
    f32                mField238;          // +0x238
    u32                mField23c;          // +0x23c
    u8                 mPad240[4];         // +0x240
    u32                mField244;          // +0x244
    i32                mField248;          // +0x248
    i32                mField24c;          // +0x24c
    i32                mField250;          // +0x250
    u32                mStrategyClassID;   // +0x254
    cString_s0104_bcc0            mWaterColorID;      // +0x258
    f32                mField26c;          // +0x26c
    f32                mField270;
    f32                mField274;
    f32                mField278;
    f32                mField27c;
    f32                mField280;
    f32                mField284;
    f32                mField288;
    f32                mField28c;
    f32                mField290;
    f32                mField294;
    f32                mField298;          // +0x298

    void baseCtorRaw();                                        // 0x00c87660
    void baseDtorRaw();                                        // 0x00c87770
    cSPSpaceToolData_s0104_bcc0();
    ~cSPSpaceToolData_s0104_bcc0();

    u8   FUN_00c87580(cOutStream* stream);                     // 0x00c87580
    u8   Write(cOutStream* stream);                            // 0x0104bcc0
    u32  FUN_0104bd50();                                       // 0x0104bd50
    i32  FUN_0104bde0();                                       // 0x0104bde0
    i32  FUN_0104be00();                                       // 0x0104be00
    f64  FUN_0104be30();                                       // 0x0104be30
    i32  FUN_0104bfa0();                                       // 0x0104bfa0
    u8   FUN_0104bff0();                                       // 0x0104bff0
    u8   FUN_0104c010();                                       // 0x0104c010
    bool func48h();                                            // 0x0104ca20
    bool IsInContext();                                        // 0x0104cb70
    void FUN_0104cbd0(i32 delta);                              // 0x0104cbd0
    void FUN_0104cc00(i32 amount);                             // 0x0104cc00
    u32  IsDeselectedAfterUse();                               // 0x0104cc40
    u8   FUN_0104cc90();                                       // 0x0104cc90
    u8   FUN_0104cdb0(cIface* target);                         // 0x0104cdb0
};
}
// ---- items of slice s0104bcc0 end

// @ 0x01040730
cSpaceTuningInit* __thiscall cSpaceTuningInit::FUN_01040730()
{
    float one = _HK_REAL_ONE;
    m24 = DAT_014853bc;
    _ReadWriteBarrier();
    m2c = DAT_01473c70;
    m00 = 0;
    m04 = 0;
    m08 = 0;
    m0c = 0;
    m10 = 0;
    m14 = 1;
    m18 = one;
    m1c = one;
    m20 = one;
    m28 = one;
    m30 = one;
    m34 = one;
    m38 = 0.0f;
    m3c = 0;
    m3d = 0;
    m40 = one;
    m44 = one;
    m48 = 0.0f;
    m4c = 0.0f;
    m50 = 0;
    m51 = 0;
    m52 = 0;
    return this;
}

// @ 0x01044360
namespace SP {
bool __cdecl FUN_01044360()
{
    return TravelToSystem(0x640b84cf);
}
}  // namespace SP

// @ 0x01044640
namespace SP {
bool __cdecl FUN_01044640()
{
    return TravelToSystem(0xcb74853c);
}
}  // namespace SP

// @ 0x01044920
namespace SP {
bool __cdecl FUN_01044920()
{
    cApp* app = App();
    cCameraController* camera = app->GetCameraController();
    cPlanetView* view = camera->GetPlanetView();
    if (!view)
        return false;
    void* object = view->FindObject(0x303154cd);
    if (!object)
        return false;
    FUN_00b3d4a0();
    if (FUN_00ae9390())
        return false;
    if (((uint8_t*)GameTimeManager())[0x48] & 1)
        return false;
    void* game = SpaceGameGet();
    cPlayerInventory* inventory = ((cSPSimulatorSpaceGame*)game)->GetPlayerInventory();
    if (!inventory->mpOwner->HasItem(&gBannerName))
        return false;
    if (((char*)GetUFOSimulator())[0x20])
        return false;
    SubsystemVec* vec = NounManager()->GetSubsystemVec((void*)0x0142db2a);
    void** it = vec->mpBegin;
    void** last = vec->mpEnd;
    while (it != last) {
        void* entry = *it;
        if (((bool (__thiscall*)(void*))((void**)*(void**)entry)[0x24 / 4])(entry))
            return false;
        ++it;
    }
    return true;
}
}  // namespace SP

// @ 0x01049a20
void cTerraformTuning::Init()
{
	PropertyManager()->GetPropertyList(0xa6d1bc70, 0x2ae0c7e, mPropList = 0);
}

// @ 0x01049f50
const wchar_t* cSpaceTokenTranslator::FUN_01049f50(int index)
{
	if (index < mTerraformingLevelString.Size())
		return mTerraformingLevelString.mpBegin[index].GetText();
	return kEmptyString16;
}

// @ 0x0104a020
cSpaceTokenTranslator::cSpaceTokenTranslator()
: mpPlanet(0), mpStar(0), mpItem(0), mpMission(0), mpEmpire(0),
	  mpSpeciesProfile(0), mpBuilding(0), mpVehicle(0), mpUFO(0), mpGenericName(0),
	  mField3C(0), mField40(0.0f), mField48(0)
{
	mTechLevelString.Index(7);
	for (int i = 0; i < 7; ++i)
		mTechLevelString.mpBegin[i].Load(0x2db6dad3, kTechLevelStringIds[i], 0);

	mTerraformingLevelString.Index(4);
	for (int i = 0; i < mTerraformingLevelString.Size(); ++i)
		mTerraformingLevelString.mpBegin[i].Load(0x2db6dad3, kTerraformingLevelStringIds[i], 0);

	mAnimalTypeString.Index(4);
	for (uint32_t i = 0; i < 4; ++i)
		mAnimalTypeString.mpBegin[i].Load(0x2db6dad3, kAnimalTypeStringIds[i], 0);

	mPlantTypeString.Index(3);
	for (uint32_t i = 0; i < 3; ++i)
		mPlantTypeString.mpBegin[i].Load(0x2db6dad3, kPlantTypeStringIds[i], 0);

	uint32_t tableId = FNVHash("ui_space", 0x811c9dc5u, 1);
	mMoneyFormatString.Load(tableId, kMoneyFormatInstanceId, 0);
	mUiSpaceName.Load(0x2db6dad3, kUiSpaceNameInstanceId, 0);
}

// @ 0x0104bff0
u8 SP::cSPSpaceToolData_s0104_bcc0::FUN_0104bff0()
{
    if (mStrategyClassID == 0) return 1;
    return (u8)((mStrategyClassID >> 8) & 1);
}

// @ 0x0104c010
u8 SP::cSPSpaceToolData_s0104_bcc0::FUN_0104c010()
{
    if (mStrategyClassID == 0) return 1;
    return (u8)((mStrategyClassID >> 7) & 1);
}
