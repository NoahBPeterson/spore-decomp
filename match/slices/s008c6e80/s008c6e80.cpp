// Slice s008c6e80: the T2K (TSI) scan-line image reader and its scan/outline bbox helpers.
// Targets: 008c6e80 FUN_008c6e80          T2K input-stream / node reader
//          008c75f0 FUN_008c75f0          scan-line bitmap decoder helper
//          008c77d0 AllocFreeNodes        grow + allocate the node free/used tables
//          008c7960 FreeAllNodes          release every node and the node table
//          008c79c0 ComputeScanBBox       scan-line bounding box
//          008c7be0 ComputeOutlineBBox    outline (per-column min/max) bounding box
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "s008c6e80.h"

// ===========================================================================
// 0x008c7960  FreeAllNodes: release every node (index 1..count) and the node table
// ===========================================================================
// @ 0x008c7960
void T2KReader::FreeAllNodes()
{
    for (int i = 1; i <= mnNodeCount; ++i) {
        tsi_DeAllocMem(mpAllocator, mppNodes[i]);
    }
    if (mppNodes != m_inlineNodes) {
        tsi_DeAllocMem(mpAllocator, mppNodes);
    }
    mnNodeCount2 = 0;
}

// ===========================================================================
// 0x008c7be0  ComputeOutlineBBox: per-row min/max over two passes
//   eax  = int* row table (column 0 = seed), ebx = output record
// ===========================================================================
// @ 0x008c7be0
void __fastcall ComputeOutlineBBox(int* rows, int pass)
{
    T2KOutline* out = gOutlineOut;
    for (int which = 0; which < 2; ++which) {
        int seed = *rows;
        int lo = seed;
        int hi = seed;
        for (int i = 1; i <= pass; ++i) {
            int v = rows[i];
            if (v > hi) {
                hi = v;
            } else if (v < lo) {
                lo = v;
            }
        }
        if (which == 0) {
            out->a_40 = lo;
            out->b_44 = hi;
            rows = gOutlineRows;
        } else {
            out->c_48 = lo;
            out->d_4c = hi;
        }
    }
}

// ===========================================================================
// 0x008c77d0  AllocFreeNodes
// ===========================================================================
// @ 0x008c77d0
void T2KReader::AllocFreeNodes(int count)
{
    (void)count;
}

// ===========================================================================
// 0x008c79c0  ComputeScanBBox
// ===========================================================================
// @ 0x008c79c0
void T2KReader::ComputeScanBBox()
{
}

// ===========================================================================
// 0x008c75f0  FUN_008c75f0
// ===========================================================================
// @ 0x008c75f0
void FUN_008c75f0()
{
}

// ===========================================================================
// 0x008c6e80  FUN_008c6e80  (T2K input-stream / node reader)
// ===========================================================================
// @ 0x008c6e80
void FUN_008c6e80()
{
}
