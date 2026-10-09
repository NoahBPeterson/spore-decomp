// Slice s007e06b0 (w2g5 slice 26).  Swarm split-model-kernel / split-controller
// ArgScript command cluster around 0x7e06b0.
//
// Region shape matches slice s007d19c0: command objects derive from
// EA::ArgScript::cCommandT<State>; the state pointer lives at +0xc and points
// at an anonymous-namespace state object whose cSplitModelKernelDescription
// member sits at state+4 (retail layout, +4 vs the 2008 PDB).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

// ---------------------------------------------------------------- allocators
void* operator new(size_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  operator delete(void* p);
void  operator delete[](void* p);
void  __cdecl EFree(void* p);                       // 0x00f47380 EASTL_allocator_deallocate

inline size_t StrLen(const char* p) { size_t n = 0; while (p[n]) ++n; return n; }

// ------------------------------------------------------------------- EASTL
namespace eastl {

extern char gEmptyBuf[];                            // 0x01667bac

// char string, retail 16-byte layout (begin/end/capacity + 4-byte allocator).
struct EString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* mAllocator;
    EString() : mpBegin(gEmptyBuf), mpEnd(gEmptyBuf), mpCapacity(gEmptyBuf + 1), mAllocator(0) {}
    void assign(const char* pBegin, const char* pEnd);   // 0x00454cb0
    ~EString() { if ((mpCapacity - mpBegin) > 1 && mpBegin) EFree(mpBegin); }
};

}  // namespace eastl

struct cSPVector3 { float x, y, z; };

struct cError { eastl::EString mMessage; cError(const char* fmt, ...); cError(const cError&); };

// ---------------------------------------------------------------- ArgScript
namespace EA {
namespace ArgScript {

class cArguments {
public:
    const char** MainArguments(int n);                              // 0x00838320
    const char** MainArguments(int* pCount, int min, int max);      // 0x00838020
    const char** OptionArguments(const char* name, int n);          // 0x00838330
};

typedef cSPVector3 Vec3;

struct cIParser {
    virtual void  v00(); virtual void  v01(); virtual void  v02(); virtual void  v03();
    virtual void  v04(); virtual void  v05(); virtual void  v06(); virtual void  v07();
    virtual void  v08(); virtual void  v09(); virtual void  v10(); virtual void  v11();
    virtual void  v12(); virtual void  v13(); virtual void  v14(); virtual void  v15();
    virtual void  v16(); virtual void  v17(); virtual void  v18(); virtual void  v19();
    virtual void  v20(); virtual void  v21(); virtual void  v22(); virtual void  v23();
    virtual void  v24(); virtual void  v25(); virtual void  v26(); virtual void  v27();
    virtual void  v28(); virtual void  v29(); virtual void  v30(); virtual void  v31();
    virtual void  v32(); virtual void  v33(); virtual void  v34(); virtual void  v35(void* cmd); // +0x8c
    virtual void  v36();                                            // +0x90
    virtual void  v37();                                            // +0x94
    virtual float v38(const char* s);                               // +0x98
    virtual void  v39();                                            // +0x9c
    virtual int   v40(const char* s);                               // +0xa0
    virtual void  v41();                                            // +0xa4
    virtual Vec3  v42(const char* s);                               // +0xa8
    virtual void  v43();                                            // +0xac
};

struct cCommandBase {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4();
    virtual void AddCommand(void* key, void* cmd);                  // +0x18
    cIParser* mParser;      // +0x4
    int       mRefCount;    // +0x8
};

struct cBlockCommandBase : cCommandBase {
    void* mChildState;      // +0xc
    char  mCommands[0x20];  // +0x10
};

uint32_t ParseEnum(const char* value, const char** table);          // 0x00840bb0

}  // namespace ArgScript

namespace IO {

struct IStream {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void ReadRegion(void* p, unsigned size);                // +0x30
};

bool ReadInt32(IStream* s, int32_t* p, unsigned n, int endian);     // 0x0093a780

}  // namespace IO

namespace Swarm {

// EA::Swarm::cDescription : EA::RefCountTemplate<int> (vtable +0, refcount +4)
struct cDescription {
    virtual void d0();
    virtual void d1();
    int mRefCount;      // +0x4
};

struct cEffectsParser {
    void* GetInheritedDescription(void* argv, int count, int type); // 0x00a6f0d0
};

}  // namespace Swarm
}  // namespace EA

