// Serializer registration (0x00ce4f60): add this object to the serializer as a child with the class descriptor at
// 0x1581000 and the name L"cTribePlanner" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_ce4f60 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_ce4f60[];   // 0x01581000 class descriptor

struct Object_ce4f60 {
    bool AddTo(Serializer_ce4f60* serializer);
};

// @ 0x00ce4f60
bool Object_ce4f60::AddTo(Serializer_ce4f60* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_ce4f60, L"cTribePlanner");
}
