// Slice s00a32f20 -- EA::Audio::System constructor (0x00a33600).
// Retail layout recovered from the constructor itself; member subobjects whose
// constructors/destructors are out-of-line are stubbed as templates whose ID
// only distinguishes the (never defined) ctor/dtor symbols.
#include "types.h"
#include <stddef.h>

struct TagA { TagA() {} }; struct TagB { TagB() {} };   // empty hash / equal_to / allocator tag temporaries

// Opaque member sub-objects: only their (out-of-line) ctor address and a dtor are known.
// T = (const TagA&, const TagB&) tag arguments of a fixed_hash_map ctor.
struct Th743
{
    Th743(); // 0x743b50
    ~Th743(); uint32_t d;
};
struct Ctx921
{
    Ctx921(int a, int b); // 0x921f00
    ~Ctx921(); uint32_t d;
};
struct Mtx9222
{
    Mtx9222(int a, int b); // 0x9222a0
    ~Mtx9222(); uint32_t d;
};
struct Rdd
{
    Rdd(); // 0xa247f0
    ~Rdd(); uint32_t d;
};
struct Q0fd
{
    Q0fd(); // 0xa0fdf0
    ~Q0fd(); uint32_t d;
    bool FunF980();             // 0xa0f980  pending work?
    bool FunF9a0();             // 0xa0f9a0  one dispatcher step
    int  FunF990();             // 0xa0f990  shutdown state
    void FunFdd0();             // 0xa0fdd0
    void FunFdc0();             // 0xa0fdc0
    void FunF940();             // 0xa0f940
    void FunFee0(void* msg);    // 0xa0fee0  push a command
    void* GetArg();             // 0x9892e0
    void Fun102e0(uint32_t tag);                 // 0xa102e0
    void Fun10120(uint32_t tag, uint32_t value); // 0xa10120
};
struct TA210
{
    TA210(const TagA&, const TagB&); // 0xa2a210
    ~TA210(); uint32_t d;
};
struct TF210
{
    TF210(const TagA&, const TagB&); // 0xa2f210
    ~TF210(); uint32_t d;
};
struct TB310
{
    TB310(const TagA&, const TagB&); // 0xa2a310
    ~TB310(); uint32_t d;
};
struct TCe10
{
    TCe10(const TagA&, const TagB&); // 0xa30e10
    ~TCe10(); uint32_t d;
};
struct TD410
{
    TD410(const TagA&, const TagB&); // 0xa2a410
    ~TD410(); uint32_t d;
};
struct TF310
{
    TF310(const TagA&, const TagB&); // 0xa2f310
    ~TF310(); uint32_t d;
};
struct T33500
{
    T33500(const TagA&, const TagB&); // 0xa33500
    ~T33500(); uint32_t d;
};
struct T32220
{
    T32220(const TagA&, const TagB&); // 0xa32220
    ~T32220(); uint32_t d;
};
struct T570
{
    T570(const TagA&, const TagB&); // 0xa2a570
    ~T570();
    uint32_t  m0;            // +0x0
    uint32_t* mpBuckets;     // +0x4  bucket array
    uint32_t  mBucket;       // +0x8  bucket index used as the end() marker
    uint32_t  mOpCode;       // +0xc
    void* Find(void* out, const uint32_t* key); // 0xa23ef0
    void  Erase(const uint32_t* key);           // 0xa23d20
};
struct T1040
{
    T1040(int n); // 0xa31040
    ~T1040();
    void* mpFirst;           // +0x0  ring buffer begin
    void* mpLimit;           // +0x4  ring buffer end
};
struct T1e320
{
    T1e320(const TagA&, const TagB&); // 0xa1e320
    ~T1e320(); uint32_t d;
};
struct T670
{
    T670(const TagA&, const TagB&); // 0xa2a670
    ~T670(); uint32_t d;
};
struct T770
{
    T770(const TagA&, const TagB&); // 0xa2a770
    ~T770(); uint32_t d;
};
struct T26990
{
    T26990(); // 0xa26990
    ~T26990();
    T26990* pNext;           // +0x00  list next
    T26990* pPrev;           // +0x04  list prev
    void*   pObj;            // +0x08  bound audio object
};
struct TF410
{
    TF410(const TagA&, const TagB&); // 0xa2f410
    ~TF410();
    uint32_t  m0;            // +0x0
    void**    mpBuckets;     // +0x4  node bucket array
    uint32_t  mBucket;       // +0x8  bucket index used as the end() marker
    void Begin(void** out);  // 0x594410
};
struct Channel
{
    Channel(const char* name, int a, int b); // 0x11e64f0
    ~Channel(); uint32_t d;
};

