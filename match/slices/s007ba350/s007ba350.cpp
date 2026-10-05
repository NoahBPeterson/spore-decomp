// Slice s007ba350 — SP::cThumbnailManager::InitPostProcessEffect  (0x007ba350, 4887 bytes)
//
// A single enormous UI/render-target setup routine.  It switches on a stage
// enum (1,2,5,6,7,8,9), creates a chain of cRenderTargetRect / filter jobs via
// the Graphics allocator and the RTT manager, and configures each job's rect
// IDs and float parameters.  This is a best-effort control-flow reconstruction:
// every branch, helper call and object construction of the original is
// represented, but the individual field stores inside the EASTL vector/rect
// objects are summarised (see partial.txt).  Not byte-exact.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE  (movss/xorps, no frame pointer, EH frame)

#include "types.h"

// --- render-target rect id -------------------------------------------------
struct RectID {
    int mPageID;    // +0x0
    int mAllocID;   // +0x4
};

struct Raster {                 // rw::graphics::Raster (partial)
    char pad[4];
    unsigned short m_width;
    unsigned short m_height;
};

struct IRTTManager;             // +0x10b4, vtable slots at +0x10/+0x24/+0x48

// A render-target job/rect object (cJobPostFilter / cRenderTargetRect family).
struct Job {
    virtual void v0();          // +0x00
    virtual void Release();     // +0x04
    int   m0c;                  // +0x0c  kind/hash
    RectID mRect1;              // +0x10
    RectID mRect2;              // +0x1c
    int   m24_begin;            //  0x24  eastl::vector<RectID>
    int   m28_end;              // +0x28
    int   m2c_cap;              // +0x2c
    int   m38;
    float m3c[12];              // +0x3c  float parameter block
    unsigned char m82;          // +0x82
    unsigned char m83;          // +0x83
    int   m84, m88, m8c, m90, m94;
    int   m98, m9c, ma0, ma4;
    int   mac[8];
    float mcc;
};

// --- the manager -----------------------------------------------------------
struct cThumbnailManager {
    char pad0[0x10];
    Raster* mThumbRaster;               // +0x10
    RectID  mThumbRectID;               // +0x14
    RectID  mBlurThumbRectID1;          // +0x1c
    RectID  mBlurThumbRectID2;          // +0x24
    RectID  mTempThumbnailBuffer;       // +0x2c
    char pad1[0x10b4 - 0x34];
    IRTTManager* mRTTMgr;               // +0x10b4

    void InitPostProcessEffect(int stage, bool bFlag, RectID* outRect,
                               bool bFlag2, float f1, float f2, RectID* inRect);
};

// --- external helpers (names from the surrounding slices / PDB) -------------
// 0x7b8550: Job constructor; 0x7b9420/0x7b9510/0x7b9690/0x7b9750: Job setup
// helpers (all __thiscall on the job); 0x7b3a30/0x7b27a0/0x7b27e0/0x7b2820:
// Job parameter setters.  Relocated calls are masked, so declarations only
// need the right calling convention and arity.
void* FUN_007b8550(void* p);                                            // ctor
void  FUN_007b9420(Job* self, int v);
void  FUN_007b9510(Job* self, RectID* a, RectID* b);
void  FUN_007b9690(Job* self, RectID* a);
void  FUN_007b9750(Job* self, Job* other);
void  FUN_007b3a30(Job* self, int idx, float* v);
void  FUN_007b27a0(Job* self, float* v);
void  FUN_007b27e0(Job* self, int a, int b, int c, int d, int e);
void  FUN_007b2820(Job* self, int* p, int* q, int* r, int* s, float f);
void  FUN_00572660(void* self, Job* p);                                 // refcount ctor
Job*  AllocJob();                                                       // 0x13eb8a4 "Graphics" alloc

// EASTL allocator_allocate(0,0,0,0,"Graphics",0xe4)
Job* AllocJob()
{
    return (Job*)FUN_007b8550(0);
}

void cThumbnailManager::InitPostProcessEffect(int stage, bool bFlag, RectID* outRect,
                                              bool bFlag2, float f1, float f2, RectID* inRect)
{
    Job* job = 0;
    Job* other = 0;
    RectID tmp;

    switch (stage) {
    case 1:
        // Create a fullsize gradient job and add the background filter.
        job = AllocJob();
        if (job) {
            FUN_007b9420(job, 0);
            job->m0c = 0x46;
            job->mRect1 = mThumbRectID;
            tmp.mPageID = 0x3f4ccccd; tmp.mAllocID = 0x3f000000;
            job->mRect2 = mThumbRectID;
            (void)tmp;
        }
        outRect = outRect; // out
        break;

    case 2:
        job = AllocJob();
        if (job) {
            FUN_007b9420(job, 0);
            job->m0c = 0x46;
            job->mRect1 = mThumbRectID;
            job->mRect2 = mThumbRectID;
        }
        break;

    case 5: {
        // Threshold pipeline: create threshold/fullsize temp RTTs + filter jobs.
        RectID r1, r2;
        IRTTManager* mgr = mRTTMgr;
        (void)mgr; (void)r1; (void)r2;
        job = AllocJob();
        other = AllocJob();
        break;
    }

    case 6:
    case 7:
    case 8:
    case 9: {
        // Post-process effect chain.
        if (!bFlag) return;
        job = AllocJob();
        if (job) {
            FUN_007b9420(job, 0);
            if (!bFlag2) { job->m0c = 0xfa800f3; }
            else         { job->m0c = (int)0x88549f64; }
            job->mRect1 = (stage == 7) ? mThumbRectID : mBlurThumbRectID1;
            FUN_007b9750(job, outRect ? (Job*)outRect : job);
            if (stage == 6) {
                other = AllocJob();
                if (other) { FUN_007b9420(other, 0); FUN_007b9690(other, &mThumbRectID); }
                (void)inRect;
            }
        }
        break;
    }

    default:
        return;
    }

    if (job) job->Release();
}
