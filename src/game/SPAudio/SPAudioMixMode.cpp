// src/game/SPAudio/SPAudioMixMode.cpp -- migrated from slice(s) s00ea8f90, s00ea5000, s00ea4330, s00a168c0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioMixMode.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResponseCurve.h"
#include <intrin.h>
#include <string.h>
#include "SP/cPlanetModel.h"
#include <stddef.h>
#include <math.h>
#include "SP/Audio/cMixMode.h"
#include "SP/Audio/cMixModeManager.h"

// ---- items of slice s00a168c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct Server;                         // EA::Messaging::Server
Server*   GetServer();                 // 0x00883860
struct IPrimitive {
    virtual void  v00();
    virtual int   v04();                 // AddRef
    virtual void  v08();                 // Release
    virtual void* v0c(u32);
    virtual bool  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();
    virtual bool  v20(int);
    virtual void  v24(int);
    virtual void  v28(float value, int mod);   // SetModificationSource(value, mod)
    virtual void  v2c(int);
    virtual int   v30();
    virtual void  v34();
    virtual void  v38();
};
struct PrimBase {
    void* vtbl0;    // +0x00
    void* vtbl1;    // +0x04
    void* vtbl2;    // +0x08
    void* m0c;      // +0x0c
    bool  mbDirty;  // +0x10
    u8    pad11[3];
    void* m14;      // +0x14
    void* mpConfig; // +0x18
    void* m1c;      // +0x1c
    int   m20;      // +0x20

    bool  Shutdown();                                   // 00a16e70
    bool  GetDirty(int);                                // 00a16eb0
    void  ClearDirty(int);                              // 00a16ec0
    bool  HandleMessage(int id, void* arg);             // 00a16f00
    bool  Init();                                       // 00a16f60
};
// ---- items of slice s00a168c0 end

// ---- items of slice s00ea4330 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Audio {
struct IEventModifier {
    void*          mpVtable0;                                // +0x00
    volatile void* mpVtable4;                                // +0x04
    uint32_t       mPad08;                                   // +0x08
    IEventModifier();
};  // namespace Audio
}
}
// ---- items of slice s00ea4330 end

// ---- items of slice s00ea5000 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char g_vt_013eb384;    // 0x013eb384  ??_7GB1@@6B@
extern "C" char g_vt_013ef094;    // 0x013ef094  ??_7GmeRefCount@@6B@
extern "C" char g_vt_0148734c;    // 0x0148734c
extern "C" char g_vt_0148737c;    // 0x0148737c
extern "C" char g_vt_0148738c;    // 0x0148738c
extern "C" char g_vt_014873d4;    // 0x014873d4
extern "C" char g_vt_0148741c;    // 0x0148741c
extern "C" char g_vt_01487628;    // 0x01487628
extern "C" char g_vt_01487a48;    // 0x01487a48
extern "C" char g_flt_01485720;   // 0x01485720  (1.0f)
extern "C" char g_flt_01486110;   // 0x01486110  (5.0f)
extern "C" char g_flt_01487370;   // 0x01487370  (10.0f)
extern "C" char g_flt_01485378;   // 0x01485378  (0.0f)
extern "C" char g_flt_013eb1bc;   // 0x013eb1bc  (-1.0f)
extern "C" char g_flt_01487378;   // 0x01487378  (FLT_MAX)
extern "C" char g_emptyString16;  // 0x01667bac  eastl::gEmptyString16
extern "C" char g_d_015e4ef0;     // 0x015e4ef0
extern "C" char g_flt_016c6adc;   // 0x016c6adc
extern "C" char g_flt_016c6ae0;   // 0x016c6ae0
extern "C" char g_flt_016c6ae4;   // 0x016c6ae4
void __cdecl operator_delete(void* p);        // 0x00f47380  ??3@YAXPAX@Z
int   GetSetting3();                          // 0x00401030
float FUN_0040ae50(float v);                  // 0x0040ae50
u32   FUN_00576550(float h);                  // 0x00576550
void* SP_App();                               // 0x0067dd10
void* SP_EffectsManager();                    // 0x0067ddd0
void* SP_AudioSystem();                       // 0x0067cb00
void* SP_PlanetModel();                       // 0x00b3d350
void* SP_MessageServer();                     // 0x0067dcc0
void* SP_NounManager();                       // 0x00b3d300
void* SP_RelationshipManager();               // 0x00b3d2c0
void* SP_RelationshipManager2();              // 0x00b3d3c0
u32   SP_GetCurrentGameMode();                // 0x00b5b800
void* FUN_01021230();                         // 0x01021230
void* FUN_01021260();                         // 0x01021260
void* FUN_01021300();                         // 0x01021300
void* SP_TimeOfDayInstance();                 // 0x00bc30b0
struct FUN_00e28a00_t { float FUN_00e28a00(); };   // 0x00e28a00
#define FUN_00e28a00(p) (((FUN_00e28a00_t*)(p))->FUN_00e28a00())
struct RelMgr2 { float FUN_00d00a10(void* a, void* b, int c); };  // 0x00d00a10
#define FUN_00d00a10(self,a,b,c) (((RelMgr2*)(self))->FUN_00d00a10(a,b,c))
struct RelMgr { int FUN_00b79e50(void* obj, float f, int one); };   // 0x00b79e50
#define FUN_00b79e50(self,obj,f,one) (((RelMgr*)(self))->FUN_00b79e50(obj,f,one))
struct TerrainMapSet;
struct Viewer;
struct NounManager;
struct AutoRef;
struct AutoRef { void* mp; AutoRef(void* p); };          // 0x00572660
struct NounManager { void* GetAvatar(); };               // 0x00b1fdb0
struct TerrainMapSet { float GetHeightAt(); };           // 0x00f927c0
struct Viewer { void GetCameraLocationInfo(float*, float*, float*, int); };  // 0x007c3d30
namespace vt {
    template <class R, class A>
    inline R call1(void* p, int byteoff, A a) {
        return ((R (__thiscall*)(void*, A))(*(void***)p)[byteoff / 4])(p, a);
    }
}
namespace vt {
    template <class R, class A, class B>
    inline R call2(void* p, int byteoff, A a, B b) {
        return ((R (__thiscall*)(void*, A, B))(*(void***)p)[byteoff / 4])(p, a, b);
    }
}
namespace vt {
    template <class R>
    inline R call0(void* p, int byteoff) {
        return ((R (__thiscall*)(void*))(*(void***)p)[byteoff / 4])(p);
    }
}
struct Prim {
    void* v0;       // 0x00
    void* v4;       // 0x04
    void* v8;       // 0x08
    int   refc;     // 0x0c
    char  mbDirty;  // 0x10
    float mValue;   // 0x14
    void* mpConfig; // 0x18
    int   m1c;      // 0x1c
    int   m20;      // 0x20
    int   m24;      // 0x24
    int   m28;      // 0x28
    int   m2c;      // 0x2c
    float m30;      // 0x30
    int   m34;      // 0x34
    float m38;      // 0x38
    float m3c;      // 0x3c
    float m40;      // 0x40
    float m44;      // 0x44

