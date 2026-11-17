// Serializer registration (0x00bd7080): add this object to the serializer as a child with the class descriptor at
// 0x156e104 and the name L"cCheatObjectManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd7080 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd7080[];   // 0x0156e104 class descriptor

struct Object_bd7080 {
    bool AddTo(Serializer_bd7080* serializer);
};

// @ 0x00bd7080
bool Object_bd7080::AddTo(Serializer_bd7080* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_bd7080, L"cCheatObjectManager");
}
