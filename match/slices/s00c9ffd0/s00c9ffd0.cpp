// Slice s00c9ffd0 -- cPathLocomotion/cVehicle/SP path-solver object cluster
// (0x00c9ffd0..0x00ca1210, 24 functions in this batch).
//
// The object at +0x34 is a Property/Transform-ish subobject addressing 3 floats
// with vtable slots 0x2c (position getter), 0x30 (rotation getter), 0x40
// (steer/set float), 0x5c (offset/tangent getter).  +0xb1c mLocomotion mode,
// +0xd00 mpAnimatingCreature, +0xd94 mpEA (list), +0xbc0 mpArray.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <math.h>

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned long long uint64_t;

// ---------------------------------------------------------------------------
// function-pointer types for vtable slots
typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVV)(void*, void*);
typedef void  (__thiscall* TFnVF)(void*, float);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef int   (__thiscall* TFnIII)(void*, int, int);
typedef int   (__thiscall* TFnIU)(void*, unsigned);
typedef void* (__thiscall* TFnP)(void*);
typedef void* (__thiscall* TFnPI)(void*, int);
typedef int   (__thiscall* TFnIP)(void*, void*);
typedef float*(__thiscall* TFnPF)(void*);
typedef float (__thiscall* TFnF)(void*);
typedef char  (__thiscall* TFnPUUP)(void*, unsigned, unsigned, void**);
typedef bool  (__thiscall* TFnPK)(void*, int);
typedef char  (__thiscall* TFnCK)(void*);
typedef uint64_t (__thiscall* TFnTime)(void*);
typedef void* (__thiscall* TFnPVVW)(void*, void*, void*, const wchar_t*);
typedef void  (__thiscall* TSetAttach)(void*, int);          // 0x00a04af0
typedef void  (__thiscall* TCreatureRelease)(void*);         // 0x00a05270
typedef void  (__thiscall* TProcessEntry)(void*, void*, void*, const wchar_t*); // 0x00695b40
typedef void  (__thiscall* TFnVPP)(void*, float*, float*);   // 0x00c9ff40

#define VTFN(p, slot)  ((*(void***)(p))[slot])

// Misc `__thiscall`-style helpers reached by absolute address.  Expressing them
// as members of a dummy class makes MSVC put the object in ECX, push the
// remaining args, and emit a direct relative call (relocation-masked).
struct IDummy {
    void __thiscall SetAttach(int);      // 0x00a04af0
    void __thiscall Rel();               // 0x00a05270
};

extern "C" {
    void  __stdcall FUN_00c9ff40(float, float*, float*);     // 0x00c9ff40
    void* __cdecl FUN_00eed0b0(void*, float*, float*);       // 0x00eed0b0 PropertyPairRead
    void* __cdecl SP_GetCurrentGameMode();                   // 0x00b5b800
    void* __cdecl SP_PlanetModel();                          // 0x00b3d350
    int   __cdecl SP_GetAverageRadius(void*, const void*);   // 0x00b7e840
    void* __cdecl SP_LayerManager();                         // 0x0067cb20
    void* __cdecl SP_PropertyManager();                      // 0x0067de30
    bool  __cdecl SP_GetPropertyAsVector3(void*, uint32_t, void*); // 0x006a1110
    void  __fastcall FUN_00695b40(void*, void*, void*, const wchar_t*);// 0x00695b40
    void* __cdecl FUN_00c6f660(void*);                       // 0x00c6f660
    bool  __cdecl FUN_00c9f490(void*, void*);                // 0x00c9f490 (ret 8)
    void  __cdecl FUN_00b452f0(void*);                       // 0x00b452f0
    void  __cdecl FUN_00b4c600(void*, void*, float);         // 0x00b4c600
    void  __fastcall FUN_00a04af0(void*, int);               // 0x00a04af0 SetAttachments
    void  __fastcall FUN_00a05270(void*);                    // 0x00a05270 Release
    char  __fastcall FUN_00feba90(void*);                    // 0x00feba90 IsRunning
    uint64_t __fastcall FUN_00bc3190(void*);                 // 0x00bc3190 GetElapsedTime
    void* __cdecl FUN_00b3d310(void*, const void*, void*);   // 0x00b3d310
}