    bool Init();                              // 0x00a16f60
    void BaseUpdate(float dt, u32 id);        // 0x00a16ed0
    bool BaseShutdown();                      // 0x00a16e70
    void SetValue(float v);                   // slot 13 (+0x34)

    void* ScalarDeletingDtor(unsigned char flags);        // 0xea5350
    bool MsgShutdown();                                   // 0xea5650
    bool Init0();                                         // 0xea53f0
    bool Init1();                                         // 0xea54f0
    bool Init2();                                         // 0xea56a0
    void ConfigParam();                                   // 0xea5700
    void Update0(float dt, u32 id);                       // 0xea5510
    void Update1(float dt, u32 id);                       // 0xea5720
    void Update2(float dt, u32 id);                       // 0xea58c0
    void Update3(float dt, u32 id);                       // 0xea5a60
    void Update4(float dt, u32 id);                       // 0xea5bc0
    void Update5(float dt, u32 id);                       // 0xea5d60
    void Update6(float dt, u32 id);                       // 0xea5e40
    void Update7(float dt, u32 id);                       // 0xea5f20
    void Update8(float dt, u32 id);                       // 0xea5fe0
    void Update9(float dt, u32 id);                       // 0xea60a0
    void Update10(float dt, u32 id);                      // 0xea6230
    void Update11(float dt, u32 id);                      // 0xea6340
    Prim* Ctor0();                                        // 0xea55b0
    Prim* Ctor1();                                        // 0xea5830
    Prim* Ctor2();                                        // 0xea59b0
    void Ctor3();                                         // 0xea53d0 -> SetValue wrapper
    bool HandleMsg(u32 msg, float* pv);                   // 0xea57c0
};
struct MixModeManager {
    void Shutdown();                     // 0x00ea9c70
    void UpdateSounds(float t);          // 0x00ea9880
};
struct MixHolder {
    void* v0;               // 0x00
    void* v4;               // 0x04
    int   m08;              // 0x08
    MixModeManager* mMix;   // 0x0c
    void Shutdown();              // 0x00ea5380
    void UpdateSounds(float t);   // 0x00ea53b0
};
struct HandlerSub {
    void* vtbl;     // 0x00
    char  pad[0x30];
    float f34;      // 0x34
    float f38;      // 0x38
    float f3c;      // 0x3c
    float f40;      // 0x40
    bool Handle(u32 msg, float* pv);   // 0xea57c0
};
struct PlanetModel {
    char  pad24[0x24];
    void* m24;                          // 0x24
    float GetWaterHeight();             // 0x00b7e390
    bool  CheckAbove(float h);          // 0x00b7e3e0
    float FUN_00b7e430(float h, int o); // 0x00b7e430
    bool  FUN_00b7ec40();               // 0x00b7ec40
    float* FUN_00b81630(void* out, const float* dir);  // 0x00b81630
};
struct MapInfo {
    char  pad34[0x34];
    float f34;
    float f38;
    float f3c;
    float f40;
    float f44;
};
struct TimeOfDay {
    char  pad24[0x24];
    float m24;                          // 0x24
    float FUN_00bc2b30(const float* pos);// 0x00bc2b30
};
struct Terraforming {
    float FUN_00c70a20();   // 0x00c70a20
    void* FUN_00c70fb0();   // 0x00c70fb0
    float FUN_00c709d0();   // 0x00c709d0
};
struct Prim;
__forceinline void SetValueDispatch(Prim* p, float v) {
    ((void (__thiscall*)(Prim*, float))((*(void***)p)[0x34 / 4]))(p, v);
}
// ---- items of slice s00ea5000 end

