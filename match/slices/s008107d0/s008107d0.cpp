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
static inline void** VT(void* o) { return *(void***)o; }

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
extern void  __cdecl FUN_00572620(int);                              // 0x572620
extern void  __cdecl FUN_0082e1d0(void*);                            // 0x82e1d0
extern u8    __cdecl FUN_00902d40(void*);                            // 0x902d40
extern void  __cdecl RBTreeInsert(void*, void*, void*, int);         // 0x9216a0
extern void  __cdecl SlotMessage_Destruct(void*);                    // 0x421cf0
extern void* __cdecl SPUIHelpers_CreateWindow(void*);                // 0x806370
extern void  __cdecl TokenIOContext_ClearStrings(void*);             // 0x902460
extern void  __cdecl FUN_00811110_c(void*, void*);                   // 0x811110
extern void  __cdecl FUN_00810c20(void*, void*, void*);              // 0x810c20
extern void  __cdecl FUN_00810b90(void*, void*, void*);              // 0x810b90

extern char vtbl_UI_BehaviorMessage, vtbl_013eb844, vtbl_Editor_cPropertyList,
            vtbl_AddRef_014181e8, vtbl_UI_cSPUILayoutResource, DAT_013f6b3c,
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
    RBNode  anchor;          // +0
    i32     count;           // +0x10
    void __thiscall insertNode(void** out, RBNode* hint, u32* key, bool right); // 0x810af0
};

// generic resource factory object
struct cSPUILayoutResourceFactory {
    void* __thiscall CreateResource(void* a, void* b, u32 type, void* d);      // 0x8107d0
    void* __thiscall Function8a0(void* a, void* b, u32 type, void* d);         // 0x8108a0
};

struct cSPUILayoutObjectCollection;
struct cSPUILayerManagerLike {
    void* __thiscall CreateObjects(u32 key);              // 0x810fd0
    void* __thiscall Method11110(u32 a, u32 b);           // 0x811110
    void* __thiscall Method11330(u32 a);                  // 0x811330
    bool  __thiscall InitMessaging();                     // 0x8115a0
    void  __thiscall ShutdownMessaging();                 // 0x8116e0
};

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
void* __thiscall cSPUILayoutResourceFactory::CreateResource(void* a, void* b, u32 type, void* d)
{
    if (type != 0x0510a95b) return 0;
    u8* obj = (u8*)operator_new(0x24, "App/SPUILayoutResource", 0, 0, 0, 0);
    u8* out = 0;
    if (obj) {
        *(void**)obj = &vtbl_Editor_cPropertyList;
        *(u32*)(obj + 4) = 0;
        *(u32*)(obj + 8) = 0;
        *(u32*)(obj + 0xc) = 0;
        *(u32*)(obj + 0x10) = 0;
        *(u32*)(obj + 0x14) = 0;
        *(void**)obj = &vtbl_AddRef_014181e8;
        *(u32*)(obj + 0x18) = 0;
        *(u32*)(obj + 0x1c) = 0;
        *(u32*)(obj + 0x20) = 0;
        ((void(__thiscall*)(void*))VT(obj)[0])(obj);
        out = obj;
    }
    u8* src = (u8*)((VF0)VT(b)[4])(b);
    void* dstRef = *(void**)src;
    void* s1 = *(void**)(src + 4);
    void* s2 = *(void**)(src + 8);
    *(void**)(out + 8) = dstRef;
    *(u32*)(out + 0xc) = 0x0510a95b;
    *(void**)(out + 0x10) = s2;
    u8 ok = ((VF3u)VT(a)[9])(a, b, out, 0x0510a95b);
    (void)s1; (void)d;
    if (ok) {
        *(void**)dstRef = out;
        ((void(__thiscall*)(void*))VT(out)[0])(out);
        ((VF0v)VT(out)[1])(out);
        return (void*)1;
    }
    ((VF0v)VT(out)[1])(out);
    return 0;
}

