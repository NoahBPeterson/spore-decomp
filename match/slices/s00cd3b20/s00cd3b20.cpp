// Serializer registration (0x00cd3b20): add this object to the serializer as a child with the class descriptor at
// 0x157ee90 and the name L"cTribeMissionManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_cd3b20 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_cd3b20[];   // 0x0157ee90 class descriptor

struct Object_cd3b20 {
    bool AddTo(Serializer_cd3b20* serializer);
};

// @ 0x00cd3b20
bool Object_cd3b20::AddTo(Serializer_cd3b20* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_cd3b20, L"cTribeMissionManager");
}
