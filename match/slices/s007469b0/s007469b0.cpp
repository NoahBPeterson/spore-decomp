// Slice s007469b0 (0x007469B0..0x007478B0): SP::cModelWorld bounds/occluder/load-queue
// helpers plus EASTL deque/vector instantiations, built /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <new>
#include <string.h>

struct Vec3 { float x, y, z; };

// --- callees / globals -----------------------------------------------------
void cHierGrid_Shutdown(void* grid);                                            // 0x00704060
void cHierGrid_Init(void* grid, void* bounds, float size, int a, int b);        // 0x00704260
void cHierGrid_Remove(void* grid, int id);                                     // 0x00704100
void FUN_00745560(void* out, int a, int b, int c, int d, int e, int f, int g, int h, int i); // 0x00745560
int  FUN_007c4510(int a, float b, void* c, void* d);                           // 0x007c4510
int  FUN_00743b20(void);                                                       // 0x00743b20
void FUN_00743b50(void* p);                                                    // 0x00743b50
void FUN_0073a820(void* p);                                                    // 0x0073a820
void FUN_0073a800(int a, int b);                                               // 0x0073a800
void FUN_00742cf0(int a);                                                      // 0x00742cf0
void FUN_007453d0(void* p);                                                    // 0x007453d0
void FUN_0073ab40(void* p);                                                    // 0x0073ab40
void FUN_00745340(void);                                                       // 0x00745340
int  FUN_007454f0(int a, int b);                                               // 0x007454f0
int  FUN_007400f0(void);                                                       // 0x007400f0
int  SP_GetPropertyAsIntArray(void* props, uint32_t key, int* count, int* data); // 0x0051e5e0
void* operator_new(uint32_t n, const char* name, int a, int b, int c, int d);  // allocator
void  operator_delete_(void* p);
void* EASTL_RBWrap(void);
void DrawRecord_CtorProto(void* owner);

// A refcounted object whose refcount lives at +4 and has a Release at vtable[4].
struct RCObj {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    int mRefCount;   // +4
};

// cModelWorld modelled with the retail byte offsets used below.
struct OccInfo { int mId; Vec3 mPosition; float mRadius; };   // 0x14
struct CModelWorld {
    unsigned char pad0[0x14];
    int mNumModels;                      // +0x14 (anchor of mModelList dummy)
    unsigned char pad18[0x2bc - 0x18];
    OccInfo* mOccluders;                 // +0x2bc

    void SetWorldBounds(Vec3 bounds[2], float a, float b);
    void UpdateOccluder(int idx, Vec3* pos, float radius);
    void ShutdownModel(int model);
};

// @ 0x007469b0 : SP::cModelWorld::SetWorldBounds
void CModelWorld::SetWorldBounds(Vec3 bounds[2], float param_3, float param_4)
{
    float d0 = bounds[0].x - bounds[0].y;  // placeholder (real shape below)
    (void)d0;
    unsigned char* b = (unsigned char*)this;
    float sx = bounds[1].x - bounds[0].x;
    float sy = bounds[1].y - bounds[0].y;
    float sz = bounds[1].z - bounds[0].z;
    float dim = sx;
    if (sy > dim) dim = sy;
    if (sz > dim) dim = sz;
    if (*(void**)(b + 0x140) != *(void**)(b + 0x13c))
        cHierGrid_Shutdown(b + 0x118);
    for (unsigned char* n = *(unsigned char**)(b + 0x19c); n != b + 0x19c; n = *(unsigned char**)n)
        *(int*)(n + 0x120) = -1;
    if (bounds[0].x <= bounds[1].x) {
        float f0 = dim * 2.0f;
        float q0 = f0 / (param_3 + 1e-08f);
        float q1 = f0 / (param_4 + 1e-08f);
        int i0 = (int)(q0 + 0.5f);
        int i1 = (int)(q1 + 0.5f);
        int lvl = i0 < 0 ? 0 : i0;
        int lv2 = i1 < 7 ? i1 : 7;
        if (lv2 < lvl) lv2 = lvl;
        cHierGrid_Init(b + 0x118, bounds, dim, lvl, lv2);
    }
}

