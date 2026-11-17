// Serializer registration (0x00c628f0): add this object to the serializer as a child with the class descriptor at
// 0x15775a8 and the name L"cMissionUseTool" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c628f0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c628f0[];   // 0x015775a8 class descriptor

struct Object_c628f0 {
    bool AddTo(Serializer_c628f0* serializer);
};

// @ 0x00c628f0
bool Object_c628f0::AddTo(Serializer_c628f0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c628f0, L"cMissionUseTool");
}
