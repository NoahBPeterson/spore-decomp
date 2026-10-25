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
#include <stdlib.h>
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

// ---------------------------------------------------------------------------
// EA::IO -- OpenType stream reader helpers used by the OTF table readers.
// ---------------------------------------------------------------------------
namespace EA { namespace IO {

typedef uint32_t size_type;
enum Endian { kEndianBig = 0, kEndianLittle = 1 };

class IStream;

// @ 0x0093a700
bool ReadUint16(IStream* pIS, uint16_t* pValue, size_type nCount, Endian endianSource);

// Stream interface: vtable slot +0x28 is Seek (position, origin) and slot +0x30
// is Read (buffer, byteCount).  Spelled with named members so the reader code
// below can stay free of raw offsets.
class IStream
{
 public:
  virtual void        vf00();
  virtual void        vf04();
  virtual void        vf08();
  virtual void        vf0c();
  virtual void        vf10();
  virtual void        vf14();
  virtual void        vf18();
  virtual void        vf1c();
  virtual void        vf20();
  virtual void        vf24();
  virtual void        Seek(uint32_t nPosition, int nOrigin);   // +0x28
  virtual void        vf2c();
  virtual uint32_t    Read(void* pDest, uint32_t nBytes);      // +0x30
};

}}  // namespace EA::IO

// ---------------------------------------------------------------------------
// EA::Allocator -- the bump allocator the OTF readers carve from.
// ---------------------------------------------------------------------------
namespace EA { namespace Allocator {

class StackAllocator
{
 public:
  size_t  mnDefaultBlockSize;     // +0x00
  void*   mpCurrentBlock;         // +0x04
  char*   mpCurrentBlockEnd;      // +0x08
  char*   mpCurrentObjectBegin;   // +0x0c
  char*   mpCurrentObjectEnd;     // +0x10

  // AllocateNewBlock @ 0x00928ba0
  bool AllocateNewBlock(size_t nSize);
};

// StackAllocator::Malloc -- bump-allocates nSize bytes (already rounded) and
// returns the block, or NULL when the block request fails.
inline uint32_t* MallocBlock(StackAllocator* pAllocator, size_t nSize)
{
  if ((intptr_t)pAllocator->mpCurrentBlockEnd
      - ((intptr_t)pAllocator->mpCurrentObjectBegin + (intptr_t)nSize) < 0)
  {
    if (!pAllocator->AllocateNewBlock(nSize))
      return (uint32_t*)0;
  }

  uint32_t* p = (uint32_t*)pAllocator->mpCurrentObjectBegin;
  pAllocator->mpCurrentObjectBegin = (char*)p + nSize;
  pAllocator->mpCurrentObjectEnd   = pAllocator->mpCurrentObjectBegin;
  return p;
}

// EA::Allocator::create_array<T>: free cdecl function.  Reserves
// sizeof(uint32_t) + sizeof(T)*count bytes (rounded up to 8) from the bump
// allocator, stores the element count in the leading word and returns the
// element block.  Element constructors are NOT run.
template <typename T>
inline T* create_array(StackAllocator* pAllocator, uint32_t nCount)
{
  const size_t nSize = (sizeof(uint32_t) + sizeof(T) * nCount + 7) & ~(size_t)7;

  uint32_t* const p = MallocBlock(pAllocator, nSize);
  *p = nCount;
  return (T*)(p + 1);
}

}}  // namespace EA::Allocator

