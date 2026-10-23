// cSPTransform / camera-space transform helpers (slice s00a7e3b0).
// Built with VS2008 SP1 (cl 15.00.30729.01) /O2 /MD /Gy /TP /arch:SSE /fp:fast: the bodies mix
// scalar SSE (movss/addss/subss/mulss/divss) with x87 (fld/fmul/fsqrt/fcompi) for the double-rounding
// vector lengths, so they only match cl 15.00 with fast floats.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// Extern helpers / callees (resolved by their FUN_<va> / method name)
// ---------------------------------------------------------------------------
extern float g_1457c90;   // 0x01457c90  -0.8f
extern float g_1486374;   // 0x01486374   0.8f
extern float g_13f11c8;   // 0x013f11c8   1e-06f
extern float g_1485720;   // 0x01485720   1.0f

// x87 vector length: SQRT(products summed in extended precision), stored as float
static float X87Len3(float a, float b, float c)
{
    float r;
    __asm { fld a }
    __asm { fmul st(0), st(0) }
    __asm { fld b }
    __asm { fmul st(0), st(0) }
    __asm { faddp st(1), st }
    __asm { fld c }
    __asm { fmul st(0), st(0) }
    __asm { faddp st(1), st }
    __asm { fsqrt }
    __asm { fstp r }
    return r;
}

// thiscall helpers on the object whose vtable the functions dispatch through
struct CspBase
{
    bool GetPos(void* out, void* p1, void* p2, void* p3);   // 0x007cda70  (vtable +0x10 target)
};

struct Camera
{
    uint32_t FUN_00a7eba0(int mask, int p3, int p4, float* outDir, int p6, int p7);  // 0x00a7eba0
    uint32_t FUN_00a7eec0(int p2, int p3);                                           // 0x00a7eec0
};

extern void __cdecl FUN_00a81b80(void* m, void* basis);           // 0x00a81b80
extern void* __cdecl FUN_00472b80(void* m, void* basis, int w);   // 0x00472b80
extern void* __cdecl FUN_007dcb00(void* a, void* b, void* out);   // 0x007dcb00
extern bool  __cdecl FUN_00a7cfb0(void* out, void* in, void* p, void* out2); // 0x00a7cfb0
extern void  __cdecl FUN_007cda70(void* m);                       // 0x007cda70
extern void  __cdecl FUN_0093aa70(void* p, void* val, int n, int z); // 0x0093aa70 write
extern void  __cdecl FUN_0093ab10(void* p, void* val, int n, int z); // 0x0093ab10 write
extern void  __cdecl FUN_007ec580(void* p, void* v);              // 0x007ec580

struct cSPTransform
{
    void operator=(cSPTransform* other);                          // 0x00537dc0
};

