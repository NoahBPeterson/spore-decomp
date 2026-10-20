// Slice s00dc3940 -- SP UFO / game-data decision and audio helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- helpers
#define VFN(p, off)     (((void**)*(void**)(p))[(off) / 4])
#define VC0(p, off)     ((int(__thiscall*)(void*))VFN(p, off))(p)
#define VC0V(p, off)    ((void(__thiscall*)(void*))VFN(p, off))(p)
#define VC1(p, off, a)  ((int(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define VCB1(p, off, a) ((char(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define VCV(p, off, a)  ((void(__thiscall*)(void*, int))VFN(p, off))(p, (int)(a))
#define VCF2(p, off, a, b) ((void(__thiscall*)(void*, int, float))VFN(p, off))(p, (int)(a), (b))

#define D(p, off) (*(int*)((char*)(p) + (off)))
#define F(p, off) (*(float*)((char*)(p) + (off)))
#define B(p, off) (*(unsigned char*)((char*)(p) + (off)))

struct Vec3f { float x, y, z; };
struct NounVec {
    int** mpBegin;
    int** mpEnd;
    int** mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    void* operator[](int i) const { return (void*)mpBegin[i]; }
};
struct IntVec { uint32_t pad; NounVec mData; };

// cGameNounManager::GetGameDataVector -- category filtered data list.
struct cGameNounManager {
    IntVec* GetGameDataVector(void* f1, void* f2, void* f3, void* f4, uint32_t id);
    IntVec* GetSomething();                       // 0x00ad49b0
};
cGameNounManager* NounManager();                  // 0x00b3d300

// behavior tree stimuli block; the object lives at ptr+8.
struct BehaviorStimuli {
    void ClearAll(int a, int b);                  // 0x00bc98f0
    int PlayIdleAnimation(int a, int b);          // 0x00bc96a0
};

// behavior_stimuli action result block.
struct Stim {
    char pad[8];
    void* p8;                                     // +0x08
    void GetAny();                                // 0x00d997e0
};

struct PFIndex { int GetFileCount(); };           // 0x008e7f80
struct Damage508 { char IsReady(); };             // 0x00bfc600

// thiscall callees whose class is unnamed here.
struct CmdObj {
    void Cmd(int id);                             // 0x00ca80e0
    void SetParam(float v);                       // 0x00c9ee70
    void SetTarget(int a);                        // 0x00ca33b0
    void Finish();                                // 0x00c9ee50
};
struct CheckObj {
    int  IsActive();                              // 0x00c9fee0
    void DoAction();                              // 0x00cacbe0
};
struct FilterObj {
    char Accept(int a);                           // 0x00c004c0
};
struct GroundObj {
    void SetPosition(float* pos);                 // 0x00c3be70
};

// ---------------------------------------------------------------- globals
extern const float k3940_10;                      // 0x013eb1bc
extern const float k4890_3;                       // 0x013eb95c
extern const float k4870_3;                       // 0x0147c394
extern const float k3940_6b4;                     // 0x0159d5b4
extern const float k3940_6b8;                     // 0x0159d5b8
extern const float k3940_half;                    // 0x01471064
extern const float k3940_out0;                    // 0x0169f444
extern const float k3940_out1;                    // 0x0169f448
extern const float k3940_out2;                    // 0x0169f44c
extern const float k3940_basis[9];                // 0x0169fa0c
extern const float k3c20_basis[9];                // 0x0169fa18
extern const float k3c20_scale;                   // 0x0169fa08
extern const float k3940_angles[5];               // 0x016dc0d4
extern const float k3940_vecs[15];                // 0x016dba24
extern const float k3940_randmul;                 // 0x0147c320
extern const float k3940_randlo;                  // 0x0147c318
extern const float k3940_randhi;                  // 0x01423748
extern const int   k3eb0_lim_a;                   // 0x0159d580
extern const float k3e10_lim_b;                   // 0x01485378
extern const int   k3eb0_lim_c;                   // 0x0159d584
extern const int   k43a0_lim_d;                   // 0x0159d588
extern const float k3f10_near;                    // 0x01469358
extern const float k4460_r;                       // 0x0159d5dc
extern const float k3c20_n;                       // 0x0159d58c
extern const float k40a0_max;                     // 0x0147c300
extern const int   k43a0_tool;                    // 0x0169f754
extern char  g_1601760;                           // 0x01601760 sMathRandom
extern char  g_mode_1654c10;                      // 0x01654c10
extern char* g_sounds_45a0[1];                    // 0x0147c3a8
extern char* g_sounds_4610[1];                    // 0x0147c3b4
extern const float k45a0_mod;                     // 0x0159d5dc

