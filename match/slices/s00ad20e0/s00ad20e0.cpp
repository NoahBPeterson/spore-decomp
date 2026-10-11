// Slice s00ad20e0 -- Simulator vignette / model-manager glue around an embedded
// registry object (at +0x88) and a 0x14-byte-element vector (at +0x20).
//
//   * 0x00ad20e0  look up a registered vignette/entry by (name,a3) ids, adding one if needed
//   * 0x00ad2200  one-time initialisation of the manager tables
//   * 0x00ad2320  configure the shared vignette object via its virtual interface
//   * 0x00ad23c0  per-tick dispatch (place a camera landmark then branch on game mode)
//   * 0x00ad2560  switch the active vignette id (notifies the message server)
//   * 0x00ad25e0  mode-filtered forwarder into 0x00ad23c0
//   * 0x00ad2650  trigger-manager helper
//   * 0x00ad2750  small derived-object constructor
//   * 0x00ad2880 / 0x00ad2910  cActionTarget-based trigger callbacks
//   * 0x00ad29d0 / 0x00ad2a50  cNavigationGoal initialisers (at / toward)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include <intrin.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

// ------------------------------------------------------------------ thiscall thunks
// Explicit __thiscall function-pointer types let a raw vtable slot be called with
// `this` in ecx and the remaining arguments on the stack.
typedef void  (__thiscall *TC_v0)(void*);
typedef void* (__thiscall *TC_p0)(void*);
typedef void  (__thiscall *TC_v1)(void*, void*);
typedef void* (__thiscall *TC_p1)(void*, void*);
typedef void  (__thiscall *TC_v2)(void*, void*, void*);
typedef void  (__thiscall *TC_v4)(void*, void*, void*, void*);
typedef void  (__thiscall *TC_v5)(void*, void*, void*, void*, void*);
#define VTC(obj, off, type) ((type)(*(void***)(obj))[((off) >> 2)])
#define VOFF(obj, off)      (*(void***)(obj))[((off) >> 2)]

// ------------------------------------------------------------------ externs
extern "C" void*   __cdecl App();                       // 0x0067dd10
extern "C" void*   __cdecl GetCurrentGameMode();        // 0x00b5b800
extern "C" void*   __cdecl GetCurrentGameModeAlt();     // 0x00b5b820
extern "C" void*   __cdecl MessageServer();             // 0x0067dcc0
extern "C" void*   __cdecl FUN_00b3d320();              // 0x00b3d320
extern "C" void*   __cdecl FUN_00b3d310();              // 0x00b3d310
extern "C" void*   __stdcall FUN_00ad11f0(void*);      // 0x00ad11f0
extern "C" int     __cdecl FUN_00c0b760(void*);         // 0x00c0b760
extern "C" void*   __cdecl GetUniverseContext();        // 0x1021080
extern "C" void*   __stdcall GetTriggerMgr(void*, void*); // 0x00b3d4d0
extern "C" void    __cdecl FUN_00951bf0(void*, void*, void*); // 0x00951bf0
extern "C" void    __cdecl FUN_00acb680(void*, void*);  // 0x00acb680 (vector insert)
extern "C" void    __fastcall cSpatialObject_ctor(void*); // 0x00c89630 (ecx=this)

bool __cdecl FUN_00ad2650(void*, void*);     // 0x00ad2650 (slice-local)
extern "C" int  __cdecl FUN_00ad2880(void*);            // 0x00ad2880 (slice-local)
extern "C" int  __cdecl FUN_00ad2910(void*);            // 0x00ad2910 (slice-local)
extern "C" void* __cdecl FUN_00ad2320(void*);           // 0x00ad2320 (slice-local)
void* __fastcall FUN_00ad2750(void*);                   // 0x00ad2750 (slice-local)

// ------------------------------------------------------------------ globals
extern int   g_167a4b8;   // 0x0167a4b8  (lazy-init bitfield)
extern int   g_167a4b4;   // 0x0167a4b4
extern int   g_167a4b0;   // 0x0167a4b0
extern int   g_1565d08;   // 0x01565d08
extern int   g_1565d00;   // 0x01565d00
extern void* g_15fd918;   // 0x015fd918  (property-list pointer)
extern int   g_167a37c;   // 0x0167a37c
extern int   g_167a380;   // 0x0167a380
extern int   g_167a384;   // 0x0167a384
extern float kf_1565d5c;  // 0x01565d5c
extern float kf_1565d60;  // 0x01565d60
extern float kf_13ec4b4;  // 0x013ec4b4
extern float kf_145a5c8;  // 0x0145a5c8
extern char  VT_13ef094[];// 0x013ef094
extern char  VT_145a5d8[];// 0x0145a5d8
extern char  VT_145a5d0[];// 0x0145a5d0

