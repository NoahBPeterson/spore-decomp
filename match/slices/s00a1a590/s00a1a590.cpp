// Slice s00a1a590 (gold3 43) -- EA::Audio response curves / Sound / Envelope.
//
//   0xa1a590  EA::Audio::ResponseCurve::SetResponseCurveData
//   0xa1a9d0  EA::Audio::ResponseCurve::InitFromConfiguration
//   0xa1aa50  EA::Audio::ResponseCurve::ResponseCurve
//   0xa1aad0  FUN_00a1aad0
//   0xa1ac70  FUN_00a1ac70
//   0xa1acd0  FUN_00a1acd0
//   0xa1ad20  FUN_00a1ad20
//   0xa1ad40  FUN_00a1ad40
//   0xa1adc0  FUN_00a1adc0
//   0xa1ae00  EA::Audio::Sound::PausedIgnoring
//   0xa1ae20  FUN_00a1ae20
//   0xa1ae40  FUN_00a1ae40
//   0xa1ae50  FUN_00a1ae50
//   0xa1ae90  EA::Audio::Sound::RunningAttenuation
//   0xa1aef0  EA::Audio::Sound::RequestStop
//   0xa1af50  FUN_00a1af50
//   0xa1af80  EA::Audio::Sound::ShouldPauseForLowGain
//   0xa1afb0  EA::Audio::Sound::ComputeGainAttenuation
//   0xa1b020  FUN_00a1b020
//   0xa1b100  EA::Audio::Envelope::Update
//   0xa1b160  EA::Audio::ResourceInstrumentBank::FindZone
//   0xa1b1e0  FUN_00a1b1e0
//   0xa1b230  EA::Audio::Sound::Tick
//   0xa1b320  FUN_00a1b320
//   0xa1b390  FUN_00a1b390
//   0xa1b440  FUN_00a1b440
#include "types.h"

static __forceinline void** VtOf(void* p) { return *(void***)p; }

// =====================================================================================
// Foreign callees / globals.
// =====================================================================================
extern "C" void* __cdecl FUN_00f473a0(uint32_t size, const char* tag, int a, int b, const char* file, uint32_t line);
extern "C" void  __cdecl FUN_00f47380(void* p);          // operator delete
void  __cdecl FUN_00ab94c0(void* self, uint32_t cap);    // FloatVec::reserve
void  __cdecl FUN_00a1a1e0(void* vec, float* val);       // FloatVec::push_back
void  __cdecl FUN_00a1a2f0(void* vec, uint32_t idx, uint32_t n, const void* val);  // RcdVec::insertN
void  __cdecl FUN_00a1a500(void* vec, uint32_t n);       // RcdVec::resize
double __cdecl FUN_0092dc50(const char* s, float* out);  // eastl::atof
int   __cdecl isalnum(int c);                            // CRT import (via 0x13cc510 thunk)
void* __cdecl FUN_00a206f0(void);                        // EA::Audio::GetSystemAT
double __cdecl pow(double, double);                      // CRT

// =====================================================================================
// Types.
// =====================================================================================

// One point of a response curve, 0x14 bytes.
struct ResponseCurveData {
    float mfInputValue;          // +0x00
    float mfOutputValue;         // +0x04
    float mfPreviousInputValue;  // +0x08
    float mfPreviousOutputValue; // +0x0c
    float mfDeltaRatio;          // +0x10
};

// A float vector with an inline 0x100-byte pool (used by FUN_00a1aad0).
struct FloatVec {
    float* mpBegin;       // +0x00
    float* mpEnd;         // +0x04
    float* mpCapacity;    // +0x08
    float* mpPoolBegin;   // +0x0c
    char   mPool[0x100];  // +0x10
};

// EA::Audio::ResponseCurve: an inline fixed_vector<ResponseCurveData,42>.
struct ResponseCurve {
    ResponseCurveData* mpBegin;    // +0x00
    ResponseCurveData* mpEnd;      // +0x04
    ResponseCurveData* mpCapacity; // +0x08
    uint8_t            pad0c[4];
    ResponseCurveData* mpPoolBegin;// +0x10
    uint8_t            pad14[4];
    ResponseCurveData  mBuffer[42];// +0x18
    uint32_t           mCount;     // +0x360

