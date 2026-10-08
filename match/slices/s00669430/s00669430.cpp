// Slice s00669430: SP::cSPUIFeedListItem::ReloadCallback (complete) and the constraint-lookup callback (outline only,
// see partial.txt).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl SP_ObjectTemplateDB();               // 0x0067cb40
void* __cdecl SP_MessageServer();                  // 0x0067dcc0
void* __cdecl cSPUILayout_FindWindow(void* self, unsigned id, int flag);
void  __cdecl FUN_00644a80(void* a, void* b, void* c, int d);
void  __cdecl FUN_006066f0(void* a);               // Constraint dtor
bool  __cdecl FUN_00664550(int v);
void  __cdecl FUN_00829d30_stub(void* p);

// Window interface slots used by the feed item (retail UTFWin::IWindow layout).
struct IWin {
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v0a(); virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual const float* GetArea();                 // +0x38
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17();
    virtual void SetArea(const float* rect);        // +0x60
    virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void SetSize(float a, float b);         // +0x70
    virtual void v1d(); virtual void v1e();
    virtual void SetFlag(int flag, int on);         // +0x7c
    virtual void SetCaption(const void* text);      // +0x80
    virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v2a(); virtual void v2b(); virtual void v2c();
    virtual void v2d(); virtual void v2e(); virtual void v2f(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39(); virtual void v3a(); virtual void v3b(); virtual void v3c();
    virtual void v3d(); virtual void v3e(); virtual void v3f(); virtual void v40();
    virtual void AddWinProc(void* proc);            // +0x104
    virtual void RemoveWinProc(void* proc);         // +0x108
};

struct RefObj {                                      // vtable-refcounted helper at +0x184
    virtual void v0();
    virtual void AddRef();                          // +0x04
    virtual void Release();                         // +0x08
    void Cancel();                                  // 0x00829d30
};

struct cSPUILayout {
    IWin* FindWindowByID(unsigned id, int flag);    // 0x008105b0
};

struct cSPColorRGBA {
    float r, g, b, a;
    cSPColorRGBA() {}
    cSPColorRGBA(const cSPColorRGBA& c) : r(c.r), g(c.g), b(c.b), a(c.a) {}
};

struct cAssetBrowser { char pad[0x18]; void* mpProps; };
cAssetBrowser* __cdecl AssetBrowser();               // 0x00401030
cSPColorRGBA* __cdecl GetColorProperty(cSPColorRGBA* out, void* props, unsigned id, cSPColorRGBA def);  // 0x00666b20
void __cdecl GetFloatProperty(void* props, unsigned id, float* out);                                    // 0x0040cf10
void __cdecl SetWindowAlpha(IWin* w, float a);                                                          // 0x00804fc0
void __cdecl SetWindowImage(IWin* w, const void* key, int index);                                       // 0x00807bb0

extern const cSPColorRGBA kColorDefaultA;            // 0x01527678
extern const cSPColorRGBA kColorDefaultB;            // 0x015275e8

struct cString {
    char pad[0x14];
    cString();                                                      // 0x006b5060
    ~cString();                                                     // 0x006b5240
    void Load(uint32_t tableId, uint32_t stringId, const wchar_t* def);   // 0x006b54b0
    const wchar_t* GetText();                                       // 0x006b55c0
};

struct NumberHolder { char pad[0x38]; int mCount; };
extern NumberHolder* gNumberHolder;                  // 0x015ee298

inline void* operator new(unsigned, void* p) { return p; }

struct AutoWin {                                     // EA::AutoRefCount<IWindow>
    IWin* mp;
    AutoWin() : mp(0) {}
    AutoWin(const AutoWin& x) : mp(x.mp) { if (mp) mp->AddRef(); }
};
struct WinVec {                                      // eastl::vector<AutoRefCount<IWindow>>
    AutoWin* mpBegin;
    AutoWin* mpEnd;
    AutoWin* mpCapacity;
    ~WinVec();                                                      // 0x004b5440
    void DoInsertValue(AutoWin* pos, const AutoWin& value);        // 0x004b6000
    void push_back(const AutoWin& value) {
        if (mpEnd < mpCapacity) {
            AutoWin* p = mpEnd++;
            if (p) ::new(p) AutoWin(value);
        } else
            DoInsertValue(mpEnd, value);
    }
};

struct FeedHelper {                                  // object created at +0x184
    FeedHelper* Init();                                             // 0x00829770 (ctor)
    void Rebuild(IWin* win, WinVec* wins, uint32_t arg, void* item);    // 0x00829bc0
};

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct FeedItem {
    char    pad00[8];
    char    mSub08[0x10];               // +0x08 (address passed on)
    const wchar_t* mpFeedName;          // +0x18
    char    pad1c[0xc];
    const wchar_t* mpFeedAuthor;        // +0x28
    char    pad2c[0x34];
    int     mCount60;                   // +0x60
    int     mCount64;                   // +0x64
    float   mArea[4];                   // +0x68 (x0, y0, x1, y1)
    uint32_t mIconKey[3];               // +0x78
    char    pad84[2];
    uint8_t mChanged;                   // +0x86
    char    pad87[0xd];
    cSPUILayout* mLayout;               // +0x94
    char    pad98[4];
    uint32_t mField9C;                  // +0x9c
    IWin*   mWinRoot;                   // +0xa0
    IWin*   mWinA4;                     // +0xa4
    IWin*   mWinA8;                     // +0xa8
    IWin*   mWinAC;                     // +0xac
    IWin*   mWinB0;                     // +0xb0
    IWin*   mWinB4;                     // +0xb4
    IWin*   mWinB8;                     // +0xb8
    IWin*   mWinBC;                     // +0xbc
    char    padc0[8];
    float   mHeightC8;                  // +0xc8
    float   mHeightCC;                  // +0xcc
    char    padd0[4];
    cSPColorRGBA mColorD4;              // +0xd4
    cSPColorRGBA mColorE4;              // +0xe4
    cSPColorRGBA mColorF4;              // +0xf4
    cSPColorRGBA mColor104;             // +0x104
    char    pad114[0x1c];
    int     mCount;                     // +0x130
    char    pad134[8];
    int     mType;                      // +0x13c
    char    pad140[0x44];
    RefObj* mpHelper;                   // +0x184
    int     CountItems();                                           // 0x006693c0
};

__forceinline void AssignWin(IWin** field, IWin* nw)
{
    IWin* old = *field;
    if (nw != old) {
        if (nw) nw->AddRef();
        *field = nw;
        if (old) old->Release();
    }
}

// -----------------------------------------------------------------------------
// @ 0x00669430  SP::cSPUIFeedListItem::ReloadCallback
// -----------------------------------------------------------------------------
void __cdecl ReloadCallback(FeedItem* self, int a2, bool reload) {
    (void)a2;
    if (!reload) {
        if (self->mWinRoot) self->mWinRoot->RemoveWinProc(self);
        if (self->mpHelper) {
            self->mpHelper->Cancel();
            RefObj* p = self->mpHelper;
            if (p) {
                self->mpHelper = 0;
                p->Release();
            }
        }
        return;
    }

    AssignWin(&self->mWinRoot, self->mLayout->FindWindowByID(0xf3c6dc19, 1));

    if (AssetBrowser() && AssetBrowser()->mpProps) {
        cSPColorRGBA buf;
        unsigned id2;
        if (self->mType == 0xb) {
            self->mColorD4 = *GetColorProperty(&buf, AssetBrowser()->mpProps, 0x139ac029, kColorDefaultA);
            id2 = 0xe025f710;
        } else {
            self->mColorD4 = *GetColorProperty(&buf, AssetBrowser()->mpProps, 0x6b9f30ed, kColorDefaultA);
            id2 = 0x2695d23c;
        }
        self->mColorF4 = *GetColorProperty(&buf, AssetBrowser()->mpProps, id2, kColorDefaultB);
        self->mColorE4 = self->mColorD4;
        self->mColor104 = self->mColorF4;
    }

    AssignWin(&self->mWinAC, self->mLayout->FindWindowByID(0xf435d021, 1));
    AssignWin(&self->mWinB0, self->mLayout->FindWindowByID(0xd4232d3b, 1));
    if (self->mWinB0)
        SetWindowAlpha(self->mWinB0, 0.0f);

    AssignWin(&self->mWinA4, self->mLayout->FindWindowByID(0xb3c6efca, 1));
    if (self->mWinA4)
        self->mWinA4->SetCaption(self->mpFeedName);

    AssignWin(&self->mWinB4, self->mLayout->FindWindowByID(0x548f3bf6, 1));
    if (self->mWinB4 && self->mIconKey[0]) {
        SetWindowImage(self->mWinB4, self->mIconKey, 0);
        self->mWinB4->SetFlag(1, 1);
    }

    if (self->mWinA4 && self->mWinB4) {
        float h = self->mWinA4->GetArea()[1];
        float w = self->mWinB4->GetArea()[2];
        float pad;
        float x;
        if (self->mIconKey[0]) {
            pad = 2.0f;
            if (AssetBrowser() && AssetBrowser()->mpProps)
                GetFloatProperty(AssetBrowser()->mpProps, 0x02beb75e, &pad);
            x = w + pad;
        } else {
            pad = 6.0f;
            if (AssetBrowser() && AssetBrowser()->mpProps)
                GetFloatProperty(AssetBrowser()->mpProps, 0xa05a01c6, &pad);
            x = pad;
        }
        self->mWinA4->SetSize(x, h);
    }

    if (self->mType == 0xb) {
        AssignWin(&self->mWinBC, self->mLayout->FindWindowByID(0x07d5f060, 1));
    } else {
        AssignWin(&self->mWinBC, self->mLayout->FindWindowByID(0x14c87a13, 1));
        if (self->mWinBC)
            self->mWinBC->SetCaption(self->mpFeedAuthor);
    }

    AssignWin(&self->mWinB8, self->mLayout->FindWindowByID(0x14c87a12, 1));
    if (self->mWinB8) {
        gNumberHolder->mCount = self->mCount;
        cString s;
        s.Load(0x21671745, 0xf4c87cf6 + (self->mCount != 1), L"*Num Subscribers*");
        self->mWinB8->SetCaption(s.GetText());
    }

    AssignWin(&self->mWinA8, self->mLayout->FindWindowByID(0xb48e225b, 1));
    if (self->mWinA8)
        self->mWinA8->SetFlag(1, 0);

    if (self->mWinRoot) {
        const float* r = self->mWinRoot->GetArea();
        float a[4] = { r[0], r[1], r[2], r[3] };
        float rect[4] = { 0.0f, 0.0f, a[2] - a[0], a[3] - a[1] };
        self->mWinRoot->SetArea(rect);
        self->mArea[0] = rect[0];
        self->mArea[1] = rect[1];
        self->mArea[2] = rect[2];
        self->mArea[3] = rect[3];
        float h = rect[3] - rect[1];
        self->mHeightC8 = h;
        self->mHeightCC = h;
    }
    if (self->mWinRoot)
        self->mWinRoot->AddWinProc(self);

    WinVec wins = { 0, 0, 0 };
    wins.push_back(*(AutoWin*)&self->mWinA4);
    wins.push_back(*(AutoWin*)&self->mWinB8);
    wins.push_back(*(AutoWin*)&self->mWinBC);

    FeedHelper* helper = 0;
    {
        void* mem = ::operator new(0x34, "UI", 0, 0, 0, 0);
        if (mem)
            helper = ((FeedHelper*)mem)->Init();
    }
    RefObj* nh = (RefObj*)helper;
    RefObj* old = self->mpHelper;
    if (nh != old) {
        if (nh) nh->AddRef();
        self->mpHelper = nh;
        if (old) old->Release();
    }
    ((FeedHelper*)self->mpHelper)->Rebuild(self->mWinRoot, &wins, self->mField9C, self->mSub08);

    self->mCount60 = self->CountItems();
    if (self->mCount60 != self->mCount64)
        self->mChanged = 1;
}

// -----------------------------------------------------------------------------
// @ 0x00669c90  constraint-lookup callback (IWinProc DoMessage override)
// -----------------------------------------------------------------------------
bool __fastcall FUN_00669c90(void* self, int a1, unsigned* a2) {
    void* item = (char*)self - 4;
    if (!*(uint8_t*)((char*)self + 0x10)) return false;
    if (!*(void**)((char*)item + 0x90)) return false;
    if (!FUN_00664550(1)) return false;
    if (*(int*)((char*)self + 0x174) != 0x11f44f6b) return false;
    if (a1 != 0x064e5bda && a1 != (int)0x9421c619) return false;
    (void)a2;
    // Skeleton: the real body dispatches on the feed-type/query hashes, builds
    // SP::FunctionalMatch::Constraint objects and probes SP::ObjectTemplateDB.
    return false;
}
