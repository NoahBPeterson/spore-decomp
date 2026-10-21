// src/game/UTFSpore_Win32/InputMan.cpp -- migrated from slice(s) s00958a70, s008d2590 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/InputMan.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount(void);
extern "C" __declspec(dllimport) short __stdcall GetAsyncKeyState(int vKey);
extern "C" __declspec(dllimport) short __stdcall GetKeyState(int nVirtKey);
extern "C" __declspec(dllimport) int __stdcall GetKeyboardState(unsigned char* lpKeyState);
extern "C" __declspec(dllimport) int __stdcall GetCursorPos(void* lpPoint);
extern "C" __declspec(dllimport) int __stdcall SetCursorPos(int x, int y);
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);
#include <math.h>
#include <string.h>
#include "EA/Allocator/ICoreAllocator.h"
#include "EA/Thread/Mutex.h"
#include "EA/Text/Typesetter.h"

// ---- items of slice s008d2590 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount(void);
extern "C" __declspec(dllimport) short __stdcall GetAsyncKeyState(int vKey);
extern "C" __declspec(dllimport) short __stdcall GetKeyState(int nVirtKey);
extern "C" __declspec(dllimport) int __stdcall GetKeyboardState(unsigned char* lpKeyState);
extern "C" __declspec(dllimport) int __stdcall GetCursorPos(void* lpPoint);
extern "C" __declspec(dllimport) int __stdcall SetCursorPos(int x, int y);
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);
struct POINT_ { int x, y; };
struct DeviceInfo {
    int type;
    int unused;
    unsigned index;
    wchar_t name[32];
};
struct IDirectInput8W_ {
    virtual long __stdcall QueryInterface(void*, void**);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
};
struct DIJOYSTATE_ {
    long lX, lY, lZ, lRx, lRy, lRz;
    long rglSlider[2];
    unsigned long rgdwPOV[4];
    unsigned char rgbButtons[32];
};
struct IDirectInputDevice8W_ {
    virtual long __stdcall QueryInterface(void*, void**);
    virtual unsigned long __stdcall AddRef();
    virtual unsigned long __stdcall Release();
    virtual long __stdcall s3();
    virtual long __stdcall s4();
    virtual long __stdcall s5();
    virtual long __stdcall s6();
    virtual long __stdcall Acquire();                                   // +0x1c
    virtual long __stdcall Unacquire();
    virtual long __stdcall GetDeviceState(unsigned long cb, void* data); // +0x24
    virtual long __stdcall s10();
    virtual long __stdcall s11();
    virtual long __stdcall s12();
    virtual long __stdcall s13();
    virtual long __stdcall s14();
    virtual long __stdcall s15();
    virtual long __stdcall s16();
    virtual long __stdcall s17();
    virtual long __stdcall s18();
    virtual long __stdcall s19();
    virtual long __stdcall s20();
    virtual long __stdcall s21();
    virtual long __stdcall s22();
    virtual long __stdcall s23();
    virtual long __stdcall s24();
    virtual long __stdcall Poll();                                      // +0x64
};
struct XINPUT_GAMEPAD_ {
    unsigned short wButtons;
    unsigned char bLeftTrigger;
    unsigned char bRightTrigger;
    short sThumbLX, sThumbLY, sThumbRX, sThumbRY;
};
struct XINPUT_STATE_ {
    unsigned long dwPacketNumber;
    XINPUT_GAMEPAD_ Gamepad;
};
extern unsigned long (__stdcall *g_XInputGetState)(unsigned long, XINPUT_STATE_*);        // 0x1667a5c
namespace EA {
namespace Input {
class InputMan;
}
}
namespace EA {
namespace Input {
class Device { public:
    virtual ~Device() {}
};
}
}
namespace EA {
namespace Input {
class Controller : public Device { public:
    InputMan* mpInputMan;
    unsigned mnIndex;
    unsigned short mRepeatCount[24];
    float mState[24];
    bool mbAvailable;
    unsigned mnLastEventTime;
    bool mbXInputDevice;
    unsigned mnXInputIndex;
    IDirectInputDevice8W_* mpDIController;
    int mAxisMapping[4];

