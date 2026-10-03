# Member AddRef: return _InterlockedIncrement(&field at +N) -> add ecx,N; mov eax,1; lock xadd [ecx],eax; inc eax
PATTERN = 'add ecx, N ; mov eax, N ; lock xadd dword ptr [ecx], eax ; inc eax ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "extern \"C\" long __cdecl _InterlockedIncrement(long volatile*);\n#pragma intrinsic(_InterlockedIncrement)\n"
def emit(va, A, N):
    off = N[0]
    src = ("struct C_%08x { char pad[%d]; long rc; int AddRef(); };\n"
           "int C_%08x::AddRef() { return _InterlockedIncrement(&rc); }") % (va, off, va)
    return src, "?AddRef@C_%08x@@QAEHXZ" % va