// ---------------------------------------------------------------- callees
void F_00cd7d10();                                 // 0x00cd7d10
void F_00d3d420();                                 // 0x00d3d420
void F_00ad48b0();                                 // 0x00ad48b0
void F_00b1e500();                                 // 0x00b1e500
void F_00ad4930();                                 // 0x00ad4930
void F_00acdff0();                                 // 0x00acdff0
void F_00dc3250();                                 // 0x00dc3250

float* FUN_0059aed0(float* out, const float* m, const float* q);   // 0x0059aed0
void*  FUN_00401010();                                             // 0x00401010
void*  SP_SpaceGameGet();                                          // 0x01002bd0
int    FUN_00c38b00(void* self);                                   // 0x00c38b00
int    FUN_00c38b80(void* self);                                   // 0x00c38b80
void*  FUN_010212a0();                                             // 0x010212a0
char   FUN_01029a10(void* self, int target);                       // 0x01029a10
char   FUN_00c004c0(void* self, int a);                            // 0x00c004c0
void   FUN_00c37130(void* self, int a);                            // 0x00c37130
void   FUN_00c3b630(void* self, void* a);                          // 0x00c3b630
void   FUN_00c3be70(void* self, float* pos);                       // 0x00c3be70
void   FUN_00dc3170(int a, int b, float x, float y, float z);      // 0x00dc3170
void   FUN_00f47380(void* p);                                      // 0x00f47380
void   Start3dSoundByName(void* name, void* sys, float x, float y, float z); // 0x00571f80
void*  EA_GetSystemAT();                                           // 0x00a206f0
void*  SP_GetCurrentGameMode();                                    // 0x00b5b800
void   FUN_00c37130(void* self, int a);                            // 0x00c37130
char   FUN_00c9fee0(void* self);                                   // 0x00c9fee0
void   FUN_00ca80e0(void* self, int id);                           // 0x00ca80e0
void   FUN_00b93c60(void* self, int count, void* src);             // 0x00b93c60
void   FUN_00829110(void* out, void* b, void* e, void* ctx, void* self); // 0x00829110

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl sqrt(double);

struct PlanetModel {
    void ToGround(Vec3f* out);                                     // 0x00b81720
    Vec3f* MakeRandomWorldPosition(Vec3f* out, const Vec3f* p, float a, float b); // 0x00b81780
};
PlanetModel* SP_PlanetModel();                                     // 0x00b3d350

struct RandLCG {
    double RandomDoubleUniform();                 // 0x009360d0
    uint32_t RandomUint32Uniform(uint32_t n);     // 0x00a68fb0
};

struct SpaceGame { void* GetAvatar(); };                           // 0x00b1fdb0
struct Avatar { void Notify(int id); };                            // 0x00ff8300
struct Empire { char IsHostileToPlayer(); };                       // 0x00c309e0
struct StarManager { Empire* GetEmpireByID(int id); };             // 0x00ba9370
StarManager* SP_StarManager();                                     // 0x00b3d2a0

// ---------------------------------------------------------------- 0x00dc3940
// Called for a freshly spawned UFO group: spreads the members around the
// anchor object and returns a random yaw offset.
// @ 0x00DC3940
char __cdecl FUN_00dc3940(void* owner, int, int, int, void* self, float* out) {
    F(self, 0x10) = k3940_10;
    cGameNounManager* nm = NounManager();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                   (void*)&F_00ad48b0, (void*)&F_00b1e500, 0x18ebadc);
    NounVec& v = vec->mData;
    int** p = v.mpBegin;
    int** end = v.mpEnd;
    int i = 0;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (D(o, 0x68c) != D(self, 0x68c) || D(o, 0x714) != D(self, 0x714))
            continue;
        D(o, 0x6b0) = i;
        unsigned u = (unsigned)D(o, 0x6b0) % 5u;
        ++i;
        float a = k3940_angles[u] * 0.5f;
        float s = (float)sin((double)a);
        float c = (float)cos((double)a);
        float q[4];
        q[0] = k3940_vecs[u * 3 + 0] * s;
        q[1] = k3940_vecs[u * 3 + 1] * s;
        q[2] = k3940_vecs[u * 3 + 2] * s;
        q[3] = c;
        Vec3f tmp;
        float* r = FUN_0059aed0(&tmp.x, k3940_basis, q);
        F(o, 0x694) = r[0];
        F(o, 0x698) = r[1];
        F(o, 0x69c) = r[2];
    }
    out[0] = k3940_out0;
    out[1] = k3940_out1;
    out[2] = k3940_out2;
    double r = ((RandLCG*)&g_1601760)->RandomDoubleUniform() * k3940_randmul;
    r -= k3940_randhi;
    if (k3940_randhi <= r)
        r = k3940_randhi;
    else if (r < k3940_randlo)
        r = k3940_randlo;
    out[3] = (float)r;
    F(owner, 0x6b4) = k3940_6b4;
    F(owner, 0x6b8) = k3940_6b8;
    B(owner, 0x690) = 1;
    return 1;
}

