// Slice s008107d0 (batch w2g6).
// UI layout-resource factory / layout-object collection helpers (EASTL vectors, rbtree).
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
typedef void* (__thiscall *VF3)(void*, void*, void*, void*);
typedef void  (__thiscall *VF4v)(void*, void*, void*, void*);
typedef u8    (__thiscall *VF3u)(void*, void*, void*, u32);
typedef u8    (__thiscall *VF4u)(void*, void*, void*, void*, u32);
static inline void** VT(void* o) { return *(void***)o; }

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)

extern void  __cdecl operator_delete__(void*);                       // 0xf47380
extern void* __cdecl operator_new(u32, void*, int, int, const char*, int); // 0xf473a0
extern void* __cdecl ZoneNew(u32, void*, int, int, void*, int);      // 0x926020
extern void  __cdecl FlushCache(int);                                // 0x6ad7c0
extern void* __cdecl EA_Messaging_GetServer();                       // 0x883860
extern void* __cdecl EA_UTFWin_GetManager();                         // 0x957f30
extern int   __cdecl FUN_006adc60(int, int);                         // 0x6adc60
extern int   __cdecl FUN_00903120(void*);                            // 0x903120
extern void* __cdecl FUN_00810f80(u32, void*, void*);                // 0x810f80
extern void  __cdecl FUN_005c1dc0(void*, void*, void*);              // 0x5c1dc0
extern void* __cdecl FUN_011e0744(void*, const void*, u32);          // 0x11e0744 (memcpy)
extern bool  __cdecl FUN_0082e1d0(void*);                            // 0x82e1d0
extern u8    __cdecl FUN_00902d40(void*, void*, u32, void*);         // 0x902d40
extern void  __cdecl RBTreeInsert(void*, void*, void*, int);         // 0x9216a0
extern void  __cdecl SlotMessage_Destruct(void*);                    // 0x421cf0
extern void* __cdecl SPUIHelpers_CreateWindow(void*);                // 0x806370
extern void  __cdecl TokenIOContext_ClearStrings(void*);             // 0x902460
extern void  __cdecl FUN_00921580(void*);                            // 0x921580 RBTreeIncrement
extern void  __cdecl FUN_00921880(void*, void*);                     // 0x921880 RBTreeErase
extern void* __cdecl FUN_008de1a0();                                 // 0x8de1a0 ObjectError
extern void  __cdecl FUN_00957d30();                                 // 0x957d30 ProcessPendingTextures

// external member-style entry points (this in ecx; relocation targets are masked)
struct CallStubs {
    void* __thiscall Find(void**, void*);          // 0xe5c780 (rbtree find)
    void* __thiscall FindWindowByID(int, int);     // 0x810200
    void  __thiscall SetVisibility(u32);           // 0x810310
    void  __thiscall StreamAssign(void*);          // 0x572620
    void  __thiscall KeyMap(void*, void*, u32);    // 0x810c20
    void  __thiscall KeyAdd(void*, void*, u32);    // 0x810b90
    void  __thiscall VecPush(void**, void**);      // 0x82f170
    void  __thiscall Nuke(void*);                  // 0x9a9600
    void* __thiscall TokenCtor(void*);             // 0x9030b0
    void* __thiscall CollCtor();                   // 0x8100d0
    u8    __thiscall CollInit(void*);              // 0x80fd60
    void* __thiscall BgLoad(u32, const char*);     // 0x93bca0
    void* __thiscall MemStream(void*, u32, const char*); // 0x93c270
};

extern char vtbl_UI_BehaviorMessage, vtbl_013eb844, vtbl_Editor_cPropertyList,
            vtbl_AddRef_014181e8, vtbl_UI_cSPUILayoutResource, DAT_013f6b3c,
            DAT_013ebb38, vtbl_013eb90c, vtbl_014181a8,
            FUN_009030b0_sym, BgLoading_sym, MemoryStream_sym,
            FUN_008100d0_sym, FUN_0080fd60_sym, FUN_00811110_sym;
extern u8 g_164cf58;

