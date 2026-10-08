// Slice s00b64470 -- mesh-group geometry collector (0x00b64a60, 2025 bytes).
//
// Given one layer slot of a model-with-layers object (the pointer passed in is the secondary-base
// subobject at object+8), picks the highest non-empty layer at or below `idx`, builds that layer's
// mesh groups through FUN_00b64870 (optionally replacing the result with the parent layer's when it
// has too few triangles), then flattens every mesh in the group into a vertex array (16-byte
// records, w = 0) and, if requested, a triangle-index array (12-byte records) with per-mesh vertex
// offsets applied. Scratch per-mesh offsets live in a Havok stack-allocated hkLocalArray<int>.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
extern "C" long __cdecl _InterlockedExchangeAdd(volatile long*, long);
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

void operator_delete__(void* p);   // 0x00f47380

struct __declspec(align(16)) Vector3 {
    float x, y, z;
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};

// ---- Havok 3.1 pieces ------------------------------------------------------------------------
extern unsigned long g_hkThreadMemoryTls;       // 0x016E4174

struct hkThreadMemory {
    virtual void vslot0();
    virtual void vslot1();
    virtual void vslot2();
    virtual void* onStackOverflow(int numBytes);         // +0x0c
    virtual void onStackUnderflow(void* p);               // +0x10
    uint32_t pad04[7];
    char* m_stackCurrent;     // +0x20
    char* m_stackPrev;        // +0x24
    char* m_stackBase;        // +0x28
    char* m_stackEnd;         // +0x2c
    void deallocateChunk(void* p, int numBytes, int memoryClass);          // 0x0107DB10

    static __forceinline hkThreadMemory& getInstance() { return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls); }
};
enum { HK_MEMORY_CLASS_ARRAY = 0x14 };

namespace hkArrayUtil {
void _reserveExactly(void* array, int numElem, int sizeElem);   // 0x0107f4a0
void _reserveMore(void* array, int sizeElem);                   // 0x0107f530
}

template <typename T> __forceinline T* hkAllocateStack(int n)
{
    hkThreadMemory& tm = hkThreadMemory::getInstance();
    int size = (n * (int)sizeof(T) + 0x10) & ~0xf;
    char* cur = tm.m_stackCurrent;
    char* next = cur + size;
    T* r;
    if ((uint32_t)next <= (uint32_t)tm.m_stackEnd) {
        tm.m_stackCurrent = next;
        r = (T*)cur;
    } else {
        r = (T*)tm.onStackOverflow(size);
    }
    return r;
}
template <typename T> __forceinline void hkDeallocateStack(T* p)
{
    hkThreadMemory& tm = hkThreadMemory::getInstance();
    tm.m_stackCurrent = (char*)p;
    if ((char*)p == tm.m_stackBase)
        tm.onStackUnderflow(p);
}

template <typename T> struct hkArray {
    enum { CAPACITY_MASK = 0x3fffffff, DONT_DEALLOCATE_FLAG = 0x80000000 };
    T* m_data;
    int m_size;
    int m_capacityAndFlags;

    __forceinline ~hkArray() { releaseMemory(); }
    __forceinline void releaseMemory()
    {
        if ((m_capacityAndFlags & DONT_DEALLOCATE_FLAG) == 0)
            hkThreadMemory::getInstance().deallocateChunk(m_data, getCapacity() * sizeof(T), HK_MEMORY_CLASS_ARRAY);
    }
    int getSize() const { return m_size; }
    int getCapacity() const { return m_capacityAndFlags & CAPACITY_MASK; }
    T& operator[](int i) { return m_data[i]; }
    __forceinline void reserveExactly(int n) { hkArrayUtil::_reserveExactly(this, n, sizeof(T)); }
    __forceinline void setSize(int n)
    {
        int cap = getCapacity();
        if (cap < n) {
            int c2 = cap * 2;
            reserveExactly(n < c2 ? c2 : n);
        }
        m_size = n;
    }
    __forceinline void pushBackXYZ0(const Vector3& v)
    {
        if (m_size == getCapacity())
            hkArrayUtil::_reserveMore(this, sizeof(T));
        T* e = &m_data[m_size++];
        e->x = v.x; e->y = v.y; e->z = v.z; e->w = 0.0f;
    }
    __forceinline void pushBack(const T& t)
    {
        if (m_size == getCapacity())
            hkArrayUtil::_reserveMore(this, sizeof(T));
        m_data[m_size++] = t;
    }
};

