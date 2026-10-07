// Slice s005ed750: SP::cSPPaletteItemRollover::Show (3370 bytes) -- the palette-item
// rollover: fills name / price / icon / error-reason windows from the item's property
// list and lays the rollover out.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (UI module: no /EHsc, no cookie).
//
// Retail layout: cSPUIPropertyLayout is 0x78 bytes (ModAPI), so the 2008 PDB's members
// sit 0x10 higher, and retail adds the icon and error-reason windows (0x98, 0xa0..0xac).
#include "types.h"

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
};
}  // namespace Math

namespace eastl {
template <typename T>
inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }

extern wchar_t gEmptyString16[1];  // 0x01667bac
class string16 {   // eastl::basic_string<wchar_t>
 public:
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    const char* mpName;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16() { DeallocateSelf(); }
    void DeallocateSelf();  // 0x00933960
};
}  // namespace eastl

namespace EA { namespace UTFWin {
class IWindow {
 public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual IWindow* GetParent();                               // +0x10
    virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual uint32_t GetFlags();                                // +0x28
    virtual void v0b(); virtual void v0c(); virtual void v0d();
    virtual const Math::Rectangle& GetRealArea();               // +0x38 (ModAPI GetRealArea)
    virtual void v0f(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void SetShadeColor(uint32_t color);                 // +0x5c
    virtual void v18(); virtual void v19(); virtual void v1a();
    virtual void SetLayoutArea(const Math::Rectangle& area);    // +0x6c
    virtual void SetLayoutLocation(float x, float y);           // +0x70
    virtual void SetLayoutSize(float w, float h);               // +0x74
    virtual void v1e();
    virtual void SetFlag(uint32_t flag, bool value);            // +0x7c
    virtual void SetCaption(const wchar_t* caption);            // +0x80
    virtual void v21(); virtual void v22(); virtual void v23();
    virtual int Invalidate();                                   // +0x90
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v2a(); virtual void v2b(); virtual void v2c();
    virtual void v2d(); virtual void v2e(); virtual void v2f(); virtual void v30();
    virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38();
    virtual void v39();
    virtual void BringToFront(IWindow* window);                 // +0xe8
};
}}  // namespace EA::UTFWin
using EA::UTFWin::IWindow;

enum { kWinFlagVisible = 1 };

// interface returned by object_cast(window, 0x0f15f4bd) (text/caption control)
class ITextControl {
 public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void SetAutoSize(int value);                                      // +0x14
    virtual void v06(); virtual void v07();
    virtual bool FitArea(Math::Rectangle* area, int a, int b);                // +0x20
};
ITextControl* CastToTextControl(IWindow* window);   // 0x005994b0

struct ResourceKey {
    uint32_t instance, type, group;
};

class PropertyList {
 public:
    virtual void v00();
    virtual int Release();   // +0x4
};

class IPropManager {
 public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, PropertyList** ppOut);  // +0x2c
};

namespace SP {
IPropManager* PropertyManager();   // 0x0067de30

class cString {   // retail size 0x14
 public:
    uint32_t mData[5];
    cString();                  // 0x006b5060
    ~cString();                 // 0x006b5240
    const wchar_t* GetText();   // 0x006b55c0
};
bool GetPropertyAsText(PropertyList* list, uint32_t id, cString* out);          // 0x006a1360
bool GetPropertyAsKeyInstance(PropertyList* list, uint32_t id, uint32_t* out);  // 0x006a12a0
}  // namespace SP

bool TryGetUIntProperty(PropertyList* list, uint32_t id, int* out);   // 0x00410370

struct ImageInfo {
    uint32_t pad[7];
    int mWidth;    // +0x1c
    int mHeight;   // +0x20
};

class cSPUILayout {
 public:
    uint32_t mData[3];
};

namespace SPUIHelpers {
ImageInfo* GetImageFromId(uint32_t instanceId);                              // 0x00458de0
ImageInfo* GetImageFromLayout(cSPUILayout* layout, uint32_t imageKey);       // 0x008061c0
void SetDrawableImage(IWindow* window, ImageInfo* image, int index);         // 0x008068d0
void AutoSizeWindowForText(IWindow* window, bool width, bool height);        // 0x00806e40
void AnchorWindowToWindow(IWindow* w, IWindow* anchor, uint32_t flags, IWindow* ref);  // 0x00807340
}  // namespace SPUIHelpers

namespace EA { namespace Locale {
int SetMoneyString(double value, wchar_t* buf, int bufSize, const wchar_t* format, const wchar_t* symbol);  // 0x008822e0
}}  // namespace EA::Locale