// ------------------------------------------------------------------ kernel
struct cSafeDynamicKernelStorage {
    int   mKernelType;            // +0x0
    void* mKernelData;            // +0x4
    void* mKernelDataVariation;   // +0x8

    void SetKernelType(int type);                              // 0x007e0340
    void SetNormal(const cSPVector3& a, const cSPVector3& b);  // 0x007e0420
    void SetOrigin(const cSPVector3& a, const cSPVector3& b);  // 0x007e0480
    void SetRadius(float a, float b);                          // 0x007e04f0
    void SetDirection(const cSPVector3& a, const cSPVector3& b);// 0x007e0570
    cSafeDynamicKernelStorage& operator=(const cSafeDynamicKernelStorage& o); // 0x007e05e0
    void Read(EA::IO::IStream* stream);                        // 0x007e06b0
};

struct cSplitModelKernelDescription : EA::Swarm::cDescription {
    cSafeDynamicKernelStorage mData;   // +0x8
    cSplitModelKernelDescription() { mRefCount = 0; mData.mKernelData = 0; mData.mKernelDataVariation = 0; mData.mKernelType = -1; }
};

// state object referenced by command+0xc
struct KernelState {
    void* vtbl;                                  // +0x0
    cSplitModelKernelDescription mDesc;          // +0x4
};

extern const char* kSplitModelKernelTypeCommands;   // 0x0153f1c8
extern const cSPVector3 gDefaultVector;             // 0x01638c48
extern void* gCmdKeySplitSlider;                    // 0x0153f1e8

// =============================================================== 0x007e06b0
// @ 0x007e06b0
void cSafeDynamicKernelStorage::Read(EA::IO::IStream* stream) {
    EA::IO::ReadInt32(stream, (int32_t*)&mKernelType, 1, 0);
    SetKernelType(mKernelType);
    switch (mKernelType) {
    case 0:
    case 1:
        stream->ReadRegion(mKernelData, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelData + 0xc), 1, 0);
        stream->ReadRegion(mKernelDataVariation, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelDataVariation + 0xc), 1, 0);
        break;
    case 2:
        stream->ReadRegion(mKernelData, 0xc);
        stream->ReadRegion((char*)mKernelData + 0xc, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelData + 0x18), 1, 0);
        stream->ReadRegion(mKernelDataVariation, 0xc);
        stream->ReadRegion((char*)mKernelDataVariation + 0xc, 0xc);
        EA::IO::ReadInt32(stream, (int32_t*)((char*)mKernelDataVariation + 0x18), 1, 0);
        break;
    }
}

// =============================================================== 0x007e07a0
// @ 0x007e07a0
cSplitModelKernelDescription* SplitModelKernelRead(EA::IO::IStream* stream) {
    cSplitModelKernelDescription* p =
        new ("Swarm", 0, 0, 0, 0) cSplitModelKernelDescription();
    p->mData.Read(stream);
    return p;
}

// =============================================================== 0x007e07f0
struct cSplitControllerEffectCommand : EA::ArgScript::cBlockCommandBase {
    void* field30;                                  // +0x30  mpEffectsParser
    int   field34;                                  // +0x34
    EA::Swarm::cDescription mDesc;                  // +0x38
    eastl::EString mName;                           // +0x40
    void Execute(EA::ArgScript::cArguments& args);
    virtual ~cSplitControllerEffectCommand() {}
};

// @ 0x007e07f0
void cSplitControllerEffectCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 3);
    const char* s = av[0];
    const char* e = s;
    while (*e) ++e;
    mName.assign(s, e);
    if (count > 1)
        ((EA::Swarm::cEffectsParser*)field30)->GetInheritedDescription(av, count, 0x29);
    mParser->v35(this);
}

// =============================================================== 0x007e0850
void FUN_007e0280();
void FUN_007dfbd0();
void FUN_007dfbf0();
void FUN_00c2e4e0();

// @ 0x007e0850
void SplitControllerAddCommands(void* self, void* server) {
    int* cmdVtbl = (int*)server;
    cSplitControllerEffectCommand* effect = 0;
    if (server) {
        effect = new ("ArgScript/SplitControllerEffect", 0, 0, 0, 0) cSplitControllerEffectCommand();
        effect->field34 = 0x30aa211;
        effect->mDesc.mRefCount = 0;
    }
    ((void(__thiscall*)(void*, void*, void*))cmdVtbl[0x14 / 4])(server, gCmdKeySplitSlider, effect);
    cSplitControllerEffectCommand* group = 0;
    if (server) {
        group = new ("ArgScript/GroupSplitController", 0, 0, 0, 0) cSplitControllerEffectCommand();
    }
    ((void(__thiscall*)(void*, void*, void*))cmdVtbl[0x18 / 4])(server, gCmdKeySplitSlider, group);
}

