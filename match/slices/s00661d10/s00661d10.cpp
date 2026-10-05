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
    char      pad6c[4];
    IWindow*  m70;                 // +0x70
    IWindow*  m74;                 // +0x74
    IWindow*  m78;                 // +0x78
    char      pad7c[0x14];
    float     m90, m94, m98;       // +0x90
    char      pad9c[4];
    FeedTreeNode* mEnd;            // +0xa0
    FeedTreeNode* mBegin;          // +0xa4
    char      padA8[0x30];

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
// 0x00661d10 : CreateFilterButtons (large; see partial.txt).  Skeleton keeps the call shape.
// ---------------------------------------------------------------------------------------------
// @ 0x00661d10
__declspec(noinline) void FeedList::CreateFilterButtons(int param, int a, int b, int* out) {
    if (!FUN_00661a10(param)) {
        if (out) *out = 0;
        return;
    }
    (void)a; (void)b;
    if (out) *out = 0;
}
