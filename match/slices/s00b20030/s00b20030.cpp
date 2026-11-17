// Serializer registration (0x00b20030): add this object to the serializer as a child with the class descriptor at
// 0x157d398 and the name L"cArtilleryProjectile" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b20030 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b20030[];   // 0x0157d398 class descriptor

struct Object_b20030 {
    bool AddTo(Serializer_b20030* serializer);
};

// @ 0x00b20030
bool Object_b20030::AddTo(Serializer_b20030* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b20030, L"cArtilleryProjectile");
}
