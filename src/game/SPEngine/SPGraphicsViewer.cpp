// src/game/SPEngine/SPGraphicsViewer.cpp -- migrated from slice(s) s004b8af0, s007c4be0, s007c3ba0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsViewer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cViewer.h"
#include "cSPMatrix4.h"

// unnamed retail callees and globals (address in the comment)
extern float g_153c7a8;
extern float g_1635db8, g_1635dbc, g_1635dc0, g_1635dc4;
extern float g_10000f;
extern void g_FUN_007c4940_body();
#include <math.h>
#include "SP/cShaderDataRenderType.h"
#include "rw/core/arena/Arena.h"
#include "SP/cISPEditorNameProvider.h"
#include "SP/cSPEditorModel.h"
#include "hkVector4.h"
#include "hkCollisionFilter.h"
#include "hkWorldCinfo.h"
#include "hkWorld.h"

// ---- items of slice s007c3ba0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec4 { float x, y, z, w; };
struct Matrix44 {
    Vec4 xAxis, yAxis, zAxis, wAxis;    // +0x00,+0x10,+0x20,+0x30
    void FUN_007c3da0(float* dst);
};
struct Camera {
    char pad0[0x54];
    float f54, f58;                 // +0x54,+0x58
    float f5c, f60;                 // +0x5c,+0x60 (width,height)
    float f64, f68;                 // +0x64,+0x68 (inverse)
    int   n6c;                      // +0x6c (projection type)
    float f70, f74;                 // +0x70,+0x74
    int   vpX, vpY, vpW, vpH;       // +0x78,+0x7c,+0x80,+0x84 (viewport)
    int   f88, f8c;                 // +0x88,+0x8c
    void SetClear(void* color, int flags);
};
struct cViewer {
    Matrix44 mCameraToWorldTransform;      // +0x00
    Matrix44 mWorldToCameraTransform;      // +0x40
    Matrix44 mCameraToClipTransform;       // +0x80
    Matrix44 mWorldToClipTransform;        // +0xc0
    Matrix44 mClipToWorldTransform;        // +0x100
    float    mClearColor[4];               // +0x140
    int      mRenderType;                  // +0x150
    int      mRenderTypeVariation;         // +0x154
    int      mShaderDataRT;                // +0x158
    float    mMaterialLODs[4];             // +0x15c
    unsigned char mTileRender;             // +0x16c
    char pad1[3];
    Camera*  mCamera;                      // +0x170

    bool   FUN_007c3ba0();
    void   FUN_007c3c50(unsigned char);
    float  FUN_007c3c90();
    float  FUN_007c3ca0();
    void   GetCameraLocationInfo(float*, float*, float*, float*);
    cViewer* FUN_007c3f70();
    void   FUN_007c4000();
    void   FUN_007c4010(unsigned*);
    float  FUN_007c4050();
    float  FUN_007c40a0();
    void   FUN_007c40c0(float*, float*);
    float  FUN_007c40e0();
    void   FUN_007c4a60(unsigned short*);
    void   FUN_007c4ad0(float, float);
    void   FUN_007c4b00(float, float);
    void   FUN_007c4b50(float);
    void   FUN_007c4ba0(float);
    void   FUN_007c4bc0(float);
    __declspec(noinline) void FUN_007c4940();   // recompute derived transforms
};
extern float g_153c7a8;
extern float g_1635db8, g_1635dbc, g_1635dc0, g_1635dc4;
extern float g_10000f;
extern void g_FUN_007c4940_body();
// ---- items of slice s007c3ba0 end

// ---- items of slice s007c4be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* FUN_00761380();                 // default raster factory / init
extern float g_identityMatrix[16];           // 0x1635fa0
extern void* g_defaultCameraRaster;          // 0x15d0838
extern void* g_defaultZBufferRaster;         // 0x15d083c
extern float g_tanScaleA;                    // 0x153c7a8
extern float g_tanScaleB;                    // 0x1401c04
extern float g_aspectEps;                    // 0x153c98c
extern float g_defaultFov;                   // 0x1410350
extern "C" void* EANew(int size, const char* name, int, int, int, int);  // 0xf473a0
extern "C" float tanf(float);                                            // CRT
extern "C" void  DrawShader(int cmd, void* data, int changed);           // 0x777ae0
extern "C" void  FUN_011f38f0(int a, void* b);                           // 0x11f38f0
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
struct D3DVIEWPORT9 { u32 X, Y, Width, Height; float MinZ, MaxZ; };
struct rwCamera {
    float m_transform[16];       // +0x00  Matrix44Affine
    void* m_raster[4];           // +0x40
    void* m_zbuffer;             // +0x50
    float m_viewOffset[2];       // +0x54
    float m_viewWindow[2];       // +0x5c
    float m_recipViewWindow[2];  // +0x64
    int   m_projectionType;      // +0x6c
    float m_nearPlane;           // +0x70
    float m_farPlane;            // +0x74
    D3DVIEWPORT9 m_viewport;     // +0x78
    void* m_window;              // +0x90
    u32   m_stencilClear;        // +0x94

