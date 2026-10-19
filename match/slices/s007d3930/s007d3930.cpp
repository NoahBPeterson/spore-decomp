// SWARM game-model debug commands and the read/description helpers around
// 0x007d3930-0x007d4a33.  Matched functions: ReadAnimationCurves (0x7d40f0),
// Wrapper::Func (0x7d44a0), EffOwner::SetVisible (0x7d4820), VecOut::Allocate
// (0x7d48e0).  Every other function is present in a behaviorally complete or
// approximate form (see nonmatching.txt / partial.txt).
//
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

void* operator new[](size_t size);
void  operator delete[](void* p);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);

namespace EA {
namespace IO {
bool ReadInt32(void* s, int32_t* p, unsigned n, int endian);   // 0x93a780
}
namespace ArgScript {
class cArguments {
public:
    const char** MainArguments(int n);
    const char** MainArguments(int* count, int min, int max);
    const char** OptionArguments(const char* name, int n);
    const char** OptionArguments(const char* name, int* count, int min, int max);
    bool HasFlag(const char* name);
};
uint32_t ParseEnum(const char* value, const char** table);
}}
bool ReadBytes(void* s, void* p, unsigned n);                  // 0x93a6c0
void* ReadIntVector(void* stream, void* vec);                  // 0x7d27d0
uint32_t FNVHash(const char* s, uint32_t seed, int a);         // 0x932e80

// game-model description stream decoders / misc helpers (see slice header)
void* sub_7d10d0(void* stream, void* vec);                     // 0x7d10d0
void* sub_7d4190(void* stream, void* vec);                     // 0x7d4190
void* sub_53bc90(void* stream, void* vec);                     // 0x53bc90
void* sub_7d1010(void* self);                                  // 0x7d1010 dtor/ctor
void  sub_7d0f60(void* self);                                  // 0x7d0f60
void* sub_7d35b0(void* self, const void* src);                 // 0x7d35b0 operator=
void  sub_454cb0(void* str, const char* first, const char* last); // 0x454cb0 string assign
void* sub_a6f090(void* parser, const char** av, int count, int which); // 0xa6f090
void  sub_7d3670(void* vec, const void* elem);                 // 0x7d3670 push_back
void  sub_455660(void* vec, const float* value);               // 0x455660 push_back
// cSPTransform::operator= and the per-label propagation helper are __thiscall
// (ecx = target, one stack argument).  Model them as member methods so the
// calling convention matches the original.
struct cSPTransformOps { cSPTransformOps* Assign(const void* src); };  // 0x537dc0
struct cLabelOps      { void Propagate(const void* txf); };            // 0x79a0d0

// split-command helpers (all __thiscall; modelled as member methods)
void  sub_7d05b0(void* out, void* node, int* key, int extra);  // 0x7d05b0
int   sub_a6eb60(const char* name, int n);                     // 0xa6eb60
void* sub_f47380(void* p);                                     // 0xf47380 allocator deallocate
extern float kFX2Pi;                                           // 0x163703c
extern const char* kSplitCommandsEnum[];                       // 0x153d820

struct IUnknown32 { virtual void AddRef(); virtual void Release(); };

// ----------------------------------------------------- IStream (slot 0x30 Read)
struct IStream {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual int Read(void* dst, uint32_t size);   // +0x30
};

// --------------------------------------------------------------- game model
namespace SP {
struct Vec20 { void* p0; void* p1; void* p2; void* p3; void* p4; };
struct cAnimationCurve {
    float mX, mY;
    Vec20 mCurve;          // +0x08
    float mA, mB, mC;      // +0x1c
    uint8_t mMode;         // +0x28
    cAnimationCurve() {     // inlined default ctor (zeroes the live fields)
        mX = 0; mY = 0;
        mCurve.p0 = 0; mCurve.p1 = 0; mCurve.p2 = 0;
        mA = 0; mB = 0; mC = 0;
        mMode = 0;
    }
    ~cAnimationCurve() {    // inlined vector teardown
        if (mCurve.p0 && *(int*)((char*)mCurve.p0 - 4))
            operator delete[](mCurve.p0);
    }
};
struct cGameModelDescription {
    void* vtbl; int mRefCount; int mStateID; uint32_t mFlags;
    float mSize; float mColourX, mColourY, mColourZ; float mAlpha;
    uint32_t mInstanceID, mGroupID, mWorldID;
    Vec20 mAnimationCurves, mModelSplitters, mSplitControllers, mGroups;
    uint32_t mFlagsToSet; uint8_t mPickLevel, mOverrideSet, pad86[2]; uint32_t field88;
    cGameModelDescription();           // 0x7d1010
    ~cGameModelDescription();          // 0x7d0f60
};

struct cError {
    cError(const char* fmt, ...);      // 0x52df30
    ~cError();
};
}

