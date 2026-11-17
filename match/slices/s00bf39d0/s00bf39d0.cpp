// Serializer registration (0x00bf39d0): add this object to the serializer as a child with the class descriptor at
// 0x156faa8 and the name L"cCivilization" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bf39d0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bf39d0[];   // 0x0156faa8 class descriptor

struct Object_bf39d0 {
    bool AddTo(Serializer_bf39d0* serializer);
};

// @ 0x00bf39d0
bool Object_bf39d0::AddTo(Serializer_bf39d0* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bf39d0, L"cCivilization");
}
