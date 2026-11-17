// Serializer registration (0x00c2f980): add this object to the serializer as a child with the class descriptor at
// 0x1572618 and the name L"cCreatureSpeciesMission" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c2f980 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c2f980[];   // 0x01572618 class descriptor

struct Object_c2f980 {
    bool AddTo(Serializer_c2f980* serializer);
};

// @ 0x00c2f980
bool Object_c2f980::AddTo(Serializer_c2f980* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c2f980, L"cCreatureSpeciesMission");
}
