// Serializer registration (0x0103b780): add this object to the serializer as a child with the class descriptor at
// 0x15b8360 and the name L"cSpaceTrading" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_103b780 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_103b780[];   // 0x015b8360 class descriptor

struct Object_103b780 {
    bool AddTo(Serializer_103b780* serializer);
};

// @ 0x0103b780
bool Object_103b780::AddTo(Serializer_103b780* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_103b780, L"cSpaceTrading");
}
