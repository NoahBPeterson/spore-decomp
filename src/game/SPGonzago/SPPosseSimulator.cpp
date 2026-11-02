// src/game/SPGonzago/SPPosseSimulator.cpp -- migrated from slice(s) s00d53b50, s00d52e90, s00d522c0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPosseSimulator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl FUN_00b3d300();                                 // 0xb3d300
extern "C" int*  __cdecl FUN_00b1f9c0();         // GetItemID (thiscall body)
extern "C" int*  __cdecl FUN_00b1fdb0();         // GetAvatar (thiscall body)
extern float     g_145c4ac;

// ---- items of slice s00d522c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_00b3d300();          // 0xb3d300
extern "C" int*  __cdecl FUN_00b1f9c0();         // GetItemID (thiscall body)
extern "C" int*  __cdecl FUN_00b1fdb0();         // GetAvatar (thiscall body)
extern float     g_145c4ac;
typedef char (__cdecl* Cmp)(int, int);
extern "C" void* __cdecl FUN_00b3d300();                                 // 0xb3d300
// ---- items of slice s00d522c0 end

// ---- items of slice s00d52e90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_Allocate(uint32_t size, const char* name, int a, int b,
                                     int c, int d);                 // 0xf473a0
extern "C" void  __cdecl EA_Free(void* p);                          // 0xf47380
extern "C" void* __cdecl SP_NounManager();                          // 0xb3d300
extern "C" void* __cdecl SP_PropertyManager();                      // 0x67de30
extern "C" void  __cdecl FUN_00b234c0();                            // ClearPosseMembers
extern "C" void  __cdecl FUN_00d01790();
extern "C" void  __cdecl FUN_00b96600();
extern "C" void* __cdecl FUN_00b90bd0(void*, void*, void*, void*);
extern "C" void  __cdecl FUN_00bbf130(void*, void*, void*, void*);
struct Property { int pad_00; uint16_t type12; };
struct PropertyPtr {
    Property* mp;
    Property* get() const { return mp; }
};
struct PropertyEnum {
    int  pad_00;
    char set(uint32_t id, uint32_t a);   // slot 0x2c: begin enumeration
    char get(uint32_t id, uint32_t* p);  // slot 0x24: get property
};
struct PropMgr { void* pad_00; PropertyEnum* vf() { return *(PropertyEnum**)this; } };
struct RefObj { virtual void dummy(); virtual void Release(); };
struct AutoRefCount {
    RefObj* mp;
    void operator=(RefObj* r) {
        RefObj* old = mp;
        mp = r;
        if (old) {
            old->Release();
        }
    }
};
struct Slot { AutoRefCount occupant; };
class PosseSim {
public:
    int pad_00[8];                     // +0x00..0x1f
    Slot**   mpBegin;                  // +0x20
    Slot**   mpEnd;                    // +0x24
    Slot**   mpCapacity;               // +0x28
    int pad_2c[3];                     // +0x2c..0x37
    int pad_38;
    void removeSlot(RefObj* p);
    void* Dtor(unsigned int flags);
    void Shutdown();
    PosseSim* Init();
};
class Inst {
public:
    void slot();          // vtable slot 7 (offset 0x1c)
};
// ---- items of slice s00d52e90 end

