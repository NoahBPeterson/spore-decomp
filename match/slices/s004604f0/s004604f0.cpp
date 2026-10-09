// Slice s004604f0: creature-material / mesh helpers of the second module.
// /Od /Ob1 /MD /Gy /TP /arch:SSE.
#include "types.h"

extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedIncrement)
#pragma intrinsic(_InterlockedExchange)

extern char g_sentinel2;   // 0x01667bac

// =====================================================================
// @ 0x461290  intrusive AddRef (thread-safe)
// =====================================================================
struct RefCounted {
    char         pad[8];
    volatile long mnRefCount;
    int AddRef();
};

int RefCounted::AddRef()
{
    return _InterlockedIncrement(&mnRefCount);
}

// =====================================================================
// @ 0x461400  initialise three string-like sub-objects
// =====================================================================
struct Sub {
    void* b;
    void* e;
    void* c;
};

struct C461400 {
    char  pad0[4];
    Sub   sub1;       // +0x04
    char  pad1[0x18];
    Sub   sub2;       // +0x28
    char  pad2[8];
    void* p3c;        // +0x3c
    void* p40;        // +0x40
    C461400* Ctor();
};

C461400* C461400::Ctor()
{
    Sub* s1 = &sub1;
    s1->b = 0;
    s1->e = 0;
    s1->c = 0;
    s1->b = &g_sentinel2;
    s1->e = s1->b;
    s1->c = (char*)s1->b + 2;
    Sub* s2 = &sub2;
    s2->b = 0;
    s2->e = 0;
    s2->c = 0;
    void** p3 = &p3c;
    *p3 = 0;
    void** p4 = &p40;
    *p4 = 0;
    return this;
}

// =====================================================================
// @ 0x460a80  recursive primitive-batch reorder, returns consumed count
// =====================================================================
int FUN_00460a80(int verts, int target, int* ids, int count)
{
    int out = 0;
    int i = 0;
    while (i < count) {
        if (target == *(short*)(verts + ids[i] * 4)) {
            int id = ids[i];
            ids[i] = ids[out];
            ids[out] = id;
            out = out + 1;
            int n = FUN_00460a80(verts, id, ids + out, count - out);
            out = n + out;
        }
        int nxt = i + 1;
        int* chosen;
        if (nxt < out) {
            chosen = &out;
        } else {
            chosen = &nxt;
        }
        i = *chosen;
    }
    return out;
}

// =====================================================================
// Skeleton-bone helpers (stride 0x8c; +4 short parent, +0x2c float weight, +0x54 Vector3)
// =====================================================================
struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) { x = o.x; y = o.y; z = o.z; } };
extern Vec3* __cdecl Vector3_Add(Vec3* a, const Vec3* b);                           // 0x41ddb0
extern Vec3* __cdecl Vector3_Sub(Vec3* out, const Vec3* a, const Vec3* b);          // 0x41db10
extern Vec3* __cdecl Vector3_Scale(Vec3* out, const Vec3* a, const float* s);       // 0x41dca0

struct Bone {
    char  pad0[4];
    short parent;      // +4
    char  pad1[0x26];
    float weight;      // +0x2c
    char  pad2[0x24];
    Vec3  pos;         // +0x54
    char  pad3[0x8c - 0x60];
};

// @ 0x460b50  add an offset to every descendant of bone `root`, recursively
void FUN_00460b50(Bone* bones, int count, int root, Vec3 offs)
{
    for (int i = root + 1; i < count; i++) {
        if (bones[i].parent == root) {
            Vector3_Add(&bones[i].pos, &offs);
            FUN_00460b50(bones, count, i, offs);
        }
    }
}

