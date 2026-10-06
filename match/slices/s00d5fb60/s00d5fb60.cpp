// Slice s00d5fb60: SP::cCityVisualizer::Update (per-frame tick). Retail layout differs from the 2008 PDB,
// so members are accessed by retail byte offset (F<T>(p, off)).
#include <math.h>
#include <float.h>
typedef unsigned int u32;
typedef unsigned long long u64;

template <class T> static inline T& F(void* p, int off) { return *(T*)((char*)p + off); }

struct Vec3 { float x, y, z; };

// virtual call helpers (thiscall through a vtable slot)
template <class R> static inline R VC0(void* o, int slot) {
    typedef R(__thiscall * Fn)(void*);
    return ((Fn)(*(void***)o)[slot])(o);
}
template <class R, class A> static inline R VC1(void* o, int slot, A a) {
    typedef R(__thiscall * Fn)(void*, A);
    return ((Fn)(*(void***)o)[slot])(o, a);
}
template <class R, class A, class B> static inline R VC2(void* o, int slot, A a, B b) {
    typedef R(__thiscall * Fn)(void*, A, B);
    return ((Fn)(*(void***)o)[slot])(o, a, b);
}

struct Stopwatch {
    void Restart();                // 0x571e80
    u64 GetElapsedTime();          // 0x93a5e0
};
struct Timer {
    bool IsRunning();              // 0xfeba90
    u64 GetElapsedTime();          // 0xbc3190
    void Restart();                // 0xbc3130
};
struct Stim {                      // blackboard written by the stimulus system
    float pad[3];
    float x, y, z;                 // +0xc
    float radius;                  // +0x18
    int id;                        // +0x1c
};
struct StimSet {                   // behavior_stimuli at creature+0xb4c -> +8
    Stim* FUN_00bc97f0(int type, int a, float prio, int b);   // 0xbc97f0
    void ClearAll(int type, int a);                           // 0xbc98f0
    int FUN_00bc9980(float dt);                               // 0xbc9980
};
struct GameTimeMgr { u64 FUN_00b316c0(); };                   // 0xb316c0
struct Rand { double RandomDoubleUniform(); };                // 0x9360d0
struct Avatar { void* FUN_00ff5b80(); };                      // 0xff5b80 (returns list head)
struct SpaceGame { Avatar* GetAvatar(); };                    // 0xb1fdb0
struct Profile { void* GetAvatarProfile(); };                 // 0x4df420
struct EffMgr { void* FUN_00ad11f0(int); };                   // 0xad11f0
struct SimGlobal {                                            // FUN_00b3d4d0 result
    char pad[0x28];
    bool b28;
    char pad2[3];
    int mode;                                                 // +0x2c
};
struct City {
    int GetCreatureCount();        // 0xbd8120
    bool FUN_00bd7df0();
    bool FUN_00bd8240();
    bool FUN_00bd8280();
    bool FUN_00bd82c0();
    void FUN_00bdf7e0(void* v);
    void FUN_00bdf880(void* v);
    void* FUN_00bd9e40();
    void* GetCivilization();       // 0xbd9bf0
    void* FUN_00bd8d60(int i);
};
struct Viz {
    void FUN_00d5bfa0(int a);
    void FUN_00d57e20(int a);
    int FUN_00d57ef0(int a);
    void FUN_00d5ef80();
    void FUN_00d581b0();
    void FUN_00d58d50();
    u32 SpaceOnlyTick();           // 0xd5e0c0
    void AllegianceUpdate();       // 0xd5d880
    bool FUN_00d599a0(void* creature);
    void FUN_00d58ea0();
    void UpdateBackgroundNoise();  // 0xd5b0c0
    void Update(u64 elapsed);
};

extern u32 SP_GetCurrentGameMode();         // 0xb5b800
extern SimGlobal* FUN_00b3d4d0();
extern void* FUN_00b33f40();
extern void FUN_00b4b040(void* p, u32 t, int one);
extern SpaceGame* SP_SpaceGameGet();        // 0x1002bd0
extern int SP_GetPlayerEmpireID();          // 0x1021090
extern GameTimeMgr* SP_GameTimeManager();   // 0xb3d380
extern void* FUN_00b3d480();
extern Profile* FUN_00401090();
extern void SP_SetUpCitizenBodyScaleRanges(void* profile, float* a, float* b, float* c);  // 0xd588a0
extern void FUN_00d57800(void* effect, Viz* viz, void* profile, int civ, int idx, Vec3* pos, float a, float b, float c);
extern void FUN_00d995f0(float dt, double gameTime, int a, void* creature, void* b, int c, int flags, int t);
extern void FUN_00aea5d0_push(void* vec, void** pos, void** val);   // 0xaea5d0 (thiscall vector grow-insert)
extern Rand sMathRandom;                    // 0x1601760
extern float g_PosX, g_PosY, g_PosZ;        // 0x169ec28, 0x169ec2c, 0x169ec30 (invalid-position sentinel)