// ---------------------------------------------------------------------------
// @ 0x00a7e3b0
// ---------------------------------------------------------------------------
uint32_t __stdcall FUN_00a7e3b0(float* pos, float* outPos, float* outDir,
                                uint32_t* outQuat, uint16_t* tf)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    float scale = *(float*)((char*)tf + 0x10);
    float sx = px, sy = py, sz = pz;

    if (scale != 1.0f || (*tf & 6) != 0)
    {
        if ((*tf & 2) != 0)
        {
            sx = (*(float*)((char*)tf + 0x14) * py + *(float*)((char*)tf + 0x1c) * pz) +
                 *(float*)((char*)tf + 0x0c) * px;
            sy = (*(float*)((char*)tf + 0x18) * py + *(float*)((char*)tf + 0x20) * pz) +
                 *(float*)((char*)tf + 0x10) * px;
            sz = (*(float*)((char*)tf + 0x1c) * py + *(float*)((char*)tf + 0x24) * pz) +
                 *(float*)((char*)tf + 0x14) * px;
        }
        px = *(float*)((char*)tf + 0x04) + scale * sx;
        py = *(float*)((char*)tf + 0x08) + scale * sy;
        pz = *(float*)((char*)tf + 0x0c) + scale * sz;
    }

    float d0 = px - *(float*)((char*)tf + 0x28);
    float d1 = py - *(float*)((char*)tf + 0x2c);
    float d2 = (pz - *(float*)((char*)tf + 0x30)) + g_13f11c8;
    float radius = *(float*)((char*)tf + 0x34);

    float len = X87Len3(d0, d1, d2);
    if (len >= g_13f11c8)
    {
        float inv = 1.0f / len;
        d0 *= inv;
        d1 *= inv;
        d2 *= inv;

        float wx = *(float*)((char*)tf + 0x28) + d0 * radius;
        float wy = *(float*)((char*)tf + 0x2c) + d1 * radius;
        float wz = *(float*)((char*)tf + 0x30) + d2 * radius;

        float r0 = d0, r1 = d1, r2 = d2;
        if (*(float*)((char*)tf + 0x10) != 1.0f || (*tf & 6) != 0)
        {
            FUN_007cda70(&wx);
            if ((*tf & 2) != 0)
            {
                r0 = (*(float*)((char*)tf + 0x1c) * r2 + *(float*)((char*)tf + 0x18) * r1) +
                     *(float*)((char*)tf + 0x14) * r0;
                r1 = (*(float*)((char*)tf + 0x20) * r2 + *(float*)((char*)tf + 0x1c) * r1) +
                     *(float*)((char*)tf + 0x18) * r0;
                r2 = (*(float*)((char*)tf + 0x24) * r2 + *(float*)((char*)tf + 0x20) * r1) +
                     *(float*)((char*)tf + 0x1c) * r0;
            }
        }

        outPos[0] = wx; outPos[1] = wy; outPos[2] = wz;
        if (outDir != 0)
        {
            outDir[0] = r0; outDir[1] = r1; outDir[2] = r2;
        }
        if (outQuat != 0)
        {
            float basis[9];
            FUN_00a81b80(&d0, basis);
            void* q = FUN_00472b80(&r0, basis, 0);
            outQuat[0] = ((uint32_t*)q)[0];
            outQuat[1] = ((uint32_t*)q)[1];
            outQuat[2] = ((uint32_t*)q)[2];
            outQuat[3] = ((uint32_t*)q)[3];
        }
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00a7e740  cSPTransform::Assign / operator=
// ---------------------------------------------------------------------------
void __stdcall FUN_00a7e740(int unused, int unused2, cSPTransform* src, cSPTransform* dst)
{
    dst->operator=(src);
}

// ---------------------------------------------------------------------------
// @ 0x00a7e760
// ---------------------------------------------------------------------------
uint32_t __stdcall FUN_00a7e760(int unused, int out4, float* pos, float* out, uint8_t* tf)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2];
    float wx = px, wy = py, wz = pz;

    if ((*tf & 2) != 0)
    {
        wx = (*(float*)(tf + 0x2c) * pz + *(float*)(tf + 0x20) * py) +
             *(float*)(tf + 0x14) * px;
        wy = (*(float*)(tf + 0x30) * pz + *(float*)(tf + 0x24) * py) +
             *(float*)(tf + 0x18) * px;
        wz = (*(float*)(tf + 0x34) * pz + *(float*)(tf + 0x28) * py) +
             *(float*)(tf + 0x1c) * px;
    }
    float scale = *(float*)(tf + 0x10);
    float lx = *(float*)(tf + 0x04) + scale * wx;
    float ly = *(float*)(tf + 0x08) + scale * wy;
    float lz = *(float*)(tf + 0x0c) + scale * wz;

    float* pv = &wx;
    if (!FUN_00a7cfb0(&wx, &lx, (void*)unused, &wx))
        return 0;

    FUN_007cda70(&lx);
    if ((*tf & 2) != 0)
    {
        float a = *(float*)(tf + 0x14) * wx;
        float b = *(float*)(tf + 0x1c) * wz;
        float c = *(float*)(tf + 0x24) * wy;
        wx = (*(float*)(tf + 0x18) * wy + *(float*)(tf + 0x1c) * wz) + *(float*)(tf + 0x14) * wx;
        wy = (*(float*)(tf + 0x20) * wx + *(float*)(tf + 0x24) * wy) + *(float*)(tf + 0x18) * wz;
        wz = (*(float*)(tf + 0x28) * wy + *(float*)(tf + 0x2c) * wx) + *(float*)(tf + 0x1c) * wz;
        (void)a; (void)b; (void)c;
    }
    out[0] = lx; out[1] = ly; out[2] = lz;
    out[3] = wx; out[4] = wy; out[5] = wz;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00a7e980