extern float g_0169a280;     // 2pi (runtime init)
extern float g_0169a288;     // quarter-sine scale
extern float g_0169a284;     // quarter step
extern float g_0157c908;     // cached vector (init -1.0f)
extern float g_0157c914;     // cached vector (init -1.0f)
extern const float g_13eb1bc;   // -1.0f
extern const float g_14749b0;   // 12582912.0f
extern const float g_1471064;   // 0.5f
extern const float g_1470f1c;   // 2.0f
extern const float g_157d284;   // 8.0f
extern const float g_140e87c;   // 0.6666667f
extern const float g_1485720;   // 1.0f
extern const float g_1477fbc;   // 200.0f
extern const float g_13ec4b8;   // 1e-08f
extern float g_01677840[];      // 16-entry (float,float) quarter-sine table

static void* g_01654c10 = (void*)0x01654c10;   // game-mode sentinel
static void* g_01186577 = (void*)0x01186577;

// ---------------------------------------------------------------------------
// vtable-call helpers
#define REF_CALL(p, slot)  do { void* _p = (p); \
    if (_p) (*(TFnV)VTFN(_p, slot))(_p); } while(0)
// io-interface refcount: slots 0x60/4==0x18 (AddRef), 0x64/4==0x19 (Release)
#define IOREF_ADDREF(p)  REF_CALL(p, 0x18)
#define IOREF_RELEASE(p) REF_CALL(p, 0x19)
#define REF_RELEASE(p)  REF_CALL(p, 1)
#define REF_ADDREF(p)   REF_CALL(p, 0)
#define REF_ADDREF2(p)  REF_CALL(p, 1)
#define REF_RELEASE2(p) REF_CALL(p, 2)

struct cSPVector3 { float x, y, z; };

// Subobject based at +0x34.
struct Sub34 { virtual void s0(); };

// The big object.  Retained as a char blob + accessors for clarity.
struct Obj {
    char  pad00[0x34];
    void* vptr34;         // +0x34 subobject vptr
    char  pad38[0xc4 - 0x38];
    char  propC4[0x20];   // +0xc4 (PropertyPairRead source)
    char  pade4[0xb1c - 0xe4];
    int   mLocomotion;    // +0xb1c
    char  padb20[0xbc0 - 0xb20];
    void* mpArray;        // +0xbc0
    char  padbc4[0xd00 - 0xbc4];
    void* mpCreature;     // +0xd00 (cAnimatingCreature)
    char  padd04[0xd64 - 0xd04];
    int   f_d64, f_d68;   // +0xd64, +0xd68
    int   f_d6c, f_d70;   // +0xd6c, +0xd70
    int   f_d74, f_d78;   // +0xd74, +0xd78
    int   f_d7c, f_d80;   // +0xd7c, +0xd80
    int   f_d84, f_d88;   // +0xd84, +0xd88
    float f_d8c;          // +0xd8c
    float f_d90;          // +0xd90
    void* mpEA;           // +0xd94

    // ---- methods (in original address order) ----
    int   __thiscall GetAltTarget();
    bool  __thiscall BringGoalToAltitude(float* target);
    int   __thiscall GetArrayCount();
    int   __thiscall CreateInteract(int key);
    void  __thiscall ClearCreature();
    void  __thiscall ProcessEA();
    int   __thiscall TimerExpired();
};

// Small POD-block helpers (assignment operators), wrapped so they can be
// __thiscall members.
struct RefOps {
    void* __thiscall CopyCtor(void* src);      // 0x00ca0900
    void* __thiscall AssignA(void* src);       // 0x00ca0940
    void* __thiscall AssignB(void* src);       // 0x00ca09a0
};

