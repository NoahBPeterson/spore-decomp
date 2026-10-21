// Slice s008d1b30: UTFSpore_Win32/InputMan.obj -- EA::Input.
#include <intrin.h>
//
//   008d1b30..008d1cb0  the EA tsi hash-class helpers (get_using_str_hashClass,
//                       put_hashClass, Delete_hashClass) and the string/uint16
//                       lookup pair they use
//   008d1cf0..008d1da0  ApplyThresholds (the per-control state/threshold update)
//                       and the DirectInput EnumDevices callback
//   008d1df0..008d2340  InputMan::Init / Shutdown, the InputMan config setter,
//                       the callback registration/fire helpers, the device
//                       enumeration helpers and GetControllerDeviceInfo
//   008d24e0            InputMan::UpdateControl
//
// Class layouts are the dev-PDB ones (tools/pdb_type.py EA::Input::InputMan /
// Controller), confirmed field by field against this slice's disassembly; the
// device/COM stub interfaces are the ones from
// match/slices/s008d2590/s008d2590.cpp (same object file).
//
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <string.h>

extern "C" {
__declspec(dllimport) void* __stdcall GetModuleHandleA(const char* name);
__declspec(dllimport) int __stdcall DirectInput8Create(void* hinst, unsigned version, const void* riid,
                                                       void** out, void* outer);
}

// tsi hash utilities' allocator hook: tsi_DeAllocMem(void* pool, void* p) (0x008d1440).
extern "C" void tsi_DeAllocMem(void* pool, void* p);

// StrIStrW(wchar_t* hay, wchar_t* needle) -- case-insensitive substring find (0x0092cc90).
extern "C" wchar_t* StrIStrW(wchar_t* hay, wchar_t* needle);

extern "C" void* MemsetT(void*, int, uint32_t);                   // 0x011e073e

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
    virtual long __stdcall AddRef();
    virtual unsigned long __stdcall Release();                                            // +0x08
    virtual long __stdcall CreateDevice(const void* guid, void** dev, void* outer);        // +0x0c
    virtual long __stdcall s4();
    virtual long __stdcall EnumDevices(unsigned type, void* cb, void* ctx, unsigned flags); // +0x14
    virtual long __stdcall s6();
    virtual long __stdcall s7();
    virtual long __stdcall s8();
    virtual long __stdcall s9();
    virtual long __stdcall s10();
    virtual long __stdcall s11();
    virtual long __stdcall s12();
    virtual long __stdcall s13();
    virtual long __stdcall s14();
    virtual long __stdcall s15();
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
    virtual long __stdcall GetCapabilities(void* caps);                   // +0x0c
    virtual long __stdcall s4();
    virtual long __stdcall s5();
    virtual long __stdcall s6();
    virtual long __stdcall Acquire();                                     // +0x1c
    virtual long __stdcall Unacquire();
    virtual long __stdcall GetDeviceState(unsigned long cb, void* data);  // +0x24
    virtual long __stdcall s10();
    virtual long __stdcall s11();
    virtual long __stdcall s12();
    virtual long __stdcall s13();
    virtual long __stdcall SetDataFormat(const void* fmt);                // +0x38
    virtual long __stdcall s15();
    virtual long __stdcall s16();
    virtual long __stdcall s17();
    virtual long __stdcall SetProperty(const void* guid, const void* hdr); // +0x2c
    virtual long __stdcall s19();
    virtual long __stdcall s20();
    virtual long __stdcall s21();
    virtual long __stdcall s22();
    virtual long __stdcall s23();
    virtual long __stdcall s24();
    virtual long __stdcall Poll();                                        // +0x64
};

// EA's tsi hash-class header.  The first 0x30 bytes are read straight off this
// slice's disassembly (get_using_str_hashClass / put_hashClass / Delete_hashClass).
struct TsiHashExtra {
    const char* mpName;       // +0x00
    unsigned short mValue;    // +0x04 (+2 pad)
};

struct TsiHashClass {
    void*    mpPool;          // +0x00  pool passed to tsi_DeAllocMem
    int      mnFreeSlot;      // +0x04  current/next open bucket
    int      mnUsedCount;     // +0x08  number of used buckets
    void*    mpfnHashStr;     // +0x0c
    int      mnReserved10;    // +0x10
    int      mnBuckets;       // +0x14  hash modulus (idiv divisor)
    void*    mpfnCompare;     // +0x18  (int(*)(void* ctx, const char* str, unsigned short key))
    void*    mpCompareArg;    // +0x1c  first argument of the compare callback
    unsigned short* mpTable;  // +0x20  [key,value] pairs
    TsiHashExtra* mpExtra;    // +0x24  optional side table
    int      mnReserved28;    // +0x28
    int      mnExtraCount;    // +0x2c
};

