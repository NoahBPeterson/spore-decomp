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
    ~T570(); uint32_t d;
};
struct T1040
{
    T1040(int n); // 0xa31040
    ~T1040(); uint32_t d;
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
    ~T26990(); uint32_t d;
};
struct TF410
{
    TF410(const TagA&, const TagB&); // 0xa2f410
    ~TF410(); uint32_t d;
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
    PAD(pad_s, 0x128ae0 + 4, 0x12c9ac);
    T1040          mPoolA;            // +0x12c9ac
    PAD(pad_t, 0x12c9ac + 4, 0x12d974);
    T570          mPolyB;            // +0x12d974
    PAD(pad_u, 0x12d974 + 4, 0x131840);
    T1040          mPoolB;            // +0x131840
    PAD(pad_v, 0x131840 + 4, 0x132808);
    T570          mPolyC;            // +0x132808
    PAD(pad_w, 0x132808 + 4, 0x1366d4);
    T1040          mPoolC;            // +0x1366d4
    PAD(pad_x, 0x1366d4 + 4, 0x13769c);
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
    PAD(pad_ad, 0x157c60 + 4, 0x158f48);
    T26990*         pObj;              // +0x158f48
    uint32_t          z158f4c;
    TF410          mHT3;              // +0x158f50
    PAD(pad_ae, 0x158f50 + 4, 0x15b6b0);
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
