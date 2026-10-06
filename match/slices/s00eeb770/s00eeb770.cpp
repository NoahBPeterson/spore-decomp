// slice s00eeb770 -- adviser / planet-surface helpers: a refcounted-list removal, two vector
// copies, a large message handler, and small surface-position accessors.
//
// Complex members use a `__fastcall`-wrapper convention (ecx = this).  The very large
// message handler 0x00eeba40 is a PARTIAL skeleton.
#include "types.h"

struct Vec3 { float x, y, z; };
struct Vec3i { int x, y, z; };

struct Manager {
    int   FUN_00f3be30();
    void* FUN_00f3d780(int a);
    void* FUN_00f3bcb0();
    void* FUN_00f3e8a0(int key);
};
struct GlobalObj {
    char pad0[0x74];
    Manager* f74;
};
extern GlobalObj* g_16c7aa4;
extern int* g_016c7a24;
extern int  g_016c7a28;
extern int  g_016c7a58;

// __fastcall wrappers for direct __thiscall helpers
void  __fastcall FUN_00e26de0(void*, int, int, int);
void* __fastcall FUN_00b7e500(void*, int);
void  __cdecl     FUN_00b65b10(float* a, int b, int c, int d, int e, float* out);
void  __fastcall  FUN_00c9ff40(void*, int, void* a, void* b);
void  __cdecl     FUN_00f28b80(void* a);
void  __cdecl     FUN_00ed1350(int a, int b);
void  __cdecl     FUN_00ed8a30(int a, int b);
void  __cdecl     operator_delete(void* p);
void  __cdecl     FUN_00e1c7f0(void* a, void* b);       // ? placeholder
void* __cdecl     FUN_005bf860(void* a, int b);
void  __cdecl     FUN_005bf120(void* a, void* b, int c, int d);
bool  __cdecl     FUN_008d3200(int a, int b);
void* __cdecl     operator_new(unsigned size, const char* file, int line, int a, int b, int c);
void* __cdecl     SP_PlanetModel();
void* __cdecl     SP_MessageServer();
void* __cdecl     SP_WindowManager();
void* __cdecl     SP_normalized_safe(void* out, float* v);
void* __cdecl     FUN_00f3e8a0_free(int key);
bool  __cdecl     FUN_00ecb6b0();
float __fastcall  FUN_00b7e390(void*, int);   // GetWaterHeight (__thiscall wrapper)
extern "C" double sqrt(double);

// ===========================================================================
// @ 0x00eebf80   int -> [p+0x18] (tail call)
// ===========================================================================
struct XGet { int Get18(); };
int __cdecl f_00eebf80(XGet* p)
{
    if (p == 0)
        return 0;
    return p->Get18();
}

// ===========================================================================
// @ 0x00eebf90
// ===========================================================================
void __cdecl f_00eebf90(int p1, int p2)
{
    FUN_005bf860((void*)p1, p2);
    FUN_005bf120((void*)(p1 + 8), (void*)p1, 0, 0);
}

// ===========================================================================
// @ 0x00eec0d0
// ===========================================================================
void __cdecl f_00eec0d0(int p)
{
    Manager* m = g_16c7aa4->f74;
    m->FUN_00f3d780(p);
}

// ===========================================================================
// @ 0x00eec540
// ===========================================================================
void __cdecl f_00eec540(int p)
{
    int n = g_016c7a28;
    for (int i = 0; i < n; ++i) {
        if (g_016c7a24[i] > p)
            break;
    }
}

// ===========================================================================
// @ 0x00eec580
// ===========================================================================
int __cdecl f_00eec580(int p)
{
    if (p <= 0)
        return 0;
    int n = g_016c7a28;
    while (p > n) {
        p = n;
        if (p <= 0)
            return 0;
    }
    return g_016c7a24[p - 1];
}

// ===========================================================================
// @ 0x00eec3d0   Vec3i by value (sret)
// ===========================================================================
Vec3i __cdecl f_00eec3d0(int* in)
{
    Vec3i out;
    out.x = 0; out.y = 0; out.z = 0;
    if (in != 0) {
        if (*in == -2) {
            Vec3i* p = (Vec3i*)g_16c7aa4->f74->FUN_00f3bcb0();
            out.x = p->x; out.y = p->y; out.z = p->z;
            return out;
        }
        Vec3i* p = (Vec3i*)g_16c7aa4->f74->FUN_00f3e8a0(*in);
        if (p != 0) {
            out.x = p->x; out.y = p->y; out.z = p->z;
        }
    }
    return out;
}

