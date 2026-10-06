// Skinner::cSkinPainterPipeline::ExecutePipeline, 0x0051afd0.
// Unoptimized skin-paint module: /Od /Ob1 /MD /Gy /TP (no /EHsc).
//
// A fall-through switch over mCurrentStage (cases 0..13, jump table at 0x51c42c). Every paint stage
// creates its job on demand (EA operator new "Skinner"), stores it in the intrusive_ptr mpCurrentJob,
// starts it (vtable slot 4) and leaves until the job reports mHasFinished, then drops it and advances.
// Layouts from ModAPI (Spore/Skinner/cSkinPainterPipeline.h, cSkinPainterJob*.h); job vtables
// (0x13f1b40 PaintParts, 0x13f1b24 AmbientOcclusion, 0x13f1b0c ColorDilateRepeat, 0x13f1af4
// CopyTex1AlphaToTex0, 0x13f1adc CopyRigblocksTintMaskAlpha, 0x13f1ac4 BumpToNormal) identified by
// their Execute slot.
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);

namespace Skinner {

struct cPaintSystem {
    uint32_t pad[0x7c / 4];
    bool mbField7C;                       // +0x7c
    bool IsField7C() { return mbField7C; }
};

cPaintSystem* GetPaintSystem();           // 0x00401080

struct Texture {
    uint32_t vt;
    uint8_t mFlags;                       // +0x04, bit 0: loaded
    uint8_t GetFlags() { return mFlags; }
};

struct TexturePtr {
    Texture* mpObject;
    Texture* get() const { return mpObject; }
    Texture* operator->() const { return mpObject; }
};

struct TextureVector {                    // eastl::fixed_vector<TexturePtr, 192>
    TexturePtr* mpBegin;
    TexturePtr* mpEnd;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    TexturePtr& operator[](uint32_t n) { return mpBegin[n]; }
};

// ILayer (vptr +0) + RefCountTemplateAtomic (vptr +4, count +8)
struct ILayer {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void v2() = 0;
    virtual void v3() = 0;
    virtual void Initialize() = 0;        // +0x10
    virtual bool Execute() = 0;
};

struct IRefAtomic {
    virtual void r0();
    int mnRefCount;
};

class cSkinPainterJob : public ILayer, public IRefAtomic {
public:
    cSkinPainterJob();                    // 0x005173a0
    bool mHasFinished;                    // +0x0c
};

class cSkinPainterJobApplyBrushes : public cSkinPainterJob {
public:
    cSkinPainterJobApplyBrushes(int a, bool b);   // 0x00517310
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int field_10, field_14, field_18, field_1C, field_20, field_24, field_28;
    bool field_2C;
};

class cSkinPainterJobPaintParts : public cSkinPainterJob {
public:
    cSkinPainterJobPaintParts() : mStage(0), mRigblockIndex(0) {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int mStage;
    int mRigblockIndex;
};

class cSkinPainterJobAmbientOcclusion : public cSkinPainterJob {
public:
    cSkinPainterJobAmbientOcclusion() {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};

class cSkinPainterJobColorDilateRepeat : public cSkinPainterJob {
public:
    cSkinPainterJobColorDilateRepeat(int a) : field_10(a), mNumSteps(8), field_18(0) {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int field_10;
    int mNumSteps;
    int field_18;
};

class cSkinPainterJobCopyTex1AlphaToTex0 : public cSkinPainterJob {
public:
    cSkinPainterJobCopyTex1AlphaToTex0() {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};

class cSkinPainterJobCopyRigblocksTintMaskAlpha : public cSkinPainterJob {
public:
    cSkinPainterJobCopyRigblocksTintMaskAlpha() : mRigblockIndex(0) {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
    int mRigblockIndex;
};

class cSkinPainterJobBumpToNormal : public cSkinPainterJob {
public:
    cSkinPainterJobBumpToNormal() {}
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};

struct IUnmanagedMessageListener { virtual void m0(); };
struct IMessageRC { virtual void n0(); };

class cSkinPainterJobExtractTexture : public IUnmanagedMessageListener, public IMessageRC, public cSkinPainterJob {
public:
    // 0x0051c470 (nonmatching in slice s0051c470). The real ctor is defined inline in the header but
    // cl /Ob1 declines to inline it; its reserved frame leaves a 6-dword hole in this caller's /Od frame
    // (blocks 11 and 13). This stand-in body only reproduces that frame; the real body lives at 0x51c470.
    cSkinPainterJobExtractTexture(int mode, uint32_t instanceID, uint32_t groupID, bool b1, int n,
                                  bool b2, bool b3)
        : mInstanceID(instanceID), mGroupID(groupID), field_20(0), field_24(n), field_28(b2),
          field_29(b3), field_2A(b1), field_2C(0), field_30(0)
    {
        uint32_t frame[6];
        frame[0] = mode;
    }
    uint32_t mInstanceID;                 // +0x18
    uint32_t mGroupID;                    // +0x1c
    void* field_20;                       // +0x20 RenderWare::Raster*
    int field_24;                         // +0x24
    bool field_28, field_29, field_2A;    // +0x28
    int field_2C;                         // +0x2c
    int field_30;                         // +0x30
    uint32_t mMessageListenerData[(0x48 - 0x34) / 4];
    int AddRef(); int Release(); void v2(); void v3(); void Initialize(); bool Execute();
};

template <class T>
struct intrusive_ptr {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

class cSkinPainterPipeline {
public:
    void ExecutePipeline();

