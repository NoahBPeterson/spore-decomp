// Slice s00f96840 -- SPTerrain/SPTerrainSphere.obj.
// cTerrainSphere plumbing: vtable forwarders, a colour sample, small container helpers
// (insertion sorts, heap sift-up), terrain-map bundle construction, and misc accessors.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <xmmintrin.h>

// ---- addresses used as literals in the original (relocations masked when matching) ----
#define DAT_015b117c (*(int*)(0x015b117c))
#define DAT_015b1180 (*(int*)(0x015b1180))
#define DAT_015b1184 (*(int*)(0x015b1184))
#define DAT_015b1188 (*(int*)(0x015b1188))
#define DAT_015b1200 (*(int*)(0x015b1200))
#define DAT_015b1204 (*(int*)(0x015b1204))
#define DAT_015b1208 (*(int*)(0x015b1208))
#define DAT_015b120c (*(int*)(0x015b120c))
#define DAT_015b1210 (*(int*)(0x015b1210))
#define DAT_015b1214 (*(int*)(0x015b1214))
#define DAT_016c9e68 (*(int**)(0x016c9e68))
#define DAT_016c9e8c (*(float*)(0x016c9e8c))
#define DAT_016c9e90 (*(float*)(0x016c9e90))
#define DAT_016c9e94 (*(float*)(0x016c9e94))

// ---- callees ----
void* __cdecl GetRenderer();                                             // 0x0067dda0
void* __cdecl SP_AppSystem();                                            // 0x0067dd00
void* __cdecl SP_MessageServer();                                        // 0x0067dcc0
void* __cdecl FUN_0067dd50();                                            // 0x0067dd50
void  __fastcall FUN_007c3ba0(void* self);                               // 0x007c3ba0
struct cViewer_s007c_4be0 { bool Init(bool arg); };                      // 0x007c4dd0 ?Init@cViewer_s007c_4be0@@QAE_N_N@Z
void* __cdecl EAAllocate(unsigned int size, const char* name, int, int, int, int);  // 0x00f473a0
void  __fastcall FUN_00f8ee90(void* self);                               // 0x00f8ee90
void  __fastcall FUN_00f8ee70(void* self);                               // 0x00f8ee70
void  __fastcall FUN_00f8eeb0(void* self);                               // 0x00f8eeb0
void  __fastcall FUN_00f8eed0(void* self);                               // 0x00f8eed0
void  __fastcall FUN_00f92170(void* self, int);                          // 0x00f92170
void  __fastcall FUN_00f92140(void* self, int);                          // 0x00f92140
void  __fastcall FUN_00f921a0(void* self, int);                          // 0x00f921a0
void  __fastcall FUN_00f92280(void* self, int);                          // 0x00f92280
void  __fastcall FUN_00f92250(void* self, int);                          // 0x00f92250
void* __fastcall FUN_00f92a50(void* self);                               // 0x00f92a50
void  __fastcall FUN_00f92be0(void* self, int index, void* map);         // 0x00f92be0
void  __fastcall SetSerializer(void* self);                              // 0x00c2e4e0

struct Vec3 { float x, y, z; };
bool __cdecl TerrainRayCast(void* map, float, float, Vec3*, Vec3*, Vec3*);  // 0x00f8e6c0

namespace SP {

class cTerrainSphere
{ public:
    void  m00f96840();
    int   m00f96870();
    int   m00f968b0(char* other);
    void  m00f96a20(int);
    void  m00f96a90(int, int idx, float val);
    void  InitializeStaticRTTTextures();
    bool  m00f96cd0(void* fn, int arg);
    void  m00f96d40();
    void  m00f96f90();
    void  m00f97130();
    Vec3* m00f974d0(Vec3* out, Vec3* p1, Vec3* p2);
    void  m00f97530(int idx, const float* bounds);
    bool  m00f975d0(int value);
    void  m00f97660();
    int   m00f97690(int* out);
    int   m00f976c0(int* a, int* b);
    bool  m00f97700(int value);
    void  m00f97750();
};

}  // namespace SP

