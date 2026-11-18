// eastl::vector<u32>::DoInsertValue(position, value) -- the position-insert of a 4-byte element
// vector (callers: VecU32::InsertSlow of the city summary reader, see s00ff21d0).
//
// Retail is /Od: the allocator call (0x00f473a0, category "Simulator") and both uninitialized
// copies are inlined into the body; the new capacity is the single spilled 4-byte local (the
// `push ecx` frame slot). The insert handles value aliasing: when the value reference points
// into [position, mpEnd) the element is read one slot further on, because the shift moves it.

typedef unsigned int u32;

extern "C" {
void* __cdecl FUN_00f473a0(u32 n, const char* name, int flags, int debugFlags, const char* file, int line);
void  __cdecl FUN_00f47380(void* p);
}

// The EASTL allocator header string the retail allocate call passes for its file argument.
static const char kAllocatorFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// Element-wise copy into raw storage (EASTL uninitialized_copy for a trivial element type).
inline u32* UninitCopy(u32* first, u32* last, u32* result)
{
    for (; first != last; ++first, ++result)
    {
        if (result)
            *result = *first;
    }
    return result;
}

struct VecU32
{
    u32* mpBegin;      // +0x00
    u32* mpEnd;        // +0x04
    u32* mpCapacity;   // +0x08

    void DoInsertValue(u32* position, const u32& value);   // 0x00ff19c0 (thiscall, ret 8)
};

// @ 0x00ff19c0
void VecU32::DoInsertValue(u32* position, const u32& value)
{
    if (mpEnd != mpCapacity)
    {
        // Read the value from one slot further on when it is itself an element that moves.
        const u32* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;

        // Construct the new tail element from the current last one, then shift the rest up.
        if (mpEnd)
            *mpEnd = *(mpEnd - 1);
        {
            u32* pLast = mpEnd - 1;
            u32* pDst  = mpEnd;
            while (pLast != position)
            {
                --pLast;
                --pDst;
                *pDst = *pLast;
            }
        }
        *position = *pValue;
        ++mpEnd;
    }
    else
    {
        const u32 count = (u32)(mpEnd - mpBegin);
        const u32 newCapacity = (count > 0) ? (2 * count) : 1;

        u32* const pNew = newCapacity
                        ? (u32*)FUN_00f473a0(newCapacity * sizeof(u32), "Simulator", 0, 0,
                                             kAllocatorFile, 0xd1)
                        : 0;

        u32* pDst = UninitCopy(mpBegin, position, pNew);
        if (pDst)
            *pDst = value;
        ++pDst;
        pDst = UninitCopy(position, mpEnd, pDst);

        if (mpBegin && ((int*)mpBegin)[-1])
            FUN_00f47380(mpBegin);

        mpBegin    = pNew;
        mpEnd      = pDst;
        mpCapacity = pNew + newCapacity;
    }
}
