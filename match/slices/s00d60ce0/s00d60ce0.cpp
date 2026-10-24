// Slice s00d60ce0: SP::cCityVisualizer::SetCity (0x00d60f00), swap the visualised city.
//
// Retail layout differs from the 2008 PDB, so members are accessed by retail byte offset
// (F<T>(p, off)), as in the sibling slice s00d5fb60.
//
// When the previous city is replaced, everything the visualizer cached for it is torn down
// (citizen list, vignette instances, per-culture-stage actor lists, sound list, event
// sounds, vignette array); then the new city is stored (intrusive AddRef/Release) and the
// bookkeeping is re-armed for it (citizen counts, timers, culture stage reset, slot circles,
// vignette spots, artifacts, per-city caches).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned int u32;
extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // thunk 0x011e0744

template <class T> static inline T& F(void* p, int off) { return *(T*)((char*)p + off); }

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
template <class R, class A, class B, class C> static inline R VC3(void* o, int slot, A a, B b, C c) {
    typedef R(__thiscall * Fn)(void*, A, B, C);
    return ((Fn)(*(void***)o)[slot])(o, a, b, c);
}

// Intrusive ref-counted object: slot 0 AddRef, slot 1 Release, slot 3 Destroy(flag).
struct IRef {
    virtual void AddRef();
    virtual void Release();
    virtual void v08();
    virtual void Destroy(int flag);
};

struct Vec3 { u32 x, y, z; };
struct Vec3f { float x, y, z; };
struct Rec18 { u32 d[6]; };
struct Rec20 { u32 d[5]; };

// eastl::vector with the sp allocator (0x14 bytes)
template <class T> struct SpVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    u32 mAllocator[2];
};

// ---- extern helpers ---------------------------------------------------------------------
// eastl::copy for AutoRefCount<T> ranges (cdecl): copy [first,last) to dst, returns dst end
IRef** CopyRefs(IRef** first, IRef** last, IRef** dst);      // 0x006782c0
Rec18* CopyRec18(Rec18* first, Rec18* last, Rec18* dst);     // 0x00afa430
struct Rec18Dtor { void FUN_007455d0(); };                   // 0x007455d0 (thiscall on the element)

struct Timer {
    void Restart();                     // 0x00bc3130
};
struct Timer2 { void FUN_00bc3170(); }; // 0x00bc3170

struct SimA { void FUN_00accf80(void* creature); };   // ret 4
SimA* FUN_00b3d480();                                   // 0x00b3d480 (no args)
struct SimB { void FUN_00bc5040(u32 id); };            // ret 4
SimB* FUN_00b3d4e0();                                   // 0x00b3d4e0 (no args)
void  FUN_00bc8fa0(const void* p);                      // cdecl, one arg
void  FUN_00c0d3a0(void* creature);                     // cdecl, one arg
struct HostB { void FUN_00bcb3d0(); };                  // 0x00bcb3d0
struct Creature { void FUN_00c227c0(); };               // 0x00c227c0
void  StopAndClearSoundList(void* list);                // 0x00d5adf0 cdecl

struct AudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Begin(u32 id);                      // 0x38
    virtual void v3c();
    virtual void SetParam(u32 id, u32 value);        // 0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void Commit();                           // 0x58
};
AudioSystem* GetSystemAT();                          // 0x00a206f0

struct City;
struct Viz;

struct City {
    int   GetCreatureCount();       // 0x00bd8120
    float FUN_00bd7d00();           // 0x00bd7d00
    void  FUN_00bd9e80(int i);      // ret 4
    u32   GetMembers();             // 0x00c8e810 (as cTribe)
    u32   FUN_00bd8130();           // 0x00bd8130
    struct Layout* FUN_00bd7f40();  // 0x00bd7f40 (returns this+0x3ec)
    Vec3f* FUN_00bd9480(Vec3f* out);// 0x00bd9480 (ret 4)
    void  FUN_00bd7f70(Vec3f* a, Vec3f* b);  // 0x00bd7f70 (ret 8)
};

