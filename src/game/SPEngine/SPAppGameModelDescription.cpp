// src/game/SPEngine/SPAppGameModelDescription.cpp -- migrated from slice(s) s007d3930, s007d2a30, s007d19c0, s007d03f0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppGameModelDescription.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameModelDescription.h"
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cIParser.h"
#include <math.h>
#include "EA/IO/IStream.h"
#include <intrin.h>
#include "EA/ArgScript/cError.h"
#include "EA/Swarm/cEffectParams.h"
#include "EA/Swarm/cTransform.h"

// unnamed retail callees and globals (address in the comment)
extern const float g_1636ef4, g_1636ef8, g_1636efc;
extern char g_empty1[];   // 0x01667bac (equiv t3)
extern char g_empty2[];   // 0x01667bad (equiv t3)

// ---- items of slice s007d03f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct V3 { int a, b, c; };
struct cArguments { void** MainArguments(int); };   // 0x00838320 thiscall
struct ObjV {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
virtual void s38();
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
    virtual V3 Get(const void* in);   // slot 44
};
struct CmdBase { void Execute(cArguments* args); };
inline void* operator new(unsigned int, void* p) { return p; }
struct Matrix3 {
    float m[9];
    void Assign(const Matrix3& o);   // 0x0041cb40 thiscall
};
static float g_1485720 = 1.0f;
static void* s_vt_1411f04[1];
static void* s_vt_1411f48[1];
struct SVec {
    float* b; float* e; float* c; char alloc[4];
    SVec& operator=(const SVec& o);   // external
};
struct cSPTransform_s007d_03f0 {
    char pad[0x38];
    cSPTransform_s007d_03f0& operator=(const cSPTransform_s007d_03f0& o);   // external 0x00537dc0
};
struct TreeThing {
    TreeThing& operator=(const TreeThing& o);   // external 0x007d0b80
};
struct S0D60 {
    uint8_t b0;
    char pad1[3];
    int f4;
    uint16_t f8, fa;
    float fc, f10, f14, f18;
    Matrix3 m1c;
    float f40, f44, f48;
    TreeThing t4c;
    S0D60& operator=(const S0D60& o);
};
S0D60& S0D60::operator=(const S0D60& o)
{
    b0 = o.b0;
    f4 = o.f4;
    f8 = o.f8;
    fa = o.fa;
    fc = o.fc;
    f10 = o.f10;
    f14 = o.f14;
    f18 = o.f18;
    m1c.Assign(o.m1c);
    f40 = o.f40;
    f44 = o.f44;
    f48 = o.f48;
    t4c = o.t4c;
    return *this;
}
struct cGameModelDescription {
    void* vftable;
    int mRefCount;
    int mStateID;
    int mFlags;
    float mSize;
    float mCX, mCY, mCZ;
    float mAlpha;
    int mInstanceID;
    int mGroupID;
    int mWorldID;
    void* a30; void* a34; void* a38;
    char pad3c[4];
    void* a40;
    void* a44; void* a48; void* a4c;
    char pad50[4];
    void* a54;
    void* a58; void* a5c; void* a60;
    char pad64[8];
    void* a6c; void* a70; void* a74;
    char pad78[8];
    int a80;
    uint8_t a84, a85;
    char pad86[2];
    int a88;
    cGameModelDescription();
    ~cGameModelDescription();
};
void* __cdecl ReadI32_93a780(void* stream, void* p, int n, int endian);   // 0x0093a780
void* __cdecl ReadU8_93a6c0(void* stream, void* p, int n);                // 0x0093a6c0
struct RdElem { int32_t a; uint8_t b; uint8_t c; uint8_t pad[2]; };
struct RdVec {
    RdElem* mpBegin;
    void Resize(unsigned n);   // 0x007cf630 thiscall ret 4
};
struct S1140 {
    float f0, f4;
    SVec v8;
    float f1c;
    float f20;
    int f24;
    uint8_t f28;
    char pad29[3];
    S1140(const S1140& o);
};
struct S2C {
    int a, b;
    SVec v;
    char pad18[4];
    float f1c, f20;
    int f24;
    uint8_t f28;
    char pad29[3];
};
struct S68 {
    uint8_t b0;
    char pad1[3];
    int f4;
    cSPTransform_s007d_03f0 t8;
    int f40, f44, f48;
    TreeThing t4c;
};
void EADelete(void* p);   // 0x00f47380
struct EAString16 {
    void* mBegin; void* mEnd; void* mCapacity;
    ~EAString16() {
        if ((((int)mCapacity - (int)mBegin) & ~1) > 2 && mBegin != 0)
            EADelete(mBegin);
    }
};
struct NameKey { unsigned int a, b, c; };
struct Vec3 { float x, y, z; };
struct cArguments_s007d_03f0;
struct ModelObjV {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
virtual void s28();
virtual void s29();
virtual void s30();
virtual void s31();
virtual void s32();
virtual void s33();
virtual void s34();
virtual void s35();
virtual void s36();
virtual void s37();
    virtual float GetF(const void* in);             // slot 38 (0x98)
virtual void s39();
virtual void s40();
virtual void s41();
virtual void s42();
virtual void s43();
    virtual void GetVec(Vec3* out, const void* in); // slot 44 (0xb0)
};
struct cEffectsParser {
    void AddAnonDescription(cArguments_s007d_03f0* args, int type, cGameModelDescription* d, int flag);  // 0x00a6fd40
    void AddDescription(cArguments_s007d_03f0* args, const void* key, int type, int flag);               // 0x00a6fc30
};
struct EAError { EAError(const char* msg); };
struct cArguments_s007d_03f0 {
    char** MainArguments(int* count, int a, int b);  // 0x00838020
    void** MainArguments(int);                       // 0x00838320
    bool   HasFlag(const char*);                     // 0x008380b0
    char** OptionArguments(const char* name, int);   // 0x00838330
};
EAString16* EAConvertToString16(EAString16* out, const char* in, int len);   // 0x0093c5a0
void        SPKeyFromName(NameKey* out, const void* name, int a, int b);     // 0x0068d840
void*       EANew(int size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
typedef void (__thiscall *ReleaseFn)(void* self, int flag);
struct cGroupGameModelCommand { void Execute(cArguments_s007d_03f0* args); };
struct AppProps { AppProps(); };   // 0x0083cdd0
struct GameModelEffect : AppProps {
    GameModelEffect();
    char pad4[0x34];
    int f34;
    char desc[0x8c];
    int fc4;
    void* pc8;
    void* pcc;
    void* pd0;
};
struct GameModelSizeCommand { void Execute(cArguments_s007d_03f0* args); };
typedef float (__thiscall *ModelGetFFn)(void* self, const void* in);
void GameModelSizeCommand::Execute(cArguments_s007d_03f0* args)
{
    int self = (int)this;
    int vtbl = **(int**)(self + 4);
    void** a = args->MainArguments(1);
    *(float*)(*(int*)(self + 0xc) + 0x14) = ((ModelGetFFn)*(void**)(vtbl + 0x98))(*(void**)(self + 4), *a);
    bool fixed = args->HasFlag("fixed");
    unsigned int* pf = (unsigned int*)(*(int*)(self + 0xc) + 0x10);
    if (fixed)
        *pf |= 0x10;
    else
        *pf &= ~0x10;
}
namespace __equiv_ann1 {
struct AppProps {
    AppProps();   // 0x0083cdd0 (equiv t2)
};
}
// ---- items of slice s007d03f0 end

// ---- items of slice s007d19c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct Vec20 { void* p0; void* p1; void* p2; void* p3; void* p4; };
}
extern "C" int __cdecl isdigit(int);
extern const char* kVisibleCommands[];                   // 0x153d728
extern const char* kDeformHandleCommands[];              // 0x153d678
extern const char* kModelSplitterTypeCommands[];         // 0x153d7c8
extern const char* kModelSplitterFuzzyModeCommands[];    // 0x153d7e8
extern void* g_cmdGameModel; // 0x153d644
#pragma intrinsic(sin, cos)
#undef SUBCOMMAND
void  operator delete[](void* p);
namespace eastl {
extern wchar_t gEmptyString16[2];
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
struct allocator_s007d_19c0 { void deallocate(void* p) { operator delete[](p); } };
}
namespace eastl {
template <typename T, typename Allocator = allocator_s007d_19c0>
class basic_string_s007d_19c0 {
public:
    T* mpBegin; T* mpEnd; T* mpCapacity; Allocator mAllocator;
    basic_string_s007d_19c0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string_s007d_19c0() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf() { if (mpCapacity - mpBegin > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
}
namespace eastl {
typedef basic_string_s007d_19c0<wchar_t> string16_s007d_19c0;
// Stored/member strings use a byte-distance threshold in their dtor (retail
// 0x7d2490: `sub; cmp 1; jle`), while the temporaries returned by
// ConvertToString16 compare in element units (retail 0x7d1e40/0x7d1cc0:
// `sub; and ~1; cmp 2; jle`). Keep both so each site matches retail.
template <typename T, typename Allocator = allocator_s007d_19c0>
class basic_string_member_s007d_19c0 {
public:
    T* mpBegin; T* mpEnd; T* mpCapacity; Allocator mAllocator;
    basic_string_member_s007d_19c0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    ~basic_string_member_s007d_19c0() { DeallocateSelf(); }
    const T* c_str() const { return mpBegin; }
    void DeallocateSelf() { if ((char*)mpCapacity - (char*)mpBegin > 1) DoFree(mpBegin); }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
};
typedef basic_string_member_s007d_19c0<wchar_t> string16_member_s007d_19c0;
}
namespace EA {
eastl::string16_s007d_19c0 ConvertToString16(const char* p, int length = -1);          // 0x93c5a0
}
namespace EA {
struct ResourceKey { uint32_t a, b, c; };
}
namespace EA {
void __cdecl SPKeyFromName(void* out, const void* name, int a, int b);      // 0x68d840
}
namespace EA {
namespace ArgScript {
class cArguments_s007d_19c0 {
public:
    const char** MainArguments(int n);                          // 0x838320
    const char** MainArguments(int* count, int min, int max);   // 0x838020
    const char** OptionArguments(const char* name, int n);      // 0x838330
    bool HasFlag(const char* name);                             // 0x8380b0
};
}
}
namespace EA {
namespace ArgScript {
struct cIParser_s007d_19c0 {
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
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
    virtual void v36();
    virtual char  v37(const char* s);   // +0x94
    virtual float v38(const char* s);   // +0x98
    virtual void  v39();                // +0x9c
    virtual char  v40(const char* s);   // +0xa0
};
}
}
namespace EA {
namespace ArgScript {
uint32_t ParseEnum(const char* value, const char** table);                  // 0x840bb0
}
}
namespace EA {
namespace ArgScript {
struct cCommandBase_s007d_19c0 {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
    virtual void c4();
    virtual void AddCommand(void* key, void* cmd);   // +0x18
    cIParser_s007d_19c0* mParser;   // +0x4
    int mRefCount;       // +0x8
};
}
}
namespace EA {
namespace ArgScript {
class cBlockCommandBase : public cCommandBase_s007d_19c0 { public:
    void* mChildState;         // +0xc
    char  mCommands[0x20];     // +0x10 (hash_map)
};
}
}
namespace EA {
namespace IO {
class IStream_s007d_19c0;
}
}
namespace EA {
namespace IO {
bool ReadInt32(IStream_s007d_19c0* s, int32_t* p, unsigned n, int endian);   // 0x93a780
}
}
struct VecOps {
    void InitSplit(unsigned n, void* alloc);        // 0x7d1c60
    void InitCurve(unsigned n, void* alloc);        // 0x7d1c00
    void InitSplitter(unsigned n, void* alloc);     // 0x6a40a0
    void InitGroup(unsigned n, void* alloc);        // 0x4aa350
};
void* VecAssignSplit(void* out, void* a, void* b, void* c, void* d);  // 0x7d0dd0
void* VecAssignCurve(void* out, void* a, void* b, void* c, void* d);  // 0x7d11b0
void* VecAssignSplitter(void* out, void* a, void* b, void* c, void* d); // 0x76ffd0
void* VecInsertGroup(void* pos, void* first, unsigned bytes); // 0x11e0744
namespace SP {
struct Vec20_s007d_19c0 {
    void* p0; void* p1; void* p2; void* p3; void* p4;
    Vec20_s007d_19c0* CopySplitControllerVector(const Vec20_s007d_19c0* src);   // 0x7d2580
    Vec20_s007d_19c0* CopyAnimationCurveVector(const Vec20_s007d_19c0* src);    // 0x7d2740
};
}
namespace SP {
extern char g_vtblDescBase[];      // 0x13ef094
}
namespace SP {
extern char g_vtblDescDerived[];   // 0x1411f04
}
namespace SP {
struct cGameModelDescription_s007d_19c0 {
    void*    vtbl;            // +0x00
    int      mRefCount;       // +0x04
    int      mStateID;        // +0x08
    uint32_t mFlags;          // +0x0c
    float    mSize;           // +0x10
    float    mColourX;        // +0x14
    float    mColourY;        // +0x18
    float    mColourZ;        // +0x1c
    float    mAlpha;          // +0x20
    uint32_t mInstanceID;     // +0x24
    uint32_t mGroupID;        // +0x28
    uint32_t mWorldID;        // +0x2c
    Vec20_s007d_19c0    mAnimationCurves;  // +0x30
    Vec20_s007d_19c0    mModelSplitters;   // +0x44
    Vec20_s007d_19c0    mSplitControllers; // +0x58
    Vec20_s007d_19c0    mGroups;           // +0x6c
    uint32_t mFlagsToSet;     // +0x80
    uint8_t  mPickLevel;      // +0x84
    uint8_t  mOverrideSet;    // +0x85
    uint8_t  pad86[2];        // +0x86
    uint32_t field88;         // +0x88
    uint32_t field8c;         // +0x8c
    cGameModelDescription_s007d_19c0(const cGameModelDescription_s007d_19c0* src);  // 0x7d2830
    ~cGameModelDescription_s007d_19c0();                                  // 0x7d0f60
};
}
namespace SP {
struct cGameModelState {
    void* vtbl;                   // +0x00
    cGameModelDescription_s007d_19c0 mDesc;  // +0x04
};
}
namespace SP {
struct Matrix33 {
    union {
        float    m[9];
        uint32_t bits[9];   // same storage; retail stores RotateZ results via int registers
    };
};
}
namespace SP {
struct cTransform {
    uint16_t mFlags;              // +0x00
    uint16_t mModificationCount;  // +0x02
    float    mTranslation[3];     // +0x04
    float    mScale;              // +0x10
    Matrix33 mRotation;           // +0x14
    void RotateZ(float angle);
};
}
namespace SP {
struct cSplitController_s007d_19c0 { uint32_t mKernel; uint8_t mType; uint8_t mFuzzy; uint16_t pad; };
}
struct UVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void* a1;
    void* a2;
    void resize(unsigned n);                             // 0x4afc80
    void DoInsertValue(uint32_t* pos, const uint32_t& v); // 0x4558a0
};
struct SVec_s007d_19c0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* a1;
    void* a2;
    void DoInsertValue(void* pos, const void* v);        // 0x7e1340
};
int  FindModelKernel(const char* name, int type);        // 0xa6ebd0
struct cError_s007d_19c0 {
    cError_s007d_19c0(const char* fmt, ...);                            // 0x52df30 (cdecl ctor)
};
struct cGameModelAlphaCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelVisibleCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelFlagsCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelNameCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelWorldCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelDeformCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelSplitterCommand : EA::ArgScript::cCommandBase_s007d_19c0 {
    SP::cGameModelState* mState;
    void Execute(EA::ArgScript::cArguments_s007d_19c0& args);
};
struct cGameModelEffectCommand : EA::ArgScript::cBlockCommandBase {
    uint32_t             field30;          // +0x30
    SP::cGameModelState  mGameModelState;  // +0x34
    eastl::string16_member_s007d_19c0 mDescName;        // +0xc8
    void OnRegister(void* parser, void* childState);
    ~cGameModelEffectCommand();
};
// ---- items of slice s007d19c0 end

// ---- items of slice s007d2a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size);
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void  operator delete(void* p);                                                  // 0xf47380
struct FloatVec {                       // eastl::vector<float, sp_vector_allocator>
    float* mpBegin; float* mpEnd; float* mpCapacity; void* mAlloc1; void* mAlloc2;
    void destroy() { if (mpBegin) operator delete[](mpBegin); mpBegin = mpEnd = mpCapacity = 0; }
    void copy_from(const FloatVec& o) {
        unsigned n = (unsigned)(o.mpEnd - o.mpBegin);
        destroy();
        if (n) {
            mpBegin = new float[n]; mpEnd = mpBegin + n; mpCapacity = mpBegin + n;
            for (unsigned i = 0; i < n; ++i) mpBegin[i] = o.mpBegin[i];
        }
    }
    FloatVec& operator=(const FloatVec& o) { if (this != &o) copy_from(o); return *this; }
};
struct cAnimationCurve {                // size 0x2c
    float mX;
    float mY;
    FloatVec mCurve;                    // +0x08
    float mA;                           // +0x1c
    float mB;                           // +0x20
    float mC;                           // +0x24
    uint8_t mMode;                      // +0x28
};
struct cSPTransform_s007d_2a30 {                   // size 0x38
    float m[0x38 / 4];
    cSPTransform_s007d_2a30& operator=(const cSPTransform_s007d_2a30& o) {
        for (int i = 0; i < 0x38 / 4; ++i) m[i] = o.m[i];
        return *this;
    }
};
struct cSplitController {               // size 0x68
    uint8_t mFlags;                     // +0x00
    uint32_t mType;                     // +0x04
    cSPTransform_s007d_2a30 mTransform;            // +0x08
    uint32_t m40, m44, m48;             // +0x40
    FloatVec mCurve;                    // +0x4c
};
template <class T> struct Vec {
    T* mpBegin; T* mpEnd; T* mpCapacity; void* mAlloc1; void* mAlloc2;
};
struct cGameModelDescription_s007d_2a30 {
    void* vtbl; int mRefCount; int mStateID; uint32_t mFlags;
    float mSize; float mColourX, mColourY, mColourZ; float mAlpha;
    uint32_t mInstanceID, mGroupID, mWorldID;
    Vec<cAnimationCurve> mAnimationCurves;   // +0x30
    Vec<cSplitController> mModelSplitters;   // +0x44
    Vec<cSplitController> mSplitControllers; // +0x58
    Vec<float> mGroups;                      // +0x6c
    uint32_t mFlagsToSet; uint8_t mPickLevel, mOverrideSet, pad86[2]; uint32_t field88;
    cGameModelDescription_s007d_2a30* Assign(cGameModelDescription_s007d_2a30* src);  // 0x007d35b0 (cGameModelDescription::Assign)
};
void  AnimRangeDtor(cAnimationCurve* first, cAnimationCurve* last);              // 0x7d08e0
cAnimationCurve* AnimRangeCopyCtor(cAnimationCurve* dst, cAnimationCurve* first, cAnimationCurve* last); // 0x7d1230
void  AnimRangeAssign(cAnimationCurve* first, cAnimationCurve* last, cAnimationCurve* dst);   // 0x7d0630
void  AnimMoveRange(cAnimationCurve* dst, cAnimationCurve* src, cAnimationCurve* srcEnd);     // 0x7d1450
void  AnimFill(cAnimationCurve* first, unsigned n, const cAnimationCurve* value);            // 0x7d1380
cAnimationCurve* AnimAllocate(unsigned n);                                                  // 0x7d2610
void  AnimUninitCopy(cAnimationCurve** dst, cAnimationCurve* first, cAnimationCurve* last,
                     cAnimationCurve* pos, cAnimationCurve* junk);               // 0x7d11b0
void  SplitRangeDtor(cSplitController* first, cSplitController* last);           // 0x7d0b30
cSplitController* SplitRangeCopyCtor(cSplitController* dst, cSplitController* first, cSplitController* last); // 0x7d0e50
void  SplitRangeAssign(cSplitController* first, cSplitController* last, cSplitController* dst);   // 0x7d0a00
void  SplitMoveRange(cSplitController* dst, cSplitController* src, cSplitController* srcEnd);     // 0x7d1510
void  SplitFill(cSplitController* first, unsigned n, const cSplitController* value);             // 0x7d14b0
cSplitController* SplitAllocate(unsigned n);                                                 // 0x7d2500
void  SplitUninitCopy(cSplitController** dst, cSplitController* first, cSplitController* last,
                      cSplitController* pos, cSplitController* junk);            // 0x7d0dd0
void  SplitVecDtor(cSplitController* p);                                         // 0x7d0d60
void  FloatVecAssign(void* dst, void* src);                                      // 0x50d4e0
void  CopyState(void* dst, void* src);                                           // 0x7d2830
void  AddDescription(void* a, void* b, int c, void* d);                          // 0xa6f9c0
struct cGameModelEffectCommand_s007d_2a30 {
    char pad[0x30];
    void* mField30;        // +0x30
    char  mState[0x94];    // +0x34
    uint8_t* mStringBegin; // +0xc8
    uint8_t* mStringEnd;   // +0xcc
    void OnEndBlock(char b);  // 0x007d2ee0 (cGameModelEffectCommand::OnEndBlock)
};
// ---- items of slice s007d2a30 end

// ---- items of slice s007d3930 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float kFX2Pi;                                           // 0x163703c
extern const char* kSplitCommandsEnum[];                       // 0x153d820
namespace EA {
namespace IO {
bool ReadInt32(void* s, int32_t* p, unsigned n, int endian);   // 0x93a780
}
}
namespace EA {
namespace ArgScript {
class cArguments_s007d_3930 {
public:
    const char** MainArguments(int n);  // 0x00838320 (EA::ArgScript::cArguments::MainArguments)
    const char** MainArguments(int* count, int min, int max);  // 0x00838020 (EA::ArgScript::cArguments::MainArguments)
    const char** OptionArguments(const char* name, int n);  // 0x00838330 (EA::ArgScript::cArguments::OptionArguments)
    const char** OptionArguments(const char* name, int* count, int min, int max);  // 0x00838130 (EA::ArgScript::cArguments::OptionArguments)
    bool HasFlag(const char* name);  // 0x008380b0 (EA::ArgScript::cArguments::HasFlag)
};
}
}
bool ReadBytes(void* s, void* p, unsigned n);                  // 0x93a6c0
uint32_t FNVHash(const char* s, uint32_t seed, int a);         // 0x932e80
void* sub_7d10d0(void* stream, void* vec);                     // 0x7d10d0
void* sub_7d4190(void* stream, void* vec);                     // 0x7d4190
void* sub_53bc90(void* stream, void* vec);                     // 0x53bc90
void* sub_7d35b0(void* self, const void* src);                 // 0x7d35b0 operator=
void  sub_454cb0(void* str, const char* first, const char* last); // 0x454cb0 string assign
void* sub_a6f090(void* parser, const char** av, int count, int which); // 0xa6f090
void  sub_7d3670(void* vec, const void* elem);                 // 0x7d3670 push_back
void  sub_455660(void* vec, const float* value);               // 0x455660 push_back
int   sub_a6eb60(const char* name, int n);                     // 0xa6eb60
void* sub_f47380(void* p);                                     // 0xf47380 allocator deallocate
struct IStream_s007d_3930 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
    virtual int Read(void* dst, uint32_t size);   // +0x30
};
namespace SP {
struct cAnimationCurve_s007d_3930 {
    float mX, mY;
    Vec20 mCurve;          // +0x08
    float mA, mB, mC;      // +0x1c
    uint8_t mMode;         // +0x28
    cAnimationCurve_s007d_3930() {     // inlined default ctor (zeroes the live fields)
        mX = 0; mY = 0;
        mCurve.p0 = 0; mCurve.p1 = 0; mCurve.p2 = 0;
        mA = 0; mB = 0; mC = 0;
        mMode = 0;
    }
    ~cAnimationCurve_s007d_3930() {    // inlined vector teardown
        if (mCurve.p0 && *(int*)((char*)mCurve.p0 - 4))
            operator delete[](mCurve.p0);
    }
};
}
namespace SP {
struct cGameModelDescription_s007d_3930 {
    void* vtbl; int mRefCount; int mStateID; uint32_t mFlags;
    float mSize; float mColourX, mColourY, mColourZ; float mAlpha;
    uint32_t mInstanceID, mGroupID, mWorldID;
    Vec20 mAnimationCurves, mModelSplitters, mSplitControllers, mGroups;
    uint32_t mFlagsToSet; uint8_t mPickLevel, mOverrideSet, pad86[2]; uint32_t field88;
    cGameModelDescription_s007d_3930();           // 0x7d1010
    ~cGameModelDescription_s007d_3930();          // 0x7d0f60
};
}
namespace SP {
struct cError {
    cError(const char* fmt, ...);      // 0x52df30
    ~cError();
};
}
struct AnimVec {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* a1; void* a2;
    void resize(unsigned n);   // 0x7d3770
};
struct cGameModelState_s007d_3930 { void* vtbl; SP::cGameModelDescription_s007d_3930 mDesc; };
struct cGameModelAnimateCommand {
    void* mParser;         // +0x4
    cGameModelState_s007d_3930* mState;   // +0xc
    void Execute(EA::ArgScript::cArguments_s007d_3930& args);
};
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
    cGameModelState_s007d_3930* mState;          // +0x0c
    void Execute(EA::ArgScript::cArguments_s007d_3930& args);
};
struct cGameModelEffectCommand_s007d_3930 {
    void* mParser;              // +0x04  (cIParser*, used for the final vcall)
    void* mField30;             // +0x30  inherited-source pointer
    void* mVtbl34;              // +0x34
    void* mDesc;                // +0x38  owned cGameModelDescription
    void* mFieldC4;             // +0xc4
    void* mName;                // +0xc8  eastl::string
    void  Execute(EA::ArgScript::cArguments_s007d_3930& args);
};
// ---- items of slice s007d3930 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
IStream_s007d_3930* ReadAnimationCurves(IStream_s007d_3930* stream, AnimVec* vec);  // 0x007d40f0 (stays in the slice: not this object's)

