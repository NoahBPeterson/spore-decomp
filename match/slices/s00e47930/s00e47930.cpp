// slice s00e47930 -- editor verb-icon panel UI refresh (retail class layout; the 2008 PDB candidate
// cSPEditorVerbIcon::StartCharge does not match the retail layout, so a local stub class is used).
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

typedef unsigned int size_t_;
void* operator new(unsigned int, const char*, int, int, int, int);
void operator delete[](void*);   // 0x00f47380

struct IWinProc { virtual void wp0(); };
struct Key3 { uint32_t a, b, c; };
struct KeyPtr { int a, b, c; void* d; };
struct V3 { float x, y, z; };

template <class T> struct AutoRef {
    T* p;
    void Set(T* n) { T* o = p; if (n != o) { if (n) n->AddRef(); p = n; if (o) o->Release(); } }
    void Clear() { T* o = p; if (o) { p = 0; o->Release(); } }
};

struct Prop {
    void* data;
    char pad[0xc];
    uint16_t flags;    // +0x10
    int16_t type;      // +0x12
};

struct IPropList;
struct IWindow {
    virtual void AddRef();
    virtual void Release();
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13();
    virtual float* GetRect();
    virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22();
    virtual void SetColor(uint32_t c);
    virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27();
    virtual void SetPos(float x, float y);
    virtual void SetSize(float w, float h);
    virtual void p30();
    virtual void SetFlag(int f, bool v);
    virtual void SetCaption(const wchar_t* s);
    virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56(); virtual void p57(); virtual void p58(); virtual void p59();
    virtual IWindow* FindChild(uint32_t id, bool b);
    virtual void p61(); virtual void p62(); virtual void p63(); virtual void p64();
    virtual void AddWinProc(IWinProc* p);
};
struct cSPUILayout {
    virtual void p0();
    virtual void AddRef();
    virtual void Release();
    cSPUILayout();                                  // 0x00810000
    IWindow* FindWindowByID(uint32_t id, int b);   // 0x008105b0
    void Init(Key3* k, int a, uint32_t b);          // 0x008120d0
    void SetParentWin(void* w, int a, uint32_t b);  // 0x008121b0
};
struct IPropList {
    virtual void AddRef();
    virtual void Release();
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8();
    virtual bool GetProperty(uint32_t id, Prop** out);
};
struct IPropMgr {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10();
    virtual bool Get(uint32_t a, uint32_t b, AutoRef<IPropList>* out);
};
struct IEffectCtl {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual IWinProc* GetWinProc();
    virtual void p5();
    virtual void SetDuration(float f);
    virtual void p7();
    virtual void SetA(int a);
    virtual void p9();
    virtual void SetXY(float x, float y);
    virtual void p11();
    virtual void SetB(int a);
    virtual void p13();
    virtual void SetC(float f);
};
struct Effect {
    virtual void AddRef();
    virtual void Release();
};
struct InflateEffect : Effect {
    char padA[8];
    IEffectCtl ctl;            // +0x0c (embedded interface with its own vptr)
    char pad[0x60 - 0x10];
    IEffectCtl ctl2;           // +0x60
    char pad2[0xb8 - 0x64];
    InflateEffect* Construct();   // 0x0097e690
};
struct FadeEffect : Effect {
    char padA[8];
    IEffectCtl ctl;            // +0x0c
    char pad[0x60 - 0x10];
    FadeEffect* Construct();      // 0x0096f060
};
struct Effect2 {               // 0xa0 bytes
    virtual void AddRef();
    virtual void Release();
    char pad[0xa0 - 4];
    Effect2();                                       // 0x006775f0
    void Setup(IWindow* w, int a, int b);            // 0x00677220
    void Apply(int a, Key3* k, int b);               // 0x00677700
};
struct AssetData {
    virtual void p0();
    virtual void Init(KeyPtr* k);
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8();
    virtual int Check();
    virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46();
    virtual void SetFlag(int a);
    virtual void SetKind(uint32_t k);
    struct RefIface { virtual void AddRef(); virtual void Release(); };
    char pad[0xc];
    RefIface ref;              // +0x10
    char pad2[0xb0 - 0x14];
    AssetData();               // 0x00dd0ca0 / 0x00dd0da0
};
struct AssetDataRef {
    AssetData* p;
    void Assign(AssetData* d);   // 0x006428c0
};
struct AssetView {
    virtual void AddRef();
    virtual void Release();
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6();
    virtual void Init(IWindow* w, AssetData* d, int a, int b);
    virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11();
    virtual void Fn(int a, int b);
    char pad[0x28 - 4];
    IWindow* sub;              // +0x28
    AssetView();               // 0x00657f70
};
struct DataHelper {
    void Fn5950(void* mgr, void* entry, int idx);   // 0x005e5950
};
struct VerbIconData {
    virtual void AddRef();
    virtual void Release();
    virtual void p2();
    virtual DataHelper* Get(uint32_t k);
    virtual void Set(IPropList* p);
    char pad[0xa8 - 4];
    Key3 key;                  // +0xa8
    VerbIconData();            // 0x005e5b60
};
struct Rollover { void SetVisibility(uint32_t a, int b); };            // 0x006052c0
struct VerbIcon {
    virtual void AddRef();
    virtual void Release();
    virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6();
    virtual void Init(IWindow* w, Key3 key, VerbIconData* d, int a, int b, uint32_t c, int d2, int e);
    VerbIcon();                // 0x005e2000
    IWindow* GetIconWindow();  // 0x007f54d0
    float Fn2910(int a);       // 0x005e2910
    Rollover* Fn2cb0();        // 0x005e2cb0
};
struct ResObj {
    const wchar_t* Fn0880();   // 0x00550880
    const wchar_t* Fn4e10();   // 0x00414e10
};
struct IResult {
    virtual void AddRef();
    virtual void Release();
    virtual void p2();
    virtual ResObj* Find(uint32_t id);
};
struct IResMan {
    virtual void p0(); virtual void p1(); virtual void p2();
    virtual bool Get(Key3* k, AutoRef<IResult>* out, int a, int b, int c, int d);
};
struct cString {
    uint32_t b[4];
    cString();                 // 0x006b5060
    ~cString();                // 0x006b5240
    const wchar_t* GetText();  // 0x006b55c0
};