// ------------------------------------------------------------------ types
struct Vec3 { float x, y, z; };

struct RegElem {              // 0x0c bytes
    int   pad0;
    uchar flag4;
    char  pad5[3];
    void* p8;
};
struct RegList {              // returned by the registry lookup
    char     pad0[8];
    RegElem* begin;           // +0x08
    RegElem* end;             // +0x0c
};

struct Element14 {            // 0x14-byte element of the +0x20 vector
    float x, y, z;
    float s1, s2;
};

struct Vec14 {                // the +0x20 vector
    Element14* begin;
    Element14* end;
    Element14* cap;
    void insert(Element14*, Element14*);  // 0x00acb680
};

struct Sub88 {                // embedded registry accessor at +0x88
    RegList* get(void* ctx);  // 0x00ad0ca0
};

// thiscall glue for free-standing objects.
struct ActionTarget {         // 0x30-byte stack temporary
    int p00, p04, p08, p0c, p10, p14, p18, p1c, p20, p24, p28, p2c;
    void ctor();              // 0x00ad7940
    void dtor();              // 0x00ad7ad0
};
struct TriggerObj {
    bool check();             // 0x00adb2a0
};
struct B453a0 { void call(void*); };   // 0x00b453a0
struct B45410 { void call(void*); };   // 0x00b45410
struct B1de80 { void* fn2(); };        // 0x00b1de80
struct Rel    { void release(void*); }; // 0x00c96e80 (this=arg0, 1 stack arg)
struct CDPL   { int GetIntProperty(void*); }; // 0x006a2660
struct C389c0 { void call(int, int); };        // 0x00c389c0
struct ObjVt  { void* get(int); };             // 0x00cee... generic
struct CVObj  { void* m(void*); };             // 0x00c... virtual slot 3

// Embedded vignette object (vtable slots 0x2c / 0x30 hit).  Slot 0x2c == 11.
struct Emb2c {
    virtual void  d0(); virtual void  d1(); virtual void  d2(); virtual void  d3();
    virtual void  d4(); virtual void  d5(); virtual void  d6(); virtual void  d7();
    virtual void  d8(); virtual void  d9(); virtual void  dA();
    virtual void* f2c();      // +0x2c
    virtual void* f30();      // +0x30
};

// Generic result type for registry entries: vtable slot 8 (+0x20) returns void*.
struct VTag {
    virtual void  d0(); virtual void  d1(); virtual void  d2(); virtual void  d3();
    virtual void  d4(); virtual void  d5(); virtual void  d6(); virtual void  d7();
    virtual void* v8();       // +0x20
};
struct ElemObj { int get(); };   // 0x00c0b760 (ecx = element)

// ------------------------------------------------------------------ the manager object
struct cMain {
    char    pad00[0x1c];
    void*   msg1c;             // +0x1c  (message target)
    Element14* vecBegin;       // +0x20
    Element14* vecEnd;         // +0x24
    Element14* vecCap;         // +0x28
    char    pad2c[0x88 - 0x2c];
    char    sub88[4];          // +0x88  (Sub88 accessor)
    char    pad8c[0xa0 - 0x8c];
    int     f_a0;              // +0xa0
    char    padA4[0xbc - 0xa4];
    void*   p_bc;              // +0xbc
    char    padC0[0x100 - 0xc0];
    char    f_100;             // +0x100
    char    f_101;             // +0x101

    void* findEntry(int a, int b);          // 0x00ad20e0
    void  init100();                        // 0x00ad2200
    void  f_23c0(void* tag, int a, int b);  // 0x00ad23c0
    void  f_2560(int arg);                  // 0x00ad2560
    void  f_25e0(void* a, void* b);         // 0x00ad25e0
    void  setup(void* tag, int cap);        // 0x00ad1000
    void  removeE(RegList* list, int idx);  // 0x00ac8a80
    void  f_12a0();                         // 0x00ad12a0
    void  f_e4e0(void* arg);                // 0x00ace4e0
    void  f_f4c0(int a, int b);             // 0x00acf4c0
    void  f_e5a0(int a, int b);             // 0x00ace5a0
    void  f_98e0(void* v);                  // 0x00ac98e0
    void  f_8130();                         // 0x00ac8130
    void  f_0bd0();                         // 0x00ad0bd0
    void  release(void* obj);               // 0x00c96e80
};

