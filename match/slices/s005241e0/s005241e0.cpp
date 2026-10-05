// Slice 13: nSPSkinner model-type helpers and the paint particle-tick callback.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

struct MT {
    int base;                                  // +0x00
    unsigned char GetResourceTypeFromModelType();  // 0x00526340
};
extern MT g_mt;                                // 0x015de470

struct Vec2Pair { int a; int b; };
struct PairVec { void push_back(const Vec2Pair& v); };   // 0x00525ff0

template <int N> inline void ScratchSlots() { uint32_t slots[N]; }
template <> inline void ScratchSlots<0>() {}

struct Model {
    int Get(int i);
    int GetChecked(int i);
};
struct Y {
    void AddPair(int a1, int a2);
};

// @ 0x005247b0
int Model::Get(int i)
{
    return i * 0x40 + g_mt.base;
}

// @ 0x00524870
void Y::AddPair(int a1, int a2)
{
    Vec2Pair local;
    local.a = a1;
    local.b = a2;
    ScratchSlots<2>();
    ((PairVec*)((char*)this + 0x94))->push_back(local);
}

// @ 0x005247d0
int Model::GetChecked(int i)
{
    int result;
    if (g_mt.GetResourceTypeFromModelType() != 0) {
        result = 0;
    } else {
        int thing = *(int*)((char*)this + 0x10);
        int* arr = *(int**)(thing + 0x1a4);
        int* slot = &arr[i];
        uint32_t raw = (uint32_t)*slot >> 0x10;
        uint32_t val;
        if (raw & 0x80000000u)
            val = (uint32_t)*(unsigned char*)(*(int*)(*(int*)((char*)this + 0x20) + 0x20) + (raw & 0x7fffffffu));
        else
            val = raw;
        if (val == 0xffffffffu)
            result = 0;
        else
            result = (int)val * 0x40 + g_mt.base;
    }
    return result;
}

// @ 0x005241e0 nSPSkinner::cPaintSystem::ParticleTickJobCallback -- PARTIAL skeleton
void FUN_005241e0(void* self) { (void)self; }
// @ 0x005248a0 -- PARTIAL skeleton (425-byte /Od body not reconstructed)
void FUN_005248a0(void* self) { (void)self; }
