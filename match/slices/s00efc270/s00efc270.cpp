// slice s00efc270 -- scenario tutorial / checklist support helpers: global checklist pointer,
// type predicates, planet-position helpers, sound/hint triggers.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE  (SSE scalar float math, x87 for float returns).
#include "types.h"

extern void** g_016c7b88;              // 0x016c7b88
extern void*  gSimulator;              // 0x016c7aa4
extern void*  g_15fd918;               // 0x015fd918
extern uint8_t g_16c7b50, g_16c7b51;   // 0x016c7b50 / 0x016c7b51
extern uint8_t g_15ad344;              // 0x015ad344
extern uint8_t g_16c7d18;              // 0x016c7d18
extern float  g_16c7b98, g_16c7b9c, g_16c7ba0;  // Vector3 globals
extern float  g_15ad338, g_15ad33c, g_15ad340, g_15ad29c;
extern float  g_1485720, g_1471064, g_13ec4d0, g_1477fc0, g_1441a88;

extern "C" void* memcpy(void*, const void*, unsigned);

int   __cdecl SP_App();
void* __cdecl FUN_00d20430(int);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl SP_GameInputManager();
void* __cdecl SP_MessageServer();
void* __cdecl SP_ConfigManager();
void* __cdecl FUN_00b18e00(void*);
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eebf80(void*);
void __fastcall FUN_00f35f70(void* self, int dummy);            // __thiscall in retail (tail jmp)
void* __cdecl FUN_00f40ea0(void*, int);
void* __fastcall FUN_00f326d0(void* self, int dummy, int b);    // __thiscall
void* __cdecl FUN_00f46410(void*, void*, void*);
void* __fastcall FUN_00f38330(void* self, int dummy, int arg);  // __thiscall
void* __fastcall FUN_00f34560(void* self, int dummy);           // __thiscall
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);

// Retail callees that take `this` in ecx (__thiscall).  Declaring them as members keeps the
// call site from writing edx (a dummy __fastcall argument did); the original leaves edx alone.
struct TutorialsTarget {
    void Update();        // 0x00f35f70  (tail-jumped from 0x00efc850)
    void SetFlag(int on); // 0x00f38330
    void Release();       // 0x00f34560
    bool Add(int id);     // 0x00f326d0
};

typedef int   (__thiscall *FN0_i)(void*);
typedef float (__thiscall *FN0_f)(void*);
typedef void  (__thiscall *FN2_ii)(void*, int, int);
typedef void  (__thiscall *FN3_iii)(void*, int, int, int);
typedef void* (__thiscall *FN1_i)(void*, int);
typedef void  (__thiscall *TF_ii)(void*, int, int);
typedef void  (__thiscall *TF_i)(void*, int);
typedef void  (__thiscall *TF_v)(void*);
typedef int   (__thiscall *TF_ri)(void*, int);
typedef int   (__thiscall *TF_r)(void*);

void          __cdecl FUN_00985e40(void*);
int           __cdecl FUN_00efc530(void*);
void* __fastcall FUN_00f33620(void*, int, void*);
void* __fastcall FUN_00f3e8a0(void*, int, int);
void* __cdecl FUN_0067dd10();
void* __cdecl FUN_00b3d350();
struct Vec3;
Vec3* __fastcall FUN_00b82620(void*, int, void*, void*, void*, int);
void* __fastcall FUN_00b13bb0(void*, int, void*, int);
void  __cdecl FUN_00eec2b0(void*, void*, int, void*, int);
void  __cdecl FUN_00eec8e0(void*, void*, void*);
extern int g_15ad298;

void FUN_00efbbe0();
void FUN_00ef8860();
void FUN_00efbf60();
void FUN_00ef8820();
void FUN_00efbe40();
void FUN_00ef8440();
void FUN_00ef8ed0();
int  __cdecl FUN_00ef7280(void);
void* __cdecl FUN_00eeca30(void*);
void* __cdecl FUN_00b3d250();

