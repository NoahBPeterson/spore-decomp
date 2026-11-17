// Serializer registration (0x00c6a8d0): add this object to the serializer as a child with the class descriptor at
// 0x1577a98 and the name L"cNest" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c6a8d0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c6a8d0[];   // 0x01577a98 class descriptor

struct Object_c6a8d0 {
    bool AddTo(Serializer_c6a8d0* serializer);
};

// @ 0x00c6a8d0
bool Object_c6a8d0::AddTo(Serializer_c6a8d0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c6a8d0, L"cNest");
}
