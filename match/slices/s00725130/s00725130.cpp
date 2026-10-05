// Slice s00725130 — SP::cMeshSimplifier::CreateEdges (PDB candidate, caller-scored).
// Giant /O2 mesh-edge builder with EH. Reconstructed control-flow top end; the inner
// edge-hash/vector machinery is omitted (marked partial). See manifest/nonmatching/partial.
#include "types.h"

extern "C" {
    int  FUN_0071ddc0(void* p, int a, int b, int c, int d);
    int  FUN_0071e040(void* p, int idx, int id);
    void FUN_007249f0(void* p);
}

struct MeshContext {
    char  pad0[8];
    char* pNodeArray;   // +0x08
    char  pad_c[0x10];
    char* pMeshes;      // +0x1c
    char* pMeshesEnd;   // +0x20
};

// @ 0x00725130
void FUN_00725130(MeshContext* ctx)
{
    void* p = ctx;
    int a = FUN_0071ddc0(p, 1, 0, 3, 0xe);
    if (a < 0)
        return;

    int b = FUN_0071ddc0(p, 8, 0, 0, 0xe);
    if (b < 0) {
        b = FUN_0071ddc0(p, 0, 0, 0, 2);
        if (b < 0) {
            b = FUN_0071ddc0(p, 2, 0, 0, 0xe);
            if (b < 0) {
                b = FUN_0071ddc0(p, 0, 0, 0, 1);
                if (b < 0) {
                    FUN_007249f0(p);
                    return;
                }
            }
        }
    }

    // PARTIAL: the original then builds an edge table (FUN_00720070 / Memset32 of -1),
    // iterates the 0x8c mesh records (end - begin) / 0x8c, resolves per-triangle wedge
    // entries via FUN_0071e040 and the +0x14 index table, and finishes with a global
    // eastl::vector resize. That machinery is not reconstructed here.
    (void)a; (void)b;
    (void)ctx->pMeshesEnd;
}
