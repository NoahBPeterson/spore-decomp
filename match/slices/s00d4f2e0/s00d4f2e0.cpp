// Slice s00d4f2e0 -- Spore Simulator drama-event cluster (cUFOAbductionEvent +
// cMeteorStrikeEvent).  Range 0x00d4f8f0..0x00d50380.  Module: SPGonzago/SPDrama.obj
//
//   0x00d4f8f0  SP::cUFOAbductionEvent::TriggerEvent   (553 B)
//   0x00d4fb20  SP::cUFOAbductionEvent::ShutdownEvent  (198 B)
//   0x00d4fbf0  SP::cUFOAbductionEvent::TickEvent      (255 B)
//   0x00d4fcf0  SP::cMeteorStrikeEvent::cMeteorStrikeEvent (169 B)
//   0x00d4fea0  SP::cMeteorStrikeEvent::ShouldDeactivate  ( 68 B)
//   0x00d4fef0  SP::cMeteorStrikeEvent::PostLoad       ( 85 B)
//   0x00d4ff50  SP::cMeteorStrikeEvent::ShouldActivate (229 B)
//   0x00d50040  FUN_00d50040                           (532 B)
//   0x00d50260  SP::cMeteorStrikeEvent::Write          (138 B)
//   0x00d502f0  FUN_00d502f0                           (134 B)
//
// The dev PDB layout of the drama-event classes is 0x10 below the retail one, so
// the classes below model the members at the retail offsets read from the
// disassembly (same convention as slices s00d4a930 / s00d4d5c0 / s00d50380).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef unsigned long long u64;

// ------------------------------------------------------------------ small types
struct cSPVector2 { float x, y; };      // SP::cSPVector2 (struct, 8 bytes)
struct Vec3       { float x, y, z; };

// eastl::vector_map<u32,u32>: {begin,end,capacity}; operator[] (0x00564a10)
// returns a pointer to the value slot of the (key,value) pair.
struct VecMapU32 {
    u32* mpBegin;   // +0x00
    u32* mpEnd;     // +0x04
    u32* mpCap;     // +0x08
    u32* Index(const u32& key);          // 0x00564a10
};

// SP::cPropertyList is a *class* (PAV in the mangled names).
struct Property {
    float* mpData;      // +0x00   the typed value
    u8     m_pad04[0xc];
    u8     m_flags10;   // +0x10
    u8     m_pad11;
    u16    m_type12;    // +0x12   EA property type tag (0xd == float, 0xa == uint)
    float* GetFloat();  // 0x0041ea70
    u32*   GetUInt();   // 0x0041ea00
};
class cPropertyList {
  public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool FindProperty(u32 id, Property** ppOut);      // +0x24
};

// ::EA::Audio::GetSystemAT() result; only these vtable slots are used.
struct AudioSystem {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34();
    virtual void v38(u32 id);                    // +0x38
    virtual void v3c(u32 id, float value);       // +0x3c
    virtual void v40(u32 id, u32 flags);         // +0x40
    virtual void a44(); virtual void a48(); virtual void a4c(); virtual void a50();
    virtual void a54();
    virtual void v58();                          // +0x58
};

// Interface embedded in a creature/avatar at +0xc0; slot +0x2c returns a float*.
struct AnchorIface {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28();
    virtual float* GetPos();                     // +0x2c
};
// The avatar's +0xc0 sub-object also exposes a path query at slot +0x2c.
struct AnchorPath {
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0c();
    virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28();
    virtual void* v2c(float value, u8** out, u32 a, u32 b);   // +0x2c
};

// cGameNounManager.
struct cGameNounManager {
    void* GetAvatar();          // 0x00b1fdb0
    void* GetPlayerTribe();     // 0x00b1fe90
    void  RemoveNoun(void* n);  // 0x00b225d0
};

