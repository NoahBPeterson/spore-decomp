// Serializer registration (0x00e194d0): add this object to the serializer as a child with the class descriptor at
// 0x15a4f70 and the name L"cUIMissionLogManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_e194d0 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_e194d0[];   // 0x015a4f70 class descriptor

struct Object_e194d0 {
    bool AddTo(Serializer_e194d0* serializer);
};

// @ 0x00e194d0
bool Object_e194d0::AddTo(Serializer_e194d0* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_e194d0, L"cUIMissionLogManager");
}
