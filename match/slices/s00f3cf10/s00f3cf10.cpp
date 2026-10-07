// Slice s00f3cf10: an editor-side "catalog / thumbnail" helper class.
// Optimized module: /O2 /MD /Gy /EHsc /TP.
//
// Recovered `this` offsets (used directly to avoid anonymous-field layout drift):
//   +0x10  Inner*  (Inner+0x68 = mode: 0/2)
//   +0x18  int f18, +0x1c char f1c
//   +0x30  void* f30, +0x38 ImageRes
//   +0x8c  int f8c
//   +0xb4  int** fB4, +0xb8 int fB8
//   +0xe8 int fE8, +0xf0 int fF0
//   +0x124 char f124
typedef unsigned int uint32_t;
#include <intrin.h>

void* operator new(unsigned sz, const char* tag, int, int, int, int);

// VFN(o, off, R, args): call virtual slot at byte offset `off` of o (thiscall).
#define VFN(o, off, R, args) ((R (__thiscall*)args)(*(void***)(o))[(off) / 4])
#define I(p, off) (*(int*)((char*)(p) + (off)))
#define PI(p, off) (*(void**)((char*)(p) + (off)))
#define F(off) (*(int*)((char*)this + (off)))

// Atomic intrusive refcount at +8 (decrement, re-read, restore on underflow), as inlined by the original.
static inline void ReleaseRef(void* o) {
    volatile long* c = (volatile long*)((char*)o + 8);
    _InterlockedExchangeAdd(c, -1);
    long n = _InterlockedExchangeAdd(c, 0);
    if (n < 1) _InterlockedExchangeAdd(c, 1);
    else _InterlockedExchangeAdd(c, 0);
}
static inline void AssignRef(void** slot, void* nv) {
    void* old = *slot;
    if (nv != old) {
        if (nv) _InterlockedExchangeAdd((volatile long*)((char*)nv + 8), 1);
        *slot = nv;
        if (old) ReleaseRef(old);
    }
}

struct IObj20 {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0C();
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1C();
    virtual void* v20(int, int, int);
};
struct cImgRes { void GetImageResource(void* p); };
struct cLayoutCollection { void Show(); };

struct ResKey { int a, b, c; };
struct Iter8 { char* node; char** bucket; };    // eastl hashtable_iterator (8 bytes, returned via sret)
struct Hashtable {
    int pad0; char** mpBucketArray; unsigned mnBucketCount;
    Iter8 find(const unsigned& k) const;
};
struct EStr3 { char* b; char* e; char* c; };    // eastl::string begin/end/capacity
struct EStrHolder { void assign(const char* b, const char* e); };

// Panel object created by FUN_00f3cf10 (0x2c bytes, vtable 0x1462d70): ref counted, with an eastl::string at +0x18.
struct BObj { BObj(); virtual void AddRef(); virtual void Release(); };
struct PanelObj {
    PanelObj() {
        mCount = 0;
        mB = 0; mImg = 0;
        str.b = (char*)0x1667bac; str.e = (char*)0x1667bac; str.c = (char*)0x1667bad;
    }
    virtual void v0();
    virtual void AddRef();
    virtual void Dtor2();
    int mCount;
    float mFloat; int mZero;
    BObj* mB; void* mImg;
    EStr3 str;
    int pad24; int mId;
};
struct XObjA { void FUN_00c3aa40(void*); };
struct XObjB { XObjB* FUN_00c04590(void*); };
struct cHerd { void SetPosition(); };
struct XObjC { void FUN_00b48770(); };
struct Obj30 { Obj30(); virtual void AddRef(); virtual void Release(); int pad[10]; };
struct cPlanet { void* GetName(); };
struct cPlanetModel { float FUN_00b7e4d0(); };

