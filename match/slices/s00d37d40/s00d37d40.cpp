// Serializer registration (0x00d37d40): add this object to the serializer as a child with the class descriptor at
// 0x1582d30 and the name L"cCreatureMissionManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d37d40 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d37d40[];   // 0x01582d30 class descriptor

struct Object_d37d40 {
    bool AddTo(Serializer_d37d40* serializer);
};

// @ 0x00d37d40
bool Object_d37d40::AddTo(Serializer_d37d40* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_d37d40, L"cCreatureMissionManager");
}
