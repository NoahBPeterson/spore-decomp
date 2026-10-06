// Slice 10: nSPSkinner paint-system tick predicates and message handling helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void AtomicRefCounted_Release(void* p);   // 0x00402420
void FUN_00525d90(void* p, void* v);      // 0x00525d90

struct RcObj { virtual void AddRef(); virtual void Release(); };
struct JobMgr { int ContinueJob(); };                         // 0x0068f970
struct Job { virtual void v0(); virtual void Release(); virtual bool Start(int, void*); virtual void v3(); virtual bool IsRunning(); };
struct Vec2f { float x, y; };
struct AOCache { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
                 virtual void SetBlendColor(void* tmp, float a, float b); };   // vtable +0x3c
struct MeshAORender { void Rebuild();  };                      // 0x00516eb0
struct Pipeline { void ExecutePipeline(); void F_0051aaa0(); void F_0051a9a0(unsigned plr, int, int, int, int, int, int, int, int, int); int pad[0x33c / 4]; int mFramesWaited; }; // 0x0051afd0 / 0051aaa0 / 0051a9a0
struct PaintListRender { void F_005123b0(); };                 // 0x005123b0
struct MatObj { void F_00526070(unsigned); void F_00526230(unsigned); void F_006909b0(); };
struct MsgServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void Post(int, int, int); };
struct JobFactory { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
                    virtual unsigned char Create(int, void*, void*, int, int, int); }; // vtable +0x40

class RandomLC { public: unsigned mSeed; void SetSeed(unsigned); };   // 0x00936090
extern RandomLC gRandom;                                              // 0x016778dc
extern void* gAppProperties;                                          // 0x015fd918
extern void* gUnknown15de57c;                                         // 0x015de57c
bool GetFloatProperty(void* list, unsigned id, float* out);           // 0x0040cf10
int InitVerbCollection(int);                                          // 0x004bb860
int GetIntProperty(void* list, unsigned id);                          // 0x006a2660 (thiscall in orig)
JobFactory* GetJobFactory();                                          // 0x0067ddb0
MsgServer* GetMessageServer();                                        // 0x0067dcc0
void RefCounted_Release(void*);                                       // 0x00453540 (thiscall)
void F_00506590(void* mat, unsigned size);                            // 0x00506590 (thiscall)

struct TickState {
    bool ShouldTick();
    void ClearPtr100();
    TickState& Assign(const TickState& o);                        // 0x005218e0
    bool HandleMessage(int id);                                   // 0x005219d0
    void Tick(int dt);                                            // 0x00521ba0
    void HandleUpdateMessage(int dt);                             // 0x00521d70
    void F_00523690();
    bool F_00525a40();
    void F_00525d90(unsigned);
    void F_006909b0();
    static void F_0051a6a0(void*);                                // 0x0051a6a0 (cdecl)
    void SetCreatureSkin(int, int);                               // 0x00522b40
};
void F_00525d90b(void* self, unsigned v);                         // 0x00525d90 (thiscall)
void F_00525cf0(void* dst, void* src);                            // 0x00525cf0 (thiscall on dst)
void VecErase(void* v, unsigned b, unsigned e);                   // 0x00530c80 (thiscall)
void VecAssign(void* v, unsigned* b, unsigned* e);                // 0x005283d0 (thiscall)
void VecFree(void* v);                                            // 0x00526a40 (thiscall)
bool GetResourceTypeFromModelType(int modelType);                 // 0x00526430 (thiscall)

// @ 0x00522720
bool TickState::ShouldTick()
{
    bool result = true;
    if (*(unsigned char*)((char*)this + 0x62) == 0) {
        int* p = (int*)((char*)this + 0x94);
        if (((p[1] - p[0]) >> 3) <= *(int*)((char*)this + 0xec)) {
            int v = *(int*)((char*)this + 0xf0);
            if (v == 0 && *(unsigned char*)((char*)this + 0x61) == 0 &&
                *(unsigned char*)((char*)this + 0x60) == 0)
                result = false;
        }
    }
    return result;
}

// @ 0x005227a0
void TickState::ClearPtr100()
{
    int** p = (int**)((char*)this + 0x100);
    if (*p != 0) {
        int* old = *p;
        *p = 0;
        if (old != 0)
            AtomicRefCounted_Release(old);
    }
}


#define F(T, off) (*(T*)((char*)this + (off)))