template <class T> struct RefVec {
    T** begin; T** end; T** cap;
    void DoInsertValue(T** pos, T** val);
    void push(T*& v) {
        T** e = end;
        if (e < cap) { end = e + 1; if (e) { *e = v; if (v) v->AddRef(); } }
        else DoInsertValue(e, &v);
    }
};
struct V3Vec {
    V3* begin; V3* end; V3* cap;
    V3* Erase(V3* a, V3* b);                 // 0x009e0480
    void DoInsertValue(V3* pos, V3* v);      // 0x004b5ad0
};

struct OwnerInfo {
    char pad[0x2c];
    uint32_t colA;     // +0x2c
    uint32_t colB;     // +0x30
    char pad2[0x64 - 0x34];
    uint32_t resKey;   // +0x64
    uint32_t imgBase;  // +0x68
};
struct Owner { char pad[0xc]; OwnerInfo* info; };

struct cEditorVerbIconPanel;
struct UIMgr {
    char pad[0x48];
    void* f48;
    uint32_t GetModeId();                       // 0x00e3b5d0
    bool IsReady(cEditorVerbIconPanel* p);      // 0x00e3cf60
    const uint32_t* GetColor(int n);            // 0x00e36fb0
    void SetImage(IWindow* w, Key3* k);         // 0x00e3b2a0
    void* FindParent(uint32_t id);              // 0x00e40670
};
struct SpeciesEntry { char pad[0x130]; IPropList* props; };
struct SpeciesMgr { char pad[0x6d4]; SpeciesEntry** begin; SpeciesEntry** end; };
struct SpeciesRoot { SpeciesMgr* Get(); };     // 0x004df550
struct DT { void Set(int a); };                // 0x0092e3d0
struct TLocal : DT { uint32_t dt2[2]; void* arr; void* e; void* c; };

