// w1g1 slice s004eb270 -- editor validity key seeding + record comparison.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
struct DeclareParam { int key; int a; int b; };
void FUN_004ea920(int, int, int);
extern int g_150ca00[];

// ===========================================================================
// @ 0x004eb930  (MATCH)
// Three-field equality of two declare-param records.
// ===========================================================================
bool FUN_004eb930(const DeclareParam& a, const DeclareParam& b)
{
    int r;
    if (a.key == b.key && a.a == b.a && a.b == b.b)
        r = 1;
    else
        r = 0;
    return *(bool*)&r;
}

// ===========================================================================
// @ 0x004eb980  (MATCH)
// Seeds the validity key table: one entry per registered model type, then two
// special entries.
// ===========================================================================
void FUN_004eb980(void)
{
    int v33 = 1;
    int n40 = 0;
    int len = 0x1b;
    for (; n40 < len; n40++)
        FUN_004ea920(g_150ca00[n40], 1, 0);
    FUN_004ea920(0x9ea3031a, 1, 0x5bf8f774);
    FUN_004ea920(0x9ea3031a, 1, 0xe46c381e);
}

// ===========================================================================
// @ 0x004eb270  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004eb270(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004eba00  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004eba00(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