// ---- items of slice s00ea8f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable: 4100)
void* __cdecl  GetSystemAT();                          // 0x00a206f0  EA::Audio::GetSystemAT
void  __cdecl  RecordEvent4(u32, u32, float, u32);     // 0x00435f40  ?RecordEvent4@@YAXIIMI@Z
void* __cdecl  EAAllocate(u32, const char*, int, int, int, int);   // 0x00f473a0
void  __cdecl  FUN_00eade60(void*);                    // 0x00eade60
u32   __cdecl  FUN_00b4f930(void*, void*);             // 0x00b4f930
void* __cdecl  FUN_011e0744(void*, const void*, u32);  // 0x011e0744  (block copy helper, returns dst)
static inline void* VT(void* obj, int off) { return ((void**) (*(void**) obj))[off / 4]; }
typedef void  (__thiscall *Fn0)(void*);
typedef void  (__thiscall *Fn1u)(void*, u32);
typedef void  (__thiscall *Fn2u)(void*, u32, u32);
typedef void  (__thiscall *Fn1f)(void*, float);
typedef float (__thiscall *Fnf0)(void*);
typedef u32   (__thiscall *Fnu0)(void*);
typedef bool  (__thiscall *Fnb1u)(void*, u32, void*, void*);
typedef void  (__thiscall *Fnv1u)(void*, u32, void*, u32);
namespace SP {
namespace Audio {
class cMixMode_s00ea_8f90;
}
}
namespace SP {
namespace Audio {
class cMixModeManager_s00ea_8f90;
}
}
namespace SP {
namespace Audio {
struct SoundVector {
    u32* mBegin;   // +0x00
    u32* mEnd;     // +0x04
    u32* mCap;     // +0x08
    u32  mAlloc[2];// +0x0c
    void VectorInsert(u32* pos, const u32* value);   // 0x00ea9440
};
}
}
namespace SP {
namespace Audio {
struct ModeNode {
    u32        first;    // +0x00 key
    cMixMode_s00ea_8f90*  second;   // +0x04 value
    ModeNode*  mpNext;   // +0x08
};
}
}
namespace SP {
namespace Audio {
struct ModeIterator {
    ModeNode*  mpNode;       // +0x00
    ModeNode** mpBucket;     // +0x04
    ModeIterator() {}        // non-trivial: returned via hidden pointer (as eastl does)
    ModeNode* operator->() const { return mpNode; }
};
}
}
namespace SP {
namespace Audio {
struct ModeMap {                       // 0x20 bytes
    u32         mPolicy;               // +0x00
    ModeNode**  mpBucketArray;         // +0x04
    u32         mnBucketCount;         // +0x08
    u32         mnElementCount;        // +0x0c
    char        mAllocator[0x10];      // +0x10
    ModeIterator find(const u32& key) const;   // 0x00645ed0 (shared hashtable::find)
    ModeNode* end_node() const { return mpBucketArray[mnBucketCount]; }
    void DoFreeNodes(ModeNode** bucketArray, u32 bucketCount);   // 0x00961d60
};
}
}
namespace SP {
namespace Audio {
struct SoundNode {
    u32        key;            // +0x00
    u32        instanceId;     // +0x04
    u32        refCount;       // +0x08
    float      fSecsSinceStop; // +0x0c
    SoundNode* mpNext;         // +0x10
};
}
}
namespace SP {
namespace Audio {
struct SoundIterator {
    SoundNode*  mpNode;
    SoundNode** mpBucket;
    SoundIterator() {}
    SoundIterator(SoundNode* n, SoundNode** b) : mpNode(n), mpBucket(b) {}
    SoundNode* operator->() const { return mpNode; }
};
}
}
namespace SP {
namespace Audio {
struct SoundMap {                      // 0x20 bytes
    u32          mPolicy;              // +0x00
    SoundNode**  mpBucketArray;        // +0x04
    u32          mnBucketCount;        // +0x08
    u32          mnElementCount;       // +0x0c
    char         mAllocator[0x10];     // +0x10
    SoundIterator find(const u32& key) const;  // 0x00db4780
    SoundNode* end_node() const { return mpBucketArray[mnBucketCount]; }
    SoundIterator erase(SoundIterator it);     // 0x00b4f930
    void insert(SoundIterator* sret, const void* value, u32 flag);  // 0x00ad9370
    void DoFreeNodes(SoundNode** bucketArray, u32 bucketCount);  // 0x007611f0
};
}
}
namespace SP {
namespace Audio {
struct Key { u32 instanceID; u32 typeID; u32 groupID; };
}
}
namespace SP {
namespace Audio {
class cMixMode_s00ea_8f90 {
 public:
    void*    mVtbl0;       // +0x00
    void*    mVtbl1;       // +0x04
    void*    mVtbl2;       // +0x08
    int      m0c;          // +0x0c
    bool     mbDirty;      // +0x10
    char     pad11[3];     // +0x11
    float    mValue;       // +0x14
    void*    mpConfig;     // +0x18
    int      m1c;          // +0x1c
    int      m20;          // +0x20
    cMixModeManager_s00ea_8f90* mManager;  // +0x24
    u32      mKeyInstance; // +0x28
    u32      mKeyType;     // +0x2c
    u32      mKeyGroup;    // +0x30
    SoundVector mA;        // +0x34 (start sounds)
    SoundVector mB;        // +0x48 (pause/instance sounds)
    SoundVector mC;        // +0x5c
    bool     mb70;         // +0x70
    bool     mbRunning;    // +0x71

    cMixMode_s00ea_8f90(cMixModeManager_s00ea_8f90* mgr, Key key);   // 0x00ea9320
    ~cMixMode_s00ea_8f90();                               // 0x00ea93c0
    bool Start();                              // 0x00ea8f90
    bool Stop(bool flag);                      // 0x00ea9260
    bool IsRunning();                          // 0x00ea8ec0 (external)
    void ConfigurePrimitive();                 // 0x00ea9550
};
}
}
namespace SP {
namespace Audio {
class cMixModeManager_s00ea_8f90 {
 public:
    void*    m00;               // +0x00  (vftable 0)
    void*    m04;               // +0x04  (vftable 1)
    int      m08;               // +0x08
    ModeMap  mModes;            // +0x0c
    SoundMap mSounds;           // +0x2c
    void*    mhServer;          // +0x4c
    void*    mhHandler;         // +0x50
    void*    mhIds;             // +0x54
    u32      mhCount;           // +0x58
    int      mhPriority;        // +0x5c
    u32      mCurrentContext;   // +0x60
    u32      mCurrentPauseElements; // +0x64
    bool     mbFlag68;          // +0x68

