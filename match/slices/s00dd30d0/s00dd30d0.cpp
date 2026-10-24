// s00dd30d0 -- SP::cSPUICommScreen (the comm-screen window) plus its helper
// methods.  Reconstructed from the retail disassembly alone
// (work/match/scratch_s00dd30d0_cards.txt).  The dev-PDB headers under
// src/game/include/SP do NOT describe this build, so every member offset below
// comes from the observed code, not from a header.
//
//   0x00dd30d0  cSPUICommScreen::Hide                 thiscall
//   0x00dd32a0  cSPUICommScreen::LayoutCommButtons    thiscall
//   0x00dd35c0  cSPUICommScreen::SetCivilizationInfo  thiscall, 1 arg (ret 4)
//   0x00dd3810  cSPUICommScreen::SetCityInfoForWindow thiscall, 1 arg (ret 4)
//   0x00dd3a00  cSPUICommScreen::SetSourceAndTarget   thiscall, 2 args (ret 8)
//   0x00dd3b60  cSPUICommScreen::~cSPUICommScreen     virtual destructor
//   0x00dd3d30  cSPUICommScreen::Shutdown             thiscall

#include <intrin.h>   // _ReadWriteBarrier (scheduling barrier, emits no code)

struct Vector4 { float x, y, z, w; };
struct cRGB    { unsigned char r, g, b, a; };

class cUIWindow;
class cCity;
class cSPUILayout;

// ---------------------------------------------------------------------------
// the generic UI object: only the vtable slots this slice exercises are named
// ---------------------------------------------------------------------------
class cUIWindow {
public:
    virtual void v00();                                          // +0x00
    virtual void Release();                                      // +0x04
    virtual void FUN_0008(int flag);                             // +0x08
    virtual void* FUN_000c(unsigned int id);                     // +0x0c
    virtual cUIWindow* v10();                                    // +0x10
    virtual void v14(int v);                                     // +0x14
    virtual void v18();                                          // +0x18
    virtual void v1c();                                          // +0x1c
    virtual void v20();                                          // +0x20
    virtual void v24();                                          // +0x24
    virtual void v28();                                          // +0x28
    virtual bool FUN_002c(unsigned int id, int arg, void* out);  // +0x2c
    virtual void v30();                                          // +0x30
    virtual const Vector4* GetPos();                             // +0x34
    virtual void v38();                                          // +0x38
    virtual void v3c();                                          // +0x3c
    virtual void v40();                                          // +0x40
    virtual void FUN_0044();                                     // +0x44
    virtual void v48();                                          // +0x48
    virtual void v4c();                                          // +0x4c
    virtual void v50();                                          // +0x50
    virtual void v54();                                          // +0x54
    virtual void v58();                                          // +0x58
    virtual void FUN_005c(unsigned int v);                       // +0x5c
    virtual void SetPos(const Vector4* p);                       // +0x60
    virtual void SetSub(float a, float b);                       // +0x64
    virtual void v68();                                          // +0x68
    virtual void v6c();                                          // +0x6c
    virtual void v70();                                          // +0x70
    virtual void v74();                                          // +0x74
    virtual void v78();                                          // +0x78
    virtual void SetState(int a, bool b);                        // +0x7c
    virtual void SetText(const void* text);                      // +0x80
    virtual void v84();                                          // +0x84
    virtual void v88();                                          // +0x88
    virtual void v8c();                                          // +0x8c
    virtual void v90();                                          // +0x90
    virtual void v94();                                          // +0x94
    virtual void v98();                                          // +0x98
    virtual void v9c();                                          // +0x9c
    virtual void vA0();                                          // +0xa0
    virtual void vA4();                                          // +0xa4
    virtual void vA8();                                          // +0xa8
    virtual void FUN_00ac(unsigned int color);                   // +0xac
    virtual void vB0();                                          // +0xb0
    virtual void vB4();                                          // +0xb4
    virtual void vB8();                                          // +0xb8
    virtual void vBC();                                          // +0xbc
    virtual void vC0();                                          // +0xc0
    virtual void vC4();                                          // +0xc4
    virtual void vC8();                                          // +0xc8
    virtual void vCC();                                          // +0xcc
    virtual void vD0();                                          // +0xd0
    virtual void vD4();                                          // +0xd4
    virtual void vD8();                                          // +0xd8
    virtual void vDC();                                          // +0xdc
    virtual void vE0();                                          // +0xe0
    virtual void vE4();                                          // +0xe4
    virtual void vE8();                                          // +0xe8
    virtual void vEC();                                          // +0xec
    virtual cUIWindow* vF0(unsigned int id, int flag);           // +0xf0

