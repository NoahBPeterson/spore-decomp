// slice s00657ad0: SP::cSPUIAssetView/UI::AssetDiscovery_View helpers.
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

class cSPUILayout { public:
    void SetReloadCallback(void* fn, void* self);   // 0x00810090 (thiscall)
};
extern "C" void FUN_00657930(void*, int);           // 0x00657930
void FUN_00657e20(void* obj, int arg);              // 0x00657e20 (cdecl)

// ---------------------------------------------------------------------------
// Win32 / compiler intrinsics
// ---------------------------------------------------------------------------
union LARGE_INTEGER {
    struct { uint32_t LowPart; int32_t HighPart; } u;
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount); // 0x013cc2b8
extern "C" unsigned __int64 __cdecl __rdtsc(void);
#pragma intrinsic(__rdtsc)

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedIncrement(volatile long*);
extern "C" long __cdecl _InterlockedDecrement(volatile long*);
extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement, _ReadWriteBarrier)

// named allocator used by the UI object factory (no <new> on this toolchain path)
void* operator new(unsigned int size, const char* pName, int flags, unsigned debugFlags,
                   const char* pFile, int line);                    // 0x00f473a0

// ---------------------------------------------------------------------------
// SDK-ish types touched by this slice
// ---------------------------------------------------------------------------
// placement-free construction hooks (thiscall entry points of the real ctors)
struct EAStopwatchCtor {
    void Construct(int units, bool start);              // 0x0093a560
};
struct EALimitStopwatchOps {
    void SetTimeLimit(unsigned int limit, bool start);  // 0x0093a480
};
struct TextZoomNameCtor {
    void* Construct();                                  // 0x008345c0
};

// Reference count lives at +8 (EA::RefCounted layout); Release does not delete.
struct IntrusiveRefCounted {
    void* mpVtable;                 // +0x00
    uint32_t mField04;              // +0x04
    volatile long mnRefCount;       // +0x08
    void AddRef() { _InterlockedIncrement(&mnRefCount); }
    int Release() {
        _InterlockedDecrement(&mnRefCount);
        if (_InterlockedExchangeAdd(&mnRefCount, 0) < 1) {
            _InterlockedIncrement(&mnRefCount);
            return 1;
        }
        return _InterlockedExchangeAdd(&mnRefCount, 0);
    }
};

struct StopwatchLayout {            // EA::StdC::Stopwatch
    uint32_t mStartLow;             // +0x00
    uint32_t mStartHigh;            // +0x04
    uint32_t mTotalLow;             // +0x08
    uint32_t mTotalHigh;            // +0x0c
    int32_t  mUnits;                // +0x10
    float    mCoefficient;          // +0x14
};

struct Animator {
    char RemoveAnimation(void* target, int flag);   // 0x007f6210
    void AddAnimation(void* target);                // 0x007f8d10
};

struct AutoPtr {                    // intrusive pointer field (pointer at +0)
    void* mpObject;                 // +0x00
    void Assign(void* obj);         // 0x00572620
};

struct PropertyList;
struct AutoRefCountPropertyList {   // EA::AutoRefCount<PropertyList>
    AutoRefCountPropertyList() : mpObject(0) {}
    void* AsPPVoidParam(int, int, int, int);        // 0x0041d870
    PropertyList* mpObject;         // +0x00
};

struct Vec3 { float x, y, z; };

namespace UI {
class TextZoomName {
public:
    TextZoomName();                             // 0x008345c0
    char SetTargetWindow(void*, void*);         // 0x00834fa0
    char Activate(int);                         // 0x00834a00
};
}