template <class T> struct DstVec;   // unused

// Retail cActionCircle is 0x64 bytes: the agent and slot vectors are its last two members.
struct Circle {
    char pad0[0x3c];
    SpVec<IRef*> mAgents;       // +0x3c
    SpVec<Rec18> mSlots;        // +0x50
};
// Retail tCultureStage (0x198 bytes); the array starts at Viz+0x38c.
struct Stage {
    u32 mActive, mReserved, mRequested, mElapsed, m10;
    char mTimer[0x20];          // +0x14
    Circle mGate;               // +0x34
    Circle mGroup[2];           // +0x98
    SpVec<IRef*> mParticipants[2];   // +0x160
    int mDeltaIn[2];
    int mDeltaOut[2];
};

// vignette instance record (0x1c bytes)
struct VigInfo { u32 id; char pad4; char flag5; char pad6[2]; u32 rest[5]; };

struct Viz {
    void FUN_00d57940(void* x);                 // ret 4
    void FUN_00d5b8d0();
    void StopVignetteInstance(VigInfo* v);      // 0x00d57f80
    void FUN_00d5bfa0(int a);                   // 0x00d5bfa0
    void FUN_00d5c8c0();
    void UpdateSlotCircles();                   // 0x00d60ce0
    void LayoutChanged();                       // 0x00d61880
    void SetupVignetteSpots(int a);             // 0x00d57b50
    void UpdateArtifacts();                     // 0x00d5de40
    void FUN_00d5c720();
    void FUN_01011cc0_dummy();
    void SetCity(City* city);                   // 0x00d60f00
};

// vector<AutoRefCount<ILogReporter>> erase(first,last) (non-inline, ret 8)
struct RefVec : SpVec<IRef*> {
    void erase(IRef** first, IRef** last);      // 0x00e25bd0
};
struct VigVec : SpVec<VigInfo> {
    void FUN_00d595d0(VigInfo* newEnd, VigInfo* oldEnd);   // ret 8
};
struct Vec3Vec : SpVec<Vec3> {
    void DoInsertN(Vec3* pos, u32 n, const Vec3& v);       // 0x00479330 (ret 0xc)
};
struct CountVec : SpVec<u32> {
    void FUN_01011cc0(u32 v);                   // ret 4 (assign/append)
};
VigInfo* CopyVig(VigInfo* first, VigInfo* last, VigInfo* dst);   // 0x00d5bf00 cdecl

extern char g_Init169ec25;     // 0x0169ec25
extern u32  g_PosX;   // 0x0169ec28 (invalid position sentinel)
extern u32  g_PosY;   // 0x0169ec2c
extern u32  g_PosZ;   // 0x0169ec30

// AutoRefCount range clear: copy [end,end) over begin (no-op), destroy tail, shrink.
static inline void ClearRefs(SpVec<IRef*>* v)
{
    IRef**& rend = v->mpEnd;
    IRef** b = v->mpBegin;
    IRef** e = rend;
    IRef** it = CopyRefs(e, e, b);
    IRef** end = rend;
    for (; it < end; ++it)
        if (*it)
            (*it)->Release();
    rend -= (e - b);
}

// eastl::vector<POD>::erase(first, last): copy the tail down, (trivially) destroy the rest, shrink.
template <class T> static inline void ErasePod(SpVec<T>* v, T* first, T* last)
{
    T* end = v->mpEnd;
    T* d = first;
    for (T* s = last; s != end; ++s, ++d)
        *d = *s;
    for (T* q = d; q < v->mpEnd; ++q)
        ;
    v->mpEnd -= (last - first);
}

static inline void ClearRec18(SpVec<Rec18>* v)
{
    Rec18*& rend = v->mpEnd;
    Rec18* b = v->mpBegin;
    Rec18* e = rend;
    Rec18* it = CopyRec18(e, e, b);
    Rec18* end = rend;
    for (; it < end; ++it)
        ((Rec18Dtor*)it)->FUN_007455d0();
    rend -= (e - b);
}