struct cSec3 {
    virtual void v00();
    int   FUN_00ebebc0();
    void  FUN_00f3cf10(bool p);
    void  FUN_00f3d210();
    void  FUN_00f3d3e0(int a1, ResKey* key, int* out);
    void  FUN_00f3d7e0(int unused);   // ret 4: one ignored stack arg
    void* FUN_00f3d780(int p);
    void* FUN_00f3d880();
    void  FUN_00f3d8a0();
    void  FUN_00f3d8c0(char p);
    void  FUN_00f3d900();
    void  FUN_00f3da90(char* p, void* q);
    void* FUN_00f3dc70(int p);
    float FUN_00f3dce0(int* v);
    void  FUN_00f3bbd0(void* h, int flag);
};

// Externals (defined elsewhere in the binary).
int* FUN_0067dd60();
void* FUN_0067cab0();
void* FUN_0067dd50();
void* FUN_0067ddb0();
void* FUN_00ResMan_GetManager();      // EA::ResourceMan::GetManager (0x67dcd0)
void* SP_GetSaveArea(unsigned);       // 0x6b1f90 (cdecl, 1 arg)
cPlanet* SP_GetActivePlanet();        // 0x1021260
EStr3* ConvertToString8(EStr3* out, void* wname);   // cdecl
cPlanetModel* SP_PlanetModel();       // 0xb3d350
void operator_delete_arr(void* p);    // 0xf47380
void* FUN_00b18e00(void* h);
XObjC* __stdcall FUN_00b3d310(void* h, void* q);
struct NounMgr { void* GetAvatar(); };
NounMgr* SP_NounManager();
unsigned FUN_00ef1990(char* a, char* b, float avg);
void FUN_00eeccb0(void* b);
void FUN_00eed720(void* p, void* o, void* o2);
void FUN_00eabf30x(void* p);
extern char* g_16c7aa4;
extern void (*g_DefaultCreateNameFromKey)(ResKey*, void*, void*, void*, int);   // [0x154c468], cdecl
extern float g_f884, g_f894, g_f8a4, g_f8b4, g_f8c4, g_f8d4, g_f8e4, g_f8f4, g_f904, g_f914, g_f924, g_f934, g_f944;

// 0x760fd0 (thiscall on the 0x20-byte object), 0xf03ff0 / 0xf04060 (thiscall on the object at g_16c7aa4+0xd8),
// and the helpers called by the hashtable walk.
struct BObjFns { void FUN_00760fd0(int a, int type, int c); };
struct KeyGen { int FUN_00f04060(); void FUN_00f03ff0(int i, ResKey* out, int flag); };
struct XObjD { void FUN_00eabf30(); void FUN_00f0dc10(); };

// 0xf3d260 / 0xf3d5d0 / the 0xf3cf10 call as seen from the callers.
void FUN_00f3d260(void* img, ResKey* key);                       // cdecl
void __stdcall FUN_00f3d5d0(int a1, ResKey* key, int* out);      // stdcall, 3 args
void __stdcall FUN_00f3cf10_nothis(int);                          // callers in this slice don't reload ecx

// ---------------------------------------------------------------------------
// @ 0x00f3cf10
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3cf10(bool p) {
    PanelObj* a = new("Simulator", 0, 0, 0, 0) PanelObj();
    a->AddRef();
    BObj* b = new("Simulator", 0, 0, 0, 0) BObj();
    if (b) b->AddRef();
    void* lst = FUN_0067dd50();
    int n = VFN(lst, 0x68, int, (void*))(lst);
    for (int i = 0; i < n; i++) {
        void* l2 = FUN_0067dd50();
        int* e = VFN(l2, 0x70, int*, (void*, int))(l2, i);
        int t = e[1];
        if (t == 7 || t == 8 || t == 10)
            ((BObjFns*)b)->FUN_00760fd0(e[0], t, e[2]);
    }
    cPlanet* planet = SP_GetActivePlanet();
    int size = p ? 0x100 : 0x80;
    int* res = FUN_0067dd60();
    void* img = VFN(res, 0x3c, void*, (void*, int, int, int, int, int, int, int, int))
        (res, (p == 0) + 0x7eb134c, 0x4694e3b, size, size, 1, 0x208, 0x15, 8);
    if (p)
        AssignRef(&PI(this, 0x34), img);
    else
        AssignRef(&PI(this, 0x30), img);
    EStr3 tmp;
    EStr3* r = ConvertToString8(&tmp, planet->GetName());
    if (r != &a->str)
        ((EStrHolder*)&a->str)->assign(r->b, r->e);
    if (tmp.c - tmp.b > 1 && tmp.b)
        operator_delete_arr(tmp.b);
    a->mFloat = SP_PlanetModel()->FUN_00b7e4d0();
    a->mZero = 0;
    a->mId = 0x57be4886;
    AssignRef(&a->mImg, img);
    BObj* old = a->mB;
    if (b != old) {
        if (b) b->AddRef();
        a->mB = b;
        if (old) old->Release();
    }
    *(char*)((char*)this + 0x124) = 0;
    *(char*)((char*)this + 0x2c) = 0;
    void* mgr = FUN_0067ddb0();
    VFN(mgr, 0x34, void, (void*, void*, int))(mgr, a, size);
    if (b) b->Release();
    VFN(a, 8, void, (void*))(a);
}