// ---------------------------------------------------------------- helpers --
struct PtrVec {
    void** mBegin;   // +0
    void** mEnd;     // +4
    void** mCap;     // +8
    void*  mAlloc;   // +0xc
    void*  mInline;  // +0x10
    void __thiscall dtor();                                   // 0x810a50
    PtrVec* __thiscall operator=(const PtrVec& rhs);          // 0x811260
    void __thiscall insert(void** pos, void** val);           // 0x810e30
};
struct EastlAlloc { u32 a, b, c, d, e; };

// rbtree node base (anchor at tree+0, root at tree+4)
struct RBNode { RBNode* left; RBNode* right; RBNode* parent; void* key; };
struct RBTree {
    RBNode  anchor;          // +0x00
    void*   mpHead;          // +0x10 (not touched by insertNode)
    i32     count;           // +0x14
    void __thiscall insertNode(void** out, RBNode* hint, u32* key, bool right); // 0x810af0
};

// generic resource factory object
class cSPUILayoutResourceFactory { public:
    bool  __thiscall CreateResource(void* a, void* b, u32 c, void* typeTag);   // 0x8107d0
    bool  __thiscall Function8a0(void* a, void* b, u32 c, void* typeTag);      // 0x8108a0
};

struct cSPUILayoutObjectCollection;
struct cSPUILayerManagerLike {
    void* __thiscall CreateObjects(u32 key);              // 0x810fd0
    void* __thiscall Method11110(u32 a, u32 b);           // 0x811110
    bool  __thiscall Method11330(u32 a);                  // 0x811330
    bool  __thiscall InitMessaging();                     // 0x8115a0
    bool  __thiscall ShutdownMessaging();                 // 0x8116e0
};

// allocated SPUILayoutResource (0x24 bytes)
struct SPUILayoutResourceObj {
    void* mpVtbl;    // +0x00
    u32   mRef;      // +0x04 (initialised with an atomic exchange)
    void* mpA;       // +0x08
    u32   mType;     // +0x0c
    void* mpB;       // +0x10
    u32   mPad14;    // +0x14
    u32   mPad18;    // +0x18
    u32   mPad1c;    // +0x1c
    u32   mPad20;    // +0x20
};

// state block returned by the token-interface vtable slot 4
struct AppResState {
    void* mpSlot;    // +0x00
    u32   mFlags;    // +0x04
    void* mpExtra;   // +0x08
};

// object reloaded by Function8a0
struct ReloadTarget {
    u8    mPad00[0x18];
    void* mpStreamSlot;  // +0x18
    u32   mnReloadKey;   // +0x1c
    void* mpTokenCtx;    // +0x20
};

// shared pointer / refcount pair produced by the BackgroundLoading ctor
struct AutoRefBlock {
    void* mpVtbl;        // +0x00 (at ref+4)
    volatile u32 mCount; // +0x04 (at ref+8)
};
struct BgSharedPtr {
    u32          mPad00;   // +0x00
    AutoRefBlock mRef;     // +0x04
    u32          mPad0c;   // +0x0c
    void*        mpData;   // +0x10
    u32          mPad14;   // +0x14
};

// temporary key / value pair passed to FUN_00810c20
struct InsertVal { u8 mFlag; f32 mF; };
struct MapKV     { void* mpColl; InsertVal mVal; };
struct ReqKey    { u8 mFlag; f32 mF; void* mpColl; };

// messaging slot-message base (0x40 bytes)
struct SlotMessageLite {
    void* mpVtbl;    // +0x00
    u32   mRef;      // +0x04
    u32   mKind;     // +0x08
    u8    mPad0c[4]; // +0x0c
    void* mpColl;    // +0x10
    u8    mPad14[0x1c];
    u32   mMsgId;    // +0x30
    u8    mPad34[4];
    u32   mTail;     // +0x38
};

struct LocalPtrVec { void** mBegin; void** mEnd; void** mCap; };

// ============================ bodies ============================

// @ 0x00810a50
void __thiscall PtrVec::dtor()
{
    void** e = mEnd;
    void** b = mBegin;
    while (b < e) {
        void* p = *b;
        if (p) ((VF0v)VT(p)[2])(p);
        ++b;
    }
    void* a = (void*)mBegin;
    if (a && a != mInline) operator_delete__(a);
}