static inline void DestroyRefMember(void* viz, int off)
{
    IRef* p = F<IRef*>(viz, off);
    if (p) {
        p->Destroy(1);
        p = F<IRef*>(viz, off);
        if (p) {
            F<IRef*>(viz, off) = 0;
            p->Release();
        }
    }
}

static inline void ReleaseAudioHandle(void* viz, int off)
{
    u32 h = F<u32>(viz, off);
    if (h != 0) {
        AudioSystem* at = GetSystemAT();
        if (at) {
            at->Begin(0x347536b);
            at->SetParam(0x3475385, h);
            at->SetParam(0x34753a0, 0);
            at->Commit();
        }
        F<u32>(viz, off) = 0;
    }
}

// @ 0x00d60f00
void Viz::SetCity(City* city)
{
    F<int>(this, 0xc3c) = -1;
    F<int>(this, 0xa4c) = -1;
    if (!g_Init169ec25) {
        FUN_00bc8fa0((const void*)0x1592928);
        FUN_00bc8fa0((const void*)0x1592d00);
        g_Init169ec25 = 1;
    }
    F<bool>(this, 0xaf4) = true;
    FUN_00b3d480();

    City* old = F<City*>(this, 0xaf0);
    if (city != old) {
        if (old != 0) {
            if (city == 0) {
                DestroyRefMember(this, 0xb60);
                DestroyRefMember(this, 0xb64);
                DestroyRefMember(this, 0xb68);
                DestroyRefMember(this, 0xb5c);
            }
            // cached citizens
            RefVec* citizens = (RefVec*)((char*)this + 0xa64);
            int n = citizens->mpEnd - citizens->mpBegin;
            for (int i = 0; i < n; ++i)
                FUN_00d57940(citizens->mpBegin[i]);
            citizens->erase(citizens->mpBegin, citizens->mpEnd);

            // vignette creature instances
            SpVec<char*>* inst = (SpVec<char*>*)((char*)this + 0xac8);
            int m = inst->mpEnd - inst->mpBegin;
            for (int i = 0; i < m; ++i) {
                char* c = inst->mpBegin[i];
                VC1<void, int>(c, 18, -1);
                char* t = F<char*>(c, 0xb54);
                if (t) {
                    char* u = F<char*>(t, 0x180);
                    if (u)
                        F<u32>(u, 4) &= 0xfffff7ff;
                }
                FUN_00c0d3a0(c);
                ((HostB*)F<void*>(c, 0xb4c))->FUN_00bcb3d0();
                FUN_00b3d480()->FUN_00accf80(c);
                ((Creature*)c)->FUN_00c227c0();
            }
            ClearRefs((SpVec<IRef*>*)((char*)this + 0xac8));
            FUN_00d5b8d0();
            ClearRefs((SpVec<IRef*>*)((char*)this + 0x364));
            ClearRefs((SpVec<IRef*>*)((char*)this + 0x378));

            IRef* o = F<IRef*>(this, 0x38c);
            F<IRef*>(this, 0x38c) = 0;
            if (o)
                VC0<void>(o, 48);

            // sound list
            char* sounds = (char*)this + 0xb00;
            StopAndClearSoundList(sounds);
            {
                SpVec<u32>* v = (SpVec<u32>*)sounds;
                u32* first = v->mpBegin;
                u32* last = v->mpEnd;
                memmove(first, last, (char*)v->mpEnd - (char*)last);
                v->mpEnd -= (last - first);
            }
            F<u32>(this, 0xb14) = 0;
            ReleaseAudioHandle(this, 0xb4c);
            {
                u32 h = F<u32>(this, 0xb50);
                if (h != 0) {
                    AudioSystem* at = GetSystemAT();
                    if (at) {
                        at->Begin(0x347536b);
                        at->SetParam(0x3475385, h);
                        at->SetParam(0x34753a0, 0);
                        at->Commit();
                    }
                    F<u32>(this, 0xb50) = 0;
                    F<char>(this, 0xb54) = 0;
                }
            }

            // culture stages: actor lists
            Stage* stages = (Stage*)((char*)this + 0x38c);
            for (int g = 0; g < 4; ++g) {
                F<City*>(this, 0xaf0)->FUN_00bd9e80(g);
                for (int j = 0; j < 2; ++j) {
                    ClearRefs(&stages[g].mParticipants[j]);
                    ClearRec18(&stages[g].mGroup[j].mSlots);
                }
            }
            if (F<int>(F<City*>(this, 0xaf0), 0x2cc) == 0)
                F<int>(F<City*>(this, 0xaf0), 0x2cc) = 1;

            // vignette instances
            VigVec* vig = (VigVec*)((char*)this + 0xbbc);
            for (int i = 0; i < (int)(vig->mpEnd - vig->mpBegin); ++i) {
                VigInfo* p = vig->mpBegin + i;
                StopVignetteInstance(p);
                if (p->flag5)
                    F<char>(this, 0xa40) = 0;
                FUN_00b3d4e0()->FUN_00bc5040(p->id);
            }
            {
                VigInfo* b = vig->mpBegin;
                VigInfo* e = vig->mpEnd;
                VigInfo* it = CopyVig(e, e, b);
                vig->FUN_00d595d0(it, vig->mpEnd);
                vig->mpEnd -= (e - b);
            }
            F<u32>(this, 0xae4) = 0;
            F<u32>(this, 0xae0) = 0;
            F<u32>(this, 0xadc) = 0;
            {
                IRef* a = F<IRef*>(this, 0xa54);
                F<IRef*>(this, 0xa54) = 0;
                if (a)
                    a->Release();
                F<char>(this, 0xa51) = 0;
                IRef* b2 = F<IRef*>(this, 0xa58);
                F<IRef*>(this, 0xa58) = 0;
                if (b2)
                    VC0<void>(b2, 25);
                F<u32>(this, 0xa60) = 0;
                F<u32>(this, 0xa5c) = 0;
            }
        }
        City* cur = F<City*>(this, 0xaf0);
        if (city != cur) {
            if (city)
                VC0<void>(city, 0);
            F<City*>(this, 0xaf0) = city;
            if (cur)
                VC0<void>(cur, 1);
        }
    }

    if (F<City*>(this, 0xaf0) == 0)
        return;

    City* c = F<City*>(this, 0xaf0);
    u32 want = c->GetCreatureCount();
    F<float>(this, 0xb58) = F<City*>(this, 0xaf0)->FUN_00bd7d00();
    ((Timer*)((char*)this + 0xb28))->Restart();
    F<u32>(this, 0xb20) = 0;
    ((CountVec*)((char*)this + 0x364))->FUN_01011cc0(F<City*>(this, 0xaf0)->GetMembers());
    ((CountVec*)((char*)this + 0x378))->FUN_01011cc0(F<City*>(this, 0xaf0)->FUN_00bd8130());
    FUN_00d5bfa0(1);
    F<u32>(this, 0xa28) = 0;
    F<u32>(this, 0xa30) = 0;
    F<u32>(this, 0xc38) = 1;
    ((Timer*)((char*)this + 0xc40))->Restart();
    F<char>(this, 0xa40) = 0;
    FUN_00d5c8c0();
    F<u32>(this, 0x158) = g_PosX;
    F<u32>(this, 0x15c) = g_PosY;
    F<u32>(this, 0x160) = g_PosZ;
    F<int>(this, 0xa44) = -1;

    // resize the per-citizen slot vector to the creature count
    {
        Vec3Vec* v = (Vec3Vec*)((char*)this + 0xb6c);
        u32 size = v->mpEnd - v->mpBegin;
        if (want > size) {
            Vec3 tmp;
            v->DoInsertN(v->mpEnd, want - size, tmp);
        } else {
            ErasePod(v, v->mpBegin + want, v->mpEnd);
        }
    }

    Stage* stages = (Stage*)((char*)this + 0x38c);
    for (int g = 0; g < 4; ++g) {
        F<City*>(this, 0xaf0)->FUN_00bd9e80(g);
        for (int j = 0; j < 2; ++j) {
            stages[g].mReserved = 0;
            stages[g].mRequested = 0;
            stages[g].mElapsed = 0;
            stages[g].m10 = 0;
            ((Timer2*)stages[g].mTimer)->FUN_00bc3170();
            ClearRec18(&stages[g].mGate.mSlots);
        }
    }
    UpdateSlotCircles();
    SetupVignetteSpots(0);
    UpdateArtifacts();
    ((Timer*)((char*)this + 0xc68))->Restart();
    FUN_00d5c720();

    {
        char* cc = F<char*>(this, 0xaf0);
        SpVec<Rec20>* v = (SpVec<Rec20>*)(cc + 0x2a4);
        ErasePod(v, v->mpBegin, v->mpEnd);
    }
    {
        char* cc = F<char*>(this, 0xaf0);
        SpVec<Rec20>* v = (SpVec<Rec20>*)(cc + 0x2b8);
        ErasePod(v, v->mpBegin, v->mpEnd);
    }
    {
        char* cc = F<char*>(this, 0xaf0);
        F<u32>(cc, 0x2d4) = g_PosX;
        F<u32>(cc, 0x2d8) = g_PosY;
        F<u32>(cc, 0x2dc) = g_PosZ;
    }
    F<u32>(F<char*>(this, 0xaf0), 0x2cc) = 0;
    F<u32>(F<char*>(this, 0xaf0), 0x2d0) = 0;
    F<u32>(this, 0xa38) = 0;
    F<u32>(this, 0xa3c) = 0;
}

