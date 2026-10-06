// Slice s00ed0b70 -- Scenario::AvatarPaletteItemUI and swatch/item UI glue.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

// ---------------------------------------------------------------- globals
extern void*         g_16c7aa4;      // 0x016c7aa4
extern void*         g_15ac028;      // 0x015ac028 (pointer constant)
extern float         g_15abf5c;      // 0x015abf5c
extern int           g_15ac028i;

// ---------------------------------------------------------------- callees
void* __cdecl FUN_00b3d320(void);                       // 0x00b3d320
void* __cdecl FUN_00b1de80(void);                       // 0x00b1de80
void  __cdecl FUN_006a1400(int, unsigned, void*);       // 0x006a1400
void  __cdecl FUN_005f22f0(float);                      // 0x005f22f0
void  __cdecl FUN_00644b60(void);                       // 0x00644b60
void  __cdecl FUN_00929c60(void);                       // 0x00929c60
void  __cdecl FUN_0092a7a0(int);                        // 0x0092a7a0
void  __cdecl FUN_00929e70(int, int, int, int, int, int, int); // 0x00929e70
void  __cdecl FUN_00929da0(void*, void*, int);          // 0x00929da0
void  __cdecl EA_RemoveHandler(int, int, int, int, int);    // 0x00571db0
void* __stdcall FUN_00ece3f0(int);                      // 0x00ece3f0
void  __fastcall FUN_00ece300(char*);                   // 0x00ece300
void* __cdecl FUN_00f45970(void);                       // 0x00f45970
void* __stdcall FUN_00401020(void*);                    // 0x00401020
void  __fastcall FUN_005f0ca0(void*);                   // 0x005f0ca0
void  __fastcall FUN_005f7380(void*);                   // 0x005f7380
void* __cdecl EA_New(unsigned, const char*, int, int, const char*, int);  // 0x00f473a0
void  __cdecl EA_Free(void*);                           // 0x00f47380
void  __cdecl FUN_00805fe0(float*, int);                // 0x00805fe0
int   __cdecl FUN_005f3060(void);                       // 0x005f3060
int   __cdecl FUN_00efc9c0(void);                       // 0x00efc9c0
void  __fastcall FUN_00ecf150(void*);                   // 0x00ecf150
void  __fastcall FUN_00ecf320(void);                    // 0x00ecf320

typedef void* (__thiscall *FV_1)(void*);
typedef void* (__thiscall *FV_i)(void*, int);
typedef int   (__thiscall *FV_ii)(void*, int, int);
typedef void  (__thiscall *FV_v)(void*);
typedef bool  (__thiscall *FB_i)(void*, int, void*);
struct ILayout { void* FindWindowByID(unsigned, int); };

// ---------------------------------------------------------------- 0x00ed0c30
struct ObjC30 { void f(int, int); };
void ObjC30::f(int a, int b)
{
    (void)a;
    int* p = *(int**)((char*)this + 0x18);
    if (p != 0) {
        char* o = (char*)p + 8;
        char* q = (char*)((FV_i)(*(void***)o)[0xc / 4])(o, 0x722e9c1);
        ((FV_i)(*(void***)(q + 0x24))[0x18 / 4])(q + 0x24, b);
    }
}

// ---------------------------------------------------------------- 0x00ed0c60
struct ObjC60 { unsigned f(unsigned, int*); };
unsigned ObjC60::f(unsigned a, int* b)
{
    if (a == 0x30c11c7) {
        if (*(char*)((char*)this + 4) != 0) {
            int* old = *(int**)((char*)this + 0x2c);
            if (b != old) {
                if (b) ((FV_v)(*(void***)b)[4 / 4])(b);
                *(int**)((char*)this + 0x2c) = b;
                if (old) ((FV_v)(*(void***)old)[8 / 4])(old);
            }
        }
    } else if (a == 0x72bdb11) {
        ((FV_v)(*(void***)(*(int**)((char*)this + 0x10)))[0x14 / 4])(*(int**)((char*)this + 0x10));
        return 0;
    }
    return 0;
}

// ---------------------------------------------------------------- 0x00ed0cc0
void* __stdcall FUN_00ed0cc0(char flag)
{
    if (flag != 0)
        return g_15ac028;
    return (void*)FUN_00ece3f0(0);
}

// ---------------------------------------------------------------- 0x00ed12d0
struct Obj12D0 { void f(int); };
void Obj12D0::f(int a)
{
    if (a == -2)
        ((FV_v)(*(void***)this)[0x14 / 4])(this);
}