// ---------------------------------------------------------------------------
// EA::Text -- OpenType structures read by the OTF table readers.
// ---------------------------------------------------------------------------
namespace EA { namespace Text {

// A coverage table (format 1 = glyph array, format 2 = range records).
struct OTFCoverageElt  { uint16_t mStart; uint16_t mEnd; uint16_t mStartCoverageIndex; };
struct OTFCoverage
{
  uint16_t          mCoverageFormat;   // +0x00
  uint16_t          mCount;            // +0x02
  // format 1 stores a glyph-id array, format 2 a range-record array; the reader
  // writes whichever it read through this one slot.
  uint16_t*         mpGlyphIdArray;    // +0x04
};

// OC.. these match the elemets carved out by create_array below.
struct OTFLangSysRecord      { uint16_t mValue; };
struct OTFLookup             { uint16_t mLookupType; uint16_t mLookupFlag; uint16_t mSubTableCount; };
struct OTFLookupSubTableGsub { uint8_t  mData[0x1c]; };
struct OTFLigature           { uint16_t mLigGlyph; uint16_t mComponentCount; uint16_t mComponents[2]; };
struct OTFClassRule          { uint8_t  mData[0x10]; };
struct OTFChainClassRule     { uint8_t  mData[0x20]; };

}}  // namespace EA::Text

namespace EA { namespace Allocator {

template EA::Text::OTFLangSysRecord*      create_array<EA::Text::OTFLangSysRecord>(StackAllocator*, uint32_t);      // @ 0x0089f0d0
template EA::Text::OTFLookup*             create_array<EA::Text::OTFLookup>(StackAllocator*, uint32_t);             // @ 0x0089f120
template EA::Text::OTFLookupSubTableGsub* create_array<EA::Text::OTFLookupSubTableGsub>(StackAllocator*, uint32_t); // @ 0x0089f170
template EA::Text::OTFLigature*           create_array<EA::Text::OTFLigature>(StackAllocator*, uint32_t);           // @ 0x0089f1d0
template EA::Text::OTFClassRule*          create_array<EA::Text::OTFClassRule>(StackAllocator*, uint32_t);          // @ 0x0089f220
template EA::Text::OTFChainClassRule*     create_array<EA::Text::OTFChainClassRule>(StackAllocator*, uint32_t);     // @ 0x0089f270

}}  // namespace EA::Allocator

// ---------------------------------------------------------------------------
// UTF-16 host<->big-endian conversions for fields the OTF readers overwrite in
// place: ea's FromBigEndian/ToBigEndian byte-swap the 16-bit word.
// ---------------------------------------------------------------------------
static inline uint16_t FromBigEndian(uint16_t n)
{
  return _byteswap_ushort(n);
}

static inline uint16_t ToBigEndian(uint16_t n)
{
  return _byteswap_ushort(n);
}

// ---------------------------------------------------------------------------
// The eastl::vector<wchar_t>-like container the OTFAttachList/OTF features
// arrays live in: a POD vector with an inline fixed_buffer_allocator (inline
// storage at +0x18, 0x800 bytes) used by FUN_008a12f0.
// ---------------------------------------------------------------------------
struct OTFWordVector
{
  uint16_t* mpBegin;         // +0x00
  uint16_t* mpEnd;           // +0x04
  uint16_t* mpCapacity;      // +0x08
  uint8_t   mPad0c[4];       // +0x0c (unused here)
  uint16_t* mpInlineBegin;   // +0x10
  uint8_t   mPad14[4];       // +0x14
  // The fixed-buffer allocator's inline storage: 0x800 bytes (0x400 words),
  // which Reset points mpBegin at.  A local of this type is 0x818 bytes.
  uint16_t  mInlineBuffer[0x400];   // +0x18

  OTFWordVector() {}

  __declspec(noinline) void Insert(uint16_t* pPosition, uint32_t nCount, const uint16_t& value);   // 0x008a0fc0
  __declspec(noinline) OTFWordVector* Reset(uint32_t n, const uint16_t* pValue);   // 0x008a12f0
};

// The raw-block release the reader runs once a temporary OTFWordVector has
// spilled out of its inline storage (EA::Allocator::FreeRawBlock).
// 0x00f47380
void FreeRawBlock(void* pBlock);

// The eastl `insert(position, n, value)` empty path that Reset's n==0 arm runs:
// a zero-length move whose destination is offset by the (zero) count.
inline void MoveEmpty(uint16_t* pPosition, uint32_t n)
{
  uint16_t* const pEnd = pPosition + n;
  memcpy(pEnd, pPosition, (size_t)((uintptr_t)pPosition - (uintptr_t)pEnd));
}

