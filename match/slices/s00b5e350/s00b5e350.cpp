// Serializer registration (0x00b5e350): add this object to the serializer as a child with the class descriptor at
// 0x15a90cc and the name L"cNPCCityMusicManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b5e350 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b5e350[];   // 0x015a90cc class descriptor

struct Object_b5e350 {
    bool AddTo(Serializer_b5e350* serializer);
};

// @ 0x00b5e350
bool Object_b5e350::AddTo(Serializer_b5e350* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b5e350, L"cNPCCityMusicManager");
}
