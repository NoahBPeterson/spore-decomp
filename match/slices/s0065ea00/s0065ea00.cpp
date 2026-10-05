// Slice s0065ea00: SP::cSPUIFeedEdit message handling, population and Init.
// UI module: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include "types.h"
#include <intrin.h>

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef int(__thiscall* FnRetI)(void*);
typedef void(__cdecl* FnC)(...);

static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
extern "C" void* operator_new_ea(unsigned int size, const char* tag, int, int, int, int);
extern "C" void  SPUIHelpers_SetWindowAreaToParent(void* win);
extern "C" void* SP_MessageServer();
extern "C" void* FUN_0067de40();
extern "C" void  FUN_00809db0(void* a, void* b);
extern "C" void  FUN_00996280(void* self, int a, int b, int c, int d);  // thiscall via struct
extern "C" void* FUN_0067cb30();
extern "C" void  FUN_0065cae0();
extern "C" void  FUN_0065d490();
extern "C" void  FUN_0065d260();
extern "C" void* GetAssetIndex();
extern "C" void* cSPUILayout_ctor(void* self);
extern "C" void* ObjectTemplateDB();
extern "C" void  AddPollinatorDebugInfo();
extern "C" void* SPUIHelpers_GetImageFromTexture();
extern const wchar_t* PTR_u_spore;  // 0x1526950

// ---------------------------------------------------------------------------
struct AssetInfo { uint64_t mnAssetID; uint32_t mnType; void* mpImage; };
struct AssetVec {
    AssetInfo* begin; AssetInfo* end; AssetInfo* cap;
    AssetInfo* DoInsertValue(AssetInfo* pos, AssetInfo* value);
    AssetInfo* erase(AssetInfo* first, AssetInfo* last);
    void push_back();
};
struct VecPtr { void* begin; void* end; void* cap; void* erase(void*, void*); };
struct HashSet { char pad[0xc]; int count; void DoFreeNodes(void*, void*); };
struct HashtableU64 { int count; int* erase(int* out, int* node, int* bucket); };
struct cSPUILayout {
    void* FindWindowByID(uint32_t id, int recursive);
    void* Init(const void* key, int a, int id);
    void  SetParentWin(void* parent, int a, int id);
    void  SetReloadCallback(void* fn, void* self);
};
struct TextSlot { void Assign(void* p); };
struct LayoutCtor { void* Create(); };
struct ComObj {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void Slot1c(void*);   // 0x1c
    virtual ComObj* Slot20();     // 0x20
};
struct cXHTMLFrameSet {
    void  FUN_00996280(int a, int b, int c, int d);
    void  FUN_00997140();
};
struct cSPUIFeedEditAssetView;
struct cSPUIFeedEdit;

extern "C" void* HashFind64(uint64_t* out, uint64_t* key);       // 0x553510
extern "C" void  HashDoInsert(uint64_t* a, uint64_t* b, int c);  // 0x553750

// IWindow with the slots used here (0x7c, 0x90, 0xf0, 0x104).
struct IWindow {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30();
    virtual void Slot7c(int, int);          // 0x7c (index 31)
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void Slot90();                  // 0x90 (index 36)
    virtual void m37(); virtual void m38(); virtual void m39(); virtual void m40();
    virtual void m41(); virtual void m42(); virtual void m43(); virtual void m44();
    virtual void m45(); virtual void m46(); virtual void m47(); virtual void m48();
    virtual void m49(); virtual void m50(); virtual void m51(); virtual void m52();
    virtual void m53(); virtual void m54(); virtual void m55(); virtual void m56();
    virtual void m57(); virtual void m58(); virtual void m59();
    virtual void* SlotF0(uint32_t id, int b);  // 0xf0 (index 60)
    virtual void m61(); virtual void m62(); virtual void m63(); virtual void m64();
    virtual void Slot104(void*);               // 0x104 (index 65)
};

