// Slice s00809700: SPUIHelpers modal/message-box helpers and misc small setters.
// The small accessors / simple members are byte-exact; the large modal and layout routines
// are only partially reconstructed.
#include "types.h"

// ================================================================== small state setters
struct AppInner { char pad[0x118]; int flag; };
struct AppOuter { char pad[0x3c]; AppInner* inner; };

extern AppOuter* g_app;              // 0x015fd918
extern uint8_t g_894;                // 0x0164c894
extern uint8_t g_895;                // 0x0164c895
extern uint8_t g_896;                // 0x0164c896
extern uint32_t g_898;               // 0x0164c898
extern uint32_t g_89c;               // 0x0164c89c
extern uint32_t g_8a0;               // 0x0164c8a0

// @ 0x008098b0
void set894(uint8_t v) { if (g_app->inner->flag != 0) g_894 = v; }
// @ 0x008098d0
void set898(uint32_t v) { if (g_app->inner->flag != 0) g_898 = v; }
// @ 0x008098f0
void set895(uint8_t v) { if (g_app->inner->flag != 0) g_895 = v; }
// @ 0x00809910
void set89c(uint32_t v) { if (g_app->inner->flag != 0) g_89c = v; }
// @ 0x00809930
void set896(uint8_t v) { if (g_app->inner->flag != 0) g_896 = v; }
// @ 0x00809950
void set8a0(uint32_t v) { if (g_app->inner->flag != 0) g_8a0 = v; }

// ================================================================== 0x00809970
struct WM {
    virtual void w0();                              // +0x00
    virtual void* w1();                             // +0x04
    virtual void w2(); virtual void w3(); virtual void w4(); virtual void w5();
    virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13();
    virtual void w14(); virtual void w15(); virtual void w16(); virtual void w17();
    virtual void w18();
    virtual void w19(void* a, void* b);             // +0x4c
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31();
    virtual void w32();
    virtual int Fn84();                             // +0x84 (index 33)
};
extern "C" WM* WindowManager();     // 0x0067caa0

int FUN_00809970()
{
    if (WindowManager() != 0) {
        if (WindowManager()->Fn84() != 0) {
            return 1;
        }
    }
    return 0;
}

// ================================================================== 0x00809fa0
struct ComObj {
    virtual void q0();
    virtual void Release();       // +4
};
struct Holder {
    void* a;                      // +0
    void* b;                      // +4
    ComObj* m8;                   // +8
    ComObj* mC;                   // +0xc
    Holder* DeleteThis(unsigned char flags);
};
extern "C" void efree(void* p); // 0x00a222c0

// @ 0x00809fa0
Holder* Holder::DeleteThis(unsigned char flags)
{
    ComObj* p = mC;
    if (p) p->Release();
    ComObj* q = m8;
    if (q) q->Release();
    if (flags & 1)
        efree(this);
    return this;
}

// ================================================================== 0x0080a5f0
extern int g_15446cc, g_15446d0, g_15446d4;
extern char g_obj_15446c8;
struct G {
    char pad[8];
    void FUN_0080a4f0(int a, int b);
};

// @ 0x0080a5f0
void FUN_0080a5f0()
{
    ((G*)&g_obj_15446c8)->FUN_0080a4f0(g_15446cc, g_15446d0);
    g_15446d4 = 0;
}

// ================================================================== 0x0080a470
extern "C" void* dbgnew(unsigned size, const void* data, int a, int b, const char* file, int line); // 0x00f473a0
extern char g_data_13f6b3c;

struct Blob {
    int i0, i1, i2, i3, i4, i5;
    float f0, f1, f2, f3;
    int i6, i7;
};

