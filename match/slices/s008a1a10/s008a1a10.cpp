// slice s008a1a10 -- container helpers: an EASTL-style vector insert (8-byte POD elements,
// vtable allocator kept in the vector) and the destructor pass for 0x60-byte inline buffers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The second half is the EA::Text shaping machinery used by the Arabic shaper:
//   eastl::vector<EA::Text::FeatureLookup, fixed_vector_allocator<0x5c,10,4,0,1>> primitives
//   (erase / insert / resize / copy / fill / move) plus AppendArabicGlyphCluster and the
//   DoGlyphSubstitution driver.
#include "types.h"

namespace SP {

// Raw block helpers from the EASTL runtime.
void FreeRawBlock(void* pBlock);                                   // 0x00f47380
void* CopyEntriesRaw(void* pFirst, void* pLast, void* pDest);      // 0x0099efa0

// ---------------------------------------------------------------------------
// vector<T, Allocator>::insert(pos, value) for the 8-byte POD entries used below.
// Word 0 doubles as the shaped-glyph flag word (EA::Text), whose byte at +0x05 is
// the OTF glyph class.
// ---------------------------------------------------------------------------
struct CVectorEntry {
  uint32_t mFlags;         // +0x00
  uint8_t  mnPad04;        // +0x04
  uint8_t  mnGlyphClass;   // +0x05
  uint16_t mnPad06;        // +0x06
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

// ===========================================================================
// EA::Text shaping helpers
// ===========================================================================
extern "C" __declspec(dllimport) void* __cdecl memcpy(void* pDest, const void* pSrc, uint32_t nBytes);

void* __cdecl operator new[](uint32_t nBytes, const char* pName, int nFlags, int nDebugFlags,
                             const char* pFile, int nLine);   // 0x00f473a0
inline void* operator new(uint32_t, void* pWhere) { return pWhere; }

#define EASTL_ALLOC_FILE \
  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace EA { namespace Text {

class OTFLookup;
class OTFClassDef;

// ---------------------------------------------------------------------------
// The OTF font object: its class-definition table (GetGlyphClass) sits at +0xac.
// ---------------------------------------------------------------------------
class OTFClassDef {
 public:
  uint16_t GetGlyphClass(uint16_t glyphId) const;   // 0x0089ef10
};

class OTF {
 public:
  char mPad00[0xac];
  OTFClassDef mClassDef;     // +0xac
};

// ---------------------------------------------------------------------------
// vector<OTFLookup*> with the 16-slot inline pool owned by FeatureLookup (0x58 bytes).
// ---------------------------------------------------------------------------
struct LookupPtrVector {
  OTFLookup** mpBegin;       // +0x00
  OTFLookup** mpEnd;         // +0x04
  OTFLookup** mpCapacity;    // +0x08
  void*       mpAllocName;   // +0x0c
  OTFLookup** mpPoolBegin;   // +0x10
  int         mnPad14;       // +0x14
  OTFLookup*  mpBuffer[16];  // +0x18 inline pool (0x40 bytes)

  // eastl::vector<OTFLookup*>::DoAssignFromIterator(first, last, context): the assign helper
  // lives outside this slice (0x008a1db0).
  void AssignRange(OTFLookup* const* ppFirst, OTFLookup* const* ppLast, uint32_t nContext);
};

// 0x60-byte key of the GSUB feature table: tag, glyph flags and the lookup pointer array.
struct FeatureLookup {
  uint32_t mFeatureTag;              // +0x00
  uint32_t mGlyphFlags;              // +0x04
  LookupPtrVector mLookupPtrArray;   // +0x08

  FeatureLookup();                                   // 0x008a2944 (inline, resize default)
  FeatureLookup(const FeatureLookup& other);         // 0x008a24c0
};

// Iterator wrapper the uninitialized_* primitives hand back by address.
struct LookupIterator {
  FeatureLookup* mpCurrent;    // +0x00
};

// Destroys every lookup array in [pFirst, pLast), releasing out-of-pool blocks.
struct FeatureLookupVector;

inline OTFLookup** MoveLookups(OTFLookup* const* ppFirst, OTFLookup* const* ppLast,
                               OTFLookup** ppDest);

// Empties a lookup array: the (empty) tail is moved over the head and the end pointer drops by the
// distance that move returned.
inline void ClearLookups(LookupPtrVector& arr)
{
  OTFLookup** const pLast = arr.mpEnd;
  OTFLookup** const pFirst = arr.mpBegin;
  MoveLookups(pLast, arr.mpEnd, pFirst);
  arr.mpEnd = pFirst + (arr.mpEnd - pLast);
}

FeatureLookup* CopyFeatureLookups(const FeatureLookup* pFirst, const FeatureLookup* pLast,
                                  FeatureLookup* pDest);               // 0x008a2380
FeatureLookup* CopyFeatureLookupsBackward(const FeatureLookup* pFirst, const FeatureLookup* pLast,
                                          FeatureLookup* pDest);       // 0x008a2420
LookupIterator* UninitializedCopyLookups(LookupIterator* pOut, const FeatureLookup* pFirst,
                                         const FeatureLookup* pLast, FeatureLookup* pDest);  // 0x008a2500
void FillFeatureLookups(FeatureLookup* pFirst, FeatureLookup* pLast,
                        const FeatureLookup* pValue);                  // 0x008a2570
void UninitializedFillLookups(FeatureLookup* pDest, uint32_t nCount,
                              const FeatureLookup* pValue);            // 0x008a2600
FeatureLookup* UninitializedMoveLookups(const FeatureLookup* pFirst, const FeatureLookup* pLast,
                                        FeatureLookup* pDest);         // 0x008a2660

// ---------------------------------------------------------------------------
// The FeatureLookup array: ten 0x60-byte inline slots after the three range pointers.
// ---------------------------------------------------------------------------
struct FeatureLookupVector {
  FeatureLookup* mpBegin;      // +0x00
  FeatureLookup* mpEnd;        // +0x04
  FeatureLookup* mpCapacity;   // +0x08
  void*          mpAllocName;  // +0x0c
  FeatureLookup* mpPoolBegin;  // +0x10
  char           mBuffer[0x60 * 10];   // +0x14 inline pool

  void DoDestroyValues(FeatureLookup* pFirst, FeatureLookup* pLast);         // 0x008a1c20
  FeatureLookup* erase(FeatureLookup* pFirst, FeatureLookup* pLast);          // 0x008a26d0
  void insert(FeatureLookup* pPosition, uint32_t nCount,
              const FeatureLookup& value);                                    // 0x008a2720
  void resize(uint32_t nSize);                                                // 0x008a2950
};

// vector<FeatureLookup> range as the substitution driver sees it (begin/end only).
struct FeatureLookupRange {
  FeatureLookup* mpBegin;   // +0x00
  FeatureLookup* mpEnd;     // +0x04
};

// ---------------------------------------------------------------------------
// Line layout: the glyph codes (u16 array at +0x2c) and the parallel shaped-glyph
// attributes (8-byte entries at +0x40).
// ---------------------------------------------------------------------------
struct LineLayout {
  char mPad00[0x2c];
  uint16_t* mpCodes;                     // +0x2c
  uint16_t* mpCodesEnd;                  // +0x30
  char mPad34[0x40 - 0x34];
  SP::CVectorEntryArray mShapedGlyphs;   // +0x40
};

void EraseShapedGlyphs(LineLayout* pLineLayout, SP::CVectorEntry* pFirst,
                       SP::CVectorEntry* pLast);                      // 0x00d018d0

// @ 0x008a1b70
// Replaces the run [nPosition, nPosition + nCount) of a line's glyph codes with one glyph:
// the code tail is memmoved down and the shaped attributes are erased.
void SubstituteGlyphs2(LineLayout* pLineLayout, uint32_t nPosition, uint32_t nCount,
                       uint16_t glyph)
{
  uint16_t* const pCodes = pLineLayout->mpCodes;
  uint16_t* const pSrc = pCodes + nPosition + nCount;
  uint16_t* const pDst = pCodes + nPosition + 1;

  memcpy(pDst, pSrc, (uint32_t)(pLineLayout->mpCodesEnd - pSrc) * sizeof(uint16_t));
  pLineLayout->mpCodesEnd = pDst + (pLineLayout->mpCodesEnd - pSrc);

  EraseShapedGlyphs(pLineLayout, pLineLayout->mShapedGlyphs.mpBegin + nPosition + 1,
                    pLineLayout->mShapedGlyphs.mpBegin + nPosition + nCount);

  pCodes[nPosition] = glyph;

  SP::CVectorEntry* const pAttributes = pLineLayout->mShapedGlyphs.mpBegin + nPosition;
  pAttributes->mFlags = (pAttributes->mFlags & 0xfffff9ff) | 0x100;
  pAttributes->mFlags &= 0xffffff1f;
  pAttributes->mFlags ^= (nCount << 12 ^ pAttributes->mFlags) & 0x3000;
  pAttributes->mFlags |= 0x800;
}

// @ 0x008a1c20
// Releases the out-of-pool lookup array of every FeatureLookup in [pFirst, pLast).
void FeatureLookupVector::DoDestroyValues(FeatureLookup* pFirst, FeatureLookup* pLast)
{
  while (pFirst < pLast) {
    OTFLookup** const ppBegin = pFirst->mLookupPtrArray.mpBegin;
    if (ppBegin != 0 && ppBegin != pFirst->mLookupPtrArray.mpPoolBegin)
      SP::FreeRawBlock(ppBegin);
    ++pFirst;
  }
}

// ---------------------------------------------------------------------------
// Line layout as AppendArabicGlyphCluster sees it: the cluster code array at +0x444 and
// the shaped-glyph attributes at +0x458.
// ---------------------------------------------------------------------------
struct CharVector {
  uint16_t* mpBegin;      // +0x00
  uint16_t* mpEnd;        // +0x04
  uint16_t* mpCapacity;   // +0x08

  void DoInsertValue(uint16_t* pPos, const uint16_t& value);   // 0x008a1900
};

struct ArabicLayout {
  char mPad0000[0x444];
  CharVector mAnalysisGlyphs;            // +0x444
  char mPad0450[0x458 - 0x450];
  SP::CVectorEntryArray mShapedGlyphs;   // +0x458

  void AppendArabicGlyphCluster(uint32_t nUnused1, uint32_t nForm, const uint16_t* pJointType,
                                uint32_t nUnused2, const uint16_t* pCharCodes, uint32_t nCount,
                                uint32_t nJointFlags, OTF* pOTF);   // 0x008a1c60
};

// @ 0x008a1c60
// Appends one Arabic cluster of nCount code points: every code goes to the cluster code
// array and its shaped-glyph record gets the form/position/joint bits and the OTF class.
void ArabicLayout::AppendArabicGlyphCluster(uint32_t nUnused1, uint32_t nForm,
                                            const uint16_t* pJointType, uint32_t nUnused2,
                                            const uint16_t* pCharCodes, uint32_t nCount,
                                            uint32_t nJointFlags, OTF* pOTF)
{
  const uint32_t nFormBits = (nForm & 3) << 12;
  const uint32_t nCountBits = (nCount & 7) << 8;
  const uint32_t nJointBits = (nJointFlags & 1) << 14;
  const OTFClassDef* const pClassDef = &pOTF->mClassDef;

  for (uint32_t i = 0; i < nCount; ++i) {
    const uint16_t glyphCode = pCharCodes[i];

    if (mAnalysisGlyphs.mpEnd < mAnalysisGlyphs.mpCapacity) {
      uint16_t* const pNew = mAnalysisGlyphs.mpEnd;
      mAnalysisGlyphs.mpEnd = pNew + 1;
      if (pNew != 0)
        *pNew = glyphCode;
    } else {
      mAnalysisGlyphs.DoInsertValue(mAnalysisGlyphs.mpEnd, glyphCode);
    }

    SP::CVectorEntry* pAttribute;
    if (mShapedGlyphs.mpEnd < mShapedGlyphs.mpCap) {
      pAttribute = mShapedGlyphs.mpEnd;
      mShapedGlyphs.mpEnd = pAttribute + 1;
      if (pAttribute != 0) {
        pAttribute->mFlags = 0;
        pAttribute->mnPad04 = 0;
        pAttribute->mnPad06 = 0;
      }
    } else {
      SP::CVectorEntry empty;
      empty.mFlags = 0;
      empty.mnPad04 = 0;
      empty.mnPad06 = 0;
      mShapedGlyphs.Insert(mShapedGlyphs.mpEnd, empty);
      pAttribute = mShapedGlyphs.mpEnd - 1;
    }

    uint32_t nFlags = pAttribute->mFlags & 0xfffff810;
    nFlags |= nCountBits;
    nFlags &= 0xffffc7ff;
    nFlags |= nFormBits;
    nFlags &= 0xffffbfff;
    nFlags |= (i & 7) << 5;
    nFlags |= nJointBits;
    nFlags = ((uint32_t)(*pJointType != 0xfffc) << 4 ^ nFlags) & 0x10 ^ nFlags;
    pAttribute->mFlags = nFlags;
    pAttribute->mnGlyphClass = (uint8_t)pClassDef->GetGlyphClass(glyphCode);
  }
}

uint32_t DoGlyphSubstitution(LineLayout& lineLayout, uint32_t nPosition,
                             const FeatureLookup& lookup, const OTFLookup& otfLookup,
                             const OTF* pOTF);                        // 0x008a1f60

// @ 0x008a2120
// Runs every OTF lookup of every feature that applies at each line position.
void DoGlyphSubstitutionsInLine(LineLayout* pLineLayout, uint32_t nPosition,
                                const FeatureLookupRange* pLookups, const OTF* pOTF)
{
  uint32_t nCount = (uint32_t)(pLookups->mpEnd - pLookups->mpBegin);

  if (nCount != 0) {
    FeatureLookup* pLookup = pLookups->mpBegin;

    do {
      if (pLookup->mLookupPtrArray.mpBegin != pLookup->mLookupPtrArray.mpEnd) {
        const uint32_t nLookups =
            (uint32_t)(pLookup->mLookupPtrArray.mpEnd - pLookup->mLookupPtrArray.mpBegin);

        for (uint32_t i = 0; i < nLookups; ++i) {
          const OTFLookup* const pOtfLookup = pLookup->mLookupPtrArray.mpBegin[i];
          uint32_t nCurrent = nPosition;

          if (nCurrent < (uint32_t)(pLineLayout->mpCodesEnd - pLineLayout->mpCodes)) {
            do {
              nCurrent = DoGlyphSubstitution(*pLineLayout, nCurrent, *pLookup, *pOtfLookup, pOTF);
            } while (nCurrent < (uint32_t)(pLineLayout->mpCodesEnd - pLineLayout->mpCodes));
          }
        }
      }

      ++pLookup;
    } while (--nCount != 0);
  }
}

// @ 0x008a24c0
// Copy constructor: the lookup array starts on its own inline pool and takes a copy of
// other's lookups through the assign helper.
FeatureLookup::FeatureLookup(const FeatureLookup& other)
{
  mFeatureTag = other.mFeatureTag;
  mGlyphFlags = other.mGlyphFlags;
  LookupPtrVector& lookupArray = mLookupPtrArray;
  lookupArray.mpPoolBegin = lookupArray.mpBuffer;
  lookupArray.mpEnd = lookupArray.mpBuffer;
  lookupArray.mpBegin = lookupArray.mpBuffer;
  lookupArray.mpCapacity = lookupArray.mpBegin + 16;
  mLookupPtrArray.AssignRange(other.mLookupPtrArray.mpBegin, other.mLookupPtrArray.mpEnd,
                              (uint32_t)&other);
}

// Default constructor used by vector::resize: zero feature tag, empty inline array.
FeatureLookup::FeatureLookup()
{
  mFeatureTag = 0;
  mGlyphFlags = 0;
  mLookupPtrArray.mpPoolBegin = mLookupPtrArray.mpBuffer;
  mLookupPtrArray.mpEnd = mLookupPtrArray.mpBuffer;
  mLookupPtrArray.mpBegin = mLookupPtrArray.mpBuffer;
  mLookupPtrArray.mpCapacity = mLookupPtrArray.mpBuffer;
}

// @ 0x008a2380
// Forwards one FeatureLookup: the tag and flags are copied, the lookup array is emptied and
// refilled from the source through the assign helper.
FeatureLookup* CopyFeatureLookups(const FeatureLookup* pFirst, const FeatureLookup* pLast,
                                  FeatureLookup* pDest)
{
  while (pFirst != pLast) {
    pDest->mFeatureTag = pFirst->mFeatureTag;
    pDest->mGlyphFlags = pFirst->mGlyphFlags;
    if (&pDest->mLookupPtrArray != &pFirst->mLookupPtrArray) {
      ClearLookups(pDest->mLookupPtrArray);
      pDest->mLookupPtrArray.AssignRange(pFirst->mLookupPtrArray.mpBegin,
                                         pFirst->mLookupPtrArray.mpEnd, (uint32_t)pDest);
    }
    ++pFirst;
    ++pDest;
  }

  return pDest;
}

// @ 0x008a2420
// The same forward copy run backwards over [pFirst, pLast) onto pDest.
FeatureLookup* CopyFeatureLookupsBackward(const FeatureLookup* pFirst, const FeatureLookup* pLast,
                                          FeatureLookup* pDest)
{
  while (pLast != pFirst) {
    --pLast;
    --pDest;
    pDest->mFeatureTag = pLast->mFeatureTag;
    pDest->mGlyphFlags = pLast->mGlyphFlags;
    if (&pDest->mLookupPtrArray != &pLast->mLookupPtrArray) {
      ClearLookups(pDest->mLookupPtrArray);
      pDest->mLookupPtrArray.AssignRange(pLast->mLookupPtrArray.mpBegin,
                                         pLast->mLookupPtrArray.mpEnd, (uint32_t)pDest);
    }
  }

  return pDest;
}

// eastl::move(first, last, dest) for OTFLookup* ranges (memmove with last - first elements).
inline OTFLookup** MoveLookups(OTFLookup* const* ppFirst, OTFLookup* const* ppLast,
                               OTFLookup** ppDest)
{
  return (OTFLookup**)memcpy(ppDest, ppFirst, (uint32_t)(ppLast - ppFirst) * sizeof(OTFLookup*));
}

// Placement construction of one FeatureLookup.
inline FeatureLookup* ConstructLookup(FeatureLookup* pDest, const FeatureLookup& other)
{
  return ::new ((void*)pDest) FeatureLookup(other);
}

// @ 0x008a2500
// uninitialized_copy of [pFirst, pLast) onto pDest, handing the advanced cursor back
// through pOut.
LookupIterator* UninitializedCopyLookups(LookupIterator* pOut, const FeatureLookup* pFirst,
                                         const FeatureLookup* pLast, FeatureLookup* pDest)
{
  pOut->mpCurrent = pDest;

  while (pFirst != pLast) {
    if (pOut->mpCurrent != 0)
      ConstructLookup(pOut->mpCurrent, *pFirst);
    ++pOut->mpCurrent;
    ++pFirst;
  }

  return pOut;
}

// @ 0x008a2570
// Assigns a FeatureLookup value to every record in [pFirst, pLast).
void FillFeatureLookups(FeatureLookup* pFirst, FeatureLookup* pLast,
                        const FeatureLookup* pValue)
{
  while (pFirst != pLast) {
    pFirst->mFeatureTag = pValue->mFeatureTag;
    pFirst->mGlyphFlags = pValue->mGlyphFlags;
    if (&pFirst->mLookupPtrArray != &pValue->mLookupPtrArray) {
      memcpy(pFirst->mLookupPtrArray.mpBegin, pFirst->mLookupPtrArray.mpEnd, 0);
      pFirst->mLookupPtrArray.mpEnd = pFirst->mLookupPtrArray.mpBegin;
      pFirst->mLookupPtrArray.AssignRange(pValue->mLookupPtrArray.mpBegin,
                                          pValue->mLookupPtrArray.mpEnd, (uint32_t)pFirst);
    }
    ++pFirst;
  }
}

// @ 0x008a2600
// uninitialized_fill_n: nCount FeatureLookups constructed from pValue at pDest.
void UninitializedFillLookups(FeatureLookup* pDest, uint32_t nCount,
                              const FeatureLookup* pValue)
{
  while (nCount != 0) {
    if (pDest != 0)
      ConstructLookup(pDest, *pValue);
    --nCount;
    ++pDest;
  }
}

// @ 0x008a2660
// uninitialized_move of [pFirst, pLast) onto pDest; returns the advanced destination.
FeatureLookup* UninitializedMoveLookups(const FeatureLookup* pFirst, const FeatureLookup* pLast,
                                        FeatureLookup* pDest)
{
  FeatureLookup* pOut = pDest;

  while (pFirst != pLast) {
    if (pOut != 0) {
      pOut->mFeatureTag = pFirst->mFeatureTag;
      pOut->mGlyphFlags = pFirst->mGlyphFlags;
      pOut->mLookupPtrArray.mpPoolBegin = pOut->mLookupPtrArray.mpBuffer;
      pOut->mLookupPtrArray.mpEnd = pOut->mLookupPtrArray.mpBuffer;
      pOut->mLookupPtrArray.mpBegin = pOut->mLookupPtrArray.mpBuffer;
      pOut->mLookupPtrArray.mpCapacity = pOut->mLookupPtrArray.mpBuffer + 16;
      pOut->mLookupPtrArray.AssignRange(pFirst->mLookupPtrArray.mpBegin,
                                        pFirst->mLookupPtrArray.mpEnd, (uint32_t)pDest);
    }
    ++pFirst;
    ++pOut;
  }

  return pOut;
}

// @ 0x008a26d0
// Erases [pFirst, pLast): the tail is copied down, the vacated records destroyed and the
// end pointer pulled back.  Returns pFirst (the new logical end of the erased range).
FeatureLookup* FeatureLookupVector::erase(FeatureLookup* pFirst, FeatureLookup* pLast)
{
  FeatureLookup* const pNewEnd = CopyFeatureLookups(pLast, mpEnd, pFirst);
  DoDestroyValues(pNewEnd, mpEnd);
  mpEnd -= pLast - pFirst;
  return pFirst;
}

// The RT allocator used when the ten inline slots are exhausted (operator new[]).
void* AllocateFeatureLookups(uint32_t nCount)
{
  return operator new[](nCount * sizeof(FeatureLookup), "EASTL", 0, 0, EASTL_ALLOC_FILE, 0xd1);
}

// @ 0x008a2720
// Inserts nCount copies of value in front of pPosition, growing (doubling) when the inline
// pool is full.
void FeatureLookupVector::insert(FeatureLookup* pPosition, uint32_t nCount,
                                 const FeatureLookup& value)
{
  if (nCount > (uint32_t)(mpCapacity - mpEnd)) {
    const uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
    const uint32_t nDouble = nSize * 2;
    uint32_t nNewCapacity = (nSize != 0) ? nDouble : 1;
    if (nSize + nCount > nNewCapacity)
      nNewCapacity = nSize + nCount;

    FeatureLookup* const pNew =
        (nNewCapacity != 0) ? (FeatureLookup*)AllocateFeatureLookups(nNewCapacity) : 0;

    const FeatureLookup* const pOldBegin = mpBegin;
    const FeatureLookup* const pOldEnd = mpEnd;

    FeatureLookup* pNewEnd = UninitializedMoveLookups(pOldBegin, pPosition, pNew);
    SP::DestroyInlineBuffers((SP::CInlineBuffer*)pOldBegin, (SP::CInlineBuffer*)pPosition,
                             (SP::CInlineBuffer*)pNew);

    UninitializedFillLookups(pNewEnd, nCount, &value);
    pNewEnd += nCount;

    FeatureLookup* const pEnd = UninitializedMoveLookups(pPosition, pOldEnd, pNewEnd);
    SP::DestroyInlineBuffers((SP::CInlineBuffer*)pPosition, (SP::CInlineBuffer*)pOldEnd,
                             (SP::CInlineBuffer*)pNewEnd);

    if (mpBegin != 0 && (void*)mpBegin != (void*)mpPoolBegin)
      SP::FreeRawBlock(mpBegin);

    mpBegin = pNew;
    mpEnd = pEnd;
    mpCapacity = pNew + nNewCapacity;
    return;
  }

  if (nCount == 0)
    return;

  FeatureLookup valueCopy(value);

  const uint32_t nAfter = (uint32_t)(mpEnd - pPosition);
  if (nCount < nAfter) {
    LookupIterator newEnd;
    UninitializedCopyLookups(&newEnd, mpEnd - nCount, mpEnd, mpEnd);
    mpEnd += nCount;
    CopyFeatureLookupsBackward(pPosition, mpEnd - nCount * 2, newEnd.mpCurrent);
    FillFeatureLookups(pPosition, pPosition + nCount, &valueCopy);
  } else {
    UninitializedFillLookups(mpEnd, nCount - nAfter, &valueCopy);
    mpEnd += nCount - nAfter;
    LookupIterator newEnd;
    newEnd.mpCurrent = mpEnd;
    UninitializedCopyLookups(&newEnd, pPosition, pPosition + nAfter, mpEnd);
    mpEnd += nAfter;
    FillFeatureLookups(pPosition, pPosition + nAfter, &valueCopy);
  }

  if (valueCopy.mLookupPtrArray.mpBegin != 0 &&
      valueCopy.mLookupPtrArray.mpBegin != valueCopy.mLookupPtrArray.mpPoolBegin)
    SP::FreeRawBlock(valueCopy.mLookupPtrArray.mpBegin);
}

// @ 0x008a2950
// Grows the array with empty lookups or erases the elements past nSize.
void FeatureLookupVector::resize(uint32_t nSize)
{
  const uint32_t nCurrent = (uint32_t)(mpEnd - mpBegin);

  if (nSize > nCurrent) {
    FeatureLookup empty;
    insert(mpEnd, nSize - nCurrent, empty);
  } else {
    erase(mpBegin + nSize, mpEnd);
  }
}

}}  // namespace EA::Text
