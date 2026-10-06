// Slice s008117f0 (batch w2g6).
// UI cSPUILayout / cSPUILayoutObjectCollection / cSPUILayoutManager.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE2.
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
typedef unsigned long  size_t_;

typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void* (__thiscall *VF2)(void*, void*, void*);
typedef void  (__thiscall *VF2v)(void*, void*, void*);
static inline void** VT(void* o) { return *(void***)o; }

extern void  __cdecl operator_delete__(void*);                     // 0xf47380
extern void* __cdecl operator_new(u32, void*, int, int, const char*, int); // 0xf473a0
extern void  __cdecl ResetChildWindowCache_();                     // 0x962be0
extern int   __cdecl eastl_Compare_(void*, void*, int);            // 0x5f7870
extern void* __cdecl eastl_RBTreeIncrement_(void*);                // 0x921580
extern void* __cdecl eastl_RBTreeDecrement_(void*);                // 0x9215c0
extern void  __cdecl eastl_RBTreeErase(void*, void*);              // 0x921880
extern void  __cdecl SPKeyFromName(void*, u32, u32, u32);          // 0x68d840
extern void* __cdecl FUN_008100d0_(void*);                         // 0x8100d0 (collection ctor)
extern void  __cdecl FUN_00810b90_(void*, void*, void*);           // 0x810b90
extern void  __cdecl FUN_00812280_(void*, void*, void*, int);      // 0x812280
extern void  __cdecl FUN_005c1dc0_(void*, void*, void*);           // 0x5c1dc0

extern char vtbl_014182a4, vtbl_014182a0, vtbl_SimCreatureAbility, vtbl_SkinnerPaintSystem,
            vtbl_UI_cConnectionDialog, vtbl_SimContentValidationSummarizer,
            FUN_008117f0_sym, FUN_00810fd0_sym, FUN_00811330_sym, FUN_00811c20_sym,
            FUN_00810620_sym, FUN_810a90_sym;
extern void* g_spLayoutManager;                                    // 0x164cf5c

// ------------------------------------------------------------------ types --
struct PtrVec {
    void** mBegin;   // +0
    void** mEnd;     // +4
    void** mCap;     // +8
    void*  mAlloc;   // +0xc
    void*  mInline;  // +0x10
    void __thiscall swap(PtrVec& rhs);                 // 0x811a20
};
// key/value views

struct cSPUILayoutObjectCollection;
struct CollStub { u8 pad[0x100]; void __thiscall m11330(); };

struct cSPUILayoutObjectCollectionV8;   // view with this = collection+8

// --------------------------------------------------------------- cSPUILayout
struct cSPUILayout {
    void** vtbl;            // +0
    i32    mRefCount;       // +4
    u32    f8;              // +8
    u32    fc;              // +0xc
    u32    f10;             // +0x10
    void*  mpCollection;    // +0x14

    __declspec(noinline) void __thiscall Shutdown(u32 param_2);    // 0x811ad0
    void  __thiscall dtor();                                       // 0x811fe0
    void* __thiscall scalarDtor(u8 flag);                          // 0x812090
    u8    __thiscall InitA(void* key, u32 b, u32 c, u32 d);        // 0x812160
    u8    __thiscall InitB(u32* key, u32 b, u32 c);                // 0x8120d0
    u8    __thiscall SetParentWin(void* p, char b, u32 c);         // 0x8121b0
};

struct cSPUILayoutDtor : public cSPUILayout {};

// --------------------------------------------------- object collection base
struct cSPUILayoutObjectCollection {
    void** vtbl;            // +0
    u8     pad4[4];
    void*  p8;              // +8
    u8     padc[4];
    void*  mAutoUpdate;     // +0x10
    u8     pad14[0x20 - 0x14];
    u8     mSerFlags;       // +0x20
    u8     pad21[0x64 - 0x21];
    void*  mBoxBegin;       // +0x64
    void*  mBoxEnd;         // +0x68
    u8     pad6c[0x88 - 0x6c];
    void*  mParent;         // +0x88
    u8     b8c;             // +0x8c
    u8     b8d;             // +0x8d

    void __thiscall attach_parent();                               // 0x811b30
    u8   __thiscall SetParentWin(void* p, char b, u32 c);          // 0x812010
    void __thiscall detach_parent();                               // 0x810140 (external)
};

