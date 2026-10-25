// slice s00775760: SP::cRuntimeModelBuilder mesh / bone accessors and the
// constructor/destructor pair for a resource model.  Small accessors are
// reconstructed; the large EH-framed routines are skeletons (partial).
#include "types.h"
#include <intrin.h>

__declspec(noinline) int FUN_00776320(int a, int b, int c, int d, int e);   // @ 0x00776320

// @ 0x007763b0  SP::cRuntimeModelBuilder::GetRuntimeMeshes
bool GetRuntimeMeshes(int param_1, int param_2, int param_3, int param_4, int param_5) {
    return FUN_00776320(param_1, param_2, param_3, param_4, param_5) == 0;
}

struct cRuntimeModelBuilder {
    char pad[0x140];

    // @ 0x007763f0
    char setFlagA(int key, int unused);
    // @ 0x00776470
    char setFlagB(int key, int unused);
    // @ 0x007764c0
    int setBoneA(int unused, const float* v, float w, int unused2);
    // @ 0x00776520
    int setBoneB(int unused, const float* v, float w, int unused2);
};

char cRuntimeModelBuilder::setFlagA(int key, int unused) {
    (void)unused;
    if (key == 0x692ea61) {
        if (*(char*)((char*)this + 0x133) != 0) {
            *(char*)((char*)this + 0x133) = 0;
            *(char*)((char*)this + 0x132) = 1;
        }
        return 1;
    }
    return 0;
}

char cRuntimeModelBuilder::setFlagB(int key, int unused) {
    (void)unused;
    if (key == 0x692ea61) {
        if (*(char*)((char*)this + 0x135) != 0) {
            *(char*)((char*)this + 0x135) = 0;
            *(char*)((char*)this + 0x134) = 1;
        }
        return 1;
    }
    return 0;
}

int cRuntimeModelBuilder::setBoneA(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x120) = v[0];
    *(float*)((char*)this + 0x124) = v[1];
    *(float*)((char*)this + 0x128) = v[2];
    *(float*)((char*)this + 0x12c) = w;
    return *(const int*)(v + 2);   // original leaves v[2] in eax (copied via a stack temp)
}

int cRuntimeModelBuilder::setBoneB(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x12c) = v[0];
    *(float*)((char*)this + 0x130) = v[1];
    *(float*)((char*)this + 0x134) = v[2];
    *(float*)((char*)this + 0x138) = w;
    return *(const int*)(v + 2);   // original leaves v[2] in eax (copied via a stack temp)
}

// ---------------------------------------------------------------------------
// 0x00775760: bake the runtime meshes of a model instance against its model resource
// (SP::cRuntimeModelBuilder area).  Stub layouts; member names carry the callee VA.
// ---------------------------------------------------------------------------
void operator_delete_array(void* p);                       // 0x00f47380 (operator delete[])
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
void operator delete(void*, const char*, int, int, int, int) {}

struct RCObj { void** vptr; volatile long rc; };
inline void RC_AddRef(RCObj* o) { _InterlockedExchangeAdd(&o->rc, 1); }

struct GmeRefCount {
    volatile long rc;
    __forceinline GmeRefCount() { _InterlockedExchange(&rc, 0); }
    virtual ~GmeRefCount() {}
};
struct GmeObj : GmeRefCount {                                // sizeof 0x58
    int f08, f0c, f10, p14[2], f1c, f20, f24, p28[2], f30, f34, f38, p3c[2], f44, f48, f4c, p50[2];
    __forceinline GmeObj() {
        f08 = f0c = f10 = 0; f1c = f20 = f24 = 0; f30 = f34 = f38 = 0; f44 = f48 = f4c = 0;
    }
    virtual ~GmeObj() {}
};
inline void GmeRelease(GmeObj* o) {
    if (_InterlockedExchangeAdd(&o->rc, -1) == 1) {
        _InterlockedExchange(&o->rc, 1);
        delete o;                                            // vtable slot 0 (deleting dtor)
    }
}

