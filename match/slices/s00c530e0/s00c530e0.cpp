// Serializer registration (0x00c530e0): add this object to the serializer as a child with the class descriptor at
// 0x1575bd8 and the name L"cMissionFetch" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c530e0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c530e0[];   // 0x01575bd8 class descriptor

struct Object_c530e0 {
    bool AddTo(Serializer_c530e0* serializer);
};

// @ 0x00c530e0
bool Object_c530e0::AddTo(Serializer_c530e0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c530e0, L"cMissionFetch");
}