// @ 0x0080a470
void __stdcall FUN_0080a470(Blob* src)
{
    Blob* p = (Blob*)dbgnew(0x34, &g_data_13f6b3c, 0, 0,
                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                            0xd1);
    if (p) {
        p->i0 = src->i0; p->i1 = src->i1; p->i2 = src->i2; p->i3 = src->i3;
        p->i4 = src->i4; p->i5 = src->i5;
        p->f0 = src->f0; p->f1 = src->f1; p->f2 = src->f2; p->f3 = src->f3;
        p->i6 = src->i6; p->i7 = src->i7;
    }
    *(int*)((char*)p + 0x30) = 0;
}

// ================================================================== 0x0080a320
// Enter/Esc message filter.  Byte-exact except the switch jump/byte tables (4 bytes).
struct Msg {
    int a, b;        // +0, +4
    int type;        // +8
    int fieldC;      // +0xc
    int key;         // +0x10
    int field14;     // +0x14
};
extern "C" bool __cdecl sOnEnterEscKeys(int a, int b, int c);

// @ 0x0080a320
bool __stdcall FUN_0080a320(void* a, Msg* m)
{
    switch (m->type) {
    case 1:
        if (m->fieldC == 0 && (m->key == 0x1b || m->key == 0xd) && m->field14 == 0)
            sOnEnterEscKeys(0, m->key, 0);
        return true;
    case 2:
    case 5:
        return true;
    case 10:
        return false;
    default:
        return false;
    }
}

// ================================================================== modal / message-box helpers
struct IWin;

#define VSLOT(o, off) (*(void***)(o))[(off) / 4]
static inline void  vcall0(void* o, int off) { ((void (__thiscall*)(void*))VSLOT(o, off))(o); }
static inline void* vp0(void* o, int off) { return ((void* (__thiscall*)(void*))VSLOT(o, off))(o); }
static inline int   vi0(void* o, int off) { return ((int (__thiscall*)(void*))VSLOT(o, off))(o); }
static inline char  vb0(void* o, int off) { return ((char (__thiscall*)(void*))VSLOT(o, off))(o); }
static inline void  vcall1(void* o, int off, void* a) { ((void (__thiscall*)(void*, void*))VSLOT(o, off))(o, a); }
static inline void* vp1(void* o, int off, void* a) { return ((void* (__thiscall*)(void*, void*))VSLOT(o, off))(o, a); }
static inline char  vb1(void* o, int off, void* a) { return ((char (__thiscall*)(void*, void*))VSLOT(o, off))(o, a); }
static inline void  vcall2(void* o, int off, void* a, void* b) { ((void (__thiscall*)(void*, void*, void*))VSLOT(o, off))(o, a, b); }
static inline void  vcall4(void* o, int off, void* a, void* b, void* c, void* d) { ((void (__thiscall*)(void*, void*, void*, void*, void*))VSLOT(o, off))(o, a, b, c, d); }
static inline void  vf2(void* o, int off, float a, float b) { ((void (__thiscall*)(void*, float, float))VSLOT(o, off))(o, a, b); }

// AutoRefCount<EA::UTFWinControls::IWinText> (a pointer at +0).
struct AutoRefIWin {
    IWin* p;
    AutoRefIWin& operator=(IWin* q);   // 0x00b5f950
};

extern "C" void*  GetLayoutManager(int id);                 // 0x00805070
struct LayoutManager { void* GetWorldMainWindow(); };      // 0x00810620
extern "C" void   Pollinator(void* win, float* rect);      // 0x00806d10
extern "C" void*  GetUTFManager();                         // 0x00957f30
extern "C" void*  CheatManager();                          // 0x0067de20
extern "C" void*  PropertyManager();                       // 0x0067de30
extern "C" void*  FUN_00806370(void* a);                   // 0x00806370
extern "C" char   WalkAll(void* a);                        // 0x008050b0
extern "C" bool   VisitWindowTreeDepthFirst(void* w, void* cb, void* user); // 0x00807d30
extern "C" bool   GetPropertyAsUint32Array(void* l, unsigned id, unsigned* count, unsigned** arr); // 0x006a0840
extern "C" void*  GetUIAllocator();                        // 0x009512c0
extern "C" void*  op_new(unsigned size, int align, const char* name, void* alloc); // 0x009512d0

