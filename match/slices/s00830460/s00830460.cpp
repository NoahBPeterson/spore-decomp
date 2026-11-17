// Cast (0x00830460): return this for interface 0x053eb526, otherwise ask the base class (Cast 0x987930).
#include "game/types.h"

struct Base_830460 {
    void* Cast(uint32_t typeID) const;   // 0x00987930
};
struct Object_830460 : Base_830460 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00830460
void* Object_830460::Cast(uint32_t typeID) const
{
    if (typeID != 0x053eb526)
        return Base_830460::Cast(typeID);
    return (void*)this;
}
