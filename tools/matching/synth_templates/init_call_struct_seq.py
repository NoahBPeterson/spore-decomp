# Plain function: 12 results of cdecl calls f(arg) stored into consecutive globals interleaved with constants.
PATTERN = 'push esi ; xor esi, esi ; push esi ; call EXT ; push N ; mov dword ptr [A], eax ; mov dword ptr [A], esi ; mov dword ptr [A], esi ; call EXT ; push esi ; mov dword ptr [A], eax ; call EXT ; push N ; mov dword ptr [A], eax ; mov dword ptr [A], esi ; call EXT ; push esi ; mov dword ptr [A], eax ; mov dword ptr [A], N ; mov dword ptr [A], esi ; mov dword ptr [A], esi ; call EXT ; push N ; mov dword ptr [A], eax ; mov dword ptr [A], N ; mov dword ptr [A], esi ; call EXT ; push esi ; mov dword ptr [A], eax ; call EXT ; push esi ; mov dword ptr [A], eax ; mov dword ptr [A], esi ; call EXT ; push esi ; mov dword ptr [A], eax ; mov dword ptr [A], esi ; mov dword ptr [A], esi ; mov dword ptr [A], esi ; call EXT ; push esi ; mov dword ptr [A], eax ; mov dword ptr [A], A ; mov dword ptr [A], esi ; call EXT ; push esi ; mov dword ptr [A], eax ; call EXT ; push esi ; mov dword ptr [A], eax ; mov dword ptr [A], esi ; call EXT ; add esp, N ; mov dword ptr [A], esi ; mov dword ptr [A], esi ; mov dword ptr [A], eax ; pop esi ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "extern \"C\" int __cdecl FUN_00e4a9d0(int); extern \"C\" int __cdecl FUN_00e4a9c0(int);\n"
def emit(va, A, N):
    a = sorted(A)
    g = lambda i: "g_%08x" % a[i]
    # (index, callee, argument expression) followed by constant stores
    seq = [(0,"d0","0"),(3,"c0","1"),(4,"c0","0"),(6,"c0",str(N[1])),(10,"d0","0"),(13,"c0","2"),(14,"c0","0"),
           (16,"c0","0"),(20,"d0","0"),(23,"c0","0"),(24,"c0","0"),(26,"c0","0")]
    consts = {1:"0",2:"0",5:"0",7:"8",8:"0",9:"0",11:"4",12:"0",15:"0",17:"0",18:"0",19:"0",21:"-1",22:"0",25:"0",27:"0",28:"0"}
    src = "".join("extern int %s;\n" % g(i) for i in range(29))
    src += "void FUN_%08x() {\n" % va
    for i in range(29):
        if i in consts: src += "  %s = %s;\n" % (g(i), consts[i])
        else:
            for s in seq:
                if s[0] == i: src += "  %s = FUN_00e4a9%s(%s);\n" % (g(i), "d0" if s[1]=="d0" else "c0", s[2])
    return src + "}", "?FUN_%08x@@YAXXZ" % va