// view whose this is the SerCollection at collection+8
struct cSPUILayoutObjectCollectionV8 {
    u8     pad0[0xc];
    void*  mService;        // +0xc
    void*  mAutoUpdate;     // +0x10
    u8     pad14[0x1c - 0x14];
    void*  mKeyB;           // +0x1c
    u8     pad20[0x80 - 0x20];
    void*  m80;             // +0x80
    u8     pad84;
    u8     b85;             // +0x85
    u8     pad86[0x8c - 0x86];
    void*  p8c;             // +0x8c
    void*  p90;             // +0x90

    void __thiscall OnLoad();                                      // 0x811b80
};

// ------------------------------------------------------- cSPUILayoutManager
struct cSPUILayoutManager {
    void** vtbl;            // +0
    void** vtbl2;           // +4
    u8     pad8[0xc - 8];
    void*  f0c;             // +0xc
    u8     pad10[0x18 - 0x10];
    void*  f18;             // +0x18
    u8     pad1c[0x28 - 0x1c];
    void*  f28;             // +0x28
    u8     pad2c[0x30 - 0x2c];

    void* __thiscall ctor();                                       // 0x811f20
    void* __thiscall scalarDtor(u8 flag);                          // 0x811f80
    __declspec(noinline) void* __thiscall CloseLayout(void* coll, u32 param); // 0x8117f0
    void* __thiscall Method11c20();                                // 0x811c20
    void  __thiscall Method11330();                                // 0x811330 (external)
    void* __thiscall CreateLayoutObjects(u32 key);                 // 0x810fd0 (external)
    void* __thiscall GetWorldMainWindow(u32 id);                   // 0x810620 (external)
};

// nodes
struct VecView { void* begin; void* end; };
struct RBNode1 { RBNode1* left; RBNode1* right; RBNode1* parent; };
struct RBTree1 {
    RBNode1 anchor;         // +0
    i32     count;          // +0x10
    void __thiscall DoNukeSubtree(void* node);   // 0x810df0
    void __thiscall eraseSys(void** out, void* node);  // 0x812310
    void __thiscall Method12370(void** out, VecView* key);  // 0x812370
};
struct RBTree2 {
    RBNode1 anchor;         // +0
    i32     count;          // +0x10
    void __thiscall DoNukeSubtree(void* node);   // 0x9a9600
};

// ============================ bodies ============================

// @ 0x008117f0
void* __thiscall cSPUILayoutManager::CloseLayout(void* coll, u32 param)
{
    // 554-byte body not reconstructed
    (void)coll; (void)param;
    return 0;
}

// @ 0x00811a20
void __thiscall PtrVec::swap(PtrVec& rhs)
{
    bool aOwner = (mBegin == 0) || (*(int*)((u8*)mBegin - 4) != 0);
    bool bOwner = (rhs.mBegin == 0) || (*(int*)((u8*)rhs.mBegin - 4) != 0);
    if (aOwner && bOwner) {
        void** t;
        t = mBegin;  mBegin = rhs.mBegin;  rhs.mBegin = t;
        t = mEnd;    mEnd   = rhs.mEnd;    rhs.mEnd   = t;
        t = mCap;    mCap   = rhs.mCap;    rhs.mCap   = t;
        return;
    }
    // mismatch path uses a temporary copy + operator=; approximated
    PtrVec tmp;
    tmp.mBegin = 0; tmp.mEnd = 0; tmp.mCap = 0; tmp.mAlloc = 0; tmp.mInline = 0;
    u32 n = (u32)((u8*)mEnd - (u8*)mBegin);
    tmp.mBegin = (void**)operator_new(n, &g_spLayoutManager, 0, 0, 0, 0);
    FUN_005c1dc0_(tmp.mBegin, mBegin, (void*)n);
    tmp.mEnd = (void**)((u8*)tmp.mBegin + n);
    tmp.mCap = tmp.mEnd;
    *this = rhs;   // not a real operator= here; behavioural approximation
    mBegin = tmp.mBegin; mEnd = tmp.mEnd; mCap = tmp.mCap;
}

// @ 0x00811ad0
void __thiscall cSPUILayout::Shutdown(u32 param_2)
{
    ResetChildWindowCache_();
    void* c = mpCollection;
    if (!c) return;
    ((VF0v)VT(c)[1])(c);
    void* c2 = mpCollection;
    if (c2) {
        mpCollection = 0;
        ((VF0v)VT(c2)[2])(c2);
    }
    if (g_spLayoutManager)
        ((cSPUILayoutManager*)g_spLayoutManager)->CloseLayout(c, param_2);
    ((VF0v)VT(c)[2])(c);
}

