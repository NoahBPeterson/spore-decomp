// Slice s007b97d0 - cThumbnailManager timeline/terrain teardown + large-image helpers.

void* EAAllocate(unsigned size, const char* area, int a, int b, void* alloc, int d); // 0x00F473A0

struct DrawParam;

struct RectID {
    int mPageID;                        // +0x00
    int mAllocID;                       // +0x04
};

// 0xe4-byte job post filter (retail layout, c.f. slice s007ba350):
// ctor 0x7b8550, Init 0x7b9420, Shutdown 0x7b9620, Draw vtable[3] 0x7b3a70.
struct TerrainFilter {
    virtual int  AddRef();                                  // vtable +0x00
    virtual int  Release();                                 // vtable +0x04
    virtual void slot2();                                   // vtable +0x08
    virtual void Draw(int, int, DrawParam*, void*);         // vtable +0x0c
    TerrainFilter* ctor();                                  // 007b8550
    void Init(bool);                                        // 007b9420
    void InnerTeardown();                                   // 007b9620

    unsigned m_refCountBaseVtbl;        // +0x04 (RefCountVTemplate vtable)
    unsigned m_refCount;                // +0x08
    unsigned m_materialId;              // +0x0c
    RectID   m_srcRectID;               // +0x10
    void*    m_srcRaster;               // +0x18
    RectID   m_destRectID;              // +0x1c
    void*    m_additionalBegin;         // +0x24
    void*    m_additionalEnd;           // +0x28
    void*    m_additionalCap;           // +0x2c
    char     m_pad30[0x38 - 0x30];      // +0x30
    void*    m_viewer;                  // +0x38
    float    m_customParams[16];        // +0x3c
    unsigned m_callNumber;              // +0x7c
    bool     m_initialized;             // +0x80
    bool     m_dumpTexture;             // +0x81
    bool     m_clearBeforeDraw;         // +0x82
    bool     m_overrideViewport;        // +0x83
    int      m_viewX;                   // +0x84
    int      m_viewY;                   // +0x88
    int      m_viewW;                   // +0x8c
    int      m_viewH;                   // +0x90
    int      m_quadrant;                // +0x94
    float    m_clearColor[4];           // +0x98
    bool     m_preSetViewport;          // +0xa8
    float    m_blurA[2];                // +0xac
    float    m_blurB[2];                // +0xb4
    float    m_blurC[2];                // +0xbc
    float    m_blurD[2];                // +0xc4
    float    m_blurStrength;            // +0xcc
    char     m_padD0[0xe4 - 0xd0];      // +0xd0
};

// SP::cViewer local image (0x174 bytes); ctor at 0x7c3f70, Init at 0x7c4dd0.
struct Viewer {
    int m_image[0x174 / 4];             // full cViewer image (int array: no /GS cookie)
    void Destroy1();                    // 007c3ba0
    Viewer* ctor();                     // 007c3f70
    bool Init(bool);                    // 007c4dd0
    ~Viewer();                          // 007c4000
};

// Stack record handed to Draw: the external viewer followed by three zero slots.
struct DrawParam {
    Viewer* mViewer;                    // +0x00
    void*   m08;                        // +0x04
    void*   m0c;                        // +0x08
    void*   m10;                        // +0x0c
};

// ---------------------------------------------------------------------------
// Planet-capture path (function 007ba0b0).
// ---------------------------------------------------------------------------

// Retail allocates these with `new("Graphics",0,0,0,0) T`, i.e. the allocator
// hook EAAllocate(size, area, 0, 0, 0, 0) followed by the inlined constructor.
inline void* operator new(unsigned size, const char* area, int a, int b, int c, int d)
{
    return EAAllocate(size, area, a, b, (void*)c, d);
}

struct cAtomicRefObject;

// 4-byte atomic intrusive pointer (CaptureCam::+0x08).
struct cAtomicRefPtr {
    cAtomicRefObject* mpObject;                                 // +0x00
    cAtomicRefPtr* Assign(cAtomicRefObject* p);                 // 0x576650
};

