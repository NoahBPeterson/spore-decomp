// Slice s00d50380: SP::cMeteorStrikeEvent (Simulator drama-event "meteor strike") cluster.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// The dev PDB layout of cMeteorStrikeEvent differs from the retail one, so the
// class below models the members at the retail offsets read from the
// disassembly; the untouched gaps are explicit padding.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;

extern "C" double sqrt(double);

// ------------------------------------------------------------------ small types
struct cSPVector2 { float x, y; };      // SP::cSPVector2 (struct, 8 bytes)
struct Vector3    { float x, y, z; };

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
    u16    m_type12;    // +0x12   EA property type tag
    float* GetFloat();  // 0x0041ea70
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

// eastl::vector_map<u32,void*> entry (8 bytes) used by mGameDataMap.
struct GDEntry { u32 mKey; void* mValue; };

// Interface embedded in a creature/avatar at +0xc0; slot +0x2c returns a float*.
struct AnchorIface {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual void a20(); virtual void a24(); virtual void a28();
    virtual float* GetPos();                     // +0x2c
};

// Object created by FUN_00b23650 (id 0x1be418e); only touched offsets are named.
struct SpawnedObj {
    u8     m_pad00[0x98];
    u8     m_v98[0xc];        // +0x98  (12-byte sub-object passed to FUN_01021260)
    u8     m_padA4[4];        // +0xa4
    void*  m_CreatureA4;      // +0xa4  (owner, ecx.add 0x504)
    u8     m_padA8[0x7c];     // +0xa8 .. +0x124
    i32    m_i124;            // +0x124
    u8     m_b128;            // +0x128
    u8     m_pad129[0x69];    // +0x129 .. +0x192
    u8     m_b192;            // +0x192
    u8     m_pad193[0x1c];    // +0x193 .. +0x1af
    u32    m_dword1af_pad;    // padding to make m_nFields reach +0xf4 range below
};

// ------------------------------------------------------------------ extern globals
extern const float kEps;        // 0x013ec4b8 (1.0e-8)
extern const float kTiny;       // 0x0147af24 (1.5258789e-05 = 2^-16)
extern const float kOne;        // 0x01485720 (1.0f)
extern const float kSeventy;    // 0x01443c8c (70.0f)
extern const float kTen;        // 0x01473c70 (10.0f)
extern const float kF_13ebc4c;  // 0x013ebc4c (default spawn-distance scalar)
extern const float kF_15d9c6c;  // 0x015d9c6c (default property scalar)
extern const float kF_14853bc;  // 0x014853bc (stimulus radius)
extern float gVec0169e440[3];   // 0x0169e440 (default vector)

// The game's global EA random linear-congruential generator.
struct RandomLCG {
    u32    RandomUint32Uniform(u32 range);   // 0x00a68fb0
    double RandomDoubleUniform();            // 0x009360d0
};
extern RandomLCG gRand;         // 0x01601760

// ------------------------------------------------------------------ managers
struct cGameNounManager {
    void* GetAvatar();          // 0x00b1fdb0
    void  RemoveNoun(void* n);  // 0x00b225d0
};
struct cViewer {
    void GetCameraLocationInfo(Vector3* a, Vector3* b, int c, int d);  // 0x007c3d30
};
struct MegaManager {              // result of FUN_00b3d480()
    void Method_aca360(void* o);  // 0x00aca360
};