    bool  SetResponseCurveData(const float* pts, int32_t n);
    bool  InitFromConfiguration(void* cfg, uint32_t key);
    ResponseCurve();
    uint8_t ParseString(char* str, char sep);
};

// ---- EA::Audio::Sound ------------------------------------------------------------------
// Opaque over its full extent; only the offsets touched by this slice are named, everything
// else is explicit padding.
struct Sound {
    uint8_t  pad000[0x3c];
    uint32_t mInstanceId;          // +0x03c
    uint8_t  pad040[0x08];
    float    mf48;                 // +0x048
    uint8_t  pad04c[0x04];
    float    mf50;                 // +0x050
    float    mf54;                 // +0x054
    float    mf58;                 // +0x058
    float    mf5c;                 // +0x05c
    uint8_t  pad060[0x0c];
    float    mf6c;                 // +0x06c
    uint8_t  pad070[0x28];
    float    mf98;                 // +0x098
    uint8_t  mb9c;                 // +0x09c  (stop flags)
    uint8_t  pad09d[3];
    uint8_t  mba0;                 // +0x0a0
    uint8_t  pad0a1[0x1f];
    uint8_t  mbC0;                 // +0x0c0  (0xf == "running")
    uint8_t  pad0c1[0x07];
    double   mdC8;                 // +0x0c8
    uint8_t  pad0d0[0x0c];
    uint32_t mdDC;                 // +0x0dc
    uint8_t  pad0e0[0xbb4];
    uint8_t  mEnvelopeArea[0x050]; // +0xc94  (embed Envelope at +0xc94)
    uint32_t mFlagsCE4;            // +0xce4
    uint8_t  padCE8[0x1104];

    bool   PausedIgnoring(uint32_t idx);
    double RunningAttenuation();
    void   RequestStop(uint32_t reason, uint8_t flags);
    bool   ShouldPauseForLowGain(float gain);
    static double ComputeGainAttenuation(float a, float b, float c, float d, float e);
    void   Tick(uint32_t a, float dt);

    bool   IsFlag1();
    bool   ClearFlag1();
    void   SetInstanceId(uint32_t id);
    bool   IsFlag2();
    bool   IsFlag80();
    double GetDoubleC8();
    double AttnHelper();
    uint8_t Bit3();
    bool   PauseStateAllowed(uint32_t idx, char flag);
};

// The envelope sub-object embedded in Sound at +0xc94.
struct Envelope {
    float    mEnvelope[6];  // +0x00
    int32_t  mPhase;        // +0x18
    uint8_t  mbStarted;     // +0x1c
    float    mElapsedTime;  // +0x20

    void Update(float dt);
};

// The curve/envelope evaluator behind FUN_00a1b020 (mode at +0x18, coeffs at +0x20..0x30).
struct CurveEval {
    float   mf[6];   // +0x00
    int32_t mMode;   // +0x18
    float   mf20;    // +0x20
    float   mf24;    // +0x24
    float   mf28;    // +0x28
    float   mf2c;    // +0x2c
    float   mf30;    // +0x30

    double Eval();
};

// The object owning the listener/emitter lists walked by 0xa1b1e0/0xa1b320/0xa1b390/0xa1b440.
struct SoundGraph {
    uint8_t  pad000[0x2e0];
    void**   mList2e0;      // +0x2e0
    void**   mList2e4;      // +0x2e4
    uint8_t  pad2e8[0x38];
    void*    mFirst320;     // +0x320
    uint8_t  pad324[0x958];
    void**   mListC7c;      // +0xc7c
    void**   mListC80;      // +0xc80

    uint32_t Dispatch(uint32_t a, uint32_t b);   // 0xa1b1e0
    bool     Remove(void* target);               // 0xa1b320
    void     PopFront();                         // 0xa1b390
    bool     Contains(void* target);             // 0xa1b440
};