// @ 0x008a0fc0
// eastl vector<wchar_t>-style insert-value: inserts nCount copies of `value` at
// pPosition, growing (doubling, or exact when larger) through EA::Allocator's
// raw operator new when the tail does not fit in the remaining capacity.
void OTFWordVector::Insert(uint16_t* pPosition, uint32_t nCount, const uint16_t& value)
{
  uint16_t* const pOldEnd = mpEnd;

  if (((uint32_t)(mpCapacity - mpEnd) >> 1) < nCount) {
    const uint32_t nOld = (uint32_t)((mpEnd - mpBegin) >> 1);
    uint32_t       nMin = nOld * 2;
    if (nOld == 0)
      nMin = 1;
    const uint32_t nWant = nOld + nCount;
    if (nWant >= nMin)
      nMin = nWant;

    uint16_t* pNewData = 0;
    if (nMin != 0)
      pNewData = (uint16_t*)operator new(nMin * 2, (void*)0);

    const size_t nHead = (size_t)((uintptr_t)pPosition - (uintptr_t)mpBegin);
    uint16_t*    pMid  = pNewData;
    if (nHead != 0)
      pMid = (uint16_t*)memcpy(pNewData, mpBegin, nHead) + (nHead >> 1);

    for (uint32_t i = 0; i < nCount; ++i)
      pMid[i] = value;

    uint16_t* const pAfterFill = pMid + nCount;
    const size_t    nTail      = (size_t)((uintptr_t)pOldEnd - (uintptr_t)pPosition);
    if (nTail != 0)
      memcpy(pAfterFill, pPosition, nTail);

    if (mpBegin != 0 && mpBegin != mpInlineBegin)
      operator delete(mpBegin);

    mpBegin    = pNewData;
    mpEnd      = (uint16_t*)((uint8_t*)pAfterFill + nTail);
    mpCapacity = pNewData + nMin;
    return;
  }

  if (nCount == 0)
    return;

  const uint32_t nTail = (uint32_t)((mpEnd - pPosition) >> 1);
  if (nCount < nTail) {
    // the tail has room: move it up by nCount and fill the hole
    memmove(pPosition + nCount, pPosition, (size_t)((uintptr_t)pOldEnd - (uintptr_t)pPosition));
    for (uint16_t* p = pPosition; p != pPosition + nCount; ++p)
      *p = value;
    mpEnd = pOldEnd + nCount;
    return;
  }

  // fill the tail, then append the remainder past the (shifted) old tail
  const uint32_t nExtra = nCount - nTail;
  for (uint16_t* p = mpEnd; p != mpEnd + nExtra; ++p)
    *p = value;

  mpEnd += nExtra;
  memmove(mpEnd, pPosition, (size_t)((uintptr_t)pOldEnd - (uintptr_t)pPosition));
  mpEnd += nTail;

  for (uint16_t* p = pPosition; p != pOldEnd; ++p)
    *p = value;
}

// @ 0x008a12f0
// Constructs the fixed-buffer word vector whose inline storage is at +0x18.
// When n == 0 the vector is left empty at its inline buffer.
OTFWordVector* OTFWordVector::Reset(uint32_t n, const uint16_t* pValue)
{
  OTFWordVector* const pThis = this;
  uint16_t* const      pInline = (uint16_t*)((uint8_t*)this + 0x18);

  pThis->mpInlineBegin = pInline;
  pThis->mpCapacity    = pInline + 0x400;   // 0x800 bytes / sizeof(uint16_t)
  pThis->mpEnd         = pInline;
  pThis->mpBegin       = pInline;

  if (n != 0) {
    Insert(pInline, n, *pValue);
    return pThis;
  }

  MoveEmpty(pInline, n);
  pThis->mpEnd += n;
  return pThis;
}

