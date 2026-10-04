// slice s00599c40 -- editor verb-icon tooltip setup (SP::cSPEditorVerbIcon), the editor budget/time
// bar panel (animated bars driven by a cSPUIAnimator), and small float / vector helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no EH, no stack cookies on wchar buffers).
#include "types.h"
#include <math.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
void  operator delete(void* p);                                             // 0x00f47380
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}

#pragma warning(disable:4035)
// EA math helpers: hand-written SSE asm.
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
__forceinline float FMin(float a, float b)
{
    __asm {
        movss xmm0, a
        minss xmm0, b
        movss a, xmm0
    }
    return a;
}
__forceinline float FMaxZero(float a)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, a
        movss a, xmm0
    }
    return a;
}


struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };
struct Rect {
    float left, top, right, bottom;
    Rect() {}
    Rect(const Rect& r) : left(r.left), top(r.top), right(r.right), bottom(r.bottom) {}
    float Width() const { return right - left; }
    float Height() const { return bottom - top; }
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

namespace eastl {
template <typename T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }

template <typename T> inline size_t CharStrlen(const T* p) { const T* q = p; while (*q) ++q; return (size_t)(q - p); }

struct allocator {};
class wstring {
public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    allocator mAllocator;

    wstring(const wchar_t* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~wstring()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete(mpBegin);
    }
    void RangeInitialize(const wchar_t* p);                                 // 0x00579a90
    wstring& append(const wchar_t* pBegin, const wchar_t* pEnd);            // 0x00429580
    wstring& operator+=(const wchar_t* p) { return append(p, p + CharStrlen(p)); }
    const wchar_t* c_str() const { return mpBegin; }
};
}  // namespace eastl

namespace EA { namespace Messaging {
void RemoveHandler(void* server, void* listener, const uint32_t* ids, uint32_t count, int priority);   // 0x00571db0
} }

namespace EA { namespace Locale {
int SetNumberString(int64_t value, wchar_t* buffer, int bufferSize);       // 0x00881ae0
} }

class IRefCounted {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
};

class IReleasable {
public:
    virtual void v00();
    virtual int Release();
};

namespace EA {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// UI windows
class IWindow;
class IWindowComponent {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual IWindow* GetWindow();                                           // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void GetTextBounds(Rect* bounds, int line, int flags);         // +0x20
};
class IWindowSlider {
public:
    virtual void v00();
    virtual void SetValue(float value);                                     // +0x04
};
class IWindow {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* GetComponent(uint32_t id);                                // +0x0c
    virtual IWindow* GetParent();                                           // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const Rect* GetArea();                                          // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetArea(const Rect* area);                                 // +0x6c
    virtual void v70();
    virtual void SetSize(float width, float height);                        // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                             // +0x7c
    virtual void SetCaption(const wchar_t* text);                           // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4();
    virtual void BringToFront(IWindow* child);                              // +0xe8
};

class cSPUILayout {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
    char pad4[0x18 - 4];
    cSPUILayout();                                                          // 0x00810000
    IWindow* FindWindowByID(uint32_t id, bool recursive);                   // 0x008105b0
    bool Init(const ResourceKey& key, bool visible, uint32_t parentID);    // 0x008120d0
    void SetParentWin(IWindow* parent, bool b, uint32_t id);                // 0x008121b0
    void Shutdown(bool b);                                                  // 0x00811ad0
};

// Animation target: vptr + window reference.
class cSPUIAnimTarget {
public:
    virtual ~cSPUIAnimTarget();
    IReleasable* mpWindow;
};
class cSPUIWindowAnimation {
public:
    virtual ~cSPUIWindowAnimation();
    int mType;
    cSPUIAnimTarget mTarget;
    uint32_t mParams[(0x80 - 0x10) / 4];
};
cSPUIWindowAnimation SPUICreateWindowAnimationTargetSize(IWindow* window, const Vector2& size, float duration);   // 0x007f8230

class cSPUIAnimator {
public:
    char data[0x20];
    cSPUIAnimator();                                                        // 0x007f83e0
    ~cSPUIAnimator();                                                       // 0x007f8c20
    void AddAnimation(cSPUIWindowAnimation* anim, IWindow* window, int flags);   // 0x007f8d10
    bool HasAnimation(IWindow* window, int flags);                          // 0x007f62c0
    void Update();                                                          // 0x007f63b0
};

namespace SPUIHelpers { float GetElapsedSeconds(float seconds, int flags); }   // 0x00805080

class cString {
public:
    uint32_t data[5];
    cString();                                                              // 0x006b5060
    ~cString();                                                             // 0x006b5240
    const wchar_t* c_str() const;                                           // 0x006b55c0
    bool Load(uint32_t tableID, uint32_t instanceID, int flags);            // 0x006b54b0
};

// ---------------------------------------------------------------------------------------------
namespace SP {

class cPropertyList {
public:
    virtual int AddRef();
    virtual int Release();
};
bool GetPropertyAsText(cPropertyList* list, uint32_t id, cString& out);                 // 0x006a1360
bool GetPropertyAsKey(cPropertyList* list, uint32_t id, ResourceKey* out);              // 0x006a1250
bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t* out);         // 0x006a12a0

class cPropertyManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, EA::AutoRefCount<cPropertyList>& out);   // +0x2c
};
cPropertyManager* PropertyManager();                                        // 0x0067de30

class cMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void AddListener(void* listener, uint32_t messageID);           // +0x24
};
cMessageServer* MessageServer();                                            // 0x0067dcc0

// EA::Messaging::AutoHandler
struct AutoHandler {
    AutoHandler() : mpServer(0), mpListener(0), mpIDs(0), mnCount(0), mnPriority(0) {}
    cMessageServer* mpServer;
    void* mpListener;
    const uint32_t* mpIDs;
    uint32_t mnCount;
    int mnPriority;

    void Init(cMessageServer* server, void* listener, const uint32_t* ids, uint32_t count, uint32_t messageID)
    {
        mpServer = server;
        mpListener = listener;
        mpIDs = ids;
        mnCount = count;
        mnPriority = 0;
        if (server && listener)
            server->AddListener(listener, messageID);
    }
    void Remove()
    {
        if (mpServer) {
            cMessageServer* server = mpServer;
            mpServer = 0;
            EA::Messaging::RemoveHandler(server, mpListener, mpIDs, mnCount, mnPriority);
        }
    }
    ~AutoHandler() { Remove(); }
};

// ---------------------------------------------------------------------------------------------
class cSPEditorVerbIcon {
public:
    char pad0[0xc];
    cSPUILayout mLayout;                                                    // +0x0c
    char pad24[0x78 - 0x24];
    Rect mArea;                                                             // +0x78
    Rect mTitleArea;                                                        // +0x88
    Rect mDescriptionArea;                                                  // +0x98

    void SetIcon(IWindow* window, const ResourceKey& key);                 // 0x00599730
    void SetupTooltip(int verbID, uint32_t propertyID);
};

extern const wchar_t kVerbTitleSeparator[];                                 // 0x013f639c

// ---------------------------------------------------------------------------------------------
class cEditorPanelBase0 {
public:
    virtual void Base0Fn();
    ~cEditorPanelBase0() {}
};
class IMessageListener {
public:
    virtual void Listener0();
    virtual bool HandleMessage(uint32_t messageID, void* message);
    IMessageListener() {}
    ~IMessageListener() {}
};
class cEditorPanelBase2 {
public:
    virtual void Base2Fn();
    cEditorPanelBase2() : mpOwner(0) {}
    ~cEditorPanelBase2() {}
    void* mpOwner;                                                          // +0x04
};

struct cMessageData {
    IWindow* mpWindow;
};
struct cCreatureStats {
    char pad0[0x28];
    int mbValid;                                                            // +0x28
    char pad2c[0xc4 - 0x2c];
    struct cCost { char pad[0x104]; float mCost; }* mpCost;                // +0xc4
};

