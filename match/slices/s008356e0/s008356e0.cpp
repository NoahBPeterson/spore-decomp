// Slice s008356e0 (w2g7 #38), 32-bit MSVC 2008 SP1.
// SPUI tooltip manager / tooltip window proc / variable-width drawable.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

#include "types.h"

static inline void** Vtbl(void* o) { return *(void***)o; }

template <class F> static F VFn(void* o, int byteOff) {
    return (F)(*(void**)((char*)Vtbl(o) + byteOff));
}

// ---------------------------------------------------------------------------
// utility declarations (masked relocations)
// ---------------------------------------------------------------------------
void* __cdecl operator_new6(uint32_t, const void*, int, int, const char*, int);
void  __cdecl operator_delete__(void*);
void  __cdecl FUN_00808b20(void*, void*, int);            // 0x808b20
void  __cdecl FUN_00805fe0(void*, void*);                 // 0x805fe0
void  __cdecl SPUI_UpdateMouseFocus(int);                 // 0x804f50
float __cdecl SPUI_GetElapsedSeconds();                   // 0x805080
void  __cdecl FUN_008352c0();                             // get manager (returns in eax)
void  __cdecl SPKeyFromName(void*, const wchar_t*, int, int); // 0x68d840
void  __cdecl VectorBool_DoInsertValue(void*, const void*, uint32_t); // 0x11e0744

extern char  g_eastlTag[];     // 0x13f6b3c
extern wchar_t g_emptyStr;     // 0x1667bac
extern wchar_t g_emptyCap;     // 0x1667bae
extern float g_tipOffX;        // 0x1548558
extern float g_tipOffY;        // 0x154855c
extern void* g_tooltipMgrPtr;  // 0x164f328 (points at manager+8)

// ---------------------------------------------------------------------------
// EASTL wide string (16 bytes incl. allocator)
// ---------------------------------------------------------------------------
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

// @ (inlined from EASTL basic_string::DeallocateSelf)
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

struct cSPUILayout {
    cSPUILayout* Construct();                          // 0x810000
    void* FindWindowByID(uint32_t id, int recurse);    // 0x8105b0
    void  Init(const void* key, int a, int b);         // 0x8120d0
    void  SetVisibility(int v);                         // 0x810590
};

// ---------------------------------------------------------------------------
// cSPUITooltipManager (retail layout; differs from the dev PDB)
// ---------------------------------------------------------------------------
struct cSPUITooltipManager {
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

// ---------------------------------------------------------------------------
// cSPUITooltipWinProc
// ---------------------------------------------------------------------------
struct IWinProc { virtual void wp0(); };
struct ISerializable { virtual void se0(); };
struct MultiHeapObject {};
struct CustomWinProc : IWinProc, ISerializable, MultiHeapObject {
    int mRefCount;
    CustomWinProc() : mRefCount(0) {}
    ~CustomWinProc() {}
};

struct cSPUITooltipWinProc : CustomWinProc {
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

