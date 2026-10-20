// Slice s00b66aa0 -- collision ray queries against entities / the physics world, plus the
// hash -> material-flag tables and a couple of small UI helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The three big query entry points (00b66aa0, 00b66b20, 00b66ed0, 00b672e0) call internal
// helpers through a register-based ABI that a normal C++ declaration cannot reproduce; those
// are reconstructed semantically (see nonmatching.txt).

#include "types.h"
#include <intrin.h>

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef void* (__stdcall *TlsGetValueFn)(u32);
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(u32);

// ---------------------------------------------------------------------------
// small external helpers
// ---------------------------------------------------------------------------
struct HkT { void FUN_0107db10(void* ptr, u32 size, u32 align); };

// hkMemory::s_instance (+0x16e4178): vtable slot 4 (0x10) = allocate(size, align).
typedef void* (__thiscall *HkAllocFn)(void*, u32, u32);
// hkThreadMemory::deallocateChunk
typedef void (__thiscall *HkDeallocFn)(void*, void*, u32, u32);

// hkShape ray / collision helpers.
typedef float*       (__thiscall *GetAabbFn)(void*);
typedef void*        (__thiscall *GetTransformFn)(void*, void*);
typedef unsigned int (__thiscall *ShapeIndexFn)(void*);
typedef void         (__thiscall *ShapeDtorFn)(void*, int);

struct XYZW { float x, y, z, w; };

// A hit result / C103 record: status at +0, position at +0x10, optional outputs at
// +0x20 (normal) and +0x24 (distance), user data at +0x28, entity at +0x2c.
struct C103 {
    int    m_status;      // +0x00
    u32    m_pad04[3];
    float  m_pos[4];      // +0x10
    float* m_normalOut;   // +0x20
    float* m_distOut;     // +0x24
    u32    m_userData;    // +0x28
    void*  m_entity;      // +0x2c

    void m655f0(C103* other);   // 0x00b655f0 copy hit record
};

// ---------------------------------------------------------------------------
// Havok world query types (real methods, not vtable-slot guesses)
// ---------------------------------------------------------------------------
struct HkWorld {
    void castRay(void* input, void* collector);   // 0x01082990
};

struct HkAllRayHitCollector {
    void sortHits();                              // 0x010cc160
};

struct D961 {
    int* Find(int* result, int);                  // 0x00496140
};

// hkWorld::castRay input block (0x20 bytes).
struct RayInput {
    XYZW from;      // +0x00
    XYZW to;        // +0x10
    u8   enable;    // +0x20
    u8   pad[3];
    u32  filter;    // +0x24
};

// hkClosestRayHitCollector.
struct ClosestHitCollector {
    void* vt;              // +0x00
    u32   earlyOut;        // +0x04
    u32   pad08[2];        // +0x08
    float normal[4];       // +0x10
    u32   pad20;           // +0x20
    float hitFraction;     // +0x24
    u32   pad28[2];        // +0x28
    void* rootCollidable;  // +0x30
};

// hkAllRayHitCollector: 8 inline entries at +0x20, stride 0x30.
struct HitEntry {
    float normal[4];       // +0x00
    u32   pad10;           // +0x10
    float hitFraction;     // +0x14
    u32   pad18;           // +0x18
    u32   pad1c;           // +0x1c
    void* collidable;      // +0x20
    u32   pad24[3];        // +0x24
};

struct AllHitsCollector {
    void*      vt;         // +0x00
    u32        pad04;      // +0x04
    u32        pad08[2];   // +0x08
    HitEntry*  data;       // +0x10
    int        size;       // +0x14
    int        flags;      // +0x18
    u32        pad1c;      // +0x1c
    HitEntry   inlineHits[8];  // +0x20
};

struct RayPredicate {
    virtual char accept(void* hit);   // vtable slot 0
};

void* __cdecl FUN_00b53940(u32);
void  __cdecl FUN_00b65710(float* out, float* in);
void  __cdecl FUN_00b665c0(u32, u32, C103* out);
void  __cdecl FUN_00b66460(u32, u32, u32, u32, u32, C103* out);
void  __cdecl FUN_00b66740(u32, void*, u32, C103*);
void  __cdecl FUN_00b66ed0(const float*, void*, u32, C103* out);
void  __cdecl FUN_00b65660(C103* a, C103* b, C103* dst);
void* __fastcall FUN_010c3770(void* mem, int, float radius);

