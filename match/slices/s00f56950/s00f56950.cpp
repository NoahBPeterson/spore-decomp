// Slice s00f56950 -- SPEngine/SPAppCloudDescription.obj, the cloud effect command family.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };

extern "C" void* __cdecl memcpy(void* dst, const void* src, size_t n);                    // 0x011e0744
extern "C" __declspec(dllimport) char* __cdecl strstr(const char* s, const char* pat);    // 0x013cc538

extern const char* PTR_s_cloud;         // 0x015b0af4  ("cloud")
extern uint32_t    DAT_015b0bfc;        // 0x015b0bfc
extern uint16_t    gEmptyString16[];    // 0x01667bac

inline void* operator new(size_t, void* p) throw() { return p; }

namespace EA {
namespace ArgScript {

#define PV(n) virtual void pv##n();
class cIParser { public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37)
    virtual float GetFloat(const char* text);              // +0x98
    PV(39) PV(40) PV(41) PV(42) PV(43)
    virtual Vec3 GetVector2(const char* text);             // +0xb0
};
#undef PV

class cArguments { public:
    const char** MainArguments(int* count, int minCount, int maxCount);                   // 0x00838020
    const char** MainArguments(int count);                                                // 0x00838320
    const char** OptionArguments(const char* name, int count);                            // 0x00838330
    const char** OptionArguments(const char* name, int* count, int minCount, int maxCount); // 0x00838130
    bool         HasFlag(const char* flag);                                               // 0x008380b0
    const char*  operator[](int index);                                                   // 0x00837f20
};

class cICommand { public: virtual void AddRef(); virtual void Release(); virtual void Cast(); };
class cCommandBase : public cICommand { public:
    cIParser* mParser;      // +0x4
    int       mRefCount;    // +0x8
    cCommandBase();         // 0x0083c800
};

}  // namespace ArgScript
}  // namespace EA

