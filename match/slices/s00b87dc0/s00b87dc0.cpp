// Slice s00b87dc0: SP::cPlanetModel continent labelling (flood-fill of the land/water bitmap of the
// six 128x128 cube-map faces with a union-find over uint16 labels, MMX height comparison).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <xmmintrin.h>
#include "types.h"

void __cdecl operator_delete__(void* p);   // 0x00f47380
void* __cdecl MemMove(void* dst, const void* src, unsigned int n);   // 0x011e0744 (memcpy thunk)

namespace SP {

int __cdecl WrapCubeFace(int n, int* face, int* x, int* y, int* dx, int* dy);   // 0x00684ca0
uint16_t __cdecl FloatToHeight16(float v);                                       // 0x00b7e680

// vector<uint16_t> that backs the union-find parent array.
struct UnionFind {
  uint16_t* mpBegin;
  uint16_t* mpEnd;
  uint16_t* mpCapacity;
  UnionFind() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~UnionFind()
  {
    if (mpBegin && ((int*)mpBegin)[-1] != 0)
      operator_delete__(mpBegin);
  }
  void reserve(unsigned int n);                       // 0x00b849e0, ret 4
  uint16_t Union(uint32_t a, uint32_t b);             // 0x00b7e6f0, ret 8
  int Flatten(int limit, uint32_t seed);              // 0x00b7e790, ret 8
};

// vector<bool> stored one byte per element.
struct ByteVector {
  uint8_t* mpBegin;
  uint8_t* mpEnd;
  uint8_t* mpCapacity;
  void DoInsertValues(uint8_t* pos, unsigned int n, const uint8_t* value);   // 0x005151b0, ret 0xc
  __forceinline void resize(unsigned int n)
  {
    const unsigned int sz = (unsigned int)(mpEnd - mpBegin);
    if (n > sz) {
      uint8_t fill = 0;
      DoInsertValues(mpEnd, n - sz, &fill);
    } else {
      uint8_t* first = mpBegin + n;
      uint8_t* last = mpEnd;
      MemMove(first, last, (unsigned int)(mpEnd - last));
      mpEnd = mpEnd + (first - last);
    }
  }
};

// vector<uint32_t>.
struct UIntVector {
  uint32_t* mpBegin;
  uint32_t* mpEnd;
  uint32_t* mpCapacity;
  void DoInsertValues(uint32_t* pos, unsigned int n, const uint32_t* value);   // 0x004cea40, ret 0xc
  __forceinline void clear()
  {
    uint32_t* first = mpBegin;
    uint32_t* last = mpEnd;
    MemMove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
    mpEnd = (uint32_t*)((char*)mpEnd + (first - last) * 4);
  }
  __forceinline void resize(unsigned int n)
  {
    const unsigned int sz = (unsigned int)(mpEnd - mpBegin);
    if (n > sz) {
      uint32_t fill = 0;
      DoInsertValues(mpEnd, n - sz, &fill);
    } else {
      uint32_t* first = mpBegin + n;
      uint32_t* last = mpEnd;
      MemMove(first, last, (unsigned int)((char*)mpEnd - (char*)last));
      mpEnd = (uint32_t*)((char*)mpEnd + (first - last) * 4);
    }
  }
};

struct cTerrainHeights {
  char pad[0x10];
  uint8_t* mpData;          // +0x10: 4 uint16 samples per cell quad, 0x1000 bytes per cell row
};

struct cTerrainMap {
  char pad[8];
  cTerrainHeights* mpHeights;   // +8
  float GetWaterLevel();        // 0x00b7e0a0: fld [this+0x3c]
};

struct cTerrainSphere {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual cTerrainMap* GetMap();   // slot 3
};

class cPlanetModel {
 public:
  void ComputeContinents();