// ---------------------------------------------------------------------------
// @ 0x00c9ffd0
float __fastcall FUN_00c9ffd0(float param_1)
{
    float local_4;
    FUN_00c9ff40(param_1, &param_1, &local_4);
    return param_1;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0040
int __thiscall Obj::GetAltTarget()
{
    Obj* o = this;
    if (o->f_d6c == 0 && o->f_d70 == 0) return o->f_d64;

    float a, b;
    FUN_00eed0b0(o->propC4, &a, &b);

    float dt = (*(TFnF)VTFN(&o->vptr34, 0x34 / 4))(&o->vptr34);

    float ratio = dt / (b - a);
    int iVar2 = o->f_d6c;
    if (iVar2 != 0 && ratio < o->f_d8c) {
        switch (o->mLocomotion) {
        case 0: if (o->f_d74) return o->f_d74; return iVar2;
        case 1: if (o->f_d7c) return o->f_d7c; return iVar2;
        case 2: if (o->f_d84) return o->f_d84; return iVar2;
        default: return iVar2;
        }
    }
    iVar2 = o->f_d70;
    if (iVar2 != 0 && o->f_d90 <= ratio && ratio != o->f_d90) {
        switch (o->mLocomotion) {
        case 0: if (o->f_d78) return o->f_d78; return iVar2;
        case 1: if (o->f_d80) return o->f_d80; return iVar2;
        case 2: if (o->f_d78 != 2) return o->f_d80; return iVar2;
        default: return iVar2;
        }
    }
    return o->f_d64;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0170
bool __thiscall Obj::BringGoalToAltitude(float* target)
{
    Obj* o = this;
    if (o->mLocomotion == 2 && SP_GetCurrentGameMode() == g_01654c10) return false;

    SP_PlanetModel();
    float* pos = (*(TFnPF)VTFN(&o->vptr34, 0x2c / 4))(&o->vptr34);

    float dx = target[0] - pos[0];
    float dy = target[1] - pos[1];
    float dz = target[2] - pos[2];
    float dist = sqrtf((dz * dz + dy * dy) + dx * dx);
    if (dist > g_1477fbc) return true;

    float inv = g_1485720 / dist;
    float sx = inv * dx;
    float sy = dy * inv;
    float sz = dz * inv;

    pos = (*(TFnPF)VTFN(&o->vptr34, 0x2c / 4))(&o->vptr34);
    float px = pos[0] + sx;
    float py = pos[1] + sy;
    float pz = pos[2] + sz;

    int n = (int)(dist * g_140e87c);
    for (int i = 0; i < n; i++) {
        int mode = o->mLocomotion;
        void* pm = SP_PlanetModel();
        bool hit;
        if (mode == 0) {
            hit = (SP_GetAverageRadius(pm, &px) & 0x98000000) == 0;
        } else if (mode == 1) {
            hit = (SP_GetAverageRadius(pm, &px) & 0x58000000) == 0;
        } else {
            hit = (~(unsigned)SP_GetAverageRadius(pm, &px) >> 5) & 1;
        }
        if (hit) return true;
        px = px + sx;
        py = py + sy;
        pz = pz + sz;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0340
int __thiscall Obj::TimerExpired()
{
    unsigned* self = (unsigned*)this;
    int* timer = (int*)((char*)self + 0x7d0);
    if (FUN_00feba90(timer)) {
        uint64_t t = FUN_00bc3190(timer);
        if (t < (uint64_t)self[0x7f0 / 4]) return 0xacf33281;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0380
int __thiscall Obj::GetArrayCount()
{
    void* a = this->mpArray;
    if (a) return (*(int*)((char*)a + 0x54) - *(int*)((char*)a + 0x50)) >> 2;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00ca03a0
int __thiscall Obj::CreateInteract(int key)
{
    int result = 0;
    if (this->mpCreature != 0) {
        void* lm = SP_LayerManager();
        if ((*(TFnPK)VTFN(lm, 0x40 / 4))(lm, key)) {
            result = (*(TFnIII)VTFN(this->mpCreature, 2))(this->mpCreature, key, 0);
            (*(TFnVII)VTFN(this->mpCreature, 3))(this->mpCreature, result, 1);
            (*(TFnVI)VTFN(this->mpCreature, 6))(this->mpCreature, result);
            (*(TFnVII)VTFN(this->mpCreature, 0x10))(this->mpCreature, result, key);
            (*(TFnVII)VTFN(this->mpCreature, 0xf))(this->mpCreature, result, 0);
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0430
void __thiscall Obj::ClearCreature()
{
    if (this->mpCreature == 0) return;
    void* p = (*(TFnP)VTFN(this->mpCreature, 0x1c))(this->mpCreature);
    if (!p) return;

    ((IDummy*)this->mpCreature)->SetAttach(0);
    void* q = (*(TFnP)VTFN(this->mpCreature, 0x1c))(this->mpCreature);
    (*(TFnVV)VTFN(q, 0xf))(q, this->mpCreature);

    if (this->mpCreature) {
        void* old = this->mpCreature;
        this->mpCreature = 0;
        ((IDummy*)old)->Rel();
    }

    (*(TFnVF)VTFN(&this->vptr34, 0x40 / 4))(&this->vptr34, 1.0f);
}

// ---------------------------------------------------------------------------
// @ 0x00ca04a0
void __thiscall Obj::ProcessEA()
{
    if (this->mpEA == 0) return;

    for (;;) {
        void* ea = this->mpEA;
        int idx = (*(TFnIII)VTFN(ea, 0x6c / 4))(ea, 8, 0);
        if (idx == -1) break;
        void* e = (*(TFnPI)VTFN(ea, 0x60 / 4))(ea, idx);
        if (!e) continue;

        void* pi = (void*)(*(TFnIU)VTFN((char*)e + 0xc, 3))((char*)e + 0xc, 0x73905ae);
        if (!pi) continue;

        REF_ADDREF(pi);
        (*(TFnVV)VTFN(this->mpEA, 0x78 / 4))(this->mpEA, pi);

        void* v = FUN_00c6f660(this);
        if (v) {
            void* r = (void*)(*(TFnIU)VTFN(v, 3))(v, 0x1186577);
            if (r) {
                void* s34 = &this->vptr34;
                float* pp = (*(TFnPF)VTFN(s34, 0x2c / 4))(s34);
                (*(TFnVV)VTFN(r, 0x38 / 4))(r, pp);
                float* qq = (*(TFnPF)VTFN(s34, 0x30 / 4))(s34);
                (*(TFnVV)VTFN(r, 0x3c / 4))(r, qq);
                *(uint8_t*)((char*)r + 0x71) = 0;

                float* pf = (*(TFnPF)VTFN(s34, 0x2c / 4))(s34);
                float inv = g_1485720 / sqrtf(((pf[0] * pf[0] + pf[1] * pf[1]) + pf[2] * pf[2]) + g_13ec4b8);

                float off1[3];
                (*(TFnVV)VTFN(s34, 0x5c / 4))(s34, off1);
                float off2[3];
                (*(TFnVV)VTFN(s34, 0x5c / 4))(s34, off2);

                float ex = off2[0] + off1[0];
                float ey = off2[1] + off1[1];
                float ez = off2[2] + off1[2];
                float inv2 = g_1485720 / sqrtf((ex * ex + (ey * ey + ez * ez)) + g_13ec4b8);
                float d[3];
                d[0] = (inv2 * ex) * g_157d284;
                d[1] = (ey * inv2) * g_157d284;
                d[2] = (ez * inv2) * g_157d284;

                void* blk = FUN_00b3d310(r, d, 0);
                FUN_00b452f0(blk);
                void* blk2 = FUN_00b3d310(s34, r, (void*)0x40000000);
                FUN_00b4c600(blk2, r, g_1470f1c);
            }
        }
        (*(TFnVV)VTFN(pi, 2))(pi, 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ca07f0
bool __cdecl FUN_00ca07f0(void* unused, void** range)
{
    void** begin = (void**)range[0];
    void** end = (void**)range[1];
    for (; begin != end; begin++) {
        if (*begin) FUN_00695b40(range, *begin, (void*)0x1570858, L"cCombatant");
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0900
void* __thiscall RefOps::CopyCtor(void* src)
{
    unsigned* s = (unsigned*)src;
    unsigned* d = (unsigned*)this;
    d[0] = s[0];
    if (d[0]) (*(TFnV)VTFN((void*)d[0], 0))((void*)d[0]);
    *(float*)(d + 1) = *(float*)(s + 1);
    *(float*)(d + 2) = *(float*)(s + 2);
    *(float*)(d + 3) = *(float*)(s + 3);
    d[4] = s[4];
    d[5] = s[5];
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0940
void* __thiscall RefOps::AssignA(void* src)
{
    unsigned* s = (unsigned*)src;
    unsigned* d = (unsigned*)this;
    void* old = (void*)d[0];
    void* nw = (void*)s[0];
    if (nw != old) {
        if (nw) (*(TFnV)VTFN(nw, 0))(nw);
        d[0] = (unsigned)nw;
        if (old) (*(TFnV)VTFN(old, 1))(old);
    }
    d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; d[4] = s[4]; d[5] = s[5];
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00ca09a0
void* __thiscall RefOps::AssignB(void* src)
{
    unsigned* s = (unsigned*)src;
    unsigned* d = (unsigned*)this;
    void* old = (void*)d[0];
    void* nw = (void*)s[0];
    if (nw != old) {
        if (nw) (*(TFnV)VTFN(nw, 1))(nw);
        d[0] = (unsigned)nw;
        if (old) (*(TFnV)VTFN(old, 2))(old);
    }
    d[1] = s[1]; d[2] = s[2];
    *(uint8_t*)(d + 3) = (uint8_t)s[3];
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0ad0
void __cdecl FUN_00ca0ad0(void** first, void** last)
{
    if (first == last) return;
    for (void** it = first + 1; it != last; it++) {
        void* val = *it;
        IOREF_ADDREF(val);
        void** hole = it;
        while (hole != first && FUN_00c9f490(hole[-1], val)) {
            void* moved = hole[-1];
            void* dst = *hole;
            if (moved != dst) {
                IOREF_ADDREF(moved);
                *hole = moved;
                IOREF_RELEASE(dst);
            }
            hole--;
        }
        void* dst = *hole;
        if (val != dst) {
            IOREF_ADDREF(val);
            *hole = val;
            IOREF_RELEASE(dst);
        }
        IOREF_RELEASE(val);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ca0ba0
void __cdecl FUN_00ca0ba0(void** first, void** last)
{
    for (; first != last; first++) {
        void* val = *first;
        IOREF_ADDREF(val);
        void** hole = first;
        bool cont = FUN_00c9f490(val, hole[-1]);
        while (cont) {
            void* moved = hole[-1];
            void* dst = *hole;
            if (moved != dst) {
                IOREF_ADDREF(moved);
                *hole = moved;
                IOREF_RELEASE(dst);
            }
            cont = FUN_00c9f490(val, hole[-2]);
            hole--;
        }
        void* dst = *hole;
        if (val != dst) {
            IOREF_ADDREF(val);
            *hole = val;
            IOREF_RELEASE(dst);
        }
        IOREF_RELEASE(val);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00ca0cf0
struct E18 { void* p; float f0, f1, f2; unsigned u0, u1; };
struct E16 { void* p; unsigned u0, u1; unsigned char b0; };

E18* __cdecl FUN_00ca0cf0(E18* s, E18* last, E18* d)
{
    if (s == last) return d;
    do {
        if (d) {
            d->p = s->p;
            if (d->p) (*(TFnV)VTFN(d->p, 0))(d->p);
            d->f0 = s->f0;
            d->f1 = s->f1;
            d->f2 = s->f2;
            d->u0 = s->u0;
            d->u1 = s->u1;
        }
        s++; d++;
    } while (s != last);
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0da0
E18* __cdecl FUN_00ca0da0(E18* s, E18* last, E18* d)
{
    if (s == last) return d;
    do {
        void* nw = s->p;
        void* old = d->p;
        if (nw != old) {
            if (nw) (*(TFnV)VTFN(nw, 0))(nw);
            d->p = nw;
            if (old) (*(TFnV)VTFN(old, 1))(old);
        }
        d->f0 = s->f0;
        d->f1 = s->f1;
        d->f2 = s->f2;
        d->u0 = s->u0;
        d->u1 = s->u1;
        s++; d++;
    } while (s != last);
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0e10
E18* __cdecl FUN_00ca0e10(E18* first, E18* s, E18* d)
{
    if (s == first) return d;
    do {
        s--; d--;
        void* nw = s->p;
        void* old = d->p;
        if (nw != old) {
            if (nw) (*(TFnV)VTFN(nw, 0))(nw);
            d->p = nw;
            if (old) (*(TFnV)VTFN(old, 1))(old);
        }
        d->f0 = s->f0;
        d->f1 = s->f1;
        d->f2 = s->f2;
        d->u0 = s->u0;
        d->u1 = s->u1;
    } while (s != first);
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0e80
E16* __cdecl FUN_00ca0e80(E16* s, E16* last, E16* d)
{
    if (s == last) return d;
    do {
        void* nw = s->p;
        void* old = d->p;
        if (nw != old) {
            if (nw) (*(TFnV)VTFN(nw, 1))(nw);
            d->p = nw;
            if (old) (*(TFnV)VTFN(old, 2))(old);
        }
        d->u0 = s->u0;
        d->u1 = s->u1;
        d->b0 = s->b0;
        s++; d++;
    } while (s != last);
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0ef0
E16* __cdecl FUN_00ca0ef0(E16* first, E16* s, E16* d)
{
    if (s == first) return d;
    do {
        s--; d--;
        void* nw = s->p;
        void* old = d->p;
        if (nw != old) {
            if (nw) (*(TFnV)VTFN(nw, 1))(nw);
            d->p = nw;
            if (old) (*(TFnV)VTFN(old, 2))(old);
        }
        d->u0 = s->u0;
        d->u1 = s->u1;
        d->b0 = s->b0;
    } while (s != first);
    return d;
}

// ---------------------------------------------------------------------------
// @ 0x00ca0f60
void __cdecl FUN_00ca0f60(void** heap, int top, void* val)
{
    while (top > 0) {
        int parent = (top - 1) >> 1;
        if (!FUN_00c9f490(heap[parent], val)) break;
        void* moved = heap[parent];
        void* dst = heap[top];
        if (moved != dst) {
            IOREF_ADDREF(moved);
            heap[top] = moved;
            IOREF_RELEASE(dst);
        }
        top = parent;
    }
    void* dst = heap[top];
    if (val != dst) {
        IOREF_ADDREF(val);
        heap[top] = val;
        IOREF_RELEASE(dst);
    }
    IOREF_RELEASE(val);
}

// ---------------------------------------------------------------------------
// @ 0x00ca1010
void __cdecl FUN_00ca1010(void** a, void** b)
{
    void* av = *a;
    IOREF_ADDREF(av);
    void* bv = *b;
    void* cur = *a;
    if (bv != cur) {
        IOREF_ADDREF(bv);
        *a = bv;
        IOREF_RELEASE(cur);
    }
    void* bv2 = *b;
    if (av != bv2) {
        IOREF_ADDREF(av);
        *b = av;
        IOREF_RELEASE(bv2);
    }
    IOREF_RELEASE(av);
}

// ---------------------------------------------------------------------------
// @ 0x00ca10a0
float* __cdecl FUN_00ca10a0()
{
    if (g_0157c908 == g_13eb1bc) {
        void* local = 0;
        void* pm = SP_PropertyManager();
        if (local) { void* t = local; local = 0; (*(TFnV)VTFN(t, 1))(t); }
        char ok = (*(TFnPUUP)VTFN(pm, 0x2c / 4))(pm, 0x4529f96f, 0x40646200, &local);
        if (ok) SP_GetPropertyAsVector3(local, 0x48f5b53, &g_0157c908);
        if (local) (*(TFnV)VTFN(local, 1))(local);
    }
    return &g_0157c908;
}

// ---------------------------------------------------------------------------
// @ 0x00ca1130
float* __cdecl FUN_00ca1130()
{
    if (g_0157c914 == g_13eb1bc) {
        void* local = 0;
        void* pm = SP_PropertyManager();
        if (local) { void* t = local; local = 0; (*(TFnV)VTFN(t, 1))(t); }
        char ok = (*(TFnPUUP)VTFN(pm, 0x2c / 4))(pm, 0x4529f96f, 0x40646200, &local);
        if (ok) SP_GetPropertyAsVector3(local, 0x48f5b54, &g_0157c914);
        if (local) (*(TFnV)VTFN(local, 1))(local);
    }
    return &g_0157c914;
}

// ---------------------------------------------------------------------------
// @ 0x00ca11c0
__declspec(noinline) float __stdcall WrapAngle(float a)
{
    while (g_0169a280 < a) a -= g_0169a280;
    while (a < 0.0f) a += g_0169a280;
    return a;
}

// ---------------------------------------------------------------------------
// @ 0x00ca1210
void __stdcall FUN_00ca1210(float* out, void* obj, float t)
{
    float f = g_0169a288 * t + g_14749b0;
    unsigned ecx = (unsigned&)f;
    unsigned j = (ecx & 0xf) * 2;
    float t0 = g_01677840[j];
    float t1 = g_01677840[j + 1];
    float tt = t - (float)(int)(ecx + 0xb4c00000) * g_0169a284;
    float* o = (float*)obj;
    float c0 = (t1 - (t0 * tt) * g_1471064) * tt + t0;
    float c1 = t1 - ((t1 * tt) * g_1471064 + t0) * tt;
    out[0] = o[0x80 / 4] * c1 + o[0x8c / 4] * c0;
    out[1] = o[0x84 / 4] * c1 + o[0x90 / 4] * c0;
    out[2] = o[0x88 / 4] * c1 + o[0x94 / 4] * c0;
}