struct cViewer2 { void GetCameraLocationInfo(Vec3*, int, int, int); }; // 0x007c3d30
struct VMsg   { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
                virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
                virtual void d8(); virtual void v9(void*, void*); };   // slot 9 (+0x24)

// ------------------------------------------------------------------ navigation goal
struct tNavigationGoal {
    Element14* pathBegin;      // +0x00
    Element14* pathEnd;        // +0x04
    Element14* pathCap;        // +0x08
    char   pad0c[0x14 - 0x0c];
    float  destX, destY, destZ;// +0x14
    float  f20;                // +0x20
    int    i24;                // +0x24
    char   pad28[0x4c - 0x28];
    uchar  b4c;                // +0x4c
    char   pad4d[0x50 - 0x4d];
    float  f50, f54, f58;      // +0x50
    int    i5c;                // +0x5c
    float  f60, f64, f68, f6c; // +0x60
    int    i70;                // +0x70
    void   InitAt(float* p, float a, float b);           // 0x00ad29d0
    void   InitToward(float* p, float* q, float a, float b); // 0x00ad2a50
};

// ================================================================================================
// 0x00ad20e0 -- find (or create) a registry entry matching (a,b).
// @ 0x00ad20e0
void* cMain::findEntry(int a, int b)
{
    void* ctx[2];
    ctx[0] = (void*)0x18eb45e;
    ctx[1] = this;
    RegList* list = ((Sub88*)((char*)this + 0x88))->get(ctx);
    int count = (int)(list->end - list->begin);
    int idx = -1;
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            RegElem* e = &list->begin[i];
            if (e->flag4 != 0)
                continue;
            void* p = e->p8;
            if (p == 0)
                continue;
            if (((VTag*)p)->v8() != (void*)0x18eb45e)
                continue;
            idx = i;
            if (*(int*)((char*)p + 0xb20) != a)
                continue;
            if (((ElemObj*)p)->get() == b)
                break;
        }
        if (idx != -1) {
            removeE(list, idx);
            return list->begin[idx].p8;
        }
    }
    int mode = (int)GetCurrentGameMode();
    if ((uint)(mode + 0xfe9ab3ff) > 1u)
        return 0;
    setup((void*)0x18eb45e, count * 2);
    removeE(list, count);
    return list->begin[count].p8;
}

// ================================================================================================
// 0x00ad2200 -- one-time initialisation of the manager tables.
// @ 0x00ad2200
void __fastcall FUN_00ad2200(cMain* self)
{
    if (self->f_100 != 0)
        return;
    if (GetCurrentGameMode() != (void*)0x1654c01) {
        int flags = g_167a4b8;
        if ((flags & 1) == 0) {
            g_167a4b8 = flags | 1;
            g_167a4b4 = g_1565d08 * 20;
        }
        if ((flags & 2) == 0) {
            g_167a4b8 = flags | 2;
            int v = ((CDPL*)g_15fd918)->GetIntProperty((void*)0x625bf68);
            g_167a4b0 = v + 0x8c;
        }
        int cap = g_167a4b4;
        int other = g_167a4b0;
        if (other < cap) other = cap;
        self->setup((void*)0x18eb4b7, other);
    }
    self->setup((void*)0x18eb45e, g_1565d00);
    self->f_100 = 1;
    int m1 = (int)GetCurrentGameMode();
    void* m2 = GetCurrentGameModeAlt();
    int c = (m1 == 0x1654c01 || m1 == 0x1654c02) ? 1 : 0;
    self->f_101 = (char)c;
    if (c == 0) {
        int c2 = ((int)m2 == 0x1654c01 || (int)m2 == 0x1654c02) ? 1 : 0;
        self->f_101 = (char)c2;
    }
    g_167a37c = 0;
    g_167a380 = 0;
    g_167a384 = 0;
}

