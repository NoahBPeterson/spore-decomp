#ifndef HEIGHTCODEC_H
#define HEIGHTCODEC_H

#include "types.h"

void* __cdecl MemSet(void* dst, int value, unsigned size);             // 0x011e073e
void  __cdecl operator_delete__(void* p);                              // 0x00f47380

extern "C" void* (__cdecl* const g_alloc_016f16ec)(unsigned size);     // 0x016f16ec  block allocator
extern "C" void  (__cdecl* const g_free_016f16f4)(void* p);            // 0x016f16f4  block release
extern "C" int   g_compactBlocks;                                      // 0x016f1734  packed-layout switch
extern "C" const unsigned short g_sizeTable[];                         // 0x014d76e8  u16 per-index sizes
extern "C" const short          g_spanTable[];                         // 0x014d7608  s16 per-block spans

// ---------------------------------------------------------------------------
// Quantised height-field block codec: a base object that decodes a packed
// descriptor word into its per-block layout and owns the int16 conversion of
// the float source, plus a derived object that owns the linked block.
// Field names are coined from the packed-descriptor usage.
// ---------------------------------------------------------------------------

struct cHeightCodec {
    virtual void Slot00();
    virtual int  ResolveId(unsigned id);          // +0x04
    virtual void Slot08();
    virtual void ReleaseSource();                 // +0x0c
    virtual void Slot10();
    virtual void OnAllocated();                   // +0x14
    virtual ~cHeightCodec();

    unsigned      mSize04;          // +0x04  divisor read back from the size table
    unsigned      mSize08;          // +0x08  same size table value
    unsigned      mField0c;         // +0x0c
    int           mBlockSize;       // +0x10  signed span from the span table
    int           mComputedSize;    // +0x14  derived block size
    unsigned char mCellDim;         // +0x18  4 - packed dimension bits
    unsigned char mPad19[0x0b];     // +0x19
    const unsigned char* mpSourceData;  // +0x24  packed id seen as four bytes
    unsigned      mSourceCopy;      // +0x28
    unsigned      mCursor;          // +0x2c
    unsigned      mCursorOffset;    // +0x30
    unsigned      mCursorExtra;     // +0x34
    unsigned char mPad38[2];        // +0x38
    unsigned char mMode3a;          // +0x3a  outer layout switch
    unsigned char mMode3b;          // +0x3b  inner layout switch
    unsigned char mMode3c;          // +0x3c
    unsigned char mPad3d;           // +0x3d
    unsigned char mBit3e;           // +0x3e  descriptor bit 0x13
    unsigned char mBit3f;           // +0x3f  descriptor bit 0x10
    unsigned char mNibble40;        // +0x40  descriptor bits 0x0c..0x0f
    unsigned char mIndex41;         // +0x41  size-table index
    unsigned char mBit42;           // +0x42  descriptor bit 0x09
    unsigned char mType43;          // +0x43  descriptor bits 0x06..0x07
    unsigned char mType44;          // +0x44  descriptor bits 0x04..0x05
    unsigned char mBit45;           // +0x45  descriptor bit 0x03
    unsigned char mBit46;           // +0x46  descriptor bit 0x02
    unsigned char mInited;          // +0x47  data allocated
    unsigned char mBlockCount;      // +0x48  1 or 2 blocks per size
    unsigned char mPad49[3];        // +0x49
    unsigned      mHandle4c;        // +0x4c  id handed to ResolveId when no pointer
    void*         mpData;           // +0x50  allocated block data

    cHeightCodec();
    void SetHandle(unsigned handle);
    int  Decode(unsigned desc);
    void AllocBlocks();
    int  Init(unsigned handle, unsigned unused);
    int  ResolveSource();
    void CopyHandle();
};

struct cHeightBlock : cHeightCodec {
    unsigned char mReserved[0x1b0 - 0x54];   // +0x54
    void*         mpLinked;                  // +0x1b0
    virtual ~cHeightBlock();
};

#endif