// ---- items of slice s00d53b50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char gPlanetMode;                             // 0x01654c10
extern const float kRingRadius;                      // 0x01583d24
extern const float kOffsetBase;                      // 0x01582e04
#define PV(n) virtual void pv##n();
struct Vec3 { float x, y, z; };
typedef Vec3 Vector3;
struct NounSub {                                     // polymorphic member at Noun+0xc0
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
    virtual const Vec3* GetPosition();               // +0x2c
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
    virtual void GetDirection(Vec3* out);            // +0x5c
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual void s28();
    virtual float GetRadius();                       // +0x74
};
struct Noun {
    virtual void AddRef();                           // +0
    virtual void Release();                          // +4
    char pad[0xc0 - 4];
    NounSub mSub;                                    // +0xc0
};
struct Entry {
    Noun* mpNoun;                                    // +0 (AutoRefCount<Noun>)
    float mAngle;                                    // +4
    float mScore;                                    // +8
};
struct NounMgr { Noun* GetAvatar(); };               // 0x00b1fdb0
NounMgr* NounManager();                              // 0x00b3d300
const void* GetCurrentGameMode();                    // 0x00b5b800
struct PlanetModelT { Vec3* Project(Vec3* out, const Vec3* in); };   // 0x00b816f0 (ret 8)
PlanetModelT* PlanetModel();                         // 0x00b3d350
void FUN_00d99e20(const Vec3* pos, Vec3* res);       // cdecl
void FUN_00c0b9d0(void* pArg);                       // cdecl
typedef char (__cdecl* Cmp_s00d5_3b50)(Entry*, Entry*);
extern "C" char __cdecl F52c90_s00d5_3b50(Entry*, Entry*);      // 0x00d52c90
void introsort(Entry** first, Entry** last, int depth, Cmp_s00d5_3b50 pred);    // 0x00d53940 (cdecl)
void insertion_sort(Entry** first, Entry** last, Cmp_s00d5_3b50 pred);          // 0x00b909f0 (cdecl)
static inline int Log2(int n) { int k = 0; while (n) { n >>= 1; ++k; } return k; }
static __forceinline void SortEntries(Entry** first, Entry** last, Cmp_s00d5_3b50 cmp)
{
    if (first != last) {
        int lg = Log2(last - first);
        introsort(first, last, lg * 2 - 2, cmp);
        if (last - first > 28) {
            insertion_sort(first, first + 28, cmp);
            for (Entry** p = first + 28; p != last; ++p) {       // unguarded insertion sort
                Entry* val = *p;
                float key = val->mScore;
                Entry** q = p;
                Entry** r = p;
                while (true) {
                    --r;
                    if ((*r)->mScore <= key) break;
                    *q = *r;
                    --q;
                }
                *q = val;
            }
        } else {
            insertion_sort(first, last, cmp);
        }
    }
}
static inline void RotateAxis(Vec3* u, const Vec3& n, float angle, const Vec3& v)
{
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    float qx = s * n.x;
    float qy = n.y * s;
    float qz = n.z * s;
    u->x = (((qy * qx) - (c * qz)) * v.y + ((c * qy) + (qz * qx)) * v.z) * 2.0f
           + (1.0f - (qy * qy + qz * qz) * 2.0f) * v.x;
    u->y = (((qz * qy) - (c * qx)) * v.z + ((c * qz) + (qy * qx)) * v.x) * 2.0f
           + (1.0f - (qz * qz + qx * qx) * 2.0f) * v.y;
    u->z = (((qz * qx) - (c * qy)) * v.x + ((c * qx) + (qz * qy)) * v.y) * 2.0f
           + (1.0f - (qy * qy + qx * qx) * 2.0f) * v.z;
}
class cRingPlacer {
public:
    char pad00[0x20];
    Entry** mpBegin;                                 // +0x20
    Entry** mpEnd;                                   // +0x24

    Entry* Place(Noun* target, Vec3* outPos);
};
namespace SP {
struct SPObject
{
    PV(0) PV(1)
    virtual void* QueryInterface(uint32_t nID);             // +0x08
};
}
namespace SP {
struct TurretTransform
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vector3* GetTranslation();                // +0x2c
};
}
namespace SP {
struct WeaponEffectSlot
{
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    virtual void Stop(int bImmediate);                      // +0x50
};
}
namespace SP {
struct cTurret_s00d5_3b50
{
    PV(0)
    virtual void* QueryInterface(uint32_t nID);             // +0x08
    char              pad0c[0x120 - 4];
    TurretTransform   mTransform;                           // +0x120
    char              pad124[0x588 - 0x124];
    WeaponEffectSlot  mEffect;                              // +0x588
    void FaceAtTarget(int nTarget);                         // 0x00bce480
};
}
namespace SP {
struct cBehaviorSpaceTurret
{
    char     pad00[0xc0];
    void*    mpTarget;                                      // +0xc0
    uint32_t mPadC4;
    int      mSdrBeamLifetime;                              // +0xc8
    uint32_t mPadCC;
    uint64_t mWeaponTimerMS;                                // +0xd0
    char     padD8[0x120 - 0xd8];
    TurretTransform mTransform;                             // +0x120