// @ 0x007d1010
cGameModelDescription::cGameModelDescription()
{
    mRefCount = 0;
    mStateID = 0xebb8e524;
    *(uint32_t*)this = (uint32_t)s_vt_1411f04;
    mFlags = 0;
    mSize = g_1485720;
    mCX = g_1636ef4;
    mCY = g_1636ef8;
    mCZ = g_1636efc;
    mAlpha = g_1485720;
    mInstanceID = 0;
    mGroupID = 0;
    mWorldID = 0;
    a30 = 0; a34 = 0; a38 = 0;
    a44 = 0; a48 = 0; a4c = 0;
    a58 = 0; a5c = 0; a60 = 0;
    a6c = 0; a70 = 0; a74 = 0;
    a80 = 0;
    a84 = 0;
    a85 = 0;
    a88 = 0;
}

// @ 0x007d10d0
void* ReadVec(void* stream, RdVec* vec)
{
    unsigned count;
    ReadI32_93a780(stream, &count, 1, 0);
    vec->Resize(count);
    for (unsigned i = 0; i < count; ++i) {
        RdElem* e = &vec->mpBegin[i];
        ReadI32_93a780(stream, &e->a, 1, 0);
        ReadU8_93a6c0(stream, &e->b, 1);
        ReadU8_93a6c0(stream, &e->c, 1);
    }
    return stream;
}