using SP::cTerrainSphere;

// @ 0x00f96840
void cTerrainSphere::m00f96840()
{
    (*(void (__thiscall**)(void*))(*(int*)this + 0x70))(this);
    (*(void (__thiscall**)(void*))(*(int*)this + 0x60))(this);
    void* f = *(void**)(*(int*)this + 0x84);
    *(int*)((char*)this + 0x814) = 0;
    ((void (__thiscall*)(void*))f)(this);
}

// @ 0x00f96870
int cTerrainSphere::m00f96870()
{
    char* p = *(char**)((char*)this + 0xfc);
    if (p == 0)
        return 0;
    if (p == (char*)this + 0x30)
        return 1;
    if (p == (char*)this + 0x74)
        return 2;
    return (unsigned)((p != (char*)this + 0xb8) - 1) & 3;
}

// @ 0x00f968b0
int cTerrainSphere::m00f968b0(char* other)
{
    char* a = this ? (char*)this + 4 : 0;
    if ((*(void* (__thiscall**)(char*, int))(*(int*)other + 0x58))(other, 8) == a)
    {
        char* b = this ? (char*)this + 4 : 0;
        if ((*(void* (__thiscall**)(char*, int))(*(int*)other + 0x58))(other, 7) == b)
            return 1;
    }
    return 0;
}

// @ 0x00f96910
int __stdcall FUN_00f96910(int i)
{
    return *((int**)0x016c9e44)[i];
}

// @ 0x00f96920
void __cdecl FUN_00f96920(const unsigned char* data, int w, int h, float u, float v,
                          float* outB, float* outG, float* outR, float* outA)
{
    if (data == 0)
    {
        *outR = 0.5f;
        *outG = 0.5f;
        *outB = 0.5f;
        *outA = 0.5f;
        return;
    }
    float fu = (float)(w - 1) * u;
    float fv = (float)(h - 1) * v;
    int ix, iy;
    __asm {
        cvtss2si eax, dword ptr fu
        mov      ix, eax
        cvtss2si eax, dword ptr fv
        mov      iy, eax
    }
    int index = (iy % h) * w + (ix % w);
    const unsigned char* px = data + index * 4;
    *outB = (float)px[2] * 0.003921569f;
    *outG = (float)px[1] * 0.003921569f;
    *outR = (float)px[0] * 0.003921569f;
    *outA = (float)px[3] * 0.003921569f;
}

// @ 0x00f96a00
int __cdecl FUN_00f96a00()
{
    int* p = DAT_016c9e68;
    return p ? *p : 0;
}

// @ 0x00f96a10
bool __stdcall FUN_00f96a10(int, int, int* out, int)
{
    *out = 0;
    return true;
}

// @ 0x00f96a20
void cTerrainSphere::m00f96a20(int)
{
    char* self = (char*)this;
    *(float*)(self + 0xa10) = 0.0f;
    *(float*)(self + 0xa14) = 0.0f;
    *(float*)(self + 0xa18) = 0.0f;
    *(float*)(self + 0xa1c) = 0.0f;
    *(float*)(self + 0xa20) = 0.0f;
    *(float*)(self + 0xa24) = 0.0f;
    *(float*)(self + 0xa28) = 0.0f;
    *(int*)(self + 0xa2c) = DAT_015b117c;
    *(int*)(self + 0xa30) = DAT_015b1180;
    *(int*)(self + 0xa34) = DAT_015b1184;
    *(int*)(self + 0xa38) = DAT_015b1188;
}

// @ 0x00f96a90
void cTerrainSphere::m00f96a90(int, int idx, float val)
{
    char* self = (char*)this;
    switch (idx)
    {
    case 0: *(float*)(self + 0xa10) = val; return;
    case 1: *(float*)(self + 0xa14) = val; return;
    case 2: *(float*)(self + 0xa18) = val; return;
    case 3: *(float*)(self + 0xa1c) = val; return;
    case 4: *(float*)(self + 0xa20) = val; return;
    case 5: *(float*)(self + 0xa24) = val; return;
    case 6: *(float*)(self + 0xa28) = val; return;
    default: return;
    }
}

