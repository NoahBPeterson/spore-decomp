// Slice s00ac6b90 -- Simulator ground/editor-layer path helpers (cSPTransform 0x3c-byte
// elements, a small embedded vector, matrix/viewport setup and noun-management glue).
//
//   * 0x00ac6b90  ground-layer constructor (cGonzagoSubsystem base + three vtables + floats)
//   * 0x00ac6c40  cSPTransform copy-constructor (words + 4 floats + Matrix3::Assign + float)
//   * 0x00ac6c90 / 0x00ac6da0 / 0x00ac6de0  range copy / assign-copy / backward copy of 0x3c elems
//   * 0x00ac6e20  ground-layer scalar deleting destructor
//   * 0x00ac6e80  vector<cSPTransform>::DoInsertValue
//   * 0x00ac6fa0  vector<cSPTransform>::push_back (default element)
//   * 0x00ac7080 / 0x00ac70c0  clear the point vector / reset
//   * 0x00ac7120  build a trail/ribbon mesh from the point vector (large; see scratch notes)
//   * 0x00ac7680  append a distance-interpolated transform
//   * 0x00ac7790 ... 0x00ac7a40  noun + cGameBundleGroundContainer management
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <string.h>
#include <math.h>
#include <new>

typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned short ushort;

// ------------------------------------------------------------------ externs
extern "C" void* __cdecl EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int); // 0x00f473a0
extern "C" void  __cdecl EASTL_allocator_deallocate(void*); // 0x00f47380
extern char sz_name_13f09b4[]; // 0x013f09b4 "Simulator"
extern char sz_file_13ebb38[]; // 0x013ebb38 "...allocator.h"
#define EA_ALLOC(sz) EASTL_allocator_allocate((sz), sz_name_13f09b4, 0, 0, sz_file_13ebb38, 0xd1)
#define EA_FREE(p)   EASTL_allocator_deallocate(p)

extern "C" void __fastcall cGonzagoSubsystem_ctor(void*); // 0x00b5b960 (this in ecx)
extern "C" void __fastcall cGonzagoSubsystem_dtor(void*); // 0x00b5b9a0 (this in ecx)

extern char VT_13f1ab0[]; // 0x013f1ab0
extern char VT_1459f50[]; // 0x01459f50
extern char VT_1459f4c[]; // 0x01459f4c
extern char VT_1459f3c[]; // 0x01459f3c
extern char VT_13eb938[]; // 0x013eb938
extern char VT_1459fc8[]; // 0x01459fc8
extern char VT_1459fc0[]; // 0x01459fc0
extern float kf_14763b8;  // 0x014763b8
extern float kf_13ec4d0;  // 0x013ec4d0
extern float kf_1485720;  // 0x01485720 (== 1.0f)
extern float kf_167a2cc;  // 0x0167a2cc
extern float kf_167a2d0;  // 0x0167a2d0
extern float kf_167a2d4;  // 0x0167a2d4
extern char  kM_167a2dc[]; // 0x0167a2dc (Matrix3)
extern int   g_16f94ec;   // 0x016f94ec
extern int   g_16f9528;   // 0x016f9528
extern int   g_16fa3a0;   // 0x016fa3a0
extern int   g_16f96a0;   // 0x016f96a0
extern int   g_16fa380;   // 0x016fa380
extern char  g_mtx_16fa4f0[]; // 0x016fa4f0 (4x4 float matrix)
extern float kf_13ec480;  // 0x013ec480
extern float kf_1471064;  // 0x01471064
extern float kf_1459f10;  // 0x01459f10 (== 255.0f)
extern float kf_1565bfc;  // 0x01565bfc

extern "C" void* __cdecl FUN_0067dd50();             // 0x0067dd50 (returns an object pointer)
extern "C" void* __cdecl FUN_007c40f0(void*, void*); // 0x007c40f0
extern "C" char __cdecl cViewer_Update(void*);       // 0x007c4fd0
extern "C" void __cdecl FUN_007c3c10(void*);         // 0x007c3c10
extern "C" void __cdecl FUN_006dde30(int, int, void*); // 0x006dde30
extern "C" int  __cdecl FUN_006dde90(int, void*, void*, void*); // 0x006dde90
extern "C" void __cdecl FUN_006ddee0();              // 0x006ddee0
extern "C" void __cdecl FUN_006ddef0(void*);         // 0x006ddef0
extern "C" int  __fastcall FUN_00cee370(void*);      // 0x00cee370 (this in ecx)
extern "C" void* __fastcall FUN_00cee330(void*);     // 0x00cee330 (this in ecx)
extern "C" void* __cdecl NounManager();              // 0x00b3d300 (static getter, no args)

