// Slice s00a37320 - audio property update: dispatches on an id and pushes a group
// of parameters into the EA::Audio system obtained from GetSystemAT.
// Compiled with /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// External callees (annotations bind the reference to the original target).
// ---------------------------------------------------------------------------
void* __cdecl GetSystemAT();              // 0xa206f0 EA::Audio::GetSystemAT

#define VFN(p, off) ((*(void***)(p))[(off) / 4])

typedef void (__thiscall* VFn1)(void*, unsigned int);
typedef void (__thiscall* VFn2)(void*, unsigned int, unsigned int);
typedef void (__thiscall* VFn2f)(void*, unsigned int, float);
typedef void (__thiscall* VFn0)(void*);

// Stand-in for the owning object: only the two members this function touches
// are named. 0x20 is the audio handle handed to the system, 0x2c a float value
// cached when the id selects that path.
struct cAudioPropertyOwner {
    char  pad_00[0x20];
    void* field_20;
    char  pad_24[8];
    float field_2c;

    bool Update(int id, const float* value, void* unused);
};

// @ 0x00a37320
bool __thiscall cAudioPropertyOwner::Update(int id, const float* value, void* unused)
{
    switch (id) {
    case 21:
        if (field_20 != 0) {
            void* sys = GetSystemAT();
            if (sys != 0) {
                ((VFn1)VFN(sys, 0x38))(sys, 0x03475376u);
                ((VFn2)VFN(sys, 0x40))(sys, 0x03475385u, (unsigned int)field_20);
                ((VFn2)VFN(sys, 0x40))(sys, 0x034753a7u, 0xc57f4567u);
                ((VFn2f)VFN(sys, 0x3c))(sys, 0x034753aau, *value);
                ((VFn0)VFN(sys, 0x58))(sys);
            }
        }
        return true;

    case 15:
        field_2c = *value;
        return true;

    case 1:
        if (field_20 != 0) {
            void* sys = GetSystemAT();
            if (sys != 0) {
                ((VFn1)VFN(sys, 0x38))(sys, 0x03475376u);
                ((VFn2)VFN(sys, 0x40))(sys, 0x03475385u, (unsigned int)field_20);
                ((VFn2)VFN(sys, 0x40))(sys, 0x034753a7u, 0x70e47545u);
                ((VFn2f)VFN(sys, 0x3c))(sys, 0x034753aau, *value);
                ((VFn0)VFN(sys, 0x58))(sys);
            }
        }
        return true;
    }

    return false;
}
