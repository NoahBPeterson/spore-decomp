# C++ EH unwind funclets + __ehhandler of a /GS- constructor of D : Base { M1..M5 }:
#   $0: jmp ~Base; $1..$5: add ecx,off(mK); jmp ~MK; __ehhandler: mov eax,__ehfuncinfo$; jmp ___CxxFrameHandler3
# Shape-equivalent: the ctor body is a stand-in; only the funclet+handler bytes are verified.
PATTERN = 'mov ecx, dword ptr [ebp - N] ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext(void*);\n"

def field(size):
    return "uint32_t a[%d];" % (size // 4) if size % 4 == 0 else "char a[%d];" % size

def emit(va, A, N):
    sp = N[0]
    o = [N[2], N[4], N[6], N[8], N[10]]
    k = (sp - 0x10) // 4
    body = "uint32_t buf[%d]; eh_ext(buf);" % k if k > 0 else "eh_ext(this);"
    b = "B_%08x" % va
    ms = ["M%d_%08x" % (i, va) for i in range(1, 6)]
    c = "C_%08x" % va
    src = "struct %s { %s %s(); ~%s(); };\n" % (b, field(o[0]), b, b)
    for i in range(4):
        src += "struct %s { %s %s(); ~%s(); };\n" % (ms[i], field(max(o[i + 1] - o[i], 4)), ms[i], ms[i])
    src += "struct %s { uint32_t a; %s(); ~%s(); };\n" % (ms[4], ms[4], ms[4])
    src += "struct %s : %s { %s %s(); };\n%s::%s() { %s }" % (c, b, " ".join("%s m%d;" % (ms[i], i + 1) for i in range(5)), c, c, c, body)
    return src, "__unwindfunclet$??0%s@@QAE@XZ$0" % c
