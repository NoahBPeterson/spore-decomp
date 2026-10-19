// src/game/SPEditors/SPUIFeedList.cpp -- migrated from slice(s) s00662d70, s00661d10 by tools/migrate/rewrite.py
// Object file: SPEditors/SPUIFeedList.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "SP/cSPUIFeedFilter.h"
#include "EA/Messaging/IHandler.h"
#include "SP/cSPUIFeedList.h"
#include <intrin.h>

// ---- items of slice s00661d10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IWindow {
    virtual void      s00(); virtual int Release();
    virtual void      s02(); virtual IWindow* FindWindow(uint32_t id);
    virtual IWindow*  GetSomething(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void      s08(); virtual void s09(); virtual uint32_t GetFlags(); virtual void s11();
    virtual void      s12(); virtual float* GetArea(); virtual void s14(); virtual void s15();
    virtual void      s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void      s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void      s24(); virtual void SetLocation(float, float); virtual void s26();
    virtual void      s27(); virtual void s28(); virtual void s29(); virtual void s30();
    virtual void      SetFlag(int, bool); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void      s35(); virtual void s36(); virtual void s37(); virtual void s38();
    virtual void      s39(); virtual void s40(); virtual void s41(); virtual void s42();
    virtual void      s43(); virtual void s44(); virtual void s45(); virtual void s46();
    virtual void      s47(); virtual void s48(); virtual void s49(); virtual void s50();
    virtual void      s51(); virtual void s52(); virtual void s53(); virtual void s54();
    virtual void      s55(); virtual void s56(IWindow*); virtual void s57(); virtual void s58();
    virtual void      s59(); virtual IWindow* FindWindowByID(uint32_t id, bool recurse);
    virtual void      s61(); virtual void s62(); virtual void s63(); virtual void s64();
    virtual void      SetReloadCallback(void*); virtual void AttachProc(void*);
};
struct cSPUILayout_s0066_1d10 {
    virtual void s0(); virtual void s1(); virtual int Release();
    void Shutdown(bool);                                   // 0x00811ad0
    IWindow* FindWindowByID(uint32_t, bool);               // 0x008105b0
    void Init(const uint32_t* area, int a, uint32_t key);  // 0x008120d0
    void SetParentWin(void* win, int a, uint32_t key);     // 0x008121b0
    void SetReloadCallback(void* fn, void* self);          // 0x00810090
    cSPUILayout_s0066_1d10* Construct();                              // 0x00810000
    char pad[0x18 - 4];
};
struct ObjX { float* FUN_006665e0(void* out); float FUN_00c37480(); };
void __cdecl EA_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0
void  __cdecl SPUIHelpers_UpdateMouseFocus(int b);                                       // 0x00804f50
struct ElemA { int Method(void* arg); };   // 0x00664640
struct ElemB { int Method(void* arg); };   // 0x00664680
struct ElemC { void Method(); };           // 0x00665870
struct ElemD { void Method(); };           // 0x00664440
struct ElemE { void Expand(void* arg); };  // 0x00664480
struct Obj50 { virtual int AddRef(); virtual int Release(); void SetActive(bool); };  // 0x006673a0
struct Obj34 { char pad[0x20]; void* m20; };
struct ObjM20 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual int  Slot40();                       // +0x40
};
struct ObjOther { char pad[0x2c]; float m2c; float GetBoundingRadius(); };  // 0x00ad2810
struct FeedTreeNode {
    char pad00[0x14];
    IWindow* mWin;     // +0x14
    bool b18;          // +0x18
    bool b19;          // +0x19
};
struct FeedList {
    char      pad00[0x10];
    bool      m10;                 // +0x10
    bool      m11;                 // +0x11
    char      pad12;
    bool      m13;                 // +0x13
    int       m14;                 // +0x14
    int       m18;                 // +0x18
    float     m1c;                 // +0x1c
    cSPUILayout_s0066_1d10* mLayout20;        // +0x20
    IWindow*  m24;                 // +0x24
    IWindow*  m28;                 // +0x28
    char      pad2c[8];
    Obj34*    m34;                 // +0x34
    ElemA**   m38;                 // +0x38 (vector begin)
    ElemA**   m3c;                 // +0x3c (vector end)
    char      pad40[0x10];
    Obj50*    m50;                 // +0x50
    void*     m54;                 // +0x54
    uint32_t  m58, m5c, m60;       // +0x58
    union { uint32_t m64; cSPUILayout_s0066_1d10* mLayout64; };  // +0x64
    IWindow*  m68;                 // +0x68
    IWindow*  m6c;                 // +0x6c
    IWindow*  m70;                 // +0x70
    IWindow*  m74;                 // +0x74
    IWindow*  m78;                 // +0x78
    char      pad7c[0x14];
    float     m90, m94, m98;       // +0x90
    char      pad9c[4];
    FeedTreeNode* mEnd;            // +0xa0
    FeedTreeNode* mBegin;          // +0xa4
    char      padA8[0x10];
    char      mHash[0x20];         // +0xb8 hashtable<Key, cSPUILayout*>
    int       md8, mdc;            // +0xd8 depth

