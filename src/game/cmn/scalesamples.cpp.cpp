// src/game/cmn/scalesamples.cpp.cpp -- migrated from slice(s) s01148050 by tools/migrate/rewrite.py
// Object file: cmn/scalesamples.cpp.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// @ 0x01148da0
namespace rw {
namespace audio {
namespace core {
void ScaleSamples(float * pData, float scale, int numSamples)
{
    if (numSamples <= 0)
        return;
    if ((((unsigned int)pData) & 0xf) == 0 && ((unsigned int)numSamples & 0xf) == 0) {
        float* pEnd = pData + numSamples;
        do {
            pData[0] *= scale;  pData[1] *= scale;  pData[2] *= scale;  pData[3] *= scale;
            pData[4] *= scale;  pData[5] *= scale;  pData[6] *= scale;  pData[7] *= scale;
            pData[8] *= scale;  pData[9] *= scale;  pData[10] *= scale; pData[11] *= scale;
            pData[12] *= scale; pData[13] *= scale; pData[14] *= scale; pData[15] *= scale;
            pData += 16;
        } while (pData != pEnd);
        return;
    }
    float* pEnd = pData + numSamples;
    for (; pData < pEnd; ++pData)
        *pData = *pData * scale;
}
}
}
}  // namespace rw::audio::core
