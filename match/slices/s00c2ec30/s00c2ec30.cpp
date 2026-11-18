// @ 0x00c2ec30
#include "game/types.h"
#include "EA/Variant.h"

// Retail unsigned-integer Variant accessor, returning the value storage.
unsigned int* __fastcall FUN_0041ea00(const EA::Variant*);

class MissionProgressLayout {
public:
    unsigned int GetProgressLayoutID();
};

unsigned int MissionProgressLayout::GetProgressLayoutID()
{
    unsigned int result = 0;
    void* properties = ((void* (__thiscall*)(void*))(*(void***)this)[0xc0 / 4])(this);
    if (properties) {
        const EA::Variant* property;
        if (((bool (__thiscall*)(void*, unsigned int, const EA::Variant**))
                (*(void***)properties)[0x24 / 4])(properties, 0x63ff8cc5, &property)
            && property->mTypeId == EA::Variant::kTypeUint32) {
            result = *FUN_0041ea00(property);
        }
    }
    return result;
}
