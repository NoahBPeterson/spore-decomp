// Slice s00f6b9a0 -- SP::cTerrainEditor::UpdateCPUFromGPU  @ 0x00f6bd70  (2190 bytes).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
//
// After the GPU edited the terrain height maps, read the changed rectangles of each of the six
// cube faces back to the CPU copy (whole face when the dirty rect is >= 0.25 of the face, else
// 64x64 tiles through FUN_00f69f50), recompute each face's min/max height, push the rects to the
// terrain sphere and post message 0x44448ed. Returns false if the sphere is missing or a tile
// read-back failed.
#include "../../include/types.h"

namespace TE {

struct Rect {
    float l, t, r, b;
    float Width() const { return r - l; }
    float Height() const { return b - t; }
};
struct MinMax { float mn, mx; };

struct Raster {
    uint32_t pad0[3];
    uint16_t width;            // +0x0c
    uint16_t height;           // +0x0e
    uint8_t depth;             // +0x10 (bits per pixel)
    // read back the pixels into dst (anonymous_namespace::FillSpriteTexture, thiscall ret 0xc)
    void ReadPixels(uint32_t* dst, uint32_t bytes, int offset);   // 0x011F0440
};

struct HeightData {
    uint32_t pad0[2];
    int mSide;                 // +0x08
    int mVersion;              // +0x0c
    uint16_t* mSamples;        // +0x10  [face][side*side]
};
struct HeightMap {
    uint32_t pad0[2];
    HeightData* mpData;        // +0x08
    char pad0c[0x50 - 0x0c];
    float mMinHeight;          // +0x50
    float mMaxHeight;          // +0x54
    void SetRange(const MinMax* r);                               // 0x00F92520 (thiscall, ret 4)
};

struct cTerrainSphere {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual HeightMap* GetHeightMap();                            // +0x0c
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void Notify(int flag);                                // +0x48
    void Relevel(float a, int b);                                 // 0x00FA43E0 (thiscall, ret 8)
    void MarkFaceDirty(int face, const Rect* r);                  // 0x00F99AC0 (thiscall, ret 8)
};

struct IMessageServer {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void Post(uint32_t id, int a, int b);                 // +0x14
};
IMessageServer* MessageServer();                                  // 0x0067DCC0

struct U32Vector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void resize(uint32_t n);                                      // 0x004CD3C0 (thiscall, ret 4)
};

extern void* g_gate;                                              // 0x015B0E48: self-referencing pointer
extern const float kMinTileFraction;                              // 0x013EB8A0 constant 0.25f
extern const float kHeightUnit;                                   // 0x0140D4F8 (1/32768)

template <class T> inline const T& Min(const T& a, const T& b) { return b < a ? b : a; }
template <class T> inline const T& Max(const T& a, const T& b) { return a < b ? b : a; }

struct cTerrainEditor {
    char pad0[0x20];
    Raster* mHeightRaster[6];           // +0x20
    char pad38[0x74 - 0x38];
    cTerrainSphere* mpSphere;           // +0x74
    char pad78[0x80 - 0x78];
    Rect mDirty[6];                     // +0x80
    char pade0[0x140 - 0xe0];
    uint16_t mMinMax[6][2];             // +0x140: per face {min, max} heights
    char pad158[0x168 - 0x158];
    U32Vector mTemp;                    // +0x168

    bool ReadTile(int face, const int* rect, float a);            // 0x00F69F50 (thiscall, ret 0xc)
    bool UpdateCPUFromGPU(float elapsed);
};

static __forceinline void ClearRect(Rect& r) { r.l = 0.0f; r.t = 0.0f; r.r = 0.0f; r.b = 0.0f; }

