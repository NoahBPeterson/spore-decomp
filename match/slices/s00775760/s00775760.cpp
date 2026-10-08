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
    void setBoneA(int unused, const float* v, float w, int unused2);
    // @ 0x00776520
    void setBoneB(int unused, const float* v, float w, int unused2);
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

void cRuntimeModelBuilder::setBoneA(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x120) = v[0];
    *(float*)((char*)this + 0x124) = v[1];
    *(float*)((char*)this + 0x128) = v[2];
    *(float*)((char*)this + 0x12c) = w;
}

void cRuntimeModelBuilder::setBoneB(int unused, const float* v, float w, int unused2) {
    (void)unused;
    (void)unused2;
    *(float*)((char*)this + 0x12c) = v[0];
    *(float*)((char*)this + 0x130) = v[1];
    *(float*)((char*)this + 0x134) = v[2];
    *(float*)((char*)this + 0x138) = w;
}

// ---------------------------------------------------------------------------
// Large EH-framed routines -- skeletons (partial).
// @ 0x00775760, 0x007760a0, 0x00776320, 0x00776590, 0x00776680
// ---------------------------------------------------------------------------
int FUN_00776320(int a, int b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 1;
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
struct Inst {
    char pad[0xf0]; Drawer* draw;
    bool sub_73eb90(RefVec* out);                             // GetMeshes, ret 4
    void* sub_73d160();                                       // GetArenaResource
    void sub_73ba50(void (*fn)());                            // ret 4
};
struct Builder { void sub_775230(void** p); };                // ret 4
extern Builder g_builder_1630b68;
void FUN_007740f0();

int FUN_006ac0a0(int a, void* p);
bool FUN_00757d20(void* p);
void FUN_0072fff0(void* p, RefVec* out);
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

int FUN_007760a0(int a, void* b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0;
}
void FUN_00776590(int* p) {
    (void)p;
}
void FUN_00776680(int* p) {
    (void)p;
}
