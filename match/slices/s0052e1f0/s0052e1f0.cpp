// Skin-paint swarm effects: cSPSkinPaintClear (description writer, effect component) and
// cSPSkinPaintDistribute (description, ArgScript commands). Unoptimized module:
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast; functions with EH frames are built with /EHsc /GS- too.
#include "types.h"

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);                            // 0x00f473a0
void operator delete(void* p, const char* name, int flags, unsigned debugFlags,
                     const char* file, int line);
void operator delete(void* p);                                             // 0x00f47380
extern "C" __declspec(dllimport) int __cdecl sscanf(const char* buffer, const char* format, ...);

// ---------------------------------------------------------------- math
namespace rw { namespace math { namespace fpu {
template <typename T, int N> struct Vector3Template {
    T x, y, z;
    T& operator[](int i) { return (&x)[i]; }
};
}}}
typedef rw::math::fpu::Vector3Template<float, 0> Vector3;

struct ColorRGB {
    float r, g, b;
    ColorRGB() {}
    ColorRGB(const Vector3& v) : r(v.x), g(v.y), b(v.z) {}
    ColorRGB& operator=(const Vector3& v)
    {
        r = v.x;
        g = v.y;
        b = v.z;
        return *this;
    }
    float& operator[](int i) { return (&r)[i]; }
};
struct cSPVector3 {
    float x, y, z;
    cSPVector3(const ColorRGB& c) : x(c.r), y(c.g), z(c.b) {}
};

// ---------------------------------------------------------------- EASTL bits
struct sp_vector_allocator {
    uint32_t mFlags[2];
    sp_vector_allocator() {}
};
namespace eastl {
template <typename T1, typename T2> struct pair {
    T1 first;
    T2 second;
    pair(const T1& a, const T2& b) : first(a), second(b) {}
};

extern char gEmptyString;           // 0x01667bac
struct allocator {
    uint32_t mFlags;
    allocator() {}
};
template <typename T> struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        ScratchSlots<1>();
        AllocateSelf();
    }
    ~basic_string()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void AllocateSelf()
    {
        mpBegin = &gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void DoFree(T* p, uint32_t n)
    {
        if (p) {
            void* q = p;
            ::operator delete(q);
        }
    }
};

template <typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase();                  // 0x0045daf0 (declined inline)
};
template <typename T> struct vector : VectorBase<T> {
    vector() {}
    ~vector()
    {
        for (T* p = mpBegin; p < mpEnd; ++p)
            p->~T();
        ScratchSlots<3>();
    }
    T* erase(T* first, T* last);    // 0x00530c80
    void clear()
    {
        ScratchSlots<6>();      // frame of the declined erase() expansion
        erase(mpBegin, mpEnd);
    }
    void push_back(const T& value); // 0x005402c0
};
}  // namespace eastl

// ---------------------------------------------------------------- ref counting / swarm bases
namespace EA {
template <typename T> struct RefCountTemplate {
    RefCountTemplate() : mRefCount(0) {}
    ~RefCountTemplate() {}
    virtual int AddRef();
    virtual int Release();
    T mRefCount;
};
template struct RefCountTemplate<int>;

namespace IO { struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual bool Write(const void* data, uint32_t size);     // +0x38
};
bool WriteUint32(IStream* s, const uint32_t* v, uint32_t count, int endian);   // 0x0093aa70
bool WriteUint64(IStream* s, const uint64_t* v, uint32_t count, int endian);   // 0x0093ab10
bool WriteBool8(IStream* s, const bool* v, uint32_t count);                    // 0x0093a9a0
}  // namespace IO

namespace Swarm {
struct cIComponent {
    cIComponent() {}
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void Stop(int immediate);       // +0x0c
};
struct cComponentBase : cIComponent, RefCountTemplate<int> {
    cComponentBase() {}
    virtual ~cComponentBase() {}
    virtual int AddRef();
    virtual int Release();
};
struct cDescription : RefCountTemplate<int> {
    cDescription() {}
};
struct cEffectsParser;
}  // namespace Swarm
}  // namespace EA
using EA::IO::IStream;