// thiscall glue: a member declaration reproduces the exact ABI (this in ecx, args on the stack).
struct Cee650 {
    void Call(void*);                      // 0x00cee650
};
struct Cee820 {
    void Call(void*);                      // 0x00cee820
};
struct C35b20 {
    void Call(void*, float);               // 0x00c35b20
};
struct C35b40 {
    void Call(float);                      // 0x00c35b40
};
struct C36510 {
    void* Ctor();                          // 0x00c36510
};
struct NounMgr {
    void* CreateNoun(void*);               // 0x00b20c60
    void  RemoveNoun(void*);               // 0x00b225d0
};
// Generic vtable dispatcher for `(**(code **)(*obj + off))(args)` call sites.
struct VObj {
    virtual void m00(); virtual void m01(); virtual void m02(void*); virtual void m03(void*);
    virtual void m04(); virtual void m05(); virtual void m06();  virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(int); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14();  virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18();  virtual void m19();
    virtual void m20(int);
};

// ------------------------------------------------------------------ types
struct Matrix3 {                       // 0x24 bytes
    float m[9];
    void Assign(const Matrix3* o);     // 0x0041cb40 (this in ecx)
};

struct cSPTransform {                  // 0x3c bytes
    short   a;                         // +0x00
    short   b;                         // +0x02
    float   x, y, z, w;                // +0x04
    Matrix3 mat;                       // +0x14
    float   s;                         // +0x38
    cSPTransform() {}                              // trivial default (fields written by callers)
    cSPTransform(const cSPTransform&);             // 0x00ac6c40
    cSPTransform& operator=(const cSPTransform&);  // 0x00537dc0
};

// vector<cSPTransform> (embedded at cGroundLayer+0x44)
struct VecT {
    cSPTransform* mpBegin;     // +0
    cSPTransform* mpEnd;       // +4
    cSPTransform* mpCapacity;  // +8
    void DoInsertValue(cSPTransform*, const cSPTransform*); // 0x00ac6e80
    void push_back();                                       // 0x00ac6fa0
};

struct cGroundLayer {
    void* vt0;                 // +0x00
    void* vt4;                 // +0x04
    char  pad08[0x14];         // +0x08
    void* vt1c;                // +0x1c
    uchar flag20;              // +0x20
    char  pad21[3];
    void* ptr24;               // +0x24
    float f28, f2c, f30, f34;  // +0x28
    float f38, f3c, f40;       // +0x38
    VecT  vec;                 // +0x44
    void clearVec();                                     // 0x00ac7080
    void reset();                                        // 0x00ac70c0
    void addInterpolated(cSPTransform*, float);          // 0x00ac7680
    void* sdtor(uint flags);                             // 0x00ac6e20
};

struct cPathBuffer {           // object built by buildMesh (0x00ac7120)
    char  pad00[8];
    void* p08;                 // +0x08
    char  pad0c[0x10];
    int   i1c, i20, i24;       // +0x1c
    cSPTransform* mpBegin;     // +0x28
    cSPTransform* mpEnd;       // +0x2c
    void buildMesh(void*, void*, void*, void*);          // 0x00ac7120
};

struct cGroundEditorRes {
    void* vt0;                 // +0x00
    void* vt4;                 // +0x04
    char  pad08[0x14];         // +0x08
    void* p1c;                 // +0x1c
    void ensureContainer();    // 0x00ac7910
    void destroyContainer();   // 0x00ac7980
    void removeNoun();         // 0x00ac79a0
    void* getContainer();      // 0x00ac79d0
};

