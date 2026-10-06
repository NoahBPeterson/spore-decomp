// @ 0x0116c750   FUN_0116c750  (5653 bytes)
//
// Twin of FUN_01164200 (0x01164200): the same terrain-brush weight-map fill for a *second*
// brush descriptor layout.  It is byte-for-byte the same algorithm with these substituted
// member offsets and data tables (measured from the decompiles):
//
//      FUN_01164200            FUN_0116c750
//      this + 0x37 (flag3b)    this + 0x2f
//      this + 0x38 (sel byte)  this + 0x30
//      this + 0x58 + n*0x18    this + 0x70 + n*0x18
//      this + 0x134 (types)    this + 0x14c (types)
//      DAT_014d6fd0            DAT_014da570
//      DAT_014d6ff8/ffa        DAT_014da598/59a
//      DAT_014d6ff9..7000      DAT_014da599..5a0
//      DAT_014d7008/09/0a      DAT_014da5a8/09/0a
//      DAT_014d71f0            DAT_014da6d8
//      DAT_014d7230            DAT_014da718
//      FUN_01164140            FUN_0116c600
//
// Filed PARTIAL, same reasons as FUN_01164200 (inlined run expansion factored out).

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" int   FUN_0116c600();      // 0x0116c600
extern "C" float DAT_014da6d8[];      // 0x014da6d8  per-material floats
extern "C" float DAT_014da718[];      // 0x014da718  per-material floats
extern "C" short DAT_014da570[];      // 0x014da570  per-type column table
extern "C" short DAT_014da598[];
extern "C" short DAT_014da59a[];
extern "C" u8    DAT_014da59e[];
extern "C" u8    DAT_014da59f[];
extern "C" u8    DAT_014da5a0[];
extern "C" u8    DAT_014da5a8[];
extern "C" u8    DAT_014da5a9[];
extern "C" u8    DAT_014da5aa[];

enum { kCells = 0x240 };
enum { kCols  = 0x12 };

struct WeightMap {
    u32   weight[kCells];
    float s[kCells];
    float a[kCells];
    float b[kCells];
};

static inline void PutRun(WeightMap* m, int idx, unsigned type, unsigned uVar10, char flag2f)
{
    if (idx < 0 || idx >= kCells || type == 7)
        return;
    m->weight[idx] = type;
    if (flag2f == 0) {
        m->s[idx] = DAT_014da6d8[type];
    }
    else if (type == 0) {
        m->a[idx] = 1.0f;
        m->b[idx] = 1.0f;
    }
    else if ((type & 1) == 0) {
        m->a[idx] = 1.0f;
        m->b[idx] = DAT_014da718[(type >> 1) + uVar10 * 0x20];
    }
    else {
        m->b[idx] = 1.0f;
        m->a[idx] = DAT_014da718[((type + 1) >> 1) + uVar10 * 0x20];
    }
}

// @ 0x0116c750
void FUN_0116c750(int param_1, int param_2, int param_3)
{
    WeightMap map;

    char cFlag2f = *(char*)(param_1 + 0x2f);
    u8   uType   = *(u8*)(param_1 + 0x30);

    bool bVar8 = (*(char*)(param_1 + 0x37) == 1) && ((*(u8*)(param_1 + 0x38) & 1) != 0);
    bool bVar9 = (*(char*)(param_1 + 0x37) == 1) && ((*(u8*)(param_1 + 0x38) & 2) != 0);

    if (!bVar8) {
        if (bVar9)
            FUN_0116c600();
        return;
    }

    int desc = param_1 + 0x70 + param_2 * 0x18;
    unsigned uVar10 = *(u16*)(desc + 4) & 1;

    for (int i = 0; i < kCells; ++i)
        map.weight[i] = 7;

    if (*(char*)(desc + 7) == 0 || *(char*)(desc + 8) != 2) {
        // scanline branch
        int iVar13 = 0x1f, iVar17 = 0x11, iVar11 = 0, iVar20 = 0x46E;
        do {
            if (*(float*)(param_3 + (iVar20 + iVar17) * 4) != 0.0f) {
                iVar11 = iVar17 + iVar13 * 0x12;
                break;
            }
            if (--iVar17 < 0) { --iVar13; iVar20 -= 0x12; iVar17 = 0x11; }
        } while (0x23F < iVar20);

        int i17 = 0;
        if (DAT_014da570[uType * 0x1e] <= iVar11) {
            const short* p = &DAT_014da570[uType * 0x1e];
            do { ++i17; } while (*++p <= iVar11);
        }
        for (int row = i17; row < 0x15; ++row) {
            const short* band = &DAT_014da570[row + uType * 0x1e];
            (void)band;
        }
        (void)iVar11;
    }
    else {
        // mirrored-polygon branch
        u8 u16v = DAT_014da5a9[uType * 0x3c];
        u8 b4   = DAT_014da5a8[uType * 0x3c];
        (void)u16v; (void)b4;
        for (int band = 0; band < 0x3e; band += 0xd) {
        }
    }

    // blend the working map into param_3
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
            else if (cFlag2f == 0) {
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