// @ 0x007d1140
S1140::S1140(const S1140& o)
{
    f0 = o.f0;
    f4 = o.f4;
    v8 = o.v8;
    f1c = o.f1c;
    f20 = o.f20;
    f24 = o.f24;
    f28 = o.f28;
}

// @ 0x007d12c0
S2C* CopyRange12C0(S2C* first, S2C* last, S2C* dst)
{
    while (first != last) {
        dst->a = first->a;
        dst->b = first->b;
        dst->v = first->v;
        dst->f1c = first->f1c;
        dst->f20 = first->f20;
        dst->f24 = first->f24;
        dst->f28 = first->f28;
        first = (S2C*)((char*)first + 0x2c);
        dst = (S2C*)((char*)dst + 0x2c);
    }
    return dst;
}

// @ 0x007d1320
char* CopyRange1320(char* first, char* last, char* dst)
{
    while (first != last) {
        S68* d = (S68*)dst;
        S68* s = (S68*)first;
        d->b0 = s->b0;
        d->f4 = s->f4;
        d->t8 = s->t8;
        d->f40 = s->f40;
        d->f44 = s->f44;
        d->f48 = s->f48;
        d->t4c = s->t4c;
        first += 0x68;
        dst += 0x68;
    }
    return dst;
}

// @ 0x007d1380
void AssignRange1380(S2C* first, S2C* last, S2C* src)
{
    while (first != last) {
        first->a = src->a;
        first->b = src->b;
        first->v = src->v;
        first->f1c = src->f1c;
        first->f20 = src->f20;
        first->f24 = src->f24;
        first->f28 = src->f28;
        first = (S2C*)((char*)first + 0x2c);
    }
}