    Controller()
        : mpInputMan(0), mnIndex(0), mbAvailable(false), mnLastEventTime(0), mbXInputDevice(false), mpDIController(0)
    {
        memset(mRepeatCount, 0, sizeof(mRepeatCount));
        memset(mState, 0, sizeof(mState));
        for (int i = 0; i < 4; ++i) mAxisMapping[i] = 0;
    }
    virtual ~Controller() {}

    void GetDeviceInfo(DeviceInfo* info);
    float GetControlValue(unsigned id, bool bBinary);
    bool GetControlButton(unsigned id, bool bPressed);
    bool GetControlStates(float* out, bool bBinary);
};
}
}
bool IsKeyDown(unsigned vk, unsigned modifiers);  // 0x008d3200 (defined below; used by a stub's inline body)
namespace EA {
namespace Input {
class Keyboard : public Device { public:
    InputMan* mpInputMan;
    unsigned mnIndex;
    bool mbAvailable;

    Keyboard() : mpInputMan(0), mnIndex(0), mbAvailable(false) {}
    virtual ~Keyboard() {}
    void GetDeviceInfo(DeviceInfo* info);
    bool GetKeyboardState(unsigned char* out);
    void GetLocale(wchar_t* out);
    bool IsToggleKeyOn(unsigned vk);
    bool IsKeyDown(unsigned vk, unsigned modifiers);
};
}
}
namespace EA {
namespace Input {
class Mouse : public Device { public:
    InputMan* mpInputMan;
    unsigned mnIndex;
    bool mbAvailable;
    int mXMin, mYMin, mXMax, mYMax;

    Mouse() : mpInputMan(0), mnIndex(0), mbAvailable(false), mXMin(0x80000000), mYMin(0x80000000), mXMax(0x7fffffff), mYMax(0x7fffffff) {}
    virtual ~Mouse() {}
    void GetDeviceInfo(DeviceInfo* info);
    void SetBounds(int xmin, int ymin, int xmax, int ymax);
    void GetBounds(int* xmin, int* ymin, int* xmax, int* ymax);
    bool GetPosition(int* x, int* y);
    bool SetPosition(int x, int y, bool bRelative);
    bool GetButtons(unsigned char* out);
    bool IsButtonDown(unsigned code);
};
}
}
namespace EA {
namespace Input {
class InputMan { public:
    virtual ~InputMan();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void OnControllerAvailability(Controller* c, bool bAvailable);   // +0x20

    void* mpDeviceChangeCallback;
    void* mpDeviceChangeCallbackContext;
    void (*mpPollCompletionCallback)(InputMan*, void*);
    void* mpPollCompletionCallbackContext;
    void* mpEventCallback;
    void* mpEventCallbackContext;
    unsigned mnEventCallbackDeviceTypeMask;
    bool mbInitialized;
    float mfNoiseThreshold;
    float mfBinaryThreshold;
    float mfAutomaticPollingRateMS;
    int mnLogLevel;
    Controller mController[4];
    Keyboard mKeyboard;
    Mouse mMouse;
    IDirectInput8W_* mpDI;
    unsigned mnDIEnumCount;
    IDirectInputDevice8W_* mpDIEnumControllers[4];

    InputMan();
    void GetControllerDeviceInfo(unsigned idx, DeviceInfo* info);          // 0x8d2330
    bool UpdateControl(Controller* c, int idx, float v, char bNormalized, unsigned dt);  // 0x8d24e0
    void UpdateController(unsigned idx);
    void PollAll();
};
}
}
bool ApplyThresholds(float v, float noise, float bin, float* out, unsigned short* count, unsigned dt); // 0x8d1cf0
// ---- items of slice s008d2590 end

