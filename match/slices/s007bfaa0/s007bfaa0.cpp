// Slice s007bfaa0 -- SP::cTestScript::HandleMessage renderer, an empty EH-framed stub, and the
// ambient-occlusion capture routine 0x007bfee0 (a sibling of 0x007c0780 in slice s007c0780: same
// per-direction shadow viewer / AO job loop, but the bounds, shadow rect and meshes come from the caller).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.  See nonmatching.txt for the completion
// diffs and equivalence verdicts.
#include "types.h"
#include <math.h>
#include <intrin.h>

struct RectID { int mPageID; int mAllocID; };

// ---------------------------------------------------------------------------
// 0x007bfaa0: cTestScript mesh-stream renderer.
// Globals carry their VA so the equivalence resolver can bind them.
// ---------------------------------------------------------------------------
extern uint32_t g_16f9528;                             // softStateDirty
extern int32_t  g_16f96a0;                             // transformType
extern void*    g_16fa380;                             // current transform pointer
extern __declspec(align(16)) float g_16fa4f0[16];      // transformLocalCopy
extern uint32_t g_16fa38c;                             // renderStateDirty
extern int32_t  g_16f9218;
extern int32_t  g_16f923c;

extern "C" int  FUN_011f13a0();                        // 0x011f13a0 GetBlendMode
extern "C" void FUN_011f1340(int);                     // 0x011f1340 SetBlendMode
extern "C" void FUN_00777bf0();                        // 0x00777bf0
extern "C" void FUN_00777c10();                        // 0x00777c10
extern "C" void __fastcall FUN_007789d0(void* state);  // 0x007789d0
extern "C" void FUN_0072ace0(void*, void*, void*, void*, int, void*);  // 0x0072ace0
extern "C" void* FUN_0067dcc0();                       // 0x0067dcc0
extern "C" void* FUN_0067dd50();                       // 0x0067dd50

namespace SP {

struct IntMap {                                        // 0x18 bytes
    int m00, m04, m08, m0C, m10, m14;
    int& operator[](const int* key);                   // 0x004210f0
};

struct RenderViewer {
    void SetRaster(RectID* rect, bool flag);           // 0x007c4be0
    bool Update();                                     // 0x007c4fd0
    void Clear(int flags);                             // 0x007c3c50
    void FlushEnd();                                   // 0x007c3c10
};

struct MeshStreamEntry {                               // 0x38 bytes
    int   mField00;                                    // +0x00
    float mTranslation[3];                             // +0x04
    float mScale;                                      // +0x10
    float mMatrix[9];                                  // +0x14
};

struct ItemList {
    void Fn(int, int, int, int);                       // 0x007b49f0
};

struct LayerDesc {                                     // 0x2c bytes
    int      mFlags;                                   // +0x00
    int      mField04;                                 // +0x04
    bool     mbField08;                                // +0x08
    int      mField0C;                                 // +0x0c
    int      mField10;                                 // +0x10
    uint32_t mDoneMessageID;                           // +0x14
    void*    mpDoneMessage;                            // +0x18
    int      mField1C;                                 // +0x1c
    int      mField20;                                 // +0x20
    int      mField24;                                 // +0x24
    int      mField28;                                 // +0x28
};

struct cTestScript {
    char              pad00[0x0c];
    void**            mMeshBegin;                      // +0x0c
    void**            mMeshEnd;                        // +0x10
    char              pad14[0x0c];
    void**            mpShaderStates;                  // +0x20
    char              pad24[0x10];
    IntMap            mMap34;                          // +0x34
    void*             mpMapsBegin;                     // +0x4c
    void*             mpMapsEnd;                       // +0x50
    char              pad54[0x0c];
    ItemList*         mpItemList;                      // +0x60
    RectID            mRect64;                         // +0x64
    RenderViewer*     mpViewer;                        // +0x6c
    int               mIndex70;                        // +0x70
    int               mCount74;                        // +0x74
    char              pad78[4];
    MeshStreamEntry*  mpEntries;                       // +0x7c
    char              pad80[0x10];
    void*             mpMessage;                       // +0x90
    void HandleMessage(void* a, void* b, void* c, void* stats);
};

}  // namespace SP

