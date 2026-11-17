// Serializer registration (0x00c79dd0): add this object to the serializer as a child with the class descriptor at
// 0x1578d18 and the name L"cPlayer" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c79dd0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c79dd0[];   // 0x01578d18 class descriptor

struct Object_c79dd0 {
    bool AddTo(Serializer_c79dd0* serializer);
};

// @ 0x00c79dd0
bool Object_c79dd0::AddTo(Serializer_c79dd0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c79dd0, L"cPlayer");
}
