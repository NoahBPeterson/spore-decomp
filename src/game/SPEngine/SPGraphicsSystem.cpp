// src/game/SPEngine/SPGraphicsSystem.cpp -- migrated from slice(s) s007a51d0, s007a41c0, s007a7210, s007a7d50, s007a62c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsSystem.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGraphicsSystem.h"
#include "SP/cGameModelResource.h"
#include "EA/AutoRefCount.h"
#include "cSPVector3.h"
#include "SP/cDebugDraw.h"
#include "SP/cIRTTManager.h"
#include "SP/cIRenderer.h"
#include "SP/cPropertyList.h"
#include "SP/cStaticBuffer.h"
#include "SP/cStaticBufferDraw.h"
#include "SP/cViewer.h"
#include <math.h>
#include <stdlib.h>
#include <intrin.h>
#include "SP/cDirectPropertyList.h"
#include "SP/cIGraphicsSystem.h"
#include "SP/cRenderTargetRectID.h"
#include "SP/cTextureInstance.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);
extern "C" void  FUN_00a23920(void*);          // mBuiltinModels vector dtor
extern "C" void  FUN_00576620(void*);          // one AutoRefCount element dtor
extern "C" void  VectorErase(void*, void*, void*); // eastl::vector<...>::erase
extern "C" void  FUN_006efc10();
extern "C" void  FUN_006f2620();
extern "C" void  FUN_00782b00();
extern "C" void  FUN_007a8360();
extern "C" void  FUN_006e1010();
extern "C" void  FUN_007a4320();
extern "C" void  FUN_006ddc90();
extern "C" void  FUN_007c3910();
extern "C" void  FUN_0067df60(int);
extern "C" void  FUN_0067df70(int);
extern "C" void  FUN_0067df80(int);
extern "C" void  FUN_0067df90(int);
extern "C" void  FUN_0067dfa0(int);
extern "C" void  FUN_0067dfb0(int);
extern "C" void  FUN_0067dfc0(int);
extern "C" void  FUN_0067dfd0(int);
extern "C" void  FUN_0067e010(int);
extern "C" void  FUN_0067e020(int);
extern "C" void* FUN_0067dd40();
extern "C" void* FUN_0067dd50();
extern "C" void  FUN_00ac97a0(void*, void*, void*);
extern "C" void* GetManager();
extern "C" int   TryGetUIntProperty(void* props, int key, int* out);
extern "C" void* sAppProperties;
extern int       sBufferTexturePropertyKeys[4];
extern char VT_cGraphicsSystem_IGraphicsSystem[];
extern char VT_cGraphicsSystem_RefCount[];
extern char VT_RefCountBase[];
extern "C" void* VectorDoInsertValue(void* dest, void* position, unsigned int bytes);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s007a62c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);
extern "C" void  FUN_00a23920(void*);          // mBuiltinModels vector dtor
extern "C" void  FUN_00576620(void*);          // one AutoRefCount element dtor
extern "C" void  VectorErase(void*, void*, void*); // eastl::vector<...>::erase
extern "C" void  FUN_006efc10();
extern "C" void  FUN_006f2620();
extern "C" void  FUN_00782b00();
extern "C" void  FUN_007a8360();
extern "C" void  FUN_006e1010();
extern "C" void  FUN_007a4320();
extern "C" void  FUN_006ddc90();
extern "C" void  FUN_007c3910();
extern "C" void  FUN_0067df60(int);
extern "C" void  FUN_0067df70(int);
extern "C" void  FUN_0067df80(int);
extern "C" void  FUN_0067df90(int);
extern "C" void  FUN_0067dfa0(int);
extern "C" void  FUN_0067dfb0(int);
extern "C" void  FUN_0067dfc0(int);
extern "C" void  FUN_0067dfd0(int);
extern "C" void  FUN_0067e010(int);
extern "C" void  FUN_0067e020(int);
extern "C" void* FUN_0067dd40();
extern "C" void* FUN_0067dd50();
extern "C" void  FUN_00ac97a0(void*, void*, void*);
extern "C" void* GetManager();
extern "C" int   TryGetUIntProperty(void* props, int key, int* out);
extern "C" void* sAppProperties;
extern int       sBufferTexturePropertyKeys[4];
extern char VT_cGraphicsSystem_IGraphicsSystem[];
extern char VT_cGraphicsSystem_RefCount[];
extern char VT_RefCountBase[];
struct RectID { int mPageID; int mAllocID; };   // cGraphicsSystem render-target rect
struct BufferRect { int mAllocID; int mPageID; }; // GetBufferRectID out-param
inline void ReleaseRefCount(void* p, int rcOffset = 8)
{
    if (p) {
        volatile long* rc = (volatile long*)((char*)p + rcOffset);
        _InterlockedExchangeAdd(rc, -1);
        long cur = _InterlockedExchangeAdd(rc, 0);
        if (cur < 1)
            _InterlockedExchangeAdd(rc, 1);
        else
            _InterlockedExchangeAdd(rc, 0);
    }
}
struct cGraphicsSystem {
    void* vtbl0;                    // +0x000
    void* vtbl1;                    // +0x004
    int   pad008;                   // +0x008
    bool  mInitialized;             // +0x00c
    char  pad00d[3];                // +0x00d
    void* mRenderer;                // +0x010
    void* mTextureManager;          // +0x014
    void* mRTTManager;              // +0x018
    void* mThumbnailManager;        // +0x01c
    void* mMaterialManager;         // +0x020
    void* mLightingManager;         // +0x024
    void* mModelManager;            // +0x028
    void* mDebugDraw;               // +0x02c
    void* mFilterChainRenderer;     // +0x030
    void* mEffectsResources;        // +0x034
    void* mEffectsRenderer;         // +0x038
    void* mShadowWorld;             // +0x03c
    void* mBuiltinBegin;            // +0x040
    void* mBuiltinEnd;              // +0x044
    void* mBuiltinCap;              // +0x048
    int   pad04c;                   // +0x04c
    void* mSplatterTexture;         // +0x050
    void* mGIFExportTexture;        // +0x054
    void* mBakeInfoTexture;         // +0x058
    void* mNMapSpecTexture;         // +0x05c
    void* mAOTexture;               // +0x060
    void* mFinalBakedTexture;       // +0x064
    void* mSmallFinalBakedTexture;  // +0x068
    void* mShadowBlurTexture;       // +0x06c
    void* mShadowTexture;           // +0x070
    void* mDepthTexture;            // +0x074
    void* mCapturedCubemapTexture;  // +0x078
    void* mCameraSnapshotTexture;   // +0x07c
    void* mCameraSnapshotZTexture;  // +0x080
    void* mCurrentCubemapFaceRaster;// +0x084
    void* mBakeBuffers[2];          // +0x088
    void* mLargeThumbnailTexture;   // +0x090
    void* mThumbnailBoundsTexture;  // +0x094
    void* mBufferTextures[4];       // +0x098
    RectID mBufferTextureRectIDs[4];// +0x0a8
    RectID mAOTextureRectID;        // +0x0c8
    RectID mSplatterTextureRectID;  // +0x0d0
    RectID mGIFExportRectID;        // +0x0d8
    RectID mBakeInfoTextureRectID;  // +0x0e0
    RectID mNMapSpecTextureRectID;  // +0x0e8
    RectID mFinalBakedTextureRectID;// +0x0f0
    RectID mSmallFinalBakedTextureRectID; // +0x0f8
    RectID mShadowBlurTextureRectID;// +0x100
    RectID mShadowTextureRectID;    // +0x108
    RectID mDOFTextureRectID;       // +0x110
    RectID mNDotLTextureRectID;     // +0x118
    RectID mDepthTextureRectID;     // +0x120
    RectID mCameraSnapshotRectID;   // +0x128
    RectID mCurrentCubemapFaceRectID; // +0x130
    RectID mBakeBufferRectIDs[2];   // +0x138
    RectID mLargeThumbnailRectID;   // +0x148
    RectID mThumbnailBoundsRectID;  // +0x150
    bool  mCurrentlyCapturingCubemap;  // +0x158
    bool  mCurrentlyCapturingSnapshot; // +0x159
    bool  mCurrentlyCapturingImpostor; // +0x15a
    int   mCameraSnapshotFormat;    // +0x15c
    unsigned short mBakeTextureSize;// +0x160

    void InitBufferTexture(int index);
    void* GetBufferTexture(int index, char param_3);
    void GetBufferRectID(int index, BufferRect* out, char param_4);
    bool  Shutdown();
    ~cGraphicsSystem();
};
struct ModelVector {
    void* mpBegin;                  // +0
    void* mpEnd;                    // +4
    void* mpCapacity;               // +8
    void InsertAt(void* position, void* value);
};
extern "C" void* VectorDoInsertValue(void* dest, void* position, unsigned int bytes);
static void ReleaseTexture(cGraphicsSystem* self, void*& field, RectID& rect, int rcOffset)
{
    if (field) {
        void* mgr = self->mRTTManager;
        ((void(__thiscall*)(void*, int, int))((*(void***)mgr)[0x14 / 4]))(mgr, rect.mPageID, rect.mAllocID);
        if (field) {
            void* p = field;
            field = 0;
            ReleaseRefCount(p, rcOffset);
        }
    }
}
// ---- items of slice s007a62c0 end