    // defined in this slice
    void  FUN_006624d0(int param);
    void  FUN_00662540();
    void  FUN_006625f0(int* param2, void* param3);
    void  FUN_00662750(int param2, int param3, char param4);
    bool  FUN_006627d0(void* a, int* msg);
    void  FUN_006628d0();
    void  FUN_00662920(bool v);
    int   FUN_00662960(void* arg);
    int   FUN_006629a0(void* arg);
    void  FUN_006629e0();
    void* FUN_00662a20(uint32_t idx);
    void* FUN_00662a40(int id);
    void  FUN_00662a90(void* arg);
    void  FUN_00662ad0();
    void  FUN_00662b40(void* obj);
    void  FUN_00662c10(void* w);
    void  FUN_00662c70(void* obj);

    // external callees (ecx = this)
    void  CreateFilterButtons(int param, int a, int b, int* out);  // 0x00661d10
    void  DoMessage();                                             // 0x0065fd30
    void  GetSupportedFilterTypes(int param);                      // 0x006600c0
    bool  FUN_00661a10(int param);                                 // 0x00661a10
    bool  FUN_00661c00(int param, int b);                          // 0x00661c00
    bool  FUN_00661b10(int param);                                 // 0x00661b10
};
// ---- items of slice s00661d10 end

// ---- items of slice s00662d70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* SP_AssetBrowser(); // 0x00401030
extern "C" float GetPropertyT_f(int obj, int key, float def);   // 0x00401030 (equiv t3)
extern "C" void  SPUIHelpers_UpdateScrollFrameVertical(void* w);
extern "C" int   cTribeTool_GetTutorialToolPrice(int obj, int key, int def); // 0x004e1c30
extern "C" void* SP_PropertyManager();
extern int gVtA;   // 0x013eb384 (equiv t3)
extern int gVtB;   // 0x013ec458 (equiv t2)
extern int gVtC;   // 0x0140016c (equiv t2)
extern int gVtD;   // 0x0140015c (equiv t2)
extern int gVtE;   // 0x0140014c (equiv t2)
extern "C" void  FUN_00662b40(void* p);
extern "C" void  FUN_00662c70(void* p);
extern "C" void* FUN_00662c10(void* v);
extern "C" void* FUN_006629a0(int v);
extern "C" void* FUN_00662960(int v);
extern "C" void  FUN_006629e0(void* p);
typedef void(__thiscall* FnP)(void*);
static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }
struct cSPUIFeedList {
    void FUN_00663350(int param);
    char  vt[0xc];                     // 0x00
    bool  mIsVisible;                  // 0x10
    bool  mWheel;                      // 0x11
    bool  m12;                         // 0x12
    bool  m13;                         // 0x13
    float mTarget;                     // 0x14
    float mActual;                     // 0x18
    float mMax;                        // 0x1c
    void* mpLayout;                    // 0x20
    void* mpWinParent;                 // 0x24
    void* mpWinRoot;                   // 0x28
    void* mpWinList;                   // 0x2c
    void* mpWinScrollRoot;             // 0x30
    void* mpWinScrollClientArea;       // 0x34
    void* mCatBegin;                   // 0x38
    void* mCatEnd;                     // 0x3c
    void* mCatCap;                     // 0x40
    void* m44;                         // 0x44
    char  pad48[4];                    // 0x48
    void* mpSelectedFeed;              // 0x4c
    void* mpServer;                    // 0x50
    void* mpHandler;                   // 0x54
    void* mpIdArray;                   // 0x58
    int   mnIdArrayCount;              // 0x5c
    int   mnPriority;                  // 0x60
    void* mpConfig;                    // 0x64