    void StartMode(u32 id);                     // 0x00ea9a40
    void StopMode(u32 id, bool flag);           // 0x00ea9a80
    bool IsModeActive(u32 id);                  // 0x00ea9ac0
    void RegisterSound(u32 id);                 // 0x00ea9b00
    void RemoveSound(u32 id, bool flag);        // 0x00ea99a0
    void UpdateSounds(float dt);                // 0x00ea9880
    void Shutdown();                            // 0x00ea9c70
};
}
}
namespace SP {
namespace Audio {
 static void ConfigureVector(SoundVector* v, void* cfg, u32 id); 
}  // 0x00ea9550 (defined below; used by a stub's inline body)
}
namespace SP {
namespace Audio {
void cMixMode_s00ea_8f90::ConfigurePrimitive()
{
    bool restart = (((Fnf0) VT(this, 0x1c))(this) != 0.0f);
    if (restart)
        Stop(false);

    ConfigureVector(&mA, mpConfig, 0x6c4692b7u);
    ConfigureVector(&mB, mpConfig, 0x4a253755u);
    ConfigureVector(&mC, mpConfig, 0xecdc329du);

    if (restart)
        Start();
}
}
}
// ---- items of slice s00ea8f90 end

// @ 0x00a16e70
bool PrimBase::Shutdown()
{
    Server* s = GetServer();
    if (s != 0) {
        void* payload = this ? (char*)this + 4 : 0;
        ((void (__thiscall*)(void*, void*, u32, int))((*(void***)s)[0x2c / 4]))(
            s, payload, 0x2b0c259u, 0xffffd8f1);
    }
    return true;
}

// @ 0x00a16eb0
bool PrimBase::GetDirty(int)
{
    return mbDirty;
}

// @ 0x00a16ec0
void PrimBase::ClearDirty(int arg)
{
    if (m20 == arg)
        mbDirty = false;
}

// @ 0x00a16f00
bool PrimBase::HandleMessage(int id, void* arg)
{
    if (id == 0x2b0c259) {
        char* obj = (char*)this - 4;
        int other = *(int*)((char*)arg + 0x18);
        int mine = ((int (__thiscall*)(void*))((*(void***)obj)[0x18 / 4]))(obj);
        if (other == mine)
            ((IPrimitive*)obj)->v38();
    }
    return true;
}

// @ 0x00ea4fd0
namespace SP { namespace Audio {
IEventModifier::IEventModifier()
{
    mpVtable4 = (void*)0x013ef094;
    mPad08 = 0;
    mpVtable0 = (void*)0x0148734c;
    mpVtable4 = (void*)0x01487348;
}
}}  // namespace SP::Audio

// @ 0x00ea5000
u32 __stdcall GetSurfaceTypeAt(float height)
{
    if (*(char*)(GetSetting3() + 0x1c) != 0)
        return 0;
    void* app = SP_App();
    if (vt::call0<u32>(app, 0x38) == 0xdbdba1 && *(void**)&g_d_015e4ef0 != 0)
        return FUN_00576550(height);

    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    if (planet == 0)
        return 0;
    void* obj = *(void**)((char*)SP_PlanetModel() + 0x24);
    if (obj == 0)
        return 0;

    void* effect = vt::call2<void*, u32, int>(SP_EffectsManager(), 0x8c, (u32)0x107ae878, 0);
    if (effect != 0) {
        vt::call0<void>(effect, 0x0);
        float v = vt::call1<float>(effect, 0x20, height);
        if (v == 0.0f) {
            vt::call0<void>(effect, 0x4);
            return 0;
        }
    }

    if (planet->CheckAbove(height)) {
        float d = FUN_0040ae50(height) - planet->GetWaterHeight();
        if (d > 0.5f) {
            if (effect != 0)
                vt::call0<void>(effect, 0x4);
            return 0x7fd0653au;
        }
        Terraforming* tf = (Terraforming*)FUN_01021260();
        if (tf != 0) {
            tf->FUN_00c70a20();
            bool low = (0.2f <= tf->FUN_00c70a20()) || (tf->FUN_00c70fb0() != 0) ? false : true;
            bool high = (tf->FUN_00c70a20() <= 0.8f) || (tf->FUN_00c70fb0() != 0) ? false : true;
            if (low) {
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 4;
            }
            if (high) {
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 5;
            }
        }
        float h = planet->FUN_00b7e430(height, 1);
        if (h > 0.0f) {
            if (h > 1.0f) {
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 1;
            }
            if (effect != 0)
                vt::call0<void>(effect, 0x4);
            return 2;
        }
    }

    {
        MapInfo* info = vt::call0<MapInfo*>(obj, 0xc);
        float h = (info->f44 + info->f3c) * info->f38 + info->f34;
        TerrainMapSet* set = vt::call1<TerrainMapSet*, float>(obj, 0xc, h);
        float gh = set->GetHeightAt();
        if (h > gh) {
            if (effect != 0)
                vt::call0<void>(effect, 0x4);
            return 0x2fe99727u;
        }
    }

    void* pa = vt::call2<void*, u32, int>(SP_EffectsManager(), 0x8c, (u32)0x2c9c762, 0);
    AutoRef ra(pa);
    void* pb = vt::call2<void*, u32, int>(SP_EffectsManager(), 0x8c, (u32)0x1c8a626, 0);
    AutoRef rb(pb);
    if (ra.mp != 0 && rb.mp != 0) {
        float x = vt::call1<float>(ra.mp, 0x20, height);
        if (x == 1.0f) {
            float y = vt::call1<float>(rb.mp, 0x20, height);
            if (y == 1.0f) {
                vt::call0<void>(rb.mp, 0x4);
                vt::call0<void>(ra.mp, 0x4);
                if (effect != 0)
                    vt::call0<void>(effect, 0x4);
                return 3;
            }
        }
    }
    if (rb.mp != 0)
        vt::call0<void>(rb.mp, 0x4);
    if (ra.mp != 0)
        vt::call0<void>(ra.mp, 0x4);
    if (effect != 0)
        vt::call0<void>(effect, 0x4);
    return 0;
}

