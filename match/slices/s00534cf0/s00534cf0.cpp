// Slice s00534cf0: Swarm skin-paint "flood" effect: ArgScript commands
// (cSPSkinPaintFloodEffectBlockCommand and its line commands), the effect
// description (nSPSkinner::cSPSkinPaintFloodDescription) ctor/copy/serialization.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int size_t;
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
void* operator new[](size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line); // 0xf473a0
inline void* operator new(size_t size, const char* name, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, name, flags, debugFlags, file, line); }
extern "C" int __cdecl _strnicmp(const char*, const char*, size_t);
extern "C" int __cdecl _stricmp(const char*, const char*);
extern "C" int __cdecl isdigit(int);
extern "C" long __cdecl atol(const char*);
extern "C" size_t __cdecl strlen(const char*);
#pragma intrinsic(strlen)

// ---------------------------------------------------------------- math
struct Vector3T {                               // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v);                // @ 0x4098a0 (out of line)
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    cSPVector3(const Vector3T& v) { x = v.x; y = v.y; z = v.z; }
    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }
};
cSPVector3 RGBToHSV(cSPVector3 rgb);            // @ 0x529d30

// Original codegen is "xorps; maxss v; minss hi" (an SSE max/min clamp against 0);
// written here as the equivalent scalar selects.
inline float Clamp(float v, float hi)
{
    v = (0.0f > v) ? 0.0f : v;
    v = (v < hi) ? v : hi;
    return v;
}

// ---------------------------------------------------------------- EASTL / EA
extern char gEmptyString[];                     // @ 0x1667bac
namespace eastl {
struct allocator {
    void deallocate(void* p, size_t) { delete[] (char*)p; }
};
struct basic_string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator mAllocator;
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~basic_string() { DeallocateSelf(); }
    void AllocateSelf() { mpBegin = gEmptyString; mpEnd = mpBegin; mpCapacity = mpBegin + 1; }
    void DeallocateSelf() {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(char* p, size_t n) { if (p) mAllocator.deallocate(p, n); }
    const char* c_str() const { return mpBegin; }
    basic_string& assign(const char* pBegin, const char* pEnd);          // @ 0x454cb0
    basic_string& assign(const char* p) { return assign(p, p + strlen(p)); }
};
} // namespace eastl

namespace EA {
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct RefCountTemplate {
    virtual ~RefCountTemplate();
    int mnRefCount;
    RefCountTemplate() : mnRefCount(0) {}
    RefCountTemplate(const RefCountTemplate&) : mnRefCount(0) {}
    int AddRef() { return mnRefCount++ + 1; }  // spelled to reproduce the /Od temp-then-store order
    int Release()                               // @ 0x453540 (declined inline)
    {
        int n = mnRefCount - 1;
        mnRefCount = mnRefCount - 1;
        if (n != 0)
            return n;
        mnRefCount = 1;
        delete this;
        return 0;
    }
};

namespace IO { struct IStream; }
} // namespace EA

bool ReadBool(EA::IO::IStream* s, bool* p);                                   // @ 0x93ac80
bool ReadUInt8(EA::IO::IStream* s, uint8_t* p, size_t n);                     // @ 0x93a6c0
bool ReadInt32(EA::IO::IStream* s, int32_t* p, size_t n, int endian);         // @ 0x93a780
bool WriteUInt8(EA::IO::IStream* s, const uint8_t* p, size_t n);              // @ 0x93a9a0
bool WriteUInt32(EA::IO::IStream* s, const uint32_t* p, size_t n, int endian);// @ 0x93aa70
bool ReadVector3(EA::IO::IStream* s, cSPVector3* p);                          // @ 0x698140
bool WriteVector3(EA::IO::IStream* s, const cSPVector3* p);                   // @ 0x6980e0

inline bool Write(EA::IO::IStream* s, uint8_t v) { uint8_t t = v; return WriteUInt8(s, &t, 1); }
inline bool Write(EA::IO::IStream* s, bool v) { return Write(s, (uint8_t)(v ? 1 : 0)); }
inline bool Write(EA::IO::IStream* s, int32_t v) { uint32_t t = v; return WriteUInt32(s, &t, 1, 0); }

namespace EA { namespace Swarm {
struct cDescription : public RefCountTemplate {
    cDescription() {}
};
}}

// ---------------------------------------------------------------- description
namespace nSPSkinner {

struct sp_vector_allocator {
    uint32_t mData[2];
    void deallocate(void* p, size_t) {
        if (((uint32_t*)p)[-1])
            delete[] (char*)p;
    }
};
template<typename T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    VectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VectorBase() {
        if (mpBegin)
            mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
    }
};
template<typename T> struct sp_vector : public VectorBase<T> {
    sp_vector() {}
    sp_vector(const sp_vector& x);
    ~sp_vector() { DoDestroyValues(this->mpBegin, this->mpEnd); }
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
};