struct IRefObj { virtual int AddRef() = 0; virtual int Release() = 0; virtual int v2() = 0; virtual void* GetSub(uint32_t type) = 0; };
struct IResMgr { virtual int v0() = 0; virtual int v1() = 0; virtual int v2() = 0;
                 virtual bool GetResource(const void* key, IRefObj** out, int a, int b, int c, int d) = 0; };
IResMgr* GetManager();                                        // 0x0067dcd0

struct ResPtr {
    IRefObj* p;
    ResPtr() : p(0) {}
    ~ResPtr() { if (p) p->Release(); }
    void reset() { IRefObj* t = p; if (t) { p = 0; t->Release(); } }
};
struct ResKey3 { uint32_t inst, type, group; };

struct Mesh : RCObj {
    char pad08[0x14]; char* part;                             // +0x1c: sub-part table
    int sub_572b10();                                         // part count
    bool sub_71dc90(int idx);                                 // ret 4
};
struct RefVec {                                               // vector of intrusive refs
    RCObj** b; RCObj** e; RCObj** cap;
    RefVec() : b(0), e(0), cap(0) {}
    ~RefVec() { sub_41eb80(); }
    void sub_41eb80();
    void sub_41ef20(GmeObj** p);                              // push_back(const intrusive_ptr<GmeObj>&)
    void sub_424430(RCObj** pos, RCObj** val);                // DoInsertValue, ret 8
};
__forceinline void PushBack(RefVec* v, RCObj** src) {
    RCObj** e = v->e;
    if (e < v->cap) {
        v->e = e + 1;
        if (e) { RCObj* x = *src; *e = x; if (x) RC_AddRef(x); }
    } else {
        v->sub_424430(e, src);
    }
}

struct FixBase { char* b; char* e; char* cap; uint32_t alloc; char* pool; uint32_t pad; };
struct FixA : FixBase { uint32_t buf[256]; void sub_4c0570(int n, int v);
    ~FixA() { if (b && b != pool) operator_delete_array(b); } };
struct FixB : FixBase { uint32_t buf[12 * 256]; void sub_774df0(int n);
    ~FixB() { if (b && b != pool) operator_delete_array(b); } };
struct FixC : FixBase { uint32_t buf[44 * 256]; void sub_774e50(int n);
    ~FixC() { if (b && b != pool) operator_delete_array(b); } };
struct FixD : FixBase { uint32_t buf[12 * 256]; void sub_774eb0(int n);
    ~FixD() { if (b && b != pool) operator_delete_array(b); } };

struct SkelInfo { uint32_t pad[2]; int* ids; int count; };    // arena/rest-pose record
struct BakeRec { uint32_t pad[3]; SkelInfo* rec; int valid; };
struct SInfo {
    int M; int count; short w0, w1; IRefObj* ref;
    ~SInfo() { if (ref) ref->Release(); }
};
struct Drawer { void sub_740550(void* boneBuf); };            // ret 4
struct ArenaRes {                                             // GetArenaResource record
    char pad08[8];
    uint32_t keyInst, keyType, keyGroup;                      // +0x08, +0x0c, +0x10
};
struct Inst {
    char pad[0xf0]; Drawer* draw;
    bool sub_73eb90(RefVec* out);                             // GetMeshes, ret 4
    ArenaRes* sub_73d160();                                   // GetArenaResource
    void sub_73ba50(void (*fn)());                            // ret 4
};
struct Builder { void sub_775230(void** p); };                // ret 4
extern Builder g_builder_1630b68;
void FUN_007740f0();

int FUN_006ac0a0(int a, void* p);
bool FUN_00757d20(void* p);
void FUN_0072fff0(void* p, RefVec* out);
void FUN_0072c100(RefVec* meshes, void* obj, int a, int b);
bool FUN_00774f80(Mesh* a, void* b);
int FUN_0071ddc0(void* m, int a, int b, int c, int d);
BakeRec* FUN_0076fb10(void* p);
bool FUN_0076fc20(SkelInfo* a, SkelInfo* b, FixA* idx);
void FUN_0076fc90(SkelInfo* a, void* idx, int n, int m, void* b, void* c, void* d);
void FUN_00720070(SInfo* s);
void FUN_00774110(SInfo* s, void* a, void* rec, int k);
bool FUN_0073a110(void* d, void* mesh, GmeObj* o);
void FUN_007754d0(void* a, void* b);
void FUN_007756b0(void* a, SInfo* s);