struct TexRef { int mHandle; int mIndex; };

// @ 0x00f96b40
void cTerrainSphere::InitializeStaticRTTTextures()
{
    void* r = GetRenderer();
    TexRef local;
    TexRef* t = (TexRef*)(*(void* (__thiscall**)(void*, TexRef*, int, int, int, int, int, int))(*(int*)r + 0x10))
                            (r, &local, 0x100, 0x100, 0x15, 0, 0x5a6f2fee, 0);
    DAT_015b1200 = t->mHandle;
    DAT_015b1204 = t->mIndex;
    (*(void (__thiscall**)(void*, int, int, const char*))(*(int*)r + 0x48))
        (r, t->mHandle, t->mIndex, "TerrainRefractionBuffers");
    DAT_016c9e68 = (int*)(*(void* (__thiscall**)(void*, int, int))(*(int*)r + 0x1c))(r, DAT_015b1200, DAT_015b1204);
    t = (TexRef*)(*(void* (__thiscall**)(void*, TexRef*, int, int, int, int, int, int))(*(int*)r + 0x10))
                     (r, &local, 0x100, 0x100, 0x15, 0, 0x43ec615b, 0);
    DAT_015b1208 = t->mHandle;
    DAT_015b120c = t->mIndex;
    (*(void (__thiscall**)(void*, int, int, const char*))(*(int*)r + 0x48))
        (r, t->mHandle, t->mIndex, "TerrainRefractionBlur1");
    t = (TexRef*)(*(void* (__thiscall**)(void*, TexRef*, int, int, int, int, int, int))(*(int*)r + 0x10))
                     (r, &local, 0x100, 0x100, 0x15, 0, 0x43ec6158, 0);
    DAT_015b1210 = t->mHandle;
    DAT_015b1214 = t->mIndex;
    (*(void (__thiscall**)(void*, int, int, const char*))(*(int*)r + 0x48))
        (r, t->mHandle, t->mIndex, "TerrainRefractionBlur2");
    ((cViewer_s007c_4be0*)0x016ca0d8)->Init(false);
}

// @ 0x00f96c60
void __cdecl FUN_00f96c60()
{
    void* r = GetRenderer();
    FUN_007c3ba0((void*)0x016ca0d8);
    (*(void (__thiscall**)(void*, int, int))(*(int*)r + 0x14))(r, DAT_015b1200, DAT_015b1204);
    (*(void (__thiscall**)(void*, int, int))(*(int*)r + 0x14))(r, DAT_015b1208, DAT_015b120c);
    (*(void (__thiscall**)(void*, int, int))(*(int*)r + 0x14))(r, DAT_015b1210, DAT_015b1214);
    DAT_016c9e68 = 0;
}

// @ 0x00f96cd0
bool cTerrainSphere::m00f96cd0(void* fn, int arg)
{
    char* self = (char*)this;
    if (*(int*)(self + 0xfc) != 0)
    {
        *(void**)(self + 0x100) = fn;
        *(int*)(self + 0x104) = arg;
        return false;
    }
    ((void (__cdecl*)(char*, int))fn)(self, arg);
    return true;
}

// @ 0x00f96d20
bool __cdecl FUN_00f96d20(int, int msg)
{
    if (msg != 0)
    {
        void* s = SP_MessageServer();
        (*(void (__thiscall**)(void*, int, int, int))(*(int*)s + 0x14))(s, msg, 0, 0);
    }
    return true;
}

// @ 0x00f96d40
void cTerrainSphere::m00f96d40()
{
    char* self = (char*)this;
    void* fn = *(void**)(self + 0x100);
    *(int*)(self + 0xfc) = 0;
    if (fn != 0)
    {
        ((void (__cdecl*)(char*, int))fn)(self, *(int*)(self + 0x104));
        *(int*)(self + 0x100) = 0;
        *(int*)(self + 0x104) = 0;
    }
}

