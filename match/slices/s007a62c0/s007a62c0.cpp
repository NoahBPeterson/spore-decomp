// slice s007a62c0  --  SP::cGraphicsSystem: destructor, buffer-texture helpers,
// AutoRefCount-vector insert, Shutdown.
// Reconstructed C++ (MSVC x86, cl 15.00 /O2 /MD /Gy /EHsc /TP).
#include "types.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" long  _InterlockedExchangeAdd(volatile long* addend, long value);
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- helpers referenced only by address -------------------------------------
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

// property lookup used by InitBufferTexture
extern "C" int   TryGetUIntProperty(void* props, int key, int* out);
extern "C" void* sAppProperties;
extern int       sBufferTexturePropertyKeys[4];

// vtables (DIR32 relocations are masked by the verifier)
extern char VT_cGraphicsSystem_IGraphicsSystem[];
extern char VT_cGraphicsSystem_RefCount[];
extern char VT_RefCountBase[];

struct RectID { int mPageID; int mAllocID; };   // cGraphicsSystem render-target rect
struct BufferRect { int mAllocID; int mPageID; }; // GetBufferRectID out-param

// AutoRefCount-style release: fetch-add -1, read back, saturate at 1.
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
    void* Shutdown();
    ~cGraphicsSystem();
};

// --------------------------------------------------------------- destructor
// @ 0x007a62c0  SP::cGraphicsSystem::~cGraphicsSystem
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

// @ 0x007a66c0  SP::cGraphicsSystem::InitBufferTexture
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

// @ 0x007a6870  SP::cGraphicsSystem::GetBufferTexture
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

// @ 0x007a68c0  SP::cGraphicsSystem::GetBufferRectID
void cGraphicsSystem::GetBufferRectID(int index, BufferRect* out, char param_4)
{
    if (param_4 == 0)
        ((void(__thiscall*)(void*, int, int))(((void**)this->vtbl0)[0x90 / 4]))(this, index, 0);
    if (this->mBufferTextures[index + 1] == 0)
        InitBufferTexture(index);
    out->mAllocID = this->mBufferTextureRectIDs[index].mAllocID;
    out->mPageID  = this->mBufferTextureRectIDs[index + 1].mPageID;
}

// --------------------------------------------------------------- vector insert
// @ 0x007a6910
// eastl::vector<EA::AutoRefCount<SP::cGameModelResource>,...>::insert(iterator, const value_type&)
struct ModelVector {
    void* mpBegin;                  // +0
    void* mpEnd;                    // +4
    void* mpCapacity;               // +8
    void InsertAt(void* position, void* value);
};

extern "C" void* VectorDoInsertValue(void* dest, void* position, unsigned int bytes);

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

// --------------------------------------------------------------- helper
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

// @ 0x007a6b40  SP::cGraphicsSystem::Shutdown
void* cGraphicsSystem::Shutdown()
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
    return (void*)1;
}