// @ 0x007d1450
S2C* CopyBack1450(S2C* first, S2C* last, S2C* dst)
{
    while (last != first) {
        last = (S2C*)((char*)last - 0x2c);
        dst = (S2C*)((char*)dst - 0x2c);
        dst->a = last->a;
        dst->b = last->b;
        dst->v = last->v;
        dst->f1c = last->f1c;
        dst->f20 = last->f20;
        dst->f24 = last->f24;
        dst->f28 = last->f28;
    }
    return dst;
}

// @ 0x007d14b0
void AssignRange14B0(char* first, char* last, char* src)
{
    while (first != last) {
        S68* d = (S68*)first;
        S68* s = (S68*)src;
        d->b0 = s->b0;
        d->f4 = s->f4;
        d->t8 = s->t8;
        d->f40 = s->f40;
        d->f44 = s->f44;
        d->f48 = s->f48;
        d->t4c = s->t4c;
        first += 0x68;
    }
}

// @ 0x007d1510
char* CopyBack1510(char* first, char* last, char* dst)
{
    while (last != first) {
        last -= 0x68;
        dst -= 0x68;
        S68* d = (S68*)dst;
        S68* s = (S68*)last;
        d->b0 = s->b0;
        d->f4 = s->f4;
        d->t8 = s->t8;
        d->f40 = s->f40;
        d->f44 = s->f44;
        d->f48 = s->f48;
        d->t4c = s->t4c;
    }
    return dst;
}