// @ 0x460bf0  scale a bone's weight and push an interpolated offset down to its children
void FUN_00460bf0(Bone* bones, int count, int root, float t)
{
    bones[root].weight = bones[root].weight * t;
    for (int i = root + 1; i < count; i++) {
        if (bones[i].parent == root) {
            Vec3 n28;
            int v2;
            Vec3* hi = Vector3_Sub(&n28, &bones[root].pos, &bones[i].pos);
            Vec3 p30;
            p30.x = hi->x; p30.y = hi->y; p30.z = hi->z;
            float key = 1.0f - t;
            Vec3 v9;
            Vector3_Add(&bones[i].pos, Vector3_Scale(&v9, &p30, &key));
            FUN_00460b50(bones, count, i, p30);
        }
    }
}

// =====================================================================
// Shared eastl-style containers
// =====================================================================
template<int N> inline void ScratchSlots() { unsigned int s[N]; }
inline void* operator new(unsigned, void* p) { return p; }
struct EmptyAlloc { EmptyAlloc() {} };
struct Alloc {
    int a, b;
    Alloc() {}
    Alloc* __thiscall Copy(const EmptyAlloc& o);   // 0x429360 (copy ctor)
};
template <class T> struct Vec {         // vector with a real allocator sub-object (0x14 bytes)
    T* b; T* e; T* c;
    Alloc al;
    void Init(const EmptyAlloc& a) { b = 0; e = 0; c = 0; al.Copy(a); }
};
template <class T> struct VecPlain {    // vector with an empty allocator (0x14 bytes)
    T* b; T* e; T* c;
    int pad[2];
    void Init() { b = 0; e = 0; c = 0; }
};

void* operator new(unsigned n, const char* name, int, int, int, int);   // 0xf473a0

// =====================================================================
// @ 0x460f80  clear-state constructor (7 vectors of 0x14 bytes)
// =====================================================================
struct C460f80 {
    Vec<int>       v0;      // 0x00
    Vec<int>       v1;      // 0x14
    Vec<int>       v2;      // 0x28
    VecPlain<int>  v3;      // 0x3c
    VecPlain<int>  v4;      // 0x50
    VecPlain<int>  v5;      // 0x64
    VecPlain<int>  v6;      // 0x78
    C460f80* __thiscall Ctor();
};


C460f80* C460f80::Ctor()
{
    char t2, t1, t0;
    ScratchSlots<1>();
    v0.Init(*(const EmptyAlloc*)&t2);
    v1.Init(*(const EmptyAlloc*)&t1);
    v2.Init(*(const EmptyAlloc*)&t0);
    v3.Init();
    v4.Init();
    v5.Init();
    v6.Init();
    return this;
}

// =====================================================================
// @ 0x4610c0 / 0x4612e0  cEditorResource-derived object ctor / dtor
// =====================================================================
extern void* vt_4610c0_a[];   // 0x13eb938
extern void* vt_4610c0_b[];   // 0x13ef094
extern void* vt_final_a[];    // 0x13eece0
extern void* vt_final_b[];    // 0x13eecdc

#define DEFVEC(NAME, ALLOC, STRIDE, FREE) \
    struct NAME { char* b; char* e; char* c; ALLOC \
        __forceinline void Dtor() { char* p; ScratchSlots<3>(); for (p = b; p < e; p += STRIDE) {} FREE(this); } };
#define DEFVEC0(NAME, ALLOC, FREE) \
    struct NAME { char* b; char* e; char* c; ALLOC \
        __forceinline void Dtor() { ScratchSlots<1>(); FREE(this); } };
extern void __fastcall Free_4e1bf0(void*);
extern void __fastcall Free_4748c0(void*);
extern void __fastcall Free_45daf0(void*);
extern void __fastcall Free_4cddd0(void*);
extern void __fastcall Free_5156b0(void*);
extern void __fastcall Free_540520(void*);
extern void __fastcall Free_425990(void*);
DEFVEC0(V98, int pad[2];, Free_4e1bf0)
DEFVEC0(V84, int pad[2];, Free_4748c0)
DEFVEC(V70, int pad[2];, 8, Free_45daf0)
DEFVEC0(V5c, Alloc al;, Free_4cddd0)
DEFVEC(V48, Alloc al;, 0xc, Free_5156b0)
DEFVEC(V34, Alloc al;, 0xc, Free_5156b0)
DEFVEC0(V20, Alloc al;, Free_540520)
DEFVEC(V0c, Alloc al;, 4, Free_425990)