// ---- items of slice s007a7d50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_0067de10();
extern "C" void  FUN_0067dfe0(void*);
struct Layout; struct TextStyle; struct TextRenderWare;
struct TextRenderWare {
    char pad000[0xa384];
    void* ScalarDelete(unsigned char flags); // 007a88b0
};
struct TextStyleStub {
    wchar_t mFontName[32];     // +0x00 (terminator at +0x3e = index 31)
    char pad040[0x200 - 0x40];
    float mFontSize;           // +0x200
    char pad204[0x214 - 0x204];
    int   mField214;           // +0x214
    char pad218[0x224 - 0x218];
    unsigned int mColor;       // +0x224
};
struct cTextRenderer {
    void* mBuffer0;            // +0x000
    void* mBuffer1;            // +0x004
    int   mField08;            // +0x008
    bool  mInitialized;        // +0x00c
    char  pad00d[3];
    TextRenderWare* mRenderImpl; // +0x010
    Layout* mLayout;           // +0x014
    TextStyleStub* mTextStyle; // +0x018
    bool  mStyleChanged;       // +0x01c
    char  pad01d[0x168 - 0x01d];
    char  mCriticalSection[24];// +0x168

    void Init();               // 007a84d0
    void CtorBody();           // 007a8390
    void Release();            // 007a8530
    void EnsureBuffers();      // 007a8310
    void SetStyle(int style);  // 007a82a0
    void SetStyleScale(float f);          // 007a82d0
    void SetFontName(const wchar_t* name); // 007a8550
    void SetFontSize(float size);          // 007a85a0
    void SetColor(const float* rgb);       // 007a85e0
    bool AllocDevice(void* obj);           // 007a8660
    bool FreeDevice(void* obj);            // 007a8700
    ~cTextRenderer();                      // 007a8790
    void* InsertGlyph(void* position, void* value); // 007a8910
};
extern "C" void FUN_007a7d50(cTextRenderer*);
// ---- items of slice s007a7d50 end

// ---- items of slice s007a7210 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int n, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);
void  operator delete(void* p, const char* name, int flags, unsigned debugFlags,
                      const char* file, int line);
namespace EA {
template <typename T>
class AutoRefCount_s007a_7210 {
public:
    T* mpObject;
    AutoRefCount_s007a_7210(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s007a_7210() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
};
}
struct cSPVector3_s007a_7210 {
    float x, y, z;
    cSPVector3_s007a_7210() {}
    cSPVector3_s007a_7210(float a, float b, float c) : x(a), y(b), z(c) {}
    cSPVector3_s007a_7210 operator-() const { return cSPVector3_s007a_7210(-x, -y, -z); }
};
namespace SP {
class cMeshData_s007a_7210;
}
namespace SP {
class cIMeshBuilder {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void v02() = 0; virtual void v03() = 0; virtual void v04() = 0; virtual void v05() = 0;
    virtual void v06() = 0; virtual void v07() = 0; virtual void v08() = 0; virtual void v09() = 0;
    virtual void v10() = 0; virtual void v11() = 0; virtual void v12() = 0; virtual void v13() = 0;
    virtual void v14() = 0; virtual void v15() = 0; virtual void v16() = 0; virtual void v17() = 0;
    virtual void v18() = 0; virtual void v19() = 0; virtual void v20() = 0; virtual void v21() = 0;
    virtual void v22() = 0; virtual void v23() = 0; virtual void v24() = 0; virtual void v25() = 0;
    virtual void v26() = 0; virtual void v27() = 0; virtual void v28() = 0; virtual void v29() = 0;
    virtual void v30() = 0; virtual void v31() = 0; virtual void v32() = 0; virtual void v33() = 0;
    virtual void v34() = 0; virtual void v35() = 0; virtual void v36() = 0; virtual void v37() = 0;
    virtual void v38() = 0; virtual void v39() = 0; virtual void v40() = 0; virtual void v41() = 0;
    virtual void v42() = 0;
    virtual cMeshData_s007a_7210* GetMeshData() = 0;   // +0xac
};
}
namespace SP {
class cGameModelResource_s007a_7210 {
public:
    virtual int AddRef();
    virtual int Release();
    cGameModelResource_s007a_7210();                    // 0x007004d0
    uint32_t mData[0x13c / 4];
};
}
namespace SP {
cIMeshBuilder* CreateMeshBuilder();                                                  // 0x00715de0
}
namespace SP {
void CreateBoxMesh(cIMeshBuilder* mb, const cSPVector3_s007a_7210& vmin, const cSPVector3_s007a_7210& vmax);  // 0x0071cde0
}
namespace SP {
void CreateMesh_c900(cIMeshBuilder* mb);                                             // 0x0071c900
}
namespace SP {
void CreateDiscMesh(cIMeshBuilder* mb, float radius, int segments);                 // 0x0071c9e0
}
namespace SP {
void CreateQuadMesh(cIMeshBuilder* mb, const cSPVector3_s007a_7210& vmin, const cSPVector3_s007a_7210& vmax); // 0x0071cc20
}
namespace SP {
void CreateMesh_d550(cIMeshBuilder* mb, float a, float b, int c, int d, int e, int f); // 0x0071d550
}
namespace SP {
void CreateMesh_d960(cIMeshBuilder* mb, float a, float b, int c, int d);           // 0x0071d960
}
namespace SP {
void CreateArrowheadMesh(cIMeshBuilder* mb, float size);                            // 0x0071d0d0
}
namespace SP {
void CreateMesh_d2f0(cIMeshBuilder* mb, float size);                                // 0x0071d2f0
}
namespace SP {
void CompileMeshData(cMeshData_s007a_7210* data, cGameModelResource_s007a_7210* model, int a, int b);     // 0x0072c0a0
}
namespace SP {
bool RegisterModel(cGameModelResource_s007a_7210* model, uint32_t instanceID, uint32_t groupID); // 0x00754310
}
namespace SP {
extern const cSPVector3_s007a_7210 kOneVector;   // 0x0153b70c  (1,1,1)
}
namespace SP {
struct BuiltinModelVector {
    EA::AutoRefCount_s007a_7210<cGameModelResource_s007a_7210>* mpBegin;
    EA::AutoRefCount_s007a_7210<cGameModelResource_s007a_7210>* mpEnd;
    EA::AutoRefCount_s007a_7210<cGameModelResource_s007a_7210>* mpCapacity;
    uint32_t mAllocator;

    void reserve(unsigned int n);                                         // 0x007658f0
    void push_back(const EA::AutoRefCount_s007a_7210<cGameModelResource_s007a_7210>& value);    // 0x007a6ac0
    EA::AutoRefCount_s007a_7210<cGameModelResource_s007a_7210>& back() { return *(mpEnd - 1); }
};
}
namespace SP {
class cGraphicsSystem_s007a_7210 {
public:
    uint32_t pad00[0x40 / 4];
    BuiltinModelVector mBuiltinModels;   // +0x40

    void CreateBuiltinModels();  // 0x007a7210 (SP::cGraphicsSystem::CreateBuiltinModels)
    void AddBuiltinModel(cIMeshBuilder* mb, uint32_t instanceID);
};
}
namespace SP {
static const uint32_t kBuiltinModelGroup = 0xd94352ed;
}
namespace SP {
__forceinline void cGraphicsSystem_s007a_7210::AddBuiltinModel(cIMeshBuilder* mb, uint32_t instanceID)
{
    {
        cGameModelResource_s007a_7210* model = new ("Graphics", 0, 0, 0, 0) cGameModelResource_s007a_7210();
        mBuiltinModels.push_back(model);
    }
    CompileMeshData(mb->GetMeshData(), mBuiltinModels.back(), -1, 0);
    RegisterModel(mBuiltinModels.back(), instanceID, kBuiltinModelGroup);
}
}
// ---- items of slice s007a7210 end

// ---- items of slice s007a41c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  EXT_6ad7c0(...);
extern "C" void** FUN_11f8af0(...);
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef float          f32;
struct TextureRectID {
  u32 mPageID;   // +0x0
  u32 mAllocID;  // +0x4
};
struct cPropertyList {
  bool GetDescription(u32 id);  // 0x6a25a0
};
extern cPropertyList* _sAppProperties;  // 0x15fd918
struct cIRenderer {
virtual void vr00();
virtual void vr01();
virtual void vr02();
virtual void vr03();
virtual void vr04();
virtual void vr05();
virtual void vr06();
virtual void vr07();
virtual void vr08();
virtual void vr09();
virtual void vr10();
virtual void vr11();
virtual void vr12();
virtual void vr13();
virtual void vr14();
virtual void vr15();
virtual void vr16();
virtual void vr17();
virtual void vr18();
virtual void vr19();
  virtual void vr20();
  virtual void RendererPreShutdown();  // +0x54
};
struct cIRTTManager {
virtual void vt00();
virtual void vt01();
virtual void vt02();
virtual void vt03();
  virtual void vt04();
  virtual void ReleaseRect(u32 pageID, u32 allocID);  // +0x14
};
struct cIBufferManager {
virtual void vb00();
virtual void vb01();
virtual void vb02();
virtual void vb03();
virtual void vb04();
virtual void vb05();
virtual void vb06();
virtual void vb07();
virtual void vb08();
virtual void vb09();
virtual void vb10();
virtual void vb11();
  virtual void vb12();
  virtual void CreateBuffer(void* pBuffer);  // +0x34
};
extern "C" cIBufferManager* APP_GetBufferManager();  // 0x67dd60
struct cLazyBuffer {
  void* mpValue;  // +0x0
  u32   mFlags;   // +0x4
};
struct cInnerObject {
  virtual void i00();  // +0x0
  virtual void i01();  // +0x4
};
struct cRefTarget {
  u32          mUnk00;   // +0x0
  u32          mUnk04;   // +0x4
  cInnerObject mInner;   // +0x8
};
struct cObjectRef {
  cRefTarget* mpObject;  // +0x0
  void Flush();
};
struct cGraphicsSystem_s007a_41c0 {
  // base_cIGraphicsSystem vtable (only slot 0x24 is called here)
virtual void vg00();
virtual void vg01();
virtual void vg02();
virtual void vg03();
virtual void vg04();
virtual void vg05();
virtual void vg06();
virtual void vg07();
  virtual void vg08();
  virtual void CreateBakeBuffer(int index);  // +0x24