struct cSPUIFeedEdit {
    void* vt;                          // 0x00
    char  pad04[0x10];                 // 0x04
    cSPUILayout* mpLayout;             // 0x14
    char  mFrameSet[0x48];             // 0x18
    char  pad60[0x1c];                 // 0x60
    IWindow* mpWin7c;                  // 0x7c
    void* mpWin80;                     // 0x80
    void* mpWin84;                     // 0x84
    void* mpWin88;                     // 0x88
    int   m8c;                         // 0x8c
    char  mbIsLoaded;                  // 0x90
    char  mbInited;                    // 0x91
    char  pad92[2];
    float mfAssetViewWidth;            // 0x94
    float mfAssetViewHeight;           // 0x98
    uint32_t mnAssetColCount;          // 0x9c
    uint32_t mnAssetRowCount;          // 0xa0
    uint32_t mnCurPage;                // 0xa4
    uint32_t mnNumPages;               // 0xa8
    int32_t  mnSelectedIndex;          // 0xac
    void* mViewBegin;                  // 0xb0
    void* mViewEnd;                    // 0xb4
    void* mViewCap;                    // 0xb8
    char  padbc[8];                    // 0xbc
    AssetVec mAssetList;               // 0xc4
    char  padcc[8];                    // 0xcc
    HashSet mNewAssets;                // 0xd8
    HashSet mDeleteAssets;             // 0xf8
    HashSet mExistingAssets;           // 0x118
    char  pad138[0x11];                // 0x138..0x148
    char  mbTransactionActive;         // 0x149
    char  mbNameSet;                   // 0x14a

    void DoMessage(int msg, void* data);
    void UnloadLayout();
    bool Populate();
    bool RemoveAsset(int a, int b);
    void ResetPanel();
    void LoadLayout();
    void Init(void* parent);
    void InitLayout();
    void LoadFilter(int param, bool b);
    char AddAsset(int a, int b, int c, void* img);
    char HandleMessage(int msg, int* data);
    void UpdateStrings();
    void UpdateEnabledState();
    void UpdateGrid();
    void UpdateButtons();
    bool SetPage(unsigned int page);
    int  GetAssetIndex2(int a, int b);
    void ShowAsset(int a, int b);
};

struct cSPUIFeedEditAssetView {
    void* vt; void* vt4; void* vt8;      // 0x00
    void* mpLayout;                        // 0x0c
    void* mpParentWin;                     // 0x10
    void* mpRootWin;                       // 0x14
    void* mpButtonWin;                     // 0x18
    void* mpAssetWin;                      // 0x1c
    void* mpBackdropWin;                   // 0x20
    void* mpGlowWin;                       // 0x24
    void* mpEmptyWin;                      // 0x28
    void* mpImage;                         // 0x2c
    int   mnMode;                          // 0x30
    int   pad34;                           // 0x34
    uint64_t mnAssetID;                    // 0x38
    uint32_t mnIndex;                      // 0x40
    uint32_t mTickMask;                    // 0x44
    float mfBlinkStart;                    // 0x48
    void ClearAsset();
    void SetMode(int m);
};

