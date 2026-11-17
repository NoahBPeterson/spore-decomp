// Serializer registration (0x00e15990): add this object to the serializer as a child with the class descriptor at
// 0x15a4e00 and the name L"cUIMissionCardPanel" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_e15990 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_e15990[];   // 0x015a4e00 class descriptor

struct Object_e15990 {
    bool AddTo(Serializer_e15990* serializer);
};

// @ 0x00e15990
bool Object_e15990::AddTo(Serializer_e15990* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_e15990, L"cUIMissionCardPanel");
}