struct cPaintVarEvalList {
    struct Modifier { cSPVector3 mVec; uint8_t mModType; uint8_t pad[3]; };
    struct Entry { float mRangeMin, mRangeMax, mValueMin, mValueMax; uint8_t mVariable, mVarModIdx, mApplyMode, mEdgeMode; };
    sp_vector<Modifier> mModifiers;     // +0x00
    sp_vector<Entry> mEntries;          // +0x14
    sp_vector<float> mCurveData;        // +0x28
    cPaintVarEvalList() { uint32_t unused; }
    cPaintVarEvalList(const cPaintVarEvalList& x);
};

// @ 0x00535c60
cPaintVarEvalList::cPaintVarEvalList(const cPaintVarEvalList& x)
    : mModifiers(x.mModifiers), mEntries(x.mEntries), mCurveData(x.mCurveData)
{
    ScratchSlots<39>();
}
bool Read(EA::IO::IStream* s, cPaintVarEvalList* list);           // @ 0x53a6d0
bool Write(EA::IO::IStream* s, const cPaintVarEvalList* list);    // @ 0x53a930

struct cSPSkinPaintFloodDescription : public EA::Swarm::cDescription {
    cPaintVarEvalList mEvalList;        // +0x08
    bool mHairFaceCamera;               // +0x44
    cSPVector3 mUserColorHSV;           // +0x48
    int mUserColorIndex;                // +0x54
    char mBlendModes[3];                // +0x58

    cSPSkinPaintFloodDescription()
    {
        mHairFaceCamera = true;
        mUserColorHSV.Set(0.0f, 0.0f, 1.0f);
        mUserColorIndex = -1;
        mBlendModes[0] = mBlendModes[1] = mBlendModes[2] = 0;
    }
    static cSPSkinPaintFloodDescription* Create(EA::IO::IStream* s, int version);
    static void Write(const cSPSkinPaintFloodDescription* d, EA::IO::IStream* s);
};

// @ 0x00535320
void Read(EA::IO::IStream* s, int version, cSPSkinPaintFloodDescription* d)
{
    Read(s, &d->mEvalList);
    ReadBool(s, &d->mHairFaceCamera);
    ReadVector3(s, &d->mUserColorHSV);
    ReadInt32(s, &d->mUserColorIndex, 1, 0);
    ReadUInt8(s, (uint8_t*)&d->mBlendModes[0], 1);
    ReadUInt8(s, (uint8_t*)&d->mBlendModes[1], 1);
    ReadUInt8(s, (uint8_t*)&d->mBlendModes[2], 1);
}

// @ 0x005353c0
void Write(EA::IO::IStream* s, const cSPSkinPaintFloodDescription* d)
{
    Write(s, &d->mEvalList);
    ::Write(s, d->mHairFaceCamera);
    WriteVector3(s, &d->mUserColorHSV);
    ::Write(s, (int32_t)d->mUserColorIndex);
    ::Write(s, (uint8_t)d->mBlendModes[0]);
    ::Write(s, (uint8_t)d->mBlendModes[1]);
    ::Write(s, (uint8_t)d->mBlendModes[2]);
}

// @ 0x005354a0
cSPSkinPaintFloodDescription* cSPSkinPaintFloodDescription::Create(EA::IO::IStream* s, int version)
{
    cSPSkinPaintFloodDescription* d = new("Swarm", 0, 0, 0, 0) cSPSkinPaintFloodDescription();
    Read(s, version, d);
    return d;
}

// @ 0x00535700
void cSPSkinPaintFloodDescription::Write(const cSPSkinPaintFloodDescription* d, EA::IO::IStream* s)
{
    nSPSkinner::Write(s, d);
}

} // namespace nSPSkinner
using namespace nSPSkinner;

