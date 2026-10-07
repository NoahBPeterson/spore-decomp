// Slice s0052d460: cSPSkinPaintClearCommand::Execute and small IO/string helpers.
#include "types.h"
#include <stdarg.h>

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------- cSPSkinPaintClearCommand::Execute
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char*, const char*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl isdigit(int);
extern "C" __declspec(dllimport) long __cdecl atol(const char*);

// EA 6-argument operator new (EASTL allocator form) and its matching delete (used only for ctor-throw cleanup).
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);   // 0x00f473a0
void operator delete(void* p, const char* name, int flags, unsigned debugFlags, const char* file, int line);

// Spore's runtime pi (a float global set at startup).
extern float g_SPPi;   // 0x015e0350
// Default hair angle (a runtime-initialized float global).
extern float g_SPHairAngleDefault;   // 0x015e0574

// SSE clamp helpers (the original is written with maxss/minss in inline asm).
inline float Clamp(float value, float minValue, float maxValue)
{
    __asm {
        movss xmm0, value
        maxss xmm0, minValue
        minss xmm0, maxValue
        movss value, xmm0
    }
    return value;
}
inline float Clamp01(float value)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, value
        minss xmm0, one
        movss value, xmm0
    }
    return value;
}

namespace rw { namespace math { namespace fpu {
template <class T, int N> struct Vector3Template
{
    T x, y, z;
    Vector3Template() {}
    Vector3Template(T x_, T y_, T z_) { x = x_; y = y_; z = z_; }
    T& operator[](int i) { return (&x)[i]; }
};
} } }
typedef rw::math::fpu::Vector3Template<float, 0> Vector3;

namespace EA {
namespace ArgScript {
class cArguments
{
public:
    const char** MainArguments(int count);                      // 0x00838320
    const char** OptionArguments(const char* name, int count);  // 0x00838330
};
// FormatParser: the parse helpers used here (slots from the Spore ModAPI FormatParser).
class cIParser
{
public:
#define PV(n) virtual void pv##n();
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
#undef PV
    virtual float ParseFloat(const char* s) const;          // +0x98
    virtual int ParseInt(const char* s) const;              // +0x9c
    virtual unsigned int ParseUInt(const char* s) const;    // +0xa0
    virtual void ParseVector2(const char* s) const;         // +0xa4
    virtual Vector3 ParseVector3(const char* s) const;      // +0xa8
    virtual void ParseVector4(const char* s) const;         // +0xac
    virtual Vector3 ParseColorRGB(const char* s) const;     // +0xb0
};
class cICommand
{
public:
    virtual void AddRef();
    virtual void Release();
    virtual void ParseLine(const cArguments& args);
    virtual void Execute(cArguments& args);
};
class cCommandBase : public cICommand
{
public:
    cIParser* mParser;   // +0x4
    int mRefCount;       // +0x8
};
class cError
{
public:
    cError(const char* fmt, ...);   // 0x0052df30
    cError(const cError& other);
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* mAllocator;
};
}
template <class T> class RefCountTemplate
{
public:
    RefCountTemplate() : mRefCount(0) {}
    virtual ~RefCountTemplate() {}
    T mRefCount;   // +0x4
    T AddRef() { return mRefCount++ + 1; }
    // Contains `delete this`, so cl declines to inline it (out-of-line copy at 0x00453540), but callers still
    // reserve its locals in their frame.
    T Release()   // 0x00453540
    {
        T r = mRefCount-- - 1;
        if (r)
            return r;
        mRefCount = 1;
        delete this;
        return 0;
    }
};
namespace Swarm {
class cDescription : public RefCountTemplate<int>
{
};
class cEffectsParser
{
public:
    // Looks the resource name up in the effects-parser resource table of the given kind (name guessed).
    unsigned __int64 GetResourceInstance(int kind, const char* name);                          // 0x00a6ec40
    void AddAnonDescription(ArgScript::cArguments& args, int type, cDescription* desc, int flags);   // 0x00a6fd40
};
}
template <class T> class AutoRefCount
{
public:
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* mpObject;
};
}