struct Er { void* vtbl; Er() { vtbl = vt_4610c0_a; } };
struct Cnt { volatile long n; Cnt() { _InterlockedExchange(&n, 0); } };
struct AbBase { void* vtbl; AbBase() { vtbl = vt_4610c0_b; } };
struct Ab : AbBase { Cnt cnt; };

struct C4610c0 {
    Er  er;                    // +0
    Ab  ab;                    // +4 (+8 refcount)
    V0c v0c;                   // +0x0c  elem 4
    V20 v20;                   // +0x20
    V34 v34;                   // +0x34  elem 0xc
    V48 v48;                   // +0x48  elem 0xc
    V5c v5c;                   // +0x5c
    V70 v70;                   // +0x70  elem 8
    V84 v84;                   // +0x84
    V98 v98;                   // +0x98
    C4610c0();                 // 0x4610c0
    void __thiscall Dtor();    // 0x4612e0
};

// @ 0x4610c0
C4610c0::C4610c0()
{
    char t0, t1, t2, t3, t4;
    er.vtbl = vt_final_a;
    ab.vtbl = vt_final_b;
    ((Vec<int>*)&v0c)->Init(*(const EmptyAlloc*)&t2);
    ((Vec<int>*)&v20)->Init(*(const EmptyAlloc*)&t3);
    ((Vec<int>*)&v34)->Init(*(const EmptyAlloc*)&t1);
    ((Vec<int>*)&v48)->Init(*(const EmptyAlloc*)&t4);
    ((Vec<int>*)&v5c)->Init(*(const EmptyAlloc*)&t0);
    ((VecPlain<int>*)&v70)->Init();
    ((VecPlain<int>*)&v84)->Init();
    ((VecPlain<int>*)&v98)->Init();
}

// @ 0x4612e0
void C4610c0::Dtor()
{
    v98.Dtor();
    v84.Dtor();
    v70.Dtor();
    v5c.Dtor();
    v48.Dtor();
    v34.Dtor();
    v20.Dtor();
    v0c.Dtor();
    ab.vtbl = vt_4610c0_b;
    er.vtbl = vt_4610c0_a;
}

// =====================================================================
// @ 0x460d40  gather mesh pieces of a model and build game meshes
// =====================================================================
struct Piece { int a, b; };
struct PieceVec {                       // 0x14: vector<Piece>
    Piece* b; Piece* e; Piece* c; Alloc al;
    unsigned size() { return e - b; }
    Piece* data() { return b; }
};
struct PieceVecList {                   // vector<PieceVec>
    PieceVec* b; PieceVec* e; PieceVec* c; Alloc al;
    PieceVecList(const EmptyAlloc& a = EmptyAlloc()) { b = 0; e = 0; c = 0; al.Copy(a); }
    ~PieceVecList();                    // 0x432de0
    PieceVec* at(unsigned i) { return b + i; }
    unsigned size() { return e - b; }
};

