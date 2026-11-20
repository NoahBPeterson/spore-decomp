// eastl::adjust_heap specialization used by SP::cSimulatorUniverse
// (adjust_heap_grob): sift-down over a 40-byte grob record, then the
// promote_heap tail call.
//
// The record is 40 bytes (SP::tGrobShockData): two ints at +0 and the
// SP::cGonzagoTimer subobject at +8 (vtable pointer +0x08, refcount +0x0c,
// 64-bit elapsed and base counters at +0x10/+0x18, a running flag at +0x20
// and the get-time callback at +0x24).  The canonical record header has not
// been recovered as a class, so the types below are local stand-ins with the
// layout and the inlined semantics the original code shows: the timer copy
// constructor points the vtable at the base timer's table (0x01465d54),
// zeroes the refcount, copies the payload and finally points the vtable at
// the record's own table (0x01464450); the timer assignment copies only the
// payload, keeping the destination's vtable and refcount.  Both counter
// pairs move as one 64-bit value, as the original does.
// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

extern const unsigned short g_grobBaseTable[];
extern const unsigned short g_grobTable[];

struct GrobTimer {
    const unsigned short* mpTable;   // +0x08
    int mRefCount;                   // +0x0c
    unsigned int mElapsedLo;         // +0x10
    unsigned int mElapsedHi;         // +0x14
    unsigned int mBaseLo;            // +0x18
    unsigned int mBaseHi;            // +0x1c
    char mRunning;                   // +0x20
    int mGetMs;                      // +0x24

    GrobTimer() : mpTable(g_grobBaseTable), mRefCount(0) {}

    GrobTimer(const GrobTimer& o) : mpTable(g_grobBaseTable), mRefCount(0)
    {
        mElapsedLo = o.mElapsedLo;
        mElapsedHi = o.mElapsedHi;
        mBaseLo = o.mBaseLo;
        mBaseHi = o.mBaseHi;
        mRunning = o.mRunning;
        mGetMs = o.mGetMs;
        mpTable = g_grobTable;
    }

    ~GrobTimer();

    GrobTimer& operator=(const GrobTimer& o)
    {
        *(unsigned long long*)&mElapsedLo = *(const unsigned long long*)&o.mElapsedLo;
        *(unsigned long long*)&mBaseLo = *(const unsigned long long*)&o.mBaseLo;
        mRunning = o.mRunning;
        mGetMs = o.mGetMs;
        return *this;
    }
};

struct Grob {
    int m00;                         // +0x00
    int m04;                         // +0x04
    GrobTimer mTimer;                // +0x08

    Grob(const Grob& o) : m00(o.m00), m04(o.m04), mTimer(o.mTimer) {}
};

typedef bool (*GrobCompare)(const Grob&, const Grob&);

void promote_heap(Grob* first, int topPosition, int position, Grob value, GrobCompare compare);

// @ 0x01011900
void adjust_heap_grob(Grob* first, int topPosition, int heapSize, int position, Grob value, GrobCompare compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    promote_heap(first, topPosition, position, value, compare);
}