// ---------------------------------------------------------------- 0x00dc3af0
// UFO escape / panic update.
// @ 0x00DC3AF0
char __cdecl FUN_00dc3af0(void* self, int, int, int, int, float* v, int, float dt) {
    if (((BehaviorStimuli*)((char*)D(self, 0x6c8) + 8))->PlayIdleAnimation(8, 0) == 0) {
        v[1] -= dt;
        if (0.0f < v[1])
            return 1;
        return 0;
    }
    if (((BehaviorStimuli*)((char*)D(self, 0x6c8) + 8))->PlayIdleAnimation(0x20, 0) == 0)
        return 1;
    v[0] -= dt;
    if (0.0f < v[0])
        return 1;
    void* o = FUN_00401010();
    if (((char(__thiscall*)(void*, void*, int))VFN(o, 0x1c))(
            o, (void*)((char*)self + 0x780), 0) == 0)
        return 1;
    void* av = ((SpaceGame*)SP_SpaceGameGet())->GetAvatar();
    ((Avatar*)av)->Notify(0x638207a);
    IntVec* vec = NounManager()->GetSomething();
    int** p = vec->mData.mpBegin;
    int** end = vec->mData.mpEnd;
    for (; p != end; ++p) {
        void* e = (void*)*p;
        if (D(e, 0x6c8) == 0)
            continue;
        BehaviorStimuli* bs = (BehaviorStimuli*)((char*)D(e, 0x6c8) + 8);
        if (bs->PlayIdleAnimation(8, 0) == 0)
            continue;
        if (VC0(e, 0x4c) != VC0(self, 0x4c))
            continue;
        bs->ClearAll(8, 0);
        FUN_00c37130(e, 1);
    }
    return 1;
}

// ---------------------------------------------------------------- 0x00dc3c20
// Attack formation setup: places the group members on a circle around the
// current attack target.
// @ 0x00DC3C20
char __cdecl FUN_00dc3c20(void* self, int, int, int, int, void* src) {
    if (src == 0)
        return 1;
    void* t;
    if (D(src, 8) != 0)
        t = (void*)VC1((void*)D(src, 8), 0xc, 0xee9b2232);
    else
        t = 0;
    FUN_00c3b630(self, t);
    void* target = (void*)FUN_00c38b00(self);
    int count;
    void* anchor;
    if (target == 0) {
        anchor = 0;
    } else {
        anchor = (void*)VC1(target, 0xc, 0xee9b2232);
    }
    count = D(anchor, 0x224);
    float* pos = (float*)VC0((char*)anchor + 0x120, 0x2c);
    float inv = 1.0f / (float)sqrt((double)(pos[2] * pos[2] + (pos[1] * pos[1] + pos[0] * pos[0])));
    float nx = pos[0] * inv;
    float ny = pos[1] * inv;
    float nz = pos[2] * inv;
    cGameNounManager* nm = NounManager();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                   (void*)&F_00ad48b0, (void*)&F_00b1e500, 0x18ebadc);
    NounVec& v = vec->mData;
    int** p = v.mpBegin;
    int** end = v.mpEnd;
    int i = 0;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (FUN_00c38b00(o) != FUN_00c38b00(self))
            continue;
        D(o, 0x6b0) = i++;
        float a = ((float)D(o, 0x6b0) / (float)count) * k3c20_scale;
        a *= 0.5f;
        float s = (float)sin((double)a);
        float c = (float)cos((double)a);
        float q[4];
        q[0] = nx * s;
        q[1] = ny * s;
        q[2] = nz * s;
        q[3] = c;
        Vec3f tmp;
        float* r = FUN_0059aed0(&tmp.x, k3c20_basis, q);
        F(o, 0x6a0) = k3c20_n * r[0];
        F(o, 0x6a4) = k3c20_n * r[1];
        F(o, 0x6a8) = k3c20_n * r[2];
    }
    return 1;
}