// ---------------------------------------------------------------------------
// EA::Text::OTF -- the OpenType table reader.
// ---------------------------------------------------------------------------
namespace EA { namespace Text {

// ---- script list (used by the GSUB feature lookup) -------------------------

// A language system table: the lookup-order / required-feature indices plus the
// feature-index array ReadScriptList carved behind it.
struct OTFLangSys
{
  uint16_t  mLookupOrder;           // +0x00
  uint16_t  mRequiredFeatureIndex;  // +0x02
  uint16_t  mFeatureIndexCount;     // +0x04
  uint16_t  mPad06;                 // +0x06
  uint16_t* mpFeatureIndexArray;    // +0x08
};

// 0x14-byte entry of a script's language-system record array.
struct OTFLangSysEntry
{
  uint32_t   mLangSysTag;   // +0x00
  uint32_t   mPad04;        // +0x04
  OTFLangSys mLangSys;      // +0x08
};

// 0x1c-byte script entry.
struct OTFScript
{
  uint32_t         mScriptTag;            // +0x00
  uint32_t         mPad04;                // +0x04
  OTFLangSys       mDefaultLangSys;       // +0x08
  uint16_t         mLangSysRecordCount;   // +0x14
  uint16_t         mPad16;                // +0x16
  OTFLangSysEntry* mpLangSysRecordArray;  // +0x18
};

struct OTFScriptList
{
  uint16_t    mPad00;         // +0x00
  uint16_t    mScriptCount;   // +0x02
  OTFScript*  mpScriptArray;  // +0x04

  // GetLangSys (defined in slice s0089e350).
  OTFLangSys* GetLangSys(uint32_t* pScriptTag, uint32_t* pLangSysTag, bool bDefault);
};

// ---- lookup list -----------------------------------------------------------

// A class definition table (GSUB/GDEF): 12 bytes.
struct OTFClassDef
{
  uint16_t  mClassFormat;   // +0x00
  uint16_t  mStartGlyph;    // +0x02
  uint16_t  mCount;         // +0x04
  uint16_t  mPad06;         // +0x06
  uint16_t* mpArray;        // +0x08
};

// A carved GSUB lookup sub-table: 0x38 bytes.
struct OTFLookupSubTable
{
  uint16_t    mFormat;          // +0x00
  uint16_t    mCoverageOffset;  // +0x02
  OTFCoverage mCoverage;        // +0x04
  uint8_t     mData[0x2c];      // +0x0c
};

// One lookup of a lookup list: 0x10 bytes.
struct OTFLookupEntry
{
  uint16_t  mOffset;            // +0x00 (relative to the list's own base)
  uint16_t  mLookupType;        // +0x02
  uint16_t  mLookupFlag;        // +0x04
  uint16_t  mSubTableCount;     // +0x06
  uint16_t* mpSubTableOffsets;  // +0x08
  void*     mpSubTableArray;    // +0x0c (only filled when the lookup type is 4)
};

// The 8-byte header ReadLookupList fills: a count plus the entry array.
struct OTFLookupList
{
  uint16_t         mPad00;         // +0x00
  uint16_t         mCount;         // +0x02
  OTFLookupEntry*  mpLookupArray;  // +0x04
};

// ---- GDEF ------------------------------------------------------------------

// An attach point carved by create_array<OTFLigature>: 8 bytes.
struct OTFAttachPoint
{
  uint16_t  mPointIndexCount;   // +0x00
  uint16_t  mPad02;             // +0x02
  uint16_t* mpPointIndexArray;  // +0x04
};

// The GDEF attach list (this+0xb8 of the GDEF blob).
struct OTFAttachList
{
  uint16_t        mCoverageOffset;    // +0x00
  uint16_t        mPad02;             // +0x02
  OTFCoverage     mCoverage;          // +0x04
  uint16_t        mGlyphCount;        // +0x10
  uint16_t        mPad12;             // +0x12
  OTFAttachPoint* mpAttachPointArray; // +0x14
};

// The GDEF ligature-caret list header (this+0xcc of the GDEF blob).
struct OTFLigCaretList
{
  OTFCoverage mCoverage;            // +0x00
  uint16_t    mLigatureGlyphCount;  // +0x08
  uint16_t    mPad0a;               // +0x0a
  void*       mpLigatureGlyphArray; // +0x0c
};

// The 0x48-byte GDEF header blob read into OTF::mGdef.
struct OTFGdef
{
  uint32_t        mVersion;                  // +0x00
  uint16_t        mOffsetGlyphClassDef;      // +0x04
  uint16_t        mOffsetAttachList;         // +0x06
  uint16_t        mOffsetLigCaretList;       // +0x08
  uint16_t        mOffsetMarkAttachClassDef; // +0x0a
  OTFClassDef     mGlyphClassDef;            // +0x0c
  OTFAttachList   mAttachList;               // +0x18
  OTFLigCaretList mLigCaretList;             // +0x2c
  OTFClassDef     mMarkAttachClassDef;       // +0x3c
};

// Table directory entry (the reader's mTableDirectory array at this+0x2c).
struct OTFTableDirectoryEntry
{
  uint32_t  mTag;        // +0x00
  uint32_t  mChecksum;   // +0x04
  uint32_t  mOffset;     // +0x08
  uint32_t  mLength;     // +0x0c
};

class OTF
{
 public:
  uint8_t mPad00[0x18];                          // +0x00
  void*   mPad18;                                // +0x18
  void*   mFeatureLookupVectors;                 // +0x1c
  void*   mAttachTablePtrs;                      // +0x20
  uint8_t mPad24[8];                             // +0x24
  OTFTableDirectoryEntry* mTableDirectory;       // +0x2c
  uint8_t mPad30[4];                             // +0x30
  uint32_t mGdefTableOffset;                     // +0x34 (the GDEF table's own base)
  uint8_t mPad38[0x68];                          // +0x38
  OTFGdef  mGdef;                                // +0xa0 (the 0x48-byte GDEF blob)
  uint8_t mPadE8[0x4c];                          // +0xe8
  EA::IO::IStream* mpFontStream;                 // +0x134
  EA::Allocator::StackAllocator mStackAllocator; // +0x138