// ------------------------------------------------------------------ extern globals
extern const float kEps;        // 0x013ec4b8
extern const float kOne;        // 0x01485720
extern float gVec0169e440[3];   // 0x0169e440  default vector (unset marker)
extern const float kF_13eecd8;  // 0x013eecd8  default impact-scale scalar (20.0)
extern const float kMilli;      // 0x013f9428  (0.001 ms -> s)
extern u8 gGameModeA;           // 0x01654c01
extern u8 gGameModeB;           // 0x01654c02

// The game's global EA random linear-congruential generator.
struct RandomLCG {
    u32    RandomUint32Uniform(u32 range);   // 0x00a68fb0
    double RandomDoubleUniform();            // 0x009360d0
};
extern RandomLCG gRand;         // 0x01601760

// ------------------------------------------------------------------ helpers
struct GameTimeMgr {
    u64 FUN_00b316c0();          // 0x00b316c0
};

extern "C" {
    void* __cdecl GetCurrentGameMode();              // 0x00b5b800
    void* __cdecl SP_NounManager();                  // 0x00b3d300
    void* __cdecl SP_GameTimeManager();              // 0x00b3d380
    void* __cdecl SP_PropertyManager();              // 0x0067de30
    void* __cdecl GetSystemAT();                     // 0x00a206f0
    void* __cdecl SP_SetGameDataOwner2(void* d, void* o);  // 0x00bfc5f0
    void* __cdecl SP_PlanetModel(void* a = 0, ...);   // 0x00b3d350
    void* __cdecl SP_EffectsManager();               // 0x0067ddd0
    void  __cdecl SetGlobalProperty(u32 id, float v);     // 0x005ca880
    void* __cdecl MapLowerBound(void* first, void* last, const u32* key, u32 flag); // 0x00d01260
    void  __cdecl DestroyCreature(void* c, u32 flags);    // 0x0102c340
    void  __cdecl FUN_00d4e8e0(void* p);             // 0x00d4e8e0
    void  __cdecl FUN_00d4edd0(u32 a, void* b);      // 0x00d4edd0
    void  __cdecl FUN_00bc97f0(u32 a, u32 b, float c, u32 d); // 0x00bc97f0
    u32   __cdecl FUN_00bc96a0(void* self, u32 a, u32 b);     // 0x00bc96a0
    void  __cdecl FUN_00c38740(void* self, float dt, u64 t);  // 0x00c38740
    void* __cdecl FUN_00d4c1b0(float* pos, float scale, char flag); // 0x00d4c1b0
    bool  __cdecl FUN_0093aa70(void* istream, const void* data, u32 count, u32 flags); // 0x93aa70 WriteUint32
    void  __cdecl FUN_00f47380(void* p);             // 0x00f47380 operator delete[]
    void* __cdecl FUN_00b3d440(void* a);             // 0x00b3d440
    void  __cdecl FUN_00b09340(void* self, void* a, void* b, u32 c, u32 d); // 0x00b09340
    void* __cdecl SP_Matrix3FromQuaternion(void* out, void* q);  // 0x0059c190
    void* __cdecl FUN_00b7f190(void* self, void* a, void* b);    // 0x00b7f190
    void* __cdecl FUN_00b81780(void* self, void* a, void* b, float c, float d, ...); // 0x00b81780
    void  __cdecl FUN_00d4e950(void* self);                      // 0x00d4e950 Clear
    void  __cdecl FUN_00d4af80(void* self, int flag);            // 0x00d4af80 InitFromTuning
    void  __cdecl FUN_00a35070(void* dst, void* end, void* src); // 0x00a35070
}
// thesecallees (this == ecx) declared bare, then called through a __thiscall pointer.
extern "C" bool  FUN_00d4da10();
extern "C" void  FUN_00d4e950(void* self);
typedef bool (__thiscall *WriteDataThunk)(void*, void*);
typedef void (__thiscall *ClearThunk)(void*);
extern "C" void FUN_0042f530(void*, void*, void*);   // 0x0042f530 eastl vector erase