// ---------------------------------------------------------------- 0x00dc3e10
// Picks a UFO that is still reachable and hands it to the behavior tree.
// @ 0x00DC3E10
double __cdecl FUN_00dc3e10(int, int, int, int, Stim* stim, char* out) {
    cGameNounManager* nm = NounManager();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                        (void*)&F_00acdff0, (void*)&F_00b1e500, 0x18c43e8);
    NounVec& v = vec->mData;
    int** p = v.mpBegin;
    int** end = v.mpEnd;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (D(o, 0x224) < k3eb0_lim_a &&
            (((FilterObj*)o)->Accept(0) || F(o, 0x220) > k3e10_lim_b)) {
            if (stim != 0)
                stim->GetAny();
            stim->p8 = o;
            *out = 1;
            return 1.0;
        }
    }
    return 0.0;
}

// ---------------------------------------------------------------- 0x00dc3eb0
// True while no UFO of the tracked category is in state 4.
// @ 0x00DC3EB0
double __cdecl FUN_00dc3eb0() {
    cGameNounManager* nm = NounManager();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                        (void*)&F_00ad4930, (void*)&F_00b1e500, 0x2dd8c42);
    NounVec& v = vec->mData;
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        void* o = v[i];
        if (D(o, 0x658) == 4)
            return 0.0;
    }
    return 1.0;
}

// ---------------------------------------------------------------- 0x00dc3f10
// Nearest usable UFO of the tracked category.
// @ 0x00DC3F10
double __cdecl FUN_00dc3f10(void* self, int, int, int, Stim* stim, char* out) {
    cGameNounManager* nm = NounManager();
    IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                        (void*)&F_00ad4930, (void*)&F_00b1e500, 0x2dd8c42);
    NounVec& v = vec->mData;
    int count = v.size();
    void* found = 0;
    float best = k3f10_near;
    int i = 0;
    for (; i < count; ++i) {
        void* o = v[i];
        if (D(o, 0x658) != 4)
            continue;
        float* a = (float*)VC0((char*)self + 0x34, 0x2c);
        float* b = (float*)VC0((char*)o + 0x34, 0x2c);
        float dx = b[0] - a[0];
        float dy = b[1] - a[1];
        float dz = b[2] - a[2];
        float dist = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
        if (best < dist)
            continue;
        IntVec* v2 = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                           (void*)&F_00ad48b0, (void*)&F_00b1e500, 0x18ebadc);
        NounVec& v2d = v2->mData;
        int n2 = v2d.size();
        int j = 0;
        for (; j < n2; ++j) {
            void* other = v2d[j];
            if (other == self)
                continue;
            if (FUN_00c38b80(other) == (int)o)
                break;
        }
        if (j < n2)
            continue;
        found = o;
        best = dist;
    }
    if (found != 0) {
        if (stim != 0)
            stim->GetAny();
        stim->p8 = found;
        *out = 1;
        return 1.0;
    }
    return 0.0;
}