template <typename T> struct hkLocalArray : hkArray<T> {
    T* m_localMemory;
    __forceinline hkLocalArray(int capacity)
    {
        this->m_data = 0;
        this->m_size = 0;
        this->m_capacityAndFlags = (int)hkArray<T>::DONT_DEALLOCATE_FLAG;
        this->m_data = hkAllocateStack<T>(capacity);
        this->m_capacityAndFlags = capacity | hkArray<T>::DONT_DEALLOCATE_FLAG;
        m_localMemory = this->m_data;
    }
    __forceinline ~hkLocalArray() { hkDeallocateStack(m_localMemory); }
};

// ---- Spore mesh pieces -----------------------------------------------------------------------
struct __declspec(align(16)) Vec16 { float x, y, z, w; };
struct Tri { int a, b, c; };

struct cSPTransform { uint8_t d[0x38]; };
cSPTransform& translateTransform(cSPTransform& out, const cSPTransform& in, const cSPTransform& delta);   // 0x006271a0

struct Property {
    uint8_t pad[0x12];
    short type;                 // +0x12 (9 = int)
    int* GetInt();              // 0x0041e990
};

// Intrusive-ref target (mesh group): refcount at +4, virtual deleting dtor at slot 0.
struct MeshGroup {
    virtual void* Destroy(int flag);
    long mRefCount;
};
// Reference whose destructor is the out-of-line helper at 0x00472520.
struct MGRefExt {
    MeshGroup* p;
    MGRefExt() : p(0) {}
    ~MGRefExt();                                   // 0x00472520
};
// Reference with inline interlocked release.
struct MGRef {
    MeshGroup* p;
    MGRef() : p(0) {}
    MGRef& operator=(const MGRefExt& o);           // 0x006df280 (AddRef new, Release old)
    __forceinline ~MGRef()
    {
        MeshGroup* g = p;
        if (g) {
            long n = _InterlockedExchangeAdd(&g->mRefCount, -1) - 1;
            if (n == 0) {
                _InterlockedExchange(&g->mRefCount, 1);
                g->Destroy(1);
            }
        }
    }
};