// external callees (addresses are resolved from these annotations)
extern "C" void  __cdecl RecordEvent2(unsigned int, unsigned int);               // 0x00435ed0
extern "C" void  __cdecl RecordEvent4(unsigned int, unsigned int, float, int);   // 0x00435f40
extern "C" unsigned int __cdecl GetRecorderState();                              // 0x00435e90
extern "C" void* __cdecl GetSystemAT();                                          // 0x00a206f0
extern "C" void* __cdecl GetSetting3();                                          // 0x00401030
extern "C" void* __cdecl ObjectError();                                          // 0x008de1a0
extern "C" void* __cdecl WindowManager();                                        // 0x0067caa0
extern "C" void* __cdecl MessageServer();                                        // 0x0067dcc0
extern "C" char  __cdecl Contains(void*, void*);                                 // 0x00805150
extern "C" char  __cdecl IsModifierKeyDown(int);                                 // 0x008d2fb0
extern "C" void  __cdecl SetGlobalProperty(unsigned int, float);                 // 0x005ca880
extern "C" void  __cdecl GetPropertyAsUint32(void*, unsigned int, unsigned int*); // 0x004af210
extern "C" char  __cdecl GetPropertyT(void*, unsigned int, int*);                // 0x0040cf10
extern "C" void* __cdecl AudioSystem();                                          // 0x0067cb00
extern "C" float __cdecl GetElapsedSeconds(float, int, void*, int);              // 0x00805080
extern "C" void* __stdcall SPUICreateAnimationTimerInterpolation(void*, float);   // 0x007f7eb0
extern "C" void* __cdecl SPUICreateWindowAnimationTargetPosition(void*, void*, float, float, void*); // 0x007f7050
extern "C" void* __cdecl SPUICreateWindowAnimationTargetSize(void*, void*, float*, void*);           // 0x007f73e0
extern "C" void  __cdecl FUN_00657240(void*, unsigned int, void*);                // 0x00657240
extern "C" void  __cdecl FUN_006572b0(unsigned int);                              // 0x006572b0
extern "C" void  __cdecl FUN_006572f0(void*, unsigned int);                       // 0x006572f0
extern "C" void  __cdecl FUN_00ac9480(void*, void*);                              // 0x00ac9480

extern void* gVt13ffcd8;            // 0x13ffcd8
extern void* gVt13ffcc8;            // 0x13ffcc8
extern void* gVt13ec458;            // 0x13ec458
extern void* gVt13eb938;            // 0x13eb938
extern void* gVt13f6400;            // 0x13f6400
extern void* gVt13f63fc;            // 0x13f63fc
extern char  gDat016e3a19;          // 0x016e3a19

struct AssetView {
    void*    mpVtable;             // +0x00
    void*    mpVtable2;            // +0x04
    uint32_t mField08;             // +0x08
    uint32_t mField0c;             // +0x0c
    uint32_t mField10;             // +0x10
    uint8_t  mField14;             // +0x14
    uint8_t  mField15;             // +0x15
    uint8_t  mField16;             // +0x16
    uint8_t  mField17;             // +0x17
    uint32_t mField18;             // +0x18
    uint8_t  mField1c;             // +0x1c
    uint8_t  mPad1d[3];            // +0x1d
    void*    mpLayout20;           // +0x20
    void*    mpAsset24;            // +0x24
    void*    mpWindow28;           // +0x28
    void*    mpAnimTarget2c;       // +0x2c
    void*    mpField30;            // +0x30
    void*    mpField34;            // +0x34
    void*    mpField38;            // +0x38
    void*    mpField3c;            // +0x3c
    void*    mpField40;            // +0x40
    void*    mpField44;            // +0x44
    void*    mpField48;            // +0x48
    void*    mpField4c;            // +0x4c
    void*    mpField50;            // +0x50
    void*    mpField54;            // +0x54
    void*    mpField58;            // +0x58
    void*    mpField5c;            // +0x5c
    void*    mpField60;            // +0x60
    void*    mpField64;            // +0x64
    void*    mpField68;            // +0x68
    void*    mpField6c;            // +0x6c
    void*    mpField70;            // +0x70
    void*    mpField74;            // +0x74
    void*    mpField78;            // +0x78
    void*    mpField7c;            // +0x7c
    void*    mpField80;            // +0x80
    void*    mpField84;            // +0x84
    void*    mpField88;            // +0x88
    void*    mpField8c;            // +0x8c
    void*    mpField90;            // +0x90
    AutoPtr  mAutoPtr94;           // +0x94
    IntrusiveRefCounted* mpField98; // +0x98
    IntrusiveRefCounted* mpField9c; // +0x9c
    StopwatchLayout mStopwatchA0;  // +0xa0
    StopwatchLayout mStopwatchB8;  // +0xb8
    StopwatchLayout mLimitD0;      // +0xd0
    uint32_t mFieldE8;             // +0xe8
    uint32_t mFieldEc;             // +0xec
    uint8_t  mFieldF0;             // +0xf0
    uint8_t  mFieldF1;             // +0xf1
    uint8_t  mFieldF2;             // +0xf2
    uint8_t  mFieldF3;             // +0xf3
    uint8_t  mFieldF4;             // +0xf4
    uint8_t  mFieldF5;             // +0xf5
    uint8_t  mFieldF6;             // +0xf6
    uint8_t  mFieldF7;             // +0xf7
    float    mFieldF8;             // +0xf8
    uint8_t  mFieldFC;             // +0xfc
    uint8_t  mFieldFD;             // +0xfd
    uint8_t  mPadFE[2];            // +0xfe
    uint32_t mField100;            // +0x100

