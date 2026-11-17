// Serializer registration (0x00ff4070): add this object to the serializer as a child with the class descriptor at
// 0x15b5ed8 and the name L"cPlayerInventory" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ff4070 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ff4070[];   // 0x015b5ed8 class descriptor

struct Object_ff4070 {
    bool AddTo(Serializer_ff4070* serializer);
};

// @ 0x00ff4070
bool Object_ff4070::AddTo(Serializer_ff4070* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_ff4070, L"cPlayerInventory");
}
