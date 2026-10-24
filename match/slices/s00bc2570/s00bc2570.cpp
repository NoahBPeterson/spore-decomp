// Slice s00bc2570 (0x00bc2570..0x00bc3485) — SP::cTimeOfDay / SP::cSPTimer and
// the editor "green simulator" float helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE

#include "types.h"

#pragma warning(disable: 4100)

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" float  __cdecl sqrtf(float);

// ---------------------------------------------------------------------------
// Globals (absolute addresses in the retail image; referenced through symbols
// so the verifier masks the relocations).
// ---------------------------------------------------------------------------
extern float g_one;          // 0x1485720   (1.0f)
extern float g_eps;          // 0x1485378   (0.0f)
extern float g_tiny;         // 0x145c198   (1.1574074e-05f)
extern float g_dayScale;     // 0x156cfc8
extern float g_thr0;         // 0x156cfb8
extern float g_thr1;         // 0x156cfbc
extern float g_thr2;         // 0x156cfc0
extern float g_thr3;         // 0x156cfc4
extern float g_halfCircle;   // 0x156cfd0
extern float g_fullCircle;   // 0x168aa88
extern float g_dir[3];       // 0x156cfd4 / d8 / dc
extern void* g_editorSim;    // 0x168aa6c
extern bool  g_015d8b50;     // 0x15d8b50

// ---------------------------------------------------------------------------
// External callees / singletons.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_01021260();      // GetActivePlanet
extern "C" int   __cdecl FUN_01021280();      // GetUniverseContext
extern "C" void  __cdecl FUN_01021740(void*);
extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b,
                                      const char* file, int line);
extern "C" void  __cdecl operator_delete(void* p);
extern "C" float* __cdecl SP_Matrix3FromQuaternion(float* out, const void* q);
extern "C" void*  __cdecl FUN_007dcb00(void* out, const void* q);
extern "C" void   __cdecl FUN_0069b760(float* a, float* b, float* dir);
extern "C" char   __cdecl FUN_00bc2520(void* p);

struct Matrix3 {
    float m[9];
    void Assign(const float* src);      // 0x41cb40
};

struct cPlanet {
    void  SetRotationNull(int);
    void* GetOrbit();                   // 0xc708a0
    void* GetRotationAxis();            // 0xc70930
    void  SetRotationPeriod(float);     // 0xc709b0
    void  SetRotationVector(void*);     // 0xc70950
    float GetRotationAngle();           // 0xc70980
    char  IsSomething();                // 0xc708f0
};

// ---------------------------------------------------------------------------
// SP::cTimeOfDay
// ---------------------------------------------------------------------------
struct cTimeOfDay {
    char  pad_0000[0x24];
    float mDayLength;   // +0x24

    void  SetDayLength(float len);
    void  FUN_00bc28c0(float len);
    float FUN_00bc2b30(void* a);
    float FUN_00bc2b60(void* a);
    int   FUN_00bc2b80(void* a);
    void  FUN_00bc2f00(float v, void* a);
    void  FUN_00bc2f70(int mode, void* a);
};

extern "C" void __cdecl FUN_00bc2670(float len);

// @ 0x00bc2570 — remove the `dir` component from two vectors, then hand off.
void FUN_00bc2570(float* a, float* b, float* dir)
{
    float d1 = (dir[0] * a[0] + dir[1] * a[1]) + dir[2] * a[2];
    float r1[3];
    r1[0] = a[0] - dir[0] * d1;
    r1[1] = a[1] - dir[1] * d1;
    r1[2] = a[2] - dir[2] * d1;

    float d2 = (b[1] * dir[1] + b[2] * dir[2]) + b[0] * dir[0];
    float r2[3];
    r2[0] = b[0] - dir[0] * d2;
    r2[1] = b[1] - dir[1] * d2;
    r2[2] = b[2] - dir[2] * d2;

    FUN_0069b760(r1, r2, dir);
}