    AssetView();                                    // 0x00657f70
    void SetWindowArea(char animate);               // 0x00657ad0
    char KeyHandler(void* unused, void* ev);        // 0x00657bc0
    char IsReady();                                 // 0x00657dd0
    void OnDetach();                                // 0x00657e00
    void UpdateVerbIcon();                          // 0x00657e60
    void Destroy();                                 // 0x006580b0
    void SetRefs(void* p24, void* p90, char fc, char fd);  // 0x006582f0
    void Update();                                  // 0x00658440
    void SetFirstUpdate(int v);                     // 0x00657930
    void SelectAsset(int a, char b, int c, char d, char e); // 0x00657a30
};

// @ 0x00657ad0  SP::cSPUIAssetView::SetWindowArea(bool animate)
void AssetView::SetWindowArea(char animate) {
    char* s = (char*)this;
    if (!*(void**)(s + 0x4c) || !*(void**)(s + 0x50))
        return;
    {
        void* w = *(void**)(s + 0x4c);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, animate);
    }
    {
        void* w = *(void**)(s + 0x50);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x7c))(w, 1, animate);
    }
    FUN_00657930(this, s[0x15]);
    if (!*(void**)(s + 0x28) || !*(void**)(s + 0x24) || !s[0xfc])
        return;
    void* target = *(void**)(s + 0x24);
    float* r = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)target + 0x38))(target);
    float x0 = r[0], y0 = r[1], x1 = r[2], y1 = r[3];
    if (!animate) {
        void* src = *(void**)(s + 0x4c);
        float* r2 = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)src + 0x34))(src);
        y1 = (r2[3] - r2[1]) + y1;
    }
    void* dst = *(void**)(s + 0x28);
    (*(void(__thiscall**)(void*, float, float))((char*)*(void**)dst + 0x74))(dst, x1 - x0,
                                                                             y1 - y0);
}