// ---------------------------------------------------------------- stream helpers
inline bool WriteValue32(IStream* s, uint32_t value) { return EA::IO::WriteUint32(s, &value, 1, 0); }
inline bool Write(IStream* s, uint32_t value) { return WriteValue32(s, value); }
inline bool Write(IStream* s, int value) { return WriteValue32(s, (uint32_t)value); }
inline bool WriteFloat32(IStream* s, float value) { return EA::IO::WriteUint32(s, (uint32_t*)&value, 1, 0); }
inline bool Write(IStream* s, float value) { return WriteFloat32(s, value); }
inline bool WriteValue64(IStream* s, uint64_t value) { return EA::IO::WriteUint64(s, &value, 1, 0); }
inline bool Write(IStream* s, uint64_t value) { return WriteValue64(s, value); }
inline bool WriteBool(IStream* s, uint8_t value) { return EA::IO::WriteBool8(s, (const bool*)&value, 1); }
inline bool Write(IStream* s, bool value) { return WriteBool(s, value ? 1 : 0); }

// ---------------------------------------------------------------- cSPSkinPaintClear
struct cSPSkinPaintClearDescription : EA::Swarm::cDescription {   // 0x70
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
};

// @ 0x0052e1f0 ?WriteClearDescription
void WriteClearDescription(IStream* s, cSPSkinPaintClearDescription* d)
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

namespace nSPSkinner {
struct cRTTBuffer {
    bool Begin();                                   // 0x00528e90
    void SetClearColor(const cSPVector3& color, float alpha);   // 0x005292d0
    void BeginDraw();                               // 0x00529bf0
};
struct cPaintMaterial : EA::RefCountTemplate<int> {
    uint32_t pad08[2];
    cRTTBuffer* mComponents[3];     // +0x10
    uint32_t mDimension;            // +0x1c
    float mGlossFactor;             // +0x20
    float mPhongFactor;             // +0x24
    float mPhongExponent;           // +0x28
    float mPartBumpScale;           // +0x2c
    float mPartSpecScale;           // +0x30
};
template <typename T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
};
struct cPaintSystem {
    uint32_t pad00[3];
    AutoRefCount<cPaintMaterial> mpMaterial;    // +0x0c
    cPaintMaterial* GetMaterial() { return mpMaterial; }
};
cPaintSystem* GetPaintSystem();     // 0x00401080
inline cPaintSystem* PaintSystem() { return GetPaintSystem(); }
}  // namespace nSPSkinner

extern Vector3 kSkinPaintUserColors[];  // 0x015df0f0
inline ColorRGB GetUserColor(int index) { return ColorRGB(kSkinPaintUserColors[index]); }
void SetHairTexture(uint32_t instance);     // 0x0052a3e0
void SetHairPrintGeom(uint32_t instance);   // 0x0052a3f0

struct cSPSkinPaintClearEffect : EA::Swarm::cComponentBase {   // 0x14
    cSPSkinPaintClearDescription* mDesc;    // +0x0c
    bool mActive;                           // +0x10
    cSPSkinPaintClearEffect(cSPSkinPaintClearDescription* desc);
    virtual void SetParams(void* a, void* b, void* c);
    virtual void Bind(void* a, void* b);
    virtual void Unbind(void* a);
    virtual void Start(void* a);
    virtual void Update(void* a, void* b, void* c);
    virtual void Stop(int immediate);
};

// @ 0x0052e5b0 ??0cSPSkinPaintClearEffect
cSPSkinPaintClearEffect::cSPSkinPaintClearEffect(cSPSkinPaintClearDescription* desc)
    : mDesc(desc), mActive(false)
{
}

// @ 0x0052e620 ?SetParams@cSPSkinPaintClearEffect
void cSPSkinPaintClearEffect::SetParams(void* a, void* b, void* c) {}
// @ 0x0052e630 ?Bind@cSPSkinPaintClearEffect
void cSPSkinPaintClearEffect::Bind(void* a, void* b) {}
// @ 0x0052e650 ?Unbind@cSPSkinPaintClearEffect
void cSPSkinPaintClearEffect::Unbind(void* a) {}
// @ 0x0052e660 ?Start@cSPSkinPaintClearEffect
void cSPSkinPaintClearEffect::Start(void* a)
{
    mActive = true;
}

