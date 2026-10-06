// Havok 3.1 chain constraint solver step: for a chain of n links (n+1 bodies), builds
// per-link 3x3 right-hand sides (forward elimination) then back-substitutes and applies impulses.
typedef unsigned int uint32_t;

struct Solver { char pad[0x40]; float dt; };
struct Chain {
    int pad0;
    int n;
    float stiff;     // 0x08
    float damp;      // 0x0c
    int off[1];      // 0x10: body offsets, n+1 entries
};

template<int K> __forceinline void Comp(const float* pa, const float* pb, const float* a, const float* b, const float* c, float& S, float& T)
{
    S = pb[0x50 / 4 + K] * c[K] + pa[0x50 / 4 + K] * b[K] + (pa[0x40 / 4 + K] - pb[0x40 / 4 + K]) * a[K];
    T = (pb[0x20 / 4 + K] - pb[0x50 / 4 + K]) * c[K] + (pa[0x20 / 4 + K] - pa[0x50 / 4 + K]) * b[K]
      + ((pa[0x10 / 4 + K] - pa[0x40 / 4 + K]) - (pb[0x10 / 4 + K] - pb[0x40 / 4 + K])) * a[K];
}

__forceinline float FwdRow(int row, const float* A, const float* B, const float* m, const float* l, const float* v,
                           float stiff, float fV, float fU)
{
    const float* a = m + row * 12;
    const float* b = a + 4;
    const float* c = a + 8;
    float S0, T0, S1, T1, S2, T2;
    Comp<0>(A, B, a, b, c, S0, T0);
    Comp<1>(A, B, a, b, c, S1, T1);
    Comp<2>(A, B, a, b, c, S2, T2);
    return stiff * a[3]
         - (((S0 * fV + fU * T0) + (fV * S2 + fU * T2)) + (S1 * fV + fU * T1))
         - (v[0] * l[row] + (v[2] * l[8 + row] + v[1] * l[4 + row]));
}

__forceinline void BackRow(int row, float v, float* A, float* B, const float* m, float* o)
{
    const float* a = m + row * 12;
    const float* b = a + 4;
    const float* c = a + 8;
    float fa = v * A[0x3c / 4];
    float fb = v * B[0x3c / 4];
    A[0x10 / 4] = fa * a[0] + A[0x10 / 4];
    A[0x14 / 4] = fa * a[1] + A[0x14 / 4];
    A[0x18 / 4] = fa * a[2] + A[0x18 / 4];
    B[0x10 / 4] = B[0x10 / 4] - fb * a[0];
    B[0x14 / 4] = B[0x14 / 4] - fb * a[1];
    B[0x18 / 4] = B[0x18 / 4] - fb * a[2];
    A[0x20 / 4] = (v * A[0x30 / 4]) * b[0] + A[0x20 / 4];
    A[0x24 / 4] = (v * A[0x34 / 4]) * b[1] + A[0x24 / 4];
    A[0x28 / 4] = (v * A[0x38 / 4]) * b[2] + A[0x28 / 4];
    B[0x20 / 4] = (v * B[0x30 / 4]) * c[0] + B[0x20 / 4];
    B[0x24 / 4] = (v * B[0x34 / 4]) * c[1] + B[0x24 / 4];
    B[0x28 / 4] = (v * B[0x38 / 4]) * c[2] + B[0x28 / 4];
    o[row] = v + o[row];
}

// @ 0x010b2890
void ChainSolve(Solver* solver, char* bodies, Chain* chain, float* mat, float* out)
{
    int n = chain->n;
    float* L = (float*)((char*)mat + n * 0x90);      // per-link 3x4 factor blocks
    float* V = (float*)((char*)mat + n * 0x120 + 0x10) - 4; // n+1 vectors, 4 floats each
    V[0] = 0; V[1] = 0; V[2] = 0; V[3] = 0;
    for (int i = 0; i < n; i++) {
        char* A = bodies + chain->off[i];
        char* B = bodies + chain->off[i + 1];
        float* m = mat + i * 36;
        float* l = L + i * 36;
        float* v = V + i * 4;
        float fV = chain->stiff * solver->dt;
        float fU = chain->damp;
        float r[3];
        r[0] = FwdRow(0, (float*)A, (float*)B, m, l, v, chain->stiff, fV, fU);
        r[1] = FwdRow(1, (float*)A, (float*)B, m, l, v, chain->stiff, fV, fU);
        r[2] = FwdRow(2, (float*)A, (float*)B, m, l, v, chain->stiff, fV, fU);
        float* nv = v + 4;
        nv[0] = r[1] * l[16] + (r[0] * l[12] + r[2] * l[20]);
        nv[1] = r[0] * l[13] + (r[1] * l[17] + r[2] * l[21]);
        nv[2] = r[0] * l[14] + (r[1] * l[18] + r[2] * l[22]);
        nv[3] = 0.0f;
    }

    float x0 = 0.0f, x1 = 0.0f, x2 = 0.0f;
    for (int i = n - 1; i >= 0; i--) {
        float* A = (float*)(bodies + chain->off[i]);
        float* B = (float*)(bodies + chain->off[i + 1]);
        float* m = mat + i * 36;
        float* l = L + i * 36;
        float* nv = V + (i + 1) * 4;
        float* o = (float*)((char*)out + i * 0xc);
        float t0 = nv[0] - (x1 * l[28] + (x0 * l[24] + x2 * l[32]));
        float t1 = nv[1] - (x0 * l[25] + (x2 * l[33] + x1 * l[29]));
        float t2 = nv[2] - (x0 * l[26] + (x2 * l[34] + x1 * l[30]));
        x0 = t0; x1 = t1; x2 = t2;
        BackRow(0, x0, A, B, m, o);
        BackRow(1, x1, A, B, m, o);
        BackRow(2, x2, A, B, m, o);
    }
}