// ============================================================ 0x7d40f0 MATCH
struct AnimVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* a1; void* a2;
    void resize(unsigned n);   // 0x7d3770
};
// @ 0x007d40f0
IStream* ReadAnimationCurves(IStream* stream, AnimVec* vec) {
    int count;
    EA::IO::ReadInt32(stream, &count, 1, 0);
    vec->resize((unsigned)count);
    for (unsigned i = 0; i < (unsigned)count; ++i) {
        char* e = (char*)vec->mpBegin + i * 0x2c;
        stream->Read(e, 8);
        ReadIntVector(stream, e + 8);
        EA::IO::ReadInt32(stream, (int32_t*)(e + 0x1c), 1, 0);
        EA::IO::ReadInt32(stream, (int32_t*)(e + 0x20), 1, 0);
        EA::IO::ReadInt32(stream, (int32_t*)(e + 0x24), 1, 0);
        ReadBytes(stream, e + 0x28, 1);
    }
    return stream;
}

// ============================================================ 0x7d44a0 MATCH
struct Comp {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63();
    virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67();
    virtual void v68(); virtual void v69(); virtual void v70(); virtual void v71();
    virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75();
    virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
    virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
    virtual void v84(); virtual void v85(); virtual void v86(); virtual void v87();
    virtual void v88(); virtual void v89(); virtual void v90();
    virtual void SetOwner(void* owner, int flag);   // +0x16c
};
struct Wrapper { void* mpComp; void Func(); };
// @ 0x007d44a0
void Wrapper::Func() { ((Comp*)mpComp)->SetOwner(this, 1); }

// ============================================================ 0x7d4820 MATCH
struct EffComp {
    virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3();
    virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7();
    virtual void e8(); virtual void e9();
    virtual void SetFlag(int f);   // +0x28
};
struct EffOwner { void SetVisible(int param); };
// @ 0x007d4820
void EffOwner::SetVisible(int param) {
    *(uint8_t*)((char*)this + 0x15) = (uint8_t)param;
    _ReadWriteBarrier();
    unsigned count = (unsigned)((*(char**)((char*)this + 0xb0) - *(char**)((char*)this + 0xac)) >> 6);
    if (count != 0) {
        for (unsigned i = 0; i < count; ++i) {
            EffComp* c = *(EffComp**)(*(char**)((char*)this + 0xac) + i * 0x40 + 0x3c);
            c->SetFlag(param);
        }
    }
    void* p = *(void**)((char*)this + 0x38);
    if (p) {
        if ((char)param) *(uint32_t*)((char*)p + 4) |= 1;
        else *(uint32_t*)((char*)p + 4) &= ~1u;
    }
}