// @ 0x00ea5350
void* Prim::ScalarDeletingDtor(unsigned char flags)
{
    this->v0 = &g_vt_0148734c;
    this->v4 = &g_vt_013ef094;
    if ((flags & 1) != 0)
        operator_delete(this);
    return this;
}

// @ 0x00ea5380
void MixHolder::Shutdown()
{
    if (mMix != 0) {
        mMix->Shutdown();
        MixModeManager* p = mMix;
        if (p != 0) {
            mMix = 0;
            vt::call0<void>(p, 0xc);
        }
    }
}

// @ 0x00ea53b0
void MixHolder::UpdateSounds(float t)
{
    if (mMix != 0)
        mMix->UpdateSounds(t);
}

// @ 0x00ea53d0
void Prim::SetValue(float v)
{
    float value = v;
    if (value != this->mValue) {
        --this->m20;
        this->mbDirty = 1;
        this->mValue = value;
    }
}

// @ 0x00ea53f0
bool Prim::Init0()
{
    if (!this->Init())
        return false;
    float* f = (float*)&this->m24;
    f[3] = 0.0f;    // 0x30
    f[2] = 0.0f;    // 0x2c
    f[4] = 0.0f;    // 0x34
    f[1] = 0.0f;    // 0x28
    f[0] = 0.0f;    // 0x24
    return true;
}

// @ 0x00ea5420
bool FUN_00ea5420(void* self)
{
    char c = vt::call0<char>((char*)self + 0x34, 0x58);
    return c == 0;
}

// @ 0x00ea5440
void* __cdecl FUN_00ea5440(void** range, const float* pos, bool (__cdecl* filter)(void*))
{
    void** it = (void**)*range;
    void** end = (void**)range[1];
    float bestDist = *(float*)&g_flt_01487378;
    int best = 0;
    if (it == end)
        return (void*)best;
    do {
        void* p = *it;
        if (filter(p)) {
            float* v = vt::call0<float*>((char*)p + 0x34, 0x2c);
            float dy = v[1] - pos[1];
            float dx = v[0] - pos[0];
            float dz = v[2] - pos[2];
            float d = dx * dx + dy * dy + dz * dz;
            if (bestDist > d) {
                best = (int)p;
                bestDist = d;
            }
        }
        ++it;
    } while (it != end);
    return (void*)best;
}

// @ 0x00ea54f0
bool Prim::Init1()
{
    if (!this->Init())
        return false;
    *(char*)&this->m24 = 1;
    *(float*)&this->m28 = 0.0f;
    return true;
}

// @ 0x00ea5510
void Prim::Update0(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* app = SP_App();
    if (vt::call0<u32>(app, 0x38) != 0x1654c05)
        return;
    void* lu = FUN_01021230();
    if (lu == 0)
        return;
    void* avatar = ((NounManager*)*(void**)((char*)lu + 0x48))->GetAvatar();
    void* empire = FUN_01021300();
    void* owner = *(void**)((char*)empire + 0x84);
    bool isOwner = (avatar == owner);
    *(bool*)&this->m24 = isOwner;
    if (isOwner) {
        *(float*)&this->m28 = *(float*)&g_flt_01487370;
        return;
    }
    if (avatar == (void*)-1)
        return;
    if (SP_GetCurrentGameMode() == 0xdbdba1)
        return;
    if (SP_RelationshipManager() == 0)
        return;
    *(float*)&this->m28 = FUN_00d00a10(SP_RelationshipManager(), avatar, owner, 0);
}

// @ 0x00ea55b0
Prim* Prim::Ctor0()
{
    Prim* p = this;
    *(void* volatile*)&p->v4 = &g_vt_013eb384;
    *(void* volatile*)&p->v8 = &g_vt_013ef094;
    p->refc = 0;
    p->mValue = 0.0f;
    p->mbDirty = 1;
    p->mpConfig = 0;
    p->m1c = 0;
    p->m20 = 0;
    p->v0 = &g_vt_0148738c;
    p->v4 = &g_vt_0148737c;
    p->v8 = &g_vt_01487a48;
    p->m24 = (int)&g_emptyString16;
    p->m28 = (int)&g_emptyString16;
    p->m2c = (int)&g_emptyString16 + 1;
    p->m34 = 0;
    p->m44 = *(float*)&g_flt_01486110;
    return p;
}

// @ 0x00ea5650
bool Prim::MsgShutdown()
{
    void* srv = SP_MessageServer();
    if (srv != 0) {
        void* self = this ? (void*)((char*)this + 4) : 0;
        void** vtbl = *(void***)srv;
        ((void (__thiscall*)(void*, void*, u32, u32))vtbl[0x2c / 4])(
            srv, self, (u32)0x1959007, (u32)0xffffd8f1);
    }
    return this->BaseShutdown();
}

