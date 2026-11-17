// Serializer registration (0x00c55f80): add this object to the serializer as a child with the class descriptor at
// 0x15760c8 and the name L"cMissionFlight101" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c55f80 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c55f80[];   // 0x015760c8 class descriptor

struct Object_c55f80 {
    bool AddTo(Serializer_c55f80* serializer);
};

// @ 0x00c55f80
bool Object_c55f80::AddTo(Serializer_c55f80* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c55f80, L"cMissionFlight101");
}
