// Slice s005a1920 -- SP::cTerrainUI / cEditorCameraController helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"
#include <math.h>

typedef unsigned int size_t;

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }

// ---------------------------------------------------------------------------
struct Vec3 { float x, y, z; };

struct cLocalInputState {
    char pad[0x40];
    bool OnKeyDown(int key, int x);         // 0x00697a50
    bool OnKeyUp(int key, int x);           // 0x00697a80
    bool OnMouseUp(int a, float x, float y, int b);   // 0x00697af0
    unsigned int OnMouseWheel(int a, int b, float x, float y);  // 0x00697b40
};

struct Cam {
    char  pad0[0x14];
    float m14;          // +0x14
    char  pad18[0x2c - 0x18];
    char  m2c;          // +0x2c
    char  pad2d[0x30 - 0x2d];
    float m30;          // +0x30
    char  pad34[0x38 - 0x34];
    float m38;          // +0x38
    float m3c;          // +0x3c
    float m40;          // +0x40
    float m44, m48, m4c, m50, m54;   // +0x44..0x58
    float m58;          // +0x58
    float m5c;          // +0x5c
    char  pad60[0x74 - 0x60];
    Vec3  m74;          // +0x74
    Vec3  m80;          // +0x80
    float m8c;          // +0x8c
    char  pad90[0x9c - 0x90];
    char  m9c;          // +0x9c
    char  pad9d[0xa0 - 0x9d];
    cLocalInputState mInput;   // +0xa0

    void SetSomething(Vec3 v, bool immediate);                       // 0x005a2010
    bool OnKeyDown(int key, int x);                                  // 0x005a2080
    bool OnKeyUp(int key, int x);                                    // 0x005a2120
    bool OnMouseUp(int a, float x, float y, int b);                  // 0x005a21c0
    void ZoomBy(float factor);                                       // 0x005a2200
    void AddAngle(float d);                                          // 0x005a2240
    void ComputeView(float* a, float* b, float* c, float* out);      // 0x005a2260
    void UpdatePitch();                                              // 0x005a22d0
    void ClearVtables();                                             // 0x005a2300
    void OnMouseWheel(int a, int b, float x, float y);               // 0x005a2580
};

extern float kOne_1485720;
extern float kHalf_1471064;
extern float k0_1_1488874;
extern float kDiv_150f2c4;
extern float k0_52_13f69b0;
extern float kSign_13eb8b0;
extern float k0_1_150f2c8;
extern float kMul_13f6a24;

extern char vtbl_5a2300_a;
extern char vtbl_5a2300_b;

// ===========================================================================
// @ 0x005a2010
void Cam::SetSomething(Vec3 v, bool immediate)
{
    m80 = v;
    if (immediate)
        m74 = v;
}

// ===========================================================================
// @ 0x005a2080
bool Cam::OnKeyDown(int key, int x)
{
    switch (key) {
    case 0x6b: case 0x6d: case 0xbb: case 0xbc: case 0xbd: case 0xbe:
        mInput.OnKeyDown(key, x);
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// @ 0x005a2120
bool Cam::OnKeyUp(int key, int x)
{
    switch (key) {
    case 0x6b: case 0x6d: case 0xbb: case 0xbc: case 0xbd: case 0xbe:
        mInput.OnKeyUp(key, x);
        return true;
    default:
        return false;
    }
}

// ===========================================================================
// @ 0x005a21c0
bool Cam::OnMouseUp(int a, float x, float y, int b)
{
    mInput.OnMouseUp(a, x, y, b);
    m2c = 0;
    return true;
}

// ===========================================================================
// @ 0x005a2200
void Cam::ZoomBy(float factor)
{
    float one = kOne_1485720;
    float f = (factor + one) * m38;
    m38 = f;
    float t = m5c;
    if (f > t)
        m38 = t;
    else {
        t = m58;
        if (t > f)
            m38 = t;
    }
    m9c = 1;
}

// ===========================================================================
// @ 0x005a2240
void Cam::AddAngle(float d)
{
    m30 = k0_1_150f2c8 * d + m30;
}

// ===========================================================================
// @ 0x005a2260
void Cam::ComputeView(float* a, float* b, float* c, float* out)
{
    float angle = m4c;
    float scale = k0_52_13f69b0 / m8c;
    *a = m44;
    *b = m48;
    *c = m4c;
    out[0] = -((m50 * scale) * angle);
    out[1] = -angle;
    out[2] = (m54 * scale) * angle;
}

// ===========================================================================
// @ 0x005a22d0
void Cam::UpdatePitch()
{
    m54 = (k0_1_1488874 - (Abs(m48) / kDiv_150f2c4) * kHalf_1471064) * m8c + m40;
}

// ===========================================================================
// @ 0x005a2300
void Cam::ClearVtables()
{
    *(void**)((char*)this + 4) = &vtbl_5a2300_a;
    *(void**)this = &vtbl_5a2300_b;
}

// ===========================================================================
// @ 0x005a2580
void Cam::OnMouseWheel(int a, int b, float x, float y)
{
    mInput.OnMouseWheel(a, b, x, y);
    float f = (((float)a * m14) * kMul_13f6a24 + kOne_1485720) * m38;
    float t = m5c;
    m38 = f;
    if (f > t)
        m38 = t;
    else {
        t = m58;
        if (t > f)
            m38 = t;
    }
    m9c = 1;
}

// ===========================================================================
// @ 0x005a1920  SP::cSPEditorBlockAbilities compact ability-row layout (PDB candidate name was wrong).
// Lays out one small icon row per block ability (icon + tooltip + optional level text) side by side;
// falls back to the full LayoutAbilities (0x005a0510) when the count fits mMaxFullRows.
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
    Rectangle() {}
    Rectangle(const Rectangle& o) : x1(o.x1), y1(o.y1), x2(o.x2), y2(o.y2) {}
};
}

