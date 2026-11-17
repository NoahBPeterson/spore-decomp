// Serializer registration (0x00ff8880): add this object to the serializer as a child with the class descriptor at
// 0x15b6160 and the name L"cSimPlanetHighLOD" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ff8880 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ff8880[];   // 0x015b6160 class descriptor

struct Object_ff8880 {
    bool AddTo(Serializer_ff8880* serializer);
};

// @ 0x00ff8880
bool Object_ff8880::AddTo(Serializer_ff8880* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_ff8880, L"cSimPlanetHighLOD");
}
