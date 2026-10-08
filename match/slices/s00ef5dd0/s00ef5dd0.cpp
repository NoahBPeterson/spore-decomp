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

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, int recursive);           // 0x008105b0
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

struct cSPEditorVerbIconTray { int pad[0x19]; int mAdventurePoints; /* +0x64 */ };
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
