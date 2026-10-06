// Slice s00e11ab0 (frozen batch op1_big #77).
//
// 0x00e11ab0 is cSPUIMinimapWin::HandleMessage (the IHandler override; `this` is the
// IHandlerRC subobject at +0x214 of the window).  The PDB "anchor" name
// vector<slot_vector_entry<cGroupMovement>>::DoInsertValue is a mislabel: the neighbours
// (0x00e0f9c0 RemoveIcon, 0x00e10580 AddIcon, 0x00e10e30 draw_trade_routes) are all
// cSPUIMinimapWin, and the body calls RemoveIcon/AddIcon on this-0x214.
//
// UI module: /arch:SSE (movss float copies, x87 float args), no /EHsc (the AutoRefCount
// image local and the cIconInfo copy get no EH frame).

#include "types.h"

typedef unsigned int uint32;

// ---------------------------------------------------------------------------
//  UTFWin interfaces (vtable slots from the ModAPI IWindow header; verified against the asm)
// ---------------------------------------------------------------------------
namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
    float GetWidth() const { return x2 - x1; }
    float GetHeight() const { return y2 - y1; }
};
}

class IWindow;

class IWinProc {
public:
    virtual int AddRef();
    virtual int Release();
};

class Object {
public:
    virtual int AddRef();                        // 0x00
    virtual int Release();                       // 0x04
    virtual void v08();                          // 0x08
    virtual void* Cast(uint32 typeID) const;     // 0x0c
};

class IWindow : public Object {
public:
    virtual IWindow* GetParent() const;                        // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual const Math::Rectangle& GetRealArea() const;        // 0x38
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void SetControlID(uint32 controlID);               // 0x50
    virtual void v54();
    virtual void v58();
    virtual void SetShadeColor(uint32 color);                  // 0x5c
    virtual void SetArea(const Math::Rectangle& area);         // 0x60
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void SetFlag(uint32 flag, bool value);             // 0x7c
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual int Invalidate();                                  // 0x90
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    virtual void vc0();
    virtual void vc4();
    virtual void vc8();
    virtual void vcc();
    virtual void vd0();
    virtual void vd4();
    virtual void AddWindow(IWindow* pWindow);                  // 0xd8
    virtual void vdc();
    virtual void DisposeWindowFamily(IWindow* pChild);         // 0xe0
    virtual void ve4();
    virtual void BringToFront(IWindow* pWindow);               // 0xe8
    virtual void vec();
    virtual IWindow* FindWindowByID(uint32 controlID, bool bRecursive);  // 0xf0
    virtual void vf4();
    virtual void vf8();
    virtual void vfc();
    virtual void v100();
    virtual void AddWinProc(IWinProc* pWinProc);               // 0x104
};

class Image {
public:
    virtual int AddRef();
    virtual int Release();
};

class UILayout;

template <class T> class AutoRefCount {
public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p);                   // out of line (0x00b5f950)
    T* get() const { return mpObject; }
};

// object_cast-style interface query: NULL stays NULL.
template <class T> inline T* object_cast(Object* p, uint32 typeID) {
    return p ? (T*)p->Cast(typeID) : 0;
}

namespace SPUIHelpers {
Image* GetImageFromLayout(UILayout* pLayout, uint32 controlID);
void SetDrawableImage(IWindow* pWindow, Image* pImage, int index);
void AnchorWindowToWindow(IWindow* pAnchor, IWindow* pWindow, uint32 flags, int offset);
float GetElapsedSeconds();
}

// EA allocator plumbing: new(align, name, allocator) T(...)
class ICoreAllocator;
ICoreAllocator* GetUIAllocator();                                  // 0x009512c0
void* operator new(size_t size, size_t align, const char* pName, ICoreAllocator* pAlloc);  // 0x009512d0

// ---------------------------------------------------------------------------
//  Window and behavior classes created here (constructors are out of line)
// ---------------------------------------------------------------------------
class WinPrimary {
public:
    virtual void p00();
};