// @ 0x00746b40 : SP::cModelWorld::UpdateOccluder
void CModelWorld::UpdateOccluder(int idx, Vec3* pos, float radius)
{
    mOccluders[idx].mPosition = *pos;
    mOccluders[idx].mRadius = radius;
}

// @ 0x00746b90 : SP::cModelWorld::ShutdownModel
struct VViewer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                 virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                 virtual void v8(); };
void cModelWorld_ShutdownModel(CModelWorld* self, int model)
{
    unsigned char* b = (unsigned char*)self;
    if (*(int*)(model + 0x120) >= 0) {
        cHierGrid_Remove(b + 0x118, *(int*)(model + 0x120));
        *(int*)(model + 0x120) = -1;
    }
    if (*(int*)(model + 0x134) != 0) {
        VViewer* v = *(VViewer**)(b + 0x224);
        // vtable slot at +0x20
        (*(void(__thiscall**)(VViewer*, int))(((char*)(*(void**)v) + 0x20)))(v, *(int*)(model + 0x134));
        *(int*)(model + 0x134) = 0;
    }
    int p = *(int*)(model + 0xdc);
    if (p) {
        int q = p + 8;
        int* it = *(int**)(p + 8);
        while (it) {
            (*(void(__thiscall**)(int*, int))((char*)(*it) + 0xc))(it, 1);
            int* nx = (int*)(q + 0x48);
            q += 0x48;
            it = (int*)*nx;
        }
        int* raw = (int*)p;
        operator_delete_((char*)raw - 4);
        *(int*)(model + 0xdc) = 0;
    }
    if (*(int**)(model + 0xe0)) {
        int* arr = *(int**)(model + 0xe0);
        int n = *arr;
        for (int i = 0; i < n; ++i) {
            int v = *(int*)(arr + 5 + i);
            if (v != -1) {
                VViewer* vw = *(VViewer**)(b + 0x224);
                (*(void(__thiscall**)(VViewer*, int))(((char*)(*(void**)vw) + 0x14)))(vw, v);
                *(int*)(arr + 5 + i) = -1;
            }
        }
        operator_delete_(arr);
        *(int*)(model + 0xe0) = 0;
    }
    unsigned char* l = *(unsigned char**)(b + 0x4c);
    unsigned char* e = *(unsigned char**)(b + 0x50);
    for (; l != e; l += 4)
        (*(void(__thiscall**)(void*, void*))((char*)(**(void***)l) + 4))(*(void**)l, (void*)(model + 8));
}

// @ 0x00746cc0 : rbtree<unsigned, AutoRefCount<cFeedbackEvent>>::find passthrough
int FUN_00746cc0(int self, int key)
{
    int it;
    // find(key) yields node or anchor; return value at +0x14 when found.
    (void)key;
    it = 0;
    if (it != self + 0x10)
        return *(int*)(it + 0x14);
    return 0;
}

// @ 0x00746cf0 : SP::cModelManager::DebugPick (PDB candidate)
int FUN_00746cf0(int self, int a, float b)
{
    int hit = 0;
    float best = 0.0f;
    int vec24[3], vec30[3];
    memset(vec24, 0, 12);
    memset(vec30, 0, 12);
    FUN_007c4510(a, b, vec30, vec24);
    int n = *(int*)(self + 0x14);
    if (n != self + 0x10) {
        do {
            void* obj = *(void**)(n + 0x14);
            if (*((char*)obj + 0x24) != 0) {
                int r = (*(int(__thiscall**)(void*, void*, void*, float*, void*))
                         (((char*)(*(void**)obj) + 0x28)))(obj, vec30, vec24, &b, 0);
                if (r && best < b) { best = b; hit = r; }
            }
            n = 0;
        } while (0);
        if (hit) {
            if (!(*(uint32_t*)(hit + 4) & 0x40)) *(uint32_t*)(hit + 4) |= 0x40;
            else *(uint32_t*)(hit + 4) &= ~0x40;
        }
    }
    return hit != 0;
}