// =============================================================== 0x007e09a0
extern int g_01675c54, g_01675c58, g_01675c3c, g_01675c48, g_01675c4c;
extern int g_016763d4, g_016763dc, g_016763e0, g_016763e8, g_016763ec;

// @ 0x007e09a0
void FUN_007e09a0(void) {
    g_01675c54 = 2;
    g_01675c58 = 2;
    g_01675c3c = (int)&FUN_007e0280;
    g_01675c48 = (int)&SplitModelKernelRead;
    g_01675c4c = (int)&FUN_007dfbd0;
    g_016763d4 = (int)&SplitControllerAddCommands;
    g_016763dc = (int)&FUN_007dfbf0;
    g_016763e0 = (int)&FUN_00c2e4e0;
    g_016763e8 = 1;
    g_016763ec = 1;
}

// ======================================================== kernel subcommands
struct cSplitModelKernelTypeCommand : EA::ArgScript::cCommandBase {
    KernelState* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments& args);
};
struct cSplitModelKernelOffsetCommand : EA::ArgScript::cCommandBase {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
struct cSplitModelKernelRadiusCommand : EA::ArgScript::cCommandBase {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
struct cSplitModelKernelNormalCommand : EA::ArgScript::cCommandBase {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
struct cSplitModelKernelOriginCommand : EA::ArgScript::cCommandBase {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
struct cSplitModelKernelDirectionCommand : EA::ArgScript::cCommandBase {
    KernelState* mState;
    void Execute(EA::ArgScript::cArguments& args);
};
struct cSplitModelKernelEffectCommand : EA::ArgScript::cBlockCommandBase {
    EA::Swarm::cEffectsParser* mpEffectsParser;   // +0x30
    int       field34;                            // +0x34
    char      pad38[8];                           // +0x38
    cSafeDynamicKernelStorage mData;              // +0x40
    eastl::EString mName;                         // +0x4c
    void Execute(EA::ArgScript::cArguments& args);
};

// @ 0x007e0a00
void cSplitModelKernelTypeCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    if (mState->mDesc.mData.mKernelType >= 0)
        throw cError("Type already specified.");
    mState->mDesc.mData.SetKernelType(
        EA::ArgScript::ParseEnum(av[0], &kSplitModelKernelTypeCommands));
}

// @ 0x007e0a60
void cSplitModelKernelOffsetCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    float a = mParser->v38(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        float b = mParser->v38(ov[0]);
        if (mState->mDesc.mData.mKernelType != 0)
            throw cError("Either type not specified or type does not support this parameter");
        *(float*)((char*)mState->mDesc.mData.mKernelData + 0xc) = a;
        *(float*)((char*)mState->mDesc.mData.mKernelDataVariation + 0xc) = b;
    } else {
        if (mState->mDesc.mData.mKernelType != 0)
            throw cError("Either type not specified or type does not support this parameter");
        *(float*)((char*)mState->mDesc.mData.mKernelData + 0xc) = a;
        *(float*)((char*)mState->mDesc.mData.mKernelDataVariation + 0xc) = 0.0f;
    }
}

// @ 0x007e0b50
void cSplitModelKernelRadiusCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    float a = mParser->v38(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    float b;
    if (ov)
        b = mParser->v38(ov[0]);
    else
        b = 0.0f;
    mState->mDesc.mData.SetRadius(a, b);
}

// @ 0x007e0bc0
void cSplitModelKernelNormalCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    cSPVector3 a = mParser->v42(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        cSPVector3 b = mParser->v42(ov[0]);
        mState->mDesc.mData.SetNormal(a, b);
    } else {
        mState->mDesc.mData.SetNormal(a, gDefaultVector);
    }
}

// @ 0x007e0c90
void cSplitModelKernelOriginCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    cSPVector3 a = mParser->v42(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        cSPVector3 b = mParser->v42(ov[0]);
        mState->mDesc.mData.SetOrigin(a, b);
    } else {
        mState->mDesc.mData.SetOrigin(a, gDefaultVector);
    }
}

