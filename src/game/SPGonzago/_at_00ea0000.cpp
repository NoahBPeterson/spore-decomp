// src/game/SPGonzago/_at_00ea0000.cpp -- migrated from slice(s) s00eac530, s00eab900, s00eaa9a0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00ea0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Messaging/AutoHandler.h"
#include "EA/Allocator/ZoneObject.h"
#include "SP/Audio/cMixModeManager.h"
#include "SP/cGameNounManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include <intrin.h>
#include "EA/Stopwatch.h"
#include <math.h>
#pragma warning(disable: 4100)

// ---- items of slice s00eaa9a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
struct ResourceKey { uint32_t instanceID, typeID, groupID; };
}
}
namespace SP {
namespace Audio {
class cMixMode_s00ea_a9a0 { public:
    virtual void AddRef();                              // +0
    virtual void Release();                             // +4
    uint32_t pad[0x1c];
    cMixMode_s00ea_a9a0(ResourceKey key, void* mgr);               // 0x00ea9320 (ret 0x10: key by value + manager)
    static void* operator new(size_t sz, const char* name, int a, int b, int c, int d);  // 0x00f473a0
};
}
}
namespace SP {
namespace Audio {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
}
}
namespace SP {
namespace Audio {
struct ModeNode {
    uint32_t first;
    AutoRefCount<cMixMode_s00ea_a9a0> second;
    ModeNode* mpNext;
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator {
    ModeNode* mpNode;
    ModeNode** mpBucket;
    ModeIterator(ModeNode* node, ModeNode** bucket) : mpNode(node), mpBucket(bucket) {}
    ModeIterator(ModeNode** bucket) : mpNode(*bucket), mpBucket(bucket) {}
    ModeIterator(const ModeIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
};
}
}
namespace SP {
namespace Audio {
inline bool operator==(const ModeIterator& a, const ModeIterator& b) { return a.mpNode == b.mpNode; }
}
}
namespace SP {
namespace Audio {
struct Vector3 { float x, y, z; };
}
}
namespace SP {
namespace Audio {
struct GonzagoController {
    void Activate(uint32_t subsystem, int a, int b);   // 0x00c8b130
    void SetFade(int a, float value);                  // 0x00c88a00
    void SetVolume(int a, float value);                // 0x00c8a020
    void Deactivate(int a, int b);                     // 0x00c8ad30
    char mData[0x64];
};
}
}
namespace SP {
namespace Audio {
extern const float kGonzagoOne;                        // 0x013ef548
}
}
namespace SP {
namespace Audio {
extern const float kGonzagoZero;                       // 0x014882b8
}
}
namespace SP {
namespace Audio {
class cNPCCityMusic {
public:
    cNPCCityMusic();                                    // 0x00eab4a0
    explicit cNPCCityMusic(uint32_t id);                // 0x00eab410
    cNPCCityMusic* Destroy(int flags);                  // 0x00eab4d0
    bool Load(const char* name);                        // 0x00eab2e0
    void SetPosition(const Vector3* position);          // 0x00eab340
    void ClearPosition();                               // 0x00eab390
    void SetEnabled(uint8_t enabled);                   // 0x00eab3b0
    void SetVector(const Vector3* value);               // 0x00eab3e0
    void SetGonzagoEnabled(bool enabled);               // 0x00eab860