// @ 0x0065ea00
void cSPUIFeedEdit::DoMessage(int msg, void* data) {
    (void)msg;
    int* p = (int*)data;
    char* s = (char*)this;
    if (p && p[2] == 0x17) {
        if (p[3] == 0x590cb98 && (uint32_t)p[4] < ((*(int*)(s + 0xc8) - *(int*)(s + 0xc4)) >> 2)) {
            cSPUIFeedEditAssetView* v = *(cSPUIFeedEditAssetView**)(*(int*)(s + 0xc4) + p[4] * 4);
            if (v->mnMode > 0) {
                if (v->mnMode < 3) {
                    v->mfBlinkStart = 0.0f;
                    (*(FnP2)Vslot(v->mpAssetWin, 0x7c))(v->mpAssetWin, 1, 1);
                    (*(FnP2)Vslot(v->mpBackdropWin, 0x7c))(v->mpBackdropWin, 1, 1);
                    (*(FnP2)Vslot(v->mpGlowWin, 0x7c))(v->mpGlowWin, 1, 1);
                    (*(FnP2)Vslot(v->mpEmptyWin, 0x7c))(v->mpEmptyWin, 1, 0);
                    (*(FnP2)Vslot(v->mpButtonWin, 0x7c))(v->mpButtonWin, 1, 1);
                    (*(FnP)Vslot(v->mpRootWin, 0x90))(v->mpRootWin);
                    uint32_t hi = (uint32_t)(v->mnAssetID >> 32);
                    v->mnMode = 3;
                    *(int*)(s + 0xac) = GetAssetIndex2((int)v->mnAssetID, (int)hi);
                    UpdateGrid();
                    return;
                }
                if (v->mnMode == 3) {
                    v->SetMode(1);
                    *(int*)(s + 0xac) = -1;
                    UpdateGrid();
                    return;
                }
            }
        }
    }
    else if (p && p[2] == 0x18) {
        if (p[4] == 0x58b5d5b) { *(bool*)(s + 0x139) = (p[5] != 0); UpdateEnabledState(); return; }
        if (p[4] == 0x58b5d76) { *(char*)(s + 0x13a) = 1; UpdateEnabledState(); return; }
    }
    else if (p && p[2] == 0x287259f6) {
        int* o = (int*)*p;
        uint32_t uVar7 = (*(uint32_t(__thiscall*)(void*))Vslot(o, 0x1c))(o);
        int k = (*(int(__thiscall*)(void*))Vslot(o, 0x20))(o);
        if (k == 0x590cb98) {
            if (uVar7 < ((*(int*)(s + 0xc8) - *(int*)(s + 0xc4)) >> 2)) {
                cSPUIFeedEditAssetView* v = *(cSPUIFeedEditAssetView**)(*(int*)(s + 0xc4) + uVar7 * 4);
                RemoveAsset((int)v->mnAssetID, (int)(v->mnAssetID >> 32));
                return;
            }
        }
        else {
            if (uVar7 == 0x58b5d7e) { SetPage(*(uint32_t*)(s + 0xac)); return; }
            if (uVar7 == 0x58b5d84) { SetPage(*(uint32_t*)(s + 0xa8)); return; }
            if (uVar7 == 0x5937900) {
                void* a = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(mpLayout, 0xf0))(mpLayout, 0x58b5d5b, 1);
                void* b = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(mpLayout, 0xf0))(mpLayout, 0x58b5d76, 1);
                (void)a; (void)b;
                if (mnAssetRowCount == 0) { *(char*)(s + 0x139) = 0; }
                else if (mnAssetRowCount == 1) { *(char*)(s + 0x139) = 1; }
                *(char*)(s + 0x139) = 1;
                return;
            }
        }
    }
    else if (p && p[2] == 0x3326e8a) {
        *(char*)(s + 0x139) = 1;
        return;
    }
    else if (p && p[2] == 0x3326e8b) {
        *(char*)(s + 0x13a) = 1;
        return;
    }
    else if (p && p[2] == 0x43b0aee) {
        FUN_00809db0(0, (void*)0x1526ce4);
        return;
    }
}

// @ 0x0065ef10
struct CallbackObj {
    char pad[0x74];
    IWindow* win;
    void Handler(int a, int b);
};
void CallbackObj::Handler(int a, int b) {
    (void)a; (void)b;
    ((cSPUIFeedEdit*)((char*)this - 0xc))->ResetPanel();
    (*(FnP)Vslot(win, 0x90))(win);
}

// @ 0x0065ef30
void cSPUIFeedEdit::LoadFilter(int param, bool b) {
    char* s = (char*)this;
    mNewAssets.DoFreeNodes(*(void**)(s + 0xdc), *(void**)(s + 0xe0)); mNewAssets.count = 0;
    mDeleteAssets.DoFreeNodes(*(void**)(s + 0xfc), *(void**)(s + 0x100)); mDeleteAssets.count = 0;
    mExistingAssets.DoFreeNodes(*(void**)(s + 0x11c), *(void**)(s + 0x120)); mExistingAssets.count = 0;
    mAssetList.erase(mAssetList.begin, mAssetList.end);
    void* db = FUN_0067cb30();
    (void)db; (void)param; (void)b;
    mnNumPages = 1;
    FUN_0065cae0();
    UpdateStrings();
    *(char*)(s + 0x139) = 1;
    UpdateEnabledState();
}