// @ 0x00657bc0  SP::cSPUIAssetView key handler
char AssetView::KeyHandler(void* unused, void* ev) {
    (void)unused;
    if (!mFieldF5)
        return 0;
    switch (*(uint32_t*)((char*)ev + 8)) {
    case 6:
        if (*(int*)((char*)ev + 0x18) == 1000)
            (*(void(__thiscall**)(void*, void*))((char*)*(void**)this + 0x50))(this, ev);
        return 0;
    case 7:
        if (*(int*)((char*)ev + 0x18) == 1000)
            (*(void(__thiscall**)(void*, void*))((char*)*(void**)this + 0x54))(this, ev);
        return 0;
    case 9: {
        void* w = mpWindow28;
        void* mgr = WindowManager();
        void* r = (*(void*(__thiscall**)(void*, void*))((char*)*(void**)w + 0x10))(w, ev);
        (*(void(__thiscall**)(void*, void*, void*))((char*)*(void**)mgr + 0x18))(mgr, mpWindow28, r);
        return 0;
    }
    case 0x1b:
        if (*(int*)((char*)ev + 0xc) != 1)
            return 0;
        if (!mFieldF6) {
            char a = IsModifierKeyDown(1000);
            char b = IsModifierKeyDown(0x3ea);
            char c = IsModifierKeyDown(0x3e9);
            if (!a && !b && !c) {
                mFieldF6 = 1;
                (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x48))(this);
            }
        }
        if (*(void**)((char*)ev + 0x18) != mpWindow28) {
            void* o = *(void**)((char*)ev + 0x18);
            (*(void(__thiscall**)(void*, void*))((char*)*(void**)o + 0x104))(o, this);
        }
        return 0;
    case 0x1c:
        if (*(int*)((char*)ev + 0xc) != 1)
            return 0;
        if (mFieldF6) {
            void* mgr = WindowManager();
            void* r = (*(void*(__thiscall**)(void*, int))((char*)*(void**)mgr + 0x48))(mgr, 1);
            if (!Contains(mpWindow28, r)) {
                mFieldF6 = 0;
                (*(void(__thiscall**)(void*, int))((char*)*(void**)this + 0x4c))(this, 0);
            }
        }
        if (*(void**)((char*)ev + 0x18) != mpWindow28) {
            void* o = *(void**)((char*)ev + 0x18);
            (*(void(__thiscall**)(void*, void*))((char*)*(void**)o + 0x108))(o, this);
        }
        return 0;
    case 0x287259f6: {
        uint32_t id = *(uint32_t*)((char*)ev + 0xc);
        if (id == 0x53d6fe2a) {
            void* p = mpField90;
            if (p) {
                long long v = (*(long long(__thiscall**)(void*))((char*)*(void**)p + 0x54))(p);
                if (v != 0) {
                    void* ms = MessageServer();
                    (*(void(__thiscall**)(void*, unsigned int, long long*, int))
                        ((char*)*(void**)ms + 0x14))(ms, 0x6299932u, &v, 0);
                }
                return 1;
            }
        }
        if (id == 0x643e520) {
            SelectAsset(1, 1, 0, 0, 0);
            return 1;
        }
        return 0;
    }
    default:
        return 0;
    }
}

// @ 0x00657f70  UI::AssetDiscovery_View::AssetDiscovery_View
AssetView::AssetView() {
    *(void* volatile*)&mpVtable2 = (void*)&gVt13ec458;
    mField08 = 0;
    mpVtable = (void*)&gVt13ffcd8;
    mpVtable2 = (void*)&gVt13ffcc8;
    mField14 = 0;
    mField15 = 0;
    mField16 = 1;
    mField17 = 0;
    mField18 = 0;
    mField1c = 0;
    mpLayout20 = 0;
    mpAsset24 = 0;
    mpWindow28 = 0;
    mpAnimTarget2c = 0;
    mpField30 = 0;
    mpField34 = 0;
    mpField38 = 0;
    mpField3c = 0;
    mpField40 = 0;
    mpField44 = 0;
    mpField48 = 0;
    mpField4c = 0;
    mpField50 = 0;
    mpField54 = 0;
    mpField58 = 0;
    mpField5c = 0;
    mpField60 = 0;
    mpField64 = 0;
    mpField68 = 0;
    mpField6c = 0;
    mpField70 = 0;
    mpField74 = 0;
    mpField78 = 0;
    mpField7c = 0;
    mpField80 = 0;
    mpField84 = 0;
    mpField88 = 0;
    mpField8c = 0;
    mpField90 = 0;
    mAutoPtr94.mpObject = 0;
    mpField98 = 0;
    mpField9c = 0;
    {
        EAStopwatchCtor* swa = (EAStopwatchCtor*)&mStopwatchA0;
        EAStopwatchCtor* swb = (EAStopwatchCtor*)&mStopwatchB8;
        EAStopwatchCtor* swc = (EAStopwatchCtor*)&mLimitD0;
        swa->Construct(4, false);
        swb->Construct(4, false);
        swc->Construct(4, false);
        ((EALimitStopwatchOps*)swc)->SetTimeLimit(0, false);
    }
    mFieldF0 = 0;
    mFieldF1 = 0;
    mFieldF2 = 0;
    mFieldF3 = 0;
    mFieldF5 = 0;
    mFieldF6 = 0;
    mFieldF7 = 0;
    mField100 = 0;
    mFieldF4 = 1;
    mFieldF8 = 0.0f;
}

