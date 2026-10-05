// Slice s00784420: SP::AddGroundBounce (0x784420) -- ground-bounce SH term:
// build the diagonal basis, multiply the SH sets, mirror in Z, apply diffuse
// reflection and accumulate.  /O2 /MD /Gy /EHsc /TP /arch:SSE module.
#include "types.h"
#include <xmmintrin.h>

extern char kBasisTriples3, kBasisTriples4, kBasisTriples5;

void FUN_00783380(float* out);                       // build 7 SH constants
void SP_MultiplySH(int n, int a, int b, void* out, char* triples);
void SP_MirrorSHInZ(int n, float* data);
void SP_ApplyDiffuseReflection(int n, const float* lit, const float* diff, float* out);
void FUN_0011e073e(void* buf, int zero, unsigned int size);

// @ 0x00784420
void SP_AddGroundBounce(int order, float* sh, const float* lit, const float* diff)
{
    int n = order * order;
    float consts[7];
    float basis[103];
    float work[100];

    FUN_00783380(consts);
    FUN_0011e073e(work, 0, (unsigned int)(n * 0x10));

    for (int i = 0; i < order; ++i) {
        int idx = (i + 1) * i;
        *(__m128*)(work + idx * 4) = _mm_set1_ps(consts[i]);
    }

    switch (order) {
    case 3: SP_MultiplySH(9, (int)sh, (int)work, basis, &kBasisTriples3); break;
    case 4: SP_MultiplySH(0x10, (int)sh, (int)work, basis, &kBasisTriples4); break;
    case 5: SP_MultiplySH(0x19, (int)sh, (int)work, basis, &kBasisTriples5); break;
    }

    if (0 < n) {
        float* dst = sh;
        float* src = basis;
        for (int i = n * 4; i != 0; --i)
            *dst++ = *src++;
    }

    SP_MirrorSHInZ(order, sh);
    SP_ApplyDiffuseReflection(order, lit, diff, sh);

    if (0 < n) {
        float* d = sh;
        float* s = basis;
        for (int i = n; i != 0; --i) {
            _mm_store_ps(d, _mm_add_ps(_mm_load_ps(s), _mm_load_ps(d)));
            d += 4;
            s += 4;
        }
    }
}
