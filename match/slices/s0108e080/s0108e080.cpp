// Havok 3.1.0 (statically linked, VC .NET 2003 build): hkAabbPhantom clone / destroy /
// statistics / internal-array management, hkPhantom listener fan-out and destructor,
// and two hkWheelConstraintData queries.
//
// Uses the class model already reconstructed for the neighbouring Havok slices
// (match/slices/s0108d0b0) so that hkArray, hkReferencedObject, hkMemory and
// hkThreadMemory are shared verbatim.
#include "types.h"

#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])

// ---- CRT / TLS ----------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);

extern unsigned long g_hkThreadMemoryTls;   // 0x016e4174

// ---- hkThreadMemory -----------------------------------------------------
struct hkThreadMemory {
    void* m_vtable;                     // +0x00
    char  m_pad04[0x1c];                // +0x04
    int   m_stackCurrent;               // +0x20
    int   m_stackEnd;                   // +0x2c
    char  m_pad30[0x84];                // +0x30
    int   m_rowHead[0x11];              // +0xb4
    // 0x0107daa0
    void* allocateChunk(int size, int memClass);
    // 0x0107db10
    void  deallocateChunk(void* p, int size, int memClass);
};
// @ 0x0107f530
extern "C++" void hkArrayUtil_reserveMore(void* array, int elemSize);

// ---- shared Havok types -------------------------------------------------
struct hkVector4 { float m_x, m_y, m_z, m_w; };
struct hkAabb { hkVector4 m_min, m_max; };

template<class T> struct hkArray {
    T*      m_data;                 // +0x00
    int32_t m_size;                 // +0x04
    int32_t m_capacityAndFlags;     // +0x08
};

struct hkReferencedObject {
    uint16_t m_memSizeAndFlags;     // +0x04
    int16_t  m_referenceCount;      // +0x06
    virtual ~hkReferencedObject();
    void setVtable(const void* vt) { *(const void**)this = vt; }
};

struct hkMemory {
    virtual ~hkMemory();
    virtual void vslot1();
    virtual void vslot2();
    virtual void vslot3();
    // slot 4 (+0x10): allocate
    virtual void* allocate(int nbytes, int memoryClass);
    // slot 5 (+0x14): deallocate
    virtual void deallocate(void* p, int nbytes, int memoryClass);
};

extern hkMemory* hkMemory_instance;      // 0x016e4178

// ---- hkStatisticsCollector ----------------------------------------------
struct hkStatisticsCollector {
    virtual ~hkStatisticsCollector();
    virtual void beginObject(const char* name, int flags, const void* obj);                              // +4
    // +8
    virtual void addArray(const char* name, int memClass, const void* data, int used, int allocated);
    virtual void vslot3();
    virtual void endObjectava();                                                                          // +0x10
    virtual void endObject();                                                                             // +0x14
};

// ---- hkWorldObject / hkPhantom / hkAabbPhantom ---------------------------
struct hkShape;
struct hkWorld;
struct hkPhantom;

// @ 0x01082770  hkWorldObject::~hkWorldObject
void hkWorldObject_dtor(void* self);
// @ 0x01082660  hkWorldObject::calcStatistics
struct hkWorldObjectMember { void calcStatistics(hkStatisticsCollector* c) const; };
// @ 0x01087ca0  hkWorldObject::copyProperties(const hkWorldObject*)
void hkWorldObject_copyProperties(void* self, const void* other);

// world-side broad-phase entry points used by updateBroadPhase
extern "C++" {
    struct HK_BroadPhaseMsg { unsigned char m_kind; void* m_self; const void* m_aabb; };
}
bool  hkWorld_broadPhaseBusy(hkWorld* w);
void  hkWorld_enterBroadPhase(hkWorld* w);
unsigned hkWorld_numCollidables(hkWorld* w);
void  hkWorld_lockBroadPhase(hkWorld* w);
void  hkWorld_unlockBroadPhase(hkWorld* w);
void* hkWorld_dispatcher(hkWorld* w);
void  hkWorld_mergeCollidables(hkWorld* w, hkArray<void*>* a, hkArray<void*>* b);
bool  hkWorld_leaveBroadPhase(hkWorld* w);
void  hkWorld_broadPhaseFinished(hkWorld* w);
void  hkCollisionDispatcher_updateAabbs(void* d, const hkAabb* aabb, int n,
                                        hkArray<void*>* out, hkArray<void*>* out2);
void  hkBroadPhaseNotify(HK_BroadPhaseMsg* msg);
void  hkStackArrayAlloc(hkArray<void*>* a, unsigned n, unsigned elemSize);
void  hkStackArrayFree(hkArray<void*>* a);

