// Serializer registration (0x00c55190): add this object to the serializer as a child with the class descriptor at
// 0x1575f90 and the name L"cMissionFindAliens" (AddChild 0x695b40).
#include "game/types.h"

struct Serializer_c55190 {
    bool AddChild(unsigned obj, const void* desc, const wchar_t* name);   // 0x00695b40
};
extern const char sDescriptor_c55190[];   // 0x01575f90 class descriptor

struct Object_c55190 {
    bool AddTo(Serializer_c55190* serializer);
};

// @ 0x00c55190
bool Object_c55190::AddTo(Serializer_c55190* serializer)
{
    return serializer->AddChild((unsigned)this, sDescriptor_c55190, L"cMissionFindAliens");
}
