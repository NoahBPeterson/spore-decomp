// Slice s007249f0 — UV/chart connectivity builder (module : UV generation).
// Large optimized function with EH (try/catch around vector temporaries), built /O2.
// It walks the per-mesh 0x8c records, remaps triangle vertex indices into a compact
// index table via a per-vertex "region" table, then feeds the result to the chart
// builder (FUN_007201d0) and FindPrimitives.
#include "types.h"

// ---------------------------------------------------------------------------
// callees (real addresses masked by relocation; declarations only need the
// right shape to reproduce the calls)
// ---------------------------------------------------------------------------
extern "C" {
    int   FUN_0071ddc0(void* p, int a, int b, int c, int d);   // 0x71ddc0
    int   FUN_0071e040(void* p, int idx, int id);              // 0x71e040
    void  FUN_004cd3c0(void* vec, int n);                      // 0x4cd3c0 (vector<int>::resize)
    void* FUN_00f473a0(unsigned n, const char* name, int f, int df, const char* file, int line); // EA alloc
    void  FUN_00f47380(void* p);                               // EASTL deallocate
    void  FUN_004cea40(void* end, int n, void* tag);           // vector<int>::DoInsertValues
    void  FUN_007201d0(void* desc, void* mesh);
    void  FUN_004558a0(void* vec, void* pos, void* val);      // vector<unsigned>::DoInsertValue
    void  FUN_0071ee10(void* p, void* out, int idx, int a, int b); // SP::FindPrimitives
    void  FUN_00921df0(void* ms);                              // EA::Thread::ThreadSleep
    void  FUN_0011e0744(void* pos, int n, int val);            // vector<bool>::DoInsertValue
    void  FUN_0073a4b0(void* p);                               // vector<cQuadric>::resize
}

struct RefObj { virtual void AddRef(); virtual void Release(); };

// A 16-byte vertex wedge entry.
struct VertEntry {
    int      x;    // +0
    int      y;    // +4
    int16_t  fmt;  // +8   (4 = int region data, 2 = ushort region data)
    uint16_t stride;// +0xa (bytes between region entries)
    RefObj*  ref;  // +0xc
};

// Per-mesh record, stride 0x8c.
struct MeshRec {
    uint32_t  count0;    // +0x00
    uint16_t* pData;     // +0x04
    int16_t   fmt;       // +0x08
    uint16_t  stride;    // +0x0a
    RefObj*   ref1;      // +0x0c
    uint32_t  count1;    // +0x10
    int*      pIdxTable; // +0x14
    char      pad_18[0x2c];
    void*     pVertBase; // +0x44
    char      pad_48[0x44];
};

// The owning context.
struct MeshContext {
    char      pad0[8];
    char*     pNodeArray;   // +0x08 (stride 0x20)
    char      pad_c[0x10];
    char*     pMeshes;      // +0x1c
    char*     pMeshesEnd;   // +0x20
    char      pad_24[0xc];
    char*     pPrims;       // +0x30 (stride 0x14)
};

struct IntVec { int* mpBegin; int* mpEnd; int* mpCap; };

