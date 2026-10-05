// w1g1 slice s004f2d40 -- editor validity table accessors.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
struct Entry { int a; int b; };
extern Entry g_150c920[];
extern int g_150c924[];

// ===========================================================================
// @ 0x004f3c40  (MATCH)
// Returns the first field of the i-th 8-byte global entry.
// ===========================================================================
int FUN_004f3c40(int i)
{
    return g_150c920[i].a;
}

// ===========================================================================
// @ 0x004f3b40  (complete; not byte-exact)
// Picks the entry with the largest metric among indices set in both bit masks
// (28 indices); 0x1c when none.
// ===========================================================================
struct Bits128 { uint32_t w[4]; };

int FUN_004f3b40(Bits128 a, Bits128 b)
{
    int best = -1;
    bool found = false;
    unsigned int i;
    int bestIdx;
    for (i = 0; i < 0x1c; i++) {
        bool inA = false;
        if (i < 0x80)
            inA = (a.w[i >> 5] & (1u << (i % 0x20))) != 0;
        if (inA) {
            bool inB = false;
            if (i < 0x80)
                inB = (b.w[i >> 5] & (1u << (i % 0x20))) != 0;
            if (inB) {
                int cand = g_150c924[i * 2];
                if (cand > best) {
                    best = cand;
                    bestIdx = i;
                    found = true;
                }
            }
        }
    }
    if (found)
        return bestIdx;
    return 0x1c;
}

// ===========================================================================
// @ 0x004f2d40  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f2d40(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f31c0  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f31c0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f3650  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f3650(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
