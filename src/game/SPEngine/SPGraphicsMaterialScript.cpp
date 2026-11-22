// src/game/SPEngine/SPGraphicsMaterialScript.cpp -- migrated from slice(s) s010409b0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsMaterialScript.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern char gEastlAllocator;                 // 0x013ebb38

// ---- items of slice s010409b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void _pv##n();
inline void* operator new(unsigned int, void* pPlace) { return pPlace; }
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual void AddHandler(void* pHandler, uint32_t nMessageId);   // +0x24
};
void RemoveHandler(void* pServer, void* pHandler, uint32_t* pIdArray, int nIdCount,
                   int nPriority);   // 0x00571db0
void* EastlAllocate(int nBytes, const char* pName, int nHint, int nFlags, void* pAllocator,
                    int nLine);              // 0x00f473a0
void EastlDeallocate(void* pBlock);          // 0x00f47380
extern char gEastlAllocator;                 // 0x013ebb38
namespace SP {
struct cTuningEntry {
  int mn00, mn04, mn08, mn0c, mn10;     // +0x00  zeroed
  int mn14;                            // +0x14  1
  float mf18, mf1c, mf20;              // +0x18  relationship band, default 1.0
  float mf24;                          // +0x24  30.0
  float mf28;                          // +0x28  1.0
  float mf2c;                          // +0x2c  10.0
  float mf30, mf34;                    // +0x30  1.0
  float mf38;                          // +0x38  0.0
  bool mb3c, mb3d;                     // +0x3c  flags, false
  char mPad3e[2];
  float mf40, mf44;                    // +0x40  1.0
  float mf48, mf4c;                    // +0x48  0.0
  bool mb50, mb51, mb52;               // +0x50  flags, false
  char mPad53;

  cTuningEntry()
      : mn00(0), mn04(0), mn08(0), mn0c(0), mn10(0), mn14(1), mf18(1.0f),
        mf1c(1.0f), mf20(1.0f), mf24(30.0f), mf28(1.0f), mf2c(10.0f), mf30(1.0f), mf34(1.0f),
        mf38(0.0f), mb3c(false), mb3d(false), mf40(1.0f), mf44(1.0f), mf48(0.0f), mf4c(0.0f),
        mb50(false), mb51(false), mb52(false) {}
};
}
namespace SP {
class cTuningEntryVector {
 public:
  cTuningEntry* mpBegin;   // +0x00
  cTuningEntry* mpEnd;     // +0x04
  cTuningEntry* mpCap;     // +0x08

  cTuningEntry* EraseRange(cTuningEntry* pFirst, cTuningEntry* pLast);   // 0x01041220
  void Insert(cTuningEntry* pPos, const cTuningEntry& value);           // 0x01041280
  void PushDefault();                                                  // 0x010413b0

  ~cTuningEntryVector() { FreeBuffer(); }
  void FreeBuffer() {
    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
      EastlDeallocate(mpBegin);
  }
};
}
namespace SP {
cTuningEntry* CopyEntries(cTuningEntry* pFirst, cTuningEntry* pLast, cTuningEntry* pDest);
}
namespace SP {
class CMessageHandlerBase {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8)
  virtual ~CMessageHandlerBase() {}   // restores the base vtable

  IMessageServer* mpServer;   // +0x04
  void* mpHandler;            // +0x08
  uint32_t* mpIdArray;        // +0x0c
  int mnIdCount;              // +0x10
  int mnPriority;             // +0x14
};
}
namespace SP {
class cTuningEntrySet : public CMessageHandlerBase {
 public:
  cTuningEntryVector mEntries;   // +0x18

  void Release();                                     // 0x01041480
  void* ScalarDeletingDestructor(unsigned char nFlags);   // 0x01041110
};
}
namespace SP {
__declspec(noinline) cTuningEntry* CopyEntries(cTuningEntry* pFirst, cTuningEntry* pLast,
                                               cTuningEntry* pDest)
{
  while (pFirst != pLast)
    *pDest++ = *pFirst++;
  return pDest;
}
}
// ---- items of slice s010409b0 end

// @ 0x01041220
namespace SP {
cTuningEntry* cTuningEntryVector::EraseRange(cTuningEntry* pFirst, cTuningEntry* pLast)
{
  cTuningEntry* pEnd = mpEnd;   // the copies may alias the vector object, so cache the end
  cTuningEntry* p = pFirst;
  for (cTuningEntry* q = pLast; q != pEnd; ++q, ++p)
    *p = *q;
  mpEnd -= pLast - pFirst;
  return pFirst;
}
}  // namespace SP

// @ 0x01041280
namespace SP {
void cTuningEntryVector::Insert(cTuningEntry* pPos, const cTuningEntry& value)
{
  if (mpEnd != mpCap) {
    const cTuningEntry* pValue = &value;
    // A record that is already stored at or after the insertion point moves up with the tail.
    if (pValue >= pPos && pValue < mpEnd)
      ++pValue;
    // The shift is a move_backward with its first copy peeled off.
    if (mpEnd != 0)
      *mpEnd = mpEnd[-1];
    cTuningEntry* pSrc = mpEnd - 1;
    cTuningEntry* pDst = mpEnd;
    while (pSrc != pPos) {
      --pSrc;
      --pDst;
      *pDst = *pSrc;
    }
    *pPos = *pValue;
    ++mpEnd;
    return;
  }

  int nCount = (int)(mpEnd - mpBegin);
  int nNewCap = (nCount != 0) ? (nCount * 2) : 1;
  cTuningEntry* pNew = (nNewCap != 0)
                           ? (cTuningEntry*)EastlAllocate(nNewCap * (int)sizeof(cTuningEntry),
                                                          "Simulator", 0, 0, &gEastlAllocator, 0xd1)
                           : 0;
  cTuningEntry* oldBegin = mpBegin;
  cTuningEntry* pNewEnd = CopyEntries(oldBegin, pPos, pNew);
  if (pNewEnd != 0)
    *pNewEnd = value;
  cTuningEntry* oldEnd = mpEnd;
  pNewEnd = CopyEntries(pPos, oldEnd, pNewEnd + 1);
  if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
    EastlDeallocate(mpBegin);
  mpEnd = pNewEnd;
  mpBegin = pNew;
  mpCap = pNew + nNewCap;
}
}  // namespace SP

// @ 0x010413b0
namespace SP {
void cTuningEntryVector::PushDefault()
{
  if (mpEnd < mpCap) {
    cTuningEntry* p = mpEnd++;
    if (p != 0)
      new (p) cTuningEntry();
  } else {
    cTuningEntry entry;
    Insert(mpEnd, entry);
  }
}
}  // namespace SP

// @ 0x01041480
namespace SP {
void cTuningEntrySet::Release()
{
  if (mpServer != 0) {
    IMessageServer* pServer = mpServer;
    mpServer = 0;
    RemoveHandler(pServer, mpHandler, mpIdArray, mnIdCount, mnPriority);
  }
  mEntries.EraseRange(mEntries.mpBegin, mEntries.mpEnd);
}
}  // namespace SP
