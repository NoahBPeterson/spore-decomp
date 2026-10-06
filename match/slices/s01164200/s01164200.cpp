// @ 0x01164200   TerrainBrushWeightMapFill  (5653 bytes)
//
// __thiscall, ret 8.  Fills the per-cell material-weight map for one terrain brush tile
// (tileIndex selects the 0x18-byte tile descriptor at this+0x58) and folds it into the
// destination buffer `dst`, which holds two 32x18 float planes (dst[0..575] and the
// "residual" plane dst[576..1151], i.e. +0x900 bytes).
//
// The original's 4-wide store blocks are cl's own unrolling of the simple per-cell loops
// below (pattern `((n-4)>>2)+1`), so the source is written as plain loops over two inline
// helpers (SetCell / CopyCell). SetCell reads this->twoMaterial per cell like the original;
// __forceinline keeps cl from outlining it (the original inlines it at all four sites).

#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

enum { kCells = 0x240 };   // 32 rows x 18 columns
enum { kCols  = 0x12 };
enum { kEmpty = 7 };       // material id meaning "leave the cell unchanged"

// 0x3c-byte per-brush-type layout table at 0x014d6fd0.
//   bands[0..21]  : start cell of each of the 21 scanline bands (bands[21] = end)
//   bands[20]     : the cell replicated into the tail; bands[21] the tail start
//   cols[0..13]   : column-band boundaries used by the 3-row "polygon" layout; band i
//                   covers cells cols[i]*3 .. cols[i+1]*3 (3 rows of width cols[i+1]-cols[i])
struct BrushTypeLayout {
    short bands[23];     // +0x00
    u8    cols[14];      // +0x2e
};
extern "C" BrushTypeLayout DAT_014d6fd0[];   // 0x014d6fd0
extern "C" float DAT_014d71f0[];             // 0x014d71f0 per-material single weight
extern "C" float DAT_014d7230[];             // 0x014d7230 [2][32] two-material blend weights

// 0x01164140: in-place 45-degree rotation of the two planes (custom register convention:
// the buffer comes in EAX; declared as a plain function here).
void FUN_01164140(float* dst);

struct BrushTile {               // 0x18 bytes at this+0x58
    char  pad0[4];
    u16   flags;                 // +0x04, bit 0 selects the DAT_014d7230 half
    char  pad6;
    char  hasPolygon;            // +0x07
    char  layoutKind;            // +0x08, 2 = polygon layout
    char  polygonAlt;            // +0x09
    char  pad0a[0x18 - 0x0a];
};

struct WeightMap {
    float a[kCells];             // two-material weight on the dst plane
    float b[kCells];             // two-material weight on the residual plane
    u32   weight[kCells];        // material id per cell, kEmpty = untouched
    float s[kCells];             // single-material contribution
};

class TerrainBrush {
public:
    char      pad0[0x3b];
    char      twoMaterial;       // +0x3b
    u8        brushType;         // +0x3c
    char      pad3d[0x43 - 0x3d];
    char      mode;              // +0x43
    u8        modeFlags;         // +0x44
    char      pad45[0x58 - 0x45];
    BrushTile tiles[10];         // +0x58
    short     materials[1];      // +0x134 (indexed by band / row*13+column-band)

    void FillWeightMap(int tileIndex, float* dst);
    void SetCell(WeightMap& m, int idx, u32 type, u32 half);
};

__forceinline void TerrainBrush::SetCell(WeightMap& m, int idx, u32 type, u32 half)
{
    m.weight[idx] = type;
    if (type != kEmpty) {
        if (twoMaterial == 0) {
            m.s[idx] = DAT_014d71f0[type];
        }
        else if (type == 0) {
            m.a[idx] = 1.0f;
            m.b[idx] = 1.0f;
        }
        else if ((type & 1) == 0) {
            m.a[idx] = 1.0f;
            m.b[idx] = DAT_014d7230[(type >> 1) + half * 0x20];
        }
        else {
            m.b[idx] = 1.0f;
            m.a[idx] = DAT_014d7230[((type + 1) >> 1) + half * 0x20];
        }
    }
}

static inline void CopyCell(WeightMap& m, int dstIdx, int srcIdx, char twoMaterial)
{
    m.weight[dstIdx] = m.weight[srcIdx];
    if (twoMaterial == 0) {
        m.s[dstIdx] = m.s[srcIdx];
    }
    else {
        m.a[dstIdx] = m.a[srcIdx];
        m.b[dstIdx] = m.b[srcIdx];
    }
}

