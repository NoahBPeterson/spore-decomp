// src/game/Spui/SPUITooltip.cpp -- migrated from slice(s) s008356e0, s00834a00 by tools/migrate/rewrite.py
// Object file: Spui/SPUITooltip.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUITooltipWinProc.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern char  g_vtblTooltipMgr;   // 0x141aec8
extern char  g_vtblContentValid; // 0x13ec458
extern void* g_p164f328;         // 0x164f328
extern float g_164f45c;          // 0x164f45c
extern float g_164f44c;          // 0x164f44c
extern float g_164f46c;          // 0x164f46c
extern float g_164f47c;          // 0x164f47c
extern float g_13fdcf4;          // 0x13fdcf4
extern float g_13fdcf8;          // 0x13fdcf8
extern char  g_1548560;          // 0x1548560
extern "C" float FUN_00805080(void);   // SPUIHelpers::GetElapsedSeconds
extern "C" void  FUN_00805ea0(void);   // SPUIHelpers::GetMainWindowArea
extern "C" void  FUN_006237d0(void);   // eastl copy_impl
extern "C" void* FUN_0067de30(void);   // SP::PropertyManager

// ---- items of slice s00834a00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void   (__thiscall *VFv)(void*);
static inline void** VT(void* o) { return *(void***)o; }
extern char  g_vtblTooltipMgr;   // 0x141aec8
extern char  g_vtblContentValid; // 0x13ec458
extern void* g_p164f328;         // 0x164f328
extern float g_164f45c;          // 0x164f45c
extern float g_164f44c;          // 0x164f44c
extern float g_164f46c;          // 0x164f46c
extern float g_164f47c;          // 0x164f47c
extern float g_13fdcf4;          // 0x13fdcf4
extern float g_13fdcf8;          // 0x13fdcf8
extern char  g_1548560;          // 0x1548560
extern "C" float FUN_00805080(void);   // SPUIHelpers::GetElapsedSeconds
extern "C" void  FUN_00805ea0(void);   // SPUIHelpers::GetMainWindowArea
extern "C" void  FUN_006237d0(void);   // eastl copy_impl
extern "C" void* FUN_0067de30(void);   // SP::PropertyManager
struct TooltipManager {
    void*    vptr;   // +0x00
    int      rc;     // +0x04
    void*    layout; // +0x08
    void*    window; // +0x0c
    void*    parent; // +0x10
    void*    props;  // +0x14
    uint32_t key0;   // +0x18
    uint32_t key1;   // +0x1c
    uint32_t key2;   // +0x20
    float    f24;    // +0x24
    float    f28;    // +0x28
    uint8_t  b2c;    // +0x2c
    uint8_t  b2d;    // +0x2d
    uint8_t  b2e;    // +0x2e

    TooltipManager();
    void Dtor();
    bool ReleaseRefs();
    bool ShouldDisplayTooltip(void* w);
    int  ShouldTimeoutTooltip();
    int  ShouldDisplayDetailedTooltip();
    void SetTooltipText(int a, int b);
    void MakeFullyVisibleInMainWindow(int dummy);
    bool LoadProps();
};
// ---- items of slice s00834a00 end