struct cCreatureData {
    char pad0[0x56c];
    float mBaseTime;                                                        // +0x56c
    char pad570[0x640 - 0x570];
    float mComplexity;                                                      // +0x640
    float mCost;                                                            // +0x644
    char pad648[0x66c - 0x648];
    float mTimeRate;                                                        // +0x66c
};
float GetCreatureTime(uint32_t id);                                         // 0x004d12a0
extern float kMaxComplexity;                                                // 0x0150dd0c
extern const uint32_t kBudgetPanelMessages[];                               // 0x013f6438

class cEditorBudgetPanel : public cEditorPanelBase0, public IMessageListener, public cEditorPanelBase2 {
public:
    AutoHandler mMessageHandler;                                            // +0x10
    EA::AutoRefCount<cSPUILayout> mLayout;                                  // +0x24
    float mBarWidth;                                                        // +0x28
    float mBarHeight;                                                       // +0x2c
    cSPUIAnimator mAnimator;                                                // +0x30
    float mTimeBarWidth;                                                    // +0x50
    float mTimeBarHeight;                                                   // +0x54
    int mComplexityLevel;                                                   // +0x58
    int mCostLevel;                                                         // +0x5c
    float mValue;                                                           // +0x60
    float mMaxValue;                                                        // +0x64
    float mFillRate;                                                        // +0x68
    float mTime;                                                            // +0x6c
    float mMaxTime;                                                         // +0x70
    float mTimeFillRate;                                                    // +0x74
    float mTimeExtraRate;                                                   // +0x78
    bool mbReset;                                                           // +0x7c

    cEditorBudgetPanel();
    ~cEditorBudgetPanel();
    virtual void Base0Fn();
    virtual bool HandleMessage(uint32_t messageID, void* message);
    void Shutdown();
    void UpdateCostText();
    void UpdateTimeText();
    void Update(float deltaTime);
    void Init(IWindow* parent);
    void SetCreature(uint32_t timeMs, cCreatureData* data, uint32_t id);
};

}  // namespace SP

using namespace SP;

