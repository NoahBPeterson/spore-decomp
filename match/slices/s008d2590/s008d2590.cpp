// Slice s008d2590: EA::Input (EAInput library) - InputMan controller polling (XInput / DirectInput),
// Controller / Keyboard / Mouse device queries and the InputMan constructor/destructor.
// Layouts follow the 2008 dev PDB (EA::Input::InputMan / Controller / Keyboard / Mouse).
// Flags: /O2 /arch:SSE (scalar SSE for float stores, x87 for float args/returns).
#include "types.h"
#include <math.h>
#include <string.h>

extern "C" {
__declspec(dllimport) unsigned long __stdcall GetTickCount(void);
__declspec(dllimport) short __stdcall GetAsyncKeyState(int vKey);
__declspec(dllimport) short __stdcall GetKeyState(int nVirtKey);
__declspec(dllimport) int __stdcall GetKeyboardState(unsigned char* lpKeyState);
__declspec(dllimport) int __stdcall GetCursorPos(void* lpPoint);
__declspec(dllimport) int __stdcall SetCursorPos(int x, int y);
__declspec(dllimport) int __stdcall GetSystemMetrics(int nIndex);
__declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
__declspec(dllimport) void* __stdcall GetProcAddress(void* h, const char* name);
}

struct POINT_ { int x, y; };

struct DeviceInfo {
    int type;
    int unused;
    unsigned index;
    wchar_t name[32];
};

// COM interfaces (only the vtable slots used here).
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

// XInput entry points resolved at runtime by InitXInputFunctions.
extern unsigned long (__stdcall *g_XInputGetState)(unsigned long, XINPUT_STATE_*);        // 0x1667a5c
extern unsigned long (__stdcall *g_XInputSetState)(unsigned long, void*);                 // 0x1667a60
extern unsigned long (__stdcall *g_XInputGetCapabilities)(unsigned long, unsigned long, void*); // 0x1667a64
extern unsigned long (__stdcall *g_XInputGetDSoundAudioDeviceGuids)(unsigned long, void*, void*); // 0x1667a68
extern bool g_bXInputInitialized;                                                          // 0x1667a71