// image window used for attack icons (size 0x20c, IWindow at +4)
class cSPUIImageWin : public WinPrimary, public IWindow {
public:
    cSPUIImageWin();                                               // 0x007f3160
    uint32 pad[(0x20c - 8) / 4];
};

class cSPUIAnimatedIconWin;
// the animated-icon interface returned by Cast(0x106f146)
class IAnimatedIcon {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
    virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
    virtual void s70(); virtual void s74(); virtual void s78(); virtual void s7c();
    virtual void s80(); virtual void s84(); virtual void s88();
    virtual void SetPeriod(int msec);                          // 0x8c
    void SetImage(Image* pImage, int columns, int rows, int frames);   // 0x007f59e0
};

// animated comm icon window (size 0x2c8, IWindow at +4)
class cSPUIAnimatedIconWin : public WinPrimary, public IWindow {
public:
    cSPUIAnimatedIconWin();                                        // 0x007f5c20
    uint32 pad[(0x2c8 - 8) / 4];
};

class IBehaviorAction {
public:
    virtual void a00();
};

class IBehaviorEventBase {
public:
    virtual void e00(); virtual void e04(); virtual void e08(); virtual void e0c();
    virtual void e10(); virtual void e14(); virtual void e18(); virtual void e1c();
    virtual void e20(); virtual void e24(); virtual void e28(); virtual void e2c();
    virtual void AddAction(IBehaviorAction* pAction);          // 0x30
};

class cSPUIBehaviorWinBoolStateEvent : public Object {
public:
    cSPUIBehaviorWinBoolStateEvent(int state, uint32 eventID, uint32 controlID, int flags);  // 0x007ff470
    uint32 pad04[(0x18 - 4) / 4];
    IBehaviorEventBase mEvents;                                    // +0x18
    uint32 pad1c[(0x90 - 0x1c) / 4];
};

class cSPUIBehaviorWinInterpolatorScale {
public:
    cSPUIBehaviorWinInterpolatorScale();                           // 0x007ff620
    virtual void i00(); virtual void i04(); virtual void i08(); virtual void i0c();
    virtual void i10(); virtual void i14(); virtual void i18(); virtual void i1c();
    virtual void i20(); virtual void i24(); virtual void i28(); virtual void i2c();
    virtual void SetRange(float from, float to);              // 0x30
    uint32 pad[(0x24 - 4) / 4];
};

class cSPUIBehaviorTimeFunctionDampedPeriodic {
public:
    cSPUIBehaviorTimeFunctionDampedPeriodic(int mode);             // 0x007fd610
    void SetParameters(float period, float phase, float offset, float amplitude,
                       float damping, int repeat);                 // 0x007fd650
    uint32 pad[0x50 / 4];
};

class cSPUIBehaviorActionWinInterpolator : public IBehaviorAction {
public:
    cSPUIBehaviorActionWinInterpolator();                          // 0x007fdab0
    void SetTimeFunction(cSPUIBehaviorTimeFunctionDampedPeriodic* pFunc);   // 0x007fdb60
    void SetInterpolator(cSPUIBehaviorWinInterpolatorScale* pInterp);       // 0x007fdb90
    uint32 pad[(0x60 - 4) / 4];
};

// ---------------------------------------------------------------------------
//  Game-side helpers
// ---------------------------------------------------------------------------
class cGameModeManager {
public:
    uint32 GetActiveModeID();                                      // 0x00a42730
};
cGameModeManager* GameModeManager();                               // 0x00b3d320

namespace SP {
uint32 GetCurrentGameMode();                                       // 0x00b5b800
class cCivilization;
class cGameNounManager {
public:
    cCivilization* GetPlayerCivilization();                        // 0x00b25fb0
    uint32 GetPlayerEmpireOrMinus1();                              // 0x00b1f9d0
};
cGameNounManager* NounManager();                                   // 0x00b3d300
}

