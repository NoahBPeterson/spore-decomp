# /Od "deleting dtor" with inlined vptr store: this->vp = vtbl; if (f & 1) EASTL_allocator_deallocate(this); return this;
PATTERN = 'push ebp ; mov ebp, esp ; push ecx ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax], A ; mov ecx, dword ptr [ebp + N] ; and ecx, N ; je +N ; mov edx, dword ptr [ebp - N] ; push edx ; call EXT ; add esp, N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret N'
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = "void EASTL_allocator_deallocate(void* p);\nvoid operator_delete_dummy();\n"
def emit(va, A, N):
    t = "%08x" % va
    src = ("extern void* vt_%s[];\nstruct C_%s { void** vp; void* F(unsigned f); };\n"
           "void* C_%s::F(unsigned f) {\n  vp = vt_%s;\n  if (f & 1) EASTL_allocator_deallocate(this);\n  return this;\n}") % (t, t, t, t)
    return src, "?F@C_%s@@QAEPAXI@Z" % t
