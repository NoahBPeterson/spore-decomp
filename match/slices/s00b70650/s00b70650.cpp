// Serializer registration (0x00b70650): add this object to the serializer as a child with the class descriptor at
// 0x156b198 and the name L"cMissionManagerBase" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b70650 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b70650[];   // 0x0156b198 class descriptor

struct Object_b70650 {
    bool AddTo(Serializer_b70650* serializer);
};

// @ 0x00b70650
bool Object_b70650::AddTo(Serializer_b70650* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_b70650, L"cMissionManagerBase");
}