// ---------------------------------------------------------------- 0x00dc40a0
// Chooses an attack target for the UFO city-needs action.
// @ 0x00DC40A0
double __cdecl FUN_00dc40a0(void* self, int, int, int, Stim* stim, char* out) {
    if (FUN_00c38b80(self) != 0)
        return 0.0;
    cGameNounManager* nm = NounManager();
    IntVec* list = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                         (void*)&F_00acdff0, (void*)&F_00b1e500, 0x18c43e8);
    int n = (int)(list->mData.mpEnd - list->mData.mpBegin);
    void* buf[1];
    FUN_00b93c60(buf, n, (char*)list + 0x10);
    float* a = (float*)VC0((char*)self + 0x34, 0x2c);
    FUN_00dc3170((int)buf, 0, a[0], a[1], a[2]);
    void* pick = 0;
    void* active = FUN_010212a0();
    char hostile = FUN_01029a10((void*)VC1(self, 0x4c, (int)active), 0);
    int** p = list->mData.mpBegin;
    int** end = list->mData.mpEnd;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (hostile != 0) {
            float f = F(o, 0x74c);
            if (f == (float)VC0(self, 0x4c) && 100.0f <= F(o, 0x748))
                break;
        }
        if (D(o, 0x228) < k3eb0_lim_c) {
            pick = (char*)o + 0x120;
            break;
        }
    }
    float bestd = k40a0_max;
    if (pick != 0) {
        float* q = (float*)VC0(pick, 0x2c);
        float* b = (float*)VC0((char*)self + 0x34, 0x2c);
        float dx = b[0] - q[0];
        float dy = b[1] - q[1];
        float dz = b[2] - q[2];
        bestd = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
    }
    IntVec* v2 = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                       (void*)&F_00dc3250, (void*)&F_00b1e500, 0x4e3fab5);
    void* nearest = pick;
    p = v2->mData.mpBegin;
    end = v2->mData.mpEnd;
    for (; p != end; ++p) {
        void* o = (void*)*p;
        if (D(o, 0x638) >= k43a0_lim_d)
            continue;
        char* sub = (char*)o + 0x34;
        float* q = (float*)VC0(sub, 0x2c);
        float* b = (float*)VC0((char*)self + 0x34, 0x2c);
        float dx = b[0] - q[0];
        float dy = b[1] - q[1];
        float dz = b[2] - q[2];
        float d = (float)sqrt((double)(dz * dz + (dy * dy + dx * dx)));
        if (d < bestd) {
            nearest = sub;
            bestd = d;
        }
    }
    if (nearest != 0) {
        if (stim != 0)
            stim->GetAny();
        stim->p8 = (void*)VC1(nearest, 0xb8, 0x17f243b);
        *out = 1;
    }
    return 0.0;
}

// ---------------------------------------------------------------- 0x00dc43a0
// Embassy-needs action: pick an embassy of a hostile empire.
// @ 0x00DC43A0
double __cdecl FUN_00dc43a0(void* self, int, int, int, Stim* stim, char* out) {
    Empire* e = SP_StarManager()->GetEmpireByID(VC0(self, 0x4c));
    if (e != 0 && e->IsHostileToPlayer()) {
        cGameNounManager* nm = NounManager();
        IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                       (void*)&F_00dc3250, (void*)&F_00b1e500, 0x4e3fab5);
        NounVec& v = vec->mData;
        int** p = v.mpBegin;
        int** end = v.mpEnd;
        for (; p != end; ++p) {
            void* o = (void*)*p;
            if (D(o, 0x64c) != k43a0_tool || D(o, 0x638) >= k43a0_lim_d)
                continue;
            if (stim != 0)
                stim->GetAny();
            stim->p8 = (void*)VC1(o, 0xc, 0x17f243b);
            *out = 1;
            return 1.0;
        }
    }
    return 0.0;
}

// ---------------------------------------------------------------- 0x00dc4460
// UFO abduction action: relocate the beam target and mark the state used.
// @ 0x00DC4460
char __cdecl FUN_00dc4460(void* self) {
    if (B(self, 0x74c) != 0) {
        PlanetModel* pm = SP_PlanetModel();
        Vec3f pos;
        pm->ToGround(&pos);
        if (D(self, 0x714) == 6) {
            cGameNounManager* nm = NounManager();
            IntVec* vec = nm->GetGameDataVector((void*)&F_00cd7d10, (void*)&F_00d3d420,
                                                           (void*)&F_00acdff0, (void*)&F_00b1e500, 0x18c43e8);
            NounVec& v = vec->mData;
            if (v.mpBegin != v.mpEnd) {
                uint32_t idx = ((RandLCG*)&g_1601760)->RandomUint32Uniform((uint32_t)v.size());
                void* o = v[idx];
                Vec3f tmp;
                Vec3f* r = pm->MakeRandomWorldPosition(&tmp, (const Vec3f*)VC0((char*)o + 0x120, 0x2c), 0.0f, k4460_r);
                pos = *r;
            }
        }
        ((GroundObj*)self)->SetPosition(&pos.x);
        B(self, 0x624) = 1;
    }
    VCV((char*)self + 0x508, 0x50, 0);
    return 1;
}

// ---------------------------------------------------------------- 0x00dc4560
// @ 0x00DC4560
void __cdecl FUN_00dc4560(void* name, float x, float y, float z) {
    void* sys = EA_GetSystemAT();
    void* h = sys != 0 ? (void*)VC0(sys, 0x20) : 0;
    Start3dSoundByName(name, h, x, y, z);
}

