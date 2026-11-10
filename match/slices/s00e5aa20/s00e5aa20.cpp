// Slice s00e5aa20: build a 0x14-byte placement record from a source position and two probes.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

struct u32;
typedef unsigned int u32x;

// 0x00e5a850: convert a level-relative position into a pair of texture coordinates.
namespace SP {
void sLevelGetTextureCoord(int level, float* pos, u32x* out0, u32x* out1);
}

// The level driver the position belongs to: its +0x00 member is the level index and
// its +0x04 member is copied verbatim into the output record.
struct PlacementSource {
    int mLevel;                                 // +0x00
    u32x mField04;                              // +0x04
};

// @ 0x00e5aa20
void __cdecl FUN_00e5aa20(u32x* pOut, const float* pPosition, const PlacementSource* pSource)
{
    u32x nProbe0;
    u32x nProbe1;
    u32x nOffset0;
    u32x nOffset1;

    pOut[0] = pSource->mField04;
    SP::sLevelGetTextureCoord(pSource->mLevel, (float*)pPosition, &pOut[1], &pOut[3]);

    float vDelta[3];
    vDelta[0] = pPosition[3] - pPosition[0];
    vDelta[1] = pPosition[4] - pPosition[1];
    vDelta[2] = pPosition[5] - pPosition[2];
    SP::sLevelGetTextureCoord(pSource->mLevel, vDelta, &nProbe0, &nProbe1);

    pOut[2] = pOut[1] + nOffset0;
    pOut[4] = pOut[3] + nOffset1;
}