// 0x00d50040: create a meteor visual effect at `pos`; returns a ref-counted ptr.
extern "C" void* FUN_00d50040(u32 effectKey, float* pos, float a, float b);
// 0x00d502f0: drop the finished meteors from both streams.
extern "C" void  __fastcall FUN_00d502f0(void* self);

// ---------------------------------------------------------------- ref-count helpers
typedef void (__thiscall *VoidThunk)(void*);
static inline void AddRefObj(void* o)  { ((VoidThunk)(*(void***)o)[0])(o); }
static inline void ReleaseObj(void* o) { ((VoidThunk)(*(void***)o)[1])(o); }
typedef void* (__thiscall *PtrThunk1)(void*);
typedef void* (__thiscall *PtrThunk2)(void*, u32);

// ---------------------------------------------------------------- cVarListSerializer
struct cVarListSerializer {
    u8 m_data[0xa14];
    void ctor_00692f90(void* obj, const char* name, u32 sig);  // 0x692f90
    bool serialize_00692900(void* stream);                     // 0x692900
};

// ---------------------------------------------------------------- event base
// eastl::vector_map<u32,u32> element; the game-data map holds (key, AutoRef) pairs.
struct RefVec {
    u8* mBegin;            // +0x00
    u8* mEnd;              // +0x04
    u8* mCap;              // +0x08
};

// One 0x80-byte record of the fixed meteor-effect vector (sp_fixed_vector).
struct Meteors {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
    u8     m_pad0c[0x20c];              // +0x0c .. +0x218
};

union F2U { float f[2]; u32 u[2]; };
union R2U { cSPVector2 v[2]; u32 u[4]; };

// ---------------------------------------------------------------- cDramaEventInstanceData
// retail offsets: the object's own vector body begins at +0x14 and the vtable words
// live at +0x00/+0x04 (the eastl-vector body of the base is overlaid at +0x00).
// The game-data map at +0x5c stores (u32 key, AutoRefCount<cGameData>) pairs.
struct VecMapGD {
    u8*  mpBegin;   // +0x00 (+0x5c overall)
    u8*  mpEnd;     // +0x04 (+0x60 overall)
    u8*  mpCap;     // +0x08 (+0x64 overall)
    u32  mAllocLo;  // +0x0c (+0x68 overall)
    u32  mAllocHi;  // +0x10 (+0x6c overall)
    void EraseByKey(const u32* key);      // 0x00d4e8e0
};
struct cDramaEventInstanceData {
    u8             m_pad00[0x20];
    cSPVector2     m_thresh20;          // +0x20
    float          m_f28;               // +0x28
    float          m_f2c;               // +0x2c
    u8             m_pad30[4];          // +0x30 (bool flag + padding)
    float          m_f34;               // +0x34  (activation-threshold padding / arg to the property fetch)
    float          m_f38;               // +0x38  mCheckTime
    float          m_f3c;               // +0x3c  mDuration
    cPropertyList* m_pPropList40;       // +0x40
    VecMapU32      m_data44;            // +0x44
    u8             m_pad50[0xc];        // +0x50 .. +0x5c
    VecMapGD       m_gd5c;              // +0x5c  mGameDataMap
    u8             m_gdSorted70;        // +0x70
    u8             m_pad71[3];          // +0x71 .. +0x74
};

// ---------------------------------------------------------------- cUFOAbductionEvent
struct cUFOAbductionEvent : cDramaEventInstanceData {
    void TriggerEvent();                 // 0x00d4f8f0
    void ShutdownEvent();                // 0x00d4fb20
    void TickEvent(float dt);            // 0x00d4fbf0
};

