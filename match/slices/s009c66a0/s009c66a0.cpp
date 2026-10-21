// Slice s009c66a0 -- nSPCreatureAnim::creature_mesh_instance_data mesh bookkeeping:
// the mesh-instance copy / release helpers plus the eastl vector <-> raw-buffer
// bridge routines for the 0x30-byte "bone" element and the 0x14-byte body-mesh
// element.
//
//   009c66a0  CloneMeshInstance        (clone a mesh slot through its manager)
//   009c67e0  ReleaseRange             (release every element of [first,last))
//   009c6860  CopyRangeOut             (copy [first,last) to dest; return dest+cnt)
//   009c68f0  CopyRangeBackward        (copy [first,last) backwards into dest)
//   009c6970  FillRange                (fill [first,last) with copies of *src)
//   009c69f0  eastl::vector<bone>::erase
//   009c6a60  eastl::vector<bone>::insert_fill (n copies of *src)
//   009c6c30  MeshHandle::Clear        (drop handle + clear the embedded vector)
//   009c6c90  eastl::vector<bone>::resize
//   009c6d70  eastl::vector<body_mesh>::insert_fill (n copies of *src)
//
// Retail offsets are used throughout (the 2008 PDB predates this build).  The
// 0x14-byte element is a body mesh: three floats, a ref-counted model pointer
// (refcount at +0x40, virtual release at vtable +0x170) and a dword counter.
// The 0x30-byte element is a bone (12 floats, copied as 12 dwords).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char uint8;
typedef unsigned int  uint32;

// --------------------------------------------------------------- element types

struct RefCounted {
    void* vptr;         // +0x00
    int   f04;          // +0x04
    char  pad08[0x38];  // +0x08
    int   refCount;     // +0x40
};

// 0x14-byte body-mesh element.
struct body_mesh_data {
    float        x;         // +0x00
    float        y;         // +0x04
    float        z;         // +0x08
    RefCounted*  model;     // +0x0c
    uint32       modcount;  // +0x10
};

// 0x30-byte bone element.
struct bone {
    float m[12];
};

// Out-of-slice raw-buffer helpers (same object file; declared extern so this slice
// reuses the original's own routines).  Signatures follow the push sequences at the
// call sites.  Addresses in the comments.
bone* RawCopy30(const void* first, const void* last, void* dst);      // 0x009c5c80
void* RawFill30(void* dst, uint32 n, const void* src);                // 0x009c6830
void  RawMoveOut30(void* out, const void* a2, void* a3, void* a4,
                   const void* a5);                                   // 0x009c64c0
void  RawMoveOut14(void* out, const void* a2, void* a3, void* a4,
                   const void* a5);                                   // 0x009c6500
void  RawFill14(void* dst, uint32 n, const void* src);                // 0x009c6560
void  RawCopy14(const void* first, const void* last, void* dst);      // 0x009c65b0
void* RawDestroy14(const void* first, const void* last, void* dst);   // 0x009c6600
void  MoveDown30(void* dst, const void* src, const void* end);        // 0x00714f70
void  SetRange30(void* first, const void* last, const void* src);     // 0x00714850

void* EAAllocate(uint32 n, const char* tag, int a, int b, const char* file,
                 int line);                                          // 0x00f473a0
void  EADeallocate(void* p);                                         // 0x00f47380
void  BoneDefaultCtor(void* self);                                   // operator_new[] thunk 0x011e073e

// -------------------------------------------------------------------- helpers

// Drops one reference from a ref-counted model pointer.
static void ReleaseModel(RefCounted* obj)
{
    if (obj == 0)
        return;
    if (obj->refCount > 1) {
        --obj->refCount;
        return;
    }
    bool flag = (unsigned)obj->f04 >> 31;
    void (__stdcall *release)(RefCounted*, unsigned) =
        *(void (__stdcall **)(RefCounted*, unsigned))((char*)obj->vptr + 0x170);
    release(obj, (unsigned)flag);
}

// @ 0x009c67e0
// Releases every 0x14-byte element of [first,last).
void ReleaseRange(body_mesh_data* first, body_mesh_data* last)
{
    while (first < last) {
        if (first->model != 0)
            ReleaseModel(first->model);
        first = (body_mesh_data*)((char*)first + 0x14);
    }
}

