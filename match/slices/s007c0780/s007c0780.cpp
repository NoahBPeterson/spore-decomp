// Slice s007c0780 — SP::cThumbnailManager::HandleMessage dispatcher, the
// cContentValidationSummarizer constructor it uses, and a destructor.
// /O2 /MD /Gy /EHsc /TP /arch:SSE2.
#include "types.h"
#include <math.h>
#include <intrin.h>

struct RectID { int mPageID; int mAllocID; };
struct DoneMsg;

// multiple-inheritance base arrangement: the IHandlerRC subobject sits at +4,
// so an override receives `this` = manager + 4 and adjusts by -4.
struct cThumbnailManagerBase { virtual void v0(); };
struct IHandlerRC {
    virtual bool HandleMessage(unsigned int msgId, void* arg);
};

struct cThumbnailManager : cThumbnailManagerBase, IHandlerRC {
    void ThumbnailDone(DoneMsg* msg);
    void FUN_007bf720(void* arg);
    void FUN_007bbde0(void* arg);
    void DilateStart(void* arg);
    void DilateWithoutAODone(void* arg);
    void FUN_007bced0(void* arg);
    void PaletteJobInfo_Shutdown(void* arg);
    void FUN_007b29a0();
    void FUN_007b2970(void* arg);
    void FUN_007b77a0(void* arg);
};