    void SetCardsVisibility(bool flag);                          // 0x00e14c10
    void FUN_00e2f270();                                         // 0x00e2f270
    void clear();                                                // 0x007b1950
};

// the layout object: its +0x08 slot (the release/detach hook) takes no argument
// (unlike the cUIWindow +0x08 slot), so it is declared as a standalone type
class cSPUILayout {
public:
    virtual void v00();                                          // +0x00
    virtual void Release();                                      // +0x04
    virtual void FUN_0008();                                     // +0x08

    cUIWindow* FindWindowByID(unsigned int id, int flag);        // 0x008105b0
    bool       SetParentWin(cUIWindow* w, bool flag, int id);    // 0x008121b0
    void       Shutdown(unsigned int flag);                      // 0x00811ad0
};

class cUIWindowFinder {
public:
    cUIWindow* FindWindowByID(unsigned int id);                  // 0x00e012b0
};

// ---------------------------------------------------------------------------
// the intrusive list kept at this+0x34 (head has only the two link pointers)
// ---------------------------------------------------------------------------
struct cListNode {
    cListNode* mpNext;      // +0x00
    cListNode* mpPrev;      // +0x04
    cUIWindow* mpObj;       // +0x08
};

class cUIList {
public:
    void erase();                                            // 0x0075f3f0
    cListNode* mpNext;                                       // +0x34
    cListNode* mpPrev;                                       // +0x38
};

// ---------------------------------------------------------------------------
// a string with only the widely used destructor body (six live at +0x44..+0xa8)
// ---------------------------------------------------------------------------
class cString {
public:
    void Destroy();                                          // 0x006b5240
    unsigned char mData[0x14];
};

class cUIHints {
public:
    void SetFlag(char flag, int value);                      // 0x0067c420
};

// a reference-counted window pointer; the +0x08 slot of cUIWindow takes no
// argument here so the layout object is kept as its own standalone type
class cUIWindowPtr {
public:
    cUIWindowPtr() { mPtr = 0; }
    ~cUIWindowPtr() { if (mPtr != 0) mPtr->Release(); }
    cUIWindow** GetPtrRef()
    {
        if (mPtr != 0) {
            cUIWindow* p = mPtr;
            mPtr = 0;
            p->Release();
        }
        return &mPtr;
    }
    cUIWindow* mPtr;                                         // +0x00
};

// ---------------------------------------------------------------------------
// red-black tree used by cCity at +0x44
// ---------------------------------------------------------------------------
struct cRBNode {
    unsigned char mPad00[0x14];
    unsigned int  mValue;                                    // +0x14
};

// the red-black-tree lookup: it reads its key and writes the resulting node
// through the same 4-byte scratch word (retail keeps exactly one stack slot)
class cRBTree {
public:
    cRBNode** find(cRBNode** pOut, const unsigned int& key);   // 0x00e5c780
};

class cCity {
public:
    int  FUN_00bf0f40();                                     // 0x00bf0f40
    int  FUN_00bf1e20();                                     // 0x00bf1e20
    const cRGB* FUN_00bd99e0();                              // 0x00bd99e0
    cCity* GetCivilization();                                // 0x00bd9bf0

    unsigned char mPad00[0x44];
    cRBTree       mTree44;                                   // +0x44
    unsigned char mPad48[0xc4 - 0x48];
    cRGB          mColorC4;                                  // +0xc4
};

// ---------------------------------------------------------------------------
// global-UI accessor / finder chain used by the space-mode branch
// ---------------------------------------------------------------------------
class cGlobalUI {
public:
    void FUN_01068300();                                     // 0x01068300
    unsigned char mPad00[0x224];
    cUIWindowFinder* mpFinder224;                            // +0x224
};

// ---------------------------------------------------------------------------
// EA::Messaging server dispatch
// ---------------------------------------------------------------------------
class cMsgServer {
public:
    virtual void v00();                                      // +0x00
    virtual void v04();                                      // +0x04
    virtual void v08();                                      // +0x08
    virtual void v0c();                                      // +0x0c
    virtual void v10();                                      // +0x10
    virtual void vf14(unsigned int id, const void* msg, int flags);   // +0x14
};

