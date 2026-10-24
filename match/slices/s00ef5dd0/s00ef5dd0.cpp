// Slice s00ef5dd0 -- 0x00ef6700 (1707 bytes, __thiscall, 5 stack args / ret 0x14): points the
// scenario-mode Sporepedia large asset view (Simulator::cSPScenarioModeSporepediaLargeAssetView,
// the sub-object at primary+0x24; the inverse of Reset 0x00ef6db0) at a new asset (name guessed: SetAsset).
//
// Stores the two ref-counted arguments, clears the cached metadata / summary resources, looks the
// asset's cAssetMetadata (type 0x30bdee3) and summary (type 0xe742574a) resources up in the resource
// manager, creates the message-listener registration (3 messages), pushes the asset into the
// author/verb helper objects, enables or disables the play/edit button, fills the "adventure points"
// caption, and finally either kicks off the metadata download (online) or looks up the download
// state of the asset's summary entries, or (when the asset has no data) hides the extra windows.
//
// Module flags: /O2 /MD /Gy /TP (no /EHsc: the original has no EH frame).
#include "types.h"
#include <string.h>
#include <intrin.h>

struct Key { uint32_t instanceID, typeID, groupID; };

// ---------------------------------------------------------------------------
// ref-counted pointer (EA::AutoRefCount): assignment copies with AddRef/Release
// ---------------------------------------------------------------------------
template <class T> struct ARef {
    T* mp;
    __forceinline ARef& operator=(T* p)
    {
        T* old = mp;
        if (p != old) {
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    __forceinline void Reset()
    {
        T* old = mp;
        if (old) {
            mp = 0;
            old->Release();
        }
    }
    ~ARef() { if (mp) mp->Release(); }
    operator T*() const { return mp; }
    T* operator->() const { return mp; }
};

struct IRefCounted {
    virtual void AddRef();                              // +0x00
    virtual void Release();                             // +0x04
};
// EA::ResourceMan::IResource-like object: Cast by type id
struct IResource : IRefCounted {
    virtual void v08();
    virtual void* Cast(uint32_t type);                  // +0x0c
};

struct IWindow {
    virtual void AddRef(); virtual void Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual uint32_t GetRealArea();                     // +0x38 (value passed on to SetLayoutArea)
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68();
    virtual void SetLayoutArea(uint32_t area);          // +0x6c
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, int value);          // +0x7c
    virtual void SetCaption(const wchar_t* text);       // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4(); virtual void va8();
    virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0(); virtual void ve4();
    virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, int recursive);   // +0xf0
};

class cSPUILayout { public:
    IWindow* FindWindowByID(uint32_t id, int recursive);           // 0x008105b0
    bool Init(const Key& key, bool a, uint32_t b);                 // 0x008120d0
    bool SetParentWin(IWindow* parent, bool a, uint32_t b);        // 0x008121b0
    void SetReloadCallback(void (*cb)(void*, void*, bool), void* ctx);  // 0x00810090
};

// Sporepedia::IAssetData with the Object sub-object (Cast/AddRef/Release) at +0x10
struct IAssetData {
    virtual void a00(); virtual void a04(); virtual void a08(); virtual void a0c(); virtual void a10();
    virtual void a14();
    virtual Key GetImageKey();                          // +0x18
    virtual void a1c(); virtual void a20(); virtual void a24(); virtual void a28(); virtual void a2c();
    virtual void a30(); virtual void a34(); virtual void a38(); virtual void a3c();
    virtual const Key* GetKey();                        // +0x40
    virtual void a44(); virtual void a48(); virtual void a4c(); virtual void a50();
    virtual int64_t GetAuthorID();                      // +0x54
    virtual void a58(); virtual void a5c(); virtual void a60(); virtual void a64(); virtual void a68();
    virtual void a6c(); virtual void a70(); virtual void a74(); virtual void a78(); virtual void a7c();
    virtual void a80(); virtual void a84(); virtual void a88(); virtual void a8c();
    virtual bool GetAssetID(uint64_t& dst);             // +0x90
    uint32_t pad04[3];
};
struct IObject : IRefCounted {
    virtual void v08();
    virtual void* Cast(uint32_t type);                  // +0x0c
};
struct cAssetData : IAssetData, IObject {
    void AddRef() { IObject::AddRef(); }
    void Release() { IObject::Release(); }
    void* Cast(uint32_t type) { return IObject::Cast(type); }
    bool IsLocalAsset();                                // 0x006418e0
};