// ------------------------------------------------------------------ extern helpers
extern "C" {
    bool GetPropertyAsFloatArray(cPropertyList* list, u32 id, int* pCount, float** ppOut);   // 0x006a08b0
    bool GetPropertyAsIntArray  (cPropertyList* list, u32 id, int* pCount, int**   ppOut);   // 0x006a07d0
    bool GetPropertyAsVector2Array(cPropertyList* list, u32 id, int* pCount, void** ppOut);  // 0x006a0920
    bool GetPropertyAsUint32Array (cPropertyList* list, u32 id, int* pCount, u32**  ppOut);   // 0x006a0840
    void* GetPropertyAsKeyInstance(cPropertyList* list, u32 id, void* pOut);                 // 0x006a12a0

    void* __cdecl GetSystemAT();                 // 0x00a206f0
    void* __cdecl SP_App();                      // 0x0067dd10
    void* __cdecl SP_NounManager();              // 0x00b3d300
    void* __cdecl SP_PlanetModel(void* a, void* b, ...);   // 0x00b3d350
    void* __cdecl FUN_00b3d480();                // 0x00b3d480
    void* __cdecl FUN_00d539d0();                // 0x00d539d0  cPosseSimulator::Instance
    void* __cdecl FUN_00401010();                // 0x00401010
    void* __cdecl FUN_01021260(void** p);        // 0x01021260
    void* __cdecl FUN_00b23650(u32 a, float b, u32 c, void* d, void* e);   // 0x00b23650
    void* __cdecl FUN_00c099e0(float* pos, float a, u32 b, void* c, u32 d, u32 e); // 0x00c099e0
    void  __cdecl FUN_00acd2d0(void* o);         // 0x00acd2d0
    void  __cdecl FUN_00d4e8e0(void* p);         // 0x00d4e8e0
    void  __cdecl FUN_00d4edd0(u32 a, void* b);  // 0x00d4edd0
    void* __cdecl FUN_00d4cf10(u32 a, u32 b);    // 0x00d4cf10
    void* __cdecl FUN_00d998d0(void* a, u32 b);  // 0x00d998d0
    void* __cdecl FUN_00c74690(void** a, u32 b, u32 c);  // 0x00c74690
    void* __cdecl FUN_00b82970(void* a, void* b, u32 c);  // 0x00b82970
    void  __cdecl FUN_00b7f190(void* self, void* a, void* b);  // 0x00b7f190
    void  __cdecl FUN_00b81780(void* self, void* a, void* b, float c, float d); // 0x00b81780
    void  __cdecl FUN_00c13a30(void* self, u32 a);           // 0x00c13a30
    void  __cdecl FUN_00d54330(void* self, void* o);         // 0x00d54330
    void  __cdecl FUN_00bc98f0(void* self, u32 a, u32 b);    // 0x00bc98f0
    void* __cdecl FUN_00bc97f0(u32 a, u32 b, float c, u32 d); // 0x00bc97f0
    void* __cdecl FUN_00bc96a0(void* self, u32 a, u32 b);    // 0x00bc96a0
    bool  __cdecl FUN_00d9a360(void* out12, float* dir);     // 0x00d9a360
    int   __cdecl GetTutorialToolPrice(void* plist, u32 id, int nDefault);  // 0x004e1c30
    void* __cdecl MapLowerBound(void* first, void* last, const u32* key, u32 flag); // 0x00d01260
    void* __cdecl FUN_00a0a360(void*** vecBegin, void** end, void** valuePtr);  // 0x00a0a360
}

// 0x00d50040: create a meteor visual effect at `pos`; returns a ref-counted ptr.
extern "C" void* FUN_00d50040(u32 effectKey, float* pos, float a, float b); // 0x00d50040
extern "C" void  FUN_00d502f0(void* self);                                  // 0x00d502f0

// ---------------------------------------------------------------- ref-count helpers
typedef void (__thiscall *VoidThunk)(void*);
static inline void AddRefObj(void* o) { ((VoidThunk)(*(void***)o)[0])(o); }
static inline void ReleaseObj(void* o) { ((VoidThunk)(*(void***)o)[1])(o); }
typedef void* (__thiscall *PtrThunk1)(void*);
typedef void* (__thiscall *PtrThunk2)(void*, u32);
static inline void* CallV0c(void* o, u32 a)
{
    return ((PtrThunk2)(*(void***)o)[0x0c / 4])(o, a);
}
static inline u32 CallV4c(void* o)
{
    return ((u32(__thiscall*)(void*))(*(void***)o)[0x4c / 4])(o);
}