// ================================================================================================
// 0x00ac6b90 -- ground-layer constructor (this in ecx, returns this).
// @ 0x00ac6b90
cGroundLayer* __fastcall cGroundLayer_ctor(cGroundLayer* p)
{
    cGonzagoSubsystem_ctor(p);
    p->vt1c = VT_13f1ab0;
    p->f28 = kf_14763b8;
    p->f2c = kf_13ec4d0;
    p->vt0 = VT_1459f50;
    p->vt4 = VT_1459f4c;
    p->vt1c = VT_1459f3c;
    p->flag20 = 1;
    p->ptr24 = 0;
    p->f30 = 0.0f;
    p->f34 = 0.0f;
    p->vec.mpBegin = 0;
    p->vec.mpEnd = 0;
    p->vec.mpCapacity = 0;
    p->f38 = 0.0f;
    p->f3c = 0.0f;
    p->f40 = 0.0f;
    return p;
}

// ================================================================================================
// 0x00ac6c40 -- cSPTransform copy-constructor.
// @ 0x00ac6c40
cSPTransform::cSPTransform(const cSPTransform& o)
{
    a = o.a;
    b = o.b;
    x = o.x;
    y = o.y;
    z = o.z;
    w = o.w;
    mat.Assign(&o.mat);
    s = o.s;
}

// ================================================================================================
// 0x00ac6c90 -- copy [first,last) into dst, raw 0x3c-byte element copies; returns advanced dst.
// @ 0x00ac6c90
struct Blob3c { uint d[15]; };
cSPTransform* __cdecl do_copy_6c90(const cSPTransform* first, const cSPTransform* last, cSPTransform* dst)
{
    while (first != last) {
        *(Blob3c*)dst = *(const Blob3c*)first;
        first++;
        dst++;
    }
    return dst;
}

// ================================================================================================
// 0x00ac6da0 -- copy [first,last) into dst via operator= + float tail; returns advanced dst.
// @ 0x00ac6da0
cSPTransform* __cdecl do_assign_6da0(const cSPTransform* first, const cSPTransform* last, cSPTransform* dst)
{
    while (first != last) {
        *dst = *first;
        dst->s = first->s;
        first++;
        dst++;
    }
    return dst;
}

// ================================================================================================
// 0x00ac6de0 -- copy_backward [first,last) into dstEnd.
// @ 0x00ac6de0
cSPTransform* __cdecl do_copyBack_6de0(const cSPTransform* first, const cSPTransform* last, cSPTransform* dstEnd)
{
    while (last != first) {
        last--;
        dstEnd--;
        *dstEnd = *last;
        dstEnd->s = last->s;
    }
    return dstEnd;
}

// ================================================================================================
// 0x00ac6e20 -- ground-layer scalar deleting destructor (this in ecx, flags on stack).
// @ 0x00ac6e20
void* cGroundLayer::sdtor(uint flags)
{
    vt0 = VT_1459f50;
    vt4 = VT_1459f4c;
    vt1c = VT_1459f3c;
    cSPTransform* v = vec.mpBegin;
    if (v && *(int*)((char*)v - 4) != 0)
        EA_FREE(v);
    vt1c = VT_13eb938;
    cGonzagoSubsystem_dtor(this);
    if (flags & 1)
        EA_FREE(this);
    return this;
}

// ================================================================================================
// 0x00ac6e80 -- vector<cSPTransform>::DoInsertValue(position, value).
// @ 0x00ac6e80
void VecT::DoInsertValue(cSPTransform* position, const cSPTransform* value)
{
    if (mpEnd != mpCapacity) {
        cSPTransform* pv = (cSPTransform*)value;
        if (pv >= position && pv < mpEnd)
            pv++;
        if (mpEnd)
            new ((void*)mpEnd) cSPTransform(*(mpEnd - 1));
        if (position != mpEnd - 1)
            do_copyBack_6de0(position, mpEnd - 1, mpEnd);
        *position = *pv;
        position->s = pv->s;
        mpEnd += 1;
        return;
    }
    // grow
    int oldCount = (int)((mpEnd - mpBegin) / (int)sizeof(cSPTransform));
    int newCap = (oldCount > 0) ? oldCount * 2 : 1;
    cSPTransform* nb = (newCap == 0) ? 0
                      : (cSPTransform*)EA_ALLOC((uint)(newCap * sizeof(cSPTransform)));
    cSPTransform* dst = do_copy_6c90(mpBegin, position, nb);
    if (dst)
        new ((void*)dst) cSPTransform(*value);
    dst++;
    dst = do_copy_6c90(position, mpEnd, dst);
    if (mpBegin && *(int*)((char*)mpBegin - 4) != 0)
        EA_FREE(mpBegin);
    mpEnd = dst;
    mpBegin = nb;
    mpCapacity = (cSPTransform*)((char*)nb + newCap * sizeof(cSPTransform));
}