// ---------------------------------------------------------------- 0x00ed1350
void FUN_00ed1350(int* p, int arg)
{
    if (p != 0) {
        char* q = (char*)((FV_i)(*(void***)p)[0xc / 4])(p, 0x8ed27e7a);
        if (q != 0)
            ((FV_ii)(*(void***)q)[0x28 / 4])(q, 4, arg);
    }
}

// ---------------------------------------------------------------- 0x00ed1500
unsigned char FUN_00ed1500(void)
{
    return *(unsigned char*)(*(int*)(*(int*)((char*)g_16c7aa4 + 0x74) + 0x10) + 0x14c);
}

// ---------------------------------------------------------------- 0x00ed1250
void* __fastcall FUN_00ed1250(void* self)
{
    char* p = (char*)self;
    FUN_00ecf150(self);
    *(void**)p = (void*)0x1489a50;
    *(void**)(p + 8) = (void*)0x1489a3c;
    *(void**)(p + 0x24) = (void*)0x1489a0c;
    *(void**)(p + 0x30) = (void*)0x14899f0;
    *(void**)(p + 0x34) = (void*)0x14899e0;
    *(void**)(p + 0x44) = (void*)0x14897d0;
    *(void**)(p + 0x6c) = (void*)0x1489960;
    *(void**)(p + 0x70) = (void*)0x1489948;
    *(int*)(p + 0x10) = (int)0xfffffffe;
    *(int*)(p + 0x14) = (int)0xe34e8a60;
    return self;
}

// ---------------------------------------------------------------- 0x00ed14c0
struct Obj14C0 { void f(int*); };
void Obj14C0::f(int* param)
{
    int* p = *(int**)((char*)this + 0x4c);
    if (p != 0) {
        ((FV_i)(*(void***)p)[0x24 / 4])(p, (int)param);
        FUN_00ece300((char*)this);
    }
    *(int*)((char*)this + 0x18) = param[0];
    *(int*)((char*)this + 0x1c) = param[1];
    *(int*)((char*)this + 0x20) = param[2];
}

// ---------------------------------------------------------------- 0x00ed1460
void FUN_00ed1460(void)
{
    char* p = (char*)EA_New(0x1c8, "Editor", 0, 0, 0, 0);
    if (p != 0) {
        FUN_005f7380(p);
        *(void**)p = (void*)0x1489aa0;
        *(void**)(p + 4) = (void*)0x13f9ea4;
        *(void**)(p + 0xc) = (void*)0x1489590;
        void* q = FUN_00401020(p);
        FUN_005f0ca0(q);
    } else {
        void* q = FUN_00401020(0);
        FUN_005f0ca0(q);
    }
}

// ---------------------------------------------------------------- 0x00ed1380
bool __fastcall FUN_00ed1380(void* self)
{
    if (FUN_005f3060() == 0)
        return false;
    float bounds[2];
    FUN_00805fe0(bounds, *(int*)((char*)self + 0x18c));
    if ((*(float*)((char*)self + 0x84) <= bounds[1] && bounds[1] != *(float*)((char*)self + 0x84)) ||
        (*(float*)((char*)self + 0x88) <= bounds[0] && bounds[0] != *(float*)((char*)self + 0x88))) {
        if (FUN_00efc9c0() != 0)
            return true;
    }
    return false;
}

// ---------------------------------------------------------------- 0x00ed13e0
bool __fastcall FUN_00ed13e0(void* self, int param)
{
    char* w = (char*)((ILayout*)*(void**)((char*)self + 0x50))->FindWindowByID(param, 1);
    if (w == 0)
        return false;
    char* q = (char*)((FV_i)(*(void***)w)[0xf0 / 4])(w, 0x665fe90);
    if (q == 0)
        return false;
    float* f = (float*)((FV_1)(*(void***)q)[0x38 / 4])(q);
    ((FV_ii)(*(void***)w)[0x74 / 4])(w, (int)((f[2] - f[0]) * 0.0f), (int)(f[3] - f[1]));
    return true;
}

// ---------------------------------------------------------------- stubs (incomplete)
void FUN_00ed0b70(void) {}
void FUN_00ed0ce0(void) {}
void FUN_00ed1030(void) {}
void FUN_00ed10b0(void) {}
void FUN_00ed1120(void) {}
void FUN_00ed1180(void) {}
void FUN_00ed1550(void) {}
