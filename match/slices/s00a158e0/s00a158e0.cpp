// Slice s00a158e0: audio DSP voice/effect nodes (gain ramp, int16 output mixdown, level meter).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
// Field access uses fld<T>(obj, offset) because these node/context types are only known by offset.
#include "types.h"
#include <new>
#include <string.h>
#include <math.h>
#include <float.h>
#include <xmmintrin.h>

template <class T> static inline T& fld(void* p, int off) { return *(T*)((char*)p + off); }

void operator delete(void*);

// ---- external callees (masked relocations) ----
extern const float g_GainTable[];                       // 0x0144d600
void  Mix_0112d590(float** dst, float** src, float gain, int dstCh, int srcCh, int n);  // 0x0112d590
struct FxSystem { void RemoveTimer(void* timer); };     // rw::audio::core::System::RemoveTimer (0x0112dad0)
struct SndPlayer1Plugin { void Initialize(); };         // rw::audio::core::PlugIn::Initialize<SndPlayer1> (0x0112dbb0)
int   GetSystemAT();                                    // EA::Audio::GetSystemAT (0x00a206f0)

struct Elem12 {                                         // 12-byte element, ctor 0x00b7d170 / dtor 0x00a151a0
    uint32_t a, b, c;
    Elem12();
    ~Elem12();
};

// -------------------------------------------------------------------------
// Buffer descriptor used by the mixing context.
struct ChanBuf { char pad0[4]; float* data; char pad8[6]; uint16_t stride; };  // +4 data, +0xe stride (floats/row)

struct MixCtx {                                         // sizeof >= 0x3002c
    char pad[0x3000c];
    ChanBuf* bufA;      // +0x3000c
    ChanBuf* bufB;      // +0x30010
    char pad14[4];
    struct { char p[0xc]; float rate; }* cfg;  // +0x30018
    char pad1c[4];
    int count;          // +0x30020
    char pad24[4];
    float tempo;        // +0x30028
};

// One gain-ramped sample: blend==0 passes through, blend==1 applies the table gain, else crossfade.
#define RAMP_STEP(K) \
    { \
        float s = src[K]; \
        if (blend == 0.0f) { \
            dst[K] = s; \
        } else if (blend == 1.0f) { \
            dst[K] = s * g_GainTable[phase >> 16]; \
        } else { \
            dst[K] = s * inv + (s * g_GainTable[phase >> 16]) * blend; \
        } \
        phase += step; \
        if (phase >= 0x10000000) phase -= 0x10000000; \
    }

// @ 0x00a158e0
int ApplyGainRamp(char* node, MixCtx* ctx)
{
    {
        int i = 2;
        const float* p = (const float*)(node + 0x80);
        bool nz;
        do {
            if (i >= 14) break;
            nz = (*p != 0.0f);
            p += 4;
            i += 2;
        } while (!nz);
    }
    if (fld<float>(node, 0x70) != 0.0f) {
        ChanBuf* out = ctx->bufB;
        int channels = fld<uint8_t>(node, 0x21);
        float blend = fld<float>(node, 0x78);
        ChanBuf* in = ctx->bufA;
        int n = ctx->count;
        float inv = 1.0f - blend;
        uint32_t step = (uint32_t)(((ctx->tempo / ctx->cfg->rate) * fld<float>(node, 0x70)) * 4096.0f * 65536.0f);
        uint32_t phase = 0;
        int ch = 0;
        if (channels > 0) {
            do {
                float* src = in->data + in->stride * ch;
                float* dst = out->data + out->stride * ch;
                phase = fld<uint32_t>(node, 0xe0);
                int i = 0;
                if (n >= 4) {
                    int g = ((n - 4) >> 2) + 1;
                    i = g * 4;
                    do {
                        RAMP_STEP(0) RAMP_STEP(1) RAMP_STEP(2) RAMP_STEP(3)
                        src += 4;
                        dst += 4;
                    } while (--g != 0);
                }
                if (i < n) {
                    int r = n - i;
                    do {
                        RAMP_STEP(0)
                        src++;
                        dst++;
                    } while (--r != 0);
                }
                ch++;
            } while (ch < channels);
        }
        fld<uint32_t>(node, 0xe0) = phase;
        ChanBuf* t = ctx->bufB;
        ctx->bufB = ctx->bufA;
        ctx->bufA = t;
    }
    return 1;
}