// @ 0x00657dd0  bool SP::cSPUIAssetView::IsAnimTargetReady()
char AssetView::IsReady() {
    char* s = (char*)this;
    void* p = *(void**)(s + 0x98);
    if (!p || !(*(unsigned char*)((char*)p + 4) & 1))
        return 0;
    void* q = *(void**)(s + 0x9c);
    if (!q || !(*(unsigned char*)((char*)q + 4) & 1))
        return 0;
    return 1;
}

// @ 0x00657e00  SP::cSPUIAssetView::OnDetach
void AssetView::OnDetach() {
    char* s = (char*)this;
    void* layout = *(void**)(s + 0x20);
    if (layout)
        ((cSPUILayout*)layout)->SetReloadCallback(0, 0);
    (*(void(__thiscall**)(void*))((char*)*(void**)s + 0x44))(s);
}

// @ 0x00657e20  select-slot helper (find child by id 0x0105a93d)
void FUN_00657e20(void* obj, int arg) {
    if (!obj)
        return;
    void* r = (*(void*(__thiscall**)(void*, int))((char*)*(void**)obj + 0xc))(obj, 0x105a93d);
    if (!r)
        return;
    (*(void(__thiscall**)(void*, int))((char*)*(void**)r + 0x14))(r, arg);
    (*(void(__thiscall**)(void*, int, int))((char*)*(void**)obj + 0x7c))(obj, 1, 1);
}

// @ 0x00657e60  SP::cSPUIAssetView::UpdateVerbIcon
void AssetView::UpdateVerbIcon() {
    char* s = (char*)this;
    void* p = *(void**)(s + 0x90);
    if (!p)
        return;
    int v = (*(int(__thiscall**)(void*))((char*)*(void**)p + 0x38))(p);
    if (v > 0x7fffffff)
        return;
    void* obj = *(void**)(s + 0x74);
    switch (v) {
    case -2: FUN_00657e20(obj, 6); return;
    case -1: return;
    case 0:  FUN_00657e20(obj, 0); return;
    case 1:  FUN_00657e20(obj, 1); return;
    case 2:  FUN_00657e20(obj, 5); return;
    case 3:  FUN_00657e20(obj, 2); return;
    case 4:  FUN_00657e20(obj, 3); return;
    case 5:  FUN_00657e20(obj, 4); return;
    default: return;
    }
}