// ============================================================ 0x7d48e0 MATCH
struct VecOut {
    void* b; void* e; void* c;
    VecOut* Allocate(unsigned n, void* alloc);
};
// @ 0x007d48e0
VecOut* VecOut::Allocate(unsigned n, void* alloc) {
    void* buf = n ? operator new(n * 0x78, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    b = buf;
    e = buf;
    c = (char*)buf + n * 0x78;
    return this;
}

// ====================================================== remaining functions
struct cGameModelState { void* vtbl; SP::cGameModelDescription mDesc; };

// @ 0x007d3930
struct cGameModelAnimateCommand {
    void* mParser;         // +0x4
    cGameModelState* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments& args);
};
void cGameModelAnimateCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);

    // Append a default-constructed animation curve to the description's curve
    // list; `e` then points at the copy that now sits at the end of that list.
    SP::cAnimationCurve curve;
    sub_7d3670(&mState->mDesc.mAnimationCurves, &curve);
    char* e = (char*)mState->mDesc.mAnimationCurves.p1 - 0x2c;

    for (int i = 0; i < count; ++i) {
        float f = ((float(__thiscall*)(void*, const char*))
                   ((*(void***)mParser)[0x98 / 4]))(mParser, av[i]);
        sub_455660(e + 8, &f);
    }

    int n;
    const char** length = args.OptionArguments("length", &n, 1, 2);
    if (length) {
        float f = ((float(__thiscall*)(void*, const char*))
                   ((*(void***)mParser)[0x98 / 4]))(mParser, length[0]);
        *(float*)(e + 0x00) = f;
        *(float*)(e + 0x04) = f;
        if (n > 1) {
            float g = ((float(__thiscall*)(void*, const char*))
                       ((*(void***)mParser)[0x98 / 4]))(mParser, length[1]);
            *(float*)(e + 0x00) = *(float*)(e + 0x00) - g;
            *(float*)(e + 0x04) = *(float*)(e + 0x04) + g;
        }
    }
    const char** channel = args.OptionArguments("channel", 1);
    if (channel)
        *(uint32_t*)(e + 0x24) = FNVHash(channel[0], 0x811c9dc5, 1);
    else
        *(uint32_t*)(e + 0x24) = 0;
    if (args.HasFlag("sustain")) *(uint8_t*)(e + 0x28) = 1;
    else if (args.HasFlag("single")) *(uint8_t*)(e + 0x28) = 2;
    else if (args.HasFlag("loop")) *(uint8_t*)(e + 0x28) = 0;
    const char** vary = args.OptionArguments("vary", 1);
    if (vary)
        *(float*)(e + 0x1c) = ((float(__thiscall*)(void*, const char*))
                               ((*(void***)mParser)[0x98 / 4]))(mParser, vary[0]);
    const char** ss = args.OptionArguments("speedScale", 1);
    if (ss)
        *(float*)(e + 0x20) = ((float(__thiscall*)(void*, const char*))
                               ((*(void***)mParser)[0x98 / 4]))(mParser, ss[0]);
}