namespace EA { namespace Input {

struct InputMan;

struct Device {
    virtual ~Device() {}
};

struct Controller : Device {
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

struct Keyboard : Device {
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

struct Mouse : Device {
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

struct InputMan {
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

}} // namespace

using namespace EA::Input;

bool ApplyThresholds(float v, float noise, float bin, float* out, unsigned short* count, unsigned dt); // 0x8d1cf0

// @ 0x008d2590
void InputMan::UpdateController(unsigned idx)
{
    Controller* c = &mController[idx];
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
        c->mState[20] = (float)st.Gamepad.bLeftTrigger * (1.0f / 255.0f);
        c->mState[21] = (float)st.Gamepad.bRightTrigger * (1.0f / 255.0f);
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
void Controller::GetDeviceInfo(DeviceInfo* info)
{
    mpInputMan->GetControllerDeviceInfo(mnIndex, info);
}

// @ 0x008d2b80
float Controller::GetControlValue(unsigned id, bool bBinary)
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
bool Controller::GetControlButton(unsigned id, bool bPressed)
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
bool Controller::GetControlStates(float* out, bool bBinary)
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
void Keyboard::GetDeviceInfo(DeviceInfo* info)
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
bool Keyboard::GetKeyboardState(unsigned char* out)
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
void Keyboard::GetLocale(wchar_t* out)
{
    wcscpy(out, L"en-us");
}

// @ 0x008d2ea0
void Mouse::GetDeviceInfo(DeviceInfo* info)
{
    info->type = 2;
    info->unused = 0;
    info->index = mnIndex;
    wcscpy(info->name, L"Mouse");
}

// @ 0x008d2ee0
void Mouse::SetBounds(int xmin, int ymin, int xmax, int ymax)
{
    mXMin = xmin;
    mYMin = ymin;
    mXMax = xmax;
    mYMax = ymax;
}

// @ 0x008d2f00
void Mouse::GetBounds(int* xmin, int* ymin, int* xmax, int* ymax)
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
bool Mouse::SetPosition(int x, int y, bool bRelative)
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
bool Mouse::GetButtons(unsigned char* out)
{
    for (int i = 0; i < 5; ++i)
        out[i] = IsMouseButtonDown(1000 + i);
    return true;
}

// @ 0x008d3080
bool InitXInputFunctions()
{
    if (!g_bXInputInitialized) {
        g_bXInputInitialized = true;
        void* h = LoadLibraryA("xinput9_1_0.dll");
        if (!h)
            h = LoadLibraryA("xinput1_1.dll");
        if (!h)
            h = LoadLibraryA("xinput9_1_0.dll");
        if (h) {
            g_XInputGetState = (unsigned long (__stdcall *)(unsigned long, XINPUT_STATE_*))GetProcAddress(h, "XInputGetState");
            g_XInputSetState = (unsigned long (__stdcall *)(unsigned long, void*))GetProcAddress(h, "XInputSetState");
            g_XInputGetCapabilities = (unsigned long (__stdcall *)(unsigned long, unsigned long, void*))GetProcAddress(h, "XInputGetCapabilities");
            g_XInputGetDSoundAudioDeviceGuids = (unsigned long (__stdcall *)(unsigned long, void*, void*))GetProcAddress(h, "XInputGetDSoundAudioDeviceGuids");
        }
    }
    return g_XInputGetState != 0;
}

// @ 0x008d3130
InputMan::~InputMan()
{
    if (mbInitialized) {
        mbInitialized = false;
        for (int i = 0; i < 4; ++i)
            mController[i].mpDIController = 0;
        mnDIEnumCount = 0;
        if (mpDI) {
            mpDI->Release();
            mpDI = 0;
        }
    }
}

// @ 0x008d31b0
void InputMan::PollAll()
{
    for (unsigned i = 0; i < 4; ++i)
        UpdateController(i);
    if (mpPollCompletionCallback)
        mpPollCompletionCallback(this, mpPollCompletionCallbackContext);
}

// @ 0x008d3200
bool IsKeyDown(unsigned vk, unsigned modifiers)
{
    if (vk - 1000 <= 4)
        return IsMouseButtonDown(vk);
    switch (vk - 1) {
    case 0: case 1: case 3: case 4: case 5:
        break;
    default:
        if (modifiers == 0x3ff || (modifiers & 0x17) == GetModifierState())
            return ((unsigned)GetAsyncKeyState(vk) >> 15) & 1;
    }
    return false;
}

// @ 0x008d3270
bool Keyboard::IsToggleKeyOn(unsigned vk)
{
    if (vk == 0x14 || (vk > 0x8f && vk <= 0x91)) {
        bool r = GetKeyState(vk) & 1;
        return r;
    }
    return false;
}

// @ 0x008d32b0
bool Mouse::GetPosition(int* x, int* y)
{
    POINT_ p;
    GetCursorPos(&p);
    *x = p.x;
    *y = p.y;
    return true;
}

// @ 0x008d32e0
bool Mouse::IsButtonDown(unsigned code)
{
    return IsMouseButtonDown(code);
}

// @ 0x008d32f0
InputMan::InputMan()
    : mpDeviceChangeCallback(0)
    , mpDeviceChangeCallbackContext(0)
    , mpPollCompletionCallback(0)
    , mpPollCompletionCallbackContext(0)
    , mpEventCallback(0)
    , mpEventCallbackContext(0)
    , mnEventCallbackDeviceTypeMask(0)
    , mbInitialized(false)
    , mfNoiseThreshold(0.02f)
    , mfBinaryThreshold(0.5f)
    , mfAutomaticPollingRateMS(0.0f)
    , mnLogLevel(0)
    , mpDI(0)
    , mnDIEnumCount(0)
{
    mpDIEnumControllers[0] = 0;
    mpDIEnumControllers[1] = 0;
    mpDIEnumControllers[2] = 0;
    mpDIEnumControllers[3] = 0;
}

// @ 0x008d3450
bool Keyboard::IsKeyDown(unsigned vk, unsigned modifiers)
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

// @ 0x008d34d0
struct InputEvent {
    int a, b, c, d, e, f;
    char g, h;
    InputEvent();
    InputEvent(int d_, int e_, int f_, char g_, int c_, char h_);
};

InputEvent::InputEvent()
{
    b = 0;
    a = 0;
    c = 0;
    d = 0;
    e = 0;
    f = 0;
    g = 0;
    h = (char)0xfe;
}

// @ 0x008d34f0
InputEvent::InputEvent(int d_, int e_, int f_, char g_, int c_, char h_)
{
    c = c_;
    d = d_;
    e = e_;
    f = f_;
    b = 0;
    a = 0;
    g = g_;
    h = h_;
}

struct Binding {
    int f0, f4, f8, fc, f10;
    signed char c14, c15;
    unsigned short s16;
    int f18;
};

struct BindingTable {
    char pad[8];
    Binding b[32];
    unsigned count;

    Binding* FindBinding(int fc, int c14, int c15);
    Binding* FindBindingMasked(int f4, int c14, int c15, unsigned mask);
};

// @ 0x008d3530
Binding* BindingTable::FindBinding(int key, int c14, int c15)
{
    for (unsigned i = 0; i < count; ++i) {
        Binding* e = &b[i];
        if (e->fc == key && e->c14 == c14 && e->c15 == c15)
            return e;
    }
    return 0;
}

// @ 0x008d3580
Binding* BindingTable::FindBindingMasked(int key, int c14, int c15, unsigned mask)
{
    for (unsigned i = 0; i < count; ++i) {
        Binding* e = &b[i];
        if (e->f4 == key && e->c14 == c14 && e->c15 == c15 && (mask & e->s16))
            return e;
    }
    return 0;
}