// @ 0x00599c40
void cSPEditorVerbIcon::SetupTooltip(int verbID, uint32_t propertyID)
{
    cSPUILayout* layout = &mLayout;
    IWindow* rootWindow = layout->FindWindowByID(0, true);
    EA::AutoRefCount<cPropertyList> verbProps;
    cString name;
    Rect area = mArea;
    if (rootWindow)
        rootWindow->SetArea(&mArea);

    IWindow* descWindow = layout->FindWindowByID(0x331cc0f, true);
    if (descWindow)
        descWindow->SetArea(&mDescriptionArea);

    if (PropertyManager()->GetPropertyList(verbID, 0xf865c777, verbProps = 0))
        GetPropertyAsText(verbProps, 0x54d95160, name);

    EA::AutoRefCount<cPropertyList> props;
    if (PropertyManager()->GetPropertyList(propertyID, 0x449505af, props = 0)) {
        IWindow* iconWindow = layout->FindWindowByID(0x677f65f, true);
        if (iconWindow) {
            ResourceKey key;
            key.instanceID = 0;
            key.typeID = 0;
            key.groupID = 0;
            GetPropertyAsKey(props, 0xd4d959e2, &key);
            if (key.instanceID)
                SetIcon(iconWindow, key);
        }

        IWindow* titleWindow = layout->FindWindowByID(0x331cc0e, true);
        if (titleWindow) {
            cString title;
            GetPropertyAsText(props, 0xd4d959e0, title);
            eastl::wstring text(name.c_str());
            text += kVerbTitleSeparator;
            text += title.c_str();
            titleWindow->SetCaption(text.c_str());
            Rect bounds;
            ((IWindowComponent*)titleWindow->GetComponent(0xf15f4bd))->GetTextBounds(&bounds, 0, 0);
            float textWidth = bounds.right - bounds.left;
            if (textWidth > mTitleArea.right - mTitleArea.left)
                area.right += textWidth - (mTitleArea.right - mTitleArea.left);
        }

        if (rootWindow)
            rootWindow->SetArea(&area);

        GetPropertyAsKeyInstance(props, 0xd4d959e3, (uint32_t*)&verbID);
        IWindow* w;
        if ((w = layout->FindWindowByID(0x6133600, true)) != 0) w->SetFlag(1, false);
        if ((w = layout->FindWindowByID(0x6133601, true)) != 0) w->SetFlag(1, false);
        if ((w = layout->FindWindowByID(0x6133602, true)) != 0) w->SetFlag(1, false);
        if ((w = layout->FindWindowByID(0x6133603, true)) != 0) w->SetFlag(1, false);

        uint32_t categoryWindow;
        switch (verbID) {
        case 0xad56080c: categoryWindow = 0x6133600; break;
        case 0xf71fa311: categoryWindow = 0x6133601; break;
        case 0xbeb528cb: categoryWindow = 0x6133602; break;
        case 0x2db6dad3: categoryWindow = 0x6133603; break;
        default: goto noCategory;
        }
        if ((w = layout->FindWindowByID(categoryWindow, true)) != 0)
            w->SetFlag(1, true);
noCategory:

        IWindow* typeWindow = layout->FindWindowByID(0x4d97710, true);
        if (typeWindow) {
            typeWindow->SetFlag(1, true);
            cString typeName;
            uint32_t textID;
            switch (verbID) {
            case 0xbeb528cb: textID = 0x67775e7; break;
            case 0xad56080c: textID = 0x67775b1; break;
            case 0xf71fa311: textID = 0x67775d9; break;
            case 0x2db6dad3: textID = 0x67775fa; break;
            default: goto noTypeName;
            }
            typeName.Load(0x9a5acf10, textID, 0);
            typeWindow->SetCaption(typeName.c_str());
        noTypeName:;
        }

        if (descWindow) {
            cString description;
            GetPropertyAsText(props, 0xd4d959e1, description);
            descWindow->SetCaption(description.c_str());
            Rect bounds;
            ((IWindowComponent*)descWindow->GetComponent(0xf15f4bd))->GetTextBounds(&bounds, 1, 0);
            area.bottom += (bounds.bottom - bounds.top) - (mDescriptionArea.bottom - mDescriptionArea.top);
        }
    }
    if (rootWindow)
        rootWindow->SetArea(&area);
}

// @ 0x0059a1c0
cSPUIAnimTarget::~cSPUIAnimTarget()
{
    if (mpWindow)
        mpWindow->Release();
}

// @ 0x0059a1e0
cSPUIWindowAnimation::~cSPUIWindowAnimation()
{
}

// @ 0x0059a230
// (scalar deleting destructor of cSPUIWindowAnimation, generated from the virtual dtor above)

// @ 0x0059a270
cEditorBudgetPanel::cEditorBudgetPanel()
    : mValue(0.0f), mMaxValue(1.0f), mFillRate(0.1f), mTime(0.0f), mMaxTime(1.0f), mTimeFillRate(30.0f),
      mComplexityLevel(0), mCostLevel(0), mbReset(false)
{
}

// @ 0x0059a320
cEditorBudgetPanel::~cEditorBudgetPanel()
{
}

// @ 0x0059a3b0
void cEditorBudgetPanel::Shutdown()
{
    mMessageHandler.Remove();
    if (mLayout) {
        mLayout->Shutdown(true);
        mLayout = 0;
    }
}

// @ 0x0059a400
void cEditorBudgetPanel::UpdateCostText()
{
    IWindow* window = mLayout->FindWindowByID(0x76b8598, true);
    if (window) {
        IWindowComponent* text = (IWindowComponent*)window->GetComponent(0xf15f4bd);
        if (text) {
            wchar_t buffer[64];
            EA::Locale::SetNumberString((int64_t)mValue, buffer, 64);
            text->GetWindow()->SetCaption(buffer);
        }
    }
}