struct cAssetMetadata : IRefCounted {
    uint32_t pad04[5];
    Key* GetAssetKeyPtr();                              // 0x005507a0: &this->mAssetKey (+0x18)
};
struct cAssetSummary : IRefCounted {                    // type 0xe742574a
    uint32_t pad04[0x19];
    int mState[4];                                      // +0x68
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const Key* key, IResource** out, int a, int b, int c, int d);   // +0x0c
};
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); } }                    // 0x0067dcd0

struct IMessageListener { virtual void ml00(); };
struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void AddListener(IMessageListener* listener, uint32_t msgId);   // +0x24
};
IMessageServer* __cdecl SP_MessageServer();                      // 0x0067dcc0

struct IConfigManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c();
    virtual int GetValue(uint32_t id);                           // +0x30
};
IConfigManager* __cdecl SP_ConfigManager();                      // 0x0067dd30

struct IAuthManager {
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20();
    virtual bool IsOffline();                                    // +0x24
};
namespace SP { namespace Pollen { IAuthManager* AuthManager(); } }   // 0x00607a60

struct IWindowManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void SetFocus(int a, IWindow* w);                    // +0x4c
};
IWindowManager* __cdecl SP_WindowManager();                      // 0x0067caa0

struct cMetadataFetcher {
    bool FindMetadata(uint32_t lo, uint32_t hi, IResource** out, int flag);   // 0x00612f50
};
struct cAssetQueue {
    uint32_t pad[0x5c / 4];
    cMetadataFetcher* mpFetcher;                                  // +0x5c
    void GetAssetFeedEx(uint32_t lo, uint32_t hi);                // 0x00610c20
};
cAssetQueue* __cdecl AssetQueue();                                // 0x0067cb30

// the 0x6563c0 parameter block
struct ShowParams {
    uint32_t f0;
    bool b4, b5, b6;
    uint32_t f8;
    bool bc;
    ShowParams();                                                 // 0x006563c0
};
struct cAssetVerbs {
    void Show(int one, ShowParams* p, cAssetData* asset);         // 0x006571e0
};
struct cAssetHelper70 {
    void SetOnline(int flag);                                     // 0x00f47080
    void SetKey(uint32_t lo, uint32_t hi);                        // 0x00f47170
};

struct cString {                                                  // SP::cString
    uint32_t mpBegin, mpEnd, mpCapacity, mAllocator;
    cString();                                                    // 0x006b5060
    ~cString();                                                   // 0x006b5240
    void Load(uint32_t id, uint32_t group, const wchar_t* dflt);  // 0x006b54b0
    const wchar_t* GetText();                                     // 0x006b55c0
};

struct cSPEditorVerbIconTray {
    int pad[0x18];                    // +0x00..+0x5f
    int mTimesPlayed;                 // +0x60
    int mAdventurePoints;             // +0x64
    void SetCaption(const wchar_t* text);   // 0x00ef5da0
};
extern cSPEditorVerbIconTray* gAdventureTray;                     // 0x015ee298
int __cdecl AdventurePointsFor(const Key* k);                     // 0x00eed8c0
int __cdecl IsAssetUnlocked(const Key* k);                        // 0x00552300

extern const uint32_t kViewMessages[3];                           // 0x0148b43c

struct PrimaryBase { virtual void p00(); };
struct Primary : PrimaryBase, IMessageListener {                  // the large asset view proper
    void ClearSelection();                                        // 0x00ef5dd0
    void ShowMetadata(IResource* r);                              // 0x00ef5e90
};

struct MsgRegistration {            // App::MessageListenerData
    IMessageServer* server;
    IMessageListener* listener;
    const uint32_t* ids;
    uint32_t count;
    uint32_t n;
};