namespace EA { namespace Input {

class InputMan;

class Device { public:
    virtual ~Device() {}
    virtual bool GetDeviceState(unsigned long cb, void* data) { return false; }
    virtual void Unacquire() {}
    virtual void Acquire() {}
    virtual bool Poll() { return false; }
};

class Controller : public Device { public:
    InputMan* mpInputMan;               // +0x04
    unsigned mnIndex;                   // +0x08
    unsigned short mRepeatCount[24];    // +0x0c
    float mState[24];                   // +0x3c
    bool mbAvailable;                   // +0x9c
    unsigned mnLastEventTime;           // +0xa0
    bool mbXInputDevice;                // +0xa4
    unsigned mnXInputIndex;             // +0xa8
    IDirectInputDevice8W_* mpDIController; // +0xac
    int mAxisMapping[4];                // +0xb0

    void GetDeviceInfo(DeviceInfo* info);
    float GetControlValue(unsigned id, bool bBinary);
    bool GetControlButton(unsigned id, bool bPressed);
    bool GetControlStates(float* out, bool bBinary);
};

class Keyboard : public Device { public:
    InputMan* mpInputMan;               // +0x04
    unsigned mnIndex;                   // +0x08
    bool mbAvailable;                   // +0x0c
};

class Mouse : public Device { public:
    InputMan* mpInputMan;               // +0x04
    unsigned mnIndex;                   // +0x08
    bool mbAvailable;                   // +0x0c
    int mXMin, mYMin, mXMax, mYMax;     // +0x10
};

class InputMan { public:
    virtual ~InputMan();                                                  // +0x00
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void OnControllerAvailability(Controller* c, bool bAvailable); // +0x20

    void* mpDeviceChangeCallback;          // +0x04
    void* mpDeviceChangeCallbackContext;   // +0x08
    void* mpPollCompletionCallback;        // +0x0c
    void* mpPollCompletionCallbackContext; // +0x10
    void* mpEventCallback;                 // +0x14
    void* mpEventCallbackContext;          // +0x18
    unsigned mnEventCallbackDeviceTypeMask;// +0x1c
    bool mbInitialized;                    // +0x20
    float mfNoiseThreshold;                // +0x24
    float mfBinaryThreshold;               // +0x28
    float mfAutomaticPollingRateMS;        // +0x2c
    int mnLogLevel;                        // +0x30
    Controller mController[4];             // +0x34
    Keyboard mKeyboard;                    // +0x334
    Mouse mMouse;                          // +0x344
    IDirectInput8W_* mpDI;                 // +0x364
    unsigned mnDIEnumCount;                // +0x368
    IDirectInputDevice8W_* mpDIEnumControllers[4]; // +0x36c

    InputMan();
    void GetControllerDeviceInfo(unsigned idx, DeviceInfo* info);          // 0x8d2330
    bool UpdateControl(Controller* c, int idx, float v, char bNormalized, unsigned dt); // 0x8d24e0
    void UpdateController(unsigned idx);
    void PollAll();
    bool Init();                                                           // 0x8d1df0
    bool Shutdown();                                                       // 0x8d20c0
    void SetConfig(int id, float v);                                       // 0x8d2110
    unsigned EnumDevices(void* out, unsigned count);                       // 0x8d21a0
    void* GetDeviceByType(int type, unsigned idx);                         // 0x8d2250
    void* SetDeviceChangeCallback(void* cb, int unused, void* ctx);        // 0x8d2290
    void FireDeviceChangeCallback(int a, int b);                           // 0x8d22b0
    void* SetPollCompletionCallback(void* cb, int unused, void* ctx);      // 0x8d22d0
    void* SetEventCallback(unsigned mask, void* cb, void* ctx);            // 0x8d22f0
    void FireEventCallback(void* p);                                       // 0x8d2310
};

}} // namespace

using namespace EA::Input;

// Globals of the EAInput library (real addresses from the disassembly).
extern unsigned long (__stdcall *g_XInputGetState)(unsigned long, void*);  // 0x1667a5c
extern bool g_bXInputInitialized;                                          // 0x1667a58