// vector of intrusive refs (begin/end/cap), freed with a delete[] header check
struct RefVec3 {
    MGRef* mpBegin;
    MGRef* mpEnd;
    MGRef* mpCap;
    void push_back(const MGRef& r);                // 0x0041ef20
    void DestroyRange(MGRef* first, MGRef* last);  // 0x004243e0
    ~RefVec3()
    {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};

struct IntVec3 {
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    ~IntVec3()
    {
        if (mpBegin && ((int*)mpBegin)[-1])
            operator_delete__(mpBegin);
    }
};

struct VertexRec {                 // 0x20 bytes
    uint32_t pad00[4];
    int mCount;                    // +0x10
    float* mpData;                 // +0x14
    uint16_t pad18;
    uint16_t mStrideBits;          // +0x1a (bytes/4 << 2)
    uint32_t pad1c;
};
struct V16Rec {                    // 16 bytes
    uint32_t pad00;
    char* mpData;                  // +0x04
    uint16_t mFormat;              // +0x08
    uint16_t mStride;              // +0x0a
    uint32_t pad0c;
};
struct Entry8c {
    uint32_t pad00;
    char* mpData;                  // +0x04
    uint16_t mFormat;              // +0x08
    uint16_t mStride;              // +0x0a
    uint32_t pad0c[2];
    short* mpIds;                  // +0x14 (pairs of shorts)
    uint8_t pad18[0x44 - 0x18];
    V16Rec* mpV16Begin;            // +0x44
    V16Rec* mpV16End;              // +0x48
    uint8_t pad4c[0x8c - 0x4c];
};
struct Prim14 {
    int mType, mEntry, mStart, mEnd, mAux;
};
struct Mesh {
    uint32_t pad00[2];
    VertexRec* mpVert;             // +0x08
    uint32_t pad0c[4];
    Entry8c* mpEntryBegin;         // +0x1c
    Entry8c* mpEntryEnd;           // +0x20
    uint32_t pad24[3];
    Prim14* mpPrimBegin;           // +0x30
};

extern signed char g_PrimTab84[12];     // 0x0140cf84
extern signed char g_PrimTab90[12];     // 0x0140cf90
extern const uint32_t g_FormatMask[];   // 0x01464904

int FindVertexIndex(Mesh* m, unsigned a, unsigned b, unsigned c, int d);   // 0x0071ddc0
int FindPairIndex(Mesh* m, int entry, int key);                           // 0x0071e040
void FindPrimitives(Mesh* m, IntVec3* out, int typeEntry, int start, int aux);   // 0x0071ee10

struct Base;
struct Sec;

struct IOwner {
    PV8 PV8 PV4 PV2
    virtual void Notify(Sec* s);      // +0x58
};
struct IProps {
    PV8 PV
    virtual bool GetProp(uint32_t id, Property** out);   // +0x24
};

struct Sec {                           // object+8 (secondary base)
    IOwner* mpOwner;                   // +0x00
    uint8_t pad04[0x90 - 0x04];
    IProps* mpProps;                   // +0x90
};
struct Base {                          // the layered object
    uint8_t pad00[0x9c];
    Mesh* mpMeshes[18];                // +0x9c
    cSPTransform mXform;               // +0xe4
};

bool FUN_00b64870(Mesh* m, int hash, const cSPTransform* xf, MGRefExt* out, int* n1, int* n2);   // 0x00b64870
int FUN_00b63f70(Base* b, int idx);                                                                // 0x00b63f70

// @ 0x00b64a60
bool CollectLayerGeometry(Sec* p, int idx, bool useParent, int maxCount, const cSPTransform& delta,
                          hkArray<Vec16>* outVerts, hkArray<Tri>* outTris)
{
    Base* self = (Base*)((char*)p - 8);
    p->mpOwner->Notify(p);
    int hash = 0;
    Property* prop;
    IProps* props = p->mpProps;
    if (props && props->GetProp(0x7ff150b, &prop) && prop->type == 9)
        hash = *prop->GetInt();
    if (idx >= 0) {
        Mesh** q = &self->mpMeshes[idx];
        while (*q == 0) {
            idx--;
            q--;
            if (idx < 0)
                return false;
        }
        if (idx >= 0) {
            Mesh* mesh = self->mpMeshes[idx];
            cSPTransform xf;
            translateTransform(xf, self->mXform, delta);
            MGRef refptr;
            int n1, n2;
            if (FUN_00b64870(mesh, hash, &xf, (MGRefExt*)&refptr, &n1, &n2) && n1 > 0 && n2 > 0) {
                if (useParent && n2 <= maxCount) {
                    int pi = FUN_00b63f70(self, idx - 1);
                    if (pi >= 0) {
                        MGRefExt tmp;
                        int m1, m2;
                        if (FUN_00b64870(self->mpMeshes[pi], hash, &xf, &tmp, &m1, &m2)) {
                            refptr = tmp;
                            n1 = m1;
                            n2 = m2;
                        }
                    }
                }
                RefVec3 group;
                group.mpBegin = 0;
                group.mpEnd = 0;
                group.mpCap = 0;
                group.push_back(refptr);
                int n = (int)(group.mpEnd - group.mpBegin);
                hkLocalArray<int> offsets(n);
                offsets.setSize(n);
                if (outVerts->getCapacity() < n1)
                    outVerts->reserveExactly(n1);
                for (int i = 0; i < n; i++) {
                    Mesh* m = (Mesh*)group.mpBegin[i].p;
                    int e = FindVertexIndex(m, 1, 0xffffffff, 3, 0xe);
                    if (e >= 0) {
                        offsets[i] = outVerts->getSize();
                        VertexRec* vr = &m->mpVert[e];
                        const float* src = vr->mpData;
                        int cnt = vr->mCount;
                        int stride = (vr->mStrideBits >> 2);
                        for (; cnt > 0; cnt--) {
                            Vector3 p3 = *(const Vector3*)src;
                            outVerts->pushBackXYZ0(p3);
                            src += stride;
                        }
                    }
                }
                if (outTris) {
                    if (outTris->getCapacity() < n2)
                        outTris->reserveExactly(n2);
                    for (int i = 0; i < n; i++) {
                        Mesh* m = (Mesh*)group.mpBegin[i].p;
                        int base = offsets[i];
                        int e = FindVertexIndex(m, 1, 0xffffffff, 3, 0xe);
                        if (e < 0)
                            continue;
                        int nSub = (int)(m->mpEntryEnd - m->mpEntryBegin);
                        for (int sub = 0; sub < nSub; sub++) {
                            Entry8c* ent = &m->mpEntryBegin[sub];
                            int idx2 = FindPairIndex(m, sub, e);
                            if (idx2 < 0)
                                continue;
                            IntVec3 prims;
                            prims.mpBegin = 0;
                            prims.mpEnd = 0;
                            prims.mpCap = 0;
                            FindPrimitives(m, &prims, sub, 4, -1);
                            int nPrims = (int)(prims.mpEnd - prims.mpBegin);
                            for (int k = 0; k < nPrims; k++) {
                                Prim14* pr = &m->mpPrimBegin[prims.mpBegin[k]];
                                int t = pr->mType;
                                int cnt;
                                if (t > 0 && t < 10) {
                                    if (t == 9)
                                        cnt = 1;
                                    else
                                        cnt = (g_PrimTab84[t] - pr->mStart + pr->mEnd) / g_PrimTab90[t];
                                } else {
                                    cnt = 0;
                                }
                                int s = pr->mStart;
                                if (ent->mpV16Begin == ent->mpV16End) {
                                    for (; cnt > 0; cnt--) {
                                        uint32_t mask = g_FormatMask[ent->mFormat];
                                        Tri tr;
                                        tr.a = (*(uint32_t*)(ent->mpData + ent->mStride * s) & mask) + base;
                                        tr.b = (*(uint32_t*)(ent->mpData + ent->mStride * (s + 1)) & mask) + base;
                                        tr.c = (*(uint32_t*)(ent->mpData + ent->mStride * (s + 2)) & mask) + base;
                                        s += 3;
                                        outTris->pushBack(tr);
                                    }
                                } else {
                                    V16Rec* r2 = &ent->mpV16Begin[ent->mpIds[idx2 * 2 + 1]];
                                    for (; cnt > 0; cnt--) {
                                        uint32_t m1 = g_FormatMask[ent->mFormat];
                                        uint32_t m2 = g_FormatMask[r2->mFormat];
                                        Tri tr;
                                        tr.a = (*(uint32_t*)(r2->mpData + (*(uint32_t*)(ent->mpData + ent->mStride * s) & m1) * r2->mStride) & m2) + base;
                                        tr.b = (*(uint32_t*)(r2->mpData + (*(uint32_t*)(ent->mpData + ent->mStride * (s + 1)) & m1) * r2->mStride) & m2) + base;
                                        tr.c = (*(uint32_t*)(r2->mpData + (*(uint32_t*)(ent->mpData + ent->mStride * (s + 2)) & m1) * r2->mStride) & m2) + base;
                                        s += 3;
                                        outTris->pushBack(tr);
                                    }
                                }
                            }
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}
