// Slice 10: nSPSkinner paint-system tick predicates and message handling helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void FUN_00525d90(void* p, void* v);      // 0x00525d90

struct RcObj { virtual void AddRef(); virtual void Release(); };
struct JobMgr {
    int ContinueJob();                                        // 0x0068f970
};
struct Job { virtual void v0(); virtual void Release(); virtual bool Start(int, void*); virtual void v3(); virtual bool IsRunning(); };
struct Vec2f { float x, y; };
struct AOCache { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
                 virtual void SetBlendColor(void* tmp, float a, float b); };   // vtable +0x3c
struct MeshAORender {
    void Rebuild();                                           // 0x00516eb0
};
struct Pipeline { void ExecutePipeline(); void F_0051aaa0(); void F_0051a9a0(unsigned plr, int, int, int, int, int, int, int, int, int); int pad[0x33c / 4]; int mFramesWaited; }; // 0x0051afd0 / 0051aaa0 / 0051a9a0
struct PaintListRender { void F_005123b0(); };                 // 0x005123b0
struct MatObj { void F_00526070(unsigned); void F_00526230(unsigned); void F_006909b0(); };
struct MsgServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void Post(int, int, int); };
struct JobFactory { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
                    virtual unsigned char Create(int, void*, void*, int, int, int); }; // vtable +0x40

class RandomLC {
public:
    unsigned mSeed;
    void SetSeed(unsigned);                                   // 0x00936090
};
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
    bool HandleMessage(int id, void* msg);                        // 0x005219d0
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
struct PairF { int first; float second; };
struct IterTag {};
// eastl::vector<eastl::pair<int,float>, sp_vector_allocator> at TickState+0x94
struct PairVector {
    PairF* mpBegin; PairF* mpEnd; PairF* mpCapacity; int mAllocator;
    PairF* erase(PairF* first, PairF* last);                     // 0x00530c80
    void DoAssign(PairF* first, PairF* last, IterTag);            // 0x005283d0
    void assign(PairF* first, PairF* last) { IterTag tag; DoAssign(first, last, tag); }
};
// eastl::fixed_vector<pair<int,float>, 8> snapshot (0x58 bytes)
struct PairFixedVector {
    PairF* mpBegin; PairF* mpEnd; PairF* mpCapacity; int mAllocator[2]; int mPool[17];
    PairFixedVector(const PairVector& src);                       // 0x00525cf0
    void DoFree();                                                // 0x00526a40
};
bool GetResourceTypeFromModelType(int modelType);                 // 0x00526430 (thiscall)

// @ 0x00522720
struct PairVec { struct E { int a, b; }; E* mpBegin; E* mpEnd; unsigned size() const { return (unsigned)(mpEnd - mpBegin); } };
struct PtrHolder { void* p; void* get() const { return p; } };
bool TickState::ShouldTick()
{
    return !(*(unsigned char*)((char*)this + 0x62) == 0 &&
             *(unsigned*)((char*)this + 0xec) >= ((PairVec*)((char*)this + 0x94))->size() &&
             ((PtrHolder*)((char*)this + 0xf0))->get() == 0 &&
             *(unsigned char*)((char*)this + 0x61) == 0 &&
             *(unsigned char*)((char*)this + 0x60) == 0);
}

extern "C" long __cdecl _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedIncrement)
struct AtomicRefCounted {
    void* vt; int pad; volatile long mRefCount;
    void AddRef() { _InterlockedIncrement(&mRefCount); }
    void Release();                                               // 0x00402420
};
template<class T> struct RefPtr {
    T* mp;
    RefPtr& operator=(T* p) { T* old = mp; if (p) p->AddRef(); mp = p; if (old) old->Release(); return *this; }
    __forceinline void Clear() { if (mp) *this = 0; }
};

// @ 0x005227a0
void TickState::ClearPtr100()
{
    ((RefPtr<AtomicRefCounted>*)((char*)this + 0x100))->Clear();
}


#define F(T, off) (*(T*)((char*)this + (off)))

// Smart-pointer member views for the copy-assign below.
template<class T> struct VRefPtr {
    T* mp;
    VRefPtr& operator=(T* p) { if (p != mp) { T* old = mp; if (p) p->AddRef(); mp = p; if (old) old->Release(); } return *this; }
    VRefPtr& operator=(const VRefPtr& o) { return operator=(o.mp); }
};
struct CountedObj;
struct CountedPtr { CountedObj* mp; CountedPtr& operator=(CountedObj* p);   // 0x00525d90 (thiscall, out of line)
                    CountedPtr& operator=(const CountedPtr& o) { return operator=(o.mp); } };
struct Vec3Copy { float x, y, z; };
struct TickStateParams {
    Vec3Copy a; Vec3Copy b; float f18; int i1c, i20, i24, i28;
    VRefPtr<RcObj> r2c; int i30; CountedPtr p34;
};

// @ 0x005218e0 copy-assign (shaped like a compiler-generated operator=; the original frame has two more unused slots)
TickState& TickState::Assign(const TickState& o)
{
#define D (*(TickStateParams*)this)
#define S (*(const TickStateParams*)&o)
    D.a = S.a;
    D.b = S.b;
    D.f18 = S.f18;
    D.i1c = S.i1c;
    D.i20 = S.i20;
    D.i24 = S.i24;
    D.i28 = S.i28;
    D.r2c = S.r2c;
    D.i30 = S.i30;
    D.p34 = S.p34;
#undef D
#undef S
    return *this;
}

// @ 0x005219d0 message handler
bool TickState::HandleMessage(int id, void* msg)
{
    switch (id) {
    case 0x247ca7b:
        if (F(unsigned char, 0x7e) && F(unsigned char, 0x7d)) {
            F(unsigned char, 0x7c) = 1;
            F(unsigned char, 0x7d) = 0;
            char* req = F(char*, 0x1c);
            if (req) {
                char* req2 = F(char*, 0x1c);
                if (*(unsigned char*)(req2 + 0x6a)) {
                    AtomicRefCounted** p = (AtomicRefCounted**)((char*)this + 0x100);
                    if (*p) {
                        AtomicRefCounted* old = *p;
                        *p = 0;
                        old->Release();
                    }
                    F_0051a6a0(p);
                }
            }
        }
        break;
    case 0x44edd9c:
        if (ShouldTick()) {
            // snapshot the pending list at +0x94, rebuild it, then restore the snapshot
            PairFixedVector local(*(PairVector*)((char*)this + 0x94));
            F_00523690();
            PairVector* mine = (PairVector*)((char*)this + 0x94);
            if ((void*)mine != (void*)&local) {
                mine->erase(mine->mpBegin, mine->mpEnd);
                mine->assign(local.mpBegin, local.mpEnd);
            }
            for (PairF* it = local.mpBegin; it < local.mpEnd; ++it) { }
            local.DoFree();
        }
        F(unsigned char, 0x7c) = 0;
        F(unsigned char, 0x7d) = 0;
        break;
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