bool ApplyThresholds(float v, float noise, float bin, float* out, unsigned short* count, unsigned dt); // 0x8d1cf0
int get_using_uint16_hashClass(TsiHashClass* h, unsigned key, unsigned short* outValue);               // 0x8d1ac0
static inline bool NotNull(void* p) { return p != 0; }

// ---------------------------------------------------------------------------
// EA tsi hash-class helpers
// ---------------------------------------------------------------------------

// @ 0x008d1b30
int get_using_str_hashClass(TsiHashClass* h, const char* str, unsigned short* outValue)
{
    const char* p = str;
    int key = 0;
    while (*p) {
        key = (key * 0x100 + (signed char)*p) % h->mnBuckets;
        p++;
    }
    for (;;) {
        unsigned short* e = &h->mpTable[key * 2];
        if (e[0] == 0xffff && e[1] == 0xffff)
            break;
        int (__cdecl* cmp)(void*, const char*, unsigned short);
        cmp = (int (__cdecl*)(void*, const char*, unsigned short))h->mpfnCompare;
        if (cmp(h->mpCompareArg, str, e[0]) != 0) {
            h->mnFreeSlot = key;
            *outValue = h->mpTable[key * 2 + 1];
            return 1;
        }
        key = (key + 1) % h->mnBuckets;
    }
    h->mnFreeSlot = key;
    TsiHashExtra* ex = h->mpExtra;
    if (ex) {
        for (int i = 0; i < h->mnExtraCount; ++i) {
            if (strcmp(ex[i].mpName, str) == 0) {
                *outValue = ex[i].mValue;
                return 1;
            }
        }
    }
    *outValue = 0xffff;
    return 0;
}

// @ 0x008d1c50
void put_hashClass(TsiHashClass* h, unsigned key, unsigned short value, const char* str)
{
    unsigned short* table = h->mpTable;
    unsigned short found;
    int ok;
    if (str)
        ok = get_using_str_hashClass(h, str, &found);
    else
        ok = get_using_uint16_hashClass(h, key, &found);
    if (ok) {
        table[h->mnFreeSlot * 2 + 1] = value;
        return;
    }
    table[h->mnFreeSlot * 2] = (unsigned short)key;
    table[h->mnFreeSlot * 2 + 1] = value;
    h->mnUsedCount++;
}

// @ 0x008d1cb0
void Delete_hashClass(TsiHashClass* h)
{
    if (!h)
        return;
    if (h->mpExtra)
        tsi_DeAllocMem(h->mpPool, h->mpExtra);
    tsi_DeAllocMem(h->mpPool, h->mpTable);
    tsi_DeAllocMem(h->mpPool, h);
}

// ---------------------------------------------------------------------------
// State / threshold helpers
// ---------------------------------------------------------------------------

// @ 0x008d1cf0
bool ApplyThresholds(float v, float noise, float bin, float* out, unsigned short* count, unsigned dt)
{
    bool found = false;
    float a = fabsf(v);
    if (noise > a)
        v = 0.0f;
    else
        v = (v < -1.0f) ? -1.0f : ((v > 1.0f) ? 1.0f : v);
    *out = v;
    if (bin > a) {
        unsigned short cnt = *count;
        if (cnt == 0 || cnt == 0xffff)
            cnt = 0;
        else
            cnt = 0xffff;
        *count = cnt;
        return found;
    }
    if (dt > 200 && *count < 0xfffd) {
        *count = *count + 1;
        found = true;
    }
    return found;
}

// @ 0x008d1da0
bool __stdcall EnumDeviceCallback(void* instanceGuid, void* userData)
{
    InputMan* man = (InputMan*)userData;
    if (instanceGuid && man->mnDIEnumCount < 4) {
        int r = man->mpDI->CreateDevice((char*)instanceGuid + 4,
                                        (void**)&man->mpDIEnumControllers[man->mnDIEnumCount], 0);
        if (r >= 0)
            man->mnDIEnumCount++;
    }
    return man->mnDIEnumCount < 4;
}