// @ 0x007bfaa0  SP::cTestScript::HandleMessage
void SP::cTestScript::HandleMessage(void* a, void* b, void* c, void* stats)
{
    bool reachedEnd = false;

    if (mMeshBegin == mMeshEnd)
        goto tail;

    g_16f9528 |= 1;
    g_16f96a0 = 4;
    g_16fa380 = g_16fa4f0;

    {
        __m128 r0 = _mm_setr_ps(1.0f, 0.0f, 0.0f, 0.0f);
        __m128 r1 = _mm_setr_ps(0.0f, 1.0f, 0.0f, 0.0f);
        __m128 r2 = _mm_setr_ps(0.0f, 0.0f, 1.0f, 0.0f);
        __m128 r3 = _mm_setzero_ps();
        __declspec(align(16)) float ident[16];
        _mm_store_ps(&ident[0], r0);
        _mm_store_ps(&ident[4], r1);
        _mm_store_ps(&ident[8], r2);
        _mm_store_ps(&ident[12], r3);
        _mm_store_ps(&g_16fa4f0[0], r0);
        _mm_store_ps(&g_16fa4f0[4], r1);
        _mm_store_ps(&g_16fa4f0[8], r2);
        _mm_store_ps(&g_16fa4f0[12], r3);

        int savedBlend = FUN_011f13a0();
        FUN_011f1340(0x10002);
        int saved9218 = g_16f9218;
        bool was4 = (g_16f923c == 4);
        g_16f923c = 8;
        g_16fa38c |= 0x10080;
        g_16f9218 = 0;

        int count = (int)(mMeshEnd - mMeshBegin);
        int start = mIndex70;
        int end = count;
        if (count - start > mCount74) {
            end = start + mCount74;
            reachedEnd = true;
        }

        FUN_00777bf0();
        mpViewer->SetRaster(&mRect64, true);
        if (mpViewer->Update()) {
            if (mIndex70 == 0)
                mpViewer->Clear(7);
            for (int i = mIndex70; i < end; ++i) {
                MeshStreamEntry* e = &mpEntries[i];
                float s = e->mScale;
                __declspec(align(16)) float m[16];
                m[0]  = e->mMatrix[0] * s;
                m[1]  = e->mMatrix[1] * s;
                m[2]  = e->mMatrix[2] * s;
                m[4]  = e->mMatrix[3] * s;
                m[5]  = e->mMatrix[4] * s;
                m[6]  = e->mMatrix[5] * s;
                m[8]  = e->mMatrix[6] * s;
                m[9]  = e->mMatrix[7] * s;
                m[10] = e->mMatrix[8] * s;
                m[12] = e->mTranslation[0];
                m[13] = e->mTranslation[1];
                m[14] = e->mTranslation[2];
                _mm_store_ps(&g_16fa4f0[0],  _mm_load_ps(&m[0]));
                _mm_store_ps(&g_16fa4f0[4],  _mm_load_ps(&m[4]));
                _mm_store_ps(&g_16fa4f0[8],  _mm_load_ps(&m[8]));
                _mm_store_ps(&g_16fa4f0[12], _mm_load_ps(&m[12]));
                g_16f96a0 = 2;
                g_16fa380 = g_16fa4f0;
                FUN_00777bf0();
                int key = i;
                int meshId = mMap34[&key];
                void* state = mpShaderStates[meshId];
                if (state)
                    FUN_007789d0(state);
                void* mapPtr = (mpMapsBegin == mpMapsEnd) ? 0
                              : (char*)mpMapsBegin + i * 0x18;
                FUN_0072ace0(mMeshBegin[i], stats, 0, mapPtr, 0, 0);
                FUN_00777c10();
            }
            mpViewer->FlushEnd();
        }
        FUN_00777c10();
        FUN_011f1340(savedBlend);
        g_16fa38c |= 0x10000;
        _mm_store_ps(&g_16fa4f0[0],  _mm_load_ps(&ident[0]));
        _mm_store_ps(&g_16fa4f0[4],  _mm_load_ps(&ident[4]));
        _mm_store_ps(&g_16fa4f0[8],  _mm_load_ps(&ident[8]));
        _mm_store_ps(&g_16fa4f0[12], _mm_load_ps(&ident[12]));
        g_16f923c = was4 ? 4 : 8;
        g_16f9218 = saved9218;
        g_16f96a0 = 4;
        g_16fa380 = g_16fa4f0;
        mIndex70 = end;
        if (reachedEnd) {
            LayerDesc info;
            info.mFlags = 1;
            info.mField04 = 0;
            info.mbField08 = true;
            info.mField0C = 0;
            info.mField10 = 0;
            info.mDoneMessageID = 0;
            info.mpDoneMessage = 0;
            info.mField1C = 0;
            info.mField20 = 0;
            info.mField24 = 0;
            info.mField28 = 0;
            void* mgr = FUN_0067dd50();
            typedef void (__thiscall *AddWorkFn)(void*, void*, int, LayerDesc*);
            AddWorkFn fn = (AddWorkFn)(*(void***)mgr)[0x78 / 4];
            fn(mgr, this, 0, &info);
            return;
        }
    }

tail:
    if (mpItemList)
        mpItemList->Fn((int)(size_t)a, (int)(size_t)b, (int)(size_t)c, (int)(size_t)stats);
    if (mpMessage) {
        void* server = FUN_0067dcc0();
        typedef void (__thiscall *MsgFn)(void*, int, void*, int, int);
        MsgFn fn = (MsgFn)(*(void***)server)[0x18 / 4];
        fn(server, 0x1c91270, mpMessage, 0, 0);
    }
}