    uint32_t vt;                                     // +0x000
    int mnRefCount;                                  // +0x004
    TextureVector mTextures;                         // +0x008 fixed_vector<TexturePtr, 192>
    uint32_t mTexturesRest[(0x320 - 0x10) / 4];
    uint32_t mTextureInstanceID;                     // +0x320
    uint32_t mTextureGroupID;                        // +0x324
    uint32_t field_328;                              // +0x328
    int field_32C;                                   // +0x32c
    intrusive_ptr<cSkinPainterJob> mpCurrentJob;     // +0x330
    int field_334;                                   // +0x334
    int field_338;                                   // +0x338
    int mCurrentStage;                               // +0x33c
    int field_340;                                   // +0x340
    int field_344;                                   // +0x344
    bool field_348;                                  // +0x348
    bool field_349;
    bool field_34A;
    bool field_34B;
    bool field_34C;
    bool field_34D;
    bool field_34E;
};

// Runs one stage's job: create + start it on first entry, then wait until it reports completion.
#define RUN_JOB(NEWJOB)                                         \
    do {                                                        \
        if (mpCurrentJob.get() == 0) {                          \
            mpCurrentJob = NEWJOB;                              \
            mpCurrentJob->Initialize();                         \
        }                                                       \
        if (mpCurrentJob->mHasFinished) {                       \
            mpCurrentJob = 0;                                   \
        } else {                                                \
            return;                                             \
        }                                                       \
    } while (0)

// @ 0x0051afd0
void cSkinPainterPipeline::ExecutePipeline()
{
    cPaintSystem* pPaintSystem = GetPaintSystem();
    field_344++;

    switch (mCurrentStage) {
    case 0:
        mCurrentStage = 1;
    case 1:
        mCurrentStage = 2;
    case 2:
        for (int i = 0, n = mTextures.size(); i < n; i++) {
            if (mTextures[i].get() != 0 && (mTextures[i]->GetFlags() & 1) == 0) {
                field_340++;
                return;
            }
        }
        mCurrentStage = 3;
    case 3:
        RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobApplyBrushes(field_338, !field_349));
        mCurrentStage = 4;
    case 4:
        if (field_348)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobPaintParts());
        mCurrentStage = 5;
    case 5:
        if (field_348 && field_34A && !pPaintSystem->IsField7C())
            return;
        mCurrentStage = 6;
    case 6:
        if (field_348 && field_34A)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobAmbientOcclusion());
        mCurrentStage = 7;
    case 7:
        if (field_348 && !field_34E)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobColorDilateRepeat(0));
        mCurrentStage = 8;
    case 8:
        if (field_348 && !field_34E)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobColorDilateRepeat(1));
        mCurrentStage = 9;
    case 9:
        if (field_348 && field_349)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobCopyTex1AlphaToTex0());
        mCurrentStage = 10;
    case 10:
        if (field_348)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobCopyRigblocksTintMaskAlpha());
        mCurrentStage = 11;
    case 11:
        if (mTextureGroupID)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobExtractTexture(
                0, mTextureInstanceID, mTextureGroupID, field_34D, field_32C, false, field_34C));
        mCurrentStage = 12;
    case 12:
        if (field_328)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobBumpToNormal());
        mCurrentStage = 13;
    case 13:
        if (field_328)
            RUN_JOB(new("Skinner", 0, 0, 0, 0) cSkinPainterJobExtractTexture(
                2, mTextureInstanceID, field_328, field_34D, -1, field_34B, field_34C));
        mCurrentStage = 14;
    default:
        if (mCurrentStage != -1)
            mCurrentStage = -1;
    }
}

}  // namespace Skinner
