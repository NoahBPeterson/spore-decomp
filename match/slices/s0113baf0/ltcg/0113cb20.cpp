// Link-time callee contracts for Delay::Release (0x0113cb20), compiled with the original VC7.1 /GL+/LTCG lane.
// Concrete timer/list/allocator effects and calling conventions come from native functions 0x0114d770,
// 0x0112dad0/0x0112d940,0x0112c850,0x01133a60 and0x01133c30; helper bodies are not claimed byte-exact.
// Exports retain native standard conventions, and mutable singleton storage gives its operand a unique link-map identity.
#include "types.h"
uint8_t* g_sys; // actual mutable external singleton storage, mapped in DLL for independent operand audit
#pragma comment(linker, "/EXPORT:?g_sys@@3PAEA,DATA")
struct Ctx {
    uint8_t b[0x800];

    // callees (other TUs) — declared, mapped by address
    void     PlugInInit16();                 // 0x114f4f0  PlugIn::Initialize<Pan3D>
    void     InitSndPlayer1();               // 0x112dbb0  PlugIn::Initialize<SndPlayer1>
    void*    SysAlloc(uint32_t, const char*, int, int); // 0x112c820 System::Alloc
    bool     AddTimer(void*, void*, void*, const char*, int, int); // 0x112d8e0
    void     RemoveTimer(void*);             // 0x112dad0
    void     SysLock();                      // 0x112c600
    void     SysUnlock();                    // 0x112c620
    uint32_t SysGetDec();                    // 0x112dc80
    void*    RegGet(void*);                  // 0x1133ed0
    void*    DecoderFactory(void*, uint8_t, int, void*); // 0x1133fc0
    uint32_t SubFeed(void*, int, int, int, int, int); // 0x114c8c0
    void     Ctor1153b00();                  // 0x1153b00
    void     Ctor11546f0();                  // 0x11546f0
    void     Ctor11547b0();                  // 0x11547b0
    void     D770();                         // 0x114d770
    void     D730();                         // 0x114d730
    bool     DelayLineInit(int, int, uint32_t); // 0x114d7b0
    void     D840(int);                      // 0x114d840
    void     C1154ee0();                     // 0x1154ee0
    void     C1154ca0(void*);                // 0x1154ca0
    uint64_t Get64();                        // 0x68c140

    // slice functions
    void     FUN_0113bb30();
    bool     FUN_0113bb90(int);
    bool     FUN_0113bc60();
    void     FUN_0113bf10(int, uint32_t*);
    void     FUN_0113ca00(int, uint8_t*);
    void     FUN_0113cb20();
    uint8_t* FUN_0113cbb0(uint8_t);
    bool     FUN_0113cd80(uint8_t*);
    uint8_t* FUN_0113cdd0(uint8_t);
    void     FUN_0113ce00();
};

// Native observed effects, not opaque stand-ins: all concrete offsets below are checked against the original.
struct Allocator {
    virtual void Slot0() = 0; virtual void Slot1() = 0; virtual void Slot2() = 0;
    virtual void Free(void* p, int flags) = 0; // native indirectslot3; ordinarythiscallret8, actual allocator effects unknown in original too
};
struct FreeSystem { unsigned char raw[0x18]; void Free(void* p, int allocator); };
struct TimerHandle { void* node; void* callback; void* context; const char* name; unsigned int ticks; unsigned char stage; unsigned char visibility; };
struct Collection {
    struct Node { Node* next; Node* prev; void** owner; };
    void* first; void* last; int blocks; Node* freeHead; Node* usedHead; int size; int capacity;
    Node* UnlinkUsed(void** owner); Node* RemoveNode(void** owner);
};
struct TimerManager {
    Collection collections[2]; float callbackTime; TimerHandle* current;
    int currentCollection; Collection::Node* deferred;
    void RemoveTimer(TimerHandle* h);
};
#pragma comment(linker, "/EXPORT:?FUN_0113cb20@Ctx@@QAEXXZ")
__declspec(noinline) void FreeSystem::Free(void* p, int allocator)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    Allocator* a = allocator ? (Allocator*)allocator : *(Allocator**)(raw + 0x14);
    a->Free(p, 0);
}
__declspec(noinline) void Ctx::D770()
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    void* p = *(void**)b;
    if (p) { ((FreeSystem*)g_sys)->Free(p, 0); *(void**)b = 0; }
    *(unsigned*)(b + 8) = 0; *(unsigned*)(b + 4) = 0; *(unsigned*)(b + 12) = 0;
}
__declspec(noinline) Collection::Node* Collection::UnlinkUsed(void** owner)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    Node* n = (Node*)*owner; *owner = 0; n->owner = 0; return n;
}
__declspec(noinline) Collection::Node* Collection::RemoveNode(void** owner)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    Node* n = (Node*)*owner; *owner = 0; n->owner = 0;
    if (n == usedHead) usedHead = n->next;
    if (n->prev) n->prev->next = n->next;
    if (n->next) n->next->prev = n->prev;
    n->next = freeHead; n->prev = 0;
    if (freeHead) freeHead->prev = n;
    freeHead = n; --size; return n;
}
__declspec(noinline) void TimerManager::RemoveTimer(TimerHandle* h)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    if (h == current) {
        currentCollection = h->stage;
        deferred = collections[h->stage].UnlinkUsed(&h->node);
    } else if (h->stage != 3) {
        collections[h->stage].RemoveNode(&h->node);
    }
    h->stage = 3; h->ticks = 0;
}
__declspec(noinline) void Ctx::RemoveTimer(void* handle)
{
#pragma comment(linker, "/EXPORT:" __FUNCDNAME__)
    ((TimerManager*)(b + 0x60))->RemoveTimer((TimerHandle*)handle);
}
// No alias restriction or fake volatile touches; same object/node/global/allocator escape graph as native.
typedef char CheckCollection[sizeof(Collection)==0x1c?1:-1];
typedef char CheckTimerManager[sizeof(TimerManager)==0x48?1:-1];
typedef char CheckTimerHandle[sizeof(TimerHandle)==0x18?1:-1];