// 0x00efc520
int __cdecl FUN_00efc520()
{
    if (g_016c7b88 != 0)
        return *(int*)g_016c7b88;
    return 0;
}

// @ 0x00efc530
bool __cdecl FUN_00efc530(int* p)
{
    if (p != 0) {
        int t = ((FN0_i)((*(void***)p)[0xe]))(p);
        if (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a || t == 0x7a81824 || t == 0x7abdd8d)
            return true;
    }
    return false;
}

// @ 0x00efc6c0
void __fastcall FUN_00efc6c0(char* p, int pad, int v)
{
    int* q = *(int**)(p + 0xc);
    if (q != 0 && *q == v)
        *q = -1;
}

// @ 0x00efc850
void __cdecl FUN_00efc850()
{
    char* sim = (char*)gSimulator;
    char* o = *(char**)(sim + 0x18);
    ((TutorialsTarget*)o)->Update();
}
// 0x00efc860
void __cdecl FUN_00efc860()
{
    if (*(int*)((char*)g_016c7b88 + 0xc) != 0) {
        void* im = SP_GameInputManager();
        ((FN2_ii)((*(void***)im)[0x19]))(im, 0x96b6b02c, 1);
    }
}

// 0x00efc890
void __cdecl FUN_00efc890()
{
    char* g = (char*)g_016c7b88;
    int o = *(int*)(g + 0xc);
    if (o != 0) {
        char* r = (char*)FUN_00b18e00((void*)o);
        *(uint8_t*)(r + 0x6e) = 1;
        void* im = SP_GameInputManager();
        ((FN2_ii)((*(void***)im)[0x19]))(im, 0x96b6b02c, 1);
    }
}

// @ 0x00efc8c0
void __cdecl FUN_00efc8c0(int v)
{
    int* g = (int*)g_016c7b88;
    int old = *g;
    *g = v;
    if (old != v)
        FUN_00f46410((void*)1, (void*)old, (void*)v);
}

// @ 0x00efc8f0
int __cdecl FUN_00efc8f0()
{
    int r = 0;
    if (g_016c7b88 != 0 && *(int*)((char*)g_016c7b88 + 8) != 0)
        r = (int)FUN_00eebf80(*(void**)((char*)g_016c7b88 + 8));
    return r;
}

// 0x00efc910
int __cdecl FUN_00efc910()
{
    int r = 0;
    if (g_016c7b88 != 0)
        r = (int)FUN_00eebf80(*(void**)((char*)g_016c7b88 + 4));
    return r;
}

// @ 0x00efc7a0
bool __fastcall FUN_00efc7a0(char* p)
{
    if (*(char*)(p + 5) != 0) {
        ((TutorialsTarget*)*(void**)(p + 8))->SetFlag(1);
        ((TutorialsTarget*)*(void**)(p + 8))->Release();
        *(char*)(p + 5) = 0;
    }
    return true;
}

// @ 0x00efc660
bool __fastcall FUN_00efc660(char* p, int pad, int a)
{
    if (a == 0)
        return false;
    char* o = (char*)FUN_00b18e00((void*)a);
    if (o == 0 || *(char*)(o + 0x6e) != 0)
        return false;
    char r = (char)FUN_00f40ea0(*(void**)(p + 8), a);
    if (r == 0) {
        void* ms = SP_MessageServer();
        ((FN2_ii)((*(void***)ms)[5]))(ms, 0x78c406b, 0);
    }
    return r != 0;
}

// @ 0x00efc7d0
bool __fastcall FUN_00efc7d0(char* p, int pad, int a, int b)
{
    char* o = (char*)FUN_00b18e00((void*)a);
    if (o != 0 && *(char*)(o + 0x6e) != 0)
        return false;
    bool r = ((TutorialsTarget*)*(void**)(p + 8))->Add(b);
    if (!r) {
        void* ms = SP_MessageServer();
        ((FN3_iii)((*(void***)ms)[5]))(ms, 0x78c406b, 0, 0);
    }
    return r;
}

