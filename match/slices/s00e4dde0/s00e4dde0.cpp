// Slice s00e4dde0: SP:: helper @ 0x00e4dde0 (269 bytes).
//
// Bins point pairs into a 20 x 15 grid: for every source point it floors the
// two world coordinates into a cell, then appends {a, b, weight, index} to
// that cell's list (at most 8 per cell).  The cell counters sit at the front
// of the block and are cleared first, so the block is uploaded to the GPU /
// sent over as one buffer.
//
// The original is a TU-local static helper: the source-point array arrives in
// EAX, the block pointer in EBX, the remaining three arguments on the stack.
// The stand-in caller at the bottom of the file keeps the block pointer in a
// callee-saved register so cl hands the helper the same registers.
//
// Two source choices decide the bytes (check.py 2026-11-17):
//  - the entry address is formed from the stored count BEFORE the counter is
//    incremented (`lea eax,[esi+ecx*8]; shl; lea`), so `n` stays in ESI for
//    the `inc esi; mov [ebx+ecx*4],esi` store; storing the counter first makes
//    cl materialise `n+1` in a second register and costs 2 bytes (271 vs 269)
//    and a different whole-function register assignment (EDI/EBX swapped);
//  - the caller in the same TU is what gives the static helper its register
//    arguments at all (docs/codegen.md 6.3).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include "sse_helpers.h"

extern "C" {
  void* __cdecl FUN_00e11e073e(void*, int, unsigned);  // 0x011e073e (memset-like)
}

extern float g_16b3c88;  // 0x016b3c88  grid origin x
extern float g_16b3c8c;  // 0x016b3c8c  grid origin y
extern float g_15a7b9c;  // 0x015a7b9c  1 / cell width
extern float g_15a7ba0;  // 0x015a7ba0  1 / cell height

struct PlacementVec3 { float x, y, z; };

// One grid entry: the segment's two endpoints, its weight and its source index.
struct PlacementEntry {
  PlacementVec3 mA;       // 0x00
  PlacementVec3 mB;       // 0x0c
  float         mfWeight; // 0x18
  int           mnIndex;  // 0x1c
};

enum { kCols = 20, kRows = 15, kPerCell = 8, kCells = kCols * kRows };

// Counter block plus the per-cell arrays, 0x4b0 bytes of counters up front.
struct PlacementGrid {
  int            mnCount[kCells];              // 0x000
  PlacementEntry maEntries[kCells * kPerCell]; // 0x4b0
};

// @ 0x00e4dde0
static __declspec(noinline) void PlacementBuildCells(
    const PlacementVec3* pA, PlacementGrid* pGrid,
    const PlacementVec3* pB, const float* pWeight, int nCount) {
  FUN_00e11e073e(pGrid->mnCount, 0, sizeof(pGrid->mnCount));
  for (int i = 0; i < nCount; ++i) {
    float fx = (pA[i].x - g_16b3c88) * g_15a7b9c;
    int nX = SseFloorToInt(fx);
    float fy = (pA[i].y - g_16b3c8c) * g_15a7ba0;
    int nY = SseFloorToInt(fy);
    if ((unsigned)nX > (unsigned)(kCols - 1) || (unsigned)nY > (unsigned)(kRows - 1))
      continue;
    int nCell = nY * kCols + nX;
    if (nCell == -1)
      continue;
    int n = pGrid->mnCount[nCell];
    if (n >= kPerCell)
      continue;
    PlacementEntry* pEntry = &pGrid->maEntries[nCell * kPerCell + n];
    pGrid->mnCount[nCell] = n + 1;
    pEntry->mA = pA[i];
    pEntry->mB = pB[i];
    pEntry->mfWeight = pWeight[i];
    pEntry->mnIndex = i;
  }
}

// Stand-in caller only (retail calls this once from 0x00e4ec02, where the point
// array sits in EAX and the grid block in EBX): cl emits the helper with those
// register arguments because this TU calls it (`__declspec(noinline)` keeps it
// out of line).  The trailing store keeps the grid pointer live across the call,
// the shape the retail caller has.
void PlacementBuildCellsCaller(PlacementGrid* pGrid, const PlacementVec3* pA,
                               const PlacementVec3* pB, const float* pWeight,
                               int nCount) {
  PlacementBuildCells(pA, pGrid, pB, pWeight, nCount);
  pGrid->mnCount[0] = 0;
}
