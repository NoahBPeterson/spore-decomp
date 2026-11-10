// Flags: /O2 /MD /Gy /TP /GS-
#include "types.h"

namespace SP {

class cSerializationInfoBuilder {
public:
    bool AddChild(unsigned int value, const void* attributes, const wchar_t* typeName);
};

extern const char gStarClueAttributes;
extern const wchar_t kStarClueTypeName[];

// @ 0x00c45100
bool __cdecl RegisterStarClueSerialization(
    cSerializationInfoBuilder* builder, unsigned int value)
{
    if (value != 0) {
        builder->AddChild(value, &gStarClueAttributes, kStarClueTypeName);
    }
    return true;
}

}
