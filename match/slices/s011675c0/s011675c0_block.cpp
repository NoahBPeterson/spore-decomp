// The linked height-field block lives in its own translation unit, so its
// destructor sees only the base declaration and has to call it.
#include "heightcodec.h"

// @ 0x011680b0 is the compiler-generated scalar deleting destructor of cHeightBlock
cHeightBlock::~cHeightBlock()
{
    if (mpLinked != 0)
        g_free_016f16f4(mpLinked);
}
