// Slice s0073cdf0 (0x0073cdf0-0x0073d1e0): SP::cModelInstance arena/deformation helpers.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE scalar floats, EH frames, no frame pointer).
#include "types.h"
#include <math.h>

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

// rw::BaseResourceDescriptor (0x6c0fa0 ctor {0,1}; 0xc2e4e0 is its empty dtor).
struct BaseResourceDescriptor {
    uint32_t m_size, m_alignment;
    BaseResourceDescriptor();         // 0x006c0fa0
    ~BaseResourceDescriptor();        // 0x00c2e4e0
};
struct RwResource { uint32_t a, b, c, d; };

// rw::core::arena::ArenaExportedObject (Arena::GetExportedObjectByIndex result).
struct ExportedObj {
    uint32_t  type;    // +0x0  (0xff0000 == exported mesh)
    void*     data;    // +0x4
    RwResource resource;               // +0x8
    BaseResourceDescriptor desc[4];    // +0x18
    ExportedObj() {
        resource.a = 0; resource.b = 0; resource.c = 0; resource.d = 0;
        type = 0; data = 0;
        desc[0].m_size = 0; desc[0].m_alignment = 1;
    }
};

// rw::core::arena::Arena
struct Arena {
    int  GetNumExportedObjects();                                  // 0x011e23a0
    void GetExportedObjectByIndex(int index, ExportedObj* out);   // 0x011e28e0
};

// SP::OrthogonalVector (0x6985b0)
extern float* __cdecl OrthogonalVector(float* out, const float* v);   // 0x006985b0

// Exported mesh record the arena hands back (doubles on disk, floats in the handle).
struct ExportedMesh {
    uint32_t id;           // +0x0
    uint32_t pad4;
    double   d[6];         // +0x8 .. +0x30
    float    f38;          // +0x38
};

// One deformation handle (stride 0x5c).
struct DeformHandle {
    int       mZero;       // +0x0
    uint16_t  mFlags;      // +0x4
    uint16_t  mVersion;    // +0x6
    float     mPos[3];     // +0x8
    uint32_t  pad14;
    float     mRot[9];     // +0x18
    uint32_t  mId;         // +0x3c
    float     mP0[3];      // +0x40
    float     mP1[3];      // +0x4c
    float     mF58;        // +0x58
};

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
    int   GetDeformationHandles(DeformHandle* dst, int maxCount);  // 0x73d1e0
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
int cModelInstance_Deform::GetDeformationHandles(DeformHandle* dst, int maxCount)
{
    if ((((uint8_t*)mDynamicDraw)[8] & 8) == 0)
        return 0;
    int p = GetArenaResource();
    if (p == 0)
        return 0;
    Arena* arena = *(Arena**)(p + 0x18);
    int count = 0;
    int num = arena->GetNumExportedObjects();
    for (int i = 0; i < num; ++i) {
        ExportedObj obj;
        arena->GetExportedObjectByIndex(i, &obj);
        if (obj.type != 0xff0000)
            continue;
        ExportedMesh* m = (ExportedMesh*)obj.data;
        int j = 0;
        for (; j < count; ++j)
            if (dst[j].mId == m->id)
                break;
        if (j < count)
            continue;
        if (count >= maxCount)
            continue;
        DeformHandle* h = &dst[j];
        h->mId = m->id;
        h->mZero = 0;
        struct V3 { float x, y, z; };
        V3 a0; a0.x = (float)m->d[0]; a0.y = (float)m->d[1]; a0.z = (float)m->d[2];
        *(V3*)h->mP0 = a0;
        V3 a1; a1.x = (float)m->d[3]; a1.y = (float)m->d[4]; a1.z = (float)m->d[5];
        *(V3*)h->mP1 = a1;
        h->mF58 = m->f38;

        float org[3] = { h->mP0[0], h->mP0[1], h->mP0[2] };
        float vx = h->mP1[0] - h->mP0[0];
        float vy = h->mP1[1] - h->mP0[1];
        float vz = h->mP1[2] - h->mP0[2];
        if (vx * vx + vy * vy + vz * vz < 0.001f) {
            vx = 1.0f; vy = 0.0f; vz = 0.0f;
        }
        float len = (float)sqrt((double)(vz * vz + (vx * vx + vy * vy)));
        float inv = 1.0f / len;
        float n[3] = { vx * inv, vy * inv, vz * inv };

        float tmp[3];
        float* o = OrthogonalVector(tmp, n);
        float ux = o[0], uy = o[1], uz = o[2];
        float ulen = (float)sqrt((double)((ux * ux + uy * uy) + uz * uz));
        float uinv = 1.0f / ulen;
        ux *= uinv; uy *= uinv; uz *= uinv;

        float rot[9];
        rot[0] = n[0]; rot[1] = n[1]; rot[2] = n[2];
        rot[3] = ux;   rot[4] = uy;   rot[5] = uz;
        rot[6] = n[1] * uz - n[2] * uy;
        rot[7] = n[2] * ux - uz * n[0];
        rot[8] = uy * n[0] - n[1] * ux;

        h->mFlags |= 4;
        h->mVersion += 1;
        h->mPos[0] = org[0]; h->mPos[1] = org[1]; h->mPos[2] = org[2];
        h->mFlags |= 2;
        h->mVersion += 1;
        for (int k = 0; k < 9; ++k)
            h->mRot[k] = rot[k];
        ++count;
    }
    return count;
}
