// @ 0x00e52a80
// SharedApp (cApp) helper: a vector of resource keys is compacted against the current
// level's resource manager.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef uint32_t ResourceKey;

struct ResourceKeyVector {
    void* mpAllocator;      // +0x00
    int mnSize;             // +0x04
    ResourceKey mKeys[1];   // +0x08
};

// Two subobjects of cApp (0x016b3c04): the key validator at +0x1c and the "nothing left"
// handler at +0xa8.
struct KeyValidator {
    int IsValid(ResourceKey key);          // 0x00b721d0
};
struct EmptyHandler {
    void OnEmpty(void* allocator);         // 0x00b72260
};

struct cApp {
    char pad0[0x1c];
    KeyValidator mValidator;               // +0x1c
    char pad20[0xa8 - 0x1c - sizeof(KeyValidator)];
    EmptyHandler mEmpty;                   // +0xa8
};

extern cApp* gApp;                         // 0x016b3c04

// @ 0x00e52a80
void FUN_00e52a80(ResourceKeyVector* vec)
{
    int i = 0;
    while (i < vec->mnSize) {
        ResourceKey key = vec->mKeys[i];
        KeyValidator* validator = &gApp->mValidator;
        if (!validator->IsValid(key)) {
            int last = --vec->mnSize;
            vec->mKeys[i] = vec->mKeys[last];
            --i;
        }
        ++i;
    }
    if (vec->mnSize == 0)
        gApp->mEmpty.OnEmpty(vec->mpAllocator);
}