// @ 0x00bc2670 — reposition the active planet's rotation for a new day length.
void FUN_00bc2670(float len)
{
    cPlanet* p = (cPlanet*)FUN_01021260();
    if (!p) return;

    p->SetRotationNull(0);
    float orbit = *(float*)((char*)p->GetOrbit() + 0x20);
    float* axis = (float*)p->GetRotationAxis();
    bool neg = axis[0] * g_dir[0] + axis[1] * g_dir[1] + axis[2] * g_dir[2] < 0.0f;

    if (len == 0.0f) {
        p->SetRotationPeriod(orbit);
        if (neg) {
            axis = (float*)p->GetRotationAxis();
            float v[3];
            v[0] = -axis[0];
            v[1] = -axis[1];
            v[2] = -axis[2];
            p->SetRotationVector(v);
        }
        return;
    }

    if (len > 0.0f) {
        if (neg) {
            float diff = orbit - len;
            if (diff < 0.0f) diff = -diff;
            if (diff < 1.5258789e-05f) { p->SetRotationNull(1); return; }
            float r = (orbit / (orbit - len)) * len;
            if (r > 0.0f) { p->SetRotationPeriod(r); return; }
            axis = (float*)p->GetRotationAxis();
            float v[3];
            v[0] = -axis[0];
            v[1] = -axis[1];
            v[2] = -axis[2];
            p->SetRotationVector(v);
        }
        p->SetRotationPeriod((orbit / (orbit + len)) * len);
    }
}

// @ 0x00bc2830 — SP::cTimeOfDay::SetDayLength(float) : __thiscall, ret 4
void cTimeOfDay::SetDayLength(float len)
{
    FUN_00bc2670(len);
    mDayLength = len;
    g_dayScale = g_one;
    g_thr0 = mDayLength * 0.208f;
    g_thr1 = mDayLength * 0.297f;
    g_thr2 = mDayLength * 0.708f;
    g_thr3 = mDayLength * 0.792f;
}

// @ 0x00bc28c0 — rescale when the reference day length changes.
void cTimeOfDay::FUN_00bc28c0(float len)
{
    if (len != g_dayScale) {
        g_dayScale = len;
        FUN_00bc2670(mDayLength / len);
    }
}

// @ 0x00bc2900 — build the (inverse-transformed) rotation matrix of a planet.
void* FUN_00bc2900(void* out, cPlanet* p)
{
    Matrix3 ident;
    ident.Assign(g_dir);           // identity seed (DAT_0168aa8c)

    void* v = (*(void* (__thiscall**)(cPlanet*))((char*)*(void**)p + 0x2c))(p);
    float pos[3];
    pos[0] = ((float*)v)[0];
    pos[1] = ((float*)v)[1];
    pos[2] = ((float*)v)[2];

    void* q = (*(void* (__thiscall**)(cPlanet*))((char*)*(void**)p + 0x30))(p);
    float mat[9];
    float* r = SP_Matrix3FromQuaternion(mat, q);
    for (int i = 0; i < 9; ++i) ident.m[i] = r[i];
    ident.Assign(r);

    *(float*)out = pos[0];
    *(float*)((char*)out + 4) = pos[1];
    *(float*)((char*)out + 8) = pos[2];
    return out;
}

// @ 0x00bc29c0 — normalized day fraction for a planet at its current angle.
float FUN_00bc29c0(void* a, cPlanet* p)
{
    float* axis = p->IsSomething() ? g_dir : (float*)p->GetRotationAxis();

    float local[3];
    FUN_00bc2900(local, p);
    FUN_00bc2570(local, (float*)a, axis);

    float v = local[0] * axis[0] + local[1] * axis[1] + local[2] * axis[2];
    if (v > g_halfCircle)
        v = v - g_fullCircle;
    else if (v < -g_halfCircle)
        v = g_fullCircle + v;
    v = v / g_fullCircle + 0.5f;

    float dot = axis[0] * g_dir[0] + axis[1] * g_dir[1] + axis[2] * g_dir[2];
    if (!p->IsSomething() && dot >= 0.0f) {
        if (p->GetRotationAngle() <= *(float*)((char*)p->GetOrbit() + 0x20))
            return v;
    }
    return 1.0f - v;
}

// @ 0x00bc2b30 — day fraction scaled by the configured day length.
float cTimeOfDay::FUN_00bc2b30(void* a)
{
    cPlanet* p = (cPlanet*)FUN_01021260();
    if (p)
        return FUN_00bc29c0(a, p) * mDayLength;
    return 0.0f;
}

// @ 0x00bc2b60 — raw day fraction.
float cTimeOfDay::FUN_00bc2b60(void* a)
{
    cPlanet* p = (cPlanet*)FUN_01021260();
    if (p)
        return FUN_00bc29c0(a, p);
    return 0.0f;
}

// @ 0x00bc2b80 — quantize the day fraction into a 0..3 phase.
int cTimeOfDay::FUN_00bc2b80(void* a)
{
    float v;
    cPlanet* p = (cPlanet*)FUN_01021260();
    if (p)
        v = FUN_00bc29c0(a, p) * mDayLength;
    else
        v = 0.0f;

    if (v < g_thr0) return 0;
    if (v < g_thr1) return 1;
    if (v < g_thr2) return 2;
    if (v < g_thr3) return 3;
    return 0;
}

