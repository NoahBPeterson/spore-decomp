// Slice s006cdca0: second group of bake evaluators.
// Bake_6ce860 is hand-written at the end (the shared macro's dot tail is x87, retail is SSE).
#include "../s006ccf50/s006ccf50.h"

// uv4u16 / colour4f  / acos(weight res.z)
DEFINE_BAKE(Bake_6cdca0, 0, 4, 1, 1, 0)   // @ 0x006cdca0
// uv4u8  / const     / dot
DEFINE_BAKE(Bake_6ce000, 2, 4, 0, 3, 1)   // @ 0x006ce000
// uv2u16 / const     / dot
DEFINE_BAKE(Bake_6ce2e0, 2, 2, 1, 3, 1)   // @ 0x006ce2e0
// uv4u16 / const     / dot
DEFINE_BAKE(Bake_6ce580, 2, 4, 1, 3, 1)   // @ 0x006ce580
// uv4u8  / colour2f  / dot
// The dot tail must do every multiply/add/subtract in SSE singles like the retail
// (mulss/addss/subss); the shared macro's plain C++ arithmetic keeps x87 excess
// precision and yields 0 where the retail yields -Inf on float-special inputs.
// @ 0x006ce860
bool Bake_6ce860(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,
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
        float* o = out;
        BakeEntry* e = entries;
        int n = count;
        do
        {
            uint32_t u[4];
            uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);
            u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3;
            float color[4];
            float* c = (float*)(hB.b + hB.d * e->f8);
            color[0] = c[0]; color[1] = c[1]; color[2] = 0.0f; color[3] = 0.0f;
            float* ps = (float*)(pos->base + pos->stride * e->f0);
            float p3[3];
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];
            float res[3];
            float scratch[3];
            FUN_006c3780(res, scratch, p3, axisDir, color, u, param10);
            float scale = scaleInfo->scale;
            o[0] = BakeMulSS(BakeAddSS(BakeMulSS(axis[0], res[0]), axis[2]), scale);
            o[1] = BakeMulSS(BakeSubSS(1.0f, BakeAddSS(BakeMulSS(res[1], axis[1]), axis[3])), scale);
            o += 2;
            e += 1;
        } while (--n);
    }
    return true;
}
