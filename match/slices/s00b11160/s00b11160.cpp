// Slice s00b11160 -- Spore terrain-camera / quaternion-hermite cluster (unnamed FUN_* functions):
#include <intrin.h>
// a cubic Hermite interpolation of a quaternion, four 0x10-stride copy/fill helpers, a
// component teardown, a terrain-sphere surface probe, a zoom-program loader, and a big
// state reset.
//
//   * 0x00b11160  ?HermiteEval@@YA?AUcSPQuaternion@@PBU1@000MM@Z
//   * 0x00b11530  forward-copy of 0x10-stride records, writes end pointer back
//   * 0x00b11580  fill N copies of a 0x10 record
//   * 0x00b115c0  copy 0x10-stride records (dest may be null)
//   * 0x00b11600  component teardown (vtable restore + guarded releases)
//   * 0x00b11790  direction -> surface position via the active terrain sphere
//   * 0x00b11870  load a zoom program from a file handle
//   * 0x00b118a0  reset a block of camera/spring state
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   uint;
typedef unsigned char  uint8;

// ---------------------------------------------------------------------------------------------
// External helpers (retail addresses).
extern "C" void  __cdecl EASTL_allocator_deallocate(void* p);        // 0x00f47380 (operator delete __cdecl)
extern "C" unsigned char __cdecl LoadArithmeticaFileImpl(void* a, void* b, void* c); // 0x007f2240

// SP::GetActiveTerrainSphere() -- 0x00f48aa0, returns cTerrainSphere* or null.
struct cTerrainSphere {
    void DirectionToSurfacePosition(void* out, const void* in);      // 0x00f98800
};
extern "C" cTerrainSphere* __cdecl SP_GetActiveTerrainSphere(void);  // 0x00f48aa0

// Spring3f helper used by the reset routine.
struct Spring3f {
    void Set(float* v, char flag);                                   // 0x00b0fae0
};
// A sub-object reset helper called with `this` at +0x90 (0x00f4ff00).
struct CamObj {
    void Fn(void* v, char flag);                                     // 0x00f4ff00
};

struct cTerrainCameraCtlZoom {
    void ReloadZoomProgram();                                        // 0x00b108b0
};

// ---------------------------------------------------------------------------------------------
// External data.
extern const float DAT_01485720;   // 1.0f
extern float       DAT_0167bd60;
extern float       DAT_0167bd64;
extern float       DAT_0167bd68;
extern unsigned    DAT_0167bd6c;
extern void* const DAT_0167bc78;
extern const char  DAT_024a4f5a[];  // "..."  path string

// ---------------------------------------------------------------------------------------------
// A 4-float quaternion, passed and returned by value.
struct cSPQuaternion {
    float x, y, z, w;
};

// A generic 4-float record (0x10 stride) copied by the helpers below.
struct Vec4f { float x, y, z, w; };

// The terrain-camera controller object this slice partly models.
struct cTerrainCameraController {
    void* DirectionToSurfacePosition(void* out);  // 0x00b11790
    void  LoadZoomProgram(void* handle);          // 0x00b11870
    void  ResetState();                           // 0x00b118a0
};

// A ref-counted editor-resource component (00b11600 teardown).
struct GmeEditorResBase {
    unsigned mVtbl0;   // +0x00
    unsigned mVtbl4;   // +0x04
    unsigned mVtbl8;   // +0x08
    char     pad0c[0x30c - 0x0c];
    void*    m30c;     // +0x30c
    void Destroy();   // 0x00b11600
};