// ---------------------------------------------------------------- cMeteorStrikeEvent
namespace SP {

struct Meteors {                        // sp_fixed_vector<AutoRefCount<cIVisualEffect>,128>
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCap;                       // +0x08
    u8     m_pad0c[0x20c];              // +0x0c .. +0x218
};

union F2U { float f[2]; u32 u[2]; };
union R2U { cSPVector2 v[2]; u32 u[4]; };

struct cMeteorStrikeEvent {
    // ---- base cDramaEventInstanceData (retail offsets observed here) ----
    u8             m_pad00[0x20];
    cSPVector2     m_thresh20;          // +0x20
    float          m_f28;               // +0x28
    float          m_f2c;               // +0x2c
    u8             m_pad30[0x10];       // +0x30 .. +0x40
    cPropertyList* m_pPropList40;       // +0x40
    VecMapU32      m_data44;            // +0x44
    u8             m_pad50[0xc];        // +0x50 .. +0x5c
    u8*            m_gdBegin5c;         // +0x5c  mGameDataMap begin
    u8*            m_gdEnd60;           // +0x60  mGameDataMap end
    u8             m_pad64[0xc];        // +0x64 .. +0x70
    u8             m_gdSorted70;        // +0x70
    u8             m_pad71[3];          // +0x71 .. +0x74
    // ---- meteor fields ----
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

    void Clear();                                                // 0x00d4e950
    void InitFromTuning(int flag);                               // 0x00d4af80
    void LoadAndInitMeteorStrikeData(cPropertyList* pList);      // 0x00d50380
    u8   FUN_00d505a0(void* pAvatar, float dt);                  // 0x00d505a0
    void ShutdownEvent();                                        // 0x00d50960
    void TickEvent(float dt);                                    // 0x00d509c0
    void FUN_00d509f0(int flag);                                 // 0x00d509f0
    void FUN_00d50a40();                                         // 0x00d50a40
    u8   FUN_00d50b80();                                         // 0x00d50b80
    u8   FUN_00d50c30();                                         // 0x00d50c30
    void FUN_00d50e40(float dt);                                 // 0x00d50e40
    void FUN_00d50ef0();                                         // 0x00d50ef0
};

} // namespace SP

typedef SP::cMeteorStrikeEvent MeteorEvent;

// =============================================================================
// @ 0x00d50380
void SP::cMeteorStrikeEvent::LoadAndInitMeteorStrikeData(cPropertyList* pList)
{
    Clear();
    m_b74 = 1;

    int     nCount = 0;
    float*  pFloat = 0;
    int*    pInt   = 0;
    void*   pVec2  = 0;
    u32*    pU32   = 0;

    if (GetPropertyAsFloatArray(pList, 0x8a788159, &nCount, &pFloat)) {
        m_f88.u[0] = ((u32*)pFloat)[0];
        m_f88.u[1] = ((u32*)pFloat)[1];
    }
    if (GetPropertyAsFloatArray(pList, 0x15585c0a, &nCount, &pFloat)) {
        m_f90.u[0] = ((u32*)pFloat)[0];
        m_f90.u[1] = ((u32*)pFloat)[1];
    }
    if (GetPropertyAsIntArray(pList, 0x5616c7e8, &nCount, &pInt)) {
        m_meteorCount[0][1] = pInt[0];
        m_meteorCount[1][1] = pInt[1];
    }
    if (GetPropertyAsFloatArray(pList, 0x9dc91e04, &nCount, &pFloat)) {
        m_timerB0.u[0] = ((u32*)pFloat)[0];
        m_timerB0.u[1] = ((u32*)pFloat)[1];
    }
    if (GetPropertyAsVector2Array(pList, 0x9920c7ca, &nCount, &pVec2)) {
        u32* src = (u32*)pVec2;
        m_rangeA0.u[0] = src[0];
        m_rangeA0.u[1] = src[1];
        m_rangeA0.u[2] = src[2];
        m_rangeA0.u[3] = src[3];
    }
    if (GetPropertyAsUint32Array(pList, 0xa45eb62d, &nCount, &pU32)) {
        m_u98[0] = pU32[0];
        m_u98[1] = pU32[1];
    }

    if (pList != 0) {
        Property* p = 0;
        if (pList->FindProperty(0x9ba81197, &p) && p->m_type12 == 13) {
            m_fB8 = *p->GetFloat();
        }
        if (pList->FindProperty(0x697c13ca, &p) && p->m_type12 == 13) {
            m_fBC = *p->GetFloat();
        }
        if (pList->FindProperty(0x4d4b5974, &p) && p->m_type12 == 13) {
            m_fC0 = *p->GetFloat();
        }
        if (pList->FindProperty(0x8a24d51c, &p) && p->m_type12 == 13) {
            m_fC4 = *p->GetFloat();
        }
    }
}