// ---------------------------------------------------------------- cMeteorStrikeEvent
namespace SP {
struct cMeteorStrikeEvent : cDramaEventInstanceData {
    u8             m_b74;               // +0x74
    u8             m_pad75[3];
    i32            m_meteorCount[2][2]; // +0x78  {current,target} per stream
    F2U            m_f88;               // +0x88  strike centre from avatar
    F2U            m_f90;               // +0x90  strike range
    u32            m_u98[2];            // +0x98  effect key
    R2U            m_rangeA0;           // +0xa0  spawn-delay range
    F2U            m_timerB0;           // +0xb0  current spawn delay
    float          m_fB8;               // +0xb8
    float          m_fBC;               // +0xbc
    float          m_fC0;               // +0xc0
    float          m_fC4;               // +0xc4
    Meteors        m_meteors[2];        // +0xc8, +0x2e0

    cMeteorStrikeEvent();                // 0x00d4fcf0
    bool ShouldDeactivate();             // 0x00d4fea0
    void PostLoad(u32 unused);           // 0x00d4fef0
    bool ShouldActivate();               // 0x00d4ff50
    bool Write(void* stream);            // 0x00d50260

    void Clear();                        // 0x00d4e950
};
}

typedef SP::cMeteorStrikeEvent MeteorEvent;

// ---------------------------------------------------------------- vtable thunks
// The property manager's slot +0x2c resolves the event's property list.
struct PropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(u32 a, u32 b, cPropertyList** out);          // +0x2c
};
// A ref-counted visual-effect object held in the meteor streams.
struct EffectObj {
    virtual void AddRef();                                        // +0x00
    virtual void Release();                                       // +0x04
    virtual void e08(); virtual void e0c();
    virtual bool IsFinished();                                    // +0x10
};
// The event object's own virtual slots used after PostLoad / during Write.
struct EventVtbl {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24();
    virtual void s28(u32 flag);                                   // +0x28
    virtual void s2c();
    virtual void s30();                                           // +0x30
};
// A serialization stream and its reader (EA::IO).
struct Reader {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14();
    virtual void* v18();                                          // +0x18
};
struct Stream {
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual Reader* v20();                                        // +0x20
};

// =============================================================================
// vtable/const addresses used by the ctor.
extern u32 kVtblContentVal0;    // 0x013ec458
extern u32 kVtblMeteor0;        // 0x0147b640
extern u32 kVtblMeteor4;        // 0x0147b62c

// =============================================================================
// @ 0x00d4f8f0
void cUFOAbductionEvent::TriggerEvent()
{
    Vec3 pos;
    pos.x = gVec0169e440[0];
    pos.y = gVec0169e440[1];
    pos.z = gVec0169e440[2];

    void* mode = GetCurrentGameMode();
    if (mode == &gGameModeA) {
        cGameNounManager* mgr = (cGameNounManager*)SP_NounManager();
        void* avatar = mgr->GetAvatar();
        float* p = ((AnchorIface*)((u8*)avatar + 0xc0))->GetPos();
        pos.x = p[0]; pos.y = p[1]; pos.z = p[2];
    } else if (mode == &gGameModeB) {
        cGameNounManager* mgr = (cGameNounManager*)SP_NounManager();
        void* tribe = mgr->GetPlayerTribe();
        float* p = (float*)SP_SetGameDataOwner2(tribe, 0);
        p = ((AnchorIface*)((u8*)p + 0x120))->GetPos();
        pos.x = p[0]; pos.y = p[1]; pos.z = p[2];
    }

    if (pos.x != gVec0169e440[0] || pos.y != gVec0169e440[1] || pos.z != gVec0169e440[2]) {
        float fScale  = 0.0f;
        float fDamage = kF_13eecd8;    // 20.0f default

        if (m_pPropList40 != 0) {
            Property* p = 0;
            if (m_pPropList40->FindProperty(0x51be5fae, &p) && p->m_type12 == 0xd) {
                fScale = *p->GetFloat();
            }
        }
        if (m_pPropList40 != 0) {
            Property* p = 0;
            if (m_pPropList40->FindProperty(0x9b0ef346, &p) && p->m_type12 == 0xd) {
                fDamage = *p->GetFloat();
            }
        }

        u32 type = m_data44.mpEnd ? 0 : 0;   // mActivationType word at +0x2c area
        (void)type;
        float fCheck = m_f2c;

        double r = gRand.RandomDoubleUniform();
        bool bOk = (fScale < r) ? 1 : 0;
        if (fScale < (float)r) bOk = 0;

        void* ufo = FUN_00d4c1b0((float*)&pos, fDamage, (char)bOk);
        FUN_00bc97f0(2, 0, fCheck, 0);

        u32 amount = 0;
        if (m_pPropList40 != 0) {
            Property* p = 0;
            if (m_pPropList40->FindProperty(0x60be63b8, &p) && p->m_type12 == 0xa) {
                amount = *p->GetUInt();
            }
        }
        u32 key = 0;
        *m_data44.Index(key) = amount;
        FUN_00d4edd0(0, ufo);

        if (GetCurrentGameMode() == &gGameModeA) {
            SetGlobalProperty(0xdca3b514, 1.0f);
        }
    }
}