    void* Ctor();
    void  Dtor();
    void  ShutdownCategories();
};
// ---- items of slice s00662d70 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void FUN_006634d0(char* p);  // 0x006634d0 (stays in the slice: not this object's)

// @ 0x006628d0
void FeedList::FUN_006628d0()
{
    if (mLayout20) {
        mLayout20->Shutdown(true);
        cSPUILayout_s0066_1d10* p = mLayout20;
        if (p) { mLayout20 = 0; p->Release(); }
    }
    if (m54) {
        void* h = m54;
        uint32_t a = m58, b = m5c, c = m60, d = m64;
        m54 = 0;
        EA_RemoveHandler(h, a, b, c, d);
    }
}

// @ 0x00662920
void FeedList::FUN_00662920(bool v)
{
    m10 = v;
    if (m24) m24->SetFlag(1, v);
    if (m28) m28->SetFlag(1, v);
}

// @ 0x00662960
int FeedList::FUN_00662960(void* arg)
{
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        int r = ((ElemA*)m38[i])->Method(arg);
        if (r) return r;
    }
    return 0;
}

// @ 0x006629a0
int FeedList::FUN_006629a0(void* arg)
{
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        int r = ((ElemB*)m38[i])->Method(arg);
        if (r) return r;
    }
    return 0;
}

// @ 0x006629e0
void FeedList::FUN_006629e0()
{
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        ((ElemC*)m38[i])->Method();
    }
}

// @ 0x00662a20
void* FeedList::FUN_00662a20(uint32_t idx)
{
    uint32_t i = idx;
    void* result = 0;
    if (i < (uint32_t)(((int)m3c - (int)m38) >> 2))
        result = m38[i];
    return result;
}

// @ 0x00662a40
void* FeedList::FUN_00662a40(int id)
{
    for (uint32_t i = 0; i < (uint32_t)(((int)m3c - (int)m38) >> 2); ++i)
        if (*(int*)((char*)m38[i] + 0xb4) == id) return m38[i];
    return 0;
}

// @ 0x00662a90
void FeedList::FUN_00662a90(void* arg)
{
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        ((ElemE*)m38[i])->Expand(arg);
    }
}

// @ 0x00662ad0
void FeedList::FUN_00662ad0()
{
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        ((ElemD*)m38[i])->Method();
    }
}