// @ 0x008108a0
void* __thiscall cSPUILayoutResourceFactory::Function8a0(void* a, void* b, u32 type, void* d)
{
    if (type != 0x0510a95b) return 0;
    u8* bb = (u8*)b;
    u8* old = *(u8**)(bb + 0x20);
    *(u32*)(bb + 0x1c) = 0;
    if (old) {
        FUN_00903120(old);
        operator_delete__(old);
        *(u32*)(bb + 0x20) = 0;
    }
    u8* k = (u8*)((VF0)VT(a)[4])(a);
    if (*(u32*)(k + 4) != 0x250fe9a2) {
        u8* tok = (u8*)operator_new(0x38, "UI/cSPUILayoutResource/TokenIOContext", 0, 0, 0, 0);
        if (tok) {
            ((void(__thiscall*)(void*, int))&FUN_009030b0_sym)(tok, 0);
        } else tok = 0;
        *(u8**)(bb + 0x20) = tok;
        void* r = ((void*(__thiscall*)(void*, unsigned int))VT(a)[0x18 / 4])(a, 8);
        u8 ok = FUN_00902d40(r);
        if (ok) FUN_0082e1d0(bb);
        TokenIOContext_ClearStrings(*(void**)(bb + 0x20));
        return (void*)(size_t)ok;
    }
    u8* pi = (u8*)((VF0)VT(a)[0x18 / 4])(a);
    if (pi) ((VF0v)VT(pi)[1])(pi);
    u32 v = ((u32(__thiscall*)(void*))VT(pi)[0x1c / 4])(pi);
    u8* sp = (u8*)ZoneNew(0x18, &DAT_013f6b3c, 0, 0, 0, 0);
    void* ref = 0;
    if (sp) {
        ((void(__thiscall*)(void*, u32))&BgLoading_sym)(sp, v);
        ref = sp;
        if (ref) ((volatile u32*)((u8*)ref + 8))[0] += 1;
    }
    void* got = ((void*(__thiscall*)(void*, void*, void*))VT(pi)[0x30 / 4])(pi, *(void**)((u8*)ref + 0x10), (void*)(size_t)v);
    if (got == (void*)(size_t)v) {
        u8* ms = (u8*)operator_new(0x24, "UI/UILayoutBinary/MemoryStream", 0, 0, 0, 0);
        if (ms) ((void(__thiscall*)(void*, u32, void*))&MemoryStream_sym)(ms, v, ref);
        FUN_00572620((int)ms);
        *(u32*)d = 1;
    } else {
        FUN_00572620(0);
    }
    ((void(__thiscall*)(void*))VT(pi)[2])(pi);
    return (void*)1;
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
extern int __stdcall FUN_00810d30(u32 msg, u8* p);
int __stdcall FUN_00810d30(u32 msg, u8* p)
{
    if (msg != 0xf62ade) return 1;
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
    return 1;
}

// @ 0x00810e30
void __thiscall PtrVec::insert(void** pos, void** val)
{
    if (mEnd != mCap) {
        if ((u8*)pos <= (u8*)val && (u8*)val < (u8*)mEnd) val++;
        if (mEnd) {
            void* last = mEnd[-1];
            *mEnd = last;
            if (last) ((VF0v)VT(last)[1])(last);
        }
        FUN_005c1dc0(pos, (u8*)mEnd - 4, mEnd);
        void* v = *val;
        void* old = *pos;
        if (v != old) {
            if (v) ((VF0v)VT(v)[1])(v);
            *pos = v;
            if (old) ((VF0v)VT(old)[2])(old);
        }
        mEnd++;
        return;
    }
    void**  ob = mBegin;
    u32 n = (u32)(mEnd - mBegin);
    if (n == 0) n = 1; else n *= 2;
    void** nb = n ? (void**)operator_new(n * 4, &DAT_013f6b3c, 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1) : 0;
    u32 off = (u32)((u8*)pos - (u8*)mBegin);
    void** np = (void**)((u8*)nb + off);
    if (np) {
        void* v = *val;
        *np = v;
        if (v) ((VF0v)VT(v)[1])(v);
    }
    FUN_005c1dc0(np + 1, pos, mEnd);
    if (ob && ob != mInline) operator_delete__(ob);
    mEnd = (void**)((u8*)np + ((u8*)mEnd - (u8*)pos) + 4);
    mBegin = nb;
    mCap = nb + n;
}

// @ 0x00810fd0
void* __thiscall cSPUILayerManagerLike::CreateObjects(u32 key)
{
    u8* obj = (u8*)operator_new(0x9c, "UI/LayoutObjects", 0, 0, 0, 0);
    u8* coll = 0;
    if (obj) {
        coll = (u8*)((void*(__thiscall*)(void*))&FUN_008100d0_sym)(obj);
        if (coll) ((VF0v)VT(coll)[1])(coll);
    }
    bool ok = (bool)(size_t)((bool(__thiscall*)(void*, int))&FUN_0080fd60_sym)(coll, (int)key);
    if (!ok) {
        if (coll) ((VF0v)VT(coll)[2])(coll);
        return 0;
    }
    u8 tmp[0x14];
    *(u8*)(tmp) = 0;
    *(f32*)(tmp + 4) = 0.0f;
    *(void**)(tmp + 8) = coll;
    if (coll) ((VF0v)VT(coll)[1])(coll);
    *(u8*)(tmp + 0x10) = 0;
    FUN_00810c20(tmp, tmp, (void*)(size_t)key);
    if (coll) ((VF0v)VT(coll)[2])(coll);
    return coll;
}

// @ 0x00811110
void* __thiscall cSPUILayerManagerLike::Method11110(u32 a, u32 b)
{
    u8* self = (u8*)this;
    u8* it = 0;
    // rbtree find(key) approximated by linear scan of the tree is not possible here;
    // this reproduces the post-find path with the found node unset.
    if (it == (u8*)this + 0x10) {
        u32 local = 0;
        u8 tmp[0x10];
        *(u8*)(tmp) = 0;
        *(u32*)(tmp + 4) = 0;
        *(u32*)(tmp + 8) = a;
        *(u32*)(tmp + 0xc) = b;
        FUN_00810b90(tmp, tmp, self);
        return 0;
    }
    return *(void**)((u8*)it + 0x14 + 8);
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
    if ((u32)(mEnd - mBegin) < n) {
        FUN_005c1dc0(mBegin, rb, (u8*)(mEnd - mBegin));
        FUN_005c1dc0(mEnd, (void**)((u8*)rb + ((u8*)mEnd - (u8*)mBegin)), (u8*)(re - rb));
        mEnd = mBegin + n;
        return this;
    }
    FUN_005c1dc0(mBegin, rb, (u8*)((u8*)re - (u8*)rb));
    mEnd = mBegin + n;
    return this;
}

// @ 0x00811330
void* __thiscall cSPUILayerManagerLike::Method11330(u32 a)
{
    (void)a;
    return 0;
}

// @ 0x008115a0
bool __thiscall cSPUILayerManagerLike::InitMessaging()
{
    u8* self = (u8*)this;
    g_164cf58 = 1;
    u8* sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, u32, void*, u32, void*))VT(sv)[0x20 / 4])(sv, 0x22568e7, self, 0, 0);
    sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, u32, void*, u32, void*))VT(sv)[0x20 / 4])(sv, 0xf62ade, self, 0, 0);
    FUN_006adc60(6, 0x40);
    FUN_006adc60(8, 0x20);
    for (int esi = 0xe4; esi > -0xc; esi -= 0xc)
        ((void(__thiscall*)(void*, void*, void*))&FUN_00811110_sym)(self,
            *(void**)(esi + 0x1544cc0), *(void**)(esi + 0x1544cc4));
    return true;
}

// @ 0x008116e0
void __thiscall cSPUILayerManagerLike::ShutdownMessaging()
{
    u8* self = (u8*)this;
    u8* sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, void*, u32, u32))VT(sv)[0x2c / 4])(sv, self, 0xf62ade, 0xffffd8f1);
    sv = (u8*)EA_Messaging_GetServer();
    ((void(__thiscall*)(void*, void*, u32, u32))VT(sv)[0x2c / 4])(sv, self, 0x22568e7, 0xffffd8f1);
}
