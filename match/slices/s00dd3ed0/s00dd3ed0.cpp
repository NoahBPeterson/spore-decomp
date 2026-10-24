// Slice s00dd3ed0 -- SP::cSPUICommScreen::Init (0x00dd4260, 1560 bytes, __thiscall, ret 4).
//
// Builds the space-comm screen: loads the UI layout, creates the texture preloader, registers the
// screen as winproc on six windows, sizes/centres the main comm window (floor()ed to whole pixels),
// creates the two vertical scroll frames and re-parents the text/button roots into them, hides the
// eight response/preview windows, resets the response count and speaker text, loads six localized
// strings and finally registers the screen's message handler with the message server.
// Layout is the retail one (AutoRefCount members at +0x0c ... +0x30), not the 2008 PDB's.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH frame in the original).
#include "types.h"
#include <math.h>
#include <intrin.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(const Rect& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
    Rect& operator=(const Rect& o) { x1 = o.x1; y1 = o.y1; x2 = o.x2; y2 = o.y2; return *this; }
};

struct IWindow {
    virtual int AddRef();                                   // +0x00
    virtual int Release();                                  // +0x04
    PV2                                                     // 2..3
    virtual IWindow* GetParent();                           // slot 4 (+0x10)
    PV8 PV                                                  // 5..13
    virtual const Rect& GetRealArea();                      // slot 14 (+0x38)
    PV8 PV                                                  // 15..23
    virtual void SetArea(const Rect& r);                    // slot 24 (+0x60)
    virtual void SetLocation(float x, float y);             // slot 25 (+0x64)
    PV                                                      // 26
    virtual void SetLayoutArea(const Rect& r);              // slot 27 (+0x6c)
    PV2 PV                                                  // 28..30
    virtual void SetFlag(int flag, bool on);                // slot 31 (+0x7c)
    PV8 PV8 PV4 PV2                                         // 32..53
    virtual void AddWindow(IWindow* w);                     // slot 54 (+0xd8)
    virtual void RemoveWindow(IWindow* w);                  // slot 55 (+0xdc)
    PV8 PV                                                  // 56..64
    virtual void AddWinProc(void* proc);                    // slot 65 (+0x104)
};

class cSPUILayout { public:                                        // refcount at +4 / +8
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    char data[0x14];
    void Init(const void* key, bool visible, uint32_t parentID);   // 0x008120d0 (thiscall, ret 0xc)
    IWindow* FindWindowByID(uint32_t id, bool recursive);          // 0x008105b0
    int* FUN_0098f5a0();                                           // 0x0098f5a0
    cSPUILayout();                                                 // 0x00810000
};

struct cTexturePreload {                                    // refcount at +0 / +4
    virtual int AddRef();
    virtual int Release();
    char data[0x30];
    cTexturePreload(int arg);                               // 0x007b07e0
};

struct cString {                                            // SP::cString, 0x14 bytes
    uint32_t d[5];
    void Load(uint32_t table, uint32_t id, int flag);       // 0x006b54b0 (thiscall, ret 0xc)
    uint32_t GetText();                                     // 0x006b55c0 (thiscall)
};
void __fastcall cStringCtor(cString* p);                    // 0x006b5060 (ctor ABI: ecx=this)

struct MessageServer {
    PV8 PV                                                  // slots 0..8
    virtual void AddHandler(void* handler, uint32_t id);    // slot 9 (+0x24)
};
MessageServer* __cdecl GetMessageServer();                  // 0x0067dcc0
extern uint32_t gMsgID;                                     // 0x015a2b30

struct AutoHandler {                                        // EA::Messaging::AutoHandler (0x14 bytes)
    MessageServer* mpServer;
    void* mpHandler;
    uint32_t* mpIdArray;
    uint32_t mnIdArrayCount;
    int mnPriority;
};

template <class T> struct Ref {                             // EA::AutoRefCount
    T* p;
    Ref& operator=(T* q) {
        if (q != p) { T* old = p; if (q) q->AddRef(); p = q; if (old) old->Release(); }
        return *this;
    }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};

IWindow* __cdecl CreateScrollFrameVertical(const wchar_t* name, Ref<IWindow>* out, int flag);   // 0x00807600
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);                 // 0x00f473a0

static __forceinline void HideWindow(cSPUILayout* layout, uint32_t id)
{
    IWindow* w = layout->FindWindowByID(id, true);
    if (w)
        w->SetFlag(1, false);
}