// @ 0x007d3b60
struct cXform {                       // SP::cTransform, at cSplitTxf+8
    uint16_t mFlags;                  // +0x00
    uint16_t mModCount;               // +0x02
    float    mTrans[3];               // +0x04
    float    mScale;                  // +0x10
    float    mRot[9];                 // +0x14
    void RotateZ(float a);            // 0x7d1ac0
    void RotateY(float a);            // 0x6b9050
    void PreRotateX(float a);         // 0x5a2d90
};
struct MapEntry { void* node; uint8_t inserted; };
struct cRBT {                         // eastl::rbtree<uint32,...> at cSplitTxf+0x4c
    char raw[0x1c];
    void Insert(MapEntry* out, const int* key, uint8_t flag);   // 0x7d0850
    void Nuke(void* sub);                                        // 0x9a9600
};
struct cSplitTxf {                    // ctor 0x7d0670
    int32_t  field00;                 // +0x00
    int32_t  mCount;                  // +0x04
    cXform   xf;                      // +0x08
    float    mOrigin[3];              // +0x40
    cRBT     map;                     // +0x4c
    void Init();                      // 0x7d0670
};
struct cStateOps { void Finalize(void* txf); };   // 0x7d36f0
struct cGameModelSplitCommand {
    void* mParser;                    // +0x04
    void* field08;
    cGameModelState* mState;          // +0x0c
    void Execute(EA::ArgScript::cArguments& args);
};
void cGameModelSplitCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 2, 0x7fffffff);

    cSplitTxf txf;
    txf.Init();

    unsigned kind = (unsigned char)EA::ArgScript::ParseEnum(av[0], kSplitCommandsEnum);
    int i = 2;
    if (kind == 0) {
        txf.mCount = (*(int*)((char*)mState + 0x4c) - *(int*)((char*)mState + 0x48)) >> 3;
    } else if (kind == 1) {
        if (count < 3)
            throw SP::cError("Either meta particle or at least one split index unspecified");
        txf.mCount = sub_a6eb60(av[1], 2);
        if (txf.mCount < 0)
            throw SP::cError("Unknown meta particle: %s", av[1]);
        for (; i < count; ++i) {
            int v = ((int(__thiscall*)(void*, const char*))
                     ((*(void***)mParser)[0x9c / 4]))(mParser, av[i]);
            MapEntry out;
            txf.map.Insert(&out, &v, 0);
        }
    } else if (kind == 2) {
        for (i = 1; i < count; ++i) {
            int v = ((int(__thiscall*)(void*, const char*))
                     ((*(void***)mParser)[0x9c / 4]))(mParser, av[i]);
            MapEntry out;
            txf.map.Insert(&out, &v, 0);
        }
    } else {
        throw SP::cError("Unimplemented split command");
    }

    const char** parg = args.OptionArguments("origin", 1);
    if (parg) {
        float* v = (float*)((void*(__thiscall*)(void*, const char*))
                            ((*(void***)mParser)[0xa8 / 4]))(mParser, parg[0]);
        float x = v[0], y = v[1], z = v[2];
        float s = txf.xf.mScale;
        float t0 = txf.xf.mTrans[0] + (txf.xf.mRot[0] * (s*x) + txf.xf.mRot[3] * (s*y) + txf.xf.mRot[6] * (s*z));
        float t1 = txf.xf.mTrans[1] + (txf.xf.mRot[1] * (s*x) + txf.xf.mRot[4] * (s*y) + txf.xf.mRot[7] * (s*z));
        float t2 = txf.xf.mTrans[2] + (txf.xf.mRot[2] * (s*x) + txf.xf.mRot[5] * (s*y) + txf.xf.mRot[8] * (s*z));
        txf.xf.mFlags |= 4;
        txf.xf.mModCount += 1;
        txf.xf.mTrans[0] = t0; txf.xf.mTrans[1] = t1; txf.xf.mTrans[2] = t2;
        txf.mOrigin[0] = x;
        txf.mOrigin[1] = y;
        txf.mOrigin[2] = z;
    }
    parg = args.OptionArguments("offset", 1);
    if (parg) {
        float* v = (float*)((void*(__thiscall*)(void*, const char*))
                            ((*(void***)mParser)[0xa8 / 4]))(mParser, parg[0]);
        txf.xf.mTrans[0] += v[0];
        txf.xf.mTrans[1] += v[1];
        txf.xf.mTrans[2] += v[2];
        txf.xf.mFlags |= 4;
        txf.xf.mModCount += 1;
    }
#define SPLIT_ANGLE(slot) \
    ((float(__thiscall*)(void*, const char*))((*(void***)mParser)[0x98 / 4]))(mParser, (slot)) * kFX2Pi
    parg = args.OptionArguments("rotateZ", 1);
    if (parg) txf.xf.RotateZ(SPLIT_ANGLE(parg[0]));
    parg = args.OptionArguments("rotateY", 1);
    if (parg) txf.xf.RotateY(SPLIT_ANGLE(parg[0]));
    parg = args.OptionArguments("rotateX", 1);
    if (parg) txf.xf.PreRotateX(SPLIT_ANGLE(parg[0]));
    parg = args.OptionArguments("rotateXYZ", 3);
    if (parg) {
        txf.xf.RotateZ(SPLIT_ANGLE(parg[2]));
        txf.xf.RotateY(SPLIT_ANGLE(parg[1]));
        txf.xf.PreRotateX(SPLIT_ANGLE(parg[0]));
    }
    parg = args.OptionArguments("rotateZXY", 3);
    if (parg) {
        txf.xf.RotateY(SPLIT_ANGLE(parg[2]));
        txf.xf.PreRotateX(SPLIT_ANGLE(parg[1]));
        txf.xf.RotateZ(SPLIT_ANGLE(parg[0]));
    }
    parg = args.OptionArguments("scale", 1);
    if (parg) {
        txf.xf.mScale = SPLIT_ANGLE(parg[0]) * txf.xf.mScale;
        txf.xf.mFlags |= 1;
        txf.xf.mModCount += 1;
    }