UIMgr* GetUIMgr();                                                  // 0x00b3d410
IPropMgr* PropertyManager();                                        // 0x0067de30
IResMan* GetManager();                                              // 0x0067dcd0
bool GetArrayKeys(IPropList* p, uint32_t id, int* count, Key3** keys);   // 0x006a0ae0
bool TryGetUIntProperty(IPropList* p, uint32_t id, uint32_t* out);  // 0x00410370
bool GetPropertyAsText(IPropList* p, uint32_t id, cString* s);      // 0x006a1360
bool GetPropertyAsKeyInstance(IPropList* p, uint32_t id, uint32_t* out);  // 0x006a12a0
bool GetPropertyAsKey(IPropList* p, uint32_t id, Key3* out);        // 0x006a1250
bool GetPropertyAsColorRGB(IPropList* p, uint32_t id, V3* out);     // 0x006a11b0
void SetNumberString(int64_t v, wchar_t* buf, int n);               // 0x00881ae0
void SetWindowImage(IWindow* w, Key3* k, int a);                    // 0x00807bb0
void SetWindowScale(IWindow* w, float s);                           // 0x00808210
void SetImageFromLayout(IWindow* w, cSPUILayout* l, uint32_t id, int a);   // 0x00806a60
uint32_t ColorFromId(uint32_t id);                                  // 0x00b6f0d0
SpeciesRoot* GetSpeciesRoot(KeyPtr* k);                             // 0x00401090
void FillTimelineData(Owner* o, TLocal* t, uint32_t inst, IPropList* p);  // 0x00e45e90
void FillKey(Owner* o, int a, Key3* k);                             // 0x00e39420
void* GetAlloc();                                                   // 0x009512c0
void* EAAlloc(unsigned int size, int align, const char* name, void* alloc);   // 0x009512d0
extern wchar_t* g_015a5b30;
extern wchar_t* g_015a5b50;

struct cEditorVerbIconPanel {
    char pad0[0xc];
    AutoRef<cSPUILayout> mLayout;       // +0x0c
    AutoRef<cSPUILayout> mLayoutB;      // +0x10
    AutoRef<cSPUILayout> mLayoutA;      // +0x14
    char pad18[4];
    uint32_t mParentId;                 // +0x1c
    AutoRef<IWindow> mWinIcon;          // +0x20
    AutoRef<IWindow> mWinText;          // +0x24
    RefVec<IWindow> mWindows;           // +0x28
    char pad34[8];
    RefVec<Effect2> mEffects;           // +0x3c
    char pad48[8];
    V3Vec mColors;                      // +0x50
    char pad5c[8];
    AutoRef<IPropList> mProps;          // +0x64
    uint32_t mId;                       // +0x68
    char pad6c[4];
    float mW;                           // +0x70
    float mH;                           // +0x74
    char pad78[0x10];
    const wchar_t* mCaption;            // +0x88
    char pad8c[0xc];
    AutoRef<AssetView> mView;           // +0x98
    AssetDataRef mData;                 // +0x9c
    AutoRef<VerbIconData> mIconData;    // +0xa0
    AutoRef<VerbIcon> mIcon;            // +0xa4
    Owner* mOwner;                      // +0xa8
    char padac[0x28];
    int mCountA;                        // +0xd4
    int mCountB;                        // +0xd8
    char paddc[8];
    uint32_t mE4;                       // +0xe4
    uint32_t mE8;                       // +0xe8
    char padec[4];
    uint32_t mF0;                       // +0xf0

    void RefreshUI();                   // 0x00e47930
    void Fn7100(KeyPtr* k);             // 0x00e47100
};

