// Serializer registration (0x00c6f430): add this object to the serializer as a child with the class descriptor at
// 0x1578618 and the name L"cObjectInstanceInventoryItem" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c6f430 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c6f430[];   // 0x01578618 class descriptor

struct Object_c6f430 {
    bool AddTo(Serializer_c6f430* serializer);
};

// @ 0x00c6f430
bool Object_c6f430::AddTo(Serializer_c6f430* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_c6f430, L"cObjectInstanceInventoryItem");
}
