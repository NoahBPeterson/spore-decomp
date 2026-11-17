// Serializer registration (0x00b79a10): add this object to the serializer as a child with the class descriptor at
// 0x156b478 and the name L"cObstacleManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b79a10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b79a10[];   // 0x0156b478 class descriptor

struct Object_b79a10 {
    bool AddTo(Serializer_b79a10* serializer);
};

// @ 0x00b79a10
bool Object_b79a10::AddTo(Serializer_b79a10* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b79a10, L"cObstacleManager");
}
