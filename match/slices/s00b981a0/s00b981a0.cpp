// Slice s00b981a0: cSpotGrid::FinishRegions (0x00b983b0, 2122 bytes).
// Flags: /O2 /MD /Gy /TP /GS-.
// The planet "spot" grid (static object at 0x156c060, see s00ba0770) is a 6-face cube of mnSize x mnSize
// cells (12 bytes each: region pointer +0, border flag byte +4). After the flood fill every region is a
// rectangle of cells; this pass (1) sorts the regions by area (largest first), (2) grows every live region
// into neighbouring regions that lie completely inside its row/column span and have uniform thickness,
// (3) re-points the absorbed cells at the grown region (and marks the absorbed regions dead), (4) recomputes
// the region's border flags (OR of the flag bytes of the cells around it) and its area, and finally
// (5) drops the dead regions from the list and re-sorts it by area.
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

struct cRegion {               // size 0x18
    u8    mbDone;              // +0x00 (0 = dead / not a region any more)
    char  mFace;               // +0x01
    short mRowMin;             // +0x02
    short mRowMax;             // +0x04
    short mColMin;             // +0x06
    short mColMax;             // +0x08
    short pad0a;
    int   mArea;               // +0x0c
    u8    mSide[4];            // +0x10 flags OR'ed from the cells left / above / right / below
    u8    mbAnySide;           // +0x14
    u8    pad15[3];
};
struct cCell { cRegion* mpRegion; u8 mFlag; u8 pad05[3]; u32 pad08; };   // size 0xc

int __cdecl WrapCubeFace(int size, int* face, int* col, int* row, int a, int b);   // 0x684ca0

typedef char (__cdecl* RegionPred)(const cRegion*, const cRegion*);
void __cdecl SortRegions(cRegion** first, cRegion** last, RegionPred pred);        // 0xbbf6c0
void __cdecl introsort(cRegion** first, cRegion** last, int depth, RegionPred pred);   // 0xd53940
void __cdecl insertion_sort(cRegion** first, cRegion** last, RegionPred pred);     // 0xb909f0

// larger regions first: return b->mArea < a->mArea;  (inlined at the one place the pointer is also called)
char __cdecl RegionLess(const cRegion* a, const cRegion* b);   // 0xb90730

struct cSpotGrid {
    u32 pad00[2];
    cRegion** mpRegionBegin;    // +0x08
    cRegion** mpRegionEnd;      // +0x0c
    u32 pad10[5];
    int mnSize;                 // +0x24
    u32 pad28[3];
    cCell* mpCells;             // +0x34

    void FinishRegions();                                                  // 0xb983b0

    __forceinline cCell& CellAt(int face, int row, int col)
    {
        int f = face, r = row, c = col;
        while (WrapCubeFace(mnSize, &f, &c, &r, 0, 0))
            ;
        return mpCells[(f * mnSize + r) * mnSize + c];
    }
};