// The +0x04 subobject of the screen (IWinProc / message-handler base in retail).
struct MsgHandlerSub {
    void* volatile mpVtbl;                                  // +0x04
    void* mF08;                                             // +0x08
    operator void*() { return this; }
};

// eastl::list sentinel/node for the response-button list at +0x34.
struct ListHead {
    void* mp[2];                                            // +0x34 mp[0]=prev, +0x38 mp[1]=next
    void Clear();                                           // 0x0075f3f0 (thiscall)
};
struct ListNode {
    void* mpPrev;                                           // +0x00
    void* mpNext;                                           // +0x04
    IWindow* mpData;                                        // +0x08
};

struct Float2 { float x, y; };
struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };

// View of the screen rooted at its +0x04 subobject (the winproc's `this`).
struct CommScreenProcView {
    void* mpVtbl;                                           // +0x00 (screen+0x04)
    void* mF04;                                             // +0x04
    Ref<cSPUILayout> mLayout;                               // +0x08 (screen+0x0c)
    char pad0c[0x3c - 0x0c];
    bool mOpen;                                             // +0x3c (screen+0x40)
    char pad3d[0xbc - 0x3d];
    IWindow* mCommButtons;                                  // +0xbc (screen+0xc0)
    bool HandleMessage(uint32_t msg, void* param);          // 0x00dd4880
};

// Shadow descriptor embedded in the layout/style area.
struct DropShadowDescriptor {
    uint32_t mValue;                                        // +0x04
    void SetMode2(int mode);                                // 0x00830150 (thiscall)
};
// Layout/style area handed to IWindow's slot 0x6c.
struct LayoutArea {
    uint32_t mStyle;                                        // +0x00
    DropShadowDescriptor mShadow;                           // +0x04
    uint32_t mF08;                                          // +0x08
    uint32_t mMode;                                         // +0x0c
    uint32_t mF10;                                          // +0x10
    uint32_t mF14;                                          // +0x14
    float    mFlash;                                        // +0x18
    float    mShadowR;                                      // +0x1c
    float    mShadowG;                                      // +0x20
    uint32_t mF24;                                          // +0x24
    uint32_t mF28;                                          // +0x28
};

extern void* gButtonImages;                                 // 0x015a2ac0
extern void* gEastlAllocator;                               // 0x013ebb38
extern float gFloatOne;                                     // 0x01470f1c
extern float gFloat18;                                      // 0x013ebc68
extern float gFloat141a6e8;                                 // 0x0141a6e8
extern float gFloat1471064;                                 // 0x01471064

IWindow* SPUIHelpers_SetButtonImages(void* images, int a, int b, Float2 pt, void* p); // 0x00808930

class cSPUICommScreen {
public:
    void* vtbl;                                             // +0x00 IWinProc
    MsgHandlerSub mHandlerSub;                              // +0x04 (message-handler/winproc subobject)
    Ref<cSPUILayout> mLayout;                               // +0x0c
    uint32_t pad10;                                         // +0x10
    Ref<IWindow> mScrollHolder;                             // +0x14
    Ref<IWindow> mTextScrollRoot;                           // +0x18
    Ref<IWindow> mButtonsHolder;                            // +0x1c
    Ref<IWindow> mButtonsRoot;                              // +0x20
    Ref<IWindow> mTextRoot;                                 // +0x24
    Ref<IWindow> mButtonsList;                              // +0x28
    uint32_t pad2c;                                         // +0x2c
    Ref<cTexturePreload> mPreload;                          // +0x30
    ListHead mButtonList;                                   // +0x34
    uint32_t mF3c;                                          // +0x3c
    bool mOpen;                                             // +0x40
    char pad41[3];
    cString mStr[6];                                        // +0x44, +0x58, +0x6c, +0x80, +0x94, +0xa8
    uint32_t mFbc;                                          // +0xbc
    IWindow* mCommButtons;                                  // +0xc0
    AutoHandler mHandler;                                   // +0xc4
    uint32_t mFd8[5];                                       // +0xd8
    const void* mFec;                                       // +0xec
    const void* mFf0;                                       // +0xf0
    const void* mFf4;                                       // +0xf4