// ---- items of slice s008356e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t g_emptyStr;     // 0x1667bac
extern wchar_t g_emptyCap;     // 0x1667bae
extern float g_tipOffX;        // 0x1548558
extern float g_tipOffY;        // 0x154855c
extern void* g_tooltipMgrPtr;  // 0x164f328 (points at manager+8)
static inline void** Vtbl(void* o) { return *(void***)o; }
template <class F> static F VFn(void* o, int byteOff) {
    return (F)(*(void**)((char*)Vtbl(o) + byteOff));
}
void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void  __cdecl FUN_00808b20(void*, void*, int);            // 0x808b20
void  __cdecl FUN_00805fe0(void*, void*);                 // 0x805fe0
void  __cdecl SPUI_UpdateMouseFocus(int);                 // 0x804f50
float __cdecl SPUI_GetElapsedSeconds();                   // 0x805080
void  __cdecl SPKeyFromName(void*, const wchar_t*, int, int); // 0x68d840
struct WString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    WString() : mpBegin(&g_emptyStr), mpEnd(&g_emptyStr), mpCapacity(&g_emptyCap) {}
    WString(const wchar_t* s) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(s); }
    ~WString() { DeallocateSelf(); }
    void DeallocateSelf();
    void RangeInitialize(const wchar_t* s);
    void assign(const wchar_t* first, const wchar_t* last);
};
void WString::DeallocateSelf() {
    if ((((int)((char*)mpCapacity - (char*)mpBegin) & -2) > 2) && mpBegin) {
        operator_delete__(mpBegin);
    }
}
static unsigned int CharStrlen(const wchar_t* p) {
    const wchar_t* e = p;
    while (*e) ++e;
    return (unsigned int)(e - p);
}
struct Point2D {
    float mX, mY;
    Point2D() {}
    Point2D(float x, float y) { mX = x; mY = y; }
    Point2D& operator=(const Point2D& o) { mX = o.mX; mY = o.mY; return *this; }
};
struct cSPUILayout_s0083_56e0 {
    cSPUILayout_s0083_56e0* Construct();                          // 0x810000
    void* FindWindowByID(uint32_t id, int recurse);    // 0x8105b0
    void  Init(const void* key, int a, int b);         // 0x8120d0
    void  SetVisibility(int v);                         // 0x810590
};
class cSPUITooltipManager { public:
    uint32_t pad0[2];         // +0x0
    void*    mpTooltipLayout; // +0x8
    void*    mpTooltipWindow; // +0xc
    void*    mpParentWindow;  // +0x10
    void*    mpTuningProps;   // +0x14
    float    mLayoutKey[3];   // +0x18
    float    mElapsedRolloverTime; // +0x24
    float    mMousedOffTime;       // +0x28
    bool     mbTooltipEnabled;     // +0x2c
    bool     mbTooltipDisplayed;   // +0x2d
    bool     mbDetailed;           // +0x2e
    char     pad1[0x38 - 0x2f];

    bool ShouldDisplayTooltip(void* pWindow);
    bool ShouldDisplayDetailedTooltip();
    bool ShouldTimeoutTooltip();
    void MakeFullyVisibleInMainWindow(float* rect);
    void CreateTooltipWindow(int wndID, const wchar_t* text, uint32_t data); // 0x835660
    void SetTooltipText(const wchar_t* text, uint32_t data);                 // 0x8354a0
    uint32_t ShowTooltip(char bShow, void* pParent, float* pRect, int wndID, float* pOffset,
                         const wchar_t* text, uint32_t data, uint32_t behavior, char bDetailed);
};
static cSPUITooltipManager* GetTooltipMgr() {
    void* p = g_tooltipMgrPtr;
    return p ? (cSPUITooltipManager*)((char*)p - 8) : 0;
}
struct IWinProc { virtual void wp0(); };
struct ISerializable { virtual void se0(); };
struct MultiHeapObject {};
struct CustomWinProc : IWinProc, ISerializable, MultiHeapObject {
    int mRefCount;
    CustomWinProc() : mRefCount(0) {}
    ~CustomWinProc() {}
};
struct cSPUITooltipWinProc_s0083_56e0 : CustomWinProc {
    WString  mLayoutName;            // +0xc
    uint32_t mWindowID;              // +0x1c
    uint32_t mDetailWindowID;        // +0x20
    WString  mTooltipString;         // +0x24
    WString  mTooltipDetailString;   // +0x34
    Point2D  mTooltipOffsetPosition; // +0x44
    uint32_t mKeyInstance;           // +0x4c
    uint32_t mKeyType;               // +0x50
    uint32_t mKeyGroup;              // +0x54
    bool     mbMouseOver;            // +0x58
    uint32_t mTooltipBehavior;       // +0x5c
    void*    mpMyWindow;             // +0x60
    uint32_t mUnk64;                 // +0x64

    cSPUITooltipWinProc_s0083_56e0();
    cSPUITooltipWinProc_s0083_56e0(const wchar_t* layout, uint32_t windowID, const wchar_t* tooltip,
                        float* offset, uint32_t behavior, const wchar_t* detail,
                        uint32_t detailWindowID);
    ~cSPUITooltipWinProc_s0083_56e0();
    void SetText(const wchar_t* text, void* data, char bImmediate);  // 0x00835ed0 (cSPUITooltipWinProc::SetText)
    uint32_t DoMessage(void* pWindow, int* msg);
};
// ---- items of slice s008356e0 end

