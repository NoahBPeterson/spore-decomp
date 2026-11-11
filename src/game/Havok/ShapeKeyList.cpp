// Havok VC7.1 companion for the mixed _at_01100000 module.
// Flags: /vc71 /O2 /MD /Gy /TP /Isrc/game/include
#include "ShapeKeyList.h"

// @ 0x01103330
hkShapeKeyList::hkShapeKeyList(hkShapeContainer* container)
{
    m_container = container;
    m_numKeys = container->getNumChildShapes();
}