static const uint32 kModeEditor = 0x1654c05;
static const uint32 kModeCiv    = 0x1654c04;

// Visibility interface embedded in game objects (+0x34 in cities etc., +0x120 in the
// placement object): slot 0x58 is the "visible to the player" test.
class IVisibility {
public:
    virtual void q00(); virtual void q04(); virtual void q08(); virtual void q0c();
    virtual void q10(); virtual void q14(); virtual void q18(); virtual void q1c();
    virtual void q20(); virtual void q24(); virtual void q28(); virtual void q2c();
    virtual void q30(); virtual void q34(); virtual void q38(); virtual void q3c();
    virtual void q40(); virtual void q44(); virtual void q48(); virtual void q4c();
    virtual void q50(); virtual void q54();
    virtual bool IsVisible();                                  // 0x58
};

struct cMapObject {                    // a city / vehicle that owns a minimap icon
    uint32 pad[0x34 / 4];
    IVisibility mVisibility;           // +0x34
};

struct cPlacedObject {                 // result of the 0x00ac86d0 lookup
    uint32 pad[0x120 / 4];
    IVisibility mVisibility;           // +0x120
};

void* LookupMinimapObjectA(uint32 key);                            // 0x00ac8730 (cdecl)
cPlacedObject* LookupMinimapObjectB(uint32 key);                   // 0x00ac86d0 (cdecl)

struct KeyVector { uint32* mpBegin; uint32* mpEnd; };
struct cKeyListOwner {
    KeyVector& GetKeys();                                          // 0x00bef6c0
};

// global vector_map<uint32, FeedbackFlags> at 0x016a204c
struct FeedbackFlags { uint32 m0; bool mbSeen; };
struct FeedbackFlagsMap {
    FeedbackFlags& operator[](const uint32& key);                  // 0x00e11910
};
extern FeedbackFlagsMap gMinimapFeedbackFlags;

// ---------------------------------------------------------------------------
//  Message payload: EA::Messaging message object
// ---------------------------------------------------------------------------
struct cIconInfo;
struct MinimapMsg {
    void* vtable;
    int mRefCount;
    uint32 mKey;          // +0x08 object / control id
    uint32 m0c;
    uint32 mValue;        // +0x10 color / id
    uint32 m14;
    uint32 mType;         // +0x18 (also a cIconInfo* for 0x1c8c174)
    uint32 m1c;
    uint32 mEmpireID;     // +0x20
};

// ---------------------------------------------------------------------------
//  cSPUIMinimapWin
// ---------------------------------------------------------------------------
class RefObject {
public:
    virtual int AddRef();
    virtual int Release();
};

struct cIconInfo {                     // size 0x24
    uint32 mType;                      // +0x00
    float mX, mY, mZ;                  // +0x04
    uint32 mFlags;                     // +0x10
    AutoRefCount<RefObject> mpObject;  // +0x14
    float mTimeout;                    // +0x18
    uint32 mAnimState;                 // +0x1c
    uint32 m20;                        // +0x20
    cIconInfo(const cIconInfo& other);                             // 0x00e0bd70
};

struct IconMapNode {
    IconMapNode* mpNodeRight;
    IconMapNode* mpNodeLeft;
    IconMapNode* mpNodeParent;
    char mColor;
    uint32 mKey;                       // +0x10
    cIconInfo mValue;                  // +0x14
};

IconMapNode* RBTreeIncrement(const IconMapNode* pNode);            // 0x00921580 (cdecl)

struct IconMapIterator {
    IconMapNode* mpNode;
    IconMapIterator() : mpNode(0) {}
    IconMapIterator(IconMapNode* p) : mpNode(p) {}
    IconMapIterator(const IconMapIterator& x) : mpNode(x.mpNode) {}
    cIconInfo* operator->() const { return &mpNode->mValue; }
    IconMapIterator& operator++() { mpNode = RBTreeIncrement(mpNode); return *this; }
    bool operator==(const IconMapIterator& x) const { return mpNode == x.mpNode; }
    bool operator!=(const IconMapIterator& x) const { return mpNode != x.mpNode; }
};