// ---- Effect base with 6 sub-elements ----
struct EffRoot { virtual ~EffRoot() {} };
struct EffBase : EffRoot {
    virtual ~EffBase() {}                               // vtable 0x01451604
    char pad[0x20];
    Elem12 elems[6];                                    // +0x24
    __declspec(noinline) EffBase();
};

// @ 0x00a15c20
EffBase::EffBase() {}

// @ 0x00a15c80
__declspec(noinline) void ConstructEffBase(EffBase* p, int off)
{
    new (p) EffBase();
    if (off) fld<char*>(p, 0xc) = (char*)p + off;
}

// @ 0x00a15cd0
bool InitMeterNode(char* p)
{
    ConstructEffBase((EffBase*)p, 0x70);
    float* f = (float*)(p + 0x70);
    for (int i = 0; i < 14; i++) { *f = 0.0f; f += 2; }
    fld<float>(p, 0x78) = 1.0f;
    fld<uint32_t>(p, 0xe0) = 0;
    return true;
}

// @ 0x00a15d40
int WriteInt16Output(char* node, MixCtx* ctx)
{
    uint32_t pos;
    if (fld<char>(node, 0x24)) {
        void* parent = fld<void*>(node, 8);
        fld<float>(parent, 0x28) = (FLT_MAX - fld<float>(node, 0x18)) + fld<float>(parent, 0x28);
        fld<float>(node, 0x18) = FLT_MAX;
        if (fld<char**>(node, 0x28) != fld<char**>(node, 0x2c)) {
            uint32_t channels = fld<uint8_t>(node, 0x20);
            ChanBuf* out = ctx->bufB;
            float* inPtr[6];
            float* outPtr[6];
            int i = 0;
            if ((int)channels > 0) {
                do {
                    ChanBuf* a = ctx->bufA;
                    inPtr[i] = a->data + a->stride * i;
                    i++;
                } while (i < (int)channels);
            }
            outPtr[0] = out->data;
            outPtr[1] = out->data + out->stride;
            Mix_0112d590(outPtr, inPtr, 1.0f, 2, channels, 0x100);
            int step = (int)(ctx->cfg->rate / (float)fld<uint32_t>(node, 0x1d8));
            uint32_t remaining = ctx->count / step;
            pos = 0;
            while (remaining != 0 && fld<char**>(node, 0x28) != fld<char**>(node, 0x2c)) {
                uint32_t chunk = (uint32_t)(fld<int>(node, 0x1d0) - fld<int>(node, 0x1d4)) >> 2;
                if (remaining < chunk) chunk = remaining;
                int16_t* dst = (int16_t*)(**fld<char***>(node, 0x28) + fld<int>(node, 0x1d4));
                int ch = 0;
                do {
                    float* src = outPtr[ch] + pos;
                    int16_t* d = dst;
                    for (uint32_t k = chunk; k != 0; k--) {
                        float f = *src;
                        src += step;
                        if (f > 1.0f) f = 1.0f;
                        else if (-1.0f > f) f = -1.0f;
                        *d = (int16_t)(int)(f * 32767.0f);
                        d += 2;
                    }
                    ch++;
                    dst++;
                } while (ch < 2);
                pos += chunk;
                fld<int>(node, 0x1d4) += chunk * 4;
                remaining -= chunk;
                if (fld<int>(node, 0x1d4) == fld<int>(node, 0x1d0)) {
                    typedef void (*Cb)(void*, void*);
                    Cb cb = fld<Cb>(node, 0x1dc);
                    if (cb) cb(**fld<char***>(node, 0x28), fld<void*>(node, 0x1e0));
                    **fld<char***>(node, 0x28) = *(fld<char**>(node, 0x2c) - 1);
                    fld<char**>(node, 0x2c) -= 1;
                    fld<int>(node, 0x1d4) = 0;
                }
            }
        }
    }
    return 1;
}