// @ 0x007e0d60
void cSplitModelKernelDirectionCommand::Execute(EA::ArgScript::cArguments& args) {
    const char** av = args.MainArguments(1);
    cSPVector3 a = mParser->v42(av[0]);
    const char** ov = args.OptionArguments("vary", 1);
    if (ov) {
        cSPVector3 b = mParser->v42(ov[0]);
        mState->mDesc.mData.SetDirection(a, b);
    } else {
        mState->mDesc.mData.SetDirection(a, gDefaultVector);
    }
}

// @ 0x007e0e30
void cSplitModelKernelEffectCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 3);
    const char* s = av[0];
    const char* e = s;
    while (*e) ++e;
    mName.assign(s, e);
    cSafeDynamicKernelStorage tmp;
    tmp.mKernelType = -1;
    tmp.mKernelData = 0;
    tmp.mKernelDataVariation = 0;
    mData = tmp;
    if (count > 1) {
        void* got = mpEffectsParser->GetInheritedDescription(av, count, 0x10);
        if (got)
            mData = *(cSafeDynamicKernelStorage*)((char*)got + 8);
    }
    mParser->v35(this);
}

// ===================================================== split controller effect
struct Matrix33 { float m[9]; void Assign(const Matrix33& o); };
struct VtblObj;

struct cSPTransform {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float    mTranslation[3]; // +0x04
    float    mScale;        // +0x10
    Matrix33 mRotation;     // +0x14
    cSPTransform& operator=(const cSPTransform& o);   // 0x00537dc0
};

// second polymorphic base (vptr at +4)
struct SplitEffectBase1 {
    virtual void w0();
    virtual void w1();
    virtual void w2();
};

// primary polymorphic base (vptr at +0)
struct SplitEffectBase0 {
    virtual void e0();
    virtual void e1();
};

struct cSplitControllerEffect : SplitEffectBase0, SplitEffectBase1 {
    int   field08;              // +0x08
    void* mpOwner;              // +0x0c
    int   field10;              // +0x10
    char  field14;              // +0x14
    void* mpState;              // +0x18
    void* vecBegin;             // +0x1c
    void* vecEnd;               // +0x20
    void* vecCap;               // +0x24
    int   field28;              // +0x28
    int   field2c;              // +0x2c
    cSPTransform mTransform;    // +0x30
    float f68, f6c, f70;        // +0x68

    cSplitControllerEffect(void* owner);                         // 007e1010
    ~cSplitControllerEffect();                                   // 007e0f70
    void UpdateInstances(int unused);                            // 007e0f00
    void AddInstance(int a, void* b);                            // 007e10c0
    void CopyFrom(void* src);                                    // 007e1450
    void Start(int unused);                                      // 007e15b0
    void OnMessage(void* a, VtblObj* b, void* c);                // 007e1540
    char HandleMessage(int type, VtblObj* b);                    // 007e1580
};

extern const float gZero3[3];        // 0x01638f7c
extern const float gOne;             // 0x01485720
extern const Matrix33 gIdentity33;   // 0x01639100

// @ 0x007e0f00
void cSplitControllerEffect::UpdateInstances(int unused) {
    (void)unused;
    if (field14 && mpState) {
        int* end = (int*)vecEnd;
        for (int* it = (int*)vecBegin; it != end; it += 2) {
            int i = it[0];
            int j = it[1];
            int* base = *(int**)((char*)mpState + 0x40);
            char* elem = (char*)base + i * 0x1c;
            *(int*)(*(int*)(elem + 4) + j * 0x78) = *(int*)elem;
            --*(int*)(elem + 0x18);
            *(int*)elem = j;
        }
        field14 = 0;
    }
}

void EFree2(void* p);   // 0x00f47380

// @ 0x007e0f70
cSplitControllerEffect::~cSplitControllerEffect() {
    if (vecBegin && *(int*)((char*)vecBegin - 4))
        EFree(vecBegin);
    if (mpState) {
        int n = *(int*)((char*)mpState + 4) - 1;
        *(int*)((char*)mpState + 4) = n;
        if (n == 0) {
            *(int*)((char*)mpState + 4) = 1;
            ((void(__thiscall*)(void*, int))(*(void***)mpState)[0])(mpState, 1);
        }
    }
}