struct IconMap {                       // eastl::map<uint32, cIconInfo>
    uint32 mCompare;                   // +0x00
    IconMapNode* mAnchorRight;         // +0x04 anchor
    IconMapNode* mAnchorLeft;          // +0x08
    IconMapNode* mAnchorParent;        // +0x0c
    char mAnchorColor;                 // +0x10
    uint32 mnSize;
    uint32 mAllocator;
    IconMapIterator find(const uint32& key);                       // 0x00e5c780
    IconMapIterator begin() { return IconMapIterator(mAnchorLeft); }
    IconMapIterator end() { return IconMapIterator((IconMapNode*)&mAnchorRight); }
};

class IHandlerRC {
public:
    virtual int AddRef();
    virtual int Release();
    virtual bool HandleMessage(uint32 messageID, void* pMessage);
};

class MinimapWinPrimary {
public:
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70(); virtual void w74(); virtual void w78(); virtual void w7c();
    virtual void w80(); virtual void w84(); virtual void w88();
    virtual void RebuildLayout();                              // 0x8c
};

class MinimapWindowPart : public IWindow {
public:
    uint32 padWindow[(0x214 - 8) / 4];
};

class cSPUIMinimapWin : public MinimapWinPrimary, public MinimapWindowPart, public IHandlerRC {
public:
    bool HandleMessage(uint32 messageID, void* pMessage);

    void RemoveIcon(uint32 id, bool bRemoveWindow, int flags);     // 0x00e0f9c0
    void AddIcon(uint32 id, const cIconInfo& info, int a, int b);  // 0x00e10580
    void SetIconColor(uint32 id, uint32 color);                    // 0x00e0c490
    void UpdateMapTexture();                                       // 0x00e0e1a0

    void ShowAttackIcon(IWindow* pWin, IconMapIterator it, uint32 id, uint32 color,
                        uint32 imageID, float decay, float duration);
    void ShowCommIcon(IWindow* pWin, IconMapIterator it, uint32 id, uint32 color,
                      uint32 imageID, float width, float height, int rows, int frames);

    uint32 padHandler[(0x24 - 4) / 4];
    bool mbPaused;                                 // +0x238 (handler +0x24)
    uint32 pad239[(0x38 - 0x28) / 4];
    AutoRefCount<RefObject> mpPendingTexture;      // +0x24c (handler +0x38)
    uint32 pad250[(0x44 - 0x3c) / 4];
    UILayout* mpLayout;                            // +0x258 (handler +0x44)
    uint32 pad25c[(0x108 - 0x48) / 4];
    IconMap mIconInfos;                            // +0x31c (handler +0x108)
    uint32 pad338[(0x148 - 0x124) / 4];
    uint32 mPendingFlags;                          // +0x35c (handler +0x148)
};

static inline void ReleaseRef(AutoRefCount<RefObject>& p) {
    RefObject* old = p.mpObject;
    if (old) {
        p.mpObject = 0;
        old->Release();
    }
}

