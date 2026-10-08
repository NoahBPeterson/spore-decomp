// Slice s00661d10: SP::cSPUIFeedList - filter-button construction, the per-category vector sweeps,
// layout teardown and the mouse-focus scroll clamps.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// allocator
// ---------------------------------------------------------------------------------------------
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0

// ---------------------------------------------------------------------------------------------
// UTFWin IWindow / cSPUILayout stubs (same slot layout as slice s0065f970).
// ---------------------------------------------------------------------------------------------
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

struct cSPUILayout {
    virtual void s0(); virtual void s1(); virtual int Release();
    void Shutdown(bool);                                   // 0x00811ad0
    IWindow* FindWindowByID(uint32_t, bool);               // 0x008105b0
    void Init(const uint32_t* area, int a, uint32_t key);  // 0x008120d0
    void SetParentWin(void* win, int a, uint32_t key);     // 0x008121b0
    void SetReloadCallback(void* fn, void* self);          // 0x00810090
    cSPUILayout* Construct();                              // 0x00810000
    char pad[0x18 - 4];
};

struct AudioAT {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void* Slot20();                                // +0x20
};

struct ObjX { float* FUN_006665e0(void* out); float FUN_00c37480(); };

struct IMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void PostMessage(uint32_t id, uint32_t a, uint32_t b);   // +0x14
};

void __cdecl EA_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // 0x00571db0
void  __cdecl SPUIHelpers_UpdateMouseFocus(int b);                                       // 0x00804f50
void  __cdecl ReloadCallback(void* self, void* layout, char b);                          // 0x0065faa0
void  __cdecl FUN_00660b90(void* self);                                                  // 0x00660b90
void  __cdecl FUN_00661900(void* a, void* b);                                            // 0x00661900
IMessageServer* __cdecl SP_MessageServer();                                              // 0x0067dcc0
void* __cdecl SP_GetSystemAT();                                                          // 0x00a206f0
void  __cdecl SP_KillSetiEffects(uint32_t id, void* at);                                 // 0x00435ed0
void* __cdecl RBTreeIncrement(void* n);                                                  // 0x00921580

// ---------------------------------------------------------------------------------------------
// element / sub-object types (calls are relocations; the names only carry the ABI).
// ---------------------------------------------------------------------------------------------
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
struct FeedSub {
    void FUN_00661700();          // 0x00661700 (thiscall)
    void FUN_00661390(void* arg); // 0x00661390 (thiscall, 1 arg)
};
struct FeedFilterA {
    int m0, m4; IWindow* m8; IWindow* mWin[4];
    void Update4();               // 0x0065f970
    void FUN_0065f820(void* arg); // 0x0065f820
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
    cSPUILayout* mLayout20;        // +0x20
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
    union { uint32_t m64; cSPUILayout* mLayout64; };  // +0x64
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

// ---------------------------------------------------------------------------------------------
// simple vector sweeps
// ---------------------------------------------------------------------------------------------
// @ 0x00662920
void FeedList::FUN_00662920(bool v) {
    m10 = v;
    if (m24) m24->SetFlag(1, v);
    if (m28) m28->SetFlag(1, v);
}

// @ 0x00662960
int FeedList::FUN_00662960(void* arg) {
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        int r = ((ElemA*)m38[i])->Method(arg);
        if (r) return r;
    }
    return 0;
}

// @ 0x006629a0
int FeedList::FUN_006629a0(void* arg) {
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        int r = ((ElemB*)m38[i])->Method(arg);
        if (r) return r;
    }
    return 0;
}

// @ 0x006629e0
void FeedList::FUN_006629e0() {
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        ((ElemC*)m38[i])->Method();
    }
}

// @ 0x00662a20
void* FeedList::FUN_00662a20(uint32_t idx) {
    uint32_t i = idx;
    void* result = 0;
    if (i < (uint32_t)(((int)m3c - (int)m38) >> 2))
        result = m38[i];
    return result;
}

// @ 0x00662a40
void* FeedList::FUN_00662a40(int id) {
    for (uint32_t i = 0; i < (uint32_t)(((int)m3c - (int)m38) >> 2); ++i)
        if (*(int*)((char*)m38[i] + 0xb4) == id) return m38[i];
    return 0;
}

