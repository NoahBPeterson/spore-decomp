// Serializer registration (0x00b2fcf0): add this object to the serializer as a child with the class descriptor at
// 0x1568e18 and the name L"cGameTerrainCursor" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b2fcf0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b2fcf0[];   // 0x01568e18 class descriptor

struct Object_b2fcf0 {
    bool AddTo(Serializer_b2fcf0* serializer);
};

// @ 0x00b2fcf0
bool Object_b2fcf0::AddTo(Serializer_b2fcf0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b2fcf0, L"cGameTerrainCursor");
}