// @ 0x007249f0
void FUN_007249f0(MeshContext* ctx)
{
    char* p = (char*)ctx;
    int job = FUN_0071ddc0(p, 1, 0, 3, 0xe);
    if (job < 0)
        return;
    if (*(int*)(ctx->pNodeArray + job * 0x20 + 0xc) != 0)
        return;

    int meshCount = (int)(ctx->pMeshesEnd - ctx->pMeshes) / 0x8c;
    for (int mi = 0; mi < meshCount; ++mi) {
        int tri = FUN_0071e040(p, mi, job);
        if (tri < 0)
            continue;

        int    recOff = mi * 0x8c;
        char*  rec    = ctx->pMeshes + recOff;
        MeshRec* mr   = (MeshRec*)rec;

        // 16-byte wedge entry for triangle `tri`.
        int16_t    sub = *(int16_t*)((char*)mr->pIdxTable + tri * 4 + 2);
        VertEntry* src = (VertEntry*)((char*)mr->pVertBase + (int)sub * 0x10);
        VertEntry  ve  = *src;
        if (ve.ref)
            ve.ref->AddRef();

        uint32_t  count0 = mr->count0;
        uint16_t* data   = mr->pData;
        int16_t   fmt    = mr->fmt;
        uint16_t  stride = mr->stride;
        RefObj*   ref1   = mr->ref1;
        if (ref1)
            ref1->AddRef();

        IntVec idx;
        idx.mpBegin = idx.mpEnd = idx.mpCap = 0;
        uint32_t count = count0;
        uint32_t origCount = 0;

        if (data == 0) {
            count = mr->count1;
            origCount = count;
            FUN_004cd3c0(&idx, (int)count);
            for (uint32_t i = 0; i < count; ++i)
                idx.mpBegin[i] = (int)i;
        } else if (fmt == 4) {
            origCount = count;
            FUN_004cd3c0(&idx, (int)count);
            for (uint32_t i = 0; i < count; ++i)
                idx.mpBegin[i] = *(int*)((char*)data + i * stride);
        } else if (fmt == 2) {
            origCount = count;
            FUN_004cd3c0(&idx, (int)count);
            for (uint32_t i = 0; i < count; ++i)
                idx.mpBegin[i] = *(uint16_t*)((char*)data + i * stride);
        }

        // Compacted output index table, `count` uints (zeroed).
        uint32_t* out = 0;
        if (count != 0) {
            out = (uint32_t*)FUN_00f473a0(count * 4, "Graphics", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                    0xd1);
        }
        uint32_t* outEnd = out + count;
        for (uint32_t i = 0; i < count; ++i)
            out[i] = 0;

        int nTri = (int)count / 3;
        uint32_t written = 0;
        int triIdx = 0;

        if (ve.fmt == 4) {
            int*      pIdx = idx.mpBegin;
            uint32_t* pOut = out + 2;
            for (int t = 0; t < nTri; ++t) {
                // region ids of the three wedge vertices
                int r0 = *(int*)((char*)ve.y + (int)ve.stride * pIdx[0]);
                int r1 = *(int*)((char*)ve.y + (int)ve.stride * pIdx[1]);
                int r2 = *(int*)((char*)ve.y + (int)ve.stride * pIdx[2]);
                if (r0 == r1 || r1 == r2 || r2 == r0) {
                    pOut[-2] = written;
                    pOut[-1] = written;
                    pOut[0]  = written;
                } else {
                    pOut[-2] = written;
                    idx.mpBegin[triIdx] = pIdx[0];
                    pOut[-1] = written + 1;
                    idx.mpBegin[triIdx + 1] = pIdx[1];
                    pOut[0] = written + 2;
                    idx.mpBegin[triIdx + 2] = pIdx[2];
                    written += 3;
                    triIdx += 3;
                }
                if ((t & 0xfff) == 0) {
                    int zero = 0;
                    FUN_00921df0(&zero);
                }
                pIdx += 3;
                pOut += 3;
            }
        } else if (ve.fmt == 2) {
            int*      pIdx = idx.mpBegin;
            uint32_t* pOut = out + 2;
            for (int t = 0; t < nTri; ++t) {
                uint16_t r0 = *(uint16_t*)((char*)ve.y + (int)ve.stride * pIdx[0]);
                uint16_t r1 = *(uint16_t*)((char*)ve.y + (int)ve.stride * pIdx[1]);
                uint16_t r2 = *(uint16_t*)((char*)ve.y + (int)ve.stride * pIdx[2]);
                if (r0 == r1 || r1 == r2 || r2 == r0) {
                    pOut[-2] = written;
                    pOut[-1] = written;
                    pOut[0]  = written;
                } else {
                    pOut[-2] = written;
                    idx.mpBegin[triIdx] = pIdx[0];
                    pOut[-1] = written + 1;
                    idx.mpBegin[triIdx + 1] = pIdx[1];
                    pOut[0] = written + 2;
                    idx.mpBegin[triIdx + 2] = pIdx[2];
                    written += 3;
                    triIdx += 3;
                }
                if ((t & 0xfff) == 0) {
                    int zero = 0;
                    FUN_00921df0(&zero);
                }
                pIdx += 3;
                pOut += 3;
            }
        }

        if (written == origCount) {
            if (out && *(int*)((char*)out - 4) != 0)
                FUN_00f47380(out);
            if (idx.mpBegin && *(int*)((char*)idx.mpBegin - 4) != 0)
                FUN_00f47380(idx.mpBegin);
        } else {
            int have = (int)((char*)idx.mpEnd - (char*)idx.mpBegin) >> 2;
            if ((int)written > have) {
                int zero = 0;
                FUN_004cea40(idx.mpEnd, (int)written - have, &zero);
            } else {
                int* here = idx.mpBegin + written;
                FUN_0011e0744(here, (int)idx.mpEnd, 0);
                idx.mpEnd = (int*)((char*)idx.mpEnd + (((char*)idx.mpEnd - (char*)here) >> 2) * -4);
            }
            struct { int n; int16_t a, b; RefObj* r; } desc;
            desc.n = (int)((char*)idx.mpEnd - (char*)idx.mpBegin) >> 2;
            desc.a = 4; desc.b = 4; desc.r = 0;
            FUN_007201d0(&desc, ctx->pMeshes + recOff);

            // append `written` to a uint vector
            if (outEnd < outEnd) {
                // (empty else-branch as in original)
            } else {
                FUN_004558a0(outEnd, &written, 0);
            }

            int* prims = 0; int* primsEnd = 0; int pad = 0;
            FUN_0071ee10(p, &prims, mi, 0, -1);
            int np = (int)((char*)primsEnd - (char*)prims) >> 2;
            for (int i = 0; i < np; ++i) {
                char* prim = ctx->pPrims + prims[i] * 0x14;
                *(int*)(prim + 8)  = (int)out[*(int*)(prim + 8)];
                *(int*)(prim + 0xc) = (int)out[*(int*)(prim + 0xc)];
            }
            int zero = 0;
            FUN_00921df0(&zero);
            if (prims && *(int*)((char*)prims - 4) != 0)
                FUN_00f47380(prims);
            if (desc.r)
                desc.r->Release();
            if (out && *(int*)((char*)out - 4) != 0)
                FUN_00f47380(out);
            if (idx.mpBegin && *(int*)((char*)idx.mpBegin - 4) != 0)
                FUN_00f47380(idx.mpBegin);
        }

        if (ref1)
            ref1->Release();
        if (ve.ref)
            ve.ref->Release();
    }

    FUN_0073a4b0(p);
}
