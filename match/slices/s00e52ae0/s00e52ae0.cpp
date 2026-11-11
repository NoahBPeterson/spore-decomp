// Slice s00e52ae0: global-object helper calling the object at +0xa8 of the excerpt-reader
// singleton (0x16b3c04): the round's element (0x00b72230, queried through a cursor that
// carries the running size) is handed to 0x00e52a80 together with that size, until the
// iterator is done.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern void* g_object_016b3c04;              // 0x016b3c04 singleton (owns the object at +0xa8)

struct Reader {
    char  pad00[0xa8];
    int   it;                                // +0xa8 iterator cursor / size

    void  Begin();                                  // 0x00e31100
    void* Next(int* cursor);                        // 0x00b72230 (element, or null when done)
};

extern void __cdecl FUN_00e52a80(void* element, float size);      // 0x00e52a80 add element

// @ 0x00e52ae0
void FUN_00e52ae0()
{
    int* cursor = &((Reader*)g_object_016b3c04)->it;
    ((Reader*)g_object_016b3c04)->Begin();
    for (;;) {
        void* element = ((Reader*)((char*)g_object_016b3c04 + 0xa8))->Next(cursor);
        if (!element)
            break;
        FUN_00e52a80(element, *(float*)cursor);
    }
}
