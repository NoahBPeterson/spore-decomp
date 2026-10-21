// Slice s00b362c0 — SP ref-counted object vector/map helpers + planet placement.
// Rebuilt from the retail disassembly (X360-era SP build).
// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"

// Skip N virtual slots (slot access via a wide vtable).  Each use needs a
// unique prefix p.
#define VS1(p)  virtual void p##_a();
#define VS2(p)  VS1(p##0) VS1(p##1)
#define VS4(p)  VS2(p##0) VS2(p##1)
#define VS8(p)  VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)
#define VS64(p) VS32(p##0) VS32(p##1)

// ------------------------------------------------------------------ external funcs
extern "C" {
void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
void  operator_delete(void* p);                                                    // 0xf47380
}
extern void* __stdcall SP_PlanetModel();                 // 0xb3d350
extern void* __stdcall SP_GonzagoModelWorld();           // 0xb3d520
extern void* __stdcall SP_EffectsManager();              // 0x67ddd0
extern void* __stdcall SP_MessageServer();               // 0x67dcc0
extern void* __fastcall SP_cPlanetModel_BuildSurfaceOrientation(void* self, const void* q, void* out); // 0xb7f250

// ------------------------------------------------------------------ external data
extern const char g_str_Simulator[];   // 0x13f09b4
extern const char g_str_EASTL[];       // 0x13f2150 (allocator)
// 0x1486110 (5.0f), 0x1418ef4 (-5.0f), 0x1485720 (1.0f)
extern float g_f1486110;   // 5.0f
extern float g_f1418ef4;   // -5.0f
extern float g_f1485720;   // 1.0f

// ---------------------------------------------------------------------------
// Ref-counted object reachable through a smart pointer.  The smart pointer
// stores a raw pointer to a handle whose refcount lives at +0x40; when the
// count drops to <=1 the handle is returned to its pool through a virtual
// release at vtable slot +0x170 taking (this, sign).
// ---------------------------------------------------------------------------
struct RefHandle;

struct RefOwner {
    VS64(v0) VS16(v1) VS8(v2) VS4(v3)
    virtual void Release(RefHandle* obj, bool sign);   // slot 92 (+0x170)
};

struct RefHandle {
    RefOwner* vtable;      // +0x00
    int field04;           // +0x04
    int pad[14];           // +0x08..0x40
    int refCount;          // +0x40

    // Decrement with release-to-pool when the last reference drops.
    void Decrement() {
        if (refCount > 1) {
            --refCount;
        } else {
            vtable->Release(this, (bool)((unsigned int)field04 >> 31));
        }
    }
};

// 8-byte element: { handle smart-pointer, float }.
struct RefPair {
    RefHandle* ptr;
    float value;
};