  // ReadLookupList and ReadGdef (definitions below).
  bool ReadLookupList(OTFLookupList* pList, uint32_t nOffset, uint32_t nLookupType);
  bool ReadGdef();

  // Defined in other slices: ReadClassDef, ReadCoverage, ReadGsubArrayEntry.
  bool ReadClassDef(OTFClassDef& classDef, uint32_t fileOffset);
  bool ReadCoverage(OTFCoverage& coverage, uint32_t fileOffset);
  bool ReadGsubArrayEntry(uint32_t pSubTable, uint32_t nType, uint32_t nFormat,
                          OTFLookupSubTable& subTable);
};

// A built lookup as the feature builder reads it: 0x10 bytes.
struct OTFBuiltLookup
{
  uint32_t  mLookupIndex;       // +0x00
  uint32_t  mPad04;             // +0x04
  uint16_t  mSubTableCount;     // +0x08
  uint16_t  mPad0a;             // +0x0a
  uint16_t* mpSubTableIndices;  // +0x0c
};

// The pointer vector the feature builder appends its sub-table refs to.
struct OTFPointerVector
{
  uint32_t* mpBegin;     // +0x00
  uint32_t* mpEnd;       // +0x04
  uint32_t* mpCapacity;  // +0x08

  void Insert(uint32_t* pPosition, const uint32_t& value);   // 0x00899480
};

// A feature lookup request: 0x60 bytes.
struct OTFFeatureLookup
{
  uint32_t         mLookupIndex;   // +0x00
  uint32_t         mPad04;         // +0x04
  OTFPointerVector mSubTableRefs;  // +0x08
  uint8_t          mPad14[0x4c];   // +0x14
};

struct OTFFeatureLookupVector
{
  OTFFeatureLookup* mpBegin;     // +0x00
  OTFFeatureLookup* mpEnd;       // +0x04
  OTFFeatureLookup* mpCapacity;  // +0x08
};

// The GSUB/GDEF feature builder (no PDB name).
class OTFGsubGpos
{
 public:
  uint8_t         mPad00[0x0c];    // +0x00
  OTFScriptList   mScriptList;     // +0x0c
  OTFBuiltLookup* mpLookupArray;   // +0x18
  uint8_t         mPad1c[4];       // +0x1c
  uint8_t*        mpSubTableBase;  // +0x20
  uint8_t         mPad24[0x10];    // +0x24
  uint32_t        mTableBase;      // +0x34

