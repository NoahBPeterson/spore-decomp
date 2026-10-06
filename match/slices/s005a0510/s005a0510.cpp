// Slice s005a0510 -- SP::cSPEditorBlockAbilities::LayoutAbilities (5132 bytes).
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc: RAII locals get no EH frame).
//
// Lays out one cSPUILayout row per block ability inside pParent: icon (texture,
// layout or image), caption text, an optional lock window and a level display
// (repeated level pips, "%d" text or a localized level string), then sizes all
// rows to the widest one and resizes pParent to fit.
//
// Retail layouts: cSPEditorVerbIconData is the 0xC4-byte retail class (ModAPI
// Editors::VerbIconData field names); cSPEditorBlockAbilities fields are at the
// retail offsets seen here (the 2008 PDB has them 8-0x10 bytes further on).
#include "types.h"

namespace EA { namespace ResourceMan {
struct Key {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}}

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
};
}

// UTFWin image (only the pixel size is read here).
struct Image {
    uint32_t pad[7];
    int mWidth;   // +0x1c
    int mHeight;  // +0x20
};

// Returned by IWindow::Cast(0x0f15f4bd): the caption/text object of a window.
struct ITextCaption {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void SetAutoSize(bool b);                                    // +0x14
    virtual void v18();
    virtual void v1c();
    virtual bool GetTextExtent(Math::Rectangle* out, int a, int b);      // +0x20
};

struct IStdDrawableBase0 {
    virtual void v00();
    uint32_t pad[2];
};
struct IStdDrawable {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* GetImage(int index);                                   // +0x10
};
struct cSPUIStdDrawable : IStdDrawableBase0, IStdDrawable {   // IStdDrawable at +0xc
    void SetImageColor(int index, uint32_t color);                     // 0x00831170
};

struct IDrawable {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual cSPUIStdDrawable* Cast(uint32_t type);                       // +0x0c
};

struct IWindow {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual void v08();
    virtual ITextCaption* Cast(uint32_t type);                           // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual const Math::Rectangle& GetArea();                            // +0x34
    virtual const Math::Rectangle& GetRealArea();                        // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetLayoutArea(const Math::Rectangle& area);             // +0x6c
    virtual void SetLayoutLocation(float x, float y);                    // +0x70
    virtual void SetLayoutSize(float w, float h);                        // +0x74
    virtual void v78();
    virtual void SetFlag(int flag, bool value);                          // +0x7c
    virtual void SetCaption(const wchar_t* caption);                     // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4();
    virtual IDrawable* GetDrawable();                                    // +0xa8
    virtual void vac(); virtual void vb0(); virtual void vb4(); virtual void vb8();
    virtual void vbc(); virtual void vc0(); virtual void vc4(); virtual void vc8();
    virtual void vcc(); virtual void vd0(); virtual void vd4();
    virtual void AddWindow(IWindow* w);                                  // +0xd8
    virtual void vdc(); virtual void ve0(); virtual void ve4(); virtual void ve8();
    virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);        // +0xf0
};

template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr(T* p) : mpObject(p) { if (p) p->AddRef(); }
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    intrusive_ptr& operator=(T* p) {
        if (p) p->AddRef();
        T* old = mpObject;
        mpObject = p;
        if (old) old->Release();
        return *this;
    }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};

namespace SP {
struct cPropertyList {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                               // +0x1c
};

struct cString {
    uint32_t pad[5];
    cString();                                                           // 0x006b5060
    ~cString();                                                          // 0x006b5240
    const wchar_t* GetText();                                            // 0x006b55c0
};

bool GetPropertyAsKey(cPropertyList* p, uint32_t id, EA::ResourceMan::Key* out);   // 0x006a1250
bool GetPropertyAsKeyInstance(cPropertyList* p, uint32_t id, uint32_t* out);       // 0x006a12a0
bool GetPropertyAsText(cPropertyList* p, uint32_t id, cString* out);               // 0x006a1360
uint32_t ColorRGBAToU32(const void* color);                                          // 0x004580c0
}