// ===========================================================================
// @ 0x00b66aa0
// ===========================================================================
// Ray query wrapper: run the entity/world query (b665c0/b66460) into a scratch C103 and merge
// the best hit into *out.
void __cdecl FUN_00b66aa0(u32 ray, u32 obj, u32 a, u32 b, u32 filter, C103* out)
{
    C103 hit;
    float normal[4];
    float dist;

    hit.m_status = 0;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = normal;

    FUN_00b665c0(ray, obj, out);
    FUN_00b66460(ray, a, b, filter, 6, &hit);

    // Inlined C103::FUN_00b659f0 (the original passes its two C103 pointers and the ray in
    // ecx/eax/edi, a register ABI C++ cannot spell): keep the closer of `out` and `hit`, and
    // when both missed accept `out` only if it lies within the ray's [pt[5], pt[4]] range.
    C103* src = out;
    C103* other = &hit;
    float* pt = (float*)ray;
    if (src->m_status == 0) {
        if (other->m_status != 0) {
            out->m655f0(other);
            return;
        }
    } else if (other->m_status != 0) {
        float m0 = src->m_pos[0] * src->m_pos[0] + src->m_pos[1] * src->m_pos[1] +
                   src->m_pos[2] * src->m_pos[2];
        float m1 = other->m_pos[0] * other->m_pos[0] + other->m_pos[1] * other->m_pos[1] +
                   other->m_pos[2] * other->m_pos[2];
        if (m0 <= m1) {
            out->m655f0(other);
            return;
        }
        out->m655f0(src);
        return;
    }
    if (src->m_status != 0) {
        float dz = src->m_pos[2] - pt[2];
        float dx = src->m_pos[0] - pt[0];
        float dy = src->m_pos[1] - pt[1];
        float n[4];
        FUN_00b65710(n, pt);
        float dot = (n[0] * dx + n[1] * dy) + n[2] * dz;
        if (pt[4] >= dot && dot >= pt[5]) {
            out->m655f0(src);
            return;
        }
    }
    out->m_status = 0;
}

// ===========================================================================
// @ 0x00b66b20
// ===========================================================================
// Place a sphere of half the target's largest AABB extent on its centre and dispatch a
// collision pair query against the shape stored on the entity behind `id`.
char __cdecl FUN_00b66b20(u32 id, void* shapeOwner, u32 filterInfo)
{
    void* found = FUN_00b53940(id);
    if (!found)
        return 0;
    void* other = *(void**)((char*)found + 0x1c);
    if (!other)
        return 0;

    float* box = ((GetAabbFn)(*(void***)shapeOwner)[0x68 / 4])(shapeOwner);
    float extent = box[3] - box[0];
    if (box[4] - box[1] > extent)
        extent = box[4] - box[1];
    if (box[5] - box[2] > extent)
        extent = box[5] - box[2];
    float radius = extent * 0.5f;

    void* gMem = *(void**)0x16e4178;
    void* mem = ((HkAllocFn)(*(void***)gMem)[0x10 / 4])(gMem, 0x10, 0x24);
    *(u16*)((char*)mem + 4) = 0x10;
    void* shape = FUN_010c3770(mem, 0, radius);

    float m[16];
    ((GetTransformFn)(*(void***)shapeOwner)[0x6c / 4])(shapeOwner, m);
    XYZW centre;
    centre.x = (m[3] + m[0]) * 0.5f;
    centre.y = (m[7] + m[4]) * 0.5f;
    centre.z = (m[11] + m[8]) * 0.5f;

    float world[16];
    world[0] = 1.0f;  world[1] = 0.0f;  world[2] = 0.0f;   world[3] = 0.0f;
    world[4] = 0.0f;  world[5] = 1.0f;  world[6] = 0.0f;   world[7] = 0.0f;
    world[8] = 0.0f;  world[9] = 0.0f;  world[10] = 1.0f;  world[11] = 0.0f;
    world[12] = centre.x; world[13] = centre.y; world[14] = centre.z; world[15] = 0.0f;

    char* physics = *(char**)0x167ecd0;
    void* hkWorld = *(void**)(physics + 0x80);

    int i0 = ((ShapeIndexFn)(*(void***)shape)[2])(shape);
    int i1 = ((ShapeIndexFn)(*(void***)other)[2])(other);
    u8 type = *(u8*)((char*)hkWorld + i1 * 0x20 + i0 + 400);
    void* dispatch = *(void**)((char*)hkWorld + 0x994 + type * 0x14);

    // two collidable/shape-instance records handed to the collision dispatcher
    char recA[0x20];
    *(void**)(recA + 0x00) = other;
    *(int*)(recA + 0x04) = -1;
    *(void**)(recA + 0x08) = (char*)*(void**)((char*)found + 0x58) + 0x10;
    *(int*)(recA + 0x0c) = 0;
    *(int*)(recA + 0x10) = 0;
    recA[0x14] = 0;
    recA[0x15] = (char)-0x14;         // self-relative offset of the record
    *(int*)(recA + 0x18) = 0;
    *(int*)(recA + 0x1c) = 0;

    char recB[0x2c];
    *(void**)(recB + 0x00) = shape;
    *(int*)(recB + 0x04) = -1;
    *(void**)(recB + 0x08) = world;
    *(int*)(recB + 0x0c) = 0;
    *(int*)(recB + 0x10) = 0;
    recB[0x14] = 0;
    recB[0x15] = (char)-0x14;
    *(int*)(recB + 0x18) = 0;
    *(void**)(recB + 0x24) = hkWorld;
    void* filter = *(void**)(physics + 0x7c);
    *(void**)(recB + 0x28) = filter ? (char*)filter + 0xc : 0;

    struct QueryResult { XYZW p; u32 k10; u32 k14; char hit; char pad[3]; u32 k1c; };
    QueryResult res;
    res.k10 = 0;
    res.k14 = 0;
    res.hit = 0;
    res.k1c = 0;
    res.p.x = 0; res.p.y = 0; res.p.z = 0; res.p.w = 0;
    res.p.w = *(float*)&filterInfo;

    ((void(__cdecl*)(void*, void*, void*, void*))dispatch)(&res.p, recA, recB, &res);

    if (*(u16*)((char*)shape + 4) != 0) {
        if (--*(u16*)((char*)shape + 6) == 0)
            ((ShapeDtorFn)(*(void***)shape)[0])(shape, 1);
    }
    return (char)(res.hit + 1);
}

