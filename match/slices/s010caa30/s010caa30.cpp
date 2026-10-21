// Slice s010caa30 -- Havok 3.1 collision shapes and filters.
//   hkConvexTransformShape (convex wrapper), hkConvexPieceMeshShape (piece-mesh wrapper),
//   hkConvexListShape dtor, hkCollisionFilterList (filter combiner).
// Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"
#include <new>
#include <xmmintrin.h>

typedef unsigned char  hkUint8;
typedef unsigned short hkUint16;
typedef unsigned int   hkUint32;
typedef int            hkInt32;
typedef float          hkReal;

struct hkBool { hkUint8 m_bool; hkBool() {} hkBool(const hkBool& o) : m_bool(o.m_bool) {} };

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern unsigned long g_hkThreadMemoryTls;                        // 0x016e4174

// ------------------------------------------------------------------ Havok layout stubs
struct hkReferencedObject {
    void**   m_vptr;              // +0x0
    hkUint16 m_memSizeAndFlags;   // +0x4
    hkUint16 m_referenceCount;    // +0x6
};

struct hkShape : public hkReferencedObject { hkUint32 m_pad08; };  // size 0xc

struct hkShapeCollection : public hkShape {                      // size 0x10
    hkUint8 m_disableWelding;     // +0xc
    hkUint8 m_pad0d[3];
};

struct hkConvexShape : public hkShape { };

struct hkVector4 { float x, y, z, w; };

struct hkTransform {                                             // size 0x40
    float m_col[16];              // +0x00  (4 columns of hkVector4)
};

struct hkConvexTransformShape : public hkConvexShape {           // size 0x60
    hkUint32       m_pad0c;       // +0xc
    hkConvexShape* m_childShape;  // +0x10
    float          m_pad14[3];    // +0x14
    hkTransform    m_transform;   // +0x20
    float          m_pad60;       // +0x60

    void convertVertexIdsToVertices(const void* ids, int num, hkVector4* out);  // 0x010caa30
    void getFirstVertex(hkVector4& out);                                        // 0x010cadb0
    int  getCollisionSpheres(void* out);                                        // 0x010cae40
};

template<class T> struct hkArray {
    T*  m_data;                   // +0x0
    int m_size;                   // +0x4
    int m_capacityAndFlags;       // +0x8
};

struct hkConvexPieceStreamData : public hkReferencedObject {     // size 0x2c
    hkArray<hkUint32> m_convexPieceStream;              // +0x8
    hkArray<hkUint32> m_convexPieceOffsets;             // +0x14
    hkArray<hkUint32> m_convexPieceSingleTriangles;     // +0x20
};

struct hkAabb {                                                  // size 0x20
    hkVector4 m_min;              // +0x0
    hkVector4 m_max;              // +0x10
};

struct hkConvexPieceMeshShape : public hkShapeCollection {       // size 0x1c
    hkConvexPieceStreamData* m_convexPieceStream;   // +0x10
    hkShapeCollection*       m_displayMesh;         // +0x14
    hkReal                   m_radius;              // +0x18

    hkUint32 getNextKey(hkUint32 key);              // @ 0x010cb230
    void*    getChildShape(hkUint32 key, char (&storage)[0xc0]);  // @ 0x010cb250
    hkUint32 getCollisionFilterInfo(hkUint32 key);// @ 0x010cb490
    void     getAabb(const hkTransform&, float, hkAabb&);  // @ 0x010cb4d0
    void     calcStatistics(void* collector);       // @ 0x010cb6a0
    void*    scalarDeletingDtor(hkUint32 flags);    // @ 0x010cb630
};

struct hkCollisionFilter : public hkReferencedObject { hkUint32 m_pad[4]; };   // size 0x18

struct hkCollidable; struct hkCollisionInput; struct hkCdBody; struct hkShapeCollection;
struct hkShapeRayCastInput; struct hkWorldRayCastInput;

struct hkCollisionFilterList : public hkCollisionFilter {        // size 0x24
    hkArray<void*> m_collisionFilters;   // +0x18

