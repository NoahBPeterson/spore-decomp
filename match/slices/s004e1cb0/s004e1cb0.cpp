// w1g1 slice s004e1cb0 -- a single 4711-byte /Od routine around 0x4e1cb0.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
//
// Large /Od body built from inlined EASTL containers; recorded as a compilable
// skeleton (see partial.txt).

typedef unsigned int uint32_t;

// @ 0x004e1cb0
void BigBody1cb0(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
}