// ================================================================================================
// 0x00ac6fa0 -- vector<cSPTransform>::push_back (default-constructed element).
// @ 0x00ac6fa0
void VecT::push_back()
{
    if (mpEnd < mpCapacity) {
        cSPTransform* e = mpEnd;
        mpEnd += 1;
        if (e) {
            e->a = 0;
            e->b = 0;
            e->x = kf_167a2cc;
            e->y = kf_167a2d0;
            e->z = kf_167a2d4;
            e->w = kf_1485720;
            e->mat.Assign((const Matrix3*)kM_167a2dc);
        }
        return;
    }
    cSPTransform tmp;
    tmp.a = 0;
    tmp.b = 0;
    tmp.x = kf_167a2cc;
    tmp.y = kf_167a2d0;
    tmp.z = kf_167a2d4;
    tmp.w = kf_1485720;
    tmp.mat.Assign((const Matrix3*)kM_167a2dc);
    DoInsertValue(mpEnd, &tmp);
}

// ================================================================================================
// 0x00ac7080 -- clear the point vector.
// @ 0x00ac7080
void cGroundLayer::clearVec()
{
    cSPTransform* b = vec.mpBegin;
    cSPTransform* e = vec.mpEnd;
    do_assign_6da0(e, e, b);
    int d = (int)((char*)e - (char*)b);
    unsigned long long pr = (unsigned long long)(long long)d * 0x77777777ULL;
    int m = (int)(pr >> 32) - d;
    vec.mpEnd = (cSPTransform*)((char*)e + ((m >> 5) - (m >> 31)) * 0x3c);
}

// ================================================================================================
// 0x00ac70c0 -- reset: zero +0x24, clear vector, notify via 0x67dd50 virtual.
// @ 0x00ac70c0
void cGroundLayer::reset()
{
    ptr24 = 0;
    cSPTransform* b = vec.mpBegin;
    cSPTransform* e = vec.mpEnd;
    do_assign_6da0(e, e, b);
    int d = (int)((char*)e - (char*)b);
    unsigned long long pr = (unsigned long long)(long long)d * 0x77777777ULL;
    int m = (int)(pr >> 32) - d;
    vec.mpEnd = (cSPTransform*)((char*)e + ((m >> 5) - (m >> 31)) * 0x3c);
    void* o = (void*)FUN_0067dd50();
    ((VObj*)o)->m20(0xb);
}

// ================================================================================================
// 0x00ac7680 -- append a transform interpolated between two distance limits (arg1=src, arg2=scale).
// @ 0x00ac7680
void cGroundLayer::addInterpolated(cSPTransform* src, float scale)
{
    if (!flag20)
        return;
    float dx = src->x - f38;
    float dy = src->y - f3c;
    float dz = src->z - f40;
    float dist = sqrtf(dx * dx + dy * dy + dz * dz);
    float alpha = 1.0f;
    if (dist > f28)
        return;
    if (f30 > dist)
        return;
    if (dist > f2c) {
        alpha = 1.0f - (dist - f2c) / (f28 - f2c);
    } else if (f34 > dist) {
        alpha = 1.0f - (dist - f30) / (f34 - f30);
    }
    vec.push_back();
    cSPTransform* e = vec.mpEnd - 1;
    *e = *src;
    e->s = alpha * scale;
}