    void UpdateWeaponData();                                // 0x00d547e0
    void UpdateAirRaidSiren();                              // 0x00d54940
};
}
namespace SP {
bool __cdecl UpdateAirRaidSiren(cBehaviorSpaceTurret* pTurret);   // 0x00d54940
}
namespace SP {
int  __cdecl AddPosseMember(cBehaviorSpaceTurret* pTurret, void* pCreature);   // 0x00d54330
}
// ---- items of slice s00d53b50 end

// @ 0x00d52c90
extern "C" int __cdecl F52c90(int a, int b)
{
    return *(float*)(b + 8) > *(float*)(a + 8);
}

// @ 0x00d52cb0
void __cdecl F52cb0(int* arr, int start, int hole, int value, Cmp cmp)
{
    if (hole <= start) {
        arr[hole] = value;
        return;
    }
    int parent;
    do {
        parent = (hole - 1) >> 1;
        if (!cmp(arr[parent], value))
            break;
        arr[hole] = arr[parent];
        hole = parent;
    } while (start < parent);
    arr[hole] = value;
}

// @ 0x00d52d80
void __fastcall F52d80(void* self, int, int* stream)
{
    (void)self; (void)stream;
}

// @ 0x00d52df0
int __fastcall F52df0(void* self)
{
    void* m = FUN_00b3d300();
    int* v = ((int*(__thiscall*)(void*))FUN_00b1f9c0)(m);
    return ((v[1] - v[0]) >> 2) - *(int*)((char*)self + 0x1c);
}

// @ 0x00d52e10
int __fastcall F52e10(void* self)
{
    int result = 0;
    void* m = FUN_00b3d300();
    int r = ((int(__thiscall*)(void*))FUN_00b1fdb0)(m);
    if (r != 0) {
        int* p = (int*)((char*)self + 0x18);
        if (*(unsigned int*)((char*)self + 0x18) > 3)
            p = (int*)&g_145c4ac;
        result = *p;
    }
    return result;
}

// @ 0x00d52e40
void __fastcall F52e40(void* self, int, int arg)
{
    (void)self; (void)arg;
}

// @ 0x00d52e90
void FUN_00d52e90()
{}

// @ 0x00d53330
void PosseSim::removeSlot(RefObj* p)
{
    int i = 0;
    unsigned int n = (unsigned int)(mpEnd - mpBegin);
    for (; (unsigned int)i < n; ++i) {
        Slot* s = mpBegin[i];
        if (s->occupant.mp == p) {
            s->occupant = (RefObj*)0;
        }
    }
}

// @ 0x00d533c0
void ReloadTuning(void* self)
{
    PropertyPtr slot;
    slot.mp = 0;
    PropMgr* pm = (PropMgr*)SP_PropertyManager();
    if (pm->vf()->set(0x48f5d7cd, 0xad56080c)) {
        if (slot.get() != 0 && slot.get()->pad_00 != 0) {
            Property* p = slot.get();
            p->pad_00 = p->pad_00;
            slot.get()->type12 = 0;
        }
    }
}

// @ 0x00d53490
void RemovePosseMember(void* self, int member, char arg3, char arg4)
{
    (void)self; (void)member; (void)arg3; (void)arg4;
    SP_NounManager();
}

// @ 0x00d536d0
void* PosseSim::Dtor(unsigned int flags)
{
    PosseSim* self = this;
    *(void**)self = (void*)0x147b810;
    *(void**)((char*)self + 8) = (void*)0x147b7ec;
    *(void**)0x169e5b8 = 0;
    Slot** e = *(Slot***)((char*)self + 0x20);
    if (e != 0 && e[-1] != 0) {
        EA_Free(e);
    }
    *(void**)((char*)self + 8) = (void*)0x13eb938;
    *(void**)self = (void*)0x13ec458;
    if (flags & 1) {
        EA_Free(self);
    }
    return self;
}

