# C++ EH unwind funclets + __ehhandler of a /GS- constructor of C { pad; M1 m1; M2 m2; M3 m3; M4 m4; } (no base):
#   $0..$3: mov ecx,[ebp-N]; add ecx,off(mK); jmp ~MK ; __ehhandler: mov eax,__ehfuncinfo$; jmp ___CxxFrameHandler3
# Shape-equivalent: the ctor body is a stand-in; only the funclet+handler bytes are verified.
PATTERN = 'mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext(void*);\n"

def field(size):
    return "uint32_t a[%d];" % (size // 4) if size % 4 == 0 else "char a[%d];" % size

def emit(va, A, N):
    sp, o1, o2, o3, o4 = N[0], N[1], N[3], N[5], N[7]
    k = (sp - 0x10) // 4
    body = "uint32_t buf[%d]; eh_ext(buf);" % k if k > 0 else "eh_ext(this);"
    m1, m2, m3, m4, c = ("%s_%08x" % (p, va) for p in ("M1", "M2", "M3", "M4", "C"))
    src = "struct %s { %s %s(); ~%s(); };\n" % (m1, field(max(o2 - o1, 4)), m1, m1)
    src += "struct %s { %s %s(); ~%s(); };\n" % (m2, field(max(o3 - o2, 4)), m2, m2)
    src += "struct %s { %s %s(); ~%s(); };\n" % (m3, field(max(o4 - o3, 4)), m3, m3)
    src += "struct %s { uint32_t a; %s(); ~%s(); };\n" % (m4, m4, m4)
    pad = field(o1).replace("a[", "p[") if o1 else ""
    src += "struct %s { %s %s m1; %s m2; %s m3; %s m4; %s(); };\n%s::%s() { %s }" % (c, pad, m1, m2, m3, m4, c, c, c, body)
    return src, "__unwindfunclet$??0%s@@QAE@XZ$0" % c