#undef SPLIT_ANGLE

    ((cStateOps*)((char*)mState + 0x5c))->Finalize(&txf);

    // drain the temporary rbtree of split indices
    void** node = *(void***)((char*)&txf + 0x58);
    while (node) {
        txf.map.Nuke(*node);
        void** next = (void**)node[1];
        sub_f47380(node);
        node = next;
    }
}

// @ 0x007d41f0
struct cGameModelEffectCommand {
    void* mParser;              // +0x04  (cIParser*, used for the final vcall)
    void* mField30;             // +0x30  inherited-source pointer
    void* mVtbl34;              // +0x34
    void* mDesc;                // +0x38  owned cGameModelDescription
    void* mFieldC4;             // +0xc4
    void* mName;                // +0xc8  eastl::string
    void  Execute(EA::ArgScript::cArguments& args);
};
void cGameModelEffectCommand::Execute(EA::ArgScript::cArguments& args) {
    int count;
    const char** av = args.MainArguments(&count, 1, 3);

    const char* s = av[0];
    const char* end = s;
    while (*end) ++end;
    sub_454cb0((char*)this + 0xc8, s, end);

    SP::cGameModelDescription tmp;
    mVtbl34 = (void*)0x30bac64;
    sub_7d35b0((char*)this + 0x38, &tmp);
    mFieldC4 = (void*)0;

    *(void**)((char*)this + 0xc4) = mField30;
    if (count > 1) {
        void* inh = sub_a6f090(mField30, av, count, 0x25);
        if (inh)
            sub_7d35b0((char*)this + 0x38, inh);
    }
    ((void(__thiscall*)(void*))((*(void***)mParser)[0x8c / 4]))(this);
}

// @ 0x007d4300
void __cdecl ReadDescription(void* stream, int version, SP::cGameModelDescription* desc) {
    int flags;
    EA::IO::ReadInt32(stream, &flags, 1, 0);
    desc->mFlags = (uint32_t)flags & 0x3f;
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mSize, 1, 0);
    ((IStream*)stream)->Read(&desc->mColourX, 0xc);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mAlpha, 1, 0);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mInstanceID, 1, 0);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mGroupID, 1, 0);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mWorldID, 1, 0);

    ReadAnimationCurves((IStream*)stream, (AnimVec*)&desc->mAnimationCurves);
    sub_7d10d0(stream, &desc->mModelSplitters);
    sub_7d4190(stream, &desc->mSplitControllers);
    sub_53bc90(stream, &desc->mGroups);

    int flagsToSet;
    EA::IO::ReadInt32(stream, &flagsToSet, 1, 0);
    desc->mFlagsToSet = (uint32_t)flagsToSet;
    ReadBytes(stream, &desc->mPickLevel, 1);
    ReadBytes(stream, &desc->mOverrideSet, 1);

    if (version >= 8) {
        EA::IO::ReadInt32(stream, (int32_t*)&desc->field88, 1, 0);
    } else {
        desc->mFlags &= ~4u;
        desc->field88 = 0;
    }
}

// @ 0x007d44c0  make a fresh description from a stream
void* MakeState(void* a, int b) {
    SP::cGameModelDescription* d = new ("Swarm", 0, 0, 0, 0) SP::cGameModelDescription();
    ReadDescription(a, b, d);
    return d;
}

// @ 0x007d4540
uint32_t TestKey(void* unused, const uint32_t* p, uint32_t* out, int n) {
    uint32_t lo = p[0x24 / 4];
    uint32_t hi = p[0x28 / 4];
    if ((lo & hi) != 0xffffffff) {
        if (n > 0) { out[0] = lo; out[1] = hi; out[2] = 0x102; }
        return 1;
    }
    return 0;
}

// @ 0x007d45d0
namespace EA { namespace Random {
class RandomLinearCongruential { public: double RandomDoubleUniform(); };
}}
extern EA::Random::RandomLinearCongruential gRandom;   // 0x16778dc
float __cdecl RandomRange(float a, float b) {
    double r = gRandom.RandomDoubleUniform();
    double lo = (double)a - (double)b;
    double hi = (double)a + (double)b;
    double v = r * (hi - lo) + lo;
    if (v < hi && lo <= v)
        return (float)v;
    return (float)v;
}