// ---- items of slice s00958a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_13eb1bc, g_1440738;
typedef uint8_t u8;
typedef uint32_t u32;
struct EAlloc { void* p; EAlloc(void* x) : p(x) {} };
struct Node { Node* next; Node* prev; };
struct V2 {
    float x, y;
    V2() {}
    V2(float a, float b) : x(a), y(b) {}
    V2(const V2& o) : x(o.x), y(o.y) {}
};
struct Msg;
struct IWin;
struct ICb { virtual void c0(); virtual void Call(IWin* w, IWin* arg); };
struct IHook {
    virtual void h0();
    virtual void Release();
    virtual void h2();
    virtual void Notify(int code, IWin* w, Msg* m);   // vtbl+0xc
};
struct IAlloc {
    virtual void a0();
    virtual void a1();
    virtual void* Alloc(int sz, const char* name, u32 flags);   // vtbl+8
    virtual void Free(void* p, int sz);               // vtbl+0xc
};
struct IRel { virtual void r0(); virtual void Release(); };   // vtbl+4
struct IWin {
    virtual void i00();
    virtual void i01();
    virtual void i02();
    virtual void i03();
    virtual IWin* vGetParent();
    virtual void i05();
    virtual void i06();
    virtual void i07();
    virtual void i08();
    virtual void i09();
    virtual void i0a();
    virtual void i0b();
    virtual void i0c();
    virtual void i0d();
    virtual void i0e();
    virtual void i0f();
    virtual void i10();
    virtual void i11();
    virtual void i12();
    virtual void i13();
    virtual void i14();
    virtual void i15();
    virtual void i16();
    virtual void i17();
    virtual void i18();
    virtual void i19();
    virtual void i1a();
    virtual void i1b();
    virtual void i1c();
    virtual void i1d();
    virtual void i1e();
    virtual void vSetFlags(int a, int b);              // vtbl+0x7c (31)
    virtual void i32(); virtual void i33(); virtual void i34(); virtual void i35();
    virtual void i36(); virtual void i37(); virtual void i38(); virtual void i39();
    virtual void i40(); virtual void i41(); virtual void i42(); virtual void i43();
    virtual void i44(); virtual void i45(); virtual void i46();
    virtual bool vHitLocal(V2 p);                      // vtbl+0xbc (47)
    virtual void i48();
    virtual V2 vToLocal(V2 p);                         // vtbl+0xc4 (49)
    virtual bool vHit(V2 p, V2* out);                  // vtbl+0xc8 (50)
    virtual void i51(); virtual void i52(); virtual void i53(); virtual void i54();
    virtual void i55(); virtual void i56(); virtual void i57();
    virtual void vSetOwner(IWin* w);                   // vtbl+0xe8 (58)
    virtual void i59(); virtual void i60(); virtual void i61();
    virtual bool vAccepts(IWin* w);                    // vtbl+0xf8 (62)
};
struct Base0 { virtual void b0(); virtual void Release(); };
struct Win : Base0, IWin {
    Node n8;            // +8 child-list link
    u32  f10;
    u32  f14;
    Node n18;           // +0x18, prev(+0x1c) != 0 means linked
    u32  f20, f24, f28;
    u32  flags;         // +0x2c
    u8   b30, b31, b32, b33;
    u32  f34;
    Win* parent;        // +0x38
    Node children;      // +0x3c
    u8   pad44[0x78 - 0x44];
    u32  f78;
};
struct Msg { IWin* src; IWin* dst; u32 rest[5]; };
struct Iter { Node* n; };
struct MsgList {
    Node    anchor;      // +0
    IAlloc* alloc;       // +8
    u32     allocFlags;  // +0xc
    MsgList(const EAlloc& a) { alloc = (IAlloc*)a.p; allocFlags = 0; anchor.next = &anchor; anchor.prev = &anchor; }
    ~MsgList() {
        Node* p = anchor.next;
        while (p != &anchor) { Node* n = p; p = p->next; alloc->Free(n, 0x24); }
    }
    // @ 0x958ca0
    Iter __thiscall EraseRange(Iter first, Iter last);
    // @ 0x9595e0
    void __thiscall InsertRange(Node* where, Iter first, Iter last, int tag);
};
struct FocusList {
    Node    anchor;      // +0
    IAlloc* alloc;       // +8
    u32     allocFlags;  // +0xc
    FocusList(const EAlloc& a) { alloc = (IAlloc*)a.p; allocFlags = 0; anchor.next = &anchor; anchor.prev = &anchor; }
    ~FocusList() {
        Node* p = anchor.next;
        while (p != &anchor) { Node* n = p; p = p->next; alloc->Free(n, 0x10); }
    }
};
template <class T> struct Ref {
    T* p;
    Ref(T* x) : p(x) {}
    ~Ref() { if (p) p->Release(); }
    T* operator->() const { return p; }
    operator T*() const { return p; }
};
struct ListHead { Node n; ListHead() { n.prev = &n; n.next = &n; } ~ListHead(); };      // dtor 0x620230
struct Mutex {
    Mutex(int a, int b);   // 0x9222a0
    ~Mutex();
    u32 pad[12];
};
struct Typesetter {
    Typesetter(int a);     // 0x89d820
    ~Typesetter();
    u32 pad[0x14c];
};
struct WM {
    virtual ~WM();
    virtual void s01();
    virtual void s02(int a, int b);
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08(int a);
    virtual void s09();
    virtual void s0a();
    virtual void s0b();
    virtual void s0c();
    virtual void s0d();
    virtual void s0e(int a);
    virtual void s0f();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void SetFocus(int a, IWin* w);              // vtbl+0x4c (19)