// @ 0x00746de0 : cLoadQueue-ish record constructor (0x48 bytes)
struct Mat3 { float m[9]; void Assign(const void* src); };   // 0x0041cb40
struct Rec48 {
    int a, b, c;      // +0 +4 +8
    short d;          // +0xc
    short e;          // +0xe
    Vec3 pos;         // +0x10
    float scale;      // +0x1c
    Mat3 rot;         // +0x20
    unsigned char f;  // +0x44
    Rec48();
};
extern float g_f162eb0c, g_f162eb10, g_f162eb14, g_f162ec38, g_f1485720;
void Matrix3_Assign(void* dst, const void* src);            // 0x0041cb40
Rec48::Rec48()
{
    a = -1;
    b = -1;
    c = 0;
    d = 0;
    e = 0;
    pos.x = g_f162eb0c;
    pos.y = g_f162eb10;
    pos.z = g_f162eb14;
    scale = g_f1485720;
    rot.Assign(&g_f162ec38);
    f = 1;
}
#pragma inline_depth(0)
Rec48* MakeRec48(Rec48* p) { return new (p) Rec48(); }
#pragma inline_depth()

// @ 0x00746e50 : big load-entry constructor
void FUN_00746e50(void* self, void* owner)
{
    unsigned char* b = (unsigned char*)self;
    memset(b, 0, 8);
    DrawRecord_CtorProto(owner);
    // vector constructors at +0x9c and +0xb4 (6 RCObj refs each)
    for (int i = 0; i < 6; ++i) { *(int*)(b + 0x9c + i * 4) = 0; *(int*)(b + 0xb4 + i * 4) = 0; }
    *(void**)(b + 0xd4) = 0;
    *(void**)(b + 0xd8) = 0;
    *(void**)(b + 0xdc) = 0;
    *(void**)(b + 0xe0) = 0;
    *(short*)(b + 0xe6) = 0;
    *(short*)(b + 0xe4) = 0;
    *(float*)(b + 0xe8) = g_f162eb0c;
    *(float*)(b + 0xec) = g_f162eb10;
    *(float*)(b + 0xf0) = g_f162eb14;
    *(float*)(b + 0xf4) = g_f1485720;
    Matrix3_Assign(b + 0xf8, &g_f162ec38);
    *(float*)(b + 0x11c) = g_f1485720;
    *(int*)(b + 0x120) = -1;
    *(unsigned char*)(b + 0x128) = 0;
    *(unsigned char*)(b + 0x129) = 0;
    *(short*)(b + 0x12a) = 0;
    *(int*)(b + 0x124) = 0;
    *(int*)(b + 0x12c) = 0;
    *(int*)(b + 0x130) = 0;
    *(int*)(b + 0x134) = 0;
    *(int*)(b + 0x138) = 0;
    *(int*)(b + 0x138) |= 0x80000;
    *(int*)(b + 0xcc) = -1;
    *(short*)(b + 0xd0) = (short)0xffff;
}
void FUN_00746e50_stub();

// @ 0x00746fc0 : big load-entry destructor
void FUN_00746fc0(void* self)
{
    unsigned char* b = (unsigned char*)self;
    void* p = *(void**)(b + 0xdc);
    if (p) {
        operator_delete_((char*)p - 4);
        *(void**)(b + 0xdc) = 0;
    }
    if (*(int*)(b + 0xe0)) {
        operator_delete_(*(void**)(b + 0xe0));
        *(void**)(b + 0xe0) = 0;
    }
    RCObj* r = (RCObj*)*(void**)(b + 0xd8);
    if (r) {
        if (--r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
    for (int i = 0; i < 6; ++i) {
        RCObj* q = (RCObj*)*(void**)(b + 0xb4 + i * 4);
        if (q && --q->mRefCount == 0) { q->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)q))(q, 1); }
        RCObj* s = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (s && --s->mRefCount == 0) { s->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)s))(s, 1); }
    }
    FUN_00745340();
}

