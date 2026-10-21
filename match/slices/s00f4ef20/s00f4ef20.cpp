// Slice s00f4ef20 (batch gold4, slice 10) -- SP terrain brush-effect / ribbon-tool helpers.
// Object file: SP terrain tools (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
//   0x00f4ef20  cTerrainBrushEffect::Stop(int)                ret 4
//   0x00f4ef40  lerpAngle(float, float, float)                free
//   0x00f4efe0  cTerrainTool::SubSet(int, float)              ret 8,  this+0x31c
//   0x00f4f000  cTerrainTool::RegisterParams(f,f,f,f,f)       ret 0x14
//   0x00f4f480  cTerrainTool::SampleCurveValue()              void-arg
//   0x00f4f530  cChannel::Advance(float)                      ret 4,   this=+0
//   0x00f4f5a0  cTerrainTool::SetMatrix(...)                  ret 0xc, this+0x0c
//   0x00f4f630  cTerrainTool::SetParams(int,f,f,f)            ret 0x10
//   0x00f4f7a0  cTerrainTool::OnPointer(float,float,int)      ret 0xc
//   0x00f4fa20  cTerrainTool::ReadFromScript()                void
//   0x00f4faa0  cTerrainTool::GetBrushVector()                void
//   0x00f4fb00  cTerrainTool::UpdateBrushSize()               void
//   0x00f4fb80  cTerrainTool::DragUpdate(float)               ret 4

#include "types.h"

namespace SP {

// ===================== float helpers (x87, CRT) =====================
float fabs_f(float v);      // 0x011e08c8   (fabs)
float fmod_f(float, float); // 0x011e08c2   (fmod)

// ===================== external callees =====================
void   Sub_697a80(void* self, int a, int b);                 // 0x00697a80
void   Sub_697af0(void* self, int a, float b, float c, int d); // 0x00697af0
void   Sub_697b20(void* self, int a, float b, float c);      // 0x00697b20
int*   Sub_41ea70();                                          // 0x0041ea70
int*   Sub_f48aa0(void* self);                               // 0x00f48aa0
float  Sub_f987f0(void* self);                               // 0x00f987f0
float  Sub_f927c0(void* self);                               // 0x00f927c0
void   Sub_f4d9c0();                                          // 0x00f4d9c0
int*   EffectsManager();                                      // 0x0067dd50

// The input/event context object embedded at cTerrainTool+0x31c.  Its methods
// are entered with ecx = &mCtx31c (hence __thiscall).
struct cCtx {
    void Key(int code, int value);                // 0x00697a80
    void Pointer(int code, float a, float b, int pressed); // 0x00697af0
    void Move(int pressed, float x, float y);     // 0x00697b20
};

// ===================== float constants =====================
extern const float K_0f;            // 0x013eb8b0  -0.0f (also the xorps sign mask)
extern const float K_n1;            // 0x013eb1bc  -1.0f
extern const float K_1f;            // 0x01485720   1.0f
extern const float K_half;          // 0x01471064   0.5f
extern const float K_half3;         // 0x01471064
extern const float K_pi;            // 0x015b0a9c   3.1415927f
extern const float K_2;             // 0x016c9170   2.0f   (writable data)
extern const float K_03f;           // 0x015b0a74   0.3f
extern const float K_03g;           // 0x015b0a78   0.3f   (writable data)
extern const float K_5f;            // 0x01486110   5.0f
extern const float K_n20;           // 0x013fdf18  -20.0f
extern const float K_p20;           // 0x013eecd8   20.0f
extern const float K_d2r;           // 0x0148e7d8  57.2957802f
extern const float K_d2r2;          // 0x0148e7f0   7.1619725f
extern const float K_10f;           // 0x01473c70  10.0f
extern const float K_6f;            // 0x0147b9f0   6.0f
extern const float K_700f;          // 0x0142eae0 700.0f
extern const float K_07f;           // 0x01485ac0   0.7f

extern int   g_screenW;             // 0x016c9050
extern int   g_screenH;             // 0x016c9054

// string literals (only their addresses matter)
extern const char S_145cf44[], S_145cf2c[], S_145cf14[], S_145cefc[], S_145cee4[];
extern const char S_145cec8[], S_145ceac[], S_145ce94[], S_145ce7c[], S_145ce64[];
extern const char S_145ce50[], S_145ce44[], S_145ce38[], S_145ce34[], S_145ce24[];
extern const char S_145ce14[], S_145ce04[], S_145cdf4[], S_145cde4[], S_145cdd4[];
extern const char S_145cdc4[], S_145cdb4[], S_145cda0[], S_145cd8c[], S_145cd70[];
extern const char S_145cd50[], S_145cd3c[], S_145cd28[], S_145cd18[];
extern const char S_1412ce0[], S_1457f80[], S_1452788[];

// ===================== script-parameter context singleton =====================
// At 0x016c90d8; each method is entered with ecx = its own address.
struct cParamCtx {
    void  Set(const char* name, float value);   // 0x007f25c0
    void  Flush();                              // 0x007f2500
    float Get(const char* name);                // 0x007f2590
};
extern cParamCtx g_paramCtx;

// ===================== the animated 0x24-byte channel =====================
struct cChannel {
    char  mFlag;                // +0x00
    char  mPad01;               // +0x01
    char  mPad02[2];            // +0x02
    float mCur;                 // +0x04
    float mStart;               // +0x08
    float mPrev;                // +0x0c
    float mParamA;              // +0x10
    float mParamB;              // +0x14
    float mTween;               // +0x18
    float mArg0;                // +0x1c
    float mArg1;                // +0x20

