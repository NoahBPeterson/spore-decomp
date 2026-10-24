// Slice s00e22860 - SporeApp 0x00e22860..0x00e236c0
// SP::cSPUIPosse layout helpers, window image setters and audio state counting.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cVec3 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
};

struct cVec4 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
    float w;                       // 0x0c
};

struct cSPUIWindow;

struct cSPUILayout {
    u8           mPad0000[0x18];
    cSPUIWindow* FindWindowByID(int windowID, int recurse);   // 0x008105b0
};

struct cSPUIAnimator {
    void Update();                 // 0x007f63b0
};

// audio object list entry
struct cAudioObject;

// object with an embedded interface sub-object at 0x0c
struct cEmbeddedObject {
    void* mpVtbl0;                 // 0x00
};

struct cHolderObj {
    u8              mPad0000[0x0c];
    cEmbeddedObject mEmbedded0c;   // 0x0c
};

struct cAnimatorFrame {
    int mFirst;                    // 0x00
    int mSecond;                   // 0x04
};

struct cAudioEntry {
    int            mField0;        // 0x00
    cAudioObject*  mpObject4;      // 0x04
};

struct cPossePart {
    u8    mPad0000[0x10];
    void* mpField10;               // 0x10
};

// Float vector helpers implemented in other slices.
cVec4* __cdecl GetMainWindowArea(cVec4* out);                // 0x00805ea0
char   __cdecl SetWindowImage(void* window, const void* rect, int mode);   // 0x00807bb0
void   __cdecl BuildAnimatorRect(void* a, void* b);          // 0x00804ed0

// vtable dispatch helpers, one per slot used by this slice.
static inline const float& max_f(const float& a, const float& b)
{
    return (a < b) ? b : a;
}
static inline const float& min_f(const float& a, const float& b)
{
    return (a > b) ? b : a;
}
static inline int VT_1C_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x07])(p);
}
static inline cVec4* VT_38_0(void* p)
{
    return ((cVec4* (__thiscall*)(void*))(*(void***)p)[0x0e])(p);
}
static inline void* VT_0C_1(void* p, int a)
{
    return ((void* (__thiscall*)(void*, int))(*(void***)p)[0x03])(p, a);
}
static inline void* VT_10_1(void* p, int a)
{
    return ((void* (__thiscall*)(void*, int))(*(void***)p)[0x04])(p, a);
}
static inline void VT_14_1(void* p, int a)
{
    ((void (__thiscall*)(void*, int))(*(void***)p)[0x05])(p, a);
}
static inline void* VT_18_0(void* p)
{
    return ((void* (__thiscall*)(void*))(*(void***)p)[0x06])(p);
}
static inline int VT_BC_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x2f])(p);
}
static inline void* VT_F0_2(void* p, int a, int b)
{
    return ((void* (__thiscall*)(void*, int, int))(*(void***)p)[0x3c])(p, a, b);
}
static inline void VT_70_2F(void* p, float a, float b)
{
    ((void (__thiscall*)(void*, float, float))(*(void***)p)[0x1c])(p, a, b);
}
static inline void VT_7C_2(void* p, int a, int b)
{
    ((void (__thiscall*)(void*, int, int))(*(void***)p)[0x1f])(p, a, b);
}
static inline int VT_A8_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x2a])(p);
}

// ---------------------------------------------------------------------------------------------
// SP::cSPUIPosse
// ---------------------------------------------------------------------------------------------
struct cSPUIPosse {
    u8            mPad0000[0x50];
    void*         mpField50;               // 0x50
    u8            mPad0054[0x60 - 0x54];
    int           mField60;                // 0x60
    u8            mPad0064[0x6c - 0x64];
    int           mField6c;                // 0x6c
    cVec3         mRect70;                 // 0x70
    cSPUILayout   mLayout7c;               // 0x7c
    u8            mPad0094[0xa4 - 0x94];
    cAudioEntry*  mpAudioBeginA4;          // 0xa4
    cAudioEntry*  mpAudioEndA8;            // 0xa8
    u8            mPad00ac[0xd4 - 0xac];
    cPossePart*   mpPartD4;                // 0xd4
    u8            mPad00d8[0x1bc - 0xd8];
    cSPUILayout   mLayout1bc;              // 0x1bc
    u8            mFlag1d4;                // 0x1d4
    u8            mPad01d5[0x1d8 - 0x1d5];
    float         mField1d8;               // 0x1d8
    float         mField1dc;               // 0x1dc
    u8            mPad01e0[0x1e4 - 0x1e0];
    u8            mFlag1e4;                // 0x1e4
    u8            mPad01e5[0x1e8 - 0x1e5];
    float         mField1e8;               // 0x1e8
    u8            mFlag1ec;                // 0x1ec
    u8            mPad01ed[0x208 - 0x1ed];
    cSPUIAnimator* mpAnimator208;          // 0x208

    void  UpdateLayout(int mode);          // 0x00e22b50
    void  SetToolWindowState(int a, int b);// 0x00e21bd0
    void  RefreshToolWindow(int a);        // 0x00e21ca0

    void  SnapToPosition();                // 0x00e22a60
    void  SetScaleF(float scale);          // 0x00e23130
    bool  SetVisibility(void* window);     // 0x00e231a0
    void  SetScale(int scale);             // 0x00e23200
    int   GetAudioCount();                 // 0x00e23250
    void  SetWindowImages(void* image);    // 0x00e235e0
    int   GetWindowImageCount();           // 0x00e23670
    void  GetWindowImageRange(int* out);   // 0x00e23680
    void  ClearToolWindow(int a, int b);   // 0x00e236a0
    void  ClearToolWindowOne(int a);       // 0x00e236b0
    void  SetWindowRect(const cVec3* rect, int unused);   // 0x00e236c0
};

