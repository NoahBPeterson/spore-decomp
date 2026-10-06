// Slice s00a68140 - EA::Audio::Eapd / Random helpers.
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
class RefObj {
public:
    virtual void ScalarDtor(int flag);   // +0x00
    int          mnRefCount;             // +0x04
};

// @ 0xa69150
class SizeHolder {
public:
    char pad[4];
    int  mnSize;                         // +0x04
    bool AddSize(int a, int b);
};
bool SizeHolder::AddSize(int a, int b)
{
    mnSize += b;
    return true;
}

// @ 0xa69180
class TableHolder {
public:
    char pad[0xc];
    int** mTable;                        // +0x0c
    int GetA(int a, int b);
};
int TableHolder::GetA(int a, int b)
{
    int* p = *(int**)((char*)mTable + b * 0x14);
    return p[a];
}

// @ 0xa691a0
class TableHolder2 {
public:
    char pad[0x20];
    int** mTable;                        // +0x20
    int GetB(int a, int b);
};
int TableHolder2::GetB(int a, int b)
{
    int* p = *(int**)((char*)mTable + b * 0x14);
    return p[a];
}

// ---------------------------------------------------------------------------
// EA::Random::RandomLinearCongruential
// ---------------------------------------------------------------------------
extern "C" {
    extern float g_2p328e10;   // 0x14558a8
    extern float g_0p5;        // 0x1471064
    extern float g_1p0;        // 0x1485720
}

class RandomLinearCongruential {
public:
    uint32_t mnSeed;                       // +0x00
    uint32_t RandomUint32Uniform(uint32_t range);  // @ 0xa68fb0
    float    RandomFloat();                        // @ 0xa68fe0
    float    RandomFloatSSE();                     // @ 0xa69020
};

uint32_t RandomLinearCongruential::RandomUint32Uniform(uint32_t range)
{
    uint64_t l = (uint64_t)mnSeed * 0x41c64e6dULL + 0x3039;
    mnSeed = (uint32_t)l;
    uint32_t u = (uint32_t)(l >> 16);
    return (uint32_t)(((uint64_t)u * range) >> 32);
}

float RandomLinearCongruential::RandomFloat()
{
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    int s = (int)mnSeed * 0x278dde6d;
    mnSeed = (uint32_t)s;
    float f = (float)s * g_2p328e10 + g_0p5;
    return (g_1p0 <= f) ? 0.0f : f;
}

float RandomLinearCongruential::RandomFloatSSE()
{
    if (mnSeed == 0)
        mnSeed = (uint32_t)__rdtsc();
    int s = (int)mnSeed * 0x278dde6d;
    float f = (float)s * g_2p328e10 + g_0p5;
    mnSeed = (uint32_t)s;
    if (g_1p0 <= f)
        return 0.0f;
    return f;
}

// @ 0xa69070  forward intrusive_ptr assignment
void AssignPtrs(RefObj** first, RefObj** last, RefObj** src)
{
    for (; first != last; ++first) {
        RefObj* p = *src;
        RefObj* q = *first;
        if (p != q) {
            if (p)
                p->mnRefCount++;
            *first = p;
            if (q) {
                int n = (*(volatile int*)&q->mnRefCount += -1);
                if (n == 0) {
                    q->mnRefCount = 1;
                    q->ScalarDtor(1);
                }
            }
        }
    }
}

// @ 0xa690d0  backward intrusive_ptr assignment
RefObj** AssignPtrsRev(RefObj** first, RefObj** last, RefObj** dst)
{
    if (last == first)
        return dst;
    do {
        RefObj* p = *--last;
        RefObj* q = *--dst;
        if (p != q) {
            if (p)
                p->mnRefCount++;
            *dst = p;
            if (q) {
                int n = (*(volatile int*)&q->mnRefCount += -1);
                if (n == 0) {
                    q->mnRefCount = 1;
                    q->ScalarDtor(1);
                }
            }
        }
    } while (last != first);
    return dst;
}

// ---- placeholders for the remaining functions -------------------------------
extern "C" int __cdecl Placeholder_68140() { return 0; }
extern "C" int __cdecl Placeholder_68190() { return 0; }
extern "C" int __cdecl Placeholder_681e0() { return 0; }
extern "C" int __cdecl Placeholder_68280() { return 0; }
extern "C" int __cdecl Placeholder_682d0() { return 0; }
extern "C" int __cdecl Placeholder_68330() { return 0; }
extern "C" int __cdecl Placeholder_683b0() { return 0; }
extern "C" int __cdecl Placeholder_68410() { return 0; }
extern "C" int __cdecl Placeholder_68430() { return 0; }
extern "C" int __cdecl Placeholder_685a0() { return 0; }
extern "C" int __cdecl Placeholder_685e0() { return 0; }
extern "C" int __cdecl Placeholder_68670() { return 0; }
extern "C" int __cdecl Placeholder_686e0() { return 0; }
extern "C" int __cdecl Placeholder_68740() { return 0; }
extern "C" int __cdecl Placeholder_687f0() { return 0; }
extern "C" int __cdecl Placeholder_68890() { return 0; }
extern "C" int __cdecl Placeholder_68990() { return 0; }
extern "C" int __cdecl Placeholder_68aa0() { return 0; }
extern "C" int __cdecl Placeholder_68af0() { return 0; }
extern "C" int __cdecl Placeholder_68bf0() { return 0; }
extern "C" int __cdecl Placeholder_68c50() { return 0; }
extern "C" int __cdecl Placeholder_68cb0() { return 0; }
extern "C" int __cdecl Placeholder_68dd0() { return 0; }
class EapdSystem {
public:
    void  Destroy();                       // 0xa68dd0
    void* ScalarDtor(int flag);            // @ 0xa68e80
};
void* EapdSystem::ScalarDtor(int flag)
{
    Destroy();
    return this;
}

class IntrusiveList {
public:
    void Remove(void* p);                  // 0xa68280
};
class Outer310 {
public:
    char pad[0x31c];
    IntrusiveList mList;                   // +0x31c
    void RemoveEntry(int p);               // @ 0xa68410
};
void Outer310::RemoveEntry(int p)
{
    if (p)
        mList.Remove(&p);
}
extern "C" int __cdecl Placeholder_68e90() { return 0; }