// @ 0x0059a470
void cEditorBudgetPanel::UpdateTimeText()
{
    IWindow* window = mLayout->FindWindowByID(0x7bfa673, true);
    if (window) {
        IWindowComponent* text = (IWindowComponent*)window->GetComponent(0xf15f4bd);
        if (text) {
            wchar_t buffer[64];
            EA::Locale::SetNumberString(CeilToInt(mTime), buffer, 64);
            text->GetWindow()->SetCaption(buffer);
        }
    }
}

extern const float kBarEpsilon;                                             // 0x013f11c8
extern const float kBarResetSeconds;                                        // 0x013f63f8

// @ 0x0059a500
void cEditorBudgetPanel::Update(float deltaTime)
{
    IWindow* bar = mLayout->FindWindowByID(0x7607a70, true);
    if (mbReset) {
        Vector2 size;
        size.x = mValue / (mMaxValue + kBarEpsilon) * mBarWidth;
        size.y = mBarHeight;
        mbReset = false;
        cSPUIWindowAnimation anim = SPUICreateWindowAnimationTargetSize(bar, size, SPUIHelpers::GetElapsedSeconds(kBarResetSeconds, 0));
        mAnimator.AddAnimation(&anim, bar, 1);
    } else if (!mAnimator.HasAnimation(bar, 1)) {
        if (mValue < mMaxValue) {
            float value = mValue + mFillRate * deltaTime * 10.0f;
            mValue = FMin(value, mMaxValue);
            bar->SetSize(mBarWidth * mValue / (kBarEpsilon + mMaxValue), mBarHeight);
        } else if (mValue > mMaxValue) {
            mValue = mValue - mFillRate * deltaTime * 10.0f;
            bar->SetSize(mBarWidth, mBarHeight);
        } else {
            goto updateTime;
        }
        UpdateCostText();
    }
updateTime:
    IWindow* timeBar = mLayout->FindWindowByID(0x7bfa675, true);
    if (mTime < mMaxTime) {
        float t = mTime + (mTimeExtraRate + mTimeFillRate) * deltaTime;
        mTime = FMin(t, mMaxTime);
        timeBar->SetSize(mTimeBarWidth * mTime / (kBarEpsilon + mMaxTime), mTimeBarHeight);
        UpdateTimeText();
    } else if (mTime > mMaxTime) {
        mTime = mTime - (mTimeExtraRate + mTimeFillRate) * deltaTime;
        timeBar->SetSize(mTimeBarWidth, mTimeBarHeight);
        UpdateTimeText();
    }
    mAnimator.Update();
}

// @ 0x0059a770
bool cEditorBudgetPanel::HandleMessage(uint32_t messageID, void* message)
{
    if (messageID == 0x4aca143) {
        IWindow* window = ((cMessageData*)message)->mpWindow;
        if (window) {
            cCreatureStats* stats = (cCreatureStats*)window->GetComponent(0x4ac90b5);
            if (stats && stats->mbValid && stats->mpCost) {
                float value = mValue - stats->mpCost->mCost;
                mValue = FMaxZero(value);
                mbReset = true;
            }
        }
    }
    return false;
}

// @ 0x0059a7f0
void cEditorBudgetPanel::Init(IWindow* parent)
{
    mLayout = new("Editor", 0, 0, 0, 0) cSPUILayout();
    ResourceKey key;
    key.instanceID = 0x6dd7de95;
    key.typeID = 0x510a95b;
    key.groupID = 0x40464100;
    mLayout->Init(key, true, 0x5b598fa);
    mLayout->SetParentWin(parent, true, 0x5b598fa);
    mLayout->FindWindowByID(0x7607a78, true);
    parent->GetParent()->BringToFront(parent);

    IWindow* bar = mLayout->FindWindowByID(0x7607a70, true);
    mBarWidth = bar->GetArea()->Width();
    mBarHeight = bar->GetArea()->Height();
    mLayout->FindWindowByID(0x7bfa675, true);       // result unused: the time bar is measured from `bar`
    mTimeBarWidth = bar->GetArea()->Width();
    mTimeBarHeight = bar->GetArea()->Height();
    UpdateCostText();

    mMessageHandler.Init(MessageServer(), static_cast<IMessageListener*>(this), kBudgetPanelMessages, 1, 0x4aca143);
}