    // @ 0x958bb0
    void __thiscall DestroyDisplayList(Node* head);
    // @ 0x958a70
    Win* __thiscall HitTest(Win* w, V2* pt, const V2& p3, V2* outLocal);
    // @ 0x958b60
    void __thiscall MarkTree(Win* w);
    // @ 0x958c60
    bool __thiscall IsFocusWindow(IWin* w);
    // @ 0x958cf0
    WM();
    // @ 0x958fa0
    bool __thiscall SendModifiedMsg(IWin* w, IWin* src, Msg* m);
    // @ 0x959050
    IWin* __thiscall UpdateCursorWindow(V2* out, bool flag);
    // @ 0x959230
    IWin* __thiscall FindWindowAt(const V2* pt);
    // @ 0x9592a0
    void __thiscall LinkTickable(Win* w);
    // @ 0x9592e0
    bool __thiscall DispatchTree(Msg* m, bool flag);
    // @ 0x9593d0
    bool __thiscall DispatchUp(Win* w, Msg* m, bool flag);
    // @ 0x9594b0
    bool __thiscall PopFocus(IWin* w, IWin* arg);
    // @ 0x959640
    bool __thiscall SendMsgFull(IWin* src, IWin* win, Msg* m, bool a4, bool a5);

    // @ 0x95b860
    void __thiscall Shutdown();
    // @ 0x95b310
    void __thiscall UpdateVisuals();
    // external (other slices)
    void __thiscall UpdateRenderState(Win* w, int a, int b);              // 0x95a140
    void __thiscall BuildDisplayList(Node* out, Win* w, void* tmp);       // 0x95a580
    void __thiscall RenderWindow(Win* w, void* ctx);                      // 0x95a510
    void __thiscall ComputeClip(void* out, Win* w);                       // 0x958150
    void __thiscall ResetChildWindowCache();                              // 0x962be0
    void __thiscall FlushMessageQueue();                                  // 0x95b290
    bool __thiscall DispatchMsgToWindow(Win* w, Msg* m, int f);  // 0x9589f0 (not in slice)
    void __thiscall F9587d0(Win* w);                               // 0x9587d0 (not in slice)

    Ref<Win> mainWin;    // +4
    ListHead lA;         // +8
    ListHead lB;         // +0x10 (tickable windows)
    ListHead lC;         // +0x18
    Node*  tickIter;     // +0x20
    u8     f24, f25, pad26[2];
    Mutex  mxA;          // +0x28
    u8     f58, f59, pad5a[2];
    ListHead lD;         // +0x5c
    ListHead lE;         // +0x64
    u8     pad6c[4];
    Mutex  mxB;          // +0x70
    ListHead lF;         // +0xa0
    float  fa8, fac, fb0, fb4;
    Ref<IRel> fb8;       // +0xb8
    float  mx, my;       // +0xbc,+0xc0
    u32    fc4;
    Ref<IHook> hook;     // +0xc8
    u32    fcc, fd0;
    MsgList q0, q1, q2, q3, q4;   // +0xd4
    u32    f124;
    Typesetter ts;       // +0x128
    Mutex  mxC;          // +0x658
    u32    f688;
    u8     pad68c[0x6b4 - 0x68c];
    Win*   f6b4;
    u32    f6b8;
    Win*   f6bc;
    u8     pad_6c0[0x81c - 0x6c0];
    FocusList focusList; // +0x81c
    IWin*  cur;          // +0x82c
    ICb*   curCb;        // +0x830
    u8     f834;
};
// ---- items of slice s00958a70 end