struct AssetView {
    void* vptr;                     // +0x00
    uint32_t pad04[2];
    cSPUILayout* mLayout;           // +0x0c
    ARef<IRefCounted> mArg1;        // +0x10
    ARef<IWindow> mWinFocus;             // +0x14
    ARef<IWindow> mWinEnable;            // +0x18
    uint32_t pad1c[(0x34 - 0x1c) / 4];
    ARef<IWindow> mWinCaption;           // +0x34
    uint32_t pad38[(0x58 - 0x38) / 4];
    ARef<IWindow> mWinHide;              // +0x58
    uint32_t pad5c[(0x70 - 0x5c) / 4];
    cAssetHelper70* mHelper;        // +0x70
    cAssetVerbs* mVerbs;            // +0x74
    ARef<cAssetData> mAsset;        // +0x78   (ref-count sub-object at +0x10 of the asset)
    ARef<cAssetMetadata> mMetadata; // +0x7c
    ARef<cAssetSummary> mSummary;   // +0x80
    uint32_t pad84[(0x94 - 0x84) / 4];
    uint32_t mKeyLo, mKeyHi;        // +0x94, +0x98
    uint8_t pad9c;
    uint8_t mBusy;                  // +0x9d
    uint8_t mFlag9e;
    uint8_t mFlag9f;
    int* mVecBegin;                 // +0xa0
    int* mVecEnd;                   // +0xa4
    uint32_t pada8[(0xcc - 0xa8) / 4];
    MsgRegistration mReg;           // +0xcc

    Primary* GetPrimary() { return (Primary*)((char*)this - 0x24); }
    bool SetAsset(IRefCounted* a1, cAssetData* asset, uint32_t a3, bool a4, int a5);   // 0x00ef6700
};