// ---------------------------------------------------------------- ArgScript
namespace EA { namespace ArgScript {

#define PADV(n) virtual void Pad##n();
struct cICommand;
struct cIBlockCommand;
struct cArguments {
    const char** MainArguments(int count) const;                              // @ 0x838320
    const char** MainArguments(size_t* pCount, int minCount, int maxCount) const; // @ 0x838020
};
struct cState { int mID; cState(int id) : mID(id) {} };

struct cICommandList {
    virtual ~cICommandList();
    PADV(1) PADV(2) PADV(3) PADV(4)
    virtual void AddBlock(const char* name, cIBlockCommand* cmd);         // slot 5
    virtual void AddCommand(const char* name, cICommand* cmd);            // slot 6
};
struct cIParser : public cICommandList {
    PADV(7) PADV(8) PADV(9) PADV(10) PADV(11) PADV(12) PADV(13) PADV(14) PADV(15) PADV(16)
    PADV(17) PADV(18) PADV(19) PADV(20) PADV(21) PADV(22) PADV(23) PADV(24) PADV(25) PADV(26)
    PADV(27) PADV(28) PADV(29) PADV(30) PADV(31) PADV(32) PADV(33) PADV(34)
    virtual void PushBlock(cIBlockCommand* cmd);                           // slot 35
    PADV(36)
    virtual bool ParseBool(const char* s);                                 // slot 37
    PADV(38) PADV(39) PADV(40) PADV(41) PADV(42) PADV(43)
    virtual Vector3T ParseVector3(const char* s);                        // slot 44
};

struct cICommand {
    virtual void ParseLine(const cArguments& args);
};
struct cCommandBase : public cICommand {
    cIParser* mParser;
    int mRefCount;
    cCommandBase();                                                        // @ 0x83c800
};
struct cIBlockCommand : public cICommandList {
};
struct cBlockCommandBase : public cIBlockCommand {
    cIParser* mParser;                  // +0x04
    int mRefCount;                      // +0x08
    cState* mChildState;                // +0x0c
    uint32_t mCommands[8];              // +0x10 hash_map<string, AutoRefCount<cICommand>>
    cBlockCommandBase();                                                   // @ 0x83cdd0
    ~cBlockCommandBase();                                                  // @ 0x83cd90
    void OnRegister(cIParser* parser, cState* state);                      // @ 0x83c780
    void SetChildState(cState* state);                                     // @ 0xfd9450
};
template<class T, class Base> struct cCommandStateT : public Base {
    T* mState;
    cCommandStateT() {}
};
template<class T> struct cCommandT : public cCommandStateT<T, cCommandBase> {
    cCommandT() {}
};
template<class T> struct cBlockCommandT : public cCommandStateT<T, cBlockCommandBase> {
    cBlockCommandT() {}
};
struct EnumTable;
char ParseEnum(const char* s, const EnumTable* table);                     // @ 0x840bb0

}} // namespace EA::ArgScript
using namespace EA::ArgScript;

namespace EA { namespace Swarm {
struct cEffectsParserBase { virtual ~cEffectsParserBase(); uint32_t mData[2]; };
struct cEffectsParser : public cEffectsParserBase, public EA::ArgScript::cState {
    cDescription* GetInheritedDescription(const char** args, size_t numArgs, int type);   // @ 0xa6f090
    void SetDescription(const char* name, int type, cDescription* desc);                  // @ 0xa6f9c0
    void AddDescription(const cArguments& args, const char* name, int type, cDescription* desc); // @ 0xa6fc30
};
}}
using EA::Swarm::cEffectsParser;

namespace {

struct cSPSkinPaintFloodEffectBlockCommand : public cBlockCommandT<cEffectsParser>, public cState {
    enum { kStateID = 0x2c1642d };
    EA::AutoRefCount<cSPSkinPaintFloodDescription> mpDesc;     // +0x38
    eastl::basic_string mName;                                  // +0x3c
    cPaintVarEvalList* mpEvalList;                              // +0x4c
    int mCurrentModifier;                                       // +0x50

    cSPSkinPaintFloodEffectBlockCommand() : cState(kStateID) { uint32_t unused; }