// ===========================================================================
// @ 0x00eec2b0   float surface-scaled direction
// ===========================================================================
// @ 0x00eec0f0
float __cdecl f_00eec0f0(float* dir, char a2, int* out, char a4);
float __cdecl f_00eec2b0(float* out, float* dir, int a3, int* flag, int a5)
{
    float h = f_00eec0f0(dir, (char)a3, flag, (char)a5);
    void* pm = SP_PlanetModel();
    float wh = FUN_00b7e390(pm, 0);
    if (h < wh) {
        *flag = 4;
        h = wh;
    }
    float x = dir[0], y = dir[1], z = dir[2];
    float inv = 1.0f / (float)sqrt((double)(x * x + y * y + z * z));
    out[0] = (x * inv) * h;
    out[1] = (y * inv) * h;
    out[2] = (z * inv) * h;
    return h;
}

// ===========================================================================
// @ 0x00eec370
// ===========================================================================
float __cdecl f_00eec370(float* dir, int a2, int a3)
{
    float local[3];
    f_00eec2b0(local, dir, a2, (int*)a3, 1);
    float d1 = (float)sqrt((double)(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]));
    float d0 = (float)sqrt((double)(local[0] * local[0] + local[1] * local[1] + local[2] * local[2]));
    return d1 - d0;
}

// ===========================================================================
// @ 0x00eec440
// ===========================================================================
void __cdecl f_00eec440(int* param_1)
{
    void* a = g_16c7aa4->f74->FUN_00f3d780(*param_1);
    if (a == 0)
        return;
    // query interface / handle to a physics object; then orient and scale
    void* obj = 0;              // **(code**)(*a + 0xc)(0x1186577)
    if (obj == 0)
        return;
    void* body = g_16c7aa4->f74->FUN_00f3e8a0(*param_1);
    if (body == 0)
        return;
    // ... gated on FUN_00f25680(body) and (*obj+0xb8)(0x137e8e0); then
    //     extract/scale a direction into param_1+1.. and write param_1[0x88].
}

// ===========================================================================
// @ 0x00eec540/580 above; large handlers below are PARTIAL.
// ===========================================================================

// ===========================================================================
// @ 0x00eeb770   remove matching entries from a refcounted list (PARTIAL body)
// ===========================================================================
struct CCList {
    char pad0[0x3c];
    int** begin;             // +0x3c
    int** end;               // +0x40
};
void __fastcall f_00eeb770(CCList* c, int dummy, int param_2, char param_3)
{
    (void)dummy; (void)c; (void)param_2; (void)param_3;
    // Walks [c+0x3c,c+0x40), calls vtable slot 0x24 on each entry, removes entries whose
    // byte +0x2c is set (vtable slot 0x20 first), then re-syncs the UI.  Not transcribed.
}

// ===========================================================================
// @ 0x00eeb920   copy list contents into two output vectors (PARTIAL body)
// ===========================================================================
void __fastcall f_00eeb920(CCList* c, int dummy, void* out1, void* out2)
{
    (void)dummy; (void)c; (void)out1; (void)out2;
    // Clears [c+0x3c..0x40), appends element fields to two vectors.  Not transcribed.
}

// ===========================================================================
// @ 0x00eeba40   large message handler (PARTIAL skeleton)
// ===========================================================================
bool __fastcall f_00eeba40(void* self, int dummy, int msg)
{
    (void)dummy; (void)self; (void)msg;
    // ~1.3 KB switch over message ids (0x287259f6 and 6..0xd) driving Begin2D/End2D,
    // window creation and surface-position queries.  Not transcribed.
    return false;
}

// ===========================================================================
// @ 0x00eebfc0   vector reserve + find (PARTIAL body)
// ===========================================================================
bool __cdecl f_00eebfc0(int param_1, int* param_2)
{
    (void)param_1; (void)param_2;
    // eastl::vector<EA::AutoRefCount<SP::cMWModel>,sp_vector_allocator>::reserve(...),
    // then linear search for a matching 3-int key.  Not transcribed.
    return false;
}

// ===========================================================================
// @ 0x00eec0f0   surface position / radius (PARTIAL body)
// ===========================================================================
float __cdecl f_00eec0f0(float* dir, char a2, int* out, char a4)
{
    (void)dir; (void)a2; (void)out; (void)a4;
    // cPlanetModel::DirectionToSurfacePosition / GetRadiusAt plus a FUN_00b65b10 ray query;
    // the ~440-byte x87 body is not transcribed.
    return 0.0f;
}