struct InstrumentZone {
    uint8_t mKeyLo;    // +0x18
    uint8_t mKeyHi;    // +0x19
    uint8_t mVelLo;    // +0x1a
    uint8_t mVelHi;    // +0x1b
    uint8_t pad[0x10];
    float   mParams[0xb];
};

struct ResourceInstrumentBank {
    uint8_t  pad00[0x18];
    InstrumentZone* mZonesBegin;  // +0x18
    InstrumentZone* mZonesEnd;    // +0x1c

    bool FindZone(int32_t key, int32_t vel, void* out);   // out receives a 0x2c-byte zone
};

// =====================================================================================
// 0xa1a590
// =====================================================================================
// @ 0x00A1A590
bool ResponseCurve::SetResponseCurveData(const float* pts, int32_t n) {
    // clear() then resize(): the end pointer is rewound to begin and the vector re-grown
    // to n entries.
    mpEnd = mpBegin;
    FUN_00a1a500(this, (uint32_t)n);

    // The retail body fills four entries per iteration with an identical block; the shape
    // below is the same computation for one entry at a time.
    for (int32_t i = 0; i < n; ++i) {
        float in = pts[i * 2];
        float out = pts[i * 2 + 1];
        float prevIn, prevOut;
        if (i == 0) {
            prevIn = in - 0.0000000001f;
            prevOut = out;
        } else {
            prevIn = pts[i * 2 - 2];
            prevOut = pts[i * 2 - 1];
        }
        float delta = out - prevOut;
        float ratio;
        if (delta != 0.0f) {
            if (delta * 0.0000000001f < (in - prevIn))
                ratio = delta / (in - prevIn);
            else
                ratio = delta;
        } else {
            ratio = 0.0f;
        }
        ResponseCurveData* e = mpBegin + i;
        e->mfInputValue = in;
        e->mfOutputValue = out;
        e->mfPreviousInputValue = prevIn;
        e->mfPreviousOutputValue = prevOut;
        e->mfDeltaRatio = ratio;
    }

    mCount = (uint32_t)(((char*)mpEnd - (char*)mpBegin) / 0x14);
    return mpBegin != mpEnd;
}

// =====================================================================================
// 0xa1a9d0
// =====================================================================================
// @ 0x00A1A9D0
bool ResponseCurve::InitFromConfiguration(void* cfg, uint32_t key) {
    float def[4];
    def[0] = 0.0f;
    def[1] = 0.0f;
    def[2] = 1.0f;
    def[3] = 1.0f;
    SetResponseCurveData(def, 2);

    if (cfg == 0)
        return false;

    float* pData = 0;
    float  count = 0.0f;
    if (!((int(__thiscall*)(void*, uint32_t, void*, void*))VtOf(cfg)[0x44 / 4])(cfg, key, &count, &pData))
        return false;

    SetResponseCurveData(pData, (int)count >> 1);
    return true;
}

// =====================================================================================
// 0xa1aa50
// =====================================================================================
// @ 0x00A1AA50
ResponseCurve::ResponseCurve() {
    mpPoolBegin = &mBuffer[0];
    mpEnd = &mBuffer[0];
    mpBegin = &mBuffer[0];
    mpCapacity = &mBuffer[42];
    mCount = 0;

    float def[4];
    def[0] = 0.0f;
    def[1] = 0.0f;
    def[2] = 1.0f;
    def[3] = 1.0f;
    SetResponseCurveData(def, 2);
}