// @ 0x00811b30
void __thiscall cSPUILayoutObjectCollection::attach_parent()
{
    u8* s = (u8*)this;
    if (*(u32*)(s + 0x88) == 0) return;
    void** p = *(void***)(s + 0x64);
    while (p != *(void***)(s + 0x68)) {
        void* o = *p++;
        void* (__thiscall *fn)(void*, void*) = (void*(__thiscall*)(void*, void*))VT(o)[0xc / 4];
        void* q = fn(o, (void*)0xeeee8218);
        if (q) {
            void* parent = *(void**)(s + 0x88);
            ((void(__thiscall*)(void*, void*))VT(parent)[0xd8 / 4])(parent, q);
        }
    }
    ((CollStub*)this)->m11330();
}

// @ 0x00811b80
void __thiscall cSPUILayoutObjectCollectionV8::OnLoad()
{
    u8* self = (u8*)this;
    cSPUILayoutObjectCollection* coll = (cSPUILayoutObjectCollection*)(self - 8);
    coll->attach_parent();
    if (*(void**)(self + 0x8c)) {
        void* fn = *(void**)(self + 0x8c);
        void* a1 = *(void**)(self + 0x90);
        ((void(__cdecl*)(void*, void*, int))fn)(a1, *(void**)(self + 0x88), 1);
    }
    ResetChildWindowCache_();
    if ((*(u8*)(self - 8 + 0x20) & 1) != 0) {
        void* svc = *(void**)(self - 8 + 0xc);
        void* au = ((void*(__thiscall*)(void*, unsigned int))VT(svc)[0x10 / 4])(svc, 0x2fbf2058);
        *(void**)(self - 8 + 0x10) = au;
        if (au) {
            struct { u32 x, y, z; } k = { 0xefbda3ff, 0x050f4731, 0x250fe9a2 };
            ((VF2v)VT(au)[0x10 / 4])(au, &k, (void*)(self - 8 + 8));
        }
    }
}

// @ 0x00811c20
void* __thiscall cSPUILayoutManager::Method11c20()
{
    return 0;   // 768-byte body not reconstructed
}

// @ 0x00811f20
void* __thiscall cSPUILayoutManager::ctor()
{
    u32* s = (u32*)this;
    s[1] = (u32)&vtbl_SimCreatureAbility;
    s[2] = 0;
    s[0] = (u32)&vtbl_014182a4;
    s[1] = (u32)&vtbl_014182a0;
    s[5] = 0;
    s[6] = 0;
    s[7] = 0;
    u32* c = s + 4;
    *c = (u32)c;
    s[5] = (u32)c;
    s[6] = 0;
    *((u8*)s + 0x1c) = 0;
    s[8] = 0;
    c = s + 0xb;
    s[0xc] = 0;
    s[0xd] = 0;
    s[0xe] = 0;
    *c = (u32)c;
    s[0xc] = (u32)c;
    s[0xd] = 0;
    *((u8*)s + 0x38) = 0;
    s[0xf] = 0;
    g_spLayoutManager = s;
    return s;
}

// @ 0x00811f80
void* __thiscall cSPUILayoutManager::scalarDtor(u8 flag)
{
    u8* s = (u8*)this;
    RBTree1* t1 = (RBTree1*)(s + 0x28);
    RBTree2* t2 = (RBTree2*)(s + 0xc);
    *(u32*)s = (u32)&vtbl_014182a4;
    *(u32*)(s + 4) = (u32)&vtbl_014182a0;
    g_spLayoutManager = 0;
    t1->DoNukeSubtree(*(void**)(s + 0x28 + 0xc));
    t2->DoNukeSubtree(*(void**)(s + 0x18));
    *(u32*)(s + 4) = (u32)&vtbl_SimCreatureAbility;
    *(u32*)s = (u32)&vtbl_SkinnerPaintSystem;
    if (flag & 1) operator_delete__(s);
    return s;
}

// @ 0x00811fe0
void __thiscall cSPUILayout::dtor()
{
    cSPUILayout* p = this;
    void* c = p->mpCollection;
    *(void**)p = &vtbl_UI_cConnectionDialog;
    if (c) p->Shutdown(1);
    c = p->mpCollection;
    if (c) ((VF0v)VT(c)[2])(c);
    *(void**)p = &vtbl_SimContentValidationSummarizer;
}

// @ 0x00812010
u8 __thiscall cSPUILayoutObjectCollection::SetParentWin(void* p, char b, u32 c)
{
    u8* s = (u8*)this;
    if (!p && b) {
        p = ((cSPUILayoutManager*)g_spLayoutManager)->GetWorldMainWindow(c);
    }
    void* cur = *(void**)(s + 0x88);
    if (p == cur) return 1;
    if (cur) detach_parent();
    void* old = *(void**)(s + 0x88);
    if (p != old) {
        if (p) ((VF0v)VT(p)[0])(p);
        *(void**)(s + 0x88) = p;
        if (old) ((VF0v)VT(old)[1])(old);
    }
    if (*(u32*)(s + 0x88)) attach_parent();
    return 1;
}