// @ 0x007d1570
void cGroupGameModelCommand::Execute(cArguments_s007d_03f0* args)
{
    int self = (int)this;
    int count = 0;
    char** argv = args->MainArguments(&count, 0, 1);
    if (count != 0) {
        ((cEffectsParser*)*(int*)(self + 0xc))->AddDescription(args, argv[0], 0x25, 0);
        return;
    }

    cGameModelDescription* desc = (cGameModelDescription*)EANew(0x8c, "Swarm", 0, 0, 0, 0);
    if (desc != 0)
        desc = new (desc) cGameModelDescription();
    if (desc != 0)
        desc->mRefCount++;

    char** a = args->OptionArguments("name", 1);
    if (a == 0)
        throw EAError("Need at least -name for anonymous modelEffect");
    NameKey key; key.a = 0; key.b = 0; key.c = 0;
    {
        EAString16 s;
        EAConvertToString16(&s, a[0], -1);
        SPKeyFromName(&key, s.mBegin, 0, 0);
    }
    desc->mInstanceID = (int)key.a;
    desc->mGroupID = (int)key.c;

    a = args->OptionArguments("size", 1);
    if (a != 0)
        desc->mSize = (*(ModelObjV**)(self + 4))->GetF(a[0]);

    a = args->OptionArguments("color", 1);
    if (a != 0) {
        Vec3 v;
        (*(ModelObjV**)(self + 4))->GetVec(&v, a[0]);
        desc->mCX = v.x;
        desc->mCY = v.y;
        desc->mCZ = v.z;
    }

    a = args->OptionArguments("alpha", 1);
    if (a != 0)
        desc->mAlpha = (*(ModelObjV**)(self + 4))->GetF(a[0]);

    a = args->OptionArguments("world", 1);
    if (a != 0) {
        NameKey key; key.a = 0; key.b = 0; key.c = 0;
        {
            EAString16 s;
            EAConvertToString16(&s, a[0], -1);
            SPKeyFromName(&key, s.mBegin, 0, 0);
        }
        desc->mWorldID = (int)key.a;
    }

    a = args->OptionArguments("group", 1);
    if (a != 0) {
        NameKey key; key.a = 0; key.b = 0; key.c = 0;
        {
            EAString16 s;
            EAConvertToString16(&s, a[0], -1);
            SPKeyFromName(&key, s.mBegin, 0, 0);
        }
        desc->mGroupID = (int)key.a;
    }

    a = args->OptionArguments("message", 1);
    if (a != 0) {
        NameKey key; key.a = 0; key.b = 0; key.c = 0;
        {
            EAString16 s;
            EAConvertToString16(&s, a[0], -1);
            SPKeyFromName(&key, s.mBegin, 0, 0);
        }
        desc->a88 = (int)key.a;
        desc->mFlags |= 4;
    }

    ((cEffectsParser*)*(int*)(self + 0xc))->AddAnonDescription(args, 0x25, desc, 0);
    if (--desc->mRefCount == 0) {
        desc->mRefCount = 1;
        ((ReleaseFn)(desc->vftable))(desc, 1);
    }
}

// @ 0x007d18c0
GameModelEffect::GameModelEffect()
{
    *(uint32_t*)this = (uint32_t)s_vt_1411f48;
    f34 = 0x30bac64;
    new (desc) cGameModelDescription();
    fc4 = 0;
    pc8 = &g_empty1;
    pcc = &g_empty1;
    pd0 = &g_empty2;
}

// @ 0x007d1910
void FUN_007d1910(int self, void* args)
{
    (void)self; (void)args;
}

// @ 0x007d1970
void CmdBase::Execute(cArguments* args)
{
    int self = (int)this;
    ObjV* obj = *(ObjV**)(self + 4);
    void** a = args->MainArguments(1);
    V3 v = obj->Get(*a);
    *(V3*)(*(int*)(self + 0xc) + 0x18) = v;
}

// @ 0x007d19c0
void cGameModelAlphaCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    mState->mDesc.mAlpha = mParser->v38(args.MainArguments(1)[0]);
}

// @ 0x007d19f0
void cGameModelVisibleCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    const char** av = args.MainArguments(1);
    char b = mParser->v37(av[0]);
    uint32_t* p = &mState->mDesc.mFlags;
    if (b) *p |= 8; else *p &= ~8u;
}

// @ 0x007d1a30
void cGameModelFlagsCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);
    for (int i = 0; i < count; ++i) {
        uint32_t e = EA::ArgScript::ParseEnum(av[i], kVisibleCommands);
        if (e < 0x20)
            mState->mDesc.mFlagsToSet |= 1u << (e & 0x1f);
    }
}