// @ 0x006580b0  SP::cSPUIAssetView teardown
void AssetView::Destroy() {
    *(void* volatile*)&mpVtable = (void*)&gVt13ffcd8;
    *(void* volatile*)&mpVtable2 = (void*)&gVt13ffcc8;
    _ReadWriteBarrier();
    if (mpField9c) {
        IntrusiveRefCounted* p = mpField9c;
        p->Release();
    }
    if (mpField98) {
        IntrusiveRefCounted* p = mpField98;
        p->Release();
    }
    if (mAutoPtr94.mpObject) {
        void* p = mAutoPtr94.mpObject;
        (*(void(__thiscall**)(void*))((char*)*(void**)p + 8))(p);
    }
    if (mpField90) {
        void* sub = (char*)mpField90 + 0x10;
        (*(void(__thiscall**)(void*))((char*)*(void**)sub + 4))(sub);
    }
#define AV_RELEASE4(field)                                              \
    do {                                                                \
        void* p = (field);                                              \
        if (p)                                                          \
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);   \
    } while (0)
    AV_RELEASE4(mpField8c);
    AV_RELEASE4(mpField88);
    AV_RELEASE4(mpField84);
    AV_RELEASE4(mpField80);
    AV_RELEASE4(mpField7c);
    AV_RELEASE4(mpField78);
    AV_RELEASE4(mpField74);
    AV_RELEASE4(mpField70);
    AV_RELEASE4(mpField6c);
    AV_RELEASE4(mpField68);
    AV_RELEASE4(mpField64);
    AV_RELEASE4(mpField60);
    AV_RELEASE4(mpField5c);
    AV_RELEASE4(mpField58);
    AV_RELEASE4(mpField54);
    AV_RELEASE4(mpField50);
    AV_RELEASE4(mpField4c);
    AV_RELEASE4(mpField48);
    AV_RELEASE4(mpField44);
    AV_RELEASE4(mpField40);
    AV_RELEASE4(mpField3c);
    AV_RELEASE4(mpField38);
    AV_RELEASE4(mpField34);
    AV_RELEASE4(mpField30);
    AV_RELEASE4(mpAnimTarget2c);
    AV_RELEASE4(mpWindow28);
    AV_RELEASE4(mpAsset24);
#undef AV_RELEASE4
    if (mpLayout20)
        (*(void(__thiscall**)(void*))((char*)*(void**)mpLayout20 + 8))(mpLayout20);
    *(void* volatile*)&mpVtable = (void*)&gVt13eb938;
    *(void* volatile*)&mpVtable2 = (void*)&gVt13ec458;
}

// @ 0x006582f0  SP::cSPUIAssetView::SetRefs(asset24, field90, fc, fd)
void AssetView::SetRefs(void* p24, void* p90, char fc, char fd) {
    void* old90 = mpField90;
    if (p90 != old90) {
        if (p90) {
            void* sub = (char*)p90 + 0x10;
            (*(void(__thiscall**)(void*))((char*)*(void**)sub + 0))(sub);
        }
        mpField90 = p90;
        if (old90) {
            void* sub = (char*)old90 + 0x10;
            (*(void(__thiscall**)(void*))((char*)*(void**)sub + 4))(sub);
        }
    }
    void* old24 = mpAsset24;
    if (p24 != old24) {
        if (p24)
            (*(void(__thiscall**)(void*))((char*)*(void**)p24 + 0))(p24);
        mpAsset24 = p24;
        if (old24)
            (*(void(__thiscall**)(void*))((char*)*(void**)old24 + 4))(old24);
    }
    mFieldFC = fc;
    mFieldFD = fd;
    if (mpField98) {
        IntrusiveRefCounted* p = mpField98;
        mpField98 = 0;
        p->Release();
    }
    if (mpField9c) {
        IntrusiveRefCounted* p = mpField9c;
        mpField9c = 0;
        p->Release();
    }
    {
        uint32_t lo;
        if (mStopwatchA0.mUnits == 1) {
            unsigned __int64 c = __rdtsc();
            lo = (uint32_t)c;
            mStopwatchA0.mStartHigh = (uint32_t)(c >> 32);
        } else {
            LARGE_INTEGER li;
            QueryPerformanceCounter(&li);
            lo = li.u.LowPart;
            mStopwatchA0.mStartHigh = (uint32_t)li.u.HighPart;
        }
        mStopwatchA0.mStartLow = lo;
    }
    mStopwatchA0.mTotalLow = 0;
    mStopwatchA0.mTotalHigh = 0;
    if (mAutoPtr94.mpObject) {
        void* p = mAutoPtr94.mpObject;
        mAutoPtr94.mpObject = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)p + 8))(p);
    }
}