// ===========================================================================
// @ 0x00b66e40
// ===========================================================================
// All-hits collector: base collector, inline 8-entry hit array, header { data, size, flags }.
struct Collector {
    void* DeletingDtor(char flag);
};

void* __fastcall Collector_DeletingDtor(void* self, int, char flag);

void* __fastcall FUN_00b66e40(void* self)
{
    *(void**)self = (void*)0x146494c;
    *(void**)((char*)self + 0x10) = (char*)self + 0x20;
    *(u32*)((char*)self + 0x18) = 0x80000008;
    char* e = (char*)self + 0x20;
    for (int i = 0; i < 8; ++i) {
        *(float*)(e + 0x14) = 1.0f;
        *(u32*)(e + 0x20) = 0;
        e += 0x30;
    }
    *(u32*)((char*)self + 0x14) = 0;
    *(float*)((char*)self + 4) = 1.0f;
    return self;
}

// ===========================================================================
// @ 0x00b66ed0
// ===========================================================================
// Closest radial hit: either a shape query through the world's collision filter, or the
// all-hits collector followed by a user predicate that picks the first accepted hit.
void __cdecl FUN_00b66ed0(const float* ray, void* world, u32 filterInfo, C103* out)
{
    RayInput in;
    in.from.x = ray[0];
    in.from.y = ray[1];
    in.from.z = ray[2];
    in.from.w = ray[3];
    float len = ray[8];
    in.to.x = ray[4] * len + in.from.x;
    in.to.y = ray[5] * len + in.from.y;
    in.to.z = ray[6] * len + in.from.z;
    in.to.w = ray[7] * len + in.from.w;
    in.enable = 0;
    in.filter = filterInfo;

    void* predicate = (void*)(unsigned)((const u32*)ray)[9];
    if (predicate == 0) {
        // Closest-hit collector: no heap allocation, root collidable at +0x30.
        ClosestHitCollector c;
        c.vt = (void*)0x1464944;
        c.earlyOut = 0x3f800000;
        c.normal[0] = 0.0f;
        c.pad20 = 0;
        c.rootCollidable = 0;
        c.hitFraction = 1.0f;
        ((HkWorld*)world)->castRay(&in, &c);
        float frac = c.hitFraction;
        void* collidable = c.rootCollidable;
        if (!collidable) {
            out->m_status = 0;
            return;
        }
        out->m_status = 3;
        if (out->m_distOut)
            *out->m_distOut = frac * ray[8];
        if (out->m_normalOut) {
            out->m_normalOut[0] = c.normal[0];
            out->m_normalOut[1] = c.normal[1];
            out->m_normalOut[2] = c.normal[2];
            out->m_normalOut[3] = c.normal[3];
        }
        float s = 1.0f - frac;
        out->m_pos[0] = frac * in.to.x + s * in.from.x;
        out->m_pos[1] = frac * in.to.y + s * in.from.y;
        out->m_pos[2] = frac * in.to.z + s * in.from.z;
        out->m_pos[3] = frac * in.to.w + s * in.from.w;
        if (*(u8*)((char*)collidable + 0x18) == 1) {
            void* ent = (char*)collidable + *(int*)((char*)collidable + 0x10);
            if (ent) {
                int local[2];
                if (*((D961*)ent)->Find(local, 0) == 3)
                    out->m_userData = *(u32*)((char*)ent + 0xc);
            }
        }
        return;
    }

    // All-hits collector: sort, then let the caller's predicate accept the first hit.
    AllHitsCollector c;
    FUN_00b66e40(&c);
    ((HkWorld*)world)->castRay(&in, &c);
    if (c.size == 0) {
        out->m_status = 0;
    } else {
        ((HkAllRayHitCollector*)&c)->sortHits();
        int n = c.size;
        out->m_status = 0;
        for (int i = 0; i < n; ++i) {
            HitEntry* e = &c.data[i];
            if (!((RayPredicate*)predicate)->accept(e))
                continue;
            out->m_status = 3;
            float frac = e->hitFraction;
            if (out->m_distOut)
                *out->m_distOut = frac * ray[8];
            if (out->m_normalOut) {
                out->m_normalOut[0] = e->normal[0];
                out->m_normalOut[1] = e->normal[1];
                out->m_normalOut[2] = e->normal[2];
                out->m_normalOut[3] = e->normal[3];
            }
            float s = 1.0f - frac;
            out->m_pos[0] = frac * in.to.x + s * in.from.x;
            out->m_pos[1] = frac * in.to.y + s * in.from.y;
            out->m_pos[2] = frac * in.to.z + s * in.from.z;
            out->m_pos[3] = frac * in.to.w + s * in.from.w;
            void* collidable = e->collidable;
            if (*(u8*)((char*)collidable + 0x18) == 1) {
                void* ent = (char*)collidable + *(int*)((char*)collidable + 0x10);
                if (ent) {
                    int local[2];
                    if (*((D961*)ent)->Find(local, 0) == 3)
                        out->m_userData = *(u32*)((char*)ent + 0xc);
                }
            }
            break;
        }
    }
    if (c.flags >= 0) {
        void* tls = ((TlsGetValueFn)*(void**)0x13cc2bc)(*(u32*)0x16e4174);
        ((HkT*)tls)->FUN_0107db10(c.data, (c.flags & 0x3fffffff) * 0x30, 0x14);
    }
}