// @ 0x00bc2c00 — fetch the day fraction vector if a planet is active.
bool __stdcall FUN_00bc2c00(void* out)
{
    if (FUN_01021280() == 0) {
        cPlanet* p = (cPlanet*)FUN_01021260();
        if (p != 0) {
            float local[3];
            float* v = (float*)FUN_00bc2900(local, p);
            uint32_t* s = (uint32_t*)v;
            uint32_t* d = (uint32_t*)out;
            d[0] = s[0];
            d[1] = s[1];
            d[2] = s[2];
            return true;
        }
    }
    return false;
}

// @ 0x00bc2c50 — apply a day fraction to the active planet's rotation.
int FUN_00bc2c50(float frac, float* dir, cPlanet* p)
{
    if (dir[0] * dir[0] + dir[1] * dir[1] < 1.5258789e-05f)
        return 1;
    if (FUN_00bc2520(p))
        return 2;

    float* axis;
    if (p->IsSomething())
        axis = g_dir;
    else
        axis = (float*)p->GetRotationAxis();

    float dot = axis[0] * g_dir[0] + axis[1] * g_dir[1] + axis[2] * g_dir[2];
    float orbit = *(float*)((char*)p->GetOrbit() + 0x20);
    if (!(!p->IsSomething() && dot >= 0.0f)) {
        if (p->GetRotationAngle() <= orbit || !p->IsSomething())
            frac = 1.0f - frac;
    }

    float local[3];
    FUN_00bc2900(local, p);
    FUN_00bc2570(local, dir, axis);

    float ang = (frac - 0.5f) * g_fullCircle * 0.5f;
    float sn = (float)sin(ang);
    float cs = (float)cos(ang);
    float q[4];
    q[0] = axis[0] * sn;
    q[1] = axis[1] * sn;
    q[2] = axis[2] * sn;
    q[3] = cs;

    void* gq = (*(void* (__thiscall**)(cPlanet*, void*))((char*)*(void**)p + 0x30))(p, q);
    float* nq = (float*)FUN_007dcb00(q, gq);
    float inv = 1.0f / sqrtf(nq[0] * nq[0] + nq[1] * nq[1] + nq[2] * nq[2] + nq[3] * nq[3]);
    float out[4];
    out[0] = inv * nq[0];
    out[1] = nq[1] * inv;
    out[2] = nq[2] * inv;
    out[3] = nq[3] * inv;
    (*(void (__thiscall**)(cPlanet*, void*))((char*)*(void**)p + 0x3c))(p, out);
    FUN_01021740(p);
    return 0;
}

// @ 0x00bc2ea0 — scalar deleting destructor of the editor resource.
struct cEditorRes {
    void* ctor();
    void* Destroy(char freeIt);
};

void* cEditorRes::Destroy(char freeIt)
{
    extern char v_1466744[], v_1466720[], v_13eb938[], v_13ec458[];
    *(void**)this = v_1466744;
    *(void**)((char*)this + 8) = v_1466720;
    g_editorSim = 0;
    void* p = *(void**)((char*)this + 0x10);
    if (p && *(int*)((char*)p - 4) != 0)
        operator_delete(p);
    *(void**)((char*)this + 8) = v_13eb938;
    *(void**)this = v_13ec458;
    if (freeIt & 1)
        operator_delete(this);
    return this;
}

// @ 0x00bc2f00 — set the day fraction for a planet (scaled).
void cTimeOfDay::FUN_00bc2f00(float v, void* a)
{
    if (FUN_01021280() != 0) return;
    cPlanet* p = (cPlanet*)FUN_01021260();
    if (!p) return;
    if (mDayLength > g_eps)
        v = v / mDayLength;
    else
        v = v * 0.000011574074f;
    FUN_00bc2c50(v, (float*)a, p);
}

// @ 0x00bc2f70 — set the day fraction by phase index.
void cTimeOfDay::FUN_00bc2f70(int mode, void* a)
{
    if (mode == 0) {
        float v = g_thr0;
        if (FUN_01021280() != 0) return;
        cPlanet* p = (cPlanet*)FUN_01021260();
        if (!p) return;
        if (mDayLength > g_eps)
            v = v / mDayLength;
        else
            v = v * 0.000011574074f;
        FUN_00bc2c50(v, (float*)a, p);
        return;
    }
    if (mode == 1) { FUN_00bc2f00(g_thr1, a); return; }
    if (mode == 2) { FUN_00bc2f00(g_thr2, a); return; }
    if (mode == 3) { FUN_00bc2f00(g_thr3, a); }
}