class IMessageRC {
public:
    IMessageRC() {}
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    void Dummy();
};

struct MsgData { unsigned int mValue; unsigned int mPad04; };

class MsgBasicRC5 : public IMessageRC {
public:
    MsgBasicRC5() : mRefCount(0), mId(0) {}

    volatile int  mRefCount;                                 // +0x04
    MsgData       mData[5];                                  // +0x08
    unsigned int  mId;                                       // +0x30
    unsigned int  mPad34;                                    // +0x34
    unsigned int  mRCFlags;                                  // +0x38
    unsigned int  mPad3c;                                    // +0x3c

    void Destruct();                                         // 0x00421cf0
};

// ---------------------------------------------------------------------------
// the screen itself: ITracerBase / cPaintSystem are the two polymorphic bases
// (their vptrs are the two 4-byte words at +0x00 and +0x04)
// ---------------------------------------------------------------------------
class ITracerBase {
public:
    virtual ~ITracerBase() {}
    virtual void v04() {}
};

class cPaintSystem {
public:
    virtual ~cPaintSystem() {}
    virtual void v04() {}
};

class cSPUICommScreen : public ITracerBase, public cPaintSystem {
public:
    virtual ~cSPUICommScreen();

    void Hide();                                             // 0x00dd30d0
    void LayoutCommButtons();                                // 0x00dd32a0
    void SetCivilizationInfo(cCity* city);                   // 0x00dd35c0
    void SetCityInfoForWindow(cCity* city);                  // 0x00dd3810
    void SetSourceAndTarget(cUIWindow* source, cCity* target);  // 0x00dd3a00
    void Shutdown();                                         // 0x00dd3d30

    void FUN_00dd2a10();                                     // 0x00dd2a10
    int  FUN_00dd1ce0(int a, int b);                         // 0x00dd1ce0
    void FUN_00dd2240(cUIWindow* w, cCity* city);            // 0x00dd2240
    int  FUN_00dd2d30();                                     // 0x00dd2d30

    __forceinline void SendSlotMessage(unsigned int id, void* value);

    cCity*        mpCity;          // +0x08
    cSPUILayout*  mpLayout;        // +0x0c
    cUIWindow*    mp10;            // +0x10
    cUIWindow*    mp14;            // +0x14
    cUIWindow*    mp18;            // +0x18
    cUIWindow*    mp1c;            // +0x1c
    cUIWindow*    mp20;            // +0x20
    cUIWindow*    mp24;            // +0x24
    cUIWindow*    mp28;            // +0x28
    cUIWindow*    mp2c;            // +0x2c
    cUIWindow*    mp30;            // +0x30
    cUIList       mList;           // +0x34
    unsigned char mPad3c[4];       // +0x3c
    unsigned char mbShown40;       // +0x40
    unsigned char mPad41[3];       // +0x41
    cString       mStr44;          // +0x44
    cString       mStr58;          // +0x58
    cString       mStr6c;          // +0x6c
    cString       mStr80;          // +0x80
    cString       mStr94;          // +0x94
    cString       mStrA8;          // +0xa8
    cUIWindow*    mpBc;            // +0xbc
    cUIWindow*    mpC0;            // +0xc0
    int           mHandlerC4;      // +0xc4
    int           mHandlerC8;      // +0xc8
    int           mHandlerCc;      // +0xcc
    int           mHandlerD0;      // +0xd0
    int           mHandlerD4;      // +0xd4
    int           mHandlerD8;      // +0xd8
    int           mHandlerDc;      // +0xdc
    int           mHandlerE0;      // +0xe0
    int           mHandlerE4;      // +0xe4
    int           mHandlerE8;      // +0xe8
    unsigned short* mpArrayEc;     // +0xec
    unsigned short* mpArrayF0;     // +0xf0
    unsigned short* mpArrayF4;     // +0xf4
};

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------
extern char g_01654c05;

