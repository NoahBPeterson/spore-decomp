// Slice s004d34f0: species tuning statics + small accessors on the tuning/profile
// object (vector at +0x48, pair pointers +0x70/+0x74, min/max floats +0x134/+0x138).
// Flags region: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast.
#include "types.h"
#pragma pack(push, 4)

// 0x004D2450, one argument here (InitStatics pushes a single 0).
void LoadSpeciesTuning(uint32_t which);

// @ 0x004D34F0  SP::`anonymous namespace'::InitStatics
void InitStatics()
{
    LoadSpeciesTuning(0);
}

// ---------------------------------------------------------------------------
// Tuning/profile object stub.
// ---------------------------------------------------------------------------
struct TuningObj {
    char pad0[0x48];
    int   mBegin;      // +0x48
    int   mEnd;        // +0x4c
    char pad50[0x20];  // up to +0x70
    int   m70;         // +0x70
    int   m74;         // +0x74
    char pad78[0x134 - 0x78];
    float mMin;        // +0x134
    float mMax;        // +0x138

    uint32_t GetAt(uint32_t index);
    int      GetActive();
    float    GetBound(bool which);
    void     SetBounds(float lo, float hi);
};

// @ 0x004D3CD0
uint32_t TuningObj::GetAt(uint32_t index)
{
    int* vec = (int*)((char*)this + 0x48);
    int count = (vec[1] - vec[0]) >> 2;
    if (count == 0 || index >= (uint32_t)count)
        return 0x04330667;
    return *(uint32_t*)(*(int*)((char*)this + 0x48) + index * 4);
}

// @ 0x004D3D40
int TuningObj::GetActive()
{
    if (m74 != 0)
        return m74;
    else
        return m70;
}

// @ 0x004D3D70
float TuningObj::GetBound(bool which)
{
    if (which)
        return mMax;
    else
        return mMin;
}

// @ 0x004D3DA0
void TuningObj::SetBounds(float lo, float hi)
{
    mMin = lo;
    mMax = hi;
}

// @ 0x004D3500  (7-arg cdecl float blend)
float Blend(float, float, float a, float, float b, float c, float d)
{
    float k1 = 40.0f;
    float kr = 20.0f;
    float k2 = 20.0f;
    float k3 = (b * k1 + a) + c * kr + d * k2;
    return k3;
}

// ---------------------------------------------------------------------------
// Remaining larger neighbours (see partial.txt).
// ---------------------------------------------------------------------------
// @ 0x004D3570
int MapGetFieldC(void* self, void* key) { (void)self; (void)key; return 0; }
// @ 0x004D35D0
int MapGetClamped(void* self, void* key) { (void)self; (void)key; return 0; }
// @ 0x004D3640
int MapGetField4(void* self, void* key) { (void)self; (void)key; return 0; }
// @ 0x004D36A0
void* MapGetPtr(void* self, void* key) { (void)self; (void)key; return 0; }
// @ 0x004D3760
void TuningOp1(void* self) { (void)self; }
// @ 0x004D3B80
void TuningOp2(void* self) { (void)self; }
// @ 0x004D3DD0
void TuningOp3(void* self) { (void)self; }