// @ 0x00ea56a0
bool Prim::Init2()
{
    if (!this->Init())
        return false;
    void* srv = SP_MessageServer();
    if (srv != 0) {
        void* self = this ? (void*)((char*)this + 4) : 0;
        void** vtbl = *(void***)srv;
        ((void (__thiscall*)(void*, void*, u32))vtbl[0x20 / 4])(srv, self, (u32)0x1959007);
    }
    float one = *(float*)&g_flt_01485720;
    this->m3c = one;
    this->m38 = one;
    this->m40 = 0.0f;
    return true;
}

// @ 0x00ea5700
void Prim::ConfigParam()
{
    if (this->mpConfig != 0)
        vt::call2<void, u32, void*>(this->mpConfig, 0x30, (u32)0x9e3669da, (char*)this + 0x44);
}

// @ 0x00ea5720
void Prim::Update1(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    if (this->m3c != this->m38) {
        float delta = this->m38 - this->m3c;
        float dir = *(float*)&g_flt_01485378 <= delta ? *(float*)&g_flt_01485720 : *(float*)&g_flt_013eb1bc;
        float ad = (float)fabs(delta);
        float step = this->m40 * dt;
        if (step > ad)
            step = ad;
        this->m3c = step * dir + this->m3c;
    }
    SetValueDispatch(this, this->m3c);
}

// @ 0x00ea57c0
bool HandlerSub::Handle(u32 msg, float* pv)
{
    if (msg == 0x1959007) {
        float v = *pv;
        float d = v - this->f38;
        this->f34 = v;
        float f = (float)fabs(d);
        if (this->f40 != 0.0f && !(f < 1e-6)) {
            this->f3c = f / this->f40;
            return true;
        }
        this->f38 = *pv;
    }
    return true;
}

// @ 0x00ea5830
Prim* Prim::Ctor1()
{
    Prim* p = this;
    *(void* volatile*)&p->v4 = &g_vt_013eb384;
    *(void* volatile*)&p->v8 = &g_vt_013ef094;
    p->refc = 0;
    p->mbDirty = 1;
    p->mValue = 0.0f;
    p->mpConfig = 0;
    p->m1c = 0;
    p->m20 = 0;
    p->v0 = &g_vt_014873d4;
    p->v4 = &g_vt_01487628;
    p->v8 = &g_vt_01487a48;
    p->m24 = (int)&g_emptyString16;
    p->m28 = (int)&g_emptyString16;
    p->m2c = (int)&g_emptyString16 + 1;
    p->m34 = 0;
    p->m38 = 0.0f;
    return p;
}

// @ 0x00ea58c0
void Prim::Update2(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* sub = vt::call0<void*>(SP_App(), 0x50);
    void* viewer = vt::call0<void*>(sub, 0x1c);
    if (viewer == 0)
        return;
    float pos[3];
    ((Viewer*)viewer)->GetCameraLocationInfo(pos, 0, 0, 0);
    TimeOfDay* tod = (TimeOfDay*)SP_TimeOfDayInstance();
    if (tod == 0)
        return;
    float dayLen = tod->m24;
    float f = tod->FUN_00bc2b30(pos);
    // The comparison result is widened to float through the x87 unit (fild/fabs/compare
    // against 0.0f); an int local plus fabsf is what produces that exact sequence.
    float diff = this->m38 - f;
    float limit = dayLen * 0.5f;
    int near_ = diff < limit;
    if (fabsf((float)near_) != 0.0f) {
        SetValueDispatch(this, f);
        this->m38 = f;
        return;
    }
    this->m38 = f;
}

// @ 0x00ea59b0
Prim* Prim::Ctor2()
{
    Prim* p = this;
    *(void* volatile*)&p->v4 = &g_vt_013eb384;
    *(void* volatile*)&p->v8 = &g_vt_013ef094;
    p->refc = 0;
    p->mbDirty = 1;
    p->mValue = 0.0f;
    p->mpConfig = 0;
    p->m1c = 0;
    p->m20 = 0;
    p->v0 = &g_vt_0148741c;
    p->v4 = &g_vt_01487628;
    p->v8 = &g_vt_01487a48;
    p->m24 = (int)&g_emptyString16;
    p->m28 = (int)&g_emptyString16;
    p->m2c = (int)&g_emptyString16 + 1;
    p->m34 = 0;
    p->m38 = *(float*)&g_flt_016c6adc;
    p->m3c = *(float*)&g_flt_016c6ae0;
    p->m40 = *(float*)&g_flt_016c6ae4;
    return p;
}

// @ 0x00ea5a60
void Prim::Update3(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* s1 = vt::call0<void*>(SP_AudioSystem(), 0x24);
    float* p = vt::call0<float*>(s1, 0x24);
    if (p[0] != this->m38 || p[1] != this->m3c || p[2] != this->m40) {
        *(u32*)&this->m38 = *(u32*)&p[0];
        *(u32*)&this->m3c = *(u32*)&p[1];
        *(u32*)&this->m40 = *(u32*)&p[2];
        void* s2 = vt::call0<void*>(SP_AudioSystem(), 0x24);
        float f = vt::call0<float>(s2, 0x20);
        int n = 0;
        if (SP_RelationshipManager2() != 0)
            n = FUN_00b79e50(SP_RelationshipManager2(), p, f, 1);
        SetValueDispatch(this, (float)n);
    }
}

// @ 0x00ea5bc0
void Prim::Update4(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* viewer = vt::call0<void*>(SP_App(), 0x58);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    float dist = 0.0f;
    if (viewer != 0 && planet != 0) {
        if (planet->FUN_00b7ec40()) {
            float pos[3];
            ((Viewer*)viewer)->GetCameraLocationInfo(pos, 0, 0, 0);
            float invLen = (float)(1.0 / sqrt((double)pos[0] * pos[0]
                      + ((double)pos[1] * pos[1] + (double)pos[2] * pos[2])));
            float dir[3];
            dir[0] = invLen * pos[0];
            dir[1] = pos[1] * invLen;
            dir[2] = pos[2] * invLen;
            float* r = planet->FUN_00b81630(0, dir);
            dist = (float)sqrt(((double)(pos[2] - r[2]) * (pos[2] - r[2])
                    + (double)(pos[1] - r[1]) * (pos[1] - r[1]))
                    + (double)(pos[0] - r[0]) * (pos[0] - r[0]));
        }
    }
    SetValueDispatch(this, dist);
}