// ---------------------------------------------------------------------------
// @ 0x00f3d210
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d210() {
    int t = *(int*)(*(int*)((char*)this + 0x10) + 0x68);
    switch (t) {
    case 0:
        ((cImgRes*)((char*)this + 0x38))->GetImageResource(*(void**)((char*)this + 0x30));
        break;
    case 2: {
        IObj20* o = (IObj20*)FUN_0067dd60();
        void* r = o->v20(F(0xe8), F(0xf0), 0);
        ((cImgRes*)((char*)this + 0x38))->GetImageResource(r);
        break;
    }
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d260  (resource key -> UI image resource registration)
// ---------------------------------------------------------------------------
struct ResListNode { ResListNode* next; ResListNode* prev; void* data; };
struct ImgRes { int* ptr; unsigned flags; };

void FUN_00f3d260(void* imgv, ResKey* key) {
    ImgRes* img = (ImgRes*)imgv;
    int* res;
    if (img) {
        if (!(img->flags & 1)) {
            void* m = FUN_0067dd60();
            VFN(m, 0x34, void, (void*, void*))(m, img);
        }
        res = img->ptr;
    } else {
        res = 0;
    }
    if (!res) return;
    Obj30* o = new("Simulator", 0, 0, 0, 0) Obj30();   // ctor 0x9986e0
    int* base = 0;
    void* sub = 0;
    if (o) {
        VFN(o, 0, void, (void*))(o);
        sub = (char*)o + 8;
    }
    ResListNode head;
    head.next = &head; head.prev = &head;
    void* mgr = FUN_00ResMan_GetManager();
    VFN(mgr, 0x4c, void, (void*, ResListNode*, int))(mgr, &head, key->b);
    void* found = 0;
    for (ResListNode* n = head.next; n != &head; n = n->next) {
        void* d = n->data;
        if (VFN(d, 0x18, int, (void*))(d) == (int)0xef7d16e1) {
            found = d;
            break;
        }
    }
    I(o, 4) = (int)res;
    VFN(o, 0, void, (void*))(o);
    I(sub, 8) = key->a;
    I(sub, 0xc) = key->b;
    I(sub, 0x10) = key->c;
    mgr = FUN_00ResMan_GetManager();
    VFN(mgr, 0x20, void, (void*, void*, int, void*, void*, int))(mgr, sub, 0, SP_GetSaveArea(0x86ca01c9), found, 0);
    I(o, 4) = 0;
    VFN(o, 0, void, (void*))(o);
    VFN(o, 4, void, (void*))(o);
    VFN(o, 4, void, (void*))(o);
    for (ResListNode* n = head.next; n != &head; ) {
        ResListNode* nx = n->next;
        operator_delete_arr(n);
        n = nx;
    }
    VFN(o, 4, void, (void*))(o);
}

// ---------------------------------------------------------------------------
// @ 0x00f3d3e0
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d3e0(int a1, ResKey* key, int* out) {
    void* mgr = FUN_00ResMan_GetManager();
    void* sa = SP_GetSaveArea(0x86ca01c9);
    int* trip = (int*)((char*)this + 0xf4);
    void** slot = (void**)((char*)this + 0x3c);
    for (unsigned i = 1; i <= 4; i++, trip += 3, slot++) {
        ResKey k;
        k.a = key->a;
        k.b = 0x2f7d0004;
        k.c = ((key->c ^ i) & 0xff) ^ key->c;
        g_DefaultCreateNameFromKey(&k, out, mgr, sa, a1);
        VFN(mgr, 0x80, void, (void*, ResKey*, int))(mgr, &k, *out);
        int* stateSlot = (int*)((char*)I(this, 0x10) + 0x68 + (i - 1) * 4);
        void* img = 0;
        switch (*stateSlot) {
        case 0:
            img = PI(this, 0x34);
            break;
        case 1:
            img = *slot;
            break;
        case 2: {
            void* m = FUN_0067dd60();
            img = VFN(m, 0x1c, void*, (void*, int, int, int, int))(m, trip[0], trip[1], trip[2], 0);
            *stateSlot = 1;
            break;
        }
        case 3: {
            void* cur = *slot;
            if (cur) {
                *slot = 0;
                ReleaseRef(cur);
            }
            continue;
        }
        }
        FUN_00f3d260(img, &k);
        void* m2 = FUN_0067dd60();
        void* ni = VFN(m2, 0x1c, void*, (void*, int, int, int, int))(m2, k.a, k.b, k.c, 0);
        AssignRef(slot, ni);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d5d0
// ---------------------------------------------------------------------------
void __stdcall FUN_00f3d5d0(int a1, ResKey* key, int* out) {
    void* mgr = FUN_00ResMan_GetManager();
    SP_GetSaveArea(0x86ca01c9);
    KeyGen* kg = *(KeyGen**)(g_16c7aa4 + 0xd8);
    int n = kg->FUN_00f04060();
    for (int i = 0; i < n; i++) {
        ResKey k;
        k.a = key->a;
        k.b = 0x2f7d0004;
        k.c = ((key->c ^ (i - 0x9c)) & 0xff) ^ key->c;
        g_DefaultCreateNameFromKey(&k, out, mgr, kg, a1);
        VFN(mgr, 0x80, void, (void*, ResKey*, int))(mgr, &k, *out);
        ResKey t = { 0, 0, 0 };
        kg->FUN_00f03ff0(i, &t, 0);
        void* m = FUN_0067dd60();
        void* img = VFN(m, 0x1c, void*, (void*, int, int, int, int))(m, t.a, t.b, t.c, 0);
        FUN_00f3d260(img, &k);
        k.c = ((key->c ^ (i - 0x38)) & 0xff) ^ key->c;
        g_DefaultCreateNameFromKey(&k, out, mgr, kg, a1);
        VFN(mgr, 0x80, void, (void*, ResKey*, int))(mgr, &k, *out);
        kg->FUN_00f03ff0(i, &t, 1);
        void* m2 = FUN_0067dd60();
        void* img2 = VFN(m2, 0x1c, void*, (void*, int, int, int, int))(m2, t.a, t.b, t.c, 0);
        FUN_00f3d260(img2, &k);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d780  (look up the object registered for a noun id; the avatar maps to the cached avatar)
// ---------------------------------------------------------------------------
void* cSec3::FUN_00f3d780(int p) {
    if (p == F(0x8c)) {
        return SP_NounManager()->GetAvatar();
    }
    void* res = 0;
    Hashtable* ht = (Hashtable*)((char*)this + 0xb0);
    Iter8 it = ht->find(*(unsigned*)(p + 0x228));
    if (ht->mpBucketArray[ht->mnBucketCount] != it.node)
        res = *(void**)(it.node + 4);
    return res;
}

// ---------------------------------------------------------------------------
// @ 0x00f3d7e0  (walk the hashtable of registered objects, post-process by type id)
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d7e0(int) {
    Iter8 it;
    it.bucket = (char**)F(0xb4);
    it.node = *it.bucket;
    if (!it.node) {
        ++it.bucket;
        if (*it.bucket == 0) {
            do { ++it.bucket; } while (*it.bucket == 0);
        }
        it.node = *it.bucket;
    }
    char** bkt = it.bucket;
    char* n = it.node;
    char* end = ((char**)F(0xb4))[F(0xb8)];
    while (n != end) {
        void* o = *(void**)(n + 4);
        int t = VFN(o, 0x20, int, (void*))(o);
        if (t == 0x74e0069) {
            void* q = VFN(o, 0xc, void*, (void*, int))(o, t);
            ((XObjD*)q)->FUN_00eabf30();
        } else {
            t = VFN(o, 0x20, int, (void*))(o);
            if (t == 0x7b38ba7) {
                void* q = VFN(o, 0xc, void*, (void*, int))(o, t);
                ((XObjD*)q)->FUN_00f0dc10();
            }
        }
        n = *(char**)(n + 8);
        while (!n) {
            ++bkt;
            n = *bkt;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d880
// ---------------------------------------------------------------------------
void* cSec3::FUN_00f3d880() {
    int iVar1 = FUN_00ebebc0();
    if (iVar1 != 0) {
        return FUN_00f3d780(iVar1);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3d8a0
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d8a0() {
    if (*(char*)((char*)this + 0x124) != 0) {
        FUN_00f3cf10_nothis(0);
        *(char*)((char*)this + 0x124) = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d8c0
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3d8c0(char p) {
    if (*(int*)((char*)this + 0x18) == 0) {
        FUN_00f3cf10_nothis(0);
        *(int*)((char*)this + 0x18) = 1;
        *(char*)((char*)this + 0x1c) = (p == 0);
        cLayoutCollection* c = (cLayoutCollection*)FUN_0067cab0();
        c->Show();
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3d900
// ---------------------------------------------------------------------------
static inline bool AnyFlag(unsigned v) {
    return ((v >> 4) & 1) || ((v >> 1) & 1) || ((v >> 2) & 1);
}

void cSec3::FUN_00f3d900() {
    if (F(0x8c) != 0) {
        void* h = FUN_00f3d780(F(0x8c));
        if (h) {
            bool any = AnyFlag(I(F(0x8c), 0x224));
            FUN_00f3bbd0(h, !any);
        }
    }
    char* inner = (char*)F(0x10);
    char* e;
    if ((unsigned)I(inner, 0x2c24) < 0x3fffffff)
        e = (char*)(I(inner, 0x2c24) * 0x238 + I(inner, 0x2c10));
    else
        e = (char*)I(inner, 0x2c14);
    char* end = (char*)I(inner, 0x2c14);
    while (end != e) {
        void* h;
        if (e + 4 == (char*)F(0x8c)) {
            h = SP_NounManager()->GetAvatar();
        } else {
            h = FUN_00f3d780((int)(e + 4));
        }
        if (h) {
            bool any = AnyFlag(I(e + 4, 0x224));
            char* obj = (char*)FUN_00b18e00(h);
            *(bool*)(obj + 0x6e) = any;
            char* r = (char*)VFN(obj, 0xac, void*, (void*))(obj);
            if (r) {
                if (any) {
                    I(r, 4) |= 8;
                    *(char*)(r + 0x5c) = 1;
                } else {
                    I(r, 4) &= ~8;
                }
            }
        }
        for (;;) {
            unsigned hdr = *(unsigned*)e;
            e += 0x238;
            if ((hdr >> 0x1e) & 1) break;
            if (!((*(unsigned*)e >> 0x1f) & 1)) break;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3da90
// ---------------------------------------------------------------------------
void cSec3::FUN_00f3da90(char* p, void* q) {
    char* inner;
    if (p == (char*)F(0x8c)) {
        inner = (char*)F(0x10);
        I(inner, 0x15c) = I(p, 0x10);
        I(inner, 0x160) = I(p, 0x14);
        I(inner, 0x164) = I(p, 0x18);
        I(inner, 0x168) = I(p, 0x1c);
        inner = (char*)F(0x10);
        I(inner, 0x150) = I(p, 4);
        I(inner, 0x154) = I(p, 8);
        I(inner, 0x158) = I(p, 0xc);
        *(float*)((char*)F(0x10) + 0x16c) = *(float*)(p + 0x20);
    }
    char* h = (char*)FUN_00f3d780((int)p);
    char* obj = (char*)FUN_00b18e00(h);
    VFN(obj, 0x38, void, (void*, void*))(obj, p + 4);
    VFN(obj, 0x3c, void, (void*, void*))(obj, p + 0x10);
    VFN(obj, 0x40, void, (void*, float))(obj, *(float*)(p + 0x20));
    if (h) {
        char* a = (char*)VFN(h, 0xc, void*, (void*, unsigned))(h, 0xb033b403);
        if (a) {
            void* s = a + 0x34;
            void* r1 = VFN(s, 0x30, void*, (void*))(s);
            void* r2 = VFN(s, 0x2c, void*, (void*, void*))(s, r1);
            ((XObjA*)a)->FUN_00c3aa40(r2);
        }
        char* b = (char*)VFN(h, 0xc, void*, (void*, unsigned))(h, 0xd0036e08);
        if (b) {
            void* sub = b + 0xc0;
            void* r = VFN(sub, 0x2c, void*, (void*))(sub);
            XObjB* x = ((XObjB*)b)->FUN_00c04590(r);
            ((cHerd*)x)->SetPosition();
            FUN_00eeccb0(b);
            VFN(sub, 0x44, void, (void*, void*, void*))(sub, p + 4, p + 0x10);
        }
    }
    FUN_00b3d310(h, q)->FUN_00b48770();
    FUN_00eed720(p, obj, obj + 0xa8);
    *(char*)(obj + 0xa7) = 1;
    VFN(obj, 0x84, void, (void*))(obj);
    if (p == (char*)F(0x8c)) {
        inner = (char*)F(0x10);
        I(inner, 0x150) = I(p + 4, 0);
        I(inner, 0x154) = I(p + 4, 4);
        I(inner, 0x158) = I(p + 4, 8);
        inner = (char*)F(0x10);
        I(inner, 0x15c) = I(p + 0x10, 0);
        I(inner, 0x160) = I(p + 0x10, 4);
        I(inner, 0x164) = I(p + 0x10, 8);
        I(inner, 0x168) = I(p + 0x10, 0xc);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3dc70  (noun id -> entry in the Inner's 0x238-byte element table)
// ---------------------------------------------------------------------------
void* cSec3::FUN_00f3dc70(int p) {
    if (p == (int)SP_NounManager()->GetAvatar())
        return (void*)F(0x8c);
    void* res = 0;
    Hashtable* ht = (Hashtable*)((char*)this + 0x90);
    Iter8 it = ht->find(*(unsigned*)&p);
    if (ht->mpBucketArray[ht->mnBucketCount] != it.node) {
        int idx = I(it.node, 4);
        res = (char*)I(F(0x10), 0x2c10) + idx * 0x238 + 4;
    }
    return res;
}

// ---------------------------------------------------------------------------
// @ 0x00f3dce0  (weighted average of 12 ints, clamped against an element count scaled by 1/1024)
// ---------------------------------------------------------------------------
float cSec3::FUN_00f3dce0(int* v) {
    float avg = (((((float)v[11] * g_f934 + (float)v[10] * g_f924) + (float)v[9] * g_f914)
                  + (float)v[8] * g_f904 + (float)v[7] * g_f8f4 + (float)v[6] * g_f8e4)
                 + ((((((float)v[5] * g_f8d4 + (float)v[4] * g_f8c4) + (float)v[3] * g_f8b4)
                      + (float)v[2] * g_f8a4) + (float)v[1] * g_f894) + (float)v[0] * g_f884))
                / g_f944;
    char* inner = (char*)F(0x10);
    char* end = (char*)I(inner, 0x2c14);
    char* beg;
    if ((unsigned)I(inner, 0x2c24) < 0x3fffffff)
        beg = (char*)(I(inner, 0x2c24) * 0x238 + I(inner, 0x2c10));
    else
        beg = end;
    unsigned cnt = FUN_00ef1990(beg, end, avg) + 1;
    float x = (float)cnt * 0.0009765625f;
    return x > avg ? x : avg;
}