// =============================================================================================
// 0x00b11160 -- cubic Hermite interpolation between four quaternions (params a..d) at t with
// tangent scale s. Returns the interpolated quaternion by value.
// @ 0x00b11160
cSPQuaternion HermiteEval(const cSPQuaternion* a, const cSPQuaternion* b,
                          const cSPQuaternion* c, const cSPQuaternion* d,
                          float t, float s)
{
    float t2  = t * t;
    float inv = DAT_01485720 / (t2 * t);      // 1 / t^3
    float half = DAT_01485720 / (t * 2.0f);   // 1 / (2t)

    float e0 = ((a->x * 2.0f - c->x * 2.0f) + (d->x + b->x) * t) * inv;
    float e1 = ((a->y * 2.0f - c->y * 2.0f) + (d->y + b->y) * t) * inv;
    float e2 = ((a->z * 2.0f - c->z * 2.0f) + (d->z + b->z) * t) * inv;
    float e3 = ((a->w * 2.0f - c->w * 2.0f) + (d->w + b->w) * t) * inv;

    cSPQuaternion r;
    float fz = b->z, fw = b->w;

    r.x = a->x + (b->x + (e0 * s + (d->x + (-b->x - (e0 * 3.0f) * t2) * half) * s) * s) * s;
    r.y = a->y + (b->y + (e1 * s + (d->y + (-b->y - (e1 * 3.0f) * t2) * half) * s) * s) * s;
    r.z = a->z + ((e2 * s + (d->z + (-b->z - (e2 * 3.0f) * t2) * half) * s) * s + fz) * s;
    r.w = a->w + ((e3 * s + (d->w + (-b->w - (e3 * 3.0f) * t2) * half) * s) * s + fw) * s;
    return r;
}

// =============================================================================================
// 0x00b11530 -- forward-copy 0x10-stride records from [from,to) into dest, writing the final
// destination pointer back to *out.
// @ 0x00b11530
void FUN_00b11530(void** out, Vec4f* from, Vec4f* to, Vec4f* dest)
{
    Vec4f* f = from;
    Vec4f* d = dest;
    *out = dest;
    if (f != to) {
        do {
            if (d != 0) {
                d->x = f->x;
                d->y = f->y;
                d->z = f->z;
                d->w = f->w;
            }
            f += 1;
            d += 1;
        } while (f != to);
        *out = d;
    }
}

// =============================================================================================
// 0x00b11580 -- fill `count` copies of the 0x10 record at src into dst.
// @ 0x00b11580
void FUN_00b11580(Vec4f* dst, unsigned count, Vec4f* src)
{
    if (count > 0) {
        Vec4f* d = dst;
        do {
            if (d != 0) {
                d->x = src->x;
                d->y = src->y;
                d->z = src->z;
                d->w = src->w;
            }
            --count;
            d += 1;
        } while (count > 0);
    }
}

// =============================================================================================
// 0x00b115c0 -- copy 0x10-stride records from [from,to) into dest (dest may be null).
// @ 0x00b115c0
void FUN_00b115c0(Vec4f* f, Vec4f* to, Vec4f* d)
{
    while (f != to) {
        if (d != 0) {
            d->x = f->x;
            d->y = f->y;
            d->z = f->z;
            d->w = f->w;
        }
        f += 1;
        d += 1;
    }
}

// =============================================================================================
// 0x00b11600 -- component teardown: restore three vtables, release +0x30c, then free a run of
// heap pointers at +0x248 .. +0x16c (each guarded by a preceding size field), then restore the
// remaining three vtables.
// @ 0x00b11600
void GmeEditorResBase::Destroy()
{
    char* s = (char*)this;
    mVtbl0 = 0x0145cf88;
    mVtbl4 = 0x0145cf78;
    mVtbl8 = 0x014667ec;
    _ReadWriteBarrier();

    if (*(void**)(s + 0x30c) != 0) {
        void* p30c = *(void**)(s + 0x30c);
        (*(void(__thiscall**)(void*))(*(unsigned*)p30c + 4))(p30c);
    }

    void* p;
    p = *(void**)(s + 0x248); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x234); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x220); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x20c); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x1f8); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x1e4); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x1d0); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x1bc); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x1a8); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x194); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x180); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);
    p = *(void**)(s + 0x16c); if (p != 0 && *(unsigned*)((char*)p - 4) != 0) EASTL_allocator_deallocate(p);

    mVtbl8 = 0x013ef094;
    mVtbl4 = 0x013eb394;
    mVtbl0 = 0x013eb938;
}