// @ 0x00ea5d60
void Prim::Update5(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    float v;
    if (planet == 0 || planet->m24 == 0)
        v = 0.0f;
    else
        v = *(float*)&g_flt_01485720;
    SetValueDispatch(this, v);
}

// @ 0x00ea5e40
void Prim::Update6(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    void* o = planet->m24;
    if (o != 0) {
        void** vtbl = *(void***)this;
        void* p = ((void* (__thiscall*)(void*))((*(void***)o)[0x10 / 4]))(o);
        ((void (__thiscall*)(Prim*, float))vtbl[0x34 / 4])(this, FUN_00e28a00(p));
    }
}

// @ 0x00ea5f20
void Prim::Update7(float dt, u32 id)
{
    Terraforming* tf = (Terraforming*)FUN_01021260();
    if (tf != 0) {
        void** vtbl = *(void***)this;
        float r = tf->FUN_00c709d0();
        ((void (__thiscall*)(Prim*, float))vtbl[0x34 / 4])(this, r);
    }
}

// @ 0x00ea5fe0
void Prim::Update8(float dt, u32 id)
{
    Terraforming* tf = (Terraforming*)FUN_01021260();
    if (tf != 0) {
        void** vtbl = *(void***)this;
        float r = tf->FUN_00c70a20();
        ((void (__thiscall*)(Prim*, float))vtbl[0x34 / 4])(this, r);
    }
}

// @ 0x00ea60a0
void Prim::Update9(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* viewer = vt::call0<void*>(SP_App(), 0x58);
    PlanetModel* planet = (PlanetModel*)SP_PlanetModel();
    float v = 0.0f;
    if (viewer != 0 && planet != 0) {
        if (planet->FUN_00b7ec40()) {
            float pos[3];
            ((Viewer*)viewer)->GetCameraLocationInfo(pos, 0, 0, 0);
            float invLen = (float)(1.0 / sqrt((double)pos[0] * pos[0]
                      + ((double)pos[1] * pos[1] + (double)pos[2] * pos[2])));
            float dir[3];
            dir[0] = invLen * pos[0];
            dir[1] = invLen * pos[1];
            dir[2] = pos[2] * invLen;
            float* r = planet->FUN_00b81630(0, dir);
            v = (float)sqrt(((double)r[0] * r[0] + (double)r[1] * r[1]) + (double)r[2] * r[2]);
        }
    }
    SetValueDispatch(this, v);
}

// @ 0x00ea6230
void Prim::Update10(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
    void* nm = SP_NounManager();
    if (nm == 0)
        return;
    void* av = ((NounManager*)nm)->GetAvatar();
    if (av == 0)
        return;
    float* p = vt::call0<float*>((char*)av + 0xc0, 0x2c);
    float y = p[1];
    float z = p[2];
    float x = p[0];
    SetValueDispatch(this, (float)sqrt(((double)y * y + (double)z * z)
        + (double)x * x));
}

// @ 0x00ea6340
void Prim::Update11(float dt, u32 id)
{
    this->BaseUpdate(dt, id);
}

// @ 0x00ea8f90
namespace SP { namespace Audio {
bool cMixMode_s00ea_8f90::Start()
{
    if (((Fnf0) VT(this, 0x1c))(this) != 0.0f)
        return false;

    // register every start sound with the manager
    for (u32* p = mA.mBegin; p != mA.mEnd; ++p)
        mManager->RegisterSound(*p);

    // notify the audio system for each instance sound
    for (u32* p = mB.mBegin; p != mB.mEnd; ++p) {
        void* sys = GetSystemAT();
        if (!sys)
            continue;
        ((Fn1u) VT(sys, 0x38))(sys, 0x3475376u);
        ((Fn2u) VT(sys, 0x40))(sys, 0x3475385u, *p);
        ((Fn2u) VT(sys, 0x40))(sys, 0x34753a7u, 0xb85523e5u);
        ((Fn1f) VT(sys, 0x3c))(sys, 1.0f);
        ((Fn2u) VT(sys, 0x40))(sys, 0x34753adu, 0);
        ((Fn0)  VT(sys, 0x58))(sys);
    }

    // second batch
    {
        void* sys = GetSystemAT();
        if (sys) {
            for (u32* p = mC.mBegin; p != mC.mEnd; ++p) {
                ((Fn1u) VT(sys, 0x38))(sys, 0x7ead55cu);
                ((Fn2u) VT(sys, 0x40))(sys, 0x4362049u, *p);
                ((Fn0)  VT(sys, 0x58))(sys);
            }
        }
    }

    // configuration-driven properties
    if (mpConfig != 0) {
        void* sys = GetSystemAT();
        if (sys != 0) {
            u32 a = 0, b = 0;
            ((Fn1u) VT(sys, 0x38))(sys, 0x5c2b8a3u);
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0x4f76ed4au, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0x4f76ed4au, &a, b * 4);
            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0xa6c8bfccu, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0xa6c8bfccu, &a, b * 4);
            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0xe91c6f7eu, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0xe91c6f7eu, &a, b * 4);
            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0x8750500du, &a, &b))
                ((Fnv1u) VT(sys, 0x4c))(sys, 0x8750500du, &a, b * 4);

            u32 h = ((Fnu0) VT(sys, 0x64))(sys);
            void* node = (void*) (size_t) FUN_00b4f930((void*) (size_t) h, 0);
            (void) node;
            u32 flags = 0;
            mb70 = (flags != 0);
            if (mb70)
                ((Fn0) VT(sys, 0x58))(sys);
            else
                ((Fn0) VT(sys, 0x5c))(sys);

            a = 0; b = 0;
            if (((Fnb1u) VT(mpConfig, 0x48))(mpConfig, 0x1fc4bce8u, &a, &b)) {
                ((Fn1u) VT(sys, 0x38))(sys, 0x60c62f5u);
                ((Fnv1u) VT(sys, 0x4c))(sys, 0x60c631du, &a, b * 4);
                ((Fn0)  VT(sys, 0x58))(sys);
            }
        }
    }

    ((Fn1f) VT(this, 0x34))(this, 1.0f);
    mbRunning = true;
    return true;
}
}}  // namespace SP::Audio

