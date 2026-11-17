// Serializer registration (0x00d4b580): add this object to the serializer as a child with the class descriptor at
// 0x15836c8 and the name L"cDramaEventInstanceData" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_d4b580 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_d4b580[];   // 0x015836c8 class descriptor

struct Object_d4b580 {
    bool AddTo(Serializer_d4b580* serializer);
};

// @ 0x00d4b580
bool Object_d4b580::AddTo(Serializer_d4b580* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_d4b580, L"cDramaEventInstanceData");
}