struct Image;

struct ITextCaption {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void SetNoWrap(bool b);                                      // +0x1c
};

struct IWindow {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual void v08();
    virtual ITextCaption* Cast(uint32_t type);                           // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const Math::Rectangle& GetRealArea();                        // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void v5c(); virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetLayoutArea(const Math::Rectangle& area);             // +0x6c
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, bool value);                          // +0x7c
    virtual void SetCaption(const wchar_t* caption);                     // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc(); virtual void vc0();
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4();
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
    operator T*() const { return mpObject; }
};

extern wchar_t gEmptyString16[];   // 0x01667bac, EASTL's shared empty string

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
struct cPropertyList {
    virtual int AddRef();                                                // +0x00
    virtual int Release();                                               // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18();
    virtual bool HasProperty(uint32_t id);                               // +0x1c
};

bool GetPropertyAsKeyInstance(cPropertyList* p, uint32_t id, uint32_t* out);       // 0x006a12a0

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
    uint32_t pad28[0x90 - 0x28 > 0 ? (0x90 - 0x28) / 4 : 1];
    uint32_t mVerbIconImageID;             // +0x90
    uint32_t pad94[(0xb4 - 0x94) / 4];
    EA::ResourceMan::Key mVerbIconStaticLayout;  // +0xb4
    cPropertyList* mpPropList;             // +0xc0
};

// Stack vector with room for 8 records (sp_vector_allocator): the word before the inline buffer is 0,
// a heap block has a non-zero header word there.
struct cSPEditorVerbIconArray8 {
    cSPEditorVerbIconData* mpBegin;
    cSPEditorVerbIconData* mpEnd;
    cSPEditorVerbIconData* mpCapacity;
    uint32_t mAllocator[2];
    uint32_t mBufferHeader;
    uint32_t mBuffer[8 * 0xc4 / 4];

    cSPEditorVerbIconArray8() {
        mpBegin = (cSPEditorVerbIconData*)mBuffer;
        mpEnd = (cSPEditorVerbIconData*)mBuffer;
        mpCapacity = (cSPEditorVerbIconData*)mBuffer + 8;
        mBufferHeader = 0;
    }
    ~cSPEditorVerbIconArray8() {
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

void BlockGetAbilities(cSPEditorVerbIconArray8* out, const EA::ResourceMan::Key* blockKey,
                       uint32_t imageGroup);                             // 0x0059fc60
}  // namespace SP

struct cSPUILayout {
    uint32_t pad[6];
    cSPUILayout();                                                       // 0x00810000
    ~cSPUILayout();                                                      // 0x00811fe0
    bool Init(const EA::ResourceMan::Key* key, bool b, uint32_t group);  // 0x008120d0
    IWindow* FindWindowByID(uint32_t id, bool recursive);                // 0x008105b0
    void SetParentWin(IWindow* parent, bool b, uint32_t group);          // 0x008121b0
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
Image* GetImageByID(uint32_t imageID);                                    // 0x00458de0
char SetDrawableImage(IWindow* w, Image* img, int index);                       // 0x008068d0
char SetImageIcon(IWindow* w, Image* img, int index);                           // 0x00806aa0
void CenterWindowInArea(IWindow* w, const Math::Rectangle* r);                  // 0x00806d10
void SetTooltipText(IWindow* w, const wchar_t* text, int a, bool b);            // 0x00806de0
}

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
    uint8_t pad61[3];
    unsigned mMaxFullRows;                       // +0x64
    uint32_t mFullLayoutId;                      // +0x68
    uint32_t mCompactLayoutId;                   // +0x6c

    void SortAbilities(cSPEditorVerbIconArray8* abilities, VerbCategoryMap* categories);  // 0x0059f7c0
    void LayoutAbilities(IWindow* pParent, bool bUseAltProperties);                       // 0x005a0510
    void LayoutAbilitiesCompact(IWindow* pParent, bool bUseAltProperties, int* pCount);  // 0x005a1920
};