    void  AssignTo(void* out);        // 0x7779e0
    int   Check();                    // 0x11f3f20
    void  SetTexture(void* t);        // 0x7c3b70
    void  SetSize(int x, int y, int w, int h);  // 0x76d7d0
    void  GetViewport(void* out);     // 0x7c4010
};
struct cViewer_s007c_4be0 {
    float mCameraToWorld[16];    // +0x00
    float mWorldToCamera[16];    // +0x40
    float mCameraToClip[16];     // +0x80
    float mWorldToClip[16];      // +0xc0
    float mClipToWorld[16];      // +0x100
    u8    mClearColor[16];       // +0x140
    int   mRenderType;           // +0x150
    int   mRenderTypeVariation;  // +0x154
    void* mShaderDataRT;         // +0x158
    float mMaterialLODs[4];      // +0x15c
    bool  mTileRender;           // +0x16c
    u8    pad16d[3];
    rwCamera* mCamera;           // +0x170

    void UpdateTransforms();                 // 0x7c4940 (extern)
    void SetViewportRect(u16* r);            // 0x7c4a60 (extern)
    void SetAspect(float a);                 // 0x7c4b50 (extern)
    int  BuildTransforms();                  // 0x7c43e0 (extern)

    void SetRaster(int* handle, bool setViewport);
    void SetCameraToWorld(float* m);
    void SetBasis(void* basis);
    void SetCameraToWorldFromBasis(float* p);
    bool Init(bool windowed);  // 0x004b8c10 (cViewer::Init)
    bool Update();
    bool Copy(cViewer_s007c_4be0* src, bool a, bool b);  // 0x007c50b0 (cViewer::Copy)
    void CopyFrom(cViewer_s007c_4be0* src);
    void SetViewportRectArgs(u16 x, u16 y, u16 w, u16 h);
    void SetViewAngle(float a);
    void SetViewAngleY(float a);
    void SetViewWindow(float x, float y);
    void FUN_007c4010(u32* out);     // 0x007c4010 (cViewer method: this->mCamera->m_viewport rect)
};
// 0x011f38f0 is a __thiscall member of VBi (`?FUN_011f38f0@VBi@@QAEXHI@Z`): the original sets ecx
// to the destination camera before releasing the source raster.
struct VBi {
    void FUN_011f38f0(int a, u32 b);
};
struct Renderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual int  v18(int a, int b);
    virtual void v1c();
    virtual void v20(int a, int b, int* out);   // (handle[0], handle[1], &rect): the original pushes rect first
};
extern Renderer* GetRenderer();          // 0x67dda0
struct Basis3 { void Build(void* owner); };  // 0x6b9440
extern u8    g_forceAspect;                  // 0x153c988
struct cShaderDataRenderType { u8 mType; u8 pad[3]; int mVariation; };
// ---- items of slice s007c4be0 end

// ---- items of slice s004b8af0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
inline void* operator new(unsigned int, void* p) { return p; }
typedef float hkReal;
class hkMemory {
public:
virtual void _v0();
virtual void _v1();
virtual void _v2();
virtual void _v3();
    virtual void* allocateChunk(int nbytes, int cl);                 // 0x10
    virtual void deallocateChunk(void* p, int nbytes, int cl);       // 0x14
    static hkMemory* s_instance;                                     // 0x016E4178
    static hkMemory& getInstance() { return *s_instance; }
};
#define HK_DECLARE_CLASS_ALLOCATOR(CLS) \
    void* operator new(unsigned int nbytes) { \
        hkReferencedObject_s004b_8af0* b = static_cast<hkReferencedObject_s004b_8af0*>(hkMemory::getInstance().allocateChunk(nbytes, CLS)); \
        b->m_memSizeAndFlags = (unsigned short)nbytes; \
        return b; } \
    void operator delete(void* p) { \
        hkReferencedObject_s004b_8af0* b = static_cast<hkReferencedObject_s004b_8af0*>(p); \
        hkMemory::getInstance().deallocateChunk(p, b->m_memSizeAndFlags, CLS); }