// @ 0x008d2590
void EA::Input::InputMan::UpdateController(unsigned idx)
{
    EA::Input::Controller* c = &mController[idx];
    unsigned now = GetTickCount();
    unsigned dt = c->mnLastEventTime - now;
    bool bChanged = false;
    unsigned n = 0;

    if (c->mbXInputDevice) {
        XINPUT_STATE_ st;
        if (g_XInputGetState(c->mnXInputIndex, &st) != 0) {
            if (c->mbAvailable) {
                c->mbAvailable = false;
                OnControllerAvailability(c, false);
            }
            return;
        }
        if (!c->mbAvailable) {
            c->mbAvailable = true;
            OnControllerAvailability(c, true);
        }
        c->mState[0] = ((float)st.Gamepad.sThumbLX + 0.5f) * 3.0518e-5f;
        c->mState[1] = ((float)st.Gamepad.sThumbLY + 0.5f) * 3.0518e-5f;
        c->mState[2] = ((float)st.Gamepad.sThumbRX + 0.5f) * 3.0518e-5f;
        c->mState[3] = ((float)st.Gamepad.sThumbRY + 0.5f) * 3.0518e-5f;
        for (unsigned i = 0; i < 4; ++i) {
            if (ApplyThresholds(c->mState[i], mfNoiseThreshold, mfBinaryThreshold, &c->mState[i], &c->mRepeatCount[i], dt)) {
                bChanged = true;
                n++;
            }
        }
        unsigned short w = st.Gamepad.wButtons;
        c->mState[8]  = (float)((w >> 2) & 1);
        c->mState[9]  = (float)(w & 1);
        c->mState[10] = (float)((w >> 3) & 1);
        c->mState[11] = (float)((w >> 1) & 1);
        c->mState[12] = (float)((w >> 14) & 1);
        c->mState[13] = (float)(w >> 15);
        c->mState[14] = (float)((w >> 12) & 2);
        c->mState[15] = (float)((w >> 11) & 2);
        c->mState[16] = (float)((w >> 5) & 1);
        c->mState[17] = (float)((w >> 4) & 1);
        c->mState[18] = (float)((w >> 8) & 1);
        c->mState[19] = (float)((w >> 9) & 1);
        c->mState[20] = (float)st.Gamepad.bLeftTrigger * 0.0039215684f;   // 0x3b808080: 1/255 rounded down
        c->mState[21] = (float)st.Gamepad.bRightTrigger * 0.0039215684f;
        c->mState[22] = (float)((w >> 6) & 1);
        c->mState[23] = (float)((w >> 7) & 1);
        for (unsigned j = 0; j < 16; ++j) {
            if (ApplyThresholds(c->mState[8 + j], mfNoiseThreshold, mfBinaryThreshold, &c->mState[8 + j], &c->mRepeatCount[8 + j], dt)) {
                bChanged = true;
                n++;
            }
        }
    } else {
        IDirectInputDevice8W_* dev = c->mpDIController;
        if (!dev)
            return;
        DIJOYSTATE_ js = {0};
        if (dev->Poll() < 0) {
            if (c->mpDIController->Acquire() < 0 || c->mpDIController->Poll() < 0)
                goto fail;
        }
        if (c->mpDIController->GetDeviceState(sizeof(js), &js) < 0) {
        fail:
            memset(&js, 0, sizeof(js));
            if (c->mbAvailable) {
                c->mbAvailable = false;
                OnControllerAvailability(c, false);
            }
        } else if (!c->mbAvailable) {
            c->mbAvailable = true;
            OnControllerAvailability(c, true);
        }
        js.lY = 0xffff - js.lY;
        js.lRy = 0xffff - js.lRy;
        unsigned i;
        for (i = 0; i < 4; ++i) {
            if (UpdateControl(c, i, (float)(&js.lX)[c->mAxisMapping[i]], 0, dt)) {
                bChanged = true;
                n++;
            }
        }
        float s, co;
        unsigned pov = js.rgdwPOV[0];
        if (pov == 0xFFFFFFFF || (unsigned short)pov == 0xFFFF) {
            s = 0.0f;
            co = 0.0f;
        } else {
            float a = (float)pov * 1.7453292e-4f;
            s = sinf(a);
            co = cosf(a);
        }
        if (UpdateControl(c, i++, s, 1, dt)) { bChanged = true; n++; }
        if (UpdateControl(c, i++, co, 1, dt)) { bChanged = true; n++; }
        c->mState[6] = 0.0f;
        c->mState[7] = 0.0f;
        for (unsigned j = 0; j < 16; ++j) {
            float v = (js.rgbButtons[j] & 0x80) ? 1.0f : 0.0f;
            float av = fabsf(v);
            if (av < mfNoiseThreshold)
                v = 0.0f;
            c->mState[8 + j] = v;
            bool b = false;
            if (av < mfBinaryThreshold) {
                unsigned short cnt = c->mRepeatCount[8 + j];
                if (cnt != 0)
                    cnt = (cnt == 0xffff) ? 0 : 0xffff;
                c->mRepeatCount[8 + j] = cnt;
            } else if (dt > 200) {
                unsigned short cnt = c->mRepeatCount[8 + j];
                if (cnt < 0xfffd) {
                    c->mRepeatCount[8 + j] = cnt + 1;
                    b = true;
                }
            }
            if (b) {
                bChanged = true;
                n++;
            }
        }
    }
    if (bChanged)
        c->mnLastEventTime = now;
}