// @ 0x0052e680 ?Update@cSPSkinPaintClearEffect
void cSPSkinPaintClearEffect::Update(void* a, void* b, void* c)
{
    nSPSkinner::cPaintMaterial* material = nSPSkinner::PaintSystem()->GetMaterial();
    if (material) {
        if (mDesc->mBitFlags & 0x80)
            SetHairTexture((uint32_t)mDesc->mHairTextureInstance);
        if (mDesc->mBitFlags & 0x100)
            SetHairPrintGeom((uint32_t)mDesc->mHairPrintGeomInstance);
        if (mDesc->mBitFlags & 1) {
            ColorRGB color;
            if (mDesc->mDiffuseUserColor < 0)
                color = mDesc->mDiffuse;
            else
                color = GetUserColor(mDesc->mDiffuseUserColor);
            material->mComponents[0]->Begin();
            material->mComponents[0]->SetClearColor(color, 1.0f);
            material->mComponents[0]->BeginDraw();
        }
        uint8_t bSpec = (mDesc->mBitFlags >> 1) & 1;
        uint8_t bBump = (mDesc->mBitFlags >> 2) & 1;
        if (bSpec || bBump) {
            ColorRGB specBump(mDesc->mSpecBump);
            specBump[1] = 0.0f;
            material->mComponents[1]->Begin();
            material->mComponents[1]->SetClearColor(specBump, 0.0f);
            material->mComponents[1]->BeginDraw();
        }
        if (mDesc->mBitFlags & 0x200)
            material->mGlossFactor = mDesc->mGlossFactor;
        if (mDesc->mBitFlags & 0x400)
            material->mPhongFactor = mDesc->mPhongFactor;
        if (mDesc->mBitFlags & 8)
            material->mPhongExponent = mDesc->mSpecBump[1] * 60.0f;
        if (mDesc->mBitFlags & 0x10)
            material->mPartBumpScale = mDesc->mPartBumpScale;
        if (mDesc->mBitFlags & 0x20)
            material->mPartSpecScale = mDesc->mPartSpecScale;
    }
    Stop(1);
}

// @ 0x0052e980 ??_GcComponentBase@Swarm@EA@@

// ---------------------------------------------------------------- cSPSkinPaintDistribute
struct cSPSkinPaintDistributeDescription : EA::Swarm::cDescription {   // 0x54
    eastl::basic_string<char> mEffect;      // +0x08
    int mParticleDescId;                    // +0x18
    float mSpacing;                         // +0x1c
    uint32_t mLimit;                        // +0x20
    uint32_t mRegionFlags;                  // +0x24
    float mBackCutoff;                      // +0x28
    float mBellyCutoff;                     // +0x2c
    float mSpineRange[2];                   // +0x30
    bool mInvertRegions;                    // +0x38
    bool mCenterOnly;                       // +0x39
    bool mExtraCover;                       // +0x3a
    bool mNonRandom;                        // +0x3b
    eastl::vector<eastl::pair<int, float> > mParticleSelect;   // +0x3c
    bool mParticleSelectIndependent;        // +0x50
    cSPSkinPaintDistributeDescription();
    virtual void Dummy();
};

// @ 0x0052ea60 ??0cSPSkinPaintDistributeDescription
inline cSPSkinPaintDistributeDescription::cSPSkinPaintDistributeDescription()
{
}

// @ 0x0052eb40 ??1cSPSkinPaintDistributeDescription
// (compiler-generated destructor; emitted out of line for the explicit call below)
void DestroyDistributeDescription(cSPSkinPaintDistributeDescription* d)
{
    d->~cSPSkinPaintDistributeDescription();
}

// @ 0x0052ec00 ??1?$RefCountTemplate@H@EA@@

void ReadDistributeDescription(IStream* stream, int version, cSPSkinPaintDistributeDescription* d);   // 0x005300d0
void WriteDistributeDescription(IStream* stream, cSPSkinPaintDistributeDescription* d);              // 0x00530310