class hkBaseObject_s004b_8af0 {
public:
    virtual ~hkBaseObject_s004b_8af0() {}
};
class hkReferencedObject_s004b_8af0 : public hkBaseObject_s004b_8af0 {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x12)
    unsigned short m_memSizeAndFlags;           // +0x4
    short m_referenceCount;                     // +0x6
    hkReferencedObject_s004b_8af0() : m_referenceCount(1) {}
    virtual ~hkReferencedObject_s004b_8af0() {}
    // Havok's HK_FORCE_INLINE: a plain inline containing `delete this` is never inlined by cl at /Ob1
    __forceinline void removeReference()
    {
        if (m_memSizeAndFlags != 0) {
            --m_referenceCount;
            if (m_referenceCount == 0)
                delete this;
        }
    }
};
class hkBool_s004b_8af0 {
public:
    char m_bool;
    hkBool_s004b_8af0() {}
    hkBool_s004b_8af0(bool b) { m_bool = (char)b; }
    hkBool_s004b_8af0& operator=(bool e) { m_bool = (char)e; return *this; }
};
class __declspec(align(16)) hkVector4_s004b_8af0 {
public:
    hkReal x, y, z, w;
    hkVector4_s004b_8af0() {}
    hkVector4_s004b_8af0(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
    void operator=(const hkVector4_s004b_8af0& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
    void set(hkReal a, hkReal b, hkReal c, hkReal d = 0.0f) { x = a; y = b; z = c; w = d; }
};
class hkCollidableCollidableFilter_s004b_8af0 { public: virtual ~hkCollidableCollidableFilter_s004b_8af0() {} virtual void isCollisionEnabled() = 0; };
class hkShapeCollectionFilter_s004b_8af0 { public: virtual ~hkShapeCollectionFilter_s004b_8af0() {} virtual void isCollisionEnabled2() = 0; };
class hkRayShapeCollectionFilter_s004b_8af0 { public: virtual ~hkRayShapeCollectionFilter_s004b_8af0() {} virtual void isCollisionEnabled3() = 0; };
class hkRayCollidableFilter_s004b_8af0 { public: virtual ~hkRayCollidableFilter_s004b_8af0() {} virtual void isCollisionEnabled4() = 0; };
class hkCollisionFilter_s004b_8af0 : public hkReferencedObject_s004b_8af0, public hkCollidableCollidableFilter_s004b_8af0,
                          public hkShapeCollectionFilter_s004b_8af0, public hkRayShapeCollectionFilter_s004b_8af0,
                          public hkRayCollidableFilter_s004b_8af0 {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x24)
};
namespace SP {
class SPEditorCollisionFilter : public hkCollisionFilter_s004b_8af0 {
public:
    virtual void isCollisionEnabled();
    virtual void isCollisionEnabled2();
    virtual void isCollisionEnabled3();
    virtual void isCollisionEnabled4();
};
}
class hkWorldCinfo_s004b_8af0 : public hkReferencedObject_s004b_8af0 {
public:
    char pad08[0x10 - 0x8];
    hkVector4_s004b_8af0 m_gravity;                        // +0x10
    char pad20[0xa0 - 0x20];
    hkWorldCinfo_s004b_8af0();                                                  // 0x010880E0
    virtual ~hkWorldCinfo_s004b_8af0() {}
    void setupSolverInfo(int st);                                    // 0x01087FD0
    void setBroadPhaseWorldSize(hkReal size);                        // 0x010881D0
};
class hkCollisionDispatcher_s004b_8af0;
class hkAgentRegisterUtil { public: static void registerAllAgents(hkCollisionDispatcher_s004b_8af0* dis); };  // 0x010C25A0
class hkShape_s004b_8af0 : public hkReferencedObject_s004b_8af0 { public: int m_userData; };
struct hkTypedBroadPhaseHandle_s004b_8af0 { int m_id; char m_type, m_ownerOffset; unsigned short m_objectQualityType; unsigned int m_collisionFilterInfo; };
class hkCollidable_s004b_8af0 {
public:
    char pad00[0x14];
    hkTypedBroadPhaseHandle_s004b_8af0 m_broadPhaseHandle; // +0x14
    hkReal m_allowedPenetrationDepth;           // +0x20
    void setCollisionFilterInfo(unsigned int info) { m_broadPhaseHandle.m_collisionFilterInfo = info; }
};
struct hkMaterial_s004b_8af0 { signed char m_responseType; hkReal m_friction; hkReal m_restitution; };
class hkWorld_s004b_8af0;
class hkWorldObject_s004b_8af0 : public hkReferencedObject_s004b_8af0 {
public:
    hkWorld_s004b_8af0* m_world;                           // +0x8
    void* m_userData;                           // +0xc
    char* m_name;                               // +0x10
    uint32_t m_multithreadLock[2];              // +0x14
    hkCollidable_s004b_8af0 m_collidable;                  // +0x1c
    char pad40[0x58 - 0x40];
    hkCollidable_s004b_8af0* getCollidableRw() { return &m_collidable; }
};
class hkEntity_s004b_8af0 : public hkWorldObject_s004b_8af0 {
public:
    void* m_motion;                             // +0x58
    void* m_simulationIsland;                   // +0x5c
    hkMaterial_s004b_8af0 m_material;                      // +0x60
    char pad6c[0xd0 - 0x6c];
};
class hkRigidBodyCinfo { public:
    unsigned int m_collisionFilterInfo;         // +0x0
    hkShape_s004b_8af0* m_shape;                           // +0x4
    char pad08[0x10 - 0x8];
    hkVector4_s004b_8af0 m_position;                       // +0x10
    char pad20[0xa0 - 0x20];
    hkReal m_restitution;                       // +0xa0
    char padA4[0xb0 - 0xa4];
    signed char m_motionType;                   // +0xb0
    char padB1[0xc0 - 0xb1];
    hkRigidBodyCinfo();                                              // 0x01087ED0
};
class hkRigidBody_s004b_8af0 : public hkEntity_s004b_8af0 {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2a)
    hkRigidBody_s004b_8af0(const hkRigidBodyCinfo& info);                       // 0x010878B0
    void removeReference();                                          // 0x0109AE60 (out of line)
};
class hkWorld_s004b_8af0 : public hkReferencedObject_s004b_8af0 {
public:
    HK_DECLARE_CLASS_ALLOCATOR(0x2c)
    char pad08[0x80 - 0x8];
    hkCollisionDispatcher_s004b_8af0* m_collisionDispatcher;   // +0x80
    char pad84[0xb5 - 0x84];
    hkBool_s004b_8af0 m_wantDeactivation;                  // +0xb5
    char padB6[0x2f0 - 0xb6];
    hkWorld_s004b_8af0(const hkWorldCinfo_s004b_8af0& info, unsigned int sdkVersion);      // 0x010840E0
    hkCollisionDispatcher_s004b_8af0* getCollisionDispatcher() { return m_collisionDispatcher; }
    void setCollisionFilter(hkCollisionFilter_s004b_8af0* filter, hkBool_s004b_8af0 runUpdate, int updateMode, int collectionMode);  // 0x01086F80
    void updateCollisionFilterOnWorld(int updateMode, int collectionMode);  // 0x010869E0
    void addEntity(hkRigidBody_s004b_8af0* entity, int activation);             // 0x01082EE0
    void stepDeltaTime(hkReal dt);                                   // 0x01082A90
};
namespace EA {
template <class T> class RefCountTemplate_s004b_8af0 {
public:
    virtual ~RefCountTemplate_s004b_8af0() {}
    T mRefCount;                                // +0x4
    RefCountTemplate_s004b_8af0() : mRefCount(0) {}
    T AddRef() { return mRefCount++ + 1; }
    // Contains `delete this`, so cl declines to inline it, yet callers still reserve its frame.
    T Release()                                                      // 0x00453540
    {
        T r = mRefCount-- - 1;
        if (r)
            return r;
        mRefCount = 1;
        delete this;
        return 0;
    }
};
}
namespace EA {
template <class T> class AutoRefCount_s004b_8af0 {
public:
    T* mpObject;
    AutoRefCount_s004b_8af0(T* pObject = 0) : mpObject(pObject) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount_s004b_8af0(const AutoRefCount_s004b_8af0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s004b_8af0() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount_s004b_8af0& operator=(T* pObject)                              // 0x0041D980
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s004b_8af0& operator=(const AutoRefCount_s004b_8af0& x) { return operator=(x.mpObject); }
};
}
namespace SP {
class cISPEditorNameProvider_s004b_8af0 { public: virtual void _v0(); };
}
namespace SP {
class cSPEditorModel_s004b_8af0 : public cISPEditorNameProvider_s004b_8af0, public EA::RefCountTemplate_s004b_8af0<int> {
public:
    void NumberBlocks();                                             // 0x004AD4E0
};
}
namespace SP {
typedef EA::AutoRefCount_s004b_8af0<cSPEditorModel_s004b_8af0> ModelRef;
}
namespace SP {
class cSPEditorPhysicsWorld_s004b_8af0 : public EA::RefCountTemplate_s004b_8af0<int> {
public:
    hkWorld_s004b_8af0* mPhysicsWorld;                     // +0x8
    hkRigidBody_s004b_8af0* mFloor;                        // +0xc
    float mGravity;                             // +0x10
    float mLapseTime;                           // +0x14
    eastl::vector<ModelRef> mModels;            // +0x18
    bool mUseDynamics;                          // +0x2c