// eastl::basic_string<char> (CaptureCam::+0x18); empty == 0x1667bac/0x1667bad.
struct eastlString {
    const char* mpBegin;                                        // +0x00
    const char* mpEnd;                                          // +0x04
    const char* mpCapacity;                                     // +0x08
    const char* mpAllocator;                                    // +0x0c
    eastlString* assign(const char* first, const char* last);   // 0x454cb0
};

// Image resource handed to the capture camera (+0x10): AddRef is vtable[0],
// Release is vtable[1].
struct ICaptureImage {
    virtual int AddRef();
    virtual int Release();
};

struct CaptureCam;

// 0x1c bytes, vtable 0x140fe88 (AddRef = vtable[0], Release = vtable[1]).
struct cPlanetCapture {
    virtual int  AddRef();                                      // vtable +0x00
    virtual int  Release();                                     // vtable +0x04
    virtual void vfn2();                                        // vtable +0x08
    virtual void vfn3();                                        // vtable +0x0c
    virtual void* SubmitCapture(int unused, void* desc);        // vtable +0x10
    char  m_bases[8];                   // +0x04 (second-base image installed by the ctor)
    bool  mInit;                        // +0x0c
    char  m_pad0d[3];                   // +0x0d
    void* mViewer;                      // +0x10
    CaptureCam* mCam;                   // +0x14
    void* m18;                          // +0x18
    cPlanetCapture();
    void Setup(CaptureCam* cam);                                // 0x7b91f0
};

// 0x28 bytes, vtable 0x140ffbc (AddRef = vtable[1], Release = vtable[2]).
struct CaptureCam {
    CaptureCam();
    virtual void vfn0();                                        // vtable +0x00
    virtual int  AddRef();                                      // vtable +0x04
    virtual int  Release();                                     // vtable +0x08
    unsigned        m04;                    // +0x04
    cAtomicRefPtr   mResource;              // +0x08
    float           mRadius;                // +0x0c
    ICaptureImage*  mImage;                 // +0x10
    int             m14;                    // +0x14
    eastlString     mName;                  // +0x18
};

// 0x20 bytes, vtable 0x1452a38 (AddRef = vtable[1], Release = vtable[2]).
struct cCaptureMessage {
    cCaptureMessage();
    virtual void vfn0();                                        // vtable +0x00
    virtual int  AddRef();                                      // vtable +0x04
    virtual int  Release();                                     // vtable +0x08
    unsigned mRefCount;                     // +0x04
    void*    mCapture;                      // +0x08 (the cPlanetCapture)
    void*    m0c;                           // +0x0c
    void*    m10;                           // +0x10 (request id from the params)
    void*    m14;                           // +0x14
    void*    m18;                           // +0x18
    void*    m1c;                           // +0x1c
};

inline cPlanetCapture::cPlanetCapture()
    : mInit(false), mViewer(0), mCam(0), m18(0)
{
}

inline CaptureCam::CaptureCam()
    : m04(0), mImage(0)
{
    mResource.mpObject = 0;
    mName.mpBegin = (const char*)0x1667bac;
    mName.mpEnd = (const char*)0x1667bac;
    mName.mpCapacity = (const char*)0x1667bad;
    mName.mpAllocator = 0;
}

inline cCaptureMessage::cCaptureMessage()
    : mRefCount(0), mCapture(0), m0c(0), m10(0), m14(0), m18(0), m1c(0)
{
}

// Capture-resource manager (TerrainMgr::+0x10b4). Only the slots used by
// 007ba0b0 are named; the rest keep their vtable position.
struct ICaptureResourceMgr {
    virtual void r0();                                                                  // +0x00
    virtual void r1();                                                                  // +0x04
    virtual void r2();                                                                  // +0x08
    virtual void r3();                                                                  // +0x0c
    virtual RectID* Lookup(RectID* dst, void* a, void* b, int type, int c, int d, int e); // +0x10
    virtual void r5();                                                                  // +0x14
    virtual void* Create(int pageId, int allocId);                                       // +0x18
    virtual void r7();   virtual void r8();   virtual void r9();
    virtual void r10();  virtual void r11();  virtual void r12();  virtual void r13();
    virtual void r14();  virtual void r15();  virtual void r16();  virtual void r17();
    virtual void SetResourceName(int pageId, int allocId, const char* name);             // +0x48
};

