// Serializer registration (0x00c35e50): add this object to the serializer as a child with the class descriptor at
// 0x1573038 and the name L"cGameBundle" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c35e50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c35e50[];   // 0x01573038 class descriptor

struct Object_c35e50 {
    bool AddTo(Serializer_c35e50* serializer);
};

// @ 0x00c35e50
bool Object_c35e50::AddTo(Serializer_c35e50* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c35e50, L"cGameBundle");
}