// @ 0x008d2b50
void EA::Input::Controller::GetDeviceInfo(DeviceInfo* info)
{
    mpInputMan->GetControllerDeviceInfo(mnIndex, info);
}

// @ 0x008d2b80
float EA::Input::Controller::GetControlValue(unsigned id, bool bBinary)
{
    id -= 2000;
    float v;
    if (id < 24) {
        v = mState[id];
        if (bBinary) {
            if (id == 0x7d6 || id == 0x7d7)
                v = (float)(v >= 0.0f);
            else
                v = (float)(fabs(v) >= mpInputMan->mfBinaryThreshold);
        }
    } else {
        v = 0.0f;
    }
    return v;
}

// @ 0x008d2c20
bool EA::Input::Controller::GetControlButton(unsigned id, bool bPressed)
{
    id -= 2000;
    if (id < 24) {
        if (bPressed)
            return mRepeatCount[id] == 1;
        return mRepeatCount[id] == 0xffff;
    }
    return false;
}

// @ 0x008d2c60
bool EA::Input::Controller::GetControlStates(float* out, bool bBinary)
{
    if (out) {
        memcpy(out, mState, sizeof(mState));
        if (bBinary) {
            float thr = mpInputMan->mfBinaryThreshold;
            for (int i = 0; i < 24; ++i)
                out[i] = (fabs(mState[i]) < thr) ? 0.0f : 1.0f;
        }
    }
    return true;
}

// @ 0x008d2d70
void EA::Input::Keyboard::GetDeviceInfo(DeviceInfo* info)
{
    info->type = 4;
    info->unused = 0;
    info->index = mnIndex;
    wcscpy(info->name, L"Keyboard");
}

// @ 0x008d2db0
unsigned GetModifierState()
{
    unsigned m = 0;
    if (GetAsyncKeyState(0x10) & 0x8000) m |= 1;
    if (GetAsyncKeyState(0x11) & 0x8000) m |= 2;
    if (GetAsyncKeyState(0x12) & 0x8000) m |= 4;
    if ((GetAsyncKeyState(0x5b) & 0x8000) || (GetAsyncKeyState(0x5c) & 0x8000)) m |= 0x10;
    return m;
}

// @ 0x008d2e20
bool EA::Input::Keyboard::GetKeyboardState(unsigned char* out)
{
    if (out) {
        unsigned char keys[256];
        if (::GetKeyboardState(keys)) {
            for (int i = 0; i < 256; ++i)
                out[i] = keys[i] >> 7;
        }
    }
    return true;
}

// @ 0x008d2e70
void EA::Input::Keyboard::GetLocale(wchar_t* out)
{
    wcscpy(out, L"en-us");
}

// @ 0x008d2ea0
void EA::Input::Mouse::GetDeviceInfo(DeviceInfo* info)
{
    info->type = 2;
    info->unused = 0;
    info->index = mnIndex;
    wcscpy(info->name, L"Mouse");
}