// =============================================================================
// @ 0x00d505a0
u8 SP::cMeteorStrikeEvent::FUN_00d505a0(void* pAvatar, float dt)
{
    if (m_meteorCount[0][0] == m_meteorCount[0][1] &&
        m_meteorCount[1][0] == m_meteorCount[1][1] &&
        m_meteors[1].mpBegin == m_meteors[1].mpEnd &&
        m_meteors[0].mpBegin == m_meteors[0].mpEnd)
    {
        return 0;
    }

    AnchorIface* pAnchor = (AnchorIface*)((u8*)pAvatar + 0xc0);
    float* pAnchorPos = pAnchor->GetPos();

    void* app = SP_App();
    void* p50 = ((PtrThunk1)(*(void***)app)[0x50 / 4])(app);
    cViewer* viewer = (cViewer*)((PtrThunk1)(*(void***)p50)[0x1c / 4])(p50);

    Vector3 v1, v2;
    v1.x = gVec0169e440[0]; v1.y = gVec0169e440[1]; v1.z = gVec0169e440[2];
    v2.x = gVec0169e440[0]; v2.y = gVec0169e440[1]; v2.z = gVec0169e440[2];

    if (viewer != 0) {
        viewer->GetCameraLocationInfo(&v1, &v2, 0, 0);
        float inv = 1.0f / (float)(sqrt((double)(v1.x * v1.x + (v1.z * v1.z + v1.y * v1.y)) + kEps));
        v1.x = inv * v1.x;
        v1.y = v1.y * inv;
        v1.z = v1.z * inv;
    }

    float dot = v2.y * v1.y + v2.z * v1.z + v2.x * v1.x;
    v2.y = v2.y - v1.y * dot;
    v2.z = v2.z - v1.z * dot;
    v2.x = v2.x - dot * v1.x;

    float inv2 = 1.0f / (float)(sqrt((double)(v2.x * v2.x + (v2.z * v2.z + v2.y * v2.y)) + kEps));
    v2.x = v2.x * inv2;
    v2.y = v2.y * inv2;
    float z2 = v2.z * inv2;
    v2.z = z2;

    for (int i = 0; i < 2; i++) {
        if (m_meteorCount[i][0] < m_meteorCount[i][1]) {
            float t = m_timerB0.f[i] - dt;
            m_timerB0.f[i] = t;
            if (t <= 0.0f) {
                double lo = (double)m_rangeA0.v[i].x;
                double hi = (double)m_rangeA0.v[i].y;
                double rv = gRand.RandomDoubleUniform() * (hi - lo) + lo;
                if (rv >= hi) rv = hi; else if (rv < lo) rv = lo;
                m_timerB0.f[i] = (float)rv;

                float dist = m_f88.f[i];
                float px = pAnchorPos[0] + dist * v2.x;
                float py = pAnchorPos[1] + dist * v2.y;
                float pz = pAnchorPos[2] + dist * v2.z;
                Vector3 pos; pos.x = px; pos.y = py; pos.z = pz;

                void* obj = FUN_00d50040(m_u98[i], (float*)&pos, m_fB8, m_f90.f[i]);
                if (obj != 0) AddRefObj(obj);

                Meteors* vec = &m_meteors[i];
                void** endp = vec->mpEnd;
                if (endp < vec->mpCap) {
                    vec->mpEnd = endp + 1;
                    if (endp != 0) {
                        *endp = obj;
                        if (obj != 0) AddRefObj(obj);
                    }
                } else {
                    FUN_00a0a360(&vec->mpBegin, endp, &obj);
                }
                m_meteorCount[i][0] = m_meteorCount[i][0] + 1;
                if (obj != 0) ReleaseObj(obj);
            }
        }
    }

    FUN_00d502f0(this);
    return 1;
}

