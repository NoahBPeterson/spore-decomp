// Slice s007bbf80 -- SP::cThumbnailManager::DilateStart (0x007bbf80, 3910 bytes)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-. Builds the dilate pipeline: a summarizer, twelve filter-chain jobs
// (each wired to render-target rects through Connect), tuning floats from a property list,
// then posts a BehaviorMessage through the manager.
#include "types.h"

void* operator new(unsigned int size, const char* group, int a, int b, int c, int d);

// ---- small helpers ----------------------------------------------------------
struct Key2 { uint32_t a, b; };
struct Vec4 {
    float x, y, z, w;
    Vec4(float ax, float ay, float az, float aw) { x = ax; y = ay; z = az; w = aw; }
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) { mpObject = p; if (p) p->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    void reset() { T* t = mpObject; if (t) { mpObject = 0; t->Release(); } }
};

// ---- property list ------------------------------------------------------------
struct Property {
    uint32_t v;
    uint8_t  pad04[0xc];
    uint8_t  flags;          // +0x10
    uint8_t  pad11;
    uint16_t type;           // +0x12
};
extern float gDefaultFloat;                                   // 0x15d1168

static inline float PropGetFloat(Property* p) {
    float* r;
    uint16_t t = p->type;
    if (t == 0xd || t == 0x10) {
        if (p->flags & 0x30)
            r = *(float**)p;
        else
            r = (float*)(t != 0 ? p : 0);
    } else {
        r = &gDefaultFloat;
    }
    return *r;
}

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual Property* GetProperty(uint32_t id);                // slot 10 (+0x28)
    bool GetDescription(uint32_t id);                          // 0x6a25a0
};
extern cPropertyList* sAppProperties;                          // 0x15fd918

struct IPropertyManager {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual bool GetPropertyList(uint32_t id, uint32_t group, AutoRefCount<cPropertyList>* out);  // slot 11 (+0x2c)
};
IPropertyManager* __cdecl PropertyManager();                   // 0x67de30

// ---- singletons -----------------------------------------------------------------
struct IMgrMsg;
struct PostMsg;
struct cContentValidationSummarizer;
struct IMgr {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void Post(cContentValidationSummarizer* sender, int a, PostMsg* msg);       // slot 30 (+0x78)
};
IMgr* __cdecl GetMgr();                                        // 0x67dd50

struct IRtt {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual void GetRectAC(Key2* out);                         // slot 43 (+0xac)
    virtual void GetRectB0(Key2* out);                         // slot 44 (+0xb0)
    virtual void s45(); virtual void s46(); virtual void s47(); virtual void s48(); virtual void s49();
    virtual void GetRectC8(Key2* out);                         // slot 50 (+0xc8)
    virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
    virtual void GetRectE0(Key2* out, int index);              // slot 56 (+0xe0)
};
IRtt* __cdecl GetRtt();                                        // 0x67dd40

// ---- summarizer (0x34 bytes, two vptrs) -------------------------------------------
struct SumBaseA {
    virtual int AddRef();
    virtual int Release();
};
struct SumBaseB {
    virtual void b0();
    virtual void b1();
    int m8;
    SumBaseB() { m8 = 0; }
};
struct cContentValidationSummarizer : SumBaseA, SumBaseB {
    int mc, m10, m14, m18, m1c;
    uint8_t m20;
    int m24, m28, m2c, m30;
    cContentValidationSummarizer() {
        mc = 0; m10 = 0; m14 = 0;
        m20 = 0;
        m24 = 0; m28 = 0; m2c = 0; m30 = 0;
    }
    void AddJob(struct cFilterChainJob* job);                  // 0x7b9750
};

// ---- filter-chain job (0xe4 bytes) ---------------------------------------------------
struct JobVec {
    Key2* mpBegin;
    Key2* mpEnd;
    Key2* mpCapacity;
    void DoInsertValue(Key2* pPosition, const Key2& val);       // 0x6ec390
    void push_back(const Key2& v) {
        Key2* p = mpEnd;
        if (p < mpCapacity) {
            mpEnd = p + 1;
            if (p) { p->a = v.a; p->b = v.b; }
        } else {
            DoInsertValue(p, v);
        }
    }
};
struct cFilterChainJob {
    virtual int AddRef();
    virtual int Release();
    uint32_t f04, f08;
    uint32_t f0c, f10, f14, f18, f1c, f20;
    JobVec inputs;                    // +0x24
    uint32_t pad30[3];
    float f3c, f40, f44, f48, f4c, f50, f54, f58;
    uint32_t pad5c[4];
    float f6c, f70, f74, f78;
    uint8_t pad7c[6];
    uint8_t b82;
    uint8_t pad83;
    uint32_t pad84[5];
    Vec4 v98;                         // +0x98
    uint32_t pada8[15];
    cFilterChainJob();                                          // 0x7b8550
    void Connect(uint32_t id, Key2* a, Key2* b, int flag);      // 0x7b9510
    void Init(int flag);                                        // 0x7b9420
};