    hkBool isCollisionEnabled(const hkCollidable&, const hkCollidable&);          // 0x010cb7b0
    hkBool isCollisionEnabled2(const hkCollisionInput&, const hkCdBody&,
                               const hkCollisionFilterList&, const hkShapeCollection&, hkUint32); // 0x010cb800
    hkBool isCollisionEnabled3(const hkShapeRayCastInput&, const hkShapeCollection&, hkUint32); // 0x010cb860
    hkBool isCollisionEnabled4(const hkWorldRayCastInput&, const hkCollidable&);   // 0x010cb8c0

    void dtor();                                                                    // 0x010cb9a0
};

void* g_hkMemoryInstance;              // hkMemory::s_instance @ 0x016e4178 (pointer)

struct hkConvexListShape : public hkShapeCollection {           // size 0x20
    hkArray<void*> m_childInfo;   // +0x10
    float m_minDistance;          // +0x1c

    void* scalarDeletingDtor(hkUint32 flags);   // @ 0x010cb760
};
// hkShapeCollection::getAabb view for a child shape (slot +0xa0 of the shape vtable).
struct hkShapeIface {
    virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
    virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
    virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
    virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31();
    virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35();
    virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void getAabb(const hkTransform&, float, hkAabb&);   // +0xa0
};

// -------- vtable views (only the slots reached by this slice are named)
// The hkShape vtable slot order used by the retail build.
struct hkShapeVtbl {
    virtual void   d00(); virtual void   d01(); virtual void   d02(); virtual void   d03();
    virtual void   d04(); virtual void   d05(); virtual void   d06(); virtual void   d07();
    virtual hkUint32 getFirstKey();                        // +0x20
    virtual hkUint32 getNextKey(hkUint32);                 // +0x24
    virtual void*  getChildShape(hkUint32);                // +0x28
    virtual hkUint32 getCollisionFilterInfo(hkUint32);     // +0x2c
    virtual void   getAabb(const hkTransform&, float, hkAabb&);  // +0x30
};

// hkConvexShape vtable as used by hkConvexTransformShape.
struct hkConvexShapeVtbl {
    virtual void   d00(); virtual void   d01(); virtual void   d02(); virtual void   d03();
    virtual void   d04(); virtual void   d05(); virtual void   d06(); virtual void   d07();
    virtual void   d08(); virtual void   d09(); virtual void   d10(); virtual void   d11();
    virtual int    getFirstVertex(hkVector4& out);                                  // +0x20
    virtual void   convertVertexIdsToVertices(const void* ids, int num, hkVector4* out); // +0x28
    virtual void   d14(); virtual void   d15();
    virtual int    getCollisionSpheres(void* out);                                  // +0x3c
};

// ------------------------------------------------------------------ externals
extern "C" void  hkShapeCollection_ctor(void* self);                             // 0x010e7fd0
struct hkShapeCollectionCtor { void ctor(); };
extern "C" void* hkConvexPieceShape_ctor(void* self, float radius);              // 0x010eb440
struct hkConvexListShapeBase { void baseDtor(); };
extern "C" void  hkThreadMemory_deallocateChunk(void* self, void* p, int n, int c); // 0x0107db10

// hkMemory::s_instance->vtable slot +0x14 == deallocate(ptr, sizeInBytes, align)
struct hkMemoryVtbl {
    virtual void  d00(); virtual void  d01(); virtual void  d02(); virtual void  d03();
    virtual void  d04();
    virtual void  deallocate(void* p, hkUint32 size, hkUint32 align);   // +0x14
};

// A hkReferencedObject-ish refcounted base whose dtor is `operator delete`-able.
struct RefObj {
    virtual void* dtor(hkUint32 flags);    // +0x0
    hkUint16     m_memSizeAndFlags;        // +0x4
    hkUint16     m_referenceCount;         // +0x6
};

