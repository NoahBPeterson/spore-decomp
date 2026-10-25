// Slice s00bc2570 (0x00bc2570..0x00bc3485) — SP::cTimeOfDay / SP::cSPTimer and
// the editor "green simulator" float helpers.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE

#include "types.h"

#pragma warning(disable: 4100)

#define SP_NOINLINE __declspec(noinline)

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);
extern "C" float  __cdecl sinf(float);
extern "C" float  __cdecl cosf(float);
extern "C" float  __cdecl tanf(float);
extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fmod(double, double);
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
struct Matrix3 {
    float m[9];
    void Assign(const float* src);      // 0x41cb40
};

struct Quat {
    float x, y, z, w;
};

extern "C" Matrix3* __cdecl SP_Matrix3FromQuaternion(Matrix3* out, const void* q);
extern "C" void*  __cdecl FUN_007dcb00(void* out, const void* a, const void* b);
extern "C" float  __cdecl FUN_0069b760(float* a, float* b, float* dir);
extern "C" char   __cdecl FUN_00bc2520(void* p);

extern Matrix3 g_identity;              // 0x168aa8c

struct cSPTransform {
    uint16_t mFlags;                    // +0x00
    uint16_t mModCount;                 // +0x02
    float    mTranslation[3];           // +0x04
    float    mScale;                    // +0x10
    Matrix3  mRotation;                 // +0x14
    cSPTransform& invert();             // 0x40efa0
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
SP_NOINLINE float FUN_00bc2570(float* a, float* b, float* dir)
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

    return FUN_0069b760(r1, r2, dir);
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
    cSPTransform xf;
    xf.mModCount = 0;
    xf.mFlags = 0;
    xf.mScale = 1.0f;
    xf.mRotation.Assign(g_identity.m);

    float* pos = (float*)(*(void* (__thiscall**)(cPlanet*))((char*)*(void**)p + 0x2c))(p);
    xf.mFlags |= 4;
    xf.mModCount++;
    xf.mTranslation[0] = pos[0];
    xf.mTranslation[1] = pos[1];
    xf.mTranslation[2] = pos[2];

    void* q = (*(void* (__thiscall**)(cPlanet*))((char*)*(void**)p + 0x30))(p);
    Matrix3 tmp;
    xf.mRotation = *SP_Matrix3FromQuaternion(&tmp, q);
    xf.mFlags |= 2;
    xf.mModCount++;
    xf.invert();

    ((float*)out)[0] = xf.mTranslation[0];
    ((float*)out)[1] = xf.mTranslation[1];
    ((float*)out)[2] = xf.mTranslation[2];
    return out;
}

// @ 0x00bc29c0 — normalized day fraction for a planet at its current angle.
float FUN_00bc29c0(void* a, cPlanet* p)
{
    float* axis = p->IsSomething() ? g_dir : (float*)p->GetRotationAxis();

    float local[3];
    FUN_00bc2900(local, p);
    float ang = FUN_00bc2570(local, (float*)a, axis);

    float r = fmod(ang, g_fullCircle);
    if (r > g_halfCircle)
        r -= g_fullCircle;
    else if (r < -g_halfCircle)
        r += g_fullCircle;
    float v = r / g_fullCircle + 0.5f;

    bool neg = axis[2] * g_dir[2] + axis[1] * g_dir[1] + axis[0] * g_dir[0] < 0.0f;
    if (p->IsSomething() || neg)
        return 1.0f - v;
    if (p->GetRotationAngle() <= *(float*)((char*)p->GetOrbit() + 0x20))
        return v;
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

    float* axis = p->IsSomething() ? g_dir : (float*)p->GetRotationAxis();
    bool neg = axis[1] * g_dir[1] + axis[0] * g_dir[0] + axis[2] * g_dir[2] < 0.0f;
    if (p->IsSomething() || neg ||
        p->GetRotationAngle() > *(float*)((char*)p->GetOrbit() + 0x20))
        frac = 1.0f - frac;

    float t = (frac - 0.5f) * g_fullCircle;

    float local[3];
    FUN_00bc2900(local, p);
    float proj = FUN_00bc2570(local, dir, axis);
    float ang = (t - proj) * 0.5f;

    Quat delta;
    float sn = sinf(ang);
    float cs = cosf(ang);
    delta.x = axis[0] * sn;
    delta.y = axis[1] * sn;
    delta.z = axis[2] * sn;
    delta.w = cs;

    void* cur = (*(void* (__thiscall**)(cPlanet*))((char*)*(void**)p + 0x30))(p);
    Quat res;
    FUN_007dcb00(&res, cur, &delta);
    float inv = 1.0f / (float)sqrt(res.x * res.x + res.y * res.y + res.z * res.z + res.w * res.w);
    Quat out;
    out.x = res.x * inv;
    out.y = res.y * inv;
    out.z = res.z * inv;
    out.w = res.w * inv;
    (*(void (__thiscall**)(cPlanet*, void*))((char*)*(void**)p + 0x3c))(p, &out);
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

// ---------------------------------------------------------------------------
// 0x00bc32a0: WriteTypedValue<signed char> (the XML typed-value writer template)
// ---------------------------------------------------------------------------
#include <string.h>

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);

