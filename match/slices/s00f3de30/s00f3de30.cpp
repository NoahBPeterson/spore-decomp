// Slice s00f3de30: simulator container/animation helpers.
// Optimized module: /O2 /MD /Gy /EHsc /TP.
// The two self-contained forwarding functions are reconstructed; the rest are
// skeletons (eastl::vector construction, hashtable lookups, large update paths).
typedef unsigned int uint32_t;

struct cX {
    virtual void v00();
    void  FUN_00f3e590(void* p, int flag);
    void* FUN_00f3e8a0(int key);
    float FUN_00f3e910();
    void  FUN_00f3e6b0(void* p);
    void* FUN_00f3e900(int* p);
    int   FUN_00f3ec90(int arg);
};

// Skeleton targets (noinline so forwarding callers keep their tail calls).
extern int g_dummy_s00f3de30;
extern void g_opaque_sink(int);

// ---------------------------------------------------------------------------
// @ 0x00f3e6b0
// ---------------------------------------------------------------------------
void cX::FUN_00f3e6b0(void* p) {
    FUN_00f3e590(p, 1);
    FUN_00f3e590(p, 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f3e900  (tail thunk to FUN_00f3e8a0 with p->field_1c)
// ---------------------------------------------------------------------------
void* cX::FUN_00f3e900(int* p) {
    return FUN_00f3e8a0(*(int*)((char*)p + 0x1c));
}

// ---------------------------------------------------------------------------
// @ 0x00f3ec90
// ---------------------------------------------------------------------------
int cX::FUN_00f3ec90(int arg) {
    (void)arg;
    if (1.0f <= FUN_00f3e910()) return 0;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00f3e590  (skeleton)
// ---------------------------------------------------------------------------
__declspec(noinline) void cX::FUN_00f3e590(void* p, int flag) {
    g_opaque_sink(flag); (void)p;
}

// ---------------------------------------------------------------------------
// @ 0x00f3e8a0  (skeleton: hashtable lower_bound)
// ---------------------------------------------------------------------------
__declspec(noinline) void* cX::FUN_00f3e8a0(int key) {
    g_opaque_sink(key);
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f3e910  (skeleton)
// ---------------------------------------------------------------------------
__declspec(noinline) float cX::FUN_00f3e910() {
    g_opaque_sink(0);
    return 0.0f;
}

// ---------------------------------------------------------------------------
// Remaining skeletons (listed in partial.txt).
// ---------------------------------------------------------------------------
int g_dummy_s00f3de30 = 0;
__declspec(noinline) void FUN_00f3de30() { g_dummy_s00f3de30 += 1; }
__declspec(noinline) void FUN_00f3dec0() { g_dummy_s00f3de30 += 2; }
__declspec(noinline) void FUN_00f3df50() { g_dummy_s00f3de30 += 3; }
__declspec(noinline) void FUN_00f3e2b0() { g_dummy_s00f3de30 += 4; }
__declspec(noinline) void FUN_00f3e3b0() { g_dummy_s00f3de30 += 5; }
__declspec(noinline) void FUN_00f3e6d0() { g_dummy_s00f3de30 += 6; }
__declspec(noinline) void FUN_00f3e810() { g_dummy_s00f3de30 += 7; }
__declspec(noinline) void FUN_00f3ecb0() { g_dummy_s00f3de30 += 8; }
