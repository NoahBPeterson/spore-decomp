// slice s0070a5b0: cLightingManager tree iteration / removal and cLightingWorld::Update.
#include <new>
#include "types.h"

void __cdecl EastlFree(void* p);                       // 0x00F47380
void* __cdecl RBTreeIncrement(void* node);             // 0x00921580
void  __cdecl RBTreeErase(void* node, void* anchor);   // 0x00921880

struct cLightingWorld {
    void Update(uint32_t param);
    void Shutdown();
};

struct RBTree {
    void Find(void* out, const void* key);   // 0xE5C780
};

struct cLightingManager {
    char pad[0x100];
    void UpdateAll(uint32_t param);
    void RemoveLightingWorld(uint32_t key);
};

// @ 0x0070ae40
void cLightingManager::UpdateAll(uint32_t param)
{
    for (char* it = *(char**)((char*)this + 0x34); it != (char*)this + 0x30;
         it = (char*)RBTreeIncrement(it)) {
        (*(cLightingWorld**)(it + 0x14))->Update(param);
    }
}

// @ 0x0070ae70
void cLightingManager::RemoveLightingWorld(uint32_t key)
{
    char* it;
    ((RBTree*)((char*)this + 0x2c))->Find(&it, &key);
    if (it != (char*)this + 0x30) {
        (*(cLightingWorld**)(it + 0x14))->Shutdown();
        --*(int*)((char*)this + 0x40);
        RBTreeIncrement(it);
        RBTreeErase(it, (char*)this + 0x30);
        cLightingWorld* w = *(cLightingWorld**)(it + 0x14);
        if (w)
            ((void(__thiscall*)(cLightingWorld*))(*(void***)w)[1])(w);
        EastlFree(it);
    }
}

// @ 0x0070a5b0  (2189-byte evaluator, skeleton only; kept as a distinct name so
// cLightingManager::UpdateAll above still emits the out-of-line call)
void UpdateWorldImpl(cLightingWorld* self, uint32_t param)
{
    (void)self;
    (void)param;
}