extern wchar_t gEmptyString16[];   // 0x01667bac, EASTL's shared empty string

// eastl::string16 (16 bytes incl. allocator), only what this function inlines.
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() { mpBegin = gEmptyString16; mpEnd = gEmptyString16; mpCapacity = gEmptyString16 + 1; }
    ~string16() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
    const wchar_t* c_str() const { return mpBegin; }
    string16& sprintf(const wchar_t* fmt, ...);                          // 0x0041e050
};

namespace SP {
// Retail 0xC4-byte verb icon record (ModAPI Editors::VerbIconData names).
struct cSPEditorVerbIconData {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual ~cSPEditorVerbIconData();                                    // +0x08
    virtual void* Cast(uint32_t type);                                   // +0x0c
    virtual void Init(cPropertyList* p);                                 // +0x10
    virtual void Shutdown();                                             // +0x14
    virtual void SetArrayIndex(int i);                                   // +0x18
    virtual void SetHotKey(int key);                                     // +0x1c
    virtual string16 GetName(bool includeLevel);                         // +0x20
    virtual string16 GetDescription();                                   // +0x24

    cSPEditorVerbIconData& operator=(const cSPEditorVerbIconData& o);    // 0x0059f0e0

    uint32_t pad04[2];
    bool mVerbIconUseDescription;          // +0x0c
    bool mVerbIconShowLevel;               // +0x0d
    bool mPaletteItemRolloverShowLevel;    // +0x0e
    bool mVerbIconRolloverShowLevel;       // +0x0f
    uint32_t pad10[2];
    float mVerbIconLevel;                  // +0x18
    float mVerbIconMaxLevel;               // +0x1c
    int field_20;                          // +0x20
    int mVerbIconCategory;                 // +0x24 (eVerbIconCategory)
    uint32_t mVerbIconRepresentativeAnimation;  // +0x28
    float mVerbIconColor[4];               // +0x2c
    uint32_t mVerbIconRolloverLevelImageID;     // +0x3c
    EA::ResourceMan::Key mVerbIconRolloverLevelLayoutID;  // +0x40
    bool mVerbIconRolloverShowIcon;        // +0x4c
    bool mVerbIconEnforceMaxLevel;         // +0x4d
    uint32_t pad50[16];
    uint32_t mVerbIconImageID;             // +0x90
    uint32_t mVerbIconTrayOverrideImageID; // +0x94
    uint32_t mVerbIconTraySmallCardOverrideImageID;  // +0x98
    EA::ResourceMan::Key mVerbIconLayout;        // +0x9c
    EA::ResourceMan::Key mVerbIconGameLayout;    // +0xa8
    EA::ResourceMan::Key mVerbIconStaticLayout;  // +0xb4
    cPropertyList* mpPropList;             // +0xc0
};

// Stack vector with room for 32 records (sp_vector_allocator): the word before
// the inline buffer is 0, a heap block has a non-zero header word there.
struct cSPEditorVerbIconArray {
    cSPEditorVerbIconData* mpBegin;
    cSPEditorVerbIconData* mpEnd;
    cSPEditorVerbIconData* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t mBufferHeader;
    uint32_t mBuffer[32 * 0xc4 / 4];

    cSPEditorVerbIconArray() {
        mpBegin = (cSPEditorVerbIconData*)mBuffer;
        mpEnd = (cSPEditorVerbIconData*)mBuffer;
        mpCapacity = (cSPEditorVerbIconData*)mBuffer + 32;
        mBufferHeader = 0;
    }
    ~cSPEditorVerbIconArray() {
        for (cSPEditorVerbIconData* p = mpBegin; p < mpEnd; ++p)
            p->~cSPEditorVerbIconData();
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    cSPEditorVerbIconData& operator[](int i) { return mpBegin[i]; }
    cSPEditorVerbIconData& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; mpEnd->~cSPEditorVerbIconData(); }
};

void BlockGetAbilities(cSPEditorVerbIconArray* out, const EA::ResourceMan::Key* blockKey,
                       uint32_t imageGroup);                             // 0x0059fc60
}

