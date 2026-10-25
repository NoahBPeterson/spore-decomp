// Slice s0073cdf0 (0x0073cdf0-0x0073d1e0): SP::cModelInstance arena/deformation helpers.
// Region: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- (SSE scalar floats, EH frames, no frame pointer).
#include "types.h"
#include <math.h>
#include <intrin.h>

// External callees (masked relocations; only convention/arity must be right).
extern "C" void FUN_0073a900(void* p, int v);   // 0x73a900

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
// Deformation / pose machinery (arena-resource lookup, transform fill, handles).
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
// Deformation-query machinery (retail: a manager + a query record).
// ---------------------------------------------------------------------------

// Reference-counted object: vfptr at +0x00, refcount at +0x04.
struct IRefObj {
    virtual void Dtor(int flag);
};

// The query record handed to the reader's Get() and walked by Find().  Its destructor
// releases mObj (the retail code inlines the interlocked release at every exit).
struct DeformQuery {
    void* mObj;    // +0x00  owning object (ref-counted)
    int   m04;     // +0x04
    int   m08;     // +0x08
    int   m0c;     // +0x0c  component count, must be 3
    int   m10;     // +0x10
    int   m14;     // +0x14
    bool  Find(void* v, int count, int index, int a, int b);   // 0x73c290
    ~DeformQuery();
};

__forceinline DeformQuery::~DeformQuery()
{
    void* o = mObj;
    if (o != 0) {
        volatile long* rc = (volatile long*)((char*)o + 4);
        if (_InterlockedDecrement(rc) == 0) {
            _InterlockedExchange(rc, 1);
            if (o != 0)
                ((IRefObj*)o)->Dtor(1);
        }
    }
}

// Reader interface at cModelInstance+0x14; slot 2 fills a query record.
struct DeformReader {
    virtual void v0();
    virtual void v1();
    virtual bool Get(DeformQuery* q);
};

// The two callback objects stashed through cModelInstance+0x1c.
struct Mc1cTarget {
    void Notify();   // 0x007c5490
    void Commit();   // 0x01200940
};

// Hand-rolled vtable (the object's vfptr lives at +0x04, so it is called explicitly).
struct McVtbl { void* fn[4]; };
typedef void (__thiscall *McSlotFn)(void*);

// Fills idx[4] (vertex indices, pre-divided by 3) and w[4] (sample weights).
extern "C" bool FUN_0073c4b0(void* q, int index, int* idx, float* w);   // 0x73c4b0

// ---------------------------------------------------------------------------
// @ 0x0073cdf0  (deformation query: fills a 3x3 float matrix, returns success)
// ---------------------------------------------------------------------------
bool cModelInstance_Deform::FillTransform(float* out)
{
    if (m18 != 0)
        FUN_0073a900(m18, 0);

    int* p = m1c;
    if (p != 0 && p[2] != 0) {
        if (p[0] == 0) {
            ((Mc1cTarget*)p[2])->Notify();
        } else {
            McVtbl* vt = *(McVtbl**)((char*)p[0] + 4);
            ((McSlotFn)vt->fn[3])((void*)p[0]);
            *(int*)p[2] = p[0];
            ((Mc1cTarget*)p[2])->Commit();
        }
    }

    DeformQuery q;
    q.mObj = 0;
    q.m04 = -1;
    q.m08 = -1;
    q.m0c = 0;
    q.m10 = -1;
    q.m14 = 0;

    if (!((DeformReader*)m14)->Get(&q) || q.m0c != 3)
        return false;

    for (int i = 0; i < 9; ++i)
        out[i] = 0.0f;

    for (int i = 0; i < 3; ++i) {
        float v[3];
        if (!q.Find(v, 3, i, 1, -1))
            return false;

        int   idx[4];
        float w[4];
        if (FUN_0073c4b0(&q, i, idx, w)) {
            int base = *(int*)(*(int*)(*(int*)((char*)m18 + 8) + 8));
            float r0 = 0.0f, r1 = 0.0f, r2 = 0.0f;
            for (int k = 0; k < 4; ++k) {
                float* V = (float*)(base + idx[k] * 0x30);
                float ox = V[0] * v[0] + V[1] * v[1] + V[2] * v[2] + V[3];
                float oy = V[4] * v[0] + V[5] * v[1] + V[6] * v[2] + V[7];
                float oz = V[8] * v[0] + V[9] * v[1] + V[10] * v[2] + V[11];
                float ww = w[k];
                r0 += ox * ww;
                r1 += oy * ww;
                r2 += oz * ww;
            }
            out[3 * i + 0] = r0;
            out[3 * i + 1] = r1;
            out[3 * i + 2] = r2;
        } else {
            out[3 * i + 0] = v[0];
            out[3 * i + 1] = v[1];
            out[3 * i + 2] = v[2];
        }
    }

    return true;
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