  char pad00[0x24];
  cTerrainSphere* mpISphere;              // +0x24
  char pad28[0x4c - 0x28];
  uint32_t* mContinentMap;                // +0x4c  (6 * 128 * 128 cells)
  UIntVector mContinentAreas;             // +0x50
  char pad5c[0x64 - 0x5c];
  ByteVector mContinentAboveWater;        // +0x64
  char pad70[0x78 - 0x70];
  bool mContinentMapDirty;                // +0x78
  char pad79[3];
  uint8_t* mCellNibbles;                  // +0x7c  (one nibble per cell)
};

// @ 0x00b87dc0
void cPlanetModel::ComputeContinents()
{
  if (!mContinentMap || !mpISphere)
    return;

  const unsigned int threshold = FloatToHeight16(mpISphere->GetMap()->GetWaterLevel());
  const uint8_t* heights = mpISphere->GetMap()->mpHeights->mpData;
  uint32_t* cells = mContinentMap;

  UnionFind uf;
  uf.reserve(0x10000);
  {
    uint16_t* p = uf.mpEnd;
    int i = 0;
    do {
      *p = (uint16_t)i;
      i++;
      p++;
    } while (i < 0x10000);
    uf.mpEnd = p;
  }

  // Pass 1: classify every cell (land bit 30, partial-water bit 31, attribute word) from its
  // 2x2 block of height samples and label connected runs with union-find.
  const __m64 thr = _mm_set1_pi32((int)threshold - 1);
  const __m64 zero = _mm_setzero_si64();
  const __m64 ones = _mm_set1_pi32(-1);
  uint32_t nextLabel = 1;
  int rowBase = 0;
  const uint8_t* rowPtr = heights;
  uint32_t* prev = cells - 1;
  do {
    uint32_t row = 0;
    do {
      uint32_t col = 0;
      const uint8_t* sample = rowPtr;
      const uint8_t* info = rowPtr + 0x804;
      do {
        __m64 anyAbove = zero;
        __m64 allAbove = ones;
        const uint8_t* q = sample;
        int k = 2;
        do {
          __m64 v = *(const __m64*)q;
          __m64 lo = _mm_cmpgt_pi32(_mm_unpacklo_pi16(v, zero), thr);
          __m64 hi = _mm_cmpgt_pi32(_mm_unpackhi_pi16(v, zero), thr);
          anyAbove = _mm_or_si64(anyAbove, lo);
          anyAbove = _mm_or_si64(anyAbove, hi);
          allAbove = _mm_and_si64(allAbove, lo);
          allAbove = _mm_and_si64(allAbove, hi);
          q += 0x800;
        } while (--k);
        uint32_t land = (anyAbove.m64_u32[1] | anyAbove.m64_u32[0]) & 0x40000000;
        uint32_t cell = (~(allAbove.m64_u32[1] & allAbove.m64_u32[0]) & 0x80000000) |
                        *(const uint16_t*)info | land;
        prev[1] = cell;

        bool hasUp = false;
        if (row != 0 && (cells[rowBase + col - 0x80] & 0x40000000) == land)
          hasUp = true;
        bool hasLeft = false;
        if (col != 0 && (prev[0] & 0x40000000) == land)
          hasLeft = true;

        if (hasUp) {
          if (hasLeft) {
            uint32_t upLabel = cells[rowBase + col - 0x80] & 0x3fff0000;
            uint32_t leftLabel = prev[0] & 0x3fff0000;
            if (upLabel == leftLabel) {
              prev[1] = cell | upLabel;
            } else {
              uint16_t merged = uf.Union(upLabel >> 16, leftLabel >> 16);
              prev[1] |= (uint32_t)merged << 16;
            }
          } else {
            prev[1] = (cells[rowBase + col - 0x80] & 0x3fff0000) | cell;
          }
        } else if (hasLeft) {
          prev[1] = (prev[0] & 0x3fff0000) | cell;
        } else {
          prev[1] = ((nextLabel & 0x3fff) << 16) | cell;
          nextLabel++;
        }
        sample += 8;
        info += 8;
        col++;
        prev++;
      } while (col < 0x80);
      rowPtr += 0x1000;
      rowBase += 0x80;
      row++;
    } while (row < 0x80);
  } while (rowBase < 0x18000);
  _mm_empty();

  // Pass 2: merge labels across the cube-face seams (faces 0-3 against their higher neighbours).
  int startX[4] = {0, 0, 0x7f, 0x7f};
  int startY[4] = {0, 0x7f, 0x7f, 0};
  int stepX[4] = {1, 0, -1, 0};
  int stepY[4] = {0, -1, 0, 1};
  int outX[4] = {0, -1, 0, 1};
  int outY[4] = {-1, 0, 1, 0};
  int faceRow = 0;
  for (int f = 0; faceRow < 0x200; f++, faceRow += 0x80) {
    for (int j = 0; j < 4; j++) {
      int face = f;
      int x = outX[j] + startX[j];
      int y = outY[j] + startY[j];
      int dx = stepX[j];
      int dy = stepY[j];
      WrapCubeFace(0x80, &face, &x, &y, &dx, &dy);
      if (f < face) {
        uint32_t* cur = cells + (faceRow + startY[j]) * 0x80 + startX[j];
        int stride = stepY[j] * 0x80 + stepX[j];
        for (uint32_t t = 0; t < 0x80; t++) {
          uint32_t other = cells[(face * 0x80 + y) * 0x80 + (dy * 0x80 + dx) * t + x];
          if (((other ^ *cur) & 0x40000000) == 0)
            uf.Union((*cur >> 16) & 0x3fff, (other >> 16) & 0x3fff);
          cur += stride;
        }
      }
    }
  }

  const unsigned int regions = (unsigned int)uf.Flatten(nextLabel, 0x3ff);
  mContinentAboveWater.resize(regions);
  mContinentAreas.clear();
  mContinentAreas.resize(regions);

  // Pass 3: replace the provisional labels by the flattened ones, accumulate the region areas and
  // above-water flags, and fold in the per-cell attribute nibble (two cells per byte).
  const uint8_t* nibbles = mCellNibbles;
  uint8_t* aboveWater = mContinentAboveWater.mpBegin;
  uint32_t* areas = mContinentAreas.mpBegin;
  uint32_t* end = cells + 0x18000;
  for (uint32_t* p = cells; p < end; p += 2) {
    uint32_t b = *nibbles++;
    uint32_t c0 = p[0];
    uint32_t id0 = uf.mpBegin[((const uint16_t*)p)[1] & 0x3fff] & 0x3ff;
    uint32_t n0 = (c0 & 0xc000ffff) | ((((b & 0xf0) << 6) | id0) << 16);
    p[0] = n0;
    aboveWater[id0] = (uint8_t)((n0 >> 30) & 1);
    areas[id0]++;

    uint32_t c1 = p[1];
    uint32_t id1 = uf.mpBegin[((const uint16_t*)p)[3] & 0x3fff] & 0x3ff;
    uint32_t n1 = (c1 & 0xc000ffff) | ((((b & 0xf) << 10) | id1) << 16);
    p[1] = n1;
    aboveWater[id1] = (uint8_t)((n1 >> 30) & 1);
    areas[id1]++;
  }
  mContinentMapDirty = false;
}

}  // namespace SP