// @ 0x008d1df0
bool InputMan::Init()
{
    if (mbInitialized)
        return true;

    mbInitialized = true;
    for (unsigned i = 0; i < 4; ++i) {
        mController[i].mpInputMan = this;
        mController[i].mnIndex = i;
        mController[i].mbXInputDevice = false;
    }
    mKeyboard.mpInputMan = this;
    mKeyboard.mnIndex = 0;
    mKeyboard.mbAvailable = true;
    mMouse.mpInputMan = this;
    mMouse.mnIndex = 0;
    mMouse.mbAvailable = true;

    bool bXInput = false;
    if (g_bXInputInitialized) {
        for (unsigned i = 0; i < 4; ++i) {
            char state[16];
            if (g_XInputGetState(i, state))
                continue;
            bXInput = true;
            break;
        }
    }
    mnDIEnumCount = 0;
    if (!bXInput) {
        void* hinst = GetModuleHandleA(0);
        if (DirectInput8Create(hinst, 0x800, (void*)0x14f8f44, (void**)&mpDI, 0) < 0)
            goto done;
        if (mpDI->EnumDevices(4, (void*)0x8d1da0, this, 1) < 0)
            goto done;
        if (mnDIEnumCount == 0)
            goto done;

        {
            Controller* c = &mController[0];
            IDirectInputDevice8W_** src = &mpDIEnumControllers[0];
            for (unsigned i = 0; i < mnDIEnumCount; ++i, ++c, ++src) {
                c->mpDIController = *src;
                c->mpDIController->SetProperty((void*)0x14f8e9c, 0);
                if (c->mpDIController->Acquire() >= 0)
                    c->mbAvailable = true;
                unsigned char fmt[0x240];
                c->mpDIController->SetDataFormat(fmt);
                c->mAxisMapping[0] = 0;
                c->mAxisMapping[1] = 1;
                c->mAxisMapping[2] = 3;
                c->mAxisMapping[3] = 4;
                unsigned char state[0x23c];
                if (c->mpDIController->GetDeviceState(0xc, state) < 0 ||
                    c->mpDIController->GetDeviceState(0x10, state) < 0) {
                    if (c->mpDIController->GetDeviceState(8, state) < 0 ||
                        c->mpDIController->GetDeviceState(0x14, state) < 0) {
                        if (c->mpDIController->GetDeviceState(8, state) >= 0 &&
                            c->mpDIController->GetDeviceState(0x18, state) >= 0) {
                            c->mAxisMapping[2] = 6;
                            c->mAxisMapping[3] = 2;
                        }
                    } else {
                        c->mAxisMapping[2] = 2;
                        c->mAxisMapping[3] = 5;
                    }
                }
            }
        }
    }

done:
    if (mnDIEnumCount < 4) {
        Controller* c = &mController[mnDIEnumCount];
        unsigned i = mnDIEnumCount;
        do {
            c->mbXInputDevice = g_bXInputInitialized;
            c->mnXInputIndex = i - mnDIEnumCount;
            i++;
            c++;
        } while (i < 4);
    }
    OnControllerAvailability(&mController[0], mController[0].mbAvailable);
    OnControllerAvailability(&mController[1], mController[1].mbAvailable);
    for (unsigned i = 0; i < 4; ++i)
        OnControllerAvailability(&mController[i], mController[i].mbAvailable);
    return true;
}

// @ 0x008d20c0
bool InputMan::Shutdown()
{
    if (!mbInitialized)
        return true;
    mbInitialized = false;
    mController[0].mpDIController = 0;
    mController[1].mpDIController = 0;
    mController[2].mpDIController = 0;
    mController[3].mpDIController = 0;
    _ReadWriteBarrier();
    IDirectInput8W_* di = mpDI;
    mnDIEnumCount = 0;
    if (di) {
        di->Release();
        mpDI = 0;
    }
    return true;
}

// @ 0x008d2110
void InputMan::SetConfig(int id, float v)
{
    switch (id) {
    case 1:
        if (v < 0.0f) v = 0.0f;
        else if (v > 1.0f) v = 1.0f;
        mfNoiseThreshold = v;
        return;
    case 2:
        if (v < 0.0f) v = 0.0f;
        else if (v > 1.0f) v = 1.0f;
        mfBinaryThreshold = v;
        return;
    case 3:
        mfAutomaticPollingRateMS = v;
        return;
    case 4:
        mnLogLevel = (int)v;
        return;
    }
}

// @ 0x008d21a0
unsigned InputMan::EnumDevices(void* out, unsigned count)
{
    unsigned i = 0;
    char* dst = (char*)out;
    Controller* c = &mController[0];
    for (int k = 0; k < 4; ++k) {
        if (i < count) {
            if (NotNull(out)) {
                (*(void (__thiscall**)(void*, void*))((char*)*(void**)c + 4))(c, dst + i * 0x8c);
            }
            i++;
        }
        c++;
    }
    if (i < count) {
        if (NotNull(out)) {
            (*(void (__thiscall**)(void*, void*))((char*)*(void**)&mKeyboard + 4))(&mKeyboard, dst + i * 0x8c);
        }
        i++;
        if (i < count) {
            if (NotNull(out)) {
                (*(void (__thiscall**)(void*, void*))((char*)*(void**)&mMouse + 4))(&mMouse, dst + i * 0x8c);
            }
            i++;
        }
    }
    return i;
}