// @ 0x00f96d80
void __cdecl FUN_00f96d80(int* begin, int* end)
{
    if (begin == end)
        return;
    for (int* i = begin + 4; i != end; i += 4)
    {
        int v0 = i[0];
        int v1 = i[1];
        unsigned key = (unsigned)i[2];
        int v3 = i[3];
        int* j = i;
        for (; j != begin && key < (unsigned)j[-2]; j -= 4)
        {
            j[0] = j[-4];
            j[1] = j[-3];
            j[2] = j[-2];
            j[3] = j[-1];
        }
        j[0] = v0;
        j[1] = v1;
        j[2] = (int)key;
        j[3] = v3;
    }
}

struct E16 { int v0; int v1; unsigned key; int v3; };

// @ 0x00f96df0
void __cdecl FUN_00f96df0(int* first, int* last)
{
    for (int* i = first; i != last; i += 4)
    {
        E16 val = *(E16*)i;
        int* j = i;
        if (val.key < (unsigned)j[-2])
        {
            do
            {
                j[0] = j[-4];
                j[1] = j[-3];
                j[2] = j[-2];
                j[3] = j[-1];
                j -= 4;
            } while (val.key < (unsigned)j[-2]);
        }
        j[0] = val.v0;
        j[1] = val.v1;
        j[2] = (int)val.key;
        j[3] = val.v3;
    }
}

struct E20 { int a, b, c, d, e; };

// @ 0x00f96e70
void __cdecl FUN_00f96e70(E20* dst, E20* end, const E20* src)
{
    for (; dst != end; ++dst)
        *dst = *src;
}

// @ 0x00f96eb0
void __cdecl FUN_00f96eb0(int* base, int top, int pos, int v0, int v1, unsigned key, int v3)
{
    int parent = (pos - 1) >> 1;
    while (pos > top)
    {
        int* p = base + parent * 4;
        if ((unsigned)p[2] >= key)
            break;
        int* c = base + pos * 4;
        c[0] = p[0];
        c[1] = p[1];
        c[2] = p[2];
        c[3] = p[3];
        pos = parent;
        parent = (pos - 1) >> 1;
    }
    int* c = base + pos * 4;
    c[0] = v0;
    c[1] = v1;
    c[2] = (int)key;
    c[3] = v3;
}

// @ 0x00f96f90
void cTerrainSphere::m00f96f90()
{
    char* self = (char*)this;
    for (int k = 0; k < 6; ++k)
    {
        float* p = (float*)(self + 0x374 + *(int*)(self + 0x36c) * 0x60) + k * 4;
        p[0] = 0.0f;
        p[1] = 0.0f;
        p[2] = 0.0f;
        p[3] = 0.0f;
    }
}