// @ 0x00f6bd70
bool cTerrainEditor::UpdateCPUFromGPU(float elapsed)
{
    cTerrainSphere* sphere = mpSphere;
    if (sphere == 0 || g_gate != (void*)&g_gate)
        return false;

    const float eps = 0.001953125f;
    bool dirty = false;
    for (int i = 0; i < 5; i++) {
        Rect& r = mDirty[i];
        if (r.l != r.r && r.t != r.b) {
            if (r.Width() < eps || r.Height() < eps)
                ClearRect(r);
            else
                dirty = true;
        }
    }
    {
        Rect& r = mDirty[5];
        if (r.l != r.r && r.t != r.b) {
            if (r.Width() < eps || r.Height() < eps)
                ClearRect(r);
            else
                goto relevel;
        }
    }
    if (!dirty)
        return true;
relevel:
    sphere->Relevel(elapsed, 0);

    {
        Raster* raster = mHeightRaster[0];
        const uint32_t width = raster->width;
        const uint32_t height = raster->height;
        const uint32_t bytesPerPixel = raster->depth >> 3;
        HeightData* heights = mpSphere->GetHeightMap()->mpData;
        bool anyUpdated = false;
        uint16_t* minMax = &mMinMax[0][0];

        for (int face = 0; face < 6; face++, minMax += 2) {
            Rect& r = mDirty[face];
            if (r.l != r.r && r.t != r.b) {
                static float sFullFraction = kMinTileFraction;
                uint16_t mn = 0xffff;
                uint16_t mx = 0;
                uint16_t* src = heights->mSamples + heights->mSide * heights->mSide * face;
                if (sFullFraction <= r.Width() || sFullFraction <= r.Height()) {
                    // large dirty area: read the whole face back
                    const uint32_t count = height * width;
                    mTemp.resize(count);
                    uint32_t* buf = mTemp.mpBegin;
                    mHeightRaster[face]->ReadPixels(buf, bytesPerPixel * height * width, 0);
                    anyUpdated = true;
                    uint16_t* dst = src;
                    for (uint32_t i = 0; i < count; i++) {
                        const uint16_t v = (uint16_t)(buf[i] >> 8);
                        dst[i] = v;
                        if (v < mn) mn = v;
                        if (mx < v) mx = v;
                    }
                } else {
                    // small dirty area: read it back in 64x64 tiles
                    const float fh = (float)height;
                    const float fw = (float)width;
                    const int row1 = (int)(r.b * fh);
                    const int col1 = (int)(r.r * fw);
                    const int row0 = (int)(r.t * fh);
                    const int col0 = (int)(r.l * fw);
                    const int nrows = (((uint32_t)(row1 - row0) - 1) >> 6) + 1;
                    const int ncols = (((uint32_t)(col1 - col0) - 1) >> 6) + 1;
                    int y = row0;
                    for (int rb = 0; rb < nrows; rb++, y += 0x40) {
                        int x = col0;
                        for (int cb = 0; cb < ncols; cb++, x += 0x40) {
                            int tile[4];
                            tile[0] = x;
                            tile[1] = y;
                            tile[2] = x + 0x40;
                            tile[3] = y + 0x40;
                            if (!ReadTile(face, tile, elapsed))
                                return false;
                        }
                    }
                    anyUpdated = true;
                    const uint32_t count = height * width;
                    for (uint32_t i = 0; i < count; i++) {
                        const uint16_t v = src[i];
                        if (v < mn) mn = v;
                        if (mx < v) mx = v;
                    }
                }
                minMax[0] = mn;
                minMax[1] = mx;
                mpSphere->MarkFaceDirty(face, &r);
                mpSphere->Notify(1);
            }
        }

        for (int i = 0; i < 6; i++)
            ClearRect(mDirty[i]);

        if (anyUpdated) {
            uint16_t lo = 0xffff;
            uint16_t hi = 0;
            lo = Min(lo, mMinMax[0][0]); hi = Max(hi, mMinMax[0][1]);
            lo = Min(lo, mMinMax[1][0]); hi = Max(hi, mMinMax[1][1]);
            lo = Min(lo, mMinMax[2][0]); hi = Max(hi, mMinMax[2][1]);
            lo = Min(lo, mMinMax[3][0]); hi = Max(hi, mMinMax[3][1]);
            lo = Min(lo, mMinMax[4][0]); hi = Max(hi, mMinMax[4][1]);
            lo = Min(lo, mMinMax[5][0]); hi = Max(hi, mMinMax[5][1]);
            MinMax range;
            range.mn = (float)((int)lo - 0x8000) * kHeightUnit;
            range.mx = (float)((int)hi - 0x8000) * kHeightUnit;
            mpSphere->GetHeightMap()->SetRange(&range);
        }
        mpSphere->GetHeightMap()->mpData->mVersion++;
        MessageServer()->Post(0x44448ed, 0, 0);
    }
    return true;
}

}  // namespace TE
