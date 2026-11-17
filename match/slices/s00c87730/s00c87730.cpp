// Serializer registration (0x00c87730): add this object to the serializer as a child with the class descriptor at
// 0x1579f50 and the name L"cSpaceInventoryItem" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c87730 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c87730[];   // 0x01579f50 class descriptor

struct Object_c87730 {
    bool AddTo(Serializer_c87730* serializer);
};

// @ 0x00c87730
bool Object_c87730::AddTo(Serializer_c87730* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_c87730, L"cSpaceInventoryItem");
}