  u32           mUnk04[3];                       // +0x04
  cIRenderer*   mRenderer;                        // +0x10
  void*         mTextureManager;                  // +0x14
  cIRTTManager* mRTTManager;                      // +0x18
  u32           mUnk1c;                           // +0x1c
  void*         mMaterialManager;                 // +0x20
  void*         mLightingManager;                 // +0x24
  void*         mModelManager;                    // +0x28
  u32           mUnk2c[10];                       // +0x2c
  void*         mGIFExportTexture;                // +0x54
  u32           mUnk58[2];                        // +0x58
  void*         mAOTexture;                       // +0x60
  void*         mFinalBakedTexture;               // +0x64
  u32           mUnk68;                           // +0x68
  void*         mShadowBlurTexture;               // +0x6c
  void*         mShadowTexture;                   // +0x70
  u32           mUnk74[4];                        // +0x74
  cLazyBuffer*  mLazyBufferObject;                // +0x84
  void*         mBakeBuffers[5];                  // +0x88
  void*         mEffectsBuffers[4];               // +0x9c
  TextureRectID mEffectsBufferRectIDs[4];         // +0xac
  u8            mByteFlags[4];                    // +0xcc
  TextureRectID mSplatterTextureRectID;           // +0xd0
  TextureRectID mGIFExportRectID;                 // +0xd8
  TextureRectID mRectE0;                          // +0xe0
  TextureRectID mRectE8;                          // +0xe8
  TextureRectID mFinalBakedTextureRectID;         // +0xf0
  TextureRectID mSmallFinalBakedTextureRectID;    // +0xf8
  TextureRectID mUnk100;                          // +0x100
  TextureRectID mUnk108;                          // +0x108
  u32           mUnk110[10];                      // +0x110
  TextureRectID mBakeBufferRectIDs[6];            // +0x138
  u32           mUnk168[2];                       // +0x168
  u16           mDebugParam;                      // +0x170
  u16           mUnk172;                          // +0x172
  f32           mDebugRadius;                     // +0x174
  f32           mDebugNear;                       // +0x178
  f32           mDebugFar;                        // +0x17c
  f32           mDebugRange;                      // +0x180
  f32           mDebugDistance;                   // +0x184
  u8            mShowDebug;                       // +0x188
  u8            mUnk189[7];                       // +0x189
  u8            mDebugFlushState;                 // +0x190
  u8            mUnk191[3];                       // +0x191

  void  SetDebugParam(u16 v);
  u32   ShouldShowDebug();
  void  SetDebugRange(f32 range, f32 distance, f32 near_, f32 far_);
  void  GetRectID(TextureRectID* out, u32 id);  // 0x007a4b10 (cGraphicsSystem::GetRectID)
  void  GetCurrentCubemapFaceRectID(u32* out);  // 0x007a4bb0 (cGraphicsSystem::GetCurrentCubemapFaceRectID)
  void  SetCurrentCubemapFaceRectID(const u32* in);
  u8    GetByteFlag(u32 i);
  void  SetByteFlag(u32 i, u8 v);
  bool  PreShutdown();  // 0x007a4d20 (cGraphicsSystem::PreShutdown)
  void  RecycleEffectsBuffers();  // 0x007a4d40 (cGraphicsSystem::RecycleEffectsBuffers)
  void* GetLazyBuffer();
  void  GetBakeBuffer(u32* out, int index);  // 0x007a4f10 (cGraphicsSystem::GetBakeBuffer)

  u32   SwapRendererDevice();                            // 0x007a4cb0
  void  UpdateManagers(u32 param_1, f32 param_2);        // 0x007a4d90
  void  RecycleBakingRTTs(u32 param_1, u32 param_2);     // 0x007a5020
  void  ReleaseRTT(void*& texture, const TextureRectID& rect);
};
struct cDebugDraw {
  u8   mUnk00[0x174];
  f32  mDebugRadius;    // +0x174
  f32  mDebugNear;      // +0x178
  f32  mDebugFar;       // +0x17c
  f32  mDebugRange;     // +0x180
  f32  mDebugDistance;  // +0x184
  u8   mUnk188[8];      // +0x188
  void Update(u32 param_1, f32 param_2);  // 0x007a4e40
};
struct cApp {
  u8  mUnk00[0x58];
virtual void a00();
virtual void a01();
virtual void a02();
virtual void a03();
virtual void a04();
virtual void a05();
virtual void a06();
virtual void a07();
virtual void a08();
virtual void a09();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
  virtual char* GetCameraViewer(u32* outPos, u32 a, u32 b, u32 c);};
extern "C" cApp* APP_GetApp();  // 0x67dd10
struct cViewer {
virtual void r00();
virtual void r01();
virtual void r02();
virtual void r03();
virtual void r04();
virtual void r05();
virtual void r06();
virtual void r07();
  void Refine(u32* pos, u32 a, u32 b, u32 c);
};
void cGraphicsSystem_s007a_41c0::ReleaseRTT(void*& texture, const TextureRectID& rect) {
  if (texture != 0) {
    mRTTManager->ReleaseRect(rect.mPageID, rect.mAllocID);
    void* const dead = texture;
    if (dead != 0) {
      texture = 0;
      volatile long* const rc = (volatile long*)((char*)dead + 8);
      _InterlockedExchange(rc, *rc - 1);
      if (*rc < 1) {
        _InterlockedExchange(rc, *rc + 1);
      }
    }
  }
}
extern "C" void  EXT_67df60(...);
extern "C" void* EXT_75fb90();
// ---- items of slice s007a41c0 end

// ---- items of slice s007a51d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
namespace SP {
struct cRenderTargetRectID_s007a_51d0 {
    int mPageID;      // +0x00
    int mAllocID;     // +0x04
};
}
namespace SP {
class cTextureInstance_s007a_51d0 {
public:
    void* mField0;                 // +0x00
    void* mField4;                 // +0x04
    volatile long mRefCount;       // +0x08
};
}
namespace SP {
class cTextureHandle {
public:
    void* mpObject;                                 // +0x00
    void* SetImageResource(void* resource);          // va 00576650
    void  Release();
};
}
namespace SP {
void cTextureHandle::Release()
{
    cTextureInstance_s007a_51d0* inst = (cTextureInstance_s007a_51d0*)mpObject;
    if (inst == 0)
        return;
    mpObject = 0;
    if (_InterlockedDecrement(&inst->mRefCount) < 1)
        _InterlockedIncrement(&inst->mRefCount);
}
}
namespace SP {
class cDirectPropertyList_s007a_51d0 {
public:
    bool GetDescription(uint32_t id) const;           // va 006a25a0 0x006a25a0
    int  GetIntProperty(uint32_t id) const;           // va 006a2660 0x006a2660
};
}
namespace SP {
class cRenderTargetManager {
public:
    PV(0) PV(1) PV(2) PV(3)
    virtual cRenderTargetRectID_s007a_51d0* CreateRenderTarget(cRenderTargetRectID_s007a_51d0* out, int width,
                                                    int height, int format, int flags,
                                                    int key, int extra);   // 0x10
    virtual void  ReleaseRenderTarget(int pageID, int allocID);            // 0x14
    PV(6)
    virtual void* GetRenderTargetImage(int pageID, int allocID);           // 0x1c
    PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17)
    virtual void  SetRenderTargetName(int pageID, int allocID, const char* name);  // 0x48
};
}
namespace SP {
class cRenderService {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
    virtual void UpdateRenderer(int delta);      // 0x34
    PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31)
    virtual void UpdateEffects(int delta);       // 0x80
};
}
namespace SP {
struct cViewportExtent {
    unsigned short mWidth;      // +0x00
    unsigned short mHeight;     // +0x02
    unsigned short mWidth2;     // +0x04
    unsigned short mHeight2;    // +0x06
};
}
namespace SP {
class cViewportInfo {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual cViewportExtent* GetExtent();        // 0x1c
};
}
namespace SP {
cViewportInfo* GetViewportInfo();                // va 0067dd50
}
namespace SP {
class cIGraphicsSystem_s007a_51d0 {
public:
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual void ReleaseSelf();                  // 0x30
    void UpdateDebugDraw();                      // va 007a4e40 (cDebugDraw::Update)
};
}
namespace SP {
class cContentValidationSummarizer {
public:
    virtual void v0();
};
}
namespace SP {
class cGraphicsSystem_s007a_51d0 : public cIGraphicsSystem_s007a_51d0, public cContentValidationSummarizer {
public:
    void*  mField08;                  // +0x08
    bool   mField0c;                  // +0x0c
    char   pad0d[3];                  // +0x0d
    cRenderService* mRenderer;        // +0x10
    void*  mField14;                  // +0x14
    cRenderTargetManager* mRTTManager;// +0x18
    void*  mField1c;                  // +0x1c
    void*  mField20;                  // +0x20
    void*  mField24;                  // +0x24
    void*  mField28;                  // +0x28
    void*  mField2c;                  // +0x2c
    void*  mField30;                  // +0x30
    void*  mField34;                  // +0x34
    cRenderService* mEffectsRenderer; // +0x38
    void*  mField3c;                  // +0x3c
    void*  mField40;                  // +0x40
    void*  mField44;                  // +0x44
    void*  mField48;                  // +0x48
    void*  mField4c;                  // +0x4c (retail ctor leaves this untouched)
    void*  mField50;                  // +0x50 (retail ctor leaves this untouched)

