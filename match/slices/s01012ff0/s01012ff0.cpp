// 0x01012ff0: eastl::partial_sort<SP::cSimulatorUniverse::tGrobShockData *,
//             bool (__cdecl *)(SP::cSimulatorUniverse::tGrobShockData const &,
//                              SP::cSimulatorUniverse::tGrobShockData const &)>
//
// Retail is EASTL's partial_sort: make_heap(first, middle, compare), then for
// every element past middle that compares before *first, take it out as a
// temporary, copy *first into its slot and push the temporary down the heap
// (adjust_heap with the extra leading difference_type(0) that this EASTL
// revision passes), and finally sort_heap the heap.  The three heap helpers are
// out-of-line in retail (0x01012330, 0x01011900, 0x010123d0), so they are
// declared here instead of being pulled in from the EASTL headers.
//
// The only source with the layout the retail code copies around (0x28 bytes:
// two dwords, then a 0x20-byte timer with its vtable at +8) is
// src/game/SPGonzago/SPSimulatorUniverse.cpp.  Its stand-ins are repeated here
// so the slice stays self-contained:
//   tGrobShockData  = { int, int, cGonzagoTimer }        (0x28 bytes)
//   cGonzagoTimer   = { void* vtbl 0x01464450, int, ... } (0x20 bytes)

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_1464450[];
extern "C" char g_1465d54[];

typedef unsigned __int64 u64;

struct cGonzagoTimer {          // 0x20 bytes, vtable at +0x00
    void* mVtbl;                // +0x00
    int   mField_04;            // +0x04
    int   mElapsedLo;           // +0x08
    int   mElapsedHi;           // +0x0c
    int   mBaseLo;              // +0x10
    int   mBaseHi;              // +0x14
    char  mRunning;             // +0x18
    char  mPad19[3];            // +0x19
    int   mGetMs;               // +0x1c

    __forceinline cGonzagoTimer(const cGonzagoTimer& o) {
        mField_04 = 0;
        mVtbl = (void*)g_1465d54;   // vtable of the timer's base subobject
        *(u64*)&mElapsedLo = *(const u64*)&o.mElapsedLo;
        *(u64*)&mBaseLo = *(const u64*)&o.mBaseLo;
        mRunning = o.mRunning;
        mGetMs = o.mGetMs;
        mVtbl = (void*)g_1464450;   // vtable of cGonzagoTimer
    }
    ~cGonzagoTimer();           // 0x00b638b0 (out of line; the temporary's
                                // destructor is called at the end of each step)
    __forceinline cGonzagoTimer& operator=(const cGonzagoTimer& o) {
        *(u64*)&mElapsedLo = *(const u64*)&o.mElapsedLo;
        *(u64*)&mBaseLo = *(const u64*)&o.mBaseLo;
        mRunning = o.mRunning;
        mGetMs = o.mGetMs;
        return *this;
    }
};

struct tGrobShockData {         // 0x28 bytes
    int           mField_00;    // +0x00
    int           mField_04;    // +0x04
    cGonzagoTimer mTimer_08;    // +0x08

    // The copy constructor is user-provided (as in SPSimulatorUniverse.cpp), so
    // the temporary in partial_sort stays a real 0x28-byte object.
    __forceinline tGrobShockData(const tGrobShockData& o)
        : mField_00(o.mField_00), mField_04(o.mField_04), mTimer_08(o.mTimer_08) {}
};

typedef bool (__cdecl* ShockCompare)(const tGrobShockData&, const tGrobShockData&);

namespace eastl {
    // 0x01012330: make_heap<tGrobShockData*, ShockCompare>
    void make_heap(tGrobShockData* first, tGrobShockData* last, ShockCompare compare);
    // 0x01011900: adjust_heap<tGrobShockData*, int, tGrobShockData, ShockCompare>
    void adjust_heap(tGrobShockData* first, int holeIndex, int len, int differenceZero,
                     tGrobShockData value, ShockCompare compare);
    // 0x010123d0: sort_heap<tGrobShockData*, ShockCompare>
    void sort_heap(tGrobShockData* first, tGrobShockData* last, ShockCompare compare);
}

// @ 0x01012ff0
// Build flags that reproduce retail's frame: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// /GS-  (no /EHsc: the temporary's destructor must not produce an unwind frame;
// /GS-: the 0x28-byte local temporary must not be probed).
// Remaining diff (354 vs 357 bytes) is only in the adjust_heap value copy:
// retail stores the timer vtable twice (0x01465d54, then 0x01464450) and orders
// the local stores as [esp+0x10],ecx / [esp+0x14],edx / [esp+0x1c],<vptr> /
// xor edx,edx / [esp+0x20],edx, where ours reorders them and emits a single
// vtable store (category: schedule/regalloc).
void partial_sort_grobShock(tGrobShockData* first, tGrobShockData* middle,
                            tGrobShockData* last, ShockCompare compare)
{
    eastl::make_heap(first, middle, compare);

    for (tGrobShockData* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const tGrobShockData temp(*i);
            *i = *first;
            eastl::adjust_heap(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }

    eastl::sort_heap(first, middle, compare);
}
