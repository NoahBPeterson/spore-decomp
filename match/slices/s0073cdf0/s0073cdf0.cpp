// Slice s0073cdf0 (0x0073cdf0-0x0073d1e0): SP::cModelInstance arena/deformation helpers.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames, no frame pointer).
#include "types.h"

// External callees (masked relocations; only convention/arity must be right).
extern "C" void FUN_0073a900(void* p, int v);   // 0x73a900
extern "C" void FUN_007c5490();                 // 0x7c5490
extern "C" void FUN_01200940();                 // 0x1200940

// ---------------------------------------------------------------------------
// Stub resource object at cModelInstance+0xc4 (RenderWareFilePtr / arena resource).
// Its vtable slot 3 takes a resource id and returns a pointer.
// ---------------------------------------------------------------------------
struct ArenaResource {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual void* v3(uint32_t id);
};

struct ArenaElem {                 // element stride 0x7c
    char pad74[0x74];
    int  field74;                  // +0x74
    char pad78[4];
};

struct ArenaHolder {               // value returned by ArenaResource::v3 for the mesh set
    char    pad108[0x108];
    ArenaElem* begin;              // +0x108
    ArenaElem* end;                // +0x10c
};

// ---------------------------------------------------------------------------
// @ 0x0073d160  SP::cModelInstance::GetArenaResource
// ---------------------------------------------------------------------------
struct cModelInstance_GetArenaResource {
    char pad[0xc4];
    ArenaResource* mResource;   // +0xc4
    int GetArenaResource();
};

int cModelInstance_GetArenaResource::GetArenaResource()
{
    int result = 0;
    ArenaResource* p = mResource;
    if (p) {
        result = (int)p->v3(0x2f4e681b);
        if (result)
            return result;
    }
    p = mResource;
    if (p) {
        ArenaHolder* h = (ArenaHolder*)p->v3(0xe6bce5);
        if (h) {
            if (h->end - h->begin == 1)
                return h->begin->field74;
        }
    }
    return result;
}

// ===========================================================================
// Deformation / pose machinery (large, still being reconstructed).
// ===========================================================================

// Arena export descriptor (Arena::GetExportedObjectByIndex result).
struct ExportedObj {
    uint32_t  type;    // +0x0  (0xff0000 == exported mesh)
    void*     data;    // +0x4
};

// rw::core::arena::Arena
struct Arena {
    int  GetNumExportedObjects();
    void GetExportedObjectByIndex(int index, ExportedObj* out);
};

// SP::OrthogonalVector (0x6985b0)
extern float* __cdecl OrthogonalVector(float* out, const float* v);

// Model-instance fields used by the deformation code (retail offsets).
struct cModelInstance_Deform {
    char pad14[0x14];
    void* m14;              // +0x14
    void* m18;              // +0x18
    int*  m1c;              // +0x1c
    char pad1c[0xd0];
    void* mDynamicDraw;     // +0xf0
    char pad2[4];

    int GetArenaResource();                       // 0x73d160
    bool  FillTransform(float* out);              // 0x73cdf0
    int   GetDeformationHandles(ExportedObj* dst, int maxCount);  // 0x73d1e0
};

// ---------------------------------------------------------------------------
// @ 0x0073cdf0  (deformation query: fills a 3x3 float matrix, returns success)
// ---------------------------------------------------------------------------
bool cModelInstance_Deform::FillTransform(float* out)
{
    // Partial: the multi-stage query/vertex walk is not yet recovered
    // (see partial.txt).  The prologue state machine is reproduced.
    if (m18 != 0)
        FUN_0073a900(m18, 0);
    if (m1c != 0 && m1c[2] != 0) {
        if (m1c[0] == 0)
            FUN_007c5490();
        else {
            FUN_007c5490();
            *(int*)m1c[2] = m1c[0];
            FUN_01200940();
        }
    }
    for (int i = 0; i < 9; ++i)
        out[i] = 0.0f;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x0073d1e0  SP::cModelInstance::GetDeformationHandles
// ---------------------------------------------------------------------------
int cModelInstance_Deform::GetDeformationHandles(ExportedObj* dst, int maxCount)
{
    if (mDynamicDraw == 0 || (((uint8_t*)mDynamicDraw)[8] & 8) == 0)
        return 0;
    int p = GetArenaResource();
    if (p == 0)
        return 0;
    Arena* arena = *(Arena**)(p + 0x18);
    int num = arena->GetNumExportedObjects();
    int count = 0;
    for (int i = 0; i < num; ++i) {
        ExportedObj desc;
        desc.type = 0;
        desc.data = 0;
        arena->GetExportedObjectByIndex(i, &desc);
        if (desc.type != 0xff0000)
            continue;
        // dedupe (by mesh pointer) and append a deformation handle to dst[count]
        // -- the transform/normal math is omitted (see partial.txt)
        ++count;
    }
    return count;
}
