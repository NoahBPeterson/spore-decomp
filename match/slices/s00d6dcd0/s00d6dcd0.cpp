// @ 0x00d6dcd0
#include "game/types.h"

// Stand-in for the object whose CountValid() (0x00c0f570) is queried here.
class cCountValid_s00d6_dcd0 {
public:
    int CountValid();   // 0x00c0f570
};

float f00d6dcd0(cCountValid_s00d6_dcd0* self)
{
    if (self->CountValid() > 0)
        return 0.0f;
    return 1.0f;
}