// @ 0x008107d0
bool __thiscall cSPUILayoutResourceFactory::CreateResource(void* a, void* b, u32 c, void* typeTag)
{
    bool result = false;
    if ((u32)(size_t_)typeTag == 0x0510a95b) {
        SPUILayoutResourceObj* obj = (SPUILayoutResourceObj*)operator_new(0x24, "App/SPUILayoutResource", 0, 0, 0, 0);
        u8* out = 0;
        if (obj) {
            obj->mpVtbl = &vtbl_Editor_cPropertyList;
            _InterlockedExchange((volatile long*)&obj->mRef, 0);
            obj->mpA = 0;
            obj->mType = 0;
            obj->mpB = 0;
            obj->mPad14 = 0;
            obj->mpVtbl = &vtbl_AddRef_014181e8;
            obj->mPad18 = 0;
            obj->mPad1c = 0;
            obj->mPad20 = 0;
            ((void(__thiscall*)(void*))VT(obj)[0])(obj);
            out = (u8*)obj;
        }
        AppResState* st = (AppResState*)((VF0)VT(a)[4])(a);
        *(void**)(out + 8) = st->mpSlot;
        *(u32*)(out + 0xc) = 0x0510a95b;
        *(void**)(out + 0x10) = st->mpExtra;
        if (((VF4u)VT(this)[9])((void*)this, a, out, (void*)(size_t_)c, 0x0510a95b)) {
            *(void**)((u8*)b) = out;
            ((void(__thiscall*)(void*))VT(out)[0])(out);
            ((void(__thiscall*)(void*))VT(out)[1])(out);
            result = true;
        } else {
            ((void(__thiscall*)(void*))VT(out)[1])(out);
        }
    }
    return result;
}

// @ 0x008108a0
bool __thiscall cSPUILayoutResourceFactory::Function8a0(void* a, void* b, u32 c, void* typeTag)
{
    bool result = false;
    (void)c;
    if ((u32)(size_t_)typeTag == 0x0510a95b) {
        ReloadTarget* t = (ReloadTarget*)b;
        void* old = t->mpTokenCtx;
        t->mnReloadKey = 0;
        if (old) {
            FUN_00903120(old);
            operator_delete__(old);
            t->mpTokenCtx = 0;
        }
        u8* iface = (u8*)a;
        void* k = ((VF0)VT(iface)[4])(iface);
        if (*(u32*)((u8*)k + 4) == 0x250fe9a2) {
            u8* pi = (u8*)((VF0)VT(iface)[6])(iface);
            if (pi) ((VF0v)VT(pi)[1])(pi);
            u32 v = ((u32(__thiscall*)(void*))VT(pi)[7])(pi);
            u8* sp = (u8*)ZoneNew(0x18, &DAT_013f6b3c, 0, 0, 0, 0);
            u8* ref = 0;
            if (sp) {
                ref = (u8*)((CallStubs*)sp)->BgLoad(v, &BgLoading_sym);
                if (ref) {
                    BgSharedPtr* bp = (BgSharedPtr*)ref;
                    _InterlockedExchangeAdd((volatile long*)&bp->mRef.mCount, 1);
                }
            }
            BgSharedPtr* bp = (BgSharedPtr*)ref;
            void* got = ((void*(__thiscall*)(void*, void*, u32))VT(pi)[0xc])(pi, bp->mpData, v);
            if (got == (void*)(size_t_)v) {
                u8* ms = (u8*)operator_new(0x24, &DAT_013f6b3c, 0, 0, 0, 0);
                if (ms) {
                    ms = (u8*)((CallStubs*)ms)->MemStream(ref, v, &MemoryStream_sym);
                }
                ((CallStubs*)((u8*)t + 0x18))->StreamAssign(ms);
                result = true;
            } else {
                result = false;
            }
            volatile long* pc = (volatile long*)&bp->mRef.mCount;
            if (_InterlockedExchangeAdd(pc, -1) == 1) {
                _InterlockedExchange(pc, 1);
                if (bp) {
                    ((void(__thiscall*)(void*, int))(*(void***)&bp->mRef)[0])(&bp->mRef, 1);
                }
            }
            ((void(__thiscall*)(void*))VT(pi)[2])(pi);
        } else {
            u8* ctx = (u8*)operator_new(0x38, "UI/cSPUILayoutResource/TokenIOContext", 0, 0, 0, 0);
            if (ctx) {
                ((CallStubs*)ctx)->TokenCtor(0);
            } else ctx = 0;
            t->mpTokenCtx = ctx;
            u8 ok = FUN_00902d40(
                ((void*(__thiscall*)(void*, void*, u32, void*))VT(iface)[6])(iface, (u8*)t + 0x1c, 8, ctx),
                (u8*)t + 0x1c, 8, ctx);
            TokenIOContext_ClearStrings(t->mpTokenCtx);
            result = ok != 0;
            if (ok) result = FUN_0082e1d0(t);
        }
    }
    return result;
}

