// Slice s00bea930: Spore manager members (6 functions, VAs 0x00bea930 .. 0x00beb5c0).
// Every function is a __thiscall member of one manager class ("Sim"); ecx = this throughout.
// The class also owns an eastl::map<int,int> triple at +0x5a0 (used by sub_beaa30/sub_beb090)
// and an object at +0x120 whose vtable slot 0x2c/0x30 returns position / orientation.
//
// Only sub_bea930 is byte-exact; the rest are faithful behavioural reconstructions recorded in
// nonmatching.txt (register-allocation / x87-vs-SSE differences that are not source-controllable).
//
// flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <stdlib.h>

// ---------------------------------------------------------------- eastl rbtree / map<int,int>
struct rbNodeBase {
    void* mpNodeRight;                  // +0x00
    void* mpNodeLeft;                   // +0x04
    void* mpNodeParent;                 // +0x08
    char  mColor;                       // +0x0c
    char  pad[3];
};
struct IntTreeMap {                     // sizeof 0x1c
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];                // +0x18
    int* Find(const int* key, int* out);    // 0x00e5c780  (thiscall on the map)
    int& operator[](const int& k);          // 0x00643a40
    void DoNukeSubtree(void* pNode);        // 0x009a9600
    void reset() {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    void clear() { DoNukeSubtree(mAnchor.mpNodeParent); reset(); }
};

template <class T> const T& emin(const T& a, const T& b) { return a < b ? a : b; }

// ---------------------------------------------------------------- engine helpers
struct Clock { unsigned __int64 getTime(); };   // 0x00b316c0
extern void* __cdecl S_b3d380();                // 0x00b3d380

struct cSPTimer {                               // 0x20 bytes (embedded in Slot80 at +0x30/+0x50)
    char pad[0x20];
    bool             FUN_feba90();              // 0x00feba90
    unsigned __int64 FUN_bc3190();              // 0x00bc3190
    void             FUN_bc30f0();              // 0x00bc30f0
    void             FUN_bc3130();              // 0x00bc3130
};

struct Notifier { char pad0[0xa4]; void* p0xa4; void RemoveListener(void* o, int v); };
Notifier* GetNotifier();                        // 0x00b3d480

struct cCivModeStrategy { void PostFeedback(void*, unsigned, unsigned, void*, int, int, int); };
cCivModeStrategy* GetCivModeStrategy();         // 0x00cf74c0

class Veh;

struct GameVec {                                 // returned by cGameNounManager::GetGameDataVector
    int  pad0;                                  // +0x00
    Veh** begin;                                // +0x04
    Veh** end;                                  // +0x08
};

struct cGameNounManager {
    void* GetPlayerCivilization();              // 0x00b25fb0
    void* FUN00b25f40(int key);                 // 0x00b25f40
    GameVec* GetGameDataVector(void*, void*, void*, void*, void*);  // 0x00b21340
};
cGameNounManager* GetNounManager();             // 0x00b3d300
void* GetCurrentGameMode();                     // 0x00b5b800
extern char DAT_01654c04;                       // 0x01654c04
extern char DAT_0168c398;                       // 0x0168c398
extern int DAT_0169cbe0;                        // 0x0169cbe0
// 0x018c43e8 is a descriptor pointer the original pushes as a plain immediate (no relocation);
// it is not inside a data section of this image, so it is written as a literal below.

class Veh {
public:
    char  pad0[0x1d8];
    int   f1d8;                                 // +0x1d8
    int   f1dc;                                 // +0x1dc
    char  pad1[0x20c - 0x1e0];
    float f20c;                                 // +0x20c
    float f210;                                 // +0x210
    int   f214;                                 // +0x214
    char  pad2[0x762 - 0x218];
    char  f762;                                 // +0x762

    void sub_be9cb0(int, int, int, int);         // 0x00be9cb0
    unsigned int FUN_00bd85c0(float*, int*);    // 0x00bd85c0
    void FUN_00ca8120(int);                     // 0x00ca8120
};

struct Elem { int type; int _4; unsigned __int64 time; float f; int _14; int v; int _1c; };