    void Dispose();                                         // 0x00dd3d30
    void Hide();                                            // 0x00dd30d0
    void Show();                                            // 0x00dd2e80
    void SetResponseCount(int n);                           // 0x00dd3ed0
    void SetSpeakerText(const wchar_t* text);               // 0x00dd2ad0
    bool GetResponseText(void* pTarget, uint32_t* pOutText); // 0x00dd4950
    void Init(const void* key);
};

// @ 0x00DD4260
void cSPUICommScreen::Init(const void* key)
{
    if (mLayout.p != 0)
        Dispose();

    mLayout = new ("UI", 0, 0, 0, 0) cSPUILayout;
    mLayout->Init(key, true, 0x5b598fa);
    mOpen = false;

    mPreload = new ("UI", 0, 0, 0, 0) cTexturePreload(-1);

    {
        uint32_t ids[6] = { 0x57df5ca, 0x57df5c8, 0x57df5c9, 0x5e51d28, 0x5e51d30, 0x1c3bb0c };
        for (uint32_t i = 0; i < 6; ++i) {
            IWindow* w = mLayout->FindWindowByID(ids[i], true);
            if (w)
                w->AddWinProc(this);
        }
    }

    IWindow* main = mLayout->FindWindowByID(0x1c3bb0c, true);
    const Rect& r = main->GetRealArea();
    Rect rc;
    rc.x1 = r.x1;
    rc.y1 = r.y1;
    rc.x2 = r.x2;
    float h = r.y2 - rc.y1;
    if (h > 768.0f)
        h = 768.0f;
    rc.y2 = h;
    float w43 = h * 1.3333334f;
    rc.y1 = 0.0f;
    rc.x1 = 0.0f;
    rc.x2 = w43;
    main->SetLayoutArea(rc);

    IWindow* parent = main->GetParent();
    const Rect& pr = parent->GetRealArea();
    Rect pa = pr;
    const Rect& cr = main->GetRealArea();
    rc = cr;
    main->SetLocation((float)floor((double)(((pa.x2 - pa.x1) - (rc.x2 - rc.x1)) * 0.5f + pa.x1)),
                      (float)floor((double)(pa.y2 - (rc.y2 - rc.y1))));

    mTextScrollRoot = 0;
    mScrollHolder = CreateScrollFrameVertical(L"ScrollFrameVerticalGeneric", &mTextScrollRoot, 1);
    mButtonsRoot = 0;
    mButtonsHolder = CreateScrollFrameVertical(L"ScrollFrameVerticalGeneric", &mButtonsRoot, 1);

    IWindow* w1 = mLayout->FindWindowByID(0x4ade899, true);
    w1->AddWindow(mScrollHolder);
    mScrollHolder->SetArea(w1->GetRealArea());
    mScrollHolder->SetLocation(0.0f, 0.0f);

    IWindow* w2 = mLayout->FindWindowByID(0x4b30b3b, true);
    w2->AddWindow(mButtonsHolder);
    mButtonsHolder->SetArea(w2->GetRealArea());
    mButtonsHolder->SetLocation(0.0f, 0.0f);

    mTextRoot = mLayout->FindWindowByID(0x4adc3bf, true);
    mButtonsList = mLayout->FindWindowByID(0x18072cb, true);

    mTextRoot->GetParent()->RemoveWindow(mTextRoot);
    mTextScrollRoot->AddWindow(mTextRoot);
    mButtonsList->GetParent()->RemoveWindow(mButtonsList);
    mButtonsRoot->AddWindow(mButtonsList);

    HideWindow(mLayout.p, 0x1c3bb0c);
    HideWindow(mLayout.p, 0x5e4e5f0);
    HideWindow(mLayout.p, 0x5e4e5f8);
    HideWindow(mLayout.p, 0x5e3c090);
    HideWindow(mLayout.p, 0x5e62a48);
    HideWindow(mLayout.p, 0x5da83b8);
    HideWindow(mLayout.p, 0x5dbd7d8);
    HideWindow(mLayout.p, 0x6429c80);

    SetResponseCount(0);
    SetSpeakerText(L"");
    mStr[0].Load(0x2db6dad3, 0x66f61c1, 0);
    mStr[1].Load(0x2db6dad3, 0x6790598, 0);
    mStr[2].Load(0x2db6dad3, 0x6790599, 0);
    mStr[3].Load(0x2db6dad3, 0x679ed24, 0);
    mStr[4].Load(0x2db6dad3, 0x66f7a1c, 0);
    mStr[5].Load(0x2db6dad3, 0x66f7a1d, 0);

    void* handler = mHandlerSub;
    MessageServer* server = GetMessageServer();
    mHandler.mpServer = server;
    mHandler.mpHandler = handler;
    mHandler.mpIdArray = &gMsgID;
    mHandler.mnIdArrayCount = 1;
    mHandler.mnPriority = 0;
    if (server != 0 && handler != 0)
        server->AddHandler(handler, gMsgID);
}