// @ 0x010caa30
void hkConvexTransformShape::convertVertexIdsToVertices(const void* p1, int numIds, hkVector4* out)
{
    ((hkConvexShapeVtbl*)(*(void**)m_childShape))
        ->convertVertexIdsToVertices(p1, numIds, out);

    const float* m = m_transform.m_col;
    float m00 = m[0], m01 = m[1], m02 = m[2];
    float m10 = m[4], m11 = m[5], m12 = m[6];
    float m20 = m[8], m21 = m[9], m22 = m[10];
    float tx  = m[12], ty = m[13], tz = m[14];

    hkVector4* v = out;
    for (int i = 0; i < numIds; ++i) {
        float x = v[i].x, y = v[i].y, z = v[i].z;
        v[i].x = m00 * x + m10 * y + m20 * z + tx;
        v[i].y = m01 * x + m11 * y + m21 * z + ty;
        v[i].z = m02 * x + m12 * y + m22 * z + tz;
    }
}

// @ 0x010cadb0
void hkConvexTransformShape::getFirstVertex(hkVector4& out)
{
    hkVector4 v;
    ((hkConvexShapeVtbl*)(*(void**)m_childShape))->getFirstVertex(v);

    const float* m = m_transform.m_col;
    out.x = m[0] * v.x + m[4] * v.y + m[8]  * v.z + m[12];
    out.y = m[1] * v.x + m[5] * v.y + m[9]  * v.z + m[13];
    out.z = m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14];
    out.w = 0.0f;
}

// @ 0x010cae40
int hkConvexTransformShape::getCollisionSpheres(void* p1)
{
    hkConvexShape* child = m_childShape;
    hkConvexShapeVtbl* cv = (hkConvexShapeVtbl*)(*(void**)child);
    int num = cv->getCollisionSpheres(p1);
    (void)num;
    return (int)p1;
}

// @ 0x010cb210
void FUN_010cb210(void* self)
{
    if (self != 0) {
        ((hkShapeCollectionCtor*)self)->ctor();
        *(void**)self = (void*)0x014a416c;
    }
}

// @ 0x010cb230
hkUint32 hkConvexPieceMeshShape::getNextKey(hkUint32 key)
{
    hkConvexPieceStreamData* s = m_convexPieceStream;
    int next = (int)key + 1;
    if (next >= s->m_convexPieceOffsets.m_size + s->m_convexPieceSingleTriangles.m_size)
        next = -1;
    return (hkUint32)next;
}

// @ 0x010cb250
void* hkConvexPieceMeshShape::getChildShape(hkUint32 key, char (&storage)[0xc0])
{
    hkConvexShape* child = (hkConvexShape*)storage;
    void* shape = (child == 0) ? 0 : hkConvexPieceShape_ctor(child, m_radius);
    *(float*)((char*)shape + 0x18) = m_radius;

    hkConvexPieceStreamData* s = m_convexPieceStream;
    hkVector4* verts = (hkVector4*)(((uintptr_t)storage + 0x33) & ~(uintptr_t)0xf);

    if (key < (hkUint32)s->m_convexPieceOffsets.m_size) {
        void* iVar3 = ((void**)s->m_convexPieceStream.m_data)[key];
        int   iVar4 = ((int*)s->m_convexPieceOffsets.m_data)[(int)iVar3];
        int*  piVar1 = &((int*)s->m_convexPieceOffsets.m_data)[(int)iVar3];
        *(void**)((char*)shape + 0x1c) = piVar1 + 1;
        *(int*)((char*)shape + 0x20) = iVar4;
        *(void**)((char*)shape + 0x10) = verts;
        *(int*)((char*)shape + 0x14) = 0;
        if (0 < iVar4) {
            hkUint32 local_224 = 2;
            int local_21c = 0;
            do {
                int idx = ((int*)(*(void**)((char*)shape + 0x1c)))[local_21c];
                hkShape* childShape = m_displayMesh;
                hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)childShape);
                void* info = v->getChildShape((hkUint32)idx);
                if ((piVar1[piVar1[0] + (local_224 - 2) / 0x1f + 1] &
                     (1u << ((local_224 - 2) % 0x1f))) != 0) {
                    verts[0] = *(hkVector4*)((char*)info + 0x10);
                    verts += 1;
                    ++*(int*)((char*)shape + 0x14);
                }
                if ((piVar1[piVar1[0] + (local_224 - 1) / 0x1f + 1] &
                     (1u << ((local_224 - 1) % 0x1f))) != 0) {
                    verts[0] = *(hkVector4*)((char*)info + 0x20);
                    verts += 1;
                    ++*(int*)((char*)shape + 0x14);
                }
                if ((piVar1[piVar1[0] + local_224 / 0x1f + 1] &
                     (1u << (local_224 % 0x1f))) != 0) {
                    verts[0] = *(hkVector4*)((char*)info + 0x30);
                    verts += 1;
                    ++*(int*)((char*)shape + 0x14);
                }
                ++local_21c;
                local_224 += 3;
            } while (local_21c < *(int*)((char*)shape + 0x20));
            return shape;
        }
    } else {
        *(int*)((char*)shape + 0x20) = 1;
        void* puVar2 = (void*)((char*)s->m_convexPieceSingleTriangles.m_data +
                               (key - (hkUint32)s->m_convexPieceOffsets.m_size) * 4);
        *(void**)((char*)shape + 0x1c) = puVar2;
        *(void**)((char*)shape + 0x10) = verts;
        *(int*)((char*)shape + 0x14) = 3;
        hkShape* childShape = m_displayMesh;
        hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)childShape);
        void* info = v->getChildShape(*(hkUint32*)puVar2);
        verts[0] = *(hkVector4*)((char*)info + 0x10);
        verts[1] = *(hkVector4*)((char*)info + 0x20);
        verts[2] = *(hkVector4*)((char*)info + 0x30);
    }
    return shape;
}