// ---------------------------------------------------------------------------------------------
// Free helpers
// ---------------------------------------------------------------------------------------------
// @ 0x00e232b0
// Returns the image window object attached to `window`, dispatching on the
// concrete window type.
void* sGetWindowImage(void* window)
{
    if (window != 0) {
        if (VT_A8_0(window) != 0) {
            void* inner = (void*)VT_A8_0(window);
            if (inner != 0) {
                void* obj = VT_0C_1(inner, 0xef3c47cf);
                if (obj != 0)
                    return VT_18_0(obj);
                obj = VT_0C_1(inner, 0x103c1908);
                if (obj != 0)
                    return VT_10_1(obj, 0);
                obj = VT_0C_1(inner, 0x053eb526);
                if (obj != 0) {
                    cHolderObj* holder = (cHolderObj*)obj;
                    return VT_10_1(&holder->mEmbedded0c, 0);
                }
            }
        }
    }
    return 0;
}

// @ 0x00e22a60
// Centers the posse window inside the main window area.
void cSPUIPosse::SnapToPosition()
{
    cSPUIWindow* window = mLayout1bc.FindWindowByID(0x3d98298, 0);
    cVec4* area = VT_38_0(window);
    float x = area->x;
    float y = area->y;
    float z = area->z;
    float w = area->w;
    float offset = mField1d8;
    cVec4 mainArea;
    if (mFlag1ec == 0) {
        cVec4* m = GetMainWindowArea(&mainArea);
        offset = ((m->z - m->x) - mField1d8) - (z - x);
    }
    cVec4* m2 = GetMainWindowArea(&mainArea);
    VT_70_2F(window, offset, ((m2->w - m2->y) - mField1dc) - (w - y));
}

// @ 0x00e23130
// Clamps the scale to [0.25, 1.0] and rebuilds the layout.
void cSPUIPosse::SetScaleF(float scale)
{
    float value = scale;
    float lo = 0.25f;
    float hi = 1.0f;
    value = max_f(value, lo);
    value = min_f(value, hi);
    mField1e8 = value;
    mFlag1d4 = 1;
    UpdateLayout(0);
}

// @ 0x00e231a0
// Shows the posse when the passed window is the scale handle.
bool cSPUIPosse::SetVisibility(void* window)
{
    if (VT_1C_0(window) != 0x3d98298)
        return false;
    if (mFlag1d4 != 0)
        UpdateLayout(0);
    cAnimatorFrame frame;
    BuildAnimatorRect(&frame.mFirst, &frame.mSecond);
    mpAnimator208->Update();
    return true;
}

// @ 0x00e23200
// Sets the visible scale handle state.
void cSPUIPosse::SetScale(int scale)
{
    mFlag1e4 = scale;
    cSPUIWindow* window = mLayout1bc.FindWindowByID(0x3d98298, 1);
    if (window != 0) {
        VT_7C_2(window, 1, scale);
        if ((u8)scale != 0) {
            mFlag1d4 = 1;
            UpdateLayout(0);
        }
    }
}

// @ 0x00e23250
// Counts audio objects that are playing or paused.
int cSPUIPosse::GetAudioCount()
{
    int count = 0;
    for (cAudioEntry* it = mpAudioBeginA4; it < mpAudioEndA8; ++it) {
        cAudioObject* obj = it->mpObject4;
        if (VT_BC_0(obj) == 2 || VT_BC_0(obj) == 4)
            ++count;
    }
    return count;
}

// @ 0x00e235e0
// Applies an image to both posse window slots.
void cSPUIPosse::SetWindowImages(void* image)
{
    cSPUIWindow* window = mLayout7c.FindWindowByID(0x3d99184, 1);
    if (window != 0) {
        void* holder = VT_F0_2(window, 0x56bd1b8, 1);
        if (holder != 0) {
            void* obj = VT_0C_1(holder, 0x105a93d);
            if (obj != 0)
                VT_14_1(obj, (int)image);
        }
        cSPUIWindow* window2 = mLayout7c.FindWindowByID(0x3d99185, 1);
        if (window2 != 0) {
            void* obj = VT_0C_1(window2, 0x105a93d);
            if (obj != 0)
                VT_14_1(obj, (int)image);
        }
    }
}

// @ 0x00e23670
// 1 when no window is attached, 2 otherwise.
int cSPUIPosse::GetWindowImageCount()
{
    return (mpField50 != 0) + 1;
}

// @ 0x00e23680
// Image id range of the attached window.
void cSPUIPosse::GetWindowImageRange(int* out)
{
    *out = mpField50 ? 0 : -1;
    out[1] = -1;
}

// @ 0x00e236a0
void cSPUIPosse::ClearToolWindow(int a, int b)
{
    if (mpField50 != 0)
        SetToolWindowState(a, b);
}

// @ 0x00e236b0
void cSPUIPosse::ClearToolWindowOne(int a)
{
    if (mpField50 != 0)
        RefreshToolWindow(a);
}

// @ 0x00e236c0
// Moves the window image to `rect`.
void cSPUIPosse::SetWindowRect(const cVec3* rect, int unused)
{
    if (mpField50 != 0) {
        cVec3& target = mRect70;
        target = *rect;
        void* image = VT_F0_2(mpPartD4->mpField10, 0x3d99151, 1);
        SetWindowImage(image, &target, 0);
    }
}