// @ 0x00efcd90
int __cdecl FUN_00efcd90()
{
    int app = SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))((void*)app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b != 0) {
        int o = ((FN0_i)((*(void***)b)[3]))(b);
        if (o != 0 && (*(char*)(o + 0x319) == 0 || *(char*)(o + 0x11) != 0))
            return 1;
    }
    return 0;
}

// @ 0x00efcae0
void __cdecl FUN_00efcae0()
{
    int app = SP_App();
    void* a = (void*)((FN0_i)((*(void***)app)[0x14]))((void*)app);
    void* b = (void*)((FN0_i)((*(void***)a)[0xe]))(a);
    if (b != 0) {
        int o = ((FN0_i)((*(void***)b)[3]))(b);
        if (o != 0) {
            *(uint8_t*)(o + 0x315) = 0;
            FUN_00d20430(0);
            return;
        }
    }
    void* m = FUN_00b3d280();
    if (m != 0) {
        FUN_00b0f950(m, 0);
        FUN_00b10c40(m, 0);
    }
}

// @ 0x00efcde0
void __fastcall FUN_00efcde0(void* p)
{
    int r;
    if (p == 0)
        r = 0;
    else
        r = ((FN0_i)((*(void***)p)[3]))(p);
    if (*(int*)(r + 0x54) != 0) {
        void* q = *(void**)(r + 0x54);
        if (q != 0) {
            int s = ((FN0_i)((*(void***)q)[3]))(q);
            ((FN2_ii)((*(void***)s)[0x15]))((void*)s, 0, 0);
            return;
        }
        FUN_00d20430(0);
    }
}

// @ 0x00efce30
void __fastcall FUN_00efce30(void* p)
{
    int r;
    if (p == 0)
        r = 0;
    else
        r = ((FN0_i)((*(void***)p)[3]))(p);
    if (*(int*)(r + 0x54) != 0) {
        void* q = *(void**)(r + 0x54);
        int s;
        if (q == 0)
            s = 0;
        else
            s = ((FN0_i)((*(void***)q)[3]))(q);
        ((FN2_ii)((*(void***)s)[0x15]))((void*)s, 1, 0);
        void* t = (void*)FUN_00b18e00(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0xe]))(t);
        t = (void*)FUN_00b18e00(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0xf]))(t);
        t = (void*)FUN_00b18e00(*(void**)(r + 0x54));
        ((FN0_i)((*(void***)t)[0x10]))(t);
    }
}

// ---------------------------------------------------------------------------
// externs
// ---------------------------------------------------------------------------
int   __cdecl SP_App();
void* __cdecl FUN_00d20430(int);
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);
void* __cdecl FUN_00d20430(int);
void* __cdecl SP_GameInputManager();
void* __cdecl SP_MessageServer();
void* __cdecl SP_ConfigManager();
void* __cdecl FUN_00b18e00(void*);
void* __cdecl FUN_00b3d280();
void* __cdecl FUN_00eebf80(void*);
void __fastcall FUN_00f35f70(void* self, int dummy);            // __thiscall in retail (tail jmp)
void* __cdecl FUN_00f40ea0(void*, int);
void* __fastcall FUN_00f326d0(void* self, int dummy, int b);    // __thiscall
void* __cdecl FUN_00f46410(void*, void*, void*);
void* __fastcall FUN_00f38330(void* self, int dummy, int arg);  // __thiscall
void* __fastcall FUN_00f34560(void* self, int dummy);           // __thiscall
void* __cdecl FUN_00b0f950(void*, int);
void* __cdecl FUN_00b10c40(void*, int);

// ---------------------------------------------------------------------------
// remaining functions (bodies approximated; see nonmatching.txt / partial.txt)
// ===========================================================================

// Member helpers with non-standard conventions (this in eax/esi) are declared
// as free functions taking the pointer explicitly; see partial.txt.
typedef float (__thiscall *PF_t)(void*);

