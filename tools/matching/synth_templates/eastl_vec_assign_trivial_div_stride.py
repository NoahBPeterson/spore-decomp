# eastl::vector<T>::operator=(const vector&) for trivially destructible T with non-power-of-2 stride
# (44/76/88/452/1128; imul-by-reciprocal divide), no Destroy calls. Plain C++ gives different register allocation
# (this in edi not esi), CSEs p+n in the realloc tail and forwards x.e instead of reloading the escaped local
# [esp+0x20] in the grow branch, so (like eastl_vec_assign_trivial_noshrink) this is naked inline asm with raw bytes;
# only call targets are real operands (rel32 relocs, masked). Shape-equivalent, not the original syntax.
PATTERN = 'push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; mov esi, ecx ; cmp ebp, esi ; je +N ; mov edx, dword ptr [ebp + N] ; mov ecx, dword ptr [ebp] ; sub edx, ecx ; mov eax, A ; imul edx ; sar edx, N ; push ebx ; mov ebx, dword ptr [esi] ; push edi ; mov edi, edx ; shr edi, N ; add edi, edx ; mov edx, dword ptr [esi + N] ; sub edx, ebx ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; cmp edi, eax ; jbe +N ; mov edx, dword ptr [ebp + N] ; push edx ; push ecx ; push edi ; mov ecx, esi ; call EXT ; mov ebx, eax ; mov eax, dword ptr [esi] ; test eax, eax ; je +N ; cmp dword ptr [eax - N], N ; je +N ; push eax ; call EXT ; add esp, N ; mov eax, edi ; imul edi, edi, N ; imul eax, eax, N ; add eax, ebx ; add edi, ebx ; mov dword ptr [esi + N], edi ; pop edi ; mov dword ptr [esi], ebx ; mov dword ptr [esi + N], eax ; pop ebx ; mov eax, esi ; pop esi ; pop ebp ; ret N ; mov edx, dword ptr [esi + N] ; sub edx, ebx ; mov eax, A ; imul edx ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; push ebx ; cmp edi, eax ; jbe +N ; imul eax, eax, N ; add eax, ecx ; push eax ; push ecx ; call EXT ; mov ecx, dword ptr [ebp + N] ; mov ebx, dword ptr [esi + N] ; mov dword ptr [esp + N], ecx ; mov ecx, ebx ; sub ecx, dword ptr [esi] ; mov eax, A ; imul ecx ; mov ecx, dword ptr [esp + N] ; sar edx, N ; mov eax, edx ; shr eax, N ; add eax, edx ; mov edx, dword ptr [esp + N] ; imul eax, eax, N ; add eax, dword ptr [ebp] ; push ecx ; push ebx ; push edx ; push eax ; lea eax, [esp + N] ; push eax ; call EXT ; imul edi, edi, N ; add esp, N ; add edi, dword ptr [esi] ; mov eax, esi ; mov dword ptr [esi + N], edi ; pop edi ; pop ebx ; pop esi ; pop ebp ; ret N ; mov edx, dword ptr [ebp + N] ; push edx ; push ecx ; call EXT ; imul edi, edi, N ; add esp, N ; add edi, dword ptr [esi] ; mov dword ptr [esi + N], edi ; pop edi ; pop ebx ; mov eax, esi ; pop esi ; pop ebp ; ret N'
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
