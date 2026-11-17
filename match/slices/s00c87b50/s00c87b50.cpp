// Serializer registration (0x00c87b50): add this object to the serializer as a child with the class descriptor at
// 0x1579ed8 and the name L"cSpaceInventory" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c87b50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c87b50[];   // 0x01579ed8 class descriptor

struct Object_c87b50 {
    bool AddTo(Serializer_c87b50* serializer);
};

// @ 0x00c87b50
bool Object_c87b50::AddTo(Serializer_c87b50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c87b50, L"cSpaceInventory");
}
