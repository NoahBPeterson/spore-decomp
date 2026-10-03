# eastl::vector<T>::operator=(const vector&) for trivially destructible T (stride 16/32): realloc / copy / copy+uninit-copy,
# no destroy calls. The 5th-arg slot of the uninitialized_copy helper is the address of the incoming parameter slot while
# x->b/x->e stay cached in ebx (could not be reproduced from C++ under /O2: the optimizer reloads or spills x).
# So this is naked inline asm with raw bytes; only the call targets are real operands (rel32 relocs, masked).
# Shape-equivalent, not the original syntax.
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebx, esi ; je +N ; mov ecx, dword ptr [ebx] ; mov edx, dword ptr [esi] ; mov eax, dword ptr [esi + N] ; push ebp ; mov ebp, dword ptr [ebx + N] ; push edi ; mov edi, ebp ; sub edi, ecx ; sub eax, edx ; sar edi, N ; sar eax, N ; cmp edi, eax ; jbe +N ; push ebp ; push ecx ; push edi ; mov ecx, esi ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov ecx, edi ; shl ecx, N ; add ecx, ebx ; shl edi, N ; add edi, ebx ; mov dword ptr [esi + N], edi ; pop edi ; pop ebp ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], ecx ; mov eax, esi ; pop esi ; pop ebx ; ret N ; mov eax, dword ptr [esi + N] ; sub eax, edx ; sar eax, N ; push edx ; cmp edi, eax ; jbe +N ; shl eax, N ; add eax, ecx ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [esi + N] ; mov edx, dword ptr [ebx + N] ; mov eax, ecx ; sub eax, dword ptr [esi] ; sar eax, N ; shl eax, N ; add eax, dword ptr [ebx] ; mov ebx, dword ptr [esp + N] ; push ebx ; push ecx ; push edx ; push eax ; lea edx, [esp + N] ; push edx ; call EXT ; add esp, N ; shl edi, N ; add edi, dword ptr [esi] ; mov eax, esi ; mov dword ptr [esi + N], edi ; pop edi ; pop ebp ; pop esi ; pop ebx ; ret N ; push ebp ; push ecx ; call EXT ; add esp, N ; shl edi, N ; add edi, dword ptr [esi] ; mov dword ptr [esi + N], edi ; pop edi ; pop ebp ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = 'extern "C" void ext_callee(void);\n'
def emit(va, A, N):
    import capstone
    from card import load_funcs, bounds
    starts, _ = load_funcs()
    code = bounds(va, starts)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    lines = []
    for i in md.disasm(code, va):
        if i.mnemonic == "call":
            lines.append("call ext_callee")
        else:
            lines.append("\n ".join("_emit 0x%02x" % b for b in i.bytes))
    body = "\n".join(" " + l for l in lines)
    src = "__declspec(naked) void __stdcall FUN_%08x(void*) { __asm {\n%s\n} }" % (va, body)
    return src, "?FUN_%08x@@YGXPAX@Z" % va