// @ 0x009c6860
// Copies [first,last) to dest, adjusting ref counts, and returns the advanced
// destination.
body_mesh_data* CopyRangeOut(body_mesh_data* first, body_mesh_data* last,
                             body_mesh_data* dest)
{
    if (first == last)
        return dest;

    do {
        dest->x = first->x;
        dest->y = first->y;
        dest->z = first->z;

        RefCounted* src = first->model;
        RefCounted* old = dest->model;
        if (old != src) {
            if (src != 0)
                ++src->refCount;
            dest->model = src;
            if (old != 0)
                ReleaseModel(old);
        }
        dest->modcount = first->modcount;

        first = (body_mesh_data*)((char*)first + 0x14);
        dest  = (body_mesh_data*)((char*)dest + 0x14);
    } while (first != last);

    return dest;
}

// @ 0x009c68f0
// Copies [first,last) backwards into dest (walking from the end).
body_mesh_data* CopyRangeBackward(body_mesh_data* dst, body_mesh_data* first,
                                  body_mesh_data* last)
{
    if (last == first)
        return dst;

    do {
        dst  = (body_mesh_data*)((char*)dst - 0x14);
        last = (body_mesh_data*)((char*)last - 0x14);

        dst->x = last->x;
        dst->y = last->y;
        dst->z = last->z;

        RefCounted* src = last->model;
        RefCounted* old = dst->model;
        if (old != src) {
            if (src != 0)
                ++src->refCount;
            dst->model = src;
            if (old != 0)
                ReleaseModel(old);
        }
        dst->modcount = last->modcount;
    } while (last != first);

    return dst;
}

// @ 0x009c6970
// Fills [first,last) with copies of *src.
void FillRange(body_mesh_data* first, body_mesh_data* last,
               const body_mesh_data* src)
{
    if (first == last)
        return;

    do {
        first->x = src->x;
        first->y = src->y;
        first->z = src->z;

        RefCounted* o = src->model;
        RefCounted* old = first->model;
        if (old != o) {
            if (o != 0)
                ++o->refCount;
            first->model = o;
            if (old != 0)
                ReleaseModel(old);
        }
        first->modcount = src->modcount;

        first = (body_mesh_data*)((char*)first + 0x14);
    } while (first != last);
}

// --------------------------------------------------------- eastl vector<bone>

struct BoneVector {
    bone* mpBegin;     // +0x00
    bone* mpEnd;       // +0x04
    bone* mpCapacity;  // +0x08

    bone* erase(bone* first, bone* last);
    void  insert_fill(bone* pos, uint32 n, const bone* src);
    void  resize(uint32 n);
};

// @ 0x009c69f0
// eastl::vector<bone>::erase(first,last): shifts [last,end) down over [first,last)
// and returns first.
bone* BoneVector::erase(bone* first, bone* last)
{
    bone* end = mpEnd;
    bone* dst = first;
    bone* src = last;

    if (last != end) {
        do {
            *dst = *src;
            dst = (bone*)((char*)dst + 0x30);
            src = (bone*)((char*)src + 0x30);
        } while (src != end);
    }

    int n = (int)((char*)first - (char*)last) / 0x30;
    mpEnd = (bone*)((char*)mpEnd + n * 0x30);
    return first;
}

