#pragma once
// Shared stub types for the mesh/attribute bake region 0x006ccf50-0x006d7xxx.
// Layouts cross-checked against the sibling slice s004248c0 (Elem32 / Handle).
#include "types.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl acos(double);

// Intrusive reference-counted object.  vtable slot 0 = AddRef, slot 1 = Release.
struct RefObject
{
    virtual void AddRef();
    virtual void Release();
};

// 0x10-byte refcounted handle.  +4 = stream base pointer, +0xa = 16-bit element stride.
struct Handle
{
    uint32_t a;         // +0
    uint32_t b;         // +4  data base
    uint16_t c;         // +8
    uint16_t d;         // +a  stride
    RefObject* mpRef;   // +c

    Handle() : a(0), b(0), c(0), d(0), mpRef(0) {}
    Handle(const Handle& o) : a(o.a), b(o.b), c(o.c), d(o.d), mpRef(o.mpRef)
    {
        if (mpRef)
            mpRef->AddRef();
    }
    ~Handle()
    {
        if (mpRef)
            mpRef->Release();
    }
    Handle* Assign(const Handle* src);   // out of line: 0x00424f70
};

// 0x20-byte element of the source table (bake input record).
struct Elem32
{
    uint32_t w0, w1, w2, w3;
    Handle handle;
};

// param_3: object whose +8 dword is the Elem32 table base.
struct ElemTable
{
    uint32_t p0;
    uint32_t p4;
    Elem32* mBegin;
};

// param_4: 0x18-byte per-output record.
struct BakeEntry
{
    uint32_t f0;        // +0   index into the param_5 (position) stream
    uint32_t f4;        // +4
    uint32_t f8;        // +8   index into the handle's colour stream
    uint32_t fc;        // +c   index into the handle's uv stream
    uint32_t f10;       // +10
    uint32_t f14;       // +14
};

// param_5: stream descriptor, base at +4, 16-bit stride at +0xa.
struct StreamDesc
{
    uint32_t p0;
    uint32_t base;
    uint16_t p8;
    uint16_t stride;
    uint32_t pc;
};

// param_7: scale object.
struct ScaleInfo
{
    char pad[0x10];
    float scale;
};

// The four instantiations of the shared evaluation core.
void FUN_006c4200(void* out0, void* out1, const void* pos3, const void* dir3,
                  const void* color, const void* uv, int param);
void FUN_006c3b90(void* out0, void* out1, const void* pos3, const void* dir3,
                  const void* color, const void* uv, int param);
void FUN_006c3550(void* out0, void* out1, const void* pos3, const void* dir3,
                  const void* color, const void* uv, int param);
void FUN_006c3780(void* out0, void* out1, const void* pos3, const void* dir3,
                  const void* color, const void* uv, int param);

// ---------------------------------------------------------------------------------------------
// Bake body.  Parameter encoding:
//   COREID : 0=6c4200 1=6c3b90 2=6c3550 3=6c3780
//   UVN    : number of uv channels (2 or 4)
//   UVT    : 0 = uint8, 1 = uint16
//   COLMODE: 0 = 4 bytes / 255, 1 = 4 floats, 2 = 2 floats, 3 = constant (1,0,0,0)
//   TAIL   : 0 = acos (weight = axis.y * res.z)
//            1 = dot  (out0 = axis.x*res.x + axis.z; out1 = 1 - (res.y*axis.y + axis.w))
//            2 = acos (weight = axis.y * |res.xy - axis.zw|)
// ---------------------------------------------------------------------------------------------
#define DEFINE_BAKE(NAME, COREID, UVN, UVT, COLMODE, TAIL)                                            \
bool NAME(float* out, int count, ElemTable* table, BakeEntry* entries, StreamDesc* pos,               \
          float* axis, ScaleInfo* scaleInfo, int index, int handleIndex, int param10)                  \
{                                                                                                     \
    Elem32* base = table->mBegin;                                                                     \
    Handle hA = base[index].handle;                                                                   \
    Handle hB;                                                                                        \
    if (handleIndex >= 0)                                                                             \
        hB.Assign(&base[handleIndex].handle);                                                         \
    if (count != 0)                                                                                   \
    {                                                                                                 \
        float axisDir[3] = { 1.0f, 0.0f, 0.0f };                                                      \
        float white[4] = { 1.0f, 0.0f, 0.0f, 0.0f };                                                 \
        float* o = out;                                                                               \
        BakeEntry* e = entries;                                                                       \
        int n = count;                                                                                \
        do                                                                                            \
        {                                                                                             \
            uint32_t u[4];                                                                            \
            if (UVT == 0) { uint8_t* s = (uint8_t*)(hA.b + hA.d * e->fc);                             \
                u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3; }                 \
            else { uint16_t* s = (uint16_t*)(hA.b + hA.d * e->fc);                                    \
                u[0] = s[0] / 3; u[1] = s[1] / 3; u[2] = s[2] / 3; u[3] = s[3] / 3; }                 \
            float color[4];                                                                           \
            if (COLMODE == 0) { uint8_t* c = (uint8_t*)(hB.b + hB.d * e->f8);                         \
                color[0] = (float)c[0] * (1.0f / 255.0f); color[1] = (float)c[1] * (1.0f / 255.0f);   \
                color[2] = (float)c[2] * (1.0f / 255.0f); color[3] = (float)c[3] * (1.0f / 255.0f); } \
            else if (COLMODE == 1) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = c[3]; }                 \
            else if (COLMODE == 2) { float* c = (float*)(hB.b + hB.d * e->f8);                        \
                color[0] = c[0]; color[1] = c[1]; color[2] = c[2]; color[3] = 0.0f; }                 \
            else { color[0] = white[0]; color[1] = white[1]; color[2] = white[2]; color[3] = white[3]; }\
            float* ps = (float*)(pos->base + pos->stride * e->f0);                                    \
            float p3[3];                                                                              \
            p3[0] = ps[0]; p3[1] = ps[1]; p3[2] = ps[2];                                              \
            float res[3];                                                                             \
            float scratch[3];                                                                         \
            void* uvp = (UVN == 2) ? (void*)&u[0] : (void*)u;                                         \
            if (COREID == 0) FUN_006c4200(res, scratch, p3, axisDir, color, uvp, param10);            \
            else if (COREID == 1) FUN_006c3b90(res, scratch, p3, axisDir, color, uvp, param10);       \
            else if (COREID == 2) FUN_006c3550(res, scratch, p3, axisDir, color, uvp, param10);       \
            else FUN_006c3780(res, scratch, p3, axisDir, color, uvp, param10);                        \
            float scale = scaleInfo->scale;                                                           \
            if (TAIL == 1)                                                                            \
            {                                                                                         \
                o[0] = (axis[0] * res[0] + axis[2]) * scale;                                          \
                o[1] = (1.0f - (res[1] * axis[1] + axis[3])) * scale;                                 \
            }                                                                                         \
            else                                                                                      \
            {                                                                                         \
                float dx = res[0] - axis[2];                                                          \
                float dy = res[1] - axis[3];                                                          \
                float len = (float)sqrt(dx * dx + dy * dy);                                           \
                float angle = (float)acos(dx / len);                                                  \
                float weight = (TAIL == 0) ? axis[1] * res[2] : axis[1] * len;                        \
                o[0] = ((axis[0] * angle) * 1.2732406f) * scale;                                      \
                o[1] = (1.0f - weight) * scale;                                                       \
            }                                                                                         \
            o += 2;                                                                                   \
            e += 1;                                                                                   \
        } while (--n);                                                                                \
    }                                                                                                 \
    return true;                                                                                      \
}
