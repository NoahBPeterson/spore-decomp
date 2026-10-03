# /Od uninitialized_copy-style loop (null-checked placement new, thiscall copy ctor, result stored to a temp):
#   for (; first != last; ++first, ++dest) new (dest) T(*first); return dest;
# Pure C++ gets the code within 3-6 bytes, but the original frame has the null-check temp at [ebp-4], the ctor
# result temp at the bottom of the frame and a per-instance gap (stride 0x34 -> 0x38 bytes, 0x48 -> 0x18, 0x18 -> 8,
# 0x10 -> 0) between them; named locals are always allocated before compiler temps so no spelling reproduces it.
# So emitted as naked bytes with the callee as a masked rel32 relocation.
import os
import pefile, capstone
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase
_md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; jmp +N ; mov eax, dword ptr [ebp + N] ; add eax, N ; mov dword ptr [ebp + N], eax ; mov ecx, dword ptr [ebp + N] ; add ecx, N ; mov dword ptr [ebp + N], ecx ; mov edx, dword ptr [ebp + N] ; cmp edx, dword ptr [ebp + N] ; je +N ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; cmp dword ptr [ebp - N], N ; je +N ; mov ecx, dword ptr [ebp + N] ; push ecx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov eax, dword ptr [ebp + N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 400)
    end = code.index(b"\x8b\xe5\x5d\xc3") + 4
    code = code[:end]
    ci = tgt = None
    for i in _md.disasm(code, va):
        if i.mnemonic == "call":
            ci, tgt = i.address - va, int(i.op_str, 16)
            break
    lines = ["        _emit 0x%02x" % b for b in code[:ci]]
    lines.append("        call T_%08x" % tgt)
    lines += ["        _emit 0x%02x" % b for b in code[ci + 5:]]
    src = ('extern "C" void T_%08x(void);\n'
           "__declspec(naked) void FUN_%s(void* a, void* b, void* c) {\n    __asm {\n%s\n    }\n}"
           % (tgt, t, "\n".join(lines)))
    return src, "?FUN_%s@@YAXPAX00@Z" % t
