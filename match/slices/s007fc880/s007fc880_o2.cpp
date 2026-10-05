// slice s007fc880 — /O2 module: UTFWin cSPUIBehaviorTimeFunction* classes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <cstddef>
#include <math.h>

// ---------------------------------------------------------------------------
// Layout-matched stubs for the cSPUIBehaviorTimeFunction hierarchy.
// The original derives from cISPUIBehaviorTimeFunction (vptr at +0) and
// EA::RefCountVTemplate<int> (vptr at +4, count at +8).
// Relocations are masked when comparing, so only the vtable slot *indices*
// matter, not the exact vtable contents.
// ---------------------------------------------------------------------------
struct PrimBase {
    virtual void  v00();
    virtual void  v01();
    virtual void  v02();
    virtual void  v03();
    virtual void  v04();
    virtual void  v05();
    virtual void  v06();
    virtual void  v07();
    virtual void  v08();
    virtual void  v09();      // +0x24
    virtual void  v10();
    virtual void  v11();
    virtual void  v12(bool);  // +0x30
    virtual void  v13();
    virtual bool  v14();      // +0x38
    virtual bool  v15();      // +0x3c
    virtual void  v16();
    virtual void  v17();
    virtual void  v18();
    virtual void  v19();
    virtual void  v20();
    virtual void  v21();
    virtual float v22(float); // +0x58
    virtual void  v23();
    virtual bool  v24();      // +0x60
    virtual float v25(float); // +0x64
};

struct RefCountBase {
    virtual long AddRef();
    virtual long Release();
    virtual long GetRefCount();
    int mRefCount;            // +0x08
};

struct cSPUIBehaviorTimeFunction : PrimBase, RefCountBase {
    float mParamDuration;         // +0x0c
    float mParamFrequency;        // +0x10
    float mParamDamping;          // +0x14
    float mParamEaseInTimeFactor; // +0x18
    float mParamEaseOutTimeFactor;// +0x1c
    float mParamPreDelayFactor;   // +0x20
    float mParamPostDelayFactor;  // +0x24
    float mParamUser1;            // +0x28
    float mParamUser2;            // +0x2c
    float mParamUser3;            // +0x30
    float mParamUser4;            // +0x34
    bool  mbExpired;              // +0x38
    bool  mbNegated;              // +0x39
    bool  mbDirty;                // +0x3a
    float mTime;                  // +0x3c
    float mWorkTimeFrom;          // +0x40
    float mWorkTimeTo;            // +0x44

    float Ease(float t);          // @ 0x007fae90 (non-virtual)
    void  SetParams(float duration, float pre, float post);
    cSPUIBehaviorTimeFunction();
    // base virtuals referenced out of line
    virtual void  v12(bool);
    virtual bool  v15();
    virtual bool  v24();
    virtual float v22(float);
};

struct cSPUIBehaviorTimeFunctionRamp : cSPUIBehaviorTimeFunction {
    cSPUIBehaviorTimeFunctionRamp();
    virtual float v22(float t);   // @ 0x007fd4e0
    virtual bool  v24();          // @ 0x007fd540
    void SetParams(float duration, float pre, float post); // @ 0x007fd4a0
};

struct cSPUIBehaviorTimeFunctionSmoothRamp : cSPUIBehaviorTimeFunctionRamp {
    cSPUIBehaviorTimeFunctionSmoothRamp(float a, float b);
    virtual float v22(float t);   // @ 0x007fd5c0
};

struct cSPUIBehaviorTimeFunctionDampedPeriodic : cSPUIBehaviorTimeFunction {
    bool  mbCeilingMode;          // +0x48
    bool  mbInitialized;          // +0x49
    char  pad4a[2];
    unsigned int mPeriodicType;   // +0x4c

    cSPUIBehaviorTimeFunctionDampedPeriodic(bool ceiling);
    void  SetParams(float duration, float pre, float post, float freq, float damping, int periodicType);
    virtual void  v12(bool param);          // @ 0x007fd6b0
    virtual bool  v15();                    // @ 0x007fd700
    virtual float v22(float t);             // @ 0x007fd790
};

