# C++ EH unwind funclets + __ehhandler of a /GS- constructor of D : Base { M1 m1; M2 m2; }:
#   $0: mov ecx,[ebp-N]; jmp ~Base
#   $1: mov ecx,[ebp-N]; add ecx,off(m1); jmp ~M1
#   $2: mov ecx,[ebp-N]; add ecx,off(m2); jmp ~M2
#   __ehhandler$ctor: mov eax,__ehfuncinfo$; jmp ___CxxFrameHandler3
# The spilled `this` lives at [ebp-N], N = 0x10 + 4*k for k words of address-taken locals.
# Member offsets come from the add immediates: Base is padded to off(m1), M1 to off(m2)-off(m1).
# Shape-equivalent: the ctor body is a stand-in; only the funclet+handler bytes are verified.
PATTERN = 'mov ecx, dword ptr [ebp - N] ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext(void*);\n"

def field(size):
    return "uint32_t a[%d];" % (size // 4) if size % 4 == 0 else "char a[%d];" % size

def emit(va, A, N):
    sp, o1, o2 = N[0], N[2], N[4]
    k = (sp - 0x10) // 4
    body = "uint32_t buf[%d]; eh_ext(buf);" % k if k > 0 else "eh_ext(this);"
    b, m1, m2, c = ("%s_%08x" % (p, va) for p in ("B", "M1", "M2", "C"))
    src = "struct %s { %s %s(); ~%s(); };\n" % (b, field(o1), b, b)
    src += "struct %s { %s %s(); ~%s(); };\n" % (m1, field(max(o2 - o1, 4)), m1, m1)
    src += "struct %s { uint32_t a; %s(); ~%s(); };\n" % (m2, m2, m2)
    src += "struct %s : %s { %s m1; %s m2; %s(); };\n%s::%s() { %s }" % (c, b, m1, m2, c, c, c, body)
    return src, "__unwindfunclet$??0%s@@QAE@XZ$0" % c