// @ 0x007d1ac0
void SP::cTransform::RotateZ(float angle)
{
    float s = (float)sin((double)angle);
    float c = (float)cos((double)angle);
    float m0 = mRotation.m[0], m1 = mRotation.m[1], m2 = mRotation.m[2];
    float m3 = mRotation.m[3], m4 = mRotation.m[4], m5 = mRotation.m[5];
    float r0 = m0 * c + m3 * s;
    float r1 = m1 * c + m4 * s;
    float r2 = m2 * c + m5 * s;
    mRotation.bits[0] = *(uint32_t*)&r0;
    mRotation.bits[1] = *(uint32_t*)&r1;
    mRotation.bits[2] = *(uint32_t*)&r2;
    mFlags |= 2;
    mModificationCount++;
    float r3 = -m0 * s + m3 * c;
    float r4 = -m1 * s + m4 * c;
    float r5 = -m2 * s + m5 * c;
    mRotation.bits[3] = *(uint32_t*)&r3;
    mRotation.bits[4] = *(uint32_t*)&r4;
    mRotation.bits[5] = *(uint32_t*)&r5;
}

// @ 0x007d1cc0
void cGameModelNameCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    eastl::string16_s007d_19c0 s = EA::ConvertToString16(args.MainArguments(1)[0], -1);
    EA::ResourceKey key;
    EA::SPKeyFromName(&key, s.c_str(), 0, 0);
    mState->mDesc.mInstanceID = key.a;
    mState->mDesc.mGroupID = key.c;
    const char** msg = args.OptionArguments("message", 1);
    if (msg) {
        eastl::string16_s007d_19c0 s2 = EA::ConvertToString16(msg[0], -1);
        EA::ResourceKey key2;
        EA::SPKeyFromName(&key2, s2.c_str(), 0, 0);
        mState->mDesc.field88 = key2.a;
        mState->mDesc.mFlags |= 4;
    }
    const char** ov = args.OptionArguments("overrideSet", 1);
    if (ov)
        mState->mDesc.mOverrideSet = mParser->v40(ov[0]);
    else
        mState->mDesc.mOverrideSet = 0;
    if (args.HasFlag("noAttachments"))
        mState->mDesc.mFlags |= 0x20;
}

// @ 0x007d1e40
void cGameModelWorldCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    eastl::string16_s007d_19c0 s = EA::ConvertToString16(args.MainArguments(1)[0], -1);
    EA::ResourceKey key = {0, 0, 0};
    EA::SPKeyFromName(&key, s.c_str(), 0, 0);
    mState->mDesc.mWorldID = key.a;
}

// @ 0x007d2330
void cGameModelDeformCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);
    for (int i = 0; i < count; ++i) {
        uint32_t v;
        if (isdigit((unsigned char)av[i][0]))
            v = mParser->v40(av[i]);
        else
            v = EA::ArgScript::ParseEnum(av[i], kDeformHandleCommands);
        UVec* g = (UVec*)&mState->mDesc.mGroups;
        uint32_t* end = g->mpEnd;
        if (end < g->mpCapacity) {
            g->mpEnd = end + 1;
            if (end) *end = v;
        } else {
            g->DoInsertValue(end, v);
        }
    }
}

// @ 0x007d23d0
void cGameModelSplitterCommand::Execute(EA::ArgScript::cArguments_s007d_19c0& args)
{
    const char** av = args.MainArguments(3);
    int kernel = FindModelKernel(av[0], 0x10);
    if (kernel < 0)
        throw cError_s007d_19c0("Unknown split model kernel: %s", av[0]);
    SP::cSplitController_s007d_19c0 sc;
    sc.mKernel = kernel;
    sc.mType  = (uint8_t)EA::ArgScript::ParseEnum(av[1], kModelSplitterTypeCommands);
    sc.mFuzzy = (uint8_t)EA::ArgScript::ParseEnum(av[2], kModelSplitterFuzzyModeCommands);
    SVec_s007d_19c0* v = (SVec_s007d_19c0*)&mState->mDesc.mModelSplitters;
    void* end = v->mpEnd;
    if (end < v->mpCapacity) {
        v->mpEnd = (char*)end + 8;
        if (end) { *(uint32_t*)end = sc.mKernel; *((uint32_t*)end + 1) = ((uint32_t*)&sc)[1]; }
    } else {
        v->DoInsertValue(end, &sc);
    }
}

// @ 0x007d2490
cGameModelEffectCommand::~cGameModelEffectCommand()
{
}

// @ 0x007d2580
SP::Vec20_s007d_19c0* SP::Vec20_s007d_19c0::CopySplitControllerVector(const Vec20_s007d_19c0* src)
{
    ((VecOps*)this)->InitSplit(
        (unsigned)(((char*)((const void**)src)[1] - (char*)((const void**)src)[0]) / 0x68),
        (char*)src + 0xc);
    void* tmp = 0;
    VecAssignSplit(&tmp, ((void**)src)[0], ((void**)src)[1], *(void**)this, (void*)src);
    *(void**)((char*)this + 4) = tmp;
    return this;
}

// @ 0x007d2670
void SWARM_GameModelAddCommands(void* unused, void* server, int* parserVtbl)
{
    cGameModelEffectCommand* effect = 0;
    cGroupGameModelCommand*   group  = 0;
    if (parserVtbl) {
        ((void(__thiscall*)(void*, void*, void*))((*(void***)server)[0x14 / 4]))(server, g_cmdGameModel, effect);
    }
    ((void(__thiscall*)(void*, void*, void*))((*(void***)server)[0x18 / 4]))(server, g_cmdGameModel, group);
}

// @ 0x007d2740
SP::Vec20_s007d_19c0* SP::Vec20_s007d_19c0::CopyAnimationCurveVector(const Vec20_s007d_19c0* src)
{
    ((VecOps*)this)->InitCurve(
        (unsigned)(((char*)((const void**)src)[1] - (char*)((const void**)src)[0]) / 0x2c),
        (char*)src + 0xc);
    void* tmp = 0;
    VecAssignCurve(&tmp, ((void**)src)[0], ((void**)src)[1], *(void**)this, (void*)src);
    *(void**)((char*)this + 4) = tmp;
    return this;
}

// @ 0x007d27d0
void* ReadIntVector(void* stream, void* vec)
{
    int count;
    EA::IO::ReadInt32((EA::IO::IStream_s007d_19c0*)stream, &count, 1, 0);
    UVec* v = (UVec*)vec;
    v->resize((unsigned)count);
    for (unsigned i = 0; i < (unsigned)count; ++i)
        EA::IO::ReadInt32((EA::IO::IStream_s007d_19c0*)stream, (int32_t*)&v->mpBegin[i], 1, 0);
    return stream;
}