  void BuildFeatureLookup(uint32_t* pScriptTag, uint32_t* pLangSysTag,
                          OTFFeatureLookupVector* pVector);   // 0x008a11c0
};

}}  // namespace EA::Text

// ---------------------------------------------------------------------------
// EA::Text::OTF::ReadLookupList -- reads a GSUB/GDEF lookup list: the lookup
// offsets, then each lookup's type/flag/sub-table count with its sub-table
// offset array, and (for lookup type 4) the sub-tables themselves plus their
// coverage tables.
// ---------------------------------------------------------------------------

// @ 0x008a0b50
bool EA::Text::OTF::ReadLookupList(OTFLookupList* pList, uint32_t nOffset, uint32_t nLookupType)
{
  mpFontStream->Seek(nOffset, 0);
  EA::IO::ReadUint16(mpFontStream, &pList->mCount, 1, EA::IO::kEndianBig);

  pList->mpLookupArray =
      EA::Allocator::create_array<OTFLookupEntry>(&mStackAllocator, pList->mCount);

  for (uint32_t i = 0; i < pList->mCount; ++i)
    EA::IO::ReadUint16(mpFontStream, &pList->mpLookupArray[i].mOffset, 1, EA::IO::kEndianBig);

  for (uint32_t i = 0; i < pList->mCount; ++i)
  {
    OTFLookupEntry* const pLookup = &pList->mpLookupArray[i];

    mpFontStream->Seek(nOffset + pLookup->mOffset, 0);
    EA::IO::ReadUint16(mpFontStream, &pLookup->mLookupType, 1, EA::IO::kEndianBig);
    EA::IO::ReadUint16(mpFontStream, &pLookup->mLookupFlag, 1, EA::IO::kEndianBig);
    EA::IO::ReadUint16(mpFontStream, &pLookup->mSubTableCount, 1, EA::IO::kEndianBig);

    pLookup->mpSubTableOffsets =
        EA::Allocator::create_array<uint16_t>(&mStackAllocator, pLookup->mSubTableCount);
    EA::IO::ReadUint16(mpFontStream, pLookup->mpSubTableOffsets, pLookup->mSubTableCount,
                       EA::IO::kEndianBig);
  }

  for (uint32_t i = 0; i < pList->mCount; ++i)
  {
    OTFLookupEntry* const pLookup = &pList->mpLookupArray[i];

    if (nLookupType != 4)
      continue;

    OTFLookupSubTable* const pSubTables =
        EA::Allocator::create_array<OTFLookupSubTable>(&mStackAllocator, pLookup->mSubTableCount);
    pLookup->mpSubTableArray = pSubTables;

    for (uint32_t j = 0; j < pLookup->mSubTableCount; ++j)
    {
      const uint32_t nSubTable = nOffset + pLookup->mOffset + pLookup->mpSubTableOffsets[j];
      mpFontStream->Seek(nSubTable, 0);

      OTFLookupSubTable* const pSubTable = &pSubTables[j];
      EA::IO::ReadUint16(mpFontStream, &pSubTable->mFormat, 1, EA::IO::kEndianBig);
      EA::IO::ReadUint16(mpFontStream, &pSubTable->mCoverageOffset, 1, EA::IO::kEndianBig);

      ReadGsubArrayEntry(nSubTable, pLookup->mLookupType, pSubTable->mFormat, *pSubTable);
    }

    for (uint32_t j = 0; j < pLookup->mSubTableCount; ++j)
    {
      OTFLookupSubTable* const pSubTable = &pSubTables[j];
      ReadCoverage(pSubTable->mCoverage,
                   nOffset + pLookup->mOffset + pSubTable->mCoverageOffset
                       + pLookup->mpSubTableOffsets[j]);
    }
  }

  return true;
}