// @ 0x00a15f70   (scalar deleting dtor of a fixed-buffer container owner)
struct FixedOwnerBase {
    virtual ~FixedOwnerBase() {}                        // vtable 0x014bc0fc
    char pad[0x20];
};
struct FixedBuf {                                       // eastl fixed vector header
    char* mpBegin; char pad[0xc]; char* mpLocal;
    ~FixedBuf() { if (mpBegin && mpBegin != mpLocal) operator delete(mpBegin); }
};
struct FixedOwner : FixedOwnerBase {
    char pad24[4];
    FixedBuf mBuf;                                      // +0x28 (mpLocal at +0x38)
    FixedOwner();
};
FixedOwner::FixedOwner() {}
// scalar deleting dtor of FixedOwner is implicit; force emission
void KeepFixedOwner(FixedOwner* p) { delete p; }

// ---- Output sink with a fixed 100-entry queue ----
struct PtrVec {
    void** mpBegin;     // +0x28
    void** mpEnd;       // +0x2c
    void** mpCap;       // +0x30
    void  DoInsertValue(void** pos, void* const* val);      // FUN_00899480
};
struct SinkBase { virtual void s0(); virtual void s1(); };
struct Sink {
    virtual void v0();                                  // vtable 0x01451670
    char pad[0x20];
    char mActive;       // +0x24
    char pad25[3];
    PtrVec mQueue;      // +0x28
    char pad34[4];
    void** mpFixed;     // +0x38
    char pad3c[4];
    void* mBuf[100];    // +0x40
    Sink() { mpFixed = mBuf; mQueue.mpEnd = mBuf; mQueue.mpBegin = mBuf; mQueue.mpCap = mQueue.mpBegin + 100; }
    int mEnd;           // +0x1d0
    int mPos;           // +0x1d4
    int mCount;         // +0x1d8
    void (*mCb)(void*, void*);   // +0x1dc
    void* mCbArg;       // +0x1e0
    float mDummy;
};

// @ 0x00a15fb0
bool InitSink(Sink* p)
{
    new (p) Sink();
    p->mActive = 0;
    void** last = p->mQueue.mpEnd;
    void** first = p->mQueue.mpBegin;
    void** end = p->mQueue.mpEnd;
    memcpy(first, last, (char*)end - (char*)last);
    p->mQueue.mpEnd = (void**)((char*)p->mQueue.mpEnd + (-(last - first)) * 4);
    p->mCb = 0;
    p->mCbArg = 0;
    return true;
}

struct SinkOwner { char pad[0x28]; float mLevel; };

struct SinkImpl : Sink {
    void Command(int op, int* args);
};
// @ 0x00a16020
void SinkImpl::Command(int op, int* args)
{
    switch (op) {
    case 0: {
        mCb = (void (*)(void*, void*))args[1];
        mCbArg = (void*)args[2];
        mEnd = args[0];
        int c = args[3];
        mPos = 0;
        mCount = c;
        mActive = 1;
        SinkOwner* o = fld<SinkOwner*>(this, 8);
        o->mLevel = (FLT_MAX - fld<float>(this, 0x18)) + o->mLevel;
        fld<float>(this, 0x18) = FLT_MAX;
        return;
    }
    case 1: {
        mActive = 0;
        SinkOwner* o = fld<SinkOwner*>(this, 8);
        o->mLevel = -fld<float>(this, 0x18) + o->mLevel;
        fld<float>(this, 0x18) = 0.0f;
        void** last = mQueue.mpEnd;
        if (GetSystemAT()) {
            uint32_t n = (uint32_t)(mQueue.mpEnd - mQueue.mpBegin);
            for (uint32_t i = 0; i < n; i++) {
                if (mCb) mCb(mQueue.mpBegin[i], mCbArg);
            }
            last = mQueue.mpEnd;
        }
        void** first = mQueue.mpBegin;
        void** end = mQueue.mpEnd;
        memcpy(first, last, (char*)end - (char*)last);
        mQueue.mpEnd = (void**)((char*)mQueue.mpEnd + (-(last - first)) * 4);
        return;
    }
    case 2: {
        int n = args[1];
        void** p = (void**)args[0];
        while (n != 0) {
            void** e = mQueue.mpEnd;
            n--;
            if (e < mQueue.mpCap) {
                mQueue.mpEnd = e + 1;
                if (e) *e = *p;
            } else {
                mQueue.DoInsertValue(e, p);
            }
            p++;
        }
        return;
    }
    }
}