// ===========================================================================
// Space-comm screen: constructor, response-button list, winproc and the
// response-text helper.  Retail (non-PDB) layout and callers.
// ===========================================================================

struct StarRecord {
    char pad00[0x84];
    void* mF84;                                             // +0x84
};

struct Empire {
    char pad00[0x84];
    void* mF84;                                             // +0x84
    int GetHomePlanet();                                    // 0x00c31730
    int FUN_00c30cb0();                                     // 0x00c30cb0
};

struct StarMgr {
    void* FUN_00885c90();                                   // 0x00885c90
};

struct cRelationshipManager {
    bool IsEnemyOrNeutral(void* a, void* b);                // 0x00d01b50
    int  ClampClassify(void* a, void* b, int c);            // 0x00d00a70
};

struct Inventory {
    char pad00[0x508];
    void* mpSubVtbl;                                        // +0x508
    char pad50c[0x540 - 0x50c];
    float mF540;                                            // +0x540
};

struct GameData {
    char pad00[0x508];
    void* mpSubVtbl;                                        // +0x508
    char pad50c[0x540 - 0x50c];
    float mF540;                                            // +0x540
    char pad544[0x714 - 0x544];
    int   mF714;                                            // +0x714
};

struct GameDataVector {
    char pad00[4];
    void** mpBegin;                                         // +0x04
    void** mpEnd;                                           // +0x08
};

struct cGameNounManager {
    GameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void* e); // 0x00b21340
};

struct CommTarget {
    char pad00[0x13c];
    int  mF13c;                                             // +0x13c
    StarRecord* GetStarRecord();                            // 0x00c71e30
};

struct Simulator {
    Inventory* GetPlayerInventory();                        // 0x00a1ad60
};

Empire* GetPlayerEmpire();                                  // 0x01021300
Simulator* GetUFOSimulator();                               // 0x00ffbe50
StarMgr* StarManager();                                     // 0x00b3d2a0
cRelationshipManager* RelationshipManager();                // 0x00b3d2c0
cGameNounManager* GetNounManager();                         // 0x00b3d300
void FUN_00cd7d10();                                        // 0x00cd7d10
void FUN_00d3d420();                                        // 0x00d3d420
void FUN_00ad48b0();                                        // 0x00ad48b0
void FUN_00b1e500();                                        // 0x00b1e500

static float SubFloat(void* pSub)
{
    return ((float (__thiscall*)(void*))(*(void***)pSub)[0x58 / 4])(pSub);
}

// Sets the open flag while handing back the first string's address, so the flag store is
// scheduled between materialising that address and the string constructor call.
__forceinline cString* SetScreenClosed(cSPUICommScreen* s, cString* p)
{
    s->mOpen = false;
    return p;
}

// @ 0x00dd4150
cSPUICommScreen* __fastcall ConstructCommScreen(cSPUICommScreen* self)
{
    self->mHandlerSub.mpVtbl = (void*)0x13eb394;    // transient base-class vtable
    self->vtbl = (void*)0x147cd8c;
    self->mHandlerSub.mpVtbl = (void*)0x147cd84;
    self->mHandlerSub.mF08 = 0;
    self->mLayout.p = 0;
    self->pad10 = 0;
    self->mScrollHolder.p = 0;
    self->mTextScrollRoot.p = 0;
    self->mButtonsHolder.p = 0;
    self->mButtonsRoot.p = 0;
    self->mTextRoot.p = 0;
    self->mButtonsList.p = 0;
    self->pad2c = 0;
    self->mPreload.p = 0;
    _ReadWriteBarrier();

    void** pHead = &self->mButtonList.mp[0];
    pHead[0] = pHead;
    pHead[1] = pHead;

    cStringCtor(SetScreenClosed(self, &self->mStr[0]));
    cStringCtor(&self->mStr[1]);
    cStringCtor(&self->mStr[2]);
    cStringCtor(&self->mStr[3]);
    cStringCtor(&self->mStr[4]);
    cStringCtor(&self->mStr[5]);

    self->mFbc = 0;
    self->mCommButtons = 0;
    self->mHandler.mpServer = 0;
    self->mHandler.mpHandler = 0;
    self->mHandler.mpIdArray = 0;
    self->mHandler.mnIdArrayCount = 0;
    self->mHandler.mnPriority = 0;
    self->mFd8[0] = 0;
    self->mFd8[1] = 0;
    self->mFd8[2] = 0;
    self->mFd8[3] = 0;
    self->mFd8[4] = 0;
    _ReadWriteBarrier();

    self->mFec = (const void*)0x1667bac;
    self->mFf0 = (const void*)0x1667bac;
    self->mFf4 = (const void*)0x1667bae;

    return self;
}

