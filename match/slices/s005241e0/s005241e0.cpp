// Slice 13: nSPSkinner model-type helpers and the paint particle-tick callback.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

struct MT {
    int base;                                  // +0x00
    unsigned char GetResourceTypeFromModelType();  // 0x00526340
};
extern MT g_mt;                                // 0x015de470

struct Vec2Pair { int a; int b; };
struct PairVec { void push_back(const Vec2Pair& v); };   // 0x00525ff0

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

struct Model {
    int Get(int i);
    int GetChecked(int i);
};
struct Y {
    void AddPair(int a1, int a2);
};

// @ 0x005247b0
int Model::Get(int i)
{
    return i * 0x40 + g_mt.base;
}

// @ 0x00524870
void Y::AddPair(int a1, int a2)
{
    Vec2Pair local;
    local.a = a1;
    local.b = a2;
    ScratchSlots<2>();
    ((PairVec*)((char*)this + 0x94))->push_back(local);
}

// @ 0x005247d0
int Model::GetChecked(int i)
{
    int result;
    if (g_mt.GetResourceTypeFromModelType() != 0) {
        result = 0;
    } else {
        int thing = *(int*)((char*)this + 0x10);
        int* arr = *(int**)(thing + 0x1a4);
        int* slot = &arr[i];
        uint32_t raw = (uint32_t)*slot >> 0x10;
        uint32_t val;
        if (raw & 0x80000000u)
            val = (uint32_t)*(unsigned char*)(*(int*)(*(int*)((char*)this + 0x20) + 0x20) + (raw & 0x7fffffffu));
        else
            val = raw;
        if (val == 0xffffffffu)
            result = 0;
        else
            result = (int)val * 0x40 + g_mt.base;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x005248A0 nSPSkinner::cPaintSystem::ParticleTickJobCallback
//   Complete behavioural reconstruction (nonmatching, see nonmatching.txt): it
//   drains the brush-hit queue under a 4ms LimitStopwatch, ticks the particles
//   when they survive the time slice, and re-arms itself through the job's
//   Continuation() until the queue and the particle vector are both empty or
//   the vertex list exceeds 0x249f0 entries.  Same size and instruction stream
//   as the original; only the /Od stack-slot order (name-hash frame layout) and
//   a couple of /Od scheduling choices differ byte-for-byte.
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);

struct StopwatchSW {                                 // EA::Stopwatch, 0x18 bytes
    uint64_t mnStartTime;            // +0x00
    uint64_t mnTotalElapsedTime;     // +0x08
    int32_t  mnUnits;                // +0x10
    float    mfCyclesToUnits;        // +0x14
    StopwatchSW(int nUnits, bool bStartImmediately);                     // 0x0093a560
    static uint64_t GetStopwatchCycle()
    {
        int64_t nReturnValue;
        QueryPerformanceCounter(&nReturnValue);
        const uint64_t nCycle = (uint64_t)nReturnValue;
        return nCycle;
    }
};

struct LimitStopwatchSW : StopwatchSW {              // EA::LimitStopwatch, 0x20 bytes
    uint64_t mnEndTime;              // +0x18
    LimitStopwatchSW(int nUnits, uint32_t nLimit = 0, bool bStartImmediately = false)
        : StopwatchSW(nUnits, false) { SetTimeLimit(nLimit, bStartImmediately); }
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);          // 0x0093a480
    bool IsTimeUp() const { return (int64_t)(mnEndTime - GetStopwatchCycle()) < 0; }
};

struct PaintVertex { uint32_t mWords[7]; };          // 0x1c bytes
struct PaintBrushHit { uint32_t mWords[0x12]; };     // 0x48 bytes

struct PaintBrushHitQueue {                          // eastl::deque<PaintBrushHit,...>
    uint8_t mOpaque[0x14];
    bool empty();                                    // 0x00425430
    PaintBrushHit& front();                          // 0x00501e20
    void pop_front();                                // 0x005263f0
};

struct PaintVertexVec {                              // eastl::vector<Vertex> header, retail size 0x14
    PaintVertex* mpBegin;                            // +0x00
    PaintVertex* mpEnd;                              // +0x04
    PaintVertex* mpCapacity;                         // +0x08
    uint32_t mAllocator[2];                          // +0x0c
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
};

struct PaintListSW {                                 // nSPSkinner::cPaintList (0x54 bytes)
    PaintVertexVec     mVertices;                    // +0x00 (retail 0x14)
    uint8_t            mBatches[0x14];               // +0x14 (Batch = 0x18)
    PaintBrushHitQueue mBrushHitQueue;               // +0x28
    void ProcessBrushHit(const void* pMesh, const PaintBrushHit& hit);   // 0x00512840
};

struct PaintMaterialSW {                             // nSPSkinner::cPaintMaterial
    uint32_t      mPad0[2];
    PaintListSW*  mpPaintList;                       // +0x08
};

struct ParticleVec {                                 // eastl::vector<cPaintParticle>
    uint32_t mPad0[4];
    bool empty();                                    // 0x00526430
};

struct PaintSysCtx {                                 // nSPSkinner::cPaintSystem
    uint32_t         mPad00[3];                      // +0x00
    PaintMaterialSW* mpMaterial;                     // +0x0c
    void*            mpBakedMesh;                    // +0x10
    uint32_t         mPad14[10];                     // +0x14 .. +0x3c
    ParticleVec      mParticles;                     // +0x3c
    void Tick(LimitStopwatchSW& timer);              // 0x005202f0
};

struct JobSW {                                       // SP::cJob
    bool Continuation(void* pCallback, void* pArg);  // 0x0068f9f0
};

// The original re-arms the job with its own address; a direct reference to our
// same-section definition would keep our object address, so it is spelled as a
// VA-annotated extern the way the rest of the slice tree does it.
extern char g_fn5248a0[];                            // 0x005248a0

// @ 0x005248A0
bool __cdecl ParticleTickJobCallback(JobSW& job, void* pCtx)
{
    PaintSysCtx* sys = (PaintSysCtx*)pCtx;
    PaintListSW* list = sys->mpMaterial->mpPaintList;
    const void* mesh = sys->mpBakedMesh;
    int nLimit = 1;
    LimitStopwatchSW timer(4, (uint32_t)nLimit, true);

    while (!list->mBrushHitQueue.empty()) {
        if (timer.IsTimeUp())
            break;
        list->ProcessBrushHit(mesh, list->mBrushHitQueue.front());
        list->mBrushHitQueue.pop_front();
    }
    if (!sys->mParticles.empty()) {
        if (!timer.IsTimeUp())
            sys->Tick(timer);
    }
    if (sys->mParticles.empty() && list->mBrushHitQueue.empty())
        return true;
    if (list->mVertices.size() > 0x249f0u)
        return true;
    return job.Continuation(g_fn5248a0, pCtx);
}

// @ 0x005241e0 nSPSkinner::cPaintSystem::RebuildBones
//   1486-byte /Od rig-block rebuild: walks mpEditorSkinPart's cRigBlock chain
//   (mBlocks .. mBlocksEnd at +0x98), resolves each block's parent transform and
//   rebuilds the skinned mesh vertex/prim data (x87/SSE movss, imul idx,0x8c bone
//   table, block types 3 and 5).  NOT reconstructed within the compile budget --
//   honest entry skeleton only; see nonmatching.txt.
void FUN_005241e0(void* self) { (void)self; }