// @ 0x00ef6700
bool AssetView::SetAsset(IRefCounted* a1, cAssetData* asset, uint32_t a3, bool a4, int a5)
{
    mBusy = 1;
    mAsset = asset;
    mArg1 = a1;
    mKeyLo = (uint32_t)-1;
    mKeyHi = (uint32_t)-1;
    mMetadata.Reset();

    cAssetData* data = 0;
    if (mAsset) {
        data = (cAssetData*)mAsset->Cast(0x13d55dc8);
        if (data) {
            const Key* k = mAsset->GetKey();
            ARef<IResource> ref;
            ref.mp = 0;
            IResourceManager* mgr = EA::ResourceMan::GetManager();
            ref.Reset();
            Key key;
            key.instanceID = k->instanceID;
            key.typeID = 0x30bdee3;
            key.groupID = k->groupID;
            if (mgr->GetResource(&key, &ref.mp, 0, 0, 0, 0)) {
                cAssetMetadata* md = ref ? (cAssetMetadata*)ref->Cast(0x30bdee3) : 0;
                mMetadata = md;
            }
        }
    }
    mSummary.Reset();

    ARef<IResource> ref2;
    ref2.mp = 0;
    {
        cAssetData* a = mAsset;
        IResourceManager* mgr = EA::ResourceMan::GetManager();
        ref2.Reset();
        if (mgr->GetResource(a->GetKey(), &ref2.mp, 0, 0, 0, 0)) {
            cAssetSummary* s = ref2 ? (cAssetSummary*)ref2->Cast(0xe742574a) : 0;
            mSummary = s;
        }
    }

    GetPrimary()->ClearSelection();
    IMessageListener* listener = GetPrimary();
    IMessageServer* ms = SP_MessageServer();
    mReg.server = ms;
    mReg.listener = listener;
    mReg.ids = kViewMessages;
    mReg.count = 3;
    mReg.n = 0;
    if (ms && listener) {
        for (uint32_t i = 0; i < 12; i += 4)
            ms->AddListener(listener, *(const uint32_t*)((const char*)kViewMessages + i));
    }

    if (data && mHelper) {
        uint64_t id;
        if (!data->GetAssetID(id)) {
            mHelper->SetOnline(0);
        } else {
            mHelper->SetOnline(1);
            mHelper->SetKey((uint32_t)id, (uint32_t)(id >> 32));
        }
    }

    if (mVerbs) {
        ShowParams p;
        p.f0 = a3;
        p.b4 = false;
        p.b5 = a4;
        p.b6 = true;
        mVerbs->Show(1, &p, mAsset);
    }

    if (mWinEnable) {
        bool isLocal = data && data->IsLocalAsset();
        bool hasAuthor = data && data->GetAuthorID() != 0;
        bool offConfig = SP_ConfigManager()->GetValue(0x5de7b4a) != 0;
        bool offline = SP::Pollen::AuthManager()->IsOffline();
        bool enable;
        if (!offConfig && !offline && !isLocal && hasAuthor)
            enable = true;
        else
            enable = false;
        mWinEnable->SetFlag(2, enable);
        mWinEnable->SetFlag(0x10, !enable);
    }

    if (mWinCaption) {
        gAdventureTray->mAdventurePoints = AdventurePointsFor(mAsset->GetKey());
        cString s;
        s.Load(0x6f5943eb, 0x2100002, L"*adventure points*");
        mWinCaption->SetCaption(s.GetText());
    }

    if (mMetadata) {
        const Key* k = mMetadata->GetAssetKeyPtr();
        mKeyLo = k->instanceID;
        mKeyHi = k->typeID;
    }

    if (mWinHide)
        mWinHide->SetFlag(1, 0);

    int ok = 1;
    if (mAsset)
        ok = IsAssetUnlocked(mAsset->GetKey());

    mFlag9e = 0;
    mFlag9f = 0;
    _ReadWriteBarrier();
    {
        int* first = mVecBegin;
        int* last = mVecEnd;
        memcpy(first, last, (size_t)((char*)mVecEnd - (char*)last));
        mVecEnd -= (last - first);
    }
    _ReadWriteBarrier();

    if ((mKeyLo & mKeyHi) != 0xffffffff && ok != 0) {
        if (SP::Pollen::AuthManager()->IsOffline()) {
            IResource* out = 0;
            cMetadataFetcher* f = AssetQueue()->mpFetcher;
            if (f->FindMetadata(mKeyLo, mKeyHi, &out, 0))
                GetPrimary()->ShowMetadata(out);
            if (out)
                out->Release();
        } else {
            cMetadataFetcher* f = AssetQueue()->mpFetcher;
            if (f->FindMetadata(mKeyLo, mKeyHi, 0, 1))
                mFlag9e = 1;
            int i = 0;
            for (uint32_t off = 0x68; off < 0x78; off += 4, ++i) {
                if (mSummary) {
                    int v = *(int*)((char*)(cAssetSummary*)mSummary + off);
                    if (v == 1 || v == 0) {
                        Key img = mAsset->GetImageKey();
                        Key k2;
                        k2.instanceID = img.instanceID;
                        k2.typeID = img.typeID;
                        k2.groupID = (img.groupID & 0xffffff00) | ((i + 1) & 0xff);
                        if (!EA::ResourceMan::GetManager()->GetResource(&k2, 0, 0, 0, 0, 0)) {
                            AssetQueue()->GetAssetFeedEx(mKeyLo, mKeyHi);
                            mFlag9f = 1;
                            break;
                        }
                    }
                }
            }
        }
    }

    if (ok == 0) {
        IWindow* w1 = mLayout->FindWindowByID(0x7ccce30, 1);
        IWindow* w2 = mLayout->FindWindowByID(0x7ccce38, 1);
        IWindow* w3 = mLayout->FindWindowByID(0x8003ed0, 1);
        IWindow* w4 = mLayout->FindWindowByID(0x7da34f8, 1);
        if (w1)
            w1->SetFlag(1, 0);
        if (w4)
            w4->SetFlag(1, 0);
        if (w2 && w3) {
            w2->SetLayoutArea(w3->GetRealArea());
            IWindow* w5 = w2->FindWindowByID(0x7b69988, 1);
            if (w5)
                w5->SetFlag(1, 0);
        }
    }

    SP_WindowManager()->SetFocus(0, mWinFocus.mp);
    return true;
}

// ===========================================================================
// Simulator::cSPScenarioModeSporepediaLargeAssetView (gold7)
// The primary view object; the cAssetView sub-object lives at +0x24.
// ===========================================================================

// embedded UI sub-object at +0x0c (constructed by FUN_0066f200)
struct tEmbedUI {
    void* mpVtable;                    // +0x00 (view +0x0c)
    uint32_t mn04, mn08, mn0c, mn10, mn14;   // view +0x10..+0x20
};