struct ISystem {
    virtual void Init();
    virtual ~ISystem();
};
struct IHandler {
    IHandler() {}
    virtual void HandleMsg();
    virtual ~IHandler();
};
struct IHandlerRC : IHandler {
    IHandlerRC() {}
    virtual void HandleMsg();
    virtual ~IHandlerRC();
};

struct AutoHandler {
    void* mpServer; void* mpHandler; uint32_t* mpIdArray; uint32_t mnIdArrayCount; uint32_t mnPriority;
    AutoHandler() : mpServer(0), mpHandler(0), mpIdArray(0), mnIdArrayCount(0), mnPriority(0) {}
    ~AutoHandler();
};

struct CoreAllocator  { CoreAllocator()  {} virtual ~CoreAllocator();  };
struct ResAllocator   { ResAllocator()   {} virtual ~ResAllocator();   };

// 0x20-byte-stride envelope/smoothed-value object with a vtable.
struct Env {
    Env() : mA(1), mB(0), mC(1.0f), mD(2.0f), mE(0) {}
    virtual ~Env();
    int mA; int mB; float mC; float mD; int mE;
};

extern float g_vec3[3];         // 0x0166da00, copied twice into the listener positions
extern const double g_cacheAge; // 0x01452f48

// Three-pointer vector-like object with an out-of-line dtor.
struct Vec3p { Vec3p() : a(0), b(0), c(0) {} ~Vec3p(); uint32_t a, b, c, pad[2]; };

struct RingStore { uint32_t* b0; uint32_t* e0; uint32_t* cap; uint32_t al; uint32_t* fixedBuf; };

#define PAD(name, from, to) uint32_t name[((to) - (from)) / 4]

class System : public ISystem, public IHandlerRC {
public:
    System();
    virtual void Init();
    virtual ~System();
    virtual void HandleMsg();

    void Update(void* ctx, float dt);       // 0x00a32f20
    void MuteAll(bool muted, bool immediate); // 0x00a233b0
    void MaintainLRU();                     // 0x00a28810