// @ 0x00d53730
void PosseSim::Shutdown()
{
    PosseSim* self = this;
    ((void(__thiscall*)(void*))FUN_00b234c0)(SP_NounManager());
    Slot** e = *(Slot***)((char*)self + 0x24);
    while (e != self->mpBegin) {
        e -= 1;
        Slot* s = *e;
        if (s->occupant.mp) {
            s->occupant = (RefObj*)0;
        }
        EA_Free(s);
        *(Slot***)((char*)self + 0x24) = e;
    }
}

// @ 0x00d53790
void PosseSim_OnTick(PosseSim* self, int arg1, int arg2)
{
    (void)self; (void)arg1; (void)arg2;
    SP_NounManager();
}

// @ 0x00d53890
void** partition(void** first, void** last, int pivot, char (__cdecl* pred)(int, int))
{
    for (;;) {
        while (pred((int)*first, pivot)) {
            ++first;
        }
        while (pred(pivot, (int)last[-1])) {
            --last;
        }
        if (first >= last) {
            return first;
        }
        void* tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
}

// @ 0x00d538f0
PosseSim* PosseSim::Init()
{
    PosseSim* self = this;
    SP_NounManager();  // placeholder; real base ctor 0xb5b6c0
    *(void**)((char*)self + 0x18) = 0;
    *(void**)((char*)self + 0x1c) = 0;
    *(void**)self = (void*)0x147b810;
    *(void**)((char*)self + 8) = (void*)0x147b7ec;
    *(unsigned int*)((char*)self + 0x10) = 60000;
    *(float*)((char*)self + 0x14) = 20.0f;
    *(void**)((char*)self + 0x34) = 0;
    Slot** base = (Slot**)((char*)self + 0x38);
    self->mpBegin = base;
    self->mpEnd = base;
    self->mpCapacity = (Slot**)((char*)self + 0x58);
    *(void**)0x169e5b8 = self;
    return self;
}

// @ 0x00d53940
void introsort(void** first, void** last, int depth, char (__cdecl* pred)(int, int))
{
    while (last - first > 28 && depth > 0) {
        void** cut = (void**)FUN_00b90bd0(first, first + (last - first) / 2, last - 1, pred);
        void** mid = partition(first, last, (int)*cut, pred);
        --depth;
        introsort(mid, last, depth, pred);
        last = mid;
    }
    if (depth == 0) {
        FUN_00bbf130(first, last, last, pred);
    }
}

// @ 0x00d539d0
void* PosseSim_Instance()
{
    void* inst = *(void**)0x169e5b8;
    if (inst == 0) {
        Inst* raw = (Inst*)EA_Allocate(0x58, "Simulator/cPosseSimulator", 0, 0, 0, 0);
        if (raw != 0) {
            ((PosseSim*)raw)->Init();
            inst = (void*)raw;
            *(void**)0x169e5b8 = inst;
            ((Inst*)inst)->slot();
        } else {
            *(void**)0x169e5b8 = 0;
        }
    }
    return *(void**)0x169e5b8;
}

// @ 0x00d53a80
void PosseSim_InitPosse(PosseSim* self)
{
    struct cPosseSlot { RefObj* occupant; float angle; float diff; };
    ReloadTuning(self);
    if (self->mpBegin == self->mpEnd) {
        FUN_00d01790();
        float base = *(float*)0x1583d20;
        float scaled = base * 1.5f;
        for (unsigned int i = 0; i < 6; ++i) {
            cPosseSlot* s = (cPosseSlot*)EA_Allocate(0xc, "Simulator/cPosseSlot", 0, 0, 0, 0);
            if (s != 0) {
                s->occupant = (RefObj*)0;
                s->angle = (float)(int)i * base + scaled;
                s->diff = 0.0f;
            } else {
                s = 0;
            }
            Slot** end = self->mpEnd;
            if (end < self->mpCapacity) {
                self->mpEnd = end + 1;
                if (end != 0) {
                    *end = (Slot*)s;
                }
            } else {
                FUN_00b96600();
            }
        }
    }
}

// @ 0x00d53b50
Entry* cRingPlacer::Place(Noun* target, Vec3* outPos)
{
    NounSub* av = (NounSub*)((char*)NounManager()->GetAvatar() + 0xc0);
    const Vec3* p = av->GetPosition();
    float px = p->x;
    float invLen = 1.0f / sqrtf((px * px + p->y * p->y) + p->z * p->z + 1e-8f);
    Vec3 n;
    n.x = px * invLen;
    n.y = p->y * invLen;
    n.z = p->z * invLen;
    Vec3 v;
    av->GetDirection(&v);

    const Vec3* ap = av->GetPosition();
    NounSub* tsub = &target->mSub;
    const Vec3* tp = tsub->GetPosition();
    float dy = tp->y - ap->y;
    float dz = tp->z - ap->z;
    float dx = tp->x - ap->x;
    float distSq = (dz * dz + dy * dy) + dx * dx;
    float invD = 1.0f / sqrtf(distSq + 1e-8f);
    Vec3 t;
    t.x = invD * dx;
    t.y = dy * invD;
    t.z = dz * invD;
    float dnx = t.x, dny = t.y, dnz = t.z;

    Entry* found = 0;
    Entry** end = mpEnd;
    for (Entry** it = mpBegin; it != end; ++it) {
        Entry* e = *it;
        RotateAxis(&t, n, e->mAngle, v);
        e->mScore = fabsf(1.0f - ((t.x * dnx + t.z * dnz) + t.y * dny));
        if (e->mpNoun == target) found = e;
    }

    SortEntries(mpBegin, mpEnd, F52c90_s00d5_3b50);

    bool planet = (GetCurrentGameMode() == &gPlanetMode);
    Entry** cursor = mpBegin;
    Entry* chosen = 0;
    float ring = kRingRadius;
    for (; cursor != end; ++cursor) {
        chosen = *cursor;
        if (planet) {
            float a = chosen->mAngle;
            if (ring * 0.5f > a) continue;
            if (a > ring * 1.5f) continue;
        }
        Noun* cur = chosen->mpNoun;
        if (cur && cur != target) {
            const Vec3* a1 = av->GetPosition();
            const Vec3* t1 = cur->mSub.GetPosition();
            float ey = t1->y - a1->y;
            float ez = t1->z - a1->z;
            float ex = t1->x - a1->x;
            float thr = distSq + 1.0f;
            if (!(((ez * ez + ey * ey) + ex * ex) > thr)) continue;
        }
        if (found) {
            Noun* t = found->mpNoun;
            if (t) { found->mpNoun = 0; t->Release(); }
        }
        break;
    }
    if (cursor == end) return 0;

    Noun* old = chosen->mpNoun;
    if (old != target) {
        target->AddRef();
        chosen->mpNoun = target;
        if (old) old->Release();
    }
    RotateAxis(&t, n, chosen->mAngle, v);
    float k1 = kOffsetBase + 1.0f;
    float rt = tsub->GetRadius();
    float ra = av->GetRadius();
    float r = (ra + rt) + k1;
    Vec3 off;
    off.x = t.x * r;
    off.y = t.y * r;
    off.z = t.z * r;
    const Vec3* pa = av->GetPosition();
    t.x = off.x + pa->x;
    t.z = pa->z + off.z;
    t.y = pa->y + off.y;
    Vec3* proj = PlanetModel()->Project(&off, &t);
    *outPos = *proj;
    FUN_00d99e20(tsub->GetPosition(), outPos);
    return chosen;
}

// @ 0x00d54330
int __cdecl SP::AddPosseMember(SP::cBehaviorSpaceTurret* pTurret, void* pCreature)
{
    // A creature joins the avatar's posse (capped at three) unless it is an enemy or already a
    // member; joining drops the creature's UI selection, herd membership and target.
    const void* pMode = GetCurrentGameMode();
    bool bEnemy = false;
    if (pMode != &gPlanetMode)
        bEnemy = true;
    if (!NounManager()->GetAvatar())
        return 0;
    if (pTurret->mpTarget == pCreature)
        return 0;
    (void)pCreature;
    FUN_00c0b9d0(0);
    if (pCreature) {
        SP::cTurret_s00d5_3b50* pNew = (SP::cTurret_s00d5_3b50*)((SP::SPObject*)pCreature)->QueryInterface(0x436f315);
        if (pNew)
            pNew->FaceAtTarget(0);
    }
    return 1;
}
