// w1g1 slice s0050bc80 -- transform/bbox helpers.
//
// Flags: /Od /Ob1 /MD /Gy /TP (integer); /arch:SSE where floats appear.

typedef unsigned int uint32_t;

struct SwapObj {
    char pad[0x58];
    uint32_t f58, f5c, f60, f64, f68;
};

// @ 0x0050bc80  (toggle a flag and swap two coordinate pairs; returns &f58)
void* __fastcall ToggleSwap(SwapObj* s)
{
    s->f68 = s->f68 ^ 1;
    uint32_t t = s->f5c;
    s->f5c = s->f64;
    s->f64 = t;
    t = s->f58;
    s->f58 = s->f60;
    s->f60 = t;
    return &s->f58;
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
void* __cdecl TriInterp3(void* out, void* w, void* v);        // 0x0041de40
void* __cdecl VecAdd(void* out, void* a, void* b);            // 0x0041dc10
void* __cdecl CopyV3(void* out, void* v);                     // 0x00436ce0

// thiscall helpers: ecx carries the base pointer, stack args are callee-popped.
struct Thiscall {
    void BuildSomethingC(int a, int b);   // 0x004fde90
    void BuildSomethingA(void* v);        // 0x0041bd50
    void Reset409c00();                   // 0x00409c00
    char IsReady();                       // 0x00526430
};

struct PeerVec {
    void push_back(const int& v);         // 0x00422380
};

// ---------------------------------------------------------------------------
// @ 0x0050bd10  (append peer, advance value, clamp against the peer extent)
// ---------------------------------------------------------------------------
void __fastcall Advance(char* self, int unused, int peer, float amount)
{
    ((PeerVec*)self)->push_back(peer);
    *(float*)(self + 0x58) = *(float*)(self + 0x58) + amount;
    float lim = *(float*)(peer + 0x64) - *(float*)(peer + 0x60);
    float* p = (float*)(self + 0x5c);
    float* q;
    if (*p > lim)
        q = p;
    else
        q = &lim;
    *(float*)(self + 0x5c) = *q;
}

// ---------------------------------------------------------------------------
// @ 0x0050c230  (bbox/weights + barycentric interpolation, table at self+0xc)
// ---------------------------------------------------------------------------
float* __fastcall BBoxQuery(char* self, int unused, float* out, int tri,
                            float* outBox, uint32_t* count, int* out2)
{
    *(float*)(self + 0x44) = 3.4028234663852886e+38f;
    ((Thiscall*)self)->BuildSomethingC(*(int*)self, tri);
    if (outBox != 0)
        *outBox = *(float*)(self + 0x44);
    if (count != 0)
        *count = *(uint32_t*)(self + 0x48) / 3;
    if (out2 != 0) {
        out2[0] = *(int*)(self + 0x4c);
        out2[1] = *(int*)(self + 0x50);
    }
    int i = *(int*)(self + 0x48);
    int* table = *(int**)(self + 0xc);
    char* base = *(char**)(self + 8);
    float w1 = *(float*)(self + 0x4c);
    float w2 = *(float*)(self + 0x50);
    float w0 = (1.0f - w1) - w2;
    float t1[3], t2[3], t3[3], t4[3], t5[3];
    float* r = (float*)VecAdd(t5,
                     VecAdd(t4,
                         TriInterp3(t3, &w0, base + table[i + 0] * 0xc),
                         TriInterp3(t2, &w1, base + table[i + 1] * 0xc)),
                     TriInterp3(t1, &w2, base + table[i + 2] * 0xc));
    out[0] = r[0];
    out[1] = r[1];
    out[2] = r[2];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0050c3b0  (ensure normals)
// ---------------------------------------------------------------------------
int __fastcall EnsureNormals(char* self)
{
    if (((Thiscall*)(self + 8))->IsReady()) {
        ((Thiscall*)(self + 0x14c))->Reset409c00();
        return (int)(self + 0x14c);
    }
    float* p = *(float**)(self + 8);
    float* dst = (float*)(self + 0x14c);
    dst[0] = p[0];
    dst[1] = p[1];
    dst[2] = p[2];
    dst[3] = p[0];
    dst[4] = p[1];
    dst[5] = p[2];
    int n = (*(int*)(self + 0xc) - *(int*)(self + 8)) / 0xc;
    uint32_t i = 1;
    while (i < (uint32_t)n) {
        ((Thiscall*)(self + 0x14c))->BuildSomethingA((char*)*(void**)(self + 8) + i * 0xc);
        ++i;
    }
    return (int)(self + 0x14c);
}

// ---------------------------------------------------------------------------
// @ 0x0050c490  (barycentric interpolation, table at self+0x58)
// ---------------------------------------------------------------------------
float* __fastcall InterpA(char* self, int unused, float* out, int tri, float u, float v)
{
    char* base = *(char**)(self + 8);
    int* idx = (int*)(*(int*)(self + 0x58) + tri * 0xc);
    float w1 = u;
    float w2 = v;
    float w0 = (1.0f - u) - v;
    float t1[3], t2[3], t3[3], t4[3], t5[3];
    float* r = (float*)VecAdd(t5,
                     VecAdd(t4,
                         TriInterp3(t3, &w0, base + idx[0] * 0xc),
                         TriInterp3(t2, &w1, base + idx[1] * 0xc)),
                     TriInterp3(t1, &w2, base + idx[2] * 0xc));
    out[0] = r[0];
    out[1] = r[1];
    out[2] = r[2];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0050c5a0  (barycentric interpolation, table at self+0x6c)
// ---------------------------------------------------------------------------
float* __fastcall InterpB(char* self, int unused, float* out, int tri, float u, float v)
{
    char* base = *(char**)(self + 0x1c);
    int* idx = (int*)(*(int*)(self + 0x6c) + tri * 0xc);
    float w1 = u;
    float w2 = v;
    float w0 = (1.0f - u) - v;
    float t1[3], t2[3], t3[3], t4[3], t5[3];
    float* r = (float*)VecAdd(t5,
                     VecAdd(t4,
                         TriInterp3(t3, &w0, base + idx[0] * 0xc),
                         TriInterp3(t2, &w1, base + idx[1] * 0xc)),
                     TriInterp3(t1, &w2, base + idx[2] * 0xc));
    float tmp[3];
    tmp[0] = r[0];
    tmp[1] = r[1];
    tmp[2] = r[2];
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