// @ 0x009c6a60
// eastl::vector<bone>::insert_fill(pos, n, src): inserts n copies of *src at pos.
void BoneVector::insert_fill(bone* pos, uint32 n, const bone* src)
{
    uint32 cap = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x30);
    if (cap < n) {
        uint32 used = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x30);
        uint32 want = used * 2;
        if (used == 0)
            want = 1;
        uint32 newCap = used + n;
        if (newCap < want)
            newCap = want;
        bone* buf = 0;
        if (newCap != 0)
            buf = (bone*)EAAllocate(newCap * 0x30, "EASTL", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                     0xd1);
        bone* mid = RawCopy30(mpBegin, pos, buf);
        RawFill30(mid, n, src);
        bone* newEnd = RawCopy30(pos, mpEnd, (bone*)((char*)mid + n * 0x30));
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            EADeallocate(mpBegin);
        mpBegin = buf;
        mpEnd = newEnd;
        mpCapacity = (bone*)((char*)buf + newCap * 0x30);
        return;
    }

    if (n == 0)
        return;

    bone local[1];
    local[0] = *src;                     // snapshot *src (12 dwords)

    uint32 tail = (uint32)(((char*)mpEnd - (char*)pos) / 0x30);
    if (n < tail) {
        bone* dst = (bone*)((char*)mpEnd - n * 0x30);
        RawMoveOut30(0, dst, mpEnd, mpEnd, 0);
        mpEnd = (bone*)((char*)mpEnd + n * 0x30);
        MoveDown30(pos, dst, mpEnd);
        SetRange30(pos, (bone*)((char*)pos + n * 0x30), local);
        return;
    }

    uint32 extra = n - tail;
    RawFill30(mpEnd, extra, local);
    mpEnd = (bone*)((char*)mpEnd + extra * 0x30);
    RawMoveOut30(0, pos, mpEnd, mpEnd, 0);
    mpEnd = (bone*)((char*)mpEnd + tail * 0x30);
    SetRange30(pos, mpEnd, local);
}

// @ 0x009c6c90
// eastl::vector<bone>::resize(n).
void BoneVector::resize(uint32 n)
{
    uint32 used = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x30);
    if (used < n) {
        char buf[0x30];
        BoneDefaultCtor(buf);
        insert_fill(mpEnd, n - used, (bone*)buf);
        return;
    }
    erase((bone*)((char*)mpBegin + n * 0x30), mpEnd);
}

// @ 0x009c6c30
// Drops the ref-counted handle at +0x00 and destroys the bone vector at +0x08.
// A member of the small handle object (this = ecx).
struct MeshHandle {
    RefCounted* mObj;      // +0x00
    uint32      mCount;    // +0x04
    BoneVector  mVec;      // +0x08

    void Clear();
};

void MeshHandle::Clear()
{
    RefCounted* obj = mObj;
    if (obj != 0) {
        mObj = 0;
        ReleaseModel(obj);
    }
    mCount = 0;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
}

// --------------------------------------------------- eastl vector<body_mesh>

struct BodyMeshVector {
    body_mesh_data* mpBegin;     // +0x00
    body_mesh_data* mpEnd;       // +0x04
    body_mesh_data* mpCapacity;  // +0x08

    void insert_fill(body_mesh_data* pos, uint32 n, const body_mesh_data* src);
};

// @ 0x009c6d70
// eastl::vector<body_mesh_data>::insert_fill(pos, n, src).
void BodyMeshVector::insert_fill(body_mesh_data* pos, uint32 n,
                                 const body_mesh_data* src)
{
    uint32 cap = (uint32)(((char*)mpCapacity - (char*)mpBegin) / 0x14);
    if (cap < n) {
        uint32 used = (uint32)(((char*)mpEnd - (char*)mpBegin) / 0x14);
        uint32 want = used * 2;
        if (used == 0)
            want = 1;
        uint32 newCap = used + n;
        if (newCap < want)
            newCap = want;
        body_mesh_data* buf = 0;
        if (newCap != 0)
            buf = (body_mesh_data*)EAAllocate(newCap * 0x14, "EASTL", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                     0xd1);
        RawCopy14(mpBegin, pos, buf);
        RawFill14((body_mesh_data*)((char*)buf + n * 0x14), 0, 0);
        RawCopy14(pos, mpEnd, (body_mesh_data*)((char*)buf + n * 0x14));
        RawDestroy14(mpBegin, pos, 0);
        if (mpBegin != 0 && *(int*)((char*)mpBegin - 4) != 0)
            EADeallocate(mpBegin);
        mpEnd = (body_mesh_data*)((char*)buf + n * 0x14 +
                                  ((char*)mpEnd - (char*)pos));
        mpBegin = buf;
        mpCapacity = (body_mesh_data*)((char*)buf + newCap * 0x14);
        return;
    }

    if (n == 0)
        return;

    body_mesh_data local = *src;
    if (local.model != 0)
        ++local.model->refCount;

    uint32 tail = (uint32)(((char*)mpEnd - (char*)pos) / 0x14);
    if (n < tail) {
        body_mesh_data* dst = (body_mesh_data*)((char*)mpEnd - n * 0x14);
        RawMoveOut14(0, dst, mpEnd, mpEnd, 0);
        mpEnd = (body_mesh_data*)((char*)mpEnd + n * 0x14);
        CopyRangeBackward(mpEnd, dst, mpEnd);
        FillRange(pos, (body_mesh_data*)((char*)pos + n * 0x14), &local);
    } else {
        uint32 extra = n - tail;
        FillRange(mpEnd, (body_mesh_data*)((char*)mpEnd + extra * 0x14), &local);
        mpEnd = (body_mesh_data*)((char*)mpEnd + extra * 0x14);
        RawMoveOut14(0, pos, mpEnd, mpEnd, 0);
        mpEnd = (body_mesh_data*)((char*)mpEnd + tail * 0x14);
        FillRange(pos, mpEnd, &local);
    }

    ReleaseModel(local.model);
}

