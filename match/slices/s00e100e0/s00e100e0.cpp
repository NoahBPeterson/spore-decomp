// Slice s00e100e0: cSPUIMinimapWin::AddIcon (0x00e10580).
// UI module, /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
//
// AddIcon(id, info, parentId, flag): copies the icon description, picks a minimap
// image id from the icon flags and the game mode, builds a WinButton with a
// ButtonDrawableRadio showing that image, registers the description in the icon map
// (mIconInfos[id] = info), positions the button (planet modes: normalized direction
// projected onto the minimap; otherwise just kept in the parent), then adds it to the
// parent window (or to the minimap itself when parentId is 0).
#include "types.h"

#include <math.h>

inline void* operator new(unsigned int, void* p) { return p; }

namespace Math {
struct Rectangle {
    float x1, y1, x2, y2;
    Rectangle() {}
    __forceinline Rectangle(float l, float t, float r, float b) : x1(l), y1(t), x2(r), y2(b) {}
};
}

struct Vector3 {
    float x, y, z;
};

class RefObject {
public:
    virtual int AddRef();
    virtual int Release();
};

class IQueried {                        // returned by RefObject slot +0x0c
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual bool IsMinimapObject();     // +0x58
};
class IQueryable {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual IQueried* Query(uint32_t typeID);    // +0x0c
};

struct cIconInfo {                      // size 0x24
    uint32_t mType;                     // +0x00
    float mX, mY, mZ;                   // +0x04 direction
    uint32_t mFlags;                    // +0x10
    IQueryable* mpObject;               // +0x14 (ref counted)
    float mTimeout;                     // +0x18
    uint32_t mAnimState;                // +0x1c
    uint32_t mImageID;                  // +0x20
    __forceinline cIconInfo(const cIconInfo& o)
        : mType(o.mType), mX(o.mX), mY(o.mY), mZ(o.mZ), mFlags(o.mFlags), mpObject(o.mpObject),
          mTimeout(o.mTimeout), mAnimState(o.mAnimState), mImageID(o.mImageID)
    {
        if (mpObject)
            mpObject->AddRef();
    }
    __forceinline ~cIconInfo()
    {
        if (mpObject)
            mpObject->Release();
    }
    cIconInfo& operator=(const cIconInfo& o);        // 0x00e0bdc0
};

class Image {
public:
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[7];
    int mWidth;                         // +0x20
};

class IWin {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual const float* GetArea();                         // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c();
    virtual void SetID(uint32_t id);                        // +0x50
    virtual void v54(); virtual void v58();
    virtual void SetColor(uint32_t color);                  // +0x5c
    virtual void SetArea(const Math::Rectangle* r);         // +0x60
    virtual void v64();
    virtual void SetSize(float w, float h);                 // +0x68
    virtual void v6c(); virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(int flag, int enable);             // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8();
    virtual void SetVisible(int v);                         // +0xac
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4();
    virtual bool AddChild(IWin* child);                     // +0xd8
    virtual void vdc(); virtual void ve0(); virtual void ve4();
    virtual void PlaceAfter(IWin* child);                   // +0xe8
    virtual void PlaceBefore(IWin* child);                  // +0xec
    virtual IWin* GetChild(int id, int recurse);            // +0xf0
};

// The button's control interface (third vtable of WinButton, object offset +0x20c).
class IButtonControl {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual IWin* GetWindow();                              // +0x10
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void SetDrawable(void* drawable);               // +0x60
};

class IDrawableSize {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void SetSize(const float* size, int a, int b);  // +0x18
};
class IDrawable {                       // drawable's third interface (object offset +0x0c)
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual IDrawableSize* GetSizeIface();                  // +0x10
    virtual void SetImage(Image* image, int a);             // +0x14
};

struct WinButtonObj {
    void** vt0;
    void** vt1;
    uint32_t pad[0x204 / 4 - 1];
    void** vt2;                         // +0x20c
    WinButtonObj();                     // 0x00966f90 UI::WinButton::WinButton
};
struct DrawableObj {
    void** vt0;
    void** vt1;
    void** vt2;                         // +0x08 (interface at +0x0c in retail)
    DrawableObj();                      // 0x00966dc0 ButtonDrawableRadio::ButtonDrawableRadio
};