// @ 0x007d2830
SP::cGameModelDescription_s007d_19c0::cGameModelDescription_s007d_19c0(const cGameModelDescription_s007d_19c0* src)
{
    vtbl = SP::g_vtblDescBase;
    mRefCount = 0;
    mStateID = *(int*)(src ? (const char*)src + 8 : 0);
    vtbl = SP::g_vtblDescDerived;
    mFlags = src->mFlags;
    mSize = src->mSize;
    mColourX = src->mColourX;
    mColourY = src->mColourY;
    mColourZ = src->mColourZ;
    mAlpha = src->mAlpha;
    mInstanceID = src->mInstanceID;
    mGroupID = src->mGroupID;
    mWorldID = src->mWorldID;
    mAnimationCurves.CopyAnimationCurveVector(&src->mAnimationCurves);
    ((VecOps*)&mModelSplitters)->InitSplitter(
        (unsigned)(((char*)((const void**)&src->mModelSplitters)[1] -
                    (char*)((const void**)&src->mModelSplitters)[0]) >> 3),
        (char*)&src->mModelSplitters + 0xc);
    {
        void* tmp = 0;
        VecAssignSplitter(&tmp, ((void**)&src->mModelSplitters)[0], ((void**)&src->mModelSplitters)[1],
                          *(void**)&mModelSplitters, (void*)src);
        *(void**)((char*)&mModelSplitters + 4) = tmp;
    }
    mSplitControllers.CopySplitControllerVector(&src->mSplitControllers);
    ((VecOps*)&mGroups)->InitGroup(
        (unsigned)(((char*)((const void**)&src->mGroups)[1] -
                    (char*)((const void**)&src->mGroups)[0]) >> 2),
        (char*)&src->mGroups + 0xc);
    {
        unsigned bytes = (unsigned)((char*)((const void**)&src->mGroups)[1] -
                                    (char*)((const void**)&src->mGroups)[0]);
        void* end = VecInsertGroup(*(void**)&mGroups, ((void**)&src->mGroups)[0], bytes);
        *(void**)((char*)&mGroups + 4) = (char*)end + ((int)bytes >> 2) * 4;
    }
    mFlagsToSet = src->mFlagsToSet;
    mPickLevel = src->mPickLevel;
    mOverrideSet = src->mOverrideSet;
    field88 = src->field88;
}