    cTextureHandle mSplatterTexture;          // +0x54
    cTextureHandle mAnimGifExportTexture;     // +0x58
    cTextureHandle mEditGifExportTexture;     // +0x5c
    cTextureHandle mBakeInfoTexture;          // +0x60
    cTextureHandle mNMapSpecTexture;          // +0x64
    cTextureHandle mAOTexture;                // +0x68
    cTextureHandle mFinalBakedTexture;        // +0x6c
    cTextureHandle mSmallFinalBakedTexture;   // +0x70
    cTextureHandle mShadowBlurTexture;        // +0x74
    cTextureHandle mShadowTexture;            // +0x78
    cTextureHandle mDepthTexture;             // +0x7c
    void*  mField80;                          // +0x80
    cTextureHandle mSnapshotTexture;          // +0x84
    void*  mField88;                          // +0x88
    cTextureHandle mBakeBuffers[2];           // +0x8c
    cTextureHandle mLargeThumbnailTexture;    // +0x94
    cTextureHandle mThumbnailBoundsTexture;   // +0x98
    void*  mBakeBufferRasters[4];             // +0x9c

    cRenderTargetRectID_s007a_51d0 mFieldAc;             // +0xac
    cRenderTargetRectID_s007a_51d0 mFieldB4;             // +0xb4
    cRenderTargetRectID_s007a_51d0 mFieldBc;             // +0xbc
    cRenderTargetRectID_s007a_51d0 mFieldC4;             // +0xc4
    int    mTextureFlags;                     // +0xcc (four one-byte dirty flags)
    cRenderTargetRectID_s007a_51d0 mAOTextureRectID;           // +0xd0
    cRenderTargetRectID_s007a_51d0 mSplatterTextureRectID;     // +0xd8
    cRenderTargetRectID_s007a_51d0 mAnimGifExportRectID;       // +0xe0
    cRenderTargetRectID_s007a_51d0 mEditGifExportRectID;       // +0xe8
    cRenderTargetRectID_s007a_51d0 mBakeInfoRectID;            // +0xf0
    cRenderTargetRectID_s007a_51d0 mNMapSpecRectID;            // +0xf8
    cRenderTargetRectID_s007a_51d0 mFinalBakedRectID;          // +0x100
    cRenderTargetRectID_s007a_51d0 mSmallFinalBakedRectID;     // +0x108
    cRenderTargetRectID_s007a_51d0 mShadowBlurRectID;          // +0x110
    cRenderTargetRectID_s007a_51d0 mShadowRectID;              // +0x118
    cRenderTargetRectID_s007a_51d0 mField120;                  // +0x120
    cRenderTargetRectID_s007a_51d0 mField128;                  // +0x128
    cRenderTargetRectID_s007a_51d0 mDepthRectID;               // +0x130
    cRenderTargetRectID_s007a_51d0 mSnapshotRectID;            // +0x138
    cRenderTargetRectID_s007a_51d0 mField140;                  // +0x140
    cRenderTargetRectID_s007a_51d0 mBakeBufferRectIDs[2];      // +0x148
    cRenderTargetRectID_s007a_51d0 mLargeThumbnailRectID;      // +0x158
    cRenderTargetRectID_s007a_51d0 mThumbnailBoundsRectID;     // +0x160

    bool   mField168;                 // +0x168
    bool   mField169;                 // +0x169
    bool   mField16a;                 // +0x16a
    char   pad16b;                    // +0x16b
    int    mField16c;                 // +0x16c
    unsigned short mField170;         // +0x170
    char   pad172[2];                 // +0x172
    float  mField174;                 // +0x174
    float  mField178;                 // +0x178
    float  mField17c;                 // +0x17c
    float  mField180;                 // +0x180
    float  mField184;                 // +0x184
    bool   mField188;                 // +0x188
    char   pad189[3];                 // +0x189
    int    mField18c;                 // +0x18c
    bool   mField190;                 // +0x190

    cGraphicsSystem_s007a_51d0();                                 // va 007a6010

    bool  InitSplatterTexture();                       // va 007a52f0 0x007a52f0
    bool  InitAnimGifExportTexture();                  // va 007a5370
    bool  InitEditGifExportTexture();                  // va 007a5410
    bool  InitAOTexture();                             // va 007a54b0 0x007a54b0
    bool  InitBakeInfoTexture();                       // va 007a5530 0x007a5530
    bool  InitNMapSpecTexture();                       // va 007a55b0 0x007a55b0
    bool  InitFinalBakedTexture();                     // va 007a5630 0x007a5630
    bool  InitSmallFinalBakedTexture();                // va 007a56b0 0x007a56b0
    bool  InitDepthTexture();                          // va 007a5730 0x007a5730
    bool  InitShadowTexture();                         // va 007a57d0 0x007a57d0
    bool  InitShadowBlurTexture();                     // va 007a5860 0x007a5860
    bool  InitSnapshotTexture();                       // va 007a5900 0x007a5900
    bool  InitLargeThumbnailTexture();                 // va 007a5990 0x007a5990
    bool  InitThumbnailBoundsTexture();                // va 007a5a20 0x007a5a20
    cTextureHandle* InitBakeBuffer(int index);         // va 007a5f70 0x007a5f70
    void  RecycleBakeBuffers();                        // va 007a5ef0 0x007a5ef0
    void  UpdateRendering(int delta);                  // va 007a5290 0x007a5290
    void  ReleaseGifExportTextures();                  // va 007a51d0
};
}
namespace SP {
extern cDirectPropertyList_s007a_51d0* gAppProperties;   // va 015fd918
}
// ---- items of slice s007a51d0 end

// @ 0x007a49e0
int __cdecl FUN_007a49e0(u32 param_1, u32 param_2, u32 param_3, u32 param_4, u32 param_5)
{
  (void)param_3;
  (void)param_4;
  (void)param_5;
  u32* const capsRoot = (u32*)FUN_11f8af0();
  u32* const caps = (u32*)capsRoot[0];
  u32* const d3d9 = *(u32**)0x16f89c8;   // _m_d3d9_ActiveState

  u32* const query = (u32*)FUN_11f8af0(caps, *(u32*)0x1712458, 1, 3, param_1);
  int rc = (int)(*(int(**)(u32*, u32))(d3d9[0] + 0x28))(d3d9, query[1]);
  if (rc < 0) {
    return 0;
  }

  u32* const capsRoot2 = (u32*)FUN_11f8af0();
  u32* const caps2 = (u32*)capsRoot2[0];
  u32* const query2 = (u32*)FUN_11f8af0(caps2, *(u32*)0x1712458,
                                        *(u32*)0x16f8bc4, param_1);
  rc = (int)(*(int(**)(u32*, u32))(d3d9[0] + 0x30))(d3d9, query2[1]);
  if (rc < 0) {
    return 0;
  }
  (void)param_2;
  return 1;
}

// @ 0x007a4a60
void cGraphicsSystem_s007a_41c0::SetDebugParam(u16 v)
{
  mDebugParam = v;
}

// @ 0x007a4a80
u32 cGraphicsSystem_s007a_41c0::ShouldShowDebug()
{
  if (mShowDebug != 0) {
    if (_sAppProperties->GetDescription(0x64574abu)) {
      return 1;
    }
  }
  return 0;
}

// @ 0x007a4ac0
void cGraphicsSystem_s007a_41c0::SetDebugRange(f32 range, f32 distance, f32 near_, f32 far_)
{
  mDebugFar = far_;
  mDebugNear = near_;
  mDebugDistance = distance;
  mDebugRange = range;
}

// @ 0x007a4b10
void cGraphicsSystem_s007a_41c0::GetRectID(TextureRectID* out, u32 id)
{
  if (id == 1) {
    const TextureRectID r = mGIFExportRectID;
    out[0] = r;
    return;
  }
  if (id == 0) {
    const TextureRectID r = mSplatterTextureRectID;
    out[0] = r;
    return;
  }
  if (id == 3) {
    const TextureRectID r = mSmallFinalBakedTextureRectID;
    out[0] = r;
    return;
  }
  if (id == 4) {
    const TextureRectID r = mFinalBakedTextureRectID;
    out[0] = r;
    return;
  }
  out->mPageID = 0;
  out->mAllocID = 0xffffffffu;
}

// @ 0x007a4bb0
void cGraphicsSystem_s007a_41c0::GetCurrentCubemapFaceRectID(u32* out)
{
  out[0] = mBakeBufferRectIDs[1].mPageID;
  out[1] = mBakeBufferRectIDs[1].mAllocID;
}