// @ 0x005a1920
void cSPEditorBlockAbilities::LayoutAbilitiesCompact(IWindow* pParent, bool bUseAltProperties, int* pCount)
{
    cSPEditorVerbIconArray8 abilities;
    BlockGetAbilities(&abilities, &mBlockKey, mIconImageGroup);

    if (mbCheckCategories && mbFilterByCategory) {
        for (int i = (int)abilities.size() - 1; i >= 0; --i) {
            cSPEditorVerbIconData& a = abilities[i];
            if (mVerbCategoryMap.find(a.mVerbIconCategory) == mVerbCategoryMap.end()) {
                a = abilities.back();
                abilities.pop_back();
            }
        }
        SortAbilities(&abilities, &mVerbCategoryMap);
    }

    unsigned count = abilities.size();
    *pCount = (int)count;
    if (count <= mMaxFullRows) {
        mAbilityLayoutKey.instanceID = mFullLayoutId;
        LayoutAbilities(pParent, bUseAltProperties);
        return;
    }

    EA::ResourceMan::Key* pKey = &mAbilityLayoutKey;
    pKey->instanceID = mCompactLayoutId;
    float totalWidth = 0.0f;
    float xPos = 0.0f;
    cSPUILayoutVector& lines = mAbilityLines;
    lines.erase(lines.mpBegin, lines.mpEnd);
    lines.resize(count);

    for (unsigned i = 0; i < count; ++i) {
        lines[i].Init(pKey, false, 0x5b598fa);
        IWindow* rowWin = lines[i].FindWindowByID(0x4c01bd5, true);
        lines[i].SetParentWin(pParent, true, 0x5b598fa);
        Math::Rectangle rowArea = rowWin->GetRealArea();
        float rowWidth = rowArea.x2 - rowArea.x1;

        Image* img = 0;
        if (abilities[i].mpPropList->HasProperty(0x668b0a0)) {
            uint32_t imageID = 0;
            GetPropertyAsKeyInstance(abilities[i].mpPropList, 0x668b0a0, &imageID);
            img = SPUIHelpers::GetImageByID(imageID != 0 ? imageID : abilities[i].mVerbIconImageID);
        } else if (abilities[i].mVerbIconImageID != 0) {
            img = SPUIHelpers::GetImageByID(abilities[i].mVerbIconImageID);
        }

        intrusive_ptr<IWindow> iconWin = lines[i].FindWindowByID(0x4c01bbe, true);
        if (img && iconWin) {
            iconWin->SetFlag(1, true);
            intrusive_ptr<IWindow> iconLayoutWin;
            if (abilities[i].mVerbIconStaticLayout.instanceID != 0) {
                cSPUILayout layout;
                layout.Init(&abilities[i].mVerbIconStaticLayout, true, 0x5b598fa);
                iconLayoutWin = layout.FindWindowByID(0x902d3163, true);
            }
            if (iconLayoutWin) {
                iconWin->AddWindow(iconLayoutWin);
                Math::Rectangle r = iconWin->GetRealArea();
                float w = r.x2 - r.x1;
                float h = r.y2 - r.y1;
                r.x1 = 0.0f;
                r.y1 = 0.0f;
                r.x2 = w;
                r.y2 = h;
                SPUIHelpers::CenterWindowInArea(iconLayoutWin, &r);
                IWindow* iconImageWin = iconLayoutWin->FindWindowByID(0x6283c92, false);
                if (iconImageWin || (iconImageWin = iconLayoutWin->FindWindowByID(0x4976e19, false)) != 0) {
                    iconImageWin->SetFlag(0x10, true);
                    SPUIHelpers::SetImageIcon(iconImageWin, img, 0);
                }
            } else {
                SPUIHelpers::SetDrawableImage(iconWin, img, 0);
            }
            string16 tip = abilities[i].GetName(false);
            SPUIHelpers::SetTooltipText(iconWin, tip.c_str(), -1, true);
        }

        IWindow* levelWin = lines[i].FindWindowByID(0x4c01bca, true);
        if (levelWin) {
            if (abilities[i].mVerbIconLevel > 0.0f && abilities[i].mPaletteItemRolloverShowLevel) {
                string16 s;
                s.sprintf(L"%d", (int)abilities[i].mVerbIconLevel);
                levelWin->SetCaption(s.c_str());
                levelWin->Cast(0xf15f4bd)->SetNoWrap(false);
            } else {
                levelWin->SetCaption(gEmptyString16);
            }
        }

        totalWidth = rowWidth + totalWidth;
        rowArea.x1 = xPos;
        // (the original passes the whole rectangle; only x1 changes)
        rowWin->SetLayoutArea(rowArea);
        xPos = rowWidth + xPos;
    }

    const Math::Rectangle& pr = pParent->GetRealArea();
    float parentWidth = pr.x2 - pr.x1;
    if (parentWidth > totalWidth)
        totalWidth = parentWidth;
    Math::Rectangle area = pParent->GetRealArea();
    area.x2 = area.x1 + totalWidth;
    pParent->SetLayoutArea(area);
}
}  // namespace SP

// @ 0x005a2370
void SetCenterCameraOffset(void* self)
{
    (void)self;
}

// @ 0x005a2400
void SetPartModeCameraOffset(void* self)
{
    (void)self;
}

// @ 0x005a24c0
void SetPaintModeCameraOffset(void* self)
{
    (void)self;
}