extern AutoRefIWin g_msgBoxObj;      // 0x0164c8f8
extern void*       g_modalWin;       // 0x0164c890
extern int         gWindowNodeOffset;// 0x01440aec
extern char        g_allocFile_13ebb38[]; // 0x013ebb38
extern float       g_half_1471064;   // 0x01471064
extern float       g_zero_13eb1bc;   // 0x013eb1bc

// ================================================================== 0x00809700
// Breadth-first window-tree visit.  The work queue is an eastl fixed list whose 12-byte
// nodes come from a 0x600-byte inline pool.
struct ChildNode { ChildNode* mpNext; ChildNode* mpPrev; };
struct TraverseNode { TraverseNode* mpNext; TraverseNode* mpPrev; IWin* mpValue; };

struct FixedPool0080 {
    void* mpHead;
    void* mpPad;
    void* mpNext;
    void* mpCapacity;
    unsigned mnNodeSize;
};
struct FixedList008097 {
    TraverseNode* mpNext;
    TraverseNode* mpPrev;
    FixedPool0080 mPool;
    char mBuffer[0x600];
};
extern "C" void* __fastcall FixedListCtor00809670(FixedList008097* self); // 0x00809670
extern "C" void  __fastcall FixedListFreeNodes0080(FixedList008097* self); // 0x00a222c0

static __forceinline TraverseNode* listAlloc008097(FixedList008097* l)
{
    FixedPool0080* p = &l->mPool;
    if (p->mpHead) {
        TraverseNode* n = (TraverseNode*)p->mpHead;
        p->mpHead = n->mpNext;
        return n;
    }
    return (TraverseNode*)dbgnew(p->mnNodeSize, &g_data_13f6b3c, 0, 0,
                                 g_allocFile_13ebb38, 0xd1);
}

static __forceinline void listPush008097(FixedList008097* l, IWin* v)
{
    TraverseNode* n = listAlloc008097(l);
    n->mpValue = v;
    n->mpNext = (TraverseNode*)l;
    n->mpPrev = l->mpPrev;
    l->mpPrev->mpNext = n;
    l->mpPrev = n;
}

static __forceinline void listPop008097(FixedList008097* l)
{
    TraverseNode* n = l->mpNext;
    n->mpPrev->mpNext = n->mpNext;
    n->mpNext->mpPrev = n->mpPrev;
    if ((unsigned)n < (unsigned)l->mPool.mpNext || (unsigned)n >= (unsigned)l->mPool.mpCapacity) {
        efree(n);
    } else {
        n->mpNext = (TraverseNode*)l->mPool.mpHead;
        l->mPool.mpHead = n;
    }
}

// @ 0x00809700
bool __cdecl FUN_00809700(IWin* root, bool (__cdecl* pred)(IWin*, void*), void* ctx)
{
    FixedList008097 list;
    FixedListCtor00809670(&list);
    listPush008097(&list, root);
    while (list.mpNext != (TraverseNode*)&list) {
        IWin* w = list.mpNext->mpValue;
        if (!pred(w, ctx)) {
            FixedListFreeNodes0080(&list);
            return false;
        }
        ChildNode* cur;
        ChildNode* end;
        vcall1(w, 0xcc, &cur);
        ChildNode** endp = (ChildNode**)vp1(w, 0xd0, &end);
        while (cur != *endp) {
            ChildNode* next = cur->mpNext;
            IWin* child = (IWin*)((char*)cur + gWindowNodeOffset);
            cur = next;
            listPush008097(&list, child);
            endp = (ChildNode**)vp1(w, 0xd0, &end);
        }
        listPop008097(&list);
    }
    FixedListFreeNodes0080(&list);
    return true;
}