// @ 0x010cb490
hkUint32 hkConvexPieceMeshShape::getCollisionFilterInfo(hkUint32 key)
{
    hkConvexPieceStreamData* s = m_convexPieceStream;
    hkUint32 info;
    if (key < (hkUint32)s->m_convexPieceOffsets.m_size) {
        int i = ((int*)s->m_convexPieceOffsets.m_data)[key];
        info = ((hkUint32*)s->m_convexPieceStream.m_data)[i + 1];
    } else {
        int i = (int)key - s->m_convexPieceOffsets.m_size;
        info = ((hkUint32*)s->m_convexPieceSingleTriangles.m_data)[i];
    }
    hkShapeCollection* display = m_displayMesh;
    hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)display);
    return v->getCollisionFilterInfo(info);
}

// @ 0x010cb4d0
void hkConvexPieceMeshShape::getAabb(const hkTransform& t, float radius, hkAabb& aabb)
{
    aabb.m_min.x = 3.402823466e+38f;
    aabb.m_min.y = 3.402823466e+38f;
    aabb.m_min.z = 3.402823466e+38f;
    aabb.m_min.w = 0.0f;
    aabb.m_max.w = 0.0f;
    aabb.m_max.x = -3.402823466e+38f;
    aabb.m_max.y = -3.402823466e+38f;
    aabb.m_max.z = -3.402823466e+38f;

    hkShapeVtbl* v = (hkShapeVtbl*)(*(void**)this);
    hkUint32 k = v->getFirstKey();
    if (k == 0xffffffffu) return;
    do {
        hkShapeVtbl* v2 = (hkShapeVtbl*)(*(void**)this);
        void* child = v2->getChildShape(k);
        hkAabb childAabb;
        ((hkShapeIface*)(*(void**)child))->getAabb(t, radius, childAabb);

        aabb.m_min.x = (aabb.m_min.x < childAabb.m_min.x) ? aabb.m_min.x : childAabb.m_min.x;
        aabb.m_min.y = (aabb.m_min.y < childAabb.m_min.y) ? aabb.m_min.y : childAabb.m_min.y;
        aabb.m_min.z = (aabb.m_min.z < childAabb.m_min.z) ? aabb.m_min.z : childAabb.m_min.z;
        aabb.m_min.w = (aabb.m_min.w < childAabb.m_min.w) ? aabb.m_min.w : childAabb.m_min.w;
        aabb.m_max.x = (aabb.m_max.x < childAabb.m_max.x) ? childAabb.m_max.x : aabb.m_max.x;
        aabb.m_max.y = (aabb.m_max.y < childAabb.m_max.y) ? childAabb.m_max.y : aabb.m_max.y;
        aabb.m_max.z = (aabb.m_max.z < childAabb.m_max.z) ? childAabb.m_max.z : aabb.m_max.z;
        aabb.m_max.w = (aabb.m_max.w < childAabb.m_max.w) ? childAabb.m_max.w : aabb.m_max.w;

        hkShapeVtbl* v3 = (hkShapeVtbl*)(*(void**)this);
        k = v3->getNextKey(k);
    } while (k != 0xffffffffu);
}