// @ 0x01164200
void TerrainBrush::FillWeightMap(int tileIndex, float* dst)
{
    bool fill   = (mode == 1 && (modeFlags & 1) != 0) ? true : false;
    bool rotate = (mode == 1 && (modeFlags & 2) != 0) ? true : false;

    if (!fill) {
        if (rotate)
            FUN_01164140(dst);
        return;
    }

    BrushTile* tile = &tiles[tileIndex];
    u32 half = tile->flags & 1;
    float* res = dst + kCells;

    WeightMap m;
    for (int i = 0; i < kCells; ++i)
        m.weight[i] = kEmpty;

    if (tile->hasPolygon != 0 && tile->layoutKind == 2) {
        // ---- 3-row polygon layout: 13 column bands per row ------------------------
        const BrushTypeLayout& L = DAT_014d6fd0[brushType];
        int row = 0;
        if (tile->polygonAlt == 0) {
            const BrushTypeLayout& T = DAT_014d6fd0[brushType];
            u32 c10 = T.cols[10];
            u32 c11 = T.cols[11];
            int tailLen = T.cols[12] - c11;
            for (int base = 0x17; base < 0x3e; base += 0xd, ++row) {
                // last column band (from the right) whose residual is non-zero in this row
                int last = -1;
                for (int i = 12; i >= 0; --i) {
                    int w = L.cols[i + 1] - L.cols[i];
                    const float* p = &res[(row + 1) * w - 1 + L.cols[i] * 3];
                    for (int j = w; j > 0; --j, --p) {
                        if (*p != 0.0f) {
                            last = i;
                            i = -10;
                            j = -10;
                        }
                    }
                }
                for (int k = last + 1; k < 12; ++k) {
                    const u8* c = &DAT_014d6fd0[brushType].cols[k];
                    int w = c[1] - c[0];
                    int idx = row * w + c[0] * 3;
                    for (int j = 0; j < w; ++j)
                        SetCell(m, idx++, materials[base + k], half);
                }
                int to   = row * tailLen + c11 * 3;
                int from = (c11 - c10) * row + c10 * 3;
                for (int j = 0; j < tailLen; ++j)
                    CopyCell(m, to++, from, twoMaterial);
            }
        }
        else {
            const BrushTypeLayout& T = DAT_014d6fd0[brushType];
            u32 c10 = T.cols[10];
            u32 c11 = T.cols[11];
            u32 c12 = T.cols[12];
            int maxStart = 0;
            for (int base = 0x17; base < 0x3e; base += 0xd, ++row) {
                int last = 2;
                for (int i = 12; i > 2; --i) {
                    int w = L.cols[i + 1] - L.cols[i];
                    const float* p = &res[(row + 1) * w - 1 + L.cols[i] * 3];
                    for (int j = w; j > 0; --j, --p) {
                        if (*p != 0.0f) {
                            last = i;
                            i = -10;
                            j = -10;
                        }
                    }
                }
                int start = last + 1;
                if (maxStart < start)
                    maxStart = start;
                for (int k = start; k < 12; ++k) {
                    const u8* c = &DAT_014d6fd0[brushType].cols[k];
                    int w = c[1] - c[0];
                    int idx = w * row + c[0] * 3;
                    for (int j = 0; j < w; ++j)
                        SetCell(m, idx++, materials[base + k], half);
                }
                int tailLen = c12 - c11;
                int from = (c11 - c10) * row + c10 * 3;
                int to   = tailLen * row + c11 * 3;
                for (int j = 0; j < tailLen; ++j)
                    CopyCell(m, to++, from, twoMaterial);
            }
            if (maxStart < 4) {
                // nothing reached the first column bands: fill scanline bands 0..7 after the
                // last non-zero residual cell of rows 0..2
                int lastCell = -1;
                for (int r = 2; r >= 0; --r) {
                    for (int c = kCols - 1; c >= 0; --c) {
                        if (res[r * kCols + c] != 0.0f) {
                            lastCell = c + r * kCols;
                            goto found3;
                        }
                    }
                }
            found3:
                const BrushTypeLayout& S = DAT_014d6fd0[brushType];
                int band = 0;
                while (S.bands[band] <= lastCell)
                    ++band;
                int idx = S.bands[band];
                for (; band < 8; ++band) {
                    const short* b = &DAT_014d6fd0[brushType].bands[band];
                    int len = b[1] - b[0];
                    for (int j = 0; j < len; ++j)
                        SetCell(m, idx++, materials[band], half);
                }
            }
        }
    }
    else {
        // ---- scanline layout: 21 bands over the whole 32x18 tile -----------------------
        int lastCell = 0;
        for (int r = 31; r >= 0; --r) {
            for (int c = kCols - 1; c >= 0; --c) {
                if (res[r * kCols + c] != 0.0f) {
                    lastCell = c + r * kCols;
                    goto found;
                }
            }
        }
    found:
        const BrushTypeLayout& S = DAT_014d6fd0[brushType];
        int band = 0;
        while (S.bands[band] <= lastCell)
            ++band;
        int idx = S.bands[band];
        for (; band < 0x15; ++band) {
            const short* b = &DAT_014d6fd0[brushType].bands[band];
            int len = b[1] - b[0];
            for (int j = 0; j < len; ++j)
                SetCell(m, idx++, materials[band], half);
        }
        // replicate the type's tail cell over the rest of the tile
        int from = DAT_014d6fd0[brushType].bands[20];
        for (int n = kCells - DAT_014d6fd0[brushType].bands[21]; n > 0; --n, ++idx) {
            if (idx >= kCells)
                break;
            CopyCell(m, idx, from, twoMaterial);
        }
    }

    // ---- fold the working map into dst -------------------------------------------------
    int cell = 0;
    for (int r = 0; r < kCells; r += kCols) {
        for (int c = 0; c < kCols; ++c, ++cell) {
            float* d = &dst[r + c];
            if (m.weight[cell] == kEmpty) {
                if (rotate) {
                    float v = *d;
                    float w = res[r + c];
                    res[r + c] = (v - w) * 0.70710677f;
                    *d = (w + v) * 0.70710677f;
                }
            }
            else if (twoMaterial == 0) {
                float f = m.s[cell];
                float v = *d / (f + 1.0f);
                res[r + c] = v;
                *d = v * f;
            }
            else {
                float v = *d;
                *d = m.a[cell] * v;
                res[r + c] = m.b[cell] * v;
            }
        }
    }
}
