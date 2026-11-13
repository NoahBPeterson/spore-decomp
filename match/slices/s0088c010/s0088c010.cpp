#include "game/types.h"

extern bool __cdecl HasAttr_006ab760(void* node, int key);

// @ 0x0088c010
void* __stdcall FindNode_0088c010(void* node, int* key, int)
{
    if (node) {
        int k = *key;
        do {
            if (HasAttr_006ab760(node, k))
                return node;
            node = *(void**)((char*)node + 0x4cc);
        } while (node);
    }
    return 0;
}