// @ 0x005218e0 copy-assign
TickState& TickState::Assign(const TickState& o)
{
    const char* src = (const char*)&o;
    for (int i = 0; i < 0x18; i += 4) *(int*)((char*)this + i) = *(const int*)(src + i);
    F(float, 0x18) = *(const float*)(src + 0x18);
    F(int, 0x1c) = *(const int*)(src + 0x1c);
    F(int, 0x20) = *(const int*)(src + 0x20);
    F(int, 0x24) = *(const int*)(src + 0x24);
    F(int, 0x28) = *(const int*)(src + 0x28);
    RcObj** dst = (RcObj**)((char*)this + 0x2c);
    RcObj* nw = *(RcObj* const*)(src + 0x2c);
    if (nw != *dst) {
        RcObj* old = *dst;
        if (nw) nw->AddRef();
        *dst = nw;
        if (old) old->Release();
    }
    F(int, 0x30) = *(const int*)(src + 0x30);
    F_00525d90b((char*)this + 0x34, *(const unsigned*)(src + 0x34));
    return *this;
}

// @ 0x005219d0 message handler
bool TickState::HandleMessage(int id)
{
    if (id == 0x247ca7b) {
        if (F(unsigned char, 0x7e) && F(unsigned char, 0x7d)) {
            F(unsigned char, 0x7c) = 1;
            F(unsigned char, 0x7d) = 0;
            char* req = F(char*, 0x1c);
            if (req) {
                if (*(unsigned char*)(req + 0x6a)) {
                    int** p = (int**)((char*)this + 0x100);
                    if (*p) {
                        int* old = *p;
                        *p = 0;
                        AtomicRefCounted_Release(old);
                    }
                    F_0051a6a0(p);
                }
            }
        }
    } else if (id == 0x44edd9c) {
        if (ShouldTick()) {
            // snapshot the pending-list at +0x94 into a local fixed vector, rebuild, copy back
            struct Local { unsigned* mpBegin; unsigned* mpEnd; unsigned pad[18]; } local;
            F_00525cf0(&local, (char*)this + 0x94);
            F_00523690();
            unsigned* mine = (unsigned*)((char*)this + 0x94);
            if (mine != (unsigned*)&local) {
                VecErase(mine, mine[0], mine[1]);
                VecAssign(mine, local.mpBegin, local.mpEnd);
            }
            for (unsigned* it = local.mpBegin; it < local.mpEnd; it += 2) { }
            VecFree(&local);
        }
        F(unsigned char, 0x7c) = 0;
        F(unsigned char, 0x7d) = 0;
    }
    return true;
}

// @ 0x00521ba0 per-frame update
void TickState::Tick(int dt)
{
    if (F(char*, 0x1c) != 0) {
        RandomLC* rng = &gRandom;
        unsigned saved = rng->mSeed;
        rng->SetSeed(F(unsigned, 0x58));
        char* mat = F(char*, 0xc);
        if (*(int*)(mat + 0x10) == 0)
            F_00506590(F(char*, 0xc), *(unsigned*)(F(char*, 0x1c) + 0x5c));
        HandleUpdateMessage(dt);
        float propA = 1.0f;
        float propB = 1.0f;
        GetFloatProperty(gAppProperties, 0x75cd84e9, &propA);
        GetFloatProperty(gAppProperties, 0xeaf2bc95, &propB);
        *(float*)(F(char*, 0x1c) + 0x70) = *(float*)(F(char*, 0xc) + 0x28);
        *(float*)(F(char*, 0x1c) + 0x74) = *(float*)(F(char*, 0xc) + 0x24) * propA;
        *(float*)(F(char*, 0x1c) + 0x78) = *(float*)(F(char*, 0xc) + 0x20) * propB;
        if (!ShouldTick()) {
            *(unsigned char*)(F(char*, 0x1c) + 0x6c) = 1;
            SetCreatureSkin(0, 0);
            void** p = (void**)((char*)this + 0x1c);
            if (*p) {
                void* old = *p;
                *p = 0;
                if (old) RefCounted_Release(old);
            }
        }
        F(unsigned, 0x58) = rng->mSeed;
        rng->SetSeed(saved);
    }
}

static inline bool JobDone(JobMgr* m) { return (1 << m->ContinueJob() & 0x3c) != 0; }

