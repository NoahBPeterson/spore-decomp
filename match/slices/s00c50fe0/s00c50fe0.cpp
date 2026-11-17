// Serializer registration (0x00c50fe0): add this object to the serializer as a child with the class descriptor at
// 0x1575978 and the name L"cMissionExplore" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c50fe0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c50fe0[];   // 0x01575978 class descriptor

struct Object_c50fe0 {
    bool AddTo(Serializer_c50fe0* serializer);
};

// @ 0x00c50fe0
bool Object_c50fe0::AddTo(Serializer_c50fe0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c50fe0, L"cMissionExplore");
}