    void Advance(float dt);     // 0x00f4f530
};

// ===================== the brush / ribbon tool =====================
struct Vector3 { float x, y, z; };

struct cTerrainTool {
    float mMat00, mMat04, mMat08, mMat0c;   // +0x00
    float mMat10, mMat14, mMat18, mMat1c;   // +0x10
    float mMat20, mMat24, mMat28, mMat2c;   // +0x20
    float mMat30, mMat34, mMat38, mMat3c;   // +0x30
    float mMat40, mMat44, mMat48, mMat4c;   // +0x40
    float mMat50, mMat54, mMat58, mMat5c;   // +0x50
    float mMat60, mMat64, mMat68;           // +0x60
    float mMat6c;                           // +0x6c
    uint8_t mPad70[0x114 - 0x70];           // +0x70
    float mVal114;                          // +0x114
    uint8_t mPad118[8];                     // +0x118

    cChannel mChanA;                        // +0x120
    cChannel mChanB;                        // +0x144

    uint8_t mPad168[0x169 - 0x168];         // +0x168
    char  mFlag169;                         // +0x169
    uint8_t mPad16a[0x274 - 0x16a];         // +0x16a
    float mVal274;                          // +0x274
    uint8_t mPad278[0x28c - 0x278];         // +0x278
    float mTween28c;                        // +0x28c
    float mTween290;                        // +0x290
    uint8_t mPad294[0x298 - 0x294];         // +0x294
    float mParam298;                        // +0x298
    float mParam29c;                        // +0x29c
    uint8_t mPad2a0[0x2ac - 0x2a0];         // +0x2a0
    float mParam2ac;                        // +0x2ac
    float mParam2b0;                        // +0x2b0
    float mParam2b4;                        // +0x2b4
    float mParam2b8;                        // +0x2b8
    float mParam2bc;                        // +0x2bc
    float mParam2c0;                        // +0x2c0
    float mParam2c4;                        // +0x2c4
    float mParam2c8;                        // +0x2c8
    uint8_t mPad2cc[0x30c - 0x2cc];         // +0x2cc
    void* mpScript30c;                      // +0x30c
    float mScriptVal310;                    // +0x310
    float mScriptVal314;                    // +0x314
    char  mDragFlag318;                     // +0x318
    char  mPressed319;                      // +0x319
    uint8_t mPad31a[0x31c - 0x31a];         // +0x31a
    cCtx  mCtx31c;                          // +0x31c
    uint32_t mButtons320;                   // +0x320
    uint8_t mPad324[0x328 - 0x324];         // +0x324
    uint32_t mButtons328;                   // +0x328
    uint8_t mPad32c[0x33c - 0x32c];         // +0x32c
    int   mMode33c;                         // +0x33c
    float mBrushX348;                       // +0x348
    float mBrushY34c;                       // +0x34c
    uint8_t mPad350[0x368 - 0x350];         // +0x350
    float mParam368;                        // +0x368
    float mParam36c;                        // +0x36c
    uint8_t mPad370[0x374 - 0x370];         // +0x370
    float mParam374;                        // +0x374
    float mParam378;                        // +0x378
    float mParam37c;                        // +0x37c
    void* mpPtr380;                         // +0x380