// ================================================================================================
// 0x00ac7120 -- build a trail/ribbon mesh from the point vector.
//
// Setup: builds an identity-ish cSPTransform temp, hands it to the viewer, stores the viewport
// dimensions at +0x1c/+0x20/+0x24, bumps the global frame counter and a 4x4 identity basis, then
// opens a debug-render scope (0x6dde30) and walks the point vector emitting a 0x18-byte vertex
// stream (position + packed colour + uv) through 0x6dde90. The exact SSE ordering of the per-point
// corner generation is reproduced below in scalar form; it is faithful to the arithmetic but is
// NOT byte-identical (see scratch notes).
// @ 0x00ac7120
void cPathBuffer::buildMesh(void* a1, void* a2, void* a3, void* a4)
{
    (void)a1;
    (void)a2;
    cSPTransform tmp;
    tmp.a = 0;
    tmp.b = 0;
    tmp.x = kf_167a2cc;
    tmp.y = kf_167a2d0;
    tmp.z = kf_167a2d4;
    tmp.w = kf_1485720;
    tmp.mat.Assign((const Matrix3*)kM_167a2dc);

    void* viewer = *(void**)a3;
    FUN_007c40f0(viewer, &tmp);
    i1c = *(int*)((char*)&tmp + 4);
    i20 = *(int*)((char*)&tmp + 8);
    i24 = *(int*)((char*)&tmp + 0xc);

    viewer = *(void**)a3;
    if (!cViewer_Update(viewer))
        goto cleanup;

    {
        float oldFrame = *(float*)&g_16f94ec;
        g_16f9528 |= 1;
        g_16fa3a0 |= 0x10000000;
        g_16f96a0 = 4;
        g_16fa380 = (int)g_mtx_16fa4f0;
        float (*M)[4] = (float(*)[4])g_mtx_16fa4f0;
        M[0][0] = 1; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
        M[1][0] = 0; M[1][1] = 1; M[1][2] = 0; M[1][3] = 0;
        M[2][0] = 0; M[2][1] = 0; M[2][2] = 1; M[2][3] = 0;
        M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 0;
        *(float*)&g_16f94ec = kf_1565bfc + oldFrame;
    }

    FUN_006dde30(3, 2, p08);

    int count = (int)((mpEnd - mpBegin) / (int)sizeof(cSPTransform));
    int idx = 0;
    if (count > 0) {
        do {
            *(int*)((char*)a4 + 0x28) += 1;
            int stride = 0;
            void* base = 0;
            int n = FUN_006dde90((count - idx) * 4, &stride, &base, a4) / 4;
            if (n <= 0 || stride != 0x18)
                break;
            char* out = (char*)base;
            for (int k = 0; k < n; k++) {
                cSPTransform* pt = mpBegin + idx + k;
                float scale = pt->w * kf_1471064;
                float cx = pt->mat.m[6] * kf_13ec480;
                float cy = pt->mat.m[7] * kf_13ec480;
                float cz = pt->mat.m[8] * kf_13ec480;
                float px = pt->x - cx;
                float py = pt->y - cy;
                float pz = pt->z - cz;
                float tx = pt->mat.m[0] * scale;
                float ty = pt->mat.m[1] * scale;
                float tz = pt->mat.m[2] * scale;
                float a = pt->s;
                if (a < 0.0f) a = 0.0f;
                a = a * kf_1459f10;
                if (a > kf_1459f10) a = kf_1459f10;
                uint col = 0xffffffu | ((uint)(int)a << 24);
                for (int c = 0; c < 3; c++) {
                    float* v = (float*)out;
                    v[0] = px + tx * (c == 0 ? -1.0f : 1.0f);
                    v[1] = py + ty * (c == 2 ? 1.0f : -1.0f);
                    v[2] = pz + tz * (c == 0 ? -1.0f : 1.0f);
                    *(uint*)(out + 0xc) = col;
                    out += 0x18;
                }
            }
            idx = count;
        } while (idx < count);
    }

cleanup:
    FUN_006ddee0();
    FUN_006ddef0((void*)*(int*)((char*)a4 + 0x14));
    g_16fa3a0 |= 0x10000000;
    *(float*)&g_16f94ec = *(float*)((char*)&tmp + 4);
    {
        cSPTransform* b = mpBegin;
        cSPTransform* e = mpEnd;
        do_assign_6da0(e, e, b);
        mpEnd = b;
    }
    FUN_007c3c10(*(void**)((char*)a4 + 0x10));
}

