// Havok's VC7.1 code is compiled separately from the mixed _at_01100000 module.
// Flags: /vc71 /O2 /MD /Gy /TP /Isrc/game/include
#include "MoppSettings.h"

// @ 0x011035f0
int hkMoppSettings::getScratchSize(hkMoppSource* src) const
{
    return (src->getNumPrimitives() + 0x1b400 + m_a.m_i1) * 16;
}