// @ 0x00efc270
int __fastcall FUN_00efc270(char* self, int pad, int tag, int arg)
{
    int sv;
    (void)pad;
    FUN_00985e40(*(void**)((char*)gSimulator + 0x14));
    switch (tag) {
    case 0x539a4ce:
        if (*(int*)(self + 0x30) != -1) {
            *(char*)(self + 0x3d) = 1;
            return 0;
        }
        break;
    case 0x4519b5f:
        ((TF_i)FUN_00ef8ed0)(self, FUN_00ef7280() == 0);
        return 0;
    case 0x539a4cf:
        if (*(char*)(self + 0x3f) != 0) {
            if (*(char*)(self + 0x3d) != 0) {
                *(char*)(self + 0x3e) = 1;
                *(char*)(self + 0x3d) = 0;
            }
            *(char*)(self + 0x3f) = 0;
            return 0;
        }
        break;
    case 0x743b6fa:
        ((TF_ii)FUN_00efbbe0)(self, 0x8c, 0x8d);
        return 0;
    case 0x74baf67: {
        sv = *(int*)(*(char**)((char*)arg + 8));
        if ((int)gSimulator != sv && *(char*)((char*)sv + (int)self + 0x38) == 0)
            ((TF_v)FUN_00ef8860)(self);
        switch (sv) {
        case 0:
            ((TF_v)FUN_00efbf60)(self);
            if (((TF_ri)FUN_00ef8820)(self, 2) == 0 && g_16c7b50 == 0) {
                ((TF_v)FUN_00ef8860)(self);
                ((TF_ii)FUN_00efbe40)(self, 0, 0);
                g_16c7b50 = 1;
            }
            return 0;
        case 1:
            ((TF_ii)FUN_00efbbe0)(self, 9, 0xa);
            ((TF_ii)FUN_00efbbe0)(self, 0x6f, 0x70);
            ((TF_ii)FUN_00efbbe0)(self, 0x26, 0x27);
            return 0;
        case 2:
            ((TF_v)FUN_00efbf60)(self);
            if (((TF_ri)FUN_00ef8820)(self, 0x87) == 0 && g_16c7b51 == 0) {
                ((TF_v)FUN_00ef8860)(self);
                ((TF_ii)FUN_00efbe40)(self, 0, 1);
                g_16c7b51 = 1;
            }
            return 0;
        }
        return 0;
    }
    case 0x7956d8a:
        if (*(int*)((char*)arg + 8) == (int)0xd23c5170) {
            ((TF_ii)FUN_00efbbe0)(self, 0xa8, 0xa9);
            *(char*)(self + 0x3c) = 1;
        } else {
            *(char*)(self + 0x3c) = 0;
        }
        return 0;
    case 0x7a12a49:
        if (((TF_r)FUN_00ef8440)(self) == 0) {
            ((TF_ii)FUN_00efbbe0)(self, 0x1d, 0x1e);
            return 0;
        }
        return 0;
    case 0x7bb7345:
        ((TF_ii)FUN_00efbbe0)(self, 0xf, 0x10);
        return 0;
    case 0x7bb7346:
        ((TF_ii)FUN_00efbbe0)(self, 0x11, 0x12);
        return 0;
    case 0x7bb7347:
        ((TF_ii)FUN_00efbbe0)(self, 0x13, 0x14);
        return 0;
    }
    return 0;
}

// @ 0x00efc4c0
float __fastcall FUN_00efc4c0(char* self, int pad)
{
    (void)pad;
    if (*(float*)(self + 0x178) > *(float*)(self + 0x174))
        return (*(float*)(self + 0x17c) - *(float*)(self + 0x174)) /
               (*(float*)(self + 0x178) - *(float*)(self + 0x174));
    return g_1485720;
}

