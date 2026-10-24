// slice s008a1a10 -- container helpers: an EASTL-style vector insert (8-byte POD elements,
// vtable allocator kept in the vector) and the destructor pass for 0x60-byte inline buffers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace SP {

// Raw block helpers from the EASTL runtime.
void FreeRawBlock(void* pBlock);                                   // 0x00f47380
void* CopyEntriesRaw(void* pFirst, void* pLast, void* pDest);      // 0x0099efa0

// ---------------------------------------------------------------------------
// vector<T, Allocator>::insert(pos, value) for the 8-byte POD entries used below.
// ---------------------------------------------------------------------------
struct CVectorEntry {
  void* mpKey;     // +0x00
  void* mpValue;   // +0x04
};

// Allocator the vector stores by pointer at +0x0c; allocate/deallocate are its 3rd/4th slots.
class IVectorAllocator {
 public:
  virtual void vf00();
  virtual void vf04();
  virtual void* Allocate(uint32_t nBytes, int nFlags, void* pName);   // +0x08
  virtual void Deallocate(void* pBlock, uint32_t nBytes);             // +0x0c
};

class CVectorEntryArray {
 public:
  CVectorEntry* mpBegin;         // +0x00
  CVectorEntry* mpEnd;           // +0x04
  CVectorEntry* mpCap;           // +0x08
  IVectorAllocator* mpAlloc;     // +0x0c
  void* mpAllocName;             // +0x10

  void Insert(CVectorEntry* pPos, const CVectorEntry& value);   // 0x008a1a10
};

// @ 0x008a1a10
// Inserts one entry in front of pPos, doubling the capacity (and reallocating through the
// vector's own allocator) when the buffer is full.
void CVectorEntryArray::Insert(CVectorEntry* pPos, const CVectorEntry& value)
{
  if (mpEnd != mpCap) {
    const CVectorEntry* pValue = &value;
    // An entry that already lives at or after the insertion point moves up with the tail.
    if (pValue >= pPos && pValue < mpEnd)
      ++pValue;
    // The shift is a move_backward with its first copy peeled off.
    if (mpEnd != 0)
      *mpEnd = mpEnd[-1];
    CVectorEntry* pSrc = mpEnd - 1;
    CVectorEntry* pDst = mpEnd;
    while (pSrc != pPos) {
      --pSrc;
      --pDst;
      *pDst = *pSrc;
    }
    *pPos = *pValue;
    ++mpEnd;
    return;
  }

  int nDiff = (int)(mpEnd - mpBegin);
  unsigned nCount = (unsigned)nDiff;
  int nNewCap = (nCount > 0u) ? (int)(nCount * 2) : 1;
  CVectorEntry* pNew;
  if (nNewCap != 0)
    pNew = (CVectorEntry*)mpAlloc->Allocate((uint32_t)(nNewCap * (int)sizeof(CVectorEntry)), 0,
                                            mpAllocName);
  else
    pNew = 0;

  void* pNewEnd = CopyEntriesRaw(mpBegin, pPos, pNew);
  if (pNewEnd != 0)
    *(CVectorEntry*)pNewEnd = value;
  pNewEnd = CopyEntriesRaw(pPos, mpEnd, (char*)pNewEnd + sizeof(CVectorEntry));

  if (mpBegin != 0) {
    int nOldCap = (int)(mpCap - mpBegin);
    mpAlloc->Deallocate(mpBegin, (uint32_t)(nOldCap * (int)sizeof(CVectorEntry)));
  }
  mpBegin = pNew;
  mpEnd = (CVectorEntry*)pNewEnd;
  mpCap = pNew + nNewCap;
}

// ---------------------------------------------------------------------------
// 0x60-byte record with an inline buffer at +0x18 that falls back to a heap block at +0x08.
// ---------------------------------------------------------------------------
struct CInlineBuffer {
  char mPad00[8];
  void* mpData;          // +0x08  heap block, or 0
  char mPad0c[0x18 - 0x0c];
  void* mpInlineData;    // +0x18  address of the record's own buffer
  char mPad1c[0x60 - 0x1c];
};

CInlineBuffer* DestroyInlineBuffers(CInlineBuffer* pFirst, CInlineBuffer* pLast,
                                    CInlineBuffer* pDest);   // 0x008a1b30

// @ 0x008a1b30
// Releases the heap block of every record in [pFirst, pLast) and returns the advanced
// destination cursor.
CInlineBuffer* DestroyInlineBuffers(CInlineBuffer* pFirst, CInlineBuffer* pLast,
                                    CInlineBuffer* pDest)
{
  while (pFirst != pLast) {
    if (pFirst->mpData != 0 && pFirst->mpData != pFirst->mpInlineData)
      FreeRawBlock(pFirst->mpData);
    ++pFirst;
    ++pDest;
  }
  return pDest;
}

}  // namespace SP