    AutoHandler       mAutoMsg;          // +0x08
    int               mRefCount;         // +0x1c
    Th743           mTickThread;       // +0x20
    uint32_t          padThr;
    Ctx921           mTickCtx;          // +0x28
    PAD(pad_a, 0x28 + 4, 0x90);
    uint32_t          mCommandBufferSize;// +0x90
    bool              mbInitialized;     // +0x94
    bool              mbPaused;
    bool              mbMutedForSilence;
    bool              mbMutedForFocus;
    bool              mbMutedByProperty;
    bool              mbMuted;
    uint8_t           b9a, b9b;
    CoreAllocator     mAllocator;        // +0x9c
    ResAllocator      mAllocator2;       // +0xa0
    uint32_t          mpRWAC;            // +0xa4
    float             mDacOutputMode;    // +0xa8
    float             mDacOutputSampleRate; // +0xac
    int               mNumOutputChannels;// +0xb0
    uint32_t          padb4;
    Mtx9222           mMutex;            // +0xb8
    PAD(pad_b, 0xb8 + 4, 0xec);
    uint32_t          mStreamPoolNumStreams;   // +0xec
    uint32_t          mStreamPoolBufferSize;   // +0xf0
    uint32_t          mStreamPoolMaxRequests;  // +0xf4
    Channel           mDebugChannel;     // +0xf8
    PAD(pad_c, 0xf8 + 4, 0x198);
    Rdd           mResourceDeviceDriver; // +0x198
    PAD(pad_d, 0x198 + 4, 0x1f8);
    uint32_t          mpConfiguration;   // +0x1f8 (AutoRefCount<IConfiguration>-like, null)
    uint8_t           mMax3d;            // +0x1fc
    uint8_t           pad1fd[3];
    int               mPerformanceLevel; // +0x200
    uint32_t          cq0, cq1, cq2;     // +0x204..0x20c
    float             cqName;            // +0x210
    Q0fd q0; uint32_t qp0[19];   // +0x214
    Q0fd q1; uint32_t qp1[19];   // +0x264
    Q0fd q2; uint32_t qp2[19];   // +0x2b4
    Q0fd q3; uint32_t qp3[19];   // +0x304
    Q0fd q4; uint32_t qp4[19];   // +0x354
    Q0fd q5; uint32_t qp5[19];   // +0x3a4
    uint8_t           s3f4, s3f5;        // +0x3f4
    uint8_t           pad3f6[2];
    uint32_t          s3f8;
    uint8_t           s3fc, s3fd;
    uint8_t           pad3fe[2];
    float             s400;              // +0x400
    TA210          mMixables;         // +0x404
    PAD(pad_g, 0x404 + 4, 0x13f4);
    TF210          mPrimitives;       // +0x13f4
    PAD(pad_h, 0x13f4 + 4, 0x23e4);
    TA210          mMapA;             // +0x23e4
    PAD(pad_i, 0x23e4 + 4, 0x33d4);
    TB310          mPrimitiveProxys;  // +0x33d4
    PAD(pad_j, 0x33d4 + 4, 0x80424);
    TCe10          mBig;              // +0x80424
    PAD(pad_k, 0x80424 + 4, 0x118a00);
    Env               env0; uint32_t e0pad[2];   // +0x118a00
    Env               env1; uint32_t e1pad[2];   // +0x118a20
    Env               env2; uint32_t e2pad[2];   // +0x118a40
    uint32_t          lst[2]; uint32_t lstA; uint8_t lstB; uint8_t lstBp[3]; uint32_t lstC; uint32_t lstD; // +0x118a60
    TD410          mEmitterConstructorMap;  // +0x118a78
    PAD(pad_l, 0x118a78 + 4, 0x118b94);
    Env               env3;              // +0x118b94
    PAD(pad_m, 0x118b94 + 0x18, 0x118bb0);
    TA210          mMapB;             // +0x118bb0
    PAD(pad_n, 0x118bb0 + 4, 0x119ba4);
    Vec3p             mVecA;             // +0x119ba4
    TF310          mHT2a;             // +0x119bb8
    PAD(pad_o, 0x119bb8 + 4, 0x11a3d8);
    TA210          mMapC;             // +0x11a3d8
    PAD(pad_p, 0x11a3d8 + 4, 0x11b3c8);
    T33500          mOutputs;          // +0x11b3c8
    PAD(pad_q, 0x11b3c8 + 4, 0x1277b4);
    T32220          mSubscriptions;    // +0x1277b4
    PAD(pad_r, 0x1277b4 + 4, 0x128ae0);
    T570          mPolyA;            // +0x128ae0
    PAD(pad_s, 0x128ae0 + 0x10, 0x12c9ac);
    T1040          mPoolA;            // +0x12c9ac
    PAD(pad_t, 0x12c9ac + 8, 0x12d974);
    T570          mPolyB;            // +0x12d974
    PAD(pad_u, 0x12d974 + 0x10, 0x131840);
    T1040          mPoolB;            // +0x131840
    PAD(pad_v, 0x131840 + 8, 0x1327fc);
    uint32_t*         mIdRead;          // +0x1327fc
    uint32_t*         mIdWrite;         // +0x132800
    uint32_t          mIdDropped;       // +0x132804
    T570          mPolyC;            // +0x132808
    PAD(pad_w, 0x132808 + 0x10, 0x1366d4);
    T1040          mPoolC;            // +0x1366d4
    PAD(pad_x, 0x1366d4 + 8, 0x13769c);
    uint32_t*         fv0;               // +0x13769c
    uint32_t*         fv1;               // +0x1376a0
    uint32_t*         fv2;               // +0x1376a4
    uint32_t          fvpad;             // +0x1376a8
    uint32_t*         fv3;               // +0x1376ac
    PAD(pad_y, 0x1376ac + 4, 0x1376b4);
    uint32_t          fvBuf[(0x13777c - 0x1376b4) / 4];   // +0x1376b4
    T1e320          mJ;                // +0x13777c
    PAD(pad_z, 0x13777c + 4, 0x13795c);
    T670          mK;                // +0x13795c
    PAD(pad_aa, 0x13795c + 4, 0x137fe8);
    T770          mExternalIds;      // +0x137fe8
    PAD(pad_ab, 0x137fe8 + 4, 0x157438);
    uint32_t          listNext, listPrev;// +0x157438
    TF310          mHT2b;             // +0x157440
    PAD(pad_ac, 0x157440 + 4, 0x157c60);
    T26990          mObj157c60;        // +0x157c60
    PAD(pad_ad, 0x157c60 + 0xc, 0x158f48);
    T26990*         pObj;              // +0x158f48
    uint32_t          z158f4c;
    TF410          mHT3;              // +0x158f50
    PAD(pad_ae, 0x158f50 + 0xc, 0x15b6b0);
    uint32_t          z6b0, z6b4, z6b8, z6bc;     // +0x15b6b0
    PAD(pad_af, 0x15b6bc + 4, 0x15b6d8);
    float             posA[3];           // +0x15b6d8
    float             posB[3];           // +0x15b6e4
    float             mat0[9];           // +0x15b6f0
    float             mat1[9];           // +0x15b714
    uint32_t          z738, z73c, z740;  // +0x15b738
    PAD(pad_ag, 0x15b740 + 4, 0x15b750);
    uint32_t          z750, z754, z758, z75c, z760; // +0x15b750
    uint32_t          n764;              // +0x15b764
    double            ageSecs;           // +0x15b768
    uint32_t          m770;              // +0x15b770
    uint8_t           b774; uint8_t b774p[3];
    uint32_t          z778;              // +0x15b778
    uint32_t*         rb0; uint32_t* rb1; uint32_t* rb2; uint32_t* rb3; // +0x15b77c
    uint32_t*         rb4;               // +0x15b78c
    uint32_t          rbPad[(0x15bb7c - 0x15b790) / 4];
    uint32_t*         sb0; uint32_t* sb1; uint32_t* sb2; uint32_t* sb3; // +0x15bb7c
    uint32_t*         sb4;               // +0x15bb8c
    PAD(pad_ai, 0x15bb8c + 4, 0x15bbf0);
    uint8_t           b15bbf0;           // +0x15bbf0
    PAD(pad_aj, 0x15bbf0 + 4, 0x15bbf8);
    Env               env4;              // +0x15bbf8
};