// @ 0x00e47930
void cEditorVerbIconPanel::RefreshUI()
{
    if (!mLayout.p) return;

    mWinIcon.Set(mLayout.p->FindWindowByID(0x94e2c6d2, 1));
    if (mWinIcon.p) {
        mWinIcon.p->AddWinProc((IWinProc*)this);
        mWinIcon.p->SetFlag(1, false);

        void* al = GetAlloc();
        void* mem = EAAlloc(0xb8, 8, "UI/InflateEffect", al);
        InflateEffect* inflate = mem ? ((InflateEffect*)mem)->Construct() : 0;
        if (inflate) {
            inflate->AddRef();
            IEffectCtl* c = &inflate->ctl;
            c->SetDuration(0.2f);
            c->SetXY(0.5f, 0.5f);
            c->SetB(2);
            c->SetC(15.0f);
            c->SetA(1);
            IEffectCtl* c2 = &inflate->ctl2;
            c2->SetDuration(0.1f);
            IWindow* wi = mWinIcon.p;
            wi->AddWinProc(c->GetWinProc());
        }
        al = GetAlloc();
        mem = EAAlloc(0x60, 8, "UI/FadeEffect", al);
        FadeEffect* fade = mem ? ((FadeEffect*)mem)->Construct() : 0;
        if (fade) {
            fade->AddRef();
            IEffectCtl* c = &fade->ctl;
            c->SetDuration(0.2f);
            c->SetXY(0.0f, 0.0f);
            c->SetB(0);
            c->SetA(1);
            IWindow* wi = mWinIcon.p;
            wi->AddWinProc(c->GetWinProc());
        }
        mWinIcon.p->SetFlag(1, true);
        if (fade) fade->Release();
        if (inflate) inflate->Release();
    }

    mWinText.Set(mLayout.p->FindWindowByID(0x60c6ca8, 1));

    uint32_t sel = 0xffffffff;
    if (mId == 0x99f0d1da || mId == 0xaaf6aaac || mId == 0xdca976d0) {
        uint32_t a = GetUIMgr()->GetModeId();
        if (a != 0xeca9947e) {
            IPropMgr* pm = PropertyManager();
            mProps.Clear();
            pm->Get(a, 0xe1d7164f, &mProps);
            if (a == 0xa7a9e952) {
                if (mF0 == 0xa35d0f5) sel = 0;
                else if (mF0 == 0x3360727f) sel = 2;
                else if (mF0 == 0x6aeb96a1) sel = 1;
            } else if (a == 0x2500e82c) {
                if (mF0 == 0xa35d0f5) sel = 1;
                else if (mF0 == 0x3360727f) sel = 0;
                else if (mF0 == 0x6aeb96a1) sel = 2;
            }
        }
    }

    int count = 0;
    Key3* keys;
    if (GetArrayKeys(mProps.p, 0x65263b4, &count, &keys)) {
        if (mWinIcon.p) mWinIcon.p->SetSize(mH, mW);
        if (sel == 0xffffffff) TryGetUIntProperty(mProps.p, 0x65263c8, &sel);
        mColors.Erase(mColors.begin, mColors.end);
        if (count > 0) {
            uint32_t id = 0x6527160;
            do {
                uint32_t i = id - 0x6527160;
                if (i < 3 && mLayout.p) {
                    IWindow* w = mLayout.p->FindWindowByID(id, 1);
                    if (w) w->SetColor(i != sel ? 0xff737373u : 0xffffffffu);
                }
                IWindow* w2 = mLayout.p->FindWindowByID(id, 1);
                if (w2) w2->AddRef();
                mWindows.push(w2);
                if (w2) w2->Release();

                if (mWindows.begin[i]) {
                    Effect2* e = new ("UI/Effect2", 0, 0, 0, 0) Effect2;
                    e->Setup(mWindows.begin[i], 1, 1);
                    Key3 k = { keys[i].a, 0xb1b104, 0xf865c777 };
                    e->Apply(1, &k, 0);
                    if (e) e->AddRef();
                    mEffects.push(e);
                    if (e) e->Release();
                    if (sel != 0xffffffff) {
                        mWindows.begin[i]->SetFlag(2, false);
                        mWindows.begin[i]->SetFlag(0x10, true);
                    }
                }
                AutoRef<IPropList> pr;
                pr.p = 0;
                IPropMgr* pm = PropertyManager();
                pr.Clear();
                if (pm->Get(keys[i].a, 0xf865c777, &pr)) {
                    V3 col;
                    if (GetPropertyAsColorRGB(pr.p, 0xd4f639cd, &col)) {
                        V3* e = mColors.end;
                        if (e < mColors.cap) {
                            mColors.end = e + 1;
                            if (e) { e->x = col.x; e->y = col.y; e->z = col.z; }
                        } else {
                            mColors.DoInsertValue(e, &col);
                        }
                    }
                }
                if (pr.p) pr.p->Release();
            } while ((int)(++id - 0x6527160) < count);
        }
        } else {
        if (GetUIMgr()->IsReady(this)) {
            if (mWinText.p) {
                cString s;
                if (GetPropertyAsText(mProps.p, 0x60b3e8e, &s))
                    mWinText.p->SetCaption(s.GetText());
            }
            IWindow* w = mLayout.p->FindWindowByID(0x34f77eef, 1);
            if (w) {
                if (mCountA > 1 || mCountB >= 1) {
                    w->SetFlag(1, true);
                    int n = mCountB;
                    if (n < 1) n = mCountA;
                    if (n == 0) {
                        w->SetCaption(L"");
                    } else {
                        wchar_t buf[64];
                        SetNumberString((int64_t)n, buf, 0x40);
                        w->SetCaption(buf);
                    }
                } else {
                    w->SetCaption(L"");
                }
            }
            w = mLayout.p->FindWindowByID(0x1562b7e4, 1);
            if (w) w->SetColor(ColorFromId(mOwner->info->colA));
            w = mLayout.p->FindWindowByID(0x15302964, 1);
            if (w) w->SetColor(ColorFromId(mOwner->info->colB));

            uint32_t inst = 0;
            if (GetPropertyAsKeyInstance(mProps.p, 0x60b3e90, &inst)) {
                uint32_t col[3];
                col[0] = col[1] = col[2] = 0;
                int n = -1;
                switch (inst) {
                case 0x78f7bdcd: n = 0; break;
                case 0x251b2c0: n = 5; break;
                case 0x25a7ca68: n = 1; break;
                case 0x2b022d18: n = 2; break;
                case 0x86a510bc: n = 3; break;
                case 0xe50a3d1a: n = 6; break;
                case 0xf2451b0b: n = 4; break;
                }
                if (n >= 0) {
                    const uint32_t* c = GetUIMgr()->GetColor(n);
                    col[0] = c[0]; col[1] = c[1]; col[2] = c[2];
                }
                IWindow* iw = mLayout.p->FindWindowByID(0x60c6db0, 1);
                if (iw) {
                    iw->SetFlag(1, col[0] != 0);
                    SetWindowImage(iw, (Key3*)col, -1);
                }
            }
        }
        Key3 k = { 0, 0, 0 };
        if (GetPropertyAsKey(mProps.p, 0x60b3e8d, &k)) {
            IWindow* w = mLayout.p->FindWindowByID(0x60c6db8, 1);
            GetUIMgr()->SetImage(w, &k);
        }
    }

    // Property-driven visibility flags.
    if (mProps.p) {
        Prop* pp;
        if (mProps.p->GetProperty(0x60def8e, &pp) && pp->type == 1) {
            char* v = (char*)pp;
            if (pp->flags & 0x30) v = *(char**)pp;
            bool b = *v != 0;
            IWindow* w = mLayout.p->FindWindowByID(0x60df097, 1);
            if (w) w->SetFlag(1, b);
        }
    }
    if (mProps.p) {
        Prop* pp;
        if (mProps.p->GetProperty(0x60def8f, &pp) && pp->type == 1) {
            char* v = (char*)pp;
            if (pp->flags & 0x30) v = *(char**)pp;
            bool b = *v != 0;
            IWindow* w = mLayout.p->FindWindowByID(0x60df098, 1);
            if (w) w->SetFlag(1, b);
        }
    }

    // Dialog layouts.
    if (GetUIMgr()) {
        bool doParent = false;
        if (mE8 == 0x976f6445 || mE8 == 0xb0ef13a6) {
            cSPUILayout* l = new ("UI/Layout", 0, 0, 0, 0) cSPUILayout;
            mLayoutA.Set(l);
            Key3 k;
            k.a = (mE8 != 0x976f6445 ? 0x878404b0u : 0u) + 0x429ae500u;
            k.b = 0x510a95b;
            k.c = (uint32_t)g_015a5b30;
            mLayoutA.p->Init(&k, 1, 0x5b598fa);
            mLayoutA.p->SetParentWin(GetUIMgr()->f48, 1, 0x5b598fa);
            IWindow* w = mLayoutA.p->FindWindowByID(0x755431d4, 1);
            if (w) w->SetCaption(mCaption);
            doParent = true;
        } else if (mE8 == 0xc0764a83) {
            doParent = true;
        }
        if (doParent) {
            void* parent = GetUIMgr()->FindParent(mParentId);
            if (parent) {
                cSPUILayout* l = new ("UI/Layout", 0, 0, 0, 0) cSPUILayout;
                mLayoutB.Set(l);
                Key3 k;
                k.a = 0x88d8120c;
                k.b = 0x510a95b;
                k.c = (uint32_t)g_015a5b30;
                mLayoutB.p->Init(&k, 1, 0x5b598fa);
                mLayoutB.p->SetParentWin(parent, 1, 0x5b598fa);
            }
        }
    }

    // Timeline / sporepedia data.
    uint32_t inst2 = 0;
    if (GetPropertyAsKeyInstance(mProps.p, 0x608db3f, &inst2)) {
        TLocal tl;
        tl.Set(2);
        tl.arr = 0; tl.e = 0; tl.c = 0;
        FillTimelineData(mOwner, &tl, inst2, mProps.p);
        KeyPtr kp = { 0, 0, 0, &tl };
        if (inst2 == 0x94995d55 || inst2 == 0x1e73d4fa) {
            AssetData* d = new ("UI/TimelineEventSporepediaData", 0, 0, 0, 0) AssetData;
            AssetData* o = mData.p;
            if (d != o) {
                if (d) d->ref.AddRef();
                mData.p = d;
                if (o) o->ref.Release();
            }
        } else {
            AssetData* d = new ("UI/TimelineEventSporepediaData", 0, 0, 0, 0) AssetData;
            mData.Assign(d);
        }
        AssetData* data = mData.p;
        data->Init(&kp);
        data->SetFlag(1);
        if (!data->Check()) {
            uint32_t v = 0;
            switch (mE4) {
            case 0xbeb528cb: v = 0xccc35c46; break;
            case 0xa426730b: v = 0xdfad9f51; break;
            case 0xad56080c: v = 0x9ea3031a; break;
            case 0xf71fa311: v = 0x372e2c04; break;
            case 0x2db6dad3: v = 0x65672ade; break;
            }
            data->SetKind(v);
        }
        IWindow* w = mLayout.p->FindWindowByID(0x608a509, 1);
        if (w) {
            AssetView* view = new ("UI/TimelineEventSporepediaView", 0, 0, 0, 0) AssetView;
            mView.Set(view);
            mView.p->Init(w, mData.p, 0, 0);
            mView.p->Fn(0, 0);
            IWindow* sub = mView.p->sub;
            if (sub) {
                float* r = w->GetRect();
                sub->SetSize(r[2] - r[0], r[3] - r[1]);
            }
        }
        if (tl.arr && ((int*)tl.arr)[-1] != 0) operator delete[](tl.arr);
    }

    // Verb icon (editor / creature).
    if (mId == 0x278e6ca8 || mId == 0x246ba26c) {
        KeyPtr kp = { 0, 0, 0, 0 };
        Key3 kk = { 0, 0, 0 };
        Fn7100(&kp);
        FillKey(mOwner, 0x10, &kk);
        AutoRef<IPropList> pr;
        pr.p = 0;
        IPropMgr* pm = PropertyManager();
        pr.Clear();
        pm->Get(kk.a, kk.c, &pr);
        SpeciesMgr* sm = GetSpeciesRoot(&kp)->Get();
        if (sm) {
            int n = (int)(sm->end - sm->begin);
            if (n > 0) {
                SpeciesEntry** it = sm->begin;
                int i = 0;
                do {
                    if ((*it)->props == pr.p) {
                        VerbIconData* d = new ("UI/TimelineEventEditorVerbIconData", 0, 0, 0, 0) VerbIconData;
                        mIconData.Set(d);
                        DataHelper* h = mIconData.p ? mIconData.p->Get(0x4ac90b5) : 0;
                        h->Fn5950(sm, sm->begin[i], i);
                        break;
                    }
                    i++;
                    it++;
                } while (i < n);
            }
        }
        if (!mIconData.p) {
            VerbIconData* d = new ("UI/TimelineEventEditorVerbIconData", 0, 0, 0, 0) VerbIconData;
            mIconData.Set(d);
            mIconData.p->Set(pr.p);
        }
        if (mIconData.p->key.a != 0) {
            IWindow* w = mLayout.p->FindWindowByID(0x60c6db0, 1);
            if (w) {
                VerbIcon* ic = new ("UI/TimelineEventEditorVerbIcon", 0, 0, 0, 0) VerbIcon;
                mIcon.Set(ic);
                mIcon.p->Init(w, mIconData.p->key, mIconData.p, 0, 1, 0xe816f049, 0, 0);
                IWindow* iw = mIcon.p->GetIconWindow();
                if (iw) {
                    float* r1 = w->GetRect();
                    float* r2 = iw->GetRect();
                    iw->SetPos(((r2[2] - r2[0]) - (r1[2] - r1[0])) * -0.5f,
                               ((r2[3] - r2[1]) - (r1[3] - r1[1])) * -0.5f);
                    float* r = w->GetRect();
                    float h = r[3] - r[1];
                    float q = h / mIcon.p->Fn2910(0);
                    float one = 1.0f;
                    float* ps = &q;
                    if (1.0 <= q) ps = &one;
                    SetWindowScale(w, *ps);
                }
                Rollover* ro = mIcon.p->Fn2cb0();
                if (ro && mId == 0x246ba26c) ro->SetVisibility(0x4d97708, 0);
                IWindow* iw2 = mIcon.p->GetIconWindow();
                if (iw2) {
                    IWindow* x = iw2->FindChild(0x6283c92, true);
                    if (x) x->SetFlag(0x10, true);
                }
            }
        }
        if (pr.p) pr.p->Release();
    }

    IWindow* w7 = mLayout.p->FindWindowByID(0x7f214c0, 1);
    if (w7 && mOwner && mId == 0xbbc2a4ef)
        SetImageFromLayout(w7, mLayout.p, mOwner->info->imgBase + 0x7d21870, -1);

    IWindow* w1 = mLayout.p->FindWindowByID(0x53d6fe2a, 1);
    IWindow* w2 = mLayout.p->FindWindowByID(0x53d6fe30, 1);
    if (w2 && w1 && mOwner && mId == 0x1af2f7b7) {
        Key3 k;
        k.a = mOwner->info->resKey;
        k.b = 0x30bdee3;
        k.c = (uint32_t)g_015a5b50;
        AutoRef<IResult> out;
        out.p = 0;
        IResMan* rm = GetManager();
        out.Clear();
        if (rm->Get(&k, &out, 0, 0, 0, 0)) {
            if (!out.p) return;
            ResObj* o = out.p->Find(0x30bdee3);
            if (o) {
                w1->SetCaption(o->Fn0880());
                w2->SetCaption(o->Fn4e10());
            }
        }
        if (out.p) out.p->Release();
    }
}
// --- equivalence checker address annotations
    void operator delete[](void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct ResObj {
    void Fn4e10(); // 0x00414e10
    void Fn0880(); // 0x00550880
};
struct AssetDataRef {
    void Assign(void*); // 0x006428c0
};
struct DataHelper {
    void Fn5950(void*, void*, int); // 0x005e5950
};
}
