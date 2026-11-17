// Serializer registration (0x00b1c430): add this object to the serializer as a child with the class descriptor at
// 0x15682b0 and the name L"cGameInputManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b1c430 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b1c430[];   // 0x015682b0 class descriptor

struct Object_b1c430 {
    bool AddTo(Serializer_b1c430* serializer);
};

// @ 0x00b1c430
bool Object_b1c430::AddTo(Serializer_b1c430* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0xc), sDescriptor_b1c430, L"cGameInputManager");
}