struct hkPhantom : hkReferencedObject {
    hkWorld* m_world;                       // +0x08
    uint32_t m_pad0c[4];                    // +0x0c
    hkShape* m_shape;                       // +0x1c
    uint32_t m_pad20;                       // +0x20
    void*    m_motionState;                 // +0x24
    uint32_t m_pad28[1];                    // +0x28
    int32_t  m_ownerOffset;                 // +0x2c
    uint8_t  m_pad30[0x58 - 0x30];          // +0x30
    hkArray<void*> m_overlapListeners;      // +0x58
    hkArray<void*> m_phantomListeners;      // +0x64

    // 0x0108e680
    void updateBroadPhase(const hkAabb& aabb);
    // 0x0108e370
    void firePhantomAdded();
    // 0x0108e300
    void firePhantomRemoved();
    // 0x0108e3e0
    void firePhantomShapeSet();
    // 0x0108e5e0
    virtual void deallocateInternalArrays();
    // 0x0108e450  hkArray<void*>::removeAtValue, inlined against m_overlapListeners
    void overlapRemoveAtValue(void* value);
    // 0x0108e4a0  hkArray<void*>::pushBack, inlined against m_overlapListeners
    void overlapPushBack(void* value);
    // 0x0108e2c0  hkArray<void*>::removeNulls, inlined against m_overlapListeners
    void overlapRemoveNulls();
};

struct hkAabbPhantom : hkPhantom {
    hkAabb m_aabb;                              // +0x70
    hkArray<void*> m_overlappingCollidables;    // +0x90

    // 0x0108dfe0
    hkAabbPhantom(const hkAabb& aabb, uint32_t collisionFilterInfo);
    // 0x0108e080
    virtual hkPhantom* clone() const;
    // 0x0108e1d0
    virtual void deallocateInternalArrays();
    // 0x0108e250
    virtual void* scalarDeletingDestructor(unsigned int flags);
    // 0x0108e4e0
    virtual void calcStatistics(hkStatisticsCollector* c) const;
};

// ---- listener interfaces (vtable slots used by the fire* fan-out) --------
// The phantom keeps hkPhantomListener* in m_phantomListeners.  The slots the
// fan-out uses are +0x04 (phantomAdded), +0x08 (phantomRemoved) and
// +0x0c (phantomShapeSet); the destructor uses +0x10.
struct hkPhantomListener {
    virtual void vslot0();
    virtual void phantomAdded(const hkPhantom* p);        // +0x04
    virtual void phantomRemoved(const hkPhantom* p);      // +0x08
    virtual void phantomShapeSet(const hkPhantom* p);     // +0x0c
    virtual void vslot4();                                // +0x10
};

// clone() allocates through hkMemory and then re-runs the (aabb, filter) ctor.
struct hkPlacement { char dummy; };
inline void* operator new(size_t, hkPlacement* p) { return p; }