// ---------------------------------------------------------------------------
uint32_t __stdcall FUN_00a7e980(float* pos, float* outPos, float* outDir, uint32_t* outQuat)
{
    float px = pos[0];
    float py = pos[1];
    float pz = pos[2] + g_13f11c8;

    float na = px - -0.8f;
    float lenA = X87Len3(na, py, pz);

    float mc = px - 0.8f;
    float lenB = X87Len3(mc, py, pz);

    float inv, vx, vz, qx;
    if (lenB <= lenA)
    {
        inv = 1.0f / lenB;
        vx = inv * mc;
        vz = pz * inv;
        qx = vx + 0.8f;
    }
    else
    {
        inv = 1.0f / lenA;
        vx = inv * na;
        vz = pz * inv;
        qx = vx - 0.8f;
    }
    float vy = inv * py;

    outPos[0] = qx; outPos[1] = vy; outPos[2] = vz;
    if (outDir != 0)
    {
        outDir[0] = vx; outDir[1] = vy; outDir[2] = vz;
    }
    if (outQuat != 0)
    {
        float basis[9];
        FUN_00a81b80(&vx, basis);
        void* q = FUN_00472b80(&qx, basis, 0);
        outQuat[0] = ((uint32_t*)q)[0];
        outQuat[1] = ((uint32_t*)q)[1];
        outQuat[2] = ((uint32_t*)q)[2];
        outQuat[3] = ((uint32_t*)q)[3];
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00a7eb60
// ---------------------------------------------------------------------------
int __cdecl FUN_00a7eb60(int* begin, int* end, int count)
{
    while (begin != end)
    {
        int obj = *begin;
        if (obj != 0)
        {
            int* vtbl = *(int**)obj;
            typedef void (__thiscall *Fn)(void*);
            Fn fn = (Fn)vtbl[0];
            fn((void*)obj);
        }
        begin += 6;
        count += 0x18;
    }
    return count;
}

// ---------------------------------------------------------------------------
// @ 0x00a7eba0
// ---------------------------------------------------------------------------
uint32_t Camera::FUN_00a7eba0(int mask, int p3, int p4, float* outDir, int p6, int p7)
{
    float dx = (float)p7;
    float dy = (float)p6;
    float dz = 0.0f;

    float pos[3];
    if (!((CspBase*)this)->GetPos(pos, (void*)p3, (void*)p4, (void*)0))
        return 0;

    float* p = pos;
    float len = X87Len3(p[0], p[1], p[2]);
    if (len > g_13f11c8)
    {
        float cross0 = p[1] * dy - p[2] * dx;
        float cross1 = p[2] * dz - p[0] * dy;
        float cross2 = p[0] * dx - p[1] * dz;
        float *c = &cross0;
        float axis0 = dy * cross0;
        float axis1 = dz * cross1;
        float axis2 = dx * cross2;
        float v0 = dy * cross0 - dz * cross2;
        float v1 = dz * cross1 - dx * cross0;
        float v2 = dx * cross2 - dy * cross1;
        float* v = &v0;
        float sum = X87Len3(v0, v1, v2);
        if (sum > g_13f11c8)
        {
            if (outDir != 0)
            {
                float qx = p[2] * sum + v1 * len;
                float qy = p[1] * sum + v0 * len;
                float qz = p[0] * sum + v2 * len;
                float inv = 1.0f / (X87Len3(qx, qy, qz) * len);
                qx *= inv; qy *= inv; qz *= inv;
                float w = p[1] * qz - p[2] * qy;
                float x = p[2] * qx - p[0] * qz;
                float y = p[0] * qy - p[1] * qx;
                float s = (p[1] * qy + p[2] * qz) + p[0] * qx;
                float basis[4] = { w, x, y, s };
                void* q = FUN_007dcb00(&w, basis, outDir);
                outDir[0] = ((float*)q)[0];
                outDir[1] = ((float*)q)[1];
                outDir[2] = ((float*)q)[2];
                outDir[3] = ((float*)q)[3];
            }
            (void)c; (void)v; (void)axis0; (void)axis1; (void)axis2;
            float scaled = len / sum;
            outDir[0] = v0 * scaled;
            outDir[1] = v1 * scaled;
            outDir[2] = v2 * scaled;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00a7eec0
// ---------------------------------------------------------------------------
uint32_t Camera::FUN_00a7eec0(int p2, int p3)
{
    float tmp[9];
    ((CspBase*)this)->GetPos(tmp, (void*)p3, 0, 0);

    float* p = tmp;
    float len = X87Len3(p[0], p[1], p[2]);
    if (len > g_13f11c8)
    {
        float cross0 = p[1] * tmp[3] - p[2] * tmp[4];
        float cross1 = p[2] * tmp[5] - p[0] * tmp[3];
        float cross2 = p[0] * tmp[4] - p[1] * tmp[5];
        float v0 = tmp[3] * cross0 - tmp[5] * cross2;
        float v1 = tmp[5] * cross1 - tmp[4] * cross0;
        float v2 = tmp[4] * cross2 - tmp[3] * cross1;
        float sum = X87Len3(v0, v1, v2);
        if (sum > g_13f11c8)
        {
            float* r = (float*)p2;
            if (r != 0)
            {
                float qx = p[2] * sum + v1 * len;
                float qy = p[1] * sum + v0 * len;
                float qz = p[0] * sum + v2 * len;
                float inv = 1.0f / (X87Len3(qx, qy, qz) * len);
                qx *= inv; qy *= inv; qz *= inv;
                float w = p[1] * qz - p[2] * qy;
                float x = p[2] * qx - p[0] * qz;
                float y = p[0] * qy - p[1] * qx;
                float s = (p[1] * qy + p[2] * qz) + p[0] * qx;
                float basis[4] = { w, x, y, s };
                void* q = FUN_007dcb00(&w, basis, r);
                r[0] = ((float*)q)[0];
                r[1] = ((float*)q)[1];
                r[2] = ((float*)q)[2];
                r[3] = ((float*)q)[3];
            }
            float scaled = len / sum;
            float* o = (float*)p3;
            o[0] = v0 * scaled;
            o[1] = v1 * scaled;
            o[2] = v2 * scaled;
        }
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00a7f1d0
// ---------------------------------------------------------------------------
void __cdecl FUN_00a7f1d0(void* writer, uint32_t* data)
{
    uint32_t tmp[2];
    tmp[0] = data[0];
    FUN_0093aa70(writer, tmp, 1, 0);
    tmp[0] = data[2];
    tmp[1] = data[3];
    FUN_0093ab10(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 4); FUN_0093aa70(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 5); FUN_0093aa70(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 6); FUN_0093aa70(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 7); FUN_0093aa70(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 8); FUN_0093aa70(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 0xe); FUN_0093aa70(writer, tmp, 1, 0);
    *(float*)tmp = *(float*)(data + 0xf); FUN_0093aa70(writer, tmp, 1, 0);
    FUN_007ec580(writer, data + 0x10);
}