class cLargeAssetView {
public:
    void* mpVtbl00;                    // +0x00
    void* mpVtbl04;                    // +0x04
    void* mpVtbl08;                    // +0x08
    tEmbedUI mEmbed;                   // +0x0c
    void* mp24;                        // +0x24  (cAssetView base vptr)
    void* mp28;                        // +0x28
    int32_t mn2c;                      // +0x2c
    void* mp30;                        // +0x30  (cSPUILayout*)
    void* mp34;                        // +0x34  (parent IWindow*)
    void* mp38; void* mp3c; void* mp40; void* mp44; void* mp48;
    void* mp4c; void* mp50; void* mp54; void* mp58;
    void* map5c[4];                    // +0x5c..+0x68
    void* map6c[4];                    // +0x6c..+0x78
    void* mp7c; void* mp80; void* mp84; void* mp88; void* mp8c; void* mp90; void* mp94;
    void* mp98; void* mp9c; void* mpA0; void* mpA4; void* mpA8; void* mpAC; void* mpB0;
    int32_t mnB4;                      // +0xb4
    int32_t mnB8;                      // +0xb8
    int32_t mnBC;                      // +0xbc
    uint8_t mbC0, mbC1, mbC2, mbC3;    // +0xc0..+0xc3
    void* mpC4;                        // +0xc4
    void* mpC8;                        // +0xc8
    void* mpCC;                        // +0xcc
    uint32_t mnD0;                     // +0xd0
    void* mpD4;                        // +0xd4
    uint32_t mnD8;                     // +0xd8
    uint8_t mBuf[0x14];                // +0xdc
    uint32_t mnF0;                     // +0xf0  (message handler id)
    uint32_t mnF4, mnF8, mnFC, mn100;  // +0xf4..+0x100

    void ClearSelection();                              // 0x00ef5dd0
    void ShowMetadata(IResource* r);                    // 0x00ef5e90
    void Destroy();                                     // 0x00ef61b0
    void OnMessage(void* sender, uint32_t msgId);       // 0x00ef6650
    void Load();                                        // 0x00ef50a0
};

struct cPropertyBag {
    bool GetInt32(uint32_t id, void* out);              // 0x00613660
    bool GetFloat(uint32_t id, void* out);              // 0x006135d0
};

struct cTooltip {
    void SetText(const wchar_t* text, void* a, char b); // 0x00835ed0
};

// EA::AutoRefCount<T> (constructor at 0x00572660)
struct tAutoRef {
    void* mp;
    void Init(void* p);                                 // 0x00572660
};

void* __cdecl AllocGame(int32_t size, const void* tag,
                        int32_t a, int32_t b, int32_t c, int32_t d);   // 0x00f473a0
void* __fastcall DialogCtor(void* pThis);               // 0x00810000
void __fastcall FUN_0066f200(void* pThis);              // 0x0066f200
void* __cdecl FUN_009512c0();                           // 0x009512c0
void* __cdecl FUN_009512d0(int32_t a, int32_t b, const char* name, void* res);  // 0x009512d0
cTooltip* __fastcall TooltipCtor(cTooltip* pThis);      // 0x00835cc0
int __cdecl FUN_00ec3ca0(float f);                      // 0x00ec3ca0
void __cdecl FUN_00ef5d80(void* a, void* b, bool c);    // 0x00ef5d80
void __cdecl operator_delete__(void* p);                // 0x00f47380
void __cdecl RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x00571db0
struct cPollinator {
    void SubscribeToFeed(void* pArg);                   // 0x00610780
};
cPollinator* __fastcall Pollinator_Get();               // 0x0067cb30
int64_t __fastcall Meta_GetID64(void* pThis);           // 0x005508a0
void __cdecl FormatString(void* pStr, uint32_t unused, const char* fmt, int64_t value);  // 0x00472f50

extern uint8_t g_allocTag13f6b3c;                       // 0x013f6b3c
extern uint32_t g_dw15ace34;                            // 0x015ace34
extern const uint32_t g_textGroups[];                   // 0x0148b39c