// @ 0x007bfeb0  empty EH-framed stub (5 stack args)
void __stdcall FUN_007bfeb0(int a, int b, int c, int d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    try {
    } catch (...) {
    }
}

namespace AO {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct BoundingBox { Vector3 mMin; Vector3 mMax; };

inline float Length(float x, float y, float z) { return sqrtf(x * x + y * y + z * z); }
inline float InvLength(float x, float y, float z) { float l2 = x * x + y * y + z * z + 1e-8f; return 1.0f / sqrtf(l2); }

struct Vector4 { float x, y, z, w; };
__declspec(align(16)) struct CameraMatrix { Vector4 mUp, mRight, mBack, mPosition; };   // w left unset

Vector3 OrthogonalVector(const Vector3& v);                     // 0x006985B0 (cdecl)

extern const Vector3 kAODirections[];                           // 0x0155BBD8

struct cViewer {
    void SetClearColor(const Vector4* color);                   // 0x007C3C20
    void SetRenderMode(int mode, int flags);                    // 0x007C3CE0
    void SetNearPlane(float n);                                 // 0x007C4BA0
    void SetFarPlane(float f);                                  // 0x007C4BC0
    void SetCameraTransform(const CameraMatrix* m);             // 0x007C4D20
    void SetViewWindow(float w, float h);                       // 0x007C5440
};

struct IRenderTargetManager {
    virtual void r00(); virtual void r01(); virtual void r02(); virtual void r03(); virtual void r04();
    virtual void r05(); virtual void r06(); virtual void r07(); virtual void r08();
    virtual void SetFlag(int on);                               // +0x24
    virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14();
    virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19();
    virtual void r20(); virtual void r21(); virtual void r22(); virtual void r23(); virtual void r24();
    virtual void r25(); virtual void r26(); virtual void r27(); virtual void r28(); virtual void r29();
    virtual void r30(); virtual void r31(); virtual void r32(); virtual void r33(); virtual void r34();
    virtual void r35(); virtual void r36(); virtual void r37(); virtual void r38(); virtual void r39();
    virtual void r40(); virtual void r41(); virtual void r42(); virtual void r43();
    virtual void AllocRect(RectID* rect);                       // +0xB0
    virtual void r45(); virtual void r46(); virtual void r47(); virtual void r48(); virtual void r49();
    virtual void r50(); virtual void r51();
    virtual void SelectRect(RectID* rect);                      // +0xD0
    virtual void r53(); virtual void r54(); virtual void r55();
    virtual void FreeRect(RectID* rect, bool b);                // +0xE0
    virtual void r57(); virtual void r58(); virtual void r59();
    virtual void SetTarget(int a);                              // +0xF0
};
IRenderTargetManager* RenderTargetManager();                    // 0x0067DD40

struct ILayerManager {
    virtual void l00(); virtual void l01(); virtual void l02(); virtual void l03(); virtual void l04();
    virtual void l05(); virtual void l06(); virtual void l07(); virtual void l08(); virtual void l09();
    virtual void l10(); virtual void l11(); virtual void l12(); virtual void l13(); virtual void l14();
    virtual void l15(); virtual void l16(); virtual void l17(); virtual void l18(); virtual void l19();
    virtual void l20(); virtual void l21(); virtual void l22(); virtual void l23(); virtual void l24();
    virtual void l25(); virtual void l26(); virtual void l27(); virtual void l28(); virtual void l29();
    virtual void AddLayer(void* layer);                         // +0x78
};
ILayerManager* LayerManager();                                  // 0x0067DD50

// App property lists
struct Property {
    float* GetValueFloat();                                     // 0x0041EA70
    int*   GetValueInt();                                       // 0x0041E990
};
struct PropertyList {
    virtual void p00();
    virtual int Release();                                      // +0x04
    virtual void p02(); virtual void p03(); virtual void p04(); virtual void p05(); virtual void p06();
    virtual bool HasProperty(uint32_t id);                      // +0x1C
    virtual void p08(); virtual void p09();
    virtual Property* GetProperty(uint32_t id);                 // +0x28
};
struct PropertyListPtr {
    PropertyList* mpObject;
    PropertyListPtr() : mpObject(0) {}
    ~PropertyListPtr() { if (mpObject) mpObject->Release(); }
    PropertyListPtr& operator=(PropertyList* p)
    {
        if (p != mpObject) {
            PropertyList* const old = mpObject;
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    PropertyList* operator->() const { return mpObject; }
};
struct IPropManager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03(); virtual void m04();
    virtual void m05(); virtual void m06(); virtual void m07(); virtual void m08(); virtual void m09();
    virtual void m10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& dst);   // +0x2C
};
IPropManager* PropertyManager();                                // 0x0067DE30

inline void GetPropFloat(PropertyList* pl, uint32_t id, float& dst)
{
    if (pl->HasProperty(id)) dst = *pl->GetProperty(id)->GetValueFloat();
}
inline void GetPropInt(PropertyList* pl, uint32_t id, int& dst)
{
    if (pl->HasProperty(id)) dst = *pl->GetProperty(id)->GetValueInt();
}

void* AllocGraphics(size_t size, const char* name, int a, int b, int c, int d);   // 0x00F473A0 operator new
}  // namespace AO