// ================================================================== 0x008099a0
// @ 0x008099a0
bool __cdecl SPUIHelpers_BeginModal(void* w, void* callback, char flag)
{
    (void)callback;
    if (!w) return false;
    void* lm = GetLayoutManager(0x5b598f7);
    IWin* main = (IWin*)((LayoutManager*)lm)->GetWorldMainWindow();
    if (!vp0(w, 0x10))
        vcall1(main, 0xd8, w);
    if (flag) {
        IWin* inner = (IWin*)vp0(w, 0x10);
        float* r = (float*)vp0(inner, 0x38);
        float a = -r[0];
        float b = -r[1];
        float rect[4];
        rect[0] = a + r[0];
        rect[1] = b + r[1];
        rect[2] = r[2] + a;
        rect[3] = r[3] + b;
        Pollinator(w, rect);
    }
    if (g_app->inner->flag != 0) {
        if (!g_msgBoxObj.p) {
            g_msgBoxObj = (IWin*)FUN_00806370(0);
            vcall1(g_msgBoxObj.p, 0x5c, (void*)(int)-1);
            vcall1(g_msgBoxObj.p, 0xac, (void*)0xbe3c4166);
            IWin* wm = (IWin*)vp0(WindowManager(), 4);
            float* r = (float*)vp0(wm, 0x38);
            vf2(g_msgBoxObj.p, 0x68, r[2] - r[0], r[3] - r[1]);
            vcall2(g_msgBoxObj.p, 0x7c, (void*)1, (void*)1);
        }
        if ((g_8a0 == 0 || g_896 == 0 || w == (void*)g_8a0) && g_895 == 0) {
            IWin* gi = (IWin*)vp0(g_msgBoxObj.p, 0x10);
            if (gi) vcall1(gi, 0xdc, g_msgBoxObj.p);
            vcall1((IWin*)vp0(w, 0x10), 0xd8, g_msgBoxObj.p);
            vcall1((IWin*)vp0(w, 0x10), 0xe8, g_msgBoxObj.p);
            g_modalWin = w;
        }
    }
    void* wm = WindowManager();
    void* proxyMgr = vp1(wm, 0x48, 0);
    int* proxy = (int*)dbgnew(0x10, "UI/cModalCallbackProxy", 0, 0, 0, 0);
    if (proxy) {
        proxy[0] = 0x1417b84;
        proxy[1] = (int)w;
        proxy[2] = (int)proxyMgr;
        if (proxyMgr) vcall0(proxyMgr, 0);
        proxy[3] = 0;
    }
    vcall2(wm, 0x74, w, proxy);
    void* cheat = CheatManager();
    if (cheat) vcall1(CheatManager(), 0x40, (void*)1);
    return true;
}

// ================================================================== 0x00809c50
// @ 0x00809c50
bool __cdecl SPUIHelpers_EndModal(void* w, unsigned result, char flag)
{
    if (!w) return false;
    if (g_app->inner->flag != 0 && g_msgBoxObj.p) {
        if (vp0(w, 0x10) && g_modalWin == w) {
            vcall1((IWin*)vp0(w, 0x10), 0xdc, g_msgBoxObj.p);
            g_modalWin = 0;
        }
    }
    vcall2(WindowManager(), 0x78, w, (void*)result);
    if (flag) {
        if (vp0(w, 0x10)) vcall1((IWin*)vp0(w, 0x10), 0xdc, w);
    }
    if (g_app->inner->flag != 0 && (g_894 != 0 || g_895 != 0)) {
        IWin* m = (IWin*)vp0(WindowManager(), 0x84);
        if (m && g_modalWin == 0 && (m == (IWin*)g_898 || m == (IWin*)g_89c)) {
            vcall1((IWin*)vp0(m, 0x10), 0xd8, g_msgBoxObj.p);
            vcall1((IWin*)vp0(m, 0x10), 0xe8, m);
            vcall1((IWin*)vp0(m, 0x10), 0xe8, g_msgBoxObj.p);
            g_modalWin = m;
        }
    }
    return true;
}

// ================================================================== 0x00809db0
struct MsgBox {
    MsgBox* ctor(void* where);                                  // 0x00816cb0
    bool Init(const void* key, bool b);                         // 0x00817040
    void Show(const char* a, const char* b, float f0, float f1);// 0x00816a20
};