// Attack icon: a pulsing image window over the target's icon (control id = key + 1).
__forceinline void cSPUIMinimapWin::ShowAttackIcon(IWindow* pWin, IconMapIterator it, uint32 id,
                                            uint32 color, uint32 imageID, float decay,
                                            float duration) {
    IWindow* pIcon = pWin->GetParent()->FindWindowByID(id, false);
    if (!pIcon) {
        AutoRefCount<Image> image;
        image = SPUIHelpers::GetImageFromLayout(mpLayout, imageID);

        pIcon = new (4, "UI/CivMinimap/AttackIcon", GetUIAllocator()) cSPUIImageWin();
        SPUIHelpers::SetDrawableImage(pIcon, image.get(), -1);

        float width = pWin->GetRealArea().GetWidth();
        float height = pWin->GetRealArea().GetHeight();
        pIcon->SetControlID(id);
        pIcon->SetArea(Math::Rectangle(0.0f, 0.0f, width, height));
        pIcon->SetFlag(1, true);
        pIcon->SetFlag(0x10, true);
        pWin->GetParent()->AddWindow(pIcon);
        SPUIHelpers::AnchorWindowToWindow(pWin, pIcon, 0x300, 0);
        if (!(it->mFlags & 1)) {
            pIcon->GetParent()->BringToFront(pIcon);
        }
        pIcon->SetShadeColor(color);

        cSPUIBehaviorWinBoolStateEvent* pEvent =
            new (4, "CivMinimap/AttackAnimation", GetUIAllocator())
                cSPUIBehaviorWinBoolStateEvent(1, 0x25a5f84, id, 0);
        pIcon->AddWinProc(object_cast<IWinProc>(pEvent, 0x2f009dd0));
        it->mAnimState = 0;

        cSPUIBehaviorWinInterpolatorScale* pScale =
            new (4, "CivMinimap/AttackAnimation", GetUIAllocator()) cSPUIBehaviorWinInterpolatorScale();
        pScale->SetRange(1.5f, 2.5f);

        cSPUIBehaviorTimeFunctionDampedPeriodic* pTime =
            new (4, "CivMinimap/AttackAnimation", GetUIAllocator()) cSPUIBehaviorTimeFunctionDampedPeriodic(1);
        pTime->SetParameters(100.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1);
        pTime->SetParameters(decay, 0.0f, 0.0f, 2.0f, 1e-5f, -1);

        cSPUIBehaviorActionWinInterpolator* pAction =
            new (8, "CivMinimap/AttackAnimation", GetUIAllocator()) cSPUIBehaviorActionWinInterpolator();
        pAction->SetInterpolator(pScale);
        pAction->SetTimeFunction(pTime);
        pEvent->mEvents.AddAction(pAction);
    }
    it->mTimeout = SPUIHelpers::GetElapsedSeconds() + duration;
    pIcon->Invalidate();
}

// Comm icon: an animated icon next to the target's icon (control id = key + 3).
__forceinline void cSPUIMinimapWin::ShowCommIcon(IWindow* pWin, IconMapIterator it, uint32 id,
                                          uint32 color, uint32 imageID, float width,
                                          float height, int rows, int frames) {
    IWindow* pIcon = pWin->GetParent()->FindWindowByID(id, false);
    if (!pIcon) {
        AutoRefCount<Image> image;
        image = SPUIHelpers::GetImageFromLayout(mpLayout, imageID);

        pIcon = new (8, "UI/CivMinimap/CommIcon", GetUIAllocator()) cSPUIAnimatedIconWin();
        pIcon->SetControlID(id);
        pIcon->SetArea(Math::Rectangle(0.0f, 0.0f, width, height));
        pIcon->SetFlag(1, true);
        pIcon->SetFlag(0x10, true);
        pWin->GetParent()->AddWindow(pIcon);
        SPUIHelpers::AnchorWindowToWindow(pWin, pIcon, 0x300, 0);
        if (!(it->mFlags & 1)) {
            pIcon->GetParent()->BringToFront(pIcon);
        }
        pIcon->SetShadeColor(color);

        IAnimatedIcon* pAnim = (IAnimatedIcon*)pIcon->Cast(0x106f146);
        pAnim->SetImage(image.get(), 4, rows, frames);
        pAnim->SetPeriod(500);
    }
    pIcon->Invalidate();
}