// @ 0x00dd3ed0
void cSPUICommScreen::SetResponseCount(int n)
{
    IWindow* pTextRoot = mTextRoot.p;
    ((void (__thiscall*)(void*))(*(void***)pTextRoot)[0xe4 / 4])(pTextRoot);

    mButtonList.Clear();
    mButtonList.mp[0] = &mButtonList;
    mButtonList.mp[1] = &mButtonList;

    IWindow* pScroll = mTextScrollRoot.p;
    float* rf = (float*)((void* (__thiscall*)(void*))
                         (*(void***)pScroll)[0x34 / 4])(pScroll);
    float width = rf[2] - rf[0];

    if (n > 0) {
        do {
            Float2 pt;
            pt.x = 0.0f;
            pt.y = 0.0f;
            IWindow* btn = SPUIHelpers_SetButtonImages(&gButtonImages, 1, 0, pt, 0);

            IWindow* parent = (IWindow*)((void* (__thiscall*)(void*))
                                         (*(void***)btn)[0x10 / 4])(btn);
            ((void (__thiscall*)(void*, uint32_t))
             (*(void***)parent)[0x54 / 4])(parent, 0x4b417d4);

            Float4 rc;
            rc.x = 0.0f;
            rc.y = 0.0f;
            rc.z = width;
            rc.w = gFloat18;
            ((void (__thiscall*)(void*, Float4*))
             (*(void***)parent)[0x60 / 4])(parent, &rc);

            ((void (__thiscall*)(void*, int, int))
             (*(void***)parent)[0x7c / 4])(parent, 1, 1);
            ((void (__thiscall*)(void*, void*))
             (*(void***)parent)[0x104 / 4])(parent, this);

            IWindow* pRoot = mTextRoot.p;
            ((void (__thiscall*)(void*, void*))
             (*(void***)pRoot)[0xd8 / 4])(pRoot, parent);

            ((void (__thiscall*)(void*, uint32_t))
             (*(void***)parent)[0x84 / 4])(parent, 0x5163044d);

            ((void (__thiscall*)(void*, int, uint32_t))
             (*(void***)btn)[0x4c / 4])(btn, 0, 0xffffb400);
            ((void (__thiscall*)(void*, int, uint32_t))
             (*(void***)btn)[0x4c / 4])(btn, 1, 0xff7f7f7f);
            ((void (__thiscall*)(void*, int, uint32_t))
             (*(void***)btn)[0x4c / 4])(btn, 2, 0xffffb400);
            ((void (__thiscall*)(void*, int, uint32_t))
             (*(void***)btn)[0x4c / 4])(btn, 3, 0xffffb400);
            ((void (__thiscall*)(void*, int, uint32_t))
             (*(void***)btn)[0x4c / 4])(btn, 7, 0xffffb400);

            float one = gFloatOne;
            ((void (__thiscall*)(void*, float, float, float, float))
             (*(void***)btn)[0x54 / 4])(btn, one, one, one, one);

            LayoutArea area;
            area.mMode = 3;
            area.mF10 = 0;
            area.mF14 = 0;
            area.mF28 = 0;
            area.mShadow.SetMode2(2);
            area.mShadowR = gFloat141a6e8;
            area.mShadowG = gFloat1471064;
            area.mFlash = gFloatOne;
            area.mShadow.mValue = 2;
            area.mStyle = 2;
            ((void (__thiscall*)(void*, LayoutArea*))
             (*(void***)btn)[0x6c / 4])(btn, &area);

            IWindow* child = (IWindow*)((void* (__thiscall*)(void*))
                                        (*(void***)parent)[0xa8 / 4])(parent);
            if (child != 0)
                child = (IWindow*)((void* (__thiscall*)(void*, uint32_t))
                                   (*(void***)child)[0xc / 4])(child, 0x103c1908);
            ((void (__thiscall*)(void*, int))
             (*(void***)child)[0x1c / 4])(child, 2);

            ((void (__thiscall*)(void*))(*(void***)btn)[0 / 4])(btn);   // AddRef

            ListHead* head = (ListHead*)mButtonList.mp[0];
            ListNode* node = (ListNode*)operator new(0xc, "Simulator", 0, 0,
                                                    (int)&gEastlAllocator, 0xd1);
            node->mpData = btn;
            ((void (__thiscall*)(void*))(*(void***)btn)[0 / 4])(btn);   // AddRef
            node->mpPrev = head;
            node->mpNext = head->mp[1];
            ((ListNode*)head->mp[1])->mpPrev = node;
            head->mp[1] = node;

            ((void (__thiscall*)(void*))(*(void***)btn)[4 / 4])(btn);   // Release
        } while (--n != 0);
    }
}

