// Slice s00f8afd0 -- SPTerrain/SPTerrainMap.obj.
// Fraction of a 6-face terrain map whose (unsigned short) height exceeds a threshold,
// plus optional bucketing of a byte taken from the top byte of a 32-bit source cell.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

struct MapU32 {
    void*          mVftable;   // +0x00
    int            mnRefCount; // +0x04
    int            mFaceSize;  // +0x08
    int            mModCount;  // +0x0c
    unsigned int*  mBegin;     // +0x10
};

struct MapU16 {
    void*           mVftable;   // +0x00
    int             mnRefCount; // +0x04
    int             mFaceSize;  // +0x08
    int             mModCount;  // +0x0c
    unsigned short* mBegin;     // +0x10
};

#define HEIGHT_SCALE 3.0518509447574615e-05f   // 1/32767
#define VALUE_SCALE  0.3921568989753723f       // 100/255

// @ 0x00f8afd0
void __cdecl ComputeThresholdFraction(const MapU32& src, const MapU16& dst, float threshold,
                                      float* outA, float* outB, float* outC, float* outD)
{
    int total = src.mFaceSize * src.mFaceSize * 6;
    const unsigned char*  values  = (const unsigned char*)src.mBegin;
    const unsigned short* heights = dst.mBegin;
    unsigned int above = 0;
    unsigned int lt3 = 0;
    unsigned int mid = 0;
    unsigned int gt32 = 0;
    bool want = outA != 0 || outB != 0 || outC != 0;

#define CELL(n)                                                        \
    do {                                                               \
        int h = (int)heights[(n)] - 0x8000;                            \
        if ((float)h * HEIGHT_SCALE > threshold) {                     \
            ++above;                                                   \
            if (want) {                                                \
                float v = (float)values[(n) * 4 + 3] * VALUE_SCALE;    \
                if (v < 3.0f)      ++lt3;                              \
                else if (v > 32.0f) ++gt32;                            \
                else               ++mid;                              \
            }                                                          \
        }                                                              \
    } while (0)

    for (int i = 0; i < total; ++i)
        CELL(i);

#undef CELL

    *outD = 1.0f - (float)above / (float)total;
    if (above == 0)
        above = 1;
    if (outA != 0)
        *outA = (float)lt3 / (float)above;
    if (outB != 0)
        *outB = (float)mid / (float)above;
    if (outC != 0)
        *outC = (float)gt32 / (float)above;
}