// =============================================================================================
// 0x00b11790 -- transform the local direction *(this+0x28)*[+0x54,+0x58,+0x5c] into a surface
// position via the active terrain sphere; cache the scaled direction in the three globals.
// @ 0x00b11790
void* cTerrainCameraController::DirectionToSurfacePosition(void* out)
{
    char* s = (char*)this;
    cTerrainSphere* sp = SP_GetActiveTerrainSphere();
    if (sp != 0) {
        if ((DAT_0167bd6c & 1) == 0)
            DAT_0167bd6c |= 1;
        float f = *(float*)(s + 0x28);
        float rx = *(float*)(s + 0x54);
        float ry = *(float*)(s + 0x58);
        float rz = *(float*)(s + 0x5c);
        float px = rx * f;
        float py = ry * f;
        float pz = rz * f;
        DAT_0167bd60 = px;
        DAT_0167bd64 = py;
        DAT_0167bd68 = pz;
        sp->DirectionToSurfacePosition(out, &DAT_0167bd60);
        return out;
    }
    if ((DAT_0167bd6c & 1) == 0)
        DAT_0167bd6c |= 1;
    float f = *(float*)(s + 0x28);
    float rx = *(float*)(s + 0x54);
    float ry = *(float*)(s + 0x58);
    float rz = *(float*)(s + 0x5c);
    float px = rx * f;
    float py = ry * f;
    float pz = rz * f;
    DAT_0167bd60 = px;
    DAT_0167bd64 = py;
    DAT_0167bd68 = pz;
    *(float*)((char*)out + 0) = DAT_0167bd60;
    *(float*)((char*)out + 4) = DAT_0167bd64;
    *(float*)((char*)out + 8) = DAT_0167bd68;
    return out;
}

// =============================================================================================
// 0x00b11870 -- store the file handle at +0x308; if non-null, load the zoom program and reload.
// @ 0x00b11870
void cTerrainCameraController::LoadZoomProgram(void* handle)
{
    char* s = (char*)this;
    *(void**)(s + 0x308) = handle;
    if (handle != 0) {
        LoadArithmeticaFileImpl(handle, (void*)&DAT_024a4f5a, (void*)&DAT_0167bc78);
        ((cTerrainCameraCtlZoom*)s)->ReloadZoomProgram();
    }
}

// =============================================================================================
// 0x00b118a0 -- reset a block of camera/spring state.
// @ 0x00b118a0
void cTerrainCameraController::ResetState()
{
    char* s = (char*)this;
    *(uint8*)(s + 0x168) = 0;
    ((Spring3f*)(s + 0x3c))->Set((float*)(s + 0x6c), 1);
    ((CamObj*)(s + 0x90))->Fn((void*)(s + 0xcc), 1);

    float f0 = *(float*)(s + 0x30);
    *(float*)(s + 0x24) = *(float*)(s + 0x28) = *(float*)(s + 0x2c) = *(float*)(s + 0x30) = f0;
    *(uint8*)(s + 0x18) = 0;
    *(uint8*)(s + 0x19) = 0;
    *(float*)(s + 0x34) = f0 * 0.0f;
    *(float*)(s + 0x38) = f0 * 0.0f;

    float f1 = *(float*)(s + 0x114);
    *(float*)(s + 0x108) = *(float*)(s + 0x10c) = *(float*)(s + 0x110) = *(float*)(s + 0x114) = f1;
    *(uint8*)(s + 0xfc) = 0;
    *(uint8*)(s + 0xfd) = 0;
    *(float*)(s + 0x118) = f1 * 0.0f;
    *(float*)(s + 0x11c) = f1 * 0.0f;

    float f2 = *(float*)(s + 0x138);
    *(float*)(s + 0x12c) = *(float*)(s + 0x130) = *(float*)(s + 0x134) = *(float*)(s + 0x138) = f2;
    *(uint8*)(s + 0x120) = 0;
    *(uint8*)(s + 0x121) = 0;
    *(float*)(s + 0x13c) = f2 * 0.0f;
    *(float*)(s + 0x140) = f2 * 0.0f;

    float f3 = *(float*)(s + 0x15c);
    *(float*)(s + 0x150) = *(float*)(s + 0x154) = *(float*)(s + 0x158) = *(float*)(s + 0x15c) = f3;
    *(uint8*)(s + 0x144) = 0;
    *(uint8*)(s + 0x145) = 0;
    *(float*)(s + 0x160) = f3 * 0.0f;
    *(float*)(s + 0x164) = f3 * 0.0f;
}