// @ 0x00ef5dd0
void cLargeAssetView::ClearSelection()
{
    {
        void* mem = AllocGame(0x18, &g_allocTag13f6b3c, 0, 0, 0, 0);
        void* pNew;
        if (mem)
            pNew = DialogCtor(mem);
        else
            pNew = 0;

        void* pOld = mp30;
        if (pNew != pOld) {
            if (pNew)
                (*(void (__thiscall**)(void*))((char*)*(void**)pNew + 4))(pNew);
            mp30 = pNew;
            if (pOld)
                (*(void (__thiscall**)(void*))((char*)*(void**)pOld + 8))(pOld);
        }

        Key k;
        k.instanceID = 0x6c0fbd13;
        k.typeID = 0x0510a95b;
        k.groupID = g_dw15ace34;
        ((cSPUILayout*)mp30)->Init(k, true, 0x5b598fa);

        void* pEmbed = &mEmbed;
        (*(void (__thiscall**)(void*))mEmbed.mpVtable)(pEmbed);

        ((cSPUILayout*)mp30)->SetParentWin((IWindow*)mp34, true, 0x5b598fa);
        ((cSPUILayout*)mp30)->SetReloadCallback(FUN_00ef5d80, this);
    }
    return Load();
}

// @ 0x00ef5e90
void cLargeAssetView::ShowMetadata(IResource* r)
{
    cPropertyBag* bag = (cPropertyBag*)r;

    struct Props { int32_t nA; float fB; int32_t nC; } p;
    p.nC = 0;
    p.nA = 3;
    p.fB = 0.0f;
    if (!bag->GetInt32(0x35c95bc4, &p.nC)) return;
    if (!bag->GetInt32(0x11576eea, &p.nA)) return;
    if (!bag->GetFloat(0x190e18aa, &p.fB)) return;

    IWindow* p7c = (IWindow*)mp7c;
    if (!p7c) return;
    p7c->SetFlag(1, 1);

    uint32_t u = (uint32_t)FUN_00ec3ca0(p.fB);

    if (mp80) {
        void* pObj = (*(void* (__thiscall**)(void*, uint32_t))
                      ((char*)*(void**)mp80 + 0x0c))(mp80, 0x106f146);
        if (pObj) {
            void* pSub = (char*)pObj + 0x20c;
            (*(void (__thiscall**)(void*, uint32_t))
             ((char*)*(void**)pSub + 0x14))(pSub, u);

            {
                cTooltip* tip = (cTooltip*)FUN_009512d0(
                    0x68, 4, "UI/Tooltip", FUN_009512c0());
                if (tip) tip = TooltipCtor(tip);

                tAutoRef ref;
                ref.Init(tip);

                {
                    cString s;
                    s.Load(0x6f5943eb, 0xc7647889, 0);
                    tip->SetText(s.GetText(), (void*)-1, (char)1);
                    (*(void (__thiscall**)(void*, void*))
                     ((char*)*(void**)mp80 + 0x104))(mp80, ref.mp);
                }

                if (ref.mp)
                    (*(void (__thiscall**)(void*))
                     ((char*)*(void**)ref.mp + 4))(ref.mp);
            }
        }
    }

    gAdventureTray->mTimesPlayed = p.nC;

    {
        cString s2;
        s2.Load(0x6f5943eb, 0x2100001, L"*number of times played*");
        IWindow* p84 = (IWindow*)mp84;
        if (p84)
            p84->SetCaption(s2.GetText());

        if (mp88) {
            void* pObj2 = (*(void* (__thiscall**)(void*, uint32_t))
                           ((char*)*(void**)mp88 + 0x0c))(mp88, 0x106f146);
            if (pObj2) {
                void* pSub2 = (char*)pObj2 + 0x20c;

                int nMax = (*(int (__thiscall**)(void*))
                            ((char*)*(void**)pSub2 + 0x10))(pSub2);
                int n = p.nA;
                if (n < 1)
                    n = 1;
                else if (n > nMax)
                    n = nMax;
                p.nA = n;

                int n2;
                if (n >= 1) {
                    int nMax2 = (*(int (__thiscall**)(void*))
                                 ((char*)*(void**)pSub2 + 0x10))(pSub2);
                    if (n <= nMax2)
                        (*(void (__thiscall**)(void*, int))
                         ((char*)*(void**)pSub2 + 0x14))(pSub2, n - 1);

                    int c = p.nA;
                    if (c < 1)
                        n2 = 1;
                    else if (c > 5)
                        n2 = 5;
                    else
                        n2 = c;
                } else {
                    n2 = 1;
                }
                p.nA = n2;

                {
                    cString s3;
                    s3.Load(0x6f5943eb, g_textGroups[n2], 0);
                    gAdventureTray->SetCaption(s3.GetText());

                    {
                        cString s4;
                        s4.Load(0x6f5943eb, 0x7d86c49, 0);

                        cTooltip* tip = (cTooltip*)FUN_009512d0(
                            0x68, 4, "UI/Tooltip", FUN_009512c0());
                        if (tip) tip = TooltipCtor(tip);

                        tAutoRef ref;
                        ref.Init(tip);

                        tip->SetText(s4.GetText(), (void*)-1, (char)1);
                        (*(void (__thiscall**)(void*, void*))
                         ((char*)*(void**)mp88 + 0x104))(mp88, ref.mp);

                        if (ref.mp)
                            (*(void (__thiscall**)(void*))
                             ((char*)*(void**)ref.mp + 4))(ref.mp);
                    }
                }
            }
        }
    }
}