// ---------------------------------------------------------------------------
// EA::Text::OTF::ReadGdef -- reads the GDEF table: the class definitions, the
// attach list (with its carved point-index arrays) and the (unread) ligature
// caret list header.  Returns false when the table is absent.
// ---------------------------------------------------------------------------

// @ 0x008a1350
bool EA::Text::OTF::ReadGdef()
{
  if (mGdefTableOffset != 0)
  {
  mpFontStream->Seek(mGdefTableOffset, 0);
  mpFontStream->Read(&mGdef, 0x48);

  if (mGdef.mOffsetGlyphClassDef != 0)
  {
    mGdef.mOffsetGlyphClassDef = FromBigEndian(mGdef.mOffsetGlyphClassDef);
    ReadClassDef(mGdef.mGlyphClassDef, (uint32_t)mGdef.mOffsetGlyphClassDef + mGdefTableOffset);
  }

  if (mGdef.mOffsetAttachList != 0)
  {
    mGdef.mOffsetAttachList = FromBigEndian(mGdef.mOffsetAttachList);
    mpFontStream->Seek((uint32_t)mGdef.mOffsetAttachList + mGdefTableOffset, 0);

    EA::IO::ReadUint16(mpFontStream, &mGdef.mAttachList.mCoverageOffset, 1, EA::IO::kEndianBig);
    EA::IO::ReadUint16(mpFontStream, &mGdef.mAttachList.mGlyphCount, 1, EA::IO::kEndianBig);

    uint16_t      nZero = 0;
    OTFWordVector attachGlyphs;
    attachGlyphs.Reset(mGdef.mAttachList.mGlyphCount, &nZero);
    EA::IO::ReadUint16(mpFontStream, attachGlyphs.mpBegin, mGdef.mAttachList.mGlyphCount,
                       EA::IO::kEndianBig);

    mGdef.mAttachList.mpAttachPointArray =
        EA::Allocator::create_array<OTFAttachPoint>(&mStackAllocator,
                                                    mGdef.mAttachList.mGlyphCount);

    for (uint32_t i = 0; i < mGdef.mAttachList.mGlyphCount; ++i)
    {
      OTFAttachPoint* const pPoint = &mGdef.mAttachList.mpAttachPointArray[i];

      mpFontStream->Seek((uint32_t)mGdef.mOffsetAttachList + mGdefTableOffset
                             + attachGlyphs.mpBegin[i],
                         0);
      EA::IO::ReadUint16(mpFontStream, &pPoint->mPointIndexCount, 1, EA::IO::kEndianBig);

      pPoint->mpPointIndexArray =
          EA::Allocator::create_array<uint16_t>(&mStackAllocator, pPoint->mPointIndexCount);
      EA::IO::ReadUint16(mpFontStream, pPoint->mpPointIndexArray, pPoint->mPointIndexCount,
                         EA::IO::kEndianBig);
    }

    ReadCoverage(mGdef.mAttachList.mCoverage,
                 (uint32_t)mGdef.mAttachList.mCoverageOffset
                     + (uint32_t)mGdef.mOffsetAttachList + mGdefTableOffset);

    // Release the glyph-offset scratch if Reset had to spill it out of the
    // vector's inline storage.
    if (attachGlyphs.mpBegin != attachGlyphs.mpInlineBegin)
      FreeRawBlock(attachGlyphs.mpBegin);
  }

  if (mGdef.mOffsetLigCaretList != 0)
  {
    mGdef.mLigCaretList.mCoverage.mCoverageFormat = 0;
    mGdef.mLigCaretList.mCoverage.mCount          = 0;
    mGdef.mLigCaretList.mCoverage.mpGlyphIdArray  = 0;
    mGdef.mLigCaretList.mLigatureGlyphCount       = 0;
    mGdef.mLigCaretList.mpLigatureGlyphArray      = 0;
  }

  if (mGdef.mOffsetMarkAttachClassDef != 0)
  {
    mGdef.mOffsetMarkAttachClassDef = FromBigEndian(mGdef.mOffsetMarkAttachClassDef);
    ReadClassDef(mGdef.mMarkAttachClassDef,
                 (uint32_t)mGdef.mOffsetMarkAttachClassDef + mGdefTableOffset);
  }

  return true;
  }

  return false;
}