// @ 0x0052e9d0 ?ReadDistributeDescriptionCommand
cSPSkinPaintDistributeDescription* ReadDistributeDescriptionCommand(IStream* stream, int version)
{
    cSPSkinPaintDistributeDescription* const p = new ("Swarm", 0, 0, 0, 0) cSPSkinPaintDistributeDescription();
    ReadDistributeDescription(stream, version, p);
    return p;
}

// @ 0x0052ec20 ?WriteDistributeDescriptionCommand
void WriteDistributeDescriptionCommand(cSPSkinPaintDistributeDescription* d, IStream* stream)
{
    WriteDistributeDescription(stream, d);
}

// ---------------------------------------------------------------- ArgScript commands
namespace EA { namespace ArgScript {
struct cIParser {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void PushMetaCommand(void* command, const char* endKeyword);   // +0x90
};
struct cState {
    uint32_t mStateID;
};
struct Line {
    struct Text {
        const char* mpBegin;
        const char* c_str() const { return mpBegin; }
    } mText;
    const char* GetText() const { return mText.c_str(); }
};
struct cArguments {
    const char** MainArguments(int count);      // 0x00838320
    bool HasFlag(const char* flag);             // 0x008380b0
};
struct cError {
    uint32_t mMessage[4];   // eastl::basic_string<char>
    cError(const char* fmt, ...);               // 0x0052df30
    cError(const cError& x);
    ~cError();
};
struct cICommand {
    virtual void AddRef();
    virtual void Release();
    virtual void Cast();
};
struct cCommandBase : cICommand {
    cIParser* mParser;
    int mRefCount;
    cCommandBase();                             // 0x0083c800
    void OnRegister(cIParser* parser, cState* state);   // 0x0083c7f0
};
struct cIMetaCommand : cICommand {};
struct cMetaCommandBase : cIMetaCommand {
    cIParser* mParser;
    int mRefCount;
    cMetaCommandBase();                         // 0x0083c840
};
struct cIBlockCommand : cICommand {};
struct cBlockCommandBase : cIBlockCommand {
    cIParser* mParser;                          // +0x04
    int mRefCount;                              // +0x08
    cState* mChildState;                        // +0x0c
    uint32_t mCommands[8];                      // +0x10 hash_map
    void OnRegister(cIParser* parser, cState* state);   // 0x0083c780
    void SetChildState(cState* state);          // 0x00fd9450
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void AddCommand(const char* name, cICommand* command);      // +0x18
};

template <typename T, typename Base> struct cCommandStateT : Base {
    T* mState;
    cCommandStateT() {}
    void OnRegister(cIParser* parser, cState* state);
};
template <typename T> struct cCommandT : cCommandStateT<T, cCommandBase> {
    cCommandT() {}
};
template <typename T> struct cMetaCommandT : cCommandStateT<T, cMetaCommandBase> {
    cMetaCommandT() {}
};
template <typename T> struct cBlockCommandT : cCommandStateT<T, cBlockCommandBase> {
    cBlockCommandT() {}
};
}}  // namespace EA::ArgScript

namespace EA { namespace Swarm {
struct cEffectsParser : RefCountTemplate<int> {
    int FindComponent(const char* name, int type);  // 0x00a6eb60
};
}}

// @ 0x0052e520 ?OnRegister@?$cCommandStateT@UcEffectsParser@Swarm@EA@@UcCommandBase@ArgScript@3@@ArgScript@EA@@
template <> void EA::ArgScript::cCommandStateT<EA::Swarm::cEffectsParser, EA::ArgScript::cCommandBase>::OnRegister(
    cIParser* parser, cState* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    cCommandBase::OnRegister(parser, state);
}


namespace {
struct cSPSkinPaintDistributeEffectCommand
    : EA::ArgScript::cBlockCommandT<EA::Swarm::cEffectsParser>, EA::ArgScript::cState {
    cSPSkinPaintDistributeDescription mDesc;        // +0x38
    eastl::basic_string<char> mDescName;
    void OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state);
};

struct cSPSkinPaintDistributeParticleCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeParticleCommand() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cSPSkinPaintDistributeParticlesCommand : EA::ArgScript::cMetaCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeParticlesCommand() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
    virtual bool Parse(const EA::ArgScript::Line& line);
};
struct cSPSkinPaintDistributeSpacingCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeSpacingCommand() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cSPSkinPaintDistributeLimitCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeLimitCommand() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
};
struct cSPSkinPaintDistributeRegionCommand : EA::ArgScript::cCommandT<cSPSkinPaintDistributeEffectCommand> {
    cSPSkinPaintDistributeRegionCommand() {}
    virtual void Execute(EA::ArgScript::cArguments& args);
};
}  // namespace

extern const char* kDistributeParticleKeyword;      // "particle"
extern const char* kDistributeParticlesKeyword;     // "particleSelect"
extern const char* kDistributeSpacingKeyword;       // "spacing"
extern const char* kDistributeLimitKeyword;         // "limit"
extern const char* kDistributeRegionKeyword;        // "region"

// @ 0x0052ec40 ?OnRegister@cSPSkinPaintDistributeEffectCommand@
void cSPSkinPaintDistributeEffectCommand::OnRegister(EA::ArgScript::cIParser* parser, EA::ArgScript::cState* state)
{
    mState = state ? (EA::Swarm::cEffectsParser*)((char*)state - 0xc) : 0;
    cBlockCommandBase::OnRegister(parser, state);
    SetChildState(this);
    AddCommand(kDistributeParticleKeyword,
               new ("ArgScript/SPSkinPaintDistributeParticle", 0, 0, 0, 0) cSPSkinPaintDistributeParticleCommand());
    AddCommand(kDistributeParticlesKeyword,
               new ("ArgScript/SPSkinPaintDistributeParticles", 0, 0, 0, 0) cSPSkinPaintDistributeParticlesCommand());
    AddCommand(kDistributeSpacingKeyword,
               new ("ArgScript/SPSkinPaintDistributeSpacing", 0, 0, 0, 0) cSPSkinPaintDistributeSpacingCommand());
    AddCommand(kDistributeLimitKeyword,
               new ("ArgScript/SPSkinPaintDistributeLimit", 0, 0, 0, 0) cSPSkinPaintDistributeLimitCommand());
    AddCommand(kDistributeRegionKeyword,
               new ("ArgScript/SPSkinPaintDistributeRegion", 0, 0, 0, 0) cSPSkinPaintDistributeRegionCommand());
}

// @ 0x0052ef40 ?Execute@cSPSkinPaintDistributeParticleCommand@
void cSPSkinPaintDistributeParticleCommand::Execute(EA::ArgScript::cArguments& args)
{
    const char** ppArgs = args.MainArguments(1);
    EA::Swarm::cEffectsParser* pEffects = mState->mState;
    int result = pEffects->FindComponent(ppArgs[0], 0x26);
    if (result < 0)
        throw EA::ArgScript::cError("unknown particle type '%s'\n", ppArgs[0]);
    else
        mState->mDesc.mParticleDescId = result;
}

// @ 0x0052efc0 ?Execute@cSPSkinPaintDistributeParticlesCommand@
void cSPSkinPaintDistributeParticlesCommand::Execute(EA::ArgScript::cArguments& args)
{
    args.MainArguments(0);
    mState->mDesc.mParticleSelect.clear();
    mState->mDesc.mParticleSelectIndependent = args.HasFlag("all");
    mParser->PushMetaCommand(this, "end");
}

// @ 0x0052f040 ?Parse@cSPSkinPaintDistributeParticlesCommand@
bool cSPSkinPaintDistributeParticlesCommand::Parse(const EA::ArgScript::Line& line)
{
    char name[128];
    name[0] = 0;
    float prob = mState->mDesc.mParticleSelectIndependent ? 1.0f : -1.0f;
    sscanf(line.GetText(), " %127s -prob %f", name, &prob);
    if (name[0]) {
        EA::Swarm::cEffectsParser* parser = mState->mState;
        int index = parser->FindComponent(name, 0x26);
        if (index >= 0) {
            ScratchSlots<2>();      // frame of the declined push_back() expansion
            mState->mDesc.mParticleSelect.push_back(eastl::pair<int, float>(index, prob));
        } else
            throw EA::ArgScript::cError("unknown particle type '%s'\n", name);
    }
    return true;
}