// @ 0x007e1010
cSplitControllerEffect::cSplitControllerEffect(void* owner) {
    field08 = 0;
    mpOwner = owner;
    field10 = 0;
    field14 = 0;
    mpState = 0;
    vecBegin = 0;
    vecEnd = 0;
    vecCap = 0;
    mTransform.mModCount = 0;
    mTransform.mFlags = 0;
    mTransform.mTranslation[0] = gZero3[0];
    mTransform.mTranslation[1] = gZero3[1];
    mTransform.mTranslation[2] = gZero3[2];
    mTransform.mScale = gOne;
    mTransform.mRotation = gIdentity33;
}

// Matrix helpers
void FUN_00537f40(void* self, void* p);                  // 0x00537f40
void FUN_0079a0d0(void* p);                              // 0x0079a0d0

// @ 0x007e10c0
void cSplitControllerEffect::AddInstance(int a, void* b) {
    cSPTransform local;
    const uint8_t* src = (const uint8_t*)b;
    local.mFlags = *(const uint16_t*)src;
    local.mModCount = *(const uint16_t*)(src + 2);
    local.mTranslation[0] = *(const float*)(src + 4);
    local.mTranslation[1] = *(const float*)(src + 8);
    local.mTranslation[2] = *(const float*)(src + 0xc);
    local.mScale = *(const float*)(src + 0x10);
    local.mRotation.Assign(*(const Matrix33*)(src + 0x14));

    FUN_00537f40(&local, (void*)a);
    mTransform = local;

    float s = *(const float*)(src + 0x10);
    float nx = -f68 * s;
    float ny = -f6c * s;
    float nz = -f70 * s;
    mTransform.mTranslation[0] +=
        mTransform.mRotation.m[0] * nx + mTransform.mRotation.m[3] * ny + mTransform.mRotation.m[6] * nz;
    mTransform.mTranslation[1] +=
        mTransform.mRotation.m[1] * nx + mTransform.mRotation.m[4] * ny + mTransform.mRotation.m[7] * nz;
    mTransform.mTranslation[2] +=
        mTransform.mRotation.m[2] * nx + mTransform.mRotation.m[5] * ny + mTransform.mRotation.m[8] * nz;
    mTransform.mFlags |= 4;
    ++mTransform.mModCount;

    if (field14) {
        int* end = (int*)vecEnd;
        for (int* it = (int*)vecBegin; it != end; it += 2) {
            int i = it[0];
            int j = it[1];
            int* base = *(int**)((char*)mpState + 0x40);
            char* elem = (char*)base + i * 0x1c;
            (*(cSPTransform*)(*(int*)(elem + 4) + j * 0x78 + 8)) = mTransform;
            FUN_0079a0d0((char*)mpState + 8);
        }
    }
}

void* FUN_0099efa0(void* begin, void* end, void* dst);   // 0x0099efa0
void* RBTreeIncrement(void* it);                          // 0x00921480

// @ 0x007e12b0
struct MyVector8 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void resize(unsigned n);
    void DoInsertValue(void* pos, void* v);   // 0x007e1340
};

// @ 0x007e12b0
void MyVector8::resize(unsigned n) {
    if (n > (unsigned)(((int)mpCapacity - (int)mpBegin) >> 3)) {
        char* p = n ? (char*)operator new(n * 8, "App", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1)
                    : 0;
        FUN_0099efa0(mpBegin, mpEnd, p);
        if (mpBegin && *(int*)((char*)mpBegin - 4))
            EFree(mpBegin);
        int count = ((int)mpEnd - (int)mpBegin) >> 3;
        char* cap = (char*)p + n * 8;
        char* end = (char*)p + count * 8;
        mpBegin = p;
        mpEnd = end;
        mpCapacity = cap;
    }
}

// @ 0x007e1450
void cSplitControllerEffect::CopyFrom(void* src) {
    if (!src)
        return;
    char was = field14;
    if (was)
        ((void(__thiscall*)(void*, int))(*(void***)this)[3])(this, 1);
    f68 = *(float*)((char*)src + 0x28);
    f6c = *(float*)((char*)src + 0x2c);
    f70 = *(float*)((char*)src + 0x30);
    void* np = *(void**)((char*)src + 0x34);
    void* op = mpState;
    if (np != op) {
        if (np)
            ++*(int*)((char*)np + 4);
        mpState = np;
        if (op) {
            int n = *(int*)((char*)op + 4) - 1;
            *(int*)((char*)op + 4) = n;
            if (n == 0) {
                *(int*)((char*)op + 4) = 1;
                ((void(__thiscall*)(void*, int))(*(void***)op)[0])(op, 1);
            }
        }
    }
    MyVector8* v = (MyVector8*)&vecBegin;
    v->resize(*(unsigned*)((char*)src + 0x20));
    void* stop = (char*)src + 0x10;
    for (void* it = *(void**)((char*)src + 0x14); it != stop; it = RBTreeIncrement(it)) {
        int val = *(int*)((char*)it + 0x10);
        int zero = 0;
        char* end = (char*)v->mpEnd;
        if (end < (char*)v->mpCapacity) {
            v->mpEnd = end + 8;
            if (end) { *(int*)end = val; *((int*)end + 1) = zero; }
        } else {
            v->DoInsertValue(end, &val);
        }
    }
    if (was)
        ((void(__thiscall*)(void*, int))(*(void***)this)[2])(this, 1);
}