// =============================================================================
// @ 0x00d50960
void SP::cMeteorStrikeEvent::ShutdownEvent()
{
    AudioSystem* sys = (AudioSystem*)GetSystemAT();
    if (sys != 0) {
        sys->v38(0x3cdd1a9);
        sys->v40(0x34753a7, 0x413df353);
        sys->v3c(0x34753aa, 0.0f);
        sys->v58();
    }
    Clear();
}

// =============================================================================
// @ 0x00d509c0
void SP::cMeteorStrikeEvent::TickEvent(float dt)
{
    cGameNounManager* mgr = (cGameNounManager*)SP_NounManager();
    void* avatar = mgr->GetAvatar();
    FUN_00d505a0(avatar, dt);
}

// =============================================================================
// @ 0x00d509f0
void SP::cMeteorStrikeEvent::FUN_00d509f0(int flag)
{
    InitFromTuning(flag);
    if (m_pPropList40 != 0 && (u8)flag == 0) {
        int n = (int)m_thresh20.x;
        u32 r = gRand.RandomUint32Uniform(0);
        u32 key = 0x5f10ce1;
        *m_data44.Index(key) = r + (u32)n;
    }
}

// =============================================================================
// @ 0x00d50a40
void SP::cMeteorStrikeEvent::FUN_00d50a40()
{
    GDEntry* begin = (GDEntry*)m_gdBegin5c;
    GDEntry* end   = (GDEntry*)m_gdEnd60;
    u32 key = 0x5f115ab;
    GDEntry* it = (GDEntry*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || it->mKey > key) it = end;

    if (it == end || it->mValue == 0) return;

    void* r = CallV0c(it->mValue, 0x52aa6117);
    if (r == 0) return;

    MegaManager* mgr = (MegaManager*)FUN_00b3d480();
    void** arr   = *(void***)((u8*)r + 0x40);
    void** arrEnd = *(void***)((u8*)r + 0x44);
    for (; arr != arrEnd; arr++) {
        void* creature = *arr;
        void* bt = *(void**)((u8*)creature + 0xb4c);
        if (bt != 0) {
            FUN_00bc98f0((u8*)bt + 8, 0, 0x4000);
            void* stim = FUN_00bc97f0(0x20000, 0, kF_14853bc, 0);
            if (stim != 0) {
                *(u32*)((u8*)stim + 0xc) = 1;
            }
        }
        mgr->Method_aca360(creature);
    }

    if (*m_data44.Index(0x613614c) != 0) {
        cGameNounManager* nm = (cGameNounManager*)SP_NounManager();
        nm->RemoveNoun(r);
    }
    FUN_00d4e8e0(&key);
}

// =============================================================================
// @ 0x00d50b80
u8 SP::cMeteorStrikeEvent::FUN_00d50b80()
{
    float v;
    Property* p = 0;
    if (m_pPropList40 == 0 || !m_pPropList40->FindProperty(0x81a3ccd6, &p)) {
        v = kF_13ebc4c;
    } else {
        u16 t = p->m_type12;
        if (t == 13 || t == 16) {
            if ((p->m_flags10 & 0x30) == 0) {
                v = *(float*)p;
            } else {
                v = *p->mpData;
            }
        } else {
            v = kF_15d9c6c;
        }
    }

    u32 key = 0x5f11011;
    u32 raw = *m_data44.Index(key);
    float mapv = *(float*)&raw;
    return (u8)(mapv > v);
}

