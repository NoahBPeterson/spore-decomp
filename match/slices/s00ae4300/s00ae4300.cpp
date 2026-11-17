// Serializer registration (0x00ae4300): add this object to the serializer as a child with the class descriptor at
// 0x1569d00 and the name L"cGonzagoSimulator" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ae4300 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ae4300[];   // 0x01569d00 class descriptor

struct Object_ae4300 {
    bool AddTo(Serializer_ae4300* serializer);
};

// @ 0x00ae4300
bool Object_ae4300::AddTo(Serializer_ae4300* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_ae4300, L"cGonzagoSimulator");
}
