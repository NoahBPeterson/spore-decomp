// Slice s00e84850 -- UI layout name initialisation from a source range and the
// window-manager element accessor.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

extern "C" void* __cdecl memcpy_(void* pDest, const void* pSrc, unsigned int size);

// Source range describing a layout name (the two char pointers are the range).
struct tNameSource {
    const char* mpFirst;                                 // +0x00
    const char* mpLast;                                  // +0x04
    uint8_t     pad008[8];                               // +0x08 .. +0x0f
    uint32_t    mField10;                                // +0x10
    uint32_t    mField14;                                // +0x14
};

// Destination: an eastl string followed by the two copied dwords.
class cLayoutName {
public:
    cLayoutName* FUN_00e84850(tNameSource* pSource);

    // eastl::basic_string<char> range initialisation (external).
    void RangeInitialize(int32_t size);                  // 0x00475ab0

    char*     mpBegin;                                   // +0x00
    char*     mpEnd;                                     // +0x04
    char*     mpCapacity;                                // +0x08
    uint8_t   pad00c[4];                                 // +0x0c
    uint32_t  mField10;                                  // +0x10
    uint32_t  mField14;                                  // +0x14
};

// UI element: the window returns a pointer to its link body, which lives four
// bytes into the element.
class cHeaderPart {
public:
    uint32_t mFlags;                                     // +0x00
};

class cLinkBody {
public:
    uint8_t mPayload[0x10];                              // +0x000
};

class cUIElement : public cHeaderPart, public cLinkBody {
public:
    void FUN_00812d90();                                 // 0x00812d90
};

class cWindow {
public:
    virtual void v000();                                 // +0x00
    virtual cLinkBody* GetLink();                        // +0x04
};

extern cWindow* __cdecl WindowManager();                 // 0x0067caa0

// @ 0xe84850 cLayoutName::FUN_00e84850
cLayoutName* __thiscall cLayoutName::FUN_00e84850(tNameSource* pSource)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    int32_t length = (int32_t)(pSource->mpLast - pSource->mpFirst);
    RangeInitialize(length + 1);
    memcpy_(mpBegin, pSource->mpFirst, (unsigned int)length);
    mpEnd = mpBegin + length;
    *mpEnd = 0;
    mField10 = pSource->mField10;
    mField14 = pSource->mField14;
    return this;
}

// @ 0xe848c0 FUN_00e848c0
void __cdecl FUN_00e848c0()
{
}

// @ 0xe84940 DoNukeSubtree
void __cdecl DoNukeSubtree()
{
}

// @ 0xe84a20 FUN_00e84a20
void __cdecl FUN_00e84a20()
{
}

// @ 0xe84b20 FUN_00e84b20
void __cdecl FUN_00e84b20()
{
}

// @ 0xe84bf0 FUN_00e84bf0
void __cdecl FUN_00e84bf0()
{
}

// @ 0xe84c80 FUN_00e84c80
void __cdecl FUN_00e84c80()
{
}

// @ 0xe84d90 FUN_00e84d90
void __cdecl FUN_00e84d90()
{
}

// @ 0xe84e40 FUN_00e84e40
void __cdecl FUN_00e84e40()
{
}

// @ 0xe84f30 SP::GetPollinatedCell
void __cdecl GetPollinatedCell()
{
}

// @ 0xe85190 FUN_00e85190
void __cdecl FUN_00e85190()
{
    cLinkBody* pLink = WindowManager()->GetLink();
    cUIElement* pElement = pLink ? (cUIElement*)pLink : 0;
    pElement->FUN_00812d90();
}

// @ 0xe851c0 JacobiDecompose
void __cdecl JacobiDecompose()
{
}

// @ 0xe853c0 ComputeCenterOfMass
void __cdecl ComputeCenterOfMass()
{
}