// @ 0x0065f390
char cSPUIFeedEdit::AddAsset(int a, int b, int c, void* img) {
    char* s = (char*)this;
    if (c == 0) return 0;
    int bucket = *(int*)(*(int*)(s + 0xdc) + *(int*)(s + 0xe0) * 4);
    uint64_t key = (uint64_t)(uint32_t)a | ((uint64_t)(uint32_t)b << 32);
    uint64_t local = 0;
    void* r = HashFind64(&local, &key);
    if (*(int*)r != bucket) { return 0; }
    int b2 = *(int*)(*(int*)(s + 0xfc) + *(int*)(s + 0x100) * 4);
    void* r2 = HashFind64(&local, &key);
    if (*(int*)r2 != b2) { return 0; }

    mAssetList.push_back();
    AssetInfo* e = (AssetInfo*)(*(int*)(s + 0xc8) - 0x10);
    e->mnAssetID = (uint64_t)(uint32_t)a | ((uint64_t)(uint32_t)b << 32);
    e->mnType = c;
    ((TextSlot*)&e->mpImage)->Assign(img);
    HashFind64(&local, &key);
    {
        int delBucket = *(int*)(*(int*)(s + 0x11c) + *(int*)(s + 0x120) * 4);
        if (*(int*)(*(int*)(s + 0x11c) + *(int*)(s + 0x120) * 4) == delBucket) {
            /* insert into mExistingAssets */
            HashDoInsert(&local, &key, 0);
        }
    }
    UpdateEnabledState();
    FUN_0065d490();
    char result = 1;
    ShowAsset(a, b);
    UpdateStrings();
    return result;
}

// @ 0x0065f4d0
void cSPUIFeedEdit::InitLayout() {
    char* s = (char*)this;
    void* obj = EASTL_allocator_allocate(0x18, "Sporepedia", 0, 0, 0, 0);
    void* nw = obj ? ((LayoutCtor*)obj)->Create() : 0;
    cSPUILayout* old = mpLayout;
    if (nw != old) {
        if (nw) (*(FnP)Vslot(nw, 4))(nw);
        mpLayout = (cSPUILayout*)nw;
        if (old) (*(FnP)Vslot(old, 8))(old);
    }
    uint32_t keyv = *(uint32_t*)0x1526cb0;
    uint32_t key[3];
    key[0] = 0xa153f7a1; key[1] = 0x510a95b; key[2] = keyv;
    mpLayout->Init(key, 1, 0x5b598fa);
    mpLayout->SetParentWin(*(void**)(s + 0x7c), 1, 0x5b598fa);
    mpLayout->SetReloadCallback((void*)0x65e9e0, this);
    LoadLayout();
}

// @ 0x0065f580
char cSPUIFeedEdit::HandleMessage(int msg, int* data) {
    char* s = (char*)this;
    if (msg == 0x3b27023) {
        if (data) {
            AddAsset(data[4], data[5], data[6], (void*)data[7]);
            UpdateGrid();
        }
        return 1;
    }
    if (*(char*)(s + 0x138)) {
        if (msg == 0x3cdd5f9) {
            IWindow* ms = (IWindow*)SP_MessageServer();
            (*(void(__thiscall*)(void*, int, int, int))Vslot(ms, 0x14))(ms, 0x53dd093, 0, 0);
            if (s) FUN_00809db0((void*)0x1526cb4, *(void**)(s + 0xfffffff4 + 0x14 + 0x14));
            return 1;
        }
        if (msg == 0x49a3777) { return 1; }
        if (msg == 0x1dd7bda9 && data && data[1] && data[0] != 1) {
            if (*(int*)(s + 0x7c) == 0) return 1;
            if (*(int*)(s + 0x7c) == 1) return 1;
        }
        *(char*)(s + 0x138) = 0;
    }
    return 0;
}

