// Serializer registration (0x00b22580): add this object to the serializer as a child with the class descriptor at
// 0x1568788 and the name L"cGameNounManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_b22580 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_b22580[];   // 0x01568788 class descriptor

struct Object_b22580 {
    bool AddTo(Serializer_b22580* serializer);
};

// @ 0x00b22580
bool Object_b22580::AddTo(Serializer_b22580* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x4), sDescriptor_b22580, L"cGameNounManager");
}