// @ 0x010cb630  hkConvexPieceMeshShape::`scalar deleting destructor'
void* hkConvexPieceMeshShape::scalarDeletingDtor(hkUint32 flags)
{
    hkConvexPieceMeshShape* self = this;
    RefObj* a = *(RefObj**)((char*)self + 0x14);
    *(void**)self = (void*)0x014a416c;
    if (a->m_memSizeAndFlags != 0) {
        if (--a->m_referenceCount == 0)
            a->dtor(1);
    }
    RefObj* b = *(RefObj**)((char*)self + 0x10);
    if (b->m_memSizeAndFlags != 0) {
        if (--b->m_referenceCount == 0)
            b->dtor(1);
    }
    *(void**)self = (void*)0x013ef094;
    if (flags & 1) {
        hkMemoryVtbl* m = *(hkMemoryVtbl**)&g_hkMemoryInstance;
        m->deallocate(self, self->m_memSizeAndFlags, 0x24);
    }
    return self;
}

// @ 0x010cb6a0
void hkConvexPieceMeshShape::calcStatistics(void* collector)
{
    struct Coll {
        virtual void report(const char*, int, void*);            // +0x0
        virtual void reportStat(const char*, int, void*, int, int);  // +0x4
        virtual void reportArray(const char*, int, void*, int, int); // +0x8
        virtual void d12(const char*, int, void*);               // +0xc
        virtual void d18();                                      // +0x18
    };
    Coll* c = (Coll*)collector;
    c->report("CvxPieceMesh", 1, this);

    hkConvexPieceStreamData* s = m_convexPieceStream;
    if (s->m_convexPieceStream.m_capacityAndFlags >= 0) {
        c->reportArray("Stream", 1, s->m_convexPieceStream.m_data,
                       s->m_convexPieceStream.m_size << 2,
                       s->m_convexPieceStream.m_capacityAndFlags << 2);
    }
    s = m_convexPieceStream;
    if (s->m_convexPieceSingleTriangles.m_capacityAndFlags >= 0) {
        c->reportArray("Stream", 1, s->m_convexPieceSingleTriangles.m_data,
                       s->m_convexPieceSingleTriangles.m_size << 2,
                       s->m_convexPieceSingleTriangles.m_capacityAndFlags << 2);
    }
    s = m_convexPieceStream;
    if (s->m_convexPieceOffsets.m_capacityAndFlags >= 0) {
        c->reportArray("Stream", 1, s->m_convexPieceOffsets.m_data,
                       s->m_convexPieceOffsets.m_size << 2,
                       s->m_convexPieceOffsets.m_capacityAndFlags << 2);
    }
    c->d12("DisplayMesh", 1, m_displayMesh);
    c->d18();
}

// @ 0x010cb760  hkConvexListShape::`scalar deleting destructor'
void* hkConvexListShape::scalarDeletingDtor(hkUint32 flags)
{
    *(void**)this = (void*)0x014a41c0;
    ((hkConvexListShapeBase*)this)->baseDtor();
    if (flags & 1) {
        hkMemoryVtbl* m = *(hkMemoryVtbl**)&g_hkMemoryInstance;
        m->deallocate(this, this->m_memSizeAndFlags, 0x24);
    }
    return this;
}

// hkCollisionFilterList::isCollisionEnabled overloads: fold over the contained filters, walking the
// array backwards, anding the results; short-circuit on the first "disabled".  Each overload is
// entered through a different interface subobject, so the visible member offsets differ.

// @ 0x010cb7b0
hkBool hkCollisionFilterList::isCollisionEnabled(const hkCollidable& a, const hkCollidable& b)
{
    struct F0 { virtual void d0(); virtual hkBool f(const hkCollidable&, const hkCollidable&); };
    int n = *(int*)((char*)this + 0x14);
    for (int i = n - 1; i >= 0; --i) {
        char* filter = ((char**)(*(void**)((char*)this + 0x10)))[i];
        hkBool r = ((F0*)((char*)filter + 8))->f(a, b);
        if (r.m_bool == 0) { hkBool out; out.m_bool = 0; return out; }
    }
    hkBool out; out.m_bool = 1; return out;
}