    char   SubSet(int code, float value);                         // 0x00f4efe0
    void   RegisterParams(float a, float b, float c, float d, float e); // 0x00f4f000
    float  SampleCurveValue();                                    // 0x00f4f480
    void   SetMatrix(float, float, float);                        // 0x00f4f5a0
    char   SetParams(int op, float a, float b, float c);          // 0x00f4f630
    char   OnPointer(float x, float y, int pressed);              // 0x00f4f7a0
    void   ReadFromScript();                                      // 0x00f4fa20
    float* GetBrushVector();                                      // 0x00f4faa0
    void   UpdateBrushSize();                                     // 0x00f4fb00
    void   DragUpdate(float dt);                                  // 0x00f4fb80
};

// ===================== cTerrainBrushEffect (only Stop here) =====================
struct cTerrainBrushDescription;

class cTerrainBrushEffect {
public:
    virtual void Initialize(void*, void*, void*);   // +0x00
    virtual void Dispose();                         // +0x04
    virtual void Start(int hardStart);              // +0x08
    virtual int  Stop(int hardStop);                // +0x0c
    virtual int  IsRunning();                       // +0x10
    virtual void ApplyEffect(float, float, void*);  // +0x14

    int   mRefCount;                                // +0x04
    int   mRefCountPad;                             // +0x08
    cTerrainBrushDescription* mDesc;                // +0x0c
    char  mActive;                                  // +0x10
};

}  // namespace SP

using namespace SP;

// g_brushVec: scratch vector written by GetBrushVector (0x016c91b4).
extern float g_brushVec[3];     // 0x016c91b4
extern char  g_latchB0;         // 0x016c91b0
extern char  g_latchB1;         // 0x016c91b1
extern int   g_frameWord;       // 0x016c91c0
extern cParamCtx g_paramCtx;    // 0x016c90d8

// ============================ bodies ============================

// @ 0x00f4ef20
int cTerrainBrushEffect::Stop(int hardStop)
{
    if (mActive) {
        cTerrainBrushDescription* d = mDesc;
        mActive = 0;
        if (*(char*)((char*)d + 0xec))
            Sub_f4d9c0();
    }
    (void)hardStop;
    return 0;
}

// @ 0x00f4ef40
float lerpAngle(float lo, float hi, float t)
{
    float x = fmod_f(hi - lo, 2.0f);
    if (x > 3.1415927f)
        x -= 2.0f;
    else if (-3.1415927f > x)
        x += 2.0f;
    return x * t + lo;
}

// @ 0x00f4efe0
char cTerrainTool::SubSet(int code, float value)
{
    mCtx31c.Key(code, *(int*)&value);
    return 0;
}