// @ 0x008352a0
unsigned int cSPUITooltipWinProc::GetEventMask() const
{
    return (uint32_t)(((mbMouseOver != 0) ? 0xFFFFFFFFu : 0) & 2) | 0x441;
}

// @ 0x008352c0
void* FUN_008352c0()
{
    if (g_p164f328 != 0)
        return (char*)g_p164f328 - 8;
    return 0;
}

// @ 0x008352d0
TooltipManager::TooltipManager()
{
    g_p164f328 = (void*)((char*)this + 8);
    rc = 0;
    vptr = &g_vtblTooltipMgr;
    layout = 0;
    window = 0;
    parent = 0;
    props = 0;
    key0 = 0;
    key1 = 0;
    key2 = 0;
    f24 = 0.0f;
    f28 = 0.0f;
    b2c = 0;
    b2d = 0;
    b2e = 0;
}

// @ 0x00835320
void TooltipManager::Dtor()
{
    *(void* volatile*)this = &g_vtblTooltipMgr;
    void* p14 = *(void* volatile*)((char*)this + 0x14);
    if (p14)  ((VFv)VT(p14)[4 / 4])(p14);
    void* p10 = *(void* volatile*)((char*)this + 0x10);
    if (p10) ((VFv)VT(p10)[4 / 4])(p10);
    void* pc = *(void* volatile*)((char*)this + 0x0c);
    if (pc) ((VFv)VT(pc)[4 / 4])(pc);
    void* p8 = *(void* volatile*)((char*)this + 0x08);
    if (p8) ((VFv)VT(p8)[8 / 4])(p8);
    *(void* volatile*)this = &g_vtblContentValid;
    g_p164f328 = 0;
}

// @ 0x008353a0
bool TooltipManager::ReleaseRefs()
{
    if (layout) { layout = 0; ((VFv)VT(layout)[8 / 4])(layout); }
    if (window) { window = 0; ((VFv)VT(window)[4 / 4])(window); }
    if (parent) { parent = 0; ((VFv)VT(parent)[4 / 4])(parent); }
    if (props)  { props = 0;  ((VFv)VT(props)[4 / 4])(props); }
    return true;
}

// @ 0x008353f0
bool TooltipManager::ShouldDisplayTooltip(void* w)
{
    bool r = false;
    if (b2c == 0 && w != parent) {
        if (b2d != 0 && FUN_00805080() - f28 < g_164f45c)
            r = true;
        if (FUN_00805080() - f24 > g_164f44c)
            return true;
    }
    return r;
}

// @ 0x00835440
int TooltipManager::ShouldTimeoutTooltip()
{
    if (b2c != 0) {
        if (FUN_00805080() - f24 > g_164f46c)
            return 1;
    }
    return 0;
}

// @ 0x00835470
int TooltipManager::ShouldDisplayDetailedTooltip()
{
    if (b2c != 0 && b2e == 0) {
        if (FUN_00805080() - f24 > g_164f47c)
            return 1;
    }
    return 0;
}

// @ 0x008354a0
void TooltipManager::SetTooltipText(int a, int b)
{
    ((void (__thiscall*)(void*, int))VT(window)[0x80 / 4])(window, a);
    ((void (__thiscall*)(void*, int))VT(window)[0x5c / 4])(window, b);
    if (window) {
        void* p = ((void* (__thiscall*)(void*, void*))VT(window)[0xc / 4])(window, (void*)0xf15f4bd);
        if (p) {
            ((void (__thiscall*)(void*, float, float))VT(window)[0x68 / 4])(window, g_13fdcf4, g_13fdcf8);
            ((void (__thiscall*)(void*, int))VT(p)[0x14 / 4])(p, 1);
            ((void (__thiscall*)(void*, int))VT(p)[0x14 / 4])(p, 0);
        }
    }
}