// =============================================================================
// @ 0x00d50c30
u8 SP::cMeteorStrikeEvent::FUN_00d50c30()
{
    GDEntry* begin = (GDEntry*)m_gdBegin5c;
    GDEntry* end   = (GDEntry*)m_gdEnd60;
    u32 key = 0x5f115ab;
    GDEntry* it = (GDEntry*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || it->mKey > key) it = end;

    void* ctx = 0;
    if (it != end && it->mValue != 0) {
        ctx = CallV0c(it->mValue, 0x52aa6117);
    }

    if (!(m_f2c <= 0.0f)) return 1;
    if (ctx == 0) return 1;
    if (*(void**)((u8*)ctx + 0x40) == *(void**)((u8*)ctx + 0x44)) return 1;

    int price = GetTutorialToolPrice(m_pPropList40, 0xf51fc002, 3);

    u32 key2 = 0x5f0f28d;
    int target = (int)*m_data44.Index(key2);

    int n = (int)((*(u8**)((u8*)ctx + 0x44) - *(u8**)((u8*)ctx + 0x40)) >> 2);
    for (int i = 0; i < n; i++) {
        void* creature = *(void**)(*(u8**)((u8*)ctx + 0x40) + i * 4);
        void* bt = *(void**)((u8*)creature + 0xb4c);
        if (FUN_00bc96a0((u8*)bt + 8, 0, 0x4000) == 0) return 1;
        void* h = FUN_00bc96a0((u8*)bt + 8, 0x2000, 0);
        if (h != 0) {
            void* a = FUN_00d998d0(h, 0x17f243b);
            if (a != 0) {
                int skip = 0;
                void* b = FUN_00d4cf10(0x5f11333, 0x4f396a66);
                if (b != 0) {
                    if (CallV4c(b) != CallV4c(a)) skip = 1;
                }
                if (!skip) {
                    u32 idv = *(u32*)((u8*)a + 0x24);
                    u32 k3 = idv;
                    if (*m_data44.Index(k3) == 0) {
                        target = target + 1;
                        u32 k4 = 0x5f0f28d;
                        *m_data44.Index(k4) = (u32)target;
                        u32 k5 = *(u32*)((u8*)a + 0x24);
                        *m_data44.Index(k5) = 1;
                    }
                }
            }
        }
    }

    u32 key6 = 0x5f0f28d;
    return (u8)(price <= (int)*m_data44.Index(key6));
}

// =============================================================================
// @ 0x00d50e40
void SP::cMeteorStrikeEvent::FUN_00d50e40(float dt)
{
    GDEntry* begin = (GDEntry*)m_gdBegin5c;
    GDEntry* end   = (GDEntry*)m_gdEnd60;
    u32 key = 0x5f11333;
    GDEntry* it = (GDEntry*)MapLowerBound(begin, end, &key, m_gdSorted70);
    if (it == end || it->mKey > key) it = end;
    if (it == end || it->mValue == 0) return;

    if (CallV0c(it->mValue, 0x4f396a66) == 0) return;

    u32 k = 0x5f11011;
    float cur = *(float*)m_data44.Index(k);
    float sum = cur + dt;
    *m_data44.Index(k) = *(u32*)&sum;
}