void* AddSplitInstance(void* out, int key, cSPTransform* t, int flag);  // 0x007d7640

// @ 0x007e15b0
void cSplitControllerEffect::Start(int unused) {
    (void)unused;
    if (!field14 && mpState) {
        int* end = (int*)vecEnd;
        int* it = (int*)vecBegin;
        if (it != end) {
            do {
                int pair[2];
                AddSplitInstance(pair, *it, &mTransform, 0);
                it[0] = pair[0];
                it[1] = pair[1];
                it += 2;
            } while (it != end);
        }
        field14 = 1;
    }
}

// @ 0x007e1540
void cSplitControllerEffect::OnMessage(void* a, VtblObj* b, void* c) {
    (void)a;
    field10 = ((int(__thiscall*)(VtblObj*))(*(void***)b)[40])(b);
    void* p = *(void**)((char*)c + 0xc8);
    if (p) {
        void* r = (void*)((int(__thiscall*)(void*, int))(*(void***)p)[3])(p, 0x32f9668);
        CopyFrom(r);
    }
}

// @ 0x007e1580
char cSplitControllerEffect::HandleMessage(int type, VtblObj* b) {
    if (type == 5) {
        void* r = (void*)((int(__thiscall*)(VtblObj*, int))(*(void***)b)[3])(b, 0x32f9668);
        CopyFrom(r);
        return 1;
    }
    return 0;
}

// ------------------------------------------------------------------ misc
struct IRefCounted {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7();
};

struct cAppStateManager {
    char pad00[0x84];
    void* field84;              // +0x84
    void* field88;              // +0x88
    char pad8c[4];
    void** mpPrevBegin;         // +0x90
    void** mpPrevEnd;           // +0x94
    char pad98[0xa8];
    IRefCounted* field140;      // +0x140
    void* field144;             // +0x144
    void* field148;             // +0x148
    void* field14c;             // +0x14c
    void* field150;             // +0x150
    IRefCounted* field154;      // +0x154
    IRefCounted* field158;      // +0x158
    bool Shutdown();
    bool StateOccurredPreviously(void* p);
};

void __cdecl RemoveHandler(void* handler, void* a, void* b, void* c, void* d); // 0x00571db0
void* CheatManager();                                                          // 0x0067de20

// @ 0x007e1650
bool cAppStateManager::Shutdown() {
    if (field140) {
        void* h = field140;
        field140 = 0;
        RemoveHandler(h, field144, field148, field14c, field150);
    }
    if (field84) {
        void* cm = CheatManager();
        ((void(__thiscall*)(void*, void*))(*(void***)cm)[7])(cm, field84);
        field84 = 0;
    }
    if (field154) {
        field154->v3();
        IRefCounted* p = field154;
        if (p) {
            field154 = 0;
            p->v1();
        }
    } else if (field158) {
        field158->v3();
        IRefCounted* p = field158;
        if (p) {
            field158 = 0;
            p->v1();
        }
    }
    return true;
}

// @ 0x007e1710
bool cAppStateManager::StateOccurredPreviously(void* p) {
    int n = (int)((mpPrevEnd - mpPrevBegin)) - 1;
    if (n >= 0) {
        void** it = mpPrevBegin + n;
        do {
            if (*it == p)
                return true;
            if (*it == field88)
                break;
            --n;
            --it;
        } while (n >= 0);
    }
    return false;
}

struct VtblObj {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(int a, int b);   // +0x18
};

struct cForwarder {
    char pad[0x15c];
    VtblObj* p15c;
    VtblObj* p160;
    void Forward(int a, int b);
};

// @ 0x007e1760
void cForwarder::Forward(int a, int b) {
    p15c->v6(a, b);
    p160->v6(a, b);
}
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