    void OnRegister(cIParser* parser, cState* state);
    void ParseLine(const cArguments& args);
    void OnEndBlock(bool cancelled);
};

template<class T> struct cPaintVariableCommand : public cCommandT<T> {
    int mVarNum;
    cPaintVariableCommand(int varNum) : mVarNum(varNum) {}
    void ParseLine(const cArguments& args);
};
struct cFloodHairFaceCameraCommand : public cCommandT<cSPSkinPaintFloodEffectBlockCommand> {
    void ParseLine(const cArguments& args);
};
struct cFloodDiffuseColorCommand : public cCommandT<cSPSkinPaintFloodEffectBlockCommand> {
    void ParseLine(const cArguments& args);
};
struct cSPSkinPaintFloodEffectCommand : public cCommandT<cEffectsParser> {
    void ParseLine(const cArguments& args);
};
extern const EnumTable kBlendModeEnum;                          // @ 0x13f2a10
extern const char* kSPSkinPaintFloodName;                       // @ 0x13f2a08

template<class T> void RegisterPaintEvalCommands(T* block);     // @ 0x535e40

// @ 0x00534cf0
void cSPSkinPaintFloodEffectBlockCommand::OnRegister(cIParser* parser, cState* state)
{
    mState = static_cast<cEffectsParser*>(state);
    cBlockCommandBase::OnRegister(parser, state);
    SetChildState(static_cast<cState*>(this));
    AddCommand("hairFaceCamera", new("Skinner", 0, 0, 0, 0) cFloodHairFaceCameraCommand());
    AddCommand("diffuseColor", new("Skinner", 0, 0, 0, 0) cFloodDiffuseColorCommand());
    AddCommand("diffuseBlend", new("Skinner", 0, 0, 0, 0) cPaintVariableCommand<cSPSkinPaintFloodEffectBlockCommand>(0));
    AddCommand("specularBlend", new("Skinner", 0, 0, 0, 0) cPaintVariableCommand<cSPSkinPaintFloodEffectBlockCommand>(1));
    AddCommand("bumpBlend", new("Skinner", 0, 0, 0, 0) cPaintVariableCommand<cSPSkinPaintFloodEffectBlockCommand>(2));
    RegisterPaintEvalCommands(this);
}

// @ 0x00534f80
void cFloodDiffuseColorCommand::ParseLine(const cArguments& args)
{
    const char** argv = args.MainArguments(1);
    if (_strnicmp(argv[0], "color", 5) == 0 && isdigit((unsigned char)argv[0][5])) {
        uint32_t index = atol(argv[0] + 5) - 1;
        do { if (index >= 3) return; } while (0);
        mState->mpDesc->mUserColorIndex = index;
        mState->mpDesc->mUserColorHSV.Set(0.0f, 0.0f, 1.0f);
    } else if (_stricmp(argv[0], "identity") == 0) {
        mState->mpDesc->mUserColorIndex = -2;
        mState->mpDesc->mUserColorHSV.Set(0.0f, 0.0f, 1.0f);
    } else {
        cSPVector3 color = mParser->ParseVector3(argv[0]);
        color[0] = Clamp(color[0], 1.0f);
        color[1] = Clamp(color[1], 1.0f);
        color[2] = Clamp(color[2], 1.0f);
        mState->mpDesc->mUserColorIndex = -1;
        mState->mpDesc->mUserColorHSV = RGBToHSV(color);
    }
}

// @ 0x00535280
template<class T>
void cPaintVariableCommand<T>::ParseLine(const cArguments& args)
{
    const char** argv = args.MainArguments(1);
    this->mState->mpDesc->mBlendModes[mVarNum] = ParseEnum(argv[0], &kBlendModeEnum);
}
template struct cPaintVariableCommand<cSPSkinPaintFloodEffectBlockCommand>;

// @ 0x005352d0
void cFloodHairFaceCameraCommand::ParseLine(const cArguments& args)
{
    const char** argv = args.MainArguments(1);
    mState->mpDesc->mHairFaceCamera = mParser->ParseBool(argv[0]);
}

// @ 0x00535880
void cSPSkinPaintFloodEffectBlockCommand::ParseLine(const cArguments& args)
{
    size_t numArgs;
    const char** argv = args.MainArguments(&numArgs, 1, 3);
    if ((int)numArgs > 1) {
        cSPSkinPaintFloodDescription* parent = (cSPSkinPaintFloodDescription*)mState->GetInheritedDescription(argv, numArgs, 0x27);
        mpDesc = new("Skinner", 0, 0, 0, 0) cSPSkinPaintFloodDescription(*parent);
    } else
        mpDesc = new("Skinner", 0, 0, 0, 0) cSPSkinPaintFloodDescription();
    mName.assign(argv[0]);
    mCurrentModifier = 0xff;
    mpEvalList = &mpDesc->mEvalList;
    mParser->PushBlock(this);
}

// @ 0x00535a60
void cSPSkinPaintFloodEffectBlockCommand::OnEndBlock(bool cancelled)
{
    if (!cancelled) {
        cSPSkinPaintFloodDescription* desc = mpDesc.mpObject;
        const char* name = mName.c_str();
        mState->SetDescription(name, 0x27, desc);
    }
    mpDesc = 0;
    mpEvalList = 0;
}

// @ 0x00535cc0
void cSPSkinPaintFloodEffectCommand::ParseLine(const cArguments& args)
{
    const char** argv = args.MainArguments(1);
    mState->AddDescription(args, argv[0], 0x27, 0);
}

} // namespace

// @ 0x00535720
void SWARM_SPSkinPaintFloodAddCommands(cICommandList* parser, cICommandList* blockParser)
{
    parser->AddCommand(kSPSkinPaintFloodName, new("ArgScript/SPSkinPaintFloodEffect", 0, 0, 0, 0) cSPSkinPaintFloodEffectCommand());
    blockParser->AddBlock(kSPSkinPaintFloodName, new("ArgScript/SPSkinPaintFloodEffectBlock", 0, 0, 0, 0) cSPSkinPaintFloodEffectBlockCommand());
}