// @ 0x00812090
void* __thiscall cSPUILayout::scalarDtor(u8 flag)
{
    cSPUILayout* p = this;
    void* c = p->mpCollection;
    *(void**)p = &vtbl_UI_cConnectionDialog;
    if (c) p->Shutdown(1);
    c = p->mpCollection;
    if (c) ((VF0v)VT(c)[2])(c);
    *(void**)p = &vtbl_SimContentValidationSummarizer;
    if (flag & 1) operator_delete__(p);
    return p;
}

// @ 0x008120d0
u8 __thiscall cSPUILayout::InitB(u32* key, u32 b, u32 c)
{
    ResetChildWindowCache_();
    void* coll = ((cSPUILayoutManager*)g_spLayoutManager)->CreateLayoutObjects((u32)key);
    void* old = mpCollection;
    if (coll != old) {
        if (coll) ((VF0v)VT(coll)[1])(coll);
        mpCollection = coll;
        if (old) ((VF0v)VT(old)[2])(old);
    }
    void* cur = mpCollection;
    if (!cur) return 0;
    f8 = key[0]; fc = key[1]; f10 = key[2];
    if (*(u32*)((u8*)cur + 0x88) == 0)
        return ((cSPUILayoutObjectCollection*)cur)->SetParentWin(0, 1, b);
    return 1;
}

// @ 0x00812160
u8 __thiscall cSPUILayout::InitA(void* name, u32 b, u32 c, u32 d)
{
    u32 k[3] = { 0, 0, 0 };
    SPKeyFromName(k, (u32)name, 0x0510a95b, b);
    return InitB(k, c, d);
}

// @ 0x008121b0
u8 __thiscall cSPUILayout::SetParentWin(void* p, char b, u32 c)
{
    if (mpCollection)
        return ((cSPUILayoutObjectCollection*)mpCollection)->SetParentWin(p, b, c);

    return 0;
}

// @ 0x00812210
bool __cdecl FUN_00812210(VecView* a, VecView* b)
{
    void* ab = a->begin;
    void* bb = b->begin;
    int la = (int)((u8*)a->end - (u8*)a->begin);
    int lb = (int)((u8*)b->end - (u8*)b->begin);
    int len = lb < la ? lb : la;
    int r = eastl_Compare_(ab, bb, len);
    if (r == 0) {
        if (la < lb) return true;
        return lb < la;
    }
    return r < 0;
}

// @ 0x00812310
void __thiscall RBTree1::eraseSys(void** out, void* node)
{
    u8* n = (u8*)node;
    count--;
    void* next = eastl_RBTreeIncrement_(node);
    eastl_RBTreeErase(node, (u8*)this + 4);
    void* data = *(void**)(n + 0x10);
    if (*(int*)(n + 0x18) - (int)data > 1 && data) operator_delete__(data);
    operator_delete__(node);
    *out = next;
}

// @ 0x00812370
void __thiscall RBTree1::Method12370(void** out, VecView* key)
{
    u8* self = (u8*)this;
    bool bLess = true;
    RBNode1* node = *(RBNode1**)(self + 0xc);
    RBNode1* last = 0;
    while (node) {
        last = node;
        u8* n = (u8*)node;
        int kl = (int)((u8*)key->end - (u8*)key->begin);
        int nl = *(int*)(n + 0x14) - *(int*)(n + 0x10);
        int len = kl <= nl ? kl : nl;
        int r = eastl_Compare_((void*)key->begin, *(void**)(n + 0x10), len);
        if (r == 0) r = (kl < nl) ? -1 : (nl < kl);
        bLess = r < 0;
        node = bLess ? *(RBNode1**)(n + 4) : *(RBNode1**)n;
    }
    RBNode1* cand = last;
    int useUpper = 0;
    if (bLess) {
        if (last == *(RBNode1**)(self + 8)) { useUpper = 1; }
        else cand = (RBNode1*)eastl_RBTreeDecrement_(last);
    }
    if (!useUpper) {
        bool lt = FUN_00812210((VecView*)((u8*)cand + 0x10), key);
        if (!lt) {
            *out = cand;
            *((u8*)out + 4) = 0;
            return;
        }
    }
    FUN_00812280_(out, cand, key, 0);
    *out = *(void**)out;
    *((u8*)out + 4) = 1;
}
