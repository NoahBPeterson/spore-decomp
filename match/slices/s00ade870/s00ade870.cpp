// Serializer registration (0x00ade870): add this object to the serializer as a child with the class descriptor at
// 0x156656c and the name L"cCinematicManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ade870 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ade870[];   // 0x0156656c class descriptor

struct Object_ade870 {
    bool AddTo(Serializer_ade870* serializer);
};

// @ 0x00ade870
bool Object_ade870::AddTo(Serializer_ade870* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_ade870, L"cCinematicManager");
}