// ============================================================================
// worker 18 additions (gold7): 0x00d60ce0, 0x00d61880, 0x00d61b20..0x00d61be0
// ============================================================================

// SP::cActionCircle (0x64 bytes) - only the members the loop needs are named.
struct ACircle {
    u32 d[0x19];
    void ctor();                                                 // 0x00afba10
    void dtor();                                                 // 0x00afbad0
    void FUN_00afd6d0(float a, float b, int c);                  // 0x00afd6d0
    void SetAtCenter(const Vec3f* center, float radius,
                     const Vec3f* facing, float altitude);       // 0x00af9cf0 (ret 0x10)
};

// eastl::vector<cActionCircle> (0x14 bytes)
struct CircleVec {
    ACircle* mpBegin;
    ACircle* mpEnd;
    ACircle* mpCapacity;
    u32 mAlloc[2];
    ACircle* erase(ACircle* first, ACircle* last);               // 0x00d5edc0 (ret 8)
    void FUN_00d5ee20(ACircle* pos, ACircle* val);               // 0x00d5ee20 (ret 8)
};

// element returned by Layout::SlotAt; GetOccupant reads its +4 pointer.
struct SlotElem {
    void* GetOccupant();                                         // 0x00fcc210
};

// The object FUN_00bd7f40 returns is the city's layout block at city+0x3ec.
struct Layout {
    u32 pad0[4];
    float mField10;          // +0x10
    u32 pad14[0xf];
    void* mpSlotBegin;       // +0x50
    void* mpSlotEnd;         // +0x54
    void* SlotAt(u32 i);                                         // 0x00af9ff0 (ret 4)
};