// @ 0x00ef61b0
void cLargeAssetView::Destroy()
{
    mpVtbl00 = (void*)0x148b3f8;
    mpVtbl04 = (void*)0x148b3e8;
    mpVtbl08 = (void*)0x148b3dc;
    mEmbed.mpVtable = (void*)0x140085c;
    mp24 = (void*)0x148b3c4;
    mp28 = (void*)0x148b3b4;

    _ReadWriteBarrier();
    if (mnF0) {
        uint32_t h = mnF0;
        mnF0 = 0;
        RemoveHandler(h, mnF4, mnF8, mnFC, mn100);
    }

    if (mpC4 && mpC4 != mpD4)
        operator_delete__(mpC4);

    if (mpB0)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpB0 + 8))(mpB0);
    if (mpAC)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpAC + 8))(mpAC);
    if (mpA8)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpA8 + 4))(mpA8);
    if (mpA4)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpA4 + 4))(mpA4);
    if (mpA0)
        (*(void (__thiscall**)(void*))((char*)*(void**)mpA0 + 4))(mpA0);
    if (mp9c) {
        void* p = (char*)mp9c + 0x10;
        (*(void (__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    if (mp98)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp98 + 4))(mp98);
    if (mp94)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp94 + 4))(mp94);
    if (mp90)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp90 + 4))(mp90);
    if (mp8c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp8c + 4))(mp8c);
    if (mp88)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp88 + 4))(mp88);
    if (mp84)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp84 + 4))(mp84);
    if (mp80)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp80 + 4))(mp80);
    if (mp7c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp7c + 4))(mp7c);

    {
        void** pp = &map6c[4];
        int i = 3;
        do {
            void* q = *--pp;
            if (q)
                (*(void (__thiscall**)(void*))((char*)*(void**)q + 4))(q);
        } while (--i >= 0);
    }
    {
        void** pp = &map5c[4];
        int i = 3;
        do {
            void* q = *--pp;
            if (q)
                (*(void (__thiscall**)(void*))((char*)*(void**)q + 4))(q);
        } while (--i >= 0);
    }

    if (mp58)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp58 + 4))(mp58);
    if (mp54)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp54 + 4))(mp54);
    if (mp50)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp50 + 4))(mp50);
    if (mp4c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp4c + 4))(mp4c);
    if (mp48)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp48 + 4))(mp48);
    if (mp44)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp44 + 4))(mp44);
    if (mp40)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp40 + 4))(mp40);
    if (mp3c)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp3c + 4))(mp3c);
    if (mp38)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp38 + 4))(mp38);
    if (mp34)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp34 + 4))(mp34);
    if (mp30)
        (*(void (__thiscall**)(void*))((char*)*(void**)mp30 + 8))(mp30);

    mp28 = (void*)0x13ec458;
    mpVtbl04 = (void*)0x13eb394;
    mpVtbl00 = (void*)0x13eb938;
}

