# Scalar deleting destructor (??_G) in an unoptimized (/Od /Ob1) module:
#   push ebp; mov ebp,esp; push ecx; mov [ebp-4],ecx; mov ecx,[ebp-4]; call ~T; mov eax,[ebp+8];
#   and eax,1; je; mov ecx,[ebp-4]; push ecx; call operator delete; add esp,4; mov eax,[ebp-4]; ...; ret 4
# Class with a virtual out-of-line dtor; the ??_G is emitted with the vftable in the TU defining the ctor.
# Call targets (dtor, operator delete -> EASTL_allocator_deallocate) are relocations.
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov eax, dword ptr [ebp + N] ; and eax, N ; je +N ; mov ecx, dword ptr [ebp - N] ; push ecx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %s { %s(); virtual ~%s(); };\n"
           "%s::%s() {}" % (c, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
