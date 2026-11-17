// Serializer registration (0x00b73b00): add this object to the serializer as a child with the class descriptor at
// 0x156b434 and the name L"cObstacle" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b73b00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b73b00[];   // 0x0156b434 class descriptor

struct Object_b73b00 {
    bool AddTo(Serializer_b73b00* serializer);
};

// @ 0x00b73b00
bool Object_b73b00::AddTo(Serializer_b73b00* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b73b00, L"cObstacle");
}