// =============================================================================
// @ 0x00d50ef0
void SP::cMeteorStrikeEvent::FUN_00d50ef0()
{
    Vector3 pos;
    pos.x = gVec0169e440[0]; pos.y = gVec0169e440[1]; pos.z = gVec0169e440[2];

    cGameNounManager* mgr = (cGameNounManager*)SP_NounManager();
    void* avatar = mgr->GetAvatar();

    if (avatar != 0) {
        u8 head[12];
        Vector3 dir;
        if (FUN_00d9a360(head, (float*)&dir)) {
            float len = (float)sqrt((double)(dir.x * dir.x + (dir.y * dir.y + dir.z * dir.z)));
            if (len > kTiny) {
                float inv = 1.0f / len;
                dir.x = dir.x * inv;
                dir.y = dir.y * inv;
                dir.z = dir.z * inv;
            }
            float sx = dir.x * kSeventy;
            float sy = dir.y * kSeventy;
            float sz = dir.z * kSeventy;

            AnchorIface* pAnchor = (AnchorIface*)((u8*)avatar + 0xc0);
            float* ap = pAnchor->GetPos();
            Vector3 target;
            target.x = ap[0] + sx;
            target.y = ap[1] + sy;
            target.z = ap[2] + sz;

            u8 surf[16];
            void* pm = SP_PlanetModel(surf, &target, 0);
            float* snapped = (float*)FUN_00b82970(pm, &target, 0);
            pos.x = snapped[0];
            pos.y = snapped[1];
            pos.z = snapped[2];
        }
    }

    if (pos.x == gVec0169e440[0] && pos.y == gVec0169e440[1] && pos.z == gVec0169e440[2]) {
        return;
    }

    float keyInst = 0.0f;
    GetPropertyAsKeyInstance(m_pPropList40, 0x1b806155, &keyInst);

    u8 orient[16];
    void* pm2 = SP_PlanetModel(orient, &pos);
    FUN_00b7f190(pm2, orient, &pos);

    u8 out2[16];
    void* owner = FUN_00b23650(0x1be418e, keyInst, 0, &pos, orient);
    if (owner == 0) return;

    if (((u32(__thiscall*)(void*))(*(u32**)owner)[0x20 / 4])(owner) != 0x1be418e) return;

    SpawnedObj* sp = (SpawnedObj*)owner;
    *m_data44.Index(0x614a7ea) = 0;
    FUN_00d4edd0(0x609f2f8, owner);
    sp->m_i124 = -1;
    sp->m_b128 = 0;
    sp->m_b192 = 1;

    void* sub = FUN_00401010();
    u8 tmp[8];
    *(u32*)(tmp + 0) = 0x0609b763;
    *(u16*)(tmp + 4) = 4;
    *(u16*)(tmp + 6) = 0;
    (*(void(__thiscall*)(void*, void*, void*))(*(u32**)sub)[0x4c / 4])(sub,
        (void*)((u8*)sp->m_CreatureA4 + 0x504), tmp);

    FUN_01021260((void**)&sp->m_v98);
    FUN_00c74690((void**)&sp->m_v98, 1, 0);
    void* b3 = FUN_00b3d480();
    void* posse = FUN_00d539d0();

    u32 count = *(u32*)((u8*)sp + 0xf4);
    for (u32 i = 0; i < count; i++) {
        Vector3 rnd;
        Vector3 dirv;
        void* pm3 = SP_PlanetModel(&dirv, &rnd, kTen, kSeventy);
        FUN_00b81780(pm3, &dirv, &rnd, kTen, kSeventy);

        float inv = 1.0f / (float)(sqrt((double)(rnd.x * rnd.x + (rnd.y * rnd.y + rnd.z * rnd.z)) + kEps));
        rnd.x = (rnd.x * inv) * kTen + rnd.x;
        rnd.y = (rnd.y * inv) * kTen + rnd.y;
        rnd.z = (rnd.z * inv) * kTen + rnd.z;

        void* creature = FUN_00c099e0((float*)&rnd, *(float*)&sp->m_CreatureA4, 1, owner, 0, 1);
        FUN_00acd2d0(creature);

        AnchorIface* cAnchor = (AnchorIface*)((u8*)creature + 0xc0);
        void* v30 = ((PtrThunk1)(*(void***)cAnchor)[0x30 / 4])(cAnchor);
        (*(void(__thiscall*)(void*, void*, void*))(*(u32**)cAnchor)[0x44 / 4])(cAnchor, &rnd, v30);
        FUN_00c13a30(creature, 1);
        if (posse != 0) {
            FUN_00d54330(posse, creature);
        }
    }
}