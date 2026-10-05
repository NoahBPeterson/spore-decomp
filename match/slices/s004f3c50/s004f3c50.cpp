// w1g1 slice s004f3c50 -- editor validity bitset intersection helper.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
struct Bits128 { uint32_t w[4]; };

inline bool AnyBit(const Bits128& x)
{
    for (unsigned int i = 0; i < 4; i++)
        if (x.w[i] != 0)
            return true;
    return false;
}

// ===========================================================================
// @ 0x004f3d60  (MATCH)
// Intersects two 4-word bit masks in place and reports whether the result is
// empty (all-zero).
// ===========================================================================
bool FUN_004f3d60(Bits128 a, Bits128 b)
{
    unsigned int i;
    for (i = 0; i < 4; i++)
        a.w[i] &= b.w[i];
    return !AnyBit(a);
}

// ===========================================================================
// @ 0x004f3c50  (INCOMPLETE skeleton)
// Resolves a resource by model type, builds the 128-bit mask from four ids and
// tests it against the resource's mask.
// ===========================================================================
bool FUN_004f3c50(int a, int b, int c, int d, int e)
{
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return false;
}