// eastl::vector<pointer> (0x14 bytes) - the gate-citizen lists and city lists.
struct PtrVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    u32 mAlloc[2];
    void Assign(void* other);                                    // 0x01011cc0 (ret 4)
};

extern float g_eps_13ec4b8;   // 0x013ec4b8
extern u32   g_negmask;       // 0x013eb8b0
extern float g_c1470f1c;      // 0x01470f1c
extern float g_c1471064;      // 0x01471064
extern float g_one_1485720;   // 0x01485720
extern float g_c147b9a4;      // 0x0147b9a4

void FUN_00d5b9f0();          // 0x00d5b9f0

// @ 0x00d60ce0
void Viz::UpdateSlotCircles()
{
    CircleVec* circles = (CircleVec*)((char*)this + 0x220);
    circles->erase(circles->mpBegin, circles->mpEnd);

    Layout* lay = F<City*>(this, 0xaf0)->FUN_00bd7f40();
    float base = F<float>(lay, 0x10);
    int n = (int)((char*)F<void*>(lay, 0x54) - (char*)F<void*>(lay, 0x50)) / 0x18;

    for (int i = 0; i < n; ++i) {
        void* slot = lay->SlotAt(i);
        void* occ = ((SlotElem*)slot)->GetOccupant();
        float radius;
        if (occ) {
            void* item = VC1<void*, u32>(occ, 3, 0x1186577);
            if (item) radius = VC0<float>(item, 29);
            else radius = base;
        } else {
            radius = base;
        }

        float* pv = (float*)((char*)F<void*>(lay, 0x50) + i * 0x18 + 0xc);
        Vec3f pos;
        pos.x = pv[0];
        pos.y = pv[1];
        pos.z = pv[2];

        if (circles->mpEnd < circles->mpCapacity) {
            ACircle* e = circles->mpEnd;
            circles->mpEnd = e + 1;
            if (e) e->ctor();
        } else {
            ACircle tmp;
            tmp.ctor();
            circles->FUN_00d5ee20(circles->mpEnd, &tmp);
            tmp.dtor();
        }

        Vec3f outv;
        Vec3f* ctr = F<City*>(this, 0xaf0)->FUN_00bd9480(&outv);
        float dy = ctr->y - pos.y;
        float dz = ctr->z - pos.z;
        float dx = ctr->x - pos.x;
        float inv = 1.0f / sqrtf(dy * dy + dz * dz + dx * dx + g_eps_13ec4b8);
        Vec3f dir;
        dir.x = inv * dx;
        dir.y = inv * dy;
        dir.z = inv * dz;

        ACircle* last = circles->mpEnd - 1;
        last->SetAtCenter(&pos, radius, &dir, 0.0f);
        last->FUN_00afd6d0(g_c1470f1c, 1.0f, 12);
    }
}