// @ 0x00810af0
void __thiscall RBTree::insertNode(void** out, RBNode* hint, u32* key, bool right)
{
    int created;
    if (!right && hint != (RBNode*)((u8*)this + 4) && *(u32*)((u8*)hint + 0x10) <= *key)
        created = 1;
    else
        created = 0;
    u8* n = (u8*)operator_new(0x24, &DAT_013f6b3c, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (n + 0x10) {
        *(u32*)(n + 0x10) = key[0];
        *(u32*)(n + 0x14) = key[1];
        *(u32*)(n + 0x18) = key[2];
        *(u32*)(n + 0x1c) = key[3];
        *(u32*)(n + 0x20) = key[4];
    }
    RBTreeInsert(n, hint, (u8*)this + 4, created);
    count++;
    if (out) *out = n;
}

// @ 0x00810d30
extern bool __stdcall FUN_00810d30(u32 msg, u8* p);
bool __stdcall FUN_00810d30(u32 msg, u8* p)
{
    if (msg != 0xf62ade) return true;
    u32 t = *(u32*)(p + 8);
    if (t == 0x050f4731 || t == 0x250fe9a2 || t == 0xefbda3ff) {
        FlushCache(6);
        u8* m = (u8*)operator_new(0x40, "UI/tSPMessage", 0, 0, 0, 0);
        u8* node = 0;
        if (m) {
            *(u32*)(m + 0x30) = 0;
            *(void**)m = &vtbl_UI_BehaviorMessage;
            *(u32*)(m + 4) = 0;
            *(u32*)(m + 0x38) = 0;
            *(void**)m = &vtbl_013eb844;
            ((void(__thiscall*)(void*))VT(m)[1])(m);
            node = m;
        }
        for (int i = 0; i < 0xc; ++i) *(u32*)(node + 8 + i * 4) = *(u32*)(p + 8 + i * 4);
        *(u32*)(node + 4) = *(u32*)(p + 4);
        *(u32*)(node + 0x38) = *(u32*)(p + 0x38);
        u8* sv = (u8*)EA_Messaging_GetServer();
        ((void(__thiscall*)(void*, u32, void*, int, int))VT(sv)[0x18 / 4])(sv, 0x065ff54a, node, 0, 0);
        ((void(__thiscall*)(void*))VT(node)[2])(node);
    }
    return true;
}

// @ 0x00810e30
void __thiscall PtrVec::insert(void** pos, void** val)
{
    if (mEnd != mCap) {
        void** vp = (void**)val;
        if (val >= pos && val < mEnd) vp = val + 1;
        if (mEnd) {
            void* last = mEnd[-1];
            *mEnd = last;
            if (last) ((VF0v)VT(last)[1])(last);
        }
        FUN_005c1dc0(pos, mEnd - 1, mEnd);
        void* v = *vp;
        void* old = *pos;
        if (v != old) {
            if (v) ((VF0v)VT(v)[1])(v);
            *pos = v;
            if (old) ((VF0v)VT(old)[2])(old);
        }
        mEnd++;
        return;
    }
    void** ob = mBegin;
    u32 n = (u32)(mEnd - mBegin);
    if (n == 0) n = 1; else n *= 2;
    void** nb = n ? (void**)operator_new(n * 4, &DAT_013f6b3c, 0, 0, &DAT_013ebb38, 0xd1) : 0;
    u32 off = (u32)((u8*)pos - (u8*)mBegin);
    u8* cp = (u8*)FUN_011e0744(nb, mBegin, off);
    void** np = (void**)(cp + off);
    if (np) {
        void* v = *val;
        *np = v;
        if (v) ((VF0v)VT(v)[1])(v);
    }
    u8* ne = (u8*)FUN_011e0744(np + 1, pos, (u32)((u8*)mEnd - (u8*)pos));
    ne += (u8*)mEnd - (u8*)pos;
    if (ob && ob != mInline) operator_delete__(ob);
    mEnd = (void**)ne;
    mBegin = nb;
    mCap = nb + n;
}

// @ 0x00810fd0
void* __thiscall cSPUILayerManagerLike::CreateObjects(u32 key)
{
    u8* obj = (u8*)operator_new(0x9c, "UI/LayoutObjects", 0, 0, 0, 0);
    u8* coll = 0;
    if (obj) {
        coll = (u8*)((CallStubs*)obj)->CollCtor();
        if (coll) ((VF0v)VT(coll)[1])(coll);
    }
    u8 ok = ((CallStubs*)coll)->CollInit((void*)(size_t_)key);
    if (!ok) {
        if (coll) ((VF0v)VT(coll)[2])(coll);
        return 0;
    }
    ReqKey x;
    x.mFlag = 0;
    x.mF = 0.0f;
    x.mpColl = coll;
    if (coll) ((VF0v)VT(coll)[1])(coll);
    MapKV y;
    y.mpColl = x.mpColl;
    y.mVal = *(InsertVal*)&x;
    ((CallStubs*)((u8*)this + 0x28))->KeyMap(&x, &y, key);
    if (coll) ((VF0v)VT(coll)[2])(coll);
    SlotMessageLite msg;
    msg.mMsgId = 0x22568e7;
    msg.mpVtbl = &vtbl_013eb90c;
    _InterlockedExchange((volatile long*)&msg.mRef, 0);
    msg.mpVtbl = &vtbl_013eb844;
    msg.mTail = 0;
    msg.mKind = 1;
    msg.mpColl = coll;
    u8* sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, u32, void*, int))VT(sv)[5])(sv, 0x22568e7, &msg, 0);
    SlotMessage_Destruct(&msg);
    if (coll) ((VF0v)VT(coll)[2])(coll);
    return coll;
}