// @ 0x0108e080
hkPhantom* hkAabbPhantom::clone() const
{
    hkMemory* mem = hkMemory_instance;
    hkAabbPhantom* obj = (hkAabbPhantom*)mem->allocate(0xa0, 0x2e);
    obj->m_memSizeAndFlags = 0xa0;

    hkAabbPhantom* e = (hkAabbPhantom*)::new ((hkPlacement*)obj) hkAabbPhantom(
        *(const hkAabb*)((const char*)this + 0x70),
        *(const uint32_t*)((const char*)this + 0x38));

    // ---- m_overlapListeners (+0x58) ----
    if ((e->m_overlapListeners.m_capacityAndFlags & 0x3fffffff) < m_overlapListeners.m_size) {
        if (e->m_overlapListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls);
            ((hkThreadMemory*)tls)->deallocateChunk(e->m_overlapListeners.m_data,
                                           (e->m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        void* tls = TlsGetValue(g_hkThreadMemoryTls);
        e->m_overlapListeners.m_data = (void**)((hkThreadMemory*)tls)->allocateChunk(m_overlapListeners.m_size << 2, 0x14);
        e->m_overlapListeners.m_capacityAndFlags =
            (e->m_overlapListeners.m_capacityAndFlags & 0x40000000) | m_overlapListeners.m_size;
    }
    e->m_overlapListeners.m_size = m_overlapListeners.m_size;
    for (int i = 0; i < m_overlapListeners.m_size; ++i)
        e->m_overlapListeners.m_data[i] = m_overlapListeners.m_data[i];

    // ---- m_phantomListeners (+0x64) ----
    if ((e->m_phantomListeners.m_capacityAndFlags & 0x3fffffff) < m_phantomListeners.m_size) {
        if (e->m_phantomListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls);
            ((hkThreadMemory*)tls)->deallocateChunk(e->m_phantomListeners.m_data,
                                           (e->m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        void* tls = TlsGetValue(g_hkThreadMemoryTls);
        e->m_phantomListeners.m_data = (void**)((hkThreadMemory*)tls)->allocateChunk(m_phantomListeners.m_size << 2, 0x14);
        e->m_phantomListeners.m_capacityAndFlags =
            (e->m_phantomListeners.m_capacityAndFlags & 0x40000000) | m_phantomListeners.m_size;
    }
    e->m_phantomListeners.m_size = m_phantomListeners.m_size;
    for (int i = 0; i < m_phantomListeners.m_size; ++i)
        e->m_phantomListeners.m_data[i] = m_phantomListeners.m_data[i];

    hkWorldObject_copyProperties(e, this);
    return e;
}

// @ 0x0108e1d0
void hkAabbPhantom::deallocateInternalArrays()
{
    if (m_overlappingCollidables.m_size == 0) {
        if (m_overlappingCollidables.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls);
            ((hkThreadMemory*)tls)->deallocateChunk(m_overlappingCollidables.m_data,
                                           (m_overlappingCollidables.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        m_overlappingCollidables.m_data = 0;
        m_overlappingCollidables.m_size = 0;
        m_overlappingCollidables.m_capacityAndFlags =
            (int32_t)((m_overlappingCollidables.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
    }
    hkPhantom::deallocateInternalArrays();
}

// @ 0x0108e250
void* hkAabbPhantom::scalarDeletingDestructor(unsigned int flags)
{
    setVtable((void*)0x0149e51c);
    if (m_overlappingCollidables.m_capacityAndFlags >= 0) {
        void* tls = TlsGetValue(g_hkThreadMemoryTls);
        ((hkThreadMemory*)tls)->deallocateChunk(m_overlappingCollidables.m_data,
                                       (m_overlappingCollidables.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
    }
    this->~hkAabbPhantom();
    if (flags & 1) {
        hkMemory* mem = hkMemory_instance;
        mem->deallocate(this, m_memSizeAndFlags, 0x2e);
    }
    return this;
}

// @ 0x0108e300
void hkPhantom::firePhantomRemoved()
{
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener*)l)->phantomRemoved(this);
    }
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        if (m_phantomListeners.m_data[i] == 0) {
            int n = --m_phantomListeners.m_size;
            for (int j = i; j < n; ++j, n = m_phantomListeners.m_size)
                m_phantomListeners.m_data[j] = m_phantomListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e370
void hkPhantom::firePhantomAdded()
{
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener*)l)->phantomAdded(this);
    }
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        if (m_phantomListeners.m_data[i] == 0) {
            int n = --m_phantomListeners.m_size;
            for (int j = i; j < n; ++j, n = m_phantomListeners.m_size)
                m_phantomListeners.m_data[j] = m_phantomListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e3e0
void hkPhantom::firePhantomShapeSet()
{
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener*)l)->phantomShapeSet(this);
    }
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        if (m_phantomListeners.m_data[i] == 0) {
            int n = --m_phantomListeners.m_size;
            for (int j = i; j < n; ++j, n = m_phantomListeners.m_size)
                m_phantomListeners.m_data[j] = m_phantomListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e4e0
void hkAabbPhantom::calcStatistics(hkStatisticsCollector* c) const
{
    ((const hkWorldObjectMember*)this)->calcStatistics(c);
    if (m_overlapListeners.m_capacityAndFlags >= 0)
        c->addArray("OvrlapLisPtr", 4, m_overlapListeners.m_data,
                    m_overlapListeners.m_size << 2,
                    (m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2);
    if (m_phantomListeners.m_capacityAndFlags >= 0)
        c->addArray("PhantmLisPtr", 4, m_phantomListeners.m_data,
                    m_phantomListeners.m_size << 2,
                    (m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2);
}

// @ 0x0108e550
hkPhantom::~hkPhantom()
{
    setVtable((void*)0x0149e34c);
    for (int i = m_phantomListeners.m_size - 1; i >= 0; --i) {
        void* l = m_phantomListeners.m_data[i];
        if (l != 0)
            ((hkPhantomListener*)l)->vslot4();
    }
    if (m_phantomListeners.m_capacityAndFlags >= 0) {
        void* tls = TlsGetValue(g_hkThreadMemoryTls);
        ((hkThreadMemory*)tls)->deallocateChunk(m_phantomListeners.m_data,
                                       (m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
    }
    if (m_overlapListeners.m_capacityAndFlags >= 0) {
        void* tls = TlsGetValue(g_hkThreadMemoryTls);
        ((hkThreadMemory*)tls)->deallocateChunk(m_overlapListeners.m_data,
                                       (m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
    }
    hkWorldObject_dtor(this);
}

// @ 0x0108e5e0
void hkPhantom::deallocateInternalArrays()
{
    if (m_overlapListeners.m_size == 0) {
        if (m_overlapListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls);
            ((hkThreadMemory*)tls)->deallocateChunk(m_overlapListeners.m_data,
                                           (m_overlapListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        int cap = (int32_t)((m_overlapListeners.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
        m_overlapListeners.m_data = 0;
        m_overlapListeners.m_size = 0;
        m_overlapListeners.m_capacityAndFlags = cap;
    }
    if (m_phantomListeners.m_size == 0) {
        if (m_phantomListeners.m_capacityAndFlags >= 0) {
            void* tls = TlsGetValue(g_hkThreadMemoryTls);
            ((hkThreadMemory*)tls)->deallocateChunk(m_phantomListeners.m_data,
                                           (m_phantomListeners.m_capacityAndFlags & 0x3fffffff) << 2, 0x14);
        }
        int cap = (int32_t)((m_phantomListeners.m_capacityAndFlags & 0xc0000000u) | 0x80000000u);
        m_phantomListeners.m_data = 0;
        m_phantomListeners.m_size = 0;
        m_phantomListeners.m_capacityAndFlags = cap;
    }
}

// ---------------------------------------------------------------------------
// hkWheelConstraintData
// ---------------------------------------------------------------------------
struct hkConstraintRuntimeInfo {
    int32_t m_sizeOfThis;      // +0x00
    int32_t m_sizeOfAll;       // +0x04
};

typedef unsigned char chkHkBool;

// The member form: `this` in ecx, then (hkBool, RuntimeInfo&) on the stack, ret 8.
struct hkBool { unsigned char m_bool; };

struct hkWheelConstraintData {
    float m_ref[8];     // +0x00 .. +0x20 (m_ref[0..7] at +0x00, second vec at +0x20)
    float m_axisA[4];   // +0x40
    float m_axisB[4];   // +0x50
    float m_axisC[4];   // +0x60
    float m_axisD[4];   // +0x70
    float m_vecE[4];    // +0x80
    float m_min;        // +0x90
    float m_max;        // +0x94
    char m_pad98[4];    // +0x98

    // 0x0108e940
    virtual void getRuntimeInfo(chkHkBool valid, hkConstraintRuntimeInfo* info) const;
    // 0x0108e970
    virtual hkBool isValid() const;
    virtual ~hkWheelConstraintData() {}
};

// @ 0x0108e940  hkWheelConstraintData::getRuntimeInfo(hkBool, RuntimeInfo&) const
void hkWheelConstraintData::getRuntimeInfo(chkHkBool valid, hkConstraintRuntimeInfo* info) const
{
    if ((int)valid) {
        info->m_sizeOfAll  = 6;
        info->m_sizeOfThis = 0x30;
        return;
    }
    info->m_sizeOfAll  = 0;
    info->m_sizeOfThis = 0;
}

extern float g_hkZeroEps;      // 0x013f89bc
extern float g_hkOne;          // 0x01485720

// ---------------------------------------------------------------------------
// hkArray<int> helpers that Havok inlines at these two out-of-line entry points
// ---------------------------------------------------------------------------
// @ 0x0108e450
void hkPhantom::overlapRemoveAtValue(void* value)
{
    int idx = 0;
    if (m_overlapListeners.m_size > 0) {
        void** q = m_overlapListeners.m_data;
        do {
            if (*q == value)
                goto found;
            ++idx;
            ++q;
        } while (idx < m_overlapListeners.m_size);
    }
    idx = -1;
found:
    {
        int n = --m_overlapListeners.m_size;
        if (idx < n) {
            for (int j = idx; j < n; ++j)
                m_overlapListeners.m_data[j] = m_overlapListeners.m_data[j + 1];
        }
    }
}

// @ 0x0108e4a0
void hkPhantom::overlapPushBack(void* value)
{
    hkArray<void*>* a = &m_overlapListeners;
    if (a->m_size == (a->m_capacityAndFlags & 0x3fffffff))
        hkArrayUtil_reserveMore(a, 4);
    a->m_data[a->m_size] = value;
    ++a->m_size;
}

// @ 0x0108e2c0
void hkPhantom::overlapRemoveNulls()
{
    for (int i = m_overlapListeners.m_size - 1; i >= 0; --i) {
        if (m_overlapListeners.m_data[i] == 0) {
            int n = --m_overlapListeners.m_size;
            for (int j = i; j < n; ++j)
                m_overlapListeners.m_data[j] = m_overlapListeners.m_data[j + 1];
        }
    }
}

// ---------------------------------------------------------------------------
// hkWheelConstraintData::isValid  (returns hkBool by value: a 1-byte struct, so the
// caller passes a hidden result pointer in the first stack slot; the pointer comes
// back in eax and the function does ret 4)
// ---------------------------------------------------------------------------
// @ 0x01080e40  hkMath::equal(float a, float b, float eps) -> hkBool
extern hkBool hkMath_equal(float a, float b, float eps);

static float hkAbsF(float v) { return v < 0.0f ? -v : v; }
static float hkLen3sq(const float* v) { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }

// @ 0x0108e970
hkBool hkWheelConstraintData::isValid() const
{
    if (hkAbsF(m_axisD[0] * m_axisC[0] + m_axisD[1] * m_axisC[1] + m_axisD[2] * m_axisC[2]) < 1e-05f &&
        hkAbsF(m_axisA[0] * m_axisB[0] + m_axisA[1] * m_axisB[1] + m_axisA[2] * m_axisB[2]) < 1e-05f &&
        hkAbsF(hkLen3sq(m_axisC) - 1.0f) < 1e-05f &&
        hkAbsF(hkLen3sq(m_axisA) - 1.0f) < 1e-05f &&
        hkAbsF(hkLen3sq(m_axisB) - 1.0f) < 1e-05f) {
        hkBool b1 = hkMath_equal(m_ref[0] * m_ref[0] + m_ref[1] * m_ref[1] + m_ref[2] * m_ref[2],
                                 1.0f, 1e-05f);
        if (b1.m_bool) {
            hkBool b2 = hkMath_equal(m_vecE[0] * m_vecE[0] + m_vecE[1] * m_vecE[1] +
                                     m_vecE[2] * m_vecE[2], 1.0f, 1e-05f);
            if (b2.m_bool && m_min <= m_max) {
                hkBool r; r.m_bool = 1; return r;
            }
        }
    }
    hkBool r; r.m_bool = 0; return r;
}

// ---------------------------------------------------------------------------
// hkPhantom::updateBroadPhase -- hands the phantom's (or its shape's) AABB to the
// world's broad phase.  When the world is already inside a broad-phase update
// (the +0x8c depth counter plus the +0x90 queued word are non-zero) the request
// is deferred as a notification message; otherwise the world is locked, the
// collision dispatcher's query is run into two thread-memory scratch arrays, the
// overlap list is compacted, and the world is unlocked again.
//
// The scratch arrays are hkArray<unsigned> buffers carved out of the thread
// memory stack with the owned bit (bit 31) set in the capacity word.
// ---------------------------------------------------------------------------
// @ 0x0108e680
void hkPhantom::updateBroadPhase(const hkAabb& aabb)
{
    hkWorld* world = m_world;
    if (world == 0)
        return;

    if (hkWorld_broadPhaseBusy(world)) {
        HK_BroadPhaseMsg msg;
        msg.m_kind = 0x11;
        msg.m_self = this;
        msg.m_aabb = &aabb;
        hkBroadPhaseNotify(&msg);
        return;
    }

    hkWorld_enterBroadPhase(world);

    unsigned n = hkWorld_numCollidables(world);
    hkArray<void*> scratchA, scratchB;
    hkStackArrayAlloc(&scratchA, n, 8);
    hkStackArrayAlloc(&scratchB, n, 8);

    void* query = (char*)this + 0x30;
    hkWorld_lockBroadPhase(world);
    hkCollisionDispatcher_updateAabbs(hkWorld_dispatcher(world), &aabb, 1,
                                      &scratchA, &scratchB);

    if (scratchB.m_data != 0 || scratchA.m_data != 0) {
        hkWorld_mergeCollidables(world, &scratchA, &scratchB);
        overlapRemoveNulls();
    }

    hkWorld_unlockBroadPhase(world);

    world = m_world;
    if (hkWorld_leaveBroadPhase(world))
        hkWorld_broadPhaseFinished(world);

    hkStackArrayFree(&scratchA);
    hkStackArrayFree(&scratchB);
    (void)query;
}
