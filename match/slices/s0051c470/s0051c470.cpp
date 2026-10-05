// Slice 4: Skinner::PaintSystem ctor/dtor cluster and small EASTL refcount/list helpers.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
#include <intrin.h>

int   GetPaintSystem();                                   // 0x00401080
void  FUN_005173a0(void* p);                              // 0x005173a0
void* EA_alloc(unsigned size, const char* name, int a, int b, int c, int d); // 0x00f473a0
void* BakeSprites_ctor(void* p);                          // 0x007b00f0
void  FUN_004039f0(void* p);                              // 0x004039f0
void  EASTL_allocator_deallocate(void* p);                // 0x00f47380
void  VectorAutoRef_erase(void* first, void* last, void* out); // 0x0042f530

extern void* g_vtblSkinnerPaintSystem;   // 0x013eb394
extern void* g_vtblLocaleChange;         // 0x013eb918
extern void* g_vtblSimCreatureAbility;   // 0x013ef094
extern void* g_vtblEditorResource;       // 0x013eb938
extern void* g_vtblPaintA;               // 0x013f1b80
extern void* g_vtblPaintB;               // 0x013f1b74
extern void* g_vtblPaintC;               // 0x013f1b5c
extern void* g_vtblPaintD;               // 0x013f1b58

// 0x0c-byte header then an atomic refcount (EA::Thread::AtomicInt<int>).
struct RefCounted {
    uint32_t mvtbl; uint32_t pad04; uint32_t pad08;
    volatile long mnRefCount;              // +0x0c
    int AddRef();
};

// Base subobjects of the MI EditorResource.
struct BaseEditor { void dtor(); };

struct PaintSystem {
    PaintSystem(int kind, void* a, void* b, char c, void* d, char e, char f);
    void dtor();
};

struct DList { void adv(); };
struct EditorResource { void* deleting_dtor(unsigned flags); };
struct AutoRefVector { void* erase(void* pos); };

struct ListIter { int* p; };

// PARTIAL marker for 0051c640.
struct SkinTexMsg { bool HandleMessage(unsigned msg, void** out); };

// @ 0x0051c620 int RefCounted::AddRef()
int RefCounted::AddRef()
{
    return (int)_InterlockedIncrement(&mnRefCount);
}

// @ 0x0051c470 ??0PaintSystem@Skinner@@...
PaintSystem::PaintSystem(int kind, void* a, void* b, char c, void* d, char e, char f)
{
    *(void**)this = &g_vtblSkinnerPaintSystem;
    *(void**)((char*)this + 4) = &g_vtblLocaleChange;
    ((BaseEditor*)((char*)this + 8))->dtor();   // inlined base ctor
    *(void**)this = &g_vtblPaintA;
    *(void**)((char*)this + 4) = &g_vtblPaintB;
    *(void**)((char*)this + 8) = &g_vtblPaintC;
    *(void**)((char*)this + 0xc) = &g_vtblPaintD;
    *(void**)((char*)this + 0x18) = a;
    *(void**)((char*)this + 0x1c) = b;
    *(int*)((char*)this + 0x20) = 0;
    *(void**)((char*)this + 0x24) = d;
    *(char*)((char*)this + 0x28) = e;
    *(char*)((char*)this + 0x29) = f;
    *(char*)((char*)this + 0x2a) = c;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x30) = 0;
    *(int*)((char*)this + 0x34) = 0;
    *(int*)((char*)this + 0x38) = 0;
    *(int*)((char*)this + 0x3c) = 0;
    *(int*)((char*)this + 0x40) = 0;
    *(int*)((char*)this + 0x44) = 0;
    *(int*)((char*)this + 0x48) = 0;
    int ps = GetPaintSystem();
    int mat = *(int*)(ps + 0xc);
    void* mem = EA_alloc(0x20, "Skinner", 0, 0, 0, 0);
    void* bs = 0;
    if (mem != 0)
        bs = BakeSprites_ctor(mem);
    void** slot = (void**)((char*)this + 0x30);
    if (bs != *slot) {
        void* old = *slot;
        if (bs != 0)
            (*(void(__thiscall**)(void*))(((void**)*(void**)bs)[0]))(bs);
        *slot = bs;
        if (old != 0)
            (*(void(__thiscall**)(void*))((*(void***)old)[1]))(old);
    }
    if (mat != 0 && *(int*)(mat + 0x10 + kind * 4) != 0)
        *(void**)((char*)this + 0x20) = *(void**)(*(int*)(mat + 0x10 + kind * 4) + 0x60);
}

// @ 0x0051d010 PaintSystem dtor (base-vtable restore)
void PaintSystem::dtor()
{
    if (*(int*)((char*)this + 0x34) != 0)
        FUN_004039f0(*(void**)((char*)this + 0x34));
    if (*(int*)((char*)this + 0x30) != 0)
        (*(void(__thiscall**)(void*))((*(void***)*(void**)((char*)this + 0x30))[1]))(*(void**)((char*)this + 0x30));
    *(void**)((char*)this + 0x0c) = &g_vtblSimCreatureAbility;
    *(void**)((char*)this + 0x08) = &g_vtblEditorResource;
    *(void**)((char*)this + 0x04) = &g_vtblLocaleChange;
    *(void**)this = &g_vtblSkinnerPaintSystem;
}

// @ 0x0051d090 EditorResource scalar deleting dtor
void* EditorResource::deleting_dtor(unsigned flags)
{
    *(void**)((char*)this + 4) = &g_vtblSimCreatureAbility;
    *(void**)this = &g_vtblEditorResource;
    if ((flags & 1) != 0)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x0051d140 intrusive-list node advance
void DList::adv()
{
    *(int*)this = *(int*)(*(int*)this + 0x10);
    while (*(int*)this == 0) {
        *(int*)((char*)this + 4) = *(int*)((char*)this + 4) + 4;
        *(int*)this = **(int**)((char*)this + 4);
    }
}

// @ 0x0051d270 eastl::vector<AutoRefCount<...>>::erase one element
void* AutoRefVector::erase(void* pos)
{
    if ((char*)pos + 4 < *(char**)((char*)this + 4)) {
        char b0 = 0, b1 = 0, b2 = 0;
        (void)b0; (void)b1; (void)b2;
        VectorAutoRef_erase((char*)pos + 4, *(void**)((char*)this + 4), pos);
    }
    char* end = *(char**)((char*)this + 4) - 4;
    *(char**)((char*)this + 4) = end;
    void** node = (void**)end;
    if (*node != 0)
        (*(void(__thiscall**)(void*))((*(void***)*node)[1]))(*node);
    return pos;
}

// @ 0x0051c640 cSkinpaintTextureExtractor::HandleMessage  -- PARTIAL skeleton
bool SkinTexMsg::HandleMessage(unsigned msg, void** out)
{
    (void)msg; (void)out;
    return false;
}