// @ 0x00b983b0
void cSpotGrid::FinishRegions()
{
    SortRegions(mpRegionBegin, mpRegionEnd, (RegionPred)RegionLess);

    cRegion** const listEnd = mpRegionEnd;
    for (cRegion** it = mpRegionBegin; it != listEnd; ++it) {
        cRegion* region = *it;
        if (region->mbDone == 0)
            continue;

        const int face = region->mFace;
        int rowMin = region->mRowMin;
        int rowMax = region->mRowMax;
        int colMin = region->mColMin;
        int colMax = region->mColMax;
        bool growLeft = true, growRight = true, growUp = true, growDown = true;
        do {
            // grow the column span: scan the cells left of / right of every row
            int thickLeft = 0, thickRight = 0, thickUp = 0, thickDown = 0;
            int row = rowMin;
            while (growLeft || growRight) {
                if (row > rowMax) {
                    if (growLeft) colMin -= thickLeft;
                    if (growRight) colMax += thickRight;
                    break;
                }
                cRegion* left = CellAt(face, row, colMin - 1).mpRegion;
                cRegion* right = CellAt(face, row, colMax + 1).mpRegion;
                bool okLeft = left && left->mbDone && left->mRowMin >= rowMin && left->mRowMax <= rowMax
                    && (thickLeft == 0 || left->mColMax - left->mColMin + 1 == thickLeft);
                growLeft = growLeft & okLeft;
                if (growLeft && thickLeft == 0)
                    thickLeft = left->mColMax - left->mColMin + 1;
                bool okRight = right && right->mbDone && right->mRowMin >= rowMin && right->mRowMax <= rowMax
                    && (thickRight == 0 || right->mColMax - right->mColMin + 1 == thickRight);
                growRight = growRight & okRight;
                if (growRight && thickRight == 0)
                    thickRight = right->mColMax - right->mColMin + 1;
                row++;
            }
            // grow the row span: scan the cells above / below every column
            int col = colMin;
            while (growUp || growDown) {
                if (col > colMax) {
                    if (growUp) rowMin -= thickUp;
                    if (growDown) rowMax += thickDown;
                    break;
                }
                cRegion* up = CellAt(face, rowMin - 1, col).mpRegion;
                cRegion* down = CellAt(face, rowMax + 1, col).mpRegion;
                bool okUp = up && up->mbDone && up->mColMin >= colMin && up->mColMax <= colMax
                    && (thickUp == 0 || up->mRowMax - up->mRowMin + 1 == thickUp);
                growUp = growUp & okUp;
                if (growUp && thickUp == 0)
                    thickUp = up->mRowMax - up->mRowMin + 1;
                bool okDown = down && down->mbDone && down->mColMin >= colMin && down->mColMax <= colMax
                    && (thickDown == 0 || down->mRowMax - down->mRowMin + 1 == thickDown);
                growDown = growDown & okDown;
                if (growDown && thickDown == 0)
                    thickDown = down->mRowMax - down->mRowMin + 1;
                col++;
            }
        } while (growLeft || growRight || growUp || growDown);

        region->mColMin = (short)colMin;
        region->mRowMin = (short)rowMin;
        region->mRowMax = (short)rowMax;
        region->mColMax = (short)colMax;

        // take over every cell of the grown rectangle
        for (int r = rowMin; r <= rowMax; r++) {
            for (int c = colMin; c <= colMax; c++) {
                cRegion* other = CellAt(face, r, c).mpRegion;
                if (other && other != region) {
                    other->mbDone = 0;
                    CellAt(face, r, c).mpRegion = region;
                }
            }
        }

        // border flags
        region->mSide[0] = 0;
        region->mSide[1] = 0;
        region->mSide[2] = 0;
        region->mSide[3] = 0;
        region->mbAnySide = 0;
        const int leftCol = colMin - 1;
        const int rightCol = colMax + 1;
        int r;
        for (r = rowMin; r <= rowMax; r++) {
            region->mSide[0] |= CellAt(face, r, leftCol).mFlag;
            region->mSide[2] |= CellAt(face, r, rightCol).mFlag;
        }
        int c;
        for (c = colMin; c <= colMax; c++) {
            region->mSide[1] |= CellAt(face, rowMin - 1, c).mFlag;
            region->mSide[3] |= CellAt(face, rowMax + 1, c).mFlag;
        }
        region->mbAnySide = region->mSide[3] | region->mSide[2] | region->mSide[1] | region->mSide[0];
        region->mArea = (colMax - colMin + 1) * (rowMax - rowMin + 1);
    }

    // drop the dead regions (remove_if + erase), then sort again
    cRegion** const first = mpRegionBegin;
    cRegion** const last = mpRegionEnd;
    cRegion** dst = first;
    while (dst != last && (*dst)->mbDone != 0)
        ++dst;
    if (dst != last) {
        for (cRegion** src = dst + 1; src != last; ++src) {
            if ((*src)->mbDone != 0) {
                *dst = *src;
                ++dst;
            }
        }
    }
    memcpy(dst, last, (mpRegionEnd - last) * sizeof(cRegion*));
    mpRegionEnd -= (last - dst);

    cRegion** const sfirst = mpRegionBegin;
    cRegion** const slast = mpRegionEnd;
    if (sfirst != slast) {
        int n = (int)(slast - sfirst);
        int lg = 0;
        for (int m = n; m != 0; m >>= 1)
            lg++;
        introsort(sfirst, slast, lg * 2 - 2, (RegionPred)RegionLess);
        if (n > 28) {
            cRegion** const mid = sfirst + 28;
            insertion_sort(sfirst, mid, (RegionPred)RegionLess);
            for (cRegion** p = mid; p != slast; ++p) {
                cRegion* val = *p;
                cRegion** q = p;
                while (q[-1]->mArea < val->mArea) {
                    *q = q[-1];
                    --q;
                }
                *q = val;
            }
        } else {
            insertion_sort(sfirst, slast, (RegionPred)RegionLess);
        }
    }
}