// @ 0x00662b40
void FeedList::FUN_00662b40(void* objp)
{
    if (!objp) return;
    ObjOther* obj = (ObjOther*)objp;
    float r = obj->m2c;
    float br = obj->GetBoundingRadius();
    float sum = r + br;
    int h = ((ObjM20*)m34->m20)->Slot40();
    float fh = (float)h;
    float v14 = *(float*)&m14;
    if (v14 > r) {
        *(float*)&m14 = r;
    } else if (sum > v14 + fh) {
        *(float*)&m14 = sum - fh;
    }
    float v = *(float*)&m14;
    if (v < 0.0f) v = 0.0f;
    if (v > m1c) v = m1c;
    *(float*)&m14 = v;
    m11 = true;
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00662c10
void FeedList::FUN_00662c10(void* w)
{
    if (m50) m50->SetActive(false);
    Obj50* old = m50;
    if (w != old) {
        if (w) ((Obj50*)w)->AddRef();
        m50 = (Obj50*)w;
        if (old) old->Release();
    }
    if (m50) {
        m50->SetActive(true);
        m13 = true;
    }
}

// @ 0x00662c70
void FeedList::FUN_00662c70(void* objp)
{
    if (!objp) return;
    void* px = *(void**)((char*)objp + 0x90);
    if (!px) return;
    float r = *(float*)((char*)px + 0x2c);
    float tmp[2];
    float* q = ((ObjX*)objp)->FUN_006665e0(tmp);
    float t = q[1] + r;
    float br = ((ObjX*)objp)->FUN_00c37480();
    float sum = br + t;
    int h = ((ObjM20*)m34->m20)->Slot40();
    float fh = (float)h;
    float v14 = *(float*)&m14;
    if (v14 > t) {
        *(float*)&m14 = t;
    } else if (sum > v14 + fh) {
        *(float*)&m14 = sum - fh;
    }
    float v = *(float*)&m14;
    if (v < 0.0f) v = 0.0f;
    if (v > m1c) v = m1c;
    *(float*)&m14 = v;
    m11 = true;
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00662d70
void cSPUIFeedList_Update(cSPUIFeedList* s)
{
    char* p = (char*)s;
    if (!*(void**)(p + 0x34) || !*(void**)(p + 0x30)) return;
    float* r = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x30), 0x38))(*(void**)(p + 0x30));
    float v[4];
    v[0] = r[0]; v[1] = r[1]; v[2] = r[2]; v[3] = r[3];
    SPUIHelpers_UpdateScrollFrameVertical(0);
    void* w = *(void**)(p + 0x34);
    float* ww = (float*)*(void**)((char*)w + 0x20);
    int a = (*(int(__thiscall*)(void*))Vslot(ww, 0x40))(ww);
    int b = (*(int(__thiscall*)(void*))Vslot(ww, 0x38))(ww);
    *(float*)(p + 0x1c) = (float)(b - a);
    void* inner = *(void**)((char*)*(void**)(p + 0x34) + 0x18);
    float* ir = (*(float*(__thiscall*)(void*))Vslot(inner, 0x38))(inner);
    v[2] = (ir[2] - ir[0]) + ir[0];
    (*(void(__thiscall*)(void*, void*))Vslot(*(void**)(p + 0x30), 0x6c))(*(void**)(p + 0x30), v);
    void* cli = *(void**)((char*)*(void**)(p + 0x34) + 0x20);
    if (cli) {
        int t1 = 0x96, t2 = 8;
        void* ab = SP_AssetBrowser();
        if (ab && *(void**)((char*)ab + 0x18)) {
            ab = SP_AssetBrowser();
            t1 = cTribeTool_GetTutorialToolPrice((int)*(void**)((char*)ab + 0x18), 0x2690b86e, 0x96);
            ab = SP_AssetBrowser();
            t2 = cTribeTool_GetTutorialToolPrice((int)*(void**)((char*)ab + 0x18), 0x908bbe2d, 8);
        }
        (*(void(__thiscall*)(void*, int))Vslot(cli, 0x4c))(cli, t1);
        (*(void(__thiscall*)(void*, int))Vslot(cli, 0x54))(cli, t2);
    }
}