// Renderer interface; only vtable slot 30 (+0x78) is used here.
struct IRenderer {
    virtual void r00();  virtual void r01();  virtual void r02();  virtual void r03();
    virtual void r04();  virtual void r05();  virtual void r06();  virtual void r07();
    virtual void r08();  virtual void r09();  virtual void r10();  virtual void r11();
    virtual void r12();  virtual void r13();  virtual void r14();  virtual void r15();
    virtual void r16();  virtual void r17();  virtual void r18();  virtual void r19();
    virtual void r20();  virtual void r21();  virtual void r22();  virtual void r23();
    virtual void r24();  virtual void r25();  virtual void r26();  virtual void r27();
    virtual void r28();  virtual void r29();
    virtual void SubmitCaptureRequest(void* request);                                   // +0x78
};

IRenderer* GetRenderer();                                           // 0x0067dd50

// Description record filled on the stack and handed to cPlanetCapture::SubmitCapture.
struct CaptureRequest {
    cCaptureMessage* mMessage;          // +0x00
    int      m04;                       // +0x04
    bool     m08;                       // +0x08
    int      m0c;                       // +0x0c
    int      m10;                       // +0x10
    unsigned mType;                     // +0x14 (0x5fc2c38)
    int      m18;                       // +0x18
    int      m1c;                       // +0x1c
    int      m20;                       // +0x20
    int      m24;                       // +0x24
    int      m28;                       // +0x28
};

// Input parameters of one planet-capture request.
struct CaptureParams {
    char pad0[8];
    float mRadius;                      // +0x08
    int   m0c;                          // +0x0c
    ICaptureImage* mImage;              // +0x10
    cAtomicRefObject* mResource;        // +0x14
    const char* mNameBegin;             // +0x18
    const char* mNameEnd;               // +0x1c
    char pad20[0x28 - 0x20];
    unsigned mRequestId;                // +0x28
};

struct TerrainMgr {
    char pad0[0x10];
    void* m_captureHandle;              // +0x10 (object created from m_captureRect)
    RectID m_captureRect;               // +0x14 (page/alloc pair of the capture target)
    char pad1c[0x10b4 - 0x1c];
    ICaptureResourceMgr* m_captureMgr;  // +0x10b4
    char pad_b8[0x10d1 - 0x10b8];
    bool m_terrainFilterInitialized;    // +0x10d1
    TerrainFilter* m_filter0;           // +0x10d4
    TerrainFilter* m_filter1;           // +0x10d8
    TerrainFilter* m_filter2;           // +0x10dc
    Viewer* m_viewer;                   // +0x10e0
    void Init();
    void CapturePlanet(void* params, void* resourceKey);
    void Teardown();
};

// Intrusive-refcount slot assignment; the retail code emits this exact shape for
// every filter slot: compare against the current value, AddRef the new object,
// publish it, then Release the displaced one.
static void SetFilterRef(TerrainFilter** slot, TerrainFilter* value)
{
    TerrainFilter* old = *slot;
    if (value == old)
        return;
    if (value)
        value->AddRef();
    *slot = value;
    if (old)
        old->Release();
}

// @ 0x007b9e80
void TerrainMgr::Teardown()
{
    if (!m_terrainFilterInitialized)
        return;
    m_viewer->Destroy1();
    Viewer* v = m_viewer;
    if (v) {
        v->~Viewer();
        operator delete[](v);
    }
    m_viewer = 0;
    m_filter0->InnerTeardown();
    TerrainFilter* p0 = m_filter0;
    if (p0) {
        m_filter0 = 0;
        p0->Release();
    }
    m_filter1->InnerTeardown();
    TerrainFilter* p1 = m_filter1;
    if (p1) {
        m_filter1 = 0;
        p1->Release();
    }
    m_filter2->InnerTeardown();
    TerrainFilter* p2 = m_filter2;
    if (p2) {
        m_filter2 = 0;
        p2->Release();
    }
    m_terrainFilterInitialized = false;
}

// ---------------------------------------------------------------------------
// Remaining functions are large timeline/large-image helpers; recorded as
// partial skeletons in partial.txt.
// ---------------------------------------------------------------------------