// @ 0x007d4620
struct cEffectParams {
    char pad[0xb4];
    IUnknown32* mUnknown[9];
    void UnknownStore(int idx, IUnknown32* p);
};
void cEffectParams::UnknownStore(int idx, IUnknown32* p) {
    IUnknown32* old = mUnknown[idx];
    if (p != old) {
        if (p) p->AddRef();
        mUnknown[idx] = p;
        if (old) old->Release();
    }
}

struct cEffectNode { void Tick(void* arg); char HandleParam(int kind, float* value, void* extra); };

// @ 0x007d4670
void cEffectNode::Tick(void* arg) {
    char* s = (char*)this;
    if (s[0x14]) {
        s[0x14] = 0;
        unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
        for (unsigned i = 0; i < n; ++i) {
            void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
            (*(void(__thiscall**)(void*, void*))((*(void***)c)[0xc / 4]))(c, arg);
        }
        void* p = *(void**)(s + 0x38);
        if (p && *(int*)((char*)p + 0x40) < 2)
            (*(void(__thiscall**)(void*, int))((*(void***)p)[0x16c / 4]))(p, 0);
    }
}

// @ 0x007d4730
char cEffectNode::HandleParam(int kind, float* value, void* extra) {
    char* s = (char*)this;
    char any = 0;
    switch (kind) {
        case 4:
            *(float*)(s + 0x2c) = *(float*)(*(int*)(s + 0xc) + 0x20) * value[0];
            any = 1; break;
        case 5:
            *(float*)(s + 0x20) = *(float*)(*(int*)(s + 0xc) + 0x14) * value[0];
            *(float*)(s + 0x24) = value[1] * *(float*)(*(int*)(s + 0xc) + 0x18);
            *(float*)(s + 0x28) = value[2] * *(float*)(*(int*)(s + 0xc) + 0x1c);
            any = 1; break;
        case 0x101:
            *(float*)(s + 0x80) = value[1];
            *(float*)(s + 0x88) = value[2];
            *(float*)(s + 0x84) = value[4];
            *(float*)(s + 0x8c) = value[5];
            any = 1; break;
        default: break;
    }
    unsigned n = (unsigned)((*(int*)(s + 0xb0) - *(int*)(s + 0xac)) >> 6);
    for (unsigned i = 0; i < n; ++i) {
        void* c = *(void**)(*(int*)(s + 0xac) + i * 0x40 + 0x3c);
        char r = (*(char(__thiscall**)(void*, int, float*, void*))((*(void***)c)[0x1c / 4]))(c, kind, value, extra);
        if (r || any) any = 1;
    }
    return any;
}

// @ 0x007d4980
// eastl vector<cSPTransform> insert: copy the transform, then
// propagate it into each live sub-entry of the element list.
struct XformVec {
    int32_t  field00;      // +0x00
    int32_t  field04;      // +0x04
    void*    p08;          // +0x08  (cSPTransform copy target)
    char     pad0c[0x34];  // +0x0c
    char*    mpBegin;      // +0x40
    char*    mpEnd;        // +0x44
    void DoInsertValue(const void* src);
};
void XformVec::DoInsertValue(const void* src) {
    ((cSPTransformOps*)((char*)this + 8))->Assign(src);
    unsigned count = (unsigned)((mpEnd - mpBegin) / 0x1c);
    unsigned off = 0;
    if (count == 0) return;
    do {
        char* base = *(char**)((char*)this + 0x40);
        int* pm = (int*)*(void**)(base + off + 4);
        int* last = (int*)*(void**)(base + off + 8);
        int* pb = last;
        while (pm != last && *pm != -2) pm = (int*)((char*)pm + 0x78);
        while (pm != pb) {
            ((cLabelOps*)((char*)pm + 4))->Propagate((char*)this + 8);
            pm = (int*)((char*)pm + 0x78);
            if (pm != last) {
                while (*pm != -2) {
                    pm = (int*)((char*)pm + 0x78);
                    if (pm == last) break;
                }
            }
        }
        off += 0x1c;
    } while (--count);
}
