// Slice s0100a640 -- SP::cSPSimulatorSpaceGame, embassy-table loader.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
//
// Reads an element count from the owning object's stream, clears the embassy
// vector, reserves room and appends that many default embassy records.  Each
// record is built as a 0x14-byte element (two vtables + three fields); the
// owning object is handed to vtable slot 5 of the record, i.e. the record's
// "initialise for this owner" call.  The trailing vtable slot 7 call on the
// owner is the tail call retail ends with (jmp [eax+0x1c]).
#include "types.h"

// 0x14-byte element of the embassy vector (see slice s0100a7c0).
struct EmbElem {
    void*   m00;        // 0x01495400 (vtable)
    void*   m04;        // 0x0149bad8 (second base vtable)
    int32_t m08;
    int32_t m0C;
    int32_t m10;
};

struct EmbVec {
    EmbElem* mpBegin;
    EmbElem* mpEnd;
    EmbElem* mpCapacity;

    void Clear(EmbElem* first, EmbElem* last);                  // 0x01008850
    void Reserve(uint32_t count);                               // 0x01008760
    void PushSlow(EmbElem* end, const EmbElem* value);           // 0x01009c60
};

// EA::IO stream read of one little-endian int32.
bool __cdecl ReadInt32(void* stream, int32_t* value, unsigned count, int endian);   // 0x0093a780

// The element's vtable (0x01495400) slot 5: initialise the record for an owner.
typedef void (__thiscall* EmbElemInitFn)(EmbElem*, void*);
static EmbElemInitFn g_embElemInit = (EmbElemInitFn)0x01495414;

// @ 0x0100a640
void LoadEmbassyList(void* owner, EmbVec* list)
{
    list->Clear(list->mpBegin, list->mpEnd);

    // owner vtable slot 8: the object's stream accessor
    typedef void* (__thiscall* OwnerStreamFn)(void*);
    OwnerStreamFn getStream = (OwnerStreamFn)(*(void***)owner)[8];

    int32_t count = 0;

    void* stream = getStream(owner);
    void* io     = ((void* (__thiscall*)(void*))(*(void***)stream)[6])(stream);

    ReadInt32(io, &count, 1, 0);

    list->Reserve((uint32_t)count);

    uint32_t i = 0;
    while (i < (uint32_t)count) {
        EmbElem elem;
        elem.m08 = 0;
        elem.m00 = (void*)0x1495400;
        elem.m04 = (void*)0x149bad8;
        elem.m0C = -1;
        elem.m10 = 1000;

        g_embElemInit(&elem, owner);

        if (list->mpEnd < list->mpCapacity) {
            EmbElem* slot = list->mpEnd++;
            if (slot != 0) {
                // the inlined copy stamps the intermediate vtable first (it is
                // observable in retail, so keep it a volatile store)
                *(void* volatile*)&slot->m04 = (void*)0x13ec458;
                slot->m08 = 0;
                slot->m00 = (void*)0x1495400;
                slot->m04 = (void*)0x149bad8;
                slot->m0C = elem.m0C;
                slot->m10 = elem.m10;
            }
        } else {
            list->PushSlow(list->mpEnd, &elem);
        }
        ++i;
    }

    return ((void (__thiscall*)(void*))(*(void***)owner)[7])(owner);
}