// @ 0x007470c0 : partial destructor of referenced members
void FUN_007470c0(void* self)
{
    unsigned char* b = (unsigned char*)self;
    *(int*)(b + 0x138) = 0x8000000;
    RCObj* p = (RCObj*)*(void**)(b + 0x98);
    if (p) { *(void**)(b + 0x98) = 0; (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)p) + 4)))(p, 1); }
    RCObj* q = (RCObj*)*(void**)(b + 0x6c);
    if (q) { *(void**)(b + 0x6c) = 0; (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)q) + 4)))(q, 1); }
    for (int i = 0; i < 6; ++i) {
        RCObj* a = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (a) { *(void**)(b + 0x9c + i * 4) = 0; if (--a->mRefCount == 0) { a->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)a))(a, 1); } }
        RCObj* c = (RCObj*)*(void**)(b + 0xb4 + i * 4);
        if (c) { *(void**)(b + 0xb4 + i * 4) = 0; if (--c->mRefCount == 0) { c->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)c))(c, 1); } }
    }
    RCObj* r = (RCObj*)*(void**)(b + 0xd8);
    if (r) {
        *(void**)(b + 0xd8) = 0;
        if (--r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
}

// @ 0x00747190 : copy-assign of an entry (ptr + 6 dwords)
void* FUN_00747190(int* dst, int* src)
{
    *dst = *src;
    int* old = (int*)dst[1];
    int* nw = (int*)src[1];
    if (nw != old) {
        if (nw) (*(void(__thiscall**)(int*))(*(void**)nw))(nw);
        dst[1] = (int)nw;
        if (old) (*(void(__thiscall**)(int*, int))(((char*)(*(void**)old) + 4)))(old, 1);
    }
    dst[2] = src[2];
    dst[3] = src[3];
    dst[4] = src[4];
    dst[5] = src[5];
    dst[6] = src[6];
    return dst;
}

// @ 0x007471f0 : SP::cModelWorld::cLoadingModel::cLoadingModel
void FUN_007471f0(void* self)
{
    unsigned char* b = (unsigned char*)self;
    memset(b, 0, 0x18);
    // mModelInstance array at +0x9c constructed empty (6 refs)
    for (int i = 0; i < 6; ++i)
        *(int*)(b + 0x9c + i * 4) = 0;
    *(int*)(b + 0x38) = 0;
    *(int*)(b + 0x3c) = 0;
    *(int*)(b + 0x40) = 6;
    *(int*)(b + 0x30) = 0;
}

// @ 0x00747270 : SP::cModelWorld::cLoadingModel::~cLoadingModel
void FUN_00747270(void* self)
{
    unsigned char* b = (unsigned char*)self;
    for (int i = 0; i < 6; ++i) {
        RCObj* r = (RCObj*)*(void**)(b + 0x9c + i * 4);
        if (r && --r->mRefCount == 0) { r->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)r))(r, 1); }
    }
    RCObj* p = (RCObj*)*(void**)(b + 0x18);
    if (p && --p->mRefCount == 0) { p->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)p))(p, 1); }
    RCObj* q = (RCObj*)*(void**)(b + 0x10);
    if (q && --q->mRefCount == 0) { q->mRefCount = 1; (*(void(__thiscall**)(RCObj*, int))(*(void**)q))(q, 1); }
}

// @ 0x00747340 : load-queue model-slot refresh
void FUN_00747340(int param_1)
{
    unsigned char* b = (unsigned char*)param_1;
    int count = 0, data = 0;
    if (SP_GetPropertyAsIntArray(*(void**)(b + 0x98), 0x60cbbef, &count, &data)) {
        int local[6] = {0, 0, 0, 0, 0, 0};
        int i = 0;
        while (true) {
            if (*(int*)(b + 0x9c + i * 4) != 0 && i < count) {
                uint32_t idx = *(uint32_t*)(data + i * 4);
                if (idx < 6) {
                    int src = *(int*)(b + 0x9c + idx * 4);
                    if (src == 0) break;
                    if (local[idx] == 0) {
                        int v = FUN_007454f0(src, *(int*)(b + 0x138));
                        FUN_007453d0((void*)v);
                    }
                }
            }
            ++i;
            if (i > 5) {
                char map[8];
                int k = 0;
                for (int j = 0; j < 6; ++j) {
                    if (local[j] == 0) map[j] = -1;
                    else { map[j] = (char)k; ++k; }
                }
                for (int j = 0; j < 6; ++j) {
                    if (*(int*)(b + 0x9c + j * 4) != 0)
                        *(char*)(b + 0xcc + j) = map[j];
                }
                return;
            }
        }
    }
    for (int i = 0; i < 6; ++i) {
        if (*(int*)(b + 0x9c + i * 4) != 0) {
            *(char*)(b + 0xcc + i) = 0;
            int v[6] = {0, 0, 0, 0, 0, 0};
            FUN_007453d0((void*)v);
        }
    }
}