// @ 0x00809db0
char __cdecl FUN_00809db0(void* where, const void* key)
{
    MsgBox* mem = (MsgBox*)dbgnew(0x78, "UI/cSPUIMessageBox", 0, 0, 0, 0);
    MsgBox* box;
    if (mem)
        box = mem->ctor(where);
    else
        box = 0;
    if (box) vcall0(box, 0);
    char ok = box->Init(key, true);
    if (ok) box->Show((const char*)0x15112d6, (const char*)0x15112d2, g_zero_13eb1bc, g_zero_13eb1bc);
    if (box) vcall0(box, 4);
    return ok;
}

// ================================================================== 0x00809e40
struct IObj0 {
    virtual void f0();                      // +0
};
struct IObj4 {
    virtual void f0();                      // +0
    virtual void f4();                      // +4
};
struct IWinObj {
    virtual void Fn0(IWin* w);              // +0
    virtual void Fn4(IWin* w, void* arg);   // +4
};

struct HelperObj {
    void** vt;          // +0
    IWinObj* m4;        // +4
    AutoRefIWin m8;     // +8
    AutoRefIWin mC;     // +0xc
    void Fn(IWin* w, void* arg);
};

// @ 0x00809e40
void __fastcall FUN_00809e40(HelperObj* self)
{
    void* mgr = GetUTFManager();
    if (!mgr) return;
    if (self->m8.p) {
        if (!vp0(self->m8.p, 0x10) || !WalkAll(self->m8.p)) {
            IWin* old = self->m8.p;
            if (old) {
                self->m8.p = 0;
                vcall0(old, 4);
            }
        }
    }
    IWin* front = (IWin*)vp0(mgr, 0x84);
    if (front) {
        vcall0(front, 0);
        if (!self->m8.p || !vb1(front, 0xf8, self->m8.p)) {
            IWin* old = self->m8.p;
            if (front != old) {
                vcall0(front, 0);
                self->m8.p = front;
                if (old) vcall0(old, 4);
            }
        }
    }
    if (!self->m8.p) {
        if (vp0(mgr, 4))
            self->m8 = (IWin*)vp0(mgr, 4);
    }
    if (self->m8.p) {
        vcall2(mgr, 0x4c, 0, self->m8.p);
        IWin* old = self->m8.p;
        if (old) {
            self->m8.p = 0;
            vcall0(old, 4);
        }
    }
    if (front) vcall0(front, 4);
}

// @ 0x00809f40
void HelperObj::Fn(IWin* w, void* arg)
{
    if (m4) m4->Fn4(w, arg);
    vcall1(w, 0x108, mC.p);
    if (mC.p) {
        IWin* old = mC.p;
        mC.p = 0;
        vcall0(old, 4);
    }
    FUN_00809e40(this);
    vcall1(this, 8, (void*)1);
}

// ================================================================== 0x00809ff0
struct ScaleArgs {
    int kind;
    float x;
    float y;
    int a;
    int b;
};

// @ 0x00809ff0
void __cdecl FUN_00809ff0(void* self)
{
    float* r = (float*)vp0(vp0(self, 0x10), 0x38);
    float a = -r[0];
    float b = -r[1];
    float t0 = a + r[0];
    float t1 = b + r[1];
    ScaleArgs args;
    args.x = (r[2] + a) + t0;
    args.y = (b + r[3]) + t1;
    args.x *= g_half_1471064;
    args.y *= g_half_1471064;
    args.kind = 6;
    args.a = 8;
    args.b = 0x3e8;
    void* mgr = GetUTFManager();
    vcall4(mgr, 0x10, 0, (IWin*)vp0(self, 0x10), &args, 0);
    args.kind = 7;
    args.a = 0;
    mgr = GetUTFManager();
    vcall4(mgr, 0x10, 0, (IWin*)vp0(self, 0x10), &args, 0);
}

