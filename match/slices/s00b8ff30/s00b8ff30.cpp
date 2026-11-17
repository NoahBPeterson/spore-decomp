// Serializer registration (0x00b8ff30): add this object to the serializer as a child with the class descriptor at
// 0x156bd38 and the name L"cPlantSpeciesManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b8ff30 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b8ff30[];   // 0x0156bd38 class descriptor

struct Object_b8ff30 {
    bool AddTo(Serializer_b8ff30* serializer);
};

// @ 0x00b8ff30
bool Object_b8ff30::AddTo(Serializer_b8ff30* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b8ff30, L"cPlantSpeciesManager");
}