// @ 0x00a16170  (push an 8-byte command onto the owner's ring)
struct CmdRing {
    char pad[0x20];
    char* mpBuf;        // +0x20
    char pad24[0x90];
    int mWrite;         // +0xb4
    void Push(uint32_t a, uint32_t b);
};
void CmdRing::Push(uint32_t a, uint32_t b)
{
    uint32_t* p = (uint32_t*)(mpBuf + mWrite);
    mWrite += 8;
    p[0] = a;
    p[1] = b;
}

struct Fx {
    void ClearState(); void RemoveTimerIfSet(); void CopyParams(); void MeterProcess(ChanBuf* buf, int n);
};

// @ 0x00a161c0
void Fx::ClearState()
{
    char* p = (char*)this;
    float* f = (float*)(p + 0x48);
    for (int i = 0; i < 0x13; i++) { *f = 0.0f; f += 2; }
    fld<float>(p, 0xf8) = 0.0f;  fld<float>(p, 0x128) = 0.0f; fld<float>(p, 0x140) = 0.0f;
    fld<float>(p, 0xfc) = 0.0f;  fld<float>(p, 0x12c) = 0.0f; fld<float>(p, 0x144) = 0.0f;
    fld<float>(p, 0x100) = 0.0f; fld<float>(p, 0x130) = 0.0f; fld<float>(p, 0x148) = 0.0f;
    fld<float>(p, 0x104) = 0.0f; fld<float>(p, 0x134) = 0.0f; fld<float>(p, 0x14c) = 0.0f;
    fld<float>(p, 0x108) = 0.0f; fld<float>(p, 0x138) = 0.0f; fld<float>(p, 0x150) = 0.0f;
    fld<float>(p, 0x10c) = 0.0f; fld<float>(p, 0x13c) = 0.0f; fld<float>(p, 0x154) = 0.0f;
}

// @ 0x00a16270
void Fx::RemoveTimerIfSet()
{
    char* p = (char*)this;
    if (fld<char>(p, 0x159) == 1) fld<FxSystem*>(p, 4)->RemoveTimer(p + 0x24);
}

// @ 0x00a16290
void ResetMeter(char* p)
{
    if (fld<int>(p, 0x3c) == 0) {
        fld<uint32_t>(p, 0x3c) = (uint16_t)(int)(fld<float>(fld<void*>(p, 4), 0xc0) * 0.01f);
    }
    if (fld<char>(p, 0x158) != 0) {
        fld<char>(p, 0x158) = 0;
        return;
    }
    fld<float>(p, 0x48) = 0.0f; fld<float>(p, 0x50) = 0.0f; fld<float>(p, 0x58) = 0.0f;
    fld<float>(p, 0x60) = 0.0f; fld<float>(p, 0x68) = 0.0f; fld<float>(p, 0x70) = 0.0f;
    fld<float>(p, 0x78) = 0.0f; fld<float>(p, 0x80) = 0.0f; fld<float>(p, 0x88) = 0.0f;
    fld<float>(p, 0x90) = 0.0f; fld<float>(p, 0x98) = 0.0f; fld<float>(p, 0xa0) = 0.0f;
}

// @ 0x00a16320
int ClearOwnerCallback(char* p)
{
    fld<Fx*>(p, 4)->ClearState();
    return 8;
}

