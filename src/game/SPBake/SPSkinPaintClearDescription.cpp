// src/game/SPBake/SPSkinPaintClearDescription.cpp -- migrated from slice(s) s0052d460, s0052e1f0, s0052c230 by tools/migrate/rewrite.py
// Object file: SPBake/SPSkinPaintClearDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cIBlockCommand.h"
#include "EA/ArgScript/cICommand.h"
#include <stdarg.h>

// unnamed retail callees and globals (address in the comment)
extern float kDefaultHairAngle;     // 0x015e0574

// ---- items of slice s0052c230 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char* kSPSkinPaintClearName;       // "spSkinPaintClear"
extern const char* kSPSkinPaintSettingsName;    // "spSkinPaintSettings"
inline void* operator new(unsigned int, void* p) { return p; }
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
struct Vector3 {    // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
};
namespace EA {
struct RefCountTemplateInt {        // EA::RefCountTemplate<int>
    virtual ~RefCountTemplateInt();
    int mRefCount;                  // +0x04
    RefCountTemplateInt() : mRefCount(0) {}
};
}
namespace EA {
namespace Swarm {
class cDescription_s0052_c230 : public RefCountTemplateInt { public:
    cDescription_s0052_c230() {}
    virtual ~cDescription_s0052_c230();
};  // namespace Swarm
}
}
struct cSPSkinPaintClearDescription : EA::Swarm::cDescription_s0052_c230 {   // 0x70
    int mDiffuseUserColor;          // +0x08
    Vector3 mDiffuse;               // +0x0c
    Vector3 mSpecBump;              // +0x18
    float mGlossFactor;             // +0x24
    float mPhongFactor;             // +0x28
    float mPartBumpScale;           // +0x2c
    float mPartSpecScale;           // +0x30
    float mHairAngle;               // +0x34
    float mHairLength;              // +0x38
    float mHairWidth;               // +0x3c
    float mHairTaper;               // +0x40
    float mHairCurl;                // +0x44
    float mHairWave;                // +0x48
    float mHairMessiness;           // +0x4c
    float mHairDensity;             // +0x50
    bool mHairFaceCamera;           // +0x54
    uint64_t mHairTextureInstance;  // +0x58
    uint64_t mHairPrintGeomInstance;// +0x60
    uint32_t mBitFlags;             // +0x68
    uint32_t pad6c;
    cSPSkinPaintClearDescription();
    virtual ~cSPSkinPaintClearDescription();
};
struct IStream;
void ReadClearDescription(IStream* stream, int version, cSPSkinPaintClearDescription* params);    // 0x0052e030
void WriteClearDescription(IStream* stream, cSPSkinPaintClearDescription* params);                 // 0x0052e1f0
namespace ArgScript {
struct cIParser;
}
namespace ArgScript {
struct cICommand {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
}
namespace ArgScript {
struct cCommandBase : cICommand {
    cIParser* mParser;
    int mRefCount;
    cCommandBase();                 // 0x0083c800
};
}
namespace ArgScript {
struct cFormatParser {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void AddParser(const char* name, cICommand* command);   // +0x18
};
}
struct cCommandStateT_cEffectsParser : ArgScript::cCommandBase {
    cCommandStateT_cEffectsParser() {}
    virtual void AddRef();
};
struct cCommandT_cEffectsParser : cCommandStateT_cEffectsParser {
    cCommandT_cEffectsParser() {}
    virtual void AddRef();
};
struct cSPSkinPaintClearCommand : cCommandT_cEffectsParser {
    uint32_t pad0c;
    cSPSkinPaintClearCommand() {}
    virtual void ParseLine();
};
// ---- items of slice s0052c230 end

// ---- items of slice s0052e1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace math {
namespace fpu {
template <typename T, int N> class Vector3Template_s0052_e1f0 { public:
    T x, y, z;
    T& operator[](int i) { return (&x)[i]; }
};
}
}
}
typedef rw::math::fpu::Vector3Template_s0052_e1f0<float, 0> Vector3_s0052_e1f0;
namespace EA {
template <typename T> class RefCountTemplate_s0052_e1f0 { public:
    RefCountTemplate_s0052_e1f0() : mRefCount(0) {}
    ~RefCountTemplate_s0052_e1f0() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};
}
namespace EA {
template struct RefCountTemplate_s0052_e1f0<int>;
}
namespace EA {
namespace IO {
 struct IStream_s0052_e1f0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual bool Write(const void* data, uint32_t size);     // +0x38
};
}
}
namespace EA {
namespace IO {
bool WriteUint32(IStream_s0052_e1f0* s, const uint32_t* v, uint32_t count, int endian);   // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool WriteUint64(IStream_s0052_e1f0* s, const uint64_t* v, uint32_t count, int endian);   // 0x0093ab10
}
}
namespace EA {
namespace IO {
bool WriteBool8(IStream_s0052_e1f0* s, const bool* v, uint32_t count);                    // 0x0093a9a0
}
}
namespace EA {
namespace Swarm {
class cDescription_s0052_e1f0 : public RefCountTemplate_s0052_e1f0<int> { public:
    cDescription_s0052_e1f0() {}
};
}
}
using EA::IO::IStream_s0052_e1f0;
inline bool WriteValue32(IStream_s0052_e1f0* s, uint32_t value) { return EA::IO::WriteUint32(s, &value, 1, 0); }
inline bool Write(IStream_s0052_e1f0* s, uint32_t value) { return WriteValue32(s, value); }
inline bool Write(IStream_s0052_e1f0* s, int value) { return WriteValue32(s, (uint32_t)value); }
inline bool WriteFloat32(IStream_s0052_e1f0* s, float value) { return EA::IO::WriteUint32(s, (uint32_t*)&value, 1, 0); }
inline bool Write(IStream_s0052_e1f0* s, float value) { return WriteFloat32(s, value); }
inline bool WriteValue64(IStream_s0052_e1f0* s, uint64_t value) { return EA::IO::WriteUint64(s, &value, 1, 0); }
inline bool Write(IStream_s0052_e1f0* s, uint64_t value) { return WriteValue64(s, value); }
inline bool WriteBool(IStream_s0052_e1f0* s, uint8_t value) { return EA::IO::WriteBool8(s, (const bool*)&value, 1); }
inline bool Write(IStream_s0052_e1f0* s, bool value) { return WriteBool(s, value ? 1 : 0); }
struct cSPSkinPaintClearDescription_s0052_e1f0 : EA::Swarm::cDescription_s0052_e1f0 {   // 0x70
    int mDiffuseUserColor;          // +0x08
    Vector3_s0052_e1f0 mDiffuse;               // +0x0c
    Vector3_s0052_e1f0 mSpecBump;              // +0x18
    float mGlossFactor;             // +0x24
    float mPhongFactor;             // +0x28
    float mPartBumpScale;           // +0x2c
    float mPartSpecScale;           // +0x30
    float mHairAngle;               // +0x34
    float mHairLength;              // +0x38
    float mHairWidth;               // +0x3c
    float mHairTaper;               // +0x40
    float mHairCurl;                // +0x44
    float mHairWave;                // +0x48
    float mHairMessiness;           // +0x4c
    float mHairDensity;             // +0x50
    bool mHairFaceCamera;           // +0x54
    uint64_t mHairTextureInstance;  // +0x58
    uint64_t mHairPrintGeomInstance;// +0x60
    uint32_t mBitFlags;             // +0x68
};
// ---- items of slice s0052e1f0 end

