// Serializer registration (0x00b2cd50): add this object to the serializer as a child with the class descriptor at
// 0x1568d40 and the name L"cGamePlantManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b2cd50 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b2cd50[];   // 0x01568d40 class descriptor

struct Object_b2cd50 {
    bool AddTo(Serializer_b2cd50* serializer);
};

// @ 0x00b2cd50
bool Object_b2cd50::AddTo(Serializer_b2cd50* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b2cd50, L"cGamePlantManager");
}
