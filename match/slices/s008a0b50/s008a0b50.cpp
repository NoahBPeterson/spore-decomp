// Slice s008a0b50 -- EASTL-style vector<wchar_t>::DoInsertValue for the SP vector family that keeps
// its allocator behind a virtual interface (insert 0x008a1900).
//
// Object layout mirrors the sibling instantiation in s008a1a10 (SP::CVectorEntryArray):
//   +0x00 mpBegin, +0x04 mpEnd, +0x08 mpCapacity, +0x0c mpAllocator, +0x10 mpAllocatorName.
// The allocator is called as Allocate(nBytes, 0, name) / Deallocate(block, nBytes) through its
// vtable slots at +0x08/+0x0c.  Inserting one 16-bit element shifts the tail with memmove (the
// last element is first copied into the free slot) and reallocates to twice the size when full,
// copying both halves with memcpy.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include <string.h>
#include <new>
#include "types.h"

// ---------------------------------------------------------------------------
// The virtual allocator the vector stores by pointer at +0x0c.
// ---------------------------------------------------------------------------
class IVectorAllocator {
 public:
  virtual void vf00();
  virtual void vf04();
  virtual void* Allocate(uint32_t nBytes, int nFlags, void* pName);   // +0x08
  virtual void Deallocate(void* pBlock, uint32_t nBytes);             // +0x0c
};

// ---------------------------------------------------------------------------
// Trivial (POD) range helpers, as used by the EASTL vector implementation.
// ---------------------------------------------------------------------------
inline uint16_t* CopyBackwardTrivial(const uint16_t* first, const uint16_t* last, uint16_t* result)
{
  return (uint16_t*)memmove(result - (last - first), first,
                            (size_t)((uintptr_t)last - (uintptr_t)first));
}

inline uint16_t* UninitializedCopyTrivial(const uint16_t* first, const uint16_t* last, uint16_t* result)
{
  return (uint16_t*)memcpy(result, first, (size_t)((uintptr_t)last - (uintptr_t)first))
         + (last - first);
}

// ---------------------------------------------------------------------------
// vector<wchar_t> with the vtable allocator.
// ---------------------------------------------------------------------------
class CWordVector {
 public:
  uint16_t* mpBegin;             // +0x00
  uint16_t* mpEnd;               // +0x04
  uint16_t* mpCapacity;          // +0x08
  IVectorAllocator* mpAllocator; // +0x0c
  void* mpAllocatorName;         // +0x10

  void Insert(uint16_t* position, const uint16_t& value);   // 0x008a1900
};

// @ 0x008a1900
// Inserts one element in front of position, doubling the capacity (and reallocating through the
// vector's own allocator) when the buffer is full.
void CWordVector::Insert(uint16_t* position, const uint16_t& value)
{
  if (mpEnd != mpCapacity) {
    const uint16_t* pValue = &value;
    // A value that already lives at or after the insertion point moves up with the tail.
    if ((pValue >= position) && (pValue < mpEnd))
      ++pValue;
    // The shift is a move_backward with its first copy peeled off.
    ::new (mpEnd) uint16_t(*(mpEnd - 1));
    CopyBackwardTrivial(position, mpEnd - 1, mpEnd);
    *position = *pValue;
    ++mpEnd;
    return;
  }

  const size_t nPosSize = (size_t)(position - mpBegin);
  const size_t nPrevSize = (size_t)(mpEnd - mpBegin);
  const size_t nNewSize = nPrevSize ? (2 * nPrevSize) : 1;
  uint16_t* const pNewData =
      nNewSize ? (uint16_t*)mpAllocator->Allocate((uint32_t)(nNewSize * sizeof(uint16_t)), 0,
                                                  mpAllocatorName)
               : 0;
  (void)nPosSize;
  uint16_t* pNewEnd = UninitializedCopyTrivial(mpBegin, position, pNewData);
  ::new (pNewEnd) uint16_t(value);
  pNewEnd = UninitializedCopyTrivial(position, mpEnd, ++pNewEnd);

  if (mpBegin != 0)
    mpAllocator->Deallocate(mpBegin, (uint32_t)((mpCapacity - mpBegin) * sizeof(uint16_t)));

  mpBegin = pNewData;
  mpEnd = pNewEnd;
  mpCapacity = pNewData + nNewSize;
}