// Per-vehicle slot in Sim::arr618 (stride 0x80).  Two 0x20-byte cSPTimer objects live
// at +0x30 and +0x50, and +0x70 holds a cVehicle-like pointer.
struct Slot80 {
    int      w[9];                              // +0x00 .. +0x20
    float    f24;                               // +0x24 q
    float    f28;                               // +0x28 l30
    float    f2c;                               // +0x2c 1 - (q + l30)
    cSPTimer t30;                               // +0x30
    cSPTimer t50;                               // +0x50
    int      obj70;                             // +0x70
    char     pad74[0xc];                        // +0x74
};

struct Matrix33T { int v[9]; };
Matrix33T& Matrix3FromQuaternion(Matrix33T& dst, const void* q);   // 0x0059c190

// Pick-event payload built for EffectsManagerPtr()->vt[0x2c]; layout from 0x00beaf00.
struct XformMsg {
    unsigned short flags;                       // +0x00
    short          count;                       // +0x02
    int            pos[3];                      // +0x04 (float triple, copied as dwords)
    int            unk10;                       // +0x10
    Matrix33T      mat;                         // +0x14
    void ctor();                                // 0x00434040
};

// Global helper object called through ecx = 0x0169c255 by 0x00beb1c0.
struct InteractCtx {
    void FUN_00cee8e0(float, int, float*);        // 0x00cee8e0
    void FUN_00cee920(void*, int, float, int, float*);  // 0x00cee920
    void FUN_00cee9c0(float, float, float*);      // 0x00cee9c0
    void FUN_00ceea20(float, float*, float*);     // 0x00ceea20
    void FUN_00ceedb0(float, int*);               // 0x00ceedb0
    void FUN_00ceea90(float, float*);             // 0x00ceea90
};

struct cPlanetModel {
    char  pad0[0x24];
    float FUN_00b7e4d0();                       // 0x00b7e4d0
};
cPlanetModel* __cdecl S_b3d350();               // 0x00b3d350 (SP::PlanetModel)

struct Noun590 {                                // object at Sim::p590
    char  pad0[0xc4];
    float f0c4;                                 // +0xc4
    float f0c8;                                 // +0xc8
    float f0cc;                                 // +0xcc
    void FUN_00bef890();                        // 0x00bef890
};

// free helpers (relocation-masked; declarations only)
void* FUN_0067ddd0();                           // 0x0067ddd0  EffectsManagerPtr

extern void FUN_00cd7d10();                     // 0x00cd7d10
extern void FUN_00d3d420();                     // 0x00d3d420
extern void FUN_00acdff0();                     // 0x00acdff0
extern void FUN_00b1e500();                     // 0x00b1e500

class Sim {
public:
    char       pad0[0x120];
    void*      vptr120;                         // +0x120
    char       pad1[0x590 - 0x124];
    void*      p590;                            // +0x590
    char       pad2[0x5a0 - 0x594];
    IntTreeMap map1;                            // +0x5a0
    IntTreeMap map2;                            // +0x5bc
    IntTreeMap map3;                            // +0x5d8
    char       pad3[0x618 - 0x5f4];
    char*      arr618;                          // +0x618
    char       pad4[0x62c - 0x61c];
    Veh**      vehBegin;                        // +0x62c
    Veh**      vehEnd;                          // +0x630
    char       pad5[0x64c - 0x634];
    int        f64c;                            // +0x64c
    char       pad6[0x750 - 0x650];
    float      f750;                            // +0x750
    int        f754;                            // +0x754
    float      f758;                            // +0x758
    int        i75c;                            // +0x75c
    char       pad7[0x770 - 0x760];
    cSPTimer   timer770;                        // +0x770
    char       padTimer770[0x88 - 0x20];        // +0x790 .. +0x7f8 (timer770 spans 0x88)
    uint8_t*   begin;                           // +0x7f8
    uint8_t*   end;                             // +0x7fc

    void FUN00bda0a0();                         // 0x00bda0a0
    void FUN00be9cb0(int, int, int, int);       // 0x00be9cb0
    void FUN00c00b00(int, int);                 // 0x00c00b00
    void sub_be92e0(int, int, int, int, int);   // 0x00be92e0
    void sub_bd9a00(void*);                     // 0x00bd9a00
    void sub_bea930();
    void sub_beaa30();
    void sub_beabb0();
    void sub_beb090(int id, int count);
    void sub_beb1c0(int idx, int p);
    void sub_beb5c0();
    void sub_bd9ed0(int);                       // 0x00bd9ed0
    void sub_be11f0();                          // 0x00be11f0
};