// @ 0x00a16340   (copy per-channel parameter banks)
void Fx::CopyParams()
{
    char* p = (char*)this;
    uint8_t c = fld<uint8_t>(p, 0x21);
    if (c == 1) {
        fld<float>(p, 0xb0) = fld<float>(p, 0x140);
        fld<float>(p, 0x80) = fld<float>(p, 0x128);
        fld<float>(p, 0x50) = fld<float>(p, 0xf8);
        return;
    }
    fld<float>(p, 0xa8) = fld<float>(p, 0x140);
    if (c == 2) {
        fld<float>(p, 0xb8) = fld<float>(p, 0x144);
        fld<float>(p, 0x78) = fld<float>(p, 0x128);
        fld<float>(p, 0x88) = fld<float>(p, 0x12c);
        fld<float>(p, 0x48) = fld<float>(p, 0xf8);
        fld<float>(p, 0x58) = fld<float>(p, 0xfc);
        return;
    }
    if (c == 4) {
        fld<float>(p, 0xb8) = fld<float>(p, 0x144);
        fld<float>(p, 0xc0) = fld<float>(p, 0x148);
        fld<float>(p, 0xc8) = fld<float>(p, 0x14c);
        fld<float>(p, 0x78) = fld<float>(p, 0x128);
        fld<float>(p, 0x88) = fld<float>(p, 0x12c);
        fld<float>(p, 0x90) = fld<float>(p, 0x130);
        fld<float>(p, 0x98) = fld<float>(p, 0x134);
        fld<float>(p, 0x48) = fld<float>(p, 0xf8);
        fld<float>(p, 0x58) = fld<float>(p, 0xfc);
        fld<float>(p, 0x60) = fld<float>(p, 0x100);
        fld<float>(p, 0x68) = fld<float>(p, 0x104);
        return;
    }
    fld<float>(p, 0xb0) = fld<float>(p, 0x144);
    fld<float>(p, 0xb8) = fld<float>(p, 0x148);
    fld<float>(p, 0xc0) = fld<float>(p, 0x14c);
    fld<float>(p, 0xc8) = fld<float>(p, 0x150);
    fld<float>(p, 0xd0) = fld<float>(p, 0x154);
    fld<float>(p, 0x78) = fld<float>(p, 0x128);
    fld<float>(p, 0x80) = fld<float>(p, 0x12c);
    fld<float>(p, 0x88) = fld<float>(p, 0x130);
    fld<float>(p, 0x90) = fld<float>(p, 0x134);
    fld<float>(p, 0x98) = fld<float>(p, 0x138);
    fld<float>(p, 0xa0) = fld<float>(p, 0x13c);
    fld<float>(p, 0x48) = fld<float>(p, 0xf8);
    fld<float>(p, 0x50) = fld<float>(p, 0xfc);
    fld<float>(p, 0x58) = fld<float>(p, 0x100);
    fld<float>(p, 0x60) = fld<float>(p, 0x104);
    fld<float>(p, 0x68) = fld<float>(p, 0x108);
    fld<float>(p, 0x70) = fld<float>(p, 0x10c);
}

// ---- Player plugin node ----
struct PlayerRoot { virtual ~PlayerRoot() {} };
struct PlayerNode : PlayerRoot {
    virtual ~PlayerNode() {}                            // vtable 0x01452110
    char pad[0x20];
    char plugin[0x10];
    __declspec(noinline) PlayerNode();
};
// @ 0x00a164d0
PlayerNode::PlayerNode()
{
    ((SndPlayer1Plugin*)(plugin - 0x0))->Initialize();
}

// @ 0x00a16520
struct QNode { void* vt; CmdRing* mOwner; void Queue(int, int); };
void QNode::Queue(int, int)
{
    mOwner->Push((uint32_t)(void*)&ClearOwnerCallback, (uint32_t)this);
}

