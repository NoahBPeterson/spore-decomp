// Slice s00892120: the loader that fills the manager object of s00891220 (flag at +0x10,
// critical section at +0x28, handles at +0x150/+0x154, context pointer at +0x160).
// Under the lock, look the context up, splice the two source ranges in and run the
// subclass hook; any failure destroys the object.  The result flag lives on the stack,
// cleared at entry and set only on the success path.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

// The critical-section helpers are called through their IAT slots: `push &cs;
// call dword ptr [0x13cc2d8]` with no `add esp`, so the callee pops the argument.
typedef void (__stdcall* CsFn)(void*);
extern CsFn g_EnterCS_013cc2d8;   // 0x013cc2d8, ret 4
extern CsFn g_LeaveCS_013cc2dc;   // 0x013cc2dc, ret 4

// 0x008d11f0 context lookup: looks its key up in the store and returns the found record.
extern "C" void* g_store_00892120;
extern "C" void* __cdecl FUN_008d11f0(void* store, const void* key);

// The failure path calls the object's slot-7 virtual (`mov eax,[this]; mov edx,[eax+0x1c];
// call edx`); the base only names that virtual, the concrete layout follows in the subclass.
struct ObjBase_00892120 {
    virtual void v0();  virtual void v1();  virtual void v2();  virtual void v3();
    virtual void v4();  virtual void v5();  virtual void v6();
    virtual void Destroy();                         // vtable slot 7 (offset +0x1c)
};

struct Obj_00892120 : ObjBase_00892120 {
    char   pad04[0x10 - 0x04];
    void*  m10;                                     // +0x010 context
    char   pad14[0x28 - 0x14];
    char   cs28[0x18];                              // 0x028 critical section (enter/leave at +0x13cc2d8/2dc)
    char   pad40[0x150 - 0x40];
    void*  m150;                                    // +0x150 looked-up context (0x008d11f0)
    void*  m154;                                    // +0x154 spliced list (0x008cc760)
    char   pad158[0x160 - 0x158];
    char   m160[4];                                 // +0x160 lookup key

    bool Load(void* a, void* b, void* c);           // @ 0x00892120
    bool Hook(void* c);                             // 0x00891b10
};

// 0x008cc760 list splice into a fresh list: the engine hands the two source ranges and
// an extra situation word (see s0088c760).
typedef void* (__thiscall* SpliceFn)(void* self, void* b, int x, void* key);

// @ 0x00892120
bool Obj_00892120::Load(void* a, void* b, void* c)
{
    char ok = 0;
    g_EnterCS_013cc2d8(cs28);
    if (m10 || !a) {
        Destroy();
        goto done;
    }
    m150 = FUN_008d11f0(g_store_00892120, m160);
    if (!m150) {
        Destroy();
        goto done;
    }
    m154 = ((SpliceFn)((void*)0x8cc760))(a, b, 0, m160);
    if (!m154 || !Hook(c)) {
        Destroy();
        goto done;
    }
    ok = 1;
done:
    g_LeaveCS_013cc2dc(cs28);
    return ok != 0;
}
