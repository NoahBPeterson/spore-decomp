// Serializer registration (0x00bfee10): add this object to the serializer as a child with the class descriptor at
// 0x1570a60 and the name L"cCommodityNode" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bfee10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bfee10[];   // 0x01570a60 class descriptor

struct Object_bfee10 {
    bool AddTo(Serializer_bfee10* serializer);
};

// @ 0x00bfee10
bool Object_bfee10::AddTo(Serializer_bfee10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bfee10, L"cCommodityNode");
}
