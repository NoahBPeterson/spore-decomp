// Serializer registration (0x00c8d780): add this object to the serializer as a child with the class descriptor at
// 0x157a9e0 and the name L"cTotemPole" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c8d780 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c8d780[];   // 0x0157a9e0 class descriptor

struct Object_c8d780 {
    bool AddTo(Serializer_c8d780* serializer);
};

// @ 0x00c8d780
bool Object_c8d780::AddTo(Serializer_c8d780* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c8d780, L"cTotemPole");
}