// @ 0x00662ea0
char cSPUIFeedList_DoMessage(cSPUIFeedList* s, int msg, int* data)
{
    (void)msg;
    char* p = (char*)s;
    if (data[2] == 9) {
        if (data[1] == *(int*)(p + 0x30) || data[1] == *(int*)(*(int*)(p + 0x34) + 0x18)) {
            float mult = 0.8f;
            void* ab = SP_AssetBrowser();
            if (ab && *(void**)((char*)ab + 0x18)) {
                ab = SP_AssetBrowser();
                mult = GetPropertyT_f((int)*(void**)((char*)ab + 0x18), 0xfd92843d, 0.8f);
            }
            float t = *(float*)(p + 0x14) - (float)data[0x18/4] * mult;
            *(float*)(p + 0x14) = t;
            if (t <= 0.0f) t = 0.0f;
            if (*(float*)(p + 0x1c) <= t) t = *(float*)(p + 0x1c);
            *(float*)(p + 0x14) = t;
            *(char*)(p + 0x11) = 1;
            return 1;
        }
    }
    else if (data[2] == (int)0x8ef0c8dd) {
        int v = *(int*)(p + 0x34);
        if (data[1] == *(int*)(v + 0x10)) {
            if (!*(char*)(p + 0x11) && v) {
                *(float*)(p + 0x18) = (float)(*(int(__thiscall*)(void*))Vslot(*(void**)(v + 0x20), 0x28))(*(void**)(v + 0x20));
                *(float*)(p + 0x14) = (float)(*(int(__thiscall*)(void*))Vslot(*(void**)(*(int*)(p + 0x34) + 0x20), 0x28))(*(void**)(*(int*)(p + 0x34) + 0x20));
            }
            void* w = *(void**)(p + 0x28);
            if (w) {
                float* r = (*(float*(__thiscall*)(void*))Vslot(w, 0x38))(w);
                float vv[4];
                vv[0] = r[0]; vv[2] = r[2];
                float d = -(float)data[5] - r[1];
                vv[1] = r[1] + d; vv[3] = r[3] + d;
                (*(void(__thiscall*)(void*, void*))Vslot(w, 0x6c))(w, vv);
            }
            return 0;
        }
    }
    return 0;
}

// @ 0x00663040
void* cSPUIFeedList::Ctor()
{
    char* p = (char*)this;
    *(void* volatile*)&p[4] = &gVtA;
    *(void* volatile*)&p[8] = &gVtB;
    *(int* volatile*)(p + 0xc) = 0;
    *(void**)(p + 0) = &gVtC;
    *(void**)(p + 4) = &gVtD;
    *(void**)(p + 8) = &gVtE;
    *(char*)(p + 0x10) = 0;
    *(char*)(p + 0x11) = 0;
    *(char*)(p + 0x12) = 0;
    *(char*)(p + 0x13) = 0;
    *(float*)(p + 0x14) = 0.0f;
    *(float*)(p + 0x18) = 0.0f;
    *(float*)(p + 0x1c) = 0.0f;
    *(void**)(p + 0x20) = 0; *(void**)(p + 0x24) = 0; *(void**)(p + 0x28) = 0;
    *(void**)(p + 0x2c) = 0; *(void**)(p + 0x30) = 0; *(void**)(p + 0x34) = 0;
    *(void**)(p + 0x38) = 0; *(void**)(p + 0x3c) = 0; *(void**)(p + 0x40) = 0;
    *(void**)(p + 0x4c) = 0;
    *(void**)(p + 0x50) = 0; *(void**)(p + 0x54) = 0; *(void**)(p + 0x58) = 0;
    *(void**)(p + 0x5c) = 0; *(void**)(p + 0x60) = 0; *(void**)(p + 0x64) = 0;
    *(void**)(p + 0x68) = 0;
    return p;
}