// --------------------------------------------------------- clone mesh instance

// The object carried in the mesh slot: a ref-counted pointer at +0x04 (used as a
// transform source and re-owned here), a transform at +0x08 and a bag of counters.
struct MeshObj {
    void*           field0;     // +0x00
    unsigned        flags;      // +0x04  (low 14 bits preserved)
    char            xform[0x44];// +0x08  (cSPTransform)
    unsigned        f4c;        // +0x4c
    unsigned        f50;        // +0x50
    unsigned        f54;        // +0x54
    float           f58;        // +0x58
    unsigned char   f5c;        // +0x5c
    char            pad5d[0x64 - 0x5d];
    RefCounted*     f64;        // +0x64
    unsigned short  f68;        // +0x68
    char            pad6a[2];
    float           f6c;        // +0x6c
    unsigned        f70;        // +0x70
    unsigned        f74;        // +0x74
    unsigned        f78;        // +0x78
    unsigned        f7c;        // +0x7c
    unsigned        f80;        // +0x80
    unsigned        f84;        // +0x84
};

void* TransformAssign(void* dst, const void* src);              // 0x00537dc0

// @ 0x009c66a0
// Clones the mesh slot `src` through `mgr`: reads the source transform through the
// owner's vtable slot 0x50, asks the manager (slot 0x0c) for a fresh slot, copies
// the transform state and hands the new instance back.
MeshObj* CloneMeshInstance(MeshObj* src, void* mgr, unsigned* out)
{
    if (src == 0 || mgr == 0)
        return 0;

    void*  owner = src->field0;
    void** v = *(void***)owner;
    int local_14;
    int local_1c;
    ((void (__thiscall*)(void*, int*, int*))v[0x50 / 4])(owner, &local_14, &local_1c);

    MeshObj* dst = (MeshObj*)((void* (__thiscall*)(void*, int, int, int))
        (*(void***)mgr)[0x0c / 4])(mgr, local_14, local_1c, 2);

    TransformAssign(dst->xform, src->xform);
    dst->flags = (dst->flags & 0xffffc000u) | (src->flags & 0x3fffu);

    dst->f4c = src->f4c;
    dst->f50 = src->f50;
    dst->f54 = src->f54;
    dst->f58 = src->f58;
    dst->f5c = src->f5c;

    RefCounted* n = src->f64;
    RefCounted* o = dst->f64;
    if (n != o) {
        if (n != 0)
            ((void (__thiscall*)(RefCounted*))(*(void***)n)[0])(n);
        dst->f64 = n;
        if (o != 0)
            ((void (__thiscall*)(RefCounted*))(*(void***)o)[1])(o);
    }

    dst->f7c = src->f7c;
    dst->f80 = src->f80;
    dst->f84 = src->f84;
    dst->f70 = src->f70;
    dst->f74 = src->f74;
    dst->f78 = src->f78;
    dst->f6c = src->f6c;

    ((void (__thiscall*)(MeshObj*, int))(*(void***)dst)[0x16c / 4])(dst, 0);

    int got = ((int (__thiscall*)(MeshObj*, int))(*(void***)src->field0)[0xa8 / 4])(src, -1);
    if (got != 0)
        ((void (__thiscall*)(void*, MeshObj*, int, int))
            (*(void***)mgr)[0xa4 / 4])(mgr, dst, got, -1);

    *out = (unsigned)dst->f68 - 1;
    return dst;
}
