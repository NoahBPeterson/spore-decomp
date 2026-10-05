// w1g1 slice s0050bc80 -- transform/bbox helpers.
//
// Flags: /Od /Ob1 /MD /Gy /TP (integer); /arch:SSE where floats appear.

typedef unsigned int uint32_t;

struct SwapObj {
    char pad[0x58];
    uint32_t f58, f5c, f60, f64, f68;
};

// @ 0x0050bc80  (toggle a flag and swap two coordinate pairs)
void __fastcall ToggleSwap(SwapObj* s)
{
    s->f68 = s->f68 ^ 1;
    uint32_t t = s->f5c;
    s->f5c = s->f64;
    s->f64 = t;
    t = s->f58;
    s->f58 = s->f60;
    s->f60 = t;
}

// @ 0x0050bd10  (advance a value, clamp against a sibling's extent)
void __fastcall Advance(int self, int peer, float amount)
{
    *(float*)(self + 0x58) = *(float*)(self + 0x58) + amount;
    float* p = (float*)(self + 0x5c);
    float lim = *(float*)(peer + 100) - *(float*)(peer + 0x60);
    if (*p <= lim) {
        static float zero = 0.0f;
        p = &zero;
    }
    *(float*)(self + 0x5c) = *p;
}

// ---------------------------------------------------------------------------
// Helpers (masked relocations).
// ---------------------------------------------------------------------------
void BuildSomethingA(int a);                          // 0x0041bd50
void BuildSomethingC();                               // 0x004fde90
void* TriInterp3(void* out, void* w, void* v);        // 0x0041de40
void* VecAdd(void* out, void* a);                     // 0x0041dc10
void CopyV3(void* out, void* v);                      // 0x00436ce0

// ---------------------------------------------------------------------------
// @ 0x0050c230  (bbox query)
// ---------------------------------------------------------------------------
int* __fastcall BBoxQuery(int* self, int a, int* out, uint32_t* count, int* out2)
{
    self[0x11] = 0x7f7fffff;
    BuildSomethingC();
    if (out != 0) *out = self[0x11];
    if (count != 0) *count = (uint32_t)self[0x12] / 3;
    if (out2 != 0) *out2 = self[0x13];
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x0050c3b0  (ensure normals)
// ---------------------------------------------------------------------------
int __fastcall EnsureNormals(int self)
{
    int* p = *(int**)(self + 8);
    *(int*)(self + 0x14c) = p[0];
    *(int*)(self + 0x150) = p[1];
    *(int*)(self + 0x154) = p[2];
    *(int*)(self + 0x158) = p[0];
    *(int*)(self + 0x15c) = p[1];
    *(int*)(self + 0x160) = p[2];
    uint32_t i = 1;
    int n = *(int*)(self + 0xc);
    while (i < (uint32_t)((n - p[0]) / 0xc)) {
        BuildSomethingA((int)(i * 0xc + *(int*)(self + 8)));
        ++i;
    }
    return self + 0x14c;
}

// ---------------------------------------------------------------------------
// @ 0x0050c490  (barycentric interpolation, one table)
// ---------------------------------------------------------------------------
void* __fastcall InterpA(int self, void* out, int tri, float u, float v)
{
    int base = *(int*)(self + 8);
    int* idx = (int*)(*(int*)(self + 0x58) + tri * 0xc);
    float w2 = v;
    float w1 = u;
    float w0 = (1.0f - u) - v;
    char t1[12], t2[12], t3[12], t4[12], t5[12];
    TriInterp3(t1, &w2, (void*)(idx[2] * 0xc + base));
    TriInterp3(t2, &w1, (void*)(idx[1] * 0xc + base));
    TriInterp3(t3, &w0, (void*)(idx[0] * 0xc + base));
    VecAdd(t4, t3);
    void* r = VecAdd(t5, t4);
    *(uint32_t*)out = *(uint32_t*)r;
    *((uint32_t*)out + 1) = *((uint32_t*)r + 1);
    *((uint32_t*)out + 2) = *((uint32_t*)r + 2);
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0050c5a0  (barycentric interpolation, second table)
// ---------------------------------------------------------------------------
void* __fastcall InterpB(int self, void* out, int tri, float u, float v)
{
    int base = *(int*)(self + 0x1c);
    int* idx = (int*)(*(int*)(self + 0x6c) + tri * 0xc);
    float w2 = v;
    float w1 = u;
    float w0 = (1.0f - u) - v;
    char t1[12], t2[12], t3[12], t4[12], t5[12];
    TriInterp3(t1, &w2, (void*)(idx[2] * 0xc + base));
    TriInterp3(t2, &w1, (void*)(idx[1] * 0xc + base));
    TriInterp3(t3, &w0, (void*)(idx[0] * 0xc + base));
    VecAdd(t4, t3);
    void* r = VecAdd(t5, t4);
    uint32_t tmp[3] = { *(uint32_t*)r, *((uint32_t*)r + 1), *((uint32_t*)r + 2) };
    CopyV3(out, tmp);
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0050bd90 / 0x0050bff0  (PARTIAL skeletons: 0.6 KB traversals)
// ---------------------------------------------------------------------------
void __cdecl TraverseA(int* a, void** b, unsigned char c, uint32_t* d, void* e, void* f, void* g, void* h)
{
    (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; (void)g; (void)h;
}
void __fastcall TraverseB(int self, void* a, float* b, void* c, void* d, void* e, void* f)
{
    (void)self; (void)a; (void)b; (void)c; (void)d; (void)e; (void)f;
}
