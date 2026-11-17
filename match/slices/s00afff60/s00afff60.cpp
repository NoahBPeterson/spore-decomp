// Serializer registration (0x00afff60): add this object to the serializer as a child with the class descriptor at
// 0x167b578 and the name L"cTreeData" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_afff60 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_afff60[];   // 0x0167b578 class descriptor

struct Object_afff60 {
    bool AddTo(Serializer_afff60* serializer);
};

// @ 0x00afff60
bool Object_afff60::AddTo(Serializer_afff60* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_afff60, L"cTreeData");
}