// @ 0x00ea9260
namespace SP { namespace Audio {
bool cMixMode_s00ea_8f90::Stop(bool flag)
{
    if (((Fnf0) VT(this, 0x1c))(this) == 0.0f)
        return false;

    ((Fn1f) VT(this, 0x34))(this, 0.0f);
    mbRunning = false;

    for (u32* p = mB.mBegin; p != mB.mEnd; ++p)
        RecordEvent4(*p, 0xb85523e5u, 0.0f, 0);

    for (u32* p = mA.mBegin; p != mA.mEnd; ++p)
        mManager->RemoveSound(*p, flag);

    void* sys = GetSystemAT();
    if (sys != 0 && mb70) {
        mb70 = false;
        ((Fn1u) VT(sys, 0x38))(sys, 0x5c2b8a3u);
        ((Fn0)  VT(sys, 0x58))(sys);
    }
    return true;
}
}}  // namespace SP::Audio

// @ 0x00ea9320
namespace SP { namespace Audio {
cMixMode_s00ea_8f90::cMixMode_s00ea_8f90(cMixModeManager_s00ea_8f90* mgr, Key key)
{
    mVtbl1 = (void*) 0x13eb384;
    mVtbl2 = (void*) 0x13ef094;
    m0c = 0;
    mbDirty = true;
    mValue = 0.0f;
    mpConfig = 0;
    mManager = mgr;
    mKeyInstance = key.instanceID;
    mKeyType = key.typeID;
    mKeyGroup = key.groupID;
    m1c = 0;
    m20 = 0;
    mVtbl0 = (void*) 0x1488000;
    mVtbl1 = (void*) 0x1487ff0;
    mVtbl2 = (void*) 0x1487fec;
    mA.mBegin = 0; mA.mEnd = 0; mA.mCap = 0;
    mB.mBegin = 0; mB.mEnd = 0; mB.mCap = 0;
    mC.mBegin = 0; mC.mEnd = 0; mC.mCap = 0;
    mb70 = false;
    mbRunning = false;
}
}}  // namespace SP::Audio

// @ 0x00ea93c0
namespace SP { namespace Audio {
cMixMode_s00ea_8f90::~cMixMode_s00ea_8f90()
{
    if (mC.mBegin) operator_delete(mC.mBegin);
    if (mB.mBegin) operator_delete(mB.mBegin);
    if (mA.mBegin) operator_delete(mA.mBegin);
    if (mpConfig)
        ((Fn0) VT(mpConfig, 0x04))(mpConfig);
    mVtbl2 = (void*) 0x13ef094;
    mVtbl1 = (void*) 0x13eb394;
    mVtbl0 = (void*) 0x13eb938;
}
}}  // namespace SP::Audio

// @ 0x00ea9440
namespace SP { namespace Audio {
void SoundVector::VectorInsert(u32* pos, const u32* value)
{
    u32* begin = mBegin;
    u32* end   = mEnd;
    u32* cap   = mCap;
    if (end != cap) {
        const u32* v = value;
        if (pos <= v && v < end)
            ++v;
        if (end)
            *end = end[-1];
        memmove(pos + 1, pos, (u32) (end - pos - 1) * 4);
        *pos = *v;
        mEnd = end + 1;
        return;
    }
    u32 count  = (u32) (end - begin);
    u32 newCap = count ? count * 2 : 1;
    u32* dst = (u32*) EAAllocate(newCap * 4, (const char*) (size_t) 0x13f09b4, 0, 0,
                                 (int) 0x13ebb38, 0xd1);
    u32 at = (u32) (pos - begin);
    u32* slot = (u32*) FUN_011e0744(dst, begin, at * 4) + at;
    if (slot)
        *slot = *value;
    u32* newEnd = (u32*) FUN_011e0744(slot + 1, pos, (u32) (end - pos) * 4) + (u32) (end - pos);
    if (begin)
        operator_delete(begin);
    mBegin = dst;
    mEnd = newEnd;
    mCap = dst + newCap;
}
}}  // namespace SP::Audio

// @ 0x00ea9550
namespace SP { namespace Audio {
static void ConfigureVector(SoundVector* v, void* cfg, u32 id)
{
    u32 cnt = 0, arr = 0;
    v->mEnd = v->mBegin;
    if (cfg == 0)
        return;
    if (!((Fnb1u) VT(cfg, 0x4c))(cfg, id, &cnt, &arr) || cnt == 0)
        return;
    FUN_00eade60((void*) (size_t) cnt);
    for (u32 i = 0; i < cnt; ++i) {
        u32 val = *(u32*) (arr + i * 0xc);
        if (v->mEnd < v->mCap)
            *v->mEnd++ = val;
        else
            v->VectorInsert(v->mEnd, &val);
    }
}
}}  // namespace SP::Audio
