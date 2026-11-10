// Slice s00c45120: mission/serialization helper (MSVC 2008 SP1, /O2).
#include "types.h"

// 0x00695b40: link (or find) a child node in a property-list writer.
struct PropertyListWriter {
    bool __thiscall Link(void* pObject, void* pGroup, const wchar_t* pName);   // 0x00695b40
};

// ---------------------------------------------------------------------------------------------
// 0x00c45120: register an object under a group descriptor and a name; always reports success
// ---------------------------------------------------------------------------------------------
// @ 0x00c45120
bool __cdecl FUN_00c45120(void* pWriter, void* pObject)
{
    if (pObject != 0)
        ((PropertyListWriter*)pWriter)->Link(pObject, (void*)0x01574d38, (const wchar_t*)0x0146d14c);
    return true;
}