// @ 0x007b97d0
struct Point2 {
    unsigned x; // +0x00
    unsigned y; // +0x04
};

void __stdcall FUN_007b97d0(Point2* param_1, Point2* param_2, void* param_3, float param_4)
{
    TerrainFilter* filter = 0;
    void* mem = EAAllocate(0xe4, "Graphics", 0, 0, 0, 0);
    if (mem)
        filter = ((TerrainFilter*)mem)->ctor();

    if (filter)
        filter->AddRef();                       // vtable[0]

    filter->Init(false);
    filter->m_materialId = 0x88549f64;
    filter->m_srcRectID.mPageID = param_1->x;
    filter->m_srcRectID.mAllocID = param_1->y;
    filter->m_destRectID.mPageID = param_2->x;
    filter->m_destRectID.mAllocID = param_2->y;
    // SetCustomParams(0, (1.2f, 1.0f, param_4, 1.0f))
    filter->m_customParams[0] = 1.2f;
    filter->m_customParams[1] = 1.0f;
    filter->m_customParams[2] = param_4;
    filter->m_customParams[3] = 1.0f;
    // SetCustomParams(1, (0.0f, 1.0f, 1.0f, 0.0f))
    filter->m_customParams[4] = 0.0f;
    filter->m_customParams[5] = 1.0f;
    filter->m_customParams[6] = 1.0f;
    filter->m_customParams[7] = 0.0f;
    // SetCustomParams(3, (0.0f, 0.0f, 0.0f, 0.0f))
    filter->m_customParams[12] = 0.0f;
    filter->m_customParams[13] = 0.0f;
    filter->m_customParams[14] = 0.0f;
    filter->m_customParams[15] = 0.0f;
    filter->m_clearColor[0] = 0.0f;
    filter->m_clearColor[1] = 0.0f;
    filter->m_clearColor[2] = 0.0f;
    filter->m_clearBeforeDraw = true;
    filter->m_clearColor[3] = 0.0f;

    Viewer viewer;
    viewer.ctor();
    viewer.Init(false);

    DrawParam param;
    param.mViewer = &viewer;
    param.m08 = 0;
    param.m0c = 0;
    param.m10 = 0;

    filter->Draw(0, 0, &param, param_3);        // vtable[3]
    viewer.Destroy1();
    filter->InnerTeardown();
    filter->Release();
}
// @ 0x007b9990
void __stdcall FUN_007b9990(Point2* param_1, Point2* param_2, void* param_3, bool param_4)
{
    TerrainFilter* filter = 0;
    void* mem = EAAllocate(0xe4, "Graphics", 0, 0, 0, 0);
    if (mem)
        filter = ((TerrainFilter*)mem)->ctor();

    if (filter)
        filter->AddRef();                       // vtable[0]

    filter->Init(false);
    filter->m_materialId = 0xdd6d0d15;
    filter->m_srcRectID.mPageID = param_1->x;
    filter->m_srcRectID.mAllocID = param_1->y;
    filter->m_destRectID.mPageID = param_2->x;
    filter->m_destRectID.mAllocID = param_2->y;
    if (param_4) {
        filter->m_clearColor[0] = 0.0f;
        filter->m_clearColor[1] = 0.0f;
        filter->m_clearColor[2] = 0.0f;
        filter->m_clearBeforeDraw = true;
        filter->m_clearColor[3] = 0.0f;
    }

    Viewer viewer;
    viewer.ctor();
    viewer.Init(false);

    DrawParam param;
    param.mViewer = &viewer;
    param.m08 = 0;
    param.m0c = 0;
    param.m10 = 0;

    filter->Draw(0, 0, &param, param_3);        // vtable[3]
    viewer.Destroy1();
    filter->InnerTeardown();
    filter->Release();
}
// @ 0x007b9b00
void TerrainMgr::Init()
{
    if (m_terrainFilterInitialized)
        return;

    // Dedicated viewer used only by the terrain thumbnail filters.
    Viewer* viewer = (Viewer*)EAAllocate(0x174, "Graphics", 0, 0, 0, 0);
    viewer = viewer ? viewer->ctor() : 0;
    m_viewer = viewer;
    viewer->Init(false);

    // Base pass: identity custom params, fully transparent clear.
    TerrainFilter* f0 = (TerrainFilter*)EAAllocate(0xe4, "Graphics", 0, 0, 0, 0);
    f0 = f0 ? f0->ctor() : 0;
    SetFilterRef(&m_filter0, f0);
    m_filter0->Init(false);
    m_filter0->m_materialId = 0x28;
    m_filter0->m_customParams[0] = 1.0f;
    m_filter0->m_customParams[1] = 1.0f;
    m_filter0->m_customParams[2] = 1.0f;
    m_filter0->m_customParams[3] = 1.0f;
    m_filter0->m_customParams[4] = 0.0f;
    m_filter0->m_customParams[5] = 1.0f;
    m_filter0->m_customParams[6] = 1.0f;
    m_filter0->m_customParams[7] = 0.0f;
    m_filter0->m_customParams[12] = 0.0f;
    m_filter0->m_customParams[13] = 0.0f;
    m_filter0->m_customParams[14] = 0.0f;
    m_filter0->m_customParams[15] = 0.0f;
    m_filter0->m_clearColor[0] = 0.0f;
    m_filter0->m_clearColor[1] = 0.0f;
    m_filter0->m_clearColor[2] = 0.0f;
    m_filter0->m_clearBeforeDraw = true;
    m_filter0->m_clearColor[3] = 0.0f;

    // First blur pass: half-resolution, transparent clear.
    TerrainFilter* f1 = (TerrainFilter*)EAAllocate(0xe4, "Terrain/ThumbnailManager/BlurFilter1", 0, 0, 0, 0);
    f1 = f1 ? f1->ctor() : 0;
    SetFilterRef(&m_filter1, f1);
    m_filter1->Init(false);
    m_filter1->m_materialId = 0x64;
    m_filter1->m_clearColor[0] = 0.0f;
    m_filter1->m_clearColor[1] = 0.0f;
    m_filter1->m_clearColor[2] = 0.0f;
    m_filter1->m_clearBeforeDraw = true;
    m_filter1->m_clearColor[3] = 0.0f;
    m_filter1->m_customParams[0] = 1.0f;
    m_filter1->m_customParams[1] = 0.5f;
    m_filter1->m_customParams[2] = 0.5f;
    m_filter1->m_customParams[3] = 0.0f;

    // Second blur pass: same shape as the first.
    TerrainFilter* f2 = (TerrainFilter*)EAAllocate(0xe4, "Terrain/ThumbnailManager/BlurFilter2", 0, 0, 0, 0);
    f2 = f2 ? f2->ctor() : 0;
    SetFilterRef(&m_filter2, f2);
    m_filter2->Init(false);
    m_filter2->m_materialId = 0x64;
    m_filter2->m_clearColor[0] = 0.0f;
    m_filter2->m_clearColor[1] = 0.0f;
    m_filter2->m_clearColor[2] = 0.0f;
    m_filter2->m_clearBeforeDraw = true;
    m_filter2->m_clearColor[3] = 0.0f;
    m_filter2->m_customParams[0] = 1.0f;
    m_filter2->m_customParams[1] = 0.5f;
    m_filter2->m_customParams[2] = 0.5f;
    m_filter2->m_customParams[3] = 0.0f;

    m_terrainFilterInitialized = true;
}
// @ 0x007b9f30
void __stdcall FUN_007b9f30(Viewer* param_1, Point2* param_2, Point2* param_3, void* param_4, float param_5)
{
    TerrainFilter* filter = 0;
    void* mem = EAAllocate(0xe4, "Graphics", 0, 0, 0, 0);
    if (mem)
        filter = ((TerrainFilter*)mem)->ctor();

    if (filter)
        filter->AddRef();                       // vtable[0]

    filter->Init(false);
    filter->m_materialId = 0x88549f64;
    filter->m_srcRectID.mPageID = param_2->x;
    filter->m_srcRectID.mAllocID = param_2->y;
    filter->m_destRectID.mPageID = param_3->x;
    filter->m_destRectID.mAllocID = param_3->y;
    // SetCustomParams(0, (1.6f, 1.0f, param_5, 1.0f))
    filter->m_customParams[0] = 1.6f;
    filter->m_customParams[1] = 1.0f;
    filter->m_customParams[2] = param_5;
    filter->m_customParams[3] = 1.0f;
    // SetCustomParams(1, (0.0f, 1.0f, 1.0f, 0.0f))
    filter->m_customParams[4] = 0.0f;
    filter->m_customParams[5] = 1.0f;
    filter->m_customParams[6] = 1.0f;
    filter->m_customParams[7] = 0.0f;
    // SetCustomParams(3, (0.0f, 0.0f, 0.0f, 0.0f))
    filter->m_customParams[12] = 0.0f;
    filter->m_customParams[13] = 0.0f;
    filter->m_customParams[14] = 0.0f;
    filter->m_customParams[15] = 0.0f;
    filter->m_clearColor[0] = 0.0f;
    filter->m_clearColor[1] = 0.0f;
    filter->m_clearColor[2] = 0.0f;
    filter->m_clearColor[3] = 0.0f;
    filter->m_clearBeforeDraw = true;
    filter->m_preSetViewport = true;

    DrawParam param;
    param.mViewer = param_1;
    param.m08 = 0;
    param.m0c = 0;
    param.m10 = 0;

    filter->Draw(0, 0, &param, param_4);        // vtable[3]
    filter->InnerTeardown();
    filter->Release();
}
// @ 0x007ba0b0
void TerrainMgr::CapturePlanet(void* params, void* resourceKey)
{
    const CaptureParams* p = (const CaptureParams*)params;

    // Capture object (holds the private viewer plus the camera).
    cPlanetCapture* capture = new ("Graphics", 0, 0, 0, 0) cPlanetCapture;
    if (capture)
        capture->AddRef();                      // vtable[0]

    // Resolve the target surface, register it under a name and create the
    // object the capture writes through.
    RectID rect;
    RectID* found = m_captureMgr->Lookup(&rect, resourceKey, resourceKey, 0x15, 0, -1, 0);
    m_captureRect = *found;
    m_captureMgr->SetResourceName(found->mPageID, found->mAllocID, "ThumbnailRTT");
    m_captureHandle = m_captureMgr->Create(m_captureRect.mPageID, m_captureRect.mAllocID);

    // Camera description, built from the request parameters.
    CaptureCam* cam = new ("Graphics", 0, 0, 0, 0) CaptureCam;
    if (cam)
        cam->AddRef();                          // vtable[1]

    ICaptureImage* oldImage = cam->mImage;
    if (p->mImage != oldImage) {
        if (p->mImage)
            p->mImage->AddRef();                // vtable[0]
        cam->mImage = p->mImage;
        if (oldImage)
            oldImage->Release();                // vtable[1]
    }
    cam->mRadius = p->mRadius;
    cam->mResource.Assign(p->mResource);
    cam->m14 = p->m0c;
    if (p->mNameBegin != cam->mName.mpBegin)
        cam->mName.assign(p->mNameBegin, p->mNameEnd);

    capture->Setup(cam);                        // 0x007b91f0

    // Message handed to the host once the capture is queued.
    cCaptureMessage* msg = new ("Graphics", 0, 0, 0, 0) cCaptureMessage;
    if (msg)
        msg->AddRef();                          // vtable[1]
    msg->mCapture = capture;
    msg->m10 = (void*)p->mRequestId;

    CaptureRequest desc;
    desc.mMessage = msg;
    desc.m04 = 0;
    desc.m08 = false;
    desc.m0c = 0;
    desc.m10 = 0;
    desc.mType = 0x5fc2c38;
    desc.m18 = 0;
    desc.m1c = 0;
    desc.m20 = 0;
    desc.m24 = 0;
    desc.m28 = 0;

    void* request = capture->SubmitCapture(0, &desc);   // vtable[4]
    GetRenderer()->SubmitCaptureRequest(request);       // vtable[30]

    if (msg)
        msg->Release();                         // vtable[2]
    cam->Release();                             // vtable[2]
    capture->Release();                         // vtable[1]
}