// @ 0x006631c0
void cSPUIFeedList_UpdateScrolling(cSPUIFeedList* s, unsigned dt)
{
    char* p = (char*)s;
    float speed = 6.0f;
    void* ab = SP_AssetBrowser();
    if (ab && *(void**)((char*)ab + 0x18)) {
        ab = SP_AssetBrowser();
        speed = GetPropertyT_f((int)*(void**)((char*)ab + 0x18), 0xac40f7e5, 6.0f);
    }
    if (*(void**)(p + 0x30) && *(float*)(p + 0x14) != *(float*)(p + 0x18)) {
        float f = (float)dt * speed * 0.001f;
        float cl = 0.0f;
        if (cl < f) cl = f;
        if (cl > 1.0f) cl = 1.0f;
        float v = (*(float*)(p + 0x14) - *(float*)(p + 0x18)) * cl + *(float*)(p + 0x18);
        *(float*)(p + 0x18) = v;
        void* cli = *(void**)(p + 0x34);
        if (cli) {
            void* inner = *(void**)((char*)cli + 0x20);
            (*(void(__thiscall*)(void*, int, int))Vslot(inner, 0x24))(inner, (int)v, 1);
        }
        float a = *(float*)(p + 0x18) - *(float*)(p + 0x14);
        if (a < 0) a = -a;
        if (!(a < 0.5f)) {
            *(float*)(p + 0x18) = *(float*)(p + 0x14);
        }
        SPUIHelpers_UpdateMouseFocus(1);
    }
    if (*(float*)(p + 0x18) == *(float*)(p + 0x14)) *(char*)(p + 0x11) = 0;
    cSPUIFeedList_Update(s);
    void* sel = *(void**)(p + 0x4c);
    if (sel) {
        FUN_00662b40(sel);
        sel = *(void**)(p + 0x4c);
        if (sel) { *(void**)(p + 0x4c) = 0; (*(FnP)Vslot(sel, 0xc))(sel); }
    }
    if (*(char*)(p + 0x13)) { FUN_00662c70(*(void**)(p + 0x50)); *(char*)(p + 0x13) = 0; }
}

// @ 0x00663860
void FUN_00663860(char* p, void* parent, int a, int b, void* cfg)
{
    void* old = *(void**)(p + 0x24);
    if (parent != old) {
        if (parent) (*(FnP)Vslot(parent, 0))(parent);
        *(void**)(p + 0x24) = parent;
        if (old) (*(FnP)Vslot(old, 4))(old);
    }
    if (cfg) {
        void* o2 = *(void**)(p + 0x28);
        if (cfg != o2) { (*(FnP)Vslot(cfg, 0))(cfg); *(void**)(p + 0x28) = cfg; if (o2) (*(FnP)Vslot(o2, 4))(o2); }
    }
    else {
        void* w = (void*)0;
        (void)w;
    }
    (void)a; (void)b;
    // full property/layout init
    void* pm = SP_PropertyManager();
    void* o2 = *(void**)(p + 0x68);
    if (o2) { *(void**)(p + 0x68) = 0; (*(FnP)Vslot(o2, 4))(o2); }
    (*(void(__thiscall*)(void*, int, void**))Vslot(pm, 0x2c))(pm, 0x6edc12d4, (void**)(p + 0x68));
    *(char*)(p + 0x10) = 1;
}

// @ 0x00663a90
char FUN_00663a90(char* p, unsigned msg, int* data)
{
    if (msg == 0x44db12e) { FUN_006634d0(p); return 0; }
    if (msg == 0x53dd093) {
        if (*(char*)(p + 0xc)) FUN_006629e0(p - 4);
        return 0;
    }
    if (msg == 0xb3d53f95 && *(char*)(p + 0xc)) {
        if (data) {
            if (!*(char*)(p + 0xe)) {
                void* g = (void*)0; (void)g;
            }
            void* arg = (void*)(unsigned)data[4];
            if (data[4] == 0) {
                if (*(char*)((char*)data + 0x14)) arg = FUN_006629a0(data[3]);
                else arg = FUN_00662960(data[3]);
            }
            FUN_00662c10(arg);
        }
    }
    return 0;
}
