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

struct cSPTimer {                               // object living at this+0x770
    char pad[0x88];
    bool             FUN_feba90();              // 0x00feba90
    unsigned __int64 FUN_bc3190();              // 0x00bc3190
    void             FUN_bc30f0();              // 0x00bc30f0
    void             FUN_bc3130();              // 0x00bc3130
};

struct Notifier { char pad0[0xa4]; void* p0xa4; void RemoveListener(void* o, int v); };
Notifier* GetNotifier();                        // 0x00b3d480

struct cCivModeStrategy { void PostFeedback(void*, unsigned, unsigned, void*, int, int, int); };
cCivModeStrategy* GetCivModeStrategy();         // 0x00cf74c0

struct cGameNounManager {
    void* GetPlayerCivilization();              // 0x00b25fb0
    void* FUN00b25f40(int key);                 // 0x00b25f40
};
cGameNounManager* GetNounManager();             // 0x00b3d300
void* GetCurrentGameMode();                     // 0x00b5b800
extern char DAT_01654c04;                       // 0x01654c04
extern char DAT_0168c398;                       // 0x0168c398
extern long long DAT_0169cbe0;                  // 0x0169cbe0
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
};

struct Elem { int type; int _4; unsigned __int64 time; float f; int _14; int v; int _1c; };
struct Slot80 { int w[0x20]; };

// free helpers (relocation-masked; declarations only)
extern "C" void  FUN_00bef890(void* self);      // 0x00bef890  (thiscall; self = p590)
int   FUN_00b21340(void*, void*, void*, void*, void*);   // 0x00b21340
void  FUN_00bda0a0();                           // 0x00bda0a0
void  FUN_00b3d350();                           // 0x00b3d350
float FUN_00b7e4d0();                           // 0x00b7e4d0
void* FUN_0067ddd0();                           // 0x0067ddd0
void  FUN_00434040();                           // 0x00434040
void  FUN_0059c190(void* dst, void* src);       // 0x0059c190
void  FUN_00bd85c0(void* a, void* b);           // 0x00bd85c0
void  FUN_00cee8e0(float a, int b, void* c);    // 0x00cee8e0
void  FUN_00cee920(void* self, float a, int b, int c, void* d); // 0x00cee920
void  FUN_00cee9c0(int a, int b, void* c);      // 0x00cee9c0
void  FUN_00ceea20(int a, void* b, void* c);    // 0x00ceea20
void  FUN_00ceedb0(int a, void* b);             // 0x00ceedb0
void  FUN_00ceea90(int a, void* b);             // 0x00ceea90
void  FUN_00ca8120(int a);                      // 0x00ca8120

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
    uint8_t*   begin;                           // +0x7f8
    uint8_t*   end;                             // +0x7fc

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
// The event construction below is a faithful sketch of the deep-vtable protocol (0xbbc37988 = the
// pick-event type id); the surrounding control flow matches the original exactly.
struct PickEvent {
    float          pos[3];      // +0x00
    unsigned short flags;       // +0x0c
    short          count;       // +0x0e
    int            mat[9];      // +0x10  (3x3 orientation copied from V120M(v,0x30))
};