// @ 0x00efc570
// Non-standard ABI in the original: first pointer arrives in EAX, second in ECX,
// float on stack. Expressed here as a plain function; byte-exactness from C is
// not achievable (no C convention passes the first argument in EAX).
bool __cdecl FUN_00efc570(void* a, void* self2, float f)
{
    char* esi;
    if (a == 0)
        return true;
    esi = (char*)a - 8;
    if (esi == 0)
        return true;
    if (*(int*)(esi + 0xd4) == 0)
        return true;
    float xmm0 = *(float*)(*(char**)((char*)g_15fd918 + 0x3c) + 0x9c) * f;
    float xmm1;
    if (self2 != 0)
        xmm1 = ((PF_t)((*(void***)self2)[0xd]))(self2);
    else
        xmm1 = *(float*)(esi + 0x20);
    unsigned char idx = *(unsigned char*)(esi + 0x129);
    char* tbl = *(char**)(esi + 0xd4);
    return (xmm0 / xmm1) < *(float*)(tbl + idx * 4 - 4);
}

// @ 0x00efc5f0
int __fastcall FUN_00efc5f0(void* self, int pad, float f, int a)
{
    (void)self; (void)pad;
    if (g_15ad33c > f)
        return 0;
    float xmm0;
    void* v = FUN_00eeca30((void*)a);
    if (v != 0)
        xmm0 = ((PF_t)((*(void***)v)[0x1c]))(v);
    else
        xmm0 = g_1485720;
    float xmm1 = g_15ad29c / f * xmm0;
    return g_15ad338 > xmm1;
}

// @ 0x00efc6e0
int __stdcall FUN_00efc6e0(void* arg)
{
    char bl = 0;
    void* esi = arg;
    int matched = 0;
    if (esi != 0) {
        int t = ((FN0_i)((*(void***)esi)[0xe]))(esi);
        if (t == 0x7a309fb || t == 0x76c67df || t == 0x771ad6a ||
            t == 0x7a81824 || t == 0x7abdd8d)
            matched = 1;
    }
    if (!matched) {
        void* v = FUN_00eebf80(esi);
        if (v != 0) {
            char b1 = 0, b2 = 0;
            FUN_00eec8e0(v, &b2, &b1);
            bl = (b1 != 0 || b2 != 0);
        }
    }
    unsigned ecx = *(unsigned*)((char*)gSimulator + 0x40);
    int eax = 1;
    if (bl) {
        if (1 & (ecx >> 1))
            eax = 2;
        else if (1 & ecx)
            eax = 3;
    }
    char* g = (char*)g_016c7b88;
    if (*(int*)(g + 0x68) != eax) {
        *(char*)(g + 0x64) = 1;
        *(int*)((char*)g_016c7b88 + 0x68) = eax;
    }
    return eax;
}

struct Vec3 { float x, y, z; };
typedef void* (__thiscall *FN_v58)(void*, int*, int*);

void* __fastcall FUN_007c4900(void*, int);
void* __cdecl FUN_00b82620(void* self, void* a, void* b, void* c, int d);

// @ 0x00efc930
// Original writes its Vec3 through ESI (an out-pointer in that register) and
// returns a flag in AL; that convention cannot be produced from C, so the out
// pointer is declared explicitly. Behaviour (compare against the 3 globals)
// matches the original.
int __cdecl FUN_00efc930(Vec3* out)
{
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0;
    void* app = FUN_0067dd10();
    void* x = ((FN_v58)((*(void***)app)[0x16]))(app, &a0, &a1);
    void* y = FUN_007c4900(x, 0);
    (void)y;
    void* pm = FUN_00b3d350();
    Vec3* v = (Vec3*)FUN_00b82620(pm, &a3, &a2, &a1, 0);
    out->x = v->x; out->y = v->y; out->z = v->z;
    if (out->x != g_16c7b98 || out->y != g_16c7b9c || out->z != g_16c7ba0)
        return 1;
    return 0;
}