// =============================================================================
// @ 0x00d4fb20
void cUFOAbductionEvent::ShutdownEvent()
{
    AudioSystem* sys = (AudioSystem*)GetSystemAT();
    if (sys != 0) {
        sys->v38(0x3cdd1a9);
        sys->v40(0x34753a7, 0xdca3b514);
        sys->v3c(0x34753aa, 0.0f);
        sys->v58();
    }

    u8* begin = m_gd5c.mpBegin;
    u8* end   = m_gd5c.mpEnd;
    u32 key   = 0;
    u8* it = (u8*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || *(u32*)it > key) it = end;
    if (it == end || *(void**)(it + 4) == 0) return;

    void* obj = *(void**)(it + 4);
    void* creature = ((PtrThunk2)(*(void***)obj)[3])(obj, 0xb033b403);
    if (creature != 0) {
        DestroyCreature(creature, 0);
        m_gd5c.EraseByKey(&key);
    }
}

// =============================================================================
// @ 0x00d4fbf0
void cUFOAbductionEvent::TickEvent(float dt)
{
    GameTimeMgr* mgr = (GameTimeMgr*)SP_GameTimeManager();
    u64 t = mgr->FUN_00b316c0();

    double seconds = (double)(i32)(t & 0x7fffffff) * kMilli;
    (void)dt;

    u8* begin = m_gd5c.mpBegin;
    u8* end   = m_gd5c.mpEnd;
    u32 key   = 0;
    u8* it = (u8*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || *(u32*)it > key) it = end;
    if (it == end || *(void**)(it + 4) == 0) return;

    void* obj = *(void**)(it + 4);
    void* creature = ((PtrThunk2)(*(void***)obj)[3])(obj, 0xb033b403);
    if (creature == 0) return;

    FUN_00c38740(creature, (float)seconds, t);
    void* base = *(void**)((u8*)creature + 0x6c8);
    if ((*(u8*)((u8*)base + 0x5fc) & 2) != 0) {
        if (FUN_00bc96a0((u8*)base + 8, 2, 0) == 0) {
            DestroyCreature(creature, 0);
            m_gd5c.EraseByKey(&key);
        }
    }
}

