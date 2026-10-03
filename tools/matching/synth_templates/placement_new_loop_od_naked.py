# /Od loop: for (f = p; n > 0; --n, f += sizeof(T)) { new (inl(f)) T(a); }  (placement new via inlined identity helper,
# null-checked ctor call, ctor result stored to a temp).  Frame size has an unexplained per-instance gap of unused
# stack slots (8..0x80 bytes) between the inline param copy (-0xc) and the ctor-result temp (bottom slot).
# Every real-source shape tried (inline helper with unused locals/params, outer locals, nested scopes, struct
# returns, default args) gets the loop and null check exact but puts unused locals ABOVE the param copy, so the
# frame size and slot numbers differ.  Hence emitted as naked bytes with the callee as a masked rel32 relocation.
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov eax, dword ptr [ebp + N] ; mov dword ptr [ebp - N], eax ; jmp +N ; mov ecx, dword ptr [ebp + N] ; sub ecx, N ; mov dword ptr [ebp + N], ecx ; mov edx, dword ptr [ebp - N] ; add edx, N ; mov dword ptr [ebp - N], edx ; cmp dword ptr [ebp + N], N ; jbe +N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [ebp - N], eax ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ebp - N], ecx ; cmp dword ptr [ebp - N], N ; je +N ; mov edx, dword ptr [ebp + N] ; push edx ; mov ecx, dword ptr [ebp - N] ; call EXT ; mov dword ptr [ebp - N], eax ; jmp +N ; mov dword ptr [ebp - N], N ; jmp +N ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    t = "%08x" % va
    code = _pe.get_data(va - _base, 256)
    end = code.index(b"\x8b\xe5\x5d\xc3") + 4
    code = code[:end]
    ci = code.index(b"\xe8", 20)
    tgt = (va + ci + 5 + struct.unpack("<i", code[ci + 1:ci + 5])[0]) & 0xffffffff
    lines = []
    for b in code[:ci]:
        lines.append("        _emit 0x%02x" % b)
    lines.append("        call T_%08x" % tgt)
    for b in code[ci + 5:]:
        lines.append("        _emit 0x%02x" % b)
    src = ('extern "C" void T_%08x(void);\n'
           "__declspec(naked) void FUN_%s(void* p, unsigned n, int a) {\n    __asm {\n%s\n    }\n}"
           % (tgt, t, "\n".join(lines)))
    return src, "?FUN_%s@@YAXPAXIH@Z" % t