#define VGETID(p)     ((int(__thiscall*)(void*))((void**)*(void***)(p))[0x4c / 4])((void*)(p))
#define VCALL(p,slot) ((void**)*(void***)(p))[(slot) / 4]
#define V120M(p,slot) ((void*(__thiscall*)(void*))VCALL((char*)(p) + 0x120, slot))((void*)((char*)(p) + 0x120))

// ==================================================================== 0x00bea930
// @ 0x00bea930
void Sim::sub_bea930()
{
    unsigned __int64 now = ((Clock*)S_b3d380())->getTime();
    unsigned int i = 0;
    unsigned int off = 0;
    while (i < (unsigned int)((int)(this->end - this->begin) >> 5)) {
        Elem* e = (Elem*)(this->begin + off);
        if (e->time <= now) {
            if (e->type == 0x5f601f4) {
                float f = e->f;
                int v = e->v;
                if (f > 100.0f) {
                    this->i75c = -1;
                    this->f758 = 0.0f;
                    this->FUN00be9cb0(v, 2, 0, 0);
                } else {
                    this->i75c = v;
                    this->f758 = f;
                }
            }
            *(Elem*)(this->begin + off) = *(Elem*)(this->end - 32);
            this->end -= 32;
        } else {
            ++i;
            off += 32;
        }
    }
}

// ==================================================================== 0x00beaa30
// @ 0x00beaa30
void Sim::sub_beaa30()
{
    int key = this->f754;
    if (key == -1)
        return;
    if (key == VGETID(this->p590))
        return;
    if (this->f750 < 100.0f)
        return;
    if ((void*)GetCurrentGameMode() == (void*)&DAT_01654c04) {
        cGameNounManager* nm = GetNounManager();
        void* civ = nm->GetPlayerCivilization();
        if (civ == this->p590) {
            GetCivModeStrategy()->PostFeedback(this, 0x784a4055, 0x2bb7aff, V120M(this, 0x2c), 0, 1, 0);
        } else {
            void* r = GetNounManager()->FUN00b25f40(key);
            if (r == civ) {
                GetCivModeStrategy()->PostFeedback(this, 0x493b63b0, 0x2bb7aff, V120M(this, 0x2c), 0, 1, 0);
            } else if (*((char*)r + 0x8a) == 0) {
                this->sub_bd9a00(r);
            }
        }
    }
    this->map1.clear();
    this->map2.clear();
    this->map3.clear();
    this->map1[key] = this->f64c;
    this->sub_be92e0(key, 1, 0, 0, 0);
}

