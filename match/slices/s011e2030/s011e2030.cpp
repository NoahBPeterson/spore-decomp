// Slice s011e2030: RenderWare 4 core, built VC .NET 2003 /GL+/LTCG (tools/README: RW4 core is
// LTCG; leaf functions still match). Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// A refcounted resource object's "release" step: drop the count and run the teardown when
// it reaches zero. The original touches the global object's count word directly
// (mov eax,[0x16f2974]; dec eax; mov [0x16f2974],eax; jne; jmp teardown), so the object is a
// single fixed global rather than a parameter.
struct RwResource_16f2974 {
    volatile int mnRefCount;                 // +0x00
};

extern RwResource_16f2974 g_rwResource_16f2974;      // 0x016f2974
extern "C" void FUN_011eaa80();                      // 0x011eaa80 teardown (ret 0)

// @ 0x011e2030
void InterpRelease_011e2030()
{
    if (--g_rwResource_16f2974.mnRefCount == 0)
        FUN_011eaa80();
}