// =====================================================================================
// 0xa1aad0
// =====================================================================================
// @ 0x00A1AAD0
uint8_t ResponseCurve::ParseString(char* str, char sep) {
    // Without an explicit separator, take the first non-alphanumeric character.
    if (sep == '\0') {
        for (char* p = str; *p != '\0'; ++p) {
            if (isalnum((int)*p) == 0) {
                sep = *p;
                break;
            }
        }
    }

    // Count the separator occurrences (plus one).
    uint32_t count = 1;
    for (char* p = str; *p != '\0'; ++p) {
        if (*p == sep)
            ++count;
    }

    // An odd number of fields cannot form (x,y) pairs.
    if ((count & 1) != 0)
        return 0;

    FloatVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCapacity = 0;
    vec.mpPoolBegin = (float*)vec.mPool;
    FUN_00ab94c0(&vec, count);

    uint32_t i = 0;
    for (;;) {
        char buf[128];
        uint32_t j = 0;
        while (str[i] != '\0' && str[i] != sep) {
            if (j < 0x7f) {
                buf[j] = str[i];
                ++j;
            }
            ++i;
        }
        buf[j] = '\0';

        float value = (float)FUN_0092dc50(buf, 0);

        if (vec.mpEnd < vec.mpCapacity)
            *vec.mpEnd++ = value;
        else
            FUN_00a1a1e0(&vec, &value);

        if (str[i] == '\0')
            break;
        ++i;
    }

    uint8_t ok = SetResponseCurveData(vec.mpBegin, (int32_t)(count / 2));

    if (vec.mpBegin != 0 && vec.mpBegin != (float*)vec.mPool)
        FUN_00f47380(vec.mpBegin);
    return ok;
}

// =====================================================================================
// 0xa1ac70
// =====================================================================================
// @ 0x00A1AC70
float FUN_00a1ac70(int a, int b) {
    // Note -> frequency ratio: 440 * 2^((n - 69) * 0.0577623).
    double fa = 440.0 * pow(2.0, ((double)a - 69.0) * 0.0577623);
    double fb = 440.0 * pow(2.0, ((double)b - 69.0) * 0.0577623);
    return (float)(fa / fb);
}

// =====================================================================================
// 0xa1acd0
// =====================================================================================
// @ 0x00A1ACD0
bool Sound::ClearFlag1() {
    if ((mFlagsCE4 & 1) == 0)
        return false;
    mFlagsCE4 &= ~1u;
    ((void(__thiscall*)(void*))VtOf(this)[0x94 / 4])(this);
    return true;
}

// =====================================================================================
// 0xa1ad20
// =====================================================================================
// @ 0x00A1AD20
void Sound::SetInstanceId(uint32_t id) {
    uint32_t flags = mFlagsCE4;
    mInstanceId = id;
    mFlagsCE4 = flags | 2u;
}

// =====================================================================================
// 0xa1ad40
// =====================================================================================
// @ 0x00A1AD40
bool Sound::IsFlag2() {
    return (mFlagsCE4 & 2) == 2;
}

// =====================================================================================
// 0xa1adc0
// =====================================================================================
// @ 0x00A1ADC0
bool Sound::PauseStateAllowed(uint32_t idx, char flag) {
    if (flag != 0 && (mFlagsCE4 & 0x800) != 0)
        return false;
    if (idx < *(uint32_t*)((char*)this + 0x1dec))
        return *((uint8_t*)this + 0x1de4 + idx) > 0u;
    return *(uint32_t*)((char*)this + 0x1de0) != 0;
}

// =====================================================================================
// 0xa1ae00
// =====================================================================================
// @ 0x00A1AE00
bool Sound::PausedIgnoring(uint32_t idx) {
    return (int)*(uint32_t*)((char*)this + 0x1de0) - (int)*((uint8_t*)this + 0x1de4 + idx) > 0;
}

// =====================================================================================
// 0xa1ae20
// =====================================================================================
// @ 0x00A1AE20
bool Sound::IsFlag80() {
    return (mFlagsCE4 & 0x80) == 0x80;
}

// =====================================================================================
// 0xa1ae40
// =====================================================================================
// @ 0x00A1AE40
double Sound::GetDoubleC8() {
    return *(double*)((char*)this + 0xcc8);
}

// =====================================================================================
// 0xa1ae50
// =====================================================================================
// @ 0x00A1AE50
double Sound::AttnHelper() {
    typedef double (__thiscall* AttnFn)(void*, float, float, float, float, float);
    double a = ((AttnFn)VtOf(this)[0xa8 / 4])(this, mf48, mf50, mf54, mf58, mf98);
    return a * mf5c;
}