// =============================================================================
// @ 0x00d4fcf0
SP::cMeteorStrikeEvent::cMeteorStrikeEvent()
{
    u8* p = (u8*)this;
    *(u32*)(p + 8)  = 0;
    *(void**)(p + 4) = (void*)&kVtblContentVal0;
    *(u8*)(p + 0xc) = 0;
    *(u32*)(p + 0x14) = 0;
    *(u32*)(p + 0x18) = 0;
    *(u32*)(p + 0x1c) = 0;
    *(float*)(p + 0x28) = 0.0f;
    *(float*)(p + 0x2c) = 0.0f;
    *(u8*)(p + 0x30) = 1;
    *(u32*)(p + 0x34) = 0;
    *(u32*)(p + 0x38) = 0;
    *(u32*)(p + 0x3c) = 0;
    *(u32*)(p + 0x40) = 0;
    *(u32*)(p + 0x44) = 0;
    *(u32*)(p + 0x48) = 0;
    *(u32*)(p + 0x4c) = 0;
    *(u32*)(p + 0x5c) = 0;
    *(u32*)(p + 0x60) = 0;
    *(u32*)(p + 0x64) = 0;
    *(void**)(p)   = (void*)&kVtblMeteor0;
    *(void**)(p + 4) = (void*)&kVtblMeteor4;
    u8* ecx = p + 0xe0;
    *(u32*)(p + 0xdc) = 0;
    *(u32*)(p + 0x2f4) = 0;
    *(u8**)(p + 0xc8) = ecx;
    *(u8**)(p + 0xcc) = ecx;
    u8* eax = p + 0x2f8;
    ecx += 0x200;
    *(u8**)(p + 0x2e0) = eax;
    *(u8**)(p + 0x2e4) = eax;
    *(u8**)(p + 0xd0) = ecx;
    eax += 0x200;
    *(u8**)(p + 0x2e8) = eax;

    Clear();
}

// =============================================================================
// @ 0x00d4fea0
bool SP::cMeteorStrikeEvent::ShouldDeactivate()
{
    if (0.0f > m_f2c) goto ret1;
    if (m_meteorCount[0][0] != m_meteorCount[0][1]) goto ret0;
    if (m_meteorCount[1][0] != m_meteorCount[1][1]) goto ret0;
    if (m_meteors[1].mpBegin != m_meteors[1].mpEnd) goto ret0;
    if (m_meteors[0].mpBegin != m_meteors[0].mpEnd) goto ret0;
ret1:
    return 1;
ret0:
    return 0;
}

// =============================================================================
// @ 0x00d4fef0
void SP::cMeteorStrikeEvent::PostLoad(u32 unused)
{
    (void)unused;
    void* mgr = SP_PropertyManager();
    void* old = m_pPropList40;
    if (old != 0) {
        m_pPropList40 = 0;
        ((VoidThunk)(*(void***)old)[1])(old);
    }
    ((PropertyManager*)mgr)->v2c(*(u32*)&m_f34, *(u32*)&m_f3c, &m_pPropList40);
    ((EventVtbl*)this)->s28(1);
    if (m_pad00[0xc] != 0) {
        ((EventVtbl*)this)->s30();
    }
}

// =============================================================================
// @ 0x00d4ff50
bool SP::cMeteorStrikeEvent::ShouldActivate()
{
    cGameNounManager* mgr = (cGameNounManager*)SP_NounManager();
    void* avatar = mgr->GetAvatar();
    if (avatar == 0) return 0;

    float fValue = 0.0f;
    if (m_pPropList40 != 0) {
        Property* p = 0;
        if (m_pPropList40->FindProperty(0xb753f503, &p) && p->m_type12 == 0xd) {
            fValue = *p->GetFloat();
        }
    }

    u8 head[0x80];
    u8* outPtr = head;
    u8* outInit = outPtr;
    void* r = ((AnchorPath*)((u8*)avatar + 0xc0))->v2c(fValue, &outPtr, 0, 0);
    FUN_00b3d440(r);
    FUN_00b09340(r, (void*)(size_t)*(u32*)&fValue, (void*)&outPtr, 0, 0);
    bool bEmpty = (outPtr == outInit);
    if (outPtr != 0 && *(u32*)(outPtr - 4) != 0) {
        FUN_00f47380(outPtr);
    }
    return bEmpty;
}