// ---------------------------------------------------------------------------
// 0x00b362c0  destroy a range of RefPair (returns the advanced out pointer)
// ---------------------------------------------------------------------------
// @ 0x00b362c0
RefPair* RefPair_DestroyRange(RefPair* first, RefPair* last, RefPair* out)
{
    while (first != last) {
        RefHandle* p = first->ptr;
        if (p) p->Decrement();
        first += 1;
        out += 1;
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b364c0  copy-assign a range of RefPair (dst <- src)
// ---------------------------------------------------------------------------
// @ 0x00b364c0
void RefPair_CopyAssign(RefPair* dst, RefPair* last, const RefPair* src)
{
    for (; dst != last; dst += 1) {
        RefHandle* nv = src->ptr;
        RefHandle* ov = dst->ptr;
        if (nv != ov) {
            if (nv) ++nv->refCount;
            dst->ptr = nv;
            if (ov) ov->Decrement();
        }
        dst->value = src->value;
    }
}

// ---------------------------------------------------------------------------
// 0x00b36530  copy a range of RefPair into out, returning the advanced out
// ---------------------------------------------------------------------------
// @ 0x00b36530
RefPair* RefPair_CopyConstruct(RefPair* first, RefPair* last, RefPair* out)
{
    while (first != last) {
        RefHandle* nv = first->ptr;
        RefHandle* ov = out->ptr;
        if (nv != ov) {
            if (nv) ++nv->refCount;
            out->ptr = nv;
            if (ov) ov->Decrement();
        }
        out->value = first->value;
        first += 1;
        out += 1;
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b365a0  copy a range of RefPair backwards, returning the new out
// ---------------------------------------------------------------------------
// @ 0x00b365a0
RefPair* RefPair_CopyConstructBackward(RefPair* first, RefPair* last, RefPair* out)
{
    while (last != first) {
        RefHandle* nv = (last - 1)->ptr;
        RefHandle* ov = (out - 1)->ptr;
        --last;
        --out;
        if (nv != ov) {
            if (nv) ++nv->refCount;
            out->ptr = nv;
            if (ov) ov->Decrement();
        }
        out->value = last->value;
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00b36610  swap two RefPairs
// ---------------------------------------------------------------------------
struct SmartPtrSlot { void Assign(RefHandle* p); };   // 0x478db0 (thiscall)

// @ 0x00b36610
void RefPair_Swap(RefPair* a, RefPair* b)
{
    RefHandle* pa = a->ptr;
    if (pa) ++pa->refCount;
    float tmp = a->value;
    ((SmartPtrSlot*)&a->ptr)->Assign(b->ptr);
    a->value = b->value;
    ((SmartPtrSlot*)&b->ptr)->Assign(pa);
    b->value = tmp;
    if (pa) pa->Decrement();
}

// ---------------------------------------------------------------------------
// 0x00b36320  map lookup helper: returns whether the found node is a real one
// ---------------------------------------------------------------------------
struct Rbtree;
struct RbtreeOps {
    void* Find(void* resultOut, const void* key);   // 0xe39fb0 (thiscall)
};

struct MapHolder {
    char pad0[0xc1];
    unsigned char alive;      // +0xc1
    char pad1[0xc8 - 0xc2];
    void* tree;               // +0xc8

    bool Lookup(int key);
};

// @ 0x00b36320
bool MapHolder::Lookup(int key)
{
    if (!alive) return false;
    void* dummy;
    void* node = ((RbtreeOps*)((char*)this + 0xc8))->Find(&dummy, &key);
    return *(void**)node == (char*)this + 0xcc;
}

// ---------------------------------------------------------------------------
// 0x00b36360  map erase helper
// ---------------------------------------------------------------------------
extern void* __stdcall RbtreeIncrement(void* node);            // 0x921580
extern void  __stdcall RBTreeErase(void* node, void* header);  // 0x921880

struct MapErase {
    void* header;   // +0x00
    int   pad;      // +0x04 (header+0 = sentinel; +4 is next)
    char  pad2[0x14 - 8];
    int   count;    // +0x14

    bool Erase(void* key);
};

// @ 0x00b36360
bool MapErase::Erase(void* key)
{
    void* node;
    ((RbtreeOps*)&header)->Find(&node, key);
    if (node == &header) return false;
    --count;
    RbtreeIncrement(node);
    RBTreeErase(node, &header);
    operator_delete(node);
    return true;
}

// ---------------------------------------------------------------------------
// 0x00b36440  map insert helper
// ---------------------------------------------------------------------------
extern void __stdcall RBTreeInsert(void* node, void* parent, void* header, int side); // 0x9216a0

struct MapInsert {
    void* header;  // +0x00
    char  pad2[0x14 - 4];
    int   count;   // +0x14

    void Insert(void** out, void* parent, const int* key, char flag);
};

// @ 0x00b36440
void MapInsert::Insert(void** out, void* parent, const int* key, char flag)
{
    unsigned int side;
    if (flag == 0 && parent != &header && *key <= *(int*)((char*)parent + 0x10))
        side = 1;
    else
        side = 0;

    char* node = (char*)EAAllocate(0x14, g_str_Simulator, 0, 0, 0, 0);
    if (node + 0x10)
        *(int*)(node + 0x10) = *key;
    RBTreeInsert(node, parent, &header, side);
    ++count;
    *out = node;
}

// ---------------------------------------------------------------------------
// 0x00b370f0  sort helper
// ---------------------------------------------------------------------------
struct SortElem;

extern void __stdcall SortFunc1(void* a, void* b, void* c);   // 0xb363b0
extern void __stdcall SortFunc2(void* a, void* b, void* c);   // 0xb363f0

// Virtual-slot call helpers (__thiscall).
typedef float (__thiscall* SortKeyFn)(void*);
typedef void* (__thiscall* Thiscall0)(void*);
typedef void* (__thiscall* Thiscall1)(void*, int);
typedef void* (__thiscall* Thiscall1p)(void*, void*);
typedef void* (__thiscall* Thiscall2)(void*, int, int);

extern void __stdcall SortInsert(void* a, int b, int c, int d, void* e, void* f); // 0xb36180

extern float __fastcall SortKey(void* self);   // 0xc887c0 (ecx-based)

// @ 0x00b370f0
void RefPair_Sort(void* base, void* mid, void* end, void* key)
{
    SortFunc1(base, mid, key);
    for (char* p = (char*)mid; p < (char*)end; p += 4) {
        float a = SortKey(*(void**)p);
        float b = SortKey(*(void**)base);
        if (a < b) {
            void* v = *(void**)p;
            *(void**)p = *(void**)base;
            SortInsert(base, 0, (int)((char*)mid - (char*)base) >> 2, 0, v, key);
        }
    }
    SortFunc2(base, mid, key);
}

// ---------------------------------------------------------------------------
// 0x00b36690  SP::cGalaxyGameEntryImpl::SetGameToEnter
// ---------------------------------------------------------------------------
struct GonzagoModelWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(void*, int);
};

extern void* __stdcall Gonzago_Fn1(void* a, int b);    // 0xb3d320
extern void* __stdcall TerrainMgr_Fn1(void* a, int b); // 0xb1daf0
extern void* __stdcall GalaxyImpl_Fn7360(void* a);     // 0xad7360

extern "C" void* SlotMessage_Construct(void* self, int a);   // 0x421c80
extern "C" void  SlotMessage_Destruct(void* self);           // 0x421cf0
extern void* __stdcall GalaxyGetString(void* a);             // 0x1186577

class cGalaxyGameEntryImpl {
public:
    unsigned int SetGameToEnter(unsigned int msg, unsigned int arg);
};

// @ 0x00b36690
unsigned int cGalaxyGameEntryImpl::SetGameToEnter(unsigned int msg, unsigned int arg)
{
    unsigned int result;
    if (msg < 0x4b719d5u) {
        if (msg == 0x4b719d4u) {
            void* p = *(void**)(arg + 8);
            GonzagoModelWorld* w = (GonzagoModelWorld*)SP_GonzagoModelWorld();
            result = 0;
            if (w) {
                w->v00();
                void* a = Gonzago_Fn1(p, 0);
                void* b = TerrainMgr_Fn1(a, 0);
                w->v18(b, 0);
                w->v04();
                return 0;
            }
        } else if (msg == 0x1a0219eu) {
            void* p = *(void**)(arg + 0x10);
            if (p) {
                if (*(int*)(arg + 8) == 3)
                    ((Thiscall1p)((void**)*(void**)((char*)this - 4))[0x54/4])((char*)this - 4, p);
                if (*(int*)(arg + 8) == 4) {
                    ((Thiscall1p)((void**)*(void**)((char*)this - 4))[0x58/4])((char*)this - 4, p);
                    return 0;
                }
            }
        } else if (msg == 0x30c11c7u && arg != 0) {
            int v = (int)GalaxyImpl_Fn7360((void*)(arg + 0x10));
            result = 0;
            if (v) {
                unsigned char buf[0x40];
                SlotMessage_Construct(buf, 0);
                *(unsigned int*)(buf + 0x20) = 0x3047cb34;
                SlotMessage_Destruct(buf);
                return 0;
            }
        }
    } else if (msg == 0x3047cb34u) {
        result = arg;
        if (*(void**)(arg + 8)) {
            unsigned int a = *(unsigned int*)(arg + 0x10);
            unsigned int b = *(unsigned int*)(arg + 0x18);
            unsigned int c = *(unsigned int*)(arg + 0x20);
            (void)a; (void)b; (void)c;
        }
    }
    return result & 0xffffff00u;
}

// ---------------------------------------------------------------------------
// 0x00b36820  SP planet-placement helper
// ---------------------------------------------------------------------------
struct PlanetModel2;
extern void* __stdcall PlanetModel_Fn0(void* a, int b);   // 0xb532b0
extern void* __fastcall PlanetModel_Fn1(void* self);       // 0xaef2e0
extern void* __stdcall PlanetModel_Fn2(void* a, int b);    // 0xad7360
extern void* __stdcall Vector3Fn1(void* a, void* b, void* c);   // 0x99c310
extern void* __stdcall Vector3Fn2(void* a, void* b, void* c);   // 0x99c1a0
extern void __stdcall PlaceFn1(void* a, void* b, void* c, void* d, void* e, void* f, int g); // 0xb668c0
extern void __stdcall PlaceFn2(void* a, void* b, void* c, void* d, void* e, void* f, int g); // 0xb669b0
extern void __stdcall PlaceFn3(void* a, void* b, void* c, void* d, void* e, void* f, int g); // 0xb66aa0

extern void* g_167ecd0;   // 0x0167ecd0 planet placement manager

// @ 0x00b36820
float Planet_PlaceDistance(void* entry, void* model, float* pos, void* out, int a4, char flag)
{
    void* pm = SP_PlanetModel();
    if (!pm || !g_167ecd0) return 0.0f;

    if (flag != 0) {
        void* p = *(void**)((char*)pm + 0x24);
        if (!p) return 0.0f;
        void* r = ((Thiscall0)((void**)*(void**)p)[0xc/4])(p);
        return *(float*)((char*)r + 0x3c) * *(float*)((char*)r + 0x38) + *(float*)((char*)r + 0x34);
    }

    float lo = g_f1418ef4;   // -5.0f
    float hi = g_f1486110;   // 5.0f
    int found = 0;
    char ch = 0;
    if (entry && *(void**)((char*)entry + 0x180)) {
        void* p = *(void**)((char*)entry + 0x180);
        p = (char*)p + 100;
        void* h = PlanetModel_Fn2(p, 0);
        found = h ? (int)PlanetModel_Fn0(h, 0) : 0;
        if (found) {
            void* v = PlanetModel_Fn1((void*)found);
            if (v) {
                void* v2 = PlanetModel_Fn1((void*)found);
                void* obj = *(void**)((char*)v2 + 0x58);
                hi = *(float*)((char*)obj + 0x98);
                ch = *(char*)((char*)h + 0x77);
                lo = -hi;
            }
        }
    }
    (void)lo; (void)hi; (void)ch;
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x00b36bb0  effects-manager driver
// ---------------------------------------------------------------------------
struct EffectsManager2 {
    virtual bool v00(); virtual bool v04(); virtual bool v08();
    virtual bool v0c(); virtual bool v10(); virtual bool v14(); virtual bool v18();
    virtual bool v1c(); virtual bool v20(); virtual bool v24(); virtual bool v28();
    virtual bool Fn2c(int a, int b, void** out);   // +0x2c
};

struct HashOps {
    char pad0[4];
    void* buckets;   // +0x04
    int   mask;      // +0x08

    void* Find(void* resultOut, const void* key);   // 0x5538f0 (thiscall)
};

struct HashHolder {
    char pad0[0x8c];
    char hashobj[0x10];   // +0x8c hash table object

    void Drive(unsigned int id);
};

extern void* RefCounted_Release(void* self, int flag);      // (virtual slot 4)
extern void* RefCounted_Dtor(void* self, int flag);         // (virtual slot 8)

// @ 0x00b36bb0
void HashHolder::Drive(unsigned int id)
{
    void* node;
    void* dummy;
    (void)dummy;
    HashOps* h = (HashOps*)((char*)this + 0x8c);
    h->Find(&node, &id);
    if (node == (void*)((char*)h->buckets + h->mask * 4)) return;

    void* obj = 0;
    EffectsManager2* mgr = (EffectsManager2*)SP_EffectsManager();
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
    bool ok = mgr->Fn2c(*(int*)((char*)node + 8), *(int*)((char*)node + 0xc), &obj);
    if (ok) ((Thiscall1)((void**)*(void**)node)[8/4])(node, 0);
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
}

// ---------------------------------------------------------------------------
// 0x00b36c40  build a matrix from two points + planet surface, push to effects
// ---------------------------------------------------------------------------
struct RwMatrix33 { float m[9]; };
extern void* __stdcall Matrix3_Assign(void* self, const void* src);       // 0x41cb40
extern void* __stdcall Matrix3FromQuaternion(void* out, const void* q);   // 0x59c190
extern void* __fastcall PlanetModel_BuildSurfaceOrientation(void* self, void* a, void* b); // 0xb7f250

// @ 0x00b36c40
void HashHolder_PushOrientation(HashHolder* self, void* p1, void* p2, void* out)
{
    void* node;
    HashOps* h = (HashOps*)((char*)self + 0x8c);
    h->Find(&node, &p1);
    if (node == (void*)((char*)h->buckets + h->mask * 4)) return;

    void* obj = 0;
    EffectsManager2* mgr = (EffectsManager2*)SP_EffectsManager();
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
    bool ok = mgr->Fn2c(*(int*)((char*)node + 8), *(int*)((char*)node + 0xc), &obj);
    if (!ok) {
        if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
        return;
    }

    float* a = (float*)p1;
    float* b = (float*)p2;
    float dx = a[0] - b[0];
    float dy = a[1] - b[1];
    float dz = a[2] - b[2];
    float len = dz * dz + dy * dy + dx * dx;
    (void)len;

    void* pm = SP_PlanetModel();
    (void)pm;
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
}

// ---------------------------------------------------------------------------
// 0x00b36f30  build orientation from planet normal, push to effects
// ---------------------------------------------------------------------------
extern void* __stdcall SP_normalized_safe(void* out, const void* v);   // 0x449c20
extern void* __stdcall SP_OrthogonalVector(void* out, const void* v);  // 0x6985b0
extern void* __stdcall SP_Matrix3FromFacingAndUp(void* out, const void* up, const void* facing); // 0x69b440

// @ 0x00b36f30
void HashHolder_PushOrientation2(HashHolder* self, void* p)
{
    void* node;
    HashOps* h = (HashOps*)((char*)self + 0x8c);
    h->Find(&node, &p);
    if (node == (void*)((char*)h->buckets + h->mask * 4)) return;

    void* obj = 0;
    EffectsManager2* mgr = (EffectsManager2*)SP_EffectsManager();
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
    bool ok = mgr->Fn2c(*(int*)((char*)node + 8), *(int*)((char*)node + 0xc), &obj);
    if (!ok) {
        if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
        return;
    }

    void* pm = SP_PlanetModel();
    (void)pm;
    if (obj) ((Thiscall1)((void**)*(void**)obj)[4/4])(obj, 0);
}
