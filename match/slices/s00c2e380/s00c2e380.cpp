// Serializer registration (0x00c2e380): add this object to the serializer as a child with the class descriptor at
// 0x1572560 and the name L"cCreatureMission" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c2e380 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c2e380[];   // 0x01572560 class descriptor

struct Object_c2e380 {
    bool AddTo(Serializer_c2e380* serializer);
};

// @ 0x00c2e380
bool Object_c2e380::AddTo(Serializer_c2e380* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c2e380, L"cCreatureMission");
}