    void* mpVtable0;                    // +0x00
    void* volatile mpVtable1;           // +0x04
    uint32_t mField08;                  // +0x08
    uint32_t mId;                       // +0x0c
    void* mHandle;                      // +0x10
    void* mpAudioObject;                // +0x14
    uint8_t mEnabled;                   // +0x18
    char pad19[0x34 - 0x19];            // +0x19
    GonzagoController mGonzago;         // +0x34
    float mGonzagoVolume;               // +0x98
    char pad9c[0x126 - 0x9c];           // +0x9c
    uint8_t mGonzagoActive;             // +0x126
    char pad127[0x12c - 0x127];         // +0x127
    float mGonzagoFade;                 // +0x12c
    float mGonzagoScale;                // +0x130
    char pad134[0x1a4 - 0x134];         // +0x134
    uint32_t mGonzagoSubsystem;         // +0x1a4
};
}
}
// ---- items of slice s00eaa9a0 end

// ---- items of slice s00eab900 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* gVtblPlaceableSound;   // 0x014883a0
extern void* gVtblPlaceableSound2;  // 0x0148838c
extern void* gVtblSpatial;          // 0x014882c8
extern float gVecA0;                // 0x016c71ac
extern float gVecA1;                // 0x016c71b0
extern float gVecA2;                // 0x016c71b4
extern float gVecB0;                // 0x016c71dc
extern float gVecB1;                // 0x016c71e0
extern float gVecB2;                // 0x016c71e4
extern void* gScenarioState;        // 0x016c7aa4
extern "C" void* FUN_006c0200();                              // 0x006c0200
extern "C" void RecordEvent4(uint32_t handle, uint32_t event, float value, uint32_t flag);  // 0x00435f40
extern "C" void FUN_00572020(void* p, int v);                 // 0x00572020
extern "C" void SetGlobalProperty(uint32_t id, float v);      // 0x005ca880
extern "C" bool __stdcall FUN_00c88940(int v);                // 0x00c88940
extern "C" uint32_t GetRecorderState();                       // 0x00435e90
extern "C" void* SP_ModelManager();                           // 0x0067dd80
extern "C" void* ScenarioTutorials_GetObject0();              // 0x00efc910
extern "C" void* ScenarioTutorials_GetObject1();              // 0x00efc8f0
extern "C" void AudioSetListener3(void* s, float x, float y, float z);  // 0x009fbc50
extern "C" int* FUN_00eedba0(void* out, void* in);            // 0x00eedba0
extern "C" float __cdecl sqrtf(float);
struct Vec3 { float x, y, z; };
struct RefObj {
    virtual void v0();
    virtual void v1();
};
struct VObj {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void* v18();
virtual void v1c();
virtual void* v20();
virtual void v24();
virtual void v28();
virtual void* v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40(float f);
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
};
struct AudioSysAT {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual int  v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void v38(uint32_t id);
    virtual void v3c(uint32_t id, float value);
    virtual void v40(uint32_t id, void* value);
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
    virtual void v58();
};
struct ModelMgr {
virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
    virtual uint32_t m28(uint32_t id, int arg);
};
struct SpatialView {
    void ctor();
    bool LoadModel(int name);
    void f00c8ad30(int a, int b);
    void f00c8b2e0();
    void f00c8a420();
    bool Write(void* stream);                               // 0x00c88a90
};
struct cGameNounManager { void* GetAvatar(); };
struct cSpatialObject {
    void* vtbl;             // +0x00
    float x;                // +0x04  (outer +0x38)
    float y;                // +0x08  (outer +0x3c)
    float z;                // +0x0c  (outer +0x40)
    uint8_t pad10[0x40];    // +0x10
    uint32_t flags;         // +0x50  (outer +0x84)
    uint8_t pad54[0x48];    // +0x54
    void* model;            // +0x9c  (outer +0xd0)

    bool f00c8a550(int name);   // 0x00c8a550
    bool LoadModel(int name);};
struct CommunityView { void func54h(const Vec3* p); };
struct GameDataView {
    void ctor();
    void dtor();
    bool Write(void* stream);                               // 0x00b18590
};
struct cVarListSerializer {
    void Construct(void* owner, void* fieldName, uint32_t id);   // 0x00692f90
    bool Serialize(void* stream);                                // 0x00692900
    uint8_t mData[0xa14];
};
extern "C" AudioSysAT* Audio_GetSystemAT();                   // 0x00a206f0
extern "C" void FUN_00657240(int a, int handle, const Vec3* pos);  // 0x00657240
extern "C" cGameNounManager* SP_NounManager();                // 0x00b3d300
void operator delete(void* p);
namespace EA {
namespace IO {
    bool WriteUint32(void* stream, const uint32_t* value, uint32_t count, int endian);  // 0x0093aa70
}
}
struct cPlaceableSound {
    void* mVtbl;            // +0x000
    void* mVtbl2;           // +0x004
    uint8_t pad008[0x0c];   // +0x008
    void* m14;              // +0x014
    uint8_t pad018[0x14];   // +0x018
    void* m2c;              // +0x02c
    uint8_t pad030[0x04];   // +0x030
    void* mSpatVtbl;        // +0x034
    float mSpatX;           // +0x038
    float mSpatY;           // +0x03c
    float mSpatZ;           // +0x040
    uint8_t pad044[0x0c];   // +0x044
    uint32_t mFlags50;      // +0x050
    uint8_t pad054[0x0c];   // +0x054
    float m60;              // +0x060
    float m64;              // +0x064
    uint8_t pad068[0x0c];   // +0x068
    uint8_t m74;            // +0x074
    uint8_t pad075[0x07];   // +0x075
    float m7c;              // +0x07c
    uint8_t pad080[0x18];   // +0x080
    float m98;              // +0x098
    void* m9c;              // +0x09c
    uint8_t pad0a0[0x0c];   // +0x0a0
    uint8_t mAc;            // +0x0ac
    uint8_t pad0ad[0x23];   // +0x0ad
    void* mD0;              // +0x0d0
    uint8_t pad0d4[0x0c];   // +0x0d4
    int mE0;                // +0x0e0
    uint8_t pad0e4[0x0c];   // +0x0e4
    uint8_t mF0;            // +0x0f0
    uint8_t pad0f1[0x07];   // +0x0f1
    float mF8;              // +0x0f8
    float mFc;              // +0x0fc
    uint8_t pad100[0x08];   // +0x100
    void* m108;             // +0x108
    void* m10c;             // +0x10c
    void* m110;             // +0x110
    int m114;               // +0x114
    int m118;               // +0x118
    void* m11c;             // +0x11c
    uint8_t m120;           // +0x120
    uint8_t m121;           // +0x121
    uint8_t m122;           // +0x122
    uint8_t m123;           // +0x123
    uint8_t m124;           // +0x124
    uint8_t m125;           // +0x125
    uint8_t m126;           // +0x126
    uint8_t m127;           // +0x127
    uint8_t m128;           // +0x128
    uint8_t m129;           // +0x129
    uint8_t m12a;           // +0x12a
    uint8_t m12b;           // +0x12b
    float m12c;             // +0x12c
    float m130;             // +0x130
    float m134;             // +0x134
    float m138;             // +0x138
    float m13c;             // +0x13c
    float m140;             // +0x140
    float m144;             // +0x144
    float m148;             // +0x148
    float m14c;             // +0x14c
    float m150;             // +0x150
    float m154;             // +0x154
    uint8_t pad158[0x0c];   // +0x158
    float m164;             // +0x164
    float m168;             // +0x168
    float m16c;             // +0x16c
    float m170;             // +0x170
    float m174;             // +0x174
    float m178;             // +0x178
    float m17c;             // +0x17c
    float m180;             // +0x180
    float m184;             // +0x184
    float m188;             // +0x188
    float m18c;             // +0x18c
    float m190;             // +0x190
    float m194;             // +0x194
    float m198;             // +0x198
    float m19c;             // +0x19c
    float m1a0;             // +0x1a0
    void* m1a4;             // +0x1a4
    void* m1a8;             // +0x1a8