#define OFS(m, v) typedef char ofs_##m[(offsetof(System, m) == (v)) ? 1 : -1]
OFS(mDebugChannel, 0xf8);
OFS(mResourceDeviceDriver, 0x198);
OFS(mpConfiguration, 0x1f8);
OFS(mPerformanceLevel, 0x200);
OFS(q0, 0x214);
OFS(q5, 0x3a4);
OFS(s3f4, 0x3f4);
OFS(s400, 0x400);
OFS(mMixables, 0x404);
OFS(mBig, 0x80424);
OFS(env0, 0x118a00);
OFS(env2, 0x118a40);
OFS(lst, 0x118a60);
OFS(mEmitterConstructorMap, 0x118a78);
OFS(env3, 0x118b94);
OFS(mVecA, 0x119ba4);
OFS(fv0, 0x13769c);
OFS(fvBuf, 0x1376b4);
OFS(mJ, 0x13777c);
OFS(listNext, 0x157438);
OFS(pObj, 0x158f48);
OFS(mHT3, 0x158f50);
OFS(z6b0, 0x15b6b0);
OFS(posA, 0x15b6d8);
OFS(mat1, 0x15b714);
OFS(n764, 0x15b764);
OFS(ageSecs, 0x15b768);
OFS(rb0, 0x15b77c);
OFS(sb0, 0x15bb7c);
OFS(env4, 0x15bbf8);

// @ 0x00a33600  EA::Audio::System::System
System::System()
    : mAutoMsg(),
      mTickThread(),
      mTickCtx(0, 1),
      mAllocator(), mAllocator2(),
      mMutex(0, 1),
      mDebugChannel("audio filesys", 0, 0),
      mResourceDeviceDriver(),
      mpConfiguration(0),
      q0(), q1(), q2(), q3(), q4(), q5(),
      mMixables(TagA(), TagB()),
      mPrimitives(TagA(), TagB()),
      mMapA(TagA(), TagB()),
      mPrimitiveProxys(TagA(), TagB()),
      mBig(TagA(), TagB()),
      env0(), env1(), env2(),
      mEmitterConstructorMap(TagA(), TagB()),
      env3(),
      mMapB(TagA(), TagB()),
      mVecA(),
      mHT2a(TagA(), TagB()),
      mMapC(TagA(), TagB()),
      mOutputs(TagA(), TagB()),
      mSubscriptions(TagA(), TagB()),
      mPolyA(TagA(), TagB()),
      mPoolA(1000),
      mPolyB(TagA(), TagB()),
      mPoolB(1000),
      mPolyC(TagA(), TagB()),
      mPoolC(1000),
      mJ(TagA(), TagB()),
      mK(TagA(), TagB()),
      mExternalIds(TagA(), TagB()),
      mHT2b(TagA(), TagB()),
      mObj157c60(),
      mHT3(TagA(), TagB()),
      env4()
{
    mRefCount = 0;
    mCommandBufferSize = 0x1f400;
    mbInitialized = false; mbPaused = false; mbMutedForSilence = false;
    mbMutedForFocus = false; mbMutedByProperty = false; mbMuted = false;
    b9a = 0; b9b = 0;
    mDacOutputMode = 1.0f;
    mDacOutputSampleRate = 44100.0f;
    mNumOutputChannels = 2;
    mStreamPoolNumStreams = 10;
    mStreamPoolBufferSize = 0x1f400;
    mStreamPoolMaxRequests = 2;
    mMax3d = 0;
    mPerformanceLevel = 3;
    cq0 = 0x1f4; cq1 = 0x1f4; cq2 = 0x1f4; cqName = 0.0f;
    s3f4 = 0; s3f5 = 0; s3f8 = 0; s3fc = 0; s3fd = 1; s400 = 5.0f;

    lst[0] = (uint32_t)&lst; lst[1] = (uint32_t)&lst;
    lstA = 0; lstB = 0; lstC = 0;

    fv0 = fvBuf; fv1 = fvBuf; fv3 = fvBuf; fv2 = fvBuf + 50;
    listNext = (uint32_t)&listNext; listPrev = (uint32_t)&listNext;

    pObj = &mObj157c60;
    z158f4c = 0;

    z6b0 = z6b4 = z6b8 = z6bc = 0;
    z738 = z73c = z740 = 0;
    z750 = z754 = z758 = z75c = z760 = 0;
    n764 = 100;
    ageSecs = g_cacheAge;
    m770 = 0x6400000;
    b774 = 0;
    z778 = 0;

    rb0 = rb1 = rb4 = (uint32_t*)((char*)this + 0x15b794);
    rb2 = (uint32_t*)((char*)this + 0x15b794 + 0x3e8);
    sb0 = sb1 = sb4 = (uint32_t*)((char*)this + 0x15bb94);
    sb2 = (uint32_t*)((char*)this + 0x15bb94 + 0x50);

    b15bbf0 = 0;
    posA[0] = g_vec3[0]; posA[1] = g_vec3[1]; posA[2] = g_vec3[2];
    posB[0] = g_vec3[0]; posB[1] = g_vec3[1]; posB[2] = g_vec3[2];
    for (int i = 0; i < 9; ++i) { mat0[i] = (i % 4 == 0) ? 1.0f : 0.0f; }
    for (int i = 0; i < 9; ++i) { mat1[i] = (i % 4 == 0) ? 1.0f : 0.0f; }
}

