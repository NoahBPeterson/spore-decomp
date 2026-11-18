// @ 0x00c93160
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Factory-style helper from the simulator/resource layer.  The registry object
// it asks is the one keyed by the literal 0x18c6d19 (0x00b20c60, whose .rdata
// neighbours are "Simulator"); the closing notification goes through
// 0x00d51660 ("Simulator/cDramaManager").
//
// Transcribed from the retail bytes:
//   * the call sequence, every immediate, the field offsets (0x34 sub-object
//     vtable, 0x230, 0x238, 0x234, 0x550, 0x18cc) and the vtable slots
//     0x0c / 0x8c are taken from the disassembly and are reliable;
//   * the helpers that take the object in ECX and pop their stack argument are
//     plain member functions: MSVC's thiscall passes `this` in ECX, leaves the
//     argument on the stack and lets the callee pop it (ret 4 / ret 8), which
//     is exactly the retail call shape;
//   * the parameter split is inferred: the vtable[0x8c] call consumes the
//     first, third, fourth and fifth stack slot, the slot before them is only
//     compared against 0x20 (an index/level) and the sixth slot is the owner
//     pointer tested for null;
//   * the body is nested inside `if (found)` returning the object, with a
//     trailing `return 0`, which is the block order retail shows (the cold
//     zero-return block sits after the success epilogue);
//   * the three-pointer temporary is the container whose storage is released at
//     the end of the function (retail reuses its storage for the lookup).

typedef unsigned int uint32_t;

// --- external callees; their call relocations are masked by the checker -----
extern "C" void* __cdecl FUN_00401090();                                  // 0x00401090
extern "C" void* __fastcall FUN_004df420(void* self);                     // 0x004df420 -> self + 0xa4
extern "C" void* __cdecl FUN_00b3d300();                                  // 0x00b3d300 -> [0x0167eae0]
extern "C" int   __cdecl FUN_00b6e050();                                  // 0x00b6e050
extern "C" void* __cdecl FUN_00b3d430();                                  // 0x00b3d430 -> [0x0167eb30]
extern "C" void  __fastcall FUN_00bbc3f0(void* self);                     // 0x00bbc3f0 byte [self+0x3c] = 1
extern "C" void* __cdecl FUN_00d51660();                                  // 0x00d51660 lazy singleton
extern "C" void  __cdecl FUN_00f47380(void* p);                           // 0x00f47380 operator delete[]

// Helpers reached with the object in ECX and one (or two) stack argument(s);
// the callee cleans them (0x00b20c60 / 0x004da330 / 0x00b6f380 / 0x00c8fd50 /
// 0x00d51700 ret 4, 0x00e5c780 ret 8).
struct CRegistry { void* Find(uint32_t id); };                      // 0x00b20c60
struct COwner    { void  Store(const void* tmp); };                 // 0x004da330
struct CSub230   { void  Store(const void* tmp); };                 // 0x00b6f380
struct CSub238   { void* Lookup(void* out, void* tmp); };           // 0x00e5c780
struct CObj      { void  Notify(int flag); };                       // 0x00c8fd50
struct CDrama    { void  Attach(void* arg); };                      // 0x00d51700

// static table the three-pointer temporary is seeded from
extern "C" char DAT_01667bac[];

typedef void* (__thiscall* PFN_V0C)(void* self, uint32_t id);
typedef void  (__thiscall* PFN_V8C)(void* self, void* a, void* b, void* c, void* d);
typedef void  (__thiscall* PFN_V00)(void* self, void* arg);

// virtual slot fetch
#define VFN(p, off) (*(void**)(*(char**)(p) + (off)))

// Temporary handed to 0x004da330 / 0x00b6f380; its three visible fields are
// {begin, end, capacity} of a container-shaped object.  Retail reserves one
// further pointer in the same local (frame is 0x14 = this plus the lookup key)
// and leaves it untouched, so it stays uninitialised here.
struct Tmp3 {
    const char* a; // @0x00  begin
    const char* b; // @0x04  end
    const char* c; // @0x08  capacity (tagged capacity word)
    const char* d; // @0x0c  never written by this function
};

// @ 0x00c93160
extern "C" void* __cdecl FUN_00c93160(void* p1, int index, void* p3, void* p4,
                                      void* p5, void* owner)
{
    if (!owner)
        owner = FUN_004df420(FUN_00401090());

    CRegistry* reg = (CRegistry*)FUN_00b3d300();
    void* found = reg->Find(0x18c6d19u);
    if (found) {
        void* obj = ((PFN_V0C)VFN(found, 0x0c))(found, 0x4f396a66u);
        if (obj) {
            *(void**)((char*)obj + 0x18cc) = owner;
            *(int*)((char*)obj + 0x234) = FUN_00b6e050();
            if ((uint32_t)index < 0x20)
                *(int*)((char*)obj + 0x550) = index;

            ((PFN_V8C)VFN(obj, 0x8c))(obj, p1, p3, p4, p5);

            Tmp3 t;
            t.a = DAT_01667bac;
            t.b = DAT_01667bac;
            t.c = DAT_01667bac + 2;
            ((COwner*)owner)->Store(&t);
            ((CSub230*)((char*)obj + 0x230))->Store(&t);

            // retail pushes &zero first and the address of a second four-byte
            // local second, so &zero is the callee's *last* argument (the slot
            // it zeroes before the lookup).
            int zero = 0;
            void* key;                          // address taken only
            void** res = (void**)((CSub238*)((char*)obj + 0x238))->Lookup(&key, &zero);
            void* value = *(void**)((char*)*res + 0x14);
            ((PFN_V00)VFN((char*)obj + 0x34, 0))((char*)obj + 0x34, value);

            FUN_00bbc3f0(FUN_00b3d430());
            ((CObj*)obj)->Notify(0);
            ((CDrama*)FUN_00d51660())->Attach(obj);

            // the same three pointers are the container's {begin, end,
            // capacity}; retail masks the tagged capacity word before the size
            // test (signed compare, so it never frees the static 2-byte table).
            if ((((int)(t.c - t.a)) & ~1) > 2 && t.a)
                FUN_00f47380((void*)t.a);
        }
        return obj;
    }
    return 0;
}