// @ 0x00521d70 nSPSkinner::cPaintSystem::HandleUpdateMessage
void TickState::HandleUpdateMessage(int dt)
{
    bool wasTicking = ShouldTick();
    bool a = JobDone(F(JobMgr*, 0xfc));
    bool b = JobDone(F(JobMgr*, 0xf8));
    bool c = false;
    F(int, 0x64) += dt;
    char tmp[0x4c];
    F(AOCache*, 0xf4)->SetBlendColor(tmp, 0.25f, 0.25f);

    if (F(unsigned char, 0x7e) && !F(unsigned char, 0x7c) && !F(unsigned char, 0x7d) && !a) {
        char* req = F(char*, 0x1c);
        if (req && *(unsigned char*)(req + 0x6a) && F(int, 0x100) != 0) {
            F(unsigned char, 0x7c) = 1;
        } else {
            F(MeshAORender*, 0x14)->Rebuild();
            unsigned v58 = 0xf1cf8a9d;
            if (InitVerbCollection(*(int*)(*(char**)(F(char*, 0x20) + 8) + 0x18)) == 0x438f6347)
                v58 = 0xf01f7f52;
            int lo = 0x40;
            int prop = GetIntProperty(gAppProperties, 0xb8864eac);
            int v5c = (prop < lo) ? lo : prop;
            JobFactory* jf = GetJobFactory();
            F(unsigned char, 0x7d) = jf->Create(0x46e92e0, gUnknown15de57c, F(char*, 0x10) + 0x14c, 0x247ca7b, v58, v5c);
        }
    }
    Job* job = F(Job*, 0xf0);
    if (job && !job->IsRunning()) {
        Job** p = (Job**)((char*)this + 0xf0);
        if (*p) {
            Job* old = *p;
            *p = 0;
            old->Release();
        }
    }
    if (F(unsigned char, 0x60)) {
        F(Pipeline*, 0x18)->ExecutePipeline();
        if (F(Pipeline*, 0x18)->mFramesWaited == -1) {
            F(Pipeline*, 0x18)->F_0051aaa0();
            (*(PaintListRender**)(F(char*, 0xc) + 0xc))->F_005123b0();
            F(unsigned char, 0x60) = 0;
        }
    }
    if (!GetResourceTypeFromModelType(*(int*)(F(char*, 0xc) + 8)))
        F(unsigned char, 0x61) = 1;
    if (F(unsigned char, 0x62) && !b && !F_00525a40() && F(int, 0xf0) == 0) {
        int* v = (int*)((char*)this + 0x94);
        if ((unsigned)F(int, 0xec) == (unsigned)((v[1] - v[0]) >> 3)) {
            c = true;
            F(unsigned char, 0x61) = 1;
        }
    }
    if (F(unsigned char, 0x61) && !F(unsigned char, 0x60)) {
        char* mat = F(char*, 0xc);
        ((MatObj*)*(char**)(mat + 8))->F_00526070(*(unsigned*)(mat + 0xc));
        ((MatObj*)(*(char**)(F(char*, 0xc) + 8) + 0x14))->F_00526230(*(unsigned*)(F(char*, 0xc) + 0xc) + 0x14);
        if (c) {
            unsigned char xfer = F(char*, 0x1c) ? *(unsigned char*)(F(char*, 0x1c) + 0x68) : 0;
            F(Pipeline*, 0x18)->F_0051a9a0(*(unsigned*)(F(char*, 0xc) + 0xc), 1, F(unsigned char, 0x63), F(int, 0x68),
                                           F(int, 0x6c), F(int, 0x70), F(int, 0x74), F(unsigned char, 0x78),
                                           F(unsigned char, 0x79), xfer);
            F(unsigned char, 0x62) = 0;
        } else if (F(unsigned char, 0x7a) && F(unsigned, 0x64) > 0x1f4) {
            F(Pipeline*, 0x18)->F_0051a9a0(*(unsigned*)(F(char*, 0xc) + 0xc), 0, 0, F(int, 0x68), F(int, 0x6c), 0, -1, 0, 0, 0);
            F(int, 0x64) = 0;
        } else {
            F(Pipeline*, 0x18)->F_0051a9a0(*(unsigned*)(F(char*, 0xc) + 0xc), 0, 1, 0, 0, 0, -1, 0, 0, 0);
        }
        F(Pipeline*, 0x18)->ExecutePipeline();
        F(unsigned char, 0x60) = 1;
        F(unsigned char, 0x61) = 0;
    }
    if (!F(unsigned char, 0x61) && !b && F_00525a40()) {
        *(int*)(F(char*, 0xf8) + 0x14) = 1;
        *(int*)(F(char*, 0xf8) + 0x1c) = 0;
        F(MatObj*, 0xf8)->F_006909b0();
        b = true;
    }
    if (!b && !F_00525a40() && F(int, 0xf0) == 0 && !JobDone(F(JobMgr*, 0xfc))) {
        for (;;) {
            int* v = (int*)((char*)this + 0x94);
            unsigned idx = F(unsigned, 0xec);
            if (idx >= (unsigned)((v[1] - v[0]) >> 3)) break;
            F(unsigned, 0xec) = idx + 1;
            unsigned* ent = (unsigned*)(F(int, 0x94) + idx * 8);
            F(unsigned char, 0x62) = 1;
            gRandom.SetSeed(ent[1]);
            AOCache* aoc = F(AOCache*, 0xf4);
            Job** p = (Job**)((char*)this + 0xf0);
            if (*p) {
                Job* old = *p;
                *p = 0;
                old->Release();
            }
            if ((*(unsigned char (**)(AOCache*, unsigned, int, void*))(*(char**)aoc + 8))(aoc, ent[0], 0, p)) {
                F(Job*, 0xf0)->Start(0, 0);
                break;
            }
        }
    }
    if (wasTicking && !ShouldTick()) {
        F_00523690();
        GetMessageServer()->Post(0x46d485d, 0, 0);
    }
}