// ---------------------------------------------------------------------------
// EA::Audio::VoiceContainer bound-property bookkeeping (0x00a33dc0, 0x00a33e90).
// The container keeps a fixed vector of 0x24-byte bindings at +0x184: the live
// range is [mpBindingsBegin, mpBindingsEnd) and every entry caches one audio
// object command (id at +0x0c, two candidate float values at +0x1c/+0x10, the
// liveness pointer at +0x14 and two flag bytes at +0x18/+0x20).
// ---------------------------------------------------------------------------
namespace EA { namespace Audio {

struct Binding
{
    uint32_t mProperty;      // +0x00  property id the binding answers
    uint32_t mPad04;         // +0x04
    uint32_t mPad08;         // +0x08
    uint32_t mCommand;       // +0x0c  audio-object command id
    float    mValueB;        // +0x10  second candidate value (flag +0x20 bit 1)
    uint32_t mpVoice;        // +0x14  non-null when the binding is live
    uint8_t  mbAltPath;      // +0x18  selects the +0x1c value when set
    uint8_t  mPad19[3];
    float    mValueA;        // +0x1c  default value
    uint8_t  mFlags20;       // +0x20  bit 0 = use mValueB, bit 1 = keep mValueA
    uint8_t  mPad21[3];
};

// rw::audio::core::System singleton: only the global lock is used here.
struct CoreSystem
{
    void Lock();             // 0x0112c600
    void Unlock();           // 0x0112c620
};
extern CoreSystem* gpCoreSystem;    // 0x016e61a8

// The audio object the bindings belong to: 0x0112ccf0 is a __thiscall command setter.
struct Voice
{
    void SetCommandComplete(uint32_t command, float value);   // 0x0112ccf0
};

struct VoiceContainer
{
    uint8_t  mPad0000[0x184];
    Binding* mpBindingsBegin;    // +0x184
    Binding* mpBindingsEnd;      // +0x188

    void CommitBoundProperties();               // 0x00a33dc0
    bool HasPropertyBinding(uint32_t property); // 0x00a33e90
};

// @ 0x00a33e90
bool VoiceContainer::HasPropertyBinding(uint32_t property)
{
    int count = (int)(mpBindingsEnd - mpBindingsBegin);
    int i = 0;
    if (count > 0) {
        Binding* pBinding = mpBindingsBegin;
        do {
            if (pBinding->mProperty == property)
                return true;
            ++i;
            ++pBinding;
        } while (i < count);
    }
    return false;
}

// @ 0x00a33dc0
void VoiceContainer::CommitBoundProperties()
{
    int count = (int)((char*)mpBindingsEnd - (char*)mpBindingsBegin) / 36;
    if (count == 0)
        return;
    if (gpCoreSystem)
        gpCoreSystem->Lock();
    __try {
        int offset = 0;
        if (count > 0) {
            do {
                Binding* pBinding = (Binding*)((char*)mpBindingsBegin + offset);
                if (pBinding->mpVoice) {
                    if (!pBinding->mbAltPath && !(pBinding->mFlags20 & 2))
                        ((Voice*)pBinding->mpVoice)->SetCommandComplete(pBinding->mCommand, pBinding->mValueA);
                    else if (pBinding->mFlags20 & 1)
                        ((Voice*)pBinding->mpVoice)->SetCommandComplete(pBinding->mCommand, pBinding->mValueB);
                }
                offset += 36;
            } while (--count != 0);
        }
    } __finally {
        if (gpCoreSystem)
            gpCoreSystem->Unlock();
    }
}

}} // namespace EA::Audio