// ================================================================================================
// 0x00ad2320 -- configure the shared vignette object through its virtual interface.
// @ 0x00ad2320
void* __cdecl FUN_00ad2320(void* param)
{
    void* edi = 0;
    void* v = FUN_00ad11f0((void*)0x18eb4b7);
    if (v != 0)
        edi = VTC(v, 0xc, TC_p1)(v, (void*)0x4f176642);
    else
        edi = 0;
    void* embParam = (char*)param + 0x120;
    void* r1 = VTC(embParam, 0x2c, TC_p0)(embParam);
    VTC(edi, 0xe8, TC_v5)(edi, 0, param, 0, r1);
    void* emb2 = (char*)edi + 0xc0;
    void* r2 = VTC(embParam, 0x2c, TC_p0)(embParam);
    VTC(emb2, 0x38, TC_v1)(emb2, r2);
    void* r3 = VTC(embParam, 0x30, TC_p0)(embParam);
    VTC(emb2, 0x3c, TC_v1)(emb2, r3);
    ((Rel*)param)->release(edi);
    return edi;
}

// ================================================================================================
// 0x00ad23c0 -- per-tick dispatch: push the camera landmark, then branch on game mode.
// @ 0x00ad23c0
void cMain::f_23c0(void* tag, int a, int b)
{
    void* app = App();
    void* x = VTC(app, 0x50, TC_p0)(app);
    void* viewer = VTC(x, 0x1c, TC_p0)(x);
    Vec3 cam;
    ((cViewer2*)viewer)->GetCameraLocationInfo(&cam, 0, 0, 0);

    float f1 = kf_1565d5c;
    float f2 = kf_1565d60;
    Element14 tmp;
    tmp.x = cam.x; tmp.y = cam.y; tmp.z = cam.z;
    tmp.s1 = f1 * f1; tmp.s2 = f2 * f2;

    if (vecEnd < vecCap) {
        vecEnd = (Element14*)((char*)vecEnd + 0x14);
    } else {
        ((Vec14*)((char*)this + 0x20))->insert(vecEnd, &tmp);
    }
    Element14* e = (Element14*)((char*)vecEnd - 0x14);
    e->x = cam.x; e->y = cam.y; e->z = cam.z;
    e->s1 = f1 * f1; e->s2 = f2 * f2;

    if (tag == (void*)0x1654c01) {
        f_e5a0(a, b);
    } else if (tag == (void*)0x1654c02) {
        f_e4e0((void*)b);
        f_12a0();
        f_e5a0(a, b);
    } else if (tag == (void*)0x1654c04) {
        f_e4e0((void*)b);
        if (p_bc)
            ((VMsg*)p_bc)->v9((void*)b, 0);
        f_12a0();
        f_f4c0(a, b);
    } else {
        if (GetUniverseContext() == 0) {
            f_e4e0((void*)b);
            if (p_bc)
                ((VMsg*)p_bc)->v9((void*)b, 0);
            f_12a0();
            f_f4c0(a, b);
        }
    }

    Element14* sb = vecBegin;
    Element14* se = vecEnd;
    FUN_00951bf0(se, se, sb);
    int count = (int)((char*)se - (char*)sb) / 20;
    vecEnd = (Element14*)((char*)vecEnd - count * 20);
}

// ================================================================================================
// 0x00ad2560 -- switch the active vignette id (notifies the message server).
// @ 0x00ad2560
void cMain::f_2560(int arg)
{
    if (arg == f_a0)
        return;
    if (f_a0 != -1)
        f_0bd0();
    void* ms = MessageServer();
    if (ms != 0) {
        ((VMsg*)ms)->v9((char*)this + 0x1c, (void*)0x1a0219e);
        ((VMsg*)ms)->v9((char*)this + 0x1c, (void*)0x6130eb9);
    }
    void* t = FUN_00b3d320();
    void* v = ((B1de80*)t)->fn2();
    f_98e0(v);
    f_8130();
    FUN_00ad2200(this);
    f_a0 = arg;
}

// ================================================================================================
// 0x00ad25e0 -- mode-filtered forwarder into 0x00ad23c0.
// @ 0x00ad25e0
void cMain::f_25e0(void* a, void* b)
{
    if (GetCurrentGameMode() == (void*)0x1654c10)
        return;
    void* mode = GetCurrentGameMode();
    if (mode == (void*)0x1654c06)
        mode = GetCurrentGameModeAlt();
    f_23c0(mode, (int)a, (int)b);
}