// =====================================================================================
// 0xa1ae90
// =====================================================================================
// @ 0x00A1AE90
double Sound::RunningAttenuation() {
    if (mbC0 == 0xf) {
        typedef double (__thiscall* AttnFn)(void*, float, float, float, float, float);
        return ((AttnFn)VtOf(this)[0xa8 / 4])(this, mf48, mf50, mf54, mf58, mf98);
    }
    return 1.0;
}

// =====================================================================================
// 0xa1aef0
// =====================================================================================
// @ 0x00A1AEF0
void Sound::RequestStop(uint32_t reason, uint8_t flags) {
    uint32_t mask = 0x80;
    if ((mFlagsCE4 & mask) == 0) {
        mFlagsCE4 |= mask;
        mdDC = reason;
        mb9c = flags;
        void* at = FUN_00a206f0();
        ((void(__thiscall*)(void*, int, uint32_t, uint32_t, uint32_t, void*))VtOf(at)[0x128 / 4])(
            at, 0x63e3de7, mInstanceId, reason, flags, this);
    }
}

// =====================================================================================
// 0xa1af50
// =====================================================================================
// @ 0x00A1AF50
uint8_t Sound::Bit3() {
    uint8_t v = mbC0;
    v = v >> 3;
    v = v & 1;
    return v;
}

// =====================================================================================
// 0xa1af80
// =====================================================================================
// @ 0x00A1AF80
bool Sound::ShouldPauseForLowGain(float gain) {
    return (mFlagsCE4 & 0x1000) == 0 && gain < mf6c;
}

// =====================================================================================
// 0xa1afb0
// =====================================================================================
// @ 0x00A1AFB0
double Sound::ComputeGainAttenuation(float a, float b, float c, float d, float e) {
    (void)d;
    if (e != 1.0f)
        a = (1.0f / e) * a;
    if (c > a)
        return 1.0;
    if (b == 0.0f)
        return 1.0;
    double t = ((double)a / (double)c) - 1.0;
    return 1.0 / (t * (double)b + 1.0);
}

// =====================================================================================
// 0xa1b020
// =====================================================================================
// @ 0x00A1B020
double CurveEval::Eval() {
    float f0 = mf[mMode];
    float f2;
    float f3;

    switch (mMode) {
    case 0:
    case 2:
        return 1.0;
    case 1:
        f2 = 1.0f;
        f3 = 0.0f;
        break;
    case 3:
        if (mf2c == 0.0f)
            mf2c = mf28;
        f2 = mf24;
        f3 = mf2c;
        break;
    case 4:
        return mf24;
    case 5:
        if (mf30 == 0.0f)
            mf30 = mf28;
        f3 = mf30;
        f2 = 0.0f;
        break;
    default:
        return 0.0;
    }

    if (f2 == 0.0f || f3 < 0.000000000001f)
        f3 = f2;

    if (f0 != 0.0f)
        f2 = ((f2 - f3) * mf20) / f0 + f3;

    mf28 = f2;
    return f2;
}

// =====================================================================================
// 0xa1b100
// =====================================================================================
// @ 0x00A1B100
void Envelope::Update(float dt) {
    if (!mbStarted || mPhase == 0 || mPhase == 4 || mPhase == 6)
        return;

    mElapsedTime = mElapsedTime + dt;
    if (mPhase >= 6)
        return;

    for (;;) {
        int32_t p = mPhase;
        if (p == 4)
            return;
        if (mEnvelope[p] > mElapsedTime)
            return;
        if (mElapsedTime == mEnvelope[p])
            return;
        p = p + 1;
        mbStarted = 1;
        mElapsedTime = 0.0f;
        mPhase = p;
        if (p >= 6)
            return;
    }
}

