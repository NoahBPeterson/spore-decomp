// Serializer registration (0x00bbec10): add this object to the serializer as a child with the class descriptor at
// 0x156cf40 and the name L"cTerraformingManager" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_bbec10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_bbec10[];   // 0x0156cf40 class descriptor

struct Object_bbec10 {
    bool AddTo(Serializer_bbec10* serializer);
};

// @ 0x00bbec10
bool Object_bbec10::AddTo(Serializer_bbec10* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_bbec10, L"cTerraformingManager");
}