// @ 0x007a4be0
void cGraphicsSystem_s007a_41c0::SetCurrentCubemapFaceRectID(const u32* in)
{
  mBakeBufferRectIDs[1].mPageID = in[0];
  mBakeBufferRectIDs[1].mAllocID = in[1];
}

// @ 0x007a4c00
u8 cGraphicsSystem_s007a_41c0::GetByteFlag(u32 i)
{
  return mByteFlags[i];
}

// @ 0x007a4c10
void cGraphicsSystem_s007a_41c0::SetByteFlag(u32 i, u8 v)
{
  mByteFlags[i] = v;
}

// @ 0x007a4c90
void cObjectRef::Flush()
{
  cRefTarget* const p = mpObject;
  if (p) {
    p->mInner.i01();
  }
}

// @ 0x007a4cb0
bool SP::cGraphicsSystem::InitRenderer()
{
  char* const fresh = (char*)EXT_75fb90();
  char* const old = (char*)mRenderer.mpObject;
  if (fresh != old) {
    if (fresh != 0) {
      (*(void(**)(char*))*(void**)fresh)(fresh);
    }
    mRenderer.mpObject = (SP::cIRenderer*)fresh;
    if (old != 0) {
      u32* const vt = *(u32**)old;
      (*(void(**)(char*))(vt + 1))(old);
    }
  }
  char* const cur = (char*)mRenderer.mpObject;
  {
    u32* const vt = *(u32**)cur;
    if ((*(char(**)(char*))(vt + 3))(cur) != 0) {
      EXT_67df60(cur);
      return 1;
    }
  }
  char* const dead = (char*)mRenderer.mpObject;
  if (dead != 0) {
    mRenderer.mpObject = 0;
    u32* const vt = *(u32**)dead;
    (*(void(**)(char*))(vt + 1))(dead);
  }
  return 0;
}

// @ 0x007a4d20
bool cGraphicsSystem_s007a_41c0::PreShutdown()
{
  cIRenderer* const r = mRenderer;
  if (r) {
    r->RendererPreShutdown();
  }
  return true;
}

// @ 0x007a4d40
void cGraphicsSystem_s007a_41c0::RecycleEffectsBuffers()
{
  for (int i = 0; i < 4; ++i) {
    if (mEffectsBuffers[i] != 0) {
      mRTTManager->ReleaseRect(mEffectsBufferRectIDs[i].mPageID,
                               mEffectsBufferRectIDs[i].mAllocID);
      mEffectsBuffers[i] = 0;
    }
  }
}

// @ 0x007a4d90
void cGraphicsSystem_s007a_41c0::UpdateManagers(u32 param_1, f32 param_2)
{
  bool flag = *(int*)(*(int*)((char*)_sAppProperties + 0x3c) + 0x130) != 0;
  if (mDebugFlushState != (u8)flag) {
    mDebugFlushState = (u8)flag;
    EXT_6ad7c0((u32)4);
    EXT_6ad7c0((u32)5);
    EXT_6ad7c0((u32)9);
    EXT_6ad7c0((u32)10);
  }
  char* const light = (char*)mLightingManager;
  if (light != 0) {
    u32* const vt = *(u32**)light;
    (*(void(**)(char*, int))(vt + 5))(light, (int)(param_2 * 1000.0f));
  }
  char* const tex = (char*)mTextureManager;
  if (tex != 0) {
    u32* const vt = *(u32**)tex;
    (*(void(**)(char*))(vt + 5))(tex);
  }
  char* const mat = (char*)mMaterialManager;
  if (mat != 0) {
    u32* const vt = *(u32**)mat;
    (*(void(**)(char*))(vt + 5))(mat);
  }
  char* const mod = (char*)mModelManager;
  if (mod != 0) {
    u32* const vt = *(u32**)mod;
    (*(void(**)(char*, u32, f32))(vt + 14))(mod, param_1, param_2);
  }
}

// @ 0x007a4e40
void __fastcall FUN_007a4e40(cDebugDraw* thiz)
{
  cDebugDraw* const self = thiz;
  // The camera accessor writes the current camera position into `pos`;
  // the viewer's refiner then adjusts it in place.
  u32 pos[3];
  const f32 lo = 0.0f;
  const f32 hi = 1.0f;
  cApp* const app = APP_GetApp();
  cViewer* const viewer = (cViewer*)app->GetCameraViewer(pos, 0, 0, 0);
  viewer->Refine(pos, 0, 0, 0);

  const f32 dx = *(f32*)&pos[0];
  const f32 dy = *(f32*)&pos[1];
  const f32 dz = *(f32*)&pos[2];
  const f32 dist = (f32)sqrt(dx * dx + dy * dy + dz * dz);

  f32 t = (dist - self->mDebugDistance) /
          (self->mDebugRange - self->mDebugDistance);
  t = __max(t, lo);
  t = __min(t, hi);
  self->mDebugRadius =
      (self->mDebugNear - self->mDebugFar) * t + self->mDebugFar;
}

// @ 0x007a4ef0
void* cGraphicsSystem_s007a_41c0::GetLazyBuffer()
{
  cLazyBuffer* const b = mLazyBufferObject;
  if ((b->mFlags & 1) == 0) {
    cIBufferManager* const mgr = APP_GetBufferManager();
    mgr->CreateBuffer(b);
  }
  return b->mpValue;
}

// @ 0x007a4f10
void cGraphicsSystem_s007a_41c0::GetBakeBuffer(u32* out, int index)
{
  if (mBakeBuffers[index + 1] == 0) {
    CreateBakeBuffer(index);
  }
  out[0] = mBakeBufferRectIDs[index + 2].mPageID;
  out[1] = mBakeBufferRectIDs[index + 2].mAllocID;
}

// @ 0x007a4f50
void __fastcall FUN_007a4f50(void* thiz, u32 /*unused*/, u32 which)
{
  u32 rect[2] = { 0xffffffffu, 0xffffffffu };
  char* const self = (char*)thiz;
  u32* const vtbl = *(u32**)self;
  switch (which) {
    case 0: (*(void(**)(char*, u32*))(vtbl + (0xb0 / 4)))(self, rect); break;
    case 1: (*(void(**)(char*, u32*))(vtbl + (0xac / 4)))(self, rect); break;
    case 2: (*(void(**)(char*, u32*))(vtbl + (0xbc / 4)))(self, rect); break;
    case 3: (*(void(**)(char*, u32*))(vtbl + (0xb4 / 4)))(self, rect); break;
    case 4: (*(void(**)(char*, u32*))(vtbl + (0xb8 / 4)))(self, rect); break;
    default: break;
  }
  char* const a = *(char**)(self + 0x18);
  char* const b = *(char**)(self + 0x14);
  char* const desc = (*(char*(**)(char*, u32, u32))(*(u32**)a + (0x1c / 4)))(
      a, rect[0], rect[1]);
  char* const out = (*(char*(**)(char*, u32*, char*))(*(u32**)b + (0x2c / 4)))(
      b, rect, desc);
  u32* const dst = *(u32**)(self + 0x24);
  dst[0] = ((u32*)out)[0];
  dst[1] = ((u32*)out)[1];
  dst[2] = ((u32*)out)[2];
}

// @ 0x007a5020
void cGraphicsSystem_s007a_41c0::RecycleBakingRTTs(u32 /*param_1*/, u32 /*param_2*/)
{
  ReleaseRTT(mGIFExportTexture, mGIFExportRectID);
  ReleaseRTT(mShadowBlurTexture, mUnk100);
  ReleaseRTT(mAOTexture, mFinalBakedTextureRectID);
  ReleaseRTT(mFinalBakedTexture, mSmallFinalBakedTextureRectID);
  ReleaseRTT(mShadowTexture, mUnk108);
  (*(void(**)(void))(*(u32*)this + 0x34))();
}

// @ 0x007a51d0
namespace SP {
void SP::cGraphicsSystem_s007a_51d0::ReleaseGifExportTextures()
{
    if (mAnimGifExportTexture.mpObject != 0) {
        mRTTManager->ReleaseRenderTarget(mAnimGifExportRectID.mPageID,
                                         mAnimGifExportRectID.mAllocID);
        mAnimGifExportTexture.Release();
    }
    if (mEditGifExportTexture.mpObject != 0) {
        mRTTManager->ReleaseRenderTarget(mEditGifExportRectID.mPageID,
                                         mEditGifExportRectID.mAllocID);
        mEditGifExportTexture.Release();
    }
    ReleaseSelf();
}
}  // namespace SP

// @ 0x007a5290
namespace SP {
void SP::cGraphicsSystem_s007a_51d0::UpdateRendering(int delta)
{
    if (mRenderer != 0)
        mRenderer->UpdateRenderer(delta);                 // 0x34
    if (mEffectsRenderer != 0)
        mEffectsRenderer->UpdateEffects(delta);           // 0x80
    if (mField188) {
        if (gAppProperties->GetDescription(0x64574ab))
            ((cIGraphicsSystem_s007a_51d0*)this)->UpdateDebugDraw();
    }
    mTextureFlags = 0x01010101;
}
}  // namespace SP

