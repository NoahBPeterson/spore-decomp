// Slice s006e4210: the single function in this slice is
//   SP::CaptureCubeMap   (0x006e4210, 3988 bytes, __cdecl, 8 args, 16-byte-aligned frame)
//
// It is an /O2 /arch:SSE2 cube-map capture routine: for each of the six cube faces it
// builds the face direction, orthonormalises a basis, composes the rotation from the
// passed quaternion/position, dispatches cViewer::UpdateTransforms and the render-target
// setup (FUN_006e3f70, FUN_007c4d20/5310/3c20), allocates Graphics-category objects with
// the six-argument operator new, walks the EffectsManager render list (vtable +0x68/+0x70)
// and submits each effect through FUN_0076b720.
//
// Nearly every vector/matrix helper is inlined into the 3988-byte body, so a faithful
// byte-for-byte reproduction is out of budget for this slice.  This file keeps a
// compiling skeleton with the exact signature / call shape; bookkeeping is in partial.txt.
#include "types.h"

namespace SP {

void CaptureCubeMap(int* pOut, float* pPosition, float* pRotation,
                    unsigned short size, int arg5, int arg6, bool flip, int arg8);

}  // namespace SP

// @ 0x006e4210
void SP::CaptureCubeMap(int*, float*, float*, unsigned short, int, int, bool, int)
{
}
