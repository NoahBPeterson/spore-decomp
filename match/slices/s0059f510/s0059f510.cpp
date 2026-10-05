// Slice s0059f510 -- SP::cSPEditorBlockAbilities layout vector + ability helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast.
#include "types.h"

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  EASTL_deallocate(void* p);   // 0x00f47380

// ---------------------------------------------------------------------------
// cSPUILayout: 0x18-byte record
// ---------------------------------------------------------------------------
struct cSPUILayout {
    char pad[0x18];
    cSPUILayout();                 // 0x00810000
    ~cSPUILayout();                // 0x00811fe0
    void Shutdown(int flag);       // 0x00811ad0
};

struct UILayoutVector {
    cSPUILayout* mpBegin;
    cSPUILayout* mpEnd;
    cSPUILayout* mpCapacity;
    uint32_t     mAlloc[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    cSPUILayout* erase(cSPUILayout* first, cSPUILayout* last);   // 0x0059f4a0
    void resize(uint32_t newSize);                               // 0x0059f950
};

struct cSPEditorBlockAbilities {
    char          pad[0x24];
    UILayoutVector mLayouts;    // +0x24
    void ShutdownLayouts();     // 0x0059f900
};

// 0xc4-byte ability record whose first field is an object with a vtable
struct AbilityRec {
    void* mpObject;     // +0x0
    char  pad[0xc4 - 4];
};

struct AbilityVector {
    AbilityRec* mpBegin;
    AbilityRec* mpEnd;
    AbilityRec* mpCapacity;
    uint32_t    mAlloc[2];
    int EraseRange(AbilityRec* first, AbilityRec* last);   // 0x0059faa0
};

// 0x18-byte UI-layout constructor (as called from resize)
cSPUILayout* ConstructLayout(cSPUILayout* p, int arg);   // 0x00810020
void VectorInsertFill(UILayoutVector* v, cSPUILayout* pos, uint32_t count, cSPUILayout* value);  // 0x0059f510
void MoveLayouts(UILayoutVector* v, cSPUILayout* dst, cSPUILayout* src);   // 0x0059ee20
cSPUILayout* MoveLayoutArray(UILayoutVector* v, cSPUILayout* out, cSPUILayout* a, cSPUILayout* b, cSPUILayout* c); // 0x0059ef30

// ability helpers
AbilityRec* FindAbilitySlot(AbilityRec* a, AbilityRec* b, AbilityRec* c);  // 0x0059f740

// ===========================================================================
// @ 0x0059f900
void cSPEditorBlockAbilities::ShutdownLayouts()
{
    UILayoutVector* v = &mLayouts;
    int n = (int)(((char*)v->mpEnd - (char*)v->mpBegin) / 0x18);
    if (n > 0) {
        int offset = 0;
        do {
            ((cSPUILayout*)((char*)v->mpBegin + offset))->Shutdown(1);
            offset += 0x18;
        } while (--n != 0);
    }
    v->erase(v->mpBegin, v->mpEnd);
}

// ===========================================================================
// @ 0x0059f950
void UILayoutVector::resize(uint32_t newSize)
{
    uint32_t cur = (uint32_t)(((char*)mpEnd - (char*)mpBegin) / 0x18);
    if (cur < newSize) {
        char tmp[0x18];
        ConstructLayout((cSPUILayout*)tmp, 0);
        VectorInsertFill(this, mpEnd, newSize - cur, (cSPUILayout*)tmp);
        ((cSPUILayout*)tmp)->~cSPUILayout();
    } else {
        erase(mpBegin + newSize, mpEnd);
    }
}

// ===========================================================================
// @ 0x0059f9e0
struct VehicleAbilities {
    void* vptr0;      // +0x0
    void* vptr1;      // +0x4
    char  pad[0x61 - 0x8];
    unsigned char b61, b62, b63;
    int   m64;        // +0x64
    int   m68;        // +0x68
    int   m6c;        // +0x6c
    VehicleAbilities();
};

VehicleAbilities::VehicleAbilities()
{
    m64 = 2;
    b61 = 1;
    b62 = 0;
    b63 = 1;
    m68 = 0xf56d252d;
    m6c = 0x3c02fae0;
}

// ===========================================================================
// @ 0x0059faa0
int AbilityVector::EraseRange(AbilityRec* first, AbilityRec* last)
{
    AbilityRec* p = FindAbilitySlot(first, mpEnd, last);
    AbilityRec* end = mpEnd;
    for (; p < end; p = (AbilityRec*)((char*)p + 0xc4)) {
        void** vtbl = *(void***)p->mpObject;
        void* fn = *(void**)((char*)vtbl + 8);
        (*(void(__thiscall**)(void*, int))fn)(p->mpObject, 0);
    }
    mpEnd = (AbilityRec*)((char*)mpEnd + (((char*)last - (char*)first) / 0xc4) * 0xc4);
    return (int)first;
}

// ===========================================================================
// @ 0x0059f510
void VectorInsertFill(UILayoutVector* v, cSPUILayout* pos, uint32_t count, cSPUILayout* value)
{
    (void)v; (void)pos; (void)count; (void)value;
}

// @ 0x0059f7c0
int SortAbilities(void* a, void* b)
{
    (void)a; (void)b;
    return 0;
}

// @ 0x0059fa50
void* ScalarDeletingDtor(void* p, unsigned char flags)
{
    (void)flags;
    return p;
}

// @ 0x0059fc60
int BlockGetAbilities(void* block, void* out)
{
    (void)block; (void)out;
    return 0;
}
