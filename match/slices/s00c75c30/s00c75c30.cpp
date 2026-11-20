// @ 0x00c75c30
// cPlayer property-array component getter.
//
// Reads the float array held by the player's property list under the given id and
// returns the component selected by the player's current index (+0x1248).  Fails
// over to 1.0f when the property list is absent, the lookup fails, or the index is
// outside 0..2.
#include "types.h"

// 0x006a08b0
bool __cdecl GetPropertyAsFloatArray(void* pList, uint32_t nId, int32_t* pCount,
                                     float** ppValues);

class cPlayerPropertySource {
public:
    uint8_t  mPad0000[0x11f4];                    // +0x0000
    void*    mpPropList;                          // +0x11f4  property list
    uint8_t  mPad11f8[0x1248 - 0x11f8];           // +0x11f8
    int32_t  mnComponent;                         // +0x1248  component index

    float GetPropertyComponent(uint32_t nId);
};

float cPlayerPropertySource::GetPropertyComponent(uint32_t nId)
{
    float*   pValues = 0;
    int32_t  nCount  = 0;

    if (mpPropList != 0 &&
        GetPropertyAsFloatArray(mpPropList, nId, &nCount, &pValues)) {
        switch (mnComponent) {
        case 0:
            return pValues[0];
        case 1:
            return pValues[1];
        case 2:
            return pValues[2];
        }
    }
    return 1.0f;
}