// ---------------------------------------------------------------------------
// EA::Audio::System::Update (0x00a32f20): one audio-server tick.
//   1. start the frame stopwatch, flush the command queue when the mixer asks
//      for it (flag +0x3f4), otherwise spin on the dispatcher while it has work
//   2. recompute the "muted" aggregate and push it through MuteAll
//   3. advance the per-object property ramp (pObj list at +0x157c60 / +0x158f48)
//   4. sweep the +0x158f50 hash table, notify every bound object, maintain the
//      LRU set and run the deferred command list
// ---------------------------------------------------------------------------
#define AVS(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))

namespace EA {

struct Stopwatch
{
    Stopwatch(int units, bool highRes);      // 0x0093a560
    void Start();                            // inlined in the original
    uint32_t mnUnits;                        // +0x00
    uint32_t mnStartLo;                      // +0x04
    uint32_t mnStartHi;                      // +0x08
    uint32_t mnTotalLo;                      // +0x0c
    uint32_t mnTotalHi;                      // +0x10
};

struct LimitStopwatch : Stopwatch
{
    LimitStopwatch(int units, bool highRes); // 0x0093a560
    void SetTimeLimit(uint32_t units, bool b);  // 0x0093a480
    bool HasTimeLeft();                         // inlined in the original
    uint32_t mnEndLo;                        // +0x14
    uint32_t mnEndHi;                        // +0x18
};

} // namespace EA

namespace rt {
struct MsgObj            // object with a virtual command interface
{
    virtual void Slot0();
    virtual void Slot4();
    virtual void Slot18(int, int);
    virtual void Slot24(uint32_t);
};
struct cmdStub           // 0x0166d9f4: mixer/notification sink with two vtable slots
{
    virtual void SlotC0();
    virtual void SlotC4();
};
extern cmdStub* gpCmdStub;          // 0x0166d9f4
extern void* gpCoreSys166 ;          // (unused placeholder)

struct CmdRecord
{
    uint32_t mType;         // +0x00
    uint32_t mArg1;         // +0x04
    uint32_t mArg2;         // +0x08
    uint32_t mArg3;         // +0x0c
    uint32_t mArg4;         // +0x10
};

struct CmdList
{
    uint32_t* mpBegin;      // +0x00
    uint32_t* mpEnd;        // +0x04
    uint32_t* mpGuard;      // +0x08
    uint32_t* mpCap;        // +0x0c
    void Assign(const uint32_t* begin, const uint32_t* end); // 0x00a32320
    void EraseRange(uint32_t* begin, uint32_t* end);         // 0x00a2ae90
};
extern CmdList   gDeferredCmds;     // 0x0166da90
extern uint32_t  gDeferredGuard;    // 0x0166de90
extern uint32_t  gDeferredStorage[];// 0x0166daa8
} // namespace rt

extern "C" int atexit(void (*fn)());
void DeferredListInit();            // 0x013c1810 (atexit target)