struct cSPUILayout {
    uint32_t pad[6];
    cSPUILayout();                                                       // 0x00810000 (folded)
    ~cSPUILayout();                                                      // 0x00811fe0
    bool Init(const EA::ResourceMan::Key* key, bool b, uint32_t group);  // 0x008120d0
    IWindow* FindWindowByID(uint32_t id, bool recursive);                // 0x008105b0
    void SetParentWin(IWindow* parent, bool b, uint32_t group);          // 0x008121b0
    void Shutdown(bool b);                                               // 0x00811ad0
};

struct cSPUILayoutVector {   // eastl::vector<cSPUILayout, sp_vector_allocator>
    cSPUILayout* mpBegin;
    cSPUILayout* mpEnd;
    cSPUILayout* mpCapacity;
    cSPUILayout* erase(cSPUILayout* first, cSPUILayout* last);           // 0x0059f4a0
    void resize(unsigned n);                                             // 0x0059f950
    cSPUILayout& operator[](int i) { return mpBegin[i]; }
};

struct RBNodeBase {
    RBNodeBase* mpNodeRight;
    RBNodeBase* mpNodeLeft;
    RBNodeBase* mpNodeParent;
    char mColor;
};
struct RBIterator {
    RBNodeBase* mpNode;
    RBIterator() : mpNode(0) {}
    RBIterator(RBNodeBase* n) : mpNode(n) {}
    RBIterator(const RBIterator& x) : mpNode(x.mpNode) {}
    bool operator==(const RBIterator& x) const { return mpNode == x.mpNode; }
};
struct VerbCategoryMap {   // eastl::map<eVerbIconCategory, ...>
    uint32_t mCompare;
    RBNodeBase mAnchor;
    RBIterator find(const int& key);                                // 0x00e39fb0 (folded)
    RBIterator end() { return RBIterator(&mAnchor); }
};

namespace SPUIHelpers {
Image* GetImageFromTexture(uint32_t instance, uint32_t group, int a, int b);    // 0x008060d0
Image* GetImageByID(uint32_t imageID);                                    // 0x00458de0
char SetDrawableImage(IWindow* w, Image* img, int index);                       // 0x008068d0
char SetImageIcon(IWindow* w, Image* img, int index);                           // 0x00806aa0
void CenterWindowInArea(IWindow* w, const Math::Rectangle* r);                  // 0x00806d10
IWindow* CreateChildImageWindow(IWindow* parent);                                    // 0x00806370
}

struct LocalizationParams {
    uint32_t pad[22];
    uint32_t mNumber;   // +0x58
};
extern LocalizationParams* g_pLocalizationParams;   // 0x015ee298

// .data tunables
extern float kAbilityMargin;     // 0x0150f16c (2.0)
extern float kAbilityLevelPad;   // 0x0150f170 (16.0)
extern float kAbilityIconPad;    // 0x0150f174 (8.0)
extern float kAbilityRowPad;     // 0x0150f178 (6.0)
extern float kAbilityIconScale;  // 0x0150f17c (1.0)

namespace SP {
struct cSPEditorBlockAbilities {
    void* vptr;
    uint32_t pad04[2];
    EA::ResourceMan::Key mBlockKey;              // +0x0c
    EA::ResourceMan::Key mAbilityLayoutKey;      // +0x18
    cSPUILayoutVector mAbilityLines;             // +0x24
    uint32_t pad30[2];
    VerbCategoryMap mVerbCategoryMap;            // +0x38
    uint32_t pad4c[3];
    bool mbFilterByCategory;                     // +0x58
    uint32_t mIconImageGroup;                    // +0x5c
    bool mbCheckCategories;                      // +0x60
    bool mbLevelAsNumber;                        // +0x61
    bool mbUseLevelTextProperty;                 // +0x62
    bool mbHideLockIfSingle;                     // +0x63