// @ 0x00747640 : deque entry lookup helper
int FUN_00747640(int self, int* key)
{
    int local[4];
    int b = (int)self;
    FUN_00745560(local, *(int*)(b + 0x28c), *(int*)(b + 0x290), *(int*)(b + 0x294),
                 *(int*)(b + 0x298), *(int*)(b + 0x29c), *(int*)(b + 0x2a0),
                 *(int*)(b + 0x2a4), *(int*)(b + 0x2a8), *key);
    return local[0] != *(int*)(b + 0x29c);
}

// @ 0x00747720 : deque< cLoadQueueEntry >::~deque
void FUN_00747720(int* d)
{
    int beg = d[2], end = d[4], map = d[5];
    if (beg != d[6]) {
        do {
            RCObj* r = (RCObj*)*(void**)(beg + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            beg += 0x1c;
            if (beg == end) { beg = *(int*)(map + 4); map += 4; end = beg + 0xe0; }
        } while (beg != d[6]);
    }
    if (*d != 0) {
        int last = d[9];
        for (int* p = (int*)d[5]; p < (int*)(last + 4); ++p)
            if (*p) operator_delete_((void*)*p);
        operator_delete_((void*)*d);
    }
}

// @ 0x007477d0 : deque< cLoadQueueEntry >::clear
void FUN_007477d0(int self)
{
    unsigned char* b = (unsigned char*)self;
    uint32_t start = *(uint32_t*)(b + 8);
    if (*(int*)(b + 0x14) == *(int*)(b + 0x24)) {
        while (start < *(uint32_t*)(b + 0x18)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
    } else {
        while (start < *(uint32_t*)(b + 0x10)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
        start = *(uint32_t*)(b + 0x1c);
        while (start < *(uint32_t*)(b + 0x18)) {
            RCObj* r = (RCObj*)*(void**)(start + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
            start += 0x1c;
        }
        if (*(int*)(b + 0x1c)) operator_delete_(*(void**)(b + 0x1c));
    }
    uint32_t* p = (uint32_t*)(*(int*)(b + 0x14) + 4);
    while (p < *(uint32_t**)(b + 0x24)) {
        uint32_t base = *p;
        for (uint32_t q = base; q < base + 0xe0; q += 0x1c) {
            RCObj* r = (RCObj*)*(void**)(q + 4);
            if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
        }
        if (*p) operator_delete_((void*)*p);
        ++p;
    }
    *(int*)(b + 0x18) = *(int*)(b + 8);
    *(int*)(b + 0x1c) = *(int*)(b + 0xc);
    *(int*)(b + 0x20) = *(int*)(b + 0x10);
    *(int*)(b + 0x24) = *(int*)(b + 0x14);
}

// @ 0x007478b0 : vector< cLoadQueueEntry, fixed_vector_allocator >::~vector
void FUN_007478b0(uint32_t* v)
{
    uint32_t beg = *v, end = v[1];
    for (; beg < end; beg += 0x1c) {
        RCObj* r = (RCObj*)*(void**)(beg + 4);
        if (r) (*(void(__thiscall**)(RCObj*, int))(((char*)(*(void**)r) + 4)))(r, 1);
    }
    if (*v != 0 && *v != v[4])
        operator_delete_((void*)*v);
}
