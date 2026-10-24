// src/game/Spui/SPUILayout.cpp -- migrated from slice(s) s008124a0, s009a9600, s008117f0, s008107d0, s0080f7c0 by tools/migrate/rewrite.py
// Object file: Spui/SPUILayout.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayoutObjectCollection.h"
#include "cSPUIResourcesKeyFilter.h"
#include "cSPUILayoutResourceFactory.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "cSPUILayeredObject.h"
#include "EA/UTFWinTools/SerCollection.h"
#include "EA/UTFWin/IWindow.h"
#include "EA/Stopwatch.h"
#include "cSPUILayoutCheat.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern void  __cdecl FlushCache(int);
extern void  __cdecl FUN_00903120(void*);         // 0x903120
extern void  __cdecl operator_delete__(void*);    // 0xf47380
extern char FUN_0080e6b0_sym, FUN_0080ee90_sym, FUN_0080f380_sym, FUN_0080d6d0_sym,
            FUN_0080d770_sym, SerShutdown_sym, SerDtor_sym, ResetWinCache_sym,
            vtbl_cConnectionDialog, vtbl_014181d8, vtbl_014181c0, vtbl_SimSummarizer,
            vtbl_AddRef_014181e8, vtbl_EditorResource, DAT_013f6b3c,
            CountedPtr_sym, FUN_00998f60_sym, FUN_00998f80_sym, FUN_0080f7c0_sym,
            SerCtor_sym;

// ---- items of slice s0080f7c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl SP_WindowManager();          // 0x67caa0
extern void* __cdecl FUN_00812da0(void*);         // 0x812da0
typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;
typedef void* (__thiscall *VF0)(void*);
typedef void  (__thiscall *VF0v)(void*);
typedef void  (__thiscall *VF1v)(void*, void*);
typedef void* (__thiscall *VF2)(void*, void*, void*);
typedef void  (__thiscall *VF2v)(void*, void*, void*);
static inline void** VT(void* o) { return *(void***)o; }
extern void* __cdecl operator_new(u32, void*, int, int, const char*, int); // 0xf473a0
extern u32   __cdecl eastl_RBTreeIncrement(void*);// 0x921580
extern u8  g_b164cf58;
struct WorldTree {
    void __thiscall find(void* sret, const u32* key);
};
struct WorldIter { void* node; };
struct cSPUILayoutObjectCollection_s0080_f7c0 {
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
struct cSPUILayoutObjectCollectionV8 {
    u8     pad0[4];
    void*  mService;        // +0x04 (collection+0xc)
    void*  mAutoUpdate;     // +0x08 (collection+0x10)
    void*  mKeyA;           // +0x0c (collection+0x14) key instance
    u8     pad10[4];        // +0x10 (collection+0x18) key type
    void*  mKeyB;           // +0x14 (collection+0x1c) key group
    u8     bSerFlags;       // +0x18 (collection+0x20)
    u8     pad19[0x80 - 0x19];
    void*  m80;             // +0x80 (collection+0x88)
    u8     pad84[0x85 - 0x84];
    u8     b85;             // +0x85 (collection+0x8d)
    u8     pad86[0x88 - 0x86];
    void*  p88;             // +0x88 (collection+0x90) reload layout owner
    void*  p8c;             // +0x8c (collection+0x94) reload callback
    void*  p90;             // +0x90 (collection+0x98) ctx

    void __thiscall Shutdown();  // 0x8101a0
    void __thiscall OnUnload();  // 0x810270
};
struct cSPUILayout_s0080_f7c0 {
    void** vtbl;            // +0
    i32    mRefCount;       // +4
    u8     pad8[0x14 - 8];
    cSPUILayoutObjectCollection_s0080_f7c0* mpCollection; // +0x14