// ==================================================================== 0x00beabb0
// @ 0x00beabb0
// A short (<20 s) or long (>=20 s) periodic tick: the long branch iterates every noun and pokes the
// manager; the short branch sweeps the front cone and raises one "pick" event per vehicle found.
void Sim::sub_beabb0()
{
    if (!this->timer770.FUN_feba90())
        return;

    unsigned __int64 ticks = this->timer770.FUN_bc3190();
    float secs = ticks * 0.001f;

    if (secs < 20.0f) {
        float ang = secs * 0.05f * 1.5707964f;
        float* fwd = (float*)V120M(this, 0x2c);
        float fx = fwd[0], fy = fwd[1], fz = fwd[2];
        float inv = (float)(1.0 / sqrt((double)(fx * fx + fy * fy + fz * fz + 1e-8f)));
        float nx = -(fx * inv), ny = -(fy * inv), nz = -(fz * inv);
        cPlanetModel* pm = S_b3d350();
        float s = (float)((1.0 - cos(ang)) * pm->FUN_00b7e4d0()) * 2.1f;
        float ox = nx * s, oy = ny * s, oz = nz * s;
        float* pos = (float*)V120M(this, 0x2c);
        float px = ox + pos[0], py = oy + pos[1], pz = oz + pos[2];

        GameVec* vec = GetNounManager()->GetGameDataVector(
            (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
            (void*)FUN_00b1e500, (void*)0x018c43e8);
        int cnt = (int)(vec->end - vec->begin);
        int me = VGETID(this);
        float negnx = -nx, negny = -ny, negnz = -nz;
        for (int i = 0; i < cnt; ++i) {
            Veh* v = vec->begin[i];
            if (VGETID(v) != me) {
                float* q = (float*)V120M(v, 0x2c);
                float dx = q[0] - px, dz = q[2] - pz, dy = q[1] - py;
                float d = (float)(1.0 / sqrt((double)(dx * dx + dz * dz + dy * dy + 1e-8f)));
                if (0.0f < d * dx * negnx + dz * d * negnz + dy * d * negny) {
                    v->f762 = 1;
                    void* listener = 0;
                    void* fxmgr = FUN_0067ddd0();
                    char ok = ((char(__thiscall*)(void*, unsigned, int, void**))VCALL(fxmgr, 0x2c))
                                  (fxmgr, 0xbbc37988, 0, &listener);
                    if (ok) {
                        XformMsg ev;
                        ev.ctor();
                        float* q2 = (float*)V120M(v, 0x2c);
                        ((int*)ev.pos)[0] = ((int*)q2)[0];
                        ((int*)ev.pos)[1] = ((int*)q2)[1];
                        ((int*)ev.pos)[2] = ((int*)q2)[2];
                        ev.flags |= 4;
                        ev.count += 1;
                        Matrix33T m;
                        Matrix3FromQuaternion(m, (const void*)V120M(v, 0x30));
                        ev.mat = m;
                        ev.flags |= 2;
                        ev.count += 1;
                        ((void(__thiscall*)(void*, XformMsg*))VCALL(listener, 0x18))
                            (listener, &ev);
                        Noun590* pl = (Noun590*)this->p590;
                        float snap[3];
                        snap[0] = pl->f0c4;
                        snap[1] = pl->f0c8;
                        snap[2] = pl->f0cc;
                        ((void(__thiscall*)(void*, int, float*, int))VCALL(listener, 0x44))
                            (listener, 5, snap, 3);
                        ((void(__thiscall*)(void*, int))VCALL(listener, 8))(listener, 0);
                    }
                    v->sub_be9cb0(me, 1, 0, 0);
                    if (listener)
                        ((void(__thiscall*)(void*))VCALL(listener, 4))(listener);
                }
            }
        }
        return;
    }

    this->FUN00bda0a0();
    GameVec* vec = GetNounManager()->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
        (void*)FUN_00b1e500, (void*)0x018c43e8);
    int cnt = (int)(vec->end - vec->begin);
    int me = VGETID(this);
    for (int i = 0; i < cnt; ++i) {
        Veh* v = vec->begin[i];
        if (VGETID(v) != me)
            v->sub_be9cb0(me, 1, 0, 0);
    }
}

// ==================================================================== 0x00beb090
// @ 0x00beb090
void Sim::sub_beb090(int id, int count)
{
    if (count <= 0)
        return;
    if (id == VGETID(this))
        return;
    if (this->f754 == -1)
        this->f754 = id;
    if (this->f754 != id) {
        int key = VGETID(this->p590);
        int v = emin(this->map1[this->f754], count);
        this->map1[this->f754] -= v;
        this->map3[this->f754] += v;
        this->map1[key] += v;
        count -= v;
        if (count > 0)
            this->f754 = id;
        if (this->f754 != id)
            goto L;
    }
    {
        int key = VGETID(this->p590);
        int v = emin(this->map1[key], count);
        this->map2[id] += v;
        this->map1[id] += v;
        key = VGETID(this->p590);
        this->map1[key] -= v;
    }
L:
    GetNotifier()->RemoveListener(this, 0);
    this->sub_beaa30();
}