    void SortAbilities(cSPEditorVerbIconArray* abilities, VerbCategoryMap* categories);  // 0x0059f7c0
    void LayoutAbilities(IWindow* pParent, bool bUseAltProperties);                      // 0x005a0510
};

// @ 0x005a0510
void cSPEditorBlockAbilities::LayoutAbilities(IWindow* pParent, bool bUseAltProperties)
{
    float y = 0.0f;
    const Math::Rectangle& parentArea = pParent->GetRealArea();
    float parentWidth = parentArea.x2 - parentArea.x1;

    cSPEditorVerbIconArray abilities;
    BlockGetAbilities(&abilities, &mBlockKey, mIconImageGroup);

    if (mbCheckCategories && mbFilterByCategory) {
        for (int i = (int)abilities.size() - 1; i >= 0; --i) {
            cSPEditorVerbIconData& a = abilities[i];
            if (mVerbCategoryMap.find(a.mVerbIconCategory) == mVerbCategoryMap.end()) {
                switch (a.mVerbIconCategory) {
                case (int)0xe2654048:
                case (int)0x93a8cfc8:
                case (int)0xa09e2868:
                case (int)0x28ebaf02:
                    break;
                default:
                    a = abilities.back();
                    abilities.pop_back();
                    break;
                }
            }
        }
        SortAbilities(&abilities, &mVerbCategoryMap);
    }

    int count = (int)abilities.size();
    float totalHeight = 0.0f;
    mAbilityLines.erase(mAbilityLines.mpBegin, mAbilityLines.mpEnd);
    mAbilityLines.resize(count);

    float maxRowWidth = 0.0f;
    float maxIconWidth = 0.0f;
    float maxTextWidth = 0.0f;
    float maxLevelWidth = 0.0f;

    for (int i = 0; i < count; ++i) {
        mAbilityLines[i].Init(&mAbilityLayoutKey, false, 0x5b598fa);
        IWindow* rowWin = mAbilityLines[i].FindWindowByID(0x4c01bd5, true);
        Math::Rectangle rowArea = rowWin->GetRealArea();
        mAbilityLines[i].SetParentWin(pParent, true, 0x5b598fa);
        float rowWidth = rowArea.x2 - rowArea.x1;
        float rowHeight = rowArea.y2 - rowArea.y1;
        float baseRowHeight = rowHeight;

        cSPEditorVerbIconData& a = abilities[i];

        // Icon image: a texture key, a key-instance property or the image ID.
        Image* img = 0;
        bool bTexture = false;
        if (a.mVerbIconRolloverShowIcon) {
            if (bUseAltProperties && a.mpPropList->HasProperty(0x6669c51)) {
                EA::ResourceMan::Key key;
                key.instanceID = 0;
                key.typeID = 0;
                key.groupID = 0;
                GetPropertyAsKey(a.mpPropList, 0x6669c51, &key);
                img = SPUIHelpers::GetImageFromTexture(key.instanceID, key.groupID, -1, -1);
                bTexture = true;
            } else if (a.mpPropList->HasProperty(0x668b0a0)) {
                uint32_t imageID = 0;
                GetPropertyAsKeyInstance(a.mpPropList, 0x668b0a0, &imageID);
                if (imageID == 0)
                    imageID = a.mVerbIconImageID;
                img = SPUIHelpers::GetImageByID(imageID);
            } else if (a.mVerbIconImageID != 0) {
                img = SPUIHelpers::GetImageByID(a.mVerbIconImageID);
            }
        }

        intrusive_ptr<IWindow> iconWin = mAbilityLines[i].FindWindowByID(0x4c01bbe, true);
        if (img == 0 || iconWin.get() == 0) {
            if (img == 0 && iconWin.get())
                iconWin->SetFlag(1, false);
            IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
            if (textWin)
                textWin->SetLayoutLocation(0.0f, textWin->GetRealArea().y1);
        } else {
            iconWin->SetFlag(1, true);
            intrusive_ptr<IWindow> iconLayoutWin;
            if (a.mVerbIconStaticLayout.instanceID != 0) {
                cSPUILayout layout;
                layout.Init(&a.mVerbIconStaticLayout, true, 0x5b598fa);
                iconLayoutWin = layout.FindWindowByID(0x902d3163, true);
            }
            if (iconLayoutWin.get()) {
                iconWin->AddWindow(iconLayoutWin.get());
                Math::Rectangle r = iconWin->GetRealArea();
                float w = r.x2 - r.x1;
                float h = r.y2 - r.y1;
                r.x1 = 0.0f;
                r.y1 = 0.0f;
                r.x2 = w;
                r.y2 = h;
                SPUIHelpers::CenterWindowInArea(iconLayoutWin.get(), &r);
                IWindow* iconImageWin = iconLayoutWin->FindWindowByID(0x6283c92, false);
                if (iconImageWin || (iconImageWin = iconLayoutWin->FindWindowByID(0x4976e19, false)) != 0) {
                    iconImageWin->SetFlag(0x10, true);
                    SPUIHelpers::SetImageIcon(iconImageWin, img, 0);
                }
            } else {
                SPUIHelpers::SetDrawableImage(iconWin.get(), img, 0);
            }
            const Math::Rectangle& ia = iconWin->GetRealArea();
            float iconWidth = ia.x2 - ia.x1;
            if (iconWidth > maxIconWidth)
                maxIconWidth = iconWidth;
        }

        // Texture icons are scaled to the image size and centered vertically.
        float iconOffset = 0.0f;
        if (iconWin.get() && bTexture && img) {
            const Math::Rectangle& ia = iconWin->GetRealArea();
            Math::Rectangle ir;
            ir.x1 = ia.x1;
            ir.y1 = ia.y1;
            ir.x2 = ia.x2;
            float iconHeight = ia.y2 - ia.y1;
            float imgHeight = (float)img->mHeight * kAbilityIconScale;
            ir.y1 = (ia.y2 + ia.y1) * 0.5f - imgHeight * 0.5f;
            ir.y2 = ir.y1 + imgHeight;
            ir.x2 = (float)img->mWidth * kAbilityIconScale + ir.x1;
            iconWin->SetLayoutArea(ir);
            const Math::Rectangle& na = iconWin->GetRealArea();
            float iconWidth = na.x2 - na.x1;
            if (iconWidth > maxIconWidth)
                maxIconWidth = iconWidth;

            IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
            if (textWin) {
                Math::Rectangle ta = textWin->GetRealArea();
                if (ir.y2 > ta.y2) {
                    ta.y2 = ir.y2;
                    textWin->SetLayoutArea(ta);
                }
                iconOffset = ir.x2 - textWin->GetRealArea().x1;
                rowWidth = iconOffset + rowWidth;
                textWin->SetLayoutLocation(ir.x2, textWin->GetRealArea().y1);
            }
            float h = kAbilityRowPad + (((ir.y2 - ir.y1) - iconHeight) * 0.5f + baseRowHeight);
            if (h > baseRowHeight)
                rowHeight = h;
        }

        // Caption text.
        IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
        if (textWin) {
            textWin->GetRealArea();
            const Math::Rectangle& ta0 = textWin->GetRealArea();
            float baseTextWidth = ta0.x2 - ta0.x1;
            if (bUseAltProperties && a.mpPropList->HasProperty(0x6669c7c)) {
                cString text;
                GetPropertyAsText(a.mpPropList, 0x6669c7c, &text);
                textWin->SetCaption(text.GetText());
            } else if (mbUseLevelTextProperty && a.mpPropList->HasProperty(0x6492b61)) {
                cString text;
                GetPropertyAsText(a.mpPropList, 0x6492b61, &text);
                textWin->SetCaption(text.GetText());
            } else if (a.mVerbIconUseDescription) {
                textWin->SetCaption(a.GetDescription().c_str());
            } else {
                textWin->SetCaption(a.GetName(false).c_str());
            }
            textWin->Cast(0xf15f4bd)->SetAutoSize(false);
            const Math::Rectangle& ta = textWin->GetRealArea();
            float textWidth = ta.x2 - ta.x1;
            if (textWidth + iconOffset >= parentWidth) {
                textWidth = parentWidth - iconOffset;
                const Math::Rectangle& tb = textWin->GetRealArea();
                textWin->SetLayoutSize(textWidth, tb.y2 - tb.y1);
            }
            textWin->Cast(0xf15f4bd)->SetAutoSize(true);
            if (textWidth > baseTextWidth)
                rowWidth = (textWidth - baseTextWidth) + rowWidth;
            float textBottom = textWin->GetRealArea().y2;
            textWin->GetRealArea();
            if (textWidth > maxTextWidth)
                maxTextWidth = textWidth;
            if (textBottom + kAbilityRowPad > rowHeight)
                rowHeight = textBottom + kAbilityRowPad;
        }

        IWindow* lockWin = mAbilityLines[i].FindWindowByID(0x64d2eee, true);
        if (lockWin)
            lockWin->SetFlag(1, !mbHideLockIfSingle || count > 1);

        // Level display.
        IWindow* levelWin = mAbilityLines[i].FindWindowByID(0x4c01bca, true);
        if (levelWin) {
            if (a.mVerbIconLevel > 0.0f && a.mPaletteItemRolloverShowLevel) {
                const Math::Rectangle& la = levelWin->GetRealArea();
                float baseLevelWidth = la.x2 - la.x1;
                float levelWidth = baseLevelWidth;
                if (a.mVerbIconRolloverLevelImageID != 0) {
                    // One pip per level, laid out left to right.
                    Image* pipImg = SPUIHelpers::GetImageByID(a.mVerbIconRolloverLevelImageID);
                    const Math::Rectangle& lb = levelWin->GetRealArea();
                    float centerY = (lb.y2 - lb.y1) * 0.5f;
                    float pipHeight = (float)pipImg->mHeight;
                    float pipWidth = (float)pipImg->mWidth;
                    float x = 0.0f;
                    for (int j = 0; (float)j < a.mVerbIconLevel; ++j) {
                        IWindow* pip = 0;
                        if (a.mVerbIconRolloverLevelLayoutID.instanceID != 0) {
                            cSPUILayout layout;
                            layout.Init(&a.mVerbIconRolloverLevelLayoutID, false, 0x5b598fa);
                            IWindow* w = layout.FindWindowByID(0x902d3163, true);
                            if (w) {
                                w->AddRef();
                                pip = w;
                            }
                            layout.Shutdown(true);
                            levelWin->AddWindow(pip);
                            IWindow* pipImageWin = pip->FindWindowByID(0x6283c92, false);
                            if (pipImageWin || (pipImageWin = pip->FindWindowByID(0x4976e19, false)) != 0) {
                                pipImageWin->SetFlag(0x10, true);
                                IDrawable* d = pipImageWin->GetDrawable();
                                if (d) {
                                    cSPUIStdDrawable* sd = d->Cast(0x53eb526);
                                    if (sd && sd->GetImage(0) && a.mpPropList->HasProperty(0x631704a))
                                        sd->SetImageColor(0, ColorRGBAToU32(a.mVerbIconColor));
                                }
                                SPUIHelpers::SetImageIcon(pipImageWin, pipImg, 0);
                            }
                            const Math::Rectangle& pa = pip->GetRealArea();
                            pipWidth = pa.x2 - pa.x1;
                            pipHeight = pa.y2 - pa.y1;
                        } else {
                            IWindow* w = SPUIHelpers::CreateChildImageWindow(levelWin);
                            if (w) {
                                w->AddRef();
                                pip = w;
                            }
                            SPUIHelpers::SetDrawableImage(pip, pipImg, -1);
                        }
                        Math::Rectangle pr;
                        pr.x1 = x;
                        pr.x2 = x + pipWidth;
                        pr.y1 = centerY - pipHeight * 0.5f;
                        pr.y2 = pr.y1 + pipHeight;
                        pip->SetLayoutArea(pr);
                        x = pr.x2;
                        pip->Release();
                    }
                    levelWidth = x;
                    levelWin->SetCaption(L"");
                } else {
                    if (mbLevelAsNumber) {
                        string16 s;
                        s.sprintf(L"%d", (int)a.mVerbIconLevel);
                        levelWin->SetCaption(s.c_str());
                    } else {
                        cString text;
                        g_pLocalizationParams->mNumber = (uint32_t)a.mVerbIconLevel;
                        intrusive_ptr<cPropertyList> propList(a.mpPropList);
                        GetPropertyAsText(a.mpPropList, 0x62d00e7, &text);
                        levelWin->SetCaption(text.GetText());
                    }
                    Math::Rectangle extent;
                    if (levelWin->Cast(0xf15f4bd)->GetTextExtent(&extent, 0, 1))
                        levelWidth = extent.x2 - extent.x1;
                }
                if (levelWidth > maxLevelWidth)
                    maxLevelWidth = levelWidth;
                if (levelWidth > baseLevelWidth)
                    rowWidth = (levelWidth - baseLevelWidth) + rowWidth;
            } else {
                levelWin->SetCaption(gEmptyString16);
                const Math::Rectangle& la = levelWin->GetRealArea();
                rowWidth = rowWidth - (la.x2 - la.x1);
            }
        }

        if (rowWidth > maxRowWidth)
            maxRowWidth = rowWidth;
        totalHeight = rowHeight + totalHeight;
        rowArea.x1 = 0.0f;
        rowArea.y1 = y;
        rowArea.x2 = maxRowWidth;
        rowArea.y2 = rowHeight + y;
        rowWin->SetLayoutArea(rowArea);
        y = rowHeight + y;
    }

    float iconPad = maxIconWidth > 0.0f ? kAbilityIconPad : 0.0f;
    float levelPad = maxLevelWidth > 0.0f ? kAbilityLevelPad : 0.0f;
    float width = kAbilityMargin * 2.0f + levelPad + iconPad + maxLevelWidth + maxTextWidth + maxIconWidth;
    const Math::Rectangle& pa = pParent->GetRealArea();
    if (pa.x2 - pa.x1 > width)
        width = pa.x2 - pa.x1;

    // Stretch every row to the common width and right-align the level column.
    for (int i = 0; i < count; ++i) {
        IWindow* rowWin = mAbilityLines[i].FindWindowByID(0x4c01bd5, true);
        mAbilityLines[i].FindWindowByID(0x4c01bbe, true);
        IWindow* textWin = mAbilityLines[i].FindWindowByID(0x4c01bc4, true);
        IWindow* levelWin = mAbilityLines[i].FindWindowByID(0x4c01bca, true);
        Math::Rectangle r = rowWin->GetRealArea();
        r.x2 = r.x1 + width;
        rowWin->SetLayoutArea(r);
        if (textWin) {
            Math::Rectangle t = textWin->GetRealArea();
            float w = t.x2 - t.x1;
            t.x1 = iconPad + maxIconWidth;
            t.x2 = t.x1 + w;
            textWin->SetLayoutArea(t);
        }
        if (levelWin) {
            Math::Rectangle l = levelWin->GetRealArea();
            l.x2 = r.x2 - kAbilityMargin;
            l.x1 = l.x2 - maxLevelWidth;
            levelWin->SetLayoutArea(l);
        }
    }

    Math::Rectangle area = pParent->GetRealArea();
    area.x2 = area.x1 + width;
    area.y2 = area.y1 + totalHeight;
    pParent->SetLayoutArea(area);
}
}  // namespace SP