    void ctorGameData();
    void f00c8a020(int a, float v);     // cSpatialObject helper on this
    void f00eab860(int v);              // 0x00eab860

    cPlaceableSound* Construct();
    void CommitAllProperties();
    void SetVolume(float v);
    void SetPitch(float v);
    float GetVolumeScaled();
    void Shutdown();
    void Update();
    void SetPosition(const Vec3* p);
    bool Write(void* stream);
    cPlaceableSound* Destroy(uint8_t flags);
};
// ---- items of slice s00eab900 end

// ---- items of slice s00eac530 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char        g_16c71e8[];                                        // 0x016c71e8
extern float       g_15a9108;                                          // 0x015a9108
#pragma warning(disable : 4035)
#define PV(n) virtual void v##n();
struct SysAT {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void Slot14(uint32_t, void**, uint32_t);   // 0x14
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual void Slot38(int);                    // 0x38
    virtual void Slot3c(int, float);             // 0x3c
    virtual void Slot40(int, int);               // 0x40
    PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void Slot58();                       // 0x58
};
struct cProperty {
    uint32_t  pad0[4];                           // +0x00
    uint16_t  pad10;                             // +0x10
    uint16_t  mnType;                            // +0x12
    float*    GetValueFloat();                   // 0x0041ea70
    uint32_t* GetValueUInt32();                  // 0x0041ea00
    bool*     GetValueBool();                    // 0x0041e920
};
struct cPropertyList_s00ea_c530 {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
virtual void f8();
virtual void fc();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
    virtual void f20();
    virtual bool Query(uint32_t id, void* out);  // +0x24
};
struct IPropsObj {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
virtual void f8();
virtual void fc();
virtual void f10();
virtual void f14();
virtual void f18();
virtual void f1c();
virtual void f20();
    virtual bool Query(uint32_t id, void* out);  // +0x24
virtual void f28();
virtual void f2c();
    virtual bool QueryFloat(uint32_t id, void* out);   // +0x30
};
struct IPropertyMgr {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
    virtual void f8();                           // +0x08
    virtual bool Get2(void* a, void* b, int, int, int, int);   // +0x0c
};
void* GetEapdObjectError();                      // 0x008de1a0 (cdecl)
void  PropertyPairRead(void* a, void* b, void* c);       // 0x00eed0b0 (cdecl)
bool  SP_GetPropertyAsVector3(void* list, uint32_t id, void* out);  // 0x006a1110
bool  SP_GetPropertyAsFloat(void* list, uint32_t id, void* out);    // 0x0040cf10
inline bool ReadFloat(cPropertyList_s00ea_c530* list, uint32_t id, float& value)
{
    cProperty* prop;
    if (list && list->Query(id, &prop) && prop->mnType == 0xd) {
        value = *prop->GetValueFloat();
        return true;
    }
    return false;
}
inline bool ReadUInt(cPropertyList_s00ea_c530* list, uint32_t id, uint32_t& value)
{
    cProperty* prop;
    if (list && list->Query(id, &prop) && prop->mnType == 0xa) {
        value = *prop->GetValueUInt32();
        return true;
    }
    return false;
}
inline bool ReadBool(cPropertyList_s00ea_c530* list, uint32_t id, uint8_t& value)
{
    cProperty* prop;
    if (list && list->Query(id, &prop) && prop->mnType == 1) {
        value = (uint8_t)*prop->GetValueBool();
        return true;
    }
    return false;
}
SysAT* GetSystemAT();                            // 0x00a206f0 (cdecl)
struct Stopwatch160 {
    uint32_t m0;                                 // +0x00  (abs +0x160)
    uint32_t m4;                                 // +0x04  (abs +0x164)
    float    m8;                                 // +0x08  (abs +0x168)
    uint32_t mc;                                 // +0x0c  (abs +0x16c)
    float    m10;                                // +0x10  (abs +0x170)
    float    m14;                                // +0x14  tempo multiplier
    float    m18;                                // +0x18  (abs +0x178)
    float    m1c;                                // +0x1c  (abs +0x17c)
    float    m20;                                // +0x20  (abs +0x180)
    float    m24;                                // +0x24  (abs +0x184)
    float    m28;                                // +0x28  (abs +0x188)
    float    m2c;                                // +0x2c  (abs +0x18c, vector3 x)
    float    m30;                                // +0x30  (abs +0x190)
    float    m34;                                // +0x34  (abs +0x194)
    void     Start();                            // 0x00435480
    int64_t  GetElapsedTimeFloat();              // 0x0093a3a0
    void     SetBoolProperty();                  // 0x0093a2e0
};
struct cCreatureBase {
    char  pad000[0x1e0];
    float m1e0;                                  // +0x1e0
};
namespace SP {
namespace Audio {
struct cPlayerCityMusic {
    char         pad000[0x100];
    uint8_t      m100;                           // +0x100  paused flag
    uint8_t      m101;                           // +0x101
    char         pad102[0x108 - 0x102];
    void*        mp108;                          // +0x108  property scratch
    void*        mp10c;                          // +0x10c  sound handle
    char         pad110[0x118 - 0x110];
    uint32_t     m118;                           // +0x118  sound id
    cPropertyList_s00ea_c530* mp11c;                        // +0x11c  property list
    uint8_t      m120;                           // +0x120
    bool         m121;                           // +0x121
    char         pad122[0x123 - 0x122];
    uint8_t      m123;                           // +0x123
    char         pad124[0x127 - 0x124];
    uint8_t      m127;                           // +0x127
    char         pad128[0x12c - 0x128];
    float        m12c;                           // +0x12c
    float        m130;                           // +0x130
    float        m134;                           // +0x134
    float        m138;                           // +0x138
    float        m13c;                           // +0x13c
    int32_t      m140;                           // +0x140
    float        m144;                           // +0x144
    float        m148;                           // +0x148
    char         pad14c[0x150 - 0x14c];
    float        m150;                           // +0x150  accumulated duration
    float        m154;                           // +0x154
    char         pad158[0x160 - 0x158];
    Stopwatch160 m160;                           // +0x160
    float*       mp198;                          // +0x198  per-slot value array
    char         pad19c[0x1a4 - 0x19c];
    uint32_t     m1a4;                           // +0x1a4
    char         pad1a8[0x1c4 - 0x1a8];
    uint32_t     m1c4;                           // +0x1c4
    uint32_t     m1c8;                           // +0x1c8
    char         pad1cc[0x1e0 - 0x1cc];
    float*       mp1e0;                          // +0x1e0  note-duration array