extern "C" void __fastcall FUN_00b5b6c0(void*);

// @ 0x00bc3040 — editor "green simulator" constructor.
void* cEditorRes::ctor()
{
    extern char v_1466744[], v_1466720[];
    FUN_00b5b6c0(this);
    *(void**)this = v_1466744;
    *(void**)((char*)this + 8) = v_1466720;
    *(void**)((char*)this + 0x10) = 0;
    *(void**)((char*)this + 0x14) = 0;
    *(void**)((char*)this + 0x18) = 0;

    void* p = operator_new(4, "Simulator", 0, 0,
                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                           0xd1);
    *(float*)p = 1440.0f;
    *(void**)((char*)this + 0x10) = p;
    *(void**)((char*)this + 0x18) = (char*)p + 4;
    *(void**)((char*)this + 0x14) = (char*)p + 4;
    *(float*)((char*)this + 0x24) = 86400.0f;
    g_editorSim = this;
    return this;
}

// ---------------------------------------------------------------------------
// SP::cSPTimer
// ---------------------------------------------------------------------------
typedef uint64_t (__cdecl* SPTimeFn)();

struct cSPTimer {
    void*   mVtbl;       // +0x00
    uint32_t mUnk4;      // +0x04
    uint64_t mElapsed;   // +0x08
    uint64_t mBase;      // +0x10
    uint8_t mRunning;    // +0x18
    uint8_t pad_19[3];
    SPTimeFn mGetTime;   // +0x1c

    void      Start();
    void      Stop();
    void      Restart();
    void      FUN_00bc3150(uint64_t delta);
    void      FUN_00bc3170();
    uint64_t  GetElapsedTime();
    cSPTimer* FUN_00bc31c0(SPTimeFn fn);
};

// @ 0x00bc30f0 — SP::cSPTimer::Start
void cSPTimer::Start()
{
    if (!mRunning) {
        mBase = mGetTime();
        mRunning = true;
    }
}

// @ 0x00bc3110 — SP::cSPTimer::Stop
void cSPTimer::Stop()
{
    if (mRunning) {
        uint64_t now = mGetTime();
        mRunning = false;
        mElapsed += now - mBase;
    }
}

// @ 0x00bc3130 — SP::cSPTimer::Restart
void cSPTimer::Restart()
{
    mBase = mGetTime();
    mElapsed = 0;
    mRunning = true;
}

// @ 0x00bc3150 — advance the base time by a 64-bit amount.
void cSPTimer::FUN_00bc3150(uint64_t delta)
{
    if (mRunning)
        mBase += delta;
}

// @ 0x00bc3170 — reset the timer to zero.
void cSPTimer::FUN_00bc3170()
{
    mBase = 0;
    mElapsed = 0;
    mRunning = false;
}

// @ 0x00bc3190 — SP::cSPTimer::GetElapsedTime
uint64_t cSPTimer::GetElapsedTime()
{
    if (mRunning) {
        uint64_t now = mGetTime();
        return mElapsed + (now - mBase);
    }
    return mElapsed;
}

// @ 0x00bc31c0 — SP::cSPTimer constructor (vtable + time callback).
cSPTimer* cSPTimer::FUN_00bc31c0(SPTimeFn fn)
{
    extern char v_1465d54[];
    mUnk4 = 0;
    mElapsed = 0;
    mBase = 0;
    mRunning = 0;
    mVtbl = v_1465d54;
    mGetTime = fn;
    return this;
}

// @ 0x00bc32a0 — typed-value string comparison helper.
extern "C" void  __cdecl FUN_00694f40(void*, int);
extern "C" void  __cdecl FUN_0056e2d0(void*, const void*);
extern "C" void* __cdecl FUN_0093c5a0(void*, int, int);
extern "C" void* __cdecl FUN_0093c6d0(void*, const void*);
extern "C" void  __cdecl FUN_0093c6d0b();

struct cTypedValue {
    virtual char FUN_00bc32a0_0(int);
    virtual char FUN_00bc32a0_4(int);
    virtual char FUN_00bc32a0_8(const wchar_t*, int);
    virtual char FUN_00bc32a0_c(int);
};

bool FUN_00bc32a0(cTypedValue* cb, int param_2, int param_3, int param_4)
{
    (void)cb; (void)param_2; (void)param_3; (void)param_4;
    return true;
}