// @ 0x00811110
void* __thiscall cSPUILayerManagerLike::Method11110(u32 a, u32 b)
{
    u8* self = (u8*)this;
    u32 k = a;
    void* node = 0;
    ((CallStubs*)(self + 0xc))->Find(&node, &k);
    if ((u8*)node != self + 0x10) {
        u8* e = (u8*)node + 0x14;
        if (e) return *(void**)(e + 8);
    }
    struct S2 { u32 m0, m1, m2, m3, m4; };
    S2 s2;
    s2.m0 = a;
    s2.m1 = a;
    s2.m2 = b;
    s2.m3 = 0;
    s2.m4 = 0;
    u32 masked = a;
    *(u8*)&masked = 0;
    ((CallStubs*)(self + 0xc))->KeyAdd(&node, &s2, masked);
    u8* n = (u8*)node;
    void* mgr = EA_UTFWin_GetManager();
    void* mgr2 = ((VF0)VT(mgr)[1])(mgr);
    void* win = SPUIHelpers_CreateWindow(mgr2);
    *(void**)(n + 0x1c) = win;
    u8* w = (u8*)win;
    u8* p1 = (u8*)((VF0)VT(w)[4])(w);
    u8* r1 = (u8*)((VF0)VT(p1)[0xe])(p1);
    f32 width = *(f32*)(r1 + 0xc) - *(f32*)(r1 + 4);
    u8* p2 = (u8*)((VF0)VT(w)[4])(w);
    u8* r2 = (u8*)((VF0)VT(p2)[0xe])(p2);
    f32 height = *(f32*)(r2 + 8) - *(f32*)r2;
    f32 box[4];
    box[0] = 0.0f;
    box[1] = 0.0f;
    box[2] = width;
    box[3] = height;
    ((void(__thiscall*)(void*, f32*))VT(w)[0x1b])(w, box);
    ((void(__thiscall*)(void*, u32))VT(w)[0x14])(w, a);
    ((void(__thiscall*)(void*, u32, u32))VT(w)[0x1f])(w, 1, 1);
    ((void(__thiscall*)(void*, u32, u32))VT(w)[0x1f])(w, 0x10, 1);
    ((void(__thiscall*)(void*, u32))VT(w)[0x2b])(w, 0);
    ((void(__thiscall*)(void*, int))VT(w)[0x17])(w, -1);
    return *(void**)(n + 0x1c);
}