namespace eastl {

class allocator { public:
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};

extern wchar_t gEmptyString16[2];   // 0x01667BAC
extern char    gEmptyString8[1];

template <typename T> struct EmptyStr;
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };

template <typename T>
inline size_t CharStrlen(const T* p) { const T* q = p; while (*q) ++q; return (size_t)(q - p); }
template <>
inline size_t CharStrlen<char>(const char* p) { return strlen(p); }

template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}

template <typename T, typename Allocator = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string(const basic_string& x);
    struct CtorDoNotInitialize {};
    basic_string(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string() { DeallocateSelf(); }

    basic_string& operator=(const basic_string& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string& assign(const T* pBegin, const T* pEnd);
    basic_string& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};

typedef basic_string<char> string;
typedef basic_string<wchar_t> string16;

} // namespace eastl

template <typename T, typename A>
eastl::basic_string<T, A>::basic_string(const eastl::basic_string<T, A>& x) : mpBegin(0), mpEnd(0), mpCapacity(0)
{
    RangeInitialize(x.mpBegin, x.mpEnd);
}
template eastl::basic_string<char>::basic_string(const eastl::basic_string<char>&);

namespace EA {
eastl::string16 ConvertToString16(const char* p, int length = -1);   // 0x0093C5A0
eastl::string16 ConvertToString16(const eastl::string& s);           // 0x0093C6D0
}

class IXmlWriter {
public:
    virtual bool BeginElement(const wchar_t* name) = 0;
    virtual bool EndElement(const wchar_t* name) = 0;
    virtual bool WriteAttribute(const wchar_t* name, const wchar_t* value) = 0;
    virtual bool WriteCharacters(const wchar_t* text) = 0;
};

template <typename T>
struct cTypedValueToStringT {
    static bool sbWriteType;
    static void Write(eastl::string& out, const T& value);
};

template <typename T>
bool WriteTypedValue(IXmlWriter* writer, const char* name, const T& value, const wchar_t* typeName)
{
    bool result = true;
    eastl::string str;
    cTypedValueToStringT<T>::Write(str, value);
    if (!str.empty()) {
        eastl::string16 name16(name ? EA::ConvertToString16(name) : eastl::string16());
        eastl::string16 text(EA::ConvertToString16(str));
        const wchar_t* element = name16.empty() ? typeName : name16.c_str();
        if (writer->BeginElement(element) &&
            (name16.empty() || !cTypedValueToStringT<T>::sbWriteType || writer->WriteAttribute(L"type", typeName)) &&
            writer->WriteCharacters(text.c_str()) &&
            writer->EndElement(element))
            result = true;
        else
            result = false;
    }
    return result;
}

// @ 0x00bc32a0  ??$WriteTypedValue@C
template bool WriteTypedValue<signed char>(IXmlWriter*, const char*, const signed char&, const wchar_t*);
