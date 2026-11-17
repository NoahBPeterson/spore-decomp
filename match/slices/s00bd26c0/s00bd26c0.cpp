// Serializer registration (0x00bd26c0): add this object to the serializer as a child with the class descriptor at
// 0x156deb4 and the name L"cBuildingScenario" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bd26c0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bd26c0[];   // 0x0156deb4 class descriptor

struct Object_bd26c0 {
    bool AddTo(Serializer_bd26c0* serializer);
};

// @ 0x00bd26c0
bool Object_bd26c0::AddTo(Serializer_bd26c0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bd26c0, L"cBuildingScenario");
}