// @ 0x00835520
void TooltipManager::MakeFullyVisibleInMainWindow(int dummy)
{
    (void)dummy;
    float area[4];
    ((void (__cdecl*)(void*))FUN_00805ea0)(area);
    float* r = ((float* (__thiscall*)(void*))VT(window)[0x38 / 4])(window);
    float sx = 0.0f;
    float* p = r;
    if (!(*r > 0.0f)) p = &sx;
    sx = *p;
    float sy = 0.0f;
    float* q = r + 1;
    if (!(r[1] > 0.0f)) q = &sy;
    sy = *q;
    if (area[2] < r[2]) sx = r[0] - (r[2] - area[2]);
    if (area[3] < r[3]) sy = r[1] - (r[3] - r[1]);
    ((void (__thiscall*)(void*, float, float))VT(window)[0x70 / 4])(window, sx, sy);
}

// @ 0x00835610
bool TooltipManager::LoadProps()
{
    void* pm = FUN_0067de30();
    if (props) { props = 0; ((VFv)VT(props)[4 / 4])(props); }
    char c = ((char (__thiscall*)(void*, int, void**))VT(pm)[0x30 / 4])(pm, 0x5c770db7, &props);
    if (c)
        ((void (__thiscall*)(void*, void*))FUN_006237d0)(&g_1548560, props);
    return true;
}

// @ 0x00835660
void FUN_00835660(void* self, int id, int a3, int a4)
{
    (void)self; (void)id; (void)a3; (void)a4;
}

// @ 0x008356e0
uint32_t cSPUITooltipManager::ShowTooltip(char bShow, void* pParent, float* pRect, int wndID, float* pOffset, const wchar_t* text, uint32_t data, uint32_t behavior, char bDetailed)
{
    if (!bShow && mbTooltipEnabled) mbTooltipDisplayed = false;
    mbTooltipEnabled = bShow != 0;
    void* oldParent = mpParentWindow;
    if (pParent != oldParent) {
        if (pParent) VFn<void(__thiscall*)(void*)>(pParent, 0)(pParent);
        mpParentWindow = pParent;
        if (oldParent) VFn<void(__thiscall*)(void*)>(oldParent, 4)(oldParent);
    }
    bool enabled = mbTooltipEnabled;
    mbDetailed = bDetailed != 0;
    if (!enabled) {
        void* w = mpTooltipWindow;
        if (w) VFn<void(__thiscall*)(void*, int, int)>(w, 0x7c)(w, 1, 0);
    } else {
        void* w = mpTooltipWindow;
        if (!w || mLayoutKey[0] != pRect[0] || mLayoutKey[1] != pRect[1] ||
            mLayoutKey[2] != pRect[2]) {
            cSPUILayout_s0083_56e0* p = (cSPUILayout_s0083_56e0*)operator_new6(0x18, "UI/Tooltip Layout", 0, 0, 0, 0);
            if (p) p = p->Construct();
            else p = 0;
            void* oldLayout = mpTooltipLayout;
            if (p != oldLayout) {
                if (p) VFn<void(__thiscall*)(void*)>(p, 4)(p);
                mpTooltipLayout = p;
                if (oldLayout) VFn<void(__thiscall*)(void*)>(oldLayout, 8)(oldLayout);
            }
            mLayoutKey[0] = pRect[0];
            mLayoutKey[1] = pRect[1];
            mLayoutKey[2] = pRect[2];
            ((cSPUILayout_s0083_56e0*)mpTooltipLayout)->Init(mLayoutKey, 1, 0x5b598f6);
            ((cSPUILayout_s0083_56e0*)mpTooltipLayout)->SetVisibility(0);
            CreateTooltipWindow(wndID, text, data);
        } else {
            int id = VFn<int(__thiscall*)(void*)>(w, 0x1c)(w);
            if (id == wndID) {
                const wchar_t* a = VFn<const wchar_t*(__thiscall*)(void*)>(w, 0x3c)(w);
                const wchar_t* b = text;
                while (*a == *b) {
                    if (*a == 0) break;
                    ++a; ++b;
                }
                int cmp = (*a == *b) ? 0 : ((*a < *b) ? -1 : 1);
                if (cmp != 0) SetTooltipText(text, data);
            } else {
                CreateTooltipWindow(wndID, text, data);
            }
        }
        void* tw = mpTooltipWindow;
        if (tw) {
            VFn<void(__thiscall*)(void*, int, int)>(tw, 0x7c)(tw, 1, 1);
            int q = VFn<int(__thiscall*)(void*)>(tw, 0x10)(tw);
            if (q) {
                void* r = VFn<void*(__thiscall*)(void*)>(tw, 0x10)(tw);
                VFn<void(__thiscall*)(void*, void*)>(r, 0xe8)(r, tw);
            }
            if (data == 0) {
                FUN_00808b20(mpParentWindow, tw, 0);
            } else if (data == 1) {
                float bounds[4];
                FUN_00805fe0(bounds, mpParentWindow);
                float* pa = VFn<float*(__thiscall*)(void*)>(mpParentWindow, 0x38)(mpParentWindow);
                float h = pa[3] - pa[1];
                float* pb = VFn<float*(__thiscall*)(void*)>(tw, 0x38)(tw);
                VFn<void(__thiscall*)(void*, float, float)>(tw, 0x70)(
                    tw, (bounds[0] + bounds[2]) * 0.5f - (pb[2] - pb[0]) * 0.5f,
                    h * 0.5f + (bounds[1] + bounds[3]) * 0.5f);
                MakeFullyVisibleInMainWindow(pRect);
                SPUI_UpdateMouseFocus(1);
                return 0;
            } else if (data == 2) {
                FUN_00808b20(mpParentWindow, tw, 0);
                float* pb = VFn<float*(__thiscall*)(void*)>(tw, 0x38)(tw);
                VFn<void(__thiscall*)(void*, float, float)>(tw, 0x70)(tw, pRect[0] + pb[0],
                                                                      pb[1] + pRect[1]);
                MakeFullyVisibleInMainWindow(pRect);
                SPUI_UpdateMouseFocus(1);
                return 0;
            }
            MakeFullyVisibleInMainWindow(pRect);
            SPUI_UpdateMouseFocus(1);
            return 0;
        }
    }
    SPUI_UpdateMouseFocus(1);
    return 0;
}