// @ 0x00f97130
void cTerrainSphere::m00f97130()
{
    char* self = (char*)this;
    void* m0 = EAAllocate(0x24, "Terrain/Sphere/HeightMap", 0, 0, 0, 0);
    if (m0) { FUN_00f8ee90(m0); *(int*)m0 = 0x14904d8; }
    FUN_00f92170(m0, 0x200);
    void* m1 = EAAllocate(0x24, "Terrain/Sphere/NormalMap", 0, 0, 0, 0);
    if (m1) { FUN_00f8ee70(m1); *(int*)m1 = 0x14904e0; }
    FUN_00f92140(m1, 0x200);
    void* m2 = EAAllocate(0x24, "Terrain/Sphere/ColorMap", 0, 0, 0, 0);
    if (m2) { FUN_00f8ee70(m2); *(int*)m2 = 0x14904e0; }
    FUN_00f92140(m2, 0x100);
    void* m3 = EAAllocate(0x24, "Terrain/Sphere/ControlMap", 0, 0, 0, 0);
    if (m3) { FUN_00f8eeb0(m3); *(int*)m3 = 0x145fd5c; }
    FUN_00f921a0(m3, 0x100);
    void* m4 = EAAllocate(0x24, "Terrain/Sphere/JetStreamMap", 0, 0, 0, 0);
    if (m4) { FUN_00f8eed0(m4); *(int*)m4 = 0x14904e8; }
    FUN_00f92280(m4, 0x40);
    void* m5 = EAAllocate(0x24, "Terrain/Sphere/PressureMap", 0, 0, 0, 0);
    if (m5) { FUN_00f8ee70(m5); *(int*)m5 = 0x14904e0; }
    FUN_00f92250(m5, 0x40);
    void* m6 = EAAllocate(0x24, "Terrain/Sphere/CloudEmitMap", 0, 0, 0, 0);
    if (m6) { FUN_00f8ee70(m6); *(int*)m6 = 0x14904e0; }
    FUN_00f92250(m6, 0x40);
    void* m7 = EAAllocate(0x24, "Terrain/Sphere/HeightAboveMap", 0, 0, 0, 0);
    if (m7) { FUN_00f8ee70(m7); *(int*)m7 = 0x14904e0; }
    FUN_00f92250(m7, 0x100);
    void* m8 = EAAllocate(0x24, "Terrain/Sphere/WindTempMap", 0, 0, 0, 0);
    if (m8) { FUN_00f8ee70(m8); *(int*)m8 = 0x14904e0; }
    FUN_00f92250(m8, 0x100);
    void* m9 = EAAllocate(0x24, "Terrain/Sphere/FloatTempMap", 0, 0, 0, 0);
    if (m9) { FUN_00f8ee70(m9); *(int*)m9 = 0x14904e0; }
    FUN_00f92250(m9, 0x100);
    void* m10 = EAAllocate(0x24, "Terrain/Sphere/FilteredMap", 0, 0, 0, 0);
    if (m10) { FUN_00f8ee70(m10); *(int*)m10 = 0x14904e0; }
    FUN_00f92250(m10, 0x100);

    void* set = EAAllocate(0x5c, "Terrain/Sphere/cTerrainMapSet", 0, 0, 0, 0);
    if (set) set = FUN_00f92a50(set);
    void* old = *(void**)(self + 0x2c);
    if (set != old)
    {
        if (set)
            ++*(int*)((char*)set + 4);
        *(void**)(self + 0x2c) = set;
        if (old)
        {
            int rc = *(int*)((char*)old + 4) - 1;
            *(int*)((char*)old + 4) = rc;
            if (rc == 0)
            {
                *(int*)((char*)old + 4) = 1;
                (*(void (__thiscall**)(void*, int))(*(int*)old))(old, 1);
            }
        }
    }
    void* ms = *(void**)(self + 0x2c);
    SetSerializer(ms);
    FUN_00f92be0(ms, 0, m0);
    FUN_00f92be0(ms, 1, m1);
    FUN_00f92be0(ms, 2, m2);
    FUN_00f92be0(ms, 3, m3);
    FUN_00f92be0(ms, 4, m4);
    FUN_00f92be0(ms, 5, m5);
    FUN_00f92be0(ms, 6, m6);
    FUN_00f92be0(ms, 7, m7);
    FUN_00f92be0(ms, 8, m8);
    FUN_00f92be0(ms, 9, m9);
    FUN_00f92be0(ms, 10, m10);
}

// @ 0x00f974d0
Vec3* cTerrainSphere::m00f974d0(Vec3* out, Vec3* p1, Vec3* p2)
{
    void* m = *(void**)((char*)this + 0x2c);
    float x = DAT_016c9e8c;
    float y = DAT_016c9e90;
    float z = DAT_016c9e94;
    out->x = x;
    out->y = y;
    out->z = z;
    TerrainRayCast(*(void**)((char*)m + 8), *(float*)((char*)m + 0x34), *(float*)((char*)m + 0x38), p1, p2, out);
    return out;
}

