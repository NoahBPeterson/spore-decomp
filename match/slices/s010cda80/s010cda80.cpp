// s010cda80 -- Havok hkBvTreeStreamAgent: the agent1n-machine forwarders, the tracker
// reset, the hkAlgorithm::quickSortRecursive<uint, less> instantiation, the class'
// scalar-deleting destructor and calcStatistics.  Offsets come from the disassembly;
// the agent's hkArray<int> sector list sits at +0x30 and the tracked machine at +0x30.
//
// Module flags: /vc71 /O2 /MD /Gy /EHsc /TP

typedef unsigned int hkUint32;

struct hkCollisionInput;                     // opaque

// hkStatisticsCollector's first slots: slot 1 is addObjectStat(const char*, int, const
// void*) and slot 2 is addBufferStat(const char*, int, const void*, int, int).  Both are
// __thiscall (the original loads `this` into ecx before the indirect call).
struct hkStatisticsCollector {
    virtual void v00();                                                    // +0x00
    virtual void addObjectStat(const char* name, int id, const void* obj);// +0x04
    virtual void addBufferStat(const char* name, int id, const void* p,
                               unsigned size, unsigned cap);              // +0x08
};

// =====================================================================
// hkBvTreeStreamAgent
// =====================================================================
struct hkBvTreeStreamAgent {
    unsigned char pad_000[0x10];
    hkUint32      v10, v14, v18, v1c;        // +0x10..+0x1c
    hkUint32      v20, v24, v28, v2c;        // +0x20..+0x2c
    int           m_sectorPtrs;              // +0x30 (hkArray<int> data)
    int           m_sectorSize;              // +0x34
    int           m_sectorCap;               // +0x38

    void invalidateTim(hkCollisionInput& in);                        // 010cda80
    void warpTime(float dt, float t, hkCollisionInput& in);          // 010cdaa0
    void updateShapeCollectionFilter(void* a, void* b, void* c);     // 010cdac0
    void* scalarDeletingDtor(unsigned int flags);                    // 010cdca0
    void calcStatistics(hkStatisticsCollector* c) const;             // 010cdcd0
};

// =====================================================================
// External helpers, VA-resolved.
// =====================================================================
extern "C" void hkAgent1nMachine_InvalidateTim(void* machine, void* in);   // 0x01103850
extern "C" void hkAgent1nMachine_WarpTime(void* machine, float dt, float t,
                                          void* in);                       // 0x01103930
extern "C" void hkAgent1nMachine_UpdateShapeCollectionFilter(void* machine,
                                                            void* args);   // 0x01104740
void hkTrackerCalcStatistics(void* machine, hkStatisticsCollector* c);     // 0x010fce10
// hkMemory::s_instance lives at a fixed global address; it holds the allocator object,
// whose vtable slot 5 is deallocate(void* p, int align, int size) -- a __thiscall member,
// so `this` lands in ecx and the three arguments are pushed (the callee does `ret 0xc`).
struct hkMemoryAllocator {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();                                                 // +0x10
    virtual void deallocate(void* p, int align, int size);              // +0x14
};
extern hkMemoryAllocator* g_hkMemoryInstance;                              // 0x016e4178

// =====================================================================
// @ 0x010cda80
void hkBvTreeStreamAgent::invalidateTim(hkCollisionInput& in)
{
    hkAgent1nMachine_InvalidateTim((char*)this + 0x30, &in);
}

// @ 0x010cdaa0
void hkBvTreeStreamAgent::warpTime(float dt, float t, hkCollisionInput& in)
{
    hkAgent1nMachine_WarpTime((char*)this + 0x30, dt, t, &in);
}

// @ 0x010cdac0
void hkBvTreeStreamAgent::updateShapeCollectionFilter(void* a, void* b, void* c)
{
    v1c = 0; v18 = 0; v14 = 0; v10 = 0;
    v2c = 0; v28 = 0; v24 = 0; v20 = 0;

    // Caller-provided block handed to the machine by address.  Field order follows the
    // original's stack stores: arg1, arg2->vtable[3], arg2, arg3, this->+0x08.
    struct Args {
        void* a;             // +0x00  (first argument)
        void* slot;          // +0x04  (b->vtable[3])
        void* b;             // +0x08  (second argument)
        void* c;             // +0x0c  (third argument)
        void* d;             // +0x10  (this->+0x08)
    } args;

    args.a    = a;
    args.slot = *(void**)(*(char**)b + 0xc);
    args.b    = b;
    args.c    = c;
    args.d    = *(void**)((char*)this + 8);

    hkAgent1nMachine_UpdateShapeCollectionFilter((char*)this + 0x30, &args);
}

// =====================================================================
// hkAlgorithm::quickSortRecursive<unsigned int, hkAlgorithm::less<unsigned int> >
// (retail symbol ??$quickSortRecursive@IV?$less@I@hkAlgorithm@@@hkAlgorithm@@YAXPAIHHV?$less@I@0@@Z)
// =====================================================================
struct hkLessUint { };

// @ 0x010cdc20
void hkAlgorithm_quickSortRecursive(unsigned int* base, int lo, int hi, hkLessUint)
{
    do {
        unsigned int pivot = base[(lo + hi) >> 1];
        int i = hi;
        int j = lo;
        do {
            while (base[j] < pivot)
                ++j;
            while (pivot < base[i])
                --i;
            if (i < j)
                break;
            if (i != j) {
                unsigned int t = base[i];
                base[i] = base[j];
                base[j] = t;
            }
            --i;
            ++j;
        } while (j <= i);
        if (lo < i)
            hkAlgorithm_quickSortRecursive(base, lo, i, hkLessUint());
        lo = j;
        if (hi <= j)
            return;
    } while (true);
}

// @ 0x010cdca0
void* hkBvTreeStreamAgent::scalarDeletingDtor(unsigned int flags)
{
    *(void**)this = (void*)0x013ef534;                 // vtable
    if (flags & 1)
        g_hkMemoryInstance->deallocate((void*)this, 8, 0x1c);
    return (void*)this;
}

// @ 0x010cdcd0
void hkBvTreeStreamAgent::calcStatistics(hkStatisticsCollector* c) const
{
    c->addObjectStat("BvTreeAgt3", 8, (void*)this);
    int cap  = m_sectorCap;
    if (cap >= 0) {
        int siz = m_sectorSize;
        const void* p = (const void*)m_sectorPtrs;
        c->addBufferStat("SectorPtrs", 8, p, siz * 4, cap * 4);
    }
    hkTrackerCalcStatistics((char*)this + 0x30, c);
}
