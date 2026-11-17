// Serializer registration (0x00c6bee0): add this object to the serializer as a child with the class descriptor at
// 0x1577bc8 and the name L"cHerd" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c6bee0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c6bee0[];   // 0x01577bc8 class descriptor

struct Object_c6bee0 {
    bool AddTo(Serializer_c6bee0* serializer);
};

// @ 0x00c6bee0
bool Object_c6bee0::AddTo(Serializer_c6bee0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c6bee0, L"cHerd");
}