// ================================================================================================
// 0x00ac7790 -- create the ground noun (free function; args on stack).
// @ 0x00ac7790
void* __stdcall createNoun_7790(void* self, float f, void* p)
{
    if (FUN_00cee370(self) >= *(int*)((char*)self + 0x1c))
        return 0;
    void* mgr = NounManager();
    void* noun = ((NounMgr*)mgr)->CreateNoun((void*)0x18c431c);
    ((C35b20*)noun)->Call(p, f);
    ((Cee820*)self)->Call(noun);
    ((VObj*)self)->m02(noun);
    return noun;
}

// ================================================================================================
// 0x00ac78a0 -- cGroundEditorRes constructor (this in ecx, returns this).
// @ 0x00ac78a0
cGroundEditorRes* __fastcall cGroundEditorRes_ctor(cGroundEditorRes* p)
{
    cGonzagoSubsystem_ctor(p);
    p->vt0 = VT_1459fc8;
    p->vt4 = VT_1459fc0;
    p->p1c = 0;
    return p;
}

// ================================================================================================
// 0x00ac7910 -- lazily (re)create the ground container at +0x1c.
// @ 0x00ac7910
void cGroundEditorRes::ensureContainer()
{
    if (p1c != 0)
        return;
    void* mem = EASTL_allocator_allocate(0x60, sz_name_13f09b4, 0, 0, 0, 0);
    void* nc = 0;
    if (mem)
        nc = ((C36510*)mem)->Ctor();
    void* old = p1c;
    if (nc != old) {
        if (nc)
            ((VObj*)nc)->m00();
        p1c = nc;
        if (old)
            ((VObj*)old)->m01();
    }
    ((VObj*)p1c)->m10(0);
}

// ================================================================================================
// 0x00ac7980 -- destroy the container at +0x1c.
// @ 0x00ac7980
void cGroundEditorRes::destroyContainer()
{
    void* o = p1c;
    if (o == 0)
        return;
    p1c = 0;
    ((VObj*)o)->m01();
}

// ================================================================================================
// 0x00ac79a0 -- remove the container's noun and destroy it.
// @ 0x00ac79a0
void cGroundEditorRes::removeNoun()
{
    void* o = p1c;
    if (o == 0)
        return;
    void* mgr = NounManager();
    ((NounMgr*)mgr)->RemoveNoun(o);
    void* c = p1c;
    if (c == 0)
        return;
    p1c = 0;
    ((VObj*)c)->m01();
}

// ================================================================================================
// 0x00ac79d0 -- return the container's +0x34 sub-object (or 0).
// @ 0x00ac79d0
void* cGroundEditorRes::getContainer()
{
    void* o = p1c;
    if (o == 0)
        return 0;
    return (char*)o + 0x34;
}

// ================================================================================================
// 0x00ac79e0 -- remove/destroy the noun registered at +0x128 (free function; args on stack).
// @ 0x00ac79e0
void __stdcall cleanup_79e0(void* self, uint a2)
{
    (void)a2;
    if (!self)
        return;
    ((C35b40*)self)->Call(0.0f);
    void* q = *(void**)((char*)self + 0x128);
    if (q) {
        ((VObj*)q)->m06();
        ((VObj*)q)->m03(self);
        ((Cee650*)q)->Call(self);
    }
    void* mgr = NounManager();
    ((NounMgr*)mgr)->RemoveNoun(self);
    if (q)
        ((VObj*)q)->m07();
}

// ================================================================================================
// 0x00ac7a40 -- drain all nouns (free function; self on stack).
// @ 0x00ac7a40
void __stdcall drainNouns_7a40(void* self)
{
    if (!self)
        return;
    int n = FUN_00cee370(self);
    while (n > 0) {
        void* noun = FUN_00cee330(self);
        if (noun)
            ((VObj*)noun)->m00();
        ((VObj*)self)->m03(noun);
        ((Cee650*)self)->Call(noun);
        ((VObj*)noun)->m17();
        void* mgr = NounManager();
        ((NounMgr*)mgr)->RemoveNoun(noun);
        ((VObj*)noun)->m01();
        n = FUN_00cee370(self);
    }
}
