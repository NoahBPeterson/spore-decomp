// Slice s00f318e0 -- Simulator scenario property object (bfs2 slice 12).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- helpers / globals
void* __cdecl MessageServer();                                   // 0x0067DCC0
void  __cdecl FUN_00fa92f0(void*);                               // 0x00FA92F0
extern int* g_16065fc;                                           // 0x016065FC
extern unsigned char g_16065f8;                                  // 0x016065F8

struct Vector3 {
    float x, y, z;
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};

struct Sub190 { char pad[0x1c]; void fn(); };                    // 0x00FA92F0 thiscall

struct Sub {
    char pad[0x58];
    float f58;
    float f5c;
    void setOne(int v);
    void fn1(Vector3);
    void fn2(Vector3);
    void fn3(Vector3);
    void fn4(Vector3);
};

struct Msg {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5();
    virtual void s6(int, int, int, int);
};

struct Vec4 { int x, y, z; float w; Vec4* Set(); };

struct Obj {
    char pad0[4];
    Sub* m4;                       // +0x004
    char pad8[0xc-8];
    float mC;                      // +0x00c
    char pad10[0xcc-0x10];
    float mCC;                     // +0x0cc
    float mD0;                     // +0x0d0
    char padD4[0xe0-0xd4];
    float mE0;                     // +0x0e0
    float mE4;                     // +0x0e4
    char padE8[0xec-0xe8];
    int  mEC;                      // +0x0ec
    int  mF0;                      // +0x0f0
    char padF4[0x100-0xf4];
    void* m100;                    // +0x100
    unsigned char m104;            // +0x104
    char pad105[0x130-0x105];
    Vector3 v130;                  // +0x130
    Vector3 v13c;                  // +0x13c
    Vector3 v148;                  // +0x148
    Vector3 v154;                  // +0x154
    char pad160[0x190-0x160];
    void*    m190;                 // +0x190
    Sub*     m194;                 // +0x194

    float lerp();
    void  set104(int v);
    void  setEC(int v);
    void  setF0(int v);
    void  set148(const Vector3& v);
    void  set154(const Vector3& v);
    void  set130(const Vector3& v);
    void  set13c(const Vector3& v);
    char  onMsg(int a, int b);
    void  release100();
};

struct X100 {
    virtual void s0(); virtual void Release(); virtual void s2();
    virtual void f0c(int); virtual char f10();
};

// @ 0x00F31B70
float Obj::lerp() { return m4->f58 + (m4->f5c - m4->f58) * mC; }

// @ 0x00F31C20
void Obj::set104(int v) { m104 = (unsigned char)v; m194->setOne(v); }

// @ 0x00F31D20
void Obj::setEC(int v) { if ((unsigned)(v-1) <= 0xe) { mEC = v; m194->setOne(v); } }

// @ 0x00F31D50
void Obj::setF0(int v) { if ((unsigned)(v-1) <= 0xe) { mF0 = v; m194->setOne(v); } }

// @ 0x00F31EA0
void MsgSend() { ((Msg*)MessageServer())->s6(0x36b154d8, 0, 0, 0); }

// @ 0x00F31FD0
Vec4* Vec4::Set() { x = 0; y = 0; z = 0; w = 1.0f; return this; }

// @ 0x00F32100
void Obj::set148(const Vector3& v) { v148 = v; m194->fn1(v148); }
// @ 0x00F32150
void Obj::set154(const Vector3& v) { v154 = v; m194->fn2(v154); }
// @ 0x00F321A0
void Obj::set130(const Vector3& v) { v130 = v; m194->fn3(v130); }
// @ 0x00F321F0
void Obj::set13c(const Vector3& v) { v13c = v; m194->fn4(v13c); }

// @ 0x00F32410
void ReleaseGlobal() { int* p = g_16065fc; if (p) { g_16065fc = 0; (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p); } g_16065f8 = 1; }

// @ 0x00F326F0
char Obj::onMsg(int a, int b) { if (a == 0x36b154d8 && m190 != 0) ((Sub190*)m190)->fn(); return 0; }

// @ 0x00F323C0
void Obj::release100()
{
    if (m100) {
        if (((X100*)m100)->f10()) {
            ((X100*)m100)->f0c(1);
            if (m100) {
                X100* p = (X100*)m100;
                m100 = 0;
                p->Release();
            }
        }
    }
}

// @ 0x00F326D0
// @ 0x00F326D0 (member of the same class as 0xF325B0)
struct C {
    float f325b0();
    int below(int dummy);
};

// @ 0x00F325B0
__declspec(noinline) float C::f325b0() { return 0.0f; }

// @ 0x00F326D0
int C::below(int dummy) { float r = f325b0(); if (r < 1.0f) return 1; return 0; }

// ---------------------------------------------------------------- active planet record
struct T { virtual void AddRef(); virtual void Release(); };
struct SubG { void fn(T* p); };
void* __cdecl GetActivePlanetRecord();           // 0x010212A0
extern void* g_16c8750;                          // 0x016C8750
extern SubG  g_16c85a0;                          // 0x016C85A0

// @ 0x00F31F80
void SelectPlanetRecord()
{
    T* p = (T*)GetActivePlanetRecord();
    if (p != (T*)g_16c8750) {
        T* old = (T*)g_16c8750;
        if (p) p->AddRef();
        g_16c8750 = p;
        if (old) old->Release();
    }
    T* q = (T*)g_16c8750;
    if (q) g_16c85a0.fn(q);
}

// ---------------------------------------------------------------- not yet matching
void FUN_00f318e0(void* self) { (void)self; }     // @ 0x00F318E0 (0x2cb0 ctor helper)
void FUN_00f31b90() { }                            // @ 0x00F31B90
void FUN_00f31c40(void* self, int v) { (void)self; (void)v; }  // @ 0x00F31C40
void FUN_00f31cb0(void* self, int v) { (void)self; (void)v; }  // @ 0x00F31CB0
void FUN_00f31d80(void* self, int v) { (void)self; (void)v; }  // @ 0x00F31D80
void FUN_00f31de0(void* self, int v) { (void)self; (void)v; }  // @ 0x00F31DE0
void FUN_00f31e60(void* self) { (void)self; }      // @ 0x00F31E60
void FUN_00f31ee0(void* self) { (void)self; }      // @ 0x00F31EE0
void FUN_00f31f20(void* a, void* b, void* c) { (void)a; (void)b; (void)c; }  // @ 0x00F31F20
void FUN_00f31ff0(void* self) { (void)self; }      // @ 0x00F31FF0
void FUN_00f32030(void* self) { (void)self; }      // @ 0x00F32030
void FUN_00f32240(void* self) { (void)self; }      // @ 0x00F32240
void FUN_00f323c0(void* self) { (void)self; }      // @ 0x00F323C0
void FUN_00f32440(void* self) { (void)self; }      // @ 0x00F32440
void FUN_00f32710(void* self, void* v) { (void)self; (void)v; }  // @ 0x00F32710
void FUN_00f32790(void* self, void* v) { (void)self; (void)v; }  // @ 0x00F32790
void FUN_00f327f0(void* self) { (void)self; }      // @ 0x00F327F0