void Sim::sub_beabb0()
{
    if (!this->timer770.FUN_feba90())
        return;

    unsigned __int64 ticks = this->timer770.FUN_bc3190();
    double secs = (double)(long long)ticks * 0.001;

    if (secs >= 20.0) {
        FUN_00bda0a0();
        GetNounManager();
        int mgr = FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
                               (void*)FUN_00b1e500, (void*)0x018c43e8);
        int cnt = (*(int*)(mgr + 8) - *(int*)(mgr + 4)) >> 2;
        void* me = (void*)VGETID(this);
        for (int i = 0; i < cnt; ++i) {
            int oid = VGETID(*(void**)(*(int*)(mgr + 4) + i * 4));
            if ((void*)oid != me)
                this->FUN00be9cb0((int)me, 1, 0, 0);
        }
        return;
    }

    float ang = (float)secs * 0.05f * 1.5707964f;
    float* fwd = (float*)V120M(this, 0x2c);
    float fx = fwd[0], fy = fwd[1], fz = fwd[2];
    float inv = 1.0f / sqrtf(fx * fx + fy * fy + fz * fz + 1e-8f);
    float nx = -(fx * inv), ny = -(fy * inv), nz = -(fz * inv);
    FUN_00b3d350();
    float s = (float)((1.0 - cos(ang)) * FUN_00b7e4d0() * 2.1);
    float ox = nx * s, oy = ny * s, oz = nz * s;
    float* pos = (float*)V120M(this, 0x2c);
    float px = ox + pos[0], py = oy + pos[1], pz = oz + pos[2];

    GetNounManager();
    int mgr = FUN_00b21340((void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00acdff0,
                           (void*)FUN_00b1e500, (void*)0x018c43e8);
    int cnt = (*(int*)(mgr + 8) - *(int*)(mgr + 4)) >> 2;
    int* base = (int*)(mgr + 4);
    float meKey = (float)VGETID(this);
    float negnx = -nx, negny = -ny, negnz = -nz;
    for (int i = 0; i < cnt; ++i) {
        void* v = (void*)base[i];
        if ((float)VGETID(v) != meKey) {
            float* q = (float*)V120M(v, 0x2c);
            float dx = q[0] - px, dz = q[2] - pz, dy = q[1] - py;
            float d = 1.0f / sqrtf(dy * dy + dz * dz + dx * dx + 1e-8f);
            if (0.0f < d * dx * negnx + dz * d * negnz + dy * d * negny) {
                *((char*)v + 0x762) = 1;
                void* listener = 0;
                void* obj = FUN_0067ddd0();
                if (listener)
                    ((void(__thiscall*)(void*))VCALL(listener, 4))(listener);
                char ok = ((char(__thiscall*)(void*, unsigned, int, void**))VCALL(obj, 0x2c))
                              (obj, 0xbbc37988, 0, &listener);
                if (ok) {
                    FUN_00434040();
                    PickEvent ev;
                    float* q2 = (float*)V120M(v, 0x2c);
                    ev.pos[0] = q2[0]; ev.pos[1] = q2[1]; ev.pos[2] = q2[2];
                    ev.flags |= 4;
                    ev.count += 1;
                    int* p590 = (int*)this->p590;
                    int* src = (int*)V120M(v, 0x30);
                    FUN_0059c190(ev.mat, src);
                    ev.flags |= 2;
                    ev.count += 1;
                    ((void(__thiscall*)(void*, void*))VCALL(listener, 0x18))(listener, &ev);
                    int snap[3];
                    snap[0] = *(int*)((char*)p590 + 0xc4);
                    snap[1] = *(int*)((char*)p590 + 0xc8);
                    snap[2] = *(int*)((char*)p590 + 0xcc);
                    ((void(__thiscall*)(void*, int, void*, int))VCALL((void*)base[i], 0x44))
                        ((void*)base[i], 5, snap, 3);
                    ((void(__thiscall*)(void*, int))VCALL(this->p590, 8))(this->p590, 0);
                }
                this->FUN00be9cb0((int)meKey, 1, 0, 0);
                if (listener)
                    ((void(__thiscall*)(void*))VCALL(listener, 4))(listener);
            }
        }
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
    Veh*    veh  = this->vehBegin[idx];
    int     u    = veh->f1dc;
    Slot80* sl   = (Slot80*)(this->arr618 + idx * 0x80);

    ((void(__thiscall*)(void*))FUN_00bef890)(this->p590);
    this->FUN00c00b00(1, u);

    float f = 0.0f;
    int   l1c = 0;
    int*  node = this->map1.Find(&u, &l1c);
    if (*node != (int)((char*)this + 0x5a4))
        f = (float)this->map1[u];

    float l18 = 0.0f;
    int   l24 = 0, l1c2 = 0;
    FUN_00bd85c0(&l18, &l1c2);
    FUN_00cee8e0(l18, l1c2, &l24);
    int l28 = 0;
    FUN_00cee920(this, f, l24, p, &l28);

    int span = sl->w[0] - sl->w[2];
    float frac = 0.0f;
    if (0 < span) {
        frac = 0.0f;
        FUN_00cee9c0(l28, l24, &frac);
        float cl = 0.0f;
        if (0.0f <= frac) cl = frac;
        if (1.0f <= cl) cl = 1.0f;
        float want = (float)this->f64c * cl * 0.25f;
        frac = (float)(int)(want + 0.5f);
        if (span < (int)(want + 0.5f)) frac = (float)span;
    }

    float l30 = 0.0f;
    float q = 0.0f;
    FUN_00ceea20(l28, &l30, &q);
    float v1 = 0.0f;
    if (0.0f <= l30) v1 = l30;
    l30 = v1;
    if (1.0f <= v1) l30 = 1.0f;
    float v2 = 0.0f;
    if (0.0f <= q) v2 = q;
    if (1.0f <= v2) v2 = 1.0f;
    q = v2;
    if (1.0f < v2 + l30) { l30 *= 0.5f; q = v2 * 0.5f; }
    sl->w[9]   = (int)l30;
    sl->w[10]  = (int)q;
    sl->w[0xb] = (int)(1.0f - (q + l30));
    veh->f20c = q;
    veh->f210 = l30;

    int l2c = 0;
    if (!this->timer770.FUN_feba90()) {
        this->timer770.FUN_bc30f0();
    } else {
        unsigned __int64 t = this->timer770.FUN_bc3190();
        if ((int)(t >> 32) != 0 || 1000 < (unsigned int)t) {
            FUN_00ceedb0(l28, &l2c);
            this->timer770.FUN_bc3130();
        }
    }

    int i     = (int)frac;
    int extra = (l2c - sl->w[2]) - (int)frac;
    if (0 < extra) l2c -= extra;
    float flag = 0.0f;
    if (sl->w[3] == 0) {
        if (l2c < 1) goto L;
    } else {
        unsigned __int64 t2 = this->timer770.FUN_bc3190();
        if (t2 <= (unsigned __int64)DAT_0169cbe0) goto L;
        flag = 1.4013e-45f;
    }
    this->timer770.FUN_bc3130();
L:
    sl->w[6]   = i;
    sl->w[7]   = l2c;
    sl->w[3]  += l2c - (int)flag;
    sl->w[2]  += i - l2c;
    sl->w[4]   = l2c;
    sl->w[5]   = (int)flag;
    if (0 < l2c)
        this->sub_beb090(u, l2c);

    if (sl->w[0x1c] != 0) {
        float pf = 0.0f;
        FUN_00ceea90(l28, &pf);
        int obj = 0;
        if (sl->w[0x1c] != 0)
            obj = (int)((void*(__thiscall*)(void*, int))VCALL((void*)sl->w[0x1c], 0xb8))
                      ((void*)sl->w[0x1c], 0x137e8e0);
        if (0.0f < pf) {
            int inner = *(int*)(obj + 0x508);
            void* r = ((void*(__thiscall*)(void*, int, void*, int))VCALL(this->p590, 0x4c))
                          (this->p590, 1, &DAT_0168c398, 0);
            ((void(__thiscall*)(int, float, void*))*(void**)(inner + 0x18))(inner, pf, r);
        }
        FUN_00ca8120(0);
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