// @ 0x00efc9c0
int __cdecl FUN_00efc9c0()
{
    int a0 = 0, a1 = 0, a2 = 0, a3 = 0;
    Vec3 v;
    void* app = FUN_0067dd10();
    void* x = ((FN_v58)((*(void***)app)[0x16]))(app, &a0, &a1);
    void* y = FUN_007c4900(x, 0);
    (void)y;
    void* pm = FUN_00b3d350();
    Vec3* r = (Vec3*)FUN_00b82620(pm, &a3, &a2, &a1, 0);
    v.x = r->x; v.y = r->y; v.z = r->z;
    if (v.x != g_16c7b98 || v.y != g_16c7b9c || v.z != g_16c7ba0)
        return 1;
    return 0;
}

// @ 0x00efc9e0
int __cdecl FUN_00efc9e0()
{
    return 0;
}

// @ 0x00efca60
int __cdecl FUN_00efca60(char* a)
{
    void* p = *(void**)(*(char**)a + 0x64);
    void* esi = 0;
    if (p != 0)
        esi = ((FN1_i)((*(void***)p)[3]))(p, 0x17f243b);
    if (((FN0_i)((*(void***)esi)[8]))(esi) == 0x2e72cae)
        return 0;
    if (*(char*)(a + 0x20) != 0) {
        if (FUN_00efc530(esi))
            return 0;
    }
    if (*(int*)0x15ad298 == 0x16c7c08) {
        if (FUN_00efc530(esi))
            return 1;
        if (FUN_00f33620(*(void**)((char*)gSimulator + 0x18), 0, esi) == 0)
            return 0;
    }
    return 1;
}

// @ 0x00efcb40
// `this` arrives in ESI in the original (non-standard convention); expressed
// here as a free function taking the pointer. Returns a float in XMM0.

float __cdecl FUN_00efcb40(void* self)
{
    float base = g_1441a88;
    void* eax = FUN_00f3e8a0(*(void**)((char*)gSimulator + 0x74), 0, *(int*)self);
    if (eax != 0) {
        int k = *(int*)((char*)eax + 4);
        if (k == 0x2399be55)      base = g_1477fc0;
        else if (k == 0x24682294) base = g_13ec4d0;
    }
    float soft;
    void* v = FUN_00eeca30(self);
    if (v != 0)
        soft = ((PF_t)((*(void***)v)[0x1c]))(v);
    else
        soft = g_1485720;
    return (g_15ad340 * soft > base) ? (g_15ad340 * soft) : base;
}

// @ 0x00efcbe0
// `this` arrives in ESI in the original; expressed as an explicit first
// parameter. The second (int) argument is the caller's stack argument.
void __cdecl FUN_00efcbe0(void* self, int arg)
{
    void* eax = FUN_0067dd10();
    eax = ((void*(__thiscall*)(void*))((*(void***)eax)[0x14]))(eax);
    eax = ((void*(__thiscall*)(void*))((*(void***)eax)[0xe]))(eax);
    if (eax == 0)
        return;
    void* edi = ((FN1_i)((*(void***)eax)[3]))(eax, 0x11966ed);
    if (edi == 0)
        return;
    float v[3];
    v[0] = ((float*)self)[0];
    v[1] = ((float*)self)[1];
    v[2] = ((float*)self)[2];
    if (g_15ad344 != 0) {
        float outA[3];
        float s1, s2, s3;
        FUN_00eec2b0(outA, v, 0, &s1, 1);
        (void)s2; (void)s3;
        float d1 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
        float d2 = outA[0] * outA[0] + outA[1] * outA[1] + outA[2] * outA[2];
        if (d2 > d1) {
            v[0] = outA[0];
            v[1] = outA[1];
            v[2] = outA[2];
        }
    }
    FUN_00b13bb0(edi, 0, v, arg);
}

// @ 0x00efccd0
void __fastcall FUN_00efccd0(char* p)
{
    (void)p;
}

// @ 0x00efcec0
void __stdcall FUN_00efcec0(int a)
{
    (void)a;
}

// @ 0x00efcfb0
int __cdecl FUN_00efcfb0(char* p)
{
    (void)p;
    return 0;
}