// @ 0x00811260
PtrVec* __thiscall PtrVec::operator=(const PtrVec& rhs)
{
    if (&rhs == this) return this;
    void** rb = rhs.mBegin, ** re = rhs.mEnd;
    u32 n = (u32)(re - rb);
    if ((u32)(mCap - mBegin) < n) {
        void** nb = (void**)FUN_00810f80(n, rb, re);
        if (mBegin && *(int*)((u8*)mBegin - 4) != 0) operator_delete__(mBegin);
        mBegin = nb;
        mCap = nb + n;
        mEnd = nb + n;
        return this;
    }
    u32 cur = (u32)(mEnd - mBegin);
    if (cur < n) {
        FUN_011e0744(mBegin, rb, cur * 4);
        FUN_011e0744(mEnd, (void**)((u8*)rb + cur * 4), (u32)((u8*)re - ((u8*)rb + cur * 4)));
        mEnd = mBegin + n;
        return this;
    }
    FUN_011e0744(mBegin, rb, (u32)((u8*)re - (u8*)rb));
    mEnd = mBegin + n;
    return this;
}

// @ 0x00811330
bool __thiscall cSPUILayerManagerLike::Method11330(u32 a)
{
    (void)a;
    u8* self = (u8*)this;
    if (*(u32*)(self + 0x88) == 0) return false;
    u8* win = (u8*)((CallStubs*)self)->FindWindowByID(-1, 1);
    if (!win) {
        u8* it   = *(u8**)(self + 0x64);
        u8* vend = *(u8**)(self + 0x68);
        void* inlineBuf[64];
        LocalPtrVec v;
        v.mBegin = inlineBuf;
        v.mEnd = inlineBuf;
        v.mCap = inlineBuf + 64;
        while (it != vend) {
            u8* elem = *(u8**)it;
            it += 4;
            void* p = ((void*(__thiscall*)(void*, u32))VT(elem)[3])(elem, 0xeeee8218);
            if (p) {
                if (v.mEnd < v.mCap) *v.mEnd++ = p;
                else ((CallStubs*)&v)->VecPush(v.mEnd, &p);
            }
        }
        u32 n = (u32)(v.mEnd - v.mBegin);
        f32 minX = 0.0f, minY = 0.0f, maxX = 0.0f, maxY = 0.0f;
        u32 i = 0;
        if (n) {
            do {
                f32* r = (f32*)((VF0)VT(v.mBegin[i])[0xe])(v.mBegin[i]);
                f32 left = r[0];
                if (i == 0) {
                    minX = left; minY = r[1]; maxX = r[2]; maxY = r[3];
                } else {
                    if (left < minX) minX = left;
                    if (r[1] < minY) minY = r[1];
                    if (r[2] > maxX) maxX = r[2];
                    if (r[3] > maxY) maxY = r[3];
                }
                ++i;
            } while (i < n);
        }
        i = 0;
        if (n) {
            do {
                u8* e = (u8*)v.mBegin[i];
                f32* r = (f32*)((VF0)VT(e)[0xe])(e);
                ((void(__thiscall*)(void*, f32, f32))VT(e)[0x19])(e, r[1] - minY, r[0] - minX);
                ++i;
            } while (i < n);
        }
        if (v.mBegin && v.mBegin != inlineBuf) operator_delete__(v.mBegin);
    } else {
        u8* p = *(u8**)(self + 0x88);
        f32* r1 = (f32*)((VF0)VT(p)[0xe])(p);
        f32 w = r1[3] - r1[1];
        f32* r2 = (f32*)((VF0)VT(p)[0xe])(p);
        f32 h = r2[2] - r2[0];
        ((void(__thiscall*)(void*, f32, f32))VT(win)[0x1a])(win, h, w);
        ((void(__thiscall*)(void*, f32, f32))VT(win)[0x19])(win, 0.0f, 0.0f);
        ((void(__thiscall*)(void*, u32))VT(win)[0x2b])(win, 0);
        ((void(__thiscall*)(void*, u32, u32))VT(win)[0x1f])(win, 0x10, 1);
    }
    ((CallStubs*)self)->SetVisibility((u32)*(u8*)(self + 0x8c));
    return true;
}

