// Slice s006d35a0: bake evaluators (dot tail).
#include "../s006ccf50/s006ccf50.h"

// @ 0x006d35a0  uv4u16 / colour4f / dot
// NOT byte-exact and NOT yet equivalent: the original's tail is guarded by an axis-length test
// (zero axis -> SVG-arcto conic path calling 0x0042d8b0/0x004f9a60), but the guard sits in a code
// region the oracle cannot observe, so the only recoverable evidence is the oracle's mem-pool
// writes.  The dot tail below matches the reachable path; the residual mem-pool mismatch is the
// unmodelled guard.  See nonmatching.txt / work/match/scratch_s006d35a0_fixlog.txt.
bool Bake_6d35a0(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,
                 float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)
{
    Elem32* base = table->mBegin;
    Handle hA = base[index].handle;
    Handle hB;
    if (handleIndex >= 0)
        hB.Assign(&base[handleIndex].handle);
    if (count != 0)
    {
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
        float* o = out;
        BakeEntry* e = entries;        int n = count;
        do
        {
            uint32_t u[4];
            uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);
            u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3;
            float color[4];
            float* c = (float*)(hB.b + hB.d * e->f8);
            color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3];
            float* ps = (float*)(pos->base + pos->stride * e->f0);
            float p3[3];
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
            float res[3];
            float scratch[3];
            FUN_006c4200(res, scratch, p3, axisDir, color, (void*)u, param10);
            float scale = scaleInfo->scale;
            o[0] = (res[0] * axis[0] + axis[2]) * scale;
            o[1] = (1.0f - (res[1] * axis[1] + axis[3])) * scale;
            o += 2;
            e += 1;
        } while (--n);
    }
    return true;
}
DEFINE_BAKE(Bake_6d38b0, 2, 4, 0, 3, 1)   // @ 0x006d38b0  uv4u8  / const    / dot
DEFINE_BAKE(Bake_6d3b90, 2, 2, 1, 3, 1)   // @ 0x006d3b90  uv2u16 / const    / dot
DEFINE_BAKE(Bake_6d3e30, 2, 4, 1, 3, 1)   // @ 0x006d3e30  uv4u16 / const    / dot
DEFINE_BAKE(Bake_6d4110, 3, 4, 0, 2, 1)   // @ 0x006d4110  uv4u8  / colour2f / dot
