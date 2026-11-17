// Serializer registration (0x00c47890): add this object to the serializer as a child with the class descriptor at
// 0x15745f0 and the name L"cMission" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c47890 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c47890[];   // 0x015745f0 class descriptor

struct Object_c47890 {
    bool AddTo(Serializer_c47890* serializer);
};

// @ 0x00c47890
bool Object_c47890::AddTo(Serializer_c47890* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c47890, L"cMission");
}
