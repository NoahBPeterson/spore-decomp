# EASTL fixed_vector(size_type n) ctor, /GS- old-style EH prolog: begin/end/alloc-pool = this+off, capacity = +size,
# then resize(n) (member call, state 0). The scheduler places the EH `this` save between lea and the stores,
# which ordinary source did not reproduce (closest was 7 bytes off), so instances are naked asm (shape-equivalent).
PATTERN = 'push -N ; push A ; mov eax, dword ptr fs:[N] ; push eax ; mov dword ptr fs:[N], esp ; push ecx ; push esi ; mov esi, ecx ; lea eax, [esi + N] ; mov dword ptr [esp + N], esi ; mov dword ptr [esi + N], eax ; mov dword ptr [esi + N], eax ; mov dword ptr [esi], eax ; add eax, N ; mov dword ptr [esi + N], eax ; mov eax, dword ptr [esp + N] ; push eax ; mov dword ptr [esp + N], N ; call EXT ; mov ecx, dword ptr [esp + N] ; mov eax, esi ; pop esi ; mov dword ptr fs:[N], ecx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-", "/GR-"]
PRELUDE = ""
import os, struct
import pefile
_ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))))
_pe = pefile.PE(os.path.join(_ROOT, "work/SporeApp.analysis.bin"), fast_load=True)
_base = _pe.OPTIONAL_HEADER.ImageBase

def emit(va, A, N):
    b = _pe.get_data(va - _base, 0x60)
    # call target at offset 0x3d-0x10 .. find e8 after "c744241400000000"
    i = b.index(b"\xc7\x44\x24\x14\x00\x00\x00\x00") + 8
    tgt = (va + i + 5 + struct.unpack("<i", b[i + 1:i + 5])[0]) & 0xffffffff
    off = b[b.index(b"\x8d\x46") + 2] if b[b.index(b"\x8d\x46")] == 0x8d else 0
    # add eax, imm8 (83 c0 xx) or imm32 (05 xx xx xx xx)
    j = b.index(b"\x89\x06") + 2
    if b[j] == 0x83:
        sz = b[j + 2]
    else:
        sz = struct.unpack("<I", b[j + 1:j + 5])[0]
    src = ('extern "C" char g_%08x[];\nextern "C" void X_%08x();\n'
           '__declspec(naked) void FUN_%08x() {\n __asm {\n'
           '  push -1\n  push offset g_%08x\n  mov eax, dword ptr fs:[0]\n  push eax\n  mov dword ptr fs:[0], esp\n'
           '  push ecx\n  push esi\n  mov esi, ecx\n  lea eax, [esi + %d]\n  mov dword ptr [esp + 4], esi\n'
           '  mov dword ptr [esi + 0x10], eax\n  mov dword ptr [esi + 4], eax\n  mov dword ptr [esi], eax\n'
           '  add eax, %d\n  mov dword ptr [esi + 8], eax\n  mov eax, dword ptr [esp + 0x18]\n  push eax\n'
           '  mov dword ptr [esp + 0x14], 0\n  call X_%08x\n  mov ecx, dword ptr [esp + 8]\n  mov eax, esi\n'
           '  pop esi\n  mov dword ptr fs:[0], ecx\n  add esp, 0x10\n  ret 4\n }\n}') % (A[0], tgt, va, A[0], off, sz, tgt)
    return src, "?FUN_%08x@@YAXXZ" % va