    cSPUILayout_s0080_f7c0* __thiscall assign(cSPUILayout_s0080_f7c0* rhs);      // 0x810050
    bool __thiscall IsVisible();                           // 0x810070
    void __thiscall SetReloadCallback(void* cb, void* ctx); // 0x810090
    bool __thiscall SetVisibility(bool vis);               // 0x810590
    void* __thiscall FindWindowByID(i32 id, char r);       // 0x8105b0
};
struct cSPUILayoutManager_s0080_f7c0 {
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
struct cConnectionDialog {
    u32 f0, f4, f8, fc, f10, f14;
    void* __thiscall ctor();
    void* __thiscall ctor2(void* arg);
};
struct EastlNodeBuilder {
    void* __thiscall alloc(void* param);
};
struct SerStub {
    void __thiscall ctor();
    void __thiscall Shutdown();
    void __thiscall dtor();
    void __thiscall Set(void* a, int b);   // 0x998f60
    int  __thiscall Get(void* key);        // 0x998f80
};
extern void* __cdecl EapdDebug_8de1a0();          // 0x8de1a0
extern int   __cdecl FUN_0082e1d0(void*);         // 0x82e1d0
extern u32   __cdecl FUN_00902fc0(void*);         // 0x902fc0
extern void  __cdecl FUN_0093a610(void*, void*);  // 0x93a610
extern void* __cdecl operator_new(u32, void*, int, int, const char*, int); // 0xf473a0
extern u32   __cdecl eastl_RBTreeIncrement(void*);// 0x921580
extern void __cdecl SPUIHelpers_UpdateMouseFocus_(int);
// ---- items of slice s0080f7c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern void* __cdecl EapdDebug_8de1a0();          // 0x8de1a0
extern void* __cdecl operator_new(u32, void*, int, int, const char*, int); // 0xf473a0
extern u32   __cdecl eastl_RBTreeIncrement(void*);// 0x921580
extern void __cdecl SPUIHelpers_UpdateMouseFocus_(int);

// ---- items of slice s008107d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* __cdecl EA_Messaging_GetServer();                       // 0x883860
extern int   __cdecl FUN_006adc60(int, int);                         // 0x6adc60
extern void  __cdecl FUN_005c1dc0(void*, void*, void*);              // 0x5c1dc0
extern void  __cdecl FUN_00572620(int);                              // 0x572620
extern void  __cdecl RBTreeInsert(void*, void*, void*, int);         // 0x9216a0
extern void  __cdecl TokenIOContext_ClearStrings(void*);             // 0x902460
extern void  __cdecl FUN_00810c20(void*, void*, void*);              // 0x810c20
extern void  __cdecl FUN_00810b90(void*, void*, void*);              // 0x810b90
extern char vtbl_UI_BehaviorMessage, vtbl_013eb844, vtbl_Editor_cPropertyList,
            vtbl_AddRef_014181e8, vtbl_UI_cSPUILayoutResource, DAT_013f6b3c,
            FUN_009030b0_sym, BgLoading_sym, MemoryStream_sym,
            FUN_008100d0_sym, FUN_0080fd60_sym, FUN_00811110_sym;
typedef float          f32;
typedef u8    (__thiscall *VF3u)(void*, void*, void*, u32);
extern void* __cdecl ZoneNew(u32, void*, int, int, void*, int);      // 0x926020
extern int   __cdecl FUN_00903120_s0081_07d0(void*);                            // 0x903120
extern void* __cdecl FUN_00810f80(u32, void*, void*);                // 0x810f80
extern u8    __cdecl FUN_00902d40(void*);                            // 0x902d40
extern u8 g_164cf58;
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
struct RBNode { RBNode* left; RBNode* right; RBNode* parent; void* key; };
struct RBTree {
    RBNode  anchor;          // +0x00
    void*   mpHead;          // +0x10 (not touched by insertNode)
    i32     count;           // +0x14
    void __thiscall insertNode(void** out, RBNode* hint, u32* key, bool right); // 0x810af0
};
struct cSPUILayoutResourceFactory_s0081_07d0 {
    void* __thiscall CreateResource(void* a, void* b, u32 type, void* d);      // 0x8107d0
    void* __thiscall Function8a0(void* a, void* b, u32 type, void* d);         // 0x8108a0
};
struct cSPUILayerManagerLike {
    void* __thiscall CreateObjects(u32 key);              // 0x810fd0
    void* __thiscall Method11110(u32 a, u32 b);           // 0x811110
    void* __thiscall Method11330(u32 a);                  // 0x811330
    bool  __thiscall InitMessaging();                     // 0x8115a0
    void  __thiscall ShutdownMessaging();                 // 0x8116e0
};
extern bool __stdcall FUN_00810d30(u32 msg, u8* p);
extern void  __cdecl FUN_011e0744(void*, void*, u32);                // 0x11e0744 (memmove)
// ---- items of slice s008107d0 end

// ---- items of slice s008117f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void  __cdecl ResetChildWindowCache_();                     // 0x962be0
extern int   __cdecl eastl_Compare_(void*, void*, int);            // 0x5f7870
extern void* __cdecl eastl_RBTreeIncrement_(void*);                // 0x921580
extern void* __cdecl eastl_RBTreeDecrement_(void*);                // 0x9215c0
extern void  __cdecl eastl_RBTreeErase(void*, void*);              // 0x921880
extern void  __cdecl FUN_00812280_(void*, void*, void*, int);      // 0x812280
extern void  __cdecl FUN_005c1dc0_(void*, void*, void*);           // 0x5c1dc0
extern char vtbl_014182a4, vtbl_014182a0, vtbl_SimCreatureAbility, vtbl_SkinnerPaintSystem,
            vtbl_UI_cConnectionDialog, vtbl_SimContentValidationSummarizer,
            FUN_008117f0_sym, FUN_00810fd0_sym, FUN_00811330_sym, FUN_00811c20_sym,
            FUN_00810620_sym, FUN_810a90_sym;
extern void* g_spLayoutManager;                                    // 0x164cf5c
extern void  __cdecl SPKeyFromName(void*, u32, u32, u32);          // 0x68d840
struct PtrVec_s0081_17f0 {
    void** mBegin;   // +0
    void** mEnd;     // +4
    void** mCap;     // +8
    void*  mAlloc;   // +0xc
    void*  mInline;  // +0x10
    void __thiscall swap(PtrVec_s0081_17f0& rhs);                 // 0x811a20
};
struct cSPUILayoutObjectCollection_s0081_17f0;
struct CollStub { u8 pad[0x100]; void __thiscall m11330(); };
struct cSPUILayout_s0081_17f0 {
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
struct cSPUILayoutObjectCollection_s0081_17f0 {
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
struct cSPUILayoutManager_s0081_17f0 {
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
// ---- items of slice s008117f0 end

// ---- items of slice s009a9600 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void FUN_f47380(void*);              // operator delete(void*) cdecl
struct S9a9600 { void f(void*); };
// ---- items of slice s009a9600 end

// ---- items of slice s008124a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*   SP_CheatManager();
extern "C" void EA_ArgScript_Output(char* parser, const char* fmt, ...);
namespace EA {
namespace ArgScript {
struct cArguments_s0081_24a0 {
    void  MainArguments(int);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    int   NumArguments();  // 0x00837f30 (EA::ArgScript::cArguments::NumArguments)
    char* OptionArguments(const char* name, int a, int b, int c);  // 0x00838130 (EA::ArgScript::cArguments::OptionArguments)
    char* OptionArguments(const char* name, int a);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
    bool  HasFlag(const char* name);  // 0x008380b0 (EA::ArgScript::cArguments::HasFlag)
};
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s0081_24a0 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual ~cCommandBase_s0081_24a0();
    char* mParser;      // +4
    int   mRefCount;    // +8
    void* mState;       // +0xc
};
}
}
using EA::ArgScript::cArguments_s0081_24a0;
using EA::ArgScript::cCommandBase_s0081_24a0;
struct LayoutMap {
    char pad0[0x0c];
    void* mRoot;         // +0xc
    char pad1[0x1c - 0x10];
    void DoNukeSubtree(void* root);
    ~LayoutMap();
};
inline LayoutMap::~LayoutMap() { DoNukeSubtree(mRoot); }
struct cSPUILayoutCheat_s0081_24a0 : cCommandBase_s0081_24a0 {
    LayoutMap mLayouts;                 // +0x10
    cSPUILayoutCheat_s0081_24a0();
    void Execute(cArguments_s0081_24a0* args);  // 0x008124a0 (cSPUILayoutCheat::Execute)
};
cSPUILayoutCheat_s0081_24a0::cSPUILayoutCheat_s0081_24a0() {
    mParser = 0;
    mRefCount = 0;
    mState = 0;
    *(void**)((char*)this + 0x14) = (char*)this + 0x14;
    *(void**)((char*)this + 0x18) = (char*)this + 0x14;
    *(int*)((char*)this + 0x1c) = 0;
    *(uint8_t*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x24) = 0;
}
// ---- items of slice s008124a0 end

// @ 0x0080fd60
void __thiscall cSPUILayoutObjectCollection_s0080_f7c0::Init(void* key)
{
    u32 k0 = ((u32*)key)[0], k1 = ((u32*)key)[1], k2 = ((u32*)key)[2];
    if (g_b164cf58) k2 = (k2 & 0xffff42ff) | 0x4200;
    void* wm = SP_WindowManager();
    void* iface = ((void*(__thiscall*)(void*))VT(wm)[1])(wm);
    void* obj = iface ? (void*)((u8*)iface - 4) : 0;
    void* a = FUN_00812da0(obj);
    ((SerStub*)((u8*)this + 8))->Set(a, 1);
    b8d = 0;
    u32 k[3] = { k0, k1, k2 };
    ((SerStub*)((u8*)this + 8))->Get(k);
}

// @ 0x0080fe10
void __thiscall cSPUILayoutObjectCollection_s0080_f7c0::Subscribe(int b)
{
    if (!(mSerFlags & 1)) return;
    void* svc = *(void**)((u8*)this + 0xc);
    void* au = ((void*(__thiscall*)(void*, unsigned int))VT(svc)[0x10 / 4])(svc, 0x2fbf2058);
    mAutoUpdate = au;
    if (!au) return;
    u32 a = *(u32*)((u8*)this + 0x14);
    (void)a;
    struct { u32 x, y, z; } k = { 0xefbda3ff, 0x050f4731, 0x250fe9a2 };
    if (b)
        ((VF2v)VT(au)[0x10 / 4])(au, &k, (void*)((u8*)this + 8));
    else
        ((VF2v)VT(au)[0x14 / 4])(au, &k, (void*)((u8*)this + 8));
}

// @ 0x0080feb0
void __thiscall cSPUILayoutObjectCollection_s0080_f7c0::ResourceChanged()
{
    if (*(u32*)((u8*)this + 0x8c) != 0) {
        FlushCache(6);
        ((void(__thiscall*)(void*))VT(this)[0x14 / 4])(this);
    }
}

// @ 0x0080fef0
bool cSPUIResourcesKeyFilter::IsKeyIncluded(EA::ResourceMan::Key const & key)
{
    return key.mType == 0xef7d16e1 || key.mType == 0x0510a95b;
}

// @ 0x0080ff50
bool cSPUILayoutResourceFactory::Init()
{
    u32 types[3] = { 0x250fe9a2, 0x050f4731, 0xefbda3ff };
    void* o = EapdDebug_8de1a0();
    ((void(__thiscall*)(void*, unsigned int, u32*, int))VT(o)[0x24 / 4])(o, 0x0510a95b, types, 3);
    return true;
}

// @ 0x0080ffa0
unsigned int cSPUILayoutResourceFactory::GetSupportedTypes(unsigned int * out, unsigned int count)
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
bool cSPUILayoutResourceFactory::CanConvert(unsigned int from, unsigned int to) const
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
cSPUILayout_s0080_f7c0* __thiscall cSPUILayout_s0080_f7c0::assign(cSPUILayout_s0080_f7c0* rhs)
{
    if (mpCollection) {
        cSPUILayoutObjectCollection_s0080_f7c0* c = mpCollection;
        mpCollection = 0;
        ((VF0v)VT(c)[2])(c);
    }
    (void)rhs;
    return this;
}

// @ 0x00810070
bool cSPUILayout::IsVisible() const
{
    cSPUILayoutObjectCollection* c = mpObjectCollection.mpObject;
    if (c) return *(bool*)((u8*)c + 0x8c);
    return false;
}

// @ 0x00810090
void cSPUILayout::SetReloadCallback(void (__cdecl *cb)(void *, cSPUILayout *, bool), void * ctx)
{
    if (mpObjectCollection.mpObject) {
        *(void**)((u8*)mpObjectCollection.mpObject + 0x90) = this;
        *(void**)((u8*)mpObjectCollection.mpObject + 0x94) = cb;
        *(void**)((u8*)mpObjectCollection.mpObject + 0x98) = ctx;
    }
}

// @ 0x008100d0
void* __thiscall cSPUILayoutObjectCollection_s0080_f7c0::ctor()
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

// @ 0x00810140
void cSPUILayoutObjectCollection::detach_parent()
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
    cSPUILayoutObjectCollection_s0080_f7c0* coll = (cSPUILayoutObjectCollection_s0080_f7c0*)((u8*)this - 8);
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
void* __thiscall cSPUILayoutObjectCollection_s0080_f7c0::FindWindowByID(i32 id, char recurse)
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
    u8* self = (u8*)this;
    cSPUILayoutObjectCollection_s0080_f7c0* coll = (cSPUILayoutObjectCollection_s0080_f7c0*)(self - 8);
    if (bSerFlags & 1) {
        void* svc = mService;
        void* au = ((void*(__thiscall*)(void*, unsigned int))VT(svc)[0x10 / 4])(svc, 0x2fbf2058);
        mAutoUpdate = au;
        if (au) {
            struct { u32 x, y, z; } k0 = { *(u32*)&mKeyA, 0xefbda3ff, *(u32*)&mKeyB };
            struct { u32 x, y, z; } k1 = { *(u32*)&mKeyA, 0x050f4731, *(u32*)&mKeyB };
            ((VF2v)VT(au)[0x14 / 4])(au, &k0, (void*)this);
            au = mAutoUpdate;
            ((VF2v)VT(au)[0x14 / 4])(au, &k1, (void*)this);
        }
    }
    ResetChildWindowCache_();
    if (p8c) {
        void* fn = p8c;
        void* a1 = p90;
        void* a2 = p88;
        ((void(__cdecl*)(void*, void*, int))fn)(a1, a2, 0);
    }
    coll->detach_parent();
}

// @ 0x00810310
bool cSPUILayoutObjectCollection::SetVisibility(bool vis)
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
        if (g == *(void**)(s + 0x88) || g == 0)
            ((void(__thiscall*)(void*, int, bool))VT(q)[0x7c / 4])(q, 1, vis);
    }
    SPUIHelpers_UpdateMouseFocus_(1);
    s[0x8c] = (u8)vis;
    return true;
}

// @ 0x008103a0
void __thiscall cSPUILayoutManager_s0080_f7c0::SetNodeVisibility(void* node, char delta)
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
    s[0] = (u32)&vtbl_AddRef_014181e8;
    void* p = (void*)s[6];
    if (p) { s[6] = 0; ((VF0v)VT(p)[2])(p); }
    void* q = (void*)s[8];
    s[7] = 0;
    if (q) { FUN_00903120(q); operator_delete__(q); s[8] = 0; }
    p = (void*)s[6];
    if (p) ((VF0v)VT(p)[2])(p);
    s[0] = (u32)&vtbl_EditorResource;
}

