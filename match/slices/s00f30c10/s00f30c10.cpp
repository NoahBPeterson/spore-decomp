// Serializer registration (0x00f30c10): add this object to the serializer as a child with the class descriptor at
// 0x15b00e0 and the name L"cScenarioSim" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_f30c10 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_f30c10[];   // 0x015b00e0 class descriptor

struct Object_f30c10 {
    bool AddTo(Serializer_f30c10* serializer);
};

// @ 0x00f30c10
bool Object_f30c10::AddTo(Serializer_f30c10* serializer)
{
    return serializer->AddChild((unsigned)((char*)this - 0x8), sDescriptor_f30c10, L"cScenarioSim");
}