// @ 0x008115a0
bool __thiscall cSPUILayerManagerLike::InitMessaging()
{
    u8* self = (u8*)this;
    g_164cf58 = 1;
    u8* sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, void*, u32))VT(sv)[8])(sv, self, 0x22568e7);
    sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, void*, u32))VT(sv)[8])(sv, self, 0xf62ade);
    FUN_006adc60(6, 0x40);
    FUN_006adc60(8, 0x20);
    for (int esi = 0xe4; esi > -0xc; esi -= 0xc)
        Method11110(*(u32*)(esi + 0x1544cc0), *(u32*)(esi + 0x1544cc4));
    u8* tree = self + 0x10;
    u8* root = *(u8**)(self + 0x18);
    u8* lb = tree;
    while (root) {
        if (*(u32*)(root + 0x10) < 0x614de4c) {
            root = *(u8**)root;
        } else {
            lb = root;
            root = *(u8**)(root + 4);
        }
    }
    if (lb == tree || *(u32*)(lb + 0x10) > 0x614de4c) lb = tree;
    if (lb != tree && *(void**)(lb + 0x1c)) {
        void* w = *(void**)(lb + 0x1c);
        ((void(__thiscall*)(void*, u32))VT(w)[0x2b])(w, 0xff000000);
    }
    tree = self + 0x10;
    root = *(u8**)(self + 0x18);
    lb = tree;
    while (root) {
        if (*(u32*)(root + 0x10) < 0x614de4c) {
            root = *(u8**)root;
        } else {
            lb = root;
            root = *(u8**)(root + 4);
        }
    }
    if (lb == tree || *(u32*)(lb + 0x10) > 0x614de4c) lb = tree;
    if (lb != tree) {
        u8* val = lb + 0x14;
        i32 next = (i32)(*(u32*)(val + 0xc) + 1);
        i32 lim = 0;
        i32 st = next > 0 ? next : lim;
        if (st >= 0) {
            if (st < 2) {
                void* w = *(void**)(val + 8);
                ((void(__thiscall*)(void*, u32, u32))VT(w)[0x1f])(w, 1, (u32)(st == 0));
            }
            *(u32*)(val + 0xc) = (u32)st;
        }
    }
    return true;
}

// @ 0x008116e0
bool __thiscall cSPUILayerManagerLike::ShutdownMessaging()
{
    u8* self = (u8*)this;
    u8* sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, void*, u32, u32))VT(sv)[0xb])(sv, self, 0xf62ade, 0xffffd8f1);
    sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, void*, u32, u32))VT(sv)[0xb])(sv, self, 0x22568e7, 0xffffd8f1);
    if (*(u32*)(self + 0x3c) != 0) {
        do {
            u8* node = *(u8**)(self + 0x30);
            void* ref = *(void**)(node + 0x10);
            if (ref) ((void(__thiscall*)(void*))VT(ref)[1])(ref);
            --*(u32*)(self + 0x3c);
            FUN_00921580(node);
            FUN_00921880(node, self + 0x2c);
            void* held = *(void**)(node + 0x10);
            if (held) ((void(__thiscall*)(void*))VT(held)[2])(held);
            operator_delete__(node);
            void* sub = (void*)((u8*)ref + 8);
            ((void(__thiscall*)(void*))VT(sub)[2])(sub);
            ((void(__thiscall*)(void*))VT(ref)[2])(ref);
        } while (*(u32*)(self + 0x3c) != 0);
    }
    struct TmpVt { void* mpVtbl; } tmp;
    tmp.mpVtbl = &vtbl_014181a8;
    void* err = FUN_008de1a0();
    ((void(__thiscall*)(void*, u32, void*))VT(err)[0x1c])(err, 0, &tmp);
    FUN_00957d30();
    void* root = *(void**)(self + 0x18);
    self += 0xc;
    ((CallStubs*)self)->Nuke(root);
    *(void**)(self + 4) = self + 4;
    *(void**)(self + 8) = self + 4;
    *(u32*)(self + 0xc) = 0;
    *(u8*)(self + 0x10) = 0;
    *(u32*)(self + 0x14) = 0;
    void* mgr = (u8*)EA_UTFWin_GetManager();
    void* m2 = ((VF0)VT(mgr)[1])(mgr);
    ((void(__thiscall*)(void*))VT(m2)[0x39])(m2);
    return true;
}
