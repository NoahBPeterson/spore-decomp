// Slice s011e2000: RenderWare 4 core, built VC .NET 2003 /GL+/LTCG (tools/README: RW4 core is
// LTCG; leaf functions still match). Flags: /vc71 /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// The addref counterpart of InterpRelease_011e2030: bump the global resource's
// reference count and run the one-time initialiser when it was zero.  The
// original keeps the object pointer in esi and returns it, so this is a
// thiscall member.
struct RwResource_16f2974 {
    volatile int mnRefCount;                 // +0x00
};

extern RwResource_16f2974 g_rwResource_16f2974;      // 0x016f2974
extern "C" void FUN_011eaa50();                      // 0x011eaa50 initialiser (ret 0)

struct Interp {
    Interp* AddRef();
};

// @ 0x011e2000
Interp* Interp::AddRef()
{
    if (g_rwResource_16f2974.mnRefCount++ == 0)
        FUN_011eaa50();
    return this;
}
