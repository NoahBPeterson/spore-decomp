// Slice s00a4f7e0: Function calling two other functions
// Standard calling convention: params on stack

// Forward declarations
extern "C" void FUN_00a471a0(void* a, void* b, void* c);  // ?binbuf_add@Eapd@Audio@EA@@YAXPAUt_binbuf@123@HPBUt_atom@123@@Z
extern "C" void FUN_00a4d3e0(void* a, void* b);  // ?glist_retext@Eapd@Audio@EA@@YAXPAUt_glist@123@PAUt_text@123@@Z

// @ 0x00a4f7e0
void FUN_00a4f7e0(void* param1, void* param2, void* param3, void* param4, void* param5)
{
    FUN_00a471a0(*(void**)((char*)param1 + 8), param4, param5);
    FUN_00a4d3e0(*(void**)((char*)param1 + 48), param1);
}
