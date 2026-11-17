// Serializer registration (0x00d53380): add this object to the serializer as a child with the class descriptor at
// 0x1583d30 and the name L"cPosseSimulator" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d53380 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d53380[];   // 0x01583d30 class descriptor

struct Object_d53380 {
    bool AddTo(Serializer_d53380* serializer);
};

// @ 0x00d53380
bool Object_d53380::AddTo(Serializer_d53380* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_d53380, L"cPosseSimulator");
}