// @ 0x00d61880
void Viz::LayoutChanged()
{
    F<bool>(this, 8) = true;

    IRef* old = F<IRef*>(this, 0x38c);
    F<IRef*>(this, 0x38c) = 0;
    if (old) VC0<void>(old, 48);

    int flag = 4;
    City* city = F<City*>(this, 0xaf0);
    PtrVec* members = (PtrVec*)city->GetMembers();
    PtrVec* others = (PtrVec*)city->FUN_00bd8130();

    {
        u32* it = (u32*)members->mpBegin;
        u32* end = (u32*)members->mpEnd;
        for (; it != end; ++it) {
            u32* g = (u32*)F<void*>(this, 0x364);
            u32* ge = (u32*)F<void*>(this, 0x368);
            while (g != ge && *g != *it) ++g;
            if (g != ge) continue;

            IRef* obj = *it ? (IRef*)(*it + 0x34) : 0;
            IRef* prev = F<IRef*>(this, 0x38c);
            if (obj != prev) {
                if (obj) VC0<void>(obj, 47);
                F<IRef*>(this, 0x38c) = obj;
                if (prev) VC0<void>(prev, 48);
            }
            flag = 0xc;
        }
    }

    if (F<void*>(this, 0x38c) == 0) {
        u32* it = (u32*)others->mpBegin;
        u32* end = (u32*)others->mpEnd;
        for (; it != end; ++it) {
            u32* g = (u32*)F<void*>(this, 0x378);
            u32* ge = (u32*)F<void*>(this, 0x37c);
            while (g != ge && *g != *it) ++g;
            if (g != ge) continue;

            IRef* obj = *it ? (IRef*)(*it + 0x70) : 0;
            IRef* prev = F<IRef*>(this, 0x38c);
            if (obj != prev) {
                if (obj) VC0<void>(obj, 47);
                F<IRef*>(this, 0x38c) = obj;
                if (prev) VC0<void>(prev, 48);
            }
        }
    }

    char* obj = F<char*>(this, 0x38c);
    if (obj) {
        Vec3f tmp;
        Vec3f* p = VC1<Vec3f*, Vec3f*>(obj, 23, &tmp);
        Vec3f neg;
        neg.x = -p->x;
        neg.y = -p->y;
        neg.z = -p->z;
        float r = VC1<float, Vec3f*>(obj, 29, &neg) + 1.0f;
        Vec3f* ctr = VC1<Vec3f*, float>(obj, 11, r);
        ACircle* circ = (ACircle*)((char*)this + 0x1bc);
        circ->SetAtCenter(ctr, r, &neg, 0.0f);
        circ->FUN_00afd6d0(g_c1470f1c, g_c1471064, flag);
    }

    ((PtrVec*)((char*)this + 0x364))->Assign(members);
    ((PtrVec*)((char*)this + 0x378))->Assign(others);
    SetupVignetteSpots(1);

    Vec3f a, b;
    F<City*>(this, 0xaf0)->FUN_00bd7f70(&a, &b);
    float dx = F<float>(this, 0x20) - a.x;
    float dy = F<float>(this, 0x24) - b.z;
    float dz = F<float>(this, 0x28) - b.x;
    if (sqrtf(dz * dz + dy * dy + dx * dx) <= g_c147b9a4)
        FUN_00d5b9f0();
    else
        FUN_00d5c8c0();
    UpdateSlotCircles();
}

