// Slice s00e52ae0: global-object helper calling the object at +0xa8 of the excerpt-reader
// singleton (0x16b3c04): each element (0x00b72230, walked with a local iterator) is handed
// to 0x00e52a80 together with the size argument, until the iterator is done.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern void* g_object_016b3c04;              // 0x016b3c04 singleton (owns the object at +0xa8)

// The +0xa8 object of the singleton: an iterator source.
struct ExcerptList {
    int   Begin();                                  // 0x00e31100 (first iterator)
    void* Next(int* it);                            // 0x00b72230 (element, or null when done)
};

extern void __cdecl FUN_00e52a80(void* element, float size);      // 0x00e52a80 add element

// @ 0x00e52ae0
void FUN_00e52ae0(float size)
{
    int it = ((ExcerptList*)((char*)g_object_016b3c04 + 0xa8))->Begin();
    for (;;) {
        ExcerptList* l = (ExcerptList*)((char*)g_object_016b3c04 + 0xa8);
        void* element = l->Next(&it);
        if (!element) break;
        FUN_00e52a80(element, size);
    }
}
