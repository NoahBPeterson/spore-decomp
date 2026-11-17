// Serializer registration (0x00b18500): add this object to the serializer as a child with the class descriptor at
// 0x1567e48 and the name L"cGameData" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b18500 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b18500[];   // 0x01567e48 class descriptor

struct Object_b18500 {
    bool AddTo(Serializer_b18500* serializer);
};

// @ 0x00b18500
bool Object_b18500::AddTo(Serializer_b18500* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b18500, L"cGameData");
}