// @ 0x00835a50
uint32_t cSPUITooltipWinProc_s0083_56e0::DoMessage(void* pWindow, int* msg)
{
    uint32_t result = 0;
    cSPUITooltipManager* mgr = GetTooltipMgr();
    switch (msg[2]) {
    case 6:
        result = mgr->ShowTooltip(0, pWindow, (float*)&mKeyInstance, mWindowID,
                                  (float*)&mTooltipOffsetPosition, 0, 0xffffffff, 0, 0);
        mgr->mbTooltipDisplayed = false;
        return result & 0xffffff00u;
    case 10:
        if (mpMyWindow) {
            if (msg[3] != 1) goto L_af5;
            {
                char c = mbMouseOver;
                uint32_t r = VFn<uint32_t(__thiscall*)(void*, int)>(mpMyWindow, 0xfc)(mpMyWindow, 1);
                if ((char)r == c) break;
                mbMouseOver = (c == 0);
                VFn<void(__thiscall*)(void*, void*)>(mpMyWindow, 0x104)(mpMyWindow, this);
            }
            goto L_af5;
        L_af5:
            if (mbMouseOver) {
                mgr->mElapsedRolloverTime = SPUI_GetElapsedSeconds();
                return result & 0xffffff00u;
            }
            result = mgr->ShowTooltip(0, 0, (float*)&mKeyInstance, mWindowID, (float*)&mTooltipOffsetPosition,
                                      0, 0xffffffff, 0, 0);
            mgr->mMousedOffTime = SPUI_GetElapsedSeconds();
        }
        break;
    case 12:
        if (mbMouseOver) {
            char c = (char)mgr->ShouldDisplayTooltip(pWindow);
            if (c) {
                mgr->mbTooltipDisplayed = true;
                result = mgr->ShowTooltip(1, pWindow, (float*)&mKeyInstance, mWindowID,
                                          (float*)&mTooltipOffsetPosition, mTooltipString.mpBegin, mUnk64,
                                          mTooltipBehavior, 0);
                return result & 0xffffff00u;
            }
            if (mTooltipDetailString.mpBegin != mTooltipDetailString.mpEnd) {
                cSPUITooltipManager* m = GetTooltipMgr();
                if (m->ShouldDisplayDetailedTooltip()) {
                    mgr->ShowTooltip(0, pWindow, (float*)&mKeyInstance, mWindowID, (float*)&mTooltipOffsetPosition,
                                     0, 0xffffffff, 0, 0);
                    result = mgr->ShowTooltip(1, pWindow, (float*)&mKeyInstance, mDetailWindowID,
                                              (float*)&mTooltipOffsetPosition, mTooltipDetailString.mpBegin,
                                              mUnk64, mTooltipBehavior, 1);
                    return result & 0xffffff00u;
                }
            }
            {
                cSPUITooltipManager* m = GetTooltipMgr();
                uint32_t r = (uint32_t)m->ShouldTimeoutTooltip();
                if ((char)r) {
                    result = mgr->ShowTooltip(0, pWindow, (float*)&mKeyInstance, mWindowID,
                                              (float*)&mTooltipOffsetPosition, 0, 0xffffffff, 0, 0);
                    mgr->mbTooltipDisplayed = false;
                    return result & 0xffffff00u;
                }
            }
        }
        break;
    case 17:
        SPKeyFromName(&mKeyInstance, mLayoutName.mpBegin, 0x510a95b, 0x40464100);
        mpMyWindow = pWindow;
        return result & 0xffffff00u;
    case 18:
        mpMyWindow = 0;
        if (mbMouseOver) {
            if (mgr) {
                result = mgr->ShowTooltip(0, 0, (float*)&mKeyInstance, mWindowID, (float*)&mTooltipOffsetPosition,
                                          0, 0xffffffff, 0, 0);
                mgr->mbTooltipDisplayed = false;
            }
            mbMouseOver = false;
        }
        break;
    default:
        break;
    }
    return result & 0xffffff00u;
}