// @ 0x00a32f20
void System::Update(void* ctx, float dt)
{
    EA::Stopwatch watch(4, false);
    watch.Start();

    if (q2.FunF980() && s3f4) {
        if (rt::gpCmdStub)
            ((void (__thiscall*)(void*))AVS(rt::gpCmdStub, 0xc0))(rt::gpCmdStub);
        s3f4 = 0;
        q2.FunFee0(&q1);
        if (rt::gpCmdStub)
            ((void (__thiscall*)(void*))AVS(rt::gpCmdStub, 0xc4))(rt::gpCmdStub);
        q2.FunFdc0();
    }

    if (!q2.FunF980()) {
        uint32_t spins = 0;
        EA::LimitStopwatch dispatchTimer(3, false);
        dispatchTimer.SetTimeLimit(cq0, true);
        do {
            ++spins;
            if ((spins & 3) == 0 && !dispatchTimer.HasTimeLeft())
                break;
            if (!q2.FunF9a0())
                break;
            ((void (__thiscall*)(System*, void*))AVS(this, 0x130))(this, q2.GetArg());
        } while (true);
        if (q2.FunF990() == 0) {
            q2.FunFdd0();
            ++s3f8;
        }
    }

    bool muted = (mbMutedForSilence || mbMuted || mbMutedForFocus || mbMutedByProperty);
    if (muted != (b9a != 0))
        MuteAll(muted, false);

    if (mObj157c60.pNext != (void*)&mObj157c60) {
        float delta = dt - cqName;
        if (delta < 0.0f)
            delta = 0.0f;

        if (pObj == (T26990*)&mObj157c60) {
            ((void (__thiscall*)(System*, float, uint32_t))AVS(this, 0x208))(this, delta, z6b0);
            cqName = dt;
            pObj = (T26990*)mObj157c60.pNext;
        }

        uint32_t spins = 0;
        EA::LimitStopwatch bindTimer(3, false);
        bindTimer.SetTimeLimit(cq2, true);
        do {
            ++spins;
            if ((spins & 3) == 0 && !bindTimer.HasTimeLeft())
                break;
            if (pObj == (T26990*)&mObj157c60)
                break;
            T26990* pCur = pObj;
            ((void (__thiscall*)(void*, float, float))AVS(pCur->pObj, 8))(pCur->pObj, dt, delta);
            if (pObj == pCur)
                pObj = (T26990*)pCur->pNext;
        } while (true);

        if (pObj == (T26990*)&mObj157c60) {
            void* it[2];
            mHT3.Begin(it);
            void* pEnd = mHT3.mpBuckets[mHT3.mBucket];
            void* pNode = it[0];
            void** ppBucket = (void**)it[1];
            while (pNode != pEnd) {
                void* pValue = *(void**)((char*)pNode + 4);
                ((void (__thiscall*)(void*, uint32_t))AVS(pValue, 0x24))(pValue, z6b0);
                pNode = *(void**)((char*)pNode + 8);
                while (pNode == 0) {
                    pNode = *++ppBucket;
                }
            }
            ((void (__thiscall*)(System*))AVS(this, 0x13c))(this);
            MaintainLRU();
            ((void (__thiscall*)(System*))AVS(this, 0x20c))(this);
        }
    }

    ((void (__thiscall*)(System*))AVS(this, 0x204))(this);

    while (rb0 != rb1) {
        if (!(rt::gDeferredGuard & 1)) {
            rt::gDeferredGuard |= 1;
            rt::gDeferredCmds.mpBegin = rt::gDeferredStorage;
            rt::gDeferredCmds.mpEnd = rt::gDeferredStorage;
            rt::gDeferredCmds.mpCap = rt::gDeferredStorage;
            rt::gDeferredCmds.mpGuard = &rt::gDeferredGuard;
            atexit(DeferredListInit);
        }
        rt::gDeferredCmds.Assign(rb0, rb1);

        uint32_t* pRec = rt::gDeferredCmds.mpBegin;
        uint32_t* pEnd = rt::gDeferredCmds.mpEnd;
        if (pRec != pEnd) {
            do {
                rt::CmdRecord* pCmd = (rt::CmdRecord*)pRec;
                if (pCmd->mType == 0x3a0fd6e) {
                    rt::MsgObj* pObj2 = (rt::MsgObj*)((void* (__thiscall*)(System*, uint32_t))AVS(this, 0x1d4))(this, pCmd->mArg1);
                    if (pObj2)
                        ((void (__thiscall*)(rt::MsgObj*))AVS(pObj2, 0))(pObj2);
                    if (pObj2)
                        ((void (__thiscall*)(rt::MsgObj*, int, int))AVS(pObj2, 0x18))(pObj2, 0, 1);
                    if (pObj2)
                        ((void (__thiscall*)(rt::MsgObj*))AVS(pObj2, 4))(pObj2);
                } else if (pCmd->mType == 0x3a129ee) {
                    if (pCmd->mArg1 >= 0x7d1 && pCmd->mArg1 <= 0xbb8) {
                        void* found;
                        mPolyB.Find(&found, &pCmd->mArg1);
                        if (found != (void*)mPolyB.mpBuckets[mPolyB.mBucket]) {
                            mPolyB.Erase(&pCmd->mArg1);
                            *mIdWrite++ = pCmd->mArg1;
                            if (mIdWrite == (uint32_t*)mPoolB.mpLimit)
                                mIdWrite = (uint32_t*)mPoolB.mpFirst;
                            if (mIdWrite == mIdRead) {
                                if (++mIdRead == (uint32_t*)mPoolB.mpLimit)
                                    mIdRead = (uint32_t*)mPoolB.mpFirst;
                            } else {
                                ++mIdDropped;
                            }
                        }
                    }
                } else if (pCmd->mType == 0x63e3de7) {
                    if (pCmd->mArg3) {
                        ((void (__thiscall*)(void*, uint32_t, int))AVS((void*)pCmd->mArg3, 0x18))((void*)pCmd->mArg3, pCmd->mArg2, pCmd->mArg2 != 0);
                        void* pRelease = (void*)pCmd->mArg3;
                        pCmd->mArg3 = 0;
                        ((void (__thiscall*)(void*))AVS(pRelease, 4))(pRelease);
                    }
                }
                q5.Fun102e0(0x3a0fcce);
                q5.Fun10120(0x3a0fce5, pCmd->mType);
                q5.Fun10120(0x3475385, pCmd->mArg1);
                q5.Fun10120(0x39e3c9f, pCmd->mArg2);
                q5.Fun10120(0x39e3ca6, pCmd->mArg3);
                q5.FunF940();
                pRec += 5;
            } while (pRec != pEnd);
        }
        rt::gDeferredCmds.EraseRange(rt::gDeferredCmds.mpBegin, rt::gDeferredCmds.mpEnd);
    }
}

