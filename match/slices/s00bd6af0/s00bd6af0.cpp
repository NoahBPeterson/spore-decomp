// Serializer registration (0x00bd6af0): add this object to the serializer as a child with the class descriptor at
// 0x156e0c8 and the name L"cCheatObject" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd6af0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd6af0[];   // 0x0156e0c8 class descriptor

struct Object_bd6af0 {
    bool AddTo(Serializer_bd6af0* serializer);
};

// @ 0x00bd6af0
bool Object_bd6af0::AddTo(Serializer_bd6af0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd6af0, L"cCheatObject");
}
