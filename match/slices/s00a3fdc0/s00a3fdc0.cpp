// @ 0x00a3fdc0
// calls arg0->field_0x28's method (thiscall, 0xa3fd70), then calls the cdecl helper
// 0xa49650 with (field_0x28, 0x34): field_0x28 is re-read after the call, so the load
// is not cached across it.
struct Obj28_00a3fdc0 {
    void Fwd_00a3fd70();                        // 0xa3fd70 (__thiscall, no args)
};

extern void Fun_00a49650(void* a, int b);       // 0xa49650 (__cdecl, 2 args)

struct Holder_00a3fdc0 {
    char pad_0x28[0x28];
    void* f28;
};

void FUN_00a3fdc0(Holder_00a3fdc0* p) {
    ((Obj28_00a3fdc0*)p->f28)->Fwd_00a3fd70();
    Fun_00a49650(p->f28, 0x34);
}