// @ 0x00ef64e0
cLargeAssetView* __fastcall cLargeAssetView_Ctor(cLargeAssetView* pThis)
{
    void** ppEmbed = (void**)&pThis->mEmbed;
    pThis->mpVtbl00 = (void*)0x14426a0;
    _ReadWriteBarrier();
    pThis->mpVtbl04 = (void*)0x13eb384;
    FUN_0066f200(ppEmbed);
    _ReadWriteBarrier();
    pThis->mp24 = (void*)0x1400744;
    pThis->mp28 = (void*)0x13ec458;
    _ReadWriteBarrier();
    pThis->mn2c = 0;
    _ReadWriteBarrier();
    pThis->mpVtbl00 = (void*)0x148b3f8;
    pThis->mpVtbl04 = (void*)0x148b3e8;
    pThis->mpVtbl08 = (void*)0x148b3dc;
    *ppEmbed = (void*)0x140085c;
    pThis->mp24 = (void*)0x148b3c4;
    pThis->mp28 = (void*)0x148b3b4;
    _ReadWriteBarrier();

    pThis->mp30 = 0;
    pThis->mp34 = 0;
    pThis->mp38 = 0;
    pThis->mp3c = 0;
    pThis->mp40 = 0;
    pThis->mp44 = 0;
    pThis->mp48 = 0;
    pThis->mp4c = 0;
    pThis->mp50 = 0;
    pThis->mp54 = 0;
    pThis->mp58 = 0;
    pThis->map5c[0] = 0;
    pThis->map5c[1] = 0;
    pThis->map5c[2] = 0;
    pThis->map5c[3] = 0;
    pThis->map6c[0] = 0;
    pThis->map6c[1] = 0;
    pThis->map6c[2] = 0;
    pThis->map6c[3] = 0;
    pThis->mp7c = 0;
    pThis->mp80 = 0;
    pThis->mp84 = 0;
    pThis->mp88 = 0;
    pThis->mp8c = 0;
    pThis->mp90 = 0;
    pThis->mp94 = 0;
    pThis->mp98 = 0;
    pThis->mp9c = 0;
    pThis->mpA0 = 0;
    pThis->mpA4 = 0;
    pThis->mpA8 = 0;
    pThis->mpAC = 0;
    pThis->mpB0 = 0;

    pThis->mbC0 = 0;
    pThis->mbC1 = 0;
    pThis->mbC2 = 0;
    pThis->mbC3 = 0;
    _ReadWriteBarrier();

    uint32_t minus1 = (uint32_t)-1;
    pThis->mnB8 = (int32_t)minus1;
    pThis->mnBC = (int32_t)minus1;

    void* pBuf = &pThis->mBuf[0];
    pThis->mpD4 = pBuf;
    pThis->mpC8 = pBuf;
    pThis->mpC4 = pBuf;
    pThis->mpCC = (char*)pBuf + 0x10;
    _ReadWriteBarrier();

    pThis->mnF0 = 0;
    pThis->mnF4 = 0;
    pThis->mnF8 = 0;
    pThis->mnFC = 0;
    pThis->mn100 = 0;
    return pThis;
}

// @ 0x00ef6650
void cLargeAssetView::OnMessage(void* sender, uint32_t msgId)
{
    if (msgId == 0x5107b1a) {
        cPollinator* poll = Pollinator_Get();
        if (poll) {
            void* p48 = mp48;
            if (p48)
                (*(void (__thiscall**)(void*, int, int))
                 ((char*)*(void**)p48 + 0x7c))(p48, 1, 1);
            void* p44 = mp44;
            if (p44)
                (*(void (__thiscall**)(void*, int, int))
                 ((char*)*(void**)p44 + 0x7c))(p44, 1, 0);

            if (mp98) {
                ((uint8_t*)&msgId)[0] = 0;      // message id with the low byte cleared
                int64_t id = Meta_GetID64(mp98);

                struct EaString { void* mpBegin; void* mpEnd; void* mpCap; uint32_t mPad; } str;
                FormatString(&str, msgId, "tag:spore.com,2006:user/%I64u", id);

                Pollinator_Get()->SubscribeToFeed(str.mpBegin);

                if ((char*)str.mpCap - (char*)str.mpBegin > 1 && str.mpBegin)
                    operator_delete__(str.mpBegin);
            }
        }
    }
}