struct RefObj {
    void* vt;
    int   mnRefCount;      // +4
    int AddRef() { return mnRefCount++ + 1; }
    void __thiscall Release();                               // 0x453540
    void __thiscall GetPieces(int src, PieceVecList* out);   // 0x7a0ee0
};
struct AutoRef {
    RefObj* p;
    AutoRef(RefObj* x) { p = x; if (p) p->AddRef(); }
    ~AutoRef() { if (p) p->Release(); }
};
struct EditorPropList {
    char pad[0x38];
    EditorPropList();                              // 0x6a1c40
    void __thiscall SetParent(int parent);         // 0x6a1710
};
struct PropMgr2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void SetPropList(EditorPropList* pl, int a, int b);     // +0x34
};
extern PropMgr2* __cdecl GetPropertyManager();                            // 0x67de30
extern void __cdecl GetFloatProperty(int owner, int key, float* out);     // 0x40cf10
extern RefObj* __cdecl FUN_0079ab90(int a, int b, void* data, int n);
extern float g_const_1486114;       // 0x1486114
extern int   g_3e8c[3];             // 0x15d3e8c
struct RefVec {
    Piece** b; Piece** e; Piece** c; Alloc al;
    RefVec(const EmptyAlloc& a = EmptyAlloc()) { b = 0; e = 0; c = 0; al.Copy(a); }
    ~RefVec();                                 // 0x41eb80
    void __thiscall PushBack(Piece* p);        // 0x41ef20
    char __thiscall IsResourceType();          // 0x526430 (SP::GetResourceTypeFromModelType)
};
extern void __cdecl GetModelAsGameMeshes(int a, RefVec* v, int b, int c, int d, int e, EditorPropList* pl,
                                         int f, int g, int h, int i, int j);   // 0x7573a0

// @ 0x460d40
void FUN_00460d40(int p1, int p2, int p3, int p4, int p5, int p6, int p7)
{
    int   t24[3];
    float u;
    t24[0] = g_3e8c[0];
    t24[1] = g_3e8c[1];
    t24[2] = g_3e8c[2];
    u = g_const_1486114;
    GetFloatProperty(p2, 0x67ef6b0, &u);
    AutoRef v33(FUN_0079ab90(1, 0, t24, 4));

    PieceVecList p30;
    v33.p->GetPieces(p3, &p30);

    RefVec v28;
    unsigned obj = p30.size();
    for (unsigned i = 0; i < obj; i++) {
        unsigned j = 0;
        unsigned n = p30.at(i)->size();
        for (; j < n; j++) {
            v28.PushBack(p30.at(i)->data() + j);
        }
    }

    EditorPropList* n37 = new ("Graphics", 0, 0, 0, 0) EditorPropList();
    n37->SetParent(p2);
    GetPropertyManager()->SetPropList(n37, p4, p5);
    if (!v28.IsResourceType()) {
        GetModelAsGameMeshes(p1, &v28, p4, p5, p6, 0, n37, 0, 0, 0, 0, p7);
    }
}

// =====================================================================
// @ 0x4604f0  BuildCreatureMaterialInfo
// =====================================================================
struct MatInfo {
    char  pad[0xc];
    char  kind;       // +0xc
    char  pad1[3];
    float f10, f14, f18, f1c;
    MatInfo();        // 0x432cf0
};
extern float g_f1485720;   // 0x1485720
extern float g_f13eecd8;   // 0x13eecd8
extern float g_f13ec480;   // 0x13ec480
extern float g_f1471064;   // 0x1471064
struct IRef { virtual void v0(); virtual void Release(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
              virtual void v6(); virtual void v7(); virtual void v8();
              virtual bool GetProperty(unsigned key, struct Property** out); };
struct Property { char pad[0x12]; unsigned short type; int* __thiscall GetInt(); };
struct PropMgr3 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(unsigned id, unsigned group, IRef** out);   // +0x2c
};
struct ShaderRes {
    char pad[0x70];
    ShaderRes();                                       // 0x40d010
    void __thiscall InsertResource(int slot, int res); // 0x77cb10
    void __thiscall setSlotU0(int slot, int v);        // 0x777a60
    void __thiscall setSlotU1(int slot, int v);        // 0x777a80
    void __thiscall setSlotV0(int slot, int v);        // 0x777aa0
    void __thiscall setSlotV1(int slot, int v);        // 0x777ac0
};
struct ResMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                virtual int GetResource(unsigned key, int a, int b); };   // +0x20
extern PropMgr3* __cdecl GetPropertyManager3();   // 0x67de30
extern ResMgr* __cdecl GetResMgr();               // 0x67dd60
struct PtrVector { void __thiscall PushBack(void* p); };   // 0x77d970
struct C472660 { char pad[0xc]; C472660(); };   // 0x472660
struct C4726d0 { char pad[0xc]; C4726d0(); };   // 0x4726d0