// @ 0x00f4f000
void cTerrainTool::RegisterParams(float a, float b, float c, float d, float e)
{
    int* mgr = EffectsManager();
    int* edi = *(int**)((char*)mgr + 0x1c);

    g_paramCtx.Set(S_145cf44, mParam2b8);
    g_paramCtx.Set(S_145cf2c, mParam2bc);
    g_paramCtx.Set(S_145cf14, mParam2c0);
    g_paramCtx.Set(S_145cefc, mParam2c4);
    g_paramCtx.Set(S_145cee4, mParam2c8);
    g_paramCtx.Set(S_145cec8, K_07f);
    g_paramCtx.Set(S_145ceac, K_10f);
    g_paramCtx.Set(S_145ce94, K_07f);
    g_paramCtx.Set(S_145ce7c, K_6f);
    g_paramCtx.Set(S_145ce64, K_700f);
    g_paramCtx.Set(S_145ce50, mVal114);
    g_paramCtx.Set(S_145ce44, mParam2b0 * K_d2r);
    g_paramCtx.Set(S_145ce38, mParam2ac * K_d2r);
    g_paramCtx.Set(S_1412ce0, a);
    g_paramCtx.Set(S_1457f80, mVal114);
    g_paramCtx.Set(S_1452788, mChanA.mTween * K_d2r);
    g_paramCtx.Set(S_145ce34, mChanB.mTween * K_d2r);
    g_paramCtx.Set(S_145ce24, K_2);
    g_paramCtx.Set(S_145ce14, K_1f);
    g_paramCtx.Set(S_145ce04, 0.0f);
    g_paramCtx.Set(S_145cdf4, 0.0f);
    g_paramCtx.Set(S_145cde4, 0.0f);
    g_paramCtx.Set(S_145cdd4, (float)g_screenW / (float)edi[0]);
    g_paramCtx.Set(S_145cdc4, (float)(-g_screenH) / (float)edi[1]);
    g_paramCtx.Set(S_145cdb4, d);
    g_paramCtx.Set(S_145cda0, b);
    g_paramCtx.Set(S_145cd8c, c * 0.0f);
    g_paramCtx.Set(S_145cd70, mParam298 * K_d2r);
    g_paramCtx.Set(S_145cd50, mParam29c * K_d2r2);
    g_paramCtx.Set(S_145cd3c, mVal274);
    g_paramCtx.Set(S_145cd28, e);
    g_paramCtx.Set(S_145cd18, mFlag169 ? 1.0f : 0.0f);
    g_paramCtx.Flush();

    mParam2b8 = g_paramCtx.Get(S_145cf44);
    mParam2bc = g_paramCtx.Get(S_145cf2c);
    mParam2c0 = g_paramCtx.Get(S_145cf14);
    mParam2c4 = g_paramCtx.Get(S_145cefc);
    mParam2c8 = g_paramCtx.Get(S_145cee4);
    mParam368 = g_paramCtx.Get(S_145cec8);
    mParam36c = g_paramCtx.Get(S_145ceac);
    mParam374 = g_paramCtx.Get(S_145ce94);
    mParam378 = g_paramCtx.Get(S_145ce7c);
    mParam37c = g_paramCtx.Get(S_145ce64);
}

// @ 0x00f4f480
float cTerrainTool::SampleCurveValue()
{
    float t = mMat5c * mMat60 + mMat58 * mMat64 + mMat54 * mMat68;
    t = t < -1.0f ? -1.0f : (t > 1.0f ? 1.0f : t);
    float x = fabs_f(t) / 3.1415927f;
    x = x < 0.0f ? 0.0f : (x > 1.0f ? 1.0f : x);
    return (mParam374 - mParam378) + mParam378 * x;
}

// @ 0x00f4f530
void cChannel::Advance(float dt)
{
    float d = mStart - mCur;
    if (d <= 0.0f)
        return;

    float v = mArg0 * dt * K_half + mParamA;
    if (v != mTween) {
        mPrev = mParamA;
        mTween = v;
        mFlag = 1;
    }
    mParamB = mTween;
    mStart = dt;
    mArg1 = mArg1 * 0.0f;
    mCur = 0.0f;
    mFlag = 0;
}