void*        GetCurrentGameMode();                          // 0x00b5b800
cUIHints*    FUN_0067cac0();                                // 0x0067cac0
cGlobalUI*   FUN_010666a0();                                // 0x010666a0
cUIWindow*   FUN_00b3d400();                                // 0x00b3d400
cUIWindow*   __stdcall FUN_00b3d4f0(int flag);              // 0x00b3d4f0
cUIWindow*   FUN_0067ddc0();                                // 0x0067ddc0
cUIWindow*   EffectsManager();                              // 0x0067ddd0
cMsgServer*  GetMessagingServer();                          // 0x00883860
int          FUN_00bef920(int v);                           // 0x00bef920
void         FUN_00807690(void* obj, int flag);             // 0x00807690
void         FUN_008076f0(void* obj);                       // 0x008076f0
void         SetImageFromKey(cUIWindow* w, int key);        // 0x00e2f5c0
unsigned int ColorRGBToU32(const void* color);              // 0x00458a40
void         FUN_00f47380(void* p);                         // 0x00f47380
void         EA_Messaging_RemoveHandler(int id, int a, int b, int c, int d);  // 0x00571db0
void         cUIWindow_clear(cUIWindow* w);                 // 0x007b1950

extern float kEighteen;                                     // 0x013ebc68  18.0f
extern float kTwo;                                          // 0x01470f1c   2.0f

#if 0
void cUIWindow::v00() {}
void cUIWindow::Release() {}
void cUIWindow::FUN_0008(int) {}
void* cUIWindow::FUN_000c(unsigned int) { return 0; }
cUIWindow* cUIWindow::v10() { return 0; }
void cUIWindow::v14(int) {}
void cUIWindow::v18() {}
void cUIWindow::v1c() {}
void cUIWindow::v20() {}
void cUIWindow::v24() {}
void cUIWindow::v28() {}
bool cUIWindow::FUN_002c(unsigned int, int, void*) { return false; }
void cUIWindow::v30() {}
const Vector4* cUIWindow::GetPos() { return 0; }
void cUIWindow::v38() {}
void cUIWindow::v3c() {}
void cUIWindow::v40() {}
void cUIWindow::FUN_0044() {}
void cUIWindow::v48() {}
void cUIWindow::v4c() {}
void cUIWindow::v50() {}
void cUIWindow::v54() {}
void cUIWindow::v58() {}
void cUIWindow::FUN_005c(unsigned int) {}
void cUIWindow::SetPos(const Vector4*) {}
void cUIWindow::SetSub(float, float) {}
void cUIWindow::v68() {}
void cUIWindow::v6c() {}
void cUIWindow::v70() {}
void cUIWindow::v74() {}
void cUIWindow::v78() {}
void cUIWindow::SetState(int, bool) {}
void cUIWindow::SetText(const void*) {}
void cUIWindow::v84() {}
void cUIWindow::v88() {}
void cUIWindow::v8c() {}
void cUIWindow::v90() {}
void cUIWindow::v94() {}
void cUIWindow::v98() {}
void cUIWindow::v9c() {}
void cUIWindow::vA0() {}
void cUIWindow::vA4() {}
void cUIWindow::vA8() {}
void cUIWindow::FUN_00ac(unsigned int) {}
void cUIWindow::vB0() {}
void cUIWindow::vB4() {}
void cUIWindow::vB8() {}
void cUIWindow::vBC() {}
void cUIWindow::vC0() {}
void cUIWindow::vC4() {}
void cUIWindow::vC8() {}
void cUIWindow::vCC() {}
void cUIWindow::vD0() {}
void cUIWindow::vD4() {}
void cUIWindow::vD8() {}
void cUIWindow::vDC() {}
void cUIWindow::vE0() {}
void cUIWindow::vE4() {}
void cUIWindow::vE8() {}
void cUIWindow::vEC() {}
cUIWindow* cUIWindow::vF0(unsigned int, int) { return 0; }
void cUIWindow::SetCardsVisibility(bool) {}
void cUIWindow::FUN_00e2f270() {}
void cUIWindow::clear() {}

void cSPUILayout::v00() {}
void cSPUILayout::Release() {}
void cSPUILayout::FUN_0008() {}

IMessageRC::~IMessageRC() {}
void IMessageRC::v04() {}
void IMessageRC::v08() {}
void IMessageRC::v0c() {}
void MsgBasicRC5::Destruct() {}
#endif