extern void* g_vtWinButton0[];          // 0x0147f868
extern void* g_vtWinButton1[];          // 0x0147f748
extern void* g_vtWinButton2[];          // 0x0147f6d8
extern void* g_vtDrawable0[];           // 0x0141788c
extern void* g_vtDrawable1[];           // 0x01417874
extern void* g_vtDrawable2[];           // 0x0141785c
extern const char g_cityIconName[];     // "UI/CivMinimap/CityIcon"
extern const char g_cityIconDrawableName[];

class cApp {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual uint32_t GetGameMode();                         // +0x38
};

cApp* __cdecl App();                                        // 0x0067dd10
Image* __cdecl GetImageFromLayout(void* layout, uint32_t id);   // 0x008061c0
void* __cdecl GetAllocator();                               // 0x009512c0
void* __cdecl TooltipAlloc(unsigned size, unsigned align, const char* name, void* alloc);   // 0x009512d0
void __cdecl FitWindowToArea(IWin* w, const Math::Rectangle* r);    // 0x00806d10
extern const float g_epsilon;           // 0x013ec4b8
extern const float g_half;              // 0x01471064 = 0.5

struct IconTree {
    cIconInfo& At(const uint32_t& key);                     // 0x00e0ff80 (map::operator[])
};

class MinimapVt {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
};

class cSPUIMinimapWin : public MinimapVt, public IWin {
public:
    uint32_t pad_008[(0x258 - 8) / 4];
    void* mpLayout;                     // +0x258
    uint32_t pad_25c[(0x31c - 0x25c) / 4];
    IconTree mIconInfos;                // +0x31c
    uint32_t pad_320[(0x364 - 0x320) / 4 - 1];
    bool mbTradeRoutesDirty;            // +0x364 (byte at +0x364)

    void FUN_e0bcb0(const float* pos, const float* out, float* extra);     // 0x00e0bcb0
    void ComputeIconPositionFromMinimapCoords(const float* c, IWin* w, bool f);   // 0x00e0bf40
    void FUN_e0d100(IWin* w, float f, const float* p);                     // 0x00e0d100
    IWin* SubWin() { return (IWin*)((char*)this + 4); }
    bool AddIcon(uint32_t id, const cIconInfo* info, int parentID, bool flag);
};

static __forceinline uint32_t PickImageID(uint32_t f, uint32_t mode, uint32_t infoImage)
{
    uint32_t id = infoImage;
    if (f & 1) {
        id = (f & 8) ? 0x5e51b64 : 0x5e51b58;
    } else if (f & 2) {
        if (f & 8)
            id = 0x5e51b4c;
        else
            id = ((f & 0x100000) ? 10 : 0) + 0x5e51b25;
    } else if (f & 0x1000) {
        id = 0x5e51b2f;
    } else if (f & 0x10) {
        id = ((f & 8) ? 0xb : 0) + 0x5e51aef;
    } else if (f & 0x40000) {
        id = 0x5e51b03;
    } else if (f & 0x20) {
        if (f & 8) {
            if (mode != 0x1654c10)
                id = 0x5e51bd7;
        } else if (f & 0x80000) {
            id = 0xccd1f01e;
        } else if (f & 0x100000) {
            id = 0x71abd9ca;
        } else {
            id = ((f & 0x200000) ? 0xadb5da70 : 0) + 0x5e51bce;
        }
    } else if (f & 0x40) {
        if (f & 8)
            id = 0x5e51b19;
        else
            id = ((mode != 0x1654c10) ? 0xfe415759 : 0) + 0x7a3c3c0;
    } else if (f & 0x80) {
        if (mode != 0x1654c10)
            id = 0x5e51b25;
    } else if (f & 0x100) {
        id = 0x5e51aef;
    } else if (f & 0x2000) {
        id = 0x5e51b19;
    } else if (f & 0x4000) {
        id = 0x5e51ad8;
    } else if (f & 0x10000) {
        id = 0x5e51bb6;
    } else if (f & 0x8000) {
        id = 0x5e51bc1;
    } else {
        id = ((f & 0x20000) ? 0x122 : 0) + 0x5e51ad8;
    }
    return id;
}