// ---- behavior message ----------------------------------------------------------------
struct BehaviorMessageBase {
    virtual void d0();
    virtual int AddRef();
    virtual int Release();
    volatile long mRef;
    BehaviorMessageBase() { mRef = 0; }
};
struct BehaviorMessage : BehaviorMessageBase {
    uint32_t f08;
    uint32_t pad0c;
    uint32_t f10;
    uint32_t pad14;
    uint32_t f18;
    uint32_t f1c;
    BehaviorMessage() { f18 = 0; }
};
struct PostMsg {
    int kind;
    int a;
    uint8_t b;
    int c, d;
    uint32_t id;
    BehaviorMessage* data;
    int e, f, g, h;
    PostMsg(BehaviorMessage* bm) {
        a = 0; b = 0; c = 0; d = 0;
        e = 0; f = 0; g = 0; h = 0;
        kind = 1;
        data = bm;
        id = 0x21d752f;
    }
    ~PostMsg() { if (data) data->Release(); }
};

// ---- the manager ------------------------------------------------------------------------
struct DilateReq {
    uint32_t pad0[2];
    uint32_t f08;
    uint32_t pad0c;
    uint32_t f10;
    uint32_t pad14;
    uint32_t f18;
    uint32_t pad1c;
    uint32_t f20;
};
struct cThumbnailManager {
    uint8_t pad0[0x10bc];
    bool    mFlag10bc;
    void DilateStart(DilateReq* req);
};

