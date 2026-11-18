// @ 0x00c2ec80
#include "game/types.h"
#include "EA/Variant.h"

unsigned int* __fastcall FUN_0041ea00(const EA::Variant*);

// The retail symbol has no surviving PDB name.
class MissionPropertyReader {
public:
    unsigned int FUN_00c2ec80();
};

unsigned int MissionPropertyReader::FUN_00c2ec80()
{
    void* properties = ((void* (__thiscall*)(void*))
        (*(void***)this)[0xc0 / 4])(this);
    if (properties) {
        unsigned int result = 0;
        const EA::Variant* property;
        if (((bool (__thiscall*)(void*, unsigned int, const EA::Variant**))
                (*(void***)properties)[0x24 / 4])(properties, 0x5d6796fd, &property)
            && property->mTypeId == EA::Variant::kTypeUint32) {
            result = *FUN_0041ea00(property);
        }
        return result;
    }
    return 0;
}