// ---------------------------------------------------------------- 0x00dc45a0
// @ 0x00DC45A0
void __cdecl FUN_00dc45a0(void* self) {
    float* p = (float*)VC0((char*)self + 0x34, 0x2c);
    if (SP_GetCurrentGameMode() == &g_mode_1654c10)
        return;
    void* sys = EA_GetSystemAT();
    void* h = sys != 0 ? (void*)VC0(sys, 0x20) : 0;
    Start3dSoundByName(g_sounds_45a0[D(self, 0xb20)], h, p[0], p[1], p[2]);
}

// ---------------------------------------------------------------- 0x00dc4610
// @ 0x00DC4610
void __cdecl FUN_00dc4610(void* self) {
    float* p = (float*)VC0((char*)self + 0x34, 0x2c);
    void* sys = EA_GetSystemAT();
    void* h = sys != 0 ? (void*)VC0(sys, 0x20) : 0;
    Start3dSoundByName(g_sounds_4610[D(self, 0xb20)], h, p[0], p[1], p[2]);
}

// ---------------------------------------------------------------- 0x00dc4670
// @ 0x00DC4670
double __cdecl FUN_00dc4670(void* self) {
    return ((PFIndex*)((char*)self + 0x508))->GetFileCount() == 2 ? 1.0 : 0.0;
}

// ---------------------------------------------------------------- 0x00dc4690
// @ 0x00DC4690
double __cdecl FUN_00dc4690(void* self) {
    return ((Damage508*)((char*)self + 0x508))->IsReady() ? 1.0 : 0.0;
}

// ---------------------------------------------------------------- 0x00dc46b0
// @ 0x00DC46B0
double __cdecl FUN_00dc46b0(void* self) {
    return (B(self, 0x2a4) & 2) != 0 ? 1.0 : 0.0;
}

// ---------------------------------------------------------------- 0x00dc46d0
// @ 0x00DC46D0
char __cdecl FUN_00dc46d0(void* self) {
    ((BehaviorStimuli*)((char*)D(self, 0xaf0) + 8))->ClearAll(1, 0);
    VC0V((char*)self + 0x34, 0xec);
    VCV((char*)self + 0x508, 0x50, 0);
    return 0;
}

// ---------------------------------------------------------------- 0x00dc4710
// @ 0x00DC4710
void __cdecl FUN_00dc4710(void* self) {
    ((CmdObj*)self)->SetParam(0.0f);
}

// ---------------------------------------------------------------- 0x00dc47b0
// @ 0x00DC47B0
void __cdecl FUN_00dc47b0(void* self) {
    ((CmdObj*)self)->Cmd(0x16);
    ((CmdObj*)self)->Cmd(0x17);
}

// ---------------------------------------------------------------- 0x00dc47d0
// @ 0x00DC47D0
void __cdecl FUN_00dc47d0(void* self) {
    ((CmdObj*)self)->Cmd(0x13);
}

// ---------------------------------------------------------------- 0x00dc47e0
// @ 0x00DC47E0
char __cdecl FUN_00dc47e0(int, int, int, int, int, float* out) {
    if (out != 0)
        *out = 0.0f;
    return 1;
}

// ---------------------------------------------------------------- 0x00dc4800
// @ 0x00DC4800
double __cdecl FUN_00dc4800(void* self) {
    return B(self, 0xbcc) != 0 ? 1.0 : 0.0;
}

// ---------------------------------------------------------------- 0x00dc4820
// @ 0x00DC4820
void __cdecl FUN_00dc4820(void* self) {
    VCV((char*)self + 0x508, 0x50, 0);
    ((void(__thiscall*)(void*, float, int))VFN((char*)self + 0x34, 0xc4))((char*)self + 0x34, 0.0f, 0);
    ((CmdObj*)self)->SetTarget(VC0((char*)self + 0x34, 0x2c));
    ((CmdObj*)self)->Finish();
}

// ---------------------------------------------------------------- 0x00dc4870
// @ 0x00DC4870
char __cdecl FUN_00dc4870(int, int, int, int, int, float* out) {
    if (out != 0)
        *out = 3.0f;
    return 1;
}

// ---------------------------------------------------------------- 0x00dc4890
// @ 0x00DC4890
char __cdecl FUN_00dc4890(void* self, int, int, int, int, float* out, int, float delta) {
    if (((CheckObj*)self)->IsActive() == 0)
        return 0;
    if ((D(self, 0x2a4) & 4) != 0) {
        ((CheckObj*)self)->DoAction();
        return 1;
    }
    if ((D(self, 0x2a4) & 8) == 0)
        return 0;
    float v = *out + delta;
    float lim = k4890_3;
    *out = v;
    if (lim > v)
        return 1;
    return 0;
}