// ---------------------------------------------------------------------------
// @ 0x00dd30d0
void cSPUICommScreen::Hide()
{
    if (mbShown40 != 0) {
        FUN_0067cac0()->SetFlag(1, 1);

        if (GetCurrentGameMode() == &g_01654c05) {
            FUN_010666a0()->FUN_01068300();
        }

        if (FUN_00b3d400() != 0) {
            FUN_00b3d400()->SetCardsVisibility(true);
        }

        FUN_00b3d4f0(0)->FUN_00e2f270();

        mpCity = 0;

        cUIWindow* w = mpLayout->FindWindowByID(0x5e4e5f8, 1);
        if (w != 0) w->SetState(1, 0);
        w = mpLayout->FindWindowByID(0x5e4e5f0, 1);
        if (w != 0) w->SetState(1, 0);
        w = mpLayout->FindWindowByID(0x6429c80, 1);
        if (w != 0) w->SetState(1, 0);

        if (GetCurrentGameMode() == &g_01654c05) {
            cUIWindow* g = FUN_010666a0()->mpFinder224->FindWindowByID(0x64e7368);
            if (g != 0) g->v10()->SetState(1, 0);
        }

        w = mpLayout->FindWindowByID(0x1c3bb0c, 1);
        if (w != 0) {
            mbShown40 = 0;
            w->SetState(1, 0);

            if (mp2c != 0) {
                mp2c->FUN_000c(1);
                if (mp2c != 0) {
                    cUIWindow* old = mp2c;
                    mp2c = 0;
                    old->Release();
                }
            }

            if (mp10 != 0) {
                mp10->FUN_000c(0);
                if (mp10 != 0) {
                    cUIWindow* old = mp10;
                    mp10 = 0;
                    old->Release();
                }
            }

            FUN_0067ddc0()->FUN_0044();

            FUN_00dd2a10();

            cUIWindowPtr effect;
            cUIWindow* mgr = EffectsManager();
            if (mgr->FUN_002c(0x3d6f60f, 0, effect.GetPtrRef())) {
                effect.mPtr->FUN_0008(0);
            }
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00dd32a0
void cSPUICommScreen::LayoutCommButtons()
{
    const Vector4* pa = mp18->GetPos();
    float ax = pa->x;
    float az = pa->z;
    const Vector4* pb = mp24->GetPos();
    Vector4 v;
    v.x = pb->x;
    v.y = pb->y;
    v.w = pb->w;
    float dz = az - ax;
    v.z = dz + pb->x;
    mp24->SetPos(&v);
    mp24->SetSub(0.0f, 0.0f);

    cListNode* head = (cListNode*)&mList;
    float total = 0.0f;
    for (cListNode* e = head->mpNext; e != head; e = e->mpNext) {
        cUIWindow* obj = e->mpObj;
        cUIWindow* inner = obj->v10();
        Vector4 w;
        w.x = 0.0f;
        w.y = 0.0f;
        w.z = dz;
        w.w = 18.0f;
        inner->SetPos(&w);
        obj->v14(1);
        const Vector4* ip = inner->GetPos();
        total += (ip->w - ip->y) + 2.0f;
    }

    v.w = v.y + total;
    mp24->SetPos(&v);
    mp24->SetSub(0.0f, 0.0f);
    FUN_00807690(mp14, 1);

    const Vector4* pi = mp18->GetPos();
    v.z = (pi->z - pi->x) + v.x;
    total = 0.0f;
    for (cListNode* e = head->mpNext; e != head; e = e->mpNext) {
        cUIWindow* obj = e->mpObj;
        cUIWindow* inner = obj->v10();
        const Vector4* ip = inner->GetPos();
        Vector4 w;
        w.x = ip->x;
        w.y = ip->y;
        w.w = ip->w;
        w.z = (v.z - v.x) + ip->x;
        inner->SetPos(&w);
        inner->SetSub(0.0f, total);
        obj->v14(1);
        const Vector4* iq = inner->GetPos();
        w.x = iq->x;
        w.y = iq->y;
        w.w = iq->w;
        w.z = (v.z - v.x) + iq->x;
        inner->SetPos(&w);
        total += (w.w - w.y) + 2.0f;
    }

    v.w = v.y + total;
    mp24->SetPos(&v);
    mp24->SetSub(0.0f, 0.0f);
    FUN_00807690(mp14, 1);
    FUN_00dd2d30();
}

// ---------------------------------------------------------------------------
// @ 0x00dd35c0
void cSPUICommScreen::SetCivilizationInfo(cCity* city)
{
    mpCity = city;

    mpLayout->FindWindowByID(0x5dff098, 1)->SetState(1, 0);
    mpLayout->FindWindowByID(0x5e4f778, 1)->SetState(1, 0);
    mpLayout->FindWindowByID(0x5e4f788, 1)->SetState(1, 0);
    mpLayout->FindWindowByID(0x5e4f770, 1)->SetState(1, 0);

    cUIWindow* main = mpLayout->FindWindowByID(0x4501222, 1)->v10();
    cUIWindow* panel = main->vF0(0x49382e8, 1);
    cUIWindow* img = mpLayout->FindWindowByID(0x5edff88, 1);

    SetImageFromKey(img, FUN_00dd1ce0(FUN_00bef920(city->FUN_00bf0f40()),
                                      city->FUN_00bf1e20()));

    cUIWindow* colorWin = mpLayout->FindWindowByID(0x6243260, 1);
    if (colorWin != 0) {
        colorWin->FUN_00ac(ColorRGBToU32(&city->mColorC4));
    }

    panel->SetState(1, 1);

    union { unsigned int mKey; cRBNode* mpNode; } scratch;
    scratch.mKey = 1;
    cRBNode** res = city->mTree44.find(&scratch.mpNode, scratch.mKey);
    panel->SetText((const void*)(*res)->mValue);

    main->vF0(0x2cf324c, 1)->FUN_005c(ColorRGBToU32(&city->mColorC4));

    int tier = FUN_00bef920(city->FUN_00bf0f40());
    main->vF0(0x2cf2f30, 1)->SetState(1, tier == 2);
    main->vF0(0x2cf2f34, 1)->SetState(1, tier == 1);
    main->vF0(0x2cf2f38, 1)->SetState(1, tier == 0);

    FUN_00dd2240(mpLayout->FindWindowByID(0x4a4504f, 1), city);
}

// ---------------------------------------------------------------------------
// @ 0x00dd3810
void cSPUICommScreen::SetCityInfoForWindow(cCity* city)
{
    cUIWindow* main = mpLayout->FindWindowByID(0x4501222, 1)->v10();
    cUIWindow* img  = mpLayout->FindWindowByID(0x5edff88, 1);

    bool shown = (city != 0);
    img->SetState(1, shown);

    if (city != 0) {
        cCity* civ = city->GetCivilization();
        mpCity = civ;

        SetImageFromKey(img, FUN_00dd1ce0(FUN_00bef920(civ->FUN_00bf0f40()),
                                          civ->FUN_00bf1e20()));

        cUIWindow* colorWin = mpLayout->FindWindowByID(0x6243260, 1);
        if (colorWin != 0) {
            colorWin->FUN_00ac(ColorRGBToU32(city->FUN_00bd99e0()));
        }

        mpLayout->FindWindowByID(0x5dff098, 1)->SetState(1, 0);
        mpLayout->FindWindowByID(0x5e4f778, 1)->SetState(1, 0);
        mpLayout->FindWindowByID(0x5e4f788, 1)->SetState(1, 0);
        mpLayout->FindWindowByID(0x5e4f770, 1)->SetState(1, 0);

        cUIWindow* panel = main->vF0(0x49382e8, 1);
        panel->SetState(1, 1);

        union { unsigned int mKey; cRBNode* mpNode; } scratch;
        scratch.mKey = 1;
        cRBNode** res = mpCity->mTree44.find(&scratch.mpNode, scratch.mKey);
        panel->SetText((const void*)(*res)->mValue);

        main->vF0(0x2cf324c, 1)->FUN_005c(ColorRGBToU32(city->FUN_00bd99e0()));

        cUIWindow* last = mpLayout->FindWindowByID(0x4a4504f, 1);
        if (last != 0) {
            FUN_00dd2240(last, mpCity);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00dd3a00
__forceinline void cSPUICommScreen::SendSlotMessage(unsigned int id, void* value)
{
    MsgBasicRC5 msg;
    msg.mId = id;
    msg.mData[0].mValue = (unsigned int)value;
    msg.mRCFlags = 0;
    msg.mData[1].mValue = 0xffffffff;
    GetMessagingServer()->vf14(msg.mId, &msg, 0);
    msg.Destruct();
}

void cSPUICommScreen::SetSourceAndTarget(cUIWindow* source, cCity* target)
{
    cCity* src = 0;
    cCity* other = 0;
    if (source != 0) {
        src   = (cCity*)source->FUN_000c(0x901f1362);
        other = (cCity*)source->FUN_000c(0xee9b2232);
    }

    mpLayout->FindWindowByID(0x4501222, 1);

    if (src != 0) {
        SetCivilizationInfo(src);
        SendSlotMessage(0x58b8f28, src);
    } else if (other != 0) {
        SetCityInfoForWindow(other);
        SendSlotMessage(0x58b8189, other);
    }

    cCity* dst = target;
    if (dst == 0) return;
    if (other != 0 && dst == other) return;
    if (src != 0 && dst->GetCivilization() == src) return;

    SendSlotMessage(0x58b817b, dst);
}

// ---------------------------------------------------------------------------
// @ 0x00dd3b60
cSPUICommScreen::~cSPUICommScreen()
{
    _ReadWriteBarrier();   // retail keeps the two vptr stores at the very top
    if (((int)(((char*)mpArrayF4 - (char*)mpArrayEc) & 0xfffffffe) > 2)
        && mpArrayEc != 0) {
        FUN_00f47380(mpArrayEc);
    }

    if (mHandlerD8 != 0) {
        int id = mHandlerD8;
        mHandlerD8 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerDc, mHandlerE0, mHandlerE4, mHandlerE8);
    }
    if (mHandlerC4 != 0) {
        int id = mHandlerC4;
        mHandlerC4 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerC8, mHandlerCc, mHandlerD0, mHandlerD4);
    }

    if (mpC0 != 0) mpC0->Release();
    if (mpBc != 0) mpBc->Release();

    mStrA8.Destroy();
    mStr94.Destroy();
    mStr80.Destroy();
    mStr6c.Destroy();
    mStr58.Destroy();
    mStr44.Destroy();

    mList.erase();

    if (mp30 != 0) mp30->Release();
    if (mp2c != 0) mp2c->Release();
    if (mp28 != 0) mp28->Release();
    if (mp24 != 0) mp24->Release();
    if (mp20 != 0) mp20->Release();
    if (mp1c != 0) mp1c->Release();
    if (mp18 != 0) mp18->Release();
    if (mp14 != 0) mp14->Release();
    if (mp10 != 0) mp10->Release();
    if (mpLayout != 0) mpLayout->FUN_0008();
}

// ---------------------------------------------------------------------------
// @ 0x00dd3d30
void cSPUICommScreen::Shutdown()
{
    if (mbShown40 != 0) {
        Hide();
    }

    if (mHandlerC4 != 0) {
        int id = mHandlerC4;
        mHandlerC4 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerC8, mHandlerCc, mHandlerD0, mHandlerD4);
    }
    if (mHandlerD8 != 0) {
        int id = mHandlerD8;
        mHandlerD8 = 0;
        EA_Messaging_RemoveHandler(id, mHandlerDc, mHandlerE0, mHandlerE4, mHandlerE8);
    }

    cListNode* head = (cListNode*)&mList;
    mList.erase();
    head->mpNext = head;
    head->mpPrev = head;
    mpCity = 0;
    _ReadWriteBarrier();   // retail loads [this+0x24] only after the store above

    {
        cUIWindow* p = mp24;
        if (p != 0) { mp24 = 0; p->Release(); }
    }
    {
        cUIWindow* p = mp28;
        if (p != 0) { mp28 = 0; p->Release(); }
    }

    FUN_008076f0(mp14);
    {
        cUIWindow* p = mp14;
        if (p != 0) { mp14 = 0; p->Release(); }
    }
    {
        cUIWindow* p = mp18;
        if (p != 0) { mp18 = 0; p->Release(); }
    }
    FUN_008076f0(mp1c);
    {
        cUIWindow* p = mp1c;
        if (p != 0) { mp1c = 0; p->Release(); }
    }
    {
        cUIWindow* p = mp20;
        if (p != 0) { mp20 = 0; p->Release(); }
    }

    if (mp30 != 0) {
        mp30->clear();
        cUIWindow* p = mp30;
        if (p != 0) { mp30 = 0; p->Release(); }
    }

    if (mpLayout != 0) {
        mpLayout->SetParentWin(0, true, 0x5b598fa);
        mpLayout->Shutdown(1);
        cSPUILayout* p = mpLayout;
        if (p != 0) { mpLayout = 0; p->FUN_0008(); }
    }

    if (mp10 != 0) {
        mp10->FUN_000c(0);
        cUIWindow* p = mp10;
        if (p != 0) { mp10 = 0; p->Release(); }
    }

    if (mp2c != 0) {
        mp2c->FUN_000c(0);
        cUIWindow* p = mp2c;
        if (p != 0) { mp2c = 0; p->Release(); }
    }
}