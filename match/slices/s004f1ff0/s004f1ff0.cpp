// w1g1 slice s004f1ff0 -- editor validity float metric helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
float FUN_004f1ff0(int a);

// ===========================================================================
// @ 0x004f21e0  (complete; not byte-exact)
// True when the metric of `a` is <= `b`.  cl emits a double-width comisd here
// where the original used a single-precision comiss.
// ===========================================================================
bool FUN_004f21e0(int a, int b)
{
    float f = FUN_004f1ff0(a);
    if (f <= (float)b)
        return true;
    return false;
}

// ===========================================================================
// @ 0x004f1ff0  (INCOMPLETE skeleton)
// ===========================================================================
float FUN_004f1ff0(int a)
{
    (void)a;
    return 0.0f;
}

// ===========================================================================
// @ 0x004f2210  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f2210(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f2610  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f2610(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
