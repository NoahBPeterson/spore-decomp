// @ 0x008de1c0
// cdecl: the object (second argument) performs its vtable call at slot 2 (offset 8)
// with (first argument, the global at 0x1436abc, 1) as stack arguments; the return
// value is ignored.
extern char g_1436abc[];

struct V_008de1c0 {
    virtual void pv0();
    virtual void pv1();
    virtual void F2(int a, void* b, int c);         // slot 2, offset 0x8
};

void FUN_008de1c0(int a, V_008de1c0* p)
{
    p->F2(a, g_1436abc, 1);
}