    cSPUITooltipWinProc();
    cSPUITooltipWinProc(const wchar_t* layout, uint32_t windowID, const wchar_t* tooltip,
                        float* offset, uint32_t behavior, const wchar_t* detail,
                        uint32_t detailWindowID);
    ~cSPUITooltipWinProc();
    void SetText(const wchar_t* text, void* data, char bImmediate);
    uint32_t DoMessage(void* pWindow, int* msg);
};

// @ 0x00835cc0
cSPUITooltipWinProc::cSPUITooltipWinProc()
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

// @ 0x00835e30
cSPUITooltipWinProc::cSPUITooltipWinProc(const wchar_t* layout, uint32_t windowID,
                                         const wchar_t* tooltip, float* offset,
                                         uint32_t behavior, const wchar_t* detail,
                                         uint32_t detailWindowID)
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

// @ 0x00835d90
cSPUITooltipWinProc::~cSPUITooltipWinProc() {
    // member strings destroyed automatically in reverse declaration order
}

// @ 0x00835ed0
void cSPUITooltipWinProc::SetText(const wchar_t* text, void* data, char bImmediate) {
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

// ---------------------------------------------------------------------------
// @ 0x008356e0  cSPUITooltipManager::ShowTooltip
// ---------------------------------------------------------------------------
uint32_t cSPUITooltipManager::ShowTooltip(char bShow, void* pParent, float* pRect, int wndID,
                                          float* pOffset, const wchar_t* text, uint32_t data,
                                          uint32_t behavior, char bDetailed) {
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
            cSPUILayout* p = (cSPUILayout*)operator_new6(0x18, "UI/Tooltip Layout", 0, 0, 0, 0);
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
            ((cSPUILayout*)mpTooltipLayout)->Init(mLayoutKey, 1, 0x5b598f6);
            ((cSPUILayout*)mpTooltipLayout)->SetVisibility(0);
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

// @ 0x00835660  cSPUITooltipManager::CreateTooltipWindow
void cSPUITooltipManager::CreateTooltipWindow(int wndID, const wchar_t* text, uint32_t data) {
    void* found = ((cSPUILayout*)mpTooltipLayout)->FindWindowByID(wndID, 1);
    void* old = mpTooltipWindow;
    if (found != old) {
        if (found) VFn<void(__thiscall*)(void*)>(found, 0)(found);
        mpTooltipWindow = found;
        if (old) VFn<void(__thiscall*)(void*)>(old, 4)(old);
    }
    void* w = mpTooltipWindow;
    if (w) {
        VFn<void(__thiscall*)(void*, int, int)>(w, 0x7c)(w, 0x10, 1);
        void* bb = VFn<void*(__thiscall*)(void*, int, int)>(w, 0);  // placeholder
        (void)bb;
        SetTooltipText(text, data);
    }
}

// @ 0x00835a50  cSPUITooltipWinProc::DoMessage
uint32_t cSPUITooltipWinProc::DoMessage(void* pWindow, int* msg) {
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

// ---------------------------------------------------------------------------
// @ 0x00835fa0  (small /Od helper)
// ---------------------------------------------------------------------------
void __cdecl FUN_00835f80(void* obj, void* owner);   // 0x835f80

struct TooltipHelper {
    void Attach(void* param);
};

void TooltipHelper::Attach(void* param) {
    FUN_00835f80(param, (char*)this - 4);
    void* r = VFn<void*(__thiscall*)(void*)>(this, 0x14)(this);
    *(void**)((char*)param + 0xc) = r;
}

// ---------------------------------------------------------------------------
// @ 0x00835fe0  cSPUIVariableWidthDrawable::Draw (complete approximation)
// ---------------------------------------------------------------------------
struct IDrawable { virtual void d0(); };
struct ISerializable2 { virtual void s0(); };
struct CustomDrawable : IDrawable, ISerializable2, MultiHeapObject {
    int mRefCount;
    CustomDrawable() : mRefCount(0) {}
};
struct RenderContext {
    void* Begin2D(int);
    void  End2D();
};
struct cSPUIVariableWidthDrawable : CustomDrawable {
    void* mpImage;       // +0xc
    uint32_t mFillColor; // +0x10
    cSPUIVariableWidthDrawable();
    void Draw(RenderContext* ctx, float* rect);
};

void cSPUIVariableWidthDrawable::Draw(RenderContext* ctx, float* rect) {
    void* painter = ctx->Begin2D(0);
    if (mpImage == 0) {
        VFn<void(__thiscall*)(void*, int)>(painter, 4)(painter, (int)mFillColor);
        VFn<void(__thiscall*)(void*, float, float, float, float)>(painter, 0x38)(
            painter, rect[0], rect[1], rect[2], rect[3]);
    } else {
        float* img = (float*)mpImage;
        if (img) VFn<void(__thiscall*)(void*, void*)>(painter, 4)(painter, img);
        float x0 = rect[0];
        float w = rect[2] - x0;
        float iw = (float)*(int*)((char*)img + 0x1c);
        if (w < iw) {
            float uv[8];
            uv[0] = 0.0f; uv[1] = 0.0f;
            uv[2] = (iw - (iw - w) * 0.5f) / iw;
            uv[3] = 1.0f;
            uv[4] = rect[1];
            uv[5] = rect[3];
            uv[6] = w - w * 0.5f;
            VFn<void(__thiscall*)(void*, float*)>(painter, 0x58)(painter, uv);
            VFn<void(__thiscall*)(void*, float*, void*, void*)>(painter, 0x58)(painter, uv, mpImage, 0);
        } else if (w == iw) {
            float uv[4] = {0.0f, 0.0f, 1.0f, 1.0f};
            VFn<void(__thiscall*)(void*, float*)>(painter, 0x58)(painter, uv);
        } else {
            float uv[8];
            uv[0] = 0.0f; uv[1] = 0.0f; uv[2] = 0.5f; uv[3] = 1.0f;
            uv[4] = rect[1]; uv[5] = rect[3]; uv[6] = rect[2];
            VFn<void(__thiscall*)(void*, float*)>(painter, 0x58)(painter, uv);
            VFn<void(__thiscall*)(void*, float*, void*, void*)>(painter, 0x58)(painter, uv, mpImage, 0);
            float step = 0.0f;
            float y1 = rect[1];
            float x = x0 + step;
            float xEnd = rect[2] - step;
            while (x < xEnd) {
                float w2 = xEnd;
                if (step < xEnd - x) w2 = step + x;
                float q[4] = { x, y1, w2, rect[3] };
                VFn<void(__thiscall*)(void*, float*, void*, void*)>(painter, 0x58)(painter, q, mpImage, 0);
                x += step;
            }
        }
    }
    ctx->End2D();
}

// @ 0x00836420
cSPUIVariableWidthDrawable::cSPUIVariableWidthDrawable()
    : mpImage(0), mFillColor(0xffffffff) {}

// ---------------------------------------------------------------------------
// @ 0x008364c0 / 0x00836500  eastl::basic_string<uint16_t> find / rfind
// ---------------------------------------------------------------------------
template <typename T> static const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }

struct UShortVec {
    const uint16_t* mpBegin;
    const uint16_t* mpEnd;
    int FindFrom(uint16_t c, uint32_t position);
    int ReverseFind(uint16_t c, uint32_t position);
};

static const uint16_t* CharTypeStringRFind(const uint16_t* pRBegin, const uint16_t* pREnd,
                                           uint16_t c) {
    while (pRBegin > pREnd) {
        if (*(pRBegin - 1) == c) return pRBegin;
        --pRBegin;
    }
    return pREnd;
}

// @ 0x008364c0
int UShortVec::FindFrom(uint16_t c, uint32_t position) {
    if (position < (uint32_t)(mpEnd - mpBegin)) {
        const uint16_t* pResult = mpBegin + position;
        while (pResult != mpEnd && *pResult != c) ++pResult;
        if (pResult != mpEnd) return (int)(pResult - mpBegin);
    }
    return -1;
}

// @ 0x00836500
int UShortVec::ReverseFind(uint16_t c, uint32_t position) {
    const uint32_t nLength = (uint32_t)(mpEnd - mpBegin);
    if (nLength) {
        const uint16_t* const pEnd = mpBegin + min_alt(nLength - 1, position) + 1;
        const uint16_t* const pResult = CharTypeStringRFind(pEnd, mpBegin, c);
        if (pResult != mpBegin) return (int)((pResult - 1) - mpBegin);
    }
    return -1;
}

// ---------------------------------------------------------------------------
// @ 0x00836620  buffer allocate-or-empty ; @ 0x00836850  copy helper
// ---------------------------------------------------------------------------
struct BoolVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mPad;          // +0xc
    uint32_t mAllocator;    // +0x10
    void ReserveBuffer(uint32_t n);
    void Init(const BoolVec& other);
};

// @ 0x00836620
void BoolVec::ReserveBuffer(uint32_t n) {
    if (n > 1) {
        uint8_t* m = (uint8_t*)operator_new6(n, g_eastlTag, 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        mpBegin = m;
        mpEnd = m;
        mpCapacity = m + n;
    } else {
        mpBegin = (uint8_t*)&g_emptyStr;
        mpEnd = (uint8_t*)&g_emptyStr;
        mpCapacity = (uint8_t*)&g_emptyCap;
    }
}

// @ 0x00836850
void BoolVec::Init(const BoolVec& other) {
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mAllocator = other.mAllocator;
    const uint8_t* pSrc = other.mpBegin;
    const uint8_t* pEnd = other.mpEnd;
    uint32_t size = (uint32_t)(pEnd - pSrc);
    ReserveBuffer(size + 1);
    uint8_t* dst = mpBegin;
    VectorBool_DoInsertValue(dst, pSrc, size);
    mpEnd = dst + (pEnd - pSrc);
    *mpEnd = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00836740  resource lookup by file extension (complete approximation)
// ---------------------------------------------------------------------------
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
};

extern "C" wchar_t* __cdecl wcsrchr(const wchar_t*, wchar_t);
extern "C" char* __cdecl strstr(const char*, const char*);
void __cdecl ConvertToString8(String8* out, const wchar_t* s, int len); // 0x93c440
void __cdecl FUN_00594410(void* it);                                     // map begin iterator

struct MapNode { uint32_t mValue; char* mKey; MapNode* mLeft; MapNode* mRight; };
struct ResFinder { uint32_t FindByExt(wchar_t* name); };

// @ 0x00836740
uint32_t ResFinder::FindByExt(wchar_t* name) {
    wchar_t* dot = wcsrchr(name, L'.');
    if (dot) {
        wchar_t* p = dot;
        while (*p) ++p;
        if ((int)(p - (dot + 1)) > 1) {
            String8 ext;
            ConvertToString8(&ext, dot + 1, -1);
            MapNode* it;
            FUN_00594410(&it);
            MapNode** root = (MapNode**)(*(int*)((char*)this + 0x10) +
                                         *(int*)((char*)this + 0x14) * 4);
            while (it != *root) {
                if (strstr(it->mKey, ext.mpBegin)) {
                    uint32_t v = it->mValue;
                    if (ext.mpBegin && (int)(ext.mpCapacity - ext.mpBegin) > 1)
                        operator_delete__(ext.mpBegin);
                    return v;
                }
                it = it->mLeft ? it->mLeft : it->mRight;
            }
            if (ext.mpBegin && (int)(ext.mpCapacity - ext.mpBegin) > 1)
                operator_delete__(ext.mpBegin);
        }
    }
    return 0;
}
