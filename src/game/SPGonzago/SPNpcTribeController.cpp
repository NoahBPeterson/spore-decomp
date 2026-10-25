// src/game/SPGonzago/SPNpcTribeController.cpp -- migrated from slice(s) s0135d100, s00cc4fa0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPNpcTribeController.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00cc4fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cIRefCounted
{
public:
    virtual int AddRef();                 // +0x00
    virtual int Release();                // +0x04
};
class cFeedbackEvent : public cIRefCounted
{
public:
    virtual void e08();                   // +0x08
    virtual uint32_t GetResourceID(uint32_t nHash);   // +0x0c
    virtual void e10();                   // +0x10
    virtual void e14();                   // +0x14
    virtual void e18();                   // +0x18
    virtual void Activate(void* pArg);    // +0x1c
    virtual void e20();                   // +0x20
    virtual void e24();                   // +0x24
    virtual void e28();                   // +0x28
    virtual bool IsDone();                // +0x2c

    uint8_t  mPad04[0x131];               // +0x04
    uint8_t  mbField135;                  // +0x135
};
struct cTimeValue
{
    uint32_t mLow;                        // +0x00
    uint32_t mHigh;                       // +0x04
};
class cSPTimer
{
public:
    virtual void st00();                  // +0x00
    virtual void st04();                  // +0x04
    uint32_t mRefCount;                   // +0x04
    cTimeValue mElapsedTime;              // +0x08
    cTimeValue mBaseTime;                 // +0x10
    uint8_t  mRunning;                    // +0x18
    uint8_t  mPad19[3];                   // +0x19
    void*    mpfnGetMillisecondTime;      // +0x1c

    cSPTimer();                                          // 0x00bc31c0
    ~cSPTimer();                                         // 0x005725a0
    cSPTimer(const cSPTimer& x)
    {
        mRefCount = 0;
        mElapsedTime = x.mElapsedTime;
        mBaseTime = x.mBaseTime;
        mRunning = x.mRunning;
        mpfnGetMillisecondTime = x.mpfnGetMillisecondTime;
    }
    int64_t GetElapsedTime();                            // 0x00bc3190
};
class cGonzagoTimer : public cSPTimer
{
public:
    cGonzagoTimer();                                     // 0x00b63890
    cGonzagoTimer(const cGonzagoTimer& x) : cSPTimer(x) {}
    ~cGonzagoTimer();                                    // 0x00b638b0
    void Destroy();                                      // 0x00b638b0
    void AddTime(int nDelta);                            // 0x00b638c0
    void Write(void* pSerializer);                       // 0x00b638d0
    void Read(void* pSerializer);                        // 0x00b63930
};
class cKeyRef
{
public:
    cIRefCounted* mpRef;                  // +0x00
    cKeyRef() : mpRef(0) {}
    cKeyRef(cIRefCounted* p) : mpRef(p) { if (mpRef) mpRef->AddRef(); }
    cKeyRef(const cKeyRef& x) : mpRef(x.mpRef) { if (mpRef) mpRef->AddRef(); }
};
struct cEventTimerValue
{
    cKeyRef       mKey;                   // +0x00
    uint32_t      mPad04;                 // +0x04
    cGonzagoTimer mTimer;                 // +0x08

    cEventTimerValue(const cEventTimerValue& x);
    cEventTimerValue(cIRefCounted** ppKey, const cGonzagoTimer& timer);
    cEventTimerValue& operator=(const cEventTimerValue& x)
    {
        mKey = x.mKey;
        mTimer = x.mTimer;
        return *this;
    }

    cFeedbackEvent* Event() { return (cFeedbackEvent*)mKey.mpRef; }
};
// ---- items of slice s00cc4fa0 end

// ---- items of slice s0135d100 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void fn_00692ca0();
extern "C" void fn_00ae3470();
extern "C" void fn_00ae3490();
extern "C" void fn_00ae3310();
extern "C" void fn_00ac8050();
extern "C" void fn_00572810();
extern "C" void fn_00572840();
extern "C" void fn_00693090();
extern "C" void fn_00694f00();
extern "C" void fn_00b1fbf0();
extern "C" void fn_00675ca0();
extern "C" void fn_00cc5d40();
extern "C" void fn_00cc54f0();
extern "C" void fn_00c2e4e0();
extern "C" void fn_00692fb0();
extern "C" void fn_00cc5010();
extern "C" void fn_00d022e0();
extern "C" void fn_00c95780();
extern "C" void fn_00c6adc0();
extern "C" void fn_00c6c4e0();
typedef void (__cdecl *fp)();
struct T {
    const char* name;
    unsigned hash;
    int off;
    int p3, p4, p5;
    int z0, z1;
    fp f[7];
    T() {}
    T(const char* n, unsigned h, int o, fp f0, fp f1, fp f2, fp f3,
      fp f4, fp f5, fp f6)
        : name(n), hash(h), z0(0), z1(0) {
        f[0] = f0; f[1] = f1; f[2] = f2; f[3] = f3;
        f[4] = f4; f[5] = f5; f[6] = f6;
        off = o;
    }
};
extern T g_0157ea38, g_0157ea74, g_0157eab0, g_0157eaec, g_0157eb28;
// ---- items of slice s0135d100 end

// @ 0x00cc53e0
cEventTimerValue::cEventTimerValue(cIRefCounted** ppKey, const cGonzagoTimer& timer)
: mKey(*ppKey), mTimer(timer)
{
}

// @ 0x0135d100
void FUN_0135d100()
{
    g_0157ea38 = T("mPostTutorialDelayTimer_Mating", 0x5ee5e11u, 0x10, fn_00692ca0, fn_00ae3470, fn_00ae3490, fn_00c2e4e0, fn_00692fb0, fn_00ae3310, fn_00ac8050);
    g_0157ea74 = T("mPostTutorialDelayTimer_Food", 0x66a2038u, 0x30, fn_00692ca0, fn_00ae3470, fn_00ae3490, fn_00c2e4e0, fn_00692fb0, fn_00ae3310, fn_00ac8050);
    g_0157eab0 = T("mTribeAppearanceProperty", 0x629a22du, 0xfc, fn_00692ca0, fn_00572810, fn_00572840, fn_00693090, fn_00694f00, fn_00b1fbf0, fn_00675ca0);
    g_0157eaec = T("mBabyGrowthTimers", 0x57a481eu, 0x60, fn_00692ca0, fn_00cc5d40, fn_00cc54f0, fn_00c2e4e0, fn_00692fb0, fn_00cc5010, fn_00d022e0);
    g_0157eb28 = T("mNPCTribeSpeciesKeys", 0x600dd49u, 0x7c, fn_00692ca0, fn_00c95780, fn_00c6adc0, fn_00c2e4e0, fn_00692fb0, fn_00b1fbf0, fn_00c6c4e0);
}