static inline u32 Pad() { return 0; }

// @ 0xd5fb60
void Viz::Update(u64 t) {
    City* city = F<City*>(this, 0xaf0);
    if (!city) return;

    int n = (F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2;
    if (n != city->GetCreatureCount()) {
        FUN_00d5bfa0(0);
        n = (F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2;
    }
    float dt = (float)t * 0.001f;
    SimGlobal* g = FUN_00b3d4d0();

    if (F<char>(city, 0x192) ||
        ((g->mode == 1 || g->mode == 2) && !g->b28 && F<int>(g, 0x160) != 0 && F<int>(g, 0x160) != 2)) {
        if (!F<bool>(this, 0xa10)) {
            ((Stopwatch*)((char*)this + 0x9f8))->Restart();
            F<bool>(this, 0xa10) = true;
        }
        t = ((Stopwatch*)((char*)this + 0x9f8))->GetElapsedTime();
        dt = (float)t * 0.001f;
        ((Stopwatch*)((char*)this + 0x9f8))->Restart();
        if (t != 0) {
            for (u32 i = 0; i < (u32)((F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2); i++) {
                void* cr = F<void**>(this, 0xa64)[i];
                FUN_00b4b040(cr ? (char*)cr + 0xc0 : 0, (u32)t, 1);
                VC1<void, u32>(cr, 24, (u32)t);
            }
            n = (F<int>(this, 0xa68) - F<int>(this, 0xa64)) >> 2;
            void* p = FUN_00b33f40();
            if (p) VC2<void, float, int>(p, 9, dt, 0);
        }
    } else {
        F<bool>(this, 0xa10) = false;
    }

    F<bool>(this, 0xaf6) = false;
    u32 flags = 0;
    if (g->mode == 1 || g->mode == 2) flags = 0x8000000;
    if (F<bool>(this, 0xaf4)) flags |= 1;
    if (city->FUN_00bd7df0() && !F<bool>(city, 0x2a0))
        F<int>(this, 0xa3c) = (F<int>(this, 0xc4) - F<int>(this, 0xc0)) / 12;
    else
        F<int>(this, 0xa3c) = 0;
    FUN_00d57e20(F<bool>(this, 0xaf4));
    FUN_00d57ef0(F<bool>(this, 0xaf4));
    bool b16 = F<int>(this, 0xc3c) > -1;
    bool b17 = F<int>(this, 0xa4c) != -1;
    FUN_00d5ef80();
    FUN_00d581b0();
    if (city->FUN_00bd8240()) flags |= 0x400000;
    if (city->FUN_00bd8280()) flags |= 0x2000000;
    if (city->FUN_00bd82c0()) flags |= 0x4000000;
    bool b14 = false;
    F<int>(this, 0xa2c) = 0;
    F<int>(this, 0xa34) = n / 2;
    city->FUN_00bdf7e0((char*)this + 0xb80);
    bool b15 = F<int>(this, 0xb80) != F<int>(this, 0xb84);
    FUN_00d58d50();
    if (F<int>(this, 0xa44) != -1) flags |= 0x10000;
    if (F<bool>(this, 0xa48)) flags |= 0x20000;

    u32 mode = SP_GetCurrentGameMode();
    if (mode == 0x1654c04) {
        city = F<City*>(this, 0xaf0);
        city->FUN_00bdf880((char*)this + 0xb94);
        b14 = F<int>(this, 0xb94) != F<int>(this, 0xb98);
        AllegianceUpdate();
    } else if (mode == 0x1654c05) {
        flags |= SpaceOnlyTick();
        F<int>(this, 0xa3c) = 0;
    }

    Vec3 pos;
    float speed;
    void* owner = F<void*>(F<void*>(this, 0xaf0), 0x298);
    if (owner) {
        Vec3* pp = VC0<Vec3*>(owner, 11);
        pos.x = pp->x; pos.y = pp->y; pos.z = pp->z;
        owner = F<void*>(F<void*>(this, 0xaf0), 0x298);
        F<float>(this, 0xa24) = VC0<float>(owner, 29);
        float d = dt;
        if (F<float>(this, 0xa14) == g_PosX && F<float>(this, 0xa18) == g_PosY && F<float>(this, 0xa1c) == g_PosZ) {
            speed = 0.0f;
        } else {
            float dx = pos.x - F<float>(this, 0xa14);
            float dy = pos.y - F<float>(this, 0xa18);
            float dz = pos.z - F<float>(this, 0xa1c);
            speed = sqrtf(dx * dx + dy * dy + dz * dz) / d;
        }
        flags |= 0x4000;
        F<float>(this, 0xa14) = pos.x;
        F<float>(this, 0xa18) = pos.y;
        F<float>(this, 0xa1c) = pos.z;
    } else {
        F<float>(this, 0xa14) = g_PosX;
        F<float>(this, 0xa18) = g_PosY;
        F<float>(this, 0xa1c) = g_PosZ;
        speed = 0.0f;
        F<float>(this, 0xa24) = 0.0f;
    }
    F<float>(this, 0xa20) = speed;

    float height = (SP_GetCurrentGameMode() == 0x1654c05) ? 15.0f : 3.0f;

    if (dt > 0.0f) {
        for (int i = 0; i < n; i++) {
            void* cr = F<void**>(this, 0xa64)[i];
            if (!VC0<bool>(cr, 11)) {
                StimSet* st = (StimSet*)(F<char*>(cr, 0xb4c) + 8);
                if (F<bool>(this, 0xaf6))
                    st->FUN_00bc97f0(1, 0, FLT_MAX, 0);
                if (F<int>(this, 0x38c))
                    st->FUN_00bc97f0(0x400, 0, 3.0f, 0);
                void* c1 = F<void*>(this, 0xaf0);
                int m = (F<int>(c1, 0x2a8) - F<int>(c1, 0x2a4)) / 20;
                void* sub = (char*)cr + 0xc0;
                Vec3* sp = VC0<Vec3*>(sub, 11);
                Vec3 q;
                q.x = sp->x; q.y = sp->y; q.z = sp->z;
                for (int j = 0; j < m; j++) {
                    float* it = (float*)(F<char*>(F<void*>(this, 0xaf0), 0x2a4) + j * 20);
                    float ix = it[0], iy = it[1], iz = it[2];
                    float dx = ix - q.x, dz = iz - q.z, dy = iy - q.y;
                    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (it[3] > dist) {
                        Stim* s = st->FUN_00bc97f0(4, 0, 15.0f, 0);
                        if (s) {
                            s->x = ix; s->y = iy; s->z = iz;
                            s->radius = height;
                            s->id = *(int*)(F<char*>(F<void*>(this, 0xaf0), 0x2a4) + j * 20 + 0x10);
                        }
                        break;
                    }
                }
                c1 = F<void*>(this, 0xaf0);
                m = (F<int>(c1, 0x2bc) - F<int>(c1, 0x2b8)) / 20;
                for (int j = 0; j < m; j++) {
                    float* it = (float*)(F<char*>(c1, 0x2b8) + j * 20);
                    float dx = it[0] - q.x, dz = it[2] - q.z, dy = it[1] - q.y;
                    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
                    if (it[3] > dist) {
                        st->ClearAll(4, 0);
                        break;
                    }
                }
                if (SP_GetCurrentGameMode() == 0x1654c05 && SP_SpaceGameGet() && SP_SpaceGameGet()->GetAvatar()) {
                    void* head = SP_SpaceGameGet()->GetAvatar()->FUN_00ff5b80();
                    for (float** node = *(float***)head; node != (float**)head; node = (float**)*node) {
                        void* rp = (char*)F<void*>(this, 0xaf0) + 0x120;
                        Vec3* r = VC0<Vec3*>(rp, 11);
                        float dx = ((float*)node)[3] - r->x;
                        float dz = ((float*)node)[5] - r->z;
                        float dy = ((float*)node)[4] - r->y;
                        if (dx * dx + dz * dz + dy * dy < 10000.0f) {
                            Stim* s = st->FUN_00bc97f0(0x200, 0, 100.0f, 0);
                            if (s) {
                                s->x = ((float*)node)[3];
                                s->y = ((float*)node)[4];
                                s->z = ((float*)node)[5];
                            }
                            float prob = 0.7f;
                            if (VC0<int>(cr, 38) != 5) prob = 0.1387f;
                            double v = sMathRandom.RandomDoubleUniform() * 100.0;
                            if (v < 100.0) {
                                if (v < 0.0) v = 0.0;
                            } else {
                                v = 100.0;
                            }
                            if (prob > v) {
                                Stim* s2 = st->FUN_00bc97f0(4, 0, 100.0f, 0);
                                if (s2) {
                                    s2->x = ((float*)node)[3];
                                    s2->y = ((float*)node)[4];
                                    s2->radius = 100.0f;
                                    s2->z = ((float*)node)[5];
                                    s2->id = SP_GetPlayerEmpireID();
                                }
                            }
                        }
                    }
                }
                c1 = F<void*>(this, 0xaf0);
                if (F<float>(c1, 0x2d4) != g_PosX || F<float>(c1, 0x2d8) != g_PosY || F<float>(c1, 0x2dc) != g_PosZ) {
                    float dx = F<float>(c1, 0x2d4) - q.x;
                    float dy = F<float>(c1, 0x2d8) - q.y;
                    float dz = F<float>(c1, 0x2dc) - q.z;
                    if (sqrtf(dx * dx + dy * dy + dz * dz) < 10.0f) {
                        Stim* s = st->FUN_00bc97f0(0x100, 0, 5.0f, 0);
                        if (s) {
                            s->x = F<float>(F<void*>(this, 0xaf0), 0x2d4);
                            s->y = F<float>(F<void*>(this, 0xaf0), 0x2d8);
                            s->z = F<float>(F<void*>(this, 0xaf0), 0x2dc);
                        }
                    }
                }
                u32 fl = flags;
                if (F<int>(this, 0xa38) < F<int>(this, 0xa3c)) fl |= 4;
                if (F<int>(this, 0x9f0)) fl |= 8;
                if (b14) fl |= 0x40;
                if (b15) fl |= 0x80;
                if (F<int>(this, 0x9f4)) fl |= 0x100;
                if (F<int>(this, 0xbd0)) {
                    if (b16 || b17 || F<bool>(F<void*>(this, 0xaf0), 0x2a0))
                        fl |= 0x800;
                    else if (F<bool>(this, 0xa50))
                        fl |= 0x100000;
                    else
                        fl |= 0x400;
                }
                if (F<int>(this, 0xa28) < F<int>(this, 0xa2c)) fl |= 0x2000;
                if (F<int>(this, 0xa5c) < F<int>(this, 0xa60)) fl |= 0x200000;
                if (F<bool>(cr, 0xfbc))
                    fl |= 0x1000;
                else if (F<int>(this, 0xa30) < F<int>(this, 0xa34))
                    fl |= 0x1000000;
                if (F<bool>(this, 8)) {
                    fl |= 0x200;
                    if (!FUN_00d599a0(cr)) fl |= 0x20;
                }
                char* sp2 = F<char*>(cr, 0xb4c);
                if (*(int*)sp2 != 0) {
                    int tt = ((StimSet*)(sp2 + 8))->FUN_00bc9980(dt);
                    u64 gt = SP_GameTimeManager()->FUN_00b316c0();
                    sp2 = F<char*>(cr, 0xb4c);
                    FUN_00d995f0(dt, (double)gt * 0.001f, *(int*)sp2, cr, sp2 + 0x1d0, *(int*)(sp2 + 0x5e8), fl, tt);
                }
                void* x = F<void*>(cr, 0xb54);
                if (x) F<int>(x, 0x14c) = 0;
            }
        }

        int m2 = (F<int>(this, 0xacc) - F<int>(this, 0xac8)) >> 2;
        for (int j = 0; j < m2; j++) {
            void* inst = F<void**>(this, 0xac8)[j];
            char* sp2 = F<char*>(inst, 0xb4c);
            if (*(int*)sp2 != 0) {
                int tt = ((StimSet*)(sp2 + 8))->FUN_00bc9980(dt);
                u64 gt = SP_GameTimeManager()->FUN_00b316c0();
                sp2 = F<char*>(inst, 0xb4c);
                FUN_00d995f0(dt, (double)gt * 0.001f, *(int*)sp2, inst, sp2 + 0x1d0, *(int*)(sp2 + 0x5e8),
                             *(int*)(sp2 + 0x5fc), tt);
            }
        }

        void* effMgrOwner = FUN_00b3d480();
        void* profile = F<City*>(this, 0xaf0)->FUN_00bd9e40();
        void* civ = F<City*>(this, 0xaf0)->GetCivilization();
        int civv = VC0<int>(civ, 19);
        if (!profile) profile = FUN_00401090()->GetAvatarProfile();
        float s1 = 1.0f, s2 = 0.2f, s3 = 1.5f;
        SP_SetUpCitizenBodyScaleRanges(profile, &s1, &s2, &s3);
        void* rp = (char*)F<void*>(this, 0xaf0) + 0x120;
        Vec3* rv = VC0<Vec3*>(rp, 11);
        Vec3 rpos;
        rpos.x = rv->x; rpos.y = rv->y; rpos.z = rv->z;

        char* gate = (char*)this + 0x39c;
        char* vecs = (char*)this + 0xa7c;
        for (int k = 0; k < 4; k++, gate += 0x198, vecs += 0x14) {
            if (F<int>(gate, -8) < F<int>(gate, -4)) {
                Timer* tm = (Timer*)(gate + 4);
                if (tm->IsRunning()) {
                    u64 el = tm->GetElapsedTime();
                    if (el <= (u64)F<u32>(gate, 0)) continue;
                }
                void* mgr = ((EffMgr*)effMgrOwner)->FUN_00ad11f0(0x18eb4b7);
                if (mgr) {
                    void* eff = VC1<void*, u32>(mgr, 3, 0x4f176642);
                    if (eff) {
                        FUN_00d57800(eff, this, profile, civv, k, &rpos, s1, s2, s3);
                        VC0<void>(eff, 0);                    // AddRef (temp AutoRefCount)
                        void* tmp = eff;
                        void** endp = F<void**>(vecs, 0);
                        if (endp < F<void**>(vecs, 4)) {
                            F<void**>(vecs, 0) = endp + 1;
                            if (endp) {
                                *endp = eff;
                                VC0<void>(eff, 0);            // AddRef
                            }
                        } else {
                            FUN_00aea5d0_push(vecs - 4, endp, &tmp);
                        }
                        if (tmp) VC0<void>(tmp, 1);           // Release temp
                        F<int>(gate, 0) = 100;
                        tm->Restart();
                    }
                }
            }
        }

        u32 flags2 = flags | 0x8000;
        char* gate2 = (char*)this + 0x398;
        char* vecs2 = (char*)this + 0xa7c;
        for (int k = 0; k < 4; k++, gate2 += 0x198, vecs2 += 0x14) {
            char* gp = (char*)F<City*>(this, 0xaf0)->FUN_00bd8d60(k);
            if (F<int>(gp, 0x1d8) == 2 || F<int>(gate2, -8) > 0) {
                F<int>(gate2, 0) = 10;
                void** it = F<void**>(vecs2, -4);
                void** end = F<void**>(vecs2, 0);
                for (; it != end; it++) {
                    void* cr = *it;
                    if (F<bool>(this, 8)) flags2 |= 0x200;
                    char* sp2 = F<char*>(cr, 0xb4c);
                    if (*(int*)sp2 != 0) {
                        int tt = ((StimSet*)(sp2 + 8))->FUN_00bc9980(dt);
                        u64 gt = SP_GameTimeManager()->FUN_00b316c0();
                        sp2 = F<char*>(cr, 0xb4c);
                        FUN_00d995f0(dt, (double)gt * 0.001f, *(int*)sp2, cr, sp2 + 0x1d0, *(int*)(sp2 + 0x5e8),
                                     flags2, tt);
                    }
                }
            }
        }
    }

    FUN_00d58ea0();
    UpdateBackgroundNoise();
    F<bool>(F<void*>(this, 0xaf0), 0x2a0) = false;
    {
        char* c = (char*)F<void*>(this, 0xaf0);
        // eastl::vector<20-byte>::clear(): erase(begin, end) -> end = begin
        F<int>(c, 0x2a8) += ((F<int>(c, 0x2a4) - F<int>(c, 0x2a8)) / 20) * 20;
        c = (char*)F<void*>(this, 0xaf0);
        F<int>(c, 0x2bc) += ((F<int>(c, 0x2b8) - F<int>(c, 0x2bc)) / 20) * 20;
    }
    {
        char* c = (char*)F<void*>(this, 0xaf0);
        F<float>(c, 0x2d4) = g_PosX;
        F<float>(c, 0x2d8) = g_PosY;
        F<float>(c, 0x2dc) = g_PosZ;
    }
    F<bool>(this, 0xaf4) = false;
    F<bool>(this, 8) = false;
    void* old = F<void*>(this, 0x38c);
    F<void*>(this, 0x38c) = 0;
    if (old) VC0<void>(old, 48);
}