// @ 0x00662a90
void FeedList::FUN_00662a90(void* arg) {
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        ((ElemE*)m38[i])->Expand(arg);
    }
}

// @ 0x00662ad0
void FeedList::FUN_00662ad0() {
    int n = (int)((int)m3c - (int)m38) >> 2;
    for (int i = 0; i < n; ++i) {
        ((ElemD*)m38[i])->Method();
    }
}

// @ 0x006628d0
void FeedList::FUN_006628d0() {
    if (mLayout20) {
        mLayout20->Shutdown(true);
        cSPUILayout* p = mLayout20;
        if (p) { mLayout20 = 0; p->Release(); }
    }
    if (m54) {
        void* h = m54;
        uint32_t a = m58, b = m5c, c = m60, d = m64;
        m54 = 0;
        EA_RemoveHandler(h, a, b, c, d);
    }
}

// @ 0x00662c10
void FeedList::FUN_00662c10(void* w) {
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

// ---------------------------------------------------------------------------------------------
// behaviourally-complete reconstructions (see nonmatching.txt)
// ---------------------------------------------------------------------------------------------
// @ 0x006624d0
void FeedList::FUN_006624d0(int param) {
    int local = 0;
    CreateFilterButtons(param, 1, 0, &local);
    bool b = local != 1;
    for (FeedTreeNode* it = mBegin; it != (FeedTreeNode*)&mEnd; it = (FeedTreeNode*)RBTreeIncrement(it)) {
        if (it->b18) {
            IWindow* w = it->mWin;
            if (w) {
                w->SetFlag(2, b);
            }
        }
    }
}

// @ 0x00662540
void FeedList::FUN_00662540() {
    for (FeedTreeNode* it = mBegin; it != (FeedTreeNode*)&mEnd; it = (FeedTreeNode*)RBTreeIncrement(it)) {
        it->b18 = false;
        it->b19 = false;
    }
    if (m14 != 0 && m18 != 0) {
        FUN_006624d0(m14);
        DoMessage();
        ((FeedFilterA*)((char*)this + 0xd8))->Update4();
        ((FeedSub*)((char*)this + 0x30))->FUN_00661700();
        FUN_00661900((void*)m14, (char*)this + 0x30);
        if (m14 == m18) {
            ((FeedSub*)((char*)this + 0x1c))->FUN_00661390((char*)this + 0x30);
            GetSupportedFilterTypes(m18);
            return;
        }
        ((FeedSub*)((char*)this + 0x1c))->FUN_00661700();
        FUN_00661900((void*)m18, (char*)this + 0x1c);
        GetSupportedFilterTypes(m18);
    }
}

// @ 0x006625f0
void FeedList::FUN_006625f0(int* param2, void* param3) {
    IWindow* old68 = m68;
    if (param2 != (int*)old68) {
        if (param2) ((IWindow*)param2)->s00();
        m68 = (IWindow*)param2;
        if (old68) old68->Release();
    }
    m14 = (int)param3;
    m18 = (int)param3;
    cSPUILayout* nl = (cSPUILayout*)EASTL_allocator_allocate(0x18, "Sporepedia", 0, 0, 0, 0);
    if (nl) nl = nl->Construct();
    cSPUILayout* old = mLayout64;
    if (nl != old) {
        if (nl) nl->s1();
        mLayout64 = nl;
        if (old) old->Release();
    }
    uint32_t area[3];
    area[0] = 0xab75403;
    area[1] = 0x510a95b;
    area[2] = *(uint32_t*)0x1526fb4;
    mLayout64->Init(area, 1, 0x5b598fa);
    mLayout64->SetParentWin(m68, 1, 0x5b598fa);
    mLayout64->SetReloadCallback((void*)0x65faa0, this);
    ReloadCallback(this, mLayout64, 1);
    if (m74) {
        float* a = m74->GetArea();
        float* b = m74->GetArea();
        m90 = b[0];
        m94 = a[1];
        float* c = m74->GetArea();
        m98 = c[2] - c[0];
    }
    ((FeedFilterA*)((char*)this + 0xd8))->FUN_0065f820(m78);
    FUN_00662540();
}

// @ 0x00662750
void FeedList::FUN_00662750(int param2, int param3, char param4) {
    if (param2 == 0) {
        m18 = param3;
    } else {
        int old = m14;
        m14 = param2;
        if (param4 == 0 || old == m18) {
            m18 = param3;
        } else {
            if (!FUN_00661c00(param2, 0)) m18 = param3;
        }
        FUN_00660b90(this);
    }
    FUN_00662540();
    SP_MessageServer()->PostMessage(0xd43aca3c, 0, 0);
}

// @ 0x006627d0
bool FeedList::FUN_006627d0(void* a, int* msg) {
    (void)a;
    if (*(int*)((char*)msg + 8) != 0x287259f6) return false;
    void* at = SP_GetSystemAT();
    void* r = at ? ((AudioAT*)at)->Slot20() : 0;
    SP_KillSetiEffects(0x43ae5220, r);
    m18 = *(int*)((char*)msg + 0xc);
    FUN_00662540();
    SP_MessageServer()->PostMessage(0xd43aca3c, 0, 0);
    return true;
}

// @ 0x00662b40
void FeedList::FUN_00662b40(void* objp) {
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

// @ 0x00662c70
void FeedList::FUN_00662c70(void* objp) {
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


// ---------------------------------------------------------------------------------------------
// 0x00661d10 : CreateFilterButtons
// ---------------------------------------------------------------------------------------------
struct CFVec2 { float x, y; };
struct CFKey { uint32_t a, b, c; };

struct CFWin {                                   // UTFWin window (slots by index)
    virtual void v0(); virtual int Release();
    virtual void v2(); virtual void v3();
    virtual CFWin* GetInner();                   // 4  +0x10
    virtual void v5(); virtual void v6();
    virtual int GetTypeId();                     // 7  +0x1c
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual float* GetArea();                    // 14 +0x38
    virtual void v15(); virtual void v16();
    virtual void SetCmd(uint32_t id);            // 17 +0x44
    virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void SetLocation(float x, float y);  // 28 +0x70
    virtual void SetSize(float w, float h);      // 29 +0x74
    virtual void v30(); virtual void v31();
    virtual void SetCaption(const wchar_t* t);   // 32 +0x80
    virtual void SetFlag2(uint32_t id);          // 33 +0x84
    virtual void v34(); virtual void v35();
    virtual void Finish();                       // 36 +0x90
    virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41();
    virtual uint32_t GetHandle();                // 42 +0xa8
    virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48();
    virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54();
    virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60();
    virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64();
    virtual void AddProc(void* p);               // 65 +0x104
};

struct CFLayout {
    virtual void s0(); virtual void s1(); virtual int Release();
    CFLayout* Construct();                               // 0x00810000
    void Init(const CFKey* k, int a, uint32_t key);      // 0x008120d0
    void SetParentWin(CFWin* w, int a, uint32_t key);    // 0x008121b0
    void SetVisibility(int v);                           // 0x00810590
    CFWin* FindWindowByID(uint32_t id, bool recurse);    // 0x008105b0
    char pad[0x14];
};

struct CFWinRef {
    CFWin* p;
    void Assign(CFWin* w);   // 0x00b5f950
};
struct CFLayoutRef {
    CFLayout* p;
    void Assign(const CFLayoutRef* r);   // 0x005766e0
    void Ctor(CFLayout* l);        // 0x00572620
};
struct CFTooltipRef {
    void* p;
    void Ctor(void* t);   // 0x00572660
};
struct CFString {
    char b[0x10];
    void Ctor();                   // 0x006b5060
    const wchar_t* GetText();      // 0x006b55c0
    void Dtor();                   // 0x006b5240
};
struct CFPlist { virtual void a0(); virtual void Release(); };
struct CFPropMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void GetPropertyList(int key, uint32_t id, CFPlist** out); };   // 11 +0x2c
struct CFValue {                                 // map value (tree node + 0x14)
    CFWinRef win; bool b4; bool b5; char pad6[2];
    float x, y; float rx, ry; uint32_t k18, k1c;
};
struct CFMap {
    void** find(void* out, const int* key);   // 0x00e5c780
    CFValue* Get(const int* key);             // 0x006612b0
};
struct CFHash {
    void** find(void* out, const CFKey* key);       // 0x00833840
    CFLayoutRef* Index(const CFKey* k);             // 0x00660c10
};

void*     __cdecl CF_AssetBrowser();                                                // 0x00401030
float     __cdecl CF_GetPropertyFloat(void* obj, uint32_t id, float def);           // 0x004e1c70
CFPropMgr* __cdecl CF_PropertyManager();                                            // 0x0067de30
bool      __cdecl CF_GetPropVec2(CFPlist* pl, uint32_t id, float* a, float* b);     // 0x006a0ae0
bool      __cdecl CF_GetPropArray(CFPlist* pl, uint32_t id, int* count, CFKey** arr);    // 0x006a0ae0
void      __cdecl CF_GetPropertyAsKey(CFPlist* pl, uint32_t id, CFKey* out);        // 0x006a1250
bool      __cdecl CF_GetPropertyAsText(CFPlist* pl, uint32_t id, CFString* out);    // 0x006a1360
void      __cdecl CF_GetPropertyAsKeyInstance(CFPlist* pl, uint32_t id, uint32_t* out);  // 0x006a12a0
CFWin*    __cdecl CF_ButtonFromHandle(uint32_t h, int t, int key, CFVec2 pos, CFWin* parent);   // 0x00806780
CFWin*    __cdecl CF_CreateButtonA(uint32_t a, int t, int key, CFVec2 pos, CFWin* parent);  // 0x00808930
CFWin*    __cdecl CF_CreateButtonB(CFKey* k, int t, int key, CFVec2 pos, CFWin* parent);    // 0x00807a50
CFWin*    __cdecl CF_InterfaceCast(CFWinRef* r);                                    // 0x005c2570
void*     __cdecl CF_AllocTooltipHeap();                                            // 0x009512c0
void*     __cdecl CF_AllocTooltip(int size, int align, const char* name, void* heap);  // 0x009512d0
struct CFTooltip {
    CFTooltip* Ctor(const wchar_t* name, uint32_t id, const wchar_t* text, float* off, int a, const void* b, int c);  // 0x00835e30
};
void* __cdecl CF_OperatorNew(uint32_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

// @ 0x00661d10
void FeedList::CreateFilterButtons(int key, int flag, int depth, int* counter) {
    if (!FUN_00661a10(key)) return;
    if (!m70) return;
    CFVec2 pos;
    float c0 = (float)*counter;
    pos.x = c0 * m98 + m90;
    pos.y = m94;
    if ((char)flag == 0) {
        float add = 0.0f;
        if (CF_AssetBrowser() && *(void**)((char*)CF_AssetBrowser() + 0x18))
            add = CF_GetPropertyFloat(*(void**)((char*)CF_AssetBrowser() + 0x18), 0x5b9cdcf4, 0.0f);
        pos.x += add;
    }
    md8 = depth;
    CFPlist* props = 0;
    CFPropMgr* pm = CF_PropertyManager();
    if (props) { CFPlist* t = props; props = 0; t->Release(); }
    pm->GetPropertyList(key, 0xcc489c6f, &props);
    if (props) {
        CFValue* node;
        char fallback = 0;
        char found[4];
        CFMap* map = (CFMap*)((char*)this + 0x9c);
        void* endNode = (char*)this + 0xa0;
        if (*map->find(found, &key) == endNode) {
            node = map->Get(&key);
            float o2c = 0, o30 = 0;
            CFWin* btn;
            if (CF_GetPropVec2(props, 0x7435a2d1, &o30, &o2c)) {
                btn = CF_CreateButtonA(*(uint32_t*)&o2c, 3, key, pos, (CFWin*)m70);
            } else {
                CFKey k = {0, 0, 0};
                CF_GetPropertyAsKey(props, 0x86ad309, &k);
                uint32_t winId = k.b;
                k.b = 0x510a95b;
                if (winId == 0 || winId == (uint32_t)-1) winId = key;
                CFLayoutRef layout; layout.p = 0;
                CFWinRef w; w.p = 0;
                CFWinRef bw; bw.p = 0;
                if (k.a == 0 || k.a == (uint32_t)-1) {
                    w.Assign(((CFLayout*)mLayout64)->FindWindowByID(winId, true));
                    bw.Assign(CF_InterfaceCast(&w));
                } else {
                    if (k.c == 0 || k.c == (uint32_t)-1) k.c = 0x40464100;
                    char it[8];
                    CFHash* h = (CFHash*)mHash;
                    h->find(it, &k);
                    void** buckets = *(void***)(mHash + 4);
                    int nb = *(int*)(mHash + 8);
                    if (*(void**)(it) != buckets[nb]) {
                        layout.Assign((CFLayoutRef*)((char*)*(void**)it + 0xc));
                    } else {
                        CFLayout* nl = (CFLayout*)CF_OperatorNew(0x18, "Sporepedia", 0, 0, 0, 0);
                        if (nl) nl = nl->Construct();
                        layout.Ctor(nl);
                        layout.p->Init(&k, 1, 0x5b598fa);
                        layout.p->SetParentWin((CFWin*)m6c, 1, 0x5b598fa);
                        layout.p->SetVisibility(0);
                        h->Index(&k)->Assign(&layout);
                    }
                    w.Assign(layout.p->FindWindowByID(winId, true));
                    bw.Assign(CF_InterfaceCast(&w));
                }
                if (w.p && bw.p) {
                    btn = CF_ButtonFromHandle(w.p->GetHandle(), 3, key, pos, (CFWin*)m70);
                    if (w.p->GetInner()->GetTypeId() == 0x7e0c110) {
                        float* r = w.p->GetArea();
                        node->rx = r[0];
                        node->ry = r[1];
                        btn->GetInner()->SetSize(r[2] - r[0], r[3] - r[1]);
                        btn->GetInner()->SetLocation(node->rx + pos.x, node->ry + pos.y);
                    }
                } else {
                    CFKey k2 = {0xfa224478, 0x2f7d0004, 0x11c0bde};
                    btn = CF_CreateButtonB(&k2, 3, key, pos, (CFWin*)m70);
                    fallback = 1;
                }
                if (layout.p) layout.p->Release();
                if (w.p) w.p->Release();
                if (bw.p) bw.p->Release();
            }
            if (btn) {
                node->win.Assign(btn->GetInner());
                btn->SetCmd(0x3436f351);
                CFString str; str.Ctor();
                if (CF_GetPropertyAsText(props, 0x7435a2d0, &str)) {
                    if (fallback) {
                        CFWin* in = btn->GetInner();
                        in->SetCaption(str.GetText());
                        btn->GetInner()->SetFlag2(0xaf14b67e);
                        btn->GetInner()->Finish();
                    } else {
                        void* mem = CF_AllocTooltip(0x68, 4, "UI/Tooltip", CF_AllocTooltipHeap());
                        CFTooltip* tt = 0;
                        if (mem) {
                            float off[2]; off[0] = 0.0f; off[1] = *(float*)0x14000fc;
                            tt = ((CFTooltip*)mem)->Ctor(L"Tooltips", 0x3754e6c, str.GetText(), off, 0, (const void*)0x14000bc, 0);
                        }
                        CFTooltipRef tr; tr.Ctor(tt);
                        node->win.p->AddProc(tr.p);
                        if (tr.p) ((CFWin*)tr.p)->Release();
                    }
                }
                str.Dtor();
            }
            CF_GetPropertyAsKeyInstance(props, 0x7435a2d2, &node->k18);
            CF_GetPropertyAsKeyInstance(props, 0x14593fac, &node->k1c);
        } else {
            node = map->Get(&key);
        }
        node->b4 = true;
        node->x = pos.x;
        node->y = pos.y;
        bool sel = (key == m18);
        node->b5 = sel;
        if (sel) mdc = depth;
        ++*counter;
        if ((char)flag) {
            CFKey* arr = 0;
            int count = 0;
            if (CF_GetPropArray(props, 0x7435a2d3, &count, &arr)) {
                if (key == m18) {
                    for (int i = 0; i < count; ++i)
                        CreateFilterButtons(arr[i].a, 0, depth + 1, counter);
                } else if (FUN_00661c00(key, 0)) {
                    int idx = -1;
                    for (int i = 0; i < count; ++i) {
                        if (FUN_00661c00(arr[i].a, 0)) { idx = i; break; }
                    }
                    if (FUN_00661b10(arr[idx].a)) {
                        CreateFilterButtons(arr[idx].a, 1, depth + 1, counter);
                    } else {
                        for (int i = 0; i < count; ++i)
                            CreateFilterButtons(arr[i].a, 0, depth + 1, counter);
                    }
                }
            }
        }
        props->Release();
    }
}