    cSPEditorPhysicsWorld_s004b_8af0();
    virtual ~cSPEditorPhysicsWorld_s004b_8af0();
    void Clear();
    void Init();  // 0x007c4dd0 (SP::cSPEditorPhysicsWorld::Init)
    hkWorld_s004b_8af0* World();                                                // 0x004B91C0
    void CreateFloor(float size);
    void UpdateCollisionFilters();
    void SetFloorFilter(unsigned int filter);
    void SetDefaultFloorFilter();
    void AddModel(cSPEditorModel_s004b_8af0* model);
    void RemoveModel(cSPEditorModel_s004b_8af0* model);
    void UpdatePhysics(unsigned int deltaMs);
};
}
// ---- items of slice s004b8af0 end

// @ 0x004b8c10
namespace SP {
void cSPEditorPhysicsWorld_s004b_8af0::Init()
{
    Clear();
    hkWorldCinfo_s004b_8af0 info;
    info.setupSolverInfo(5);
    info.m_gravity = hkVector4_s004b_8af0(0.0f, 0.0f, -mGravity);
    info.setBroadPhaseWorldSize(300.0f);
    mPhysicsWorld = new hkWorld_s004b_8af0(info, 0x765c);
    mPhysicsWorld->m_wantDeactivation = false;
    hkAgentRegisterUtil::registerAllAgents(mPhysicsWorld->getCollisionDispatcher());
    hkCollisionFilter_s004b_8af0* filter = new SPEditorCollisionFilter();
    mPhysicsWorld->setCollisionFilter(filter, true, 0, 1);
    filter->removeReference();
    mLapseTime = 0.0f;
    CreateFloor(15.0f);
}
}  // namespace SP

// @ 0x007c3d30
void SP::cViewer::GetCameraLocationInfo(cSPVector3 * w, cSPVector3 * y, cSPVector3 * z, cSPVector3 * x) const
{
    if (w != 0) {
        int* d = (int*)w; const int* s = (const int*)&mCameraToWorldTransform.wAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
    if (y != 0) {
        int* d = (int*)y; const int* s = (const int*)&mCameraToWorldTransform.yAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
    if (z != 0) {
        int* d = (int*)z; const int* s = (const int*)&mCameraToWorldTransform.zAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
    if (x != 0) {
        int* d = (int*)x; const int* s = (const int*)&mCameraToWorldTransform.xAxis;
        d[0] = s[0]; d[1] = s[1]; d[2] = s[2];
    }
}

// @ 0x007c3da0
void Matrix44::FUN_007c3da0(float* dst)
{
    // Three 12-byte row copies out of the 16-byte rows (xAxis/yAxis/zAxis -> dst[0..8]).
    // Retail keeps the first two rows relative to the original bases and then advances both
    // (`add $0x20,%ecx; add $0x18,%eax` at 0x7c3dc9), which also leaves eax = dst+0x18; cl folds
    // the advances into displacements here because the bumped pointers are dead afterwards.
    const int* s = (const int*)this;
    int* d = (int*)dst;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[4];
    d[4] = s[5];
    d[5] = s[6];
    d[6] = s[8];
    d[7] = s[9];
    d[8] = s[10];
}

// @ 0x007c3de0
void FUN_007c3de0(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007c3f70
cViewer* cViewer::FUN_007c3f70()
{
    mClearColor[0] = g_1635db8;
    mClearColor[1] = g_1635dbc;
    mClearColor[2] = g_1635dc0;
    mClearColor[3] = g_1635dc4;
    float lod = g_10000f;
    mRenderType = 0;
    mRenderTypeVariation = 0;
    mShaderDataRT = 0;
    mMaterialLODs[0] = lod;
    mMaterialLODs[1] = lod;
    mMaterialLODs[2] = lod;
    mMaterialLODs[3] = lod;
    mTileRender = 1;
    mCamera = 0;
    return this;
}

// @ 0x007c4000
void cViewer::FUN_007c4000()
{
    if (mCamera != 0)
        FUN_007c3ba0();
}

// @ 0x007c4010
void cViewer::FUN_007c4010(unsigned* out)
{
    Camera* c = mCamera;
    unsigned short x = (unsigned short)c->vpX;
    unsigned short y = (unsigned short)c->vpY;
    unsigned short w = (unsigned short)c->vpW;
    unsigned short h = (unsigned short)c->vpH;
    out[2] = (unsigned)w + (unsigned)x;
    out[1] = (unsigned)y;
    out[0] = (unsigned)x;
    out[3] = (unsigned)h + (unsigned)y;
}

// @ 0x007c4050
float cViewer::FUN_007c4050()
{
    float a = mCamera->f60;
    if (mCamera->f5c != a)
        a = a * 1.3333334f;
    return (360.0f / g_153c7a8) * atan2f(a, 1.0f);
}

// @ 0x007c40a0
float cViewer::FUN_007c40a0()
{
    return (360.0f / g_153c7a8) * atan2f(mCamera->f60, 1.0f);
}

// @ 0x007c40c0
void cViewer::FUN_007c40c0(float* a, float* b)
{
    *a = mCamera->f5c;
    *b = mCamera->f60;
}

// @ 0x007c40e0
float cViewer::FUN_007c40e0()
{
    return mCamera->f5c / mCamera->f60;
}

// @ 0x007c40f0
void FUN_007c40f0(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007c4180
void FUN_007c4180(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }

// @ 0x007c42a0
void FUN_007c42a0(void* a, void* b)
{ (void)a; (void)b; }

// @ 0x007c43e0
void FUN_007c43e0(void* a)
{ (void)a; }

// @ 0x007c4510
void FUN_007c4510(void* a)
{ (void)a; }

// @ 0x007c46f0
void FUN_007c46f0(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }

// @ 0x007c4730
void FUN_007c4730(void* a)
{ (void)a; }

// @ 0x007c4900
void FUN_007c4900(void* a, void* b, void* c)
{ (void)a; (void)b; (void)c; }

// @ 0x007c4940
__declspec(noinline) void cViewer::FUN_007c4940()
{ g_FUN_007c4940_body(); }

// @ 0x007c4a60
void cViewer::FUN_007c4a60(unsigned short* p)
{
    unsigned short y  = p[2];
    unsigned short h  = p[6];
    unsigned short x  = p[0];
    unsigned short wv = p[4];
    Camera* c = mCamera;
    c->vpY = (unsigned)y;
    c->vpW = (unsigned)(unsigned short)(wv - x);
    c->f88 = 0;
    c->vpX = (unsigned)x;
    c->vpH = (unsigned)(unsigned short)(h - y);
    c->f8c = 0x3f800000;
    FUN_007c4940();
}

// @ 0x007c4ad0
void cViewer::FUN_007c4ad0(float a, float b)
{
    Camera* c = mCamera;
    c->f54 = a;
    c->f58 = b;
    FUN_007c4940();
}

// @ 0x007c4b00
void cViewer::FUN_007c4b00(float a, float b)
{
    Camera* c = mCamera;
    c->f5c = a;
    c->f60 = b;
    c->f64 = 1.0f / a;
    c->f68 = 1.0f / b;
    FUN_007c4940();
}

// @ 0x007c4b50
void cViewer::FUN_007c4b50(float a)
{
    Camera* c = mCamera;
    float h = c->f60;
    float w = h * a;
    float invW = 1.0f / w;
    float invH = 1.0f / h;
    c->f5c = w;
    c->f60 = h;
    c->f64 = invW;
    c->f68 = invH;
    FUN_007c4940();
}

// @ 0x007c4ba0
void cViewer::FUN_007c4ba0(float a)
{ Camera* c = mCamera; c->f70 = a; FUN_007c4940(); }

// @ 0x007c4bc0
void cViewer::FUN_007c4bc0(float a)
{ Camera* c = mCamera; c->f74 = a; FUN_007c4940(); }

// @ 0x007c4be0
__declspec(noinline) void cViewer_s007c_4be0::SetRaster(int* handle, bool setViewport)
{
    Renderer* r = GetRenderer();
    int v = r->v18(handle[0], handle[1]);
    mCamera->m_raster[0] = (void*)v;
    if (setViewport) {
        int rect[4];
        Renderer* r2 = GetRenderer();
        r2->v20(handle[0], handle[1], rect);
        SetViewportRect((u16*)rect);
    }
}

// @ 0x007c4c40
__declspec(noinline) void cViewer_s007c_4be0::SetCameraToWorld(float* m)
{
    for (int i = 0; i < 16; i++) mCameraToWorld[i] = m[i];
    rwCamera* cam = mCamera;
    float* d = cam->m_transform;
    // SIMD 3x3 transpose with sign flip on row 0 (see disassembly).
    d[0] = -m[0]; d[1] = -m[1]; d[2] = -m[2]; d[3] = -m[0];
    d[4] =  m[8]; d[5] =  m[9]; d[6] =  m[10]; d[7] =  m[8];
    d[8] =  m[4]; d[9] =  m[5]; d[10] = m[6]; d[11] = m[4];
    d[12] = m[12]; d[13] = m[13]; d[14] = m[14]; d[15] = m[12];
    UpdateTransforms();
}

// @ 0x007c4d00
__declspec(noinline) void cViewer_s007c_4be0::SetBasis(void* basis)
{
    ((Basis3*)basis)->Build(this);
    SetCameraToWorld(mCameraToWorld);
}

// @ 0x007c4d20
__declspec(noinline) void cViewer_s007c_4be0::SetCameraToWorldFromBasis(float* p)
{
    float m[16];
    m[0] = -p[0]; m[1] = -p[1]; m[2] = -p[2]; m[3] = 0.0f;
    m[4] =  p[8]; m[5] =  p[9]; m[6] =  p[10]; m[7] = 0.0f;
    m[8] =  p[4]; m[9] =  p[5]; m[10] = p[6]; m[11] = 0.0f;
    m[12] = p[12]; m[13] = p[13]; m[14] = p[14]; m[15] = 1.0f;
    SetCameraToWorld(m);
}

// @ 0x007c4dd0
__declspec(noinline) bool cViewer_s007c_4be0::Init(bool windowed)
{
    if (mCamera != 0) return false;
    mCamera = (rwCamera*)FUN_00761380();
    if (mCamera == 0) return false;
    if (mShaderDataRT == 0) {
        mShaderDataRT = EANew(8, "Graphics", 0, 0, 0, 0);
        ((int*)mShaderDataRT)[1] = -1;
        *(u8*)mShaderDataRT = 0xff;
    }

    rwCamera* cam = mCamera;
    cam->m_nearPlane = 1.0f;
    cam->m_farPlane = 1000.0f;

    rwCamera* def = (rwCamera*)g_defaultCameraRaster;
    u16 w = *(u16*)((char*)def + 0x0c);
    u16 h = *(u16*)((char*)def + 0x0e);
    cam->m_viewport.X = 0;
    cam->m_viewport.Y = 0;
    cam->m_viewport.Width = w;
    cam->m_viewport.Height = h;
    cam->m_viewport.MinZ = 0.0f;
    cam->m_viewport.MaxZ = 1.0f;

    float* d = cam->m_transform;
    d[0]=1.0f; d[1]=0; d[2]=0; d[3]=0;
    d[4]=0; d[5]=1.0f; d[6]=0; d[7]=0;
    d[8]=0; d[9]=0; d[10]=1.0f; d[11]=0;
    d[12]=0; d[13]=0; d[14]=0; d[15]=0;

    for (int i = 0; i < 16; i++) mCameraToWorld[i] = g_identityMatrix[i];

    cam->m_raster[0] = g_defaultCameraRaster;
    cam->m_zbuffer   = g_defaultZBufferRaster;

    if (!windowed) {
        cam->m_projectionType = 1;
        float t = tanf(g_tanScaleA * g_tanScaleB * g_defaultFov);
        cam->m_viewWindow[1] = t;
        float a = ((float)w / (float)h) * t;
        cam->m_viewWindow[0] = a;
        cam->m_recipViewWindow[0] = 1.0f / a;
        cam->m_recipViewWindow[1] = 1.0f / t;
    } else {
        cam->m_projectionType = 2;
        cam->m_viewWindow[0] = 1.0f;
        cam->m_viewWindow[1] = 1.0f;
        cam->m_recipViewWindow[1] = 1.0f;
        cam->m_recipViewWindow[0] = 1.0f;
    }
    UpdateTransforms();
    return true;
}

// @ 0x007c4fd0
__declspec(noinline) bool cViewer_s007c_4be0::Update()
{
    rwCamera* cam = mCamera;
    if (cam->m_raster[0] == 0) return false;

    float aspect = (float)cam->m_viewport.Width / (float)cam->m_viewport.Height;
    float cur = cam->m_viewWindow[0] / cam->m_viewWindow[1];
    float diff = cur - aspect;
    if (diff < 0) diff = -diff;
    if (diff > g_aspectEps && g_forceAspect != 0 && mTileRender)
        SetAspect(aspect);

    if (!mCamera->Check()) return false;
    BuildTransforms();

    cShaderDataRenderType* sd = (cShaderDataRenderType*)mShaderDataRT;
    int changed;
    if (sd->mVariation == mRenderType) {
        changed = (u8)sd->mType == (u8)mRenderTypeVariation ? 0 : 1;
    } else {
        changed = 1;
    }
    sd->mVariation = mRenderType;
    sd->mType = (u8)mRenderTypeVariation;
    DrawShader(0x201, sd, changed);
    return true;
}

// @ 0x007c50b0
__declspec(noinline) bool cViewer_s007c_4be0::Copy(cViewer_s007c_4be0* src, bool copyZBuffer, bool keepRaster)
{
    if (this == src) return true;
    if (src == 0 || src->mCamera == 0 || mCamera == 0) return false;

    rwCamera* sc = src->mCamera;
    mTileRender = src->mTileRender;
    mRenderTypeVariation = src->mRenderTypeVariation;
    mRenderType = src->mRenderType;
    mCamera->m_projectionType = sc->m_projectionType;
    mCamera->m_nearPlane = sc->m_nearPlane;
    mCamera->m_farPlane  = sc->m_farPlane;
    mCamera->m_viewOffset[0] = sc->m_viewOffset[0];
    mCamera->m_viewOffset[1] = sc->m_viewOffset[1];

    char local[0x40];
    sc->AssignTo(local);
    mCamera->SetTexture(local);

    for (int i = 0; i < 16; i++) mCameraToWorld[i] = src->mCameraToWorld[i];
    mCamera->m_raster[0] = sc->m_raster[0];
    if (!copyZBuffer)
        mCamera->m_zbuffer = sc->m_zbuffer;
    if (!keepRaster && sc->m_raster[1] != 0)
        ((VBi*)mCamera)->FUN_011f38f0(1, (u32)sc->m_raster[1]);

    int r[4];
    src->FUN_007c4010((u32*)r);
    mCamera->SetSize(r[0], r[1], r[2] - r[0], r[3] - r[1]);

    float vx = sc->m_viewWindow[0];
    float vy = sc->m_viewWindow[1];
    rwCamera* dc = mCamera;
    dc->m_viewWindow[0] = vx;
    dc->m_viewWindow[1] = vy;
    dc->m_recipViewWindow[0] = 1.0f / vx;
    dc->m_recipViewWindow[1] = 1.0f / vy;
    UpdateTransforms();
    return true;
}

// @ 0x007c5240
__declspec(noinline) void cViewer_s007c_4be0::CopyFrom(cViewer_s007c_4be0* src)
{
    if (this == src) return;
    mTileRender = src->mTileRender;
    {
        float* s = src->mCamera->m_transform;
        float* d = mCamera->m_transform;
        for (int i = 0; i < 16; i++) d[i] = s[i];
    }
    for (int i = 0; i < 16; i++) mCameraToWorld[i] = src->mCameraToWorld[i];
    mCamera->m_nearPlane = src->mCamera->m_nearPlane;
    mCamera->m_farPlane  = src->mCamera->m_farPlane;
    float vx = src->mCamera->m_viewWindow[0];
    float vy = src->mCamera->m_viewWindow[1];
    rwCamera* d = mCamera;
    d->m_viewWindow[0] = vx;
    d->m_viewWindow[1] = vy;
    d->m_recipViewWindow[0] = 1.0f / vx;
    d->m_recipViewWindow[1] = 1.0f / vy;
    UpdateTransforms();
}
