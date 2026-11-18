// Slice s00c43cc0 -- eastl::vector<16-byte>::insert(iterator, const T&).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The same 277-byte template instantiation as 0x00d5a140 (SPCityVisualizer.cpp),
// only the range-copy helper differs. With spare capacity the last element is
// copied into the free slot, the tail is shifted right by copy_backward
// (0x00edba80) and the value is stored as four dwords, the second of which is
// left in eax. Without spare capacity the buffer doubles (at least one element),
// is allocated through operator new("Simulator", ... EASTL/allocator.h:0xd1),
// the head and tail are move-constructed by 0x00ba7920, and the old block is
// freed.
#include "types.h"

// Stand-in for the template's element type: 16 bytes, three floats plus one
// 32-bit word. The floats are copied through x87 (fld/fstp) while the last word
// is always copied with a plain mov, which is what the original does.
struct Elem16_s00c4_3cc0 {
    float a;
    float b;
    float c;
    uint32_t d;
};

// Stand-in for the EASTL vector header this function is called on: begin, end
// and capacity-end pointers, then the held/inline buffer pointer checked before
// freeing. [0xc] is untouched by this function.
struct Vec16_s00c4_3cc0 {
    Elem16_s00c4_3cc0* mpBegin;
    Elem16_s00c4_3cc0* mpEnd;
    Elem16_s00c4_3cc0* mpCapacity;
    uint32_t mPad0c;
    Elem16_s00c4_3cc0* mpInline;

    uint32_t Insert(Elem16_s00c4_3cc0* pos, const Elem16_s00c4_3cc0* pValue);
};

// ---- retail callees (call targets are address-masked by the fingerprint) ----
extern char g_szSimulator[];   // 0x013f09b4 "Simulator"
extern char g_szAllocatorH[];  // 0x013ebb38 ".../EASTL/allocator.h"

void* __cdecl operator_new(uint32_t size, const char* pName, int a, int b,
                           const char* pFile, uint32_t line);            // 0x00f473a0
void __cdecl operator_delete(void* pBlock);                              // 0x00f47380
void* __cdecl FUN_00ba7920(void* pFirst, const void* pMiddle, void* pDest); // 0x00ba7920 uninitialized move
void __cdecl FUN_00edba80(void* pFirst, const void* pLast, void* pDest);    // 0x00edba80 copy_backward

// @ 0x00c43cc0
uint32_t Vec16_s00c4_3cc0::Insert(Elem16_s00c4_3cc0* pos, const Elem16_s00c4_3cc0* pValue)
{
    Elem16_s00c4_3cc0* const end = mpEnd;
    if (end != mpCapacity)
    {
        const Elem16_s00c4_3cc0* value = pValue;
        if (value >= pos && value < end)
            value = value + 1;
        if (end)
        {
            Elem16_s00c4_3cc0* const last = end - 1;
            end->a = last->a;
            end->b = last->b;
            end->c = last->c;
            end->d = last->d;
        }
        FUN_00edba80(pos, mpEnd - 1, mpEnd);
        *(uint32_t*)&pos->a = *(const uint32_t*)&value->a;
        uint32_t b = *(const uint32_t*)&value->b;
        *(uint32_t*)&pos->b = b;
        *(uint32_t*)&pos->c = *(const uint32_t*)&value->c;
        *(uint32_t*)&pos->d = *(const uint32_t*)&value->d;
        mpEnd = mpEnd + 1;
        return b;
    }
    else
    {
        uint32_t n = (uint32_t)(int)(mpEnd - mpBegin);
        if (n > 0)
            n = n * 2;
        else
            n = 1;
        Elem16_s00c4_3cc0* pNew;
        if (n)
            pNew = (Elem16_s00c4_3cc0*)operator_new(n << 4, g_szSimulator, 0, 0,
                                                    g_szAllocatorH, 0xd1);
        else
            pNew = 0;
        Elem16_s00c4_3cc0* const begin = mpBegin;
        Elem16_s00c4_3cc0* p = (Elem16_s00c4_3cc0*)FUN_00ba7920(begin, pos, pNew);
        if (p)
        {
            p->a = pValue->a;
            p->b = pValue->b;
            p->c = pValue->c;
            p->d = pValue->d;
        }
        Elem16_s00c4_3cc0* oldEnd = mpEnd;
        p = (Elem16_s00c4_3cc0*)FUN_00ba7920(pos, oldEnd, p + 1);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpEnd = p;
        mpCapacity = pNew + n;
        mpBegin = pNew;
    }
}