// @ 0x00f4f5a0
void cTerrainTool::SetMatrix(float x, float y, float z)
{
    // Builds the 0x54-byte matrix at +0x00: a zero vector, then (x,y,z)
    // repeated at +0x0c, +0x18, +0x24, +0x30, then the (x,y,z) column
    // scaled by zero at +0x3c and duplicated at +0x48.
    int ix = *(int*)&x;
    int iy = *(int*)&y;
    int iz = *(int*)&z;

    *(int*)((char*)this + 0x0c) = ix;
    *(int*)((char*)this + 0x18) = ix;
    *(int*)((char*)this + 0x24) = ix;
    *(int*)((char*)this + 0x30) = ix;
    *(int*)((char*)this + 0x10) = iy;
    *(int*)((char*)this + 0x1c) = iy;
    *(int*)((char*)this + 0x28) = iy;
    *(int*)((char*)this + 0x34) = iy;
    *(int*)((char*)this + 0x14) = iz;
    *(int*)((char*)this + 0x20) = iz;
    *(int*)((char*)this + 0x2c) = iz;
    *(int*)((char*)this + 0x38) = iz;

    *(char*)((char*)this + 0x00) = 0;
    *(char*)((char*)this + 0x01) = 0;
    *(float*)((char*)this + 0x04) = 0.0f;
    *(float*)((char*)this + 0x08) = 0.0f;

    *(float*)((char*)this + 0x3c) = x * 0.0f;
    *(float*)((char*)this + 0x40) = y * 0.0f;
    *(float*)((char*)this + 0x44) = z * 0.0f;
    *(int*)((char*)this + 0x48) = *(int*)((char*)this + 0x3c);
    *(int*)((char*)this + 0x4c) = *(int*)((char*)this + 0x40);
    *(int*)((char*)this + 0x50) = *(int*)((char*)this + 0x44);
}

// @ 0x00f4f630
char cTerrainTool::SetParams(int op, float a, float b, float c)
{
    if (op == 0x3e9) {
        if (mChanB.mStart - mChanB.mCur > 0.0f) {
            float v = mChanB.mArg0 * 0.3f * 0.5f + mChanB.mParamA;
            if (v != mChanB.mTween) {
                mChanB.mPrev = mChanB.mParamA;
                mChanB.mTween = v;
                mChanB.mFlag = 1;
            }
            mChanB.mParamB = mChanB.mTween;
            mChanB.mStart = 0.3f;
            mChanB.mArg1 = mChanB.mArg1 * 0.0f;
            mChanB.mCur = 0.0f;
            mChanB.mFlag = 0;
        }
        if (mChanA.mStart - mChanA.mCur > 0.0f) {
            float v = mChanA.mArg0 * 0.3f * 0.5f + mChanA.mParamA;
            if (v != mChanA.mTween) {
                mChanA.mPrev = mChanA.mParamA;
                mChanA.mTween = v;
                mChanA.mFlag = 1;
            }
            mChanA.mParamB = mChanA.mTween;
            mChanA.mStart = 0.3f;
            mChanA.mArg1 = mChanA.mArg1 * 0.0f;
            mChanA.mCur = 0.0f;
            mChanA.mFlag = 0;
        }
    }
    mCtx31c.Pointer(op, a, b, c);
    return 0;
}
// @ 0x00f4f7a0
char cTerrainTool::OnPointer(float x, float y, int pressed)
{
    mDragFlag318 = 1;
    mCtx31c.Move(pressed, x, y);

    if (mPressed319 == 0 && *((char*)mpPtr380 + (int)this - 0xa8) != 0) {
        float dx = mBrushY34c - y;
        float dy = mBrushX348 - x;
        dx = dx < -20.0f ? -20.0f : (dx > 20.0f ? 20.0f : dx);
        float ax = -mParam298 * dx;
        dy = dy < -20.0f ? -20.0f : (dy > 20.0f ? 20.0f : dy);
        float ay = fabs_f(ax) > 0.0f ? (mChanB.mParamA + ax) : 0.0f;
        (void)ay;

        if (fabs_f(ax) > 0.0f) {
            mTween28c = mChanB.mParamA + ax;
            g_latchB1 = 0;
            if (mTween28c != mChanB.mTween) {
                mChanB.mPrev = mChanB.mParamA;
                mChanB.mTween = mTween28c;
                mChanB.mFlag = 1;
            }
        } else if (g_latchB1 == 0) {
            g_latchB1 = 1;
            mChanB.Advance(0.3f);
        }

        ax = -mParam29c * dy;
        if (fabs_f(ax) > 0.0f) {
            float v = mChanA.mParamA + ax;
            ax = v < mParam2ac ? mParam2ac : (v > mParam2b0 ? mParam2b0 : v);
            mTween290 = ax;
            g_latchB0 = 0;
            if (ax != mChanA.mTween) {
                mChanA.mPrev = mChanA.mParamA;
                mChanA.mFlag = 1;
                mChanA.mTween = mTween290;
                return pressed != 0;
            }
        } else if (g_latchB0 == 0 && fabs_f(ax) <= 0.0f) {
            g_latchB0 = 1;
            mChanA.Advance(0.3f);
        }
    }

    return pressed != 0;
}
// @ 0x00f4fa20
void cTerrainTool::ReadFromScript()
{
    typedef char (__thiscall *Fn)(void*, int, void**);

    if (mpScript30c) {
        int* vt = *(int**)mpScript30c;
        void* slot;
        if (((Fn)vt[9])(mpScript30c, 0x1102b20, &slot) && *(short*)((char*)slot + 0x12) == 0xd)
            mScriptVal310 = *(float*)Sub_41ea70();
    }
    if (mpScript30c) {
        int* vt = *(int**)mpScript30c;
        void* slot;
        if (((Fn)vt[9])(mpScript30c, 0x1102b2f, &slot) && *(short*)((char*)slot + 0x12) == 0xd)
            mScriptVal314 = *(float*)Sub_41ea70();
    }
}

