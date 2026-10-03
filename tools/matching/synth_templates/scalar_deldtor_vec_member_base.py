# Scalar deleting dtor of D : Base (out-of-line virtual dtor); implicit dtor destroys a vector-like member
# (inline: if ((cap-begin)>1 && begin) free(begin)) at offset N2 then an out-of-line member at N1, then base.
PATTERN = 'push esi ; mov esi, ecx ; mov eax, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; sub ecx, eax ; cmp ecx, N ; jle +N ; test eax, eax ; je +N ; push eax ; call EXT ; add esp, N ; lea ecx, [esi + N] ; call EXT ; mov ecx, esi ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = ("void EASTL_allocator_deallocate(void* p);\n"
           "struct Base { Base(); virtual ~Base(); };\n"
           "struct Mem { ~Mem(); };\n"
           "struct Vec { char* b; char* e; char* c; ~Vec() { if ((c - b) > 1 && b) EASTL_allocator_deallocate(b); } };\n")

def emit(va, A, N):
    c = "C_%08x" % va
    # N: [vec_begin_off, vec_cap_off, mem_off, ...] in operand order
    vo, mo = N[0], N[4]
    src = ("struct %s : Base { char p0[%d]; Mem m; char p1[%d]; Vec v; %s(); };\n"
           "%s::%s() {}" % (c, mo - 4, vo - mo - 1, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
