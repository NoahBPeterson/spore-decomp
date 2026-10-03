# C++ EH unwind funclet + __ehhandler of a /GS- constructor of C { pad; M m; } (member with dtor):
#   $0: mov ecx,[ebp-N]; add ecx,off(m); jmp ~M ; __ehhandler: mov eax,__ehfuncinfo$; jmp ___CxxFrameHandler3
# Shape-equivalent: ctor body is a stand-in; only funclet+handler bytes are verified.
PATTERN = 'mov ecx, dword ptr [ebp - N] ; add ecx, N ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext(void*);\n"

def emit(va, A, N):
    sp, off = N[0], N[1]
    k = (sp - 0x10) // 4
    body = "uint32_t buf[%d]; eh_ext(buf);" % k if k > 0 else "eh_ext(this);"
    m, c = "M_%08x" % va, "C_%08x" % va
    pad = "uint32_t a[%d];" % (off // 4) if off % 4 == 0 else "char a[%d];" % off
    src = "struct %s { uint32_t x; %s(); ~%s(); };\n" % (m, m, m)
    src += "struct %s { %s %s m; %s(); };\n%s::%s() { %s }" % (c, pad, m, c, c, c, body)
    return src, "__unwindfunclet$??0%s@@QAE@XZ$0" % c
