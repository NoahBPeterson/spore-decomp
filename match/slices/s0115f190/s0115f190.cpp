// s0115f190 -- rw::audio::core FFT finishing stage (companion of ComplexFFTForward).
//
// Reconstructed from the disassembly in work/match/scratch_s0115f190_cards.txt.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (same rw::audio::core
// module as slices s0115e4c0 / s0115f2a0; SSE scalar math).
//
// The routine runs the forward transform, mirrors the DC bin to data[n] (n = 2 * 2^log2n),
// then folds the two halves of the spectrum with the cos/sin tables (a complex multiply by
// e^-j*pi*k/half) walking q backwards from data+n and the tables forwards.
//
// STATUS: reconstructed in full but NOT byte-exact (183-byte diff; see nonmatching.txt).
// The residual is register allocation / scheduling only: the original folds the cos table
// pointer into the sin pointer ([sinT + (cosT - sinT)]) which frees ebx for log2n; MSVC here
// keeps two live pointers, so the callee-saved assignment and the xmm schedule differ.
#include "types.h"

// Precomputed tables live behind the header; the offsets are relative to the header.
struct FftTable {
    int log2n;          // +0x00
    int unk04;          // +0x04
    int unk08;          // +0x08
    int cosOffset;      // +0x0c  float cos[]
    int sinOffset;      // +0x10  float sin[]
    int bitrevOffset;   // +0x14  int   bitrev[]
};

void ComplexFFTForward(FftTable* table, float* data);   // 0x0115e4c0

// @ 0x0115f190
void __cdecl FUN_0115f190(FftTable* table, float* data)
{
    int log2n = table->log2n;
    const float* cosT = (const float*)((char*)table + table->cosOffset);
    const float* sinT = (const float*)((char*)table + table->sinOffset);

    ComplexFFTForward(table, data);

    int n = 1 << (log2n + 1);
    data[n] = data[0];
    data[n + 1] = data[1];
    float* q = data + n;
    int half = n >> 1;
    int i = 0;
    if (half >= 0) {
        do {
            float v12 = *cosT;
            float f10 = *q + data[i];
            float f7 = data[i] - *q;
            float f9 = data[i + 1] - q[1];
            float f11 = data[i + 1] + q[1];
            float f8 = *sinT * f7;
            f7 = v12 * f7;
            float f13 = *sinT * f11;
            v12 = v12 * f11;
            data[i] = ((f10 - f8) + v12) * 0.5f;
            data[i + 1] = ((f9 - f7) - f13) * 0.5f;
            *q = ((f8 + f10) - v12) * 0.5f;
            q[1] = ((-f9 - f7) - f13) * 0.5f;
            i += 2;
            q -= 2;
            cosT++;
            sinT++;
        } while (i <= half);
    }
}
