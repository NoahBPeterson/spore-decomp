# Variant of uninit_copy_dead_loop_od where loop 2 is a destroy loop (dtor call + dead delete call). Naked bytes, all calls relocated.
# Original note: loop 1 copy-constructs each element (null-checked placement new,
# thiscall copy ctor, ctor result stored to a temp) and loop 2 is an empty cleanup loop over the same range;
# returns dest end.  Pure-C++ shapes get the loops and null check right (nested-scope version is within 24 diff
# bytes) but the stack frame layout is wrong: the original has the placement temp at [ebp-0xc], a return slot at -4,
# a bool at -5 and a per-instance gap of unused slots (0..0x38 bytes, not tied to sizeof(T)) before the loop
# variables.  Tried: block scopes, hoisted decls, inline helpers with tag struct / bool params, Cn/Pv helpers.
# So emitted as naked bytes with the callee as a masked rel32 relocation.
import os, struct
import pefile, capstone
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase
_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov byte ptr [ebp - N], N ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], ecx ; jmp +N ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; add eax, N ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; cmp ecx, dword ptr [ebp + N] ; je +N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; cmp dword ptr [ebp - N], N ; je +N ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov byte ptr [ebp - N], N ; mov edx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; jmp +N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; cmp eax, dword ptr [ebp + N] ; je +N ; mov ecx, dword ptr [ebp - N] ; call EXT ; xor ecx, ecx ; and ecx, N ; je +N ; mov edx, dword ptr [ebp - N] ; push edx ; call EXT ; add esp, N ; jmp +N ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 400)
    end = code.index(b"\x8b\xe5\x5d\xc3") + 4
    code = code[:end]
    calls = {}
    for i in _md.disasm(code, va):
        if i.mnemonic == "call":
            calls[i.address - va] = int(i.op_str, 16)
    lines, pos = [], 0
    for off in sorted(calls):
        lines += ["        _emit 0x%02x" % b for b in code[pos:off]]
        lines.append("        call T_%08x" % calls[off])
        pos = off + 5
    lines += ["        _emit 0x%02x" % b for b in code[pos:]]
    decl = "".join('extern "C" void T_%08x(void);\n' % x for x in sorted(set(calls.values())))
    src = (decl + "__declspec(naked) void* FUN_%s(void* a, void* b, void* c) {\n    __asm {\n%s\n    }\n}"
           % (t, "\n".join(lines)))
    return src, "?FUN_%s@@YAPAXPAX00@Z" % t
