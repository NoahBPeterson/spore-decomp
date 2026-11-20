// @ 0x007dc140
#include "game/types.h"
#include <intrin.h>
#pragma intrinsic(_ReadWriteBarrier)

namespace SP {
class cSmoothCameraController {
public:
    char mCameraState[0x14c];
    void** mpOrientationBegin_14c;
    void** mpOrientationEnd_150;
    char mCameraState154[0xc];
    int mOrientationIndex_160;

    void SetCurrentDiscreteOrientation(int orientation);
};

void cSmoothCameraController::SetCurrentDiscreteOrientation(int orientation)
{
    mOrientationIndex_160 = orientation;
    _ReadWriteBarrier();
    int count = mpOrientationEnd_150 - mpOrientationBegin_14c;
    if (count > 0) {
        if (mOrientationIndex_160 < 0) {
            do {
                _ReadWriteBarrier();
                mOrientationIndex_160 += count;
                _ReadWriteBarrier();
            } while (mOrientationIndex_160 < 0);
        }
        if (mOrientationIndex_160 >= count) {
            do {
                _ReadWriteBarrier();
                mOrientationIndex_160 -= count;
                _ReadWriteBarrier();
            } while (mOrientationIndex_160 >= count);
        }
    }
}
}