// @ 0x007c1170  SP::cThumbnailManager::HandleMessage
bool IHandlerRC::HandleMessage(unsigned int msgId, void* arg)
{
    switch (msgId) {
    case 0x1c913db: ((cThumbnailManager*)((char*)this - 4))->ThumbnailDone((DoneMsg*)arg); return true;
    case 0x1c91270: ((cThumbnailManager*)((char*)this - 4))->FUN_007bf720(arg); return true;
    case 0x212c1ee: ((cThumbnailManager*)((char*)this - 4))->FUN_007bbde0(arg); return true;
    case 0x21d7528: ((cThumbnailManager*)((char*)this - 4))->DilateStart(arg); return true;
    case 0x21d752f: ((cThumbnailManager*)((char*)this - 4))->DilateWithoutAODone(arg); return true;
    case 0x31e09b4: ((cThumbnailManager*)((char*)this - 4))->FUN_007bced0(arg); return true;
    case 0x5221305: ((cThumbnailManager*)((char*)this - 4))->PaletteJobInfo_Shutdown(arg); return true;
    case 0x50b834d: ((cThumbnailManager*)((char*)this - 4))->FUN_007b29a0(); return true;
    case 0x5fadac4: ((cThumbnailManager*)((char*)this - 4))->FUN_007b2970(arg); return true;
    case 0x5fc2c38: ((cThumbnailManager*)((char*)this - 4))->FUN_007b77a0(arg); return true;
    case 0x7b240a0: ((cThumbnailManager*)((char*)this - 4))->FUN_007b77a0(arg); return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x007c12a0  cContentValidationSummarizer-like constructor (vtable + zero)
// ---------------------------------------------------------------------------
struct ContentValidationSummarizer {
    virtual void v0();
    virtual void v1();
    char pad[0x94 - 0x08];
};

// @ 0x007c1330  matching destructor
void FUN_007c1330(void* p) { (void)p; }

// ===========================================================================
// @ 0x007c0780  SP::cThumbnailManager ambient-occlusion capture setup.
// For a model's bounding box it creates the AO model, a 1/N averaging post
// filter on the AO gather target, and then, for each of N sample directions
// (kAODirections), points shadow viewer i at the model from that direction and
// queues AO render job i as a layer. Returns false if a capture is running.
// ===========================================================================
namespace AO {

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct BoundingBox { Vector3 mMin; Vector3 mMax; };

inline float Length(float x, float y, float z) { return sqrtf(x * x + y * y + z * z); }
inline float InvLength(float x, float y, float z) { return 1.0f / sqrtf(x * x + y * y + z * z + 1e-8f); }

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
    int mFilterIndex;                                           // +0x28 (after padding)
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
              RectID* shadowRect, RectID* gatherRect, int passIndex, int flags);   // 0x007BF9C0
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

    bool CaptureAmbientOcclusion(uint32_t instanceID, uint32_t groupID, const BoundingBox& bbox,
                                 int userData, uint32_t propListID, int target);
};

// @ 0x007c0780
bool cThumbnailManagerAO::CaptureAmbientOcclusion(uint32_t instanceID, uint32_t groupID, const BoundingBox& bbox,
                                                  int userData, uint32_t propListID, int target)
{
    if (mCurrentlyCapturingAO)
        return false;
    mCurrentlyCapturingAO = true;

    RenderTargetManager()->SetTarget(target);
    mSkinModel = mAOModelWorld->CreateModel(instanceID, groupID, 0);
    mMultiplyDiffuseWithAO = false;

    RectID shadowRect;
    shadowRect.mPageID = -1;
    shadowRect.mAllocID = -1;
    RenderTargetManager()->AllocRect(&shadowRect);
    RenderTargetManager()->SetFlag(0);
    RenderTargetManager()->SetFlag(1);
    mAmbOccSplatterViewer->SetRenderMode(9, 1);
    ILayerManager* layerManager = LayerManager();

    const Vector3 center((bbox.mMax.x + bbox.mMin.x) * 0.5f,
                         (bbox.mMax.y + bbox.mMin.y) * 0.5f,
                         (bbox.mMax.z + bbox.mMin.z) * 0.5f);
    const float dx = bbox.mMax.x - bbox.mMin.x;
    const float dy = bbox.mMax.y - bbox.mMin.y;
    const float dz = bbox.mMax.z - bbox.mMin.z;
    const float radius = Length(dx, dy, dz) * 0.5f + 1.0f;

    PropertyListPtr propList;
    float scale = 1.0f;
    int mode = 0;
    float heightOffset = 0.0f;
    int flipCounter = 0;
    int flipPeriod = 4;
    int passCount = 0x40;

    IPropManager* propManager = PropertyManager();
    propList = 0;
    if (propManager->GetPropertyList(propListID, 0x40200100, propList)) {
        GetPropFloat(propList.mpObject, 0x4ee8a87, scale);
        GetPropInt(propList.mpObject, 0x4efaf18, mode);
        GetPropFloat(propList.mpObject, 0x4efbdc8, heightOffset);
        GetPropInt(propList.mpObject, 0x4efd359, flipPeriod);
        GetPropInt(propList.mpObject, 0x5b99de4, passCount);
    }
    const float viewSize = scale * radius;

    mAmbOccGatherViewer->SetRenderMode(0, 0);
    RectID splatRect;
    splatRect.mPageID = -1;
    splatRect.mAllocID = -1;
    RenderTargetManager()->FreeRect(&splatRect, false);
    RenderTargetManager()->FreeRect(&mAOGatherRectID, true);

    FilterPtr filter(new("Graphics", 0, 0, 0, 0) cJobPostFilter());
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
        viewer->SetViewWindow(viewSize, viewSize);
        viewer->SetNearPlane(0.1f);
        viewer->SetFarPlane(radius * 2.0f);

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
        camera.mPosition.z = z * radius + center.z + heightOffset;
        viewer->SetCameraTransform(&camera);

        RectID shadowMapRect;
        shadowMapRect.mPageID = -1;
        shadowMapRect.mAllocID = -1;
        RenderTargetManager()->SelectRect(&shadowMapRect);
        viewer->SetRenderMode(2, 0);
        Vector4 clearColor;
        clearColor.x = 0.0f;
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
        msg->mGatherAllocID = shadowRect.mAllocID;
        msg->mGatherPageID = shadowRect.mPageID;
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
        MeshVector meshes;

        mAmbOccRenderJob[i]->Init(mAOModelWorld, meshes, viewer, mAmbOccSplatterViewer,
                                  &shadowMapRect, &splatRect, i, 0);
        layerManager->AddLayer(mAmbOccRenderJob[i]->GetLayer(0, &info));
    }
    return true;
}

}  // namespace AO