// ---- items of slice s0052d460 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint8_t DAT_015dfa30[0x800];
extern void*   DAT_01667bac;
int  Vsnprintf8(char* buf, uint32_t n, const char* fmt, ...);          // 0x00938400
struct EastlString {
    void Assign(const char* first, const char* last);                  // 0x00454cb0
};
int  ReadInt32(void* self, void* dst, int count, int flags);   // EA::IO::ReadInt32
void FUN_0093ac80(void* self, void* dst);                      // 0x0093ac80
void FUN_0093a800(void* self, void* dst, int count, int flags); // 0x0093a800
struct IStream_s0052_d460 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
    virtual void v12(int*, int);   // +0x30
};
// ---- items of slice s0052d460 end

// @ 0x0052d160
inline cSPSkinPaintClearDescription::cSPSkinPaintClearDescription()
: mDiffuseUserColor(-1), mDiffuse(1.0f, 1.0f, 1.0f), mSpecBump(0.0f, 1.0f, 0.5f), mGlossFactor(0.5f),
      mPhongFactor(1.0f), mPartBumpScale(1.0f), mPartSpecScale(1.0f), mHairAngle(kDefaultHairAngle),
      mHairLength(0.0f), mHairWidth(0.03f), mHairTaper(1.0f), mHairCurl(0.0f), mHairWave(0.0f),
      mHairMessiness(0.0f), mHairDensity(1.0f), mHairFaceCamera(true), mHairTextureInstance(0),
      mHairPrintGeomInstance(0), mBitFlags(0)
{
}

// @ 0x0052d310
void WriteClearDescriptionCommand(cSPSkinPaintClearDescription* params, IStream* stream)
{
    WriteClearDescription(stream, params);
}

// @ 0x0052df30
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
    ((EastlString*)out)->Assign((const char*)DAT_015dfa30, p);
    return out;
}

// @ 0x0052e030
void ReadSkinPaintData(IStream_s0052_d460* self, int version, int data)
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

// @ 0x0052e1f0
void WriteClearDescription(IStream_s0052_e1f0* s, cSPSkinPaintClearDescription_s0052_e1f0* d)
{
    Write(s, d->mDiffuseUserColor);
    s->Write(&d->mDiffuse, 12);
    s->Write(&d->mSpecBump, 12);
    Write(s, d->mGlossFactor);
    Write(s, d->mPhongFactor);
    Write(s, d->mPartBumpScale);
    Write(s, d->mPartSpecScale);
    Write(s, d->mHairAngle);
    Write(s, d->mHairLength);
    Write(s, d->mHairWidth);
    Write(s, d->mHairTaper);
    Write(s, d->mHairCurl);
    Write(s, d->mHairWave);
    Write(s, d->mHairMessiness);
    Write(s, d->mHairDensity);
    Write(s, d->mHairFaceCamera);
    Write(s, d->mHairTextureInstance);
    Write(s, d->mHairPrintGeomInstance);
    Write(s, d->mBitFlags);
}
