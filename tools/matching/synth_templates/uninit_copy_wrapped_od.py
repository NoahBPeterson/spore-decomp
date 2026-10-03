# /Od /Ob1 uninitialized_copy through two layers of inline wrappers:
#   for (d = dest; first != last; ++first, ++d) if (d) T(*first) (out-of-line copy ctor); return d;
# The loop is not inlinable under /Ob1 (loop-bearing inline functions are never expanded; __forceinline does expand
# but copies only modified params, not all three), so the arg-temp slots (-0x38..-0x30, allocated after the body
# temps) could not be reproduced from source.  Emitted as naked bytes with the callee as a relocated call.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp + N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; jmp +N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov dword ptr [ebp - N], ecx ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; xor ecx, ecx ; cmp eax, dword ptr [ebp - N] ; setne cl ; movzx edx, cl ; test edx, edx ; je +N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; cmp dword ptr [ebp - N], N ; je +N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], edx ; mov eax, dword ptr [ebp - N] ; push eax ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 256)
    end = code.index(b"\x8b\xe5\x5d\xc3") + 4
    code = code[:end]
    ci = code.index(b"\xe8", 20)
    tgt = (va + ci + 5 + struct.unpack("<i", code[ci + 1:ci + 5])[0]) & 0xffffffff
    lines = ["        _emit 0x%02x" % b for b in code[:ci]]
    lines.append("        call T_%08x" % tgt)
    lines += ["        _emit 0x%02x" % b for b in code[ci + 5:]]
    src = ('extern "C" void T_%08x(void);\n'
           "__declspec(naked) void* FUN_%s(void* a, void* b, void* c) {\n    __asm {\n%s\n    }\n}"
           % (tgt, t, "\n".join(lines)))
    return src, "?FUN_%s@@YAPAXPAX00@Z" % t