// @ 0x008d2250
void* InputMan::GetDeviceByType(int type, unsigned idx)
{
    void* r = 0;
    switch (type) {
    case 1:
        if (idx < 4)
            r = &mController[idx];
        break;
    case 2:
        r = &mMouse;
        break;
    case 4:
        r = &mKeyboard;
        break;
    }
    return r;
}

// @ 0x008d2290
void* InputMan::SetDeviceChangeCallback(void* cb, int unused, void* ctx)
{
    void* old = mpDeviceChangeCallback;
    mpDeviceChangeCallback = cb;
    mpDeviceChangeCallbackContext = ctx;
    return old;
}

// @ 0x008d22b0
void InputMan::FireDeviceChangeCallback(int a, int b)
{
    if (mpDeviceChangeCallback)
        ((void (__cdecl*)(int, int, void*))mpDeviceChangeCallback)(
            a, b, mpDeviceChangeCallbackContext);
}

// @ 0x008d22d0
void* InputMan::SetPollCompletionCallback(void* cb, int unused, void* ctx)
{
    void* old = mpPollCompletionCallback;
    mpPollCompletionCallback = cb;
    mpPollCompletionCallbackContext = ctx;
    return old;
}

// @ 0x008d22f0
void* InputMan::SetEventCallback(unsigned mask, void* cb, void* ctx)
{
    void* old = mpEventCallback;
    mpEventCallback = cb;
    mpEventCallbackContext = ctx;
    mnEventCallbackDeviceTypeMask = mask;
    return old;
}

// @ 0x008d2310
void InputMan::FireEventCallback(void* p)
{
    if (mpEventCallback)
        ((void (__cdecl*)(void*, void*))mpEventCallback)(p, mpEventCallbackContext);
}

// @ 0x008d2330
void InputMan::GetControllerDeviceInfo(unsigned idx, DeviceInfo* info)
{
    info->type = 1;
    info->unused = 6;
    info->index = idx;
    wcscpy(info->name, L"Controller");
    Controller* c = &mController[idx];
    if (c->mbXInputDevice) {
        wcscpy(info->name, L"XInput Controller");
        info->unused = 3;
        return;
    }
    if (!c->mpDIController)
        return;

    unsigned char caps[0x448];
    MemsetT(caps, 0, 0x448);
    *(unsigned*)(caps + 4) = 0x44c;
    if (c->mpDIController->GetCapabilities(caps) < 0)
        return;
    wcsncpy(info->name, *(wchar_t**)(caps + 0x40), 0x40);
    info->name[0x40 - 1] = 0;
    if (StrIStrW(info->name, L"xbox") && StrIStrW(info->name, L"360")) {
        wcscpy(info->name, L"XInput Controller");
        info->unused = 3;
        return;
    }
    unsigned char fmt[0x23c];
    MemsetT(fmt, 0, 0x23c);
    *(unsigned*)(fmt + 4) = 0x240;
    if (c->mpDIController->SetDataFormat(fmt) < 0 ||
        c->mpDIController->SetProperty((void*)0x0, (void*)0x10) < 0) {
        if (c->mpDIController->SetProperty((void*)0x0, (void*)0x8) < 0 ||
            c->mpDIController->SetProperty((void*)0x0, (void*)0x14) < 0)
            return;
    }
    info->unused = 1;
}

// @ 0x008d24e0
bool InputMan::UpdateControl(Controller* c, int idx, float v, char bNormalized, unsigned dt)
{
    if (!bNormalized)
        v = v * 3.0518e-05f - 1.0f;
    float av = fabsf(v);
    if (av < mfNoiseThreshold)
        v = 0.0f;
    c->mState[idx] = v;
    if (mfBinaryThreshold > av) {
        unsigned short cnt = c->mRepeatCount[idx];
        if (cnt != 0)
            cnt = (cnt == 0xffff) ? 0 : 0xffff;
        c->mRepeatCount[idx] = cnt;
        return false;
    }    if (dt > 200 && c->mRepeatCount[idx] < 0xfffd) {
        c->mRepeatCount[idx] = c->mRepeatCount[idx] + 1;
        return true;
    }
    return false;
}