// @ 0x008d2ee0
void EA::Input::Mouse::SetBounds(int xmin, int ymin, int xmax, int ymax)
{
    mXMin = xmin;
    mYMin = ymin;
    mXMax = xmax;
    mYMax = ymax;
}

// @ 0x008d2f00
void EA::Input::Mouse::GetBounds(int* xmin, int* ymin, int* xmax, int* ymax)
{
    *xmin = mXMin;
    *ymin = mYMin;
    *xmax = mXMax;
    *ymax = mYMax;
}

// @ 0x008d2f30
bool GetCursorPosition(int* x, int* y)
{
    POINT_ p;
    GetCursorPos(&p);
    *x = p.x;
    *y = p.y;
    return true;
}

// @ 0x008d2f60
bool EA::Input::Mouse::SetPosition(int x, int y, bool bRelative)
{
    POINT_ p;
    if (bRelative) {
        GetCursorPos(&p);
        x += p.x;
        y += p.y;
    }
    SetCursorPos(x, y);
    return true;
}

// @ 0x008d2fb0
bool IsMouseButtonDown(unsigned code)
{
    if (code - 1000 <= 0x3ec) {
        int swapMap[5] = { 0x3ea, 0x3e9, 0x3e8, 0x3ec, 0x3eb };
        int vkMap[5] = { 1, 4, 2, 5, 6 };
        if (GetSystemMetrics(23))
            code = swapMap[code - 1000];
        return ((unsigned)GetAsyncKeyState(vkMap[code - 1000]) >> 15) & 1;
    }
    return false;
}

// @ 0x008d3050
bool EA::Input::Mouse::GetButtons(unsigned char* out)
{
    for (int i = 0; i < 5; ++i)
        out[i] = IsMouseButtonDown(1000 + i);
    return true;
}

// @ 0x008d31b0
void EA::Input::InputMan::PollAll()
{
    for (unsigned i = 0; i < 4; ++i)
        UpdateController(i);
    if (mpPollCompletionCallback)
        mpPollCompletionCallback(this, mpPollCompletionCallbackContext);
}

// @ 0x008d3270
bool EA::Input::Keyboard::IsToggleKeyOn(unsigned vk)
{
    if (vk == 0x14 || (vk > 0x8f && vk <= 0x91)) {
        bool r = GetKeyState(vk) & 1;
        return r;
    }
    return false;
}

// @ 0x008d32b0
bool EA::Input::Mouse::GetPosition(int* x, int* y)
{
    POINT_ p;
    GetCursorPos(&p);
    *x = p.x;
    *y = p.y;
    return true;
}

// @ 0x008d32e0
bool EA::Input::Mouse::IsButtonDown(unsigned code)
{
    return IsMouseButtonDown(code);
}

// @ 0x008d3450
bool EA::Input::Keyboard::IsKeyDown(unsigned vk, unsigned modifiers)
{
    if (vk - 1000 <= 4)
        return IsMouseButtonDown(vk);
    switch (vk - 1) {
    case 0: case 1: case 3: case 4: case 5:
        return false;
    default:
        break;
    }
    bool r = ((unsigned)GetAsyncKeyState(vk) >> 15) & 1;
    return r;
}

// @ 0x00959050
IWin* __thiscall WM::UpdateCursorWindow(V2* out, bool flag)
{
    V2 loc(g_1440738, g_1440738);
    float q[4];
    q[0] = g_13eb1bc; q[1] = mx; q[2] = my; q[3] = 0.0f;
    Win* hit = HitTest(mainWin, (V2*)&q[1], V2(0.0f, 0.0f), &loc);
    IWin* hw = hit;
    if (cur == 0 || cur->vAccepts(hw)) {
        SetFocus(1, hw);
    } else {
        SetFocus(1, cur);
        loc = cur->vToLocal(V2(mx, my));
    }
    Win* f = f6b4;
    if (f6bc) {
        IWin* b = f6bc;
        loc = b->vToLocal(V2(mx, my));
    }
    if (!f6bc && f && flag) {
        IWin* par = f->parent;
        if (par && (f->flags & 4))
            par->vSetOwner(f);
        SetFocus(0, f);
    }
    if (out) {
        out->x = loc.x;
        out->y = loc.y;
    }
    return f;
}
