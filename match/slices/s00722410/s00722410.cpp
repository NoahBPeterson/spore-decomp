// eastl::vector<SP::cTextureChart, ...> helpers (retail offsets from disasm).
#include "types.h"

extern "C" void  __cdecl EASTL_allocator_deallocate(void* p);
extern "C" void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int a, int b,
                                                  const char* file, int line);
extern "C" void __stdcall VectorAppend8(void* dstEnd, void* val);      // 00722410
extern "C" void* __cdecl AllocConstruct38(int n, const void* a, const void* b); // 00722990

struct Vec8 { float x, y; };
struct VecAny { int* begin; int* end; int* cap; void Assign(int n, int value, int dummy); void Push8(Vec8* val); };

// @ 0x00722410  (vector<...>::insert at end; complex, reduced)
void __cdecl VectorAppend8Impl(void* dstEnd, void* val)
{
    (void)dstEnd; (void)val;
}

// @ 0x00722520
void __thiscall VecAny::Assign(int n, int value, int dummy)
{
    int* p;
    if (n != 0)
        p = (int*)EASTL_allocator_allocate(n * 4, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    else
        p = 0;
    this->begin = p;
    this->cap = p + n;
    this->end = p + n;
    if (n > 0) {
        for (; n != 0; n--)
            *p++ = value;
    }
    (void)dummy;
}

// @ 0x00722580  (insert n elements of 0x18 at position)
void __cdecl VecInsert18(int* v, void* pos, uint32_t n, void* val)
{
    (void)v; (void)pos; (void)n; (void)val;
}

// @ 0x00722770  (insert n elements of 0x28 at position)
void __cdecl VecInsert28(int* v, void* pos, uint32_t n, void* val)
{
    (void)v; (void)pos; (void)n; (void)val;
}

// @ 0x00722990
void* __cdecl AllocConstruct38(int n, const void* a, const void* b)
{
    void* p;
    if (n == 0)
        p = 0;
    else
        p = EASTL_allocator_allocate(n * 0x38, "Graphics", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    (void)a; (void)b;
    return p;
}

// @ 0x007229f0  (copy chart record 0x50 + inner vector)
void* __cdecl CopyChartRecord(void* dst, void* src)
{
    unsigned char* d = (unsigned char*)dst;
    unsigned char* s = (unsigned char*)src;
    for (int i = 0; i < 0x50; i += 4)
        *(int*)(d + i) = *(int*)(s + i);
    return dst;
}

// @ 0x00722b20  (find-or-insert float key -> int payload)
int __cdecl FindOrInsertF(void* hash, float* key)
{
    (void)hash;
    int* p = (int*)((char*)key + 0xc);
    return *p;
}

// @ 0x00722ba0  (swap two vectors with copy-on-alloc)
void __cdecl SwapVecIfOwned(int* a, int* b)
{
    int* t0 = (int*)a[0]; int* t1 = (int*)a[1]; int* t2 = (int*)a[2];
    a[0] = b[0]; a[1] = b[1]; a[2] = b[2];
    b[0] = (int)t0; b[1] = (int)t1; b[2] = (int)t2;
}

// @ 0x00722c60
void __thiscall VecAny::Push8(Vec8* val)
{
    Vec8* e = (Vec8*)this->end;
    if (e < (Vec8*)this->cap) {
        this->end = (int*)(e + 1);
        if (e != 0) {
            e->x = val->x;
            e->y = val->y;
            return;
        }
    } else {
        VectorAppend8(e, val);
    }
}

// @ 0x00722ca0
int* __cdecl ConstructIntVec(int* v, int n, int val)
{
    v[0] = 0; v[1] = 0; v[2] = 0;
    ((VecAny*)v)->Assign(n, val, 0);
    return v;
}

// @ 0x00722d00  (cTextureChart build; large, reduced)
void __cdecl BuildTextureChart(int param_1)
{
    (void)param_1;
}
