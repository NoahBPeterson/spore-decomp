// Declarations for slice s008c6e80 (the T2K / TSI scan-line image reader).
// Callees are external (relocated) in the original.
#pragma once
#include "types.h"

// The allocator object is passed as the first argument of the TSI allocator calls.
typedef void* tsiAlloc;
struct T2KReader;
void tsi_DeAllocMem(tsiAlloc a, void* p);           // 0x008D1440
void tsi_Error(void* ctx, int code);                // 0x008D10C0
int  ReadInt32(T2KReader* in);                      // 0x008CC0F0
void PrimeT2KInputStream();                         // 0x008CC0B0

// One decoded scan node: two ints (the outline pass reads them as a pair).
struct T2KNode {
    int x;                                          // 0x000 (halved for the bbox)
    int y;                                          // 0x004
    T2KNode* mpNext;                                // 0x008
};

// The per-column outline bounds record filled by ComputeOutlineBBox.
struct T2KOutline {
    uint32_t pad_00[0x40/4];                        // 0x000..0x040
    int      a_40;                                  // 0x040
    int      b_44;                                  // 0x044
    int      c_48;                                  // 0x048
    int      d_4c;                                  // 0x04c
};

extern T2KOutline* gOutlineOut;                     // ebx in ComputeOutlineBBox
extern int*        gOutlineRows;                    // param_1 reload

// The T2K reader.  The retail members are reached by their offsets; the node table is either
// the inline array at +0x217c or a separately allocated block at +0x21fc.
struct T2KReader {
    uint32_t  pad_000[0x214/4];                     // 0x000..0x214
    uint32_t  ringCapacity;                         // 0x214
    uint32_t  ringStart;                            // 0x218
    uint32_t  readCursor;                           // 0x21c
    uint32_t  pad_220[3];                           // 0x220..0x22c
    int       mpErrorContext;                       // 0x22c
    uint8_t   pad_230[0x217c - 0x230];              // 0x230..0x217c
    T2KNode*  m_inlineNodes[0x20];                  // 0x217c inline node table (32 entries)
    T2KNode** mppNodes;                             // 0x21fc node table pointer
    int       mnNodeCount2;                         // 0x2200
    int       mnNodeCount;                          // 0x2204
    uint8_t   pad_2208[0x2234 - 0x2208];            // 0x2208..0x2234
    tsiAlloc  mpAllocator;                          // 0x2234

    void FreeAllNodes();                            // 0x008C7960
    void AllocFreeNodes(int count);                 // 0x008C77D0
    void ComputeScanBBox();                         // 0x008C79C0
};

void __fastcall ComputeOutlineBBox(int* rows, int pass);    // 0x008C7BE0
void FUN_008c75f0();                                        // 0x008C75F0
void FUN_008c6e80();                                        // 0x008C6E80