// @ 0x007a52f0
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitSplatterTexture()
{
    int dim = mField170;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "SplatterRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mSplatterTexture.SetImageResource(image);
        mSplatterTextureRectID.mPageID = pageID;
        mSplatterTextureRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5370
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitAnimGifExportTexture()
{
    int w = gAppProperties->GetIntProperty(0x5893ed4);
    int h = gAppProperties->GetIntProperty(0x5893ee8);
    int size = h * w;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, size, size, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "AnimGIFExportRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mAnimGifExportTexture.SetImageResource(image);
        mAnimGifExportRectID.mPageID = pageID;
        mAnimGifExportRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5410
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitEditGifExportTexture()
{
    int w = gAppProperties->GetIntProperty(0x5893ed4);
    int h = gAppProperties->GetIntProperty(0x5893ee8);
    int size = h * w;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, size, size, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "EditGIFExportRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mEditGifExportTexture.SetImageResource(image);
        mEditGifExportRectID.mPageID = pageID;
        mEditGifExportRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a54b0
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitAOTexture()
{
    int dim = mField170;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xba595d5d, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "AORTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mAOTexture.SetImageResource(image);
        mAOTextureRectID.mPageID = pageID;
        mAOTextureRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5530
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitBakeInfoTexture()
{
    int dim = mField170;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "BakeInfoRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mBakeInfoTexture.SetImageResource(image);
        mBakeInfoRectID.mPageID = pageID;
        mBakeInfoRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a55b0
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitNMapSpecTexture()
{
    int dim = mField170;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "NMapSpecRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mNMapSpecTexture.SetImageResource(image);
        mNMapSpecRectID.mPageID = pageID;
        mNMapSpecRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5630
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitFinalBakedTexture()
{
    int dim = mField170;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "FinalBakedRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mFinalBakedTexture.SetImageResource(image);
        mFinalBakedRectID.mPageID = pageID;
        mFinalBakedRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a56b0
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitSmallFinalBakedTexture()
{
    int dim = mField170 >> 1;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "SmallFinalBakedRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mSmallFinalBakedTexture.SetImageResource(image);
        mSmallFinalBakedRectID.mPageID = pageID;
        mSmallFinalBakedRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5730
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitDepthTexture()
{
    cViewportExtent* extent = GetViewportInfo()->GetExtent();
    int width = extent->mWidth;
    int height = extent->mWidth2;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, width, height, 0x15, 0, 0x9b304161, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "DepthTexture");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mDepthTexture.SetImageResource(image);
        mDepthRectID.mPageID = pageID;
        mDepthRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a57d0
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitShadowTexture()
{
    GetViewportInfo()->GetExtent();
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, 0x200, 0x200, 0x15, 8, 0xf19d8d5, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "ShadowRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mShadowTexture.SetImageResource(image);
        mShadowRectID.mPageID = pageID;
        mShadowRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5860
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitShadowBlurTexture()
{
    cViewportExtent* extent = GetViewportInfo()->GetExtent();
    int width = extent->mWidth;
    int height = extent->mWidth2;
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, width, height, 0x15, 9, 0xfd9802c7, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "ShadowBlurTexture");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mShadowBlurTexture.SetImageResource(image);
        mShadowBlurRectID.mPageID = pageID;
        mShadowBlurRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5900
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitSnapshotTexture()
{
    cViewportExtent* extent = GetViewportInfo()->GetExtent();
    int width = (int)extent->mWidth | ((int)extent->mHeight << 16);
    int height = (int)extent->mWidth2 | ((int)extent->mHeight2 << 16);
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, width, height, 0x15, 9, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "CameraSnapshot");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mSnapshotTexture.SetImageResource(image);
        mSnapshotRectID.mPageID = pageID;
        mSnapshotRectID.mAllocID = allocID;
    }
    return mSnapshotTexture.mpObject != 0;
}
}  // namespace SP

// @ 0x007a5990
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitLargeThumbnailTexture()
{
    int dim = gAppProperties->GetIntProperty(0x8649077);
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "LargeThumbnailRTT");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mLargeThumbnailTexture.SetImageResource(image);
        mLargeThumbnailRectID.mPageID = pageID;
        mLargeThumbnailRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5a20
namespace SP {
bool SP::cGraphicsSystem_s007a_51d0::InitThumbnailBoundsTexture()
{
    cRenderTargetRectID_s007a_51d0 tmp;
    cRenderTargetRectID_s007a_51d0* rt =
        mRTTManager->CreateRenderTarget(&tmp, 0x40, 0x40, 0x15, 0, 0xffffffff, 0);
    int pageID = rt->mPageID;
    int allocID = rt->mAllocID;
    mRTTManager->SetRenderTargetName(pageID, allocID, "ThumbnailBoundsRect");
    if (allocID != -1) {
        void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
        mThumbnailBoundsTexture.SetImageResource(image);
        mThumbnailBoundsRectID.mPageID = pageID;
        mThumbnailBoundsRectID.mAllocID = allocID;
        return true;
    }
    return false;
}
}  // namespace SP

// @ 0x007a5ef0
namespace SP {
void SP::cGraphicsSystem_s007a_51d0::RecycleBakeBuffers()
{
    for (int i = 0; i < 2; ++i) {
        if (mBakeBufferRasters[i] != 0) {
            mRTTManager->ReleaseRenderTarget(mBakeBufferRectIDs[i].mPageID,
                                             mBakeBufferRectIDs[i].mAllocID);
            if (mBakeBuffers[i].mpObject != 0)
                mBakeBuffers[i].Release();
        }
    }
}
}  // namespace SP

// @ 0x007a5f70
namespace SP {
SP::cTextureHandle* SP::cGraphicsSystem_s007a_51d0::InitBakeBuffer(int index)
{
    cTextureHandle* slot = &mBakeBuffers[index];
    if (slot->mpObject == 0) {
        int dim = mField170;
        cRenderTargetRectID_s007a_51d0 tmp;
        cRenderTargetRectID_s007a_51d0* rt =
            mRTTManager->CreateRenderTarget(&tmp, dim, dim, 0x15, 0, 0xffffffff, 0);
        int pageID = rt->mPageID;
        int allocID = rt->mAllocID;
        mRTTManager->SetRenderTargetName(pageID, allocID, "BakeBuffers");
        if (pageID != -1) {
            void* image = mRTTManager->GetRenderTargetImage(pageID, allocID);
            slot->SetImageResource(image);
            mBakeBufferRectIDs[index].mPageID = pageID;
            mBakeBufferRectIDs[index].mAllocID = allocID;
        }
    }
    return slot;
}
}  // namespace SP

// @ 0x007a6010
namespace SP {
SP::cGraphicsSystem_s007a_51d0::cGraphicsSystem_s007a_51d0()
{
    mField08 = 0;
    mField0c = false;
    mRenderer = 0;
    mField14 = 0;
    mRTTManager = 0;
    mField1c = 0;
    mField20 = 0;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mField30 = 0;
    mField34 = 0;
    mEffectsRenderer = 0;
    mField3c = 0;
    mField40 = 0;
    mField44 = 0;
    mField48 = 0;
    // mField4c / mField50 are intentionally left untouched by the retail ctor.

    mSplatterTexture.mpObject = 0;
    mAnimGifExportTexture.mpObject = 0;
    mEditGifExportTexture.mpObject = 0;
    mBakeInfoTexture.mpObject = 0;
    mNMapSpecTexture.mpObject = 0;
    mAOTexture.mpObject = 0;
    mFinalBakedTexture.mpObject = 0;
    mSmallFinalBakedTexture.mpObject = 0;
    mShadowBlurTexture.mpObject = 0;
    mShadowTexture.mpObject = 0;
    mDepthTexture.mpObject = 0;
    mField80 = 0;
    mSnapshotTexture.mpObject = 0;
    mField88 = 0;
    mBakeBuffers[0].mpObject = 0;
    mBakeBuffers[1].mpObject = 0;
    mLargeThumbnailTexture.mpObject = 0;
    mThumbnailBoundsTexture.mpObject = 0;
    mBakeBufferRasters[0] = 0;
    mBakeBufferRasters[1] = 0;
    mBakeBufferRasters[2] = 0;
    mBakeBufferRasters[3] = 0;

    mFieldAc.mPageID = -1;      mFieldAc.mAllocID = -1;
    mFieldB4.mPageID = -1;      mFieldB4.mAllocID = -1;
    mFieldBc.mPageID = -1;      mFieldBc.mAllocID = -1;
    mFieldC4.mPageID = -1;      mFieldC4.mAllocID = -1;
    mAOTextureRectID.mPageID = -1;          mAOTextureRectID.mAllocID = -1;
    mSplatterTextureRectID.mPageID = -1;    mSplatterTextureRectID.mAllocID = -1;
    mAnimGifExportRectID.mPageID = -1;      mAnimGifExportRectID.mAllocID = -1;
    mEditGifExportRectID.mPageID = -1;      mEditGifExportRectID.mAllocID = -1;
    mBakeInfoRectID.mPageID = -1;           mBakeInfoRectID.mAllocID = -1;
    mNMapSpecRectID.mPageID = -1;           mNMapSpecRectID.mAllocID = -1;
    mFinalBakedRectID.mPageID = -1;         mFinalBakedRectID.mAllocID = -1;
    mSmallFinalBakedRectID.mPageID = -1;    mSmallFinalBakedRectID.mAllocID = -1;
    mShadowBlurRectID.mPageID = -1;         mShadowBlurRectID.mAllocID = -1;
    mShadowRectID.mPageID = -1;             mShadowRectID.mAllocID = -1;
    mField120.mPageID = -1;                 mField120.mAllocID = -1;
    mField128.mPageID = -1;                 mField128.mAllocID = -1;
    mDepthRectID.mPageID = -1;              mDepthRectID.mAllocID = -1;
    mSnapshotRectID.mPageID = -1;           mSnapshotRectID.mAllocID = -1;
    mField140.mPageID = -1;                 mField140.mAllocID = -1;
    mBakeBufferRectIDs[0].mPageID = -1;     mBakeBufferRectIDs[0].mAllocID = -1;
    mBakeBufferRectIDs[1].mPageID = -1;     mBakeBufferRectIDs[1].mAllocID = -1;
    mLargeThumbnailRectID.mPageID = -1;     mLargeThumbnailRectID.mAllocID = -1;
    mThumbnailBoundsRectID.mPageID = -1;    mThumbnailBoundsRectID.mAllocID = -1;

    mField168 = false;
    mField169 = false;
    mField16a = false;
    mField16c = -1;
    mField170 = 0x100;
    mField174 = 200.0f;
    mField178 = 1000.0f;
    mField17c = 50.0f;
    mField180 = 5000.0f;
    mField184 = 10.0f;
    mField188 = false;
    mField18c = 0;
    mField190 = false;

    mTextureFlags = 0x01010101;
}
}  // namespace SP

// @ 0x007a62c0
cGraphicsSystem::~cGraphicsSystem()
{
    this->vtbl0 = (void*)VT_cGraphicsSystem_IGraphicsSystem;
    this->vtbl1 = (void*)VT_cGraphicsSystem_RefCount;

    // The original destroys the trailing AutoRefCount block + bake buffers first.
    ReleaseRefCount(this->mBufferTextures[0]);
    ReleaseRefCount(this->mThumbnailBoundsTexture);
    FUN_00576620(&this->mBakeBuffers[1]);
    FUN_00576620(&this->mLargeThumbnailTexture);
    ReleaseRefCount(this->mCurrentCubemapFaceRaster);
    ReleaseRefCount(this->mCameraSnapshotTexture);
    ReleaseRefCount(this->mCapturedCubemapTexture);
    ReleaseRefCount(this->mDepthTexture);
    ReleaseRefCount(this->mShadowTexture);
    ReleaseRefCount(this->mShadowBlurTexture);
    ReleaseRefCount(this->mSmallFinalBakedTexture);
    ReleaseRefCount(this->mFinalBakedTexture);
    ReleaseRefCount(this->mAOTexture);
    ReleaseRefCount(this->mNMapSpecTexture);
    ReleaseRefCount(this->mBakeInfoTexture);
    ReleaseRefCount(this->mGIFExportTexture);

    FUN_00a23920(&this->mBuiltinBegin);

    if (this->mShadowWorld)     ((void(__thiscall*)(void*))((*(void***)this->mShadowWorld)[1]))(this->mShadowWorld);
    if (this->mEffectsRenderer) ((void(__thiscall*)(void*))((*(void***)this->mEffectsRenderer)[1]))(this->mEffectsRenderer);
    if (this->mEffectsResources)((void(__thiscall*)(void*))((*(void***)this->mEffectsResources)[1]))(this->mEffectsResources);
    if (this->mFilterChainRenderer)((void(__thiscall*)(void*))((*(void***)this->mFilterChainRenderer)[1]))(this->mFilterChainRenderer);
    if (this->mModelManager)    ((void(__thiscall*)(void*))((*(void***)this->mModelManager)[1]))(this->mModelManager);
    if (this->mLightingManager) ((void(__thiscall*)(void*))((*(void***)this->mLightingManager)[1]))(this->mLightingManager);
    if (this->mMaterialManager) ((void(__thiscall*)(void*))((*(void***)this->mMaterialManager)[1]))(this->mMaterialManager);
    if (this->mThumbnailManager)((void(__thiscall*)(void*))((*(void***)this->mThumbnailManager)[1]))(this->mThumbnailManager);
    if (this->mRTTManager)      ((void(__thiscall*)(void*))((*(void***)this->mRTTManager)[1]))(this->mRTTManager);
    if (this->mTextureManager)  ((void(__thiscall*)(void*))((*(void***)this->mTextureManager)[1]))(this->mTextureManager);
    if (this->mRenderer)        ((void(__thiscall*)(void*))((*(void***)this->mRenderer)[1]))(this->mRenderer);

    this->vtbl1 = (void*)VT_RefCountBase;
}

// @ 0x007a66c0
void cGraphicsSystem::InitBufferTexture(int index)
{
    if (this->mBufferTextures[index + 1] != 0)
        return;

    int n = 1;
    if (index < 4)
        TryGetUIntProperty(sAppProperties, sBufferTexturePropertyKeys[index], &n);

    void* p = FUN_0067dd50();
    int* wh = (int*)((void* (__thiscall*)(void*))((*(void***)p)[0x1c / 4]))(p);

    unsigned short w = (unsigned short)(wh[0] / n);
    unsigned short h = (unsigned short)(wh[1] / n);

    RectID rect;
    rect.mPageID = 0x1667bac;
    rect.mAllocID = 0x1667bad;

    void* mgr = this->mRTTManager;
    BufferRect* res = (BufferRect*)((void* (__thiscall*)(void*, BufferRect*, unsigned short,
                                                         unsigned short, int, int, int, int))
        ((*(void***)mgr)[0x10 / 4]))(mgr, (BufferRect*)&rect, w, h, 0x15, 0, -1, 0);
    int allocID = res->mAllocID;
    int pageID = res->mPageID;

    ((void(__thiscall*)(void*, int, int, const char*))((*(void***)mgr)[0x48 / 4]))
        (mgr, allocID, pageID, "EffectsBuffers");

    if (allocID != -1) {
        void* raster = ((void* (__thiscall*)(void*, int, int))((*(void***)mgr)[0x18 / 4]))
            (mgr, allocID, pageID);
        this->mBufferTextures[index + 1] = raster;
        this->mBufferTextureRectIDs[index].mAllocID = allocID;
        this->mBufferTextureRectIDs[index + 1].mPageID = pageID;
    }
}

// @ 0x007a6870
void* cGraphicsSystem::GetBufferTexture(int index, char param_3)
{
    if (param_3 == 0) {
        void* sys = FUN_0067dd40();
        ((void(__thiscall*)(void*, int, int))((*(void***)sys)[0x90 / 4]))(sys, index, 0);
    }
    if (this->mBufferTextures[index + 1] == 0)
        InitBufferTexture(index);
    return this->mBufferTextures[index + 1];
}

// @ 0x007a68c0
void cGraphicsSystem::GetBufferRectID(int index, BufferRect* out, char param_4)
{
    if (param_4 == 0)
        ((void(__thiscall*)(void*, int, int))(((void**)this->vtbl0)[0x90 / 4]))(this, index, 0);
    if (this->mBufferTextures[index + 1] == 0)
        InitBufferTexture(index);
    out->mAllocID = this->mBufferTextureRectIDs[index].mAllocID;
    out->mPageID  = this->mBufferTextureRectIDs[index + 1].mPageID;
}

// @ 0x007a6910
void ModelVector::InsertAt(void* position, void* value)
{
    void* end = this->mpEnd;
    if (end != this->mpCapacity) {
        if (position <= value && value < end)
            value = (char*)value + 4;

        void* p = end;
        if (p) {
            void* src = *(void**)((char*)end - 4);
            *(void**)p = src;
            if (src)
                ((void(__thiscall*)(void*))((*(void***)src)[0]))(src);
        }
        FUN_00ac97a0(position, (char*)this->mpEnd - 4, this->mpEnd);
        void* v = *(void**)value;
        void* old = *(void**)position;
        if (v != old) {
            if (v)
                ((void(__thiscall*)(void*))((*(void***)v)[0]))(v);
            *(void**)position = v;
            if (old)
                ((void(__thiscall*)(void*))((*(void***)old)[1]))(old);
        }
        this->mpEnd = (char*)this->mpEnd + 4;
        return;
    }

    int count = (int)((char*)end - (char*)this->mpBegin) >> 2;
    int newCap;
    void* newBegin;
    if (count == 0) {
        newCap = 1;
        newBegin = EASTL_allocator_allocate((unsigned)(newCap * 4), "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    } else {
        newCap = count * 2;
        if (newCap == 0) {
            newBegin = 0;
        } else {
            newBegin = EASTL_allocator_allocate((unsigned)(newCap * 4), "Graphics", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                0xd1);
        }
    }

    unsigned int prefix = (unsigned int)((char*)position - (char*)this->mpBegin);
    void* mid = VectorDoInsertValue(newBegin, this->mpBegin, prefix);
    void* slot = (char*)mid + (prefix & ~3u);
    void* v = *(void**)value;
    *(void**)slot = v;
    if (v)
        ((void(__thiscall*)(void*))((*(void***)v)[0]))(v);

    int tail = (int)((char*)this->mpEnd - (char*)position);
    void* last = VectorDoInsertValue((char*)slot + 4, position, tail);
    if (this->mpBegin && *(int*)((char*)this->mpBegin - 4) != 0)
        EASTL_allocator_deallocate(this->mpBegin);
    this->mpEnd = (char*)last + (tail & ~3u);
    this->mpBegin = newBegin;
    this->mpCapacity = (char*)newBegin + newCap * 4;
}

// @ 0x007a6b40
bool cGraphicsSystem::Shutdown()
{
    if (this->mInitialized != false) {
        this->mInitialized = false;
        ((void(__thiscall*)(void*, void*, void*))VectorErase)
            (&this->mBuiltinBegin, this->mBuiltinBegin, this->mBuiltinEnd);

        if (this->mThumbnailManager) {
            FUN_0067dfc0(0);
            ((void(__thiscall*)(void*))((*(void***)this->mThumbnailManager)[0x10 / 4]))(this->mThumbnailManager);
            void* p = this->mThumbnailManager;
            if (p) { this->mThumbnailManager = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        if (this->mModelManager) {
            FUN_0067df90(0);
            ((void(__thiscall*)(void*))((*(void***)this->mModelManager)[0x10 / 4]))(this->mModelManager);
            void* p = this->mModelManager;
            if (p) { this->mModelManager = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        if (this->mFilterChainRenderer) {
            ((void(__thiscall*)(void*))((*(void***)this->mFilterChainRenderer)[0x14 / 4]))(this->mFilterChainRenderer);
            void* p = this->mFilterChainRenderer;
            if (p) { this->mFilterChainRenderer = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        if (this->mEffectsRenderer) {
            ((void(__thiscall*)(void*))((*(void***)this->mEffectsRenderer)[0x7c / 4]))(this->mEffectsRenderer);
            void* p = this->mEffectsRenderer;
            if (p) { this->mEffectsRenderer = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
            FUN_0067e020(0);
        }
        FUN_006efc10();
        if (this->mEffectsResources) {
            FUN_006f2620();
            void* p = this->mEffectsResources;
            if (p) { this->mEffectsResources = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
            FUN_0067e010(0);
        }
        if (this->mLightingManager) {
            FUN_0067dfa0(0);
            ((void(__thiscall*)(void*))((*(void***)this->mLightingManager)[0x10 / 4]))(this->mLightingManager);
            void* p = this->mLightingManager;
            if (p) { this->mLightingManager = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        if (this->mMaterialManager) {
            FUN_0067df70(0);
            ((void(__thiscall*)(void*))((*(void***)this->mMaterialManager)[0x10 / 4]))(this->mMaterialManager);
            void* p = this->mMaterialManager;
            if (p) { this->mMaterialManager = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        if (this->mShadowWorld) {
            FUN_0067dfd0(0);
            FUN_00782b00();
            void* p = this->mShadowWorld;
            if (p) {
                this->mShadowWorld = 0;
                void* q = (char*)p + 8;
                ((void(__thiscall*)(void*))((*(void***)q)[1]))(q);
            }
        }

        ReleaseTexture(this, this->mGIFExportTexture,        this->mGIFExportRectID, 8);
        ReleaseTexture(this, this->mSmallFinalBakedTexture,  this->mSplatterTextureRectID, 8);
        ReleaseTexture(this, this->mAOTexture,               this->mFinalBakedTextureRectID, 8);
        ReleaseTexture(this, this->mFinalBakedTexture,       this->mSmallFinalBakedTextureRectID, 8);
        ReleaseTexture(this, this->mShadowBlurTexture,       this->mShadowBlurTextureRectID, 8);
        ReleaseTexture(this, this->mShadowTexture,           this->mShadowTextureRectID, 8);
        ReleaseTexture(this, this->mDepthTexture,            this->mDOFTextureRectID, 8);
        ReleaseTexture(this, this->mCapturedCubemapTexture,  this->mNDotLTextureRectID, 0);
        ReleaseTexture(this, this->mCameraSnapshotTexture,   this->mCurrentCubemapFaceRectID, 8);
        if (this->mCameraSnapshotZTexture) this->mCameraSnapshotZTexture = 0;
        if (this->mBakeBuffers[0])         this->mBakeBuffers[0] = 0;
        ReleaseTexture(this, this->mCurrentCubemapFaceRaster, this->mBakeBufferRectIDs[0], 0);
        ReleaseTexture(this, this->mBakeInfoTexture,         this->mBakeInfoTextureRectID, 8);
        ReleaseTexture(this, this->mNMapSpecTexture,         this->mNMapSpecTextureRectID, 8);

        for (int i = 0; i < 4; ++i) {
            if (this->mBufferTextures[i + 1]) {
                void* mgr = this->mRTTManager;
                ((void(__thiscall*)(void*, int, int))((*(void***)mgr)[0x14 / 4]))
                    (mgr, this->mBufferTextureRectIDs[i].mPageID, this->mBufferTextureRectIDs[i].mAllocID);
                this->mBufferTextures[i + 1] = 0;
            }
        }

        if (this->mRTTManager) {
            FUN_0067dfb0(0);
            ((void(__thiscall*)(void*))((*(void***)this->mRTTManager)[0x0c / 4]))(this->mRTTManager);
            void* p = this->mRTTManager;
            if (p) { this->mRTTManager = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        FUN_007a8360();
        if (this->mTextureManager) {
            FUN_0067df80(0);
            ((void(__thiscall*)(void*))((*(void***)this->mTextureManager)[0x10 / 4]))(this->mTextureManager);
            void* p = this->mTextureManager;
            if (p) { this->mTextureManager = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
        }
        FUN_006e1010();
        FUN_007a4320();
        FUN_006ddc90();
        FUN_007c3910();

        for (int i = 3; i != 0; --i) {
            void* rm = GetManager();
            ((void(__thiscall*)(void*, int, int))((*(void***)rm)[0x70 / 4]))(rm, 0, 0);
        }
    }

    if (this->mRenderer) {
        FUN_0067df60(0);
        ((void(__thiscall*)(void*))((*(void***)this->mRenderer)[0x10 / 4]))(this->mRenderer);
        void* p = this->mRenderer;
        if (p) { this->mRenderer = 0; ((void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
    }

    void* rm = GetManager();
    void* res = ((void* (__thiscall*)(void*, unsigned int, int))((*(void***)rm)[0x48 / 4]))
        (rm, 0x2f4e681b, -1);
    if (res != 0 &&
        ((int (__thiscall*)(void*))((*(void***)res)[0x18 / 4]))(res) == (int)0xaf4ffa27) {
        void* rm2 = GetManager();
        ((void(__thiscall*)(void*, int, void*, int))((*(void***)rm2)[0x44 / 4]))(rm2, 0, res, 0);
    }
    void* rm3 = GetManager();
    void* res2 = ((void* (__thiscall*)(void*, unsigned int, int))((*(void***)rm3)[0x48 / 4]))
        (rm3, 0x3e421ed, -1);
    if (res2 != 0 &&
        ((int (__thiscall*)(void*))((*(void***)res2)[0x18 / 4]))(res2) == 0x5f10581) {
        void* rm4 = GetManager();
        ((void (__thiscall*)(void*, int, void*, int))((*(void***)rm4)[0x44 / 4]))(rm4, 0, res2, 0);
    }
    return true;
}

// @ 0x007a7210
namespace SP {
void cGraphicsSystem_s007a_7210::CreateBuiltinModels()
{
    mBuiltinModels.reserve(16);

    EA::AutoRefCount_s007a_7210<cIMeshBuilder> mb(CreateMeshBuilder());

    {
        cSPVector3_s007a_7210 boxMin(-0.1f, -0.1f, -0.1f);
        cSPVector3_s007a_7210 boxMax(0.1f, 0.1f, 0.1f);
        CreateBoxMesh(mb, boxMin, boxMax);
    }
    AddBuiltinModel(mb, 0x1565205f);

    CreateMesh_c900(mb);
    AddBuiltinModel(mb, 0x2ebcd6a6);

    CreateDiscMesh(mb, 1.0f, 10);
    AddBuiltinModel(mb, 0xcf571b4e);

    CreateDiscMesh(mb, 1.0f, 64);
    AddBuiltinModel(mb, 0xcd672bca);

    CreateQuadMesh(mb, cSPVector3_s007a_7210(-1.0f, -1.0f, 0.0f), cSPVector3_s007a_7210(1.0f, 1.0f, 0.0f));
    AddBuiltinModel(mb, 0xf24b36e0);

    CreateBoxMesh(mb, -kOneVector, kOneVector);
    AddBuiltinModel(mb, 0x2099b900);

    CreateMesh_d550(mb, 1.0f, 4.0f, 10, 2, 2, 0);
    AddBuiltinModel(mb, 0xc7862c87);

    CreateMesh_d960(mb, 1.0f, 4.0f, 1, 10);
    AddBuiltinModel(mb, 0xddc5a098);

    CreateArrowheadMesh(mb, 1.0f);
    AddBuiltinModel(mb, 0x7990c40a);

    CreateMesh_d2f0(mb, 1.0f);
    AddBuiltinModel(mb, 0xafa8492a);

    CreateDiscMesh(mb, 1.0f, 16);
    AddBuiltinModel(mb, 0xd622470c);

    CreateDiscMesh(mb, 1.0f, 32);
    AddBuiltinModel(mb, 0xd622470f);

    CreateDiscMesh(mb, 1.0f, 48);
    AddBuiltinModel(mb, 0xd622470e);

    CreateDiscMesh(mb, 1.0f, 64);
    AddBuiltinModel(mb, 0xd6224709);

    CreateDiscMesh(mb, 1.0f, 96);
    AddBuiltinModel(mb, 0xd6224708);
}
}  // namespace SP

// @ 0x007a7d50
extern "C" void FUN_007a7d50(cTextRenderer* self)
{
    self->mInitialized = true;
    self->Init();
}

// @ 0x007a8360
void FUN_007a8360()
{
    void* p = FUN_0067de10();
    if (p) {
        FUN_0067dfe0(0);
        ((void(__thiscall*)(void*))((*(void***)p)[0x0c / 4]))(p);
    }
}