// =============================================================================
// @ 0x00d50040
// The effect holder's transform record: a translation + a 3x3 basis.
struct Matrix3 { float m[9]; };
struct Transform {
    u16     mFlags;   // +0x00
    u16     mRev;     // +0x02
    float   mScale;   // +0x04
    float   mX;       // +0x08
    float   mY;       // +0x0c
    float   mZ;       // +0x10
    Matrix3 mMat;     // +0x14
};
struct EffectHolder {
    virtual void h00();
    virtual void h04();                                   // release
    virtual void h08(u32 arg);                            // +0x08
    virtual void h0c(); virtual void h10(); virtual void h14();
    virtual void SetTransform(Transform* t);              // +0x18
};

void* FUN_00d50040(u32 effectKey, float* pos, float a, float b)
{
    (void)a;
    EffectHolder* holder = 0;
    void* em = SP_EffectsManager();
    if (holder != 0) {
        EffectHolder* old = holder;
        holder = 0;
        old->h04();
    }

    bool ok = ((bool (*)(void*, u32, u32, EffectHolder**))((void**)*(void**)em)[0x2c / 4])
                  (em, effectKey, 0, &holder);
    if (ok) {
        Vec3 p;
        p.x = pos[0]; p.y = pos[1]; p.z = pos[2];

        // A random world position near `p`, then the surface orientation there.
        Vec3 rp;
        float* rnd = (float*)FUN_00b81780(SP_PlanetModel(), &rp, &p, 0.0f, 0.0f, pos);
        Vec3 q; q.x = rnd[0]; q.y = rnd[1]; q.z = rnd[2];

        void* orient = FUN_00b7f190(SP_PlanetModel(), &q, &p);

        // Scale the surface normal by (1/len + b).
        float inv = 1.0f / (float)sqrt((double)(q.x * q.x + (q.y * q.y + q.z * q.z)));
        float len = 1.0f / inv + b;

        Transform t;
        t.mFlags = 0; t.mRev = 0;
        t.mScale = 1.0f;
        t.mX = q.x * inv * len;
        t.mY = q.y * inv * len;
        t.mZ = q.z * inv * len;

        SP_Matrix3FromQuaternion(&t.mMat, orient);

        t.mFlags |= 4;
        t.mRev += 1;
        t.mFlags |= 2;
        holder->SetTransform(&t);
        holder->h08(0);
    }
    if (holder != 0) {
        holder->h04();
    }
    return holder;
}

// =============================================================================
// @ 0x00d50260
bool SP::cMeteorStrikeEvent::Write(void* stream)
{
    Stream* s = (Stream*)stream;
    Reader* reader = s->v20();
    u32 key = 0x5599ef6;
    void* istream = reader->v18();
    FUN_0093aa70(istream, &key, 1, 0);
    bool ok = ((WriteDataThunk)FUN_00d4da10)(this, stream);

    cVarListSerializer local;
    local.ctor_00692f90(this, (const char*)0x1583998, 0x1a80d26);
    if (ok) {
        if (local.serialize_00692900(stream)) return true;
    }
    return false;
}

// =============================================================================
// @ 0x00d502f0
void __fastcall FUN_00d502f0(void* self)
{
    u8* esi = (u8*)self + 0xcc;
    int n = 2;
    do {
        u8* edi = *(u8**)(esi - 4);
        u8* end = *(u8**)esi;
        if (edi != end) {
            u8* ebp = edi + 4;
            do {
                EffectObj* obj = *(EffectObj**)edi;
                if (obj != 0) {
                    obj->AddRef();
                }
                if (!obj->IsFinished()) {
                    if (ebp < *(u8**)esi) {
                        FUN_0042f530(ebp, *(void**)esi, edi);
                    }
                    *(u32*)esi -= 4;
                    EffectObj* t = *(EffectObj**)(*(u8**)esi);
                    if (t != 0) {
                        t->Release();
                    }
                } else {
                    edi += 4;
                    ebp += 4;
                }
                obj->Release();
            } while (edi != *(u8**)esi);
        }
        esi += 0x218;
    } while (--n != 0);
}