// @ 0x00835cc0
cSPUITooltipWinProc_s0083_56e0::cSPUITooltipWinProc_s0083_56e0()
: mLayoutName(L"Tooltips"),
      mWindowID(0x3754e6c),
      mDetailWindowID(0x3754e6c),
      mTooltipString(),
      mTooltipDetailString(),
      mTooltipOffsetPosition(g_tipOffX, g_tipOffY) {
    mKeyInstance = 0;
    mKeyType = 0;
    mKeyGroup = 0;
    mbMouseOver = false;
    mTooltipBehavior = 0;
    mpMyWindow = 0;
    mUnk64 = 0xffffffff;
}

// @ 0x00835d90
cSPUITooltipWinProc::~cSPUITooltipWinProc()
{
    // member strings destroyed automatically in reverse declaration order
}

// @ 0x00835e30
cSPUITooltipWinProc_s0083_56e0::cSPUITooltipWinProc_s0083_56e0(const wchar_t* layout, uint32_t windowID, const wchar_t* tooltip, float* offset, uint32_t behavior, const wchar_t* detail, uint32_t detailWindowID)
: mLayoutName(layout),
      mWindowID(windowID),
      mDetailWindowID(detailWindowID),
      mTooltipString(tooltip),
      mTooltipDetailString(detail) {
    mTooltipOffsetPosition = *(const Point2D*)offset;
    mKeyInstance = 0;
    mKeyType = 0;
    mKeyGroup = 0;
    mTooltipBehavior = behavior;
    mbMouseOver = false;
    mpMyWindow = 0;
    mUnk64 = 0xffffffff;
}

// @ 0x00835ed0
void cSPUITooltipWinProc_s0083_56e0::SetText(const wchar_t* text, void* data, char bImmediate)
{
    if (text) {
        mTooltipString.assign(text, text + CharStrlen(text));
        bool bOver = mbMouseOver;
        mUnk64 = (uint32_t)data;
        if (bOver && bImmediate) {
            GetTooltipMgr()->ShowTooltip(1, mpMyWindow, (float*)&mKeyInstance, mWindowID,
                                         (float*)&mTooltipOffsetPosition, text, (uint32_t)data,
                                         mTooltipBehavior, 0);
        }
    }
}