struct cSPSkinPaintClearDescription : public EA::Swarm::cDescription
{
    enum
    {
        kFlagDiffuse = 0, kFlagSpec = 1, kFlagBump = 2, kFlagExponent = 3, kFlagPartBumpScale = 4,
        kFlagPartSpecScale = 5, kFlagHair = 6, kFlagHairTex = 7, kFlagHairPrintGeom = 8, kFlagGloss = 9,
        kFlagPhong = 10, kFlagMax = 11
    };
    // Inline in the original too: cl declines to expand it here (an out-of-line copy is at 0x0052d160), but
    // Execute's frame still reserves its two inline Vector3-ctor slots.
    cSPSkinPaintClearDescription()   // 0x0052d160
        : mDiffuseUserColor(-1), mDiffuse(1.0f, 1.0f, 1.0f), mSpecBump(0.0f, 1.0f, 0.5f), mGlossFactor(0.5f),
          mPhongFactor(1.0f), mPartBumpScale(1.0f), mPartSpecScale(1.0f), mHairAngle(g_SPHairAngleDefault),
          mHairLength(0.0f), mHairWidth(0.03f), mHairTaper(1.0f), mHairCurl(0.0f), mHairWave(0.0f),
          mHairMessiness(0.0f), mHairDensity(1.0f), mHairFaceCamera(true), mHairTextureInstance(0),
          mHairPrintGeomInstance(0), mBitFlags(0)
    {
    }
    int mDiffuseUserColor;                     // +0x8
    Vector3 mDiffuse;                          // +0xc
    Vector3 mSpecBump;                         // +0x18 (spec, exponent, bump)
    float mGlossFactor;                        // +0x24
    float mPhongFactor;                        // +0x28
    float mPartBumpScale;                      // +0x2c
    float mPartSpecScale;                      // +0x30
    float mHairAngle;                          // +0x34
    float mHairLength;                         // +0x38
    float mHairWidth;                          // +0x3c
    float mHairTaper;                          // +0x40
    float mHairCurl;                           // +0x44
    float mHairWave;                           // +0x48
    float mHairMessiness;                      // +0x4c
    float mHairDensity;                        // +0x50
    bool mHairFaceCamera;                      // +0x54
    unsigned __int64 mHairTextureInstance;     // +0x58
    unsigned __int64 mHairPrintGeomInstance;   // +0x60
    unsigned int mBitFlags;                    // +0x68
};