// ================================================================== 0x0080a0f0
struct IdRange {
    unsigned* ids;
    unsigned count;
};

__declspec(noinline) void __cdecl FUN_00809ff0(void* self);

// @ 0x0080a0f0
bool __cdecl FUN_0080a0f0(IWin* w, IdRange* range)
{
    if (w) {
        IWin* c = (IWin*)vp1(w, 0x0c, (void*)0x8ed27e7a);
        if (c) {
            vcall0(c, 0);
            unsigned* ids = range->ids;
            unsigned count = range->count;
            for (unsigned i = 0; i < count; ++i) {
                if ((unsigned)vi0(w, 0x1c) == ids[i] || (unsigned)vi0(w, 0x20) == ids[i]) {
                    if (WalkAll((IWin*)vp0(c, 0x10))) {
                        FUN_00809ff0(c);
                        vcall0(c, 4);
                        return false;
                    }
                }
            }
            vcall0(c, 4);
        }
    }
    return true;
}

// ================================================================== 0x0080a1a0
// @ 0x0080a1a0
bool __cdecl sOnEnterEscKeys(int a, int key, int c)
{
    (void)a; (void)c;
    void* prop = 0;
    unsigned* ids = 0;
    unsigned count = 0;
    void* pm = PropertyManager();
    if (prop) {
        void* old = prop;
        prop = 0;
        vcall0(old, 4);
    }
    if (((char (__thiscall*)(void*, unsigned, void**))VSLOT(pm, 0x30))(pm, 0x5c770db7, &prop)) {
        if (key == 0x1b)
            GetPropertyAsUint32Array(prop, 0x8ae332a, &count, &ids);
        else if (key == 0xd)
            GetPropertyAsUint32Array(prop, 0x98051d6d, &count, &ids);
    }
    IWin* w0 = (IWin*)vp0(GetUTFManager(), 0x84);
    if (w0) vcall0(w0, 0);
    IWin* w1 = (IWin*)vp0(GetUTFManager(), 4);
    if (w1) vcall0(w1, 0);
    IWin* wins[2];
    wins[0] = w0;
    wins[1] = w1;
    for (int i = 0; i < 2; ++i) {
        if (wins[i]) {
            IdRange range;
            range.ids = ids;
            range.count = count;
            if (!VisitWindowTreeDepthFirst(wins[i], (void*)FUN_0080a0f0, &range)) {
                if (w1) vcall0(w1, 4);
                if (w0) vcall0(w0, 4);
                if (prop) vcall0(prop, 4);
                return i == 0;
            }
        }
    }
    if (w1) vcall0(w1, 4);
    if (w0) vcall0(w0, 4);
    if (prop) vcall0(prop, 4);
    return false;
}

// ================================================================== 0x0080a390
struct ModalBind {
    void** vt;          // +0
    IWinObj* m4;        // +4
    AutoRefIWin m8;     // +8
    AutoRefIWin mC;     // +0xc
    void Fn(IWin* w);
};

// @ 0x0080a390
void ModalBind::Fn(IWin* w)
{
    if (m4) m4->Fn0(w);
    WM* mgr = (WM*)GetUTFManager();
    if (mgr->w1())
        mgr->w19(0, mgr->w1());
    mgr->w19(0, w);
    void* alloc = GetUIAllocator();
    int* raw = (int*)op_new(0xc, 4, "cDoModalWinProc", alloc);
    int* obj;
    if (raw) {
        raw[1] = 0x13fa72c;
        raw[2] = 0;
        raw[0] = 0x1417bc0;
        raw[1] = 0x13fa750;
        obj = raw;
    } else {
        obj = 0;
    }
    IWin* old = mC.p;
    if ((IWin*)obj != old) {
        if (obj) ((IObj0*)obj)->f0();
        mC.p = (IWin*)obj;
        if (old) ((IObj4*)old)->f4();
    }
    vcall1(w, 0x104, mC.p);
}