// @ 0x4604f0
void BuildCreatureMaterialInfo(PtrVector* out, unsigned id, int tex0, int tex1, int unused, char skipLookup)
{
    MatInfo* mi = new ("Editor", 0, 0, 0, 0) MatInfo();
    mi->f18 = g_f1485720;
    mi->f10 = g_f13eecd8;
    mi->f14 = g_f13ec480;
    mi->f1c = g_f1471064;
    if (id == 0x3d97a8e4) {
        mi->kind = 4;
    } else if (id == 0x438f6347) {
        mi->kind = 5;
    } else {
        int level = 2;
        if (!skipLookup) {
            unsigned key = 0x4529f96f;
            unsigned group = 0x40626200;
            IRef* list = 0;
            PropMgr3* pm = GetPropertyManager3();
            if (list) {
                IRef* t = list;
                list = 0;
                t->Release();
            }
            if (pm->GetPropertyList(key, group, &list)) {
                IRef* l = list;
                if (l) {
                    Property* prop;
                    if (l->GetProperty(0x4c6ba3c, &prop)) {
                        if (prop->type == 9) level = *prop->GetInt();
                    }
                }
            }
            if (list) list->Release();
        }
        if (level >= 2) mi->kind = 7; else mi->kind = 6;
    }
    out->PushBack(mi);
    int flag = tex0 != 0;
    if (mi->kind == 4) {
        ShaderRes* sr = new ("Editor", 0, 0, 0, 0) ShaderRes();
        int r2 = GetResMgr()->GetResource(0x552a5077, 0, 0);
        sr->InsertResource(0, tex0);
        sr->setSlotU0(0, 3); sr->setSlotU1(0, 2); sr->setSlotV0(0, 2); sr->setSlotV1(0, flag);
        sr->InsertResource(1, tex1);
        sr->setSlotU0(1, 3); sr->setSlotU1(1, 2); sr->setSlotV0(1, 2); sr->setSlotV1(1, flag);
        sr->InsertResource(2, r2);
        sr->setSlotU0(2, 3); sr->setSlotU1(2, 2); sr->setSlotV0(2, 2); sr->setSlotV1(2, flag);
        out->PushBack(sr);
    } else if (mi->kind == 7 || mi->kind == 5) {
        ShaderRes* sr = new ("Editor", 0, 0, 0, 0) ShaderRes();
        sr->InsertResource(0, tex0);
        sr->setSlotU0(0, 1); sr->setSlotU1(0, 2); sr->setSlotV0(0, 2); sr->setSlotV1(0, flag);
        sr->InsertResource(1, tex1);
        sr->setSlotU0(1, 3); sr->setSlotU1(1, 2); sr->setSlotV0(1, 2); sr->setSlotV1(1, flag);
        out->PushBack(sr);
    } else if (mi->kind == 6) {
        ShaderRes* sr = new ("Editor", 0, 0, 0, 0) ShaderRes();
        sr->InsertResource(0, tex0);
        sr->setSlotU0(0, 1); sr->setSlotU1(0, 2); sr->setSlotV0(0, 2); sr->setSlotV1(0, flag);
        out->PushBack(sr);
    }
    if (id == 0x2b978c46) {
        out->PushBack(new ("Editor", 0, 0, 0, 0) C472660());
    } else if (id == 0x3d97a8e4) {
        out->PushBack(new ("Editor", 0, 0, 0, 0) C4726d0());
    }
}
// --- equivalence checker address annotations
    extern float g_f13ec480; // 0x013ec480
    extern float g_f13eecd8; // 0x013eecd8
    extern float g_f1471064; // 0x01471064
    extern float g_f1485720; // 0x01485720

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EditorPropList {
    void SetParent(int); // 0x006a1710
    EditorPropList(); // 0x006a1c40
};
}