// ===========================================================================
// @ 0x00b672e0
// ===========================================================================
void __cdecl FUN_00b672e0(u32 ray, u32 obj, u32 world, C103* out)
{
    C103 hit;
    float normal[4];
    float dist;

    hit.m_status = 0;
    hit.m_normalOut = 0;
    hit.m_distOut = 0;
    hit.m_userData = 0;
    hit.m_entity = 0;
    if (out->m_distOut)
        hit.m_distOut = &dist;
    if (out->m_normalOut)
        hit.m_normalOut = normal;

    FUN_00b66740(ray, (char*)ray + 0x10, obj, out);
    FUN_00b66ed0((const float*)ray, (void*)world, 6, &hit);
    FUN_00b65660(out, &hit, out);
}

// ===========================================================================
// @ 0x00b67360
// ===========================================================================
void* __fastcall Collector_DeletingDtor(void* self, int, char flag)
{
    *(void**)self = (void*)0x146494c;
    _ReadWriteBarrier();
    u32 n = *(u32*)((char*)self + 0x18);
    if ((int)n >= 0) {
        n &= 0x3fffffff;
        void* tls = TlsGetValue(*(u32*)0x16e4174);
        ((HkT*)tls)->FUN_0107db10(*(void**)((char*)self + 0x10), n * 0x30, 0x14);
    }
    *(void**)self = (void*)0x14613b8;
    if (flag & 1)
        operator delete(self);
    return self;
}

// ===========================================================================
// @ 0x00b673c0
// ===========================================================================
typedef int (__thiscall *HashFn)(void*);