// --- small behaviour-tree guards (0x00d61b20 .. 0x00d61be0) ------------------

typedef unsigned char u8;

struct Node {
    char pad0[0x6c];
    u32  mFlags;                // +0x6c
    int  Parent();              // 0x00ff0420
};
Node* GetActiveNode();          // 0x00d51660

struct CreatureB {
    void FUN_00c0b370(int a);       // 0x00c0b370
    void UpdateLocomotion(int m);   // 0x00c14750
};

struct StimSetB {
    void ClearAll(int type, int flags);   // 0x00bc98f0
};

struct AvatarN { int Get(); };            // 0x00c04590
struct NounMgr { AvatarN* GetAvatar(); }; // 0x00b1fdb0
NounMgr* NounManagerB();                  // 0x00b3d300

// @ 0x00d61b20
void FUN_00d61b20(Creature* c)
{
    VC3<void, int, int, int>(c, 33, 0, 0, 0);
    ((CreatureB*)c)->UpdateLocomotion(0);
}

// @ 0x00d61b50
float FUN_00d61b50(int v)
{
    Node* n = GetActiveNode();
    if (((u8)(n->mFlags >> 4) & 1) != 0 && n->Parent() == v)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d61b80
void FUN_00d61b80(CreatureB* c, int a2, int a3, int a4, int a5, int* out)
{
    c->FUN_00c0b370(-1);
    ((StimSetB*)(F<char*>(c, 0xb4c) + 8))->ClearAll(0, 0x10);
    out[2] = -1;
}

// @ 0x00d61bb0
float FUN_00d61bb0()
{
    Node* n = GetActiveNode();
    if (((u8)(n->mFlags >> 4) & 1) != 0 && n->Parent() != 0)
        return 1.0f;
    return 0.0f;
}

// @ 0x00d61be0
float FUN_00d61be0(void* a1)
{
    AvatarN* avatar = NounManagerB()->GetAvatar();
    Node* n = GetActiveNode();
    if (((u8)(n->mFlags >> 4) & 1) != 0) {
        int x = avatar->Get();
        int y = ((AvatarN*)a1)->Get();
        if (y == x)
            return 1.0f;
    }
    return 0.0f;
}