// @ 0x007fd460
cSPUIBehaviorTimeFunctionRamp::cSPUIBehaviorTimeFunctionRamp() {
    mParamDuration = 1.0f;
}

// @ 0x007fd4a0
void cSPUIBehaviorTimeFunctionRamp::SetParams(float duration, float pre, float post) {
    v09();
    mParamPreDelayFactor = pre;
    mParamPostDelayFactor = post;
    mParamDuration = duration;
    v24();
}

// @ 0x007fd4e0
float cSPUIBehaviorTimeFunctionRamp::v22(float t) {
    float r = 0.0f;
    if (mWorkTimeFrom <= t) {
        if (mTime <= mWorkTimeTo)
            r = (t - mWorkTimeFrom) / (mWorkTimeTo - mWorkTimeFrom);
        else
            r = 1.0f;
    }
    return r;
}

// @ 0x007fd540
bool cSPUIBehaviorTimeFunctionRamp::v24() {
    if (mParamDuration >= 0.0f && mParamDuration < 1.52587890625e-05f)
        mParamDuration = 1.52587890625e-05f;
    return cSPUIBehaviorTimeFunction::v24();
}

// @ 0x007fd570
cSPUIBehaviorTimeFunctionSmoothRamp::cSPUIBehaviorTimeFunctionSmoothRamp(float a, float b) {
    mParamDuration = 1.0f;
    mParamEaseInTimeFactor = a;
    mParamEaseOutTimeFactor = b;
}

// @ 0x007fd5c0
float cSPUIBehaviorTimeFunctionSmoothRamp::v22(float t) {
    float u = 0.0f;
    if (mWorkTimeFrom <= t) {
        if (mTime <= mWorkTimeTo)
            u = (t - mWorkTimeFrom) / (mWorkTimeTo - mWorkTimeFrom);
        else
            u = 1.0f;
    }
    return Ease(u);
}

// @ 0x007fd610
cSPUIBehaviorTimeFunctionDampedPeriodic::cSPUIBehaviorTimeFunctionDampedPeriodic(bool ceiling) {
    mbCeilingMode = ceiling;
    mbInitialized = false;
    mPeriodicType = 1;
}

// @ 0x007fd650
void cSPUIBehaviorTimeFunctionDampedPeriodic::SetParams(float duration, float pre, float post,
                                                        float freq, float damping, int periodicType) {
    if (periodicType != -1)
        mPeriodicType = periodicType;
    v09();
    mParamPreDelayFactor = pre;
    mParamPostDelayFactor = post;
    mParamFrequency = freq;
    mParamDamping = damping;
    mParamDuration = duration;
    v24();
    mbInitialized = true;
}

// @ 0x007fd6b0
void cSPUIBehaviorTimeFunctionDampedPeriodic::v12(bool param) {
    if (mParamDamping > 0.0f || v14()) {
        cSPUIBehaviorTimeFunction::v12(param);
        v09();
    }
}

// @ 0x007fd700
bool cSPUIBehaviorTimeFunctionDampedPeriodic::v15() {
    if (mParamDamping < 0.0f)
        return cSPUIBehaviorTimeFunction::v15();
    float t = mTime;
    float wf = mWorkTimeFrom;
    if (wf < t) {
        float e = expf(-(t - wf) * mParamDamping);
        if (e < 0.001f) {
            return mTime > mParamDuration;
        }
    }
    return false;
}

// @ 0x007fd790
float cSPUIBehaviorTimeFunctionDampedPeriodic::v22(float t) {
    float f5 = 1.0f;
    float f1 = 0.0f;
    float orig = t;
    t = t - mWorkTimeFrom;
    if (t > 0.0f) {
        if (mParamDamping > 0.0f) {
            f1 = mParamDamping;
            f5 = expf(-(f1 * t));
        } else if (mParamDamping < 0.0f && orig > mWorkTimeTo) {
            t = mWorkTimeTo - mWorkTimeFrom;
        }
        float v = v25(t);
        return 1.0f - v * f5;
    }
    return f1;
}