// @ 0x00e10580 ?AddIcon@cSPUIMinimapWin@@QAE_NIPBUcIconInfo@1@H_N@Z
bool cSPUIMinimapWin::AddIcon(uint32_t id, const cIconInfo* info, int parentID, bool flag)
{
    cIconInfo local(*info);
    IWin* parent = 0;
    if (parentID) {
        parent = SubWin()->GetChild(parentID, 0);
        if (!parent)
            return false;
    }
    uint32_t mode = App()->GetGameMode();
    if (!(local.mFlags & 8) && local.mpObject) {
        IQueried* q = local.mpObject->Query(0x1186577);
        if (q && q->IsMinimapObject())
            local.mFlags |= 8;
    }
    uint32_t imageID = PickImageID(local.mFlags, mode, local.mImageID);

    Image* image = GetImageFromLayout(mpLayout, imageID);
    if (image)
        image->AddRef();

    WinButtonObj* wb = (WinButtonObj*)TooltipAlloc(0x888, 4, g_cityIconName, GetAllocator());
    IButtonControl* button = 0;
    if (wb) {
        new (wb) WinButtonObj();
        wb->vt0 = g_vtWinButton0;
        wb->vt1 = g_vtWinButton1;
        wb->vt2 = g_vtWinButton2;
        button = (IButtonControl*)&wb->vt2;
    }
    IWin* win = button->GetWindow();

    DrawableObj* dr = (DrawableObj*)TooltipAlloc(0x18, 4, g_cityIconDrawableName, GetAllocator());
    IDrawable* drawable = 0;
    if (dr) {
        new (dr) DrawableObj();
        dr->vt0 = g_vtDrawable0;
        dr->vt1 = g_vtDrawable1;
        dr->vt2 = g_vtDrawable2;
        drawable = (IDrawable*)((char*)dr + 0xc);
    }
    drawable->SetImage(image, 0);
    float size[2];
    size[0] = size[1] = (float)image->mWidth;
    drawable->GetSizeIface()->SetSize(size, 0, 0);
    button->SetDrawable(drawable);
    win->SetID(id);
    win->SetVisible(0);
    win->SetColor(local.mType ? local.mType : (uint32_t)-1);
    Math::Rectangle area(0.0f, 0.0f, size[0], size[1]);
    win->SetArea(&area);

    bool result;
    if (local.mFlags & 2) {
        if (mode == 0x1654c02) {
            mbTradeRoutesDirty = true;
        } else {
            win->SetSize(size[0] * g_half, size[1] * g_half);
        }
    }
    float inv = 1.0f / (float)sqrt((double)(local.mZ * local.mZ + local.mY * local.mY + local.mX * local.mX + g_epsilon));
    Vector3 n;
    n.x = inv * local.mX;
    n.y = local.mY * inv;
    n.z = local.mZ * inv;
    local.mX = n.x;
    local.mY = n.y;
    local.mZ = n.z;
    float f = 0.0f;
    FUN_e0bcb0(&local.mX, &n.x, flag ? &f : 0);
    ComputeIconPositionFromMinimapCoords(&n.x, win, false);
    if (!parent) {
        mIconInfos.At(id) = local;
        IWin* self = SubWin();
        result = self->AddChild(win);
        if (mode == 0x1654c10) {
            if (local.mFlags & 0x80)
                self->PlaceAfter(win);
            else
                self->PlaceBefore(win);
        } else if (!(local.mFlags & 0x18021)) {
            self->PlaceAfter(win);
        } else {
            self->PlaceBefore(win);
        }
    } else {
        const float* a = parent->GetArea();
        float x1 = a[0], y1 = a[1];
        Math::Rectangle r(-x1 + x1, -y1 + y1, a[2] + -x1, a[3] + -y1);
        FitWindowToArea(win, &r);
        win->SetFlag(1, 1);
        win->SetFlag(0x10, 1);
        mIconInfos.At(id) = local;
        result = parent->AddChild(win);
        parent->PlaceAfter(win);
    }
    if (flag)
        FUN_e0d100(win, f, &n.x);
    image->Release();
    return result;
}