bool __cdecl FUN_00b673c0(void* obj)
{
    int h = ((HashFn)(*(void***)obj)[0x38 / 4])(obj);
    switch (h) {
    case 0x0436f315:
    case 0x0116d858:
    case 0xb033b403:
    case 0xd0036e08:
    case 0x00ee02c7:
    case 0x0137e8e0:
    case 0x01a55e4d:
    case 0x01b92b27:
    case 0x1007ae63:
    case 0x04e3faaf:
    case 0x0ecade42:
    case 0x0ff10521:
    case 0x4f176642:
    case 0x4f396a66:
        return true;
    }
    return false;
}

// ===========================================================================
// @ 0x00b67440
// ===========================================================================
// Set the icon tint: alpha 0 hides the icon, otherwise alpha*255 goes into the top byte of
// the RGBA colour and the icon is shown again.
void __cdecl FUN_00b67440(u32 color, float alpha, void* self)
{
    void*** vt = (void***)self;
    if (alpha == 0.0f) {
        ((void(__thiscall*)(void*, int, int))(*vt)[0x7c / 4])(self, 1, 0);
        return;
    }
    u32 rgba;
    if (color == 0) {
        rgba = ((u32)(int)(alpha * 255.0f) << 24) | 0xffffff;
    } else {
        rgba = ((u32)(int)(alpha * 255.0f) << 24) |
               (*(u32(__cdecl**)(u32))0x00458a40)(color) & 0xffffff;
    }
    ((void(__thiscall*)(void*, u32))(*vt)[0x5c / 4])(self, rgba);
    ((void(__thiscall*)(void*, int, int))(*vt)[0x7c / 4])(self, 1, 1);
}

// ===========================================================================
// @ 0x00b674d0
// ===========================================================================
int __cdecl FUN_00b674d0(u32 mode)
{
    switch (mode) {
    case 0: return -1;
    case 1: return 5;
    case 2: return 1;
    case 3: return 2;
    case 4: return 3;
    case 5: return 0;
    case 6: return 4;
    }
    return -1;
}

// ===========================================================================
// @ 0x00b67530
// ===========================================================================
int __cdecl FUN_00b67530(u32 mode, char flag)
{
    if (flag != 0)
        return 7;
    switch (mode) {
    case 0: return -1;
    case 1: return 2;
    case 2: return 1;
    case 3: return 3;
    case 4: return 4;
    case 5: return 0;
    case 6: return 5;
    case 7: return 6;
    }
    return -1;
}

// ===========================================================================
// @ 0x00b675a0
// ===========================================================================
int __cdecl FUN_00b675a0(u32 mode)
{
    switch (mode) {
    case 7: return 0;
    case 1: return 2;
    case 8: return 3;
    case 3: return 4;
    case 2: return 5;
    case 5: return 6;
    case 6: return 7;
    case 4: return 8;
    case 9: return 9;
    default: return -1;
    }
}

// ===========================================================================
// @ 0x00b67610
// ===========================================================================
int __cdecl FUN_00b67610(int key)
{
    switch (key) {
    case 0xd0036e08: return 1;
    case 0xb033b403: return 0x40;
    case 0x0137e8e0: return 4;
    case 0x00ee02c7: return 8;
    case 0x0116d858: return 8;
    case 0x0ff10521: return 0x10;
    case 0x0ecade42: return 0x10;
    case 0x01a55e4d: return 0x10;
    case 0x1007ae63: return 0x10;
    case 0x0436f315: return 0x20;
    case 0x4f176642: return 2;
    }
    return 0;
}

// ===========================================================================
// @ 0x00b676a0
// ===========================================================================
void __cdecl FUN_00b676a0(void)
{
    char* p = *(char**)0x1687348;
    if (p)
        p[0x30] = (char)(p[0x30] == 0);
}

// ===========================================================================
// @ 0x00b677a0
// ===========================================================================
void* __cdecl SP_GetCurrentGameMode(void);
u32   __cdecl ResourceKeyToIcon(u32 key);

struct ModeObj { char pad[0x74]; void* m_table; };
struct ModeTable { int __thiscall FUN_00f3e900(u32 key); };

u32 __cdecl FUN_00b677a0(u32 key)
{
    if (SP_GetCurrentGameMode() == (void*)0x01654c10) {
        ModeObj* o = *(ModeObj**)0x016c7aa4;
        ModeTable* t = (ModeTable*)o->m_table;
        u32 k = key;
        int icon = t->FUN_00f3e900(k);
        if (icon != 0)
            return ResourceKeyToIcon(icon);
    }
    return 0x867a9ee9;
}
