// Serializer registration (0x00c5e7b0): add this object to the serializer as a child with the class descriptor at
// 0x1577008 and the name L"cMissionScan" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c5e7b0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c5e7b0[];   // 0x01577008 class descriptor

struct Object_c5e7b0 {
    bool AddTo(Serializer_c5e7b0* serializer);
};

// @ 0x00c5e7b0
bool Object_c5e7b0::AddTo(Serializer_c5e7b0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c5e7b0, L"cMissionScan");
}