// ==================================================================== 0x00beb1c0
// @ 0x00beb1c0
void Sim::sub_beb1c0(int idx, int p)
{
    Veh*    veh = this->vehBegin[idx];
    int     u   = veh->f1dc;
    Slot80* sl  = (Slot80*)(this->arr618 + idx * 0x80);

    ((Noun590*)this->p590)->FUN_00bef890();
    this->FUN00c00b00(1, u);

    int   slot;
    int   n     = 0;
    int*  it    = this->map1.Find(&slot, &u);
    if (*it != (int)((char*)this + 0x5a4))
        n = this->map1[u];

    float g = 0.0f;
    int   h = 0;
    veh->FUN_00bd85c0(&g, &h);
    float A = 0.0f;
    ((InteractCtx*)0x0169c255)->FUN_00cee8e0(g, h, &A);
    float B = 0.0f;
    ((InteractCtx*)0x0169c255)->FUN_00cee920(this, n, A, p, &B);

    int span = sl->w[0] - sl->w[2];
    int fi   = 0;
    if (0 < span) {
        float frac = 0.0f;
        ((InteractCtx*)0x0169c255)->FUN_00cee9c0(B, A, &frac);
        frac = __max(frac, 0.0f);
        frac = __min(frac, 1.0f);
        fi = (int)((float)this->f64c * frac * 0.25f);
        if (span < fi) fi = span;
    }

    float l30 = 0.0f;
    float q   = 0.0f;
    ((InteractCtx*)0x0169c255)->FUN_00ceea20(B, &q, &l30);
    q = __max(q, 0.0f);
    q = __min(q, 1.0f);
    l30 = __max(l30, 0.0f);
    l30 = __min(l30, 1.0f);
    if (1.0f < q + l30) { l30 *= 0.5f; q *= 0.5f; }
    sl->f24 = q;
    sl->f28 = l30;
    sl->f2c = 1.0f - (q + l30);
    veh->f20c = l30;
    veh->f210 = q;

    int l2c = 0;
    if (!sl->t30.FUN_feba90()) {
        sl->t30.FUN_bc30f0();
    } else {
        unsigned __int64 t = sl->t30.FUN_bc3190();
        if ((int)(t >> 32) != 0 || 1000 < (unsigned int)t) {
            ((InteractCtx*)0x0169c255)->FUN_00ceedb0(B, &l2c);
            sl->t30.FUN_bc3130();
        }
    }

    int extra = (l2c - sl->w[2]) - fi;
    if (0 < extra) l2c -= extra;
    int flag = 0;
    if (sl->w[3] == 0) {
        if (l2c < 1) goto L;
        sl->t50.FUN_bc3130();
    } else {
        unsigned __int64 t2 = sl->t50.FUN_bc3190();
        if (t2 <= (unsigned __int64)(long long)DAT_0169cbe0) goto L;
        flag = 1;
        sl->t50.FUN_bc3130();
    }
L:
    sl->w[6]   = fi;
    sl->w[7]   = l2c;
    sl->w[3]  += l2c - flag;
    sl->w[2]  += fi - l2c;
    sl->w[4]   = l2c;
    sl->w[5]   = flag;
    if (0 < l2c)
        this->sub_beb090(u, l2c);

    if (sl->obj70 != 0) {
        float pf = 0.0f;
        ((InteractCtx*)0x0169c255)->FUN_00ceea90(B, &pf);
        Veh* obj = 0;
        if (sl->obj70 != 0)
            obj = (Veh*)((void*(__thiscall*)(void*, int))VCALL((void*)sl->obj70, 0xb8))
                      ((void*)sl->obj70, 0x137e8e0);
        if (0.0f < pf) {
            void* inner = (void*)((char*)obj + 0x508);
            void* r = ((void*(__thiscall*)(void*, int, void*, int))VCALL(this->p590, 0x4c))
                          (this->p590, 1, &DAT_0168c398, 0);
            ((void(__thiscall*)(void*, float, void*))VCALL(inner, 0x18))(inner, pf, r);
        }
        obj->FUN_00ca8120(0);
    }
}

// ==================================================================== 0x00beb5c0
// @ 0x00beb5c0
void Sim::sub_beb5c0()
{
    int n = (int)((char*)this->vehEnd - (char*)this->vehBegin) >> 2;
    int count = 0;
    bool any = false;
    for (unsigned j = 0; j < (unsigned)n; ++j)
        count += (this->vehBegin[j]->f1d8 == 2);
    for (unsigned j = 0; j < (unsigned)n; ++j) {
        this->vehBegin[j]->f214 = (int)(this->vehBegin[j]->f214 * 0.8f);
        if (this->vehBegin[j]->f1d8 == 2) {
            this->sub_beb1c0(j, count);
            any = true;
        } else {
            this->sub_bd9ed0(j);
        }
    }
    if (!any)
        this->sub_be11f0();
}