// @ 0x00dd4880
bool CommScreenProcView::HandleMessage(uint32_t msg, void* param)
{
    if (msg == 0x65ff54a) {
        int* p = mLayout.p->FUN_0098f5a0();
        struct { int a, b, c; } key;
        key.a = p[0];
        key.b = p[1];
        key.c = p[2];
        int* arg = (int*)param;
        if (arg[0x10 / 4] == key.c && arg[0x18 / 4] == key.a) {
            bool bWasOpen = mOpen;
            if (bWasOpen)
                ((cSPUICommScreen*)((char*)this - 4))->Hide();
            ((cSPUICommScreen*)((char*)this - 4))->Dispose();
            ((cSPUICommScreen*)((char*)this - 4))->Init((const void*)&key);
            if (bWasOpen) {
                ((cSPUICommScreen*)((char*)this - 4))->Show();
                return true;
            }
        }
    } else if (msg == 0x20c089c) {
        IWindow* pTarget = mCommButtons;
        if (pTarget != 0) {
            float* f = (float*)param;
            Float3 pos;
            pos.x = f[0];
            pos.y = f[1];
            pos.z = f[2];
            _ReadWriteBarrier();
            ((void (__thiscall*)(void*, Float3*))
             (*(void***)pTarget)[0x30 / 4])(pTarget, &pos);
        }
    }
    return true;
}

// @ 0x00dd4950
bool cSPUICommScreen::GetResponseText(void* pTarget, uint32_t* pOutText)
{
    CommTarget* pSel = (CommTarget*)pTarget;
    StarRecord* pStar = pSel->GetStarRecord();
    Empire* pEmpire = GetPlayerEmpire();
    Simulator* pSim = GetUFOSimulator();
    Inventory* pInv = pSim->GetPlayerInventory();

    if (pStar != 0) {
        void* starId = pStar->mF84;
        StarMgr* pMgr = StarManager();
        if (starId == pMgr->FUN_00885c90()) {
            cRelationshipManager* pRel = RelationshipManager();
            if (pRel->IsEnemyOrNeutral(starId, pEmpire->mF84)) {
                int cls = pRel->ClampClassify(starId, pEmpire->mF84, 1);
                if (cls == 0 || cls == 1)
                    return false;
            }
        }
    }

    Empire* pEmpire2 = GetPlayerEmpire();
    if (pEmpire2->FUN_00c30cb0() == 0) {
        if (pSel->mF13c != pEmpire->GetHomePlanet()) {
            *pOutText = mStr[3].GetText();
            return false;
        }
    }

    if (pInv->mF540 != SubFloat(&pInv->mpSubVtbl))
        return true;

    GameDataVector* v = GetNounManager()->GetGameDataVector(
        (void*)&FUN_00cd7d10, (void*)&FUN_00d3d420, (void*)&FUN_00ad48b0,
        (void*)&FUN_00b1e500, (void*)0x018ebadc);
    int count = (int)(v->mpEnd - v->mpBegin);
    for (int i = 0; i < count; ++i) {
        GameData* gd = (GameData*)v->mpBegin[i];
        if (gd != 0 && gd->mF714 == 3) {
            if (gd->mF540 != SubFloat(&gd->mpSubVtbl))
                return true;
        }
    }

    *pOutText = mStr[4].GetText();
    return false;
}