// ---------------------------------------------------------------------------
// eastl::fixed_hash_map<uint32_t, eastl::fixed_hash_map<uint32_t,float,20,21,1,
// eastl::hash<uint32_t>,eastl::equal_to<uint32_t>,0>, 100,101,1,
// eastl::hash<uint32_t>,eastl::equal_to<uint32_t>,0> constructor (0x00a33500).
// The map is the nested "big" property table: 100 node slots of 0x1e8 bytes
// carved out of the object itself at +0x1cc, 101 buckets right after them.
// ---------------------------------------------------------------------------
namespace eastl {

// Only the free-list head and the init entry point matter for construction.
struct fixed_pool_base
{
    void* mpHead;   // +0x00  first free node
    void init(void* pMemory, uint32_t nSize, uint32_t nNodeSize, uint32_t nAlignment, uint32_t nOffset); // 0x00921260
};

// Pool description the hashtable base constructor consumes.
struct node_pool_desc
{
    void*    mpMap;       // +0x00  map being constructed
    uint8_t* mpNodes;     // +0x04  first node slot
    uint8_t* mpNodesEnd;  // +0x08  one past the last node slot
    uint32_t mnNodeSize;  // +0x0c  bytes per node
};

// Instantiated map type: 101 buckets, 100 node slots of 0x1e8 bytes.
struct fixed_hash_map_u32_nested
{
    void*    mpBegin;                   // +0x000
    void*    mpEnd;                     // +0x004
    uint32_t mnBucketCount;             // +0x008  buckets currently allocated
    void*    mpBucketArray;             // +0x00c
    float    mLoadFactor;               // +0x010
    float    mGrowthFactor;             // +0x014
    uint32_t mnElementCount;            // +0x018
    uint8_t  mPad1c[0x1cc - 0x1c];      // +0x01c  rest of the hashtable state
    uint8_t  mNodeStorage[0xbea0];      // +0x1cc  100 slots * 0x1e8 bytes

    fixed_hash_map_u32_nested(const struct hash_tag&, const struct equal_to_tag&); // 0x00a33500
    void BaseInit(void* pAllocator, const node_pool_desc& desc);  // 0x00a23a40
    void Rehash(uint32_t nBucketCount);                           // 0x00a22060
};

struct hash_tag {};
struct equal_to_tag {};

// 0x00921340: tagged allocation of the node pool bookkeeping (tag 0x65).
void* RequestPoolBookkeeping(uint32_t tag);
// 0x009213c0: bucket count of an existing bucket array.
uint32_t BucketCount(void* pBucketArray);

// @ 0x00a33500
fixed_hash_map_u32_nested::fixed_hash_map_u32_nested(const hash_tag&, const equal_to_tag&)
{
    fixed_pool_base pool;
    pool.mpHead = 0;
    pool.init(mNodeStorage, sizeof(mNodeStorage), 0x1e8, 4, 0);

    node_pool_desc desc;
    desc.mpMap      = this;
    desc.mpNodes    = mNodeStorage;
    desc.mpNodesEnd = mNodeStorage + sizeof(mNodeStorage);
    desc.mnNodeSize = 0x1e8;
    BaseInit(RequestPoolBookkeeping(0x65), desc);

    mLoadFactor    = 10000.0f;
    mGrowthFactor  = 2.0f;
    mnElementCount = 0;

    uint32_t nBucketCount = BucketCount(mpBucketArray);
    if (mnBucketCount < nBucketCount)
        Rehash(nBucketCount);
}

} // namespace eastl