// @ 0x00658440  SP::cSPUIAssetView::Update
void AssetView::Update() {
    if (!mpWindow28)
        return;
    if (!mFieldF4)
        return;
    {
        void* sys = GetSystemAT();
        uint32_t v = 0;
        if (sys)
            v = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)sys + 0x20))(sys);
        RecordEvent2(0x3e623019u, v);
    }
    {
        void* inner = (*(void*(__thiscall**)(void*))((char*)*(void**)mpWindow28 + 0x10))(mpWindow28);
        (*(void(__thiscall**)(void*, void*))((char*)*(void**)inner + 0xe8))(inner, mpWindow28);
    }
    {
        void* settings = GetSetting3();
        void* animator = settings ? *(void**)((char*)settings + 0x14) : 0;
        if (animator) {
            float* r = (float*)(*(void*(__thiscall**)(void*))((char*)*(void**)mpWindow28 + 0x38))(mpWindow28);
            float w = r[2] - r[0];
            float h = r[3] - r[1];
            float dx = (w * 1.1f - w) * 0.5f;
            float dy = (h * 1.1f - h) * 0.5f;
            float left = -dx;
            float top = -dy;
            float right = w + dx;
            float bottom = h + dy;
            Animator* anim = (Animator*)animator;
            anim->RemoveAnimation(mpAnimTarget2c, 1);
            anim->RemoveAnimation(mpAnimTarget2c, 0);
            {
                uint32_t interpBuf[2];      // {vtable, object} return temp
                uint32_t posBuf[2];         // {vtable, object} return temp
                float elapsed = GetElapsedSeconds(0.1f, 2, mpAnimTarget2c, 1);
                void* interp = SPUICreateAnimationTimerInterpolation(interpBuf, elapsed);
                void* target = SPUICreateWindowAnimationTargetPosition(posBuf, mpAnimTarget2c,
                                                                       left, top, interp);
                anim->AddAnimation(target);
                if (posBuf[1])
                    (*(void(__thiscall**)(void*))((char*)*(void**)posBuf[1] + 4))((void*)posBuf[1]);
                if (interpBuf[1])
                    (*(void(__thiscall**)(void*))((char*)*(void**)interpBuf[1] + 4))((void*)interpBuf[1]);
            }
            {
                float size[2];
                size[0] = right - left;
                size[1] = bottom - top;
                uint32_t interpBuf2[2];
                uint32_t sizeBuf[2];
                float elapsed = GetElapsedSeconds(0.1f, 2, mpAnimTarget2c, 1);
                void* interp = SPUICreateAnimationTimerInterpolation(interpBuf2, elapsed);
                void* target = SPUICreateWindowAnimationTargetSize(sizeBuf, mpAnimTarget2c, size, interp);
                anim->AddAnimation(target);
                if (sizeBuf[1])
                    (*(void(__thiscall**)(void*))((char*)*(void**)sizeBuf[1] + 4))((void*)sizeBuf[1]);
                if (interpBuf2[1])
                    (*(void(__thiscall**)(void*))((char*)*(void**)interpBuf2[1] + 4))((void*)interpBuf2[1]);
            }
            {
                UI::TextZoomName* zoom = (UI::TextZoomName*)operator new(0x78, "UI/TextZoomName", 0, 0, 0, 0);
                if (zoom)
                    ((TextZoomNameCtor*)zoom)->Construct();
                mAutoPtr94.Assign(zoom);
            }
            void* p = mpField44;
            if (p)
                (*(void(__thiscall**)(void*))((char*)*(void**)p + 0))(p);
            if (mpField68) {
                unsigned char f = (*(unsigned char(__thiscall**)(void*))((char*)*(void**)mpField68 + 0x28))(mpField68);
                if (f & 1)
                    FUN_00ac9480(&mpField6c, &mpField6c);
            }
            {
                uint32_t h = p ? (*(uint32_t(__thiscall**)(void*, unsigned int))
                                  ((char*)*(void**)p + 0xc))(p, 0xf15f4bdu) : 0;
                Vec3 zero;
                zero.x = 0.0f; zero.y = 0.0f; zero.z = 0.0f;
                void* win = (*(void*(__thiscall**)(void*, int, int, Vec3))
                             ((char*)*(void**)mpWindow28 + 0x10))(mpWindow28, 0, 0, zero);
                UI::TextZoomName* zoom = (UI::TextZoomName*)mAutoPtr94.mpObject;
                if (zoom->SetTargetWindow((void*)h, win))
                    zoom->Activate(0);
                if (p)
                    (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
            }
        }
    }
    if (mpField38 && mFieldF2) {
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)mpField38 + 0x7c))(mpField38, 1, 1);
        SetFirstUpdate(mField15);
    }
    if (mpField90) {
        char f = (*(char(__thiscall**)(void*))((char*)*(void**)mpField90 + 0x64))(mpField90);
        if (f)
            (*(void(__thiscall**)(void*))((char*)*(void**)this + 0x2c))(this);
    }
    if (!mpField90)
        return;
    if (!GetSystemAT())
        return;
    {
        uint32_t* vec = (uint32_t*)(*(void*(__thiscall**)(void*))((char*)*(void**)mpField90 + 0x40))(mpField90);
        uint32_t v0 = vec[0];
        uint32_t v1 = vec[1];
        uint32_t v2 = vec[2];
        Vec3 vecCopy;
        vecCopy.x = *(float*)&v0;
        vecCopy.y = *(float*)&v1;
        vecCopy.z = *(float*)&v2;
        if (v1 != 0xb1b104)
            return;
        {
            AutoRefCountPropertyList props;
            uint8_t aux[12];
            void* dbg = ObjectError();
            (*(void(__thiscall**)(void*, uint8_t*, void*))((char*)*(void**)dbg + 0xc))
                (dbg, aux, props.AsPPVoidParam(0, 0, 0, 0));
            if (props.mpObject) {
                uint32_t handle = 0;
                GetPropertyAsUint32(props.mpObject, 0xb6878619u, &handle);
                if (handle) {
                    int fA = 0, fB = 0, fC = 0;
                    char ok = GetPropertyT(props.mpObject, 0x66ef9abau, &fA);
                    if (ok)
                        ok = GetPropertyT(props.mpObject, 0xe4dd1818u, &fB);
                    if (ok)
                        ok = GetPropertyT(props.mpObject, 0xcd928a9u, &fC);
                    SetGlobalProperty(0x8dff6314u, 1.0f);
                    mField100 = GetRecorderState();
                    void* audio = AudioSystem();
                    void* a1 = (*(void*(__thiscall**)(void*))((char*)*(void**)audio + 0x1c))(audio);
                    float* pos = (float*)(*(void*(__thiscall**)(void*, int))((char*)*(void**)a1 + 0x10))(a1, 0);
                    Vec3 p;
                    p.x = pos[0]; p.y = pos[1]; p.z = pos[2];
                    FUN_00657240((void*)handle, mField100, &p);
                    RecordEvent4(mField100, 0x12d2a4d4u, 0.0f, 0);
                    RecordEvent4(mField100, 0xba134192u, 0.0f, 0);
                    FUN_006572f0((void*)&gDat016e3a19, mField100);
                    if (ok) {
                        RecordEvent4(mField100, 0x66ef9abau, *(float*)&fA, 0);
                        RecordEvent4(mField100, 0xe4dd1818u, *(float*)&fB, 0);
                        RecordEvent4(mField100, 0xcd928a9u, *(float*)&fC, 0);
                    }
                    FUN_006572b0(mField100);
                }
                (*(void(__thiscall**)(void*))((char*)*(void**)props.mpObject + 4))(props.mpObject);
            }
        }
    }
}
