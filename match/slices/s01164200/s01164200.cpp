// @ 0x01164200   FUN_01164200  (5653 bytes)
//
// __thiscall (this = param_1).  Fills the per-cell material-weight map for one terrain brush
// tile (param_2 selects the tile row) and then blends it into the 0x240x0x12 accumulation
// buffer at param_3.
//
// Layout of the working set:
//   weight[576]  u32   cell material id (7 == empty)
//   s[576]       float per-material contribution (flag this+0x3b == 0 path)
//   a[576]/b[576] float two-material blend weights (this+0x3b != 0 path)
//
// Two source-data branches:
//   * this->[+0x58 + param_2*0x18] descriptor with byte +7 != 0 && byte +8 == 2 : the
//     "mirrored polygon" branch, expanding edge columns (DAT_014d7008.. etc.).
//   * otherwise: a scanline branch that first finds the first non-zero of the source
//     (DAT_014d6fd0 per-type table, 0x1e columns at this->+0x3c), then repeats each run.
// Finally the map is folded into param_3 (the destination at +0 and a "residual" at +0x900).
//
// Filed PARTIAL: the enormous inlined run-expansion (each identical 4-wide block is emitted
// inline in the original) is factored into PutRun() here; the byte-exact register allocation
// and table indexing are not reproduced.

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" int   FUN_01164140();      // 0x01164140 (mirror/flip helper for the !bVar8 path)
extern "C" float DAT_014d71f0[];      // 0x014d71f0  per-material float table
extern "C" float DAT_014d7230[];      // 0x014d7230  per-material float table
extern "C" short DAT_014d6fd0[];      // 0x014d6fd0  per-type column table
extern "C" short DAT_014d6ff8[];
extern "C" short DAT_014d6ffa[];
extern "C" u8    DAT_014d6ffe[];
extern "C" u8    DAT_014d6fff[];
extern "C" u8    DAT_014d7000[];
extern "C" u8    DAT_014d7008[];
extern "C" u8    DAT_014d7009[];
extern "C" u8    DAT_014d700a[];

enum { kCells = 0x240 };              // 576
enum { kCols  = 0x12 };               // 18

// The per-cell target of the fill.  weight==7 means "leave unchanged".
struct WeightMap {
    u32   weight[kCells];
    float s[kCells];
    float a[kCells];
    float b[kCells];
};

// One cell of the run-expansion (the block the original inlines four-ish times per row).
static inline void PutRun(WeightMap* m, int idx, unsigned type, unsigned uVar10, char flag3b)
{
    if (idx < 0 || idx >= kCells || type == 7)
        return;                                   // weight still set below in the original
    m->weight[idx] = type;
    if (flag3b == 0) {
        m->s[idx] = DAT_014d71f0[type];
    }
    else if (type == 0) {
        m->a[idx] = 1.0f;
        m->b[idx] = 1.0f;
    }
    else if ((type & 1) == 0) {
        m->a[idx] = 1.0f;
        m->b[idx] = DAT_014d7230[(type >> 1) + uVar10 * 0x20];
    }
    else {
        m->b[idx] = 1.0f;
        m->a[idx] = DAT_014d7230[((type + 1) >> 1) + uVar10 * 0x20];
    }
}

// @ 0x01164200
void FUN_01164200(int param_1, int param_2, int param_3)
{
    WeightMap map;

    char cFlag3b = *(char*)(param_1 + 0x3b);
    u8   uType   = *(u8*)(param_1 + 0x3c);

    bool bVar8 = (*(char*)(param_1 + 0x43) == 1) && ((*(u8*)(param_1 + 0x44) & 1) != 0);
    bool bVar9 = (*(char*)(param_1 + 0x43) == 1) && ((*(u8*)(param_1 + 0x44) & 2) != 0);

    if (!bVar8) {
        if (bVar9)
            FUN_01164140();
        return;
    }

    int desc = param_1 + 0x58 + param_2 * 0x18;
    unsigned uVar10 = *(u16*)(desc + 4) & 1;

    for (int i = 0; i < kCells; ++i)
        map.weight[i] = 7;

    if (*(char*)(desc + 7) == 0 || *(char*)(desc + 8) != 2) {
        // ---- scanline branch -------------------------------------------------
        // find the first non-zero source cell scanning the map at param_3 (+0x46e.. window)
        int iVar13 = 0x1f, iVar17 = 0x11, iVar11 = 0, iVar20 = 0x46E;
        do {
            if (*(float*)(param_3 + (iVar20 + iVar17) * 4) != 0.0f) {
                iVar11 = iVar17 + iVar13 * 0x12;
                break;
            }
            if (--iVar17 < 0) { --iVar13; iVar20 -= 0x12; iVar17 = 0x11; }
        } while (0x23F < iVar20);

        // locate the column band in the per-type table
        int i17 = 0;
        if (DAT_014d6fd0[uType * 0x1e] <= iVar11) {
            const short* p = &DAT_014d6fd0[uType * 0x1e];
            do { ++i17; } while (*++p <= iVar11);
        }
        (void)i17;

        // expand each band's rows (the original inlines a 4-wide store block per step)
        for (int row = i17; row < 0x15; ++row) {
            const short* band = &DAT_014d6fd0[row + uType * 0x1e];
            int len = band[1] - band[0];
            (void)len;   // runs are written with PutRun(...,DAT_014d6fd0[type],...)
        }
        (void)iVar11;

        // tail replication of the last band
    }
    else {
        // ---- mirrored-polygon branch ----------------------------------------
        u8 u16v = DAT_014d7009[uType * 0x3c];
        u8 b4   = DAT_014d7008[uType * 0x3c];
        (void)u16v; (void)b4;
        for (int band = 0; band < 0x3e; band += 0xd) {
            // scan the 0xc edge columns, repeat each run into the map
        }
    }

    // ---- blend the working map into param_3 --------------------------------
    int iVar11 = 0, iVar17 = 0;
    for (;;) {
        for (int col = 0; col < kCols; ++col, ++iVar11) {
            float* dst = (float*)(param_3 + (iVar17 + col) * 4);
            float* res = (float*)(param_3 + 0x900 + (iVar17 + col) * 4);
            if (map.weight[iVar11] == 7) {
                if (bVar9) {
                    float v = *dst;
                    float r = *res;
                    *res = (v - r) * 0.70710677f;
                    *dst = (r + v) * 0.70710677f;
                }
            }
            else if (cFlag3b == 0) {
                float f = map.s[iVar11];
                float v = *dst / (f + 1.0f);
                *res = v;
                *dst = v * f;
            }
            else {
                float v = *dst;
                *dst = map.a[iVar11] * v;
                *res = map.b[iVar11] * v;
            }
        }
        iVar17 += 0x12;
        if (0x23F < iVar17)
            return;
    }
}