// ================================================================================================
// 0x00ad2650 -- trigger-manager helper.
// @ 0x00ad2650
bool __cdecl FUN_00ad2650(void* a, void* b)
{
    bool r = ((TriggerObj*)GetTriggerMgr(a, b))->check();
    _ReadWriteBarrier();
    return r;
}

// ================================================================================================
// 0x00ad2750 -- small derived-object constructor.
// @ 0x00ad2750
void* __fastcall FUN_00ad2750(void* p)
{
    cSpatialObject_ctor(p);
    *(void* volatile*)((char*)p + 0xd4) = VT_13ef094;
    *(int*)((char*)p + 0xd8) = 0;
    *(void**)((char*)p + 0x00) = VT_145a5d8;
    *(void**)((char*)p + 0xd4) = VT_145a5d0;
    return p;
}

// ================================================================================================
// 0x00ad2880 -- cActionTarget-based trigger callback (variant 1).
// @ 0x00ad2880
int __cdecl FUN_00ad2880(void* param)
{
    if (param != 0) {
        void* iv = VTC(param, 0xc, TC_p1)(param, (void*)0x55aa4e6);
        if (iv != 0) {
            ActionTarget at;
            at.ctor();
            void* eax = *(void**)((char*)iv + 0xc);
            void* tm = GetTriggerMgr(eax, &at);
            if (((TriggerObj*)tm)->check()) {
                void* f = (void*)(long)at.p2c;
                if (f != 0) {
                    if (*(char*)((char*)iv + 0x10) != 0) {
                        void* g = FUN_00b3d310();
                        ((B453a0*)g)->call(f);
                        at.dtor();
                        return 1;
                    }
                    void* g = FUN_00b3d310();
                    ((B45410*)g)->call(f);
                }
            }
            at.dtor();
        }
    }
    return 1;
}

// ================================================================================================
// 0x00ad2910 -- cActionTarget-based trigger callback (variant 2).
// @ 0x00ad2910
int __cdecl FUN_00ad2910(void* param)
{
    if (param != 0) {
        void* iv = VTC(param, 0xc, TC_p1)(param, (void*)0x60b4546);
        if (iv != 0) {
            ActionTarget at;
            at.ctor();
            void* eax = *(void**)((char*)iv + 0xc);
            void* tm = GetTriggerMgr(eax, &at);
            if (((TriggerObj*)tm)->check()) {
                void* f = (void*)(long)at.p2c;
                if (f != 0) {
                    void* r = VTC(f, 0xb8, TC_p1)(f, (void*)0x2dd8c33);
                    if (r != 0) {
                        *(uchar*)((char*)r + 0x65d) = *(uchar*)((char*)iv + 0x10);
                        at.dtor();
                        return 1;
                    }
                    void* r2 = VTC(f, 0xb8, TC_p1)(f, (void*)0xb033b403);
                    if (r2 != 0) {
                        ((C389c0*)r2)->call(9, *(uchar*)((char*)iv + 0x10));
                    }
                }
            }
            at.dtor();
        }
    }
    return 1;
}

// ================================================================================================
// 0x00ad29d0 -- cNavigationGoal::InitAt.
// @ 0x00ad29d0
void tNavigationGoal::InitAt(float* p, float a, float b)
{
    pathBegin = 0;
    pathEnd = 0;
    pathCap = 0;
    destX = p[0];
    destY = p[1];
    destZ = p[2];
    f20 = a;
    i24 = 0;
    b4c = 0;
    f50 = 0.0f;
    f54 = 0.0f;
    f58 = 0.0f;
    f60 = b;
    f64 = kf_13ec4b4;
    i5c = 1;
    f68 = kf_145a5c8;
    f6c = 0.0f;
    i70 = 0;
}

// ================================================================================================
// 0x00ad2a50 -- cNavigationGoal::InitToward.
// @ 0x00ad2a50
void tNavigationGoal::InitToward(float* p, float* q, float a, float b)
{
    pathBegin = 0;
    pathEnd = 0;
    pathCap = 0;
    destX = p[0];
    destY = p[1];
    destZ = p[2];
    f20 = a;
    i24 = 0;
    b4c = 0;
    f50 = q[0];
    f54 = q[1];
    f58 = q[2];
    f60 = b;
    f64 = kf_13ec4b4;
    f68 = kf_145a5c8;
    i5c = 3;
    f6c = 0.0f;
    i70 = 0;
}