// @ 0x00f97530
void cTerrainSphere::m00f97530(int idx, const float* bounds)
{
    char* self = (char*)this;
    int count = (*(int*)(self + 0x788) - *(int*)(self + 0x784)) / 0xac;
    if (count > 0)
    {
        int off = 0;
        do
        {
            char* e = *(char**)(self + 0x784) + off;
            unsigned flags = *(unsigned*)(e + 0xa4);
            if (((flags >> 0x1b) & 1) == 0)
            {
                float* f = (float*)(e + 0x38 + idx * 16);
                if (f[2] > bounds[0] && bounds[2] > f[0] && f[3] > bounds[1] && bounds[3] > f[1])
                    *(unsigned*)(e + 0xa4) = flags | 0x8000000;
            }
            off += 0xac;
            --count;
        } while (count != 0);
    }
}

// @ 0x00f975d0
bool cTerrainSphere::m00f975d0(int value)
{
    char* self = (char*)this;
    int n1 = (*(int*)(self + 0x788) - *(int*)(self + 0x784)) / 0xac;
    unsigned i = 0;
    if (n1 != 0)
    {
        int* p = (int*)(*(char**)(self + 0x784) + 0xa8);
        do
        {
            if (*p == value)
                return true;
            ++i;
            p += 0x2b;
        } while (i < (unsigned)n1);
    }
    int n2 = (*(int*)(self + 0x774) - *(int*)(self + 0x770)) / 0xac;
    i = 0;
    if (n2 != 0)
    {
        int* p = (int*)(*(char**)(self + 0x770) + 0xa8);
        do
        {
            if (*p == value)
                return true;
            ++i;
            p += 0x2b;
        } while (i < (unsigned)n2);
    }
    return false;
}

// @ 0x00f97660
void cTerrainSphere::m00f97660()
{
    char* self = (char*)this;
    char saved = (*(char**)(self + 0x210))[0xac];
    (*(char**)(self + 0x210))[0xac] = 0;
    (*(void (__thiscall**)(char*))(*(int*)self + 0xac))(self);
    (*(char**)(self + 0x210))[0xac] = saved;
}

// @ 0x00f97690
int cTerrainSphere::m00f97690(int* out)
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7d8) != *(int*)(self + 0x7dc))
    {
        *out = *(int*)(self + 0x7d8);
        return (*(int*)(self + 0x7dc) - *(int*)(self + 0x7d8)) >> 2;
    }
    return 0;
}

// @ 0x00f976c0
int cTerrainSphere::m00f976c0(int* a, int* b)
{
    char* self = (char*)this;
    if (*(int*)(self + 0x7ac) != 0)
    {
        if (a != 0)
            *a = *(int*)(self + 0x7b0);
        if (b != 0)
            *b = *(int*)(self + 0x7c4);
        return *(int*)(self + 0x7ac);
    }
    return 0;
}

// @ 0x00f97700
bool cTerrainSphere::m00f97700(int value)
{
    char* self = (char*)this;
    int n = (*(int*)(self + 0x79c) - *(int*)(self + 0x798)) / 0xac;
    int i = 0;
    if (n > 0)
    {
        int* p = (int*)(*(char**)(self + 0x798) + 0xa8);
        do
        {
            if (*p == value)
                return true;
            ++i;
            p += 0x2b;
        } while (i < n);
    }
    return false;
}

// @ 0x00f97750
void cTerrainSphere::m00f97750()
{
    char* self = (char*)this;
    void* app = SP_AppSystem();
    (*(void (__thiscall**)(void*))(*(int*)app + 0x6c))(app);
    void* o = FUN_0067dd50();
    if ((*(char (__thiscall**)(void*))(*(int*)o + 0x88))(o))
    {
        while (*(char**)(self + 0xfc) != 0)
        {
            char* obj = *(char**)(self + 0xfc);
            if ((*(char (__thiscall**)(char*, char*, int))(*(int*)obj + 4))(obj, self, 0) != 0)
                break;
        }
        o = FUN_0067dd50();
        (*(void (__thiscall**)(void*))(*(int*)o + 0x8c))(o);
    }
    app = SP_AppSystem();
    (*(void (__thiscall**)(void*))(*(int*)app + 0x70))(app);
}