// @ 0x00e11ab0
bool cSPUIMinimapWin::HandleMessage(uint32 messageID, void* pMessage) {
    MinimapMsg* msg = (MinimapMsg*)pMessage;
    IWindow* attackWin;
    IconMapIterator attackIt;
    uint32 attackID;
    uint32 attackColor;

    switch (messageID) {
    case 0x19d6324:
        SetIconColor(msg->mKey, msg->mValue);
        break;

    case 0x164b4eb:
        if (msg) {
            uint32 color = msg->mValue;
            IWindow* pWin = FindWindowByID(msg->mKey, false);
            if (pWin) {
                pWin->SetShadeColor(color);
            }
        }
        break;

    case 0x1c3d2e0:
        mPendingFlags |= (uint32)pMessage;
        break;

    case 0x1c8c174:
        if (msg) {
            RemoveIcon(msg->mKey, true, 0);
            uint32 id = msg->mValue;
            cIconInfo info(*(const cIconInfo*)msg->mType);
            AddIcon(id, info, 0, 0);
        }
        break;

    case 0x1e8c9df:
        RemoveIcon(msg->mKey, true, 0);
        break;

    case 0x354b9e8: {
        if (GameModeManager()->GetActiveModeID() == kModeEditor) break;
        uint32 key = msg->mKey;
        uint32 color = msg->mValue;
        cMapObject* pObject = (cMapObject*)key;
        if (GameModeManager()->GetActiveModeID() != kModeEditor && pObject &&
            !pObject->mVisibility.IsVisible())
            break;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        break;
    }

    case 0x30aa01b: {
        if (!msg) break;
        void* pA = LookupMinimapObjectA(msg->mKey);
        cPlacedObject* pB = LookupMinimapObjectB(msg->mKey);
        if (!pA && !pB) break;
        uint32 color = msg->mValue;
        uint32 key = pA ? (uint32)pA : (uint32)pB;
        uint32 empireID = msg->mEmpireID;
        SP::cCivilization* pCiv = pA ? 0 : SP::NounManager()->GetPlayerCivilization();
        if (GameModeManager()->GetActiveModeID() != kModeEditor && pB && pCiv &&
            !pB->mVisibility.IsVisible()) {
            if (SP::NounManager()->GetPlayerEmpireOrMinus1() != empireID) break;
        }
        if (msg->mType == 1) {
            IconMapIterator it = mIconInfos.find(key);
            if (it == mIconInfos.end()) break;
            IWindow* pWin = FindWindowByID(key, true);
            if (!pWin) break;
            if (!(it->mFlags & 1)) {
                BringToFront(pWin);
            }
            attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        } else {
            IconMapIterator it = mIconInfos.find(key);
            if (it == mIconInfos.end()) break;
            IWindow* pWin = FindWindowByID(key, true);
            if (!pWin) break;
            if (!(it->mFlags & 1)) {
                BringToFront(pWin);
            }
            attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        }
        break;
    }

    case 0x3ac86ad:   // game paused: freeze attack animations
        if (SP::GetCurrentGameMode() == kModeCiv && !mbPaused) {
            mbPaused = true;
            float now = SPUIHelpers::GetElapsedSeconds();
            IWindow* pChild = 0;
            for (IconMapIterator it = mIconInfos.begin(); it != mIconInfos.end(); ++it) {
                uint32 key = it.mpNode->mKey;
                if (it->mFlags & 0x40103) {
                    IWindow* pWin = FindWindowByID(key, true);
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 1, true);
                    }
                    if (pChild) {
                        pChild->SetFlag(1, false);
                        it->mTimeout -= now;
                    }
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 3, true);
                    }
                    if (pChild) {
                        pWin->GetParent()->DisposeWindowFamily(pChild);
                    }
                }
            }
        }
        break;

    case 0x3ac86b5:   // game resumed
        if (SP::GetCurrentGameMode() == kModeCiv && mbPaused) {
            mbPaused = false;
            float now = SPUIHelpers::GetElapsedSeconds();
            IWindow* pChild = 0;
            for (IconMapIterator it = mIconInfos.begin(); it != mIconInfos.end(); ++it) {
                uint32 key = it.mpNode->mKey;
                if (it->mFlags & 0x40103) {
                    IWindow* pWin = FindWindowByID(key, true);
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 1, true);
                    }
                    if (pChild) {
                        it->mTimeout += now;
                    }
                    if (pWin) {
                        pChild = pWin->GetParent()->FindWindowByID(key + 3, true);
                    }
                    if (pChild) {
                        pWin->GetParent()->DisposeWindowFamily(pChild);
                    }
                }
            }
        }
        break;

    case 0x44448ed: {
        uint32 mode = SP::GetCurrentGameMode();
        if (mode == kModeEditor || mode == kModeCiv) {
            mPendingFlags |= 2;
        }
        break;
    }

    case 0x44edd9c:
        ReleaseRef(mpPendingTexture);
        Invalidate();
        RebuildLayout();
        mPendingFlags |= 4;
        UpdateMapTexture();
        break;

    case 0x53039b6: {
        if (GameModeManager()->GetActiveModeID() == kModeEditor) break;
        uint32 color = msg->mValue;
        uint32 key = msg->mKey;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        ShowAttackIcon(pWin, it, key + 1, color, 0x5e51b9d, 50.0f, 10.0f);
        break;
    }

    case 0x55d55d9: {
        if (!msg) break;
        uint32 key = msg->mKey;
        if (!key) break;
        uint32 color = msg->mValue;
        cMapObject* pObject = (cMapObject*)key;
        if (GameModeManager()->GetActiveModeID() != kModeEditor && pObject &&
            !pObject->mVisibility.IsVisible())
            break;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        break;
    }

    case 0x58b817b: {
        if (!msg) break;
        uint32 key = msg->mKey;
        if (!key) break;
        uint32 color = msg->mValue;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        ShowCommIcon(pWin, it, key + 3, color, 0x5e51bed, 42.0f, 42.0f, 4, 0xf);
        break;
    }

    case 0x58b8189: {
        if (!msg) break;
        uint32 key = msg->mKey;
        if (!key) break;
        uint32 color = msg->mValue;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        ShowCommIcon(pWin, it, key + 3, color, 0x5e51bdf, 65.0f, 43.0f, 2, 7);
        break;
    }

    case 0x58b8f28: {
        if (!msg) break;
        cKeyListOwner* pOwner = (cKeyListOwner*)msg->mKey;
        if (!pOwner) break;
        uint32 color = msg->mValue;
        KeyVector& keys = pOwner->GetKeys();
        for (uint32* pKey = keys.mpBegin; pKey != keys.mpEnd; ++pKey) {
            uint32 key = *pKey;
            IconMapIterator it = mIconInfos.find(key);
            if (it == mIconInfos.end()) continue;
            IWindow* pWin = FindWindowByID(key, true);
            if (!pWin) continue;
            if (!(it->mFlags & 1)) {
                BringToFront(pWin);
            }
            ShowCommIcon(pWin, it, key + 3, color, 0x5e51bdf, 65.0f, 43.0f, 2, 7);
        }
        break;
    }

    case 0x5c3bed8: {
        uint32 color = msg->mValue;
        uint32 key = msg->mKey;
        IconMapIterator it = mIconInfos.find(key);
        if (it == mIconInfos.end()) break;
        IWindow* pWin = FindWindowByID(key, true);
        if (!pWin) break;
        if (!(it->mFlags & 1)) {
            BringToFront(pWin);
        }
        attackWin = pWin; attackIt = it; attackID = key + 1; attackColor = color;
        goto show_attack;
        break;
    }

    case 0x66603cd:
        gMinimapFeedbackFlags[msg->mKey].mbSeen = true;
        break;
    }
    return false;

show_attack:
    // the common attack-icon tail shared by 0x354b9e8, 0x30aa01b, 0x55d55d9 and 0x5c3bed8
    ShowAttackIcon(attackWin, attackIt, attackID, attackColor, 0x5e51b8c, 10.0f, 2.0f);
    return false;
}