void*  __cdecl EAAllocate(uint32_t size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void   __cdecl FUN_007ecc30(float scale, void* vec);                                      // 0x007ecc30
float* __cdecl FUN_00aa2fe0(float* out, EA::ArgScript::cIParser* parser,
                            const char** opt, int count);                                 // 0x00aa2fe0
void   __cdecl FUN_00f52b80(EA::ArgScript::cArguments& args, void* state,
                            EA::ArgScript::cIParser* parser);                             // 0x00f52b80

namespace SP {
template <class T> struct SimpleVector {                        // eastl::vector<T, sp_vector_allocator>
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void DoInsertValue(T* pos, const T& value);                  // 0x00455660
    void AllocateCopy(int count, const void* allocator);          // 0x004aa350
    void resize(int count);                                      // 0x004afc80
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T* erase(T* first, T* last) {
        memcpy(first, last, (uint32_t)((char*)mpEnd - (char*)last));
        mpEnd = mpEnd - (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

template <class T> struct Vector {                               // out-of-line erase / DoInsertValue
    T*       mpBegin;
    T*       mpEnd;
    T*       mpCapacity;
    uint32_t mAllocator[2];

    void DoInsertValue(T* pos, const T& value);                  // 0x007ed1b0
    T* erase(T* first, T* last);                                 // 0x009e0480
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { erase(mpBegin, mpEnd); }
};
}  // namespace SP

// The command "state" object shared by the loop / speed / delay commands.  It is the
// cCloudEffectCommand embedded in cCloudEffect seen from 8 bytes before its own start.
struct cCloudState {
    char     pad00[0x10];
    uint32_t mFlags;                       // +0x10
    char     pad14[0x20 - 0x14];
    float    mDelayLo;                     // +0x20
    float    mDelayHi;                     // +0x24
    float    mTriggerLo;                   // +0x28
    float    mTriggerHi;                   // +0x2c
    char     pad30[0x6c - 0x30];
    SP::SimpleVector<float> mCurve;        // +0x6c
    float    mScale;                       // +0x80
    uint16_t mMode;                        // +0x84
    char     pad86[0x188 - 0x86];
    SP::Vector<Vec3> mBoxColor;            // +0x188
    SP::SimpleVector<float> mCurve2;       // +0x19c
};

// ---- cCloudEffectCommand : the 0x268-byte effect command embedded in cCloudEffect --------
struct SubD0
{
    uint32_t w[5];
    void AssignFrom(const SubD0& src);      // 0x006f50f0
};
struct Sub164
{
    uint32_t w[5];
    void AssignFrom(const Sub164& src);     // 0x00a9a310
};
struct Sub180
{
    uint32_t w[5];
    void AssignFrom(const Sub180& src);     // 0x006f50f0
};
struct Sub1a8
{
    uint32_t w[5];
    void AssignFrom(const Sub1a8& src);     // 0x00a87920
};
struct Sub1f8
{
    uint32_t w[13];
    void AssignFrom(const Sub1f8& src);     // 0x00a9a7f0
};
struct Sub254
{
    uint32_t w[5];
    void AssignFrom(const Sub254& src);     // 0x00a9a370
};
struct Blob20 { uint32_t w[8]; };

struct cCloudEffectCommand {
    void*    mVtbl;                // +0x00
    void*    mParser;              // +0x04
    int      mFlags08;             // +0x08
    float    mFloats[22];          // +0x0c .. +0x60
    SP::SimpleVector<float> v64;   // +0x64
    float    f78;                  // +0x78
    uint16_t w7c;                  // +0x7c
    float    f80;                  // +0x80
    SP::SimpleVector<float> v84;   // +0x84
    float    f98;                  // +0x98
    SP::SimpleVector<float> v9c;   // +0x9c
    float    fb0;                  // +0xb0
    SP::SimpleVector<float> vb4;   // +0xb4
    float    fc8;                  // +0xc8
    float    fcc;                  // +0xcc
    SubD0    d0;                   // +0xd0
    float    fe4;                  // +0xe4
    float    fe8;                  // +0xe8
    float    fec;                  // +0xec
    SP::SimpleVector<float> vf0;   // +0xf0
    float    f104;                 // +0x104
    Blob20   blob108;              // +0x108
    uint8_t  b128[8];              // +0x128
    float    f130[13];             // +0x130 .. +0x160
    Sub164   s164;                 // +0x164
    uint8_t  b178[5];              // +0x178
    Sub180   s180;                 // +0x180
    SP::SimpleVector<float> v194;  // +0x194
    Sub1a8   s1a8;                 // +0x1a8
    float    f1bc[9];              // +0x1bc .. +0x1dc
    uint32_t a1e0[6];              // +0x1e0
    Sub1f8   s1f8;                 // +0x1f8
    float    f22c;                 // +0x22c
    float    f230;                 // +0x230
    float    f234;                 // +0x234
    SP::SimpleVector<float> v238;  // +0x238
    float    f24c;                 // +0x24c
    float    f250;                 // +0x250
    Sub254   s254;                 // +0x254

    cCloudEffectCommand();                                     // 0x00f53590
    cCloudEffectCommand(const cCloudEffectCommand& src);       // 0x00f56cc0
};

struct AppPropsFields {
    virtual void vf0();
    AppPropsFields();              // 0x0083cdd0
    char mPad[0x2c];               // vptr + 0x2c = 0x30
};

struct cOwner { void Set(const char* name, int a, void* obj); }; // 0x00a6f9c0

struct cCloudEffect : AppPropsFields {
    cOwner*  mOwner;               // +0x30
    int      mPad34;               // +0x34
    int      mField38;             // +0x38
    int      mPad3c;               // +0x3c
    cCloudEffectCommand mCmd;      // +0x40
    char     pad2a8[8];            // +0x2a8
    const char* mStrBegin;         // +0x2b0
    const char* mStrEnd;           // +0x2b4
    void*    mStrCap;              // +0x2b8
    int      mPad2bc;              // +0x2bc
    uint8_t  mFlag2c0;             // +0x2c0

    cCloudEffect() : mField38(0xeba93c76), mStrBegin((const char*)gEmptyString16),
                     mStrEnd((const char*)gEmptyString16), mStrCap((void*)0x1667bad) {}
    virtual void Update(char flag);                            // 0x00f57410 = vtable +0x14
};

namespace {

using EA::ArgScript::cArguments;
using EA::ArgScript::cCommandBase;

struct cCloudLoopCommand : cCommandBase {
    cCloudState* mState;                   // +0xc
    void Execute(cArguments& args);
};

struct cCloudLoopBoxColorCommand : cCommandBase {
    cCloudState* mState;
    void Execute(cArguments& args);
};

struct cCloudCurveCommand : cCommandBase {
    cCloudState* mState;
    void Execute(cArguments& args);
};

struct cCloudSpeedCommand : cCommandBase {
    cCloudState* mState;
    void Execute(cArguments& args);
};

struct cCloudDelayCommand : cCommandBase {
    cCloudState* mState;
    void Execute(cArguments& args);
};

}  // namespace

// Command registrar (virtual AddCommand = vtable +0x14, AddGroup = vtable +0x18).
struct Registrar {
    virtual void rv0(); virtual void rv1(); virtual void rv2(); virtual void rv3(); virtual void rv4();
    virtual void AddCommand(const char* name, void* obj);      // +0x14
    virtual void AddGroup(const char* name, void* obj);        // +0x18
};

// @ 0x00f56950
void cCloudLoopCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 0, 0x7fffffff);
    if (count > 0) {
        mState->mCurve.clear();
        for (int i = 0; i < count; ++i)
            mState->mCurve.push_back(mParser->GetFloat(argv[i]));
    }
    FUN_00f52b80(args, (char*)mState + 8, mParser);
}

// @ 0x00f56a30
void cCloudLoopBoxColorCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mBoxColor.clear();
    for (int i = 0; i < count; ++i)
        mState->mBoxColor.push_back(mParser->GetVector2(argv[i]));
    const char* s = args[0];
    if (strstr(s, "255"))
        FUN_007ecc30(0.00392156862745098f, &mState->mBoxColor);
    mState->mFlags |= 0x40000000;
    args.HasFlag("orient");
}

// @ 0x00f56b30
void cCloudCurveCommand::Execute(cArguments& args)
{
    int count;
    const char** argv = args.MainArguments(&count, 1, 0x7fffffff);
    mState->mCurve2.clear();
    for (int i = 0; i < count; ++i)
        mState->mCurve2.push_back(mParser->GetFloat(argv[i]));
    const char* s = args[0];
    if (strstr(s, "255")) {
        SP::SimpleVector<float>* v = &mState->mCurve2;
        for (uint32_t i = 0; i < v->size(); ++i)
            v->mpBegin[i] *= 0.00392156862745098f;
    }
    mState->mFlags |= 0x40000000;
    args.HasFlag("orient");
}

// @ 0x00f57280
void cCloudSpeedCommand::Execute(cArguments& args)
{
    const char** argv = args.MainArguments(1);
    mState->mCurve.resize(1);
    mState->mCurve.mpBegin[0] = mParser->GetFloat(argv[0]);
    mState->mFlags |= 1;
    mState->mScale = 0.01f;
    mState->mMode = 1;
    FUN_00f52b80(args, (char*)mState + 8, mParser);
}

// @ 0x00f57300
void cCloudDelayCommand::Execute(cArguments& args)
{
    const char** argv = args.MainArguments(1);
    mState->mCurve.resize(1);
    mState->mCurve.mpBegin[0] = mParser->GetFloat(argv[0]);
    mState->mFlags |= 2;

    int count;
    const char** opt = args.OptionArguments("delay", &count, 1, 2);
    if (opt) {
        float out[2];
        float* r = FUN_00aa2fe0(out, mParser, opt, count);
        mState->mDelayLo = r[0];
        mState->mDelayHi = r[1];
    }

    opt = args.OptionArguments("hold", &count, 1, 0x7fffffff);
    if (opt) {
        mState->mFlags |= 0x10000000;
    } else {
        opt = args.OptionArguments("kill", &count, 1, 2);
        if (!opt)
            return;
        mState->mFlags |= 0x8000000;
    }
    mState->mScale = mParser->GetFloat(opt[0]);
    mState->mMode = 1;
}

// @ 0x00f56cc0
cCloudEffectCommand::cCloudEffectCommand(const cCloudEffectCommand& src)
{
    mVtbl = (void*)0x148e910;
    mParser = 0;
    mFlags08 = src.mFlags08;
    for (int i = 0; i < 22; ++i)
        mFloats[i] = src.mFloats[i];
    v64.AllocateCopy((int)src.v64.size(), src.v64.mAllocator);
    {
        void* p = memcpy(v64.mpBegin, src.v64.mpBegin,
                         (uint32_t)((char*)src.v64.mpEnd - (char*)src.v64.mpBegin));
        v64.mpEnd = (float*)p + src.v64.size();
    }
    f78 = src.f78;
    w7c = src.w7c;
    f80 = src.f80;
    v84.AllocateCopy((int)src.v84.size(), src.v84.mAllocator);
    {
        void* p = memcpy(v84.mpBegin, src.v84.mpBegin,
                         (uint32_t)((char*)src.v84.mpEnd - (char*)src.v84.mpBegin));
        v84.mpEnd = (float*)p + src.v84.size();
    }
    f98 = src.f98;
    v9c.AllocateCopy((int)src.v9c.size(), src.v9c.mAllocator);
    {
        void* p = memcpy(v9c.mpBegin, src.v9c.mpBegin,
                         (uint32_t)((char*)src.v9c.mpEnd - (char*)src.v9c.mpBegin));
        v9c.mpEnd = (float*)p + src.v9c.size();
    }
    fb0 = src.fb0;
    vb4.AllocateCopy((int)src.vb4.size(), src.vb4.mAllocator);
    {
        void* p = memcpy(vb4.mpBegin, src.vb4.mpBegin,
                         (uint32_t)((char*)src.vb4.mpEnd - (char*)src.vb4.mpBegin));
        vb4.mpEnd = (float*)p + src.vb4.size();
    }
    fc8 = src.fc8;
    fcc = src.fcc;
    d0.AssignFrom(src.d0);
    fe4 = src.fe4;
    fe8 = src.fe8;
    fec = src.fec;
    vf0.AllocateCopy((int)src.vf0.size(), src.vf0.mAllocator);
    {
        void* p = memcpy(vf0.mpBegin, src.vf0.mpBegin,
                         (uint32_t)((char*)src.vf0.mpEnd - (char*)src.vf0.mpBegin));
        vf0.mpEnd = (float*)p + src.vf0.size();
    }
    f104 = src.f104;
    blob108 = src.blob108;
    for (int i = 0; i < 8; ++i)  b128[i] = src.b128[i];
    for (int i = 0; i < 13; ++i) f130[i] = src.f130[i];
    s164.AssignFrom(src.s164);
    for (int i = 0; i < 5; ++i)  b178[i] = src.b178[i];
    s180.AssignFrom(src.s180);
    v194.AllocateCopy((int)src.v194.size(), src.v194.mAllocator);
    {
        void* p = memcpy(v194.mpBegin, src.v194.mpBegin,
                         (uint32_t)((char*)src.v194.mpEnd - (char*)src.v194.mpBegin));
        v194.mpEnd = (float*)p + src.v194.size();
    }
    s1a8.AssignFrom(src.s1a8);
    for (int i = 0; i < 9; ++i)  f1bc[i] = src.f1bc[i];
    for (int i = 0; i < 6; ++i)  a1e0[i] = src.a1e0[i];
    s1f8.AssignFrom(src.s1f8);
    f22c = src.f22c;
    f230 = src.f230;
    f234 = src.f234;
    v238.AllocateCopy((int)src.v238.size(), src.v238.mAllocator);
    {
        void* p = memcpy(v238.mpBegin, src.v238.mpBegin,
                         (uint32_t)((char*)src.v238.mpEnd - (char*)src.v238.mpBegin));
        v238.mpEnd = (float*)p + src.v238.size();
    }
    f24c = src.f24c;
    f250 = src.f250;
    s254.AssignFrom(src.s254);
}

// @ 0x00f57410
void cCloudEffect::Update(char flag)
{
    if (flag == 0) {
        if (mFlag2c0 != 0)
            mCmd.mFlags08 |= 0x80000000;
        if (mCmd.b128[0] == 0) {
            if (mFlag2c0 != 0)
                mCmd.b128[0] = 2;
            else if ((mCmd.mFlags08 & DAT_015b0bfc) != 0)
                mCmd.b128[0] = 1;
        }
        cCloudEffectCommand* p = (cCloudEffectCommand*)EAAllocate(0x268, "Swarm", 0, 0, 0, 0);
        p = new (p) cCloudEffectCommand(mCmd);
        mOwner->Set(mStrBegin, 0x2b, p);
    }
    if (mStrBegin != mStrEnd) {
        *(char*)mStrBegin = 0;
        mStrEnd = mStrBegin;
    }
}

struct cCloudGroup : EA::ArgScript::cCommandBase {
    int mPad;                      // +0xc
    cCloudGroup() {}
};

// @ 0x00f574c0
void SWARM_CloudAddCommands(Registrar* p1, Registrar* p2)
{
    cCloudEffect* obj = (cCloudEffect*)EAAllocate(0x2c8, "ArgScript/CloudEffect", 0, 0, 0, 0);
    obj = new (obj) cCloudEffect();
    p2->AddCommand(PTR_s_cloud, obj);

    cCloudGroup* grp = (cCloudGroup*)EAAllocate(0x10, "ArgScript/GroupCloud", 0, 0, 0, 0);
    if (grp) {
        new (grp) cCloudGroup();
        p1->AddGroup(PTR_s_cloud, grp);
    } else {
        p1->AddGroup(PTR_s_cloud, grp);
    }
}