inline void* operator new(size_t size, const char* name, int a, int b, int c, int d)
{
    return AO::AllocGraphics(size, name, a, b, c, d);
}

namespace AO {

struct IModel;
struct IModelWorld {
    virtual void w00(); virtual void w01(); virtual void w02();
    virtual IModel* CreateModel(uint32_t instanceID, uint32_t groupID, int flags);   // +0x0C
};
struct ModelPtr {
    IModel* mpObject;
    ModelPtr& operator=(IModel* p);                             // 0x00478DB0
};

class cJobPostFilter {
public:
    virtual int AddRef();                                       // +0x00
    virtual int Release();                                      // +0x04
    cJobPostFilter();                                           // 0x007B8550
    void Init(int materialID, RectID* src, RectID* dst, int raster);   // 0x007B9510
    char pad04[0x3c - 0x04];
    float mCustomParams[8];                                     // +0x3C
    char pad5c[0xe4 - 0x5c];
};
struct FilterPtr {
    cJobPostFilter* mpObject;
    FilterPtr(cJobPostFilter* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~FilterPtr() { if (mpObject) mpObject->Release(); }
    cJobPostFilter* operator->() const { return mpObject; }
};

struct cFilterChainJob {
    char pad0[0x20];
    bool mbActive;                                              // +0x20
    char pad21[7];
    int mFilterIndex;                                           // +0x28
    void AddFilter(cJobPostFilter* filter);                     // 0x007B9750
    void Start() { if (!mbActive) { mbActive = true; mFilterIndex = 0; } }
};

// The "AO pass done" message (0x40 bytes): ref-counted message base + payload.
struct cMessageBase {
    virtual ~cMessageBase();
    virtual int AddRef();                                       // +0x04
    virtual int Release();                                      // +0x08
    volatile long mnRefCount;                                   // +0x04
    cMessageBase() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cAOPassMessage : cMessageBase {
    int mPassIndex;  int pad0c;                                 // +0x08
    int mUserData;   int pad14;                                 // +0x10
    int mPassCount;  int pad1c;                                 // +0x18
    int mGatherAllocID; int pad24;                              // +0x20
    int mGatherPageID;  int pad2c;                              // +0x28
    int mPropListID; int pad34;                                 // +0x30
    int mField38;                                               // +0x38
    int pad3c;
    cAOPassMessage() : mField38(0) {}
    ~cAOPassMessage();
};
struct MessagePtr {
    cMessageBase* mpObject;
    MessagePtr() : mpObject(0) {}
    ~MessagePtr() { if (mpObject) mpObject->Release(); }
    MessagePtr& operator=(cMessageBase* p) { if (p) p->AddRef(); mpObject = p; return *this; }
};

// Layer description handed to the AO job (message 0x212c1ee is posted when it is done).
struct LayerInfo {
    int mFlags;                                                 // +0x00
    int mField04;                                               // +0x04
    bool mbField08;                                             // +0x08
    int mField0C;                                               // +0x0C
    int mField10;                                               // +0x10
    uint32_t mDoneMessageID;                                    // +0x14
    MessagePtr mpDoneMessage;                                   // +0x18
    int mField1C, mField20, mField24, mField28;                 // +0x1C
};

struct MeshVector {                                             // eastl::vector<AutoRefCount<cMeshData>>
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    int mAllocator;
    MeshVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~MeshVector() { DestroyRange(mpBegin, mpEnd); if (mpBegin) Free(mpBegin); }
    void DestroyRange(void** first, void** last);               // 0x004243E0
    static void Free(void* p);
};

struct cAmbOccJob {
    virtual void j00(); virtual void j01(); virtual void j02(); virtual void j03();
    virtual void* GetLayer(int a, LayerInfo* info);             // +0x10
    void Init(IModelWorld* world, const MeshVector& meshes, cViewer* shadowViewer, cViewer* splatterViewer,
              RectID* shadowRect, RectID* gatherRect, int passIndex, bool flag);   // 0x007BF9C0
};

struct cThumbnailManagerAO {
    char pad0[0x88];
    cViewer* mAmbOccShadowViewers[1024];                        // +0x88
    cViewer* mAmbOccSplatterViewer;                             // +0x1088
    cViewer* mAmbOccGatherViewer;                               // +0x108C
    char pad1090[0x10bc - 0x1090];
    bool mMultiplyDiffuseWithAO;                                // +0x10BC
    char pad10bd[0x10c4 - 0x10bd];
    IModelWorld* mAOModelWorld;                                 // +0x10C4
    ModelPtr mSkinModel;                                        // +0x10C8
    int mSplatInProgress;                                       // +0x10CC
    bool mCurrentlyCapturingAO;                                 // +0x10D0
    char pad10d1[0x10f4 - 0x10d1];
    RectID mAOGatherRectID;                                     // +0x10F4
    cFilterChainJob* mAOPostProcessLayer;                       // +0x10FC
    cAmbOccJob* mAmbOccRenderJob[1024];                         // +0x1100

