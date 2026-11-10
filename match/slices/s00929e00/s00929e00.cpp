// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <intrin.h>

struct IRefCount {
    virtual void AddRef() = 0;
    virtual void Release() = 0;
};

struct Callback;
typedef void (__cdecl* CallbackFn)(void* ctx, int time, int delta);
void CallbackCancel(Callback* cb); // 0x00929d10

struct Callback {
    int mProc;            // +0x04
    int mTimeType;        // +0x08
    int mPeriod;          // +0x0c
    int mJitter;          // +0x10
    CallbackFn mpFn;      // +0x14
    void* mpCtx;          // +0x18
    IRefCount* mpObj;     // +0x1c
    bool mbActive;        // +0x20

    virtual ~Callback();

    // The barrier keeps the mpObj reload after the function-pointer stores.
    void SetObj(IRefCount* obj)
    {
        _ReadWriteBarrier();
        IRefCount* old = mpObj;
        if (obj != old) {
            if (obj)
                obj->AddRef();
            mpObj = obj;
            if (old)
                old->Release();
        }
    }

    void Set(CallbackFn fn, void* ctx, IRefCount* obj)
    {
        if (fn == 0) {
            mpFn = (CallbackFn)CallbackCancel;
            mpCtx = this;
        } else {
            mpFn = fn;
            mpCtx = ctx;
        }
        SetObj(obj);
    }

    Callback();
};

Callback::~Callback() {}

// @ 0x00929e00
Callback::Callback()
    : mProc(2), mTimeType(0), mPeriod(1000), mJitter(500), mpObj(0), mbActive(false)
{
    Set(0, 0, 0);
}