    cCreatureBase* GetCreature();                // 0x006c0200
    void        CommitAllProperties();           // 0x00eab900

    void        FUN_00eac530();                  // 0x00eac530
    void        SetPosition(float*);             // 0x00eacd50
    bool        SelectRhythm(uint32_t);          // 0x00eacdb0
    bool        SelectInstrument(uint32_t);      // 0x00eace30
    void        PlayMelody(uint32_t);            // 0x00eaceb0
    void        PlayNote(uint32_t);              // 0x00eacf10
    void        FUN_00eacf70(uint8_t);           // 0x00eacf70
    void        Pause(uint8_t);                  // 0x00eacff0
    long double FUN_00ead040();                  // 0x00ead040
    void        FUN_00ead090(int, float);        // 0x00ead090
    void        SetNoteDuration(int, float);     // 0x00ead0c0
};  // namespace Audio
}
}
struct cSPVector3_s00ea_c530 { float x, y, z; };
struct cSPTransform_s00ea_c530 {
    float m[12];                                     // opaque 0x30-byte transform
    cSPTransform_s00ea_c530();                                  // 0x00409930
    void SetA(const cSPVector3_s00ea_c530* v);                  // 0x006ba800
    void TransformVector(const cSPVector3_s00ea_c530* v);       // 0x0049d640
};
float*     FUN_0059aed0(float* out, const void* key, uint32_t value);  // 0x0059aed0
cSPVector3_s00ea_c530* normalized_safe(cSPVector3_s00ea_c530* out, const cSPVector3_s00ea_c530* in);    // 0x00449c20
float      CeilF(float x);                                             // 0x0083ce70
struct g16c7aa4_t { int32_t pad[0xcc / 4]; int32_t mCC; };
extern g16c7aa4_t* g_16c7aa4;                                          // 0x016c7aa4
struct CityMusicVoice {
    // --- vtable (the slots at +0x2c and +0x5c are the two used below) ------
    virtual void         V00();
    virtual void         V04();
    virtual void         V08();
    virtual void         V0c();
    virtual void         V10();
    virtual void         V14();
    virtual void         V18();
    virtual void         V1c();
    virtual void         V20();
    virtual void         V24();
    virtual void         V28();
    virtual cSPVector3_s00ea_c530*  V2c(float t);               // +0x2c
    virtual void         V30();
    virtual void         V34();
    virtual void         V38();
    virtual void         V3c();
    virtual void         V40();
    virtual void         V44();
    virtual void         V48();
    virtual void         V4c();
    virtual void         V50();
    virtual void         V54();
    virtual void         V58();
    virtual cSPVector3_s00ea_c530*  V5c(cSPVector3_s00ea_c530* out);       // +0x5c

