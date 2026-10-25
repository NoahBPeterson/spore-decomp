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
void __fastcall FUN_00812280_(void* self, void* edxu, void* out, void* last, void* key, int z); // 0x812280
extern void  __cdecl FUN_005c1dc0_(void*, void*, void*);           // 0x5c1dc0
extern float __cdecl SPUI_GetElapsedSeconds();                      // 0x805080
extern void  __cdecl SPUI_UpdateMouseFocus(int);                    // 0x804f50
extern void* __cdecl Messaging_GetServer();                         // 0x883860
extern void  __cdecl SlotMessage_Destruct(void*);                   // 0x421cf0
extern void* __cdecl RBTreeUintFind_(void* self, void* out, void* key); // 0xe5c780 (tree find)
extern float g_closeLayoutLag;                                     // 0x147b9f0
extern float g_closeLayoutWindow;                                  // 0x14181a4

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
    PtrVec& __thiscall operator=(const PtrVec& rhs);   // 0x811260
};
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
void __fastcall VecCtorCount_(void* self, void* edx_unused, unsigned count, void* alloc); // 0x810a90 (vector(count,alloc))
void __cdecl PtyVecInsert_(void** pos, void** val);                // 0x810e30 (PtrVec::insert)
void __cdecl PtrVecDtor_(PtrVec*);                                 // 0x810a50 (PtrVec::dtor)
// key/value views

class cSPUILayoutObjectCollection;
struct CollStub { u8 pad[0x100]; void __thiscall m11330(); };

struct cSPUILayoutObjectCollectionV8;   // view with this = collection+8