// @ 0x0065f700
void cSPUIFeedEdit::Init(void* parent) {
    char* s = (char*)this;
    if (*(char*)(s + 0x91)) return;
    ((cXHTMLFrameSet*)(s + 0x18))->FUN_00996280(0x1002, 0x1006, 0x1003, 0x1024);
    IWindow* ms = (IWindow*)SP_MessageServer();
    if (!ms) return;

    void* old = *(void**)(s + 0x7c);
    if (parent != old) {
        if (parent) (*(FnP)Vslot(parent, 0))(parent);
        *(void**)(s + 0x7c) = parent;
        if (old) (*(FnP)Vslot(old, 4))(old);
    }
    ComObj* m = (ComObj*)FUN_0067de40();
    ComObj* q = m->Slot20();
    q->Slot1c(s);
    ((cSPUIFeedEdit*)s)->InitLayout();
    *(char*)(s + 0x91) = 1;
    void* handler = s + 0x10;
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x3b27023);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x1dd7bda9);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x3cdd5f9);
    (*(void(__thiscall*)(void*, void*, int))Vslot(ms, 0x20))(ms, handler, 0x49a3777);
}

// @ 0x0065f810
struct ModeViewGetter { char* Get(bool b); };
char* ModeViewGetter::Get(bool b) {
    char* r = (char*)this + 0x30;
    if (!b) r = (char*)this + 0x1c;
    return r;
}

// Keep every translated member function emitted even though some are only invoked
// indirectly through the original vtable.
__declspec(noinline) void keepalive_s0065ea00(cSPUIFeedEdit* p, cSPUIFeedEditAssetView* v) {
    p->DoMessage(0, 0);
    p->AddAsset(0, 0, 0, 0);
    p->LoadFilter(0, false);
    p->UnloadLayout();
    if (v) v->ClearAsset();
}

// @ 0x0065f820
struct WindowSet4 {
    void* p0; void* p4; IWindow* pParent; IWindow* pC; IWindow* p10; IWindow* p14; IWindow* p18;
    void Set(IWindow* parent);
};
void WindowSet4::Set(IWindow* parent) {
    p0 = 0;
    p4 = 0;
    IWindow* old = pParent;
    if (parent != old) {
        if (parent) (*(FnP)Vslot(parent, 0))(parent);
        pParent = parent;
        if (old) (*(FnP)Vslot(old, 4))(old);
    }
    if (pParent) {
        IWindow* a = (IWindow*)pParent->SlotF0(0xda7f4890, 1);
        IWindow* o1 = pC;
        if (a != o1) { if (a) (*(FnP)Vslot(a, 0))(a); pC = a; if (o1) (*(FnP)Vslot(o1, 4))(o1); }
        IWindow* b = (IWindow*)pParent->SlotF0(0xda7f4891, 1);
        IWindow* o2 = p10;
        if (b != o2) { if (b) (*(FnP)Vslot(b, 0))(b); p10 = b; if (o2) (*(FnP)Vslot(o2, 4))(o2); }
        IWindow* c = (IWindow*)pParent->SlotF0(0xda7f4892, 1);
        IWindow* o3 = p14;
        if (c != o3) { if (c) (*(FnP)Vslot(c, 0))(c); p14 = c; if (o3) (*(FnP)Vslot(o3, 4))(o3); }
        IWindow* d = (IWindow*)pParent->SlotF0(0xda7f4893, 1);
        IWindow* o4 = p18;
        if (d != o4) { if (d) (*(FnP)Vslot(d, 0))(d); p18 = d; if (o4) (*(FnP)Vslot(o4, 4))(o4); }
        IWindow** w = (IWindow**)((char*)this + 0xc);
        int n = 4;
        do {
            IWindow* x = *w;
            if (x) (*(FnP2)Vslot(x, 0x7c))(x, 1, 0);
            ++w;
        } while (--n);
    }
}
