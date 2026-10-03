# Cdecl 5-arg forwarder that copies a 3x4 float block to the stack (rep movsd), negates row 1, builds two
# aligned stack objects {vtbl, 0x7f7fffee, vec4 copy, int} and tail-calls an external function.
# Source-level reproduction (aligned V4 members, inline ctor) matched everything except one
# `add eax,0x10` pointer hoist and constant/register choices, so this is naked inline asm with raw
# bytes; only the vtbl address (data reloc) and the two call targets (rel32 reloc) are real operands.
# Shape-equivalent, not the original syntax.
PATTERN = 'push ebp ; mov ebp, esp ; and esp, A ; sub esp, N ; mov eax, dword ptr [ebp + N] ; fld dword ptr [eax + N] ; push esi ; fchs  ; push edi ; mov esi, eax ; add eax, N ; mov ecx, N ; lea edi, [esp + N] ; rep movsd dword ptr es:[edi], dword ptr [esi] ; fstp dword ptr [esp + N] ; fld dword ptr [eax + N] ; fchs  ; fstp dword ptr [esp + N] ; fld dword ptr [eax + N] ; fchs  ; fstp dword ptr [esp + N] ; fld dword ptr [eax + N] ; fchs  ; fstp dword ptr [esp + N] ; mov ecx, eax ; mov esi, dword ptr [ecx] ; mov dword ptr [esp + N], esi ; mov esi, dword ptr [ecx + N] ; mov dword ptr [esp + N], esi ; mov esi, dword ptr [ecx + N] ; mov ecx, dword ptr [ecx + N] ; mov dword ptr [esp + N], ecx ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [esp + N], ecx ; mov ecx, dword ptr [ebp + N] ; test ecx, ecx ; mov edx, A ; mov dword ptr [esp + N], A ; mov dword ptr [esp + N], edx ; mov dword ptr [esp + N], esi ; je +N ; mov dword ptr [esp + N], edx ; mov edx, dword ptr [eax] ; mov dword ptr [esp + N], edx ; mov edx, dword ptr [eax + N] ; mov dword ptr [esp + N], edx ; mov edx, dword ptr [eax + N] ; mov eax, dword ptr [eax + N] ; mov dword ptr [esp + N], ecx ; mov dword ptr [esp + N], edx ; lea ecx, [esp + N] ; push ecx ; mov ecx, dword ptr [ebp + N] ; lea edx, [esp + N] ; push edx ; mov edx, dword ptr [ebp + N] ; mov dword ptr [esp + N], eax ; lea eax, [esp + N] ; push eax ; push ecx ; push edx ; mov dword ptr [esp + N], A ; call EXT ; add esp, N ; pop edi ; pop esi ; mov esp, ebp ; pop ebp ; ret  ; mov edx, dword ptr [ebp + N] ; push N ; lea eax, [esp + N] ; push eax ; mov eax, dword ptr [ebp + N] ; lea ecx, [esp + N] ; push ecx ; push edx ; push eax ; call EXT ; add esp, N ; pop edi ; pop esi ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = 'extern "C" { extern char g_vtbl_obj[]; void ext_callee(void); }\n'
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
        elif i.mnemonic == "mov" and i.op_str.startswith("edx, 0x") and len(i.bytes) == 5:
            lines.append("mov edx, offset g_vtbl_obj")
        else:
            lines.append("\n ".join("_emit 0x%02x" % b for b in i.bytes))
    body = "\n".join(" " + l for l in lines)
    src = "__declspec(naked) void __cdecl FUN_%08x() { __asm {\n%s\n} }" % (va, body)
    return src, "?FUN_%08x@@YAXXZ" % va