// @ 0x010cb800
hkBool hkCollisionFilterList::isCollisionEnabled2(const hkCollisionInput& a, const hkCdBody& b,
                                                  const hkCollisionFilterList& c,
                                                  const hkShapeCollection& d, hkUint32 e)
{
    struct F { virtual hkBool f(const hkCollisionInput&, const hkCdBody&,
                                const hkCollisionFilterList&, const hkShapeCollection&, hkUint32); };
    int n = *(int*)((char*)this + 0x10);
    for (int i = n - 1; i >= 0; --i) {
        char* filter = ((char**)(*(void**)((char*)this + 0xc)))[i];
        hkBool r = ((F*)((char*)filter + 0xc))->f(a, b, c, d, e);
        if (r.m_bool == 0) { hkBool out; out.m_bool = 0; return out; }
    }
    hkBool out; out.m_bool = 1; return out;
}

// @ 0x010cb860
hkBool hkCollisionFilterList::isCollisionEnabled3(const hkShapeRayCastInput& a,
                                                  const hkShapeCollection& b, hkUint32 c)
{
    struct F { virtual hkBool f(const hkShapeRayCastInput&, const hkShapeCollection&, hkUint32); };
    int n = *(int*)((char*)this + 0xc);
    for (int i = n - 1; i >= 0; --i) {
        char* filter = ((char**)(*(void**)((char*)this + 8)))[i];
        hkBool r = ((F*)((char*)filter + 0x10))->f(a, b, c);
        if (r.m_bool == 0) { hkBool out; out.m_bool = 0; return out; }
    }
    hkBool out; out.m_bool = 1; return out;
}

// @ 0x010cb8c0
hkBool hkCollisionFilterList::isCollisionEnabled4(const hkWorldRayCastInput& a, const hkCollidable& b)
{
    struct F0 { virtual void d0(); virtual hkBool f(const hkWorldRayCastInput&, const hkCollidable&); };
    int n = *(int*)((char*)this + 8);
    for (int i = n - 1; i >= 0; --i) {
        char* filter = ((char**)(*(void**)((char*)this + 4)))[i];
        hkBool r = ((F0*)((char*)filter + 0x14))->f(a, b);
        if (r.m_bool == 0) { hkBool out; out.m_bool = 0; return out; }
    }
    hkBool out; out.m_bool = 1; return out;
}

// @ 0x010cb9a0  hkCollisionFilterList::~hkCollisionFilterList
void hkCollisionFilterList::dtor()
{
    hkCollisionFilterList* self = this;
    *(void**)self = (void*)0x014a4210;
    *(void**)((char*)self + 8)  = (void*)0x014a4208;
    *(void**)((char*)self + 0xc) = (void*)0x014a4200;
    *(void**)((char*)self + 0x10) = (void*)0x014a41f8;
    *(void**)((char*)self + 0x14) = (void*)0x014a41f0;

    int n = *(int*)((char*)self + 0x1c);
    for (int i = 0; i < n; ++i) {
        RefObj* f = ((RefObj**)(*(void**)((char*)self + 0x18)))[i];
        if (f->m_memSizeAndFlags != 0) {
            if (--f->m_referenceCount == 0)
                f->dtor(1);
        }
    }
    if (*(int*)((char*)self + 0x20) >= 0) {
        void* mem = TlsGetValue(g_hkThreadMemoryTls);
        hkThreadMemory_deallocateChunk(mem, *(void**)((char*)self + 0x18),
                                       (*(int*)((char*)self + 0x20) & 0x3fffffff) << 2, 0x14);
    }
    *(void**)((char*)self + 0x14) = (void*)0x013ef82c;
    *(void**)((char*)self + 0x10) = (void*)0x013ef824;
    *(void**)((char*)self + 0xc)  = (void*)0x013ef824;
    *(void**)((char*)self + 8)   = (void*)0x013ef82c;
    *(void**)self = (void*)0x013ef094;
}