// @ 0x00810460
bool cSPUILayoutResourceFactory::WriteResource(EA::ResourceMan::Resource * a, EA::ResourceMan::Record * b, void * type, unsigned int d)
{
    (void)type;
    int type_v = (int)d;
    u8 bl = 0;
    if (type_v == 0x250fe9a2) {
        if (!a) return (void*)(size_t)bl;
        void* x = ((void*(__thiscall*)(void*, unsigned int))VT(a)[0xc / 4])(a, 0x05adf5fb);
        if (!x) return (void*)(size_t)bl;
        if (*(int*)((u8*)x + 0x1c)) bl = (u8)(size_t)FUN_0082e1d0(x);
        void* y = *(void**)((u8*)x + 0x18);
        if (!y) return (void*)(size_t)bl;
        ((void(__thiscall*)(void*, int, int))VT(y)[0x28 / 4])(y, 0, 0);
        void* z = *(void**)((u8*)x + 0x18);
        u32 w = ((u32(__thiscall*)(void*, int))VT(b)[0x18 / 4])(b, -1);
        FUN_0093a610(z, (void*)(size_t)w);
        return (void*)1;
    } else if (type_v == 0x050f4731) {
        if (!a) return (void*)(size_t)bl;
        void* pp = *(void**)((u8*)a + 0x1c);
        if (!pp) return (void*)(size_t)bl;
        void* qq = *(void**)((u8*)a + 0x20);
        u32 w = ((u32(__thiscall*)(void*, void*, int, void*))VT(b)[0x18 / 4])(b, pp, 1, qq);
        bl = (u8)(size_t)FUN_00902fc0((void*)(size_t)w);
    }
    return (void*)(size_t)bl;
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
bool cSPUILayout::SetVisibility(bool vis)
{
    if (mpObjectCollection.mpObject) return mpObjectCollection.mpObject->SetVisibility(vis);
    return false;
}

// @ 0x008105b0
EA::UTFWin::IWindow * cSPUILayout::FindWindowByID(unsigned int id, bool r) const
{
    if (mpObjectCollection.mpObject) return mpObjectCollection.mpObject->FindWindowByID(id, r);
    return 0;
}

// @ 0x008105d0
void* __thiscall cSPUILayoutObjectCollection_s0080_f7c0::VectorDtor(u8 flag)
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
void* __thiscall cSPUILayoutManager_s0080_f7c0::GetWorldMainWindow(u32 id)
{
    WorldIter it;
    it.node = this;
    mTree.find(&it, &id);
    if (it.node == (void*)((u8*)this + 0x10)) return 0;
    if ((u8*)it.node + 0x14 == 0) return 0;
    return *(void**)((u8*)it.node + 0x1c);
}

// @ 0x00810660
void __thiscall cSPUILayoutManager_s0080_f7c0::Method10660(u32 id, bool vis)
{
    WorldIter it;
    it.node = this;
    mTree.find(&it, &id);
    if (it.node != (void*)((u8*)this + 0x10) && (u8*)it.node + 0x14 != 0)
        SetNodeVisibility((u8*)it.node + 0x14, (char)vis);
}

// @ 0x008106a0
void __thiscall cSPUILayoutManager_s0080_f7c0::SetAllWorldsVisibility(bool vis)
{
    u8* s = (u8*)this;
    void* anchor = (void*)(s + 0x10);
    void* node = *(void**)(s + 0x14);
    if (node == anchor) return;
    int delta = vis ? -1 : 1;
    do {
        u8* cur = (u8*)node;
        node = (void*)(size_t)eastl_RBTreeIncrement(node);
        SetNodeVisibility(cur + 0x20, (char)delta);
    } while (node != anchor);
}

// @ 0x00810730
bool __thiscall cSPUILayoutManager_s0080_f7c0::AnyWorldHidden()
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
bool __thiscall cSPUILayoutManager_s0080_f7c0::IsWorldVisible(u32 id)
{
    WorldIter it;
    it.node = this;
    mTree.find(&it, &id);
    if (it.node == (void*)((u8*)this + 0x10)) return false;
    if ((u8*)it.node + 0x14 == 0) return false;
    return *(int*)((u8*)it.node + 0x14 + 0xc) == 0;
}

// @ 0x008107d0
void* __thiscall cSPUILayoutResourceFactory_s0081_07d0::CreateResource(void* a, void* b, u32 type, void* d)
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
void* __thiscall cSPUILayoutResourceFactory_s0081_07d0::Function8a0(void* a, void* b, u32 type, void* d)
{
    if (type != 0x0510a95b) return 0;
    u8* bb = (u8*)b;
    u8* old = *(u8**)(bb + 0x20);
    *(u32*)(bb + 0x1c) = 0;
    if (old) {
        FUN_00903120_s0081_07d0(old);
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

// @ 0x008117f0
bool cSPUILayoutManager::CloseLayout(cSPUILayoutObjectCollection * coll, bool param)
{
    // 554-byte body not reconstructed
    (void)coll; (void)param;
    return 0;
}

// @ 0x00811a20
void __thiscall PtrVec_s0081_17f0::swap(PtrVec_s0081_17f0& rhs)
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
    PtrVec_s0081_17f0 tmp;
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
void __thiscall cSPUILayout_s0081_17f0::Shutdown(u32 param_2)
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
        ((cSPUILayoutManager_s0081_17f0*)g_spLayoutManager)->CloseLayout(c, param_2);
    ((VF0v)VT(c)[2])(c);
}

// @ 0x00811b30
void cSPUILayoutObjectCollection::attach_parent()
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
void cSPUILayoutObjectCollection::OnLoad()
{
    u8* self = (u8*)static_cast<EA::UTFWinTools::SerCollection *>(this);
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
bool cSPUILayoutObjectCollection::Reload()
{
    return 0;   // 768-byte body not reconstructed
}

// @ 0x00811f20
void* __thiscall cSPUILayoutManager_s0081_17f0::ctor()
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
void* __thiscall cSPUILayoutManager_s0081_17f0::scalarDtor(u8 flag)
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
void __thiscall cSPUILayout_s0081_17f0::dtor()
{
    cSPUILayout_s0081_17f0* p = this;
    void* c = p->mpCollection;
    *(void**)p = &vtbl_UI_cConnectionDialog;
    if (c) p->Shutdown(1);
    c = p->mpCollection;
    if (c) ((VF0v)VT(c)[2])(c);
    *(void**)p = &vtbl_SimContentValidationSummarizer;
}

// @ 0x00812010
bool cSPUILayoutObjectCollection::SetParentWin(EA::UTFWin::IWindow * p, bool b, unsigned int c)
{
    u8* s = (u8*)this;
    if (!p && b) {
        p = (EA::UTFWin::IWindow *)((cSPUILayoutManager*)g_spLayoutManager)->GetWorldMainWindow(c);
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
void* __thiscall cSPUILayout_s0081_17f0::scalarDtor(u8 flag)
{
    cSPUILayout_s0081_17f0* p = this;
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
u8 __thiscall cSPUILayout_s0081_17f0::InitB(u32* key, u32 b, u32 c)
{
    ResetChildWindowCache_();
    void* coll = ((cSPUILayoutManager_s0081_17f0*)g_spLayoutManager)->CreateLayoutObjects((u32)key);
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
        return ((cSPUILayoutObjectCollection_s0081_17f0*)cur)->SetParentWin(0, 1, b);
    return 1;
}

// @ 0x00812160
u8 __thiscall cSPUILayout_s0081_17f0::InitA(void* name, u32 b, u32 c, u32 d)
{
    u32 k[3] = { 0, 0, 0 };
    SPKeyFromName(k, (u32)name, 0x0510a95b, b);
    return InitB(k, c, d);
}

// @ 0x008121b0
bool cSPUILayout::SetParentWin(EA::UTFWin::IWindow * p, bool b, unsigned int c)
{
    if (mpObjectCollection.mpObject)
        return ((cSPUILayoutObjectCollection*)mpObjectCollection.mpObject)->SetParentWin(p, b, c);

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

// @ 0x008124a0
void cSPUILayoutCheat_s0081_24a0::Execute(cArguments_s0081_24a0* args)
{
    args->MainArguments(0);
    int n = args->NumArguments();
    if (n < 2) {
        EA_ArgScript_Output(mParser, "List of loaded UI layouts:\n");
        return;
    }
    char* load = args->OptionArguments("load", 1, 3, 0);
    if (load) {
        return;
    }
    char* unload = args->OptionArguments("unload", 1);
    if (unload) {
        return;
    }
    if (args->HasFlag("textures")) {
        SP_CheatManager();
    }
}

// @ 0x009a9600
void S9a9600::f(void* node_)
{
  char* node = (char*)node_;
  while (node) {
    ((S9a9600*)this)->f(*(void**)node);
    char* next = *(char**)(node + 4);
    FUN_f47380(node);
    node = next;
  }
}