// @ 0x007bbf80
void cThumbnailManager::DilateStart(DilateReq* req) {
    uint32_t a18 = req->f18;
    uint32_t b = req->f08;
    uint32_t a10 = req->f10;
    uint32_t d = req->f20;
    IMgr* mgr = GetMgr();
    IRtt* rtt = GetRtt();
    Key2 sizeId;
    sizeId.a = (uint32_t)-1;
    sizeId.b = (uint32_t)-1;
    rtt->GetRectB0(&sizeId);
    cPropertyList* appProps = sAppProperties;

    AutoRefCount<cContentValidationSummarizer> cs(new ("Graphics", 0, 0, 0, 0) cContentValidationSummarizer());
    if (!cs.mpObject->m20) {
        cs.mpObject->m20 = 1;
        cs.mpObject->m28 = 0;
    }
    AutoRefCount<cFilterChainJob> j1(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j2(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j3(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j4(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j5(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j6(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j7(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j8(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j9(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j10(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j11(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());
    AutoRefCount<cFilterChainJob> j12(new ("Graphics", 0, 0, 0, 0) cFilterChainJob());

    Key2 pA, pB;
    pA.a = (uint32_t)-1; pA.b = (uint32_t)-1;
    pB.a = (uint32_t)-1; pB.b = (uint32_t)-1;
    GetRtt()->GetRectE0(&pA, 0);
    GetRtt()->GetRectE0(&pB, 1);
    j1.mpObject->Connect(0xe7, &pB, &pA, 0);
    j1.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
    j1.mpObject->b82 = 1;
    j1.mpObject->inputs.push_back(pB);
    j1.mpObject->f3c = 1.0f;
    j1.mpObject->f40 = 1.0f;
    j1.mpObject->f44 = 1.0f;
    j1.mpObject->f48 = 1.0f;
    j1.mpObject->f4c = 1.0f;
    j1.mpObject->f50 = 1.0f;
    j1.mpObject->f54 = 1.0f;
    float one = 1.0f;
    j1.mpObject->f58 = 0.0f;
    float zero = 0.0f;
    float half = 0.5f;

    AutoRefCount<cPropertyList> propList(0);
    IPropertyManager* pm = PropertyManager();
    propList.reset();
    if (pm->GetPropertyList(d, 0x40200100, &propList)) {
        one = PropGetFloat(propList.mpObject->GetProperty(0x26cabbf));
        zero = PropGetFloat(propList.mpObject->GetProperty(0x26dc91e));
        half = PropGetFloat(propList.mpObject->GetProperty(0x27c7387));
    }

    if (mFlag10bc) {
        j8.mpObject->Connect(0xdd, &pA, &pB, 0);
        j3.mpObject->Connect(0xd2, &pB, &pA, 0);
        j4.mpObject->Connect(0xd2, &pA, &pB, 0);
        j4.mpObject->v98 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        j4.mpObject->b82 = 1;
        j10.mpObject->Connect(0x65, &pB, &pA, 0);
        j10.mpObject->v98 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        j10.mpObject->b82 = 1;
        j10.mpObject->f3c = 1.0f;
        j10.mpObject->f40 = half;
        j10.mpObject->f44 = 0.0f;
        j10.mpObject->f48 = 0.0f;
        j11.mpObject->Connect(0x65, &pA, &sizeId, 0);
        j11.mpObject->v98 = Vec4(1.0f, 1.0f, 1.0f, 1.0f);
        j11.mpObject->b82 = 1;
        {
            Key2 pC;
            pC.a = (uint32_t)-1; pC.b = (uint32_t)-1;
            rtt->GetRectAC(&pC);
            j11.mpObject->f3c = 1.0f;
            j11.mpObject->f40 = half;
            j11.mpObject->f44 = 0.0f;
            j11.mpObject->f48 = 0.0f;
            j2.mpObject->Connect(0xe7, &pC, &pA, 0);
            j2.mpObject->inputs.push_back(pC);
            j2.mpObject->f3c = 1.0f;
            j2.mpObject->f40 = 1.0f;
            j2.mpObject->f44 = 1.0f;
            j2.mpObject->f48 = 1.0f;
            j2.mpObject->f4c = 1.0f;
            j2.mpObject->f50 = 1.0f;
            j2.mpObject->f54 = 1.0f;
            j2.mpObject->f58 = 0.0f;
            j5.mpObject->Connect(0xd2, &pA, &pB, 0);
            j6.mpObject->Connect(0xd2, &pB, &pA, 0);
            j9.mpObject->Connect(0xcb, &sizeId, &pB, 0);
            j9.mpObject->b82 = 1;
            j9.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
            j9.mpObject->f3c = one;
            j9.mpObject->f40 = 1.0f;
            j9.mpObject->f44 = 1.0f;
            j9.mpObject->f48 = 1.0f;
            j9.mpObject->f6c = 0.0f;
            j9.mpObject->f70 = 0.0f;
            j9.mpObject->f74 = zero;
            j9.mpObject->f78 = 0.0f;
            j9.mpObject->inputs.push_back(pA);
            j7.mpObject->Connect(0x4f8e3f8e, &pB, (Key2*)&a18, 0);
            j7.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
            j7.mpObject->b82 = 1;
            j7.mpObject->inputs.push_back(pC);
        }
        if (appProps->GetDescription(0x1a91189c)) {
            Key2 pD;
            pD.a = (uint32_t)-1; pD.b = (uint32_t)-1;
            GetRtt()->GetRectC8(&pD);
            j12.mpObject->Init(0);
            j12.mpObject->f0c = 0x88549f64;
            j12.mpObject->f10 = a18;
            j12.mpObject->f14 = a10;
            j12.mpObject->f1c = pD.a;
            j12.mpObject->f20 = pD.b;
            j12.mpObject->f3c = 1.2f;
            j12.mpObject->f40 = 1.0f;
            j12.mpObject->f44 = 1.0f;
            j12.mpObject->f48 = 1.0f;
            j12.mpObject->f4c = 0.0f;
            j12.mpObject->f50 = 1.0f;
            j12.mpObject->f54 = 1.0f;
            j12.mpObject->f58 = 0.0f;
            j12.mpObject->f6c = 0.0f;
            j12.mpObject->f70 = 0.0f;
            j12.mpObject->f74 = 0.0f;
            j12.mpObject->f78 = 0.0f;
        }
    } else {
        j8.mpObject->Connect(0xdd, &pA, &pB, 0);
        j3.mpObject->Connect(0xd2, &pB, &pA, 0);
        j4.mpObject->Connect(0xd2, &pA, &pB, 0);
        j10.mpObject->Connect(0x65, &pB, &pA, 0);
        j11.mpObject->Connect(0x65, &pA, (Key2*)&a18, 0);
        j10.mpObject->v98 = Vec4(0.0f, 0.0f, 0.0f, 0.0f);
        j10.mpObject->b82 = 1;
        j10.mpObject->f3c = 1.0f;
        j10.mpObject->f40 = half;
        j10.mpObject->f44 = half;
        j10.mpObject->f48 = 0.0f;
    }

    cs.mpObject->AddJob(j1.mpObject);
    cs.mpObject->AddJob(j8.mpObject);
    if (mFlag10bc) {
        cs.mpObject->AddJob(j3.mpObject);
        cs.mpObject->AddJob(j4.mpObject);
        cs.mpObject->AddJob(j10.mpObject);
        cs.mpObject->AddJob(j11.mpObject);
        cs.mpObject->AddJob(j2.mpObject);
        cs.mpObject->AddJob(j5.mpObject);
        cs.mpObject->AddJob(j6.mpObject);
        cs.mpObject->AddJob(j9.mpObject);
        cs.mpObject->AddJob(j7.mpObject);
        if (appProps->GetDescription(0x1a91189c))
            cs.mpObject->AddJob(j12.mpObject);
    } else {
        cs.mpObject->AddJob(j3.mpObject);
        cs.mpObject->AddJob(j4.mpObject);
        cs.mpObject->AddJob(j10.mpObject);
        cs.mpObject->AddJob(j11.mpObject);
    }

    BehaviorMessage* bm = new ("Graphics", 0, 0, 0, 0) BehaviorMessage();
    if (bm)
        bm->AddRef();
    bm->f08 = b;
    bm->f10 = (uint32_t)cs.mpObject;
    PostMsg msg(bm);
    mgr->Post(cs.mpObject, 0, &msg);
}