// item availability status filled in by the status provider (third argument)
struct ItemStatus {
    SP::cString mReason;       // +0x00
    SP::cString mReason2;      // +0x14
    uint32_t mColor;           // +0x28
    uint32_t mImageKey;        // +0x2c
    bool mbUseSymbol;          // +0x30
    ItemStatus();              // 0x005a7810
};

class IItemStatusProvider {
 public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual int GetStatus(const ResourceKey& key, ItemStatus* status);   // +0x10
};

class IAbilityProvider {
 public:
    virtual void v00(); virtual void v01();
    virtual int Release();                                  // +0x08
    virtual void SetupWindow(IWindow* window, bool locked); // +0x0c
    virtual int GetCount();                                 // +0x10
};

struct AbilityProviderPtr {
    IAbilityProvider* mpObject;
    AbilityProviderPtr& operator=(IAbilityProvider* p);    // 0x00572620
    __forceinline void reset()
    {
        if (mpObject) {
            IAbilityProvider* p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};

struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr()
    {
        if (mpObject)
            mpObject->Release();
    }
    PropertyList** AsPPTypeParam()
    {
        if (mpObject) {
            PropertyList* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};

class cSPUIPropertyLayout {
 public:
    uint32_t mHeader[3];          // +0x00 (IWinProc, RefCount)
    cSPUILayout mLayout;          // +0x0c
    uint32_t mBase[0x60 / 4];     // +0x18 .. +0x78
    void SetFlag(int flag);               // 0x00828020
    void ForceVisibleLocation();          // 0x00828110
};

namespace SP {
class cSPPaletteItemRollover : public cSPUIPropertyLayout {
 public:
    IWindow* mWinRoot;                 // +0x78
    IWindow* mWinBackgroundStandard;   // +0x7c
    IWindow* mWinBackgroundNoFunds;    // +0x80
    IWindow* mWinBackgroundLocked;     // +0x84
    IWindow* mWinPrice;                // +0x88
    IWindow* mWinVerbIcons;            // +0x8c
    IWindow* mWinAbilityLines;         // +0x90
    IWindow* mWinName;                 // +0x94
    IWindow* mWinIcon;                 // +0x98
    IWindow* mWinHeader;               // +0x9c
    IWindow* mWinErrorGroup;           // +0xa0
    IWindow* mWinErrorIcon;            // +0xa4
    IWindow* mWinErrorSymbol;          // +0xa8
    IWindow* mWinErrorReason;          // +0xac
    void* mInfo;                       // +0xb0
    AbilityProviderPtr mAbilities;     // +0xb4
    bool mNeedToInit;                  // +0xb8
    bool mShowAbilities;               // +0xb9

    void Show(const ResourceKey& key, IAbilityProvider* abilities, IItemStatusProvider* statusProvider,
              wchar_t currencySymbol, bool locked, bool queryStatus);
};

// @ 0x005ed750
void cSPPaletteItemRollover::Show(const ResourceKey& key, IAbilityProvider* abilities,
                                  IItemStatusProvider* statusProvider, wchar_t currencySymbol,
                                  bool locked, bool queryStatus)
{
    PropertyListPtr propList;
    PropertyManager()->GetPropertyList(key.instance, key.group, propList.AsPPTypeParam());
    if (!propList.mpObject)
        return;
    if (!mWinRoot || !mWinBackgroundNoFunds || !mWinBackgroundLocked || !mWinBackgroundStandard ||
        !mWinPrice || !mWinAbilityLines || !mWinName || !mWinHeader || !mWinErrorGroup ||
        !mWinErrorIcon || !mWinErrorReason)
        return;

    int price = 0;
    TryGetUIntProperty(propList.mpObject, 0x2166464, &price);

    ItemStatus status;
    int state = 1;
    if (statusProvider && queryStatus)
        state = statusProvider->GetStatus(key, &status);
    bool bAvailable = (state == 1);
    if (status.mColor != 0xffff0000)
        bAvailable = true;
    bool bLocked = locked || state == 7;

    eastl::string16 unused;
    const wchar_t* name = L"";
    cString nameText;
    if (GetPropertyAsText(propList.mpObject, 0x8f6fc401, &nameText))
        name = nameText.GetText();
    mWinName->SetCaption(name);

    uint32_t iconId = 0;
    GetPropertyAsKeyInstance(propList.mpObject, 0x666b54e, &iconId);
    if (iconId == 0 || mWinIcon) {
        ImageInfo* image = 0;
        if (iconId != 0)
            image = SPUIHelpers::GetImageFromId(iconId);
        if (image) {
            mWinIcon->SetFlag(kWinFlagVisible, true);
            SPUIHelpers::SetDrawableImage(mWinIcon, image, -1);
            if (mWinName)
                mWinName->SetLayoutLocation(mWinIcon->GetRealArea().x2 + 4.0f, mWinName->GetRealArea().y1);
        } else if (mWinIcon) {
            mWinIcon->SetFlag(kWinFlagVisible, false);
            if (mWinName) {
                const Math::Rectangle& iconArea = mWinIcon->GetRealArea();
                mWinName->SetLayoutLocation(iconArea.x1, mWinName->GetRealArea().y1);
            }
        }
    }

    wchar_t priceText[0x28];
    priceText[0] = 0;
    if (price != 0) {
        wchar_t symbol[2];
        symbol[0] = currencySymbol;
        symbol[1] = 0;
        EA::Locale::SetMoneyString((double)price, priceText, 0x28, L"%-F%-p", symbol);
    }
    bool bShowPrice = !bLocked && state != 6 && price > 0;
    mWinPrice->SetCaption(priceText);
    mWinPrice->SetFlag(kWinFlagVisible, bShowPrice);
    mWinPrice->SetShadeColor(bAvailable ? 0xffffffff : 0xffff0000);
    mWinBackgroundStandard->SetFlag(kWinFlagVisible, bAvailable && !bLocked);
    mWinBackgroundNoFunds->SetFlag(kWinFlagVisible, !bAvailable && !bLocked);
    mWinBackgroundLocked->SetFlag(kWinFlagVisible, bLocked);
    mWinPrice->Invalidate();

    float errorWidth = 0.0f;
    if (state == 1 || state == 7) {
        mWinErrorGroup->SetFlag(kWinFlagVisible, false);
    } else {
        mWinErrorGroup->SetFlag(kWinFlagVisible, true);
        mWinErrorReason->SetCaption(status.mReason.GetText());
        mWinErrorReason->SetShadeColor(status.mColor);
        mWinErrorIcon->SetShadeColor(status.mColor);
        mWinErrorSymbol->SetShadeColor(status.mColor);
        float left;
        float right;
        bool showSymbol;
        if (status.mbUseSymbol) {
            wchar_t symbol[2];
            symbol[0] = currencySymbol;
            symbol[1] = 0;
            mWinErrorSymbol->SetCaption(symbol);
            CastToTextControl(mWinErrorSymbol)->SetAutoSize(0);
            left = mWinErrorSymbol->GetRealArea().x1;
            right = mWinErrorSymbol->GetRealArea().x2 + 5.0f;
            mWinErrorIcon->SetFlag(kWinFlagVisible, false);
            showSymbol = true;
        } else {
            ImageInfo* image = SPUIHelpers::GetImageFromLayout(&mLayout, status.mImageKey);
            if (image) {
                mWinErrorIcon->SetLayoutSize((float)image->mWidth, (float)image->mHeight);
                SPUIHelpers::SetDrawableImage(mWinErrorIcon, image, -1);
                left = mWinErrorIcon->GetRealArea().x1;
                right = mWinErrorIcon->GetRealArea().x2 + 5.0f;
            } else {
                left = 0.0f;
                right = 0.0f;
            }
            mWinErrorIcon->SetFlag(kWinFlagVisible, image != 0);
            showSymbol = false;
        }
        mWinErrorSymbol->SetFlag(kWinFlagVisible, showSymbol);
        errorWidth = right - left;
        Math::Rectangle area = mWinErrorReason->GetRealArea();
        area.x1 = right;
        mWinErrorReason->SetLayoutArea(area);
        if (CastToTextControl(mWinErrorReason)->FitArea(&area, 0, 1))
            errorWidth = area.x2 - left;
    }

    float headerTop = mWinHeader->GetRealArea().y1;
    CastToTextControl(mWinName)->SetAutoSize(0);
    Math::Rectangle nameArea = mWinName->GetRealArea();
    float nameWidth = nameArea.x2 - nameArea.x1;
    float nameHeight = nameArea.y2 - nameArea.y1;
    if (bShowPrice)
        SPUIHelpers::AutoSizeWindowForText(mWinPrice, true, false);
    Math::Rectangle priceArea = mWinPrice->GetRealArea();
    float priceHeight = priceArea.y2 - priceArea.y1;
    float rowHeight = eastl::max(eastl::max(priceHeight, nameHeight), 24.0f) + 4.0f;
    nameArea.y1 = (rowHeight - nameHeight) * 0.5f;
    nameArea.y2 = nameArea.y1 + nameHeight;
    priceArea.y1 = (rowHeight - priceHeight) * 0.5f;
    priceArea.y2 = priceArea.y1 + priceHeight;
    mWinPrice->SetLayoutArea(priceArea);
    Math::Rectangle headerArea = mWinHeader->GetRealArea();
    headerArea.y1 = headerTop;
    headerArea.y2 = rowHeight + headerTop;
    mWinHeader->SetLayoutArea(headerArea);
    nameArea.x2 = nameArea.x1 + nameWidth;
    mWinName->SetLayoutArea(nameArea);

    float width = nameWidth;
    if (mWinIcon && (mWinIcon->GetFlags() & kWinFlagVisible)) {
        const Math::Rectangle& iconArea = mWinIcon->GetRealArea();
        width = (iconArea.x2 - iconArea.x1) + nameWidth + 4.0f;
    }
    const Math::Rectangle& hdr = mWinHeader->GetRealArea();
    float bottom = (hdr.y2 - hdr.y1) + headerTop;
    mWinRoot->SetLayoutSize(width, nameArea.y2 - nameArea.y1);
    if (bShowPrice)
        SPUIHelpers::AnchorWindowToWindow(mWinName, mWinPrice, 0x600, mWinPrice);

    const Math::Rectangle& hdr2 = mWinHeader->GetRealArea();
    float headerWidth = hdr2.x2 - hdr2.x1;
    float total = width + 20.0f;
    if (bShowPrice) {
        const Math::Rectangle& pa = mWinPrice->GetRealArea();
        total = (pa.x2 - pa.x1) + total + 20.0f;
    }
    if (errorWidth + 20.0f > total)
        total = errorWidth + 20.0f;
    if (180.0f > total) {
        float d = 180.0f - total;
        total = 180.0f;
        if (20.0f > d)
            total = (20.0f - d) + 180.0f;
    }
    const Math::Rectangle& ra = mWinRoot->GetRealArea();
    total = (ra.x2 - ra.x1) + (total - headerWidth);
    if (1.0f > total)
        total = 1.0f;
    mWinRoot->SetLayoutSize(total, nameArea.y2 - nameArea.y1);

    const Math::Rectangle& hdr3 = mWinHeader->GetRealArea();
    headerWidth = hdr3.x2 - hdr3.x1;
    float finalWidth = total;
    if (mWinErrorGroup->GetFlags() & kWinFlagVisible) {
        mWinErrorGroup->SetLayoutLocation(mWinErrorGroup->GetRealArea().x1, bottom);
        const Math::Rectangle& er = mWinErrorReason->GetRealArea();
        bottom = (er.y2 - er.y1) + (bottom + 4.0f);
    }

    mAbilities.reset();
    if (mShowAbilities && mWinAbilityLines) {
        const Math::Rectangle& al = mWinAbilityLines->GetRealArea();
        mWinAbilityLines->SetLayoutSize(headerWidth, al.y2 - al.y1);
        mAbilities = abilities;
        mAbilities.mpObject->SetupWindow(mWinAbilityLines, bLocked);
    }
    bool showAbilities;
    if (mAbilities.mpObject && mAbilities.mpObject->GetCount() > 0) {
        bottom += 4.0f;
        Math::Rectangle area = mWinAbilityLines->GetRealArea();
        float y2 = (area.y2 - area.y1) + bottom;
        area.y1 = bottom;
        area.y2 = y2;
        mWinAbilityLines->SetLayoutArea(area);
        bottom = y2;
        float linesWidth = (area.x2 - area.x1) + 20.0f;
        const Math::Rectangle& hdr4 = mWinHeader->GetRealArea();
        if (linesWidth > hdr4.x2 - hdr4.x1) {
            const Math::Rectangle& hdr5 = mWinHeader->GetRealArea();
            finalWidth = (linesWidth - (hdr5.x2 - hdr5.x1)) + total;
        }
        showAbilities = true;
    } else {
        showAbilities = false;
    }
    mWinAbilityLines->SetFlag(kWinFlagVisible, showAbilities);
    mWinRoot->SetLayoutSize(finalWidth, ((bottom - headerTop) - 2.0f) - 2.0f);
    SetFlag(1);
    IWindow* parent = mWinRoot->GetParent();
    if (parent)
        parent->BringToFront(mWinRoot);
    ForceVisibleLocation();
}
}  // namespace SP
