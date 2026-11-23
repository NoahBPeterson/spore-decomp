// @ 0x00a02d80
// virtual slot-2 tail call: mov ecx,[esp+4] / mov eax,[ecx] / mov edx,[eax+8] / jmp edx
struct VT3_00a02d80 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
void FUN_00a02d80(VT3_00a02d80* o) { o->v2(); }
