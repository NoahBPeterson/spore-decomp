// Slice s0080f7c0 (batch w2g6).
// UI::cSPUILayerManager / cSPUILayeredObject / cSPUILayout* region.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE2.
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            i32;
typedef float          f32;
typedef unsigned long  size_t_;

// ---------------------------------------------------------------- stubs ----
typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void* (__thiscall *VF1)(void*, void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void* (__thiscall *VF2)(void*, void*, void*);
typedef void  (__thiscall *VF2v)(void*, void*, void*);
typedef void* (__thiscall *VF3)(void*, void*, void*, void*);
typedef void  (__thiscall *VF3v)(void*, void*, void*, void*);
static inline void** VT(void* o) { return *(void***)o; }

// external routines (relocated calls)
extern void  __cdecl FlushCache(int);
extern void* __cdecl SP_WindowManager();          // 0x67caa0
extern void* __cdecl EapdDebug_8de1a0();          // 0x8de1a0
extern void* __cdecl EA_UTFWin_GetManager();      // 0x957f30
extern void* __cdecl SP_MessageServer();          // 0x67dcc0
extern void* __cdecl SP_ModelManager();           // 0x67dd80
extern void* __cdecl FUN_0067dd50();              // 0x67dd50
extern u8    __cdecl FUN_0082e700(int);           // 0x82e700
extern void* __cdecl SPUIHelpers_VisitWindowTreeDepthFirst(void*, void*, void*); // 0x807d30
extern int   __cdecl FUN_0082e1d0(void*);         // 0x82e1d0
extern bool  __cdecl FUN_00902fc0(void*);         // 0x902fc0
extern void  __cdecl FUN_0093a610(void*, void*);  // 0x93a610
// EA::XML::TokenIOContext: its destructor is a plain __thiscall with no stack arguments.
struct TokenIOContext {
    void Destroy();   // 0x00903120
};
extern void  __cdecl operator_delete__(void*);    // 0xf47380
extern void* __cdecl operator_new(u32, void*, int, int, const char*, int); // 0xf473a0
typedef void* (__thiscall *VFTh1)(void*);
extern char FUN_00812da0_sym;                     // 0x812da0 (arg in ecx, no stack)
extern void* __cdecl cSP_getA();                  // 0x67cad0 (global getter, no args)
extern u32   __cdecl eastl_RBTreeIncrement(void*);// 0x921580
extern void  __cdecl FUN_0080ee90(void*, void*);  // 0x80ee90

// relocated function/data symbols (addresses masked by the checker)
extern char FUN_0080e6b0_sym, FUN_0080ee90_sym, FUN_0080f380_sym, FUN_0080d6d0_sym,
            FUN_0080d770_sym, SerShutdown_sym, SerDtor_sym, ResetWinCache_sym,
            vtbl_cConnectionDialog, vtbl_014181d8, vtbl_014181c0, vtbl_SimSummarizer,
            vtbl_AddRef_014181e8, vtbl_EditorResource, DAT_013f6b3c,
            CountedPtr_00423c40, FUN_00998f60_sym, FUN_00998f80_sym, FUN_0080f7c0_sym,
            SerCtor_sym;
extern void __cdecl SPUIHelpers_UpdateMouseFocus_(int);
extern f32 DAT_0164ce30[9];                         // default rotation (9 floats)
extern f32 DAT_0164cd08, DAT_0164cd0c, DAT_0164cd10; // default translation x/y/z
extern u8  DAT_0164cf58;                             // Init() key-flag global
extern void* g_15fd918;

// ---- eastl vector of pointers (header + allocator) ----
struct PtrVec {
    void* mBegin;   // +0
    void* mEnd;     // +4
    void* mCap;     // +8
    void* mAlloc;   // +0xc
    void __thiscall erase(void* first, void* last);
};

// ---- model object (subset used here) ----
#include <intrin.h>
struct cMWModel {
    void** vtbl;      // +0
    u32    flags;     // +4
    u16    w8;        // +8
    u16    wa;        // +0xa
    f32    tx;        // +0xc
    f32    ty;        // +0x10
    f32    tz;        // +0x14
    f32    f18;       // +0x18
    f32    rot[9];    // +0x1c
    i32    ref40;     // +0x40
    u32    groups[8]; // +0x44
};

// ---- rbtree find helper ----
struct WorldTree {
    u8     pad0[4];     // +0  (manager +0xc)
    void*  mAnchor;     // +4  (manager +0x10)
    void*  mRoot;       // +8  (manager +0x14)
    void __thiscall find(void* sret, const u32* key);
};
struct WorldIter { void* node; };

// ------------------------------------------------------- cSPUILayeredObject -
class cSPUILayeredObject { public:
    void** vtbl;        // +0
    i32    mRefCount;   // +4
    void*  mpViewer;    // +8
    void*  mpWindow;    // +0xc
    void*  mpWinProc;   // +0x10
    PtrVec mModels;     // +0x14
    u8     pad24[0x6c - 0x24];
    f32    m6c;         // +0x6c
    u8     pad70[0x74 - 0x70];
    u8     b74;         // +0x74
    u8     pad75[2];
    u8     b77;         // +0x77

    bool __thiscall MethodF9D0(void* a, void* key);
    void* __thiscall MethodFAC0(void* a, void* b, void* cb);
    void* __thiscall AddModel(cMWModel* model);
};

// ------------------------------------------------------- cSPUILayerManager --
class cSPUILayerManager { public:
    void** vtbl;        // +0
    void** vtbl2;       // +4
    u8     pad8[4];
    PtrVec mObjects;    // +0xc
    u8     pad1c[4];
    PtrVec mRemoved;    // +0x20
    u8     pad30[4];
    u8     b34;         // +0x34
    u8     pad35[3];
    i32    i38;         // +0x38
    void*  p3c;         // +0x3c
    PtrVec mLayerInfos; // +0x40
    u8     pad50[0x94 - 0x50];
    u8     b94;         // +0x94

    bool __thiscall RemoveObject(cSPUILayeredObject* p);
    void __thiscall RemoveAllObjects();
    void __thiscall DrawLayer(void* a, void* b, void* c, void* d);
    void __thiscall MethodE6B0(void* pUIMgr, int layer, void* a, void* b); // 0x80e6b0
    bool __thiscall Shutdown();
    void* __thiscall AddObject(void* a, void* b, void* cb);
};

// ------------------------------------------------- cSPUILayoutObjectCollection
class cSPUILayoutObjectCollection { public:
    void** vtbl;            // +0
    u8     pad4[4];
    void*  p8;              // +8  (SerCollection secondary)
    u8     padc[4];
    void*  mAutoUpdate;     // +0x10
    u8     pad14[0x20 - 0x14];
    u8     mSerFlags;       // +0x20
    u8     pad21[0x64 - 0x21];
    void*  mBoxBegin;       // +0x64
    void*  mBoxEnd;         // +0x68
    u8     pad6c[0x88 - 0x6c];
    void*  m88;             // +0x88
    u8     b8c;             // +0x8c
    u8     b8d;             // +0x8d

    void __thiscall ResourceChanged();                 // 0x80feb0
    void* __thiscall ctor();                           // 0x8100d0
    void __thiscall Init(void* key);                   // 0x80fd60
    void __thiscall Subscribe(int b);                  // 0x80fe10
    void __thiscall detach_parent();                   // 0x810140
    void* __thiscall FindWindowByID(i32 id, char recurse); // 0x810200
    bool __thiscall SetVisibility(bool vis);           // 0x810310
    void* __thiscall VectorDtor(u8 flag);              // 0x8105d0
};
// view whose `this` is the SerCollection at collection+8
struct cSPUILayoutObjectCollectionV8 {
    u8     pad0[4];
    void*  mService;        // +0x04 (collection+0xc)
    void*  mAutoUpdate;     // +0x08 (collection+0x10)
    void*  mKeyA;           // +0x0c (collection+0x14) key instance
    u8     pad10[4];        // +0x10 (collection+0x18) key type
    void*  mKeyB;           // +0x14 (collection+0x1c) key group
    u8     bSerFlags;       // +0x18 (collection+0x20)
    u8     pad19[0x80 - 0x19];
    void*  m80;             // +0x80 (base+0x88)
    u8     pad84[1];        // +0x84
    u8     b85;             // +0x85 (base+0x8d)
    u8     pad86[2];        // +0x86..0x87
    void*  p88;             // +0x88 (base+0x90) reload layout owner
    void*  p8c;             // +0x8c (base+0x94) reload callback
    void*  p90;             // +0x90 (base+0x98) ctx

    void __thiscall Shutdown();  // 0x8101a0
    void __thiscall OnUnload();  // 0x810270
};

// --------------------------------------------------------------- cSPUILayout
class cSPUILayout { public:
    void** vtbl;            // +0
    i32    mRefCount;       // +4
    u8     pad8[0x14 - 8];
    cSPUILayoutObjectCollection* mpCollection; // +0x14

    cSPUILayout* __thiscall assign(cSPUILayout* rhs);      // 0x810050
    bool __thiscall IsVisible();                           // 0x810070
    void __thiscall SetReloadCallback(void* cb, void* ctx); // 0x810090
    bool __thiscall SetVisibility(bool vis);               // 0x810590
    void* __thiscall FindWindowByID(i32 id, char r);       // 0x8105b0
};

// --------------------------------------------------- cSPUILayoutResourceFactory
class cSPUILayoutResourceFactory { public:
    bool __thiscall Init();                            // 0x80ff50
    bool __thiscall WriteResource(void* res, void* rec, void* tok, int type); // 0x810460
};

// ------------------------------------------------------- cSPUILayoutManager
class cSPUILayoutManager { public:
    void** vtbl;            // +0
    u8     pad4[0xc - 4];
    WorldTree mTree;        // +0xc
    void*  mRoot;           // +0x14

    void* __thiscall GetWorldMainWindow(u32 id);       // 0x810620
    void  __thiscall Method10660(u32 id, bool vis);    // 0x810660
    void  __thiscall SetAllWorldsVisibility(bool vis); // 0x8106a0
    bool  __thiscall AnyWorldHidden();                 // 0x810730
    bool  __thiscall IsWorldVisible(u32 id);           // 0x810760
    void  __thiscall SetNodeVisibility(void* node, char delta); // 0x8103a0
};

// ---- resource-key filter / layout resource factory free helpers ----
struct ResourceKey { u32 mInstance; u32 mType; u32 mGroup; u32 mPad0c; };
struct cConnectionDialog {
    u32 f0, f4, f8, fc, f10, f14;
    void* __thiscall ctor();
    void* __thiscall ctor2(void* arg);
};
struct EastlNodeBuilder {
    void* __thiscall alloc(void* param);
};
// SerCollection operations (used as methods of the +8 subobject / base)
struct SerStub {
    void __thiscall ctor();
    void __thiscall Shutdown();
    void __thiscall dtor();
    void __thiscall Set(void* a, int b);   // 0x998f60
    bool __thiscall Get(void* key);        // 0x998f80
};
struct ObjStub {
    void __thiscall go();                  // 0x80f380
};
extern void __cdecl ResetChildWindowCache_();  // 0x962be0
struct cSPUIResourcesKeyFilter {
    bool __thiscall IsKeyIncluded(ResourceKey* key);   // 0x80fef0
};
struct cSPUILayoutResourceFactory2 {
    u32  __thiscall GetSupportedTypes(u32* out, u32 count); // 0x80ffa0
    bool __thiscall CanConvert(u32 from, u32 to);           // 0x80ffd0
};

// ============================ bodies ============================

// @ 0x0080f7c0
bool __thiscall cSPUILayerManager::RemoveObject(cSPUILayeredObject* p)
{
    int i = 0;
    cSPUILayeredObject** slot = (cSPUILayeredObject**)mObjects.mBegin;
    if (((int)((u8*)mObjects.mEnd - (u8*)mObjects.mBegin) >> 2) == 0) return false;
    do {
        if (*slot == p) {
            cSPUILayeredObject* tmp = p;
            if (tmp) ((VF0v)VT(tmp)[1])(tmp);
            if (mRemoved.mEnd < mRemoved.mCap) {
                void** dst = (void**)mRemoved.mEnd;
                mRemoved.mEnd = (u8*)mRemoved.mEnd + 4;
                if (dst) {
                    *dst = p;
                    if (p) ((VF0v)VT(p)[1])(p);
                }
            } else {
                FUN_0080ee90(mRemoved.mEnd, &tmp);
            }
            if (tmp) ((VF0v)VT(tmp)[2])(tmp);
            if (p->mpWindow) {
                if (p->b74) ((VF1v)VT(p->mpWindow)[0x108 / 4])(p->mpWindow, p->mpWinProc);
                void* w = p->mpWindow;
                if (w) { p->mpWindow = 0; ((VF0v)VT(w)[1])(w); }
                p->b74 = 0;
            }
            void* last = ((void**)mObjects.mEnd)[-1];
            void* old = (void*)*slot;
            if (last != old) {
                if (last) ((VF0v)VT(last)[1])(last);
                *slot = (cSPUILayeredObject*)last;
                if (old) ((VF0v)VT(old)[2])(old);
            }
            mObjects.mEnd = (u8*)mObjects.mEnd - 4;
            void* tail = *(void**)mObjects.mEnd;
            if (tail) ((VF0v)VT(tail)[2])(tail);
            return true;
        }
        ++i;
        ++slot;
    } while (i < ((int)((u8*)mObjects.mEnd - (u8*)mObjects.mBegin) >> 2));
    return false;
}

// @ 0x0080f8e0
void __thiscall cSPUILayerManager::RemoveAllObjects()
{
    while (mObjects.mBegin != mObjects.mEnd) {
        cSPUILayeredObject* o = *(cSPUILayeredObject**)mObjects.mBegin;
        RemoveObject(o);
    }
    mRemoved.erase(mRemoved.mBegin, mRemoved.mEnd);
}

// @ 0x0080f920
void __thiscall cSPUILayerManager::DrawLayer(void* a, void* b, void* c, void* d)
{
    void* mgr = EA_UTFWin_GetManager();
    if (!mgr) return;
    void* g = g_15fd918;
    if (g) {
        if (*(int*)(*(int*)((u8*)g + 0x3c) + 8) == 0) return;
    }
    if (b94 == 0) {
        b94 = 1;
    } else if (b94 == 1) {
        void* ms = SP_MessageServer();
        if (ms) {
            ms = SP_MessageServer();
            ((void(__thiscall*)(void*, u32, int, int))VT(ms)[0x14 / 4])(ms, 0x0366b9aa, 0, 0);
        }
        b94++;
    }
    mRemoved.erase(mRemoved.mBegin, mRemoved.mEnd);
    ((VF0v)VT(mgr)[0x28 / 4])(mgr);
    for (int i = 0; i < 0xf; ++i) {
        if (FUN_0082e700(i))
            MethodE6B0(mgr, i, a, b);
    }
    (void)c; (void)d;
}

// @ 0x0080f9d0
bool __thiscall cSPUILayeredObject::MethodF9D0(void* a, void* key)
{
    if (*(int*)((u8*)key + 8) == 0x12) {
        cSPUILayeredObject* o = *(cSPUILayeredObject**)((u8*)this + 0xc);
        if (*(void**)((u8*)o + 0xc) == a && o->b74)
            ((cSPUILayerManager*)cSP_getA())->RemoveObject(o);
    }
    return false;
}

// @ 0x0080fa00
extern void __fastcall FUN_0080f380_fwd(void*);   // 0x80f380
void __fastcall FUN_0080fa00(void* p)
{
    if (p) p = (u8*)((u32)p + 0xfffffdb0u);
    else   p = 0;
    ((ObjStub*)p)->go();
}

// @ 0x0080fa20
bool __thiscall cSPUILayerManager::Shutdown()
{
    if (b34) {
        void* o = FUN_0067dd50();
        ((void(__thiscall*)(void*, int))VT(o)[0x50 / 4])(o, 0x1e);
        RemoveAllObjects();
        for (int i = 0; i < 0x3c; i += 4) {
            void* q = *(void**)((u8*)mLayerInfos.mBegin + i);
            if (q) { *(void**)((u8*)mLayerInfos.mBegin + i) = 0; ((VF0v)VT(q)[1])(q); }
        }
        mLayerInfos.erase(mLayerInfos.mBegin, mLayerInfos.mEnd);
        ((void(__thiscall*)(void*, int))VT(p3c)[0x134 / 4])(p3c, 0);
        void* q = p3c;
        if (q) { p3c = 0; ((VF0v)VT(q)[1])(q); }
        void* mm = SP_ModelManager();
        ((void(__thiscall*)(void*, unsigned int))VT(mm)[0x18 / 4])(mm, 0x032fab08);
        b34 = 0;
    }
    return true;
}

// @ 0x0080fac0
void* __thiscall cSPUILayeredObject::MethodFAC0(void* a, void* b, void* cb)
{
    u8* base = (u8*)cSP_getA();
    void* picked;
    if (mpWindow) {
        struct VisitCtx { u8 bContinue; i32 nBest; i32 nWorst; } ctx;
        cSP_getA();
        ctx.nBest = 0x2710;
        ctx.nWorst = 0xffffd8f0;
        ctx.bContinue = 0;
        SPUIHelpers_VisitWindowTreeDepthFirst(mpWindow, &FUN_0080d6d0_sym, &ctx);
        if ((u32)ctx.nBest < 0xf) picked = (void*)(*(int*)(base + 0x40) + ctx.nBest * 4);
        else picked = 0;
    } else {
        picked = (void*)(*(int*)(base + 0x40));
    }
    void* res;
    if (cb)
        res = ((void*(__cdecl*)(void*, void*, void*))cb)(a, b, *(void**)picked);
    else
        res = ((void*(__cdecl*)(void*, void*, void*))&FUN_0080d770_sym)(a, b, *(void**)picked);
    cMWModel* m = (cMWModel*)res;
    if (m) {
        m->ref40++;
        __movsd((unsigned long*)m->rot, (unsigned long*)DAT_0164ce30, 9);
        m->f18 = 1.0f;
        *(u32*)&m->tx = *(u32*)&DAT_0164cd08;
        *(u32*)&m->ty = *(u32*)&DAT_0164cd0c;
        *(u32*)&m->tz = *(u32*)&DAT_0164cd10;
        m->w8 = 0; m->wa = 0;
        void* mm = SP_ModelManager();
        u32 grp = ((u32(__thiscall*)(void*, unsigned int, int))VT(mm)[0x28 / 4])(mm, 0x032fab27, 0);
        if (grp < 0x40)
            m->groups[grp >> 5] &= ~(1u << (grp & 0x1f));
        if (mModels.mEnd < mModels.mCap) {
            void** dst = (void**)mModels.mEnd;
            mModels.mEnd = (u8*)mModels.mEnd + 4;
            if (dst) { *dst = m; m->ref40++; }
        } else {
            cMWModel* tmp = m;
            ((void* (__thiscall*)(void*, void*, void*))&CountedPtr_00423c40)(&mModels, mModels.mEnd, &tmp);
            m = tmp;
        }
        b77 = 1;
        m6c = 0.0f;
        if (m) {
            if (m->ref40 > 1) m->ref40--;
            else ((void(__thiscall*)(void*, int))VT(m->vtbl)[0x170 / 4])(m, (int)(m->flags >> 0x1f) & 1);
        }
    }
    return m;
}

// @ 0x0080fc50
void* __thiscall cSPUILayeredObject::AddModel(cMWModel* m)
{
    if (m) {
        m->f18 = 1.0f;
        __movsd((unsigned long*)m->rot, (unsigned long*)DAT_0164ce30, 9);
        *(u32*)&m->tx = *(u32*)&DAT_0164cd08;
        *(u32*)&m->ty = *(u32*)&DAT_0164cd0c;
        *(u32*)&m->tz = *(u32*)&DAT_0164cd10;
        m->w8 = 0; m->wa = 0;
        void* mm = SP_ModelManager();
        u32 grp = ((u32(__thiscall*)(void*, unsigned int, int))VT(mm)[0x28 / 4])(mm, 0x032fab27, 0);
        if (grp < 0x40)
            m->groups[grp >> 5] &= ~(1u << (grp & 0x1f));
        m->ref40++;
        cMWModel* tmp = m;
        if (mModels.mEnd < mModels.mCap) {
            void** dst = (void**)mModels.mEnd;
            mModels.mEnd = (u8*)mModels.mEnd + 4;
            if (dst) { *dst = m; m->ref40++; }
        } else {
            ((void* (__thiscall*)(void*, void*, void*))&CountedPtr_00423c40)(&mModels, mModels.mEnd, &tmp);
        }
        if (tmp) {
            if (tmp->ref40 > 1) tmp->ref40--;
            else ((void(__thiscall*)(void*, int))VT(tmp->vtbl)[0x170 / 4])(tmp, (int)(tmp->flags >> 0x1f) & 1);
        }
        b77 = 1;
        m6c = 0.0f;
    }
    return m;
}

// @ 0x0080fd60
void __thiscall cSPUILayoutObjectCollection::Init(void* key)
{
    u32 k0 = ((u32*)key)[0], k1 = ((u32*)key)[1], k2 = ((u32*)key)[2];
    if (DAT_0164cf58) k2 = (k2 & 0xffff42ff) | 0x4200;
    void* wm = SP_WindowManager();
    void* iface = ((void*(__thiscall*)(void*))VT(wm)[1])(wm);
    void* obj = iface ? (void*)((u8*)iface - 4) : 0;
    void* a = ((VFTh1)&FUN_00812da0_sym)(obj);
    ((SerStub*)((u8*)this + 8))->Set(a, 1);
    b8d = 0;
    u32 k[3] = { k0, k1, k2 };
    if (!((SerStub*)((u8*)this + 8))->Get(k)) {
        if (!DAT_0164cf58) {
            k[2] = (k[2] & 0xffff42ff) | 0x4200;
            ((SerStub*)((u8*)this + 8))->Get(k);
        }
    }
}

// @ 0x0080fe10
void __thiscall cSPUILayoutObjectCollection::Subscribe(int b)
{
    if (!(mSerFlags & 1)) return;
    void* svc = *(void**)((u8*)this + 0xc);
    void* au = ((void*(__thiscall*)(void*, unsigned int))VT(svc)[0x10 / 4])(svc, 0x2fbf2058);
    mAutoUpdate = au;
    if (!au) return;
    struct SerKey { u32 mInstance; u32 mType; u32 mGroup; };
    u32 inst = *(u32*)((u8*)this + 0x14);
    u32 grp  = *(u32*)((u8*)this + 0x1c);
    SerKey k0 = { inst, 0xefbda3ff, grp };
    SerKey k1 = { inst, 0x050f4731, grp };
    if ((char)b) {
        ((VF2v)VT(au)[0x10 / 4])(au, &k0, (void*)((u8*)this + 8));
        au = *(void**)((u8*)this + 0x10);
        ((VF2v)VT(au)[0x10 / 4])(au, &k1, (void*)((u8*)this + 8));
    } else {
        ((VF2v)VT(au)[0x14 / 4])(au, &k0, (void*)((u8*)this + 8));
        au = *(void**)((u8*)this + 0x10);
        ((VF2v)VT(au)[0x14 / 4])(au, &k1, (void*)((u8*)this + 8));
    }
}

// @ 0x0080feb0
void __thiscall cSPUILayoutObjectCollection::ResourceChanged()
{
    if (*(u32*)((u8*)this + 0x8c) != 0) {
        FlushCache(6);
        ((void(__thiscall*)(void*))VT(this)[0x14 / 4])(this);
    }
}

// @ 0x008100d0
void* __thiscall cSPUILayoutObjectCollection::ctor()
{
    u8* s = (u8*)this;
    *(void* volatile*)s = &vtbl_SimSummarizer;
    *(u32*)(s + 4) = 0;
    ((SerStub*)(s + 8))->ctor();
    *(void* volatile*)s = &vtbl_014181d8;
    *(void* volatile*)(s + 8) = &vtbl_014181c0;
    *(u32*)(s + 0x88) = 0;
    s[0x8d] = 0;
    *(u32*)(s + 0x90) = 0;
    *(u32*)(s + 0x94) = 0;
    *(u32*)(s + 0x98) = 0;
    s[0x8c] = 1;
    return s;
}

// @ 0x0080fef0
bool __thiscall cSPUIResourcesKeyFilter::IsKeyIncluded(ResourceKey* key)
{
    return key->mType == 0xef7d16e1 || key->mType == 0x0510a95b;
}

// @ 0x0080ff50
bool __thiscall cSPUILayoutResourceFactory::Init()
{
    u32 types[3] = { 0x250fe9a2, 0x050f4731, 0xefbda3ff };
    void* o = EapdDebug_8de1a0();
    ((void(__thiscall*)(void*, unsigned int, u32*, int))VT(o)[0x24 / 4])(o, 0x0510a95b, types, 3);
    return true;
}

// @ 0x0080ffa0
u32 __thiscall cSPUILayoutResourceFactory2::GetSupportedTypes(u32* out, u32 count)
{
    if (out) {
        if (count < 3) return 0;
        out[0] = 0xefbda3ff;
        out[1] = 0x050f4731;
        out[2] = 0x250fe9a2;
    }
    return 3;
}

// @ 0x0080ffd0
bool __thiscall cSPUILayoutResourceFactory2::CanConvert(u32 from, u32 to)
{
    if ((from == 0xefbda3ff || from == 0x050f4731 || from == 0x250fe9a2) && to == 0x0510a95b)
        return true;
    return false;
}

// @ 0x00810000
void* __thiscall cConnectionDialog::ctor()
{
    u32* s = (u32*)this;
    s[1] = 0;
    *(void**)s = &vtbl_cConnectionDialog;
    s[2] = 0; s[3] = 0; s[4] = 0; s[5] = 0;
    return this;
}

// @ 0x00810020
void* __thiscall cConnectionDialog::ctor2(void* arg)
{
    u32* s = (u32*)this;
    s[1] = 0;
    *(void**)s = &vtbl_cConnectionDialog;
    s[2] = 0; s[3] = 0; s[4] = 0; s[5] = 0;
    void* c = 0;
    if (c) { s[5] = 0; ((VF0v)VT(c)[2])(c); }
    (void)arg;
    return this;
}

// @ 0x00810050
cSPUILayout* __thiscall cSPUILayout::assign(cSPUILayout* rhs)
{
    if (mpCollection) {
        cSPUILayoutObjectCollection* c = mpCollection;
        mpCollection = 0;
        ((VF0v)VT(c)[2])(c);
    }
    (void)rhs;
    return this;
}

// @ 0x00810070
bool __thiscall cSPUILayout::IsVisible()
{
    cSPUILayoutObjectCollection* c = mpCollection;
    if (c) return *(bool*)((u8*)c + 0x8c);
    return false;
}

// @ 0x00810090  (installs the reload callback on the collection; reading the collection into a
// local first is what makes cl keep it in eax from the first instruction to the ret, as retail does)
void __thiscall cSPUILayout::SetReloadCallback(void* cb, void* ctx)
{
    cSPUILayoutObjectCollection* c = mpCollection;
    if (c) {
        *(void**)((u8*)c + 0x90) = this;
        *(void**)((u8*)c + 0x94) = cb;
        *(void**)((u8*)c + 0x98) = ctx;
    }
}

// @ 0x00810140
void __thiscall cSPUILayoutObjectCollection::detach_parent()
{
    u8* s = (u8*)this;
    void** p = *(void***)(s + 0x64);
    while (p != *(void***)(s + 0x68)) {
        void* o = *p++;
        void* q = ((void*(__thiscall*)(void*, void*))VT(o)[0xc / 4])(o, (void*)0xeeee8218);
        if (!q) continue;
        if (((VF0)VT(q)[0x10 / 4])(q)) {
            void* r = ((VF0)VT(q)[0x10 / 4])(q);
            ((VF1v)VT(r)[0xdc / 4])(r, q);
        }
    }
}

// @ 0x008101a0
void __thiscall cSPUILayoutObjectCollectionV8::Shutdown()
{
    if (b85) return;
    b85 = 1;
    cSPUILayoutObjectCollection* coll = (cSPUILayoutObjectCollection*)((u8*)this - 8);
    coll->detach_parent();
    if (m80) {
        void* c = m80;
        m80 = 0;
        ((VF0v)VT(c)[1])(c);
    }
    coll->Subscribe(0);
    ((SerStub*)this)->Shutdown();
    b85 = 0;
}

// @ 0x00810200
void* __thiscall cSPUILayoutObjectCollection::FindWindowByID(i32 id, char recurse)
{
    u8* s = (u8*)this;
    void** p = *(void***)(s + 0x64);
    void** e = *(void***)(s + 0x68);
    while (p != e) {
        void* o = *p++;
        void* q = ((void*(__thiscall*)(void*, void*))VT(o)[0xc / 4])(o, (void*)0xeeee8218);
        if (!q) continue;
        i32 got = (i32)(size_t)((VF0)VT(q)[0x1c / 4])(q);
        if (got == id) return q;
        if (recurse) {
            void* r = ((VF2)VT(q)[0xf0 / 4])(q, (void*)(size_t)id, (void*)1);
            if (r) return r;
        }
    }
    return 0;
}

// @ 0x00810270
void __thiscall cSPUILayoutObjectCollectionV8::OnUnload()
{
    cSPUILayoutObjectCollection* coll = (cSPUILayoutObjectCollection*)((u8*)this - 8);
    if (bSerFlags & 1) {
        void* svc = mService;
        void* au = ((void*(__thiscall*)(void*, unsigned int))VT(svc)[0x10 / 4])(svc, 0x2fbf2058);
        mAutoUpdate = au;
        if (au) {
            struct SerKey { u32 mInstance; u32 mType; u32 mGroup; };
            u32 inst = *(u32*)&mKeyA;
            u32 grp  = *(u32*)&mKeyB;
            SerKey k0 = { inst, 0xefbda3ff, grp };
            SerKey k1 = { inst, 0x050f4731, grp };
            ((VF2v)VT(au)[0x14 / 4])(au, &k0, (void*)this);
            au = mAutoUpdate;
            ((VF2v)VT(au)[0x14 / 4])(au, &k1, (void*)this);
        }
    }
    ResetChildWindowCache_();
    if (p8c) {
        ((void(__cdecl*)(void*, void*, int))p8c)(p90, p88, 0);
    }
    coll->detach_parent();
}

// @ 0x00810310
bool __thiscall cSPUILayoutObjectCollection::SetVisibility(bool vis)
{
    u8* s = (u8*)this;
    if (*(u32*)(s + 0x88) == 0) {
        s[0x8c] = (u8)vis;
        return true;
    }
    void** p = *(void***)(s + 0x64);
    void** e = *(void***)(s + 0x68);
    while (p != e) {
        void* o = *p++;
        void* q = ((void*(__thiscall*)(void*, void*))VT(o)[0xc / 4])(o, (void*)0xeeee8218);
        if (!q) continue;
        void* g = ((VF0)VT(q)[0x10 / 4])(q);
        if (g == m88 || g == 0)
            ((void(__thiscall*)(void*, int, bool))VT(q)[0x7c / 4])(q, 1, vis);
    }
    SPUIHelpers_UpdateMouseFocus_(1);
    s[0x8c] = (u8)vis;
    return true;
}

// @ 0x008103a0
void __thiscall cSPUILayoutManager::SetNodeVisibility(void* node, char delta)
{
    u8* n = (u8*)node;
    int nv = *(int*)(n + 0xc) + (delta ? -1 : 1);
    if (nv <= 0) nv = 0;
    if (nv >= 0 && nv < 2) {
        void* o = *(void**)(n + 8);
        ((void(__thiscall*)(void*, int, int))VT(o)[0x7c / 4])(o, 1, nv == 0);
    }
    *(int*)(n + 0xc) = nv;
}

// @ 0x00810400
void __fastcall cEditorResource_dtor(void* thisp)
{
    u32* s = (u32*)thisp;
    *(void* volatile*)s = &vtbl_AddRef_014181e8;  // volatile on both: the original stores the vptr
    void* p = *(void* volatile*)((u8*)s + 0x18);  // before reloading +0x18, and the two do not swap
    if (p) { s[6] = 0; ((VF0v)VT(p)[2])(p); }
    void* q = (void*)s[8];
    s[7] = 0;
    if (q) { ((TokenIOContext*)q)->Destroy(); operator_delete__(q); s[8] = 0; }
    p = (void*)s[6];
    if (p) ((VF0v)VT(p)[2])(p);
    s[0] = (u32)&vtbl_EditorResource;
}

// @ 0x00810460
bool __thiscall cSPUILayoutResourceFactory::WriteResource(void* res, void* rec, void* tok, int type)
{
    (void)tok;
    bool bl = false;
    if (type == 0x250fe9a2) {
        if (!res) return bl;
        void* x = ((void*(__thiscall*)(void*, unsigned int))VT(res)[0xc / 4])(res, 0x05adf5fb);
        if (!x) return bl;
        if (*(int*)((u8*)x + 0x1c)) bl = (bool)FUN_0082e1d0(x);
        void* y = *(void**)((u8*)x + 0x18);
        if (!y) return bl;
        ((void(__thiscall*)(void*, int, int))VT(y)[0x28 / 4])(y, 0, 0);
        void* z = *(void**)((u8*)x + 0x18);
        u32 w = ((u32(__thiscall*)(void*, int))VT(rec)[0x18 / 4])(rec, -1);
        FUN_0093a610(z, (void*)(size_t)w);
        return true;
    } else if (type == 0x050f4731) {
        if (!res) return bl;
        void* pp = *(void**)((u8*)res + 0x1c);
        if (!pp) return bl;
        void* qq = *(void**)((u8*)res + 0x20);
        u32 w = ((u32(__thiscall*)(void*, void*, int, void*))VT(rec)[0x18 / 4])(rec, pp, 1, qq);
        bl = FUN_00902fc0((void*)(size_t)w);
    }
    return bl;
}

// @ 0x00810520
void* __thiscall EastlNodeBuilder::alloc(void* param)
{
    u8* self = (u8*)param;
    void* base = operator_new(0x1c, &DAT_013f6b3c, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    u8* s = (u8*)base + 0x10;
    if (s) {
        void* p = *(void**)self;
        *(void**)s = p;
        if (p) ((VF0v)VT(p)[1])(p);
        *(void**)(s + 4) = *(void**)(self + 4);
        *(void**)(s + 8) = *(void**)(self + 8);
    }
    return base;
}

// @ 0x00810590
bool __thiscall cSPUILayout::SetVisibility(bool vis)
{
    if (mpCollection) return mpCollection->SetVisibility(vis);
    return false;
}

// @ 0x008105b0
void* __thiscall cSPUILayout::FindWindowByID(i32 id, char r)
{
    if (mpCollection) return mpCollection->FindWindowByID(id, r);
    return 0;
}

// @ 0x008105d0
void* __thiscall cSPUILayoutObjectCollection::VectorDtor(u8 flag)
{
    u8* s = (u8*)this;
    u8* ser = s + 8;
    *(void**)s = &vtbl_014181d8;
    *(void**)ser = &vtbl_014181c0;
    void* c = m88;
    if (c) ((VF0v)VT(c)[1])(c);
    ((SerStub*)(s + 8))->dtor();
    *(void**)s = &vtbl_SimSummarizer;
    if (flag & 1) operator_delete__(s);
    return s;
}

// @ 0x00810620
void* __thiscall cSPUILayoutManager::GetWorldMainWindow(u32 id)
{
    u8* anchor = (u8*)this + 0x10;
    WorldIter it;
    it.node = this;
    mTree.find(&it, &id);
    if ((u8*)it.node == anchor) return 0;
    if ((u8*)it.node + 0x14 == 0) return 0;
    return *(void**)((u8*)it.node + 0x1c);
}

// @ 0x00810660
void __thiscall cSPUILayoutManager::Method10660(u32 id, bool vis)
{
    u8* anchor = (u8*)this + 0x10;
    WorldIter it;
    it.node = this;
    mTree.find(&it, &id);
    if ((u8*)it.node != anchor && (u8*)it.node + 0x14 != 0)
        SetNodeVisibility((u8*)it.node + 0x14, vis);
}

// @ 0x008106a0
void __thiscall cSPUILayoutManager::SetAllWorldsVisibility(bool vis)
{
    u8* s = (u8*)this;
    void* anchor = (void*)(s + 0x10);
    void* node = *(void**)(s + 0x14);
    if (node == anchor) return;
    int delta = vis ? -1 : 1;
    do {
        u8* cur = (u8*)node;
        node = (void*)(size_t)eastl_RBTreeIncrement(node);
        int nv = *(int*)(cur + 0x20) + delta;
        if (nv <= 0) nv = 0;
        if (nv >= 0 && nv < 2) {
            void* o = *(void**)(cur + 0x1c);
            ((void(__thiscall*)(void*, int, bool))VT(o)[0x7c / 4])(o, 1, nv == 0);
        }
        *(int*)(cur + 0x20) = nv;
    } while (node != anchor);
}

// @ 0x00810730
bool __thiscall cSPUILayoutManager::AnyWorldHidden()
{
    u8* s = (u8*)this;
    void* anchor = (void*)(s + 0x10);
    void* node = *(void**)(s + 0x14);
    while (node != anchor) {
        u8* cur = (u8*)node;
        node = (void*)(size_t)eastl_RBTreeIncrement(node);
        if (*(int*)(cur + 0x20) == 0) return true;
    }
    return false;
}

// @ 0x00810760
bool __thiscall cSPUILayoutManager::IsWorldVisible(u32 id)
{
    u8* anchor = (u8*)this + 0x10;
    WorldIter it;
    it.node = this;
    mTree.find(&it, &id);
    if ((u8*)it.node == anchor) return false;
    if ((u8*)it.node + 0x14 == 0) return false;
    return *(int*)((u8*)it.node + 0x14 + 0xc) == 0;
}