// @ 0x007d2a30
void AnimDoInsertValue(Vec<cAnimationCurve>* v, cAnimationCurve* pos, unsigned n, cAnimationCurve* value)
{
    unsigned cap = (unsigned)((v->mpEnd - v->mpBegin));
    if (cap >= n) {
        if (n) {
            unsigned count = (unsigned)((v->mpEnd - pos) / 1);
            (void)count;
        }
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN * 2; if (oldN == 0) newCap = 1;
    unsigned need = oldN + n; if (need > newCap) newCap = need; else if (newCap < need) newCap = need;
    cAnimationCurve* buf = newCap ? (cAnimationCurve*)(void*)operator new(newCap * sizeof(cAnimationCurve), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* mid = AnimRangeCopyCtor(buf, v->mpBegin, pos);
    AnimRangeAssign(pos, v->mpEnd, mid);
    AnimFill(mid, n, value);
    cAnimationCurve* end = AnimRangeCopyCtor(mid + n, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d2c70
void SplitDoInsertValue(Vec<cSplitController>* v, cSplitController* pos, unsigned n, cSplitController* value)
{
    unsigned cap = (unsigned)(v->mpEnd - v->mpBegin);
    if (cap >= n) {
        if (n) {
            unsigned count = (unsigned)(v->mpEnd - pos);
            (void)count;
        }
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN * 2; if (oldN == 0) newCap = 1;
    unsigned need = oldN + n; if (need > newCap) newCap = need;
    cSplitController* buf = newCap ? (cSplitController*)(void*)operator new(newCap * sizeof(cSplitController), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* mid = SplitRangeCopyCtor(buf, v->mpBegin, pos);
    SplitRangeAssign(pos, v->mpEnd, mid);
    SplitFill(mid, n, value);
    cSplitController* end = SplitRangeCopyCtor(mid + n, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d2ee0
void cGameModelEffectCommand_s007d_2a30::OnEndBlock(char b)
{
    if (b == 0) {
        void* s = operator new(0x8c, "Swarm", 0, 0, 0, 0);
        if (s) CopyState(s, &mState[4]);
        else s = 0;
        AddDescription(mField30, mStringBegin, 0x25, s);
    }
    if (mStringBegin != mStringEnd) {
        *mStringBegin = 0;
        mStringEnd = mStringBegin;
    }
}

// @ 0x007d2f90
Vec<cAnimationCurve>* AnimVecAssign(Vec<cAnimationCurve>* self, Vec<cAnimationCurve>* src)
{
    if (src == self) return self;
    unsigned n = (unsigned)(src->mpEnd - src->mpBegin);
    unsigned cap = (unsigned)(self->mpCapacity - self->mpBegin);
    if (cap < n) {
        cAnimationCurve* buf = (cAnimationCurve*)AnimAllocate(n);
        AnimRangeDtor(self->mpBegin, self->mpEnd);
        if (self->mpBegin) operator delete[](self->mpBegin);
        self->mpBegin = buf; self->mpEnd = buf + n; self->mpCapacity = buf + n;
        return self;
    }
    unsigned m = (unsigned)(self->mpEnd - self->mpBegin);
    if (m < n) {
        AnimRangeAssign(src->mpBegin, src->mpBegin + m, self->mpBegin);
        AnimUninitCopy(&src->mpEnd, src->mpBegin + m, src->mpEnd, self->mpEnd, src->mpEnd);
        self->mpEnd = self->mpBegin + n;
    } else {
        AnimRangeAssign(src->mpBegin, src->mpEnd, self->mpBegin);
        AnimRangeDtor(self->mpBegin + n, self->mpEnd);
        self->mpEnd = self->mpBegin + n;
    }
    return self;
}

// @ 0x007d30d0
Vec<cSplitController>* SplitVecAssign(Vec<cSplitController>* self, Vec<cSplitController>* src)
{
    if (src == self) return self;
    unsigned n = (unsigned)(src->mpEnd - src->mpBegin);
    unsigned cap = (unsigned)(self->mpCapacity - self->mpBegin);
    if (cap < n) {
        cSplitController* buf = (cSplitController*)SplitAllocate(n);
        SplitRangeDtor(self->mpBegin, self->mpEnd);
        if (self->mpBegin) operator delete[](self->mpBegin);
        self->mpBegin = buf; self->mpEnd = buf + n; self->mpCapacity = buf + n;
        return self;
    }
    unsigned m = (unsigned)(self->mpEnd - self->mpBegin);
    if (m < n) {
        SplitRangeAssign(src->mpBegin, src->mpBegin + m, self->mpBegin);
        SplitUninitCopy(&src->mpEnd, src->mpBegin + m, src->mpEnd, self->mpEnd, src->mpEnd);
        self->mpEnd = self->mpBegin + n;
    } else {
        SplitRangeAssign(src->mpBegin, src->mpEnd, self->mpBegin);
        SplitRangeDtor(self->mpBegin + n, self->mpEnd);
        self->mpEnd = self->mpBegin + n;
    }
    return self;
}

// @ 0x007d3210
void AnimVecInsert(Vec<cAnimationCurve>* v, cAnimationCurve* pos, cAnimationCurve* value)
{
    if (v->mpEnd != v->mpCapacity) {
        cAnimationCurve* p = (pos <= value && value < v->mpEnd) ? value + 1 : value;
        if (v->mpEnd) AnimRangeDtor(v->mpEnd - 1, v->mpEnd);
        AnimMoveRange(pos, v->mpEnd - 1, v->mpEnd);
        *pos = *p; pos->mCurve = p->mCurve; pos->mA = p->mA; pos->mB = p->mB; pos->mC = p->mC; pos->mMode = p->mMode;
        v->mpEnd = v->mpEnd + 1;
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN ? oldN * 2 : 1;
    cAnimationCurve* buf = newCap ? (cAnimationCurve*)(void*)operator new(newCap * sizeof(cAnimationCurve), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cAnimationCurve* mid = AnimRangeCopyCtor(buf, v->mpBegin, pos);
    AnimRangeAssign(pos, v->mpEnd, mid);
    *mid = *value; mid->mCurve = value->mCurve; mid->mA = value->mA; mid->mB = value->mB; mid->mC = value->mC; mid->mMode = value->mMode;
    cAnimationCurve* end = AnimRangeCopyCtor(mid + 1, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d33e0
void SplitVecInsert(Vec<cSplitController>* v, cSplitController* pos, cSplitController* value)
{
    if (v->mpEnd != v->mpCapacity) {
        cSplitController* p = (pos <= value && value < v->mpEnd) ? value + 1 : value;
        if (v->mpEnd) SplitVecDtor(v->mpEnd - 1);
        SplitMoveRange(pos, v->mpEnd - 1, v->mpEnd);
        pos->mFlags = p->mFlags; pos->mType = p->mType; pos->mTransform = p->mTransform;
        pos->m40 = p->m40; pos->m44 = p->m44; pos->m48 = p->m48; pos->mCurve = p->mCurve;
        v->mpEnd = v->mpEnd + 1;
        return;
    }
    unsigned oldN = (unsigned)(v->mpEnd - v->mpBegin);
    unsigned newCap = oldN ? oldN * 2 : 1;
    cSplitController* buf = newCap ? (cSplitController*)(void*)operator new(newCap * sizeof(cSplitController), "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
    cSplitController* mid = SplitRangeCopyCtor(buf, v->mpBegin, pos);
    SplitRangeAssign(pos, v->mpEnd, mid);
    mid->mFlags = value->mFlags; mid->mType = value->mType; mid->mTransform = value->mTransform;
    mid->m40 = value->m40; mid->m44 = value->m44; mid->m48 = value->m48; mid->mCurve = value->mCurve;
    cSplitController* end = SplitRangeCopyCtor(mid + 1, pos, v->mpEnd);
    if (v->mpBegin) operator delete[](v->mpBegin);
    v->mpBegin = buf; v->mpEnd = end; v->mpCapacity = buf + newCap;
}

// @ 0x007d35b0
cGameModelDescription_s007d_2a30* cGameModelDescription_s007d_2a30::Assign(cGameModelDescription_s007d_2a30* src)
{
    cGameModelDescription_s007d_2a30* self = this;
    self->mStateID = src ? src->mStateID : 0;
    self->mFlags = src->mFlags;
    self->mSize = src->mSize;
    self->mColourX = src->mColourX; self->mColourY = src->mColourY; self->mColourZ = src->mColourZ;
    self->mAlpha = src->mAlpha;
    self->mInstanceID = src->mInstanceID;
    self->mGroupID = src->mGroupID;
    self->mWorldID = src->mWorldID;
    AnimVecAssign(&self->mAnimationCurves, &src->mAnimationCurves);
    SplitVecAssign(&self->mModelSplitters, &src->mModelSplitters);
    SplitVecAssign(&self->mSplitControllers, &src->mSplitControllers);
    FloatVecAssign(&self->mGroups, &src->mGroups);
    self->mFlagsToSet = src->mFlagsToSet;
    self->mPickLevel = src->mPickLevel;
    self->mOverrideSet = src->mOverrideSet;
    self->field88 = src->field88;
    return self;
}

// @ 0x007d3770
void AnimVecResize(Vec<cAnimationCurve>* v, unsigned n)
{
    cAnimationCurve* begin = v->mpBegin;
    cAnimationCurve* end = v->mpEnd;
    if ((unsigned)(end - begin) < n) {
        cAnimationCurve tmp;
        unsigned i;
        tmp.mX = 0; tmp.mY = 0;
        tmp.mCurve.mpBegin = tmp.mCurve.mpEnd = tmp.mCurve.mpCapacity = 0; tmp.mCurve.mAlloc1 = tmp.mCurve.mAlloc2 = 0;
        tmp.mA = 0; tmp.mB = 0; tmp.mC = 0; tmp.mMode = 0;
        AnimDoInsertValue(v, end, n - (unsigned)(end - begin), &tmp);
        tmp.mCurve.destroy();
    }
}

// @ 0x007d3860
void SplitVecResize(Vec<cSplitController>* v, unsigned n)
{
    cSplitController* begin = v->mpBegin;
    cSplitController* end = v->mpEnd;
    if ((unsigned)(end - begin) < n) {
        cSplitController tmp;
        tmp.mFlags = 0; tmp.mType = 0;
        for (int i = 0; i < 0x38 / 4; ++i) tmp.mTransform.m[i] = 0;
        tmp.m40 = tmp.m44 = tmp.m48 = 0;
        tmp.mCurve.mpBegin = tmp.mCurve.mpEnd = tmp.mCurve.mpCapacity = 0; tmp.mCurve.mAlloc1 = tmp.mCurve.mAlloc2 = 0;
        SplitDoInsertValue(v, end, n - (unsigned)(end - begin), &tmp);
        tmp.mCurve.destroy();
    } else {
        // shrink: destroy [begin+n, end)
    }
}

// @ 0x007d3930
void cGameModelAnimateCommand::Execute(EA::ArgScript::cArguments_s007d_3930& args)
{
    int count;
    const char** av = args.MainArguments(&count, 1, 0x7fffffff);

    // Append a default-constructed animation curve to the description's curve
    // list; `e` then points at the copy that now sits at the end of that list.
    SP::cAnimationCurve_s007d_3930 curve;
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
void cGameModelSplitCommand::Execute(EA::ArgScript::cArguments_s007d_3930& args)
{
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
void cGameModelEffectCommand_s007d_3930::Execute(EA::ArgScript::cArguments_s007d_3930& args)
{
    int count;
    const char** av = args.MainArguments(&count, 1, 3);

    const char* s = av[0];
    const char* end = s;
    while (*end) ++end;
    sub_454cb0((char*)this + 0xc8, s, end);

    SP::cGameModelDescription_s007d_3930 tmp;
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
void __cdecl ReadDescription(void* stream, int version, SP::cGameModelDescription_s007d_3930* desc)
{
    int flags;
    EA::IO::ReadInt32(stream, &flags, 1, 0);
    desc->mFlags = (uint32_t)flags & 0x3f;
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mSize, 1, 0);
    ((IStream_s007d_3930*)stream)->Read(&desc->mColourX, 0xc);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mAlpha, 1, 0);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mInstanceID, 1, 0);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mGroupID, 1, 0);
    EA::IO::ReadInt32(stream, (int32_t*)&desc->mWorldID, 1, 0);

    ReadAnimationCurves((IStream_s007d_3930*)stream, (AnimVec*)&desc->mAnimationCurves);
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

// @ 0x007d44c0
void* MakeState(void* a, int b)
{
    SP::cGameModelDescription_s007d_3930* d = new ("Swarm", 0, 0, 0, 0) SP::cGameModelDescription_s007d_3930();
    ReadDescription(a, b, d);
    return d;
}