// @ 0x00f4faa0
float* cTerrainTool::GetBrushVector()
{
    if ((g_frameWord & 1) == 0)
        g_frameWord |= 1;

    float s = mMat28;
    float a = mMat54 * s;
    float b = mMat58 * s;
    float c = mMat5c * s;
    g_brushVec[0] = a;
    g_brushVec[1] = b;
    g_brushVec[2] = c;
    return g_brushVec;
}

// @ 0x00f4fb00
void cTerrainTool::UpdateBrushSize()
{
    int* p = Sub_f48aa0(this);
    float v;
    if (p) {
        float t = Sub_f987f0(p);
        int* vt = *(int**)p;
        typedef void* (__thiscall *Fn)(void*, void*);
        void* r = ((Fn)vt[3])(p, (char*)this + 0x6c);
        float q = Sub_f927c0(r);
        v = mParam2b4 + (t > q ? t : q);
    } else {
        v = 0.0f;
    }
    if (v != mMat30) {
        mMat24 = mMat28;
        mMat30 = v;
        *(char*)&mMat18 = 1;
    }
}

// @ 0x00f4fb80
void cTerrainTool::DragUpdate(float dt)
{
    if (mMode33c == 1) {
        if (mButtons320 & 0x40) {
            float v = mChanA.mTween - mParam29c * dt;
            v = v < mParam2ac ? mParam2ac : (v > mParam2b0 ? mParam2b0 : v);
            mTween290 = v;
            if (v != mChanA.mTween) {
                mChanA.mPrev = mChanA.mParamA;
                mChanA.mFlag = 1;
                mChanA.mTween = mTween290;
            }
        }
        if (mButtons320 & 0x100) {
            float v = mParam29c * dt + mChanA.mTween;
            v = v < mParam2ac ? mParam2ac : (v > mParam2b0 ? mParam2b0 : v);
            mTween290 = v;
            if (v != mChanA.mTween) {
                mChanA.mPrev = mChanA.mParamA;
                mChanA.mFlag = 1;
                mChanA.mTween = mTween290;
            }
        }
    } else if (mMode33c == 0) {
        if ((mButtons320 & 2) || (mButtons328 & 0x200)) {
            float v = mChanA.mTween - mParam29c * dt * 5.0f;
            v = v < mParam2ac ? mParam2ac : (v > mParam2b0 ? mParam2b0 : v);
            mTween290 = v;
            if (v != mChanA.mTween) {
                mChanA.mPrev = mChanA.mParamA;
                mChanA.mFlag = 1;
                mChanA.mTween = mTween290;
            }
        }
        if ((mButtons320 & 4) || (mButtons328 & 8)) {
            float v = mParam29c * dt * 5.0f + mChanA.mTween;
            v = v < mParam2ac ? mParam2ac : (v > mParam2b0 ? mParam2b0 : v);
            mTween290 = v;
            if (v != mChanA.mTween) {
                mChanA.mPrev = mChanA.mParamA;
                mChanA.mFlag = 1;
                mChanA.mTween = mTween290;
            }
        }
    }

    if (mDragFlag318 == 0)
        OnPointer(mBrushX348, mBrushY34c, 0);
    mDragFlag318 = 0;
}