namespace {
class cSPSkinPaintClearCommand : public EA::ArgScript::cCommandBase
{
public:
    EA::Swarm::cEffectsParser* mState;   // +0xc
    virtual void Execute(EA::ArgScript::cArguments& args);
};

// @ 0x0052d460
// skinpaintClear [-rgb|-diffuse colorN|<color>] [-specBump <v3>] [-spec f] [-bump f] [-specExp|-exponent f]
//                [-gloss f] [-phong f] [-partBumpScale f] [-partSpecScale f] [-hair 9 values]
//                [-hairTexture name] [-hairPrintGeom name]
void cSPSkinPaintClearCommand::Execute(EA::ArgScript::cArguments& args)
{
    const char** optArgs = args.MainArguments(0);
    bool hasBump = false;
    bool hasSpec = false;
    EA::AutoRefCount<cSPSkinPaintClearDescription> desc =
        new ("Skinner/Clear", 0, 0, 0, 0) cSPSkinPaintClearDescription();

    if ((optArgs = args.OptionArguments("rgb", 1)) != 0 || (optArgs = args.OptionArguments("diffuse", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagDiffuse;
        if (_strnicmp(optArgs[0], "color", 5) == 0 && isdigit((unsigned char)optArgs[0][5]))
        {
            int n = atol(optArgs[0] + 5) - 1;
            if (n < 0 || n >= 3)
                throw EA::ArgScript::cError("unknown paint color '%s'", optArgs[0]);
            desc->mDiffuseUserColor = n;
        }
        else
        {
            desc->mDiffuseUserColor = -1;
            desc->mDiffuse = mParser->ParseColorRGB(optArgs[0]);
        }
    }
    if ((optArgs = args.OptionArguments("specBump", 1)) != 0)
    {
        desc->mBitFlags |= (1 << cSPSkinPaintClearDescription::kFlagSpec) | (1 << cSPSkinPaintClearDescription::kFlagBump) | (1 << cSPSkinPaintClearDescription::kFlagExponent);
        desc->mSpecBump = mParser->ParseVector3(optArgs[0]);
        desc->mSpecBump[1] = Clamp(desc->mSpecBump[1] * 255.0f, 1.0f, 60.0f) / 60.0f;
    }
    if ((optArgs = args.OptionArguments("spec", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagSpec;
        desc->mSpecBump[0] = Clamp01(mParser->ParseFloat(optArgs[0]));
        hasSpec = true;
    }
    if ((optArgs = args.OptionArguments("bump", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagBump;
        desc->mSpecBump[2] = Clamp01(mParser->ParseFloat(optArgs[0]));
        hasBump = true;
    }
    if ((optArgs = args.OptionArguments("specExp", 1)) != 0 || (optArgs = args.OptionArguments("exponent", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagExponent;
        desc->mSpecBump[1] = Clamp(mParser->ParseFloat(optArgs[0]), 1.0f, 60.0f) / 60.0f;
    }
    if ((optArgs = args.OptionArguments("gloss", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagGloss;
        desc->mGlossFactor = mParser->ParseFloat(optArgs[0]);
    }
    if ((optArgs = args.OptionArguments("phong", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagPhong;
        desc->mPhongFactor = mParser->ParseFloat(optArgs[0]);
    }
    if ((optArgs = args.OptionArguments("partBumpScale", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagPartBumpScale;
        desc->mPartBumpScale = mParser->ParseFloat(optArgs[0]);
    }
    if ((optArgs = args.OptionArguments("partSpecScale", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagPartSpecScale;
        desc->mPartSpecScale = mParser->ParseFloat(optArgs[0]);
    }
    if ((optArgs = args.OptionArguments("hair", 9)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagHair;
        desc->mHairLength = mParser->ParseFloat(optArgs[0]);
        desc->mHairAngle = mParser->ParseFloat(optArgs[1]) * (g_SPPi / 180.0f);
        desc->mHairWidth = mParser->ParseFloat(optArgs[2]);
        desc->mHairTaper = mParser->ParseFloat(optArgs[3]);
        desc->mHairCurl = mParser->ParseFloat(optArgs[4]);
        desc->mHairWave = mParser->ParseFloat(optArgs[5]);
        desc->mHairMessiness = mParser->ParseFloat(optArgs[6]);
        desc->mHairDensity = mParser->ParseFloat(optArgs[7]);
        if (mParser->ParseInt(optArgs[8]) == 0)
            desc->mHairFaceCamera = false;
        else
            desc->mHairFaceCamera = true;
    }
    if ((optArgs = args.OptionArguments("hairTexture", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagHairTex;
        desc->mHairTextureInstance = mState->GetResourceInstance(0, optArgs[0]);
    }
    if ((optArgs = args.OptionArguments("hairPrintGeom", 1)) != 0)
    {
        desc->mBitFlags |= 1 << cSPSkinPaintClearDescription::kFlagHairPrintGeom;
        desc->mHairPrintGeomInstance = mState->GetResourceInstance(2, optArgs[0]);
    }
    if (desc->mBitFlags == 0)
        throw EA::ArgScript::cError("must specify at least one option");
    if (hasBump != hasSpec)
        throw EA::ArgScript::cError("must clear bump and spec channels simultaneously");
    mState->AddAnonDescription(args, 0x22, desc, 0);
}
}

// ---------------------------------------------------------------- error string builder
extern uint8_t DAT_015dfa30[0x800];
extern void*   DAT_01667bac;
int  Vsnprintf8(char* buf, uint32_t n, const char* fmt, ...);          // 0x00938400
void EastlStringAssign(void* str, const char* first, const char* last); // 0x00454cb0

// @ 0x0052df30  cError/cError(const char* fmt, ...)
int* ErrorStringCtor(int* out, const char* fmt, ...)
{
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[0] = (int)&DAT_01667bac;
    out[1] = out[0];
    out[2] = out[0] + 1;
    va_list ap;
    va_start(ap, fmt);
    Vsnprintf8((char*)DAT_015dfa30, 0x800, fmt, ap);
    va_end(ap);
    char* p = (char*)DAT_015dfa30;
    while (*p)
        p++;
    EastlStringAssign(out, (const char*)DAT_015dfa30, p);
    return out;
}

// @ 0x0052dfe0  vector range constructor (3 words zeroed, then assign [first,last))
struct SVec3 {
    void* p0;
    void* p1;
    void* p2;
    void RangeAssign(void* first, void* last);   // 0x0047d390
    SVec3(void** range);                          // 0x0052dfe0
};
SVec3::SVec3(void** range)
{
    p0 = 0;
    p1 = 0;
    p2 = 0;
    RangeAssign(range[0], range[1]);
}

// ---------------------------------------------------------------- IO read
int  ReadInt32(void* self, void* dst, int count, int flags);   // EA::IO::ReadInt32
void FUN_0093ac80(void* self, void* dst);                      // 0x0093ac80
void FUN_0093a800(void* self, void* dst, int count, int flags); // 0x0093a800

struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(int*, int);   // +0x30
};

// @ 0x0052e030
void ReadSkinPaintData(IStream* self, int version, int data)
{
    ReadInt32(self, (void*)(data + 8), 1, 0);
    self->v12((int*)(data + 0xc), 0xc);
    self->v12((int*)(data + 0x18), 0xc);
    if (version >= 2)
        ReadInt32(self, (void*)(data + 0x24), 1, 0);
    if (version >= 3)
        ReadInt32(self, (void*)(data + 0x28), 1, 0);
    ReadInt32(self, (void*)(data + 0x2c), 1, 0);
    ReadInt32(self, (void*)(data + 0x30), 1, 0);
    ReadInt32(self, (void*)(data + 0x34), 1, 0);
    ReadInt32(self, (void*)(data + 0x38), 1, 0);
    ReadInt32(self, (void*)(data + 0x3c), 1, 0);
    ReadInt32(self, (void*)(data + 0x40), 1, 0);
    ReadInt32(self, (void*)(data + 0x44), 1, 0);
    ReadInt32(self, (void*)(data + 0x48), 1, 0);
    ReadInt32(self, (void*)(data + 0x4c), 1, 0);
    ReadInt32(self, (void*)(data + 0x50), 1, 0);
    FUN_0093ac80(self, (void*)(data + 0x54));
    FUN_0093a800(self, (void*)(data + 0x58), 1, 0);
    FUN_0093a800(self, (void*)(data + 0x60), 1, 0);
    ReadInt32(self, (void*)(data + 0x68), 1, 0);
}
