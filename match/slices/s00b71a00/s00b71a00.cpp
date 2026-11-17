// Serializer registration (0x00b71a00): add this object to the serializer as a child with the class descriptor at
// 0x156b308 and the name L"cNanoDroneManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b71a00 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b71a00[];   // 0x0156b308 class descriptor

struct Object_b71a00 {
    bool AddTo(Serializer_b71a00* serializer);
};

// @ 0x00b71a00
bool Object_b71a00::AddTo(Serializer_b71a00* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_b71a00, L"cNanoDroneManager");
}
