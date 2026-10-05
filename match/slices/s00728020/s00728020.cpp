// Slice s00728020 — SP::cMeshSimplifier mesh-clustering entry points.
//   00728020 Simplify            (reconstructed)
//   other functions              (partial skeletons)
#include "types.h"

// Per-mesh record, stride 0x8c.
struct MeshRec { char pad[0x8c]; };
struct MeshCtx {
    char     pad0[0x1c];
    MeshRec* begin;   // +0x1c
    MeshRec* end;     // +0x20
};

extern "C" {
    void FUN_00726c20(void* p, float f, int one, void* p4);   // 0x726c20
    void FUN_00725130(void* p);                               // 0x725130
    void FUN_00735a90(void* p);                               // 0x735a90
    void FUN_00737ef0(void* p);                               // 0x737ef0
    void FUN_00921df0(void* ms);                              // EA::Thread::ThreadSleep
}

// @ 0x00728020  SP::cMeshSimplifier::Simplify
void FUN_00728020(MeshCtx* ctx, float f, int mode, void* p4)
{
    if (ctx->end - ctx->begin != 0) {
        FUN_00726c20(ctx, f, 1, p4);
        int z = 0;
        FUN_00921df0(&z);
        FUN_00725130(ctx);
        z = 0;
        FUN_00921df0(&z);
        FUN_00735a90(ctx);
        z = 0;
        FUN_00921df0(&z);
        FUN_00737ef0(ctx);
        z = 0;
        FUN_00921df0(&z);
    }
}

// @ 0x007280b0  (PARTIAL)
void FUN_007280b0(void* self, void* param_2, int param_3, int param_4, int param_5)
{
    (void)self; (void)param_2; (void)param_3; (void)param_4; (void)param_5;
}

// @ 0x007281d0  `anonymous namespace'::cUVGenJobInfo::~cUVGenJobInfo  (PARTIAL)
void FUN_007281d0(void* self)
{
    (void)self;
}

// @ 0x00728330  eastl::vector<SP::cClusterInfo, eastl::sp_vector_allocator>::resize  (PARTIAL)
void FUN_00728330(void* self, unsigned n)
{
    (void)self; (void)n;
}

// @ 0x00728400  (PARTIAL)
void FUN_00728400(void* self, unsigned a, unsigned b)
{
    (void)self; (void)a; (void)b;
}

// @ 0x007285a0  SP::cMeshClusterer::CreateClusterInfo  (PARTIAL)
void FUN_007285a0(void* self)
{
    (void)self;
}

// @ 0x007289a0  (PARTIAL)
void FUN_007289a0(void* self)
{
    (void)self;
}

// @ 0x00728af0  SP::cMeshClusterer::Cluster  (PARTIAL)
void FUN_00728af0(void* self, void* meshData, int n)
{
    (void)self; (void)meshData; (void)n;
}
