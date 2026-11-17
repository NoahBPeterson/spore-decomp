// Serializer registration (0x00b4ce00): add this object to the serializer as a child with the class descriptor at
// 0x1569a10 and the name L"cGonzagoPhysics" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b4ce00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b4ce00[];   // 0x01569a10 class descriptor

struct Object_b4ce00 {
    bool AddTo(Serializer_b4ce00* serializer);
};

// @ 0x00b4ce00
bool Object_b4ce00::AddTo(Serializer_b4ce00* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b4ce00, L"cGonzagoPhysics");
}