    // --- data -------------------------------------------------------------
    void        func58h(uint32_t id);                // 0x00c886d0
    void        FUN_00eaca50(uint32_t id);           // 0x00eaca50
    char        pad04[0xe0 - 0x04];
    void*       mpE0;                                // +0xe0  pending event object
    char        padE4[0xed - 0xe4];
    uint8_t     mEd;                                 // +0xed
    char        padEE[0xf4 - 0xee];
    uint8_t     mF4;                                 // +0xf4  position initialised
    char        padF5[0xf7 - 0xf5];
    uint8_t     mF7;                                 // +0xf7
    char        padF8[0x104 - 0xf8];
    float       m104;                                // +0x104
    char        pad108[0x110 - 0x108];
    float       m110;                                // +0x110
    float       m114;                                // +0x114
    float       m118;                                // +0x118
    float       m11c;                                // +0x11c
    float       m120;                                // +0x120
    cSPVector3_s00ea_c530  mV124;                               // +0x124
};
// ---- items of slice s00eac530 end

// @ 0x00eab860
namespace SP { namespace Audio {
void cNPCCityMusic::SetGonzagoEnabled(bool enabled)
{
    if (enabled) {
        if (mGonzagoActive)
            return;
        if (mGonzagoFade == kGonzagoZero)
            return;
        mGonzagoActive = 1;
        mGonzago.Activate(mGonzagoSubsystem, 0, 1);
        mGonzago.SetFade(1, kGonzagoOne);
        mGonzago.SetVolume(1, mGonzagoScale * mGonzagoVolume);
    } else {
        if (!mGonzagoActive)
            return;
        mGonzagoActive = 0;
        mGonzago.Deactivate(1, 0);
    }
}
}}  // namespace SP::Audio

// @ 0x00eab900
void cPlaceableSound::CommitAllProperties()
{
    float level1 = 1.0f;
    float level0 = 1.0f;
    void* p = FUN_006c0200();
    if (p) {
        level1 = *(float*)((char*)p + 0x1e4);
        level0 = *(float*)((char*)p + 0x1e0);
    }
    AudioSysAT* at = Audio_GetSystemAT();
    int handle = at ? at->v20() : 0;
    m114 = handle;
    FUN_00657240(m118, handle, (const Vec3*)&mSpatX);
    RecordEvent4((uint32_t)m114, 0xc57f4567, m98, 0);
    RecordEvent4((uint32_t)m114, 0x25df0108, level1, 0);
    if (m121 != 0) {
        RecordEvent4((uint32_t)m114, 0x12d2a4d4, 1.0f, 0);
        RecordEvent4((uint32_t)m114, 0x66ef9aba, level0, 0);
        RecordEvent4((uint32_t)m114, 0xe4dd1818, m13c, 0);
        RecordEvent4((uint32_t)m114, 0x0cd928a9, m140, 0);
    } else {
        RecordEvent4((uint32_t)m114, 0x71bc3009, level0, 0);
    }
    int h = m114;
    AudioSysAT* at2 = Audio_GetSystemAT();
    if (at2) {
        at2->v38(0x3475365);
        at2->v40(0x3475385, (void*)h);
        at2->v58();
    }
}

// @ 0x00eaba90
void cPlaceableSound::SetVolume(float v)
{
    m64 = v;
    m7c = v;
    if (mF8 != 0.0f) {
        if (FUN_00c88940(1))
            f00c8a020(1, mFc * m64);
    }
    if (mE0 != 0)
        RecordEvent4((uint32_t)mE0, 0xc57f4567, m64, 0);
}

// @ 0x00eabb10
void cPlaceableSound::SetPitch(float v)
{
    m164 = v;
    if (m114 != 0)
        RecordEvent4((uint32_t)m114, 0x25df0108, v, 0);
}

// @ 0x00eabb50
float cPlaceableSound::GetVolumeScaled()
{
    return m154 * m60;
}

// @ 0x00eabba0
cPlaceableSound* cPlaceableSound::Construct()
{
    ctorGameData();
    ((SpatialView*)((char*)this + 0x34))->ctor();
    mVtbl = &gVtblPlaceableSound;
    mVtbl2 = &gVtblPlaceableSound2;
    mSpatVtbl = &gVtblSpatial;
    _ReadWriteBarrier();  // keep the original store groups in source order
    m108 = 0;
    m10c = 0;
    m110 = 0;
    m114 = 0;
    m118 = 0;
    m11c = 0;
    _ReadWriteBarrier();
    m144 = 60.0f;
    m148 = 90.0f;
    m14c = -1.0f;
    m150 = 0.1f;
    m154 = 2.0f;
    m16c = 2.0f;
    _ReadWriteBarrier();
    m120 = 0;
    m121 = 0;
    m122 = 0;
    m123 = 0;
    m124 = 0;
    m126 = 0;
    m127 = 0;
    m128 = 0;
    m129 = 0;
    m12a = 0;
    m12b = 0;
    _ReadWriteBarrier();
    m130 = 0.0f;
    m134 = 0.0f;
    m138 = 0.0f;
    m13c = 0.0f;
    m140 = 0.0f;
    _ReadWriteBarrier();
    m164 = 1.0f;
    m168 = 0.0f;
    m170 = 1.0f;
    m174 = 1.0f;
    m178 = 0.0f;
    m17c = 5.0f;
    m180 = 0.0f;
    m184 = 5.0f;
    m188 = 1.0f;
    _ReadWriteBarrier();
    m125 = 1;
    _ReadWriteBarrier();
    m18c = gVecB0 * 7.0f;
    m190 = gVecB1 * 7.0f;
    m194 = gVecB2 * 7.0f;
    _ReadWriteBarrier();
    m198 = gVecA0;
    m19c = gVecA1;
    m1a0 = gVecA2;
    m1a4 = 0;
    m1a8 = 0;
    return this;
}

// @ 0x00eabe10
void cPlaceableSound::Shutdown()
{
    if (m114 != 0) {
        FUN_00572020((void*)m114, 0);
        m114 = 0;
    }
    if (m129 != 0) {
        SetGlobalProperty(0x8dff6314, 0.0f);
        m129 = 0;
    }
    if (m126 != 0) {
        m126 = 0;
        ((SpatialView*)((char*)this + 0x34))->f00c8ad30(1, 0);
    }
    if (m2c != 0) {
        void* p = m2c;
        m2c = 0;
        ((RefObj*)p)->v1();
    }
    ((SpatialView*)((char*)this + 0x34))->f00c8b2e0();
}

// @ 0x00eabe90
bool cSpatialObject::LoadModel(int name)
{
    flags |= 8;
    bool ok = f00c8a550(name);
    if (model != 0) {
        ModelMgr* mgr = (ModelMgr*)SP_ModelManager();
        int m = (int)model;
        uint32_t id = mgr->m28(0x6669387, 0);
        if (id < 0x40) {
            uint32_t* p = (uint32_t*)(m + 0x44 + (id >> 5) * 4);
            *p |= 1u << (id & 0x1f);
        }
        *(uint32_t*)((int)model + 4) |= 2;
        int m2 = (int)model;
        int tmp[3];
        int* r = FUN_00eedba0(tmp, (char*)this - 0x34);
        *(int*)(m2 + 0x4c) = r[0];
        *(int*)(m2 + 0x50) = r[1];
        *(int*)(m2 + 0x54) = r[2];
    }
    return ok;
}

// @ 0x00eabf30
void cPlaceableSound::Update()
{
    int state = *(int*)((char*)gScenarioState + 0xcc);
    if (state == 2 && mD0 != 0)
        *(uint32_t*)((char*)mD0 + 4) &= ~1u;

    void* obj = FUN_006c0200();
    if (!obj)
        return;
    if (m14 == 0)
        return;
    ((VObj*)m14)->v14();

    int model = (int)mD0;
    int tmp[3];
    FUN_00eedba0(tmp, this);
    *(int*)(model + 0x4c) = tmp[0];
    *(int*)(model + 0x50) = tmp[1];
    *(int*)(model + 0x54) = tmp[2];

    if (m98 != *(float*)((char*)obj + 0x20))
        ((VObj*)((char*)this + 0x34))->v40(*(float*)((char*)obj + 0x20));

    float f = *(float*)((char*)obj + 0x1e4);
    if (m164 != f)
        SetPitch(f);

    uint8_t selected = (uint8_t)(mAc == 0);
    if (m125 == 0 && selected)
        m122 = 0;
    m125 = selected;

    uint8_t isTutorial = 0;
    uint8_t isScenario = 0;
    if (state == 1) {
        isTutorial = (uint8_t)(ScenarioTutorials_GetObject0() == obj);
        isScenario = (uint8_t)(ScenarioTutorials_GetObject1() == obj);
    }
    uint8_t wasSelected = m125;

    if (m129 != isTutorial) {
        m129 = isTutorial;
        SetGlobalProperty(0x8dff6314, isTutorial ? 1.0f : 0.0f);
    }

    bool skip = false;
    if (m127 == 0) {
        if (m120 != 0) {
            if (isTutorial && m12a == 0) {
                if (m12c != 0.0f && state == 1)
                    CommitAllProperties();
            }
        } else {
            skip = true;
        }
    }
    if (!skip && m120 != 0) {
        if (state == 2) {
            cGameNounManager* mgr = SP_NounManager();
            void* avatar = mgr->GetAvatar();
            if (avatar) {
                Vec3* pos = (Vec3*)((VObj*)((char*)avatar + 0xc0))->v2c();
                float dx = pos->x - mSpatX;
                float dy = pos->y - mSpatY;
                float dz = pos->z - mSpatZ;
                float dist = sqrtf(dz * dz + (dy * dy + dx * dx));
                if (m12c * m98 > dist) {
                    if (m125 != 0 && m122 == 0) {
                        m122 = 1;
                        CommitAllProperties();
                    }
                } else {
                    if (m122 != 0 && m123 != 0) {
                        FUN_00572020((void*)m114, 0);
                        m114 = 0;
                    }
                }
            }
        }
    }
    if (m120 == 0) {
        if (m124 != 0 && wasSelected != 0 && m118 != 0 && m114 == 0) {
            m114 = (int)GetRecorderState();
            AudioSysAT* at = Audio_GetSystemAT();
            if (at) {
                at->v38(0x3475365);
                at->v40(0x3475381, (void*)m118);
                at->v40(0x3475385, (void*)m114);
                at->v3c(0x3475391, mSpatX);
                at->v3c(0x3475395, mSpatY);
                at->v3c(0x3475398, mSpatZ);
                at->v3c(0xc57f4567, m98);
                at->v3c(0x25df0108, *(float*)((char*)obj + 0x1e4));
                at->v3c(0x71bc3009, *(float*)((char*)obj + 0x1e0));
                at->v58();
            }
        }
    }

    f00eab860((isScenario || isTutorial) ? 1 : 0);
    if (m114 != 0 && wasSelected == 0) {
        FUN_00572020((void*)m114, 0);
        m114 = 0;
    }
    m12a = isTutorial;
}

// @ 0x00eac310
void cPlaceableSound::SetPosition(const Vec3* p)
{
    ((CommunityView*)this)->func54h(p);
    uint8_t wasActive = m74;
    mF0 = 1;
    if (wasActive != 0 && mE0 != 0)
        AudioSetListener3((void*)mE0, p->x, p->y, p->z);
}

extern SP::cDataSerializerGeneric gPlaceableSoundSerializer;  // 0x015a912c

// @ 0x00eac360
bool cPlaceableSound::Write(void* stream)
{
    VObj* __restrict holder = static_cast<VObj*>(((VObj*)stream)->v20());
    uint32_t id = 0x74e0069;
    void* out = holder->v18();
    EA::IO::WriteUint32(out, &id, 1, 0);
    bool ok = ((GameDataView*)this)->Write(stream)
           && ((SpatialView*)((char*)this + 0x34))->Write(stream);
    SP::cVarListSerializer ser(this, &gPlaceableSoundSerializer,
        SP::cVarListSerializer::kSignature);
    if (ok && ser.Serialize(*static_cast<SP::cIObjectDatabaseOStream*>(stream)))
        return true;
    return false;
}

// @ 0x00eac4c0
cPlaceableSound* cPlaceableSound::Destroy(uint8_t flags)
{
    mVtbl = &gVtblPlaceableSound;
    mVtbl2 = &gVtblPlaceableSound2;
    mSpatVtbl = &gVtblSpatial;
    _ReadWriteBarrier();  // the original keeps the m1a8 load after the vtable stores
    RefObj* p = (RefObj*)m1a8;
    if (p != 0) {
        p->v1();
    }
    if (m11c != 0) {
        RefObj* q = (RefObj*)m11c;
        q->v1();
    }
    ((SpatialView*)((char*)this + 0x34))->f00c8a420();
    ((GameDataView*)this)->dtor();
    if (flags & 1)
        operator delete(this);
    return this;
}

// @ 0x00eac530
void SP::Audio::cPlayerCityMusic::FUN_00eac530()
{
    PropertyPairRead(&mp108, &m160.m10, &m160.m14);

    IPropertyMgr* mgr = (IPropertyMgr*)GetEapdObjectError();
    if (mp11c != 0) {
        cPropertyList_s00ea_c530* old = mp11c;
        mp11c = 0;
        old->Release();
    }
    mgr->Get2(&mp108, &mp11c, 0, 0, 0, 0);

    if (mp11c != 0) {
        ReadUInt (mp11c, 0x6dba9e07, m1a4);
        ReadFloat(mp11c, 0xcce9e754, m160.m28);
        SP_GetPropertyAsVector3(mp11c, 0xb14ca983, &m160.m2c);
        SP_GetPropertyAsVector3(mp11c, 0x4888547a, &mp198);
        ReadFloat(mp11c, 0x8d3ef5d0, m160.m18);
        ReadFloat(mp11c, 0x4102db36, m160.m1c);
        ReadFloat(mp11c, 0x0eb4af2d, m160.m20);
        ReadFloat(mp11c, 0x298a6aff, m160.m24);
        ReadUInt (mp11c, 0xb6878619, m118);
        ReadBool (mp11c, 0xc125ef88, m120);
        m121 = ReadFloat(mp11c, 0x66ef9aba, m138)
            && ReadFloat(mp11c, 0xe4dd1818, m13c)
            && SP_GetPropertyAsFloat(mp11c, 0x0cd928a9, &m140);
        if (m121) {
            ReadFloat(mp11c, 0x7d383db4, m144);
            ReadFloat(mp11c, 0x61709942, m148);
            m148 = m148 + 1.0f;
        }
        ReadFloat(mp11c, 0xc9a583f6, m160.m8);
        ReadFloat(mp11c, 0xc9a583f6, m160.m8);
        ReadFloat(mp11c, 0xddd19567, m150);
        ReadFloat(mp11c, 0xd861c661, m154);
    }

    IPropsObj* local = 0;
    SysAT* sys = GetSystemAT();
    if (sys != 0) {
        if (local != 0) {
            IPropsObj* old = local;
            local = 0;
            old->Release();
        }
        sys->Slot14(m118, (void**)&local, 0x21407ee);
    }
    if (local != 0) {
        local->QueryFloat(0xf616b72, &m130);
        local->QueryFloat(0x3593710, &m134);
        local->Query(0x6dd08218, &m127);
    }
    if (m127) {
        if (m120)
            m120 = 0;
    }
    if (m127) {
        m12c = m134;
        m123 = 1;
    } else {
        m12c = m130;
    }
    ReadBool(mp11c, 0xda75d09a, m123);
    if (local != 0)
        local->Release();
}

// @ 0x00eaca50
void CityMusicVoice::FUN_00eaca50(uint32_t id)
{
    func58h(id);                                     // 0x00c886d0

    if (mF7 == 0)
        return;
    if (g_16c7aa4->mCC != 1)
        return;

    SP::Audio::cPlayerCityMusic* owner = (SP::Audio::cPlayerCityMusic*)((char*)this - 0x34);
    cCreatureBase* creature = owner->GetCreature();  // 0x006c0200
    if (creature == 0)
        return;

    float range;
    if (mEd != 0)
        range = m114 - m110;
    else
        range = m120 - m11c;
    if (range == 0.0f)
        return;

    // the vector this voice samples its position into (reused by both halves)
    cSPVector3_s00ea_c530 v;

    if (mF4 == 0) {
        float* p = FUN_0059aed0(&v.x, g_16c71e8, id);
        mV124.x = p[0];
        mV124.y = p[1];
        mV124.z = p[2];

        if (mEd != 0) {
            if (creature->m1e0 == 1.0f)
                creature->m1e0 = m104;
        }
        cSPTransform_s00ea_c530 xf;                             // 0x00409930
        float lo, hi;
        if (mEd != 0) {
            lo = m110;
            hi = m114;
        } else {
            lo = m11c;
            hi = m120;
        }
        cSPVector3_s00ea_c530* n = normalized_safe(&v,
            V2c((creature->m1e0 - lo) * g_15a9108 / (hi - lo)));   // 0x00449c20
        xf.SetA(n);                                  // 0x006ba800
        xf.TransformVector(&mV124);                  // 0x0049d640
        mF4 = 1;
    }

    cSPVector3_s00ea_c530* q = V5c(&v);                         // vtable +0x5c
    long double dot = mV124.x * (long double)q->x
                    + mV124.y * (long double)q->y
                    + mV124.z * (long double)q->z;
    float t = (float)(acos(dot) / g_15a9108);        // 0x011e08c8

    float lo, hi;
    if (mEd != 0) {
        lo = m110;
        hi = m114;
    } else {
        lo = m11c;
        hi = m120;
    }
    t = lo + (hi - lo) * t;
    if (t == creature->m1e0)
        return;
    creature->m1e0 = t;

    if (mEd == 0) {
        void* ev = mpE0;
        if (ev == 0)
            return;
        RecordEvent4((uint32_t)ev, 0x71bc3009, t, 0);   // 0x00435f40
    } else {
        long double c = CeilF(t);                    // 0x0083ce70
        if (m118 == c)
            return;
        m118 = (float)c;
        owner->CommitAllProperties();                // 0x00eab900
    }
}