// =====================================================================================
// 0xa1b160
// =====================================================================================
// @ 0x00A1B160
bool ResourceInstrumentBank::FindZone(int32_t key, int32_t vel, void* out) {
    int32_t n = (int32_t)(((char*)mZonesEnd - (char*)mZonesBegin) / 0x2c);
    for (int32_t i = 0; i < n; ++i) {
        InstrumentZone* z = (InstrumentZone*)((char*)mZonesBegin + i * 0x2c);
        if (key >= (int)z->mKeyLo && key <= (int)z->mKeyHi &&
            vel >= (int)z->mVelLo && vel <= (int)z->mVelHi) {
            const uint32_t* src = (const uint32_t*)z;
            uint32_t* dst = (uint32_t*)out;
            for (int k = 0; k != 0xb; ++k)
                dst[k] = src[k];
            return true;
        }
    }
    return false;
}

// =====================================================================================
// 0xa1b1e0
// =====================================================================================
// @ 0x00A1B1E0
uint32_t SoundGraph::Dispatch(uint32_t a, uint32_t b) {
    // `this` is an interior pointer: the vtable lives 4 bytes before it.
    char* vtableOwner = (char*)this - 4;
    if (((bool(__thiscall*)(void*, uint32_t, uint32_t))VtOf(vtableOwner)[0xac / 4])(vtableOwner, a, b))
        return 1;
    void* inner = *(void**)((char*)this + 0x40);
    if (inner != 0)
        return ((uint32_t(__thiscall*)(void*, uint32_t, uint32_t))VtOf(inner)[0x30 / 4])(inner, a, b);
    return 0;
}

// =====================================================================================
// 0xa1b230
// =====================================================================================
// @ 0x00A1B230
void Sound::Tick(uint32_t a, float dt) {
    *(float*)((char*)this + 0x324) = dt + *(float*)((char*)this + 0x324);
    ((Envelope*)((char*)this + 0xc94))->Update(dt);

    if ((mFlagsCE4 & 0x40) != 0) {
        if (*(int32_t*)((char*)this + 0xcac) == 6 ||
            ((bool(__thiscall*)(void*, uint32_t, int))VtOf(this)[0x20 / 4])(this, 0xffffffffu, 1)) {
            ((void(__thiscall*)(void*))VtOf(this)[0x8c / 4])(this);
            return;
        }
    }

    if (((bool(__thiscall*)(void*, float))VtOf(this)[0x70 / 4])(this, dt)) {
        float p = mf98;
        float gain = mf58;
        if (p != 1.0f)
            gain = gain * p;
        if (mbC0 == 0xf && gain < mf48 && mba0 == 0) {
            if (((bool(__thiscall*)(void*, int, int))VtOf(this)[0x20 / 4])(this, 2, 0))
                return;
        }
        ((void(__thiscall*)(void*, float, uint32_t, int))VtOf(this)[0x9c / 4])(this, dt, a, 0);
    }
    (void)a;
}

// =====================================================================================
// 0xa1b320
// =====================================================================================
// @ 0x00A1B320
bool SoundGraph::Remove(void* target) {
    void** it = mListC7c;
    while (it != mListC80) {
        if (*it == target) {
            ((void(__thiscall*)(void*, int))VtOf(target)[0xd4 / 4])(target, 0);
            void** last = mListC80 - 1;
            *it = *last;
            mListC80 = last;
            ((void(__thiscall*)(void*))VtOf(target)[4 / 4])(target);
            return true;
        }
        ++it;
    }
    return false;
}

// =====================================================================================
// 0xa1b390
// =====================================================================================
// @ 0x00A1B390
void SoundGraph::PopFront() {
    void** end = mListC80;
    void* item = *(end - 1);
    mListC80 = end - 1;

    ((void(__thiscall*)(void*))VtOf(item)[4 / 4])(item);

    for (void** it = mListC7c; it != mListC80; ++it)
        ((void(__thiscall*)(void*, void*))VtOf(*it)[0xd4 / 4])(*it, item);

    ((void(__thiscall*)(void*, void*))VtOf(item)[0xc8 / 4])(item, this);
}

// =====================================================================================
// 0xa1b440
// =====================================================================================
// @ 0x00A1B440
bool SoundGraph::Contains(void* target) {
    if (mFirst320 != 0 && target == mFirst320)
        return true;
    for (void** it = mList2e0; it != mList2e4; ++it) {
        if (*it == target)
            return true;
    }
    return false;
}