// --------------------------------------------------------------- cSPUILayout
class cSPUILayout { public:
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
class cSPUILayoutObjectCollection { public:
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
class cSPUILayoutManager { public:
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
    bool  __thiscall Method11c20();                                // 0x811c20
    void  __thiscall Method11330();                                // 0x811330 (external)
    void* __thiscall CreateLayoutObjects(u32 key);                 // 0x810fd0 (external)
    void* __thiscall GetWorldMainWindow(u32 id);                   // 0x810620 (external)
};

// nodes
struct VecView { void* begin; void* end; };
struct RBNode1 { RBNode1* left; RBNode1* right; RBNode1* parent; };
// The node base sits at +4, not +0: eraseSys passes (this + 4) as the tree to
// eastl::RBTreeErase and retail decrements the size at [this + 0x14], i.e.
// +4 + 0x10 (the base is four dwords: parent, left, right, colour).
struct RBTree1 {
    void*   mpHead;         // +0
    RBNode1 anchor;         // +4
    void*   mColor;         // +0x10
    i32     count;          // +0x14
    void __thiscall DoNukeSubtree(void* node);   // 0x810df0
    void* __thiscall eraseSys(void** out, void* node);  // 0x812310
    void __thiscall Method12370(void** out, VecView* key, int unused);  // 0x812370
};
struct RBTree2 {
    RBNode1 anchor;         // +0
    i32     count;          // +0x10
    void __thiscall DoNukeSubtree(void* node);   // 0x9a9600
};

// ============================ bodies ============================

// Node of the manager's per-layout trees: {left,right,parent} then a value pointer,
// a byte flag and a float timestamp; sentinel/root bookkeeping lives in the tree header.
struct CloseLayoutNode {
    CloseLayoutNode* left;    // +0
    CloseLayoutNode* right;   // +4
    CloseLayoutNode* parent;  // +8
    void*            value;   // +0x10
    u8               flag;    // +0x14
    u8               pad15[3];
    f32              time;    // +0x18
};

static void ReleaseIface_(void* obj)                       // COM-ish: release through (u8*)obj+8
{
    if (!obj) return;
    void* inner = *(void**)((u8*)obj + 8);
    if (!inner) return;
    ((void(__thiscall*)(void*))(*(void***)inner)[8 / 4])((u8*)obj + 8);
}

// @ 0x008117f0
void* __thiscall cSPUILayoutManager::CloseLayout(void* coll, u32 param)
{
    u8* m = (u8*)this;
    char didWork = 0;                                   // [esp+0x13]
    f32 now = SPUI_GetElapsedSeconds();                 // 0x805080

    // ---- expire/lookup the layout record for `coll` in the tree at +0x28 ---------------
    void* key = coll;
    void* found = 0;
    void* endSentinel = m + 0x2c;
    RBTreeUintFind_(m + 0x28, &found, &key);            // 0xe5c780
    CloseLayoutNode* node = (CloseLayoutNode*)found;
    if (node != (CloseLayoutNode*)endSentinel) {
        node->flag = 1;
        node->time = now;
        if (param != 0) {
            node->time = now - g_closeLayoutLag;        // 0x147b9f0
        } else {
            // notify each child window in the collection's box
            void** p = *(void***)((u8*)coll + 0x64);
            void** end = *(void***)((u8*)coll + 0x68);
            while (p != end) {
                void* o = *p++;
                void* sub = ((void*(__thiscall*)(void*, void*))VT(o)[0xc / 4])(o, (void*)0xeeee8218);
                if (sub)
                    ((void(__thiscall*)(void*, int, int))VT(sub)[0x7c / 4])(sub, 1, 0);
            }
            SPUI_UpdateMouseFocus(1);                   // 0x804f50
        }
        // post a close-layout message (tag 0x22568e7) through the messaging server
        u8 msg[0x34];
        *(u32*)(msg + 0x30) = 0x22568e7;                // [esp+0x50]
        *(u32*)(msg + 0x00) = 0x13eb90c;                // vtable ([esp+0x20])
        *(u32*)(msg + 0x04) = 0x13eb844;                // ([esp+0x20] retagged)
        didWork = 1;                                    // [esp+0x13] = 1
        void* srv = Messaging_GetServer();              // 0x883860
        void* srvvt = *(void**)srv;
        ((void(__thiscall*)(void*, u32, void*))*(void**)((u8*)srvvt + 0x14))(srv, 0x22568e7, msg);
        SlotMessage_Destruct(msg);                      // 0x421cf0
    }

    // ---- expire records in the tree at +0x30 whose elapsed time exceeds the window ------
    CloseLayoutNode* cur = *(CloseLayoutNode**)(m + 0x30);
    PtrVec collected;                                   // esp+0x60..0x70 (inline empty vector)
    collected.mBegin = (void**)&collected;
    collected.mEnd   = (void**)&collected;
    collected.mCap   = (void**)&collected;
    collected.mAlloc = 0;
    collected.mInline= 0;
    while (cur != (CloseLayoutNode*)endSentinel) {
        CloseLayoutNode* n = cur;
        cur = (CloseLayoutNode*)eastl_RBTreeIncrement_(cur);      // 0x921580
        if (n->flag != 0) {
            f32 dt = now - n->time;
            if (dt > g_closeLayoutWindow) {                       // 0x14181a4
                // collect the value pointer
                void** slot = collected.mEnd;
                if (slot < collected.mCap) {
                    collected.mEnd = slot + 1;
                    if (slot) *slot = n->value;
                } else {
                    PtyVecInsert_((void**)&collected.mEnd, &n->value);    // 0x810e30
                }
                // unlink and free the node
                --*(int*)((u8*)this + 0x3c);                      // tree2 count--
                eastl_RBTreeIncrement_(n);
                eastl_RBTreeErase((u8*)this + 0x2c, n);           // 0x921880
                if (n->value)
                    ((void(__thiscall*)(void*))(*(void***)n->value)[8 / 4])(n->value);
                operator_delete__(n);                             // 0xf47380
            }
        }
    }
    // release the collected references
    void** v = collected.mEnd;
    while (v != collected.mBegin) {
        void* obj = *--v;
        ReleaseIface_(obj);
    }
    PtrVecDtor_(&collected);                            // 0x810a50
    return (void*)(int)didWork;
}

// @ 0x00811a20
void __thiscall PtrVec::swap(PtrVec& rhs)
{
    void** a = mBegin;
    void** b = rhs.mBegin;
    if ((a == 0 || *((int*)a - 1) != 0) &&
        (b == 0 || *((int*)b - 1) != 0)) {
        void** t;
        t = mBegin;  mBegin = rhs.mBegin;  rhs.mBegin = t;
        t = mEnd;    mEnd   = rhs.mEnd;    rhs.mEnd   = t;
        t = mCap;    mCap   = rhs.mCap;    rhs.mCap   = t;
        return;
    }
    // allocator mismatch: build tmp as a copy of *this, then *this = rhs, rhs = tmp, free tmp
    PtrVec tmp;
    u32 count = (u32)(((u8*)mEnd - (u8*)mBegin) >> 2);
    VecCtorCount_(&tmp, 0, count, &mAlloc);   // 0x810a90 (this, count, alloc)
    u32 bytes = (u32)((u8*)mEnd - (u8*)mBegin);
    memcpy(tmp.mBegin, mBegin, bytes);
    tmp.mEnd = (void**)((u8*)tmp.mBegin + bytes);
    this->operator=(rhs);      // 0x811260
    rhs.operator=(tmp);        // 0x811260
    if (tmp.mBegin != 0 && *((int*)tmp.mBegin - 1) != 0)
        operator_delete__(tmp.mBegin);
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
    coll->attach_parent();                                  // 0x811b30
    void* fn = *(void**)(self + 0x8c);
    if (fn) {
        void* a1 = *(void**)(self + 0x90);
        void* a2 = *(void**)(self + 0x88);
        ((void(__cdecl*)(void*, void*, int))fn)(a1, a2, 1);
    }
    ResetChildWindowCache_();                               // 0x962be0
    u8* base = self - 8;
    if ((*(u8*)(base + 0x20) & 1) != 0) {                   // [esi+0x20], esi = self-8
        void* svc = *(void**)(base + 0x0c);                 // [esi+0xc]
        void* au = ((void*(__thiscall*)(void*, unsigned int))VT(svc)[0x10 / 4])(svc, 0x2fbf2058);
        *(void**)(base + 0x10) = au;                        // [esi+0x10]
        if (au) {
            u32 v14 = *(u32*)(base + 0x14);
            u32 v1c = *(u32*)(base + 0x1c);
            u32 keyA[3] = { 0xefbda3ff, v14, v1c };
            u32 keyB[3] = { 0x050f4731, v14, v1c };
            void* dst = (void*)(base + 8);
            ((void(__thiscall*)(void*, u32*, void*))VT(au)[0x10 / 4])(au, keyA, dst);
            void* au2 = *(void**)(base + 0x10);
            ((void(__thiscall*)(void*, u32*, void*))VT(au2)[0x10 / 4])(au2, keyB, dst);
        }
    }
}

// ---- views for the 0x00811c20 collection Reload body ------------------------
struct WStr {                                       // eastl wide string, 0x10 B
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08
    u32   mAlloc;    // +0x0c (left untouched by the original)
    void __thiscall Assign(const WStr& rhs);        // 0x57cb60
    void __thiscall Destroy_();                     // 0x933960
};

struct MStream {
    u8    pad00[0x24];
    void  __thiscall Init(void* buf, u32 size, int a, int b, int c, const char* name); // 0x93c2c0
    void  __thiscall SetOption(int opt, float val); // 0x93bb40
    void  __thiscall AddRef_();                     // 0x83f5d0
    u8    __thiscall SetPosition(int a, int b);     // 0x93c0c0
    void  __thiscall Destroy_();                    // 0x93bde0
};

struct Iface4 {
    void __thiscall Report(u32 code);                   // 0x999480
};

struct CollOps {
    void __thiscall Flush();                            // 0x999050
};

struct VecOps {
    void __thiscall Destroy_();                         // 0x7a41a0
};

struct ReloadKey { u32 a, b, c, d; };                   // d is never written

struct LayoutChild {                                    // looked-up layout child
    u8    pad00[0x18];
    void* mpChildObj;   // +0x18 (tear-down target / load target)
    void* mpToken;      // +0x1c (token tree to serialise on rebuild)
    void* mpCtx;        // +0x20 (token io context)
};

struct ReloadView {                                     // this = collection
    void** vtbl;        // +0x00
    void*  mpIface;     // +0x04
    void*  p08;         // +0x08
    u32    m0c;         // +0x0c
    u32    m10;         // +0x10
    u32    m14;         // +0x14
    void*  m18;         // +0x18
    u8     pad1c[0x40]; // +0x1c
    PtrVec vec5c;       // +0x5c
    WStr   name70;      // +0x70
};

typedef u8  (__thiscall *SvcFindFn)(void*, ReloadKey*, void**, int, int, int, int);
typedef void(__thiscall *SvcNameFn)(void*, void*, WStr*);
typedef int (__thiscall *IfaceLoadFn)(void*, void*, void*, void*, void*);

extern "C" void* FUN_008de1a0();                        // 0x8de1a0 layout-root service
extern "C" void  SetCachingType(int, void*);            // 0x6ac040
extern "C" u8    WriteTokenList(void*, void*, u32, void*); // 0x902fc0
extern wchar_t   g_1667bac[2];                          // empty wide-string sentinel
extern const char g_13ebacc[];                          // "UTF/MemoryStream"

// @ 0x00811c20  cSPUILayoutManager::Method11c20 (cSPUILayoutObjectCollection::Reload)
bool __thiscall cSPUILayoutManager::Method11c20()
{
    ReloadView* v = (ReloadView*)this;
    if (!v->mpIface)
        return false;

    PtrVec tmp;
    tmp.mBegin = 0;
    tmp.mEnd = 0;
    tmp.mCap = 0;
    v->vec5c.swap(tmp);

    void* svc = FUN_008de1a0();
    if (!svc)
        ((Iface4*)v->mpIface)->Report(0x4fbd0001);

    void* out = 0;
    ReloadKey key;
    key.a = v->m0c;
    key.b = v->m10;          // overwritten below, as in the original
    key.c = v->m14;
    key.b = 0x510a95b;

    u8 ok = ((SvcFindFn)((void**)*(void***)svc)[3])(svc, &key, &out, 0, 0, 0, 0);
    if (!ok)
        goto fail;

    SetCachingType(6, out);
    {
        LayoutChild* child = (LayoutChild*)out;
        if (!child)
            goto fail;

        if (child->mpToken) {
            u8 buf[0x40];
            MStream ms;
            WStr temp;
            int r;

            ms.Init(buf, 0x40, 1, 0, 0, g_13ebacc);
            ms.SetOption(1, 1.0f);
            ms.AddRef_();
            WriteTokenList(&ms, child->mpToken, 2, child->mpCtx);
            ms.SetPosition(0, 0);

            temp.mpBegin = &g_1667bac[0];
            temp.mpEnd   = &g_1667bac[0];
            temp.mpCap   = &g_1667bac[1];
            ((SvcNameFn)((void**)*(void***)svc)[0x7c / 4])(svc, &v->m0c, &temp);
            if (temp.mpBegin != temp.mpEnd)
                v->name70.Assign(temp);

            r = ((IfaceLoadFn)((void**)*(void***)v->mpIface)[6])
                    (v->mpIface, &ms, v->name70.mpBegin, this, v->m18);
            if (r != 0) {
                temp.Destroy_();
                ms.Destroy_();
                goto fail;
            }

            v->vec5c.swap(tmp);
            ((CollOps*)this)->Flush();
            v->vec5c.swap(tmp);
            ((void (__thiscall*)(void*))((void**)*(void***)this)[3])(this);
            temp.Destroy_();
            ms.Destroy_();
            if (out)
                ((void (__thiscall*)(void*))((void**)*(void***)out)[1])(out);
            ((VecOps*)&tmp)->Destroy_();
            return true;
        } else if (child->mpChildObj) {
            WStr temp;
            void* childObj = child->mpChildObj;
            int r;

            temp.mpBegin = &g_1667bac[0];
            temp.mpEnd   = &g_1667bac[0];
            temp.mpCap   = &g_1667bac[1];
            ((SvcNameFn)((void**)*(void***)svc)[0x7c / 4])(svc, &v->m0c, &temp);
            if (temp.mpBegin != temp.mpEnd)
                v->name70.Assign(temp);

            ((void (__thiscall*)(void*, int, int))
                ((void**)*(void***)childObj)[0x28 / 4])(childObj, 0, 0);

            r = ((IfaceLoadFn)((void**)*(void***)v->mpIface)[6])
                    (v->mpIface, childObj, v->name70.mpBegin, this, v->m18);
            if (r != 0) {
                temp.Destroy_();
                goto fail;
            }

            v->vec5c.swap(tmp);
            ((CollOps*)this)->Flush();
            v->vec5c.swap(tmp);
            ((void (__thiscall*)(void*))((void**)*(void***)this)[3])(this);
            temp.Destroy_();
            if (out)
                ((void (__thiscall*)(void*))((void**)*(void***)out)[1])(out);
            ((VecOps*)&tmp)->Destroy_();
            return true;
        }
    }

fail:
    if (out)
        ((void (__thiscall*)(void*))((void**)*(void***)out)[1])(out);
    if (tmp.mBegin && ((u32*)tmp.mBegin)[-1] != 0)
        operator_delete__(tmp.mBegin);
    return false;
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
    if (r == 0)
        return la < lb;
    return r < 0;
}

// Retail is declared void, but eax is live at the ret: it holds the `out` argument (the
// pointer the increment result is finally stored through), so the residue is modelled by
// returning it.
// @ 0x00812310
void* __thiscall RBTree1::eraseSys(void** out, void* node)
{
    u8* n = (u8*)node;
    count--;
    void* next = eastl_RBTreeIncrement_(node);
    eastl_RBTreeErase(node, (u8*)this + 4);
    void* data = *(void**)(n + 0x10);
    if (*(int*)(n + 0x18) - (int)data > 1 && data) operator_delete__(data);
    operator_delete__(node);
    *out = next;
    return out;
}

// @ 0x00812370  (lower_bound/upper_bound over the tree; 3-arg (out, key, unused), ret 0xc)
void __thiscall RBTree1::Method12370(void** out, VecView* key, int unused)
{
    u8* self = (u8*)this;
    (void)unused;
    bool bLess = true;
    RBNode1* node = *(RBNode1**)(self + 0xc);   // root / begin (edi)
    RBNode1* last = (RBNode1*)(self + 4);       // sentinel-ish (esi)
    while (node) {
        u8* n = (u8*)node;
        int kl = (int)((u8*)key->end - (u8*)key->begin);
        int nl = (int)(*(u8**)(n + 0x14) - *(u8**)(n + 0x10));
        int len = nl < kl ? nl : kl;                 // min(nl, kl)
        int r = eastl_Compare_((void*)key->begin, *(void**)(n + 0x10), len);
        if (r == 0)
            r = (kl < nl) ? -1 : (kl > nl ? 1 : 0);
        bLess = r < 0;
        last = node;
        node = bLess ? *(RBNode1**)(n + 4) : *(RBNode1**)n;
    }
    RBNode1* cand = last;                    // edi = esi
    if (bLess) {
        if (last == *(RBNode1**)(self + 8)) {          // esi == [ebx+8] -> upper bound
            FUN_00812280_(this, 0, out, last, key, 0);
            *out = *(void**)out;
            *((u8*)out + 4) = 1;
            return;
        }
        cand = (RBNode1*)eastl_RBTreeDecrement_(last);  // 0x9215c0
    }
    if (!FUN_00812210((VecView*)((u8*)cand + 0x10), key)) {
        *out = cand;
        *((u8*)out + 4) = 0;
        return;
    }
    FUN_00812280_(this, 0, out, last, key, 0);
    *out = *(void**)out;
    *((u8*)out + 4) = 1;
}