// @ 0x0059a980
void cEditorBudgetPanel::SetCreature(uint32_t timeMs, cCreatureData* data, uint32_t id)
{
    if (data) {
        float time = GetCreatureTime(id) + data->mBaseTime;
        mMaxTime = (float)CeilToInt(time);
        mMaxValue = data->mCost;
        mFillRate = data->mComplexity;
        mTimeExtraRate = data->mTimeRate;
        mCostLevel = RoundToInt(mMaxValue * 0.00036363635f);
        if (mCostLevel >= 4)
            mCostLevel = 3;
        else if (mCostLevel < 1)
            mCostLevel = 1;
        mComplexityLevel = RoundToInt(mFillRate / kMaxComplexity * 4.0f);
        if (mComplexityLevel >= 4)
            mComplexityLevel = 3;
        else if (mComplexityLevel < 1)
            mComplexityLevel = 1;

        IWindow* w = mLayout->FindWindowByID(0x760d080, true);
        if (w) {
            IWindowSlider* slider = (IWindowSlider*)w->GetComponent(0x10edf11);
            if (slider)
                slider->SetValue((float)mCostLevel * 33.333332f);
        }
        w = mLayout->FindWindowByID(0x75f9168, true);
        if (w) {
            IWindowSlider* slider = (IWindowSlider*)w->GetComponent(0x10edf11);
            if (slider)
                slider->SetValue((float)mComplexityLevel * 33.333332f);
        }
    }
    Update((float)timeMs * 0.001f);
}

union FloatBits { float f; uint32_t i; };

// @ 0x0059ab10
int IsFiniteFloat(float f)
{
    FloatBits u;
    u.f = f;
    if ((u.i & 0x7fffffff) == 0 || ((u.i - 0x800000) & 0x7f800000) < 0x7f000000)
        return 1;
    return 0;
}

// @ 0x0059ab50
float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}

static inline bool IsFiniteInline(float f)
{
    FloatBits u;
    u.f = f;
    return (u.i & 0x7fffffff) == 0 || ((u.i - 0x800000) & 0x7f800000) < 0x7f000000;
}

// @ 0x0059ab70
int IsFiniteVector(const Vector3& v)
{
    if (IsFiniteInline(v.x) && IsFiniteInline(v.y) && IsFiniteInline(v.z))
        return 1;
    return 0;
}

extern float kPi;                                                           // 0x0150de58

// @ 0x0059ac00
float WrapAngle(float angle)
{
    float twoPi = kPi + kPi;
    float a = fmodf(angle, twoPi);
    if (a > kPi)
        return a - twoPi;
    if (a < -kPi)
        return a + twoPi;
    return a;
}

struct cSmoothedVector {
    char pad0[0x58];
    Vector3 mTarget;                                                        // +0x58
    Vector3 mCurrent;                                                       // +0x64
    void SetTarget(const Vector3& v, bool immediate);
};

// @ 0x0059ac60
void cSmoothedVector::SetTarget(const Vector3& v, bool immediate)
{
    mTarget = v;
    if (immediate)
        mCurrent = v;
}

struct cIDHolder {
    char pad0[0x1c];
    uint32_t mID;                                                           // +0x1c
    bool IsID(uint32_t id) const;
};

// @ 0x0059ac90
bool cIDHolder::IsID(uint32_t id) const
{
    return mID == id;
}
