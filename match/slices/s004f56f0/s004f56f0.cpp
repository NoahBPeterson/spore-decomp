// w1g1 slice s004f56f0 -- editor validity string/key/bitset helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
struct wstring { unsigned int find(wchar_t c, unsigned int pos); };
extern wstring g_15da7d4;

struct Key { int a; int pad; int c; };
struct Obj {
    int f0;
    int f1;
    bool Compare(const Key* k);
};
struct Bits {
    uint32_t w[4];
    Bits* Flip();
};

// ===========================================================================
// @ 0x004f56f0  (complete; not byte-exact)
// True when `c` is absent from the global validity string.
// ===========================================================================
bool FUN_004f56f0(wchar_t c)
{
    if (g_15da7d4.find(c, 0) != (unsigned int)-1)
        return false;
    return true;
}

// ===========================================================================
// @ 0x004f64d0  (complete; not byte-exact)
// Key comparison: k->c against f0 and k->a against f1.
// ===========================================================================
bool Obj::Compare(const Key* k)
{
    return k->c == f0 && k->a == f1;
}

// ===========================================================================
// @ 0x004f65d0  (complete; not byte-exact)
// Bitwise-NOT of all four words, returning the object.
// ===========================================================================
Bits* Bits::Flip()
{
    unsigned int i;
    for (i = 0; i < 4; i++)
        w[i] = ~w[i];
    return this;
}

// ===========================================================================
// @ 0x004f6510  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f6510(void* a, void* b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004f5720  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f5720(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004f5c60  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004f5c60(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