// @ 0x00a16550
void Fx::MeterProcess(ChanBuf* buf, int n)
{
    char* node = (char*)this;
    int channels = fld<uint8_t>(node, 0x21);
    int fill = 0;
    if (channels <= 0) {
        fld<int>(node, 0x40) = 0;
        return;
    }
    float* acc = (float*)(node + 0xe0);
    fill = fld<int>(node, 0x40);
    for (int ch = 0; ch < channels; ch++, acc++) {
        float* p = buf->data + buf->stride * ch;
        float* end = p + n;
        fill = fld<int>(node, 0x40);
        while (p < end) {
            int avail = (int)(end - p);
            int room = fld<int>(node, 0x3c) - fill;
            if (avail < room) room = avail;
            room &= ~3;
            if (room == 0) {
                float f = *p;
                if (f <= 0.0f) f = f * -1.0f;
                if (f > acc[0xc]) acc[0xc] = f;
                if (f > acc[0x18]) acc[0x18] = f;
                float s = *p;
                p++;
                fill++;
                acc[0] = s * s + acc[0];
            } else if (((uint32_t)p & 0xf) == 0) {
                float* stop = p + room;
                do {
                    __m128 v = _mm_load_ps(p);
                    __m128 sq = _mm_mul_ps(v, v);
                    __m128 hi = _mm_movehl_ps(sq, sq);
                    __m128 m = _mm_max_ss(_mm_max_ss(sq, _mm_shuffle_ps(sq, sq, 0xb1)),
                                          _mm_max_ss(hi, _mm_shuffle_ps(hi, hi, 0xb1)));
                    m = _mm_sqrt_ss(m);
                    acc[0xc] = _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(acc[0xc]), m));
                    acc[0x18] = _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(acc[0x18]), m));
                    float sa = _mm_cvtss_f32(sq);
                    float sb = _mm_cvtss_f32(_mm_shuffle_ps(sq, sq, 1));
                    float sc = _mm_cvtss_f32(hi);
                    float sd = _mm_cvtss_f32(_mm_shuffle_ps(hi, hi, 1));
                    acc[0] = ((sa + sb) + (sc + sd)) + acc[0];
                    fill += 4;
                    p += 4;
                } while (p != stop);
            } else if (room > 0) {
                int groups = ((room - 1) >> 2) + 1;
                do {
                    float a = p[0], b = p[1], c = p[2], d = p[3];
                    if (a <= 0.0f) a = a * -1.0f;
                    if (b <= 0.0f) b = b * -1.0f;
                    if (c <= 0.0f) c = c * -1.0f;
                    if (d <= 0.0f) d = d * -1.0f;
                    if (a > acc[0xc]) acc[0xc] = a;
                    if (b > acc[0xc]) acc[0xc] = b;
                    if (c > acc[0xc]) acc[0xc] = c;
                    if (d > acc[0xc]) acc[0xc] = d;
                    float pk = acc[0xc];
                    if (pk > acc[0x18]) acc[0x18] = pk;
                    acc[0] = p[0] * p[0] + acc[0];
                    acc[0] = p[1] * p[1] + acc[0];
                    acc[0] = p[2] * p[2] + acc[0];
                    acc[0] = p[3] * p[3] + acc[0];
                    fill += 4;
                    p += 4;
                } while (--groups != 0);
            }
            if (fill >= fld<int>(node, 0x3c)) {
                fill = 0;
                acc[0x12] = acc[0xc];
                acc[0xc] = 0.0f;
                float sum = acc[0];
                acc[0] = 0.0f;
                acc[6] = sqrtf(sum / (float)fld<int>(node, 0x3c));
            }
        }
    }
    fld<int>(node, 0x40) = fill;
}

// @ 0x00a16820
int RunMeter(char* node, MixCtx* ctx)
{
    if (fld<float>(node, 0xd8) != 0.0f) {
        ((Fx*)node)->MeterProcess(ctx->bufA, 0x100);
        ((Fx*)node)->CopyParams();
        fld<char>(node, 0x158) = 1;
        return 1;
    }
    return 1;
}

// @ 0x00a16870
void ConstructPlayerNode(PlayerNode* p, int off)
{
    new (p) PlayerNode();
    if (off) fld<char*>(p, 0xc) = (char*)p + off;
}
