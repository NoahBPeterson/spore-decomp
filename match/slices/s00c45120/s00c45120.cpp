// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

namespace SP {

class cSerializationInfoBuilder {
public:
    bool AddChild(unsigned int value, const void* attributes, const wchar_t* typeName);
};

extern const char gPlanetClueAttributes;
extern const wchar_t kPlanetClueTypeName[];

// @ 0x00c45120
bool __cdecl RegisterPlanetClueSerialization(
    cSerializationInfoBuilder* builder, unsigned int value)
{
    if (value != 0) {
        builder->AddChild(value, &gPlanetClueAttributes, kPlanetClueTypeName);
    }
    return true;
}

}