// @ 0x00775760
int FUN_00775760(Inst* inst, RefVec* outMeshes, void** out3, void** out4, ResKey3 key, int arg8) {
    if (!inst) return 1;
    key.type = 0x2f4e681b;
    ResPtr res;
    IResMgr* mgr = GetManager();
    res.reset();
    if (!mgr->GetResource(&key, &res.p, 0, 0, 0, 0)) return 1;
    FUN_006ac0a0(9, res.p);
    if (!res.p) return 1;
    IRefObj* sub = (IRefObj*)res.p->GetSub(0x2f4e681b);
    if (!sub) return 1;
    if (FUN_00757d20(sub)) return 2;

    RefVec v1;
    RefVec v2;
    FUN_0072fff0(sub, &v1);
    if (!inst->sub_73eb90(&v2)) return 3;
    int n = (int)(v2.e - v2.b);
    if (n != (int)(v1.e - v1.b)) return 4;

    for (int i = 0; i < n; ++i) {
        Mesh* a = (Mesh*)v2.b[i];
        Mesh* b = (Mesh*)v1.b[i];
        if (!FUN_00774f80(a, b)) return 5;
        int s1 = FUN_0071ddc0(a, 1, -1, 3, 0xe);
        int s2 = FUN_0071ddc0(b, 1, -1, 3, 0xe);
        if (s1 < 0 || s2 < 0) return 5;
        int parts = a->sub_572b10();
        uint32_t* q = (uint32_t*)(a->part + 0x44);
        for (int j = 0; j < parts; ++j, q += 0x23) {
            if (q[0] != q[1]) return 5;
            if (b->sub_71dc90(j)) return 5;
        }
    }

    BakeRec* r1 = FUN_0076fb10(sub);
    SkelInfo* rb = (r1 && r1->valid) ? r1->rec : 0;
    BakeRec* r2 = FUN_0076fb10(inst->sub_73d160());
    SkelInfo* arena;
    int N;
    if (r2 && r2->valid) {
        arena = r2->rec;
        N = arena ? arena->count : 0;
    } else {
        arena = 0;
        N = 0;
    }
    int M = rb ? rb->count : 0;

    FixA A; A.sub_4c0570(N, -1);
    FixB B; B.sub_774df0(M);
    FixC C; C.sub_774e50(M);
    FixD D; D.sub_774eb0(N);
    SInfo S;
    S.M = M; S.count = 0; S.w0 = 0x30; S.w1 = 0x30; S.ref = 0;
    *out4 = 0;
    if (arena) {
        if (rb) {
            for (int i = 0; i < N; ++i) {
                int id = arena->ids[i];
                int found = -1;
                for (int j = 0; j < M; ++j)
                    if (id == rb->ids[j]) found = j;
                ((int*)A.b)[i] = found;
            }
            if (!FUN_0076fc20(arena, rb, &A)) return 6;
            FUN_0076fc90(arena, A.b, N, M, B.b, C.b, D.b);
            inst->sub_73ba50(FUN_007740f0);
            g_builder_1630b68.sub_775230(out4);
            FUN_00720070(&S);
            FUN_00774110(&S, *out4, FUN_0076fb10(sub), arg8);
        } else {
            inst->draw->sub_740550(D.b);
        }
    }

    RefVec v3;
    for (int i = 0; i < n; ++i) {
        GmeObj* o = new ("Graphics", 0, 0, 0, 0) GmeObj();
        if (o) _InterlockedExchangeAdd(&o->rc, 1);
        if (arena && FUN_0073a110(D.b, v2.b[i], o)) {
            v3.sub_41ef20(&o);
        } else {
            PushBack(&v3, &v2.b[i]);
        }
        if (o) GmeRelease(o);
    }
    for (int i = 0; i < n; ++i) {
        void* m = v1.b[i];
        FUN_007754d0(v3.b[i], m);
        if (S.count) FUN_007756b0(m, &S);
    }
    for (int i = 0; i < n; ++i)
        PushBack(outMeshes, &v1.b[i]);
    sub->AddRef();
    *out3 = sub;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x007760a0: build a runtime model instance from an arena resource key.
// 0x00776590 / 0x00776680: tear down a shader-preview object.
// ---------------------------------------------------------------------------
void* EAAllocate(size_t size, const char* name, int flags, int debugFlags, int file, int line);  // 0x00f473a0
void SetKeyKind(ResKey3* key, int kind, int flags);           // 0x0068c6d0

struct EABlockCookie { int users; };                          // EAAllocate keeps its owner count just before a block
inline bool EABlockInUse(void* block) { return ((EABlockCookie*)block)[-1].users != 0; }

struct Matrix3 {
    float rows[9];
    void Assign(const float* src);                            // 0x0041cb40
};
struct TransformPose {
    short flags;                                              // +0x00
    short id;                                                 // +0x02
    float qx, qy, qz, qw;                                     // +0x04..+0x13
    Matrix3 matrix;                                           // +0x14
};
struct BuilderOut;                                            // refcount at +0x04, Destroy at slot 0
struct Elem7c {
    Elem7c* Init(const TransformPose* src, IRefObj* sub, BuilderOut* builder);  // 0x00757e20
    void Destroy();                                           // 0x0041f2d0
    char bytes[0x7c];
};
struct ElemVec {
    Elem7c* begin; Elem7c* end; Elem7c* cap;
    void PushBack(Elem7c* elem);                              // 0x0041f650
};
struct MeshObj {
    virtual void AddRef();                                    // slot 0
    virtual void Release();                                   // slot 1
    MeshObj* Init();                                          // 0x007004d0
    char pad04[0x104];                                        // +0x004
    ElemVec elems;                                            // +0x108
    char pad114[0x20];                                        // +0x114
    float field134;                                           // +0x134
    char pad138[8];                                           // +0x138
};
struct BuilderOut {
    virtual void Destroy(int arg);                            // slot 0
    int refs;                                                 // +0x04
};
extern const float g_poseQuatX;                               // 0x01630b8c
extern const float g_poseQuatY;                               // 0x01630b90
extern const float g_poseQuatZ;                               // 0x01630b94
extern const float g_realOne;                                 // 0x01485720
extern const float g_bindMatrix[];                            // 0x01630ccc

// @ 0x007760a0  FUN_007760a0
int FUN_007760a0(Inst* inst, void** out, ResKey3 key, int arg8) {
    RefVec meshes;
    void* out3 = 0;
    void* out4 = 0;
    if (key.inst == 0xffffffff) {
        ArenaRes* arena = inst->sub_73d160();
        if (arena) {
            arena = inst->sub_73d160();
            key.inst = arena->keyInst;
            key.type = arena->keyType;
            key.group = arena->keyGroup;
            SetKeyKind(&key, 0x61, 0);
        }
    }
    int res = FUN_00775760(inst, &meshes, &out3, &out4, key, arg8);
    if (res == 0) {
        MeshObj* obj = (MeshObj*)EAAllocate(0x140, "Graphics", 0, 0, 0, 0);
        if (obj) obj = obj->Init();
        if (obj) obj->AddRef();
        obj->field134 = 0.0f;
        FUN_0072c100(&meshes, obj, -1, 0);

        TransformPose pose;
        pose.flags = 0;
        pose.id = 0;
        pose.qx = g_poseQuatX;
        pose.qy = g_poseQuatY;
        pose.qz = g_poseQuatZ;
        pose.qw = g_realOne;
        pose.matrix.Assign(g_bindMatrix);

        Elem7c elem;
        Elem7c* built = elem.Init(&pose, (IRefObj*)out3, (BuilderOut*)out4);
        obj->elems.PushBack(built);
        elem.Destroy();

        obj->AddRef();
        *out = obj;
        obj->Release();
    }
    int result = res;
    if (out4) {
        BuilderOut* builder = (BuilderOut*)out4;
        int refs = builder->refs - 1;
        builder->refs = refs;
        if (refs == 0) {
            builder->refs = 1;
            builder->Destroy(1);
        }
    }
    if (out3) ((IRefObj*)out3)->Release();
    return result;
}

// @ 0x00776320  FUN_00776320
int FUN_00776320(int instArg, int outMeshesArg, int out3Arg, int out4Arg, int arg8) {
    Inst* inst = (Inst*)instArg;
    if (inst) {
        ArenaRes* arena = inst->sub_73d160();
        if (arena) {
            ResKey3 key;
            key.inst = arena->keyInst;
            key.type = arena->keyType;
            key.group = arena->keyGroup;
            SetKeyKind(&key, 0x61, 0);
            return FUN_00775760(inst, (RefVec*)outMeshesArg, (void**)out3Arg, (void**)out4Arg, key, arg8);
        }
    }
    return 1;
}

struct Counted {
    void* vptr;                                               // +0x00
    int field04;                                              // +0x04
    volatile long refs;                                       // +0x08
    void Release() {
        _InterlockedDecrement(&refs);
        if (_InterlockedExchangeAdd(&refs, 0) < 1) _InterlockedIncrement(&refs);
        else _InterlockedExchangeAdd(&refs, 0);
    }
};
struct HtTable {
    void* base;                                               // +0x00
    void* buckets;                                            // +0x04
    unsigned bucketCount;                                     // +0x08
    unsigned elementCount;                                    // +0x0c
    void DoFreeNodes(void* buckets, unsigned bucketCount);    // 0x007611f0
    void FreeAll() {
        DoFreeNodes(buckets, bucketCount);
        elementCount = 0;
        if (bucketCount > 1) operator_delete_array(buckets);
    }
};
struct PtrVec {
    void** begin; void** end;
    void DestroyRange(void** begin, void** end);              // 0x0070f520
    void FreeAll() {
        DestroyRange(begin, end);
        if (begin && EABlockInUse(begin)) operator_delete_array(begin);
    }
};
struct ShaderPreview {
    void* vtbl0;                                              // +0x000
    int field04;                                              // +0x004
    void* vtbl8;                                              // +0x008
    char pad0c[0x100];                                        // +0x00c
    void* buffer10c;                                          // +0x10c
    char pad110[0x30];                                        // +0x110
    HtTable table;                                            // +0x140
    char pad150[0x10];                                        // +0x150
    PtrVec meshes;                                            // +0x160
    char pad168[0x0c];                                        // +0x168
    Counted* counted;                                         // +0x174
};
struct ShaderPreviewA : ShaderPreview { void Destroy(); };
struct ShaderPreviewB : ShaderPreview { void Destroy(); };

// @ 0x00776590  ShaderPreviewA::Destroy
void ShaderPreviewA::Destroy() {
    vtbl0 = (void*)0x140e670;
    vtbl8 = (void*)0x140e660;
    _ReadWriteBarrier();
    if (counted) counted->Release();
    meshes.FreeAll();
    table.FreeAll();
    if (buffer10c && EABlockInUse(buffer10c)) operator_delete_array(buffer10c);
    vtbl8 = (void*)0x13eb394;
    vtbl0 = (void*)0x13ec458;
}

// @ 0x00776680  ShaderPreviewB::Destroy
void ShaderPreviewB::Destroy() {
    vtbl0 = (void*)0x140e698;
    vtbl8 = (void*)0x140e688;
    meshes.FreeAll();
    table.FreeAll();
    if (buffer10c && EABlockInUse(buffer10c)) operator_delete_array(buffer10c);
    vtbl8 = (void*)0x13eb394;
    vtbl0 = (void*)0x13ec458;
}