// ---------------------------------------------------------------------------
// OTFGsubGpos::BuildFeatureLookup -- walks the requested feature/lookup pairs,
// finds each requested lookup in the lang sys's feature-index list and collects
// the sub-table references it needs.
// ---------------------------------------------------------------------------

// @ 0x008a11c0
void EA::Text::OTFGsubGpos::BuildFeatureLookup(uint32_t* pScriptTag, uint32_t* pLangSysTag,
                                               OTFFeatureLookupVector* pVector)
{
  OTFLangSys* const pLangSys = mScriptList.GetLangSys(pScriptTag, pLangSysTag, false);

  uint32_t nRemaining =
      (uint32_t)((uintptr_t)pVector->mpEnd - (uintptr_t)pVector->mpBegin) / 0x60;
  if (nRemaining == 0)
    return;

  uint32_t nReqOffset = 0;
  do
  {
    OTFFeatureLookup* const pReq =
        (OTFFeatureLookup*)((uint8_t*)pVector->mpBegin + nReqOffset);

    uint32_t nIndex = 0;
    if (pLangSys->mFeatureIndexCount != 0)
    {
      const uint16_t* pFeatureIndex = pLangSys->mpFeatureIndexArray;
      do
      {
        const OTFBuiltLookup* const pLookup =
            (OTFBuiltLookup*)((uint8_t*)mpLookupArray + (uint32_t)*pFeatureIndex * 0x10);

        if (pLookup->mLookupIndex == pReq->mLookupIndex)
        {
          // The zero-length round-trip through the trivial move helper, which
          // parks the sub-table-ref vector's end back at its begin.
          uint32_t* const pBegin = pReq->mSubTableRefs.mpBegin;
          uint32_t* const pEnd   = pReq->mSubTableRefs.mpEnd;
          memcpy(pBegin, pEnd, (size_t)((uintptr_t)pEnd - (uintptr_t)pEnd));
          pReq->mSubTableRefs.mpEnd = pEnd - (pEnd - pBegin);

          uint32_t nSub = 0;
          if (pLookup->mSubTableCount != 0)
          {
            do
            {
              uint32_t* const pSlot = pReq->mSubTableRefs.mpEnd;
              const uint32_t  nValue =
                  (uint32_t)((uintptr_t)mpSubTableBase
                             + (uint32_t)pLookup->mpSubTableIndices[nSub] * 0x10);

              if (pSlot < pReq->mSubTableRefs.mpCapacity)
              {
                pReq->mSubTableRefs.mpEnd = pSlot + 1;
                if (pSlot != 0)
                  *pSlot = nValue;
              }
              else
                pReq->mSubTableRefs.Insert(pSlot, nValue);

              ++nSub;
            } while (nSub < pLookup->mSubTableCount);
          }
          break;
        }

        ++nIndex;
        ++pFeatureIndex;
      } while (nIndex < pLangSys->mFeatureIndexCount);
    }

    nReqOffset += 0x60;
    --nRemaining;
  } while (nRemaining != 0);
}