    void FUN_007b5c80(MeshVector* meshes, Vector3* outCenter, float* outRadius);        // 0x007B5C80, ret 0xc (this unused)
    void FUN_007b87f0(IModelWorld* world, Vector3* outCenter, float* outRadius);        // 0x007B87F0, ret 0xc (this unused)
    bool CaptureAmbientOcclusionB(RectID* shadowRect, IModelWorld* world, MeshVector* meshes, int userData,
                                  uint32_t propListID, bool useMeshes);                 // 0x007BFEE0
};


// @ 0x007bfee0
bool cThumbnailManagerAO::CaptureAmbientOcclusionB(RectID* shadowRect, IModelWorld* world, MeshVector* meshes,
                                                   int userData, uint32_t propListID, bool useMeshes)
{
    if (mCurrentlyCapturingAO)
        return false;
    mCurrentlyCapturingAO = true;
    mMultiplyDiffuseWithAO = true;

    RenderTargetManager()->SetFlag(0);
    RenderTargetManager()->SetFlag(1);
    mAmbOccSplatterViewer->SetRenderMode(9, 0);
    ILayerManager* layerManager = LayerManager();

    RectID shadowMapRect;
    shadowMapRect.mPageID = -1;
    shadowMapRect.mAllocID = -1;
    RenderTargetManager()->SelectRect(&shadowMapRect);

    Vector3 center;
    float radius = 0.0f;
    if (useMeshes)
        FUN_007b5c80(meshes, &center, &radius);
    else
        FUN_007b87f0(world, &center, &radius);

    PropertyListPtr propList;
    int mode = 0;
    int flipCounter = 0;
    int flipPeriod = 4;
    int passCount = 0x40;

    IPropManager* propManager = PropertyManager();
    propList = 0;
    if (propManager->GetPropertyList(propListID, 0x40200100, propList)) {
        if (propList->HasProperty(0x4ee8a87)) propList->GetProperty(0x4ee8a87);
        if (propList->HasProperty(0x4efaf18)) mode = *propList->GetProperty(0x4efaf18)->GetValueInt();
        if (propList->HasProperty(0x4efbdc8)) propList->GetProperty(0x4efbdc8);
        if (propList->HasProperty(0x4efd359)) flipPeriod = *propList->GetProperty(0x4efd359)->GetValueInt();
        if (propList->HasProperty(0x5b99de4)) passCount = *propList->GetProperty(0x5b99de4)->GetValueInt();
    }

    mAmbOccGatherViewer->SetRenderMode(0, 0);
    FilterPtr filter(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
    RectID splatRect;
    splatRect.mPageID = -1;
    splatRect.mAllocID = -1;
    RenderTargetManager()->FreeRect(&splatRect, false);
    RenderTargetManager()->FreeRect(&mAOGatherRectID, true);

    filter->Init(0x2d, &splatRect, &mAOGatherRectID, 0);
    const float weight = 1.0f / (float)passCount;
    filter->mCustomParams[3] = 1.0f;
    filter->mCustomParams[2] = weight;
    filter->mCustomParams[0] = weight;
    filter->mCustomParams[1] = weight;
    filter->mCustomParams[4] = 0.0f;
    filter->mCustomParams[5] = 1.0f;
    filter->mCustomParams[6] = 1.0f;
    filter->mCustomParams[7] = 0.0f;
    mAOPostProcessLayer->Start();
    mAOPostProcessLayer->AddFilter(filter.mpObject);

    const float farPlane = radius * 5.0f;
    for (int i = 0; i < passCount; i++) {
        const Vector3 dir = kAODirections[i];
        float z = dir.z;
        if (mode == 1) {
            if (dir.z < 0.0f && ++flipCounter == flipPeriod) {
                z = fabsf(dir.z);
                flipCounter = 0;
            }
        } else if (mode == 2) {
            if (dir.z < 0.0f && ++flipCounter == flipPeriod) {
                z = -fabsf(dir.z);
                flipCounter = 0;
            }
        }

        cViewer* viewer = mAmbOccShadowViewers[i];
        const Vector3 view(dir.x, dir.y, z);
        viewer->SetViewWindow(radius, radius);
        viewer->SetNearPlane(0.1f);
        viewer->SetFarPlane(farPlane);

        const Vector3 ortho = OrthogonalVector(view);
        const float invUp = InvLength(ortho.x, ortho.y, ortho.z);
        const Vector3 up(ortho.x * invUp, invUp * ortho.y, invUp * ortho.z);
        const Vector3 side(view.z * up.y - view.y * up.z,
                           up.z * view.x - view.z * up.x,
                           view.y * up.x - up.y * view.x);
        const float invSide = InvLength(side.x, side.y, side.z);

        CameraMatrix camera;
        camera.mUp.x = up.x;
        camera.mUp.y = up.y;
        camera.mUp.z = up.z;
        camera.mRight.x = invSide * side.x;
        camera.mRight.y = invSide * side.y;
        camera.mRight.z = invSide * side.z;
        camera.mBack.x = -view.x;
        camera.mBack.y = -view.y;
        camera.mBack.z = -view.z;
        camera.mPosition.x = dir.x * radius + center.x;
        camera.mPosition.y = dir.y * radius + center.y;
        camera.mPosition.z = z * radius + center.z;
        viewer->SetCameraTransform(&camera);

        viewer->SetRenderMode(2, 0);
        Vector4 clearColor;
        clearColor.x = 1.0f;
        clearColor.y = 0.0f;
        clearColor.z = 0.0f;
        clearColor.w = 0.0f;
        viewer->SetClearColor(&clearColor);

        cAOPassMessage* msg = new("Graphics", 0, 0, 0, 0) cAOPassMessage();
        LayerInfo info;
        info.mpDoneMessage = msg;
        msg->mPassIndex = i;
        msg->mUserData = userData;
        msg->mPassCount = passCount;
        msg->mGatherAllocID = shadowRect->mAllocID;
        msg->mGatherPageID = shadowRect->mPageID;
        msg->mPropListID = propListID;
        info.mFlags = 1;
        info.mField04 = 0;
        info.mbField08 = false;
        info.mField0C = 0;
        info.mField10 = 0;
        info.mDoneMessageID = 0x212c1ee;
        info.mField1C = 0;
        info.mField20 = 0;
        info.mField24 = 0;
        info.mField28 = 0;

        mAmbOccRenderJob[i]->Init(world, *meshes, viewer, mAmbOccSplatterViewer,
                                  &shadowMapRect, &splatRect, i, useMeshes);
        layerManager->AddLayer(mAmbOccRenderJob[i]->GetLayer(0, &info));
    }
    return true;
}

}  // namespace AO
