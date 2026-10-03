# C++ EH unwind funclet + __ehhandler of a /GS- constructor whose base class has a destructor:
#   __unwindfunclet$ctor$0: mov ecx,[ebp-N]; jmp ~Base     __ehhandler$ctor: mov eax,__ehfuncinfo$; jmp ___CxxFrameHandler3
# If the ctor body throws, the already-constructed base subobject is destroyed through the spilled
# `this`. EH registration occupies [ebp-0xC..ebp); `this` is spilled just below the other EH-frame
# locals, so N = 0x10 + 4*k for k words of address-taken locals. Shape-equivalent: ctor body is a stand-in.
PATTERN = 'mov ecx, dword ptr [ebp - N] ; jmp EXT ; mov eax, A ; jmp EXT'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GS-"]
PRELUDE = "typedef unsigned int uint32_t;\nvoid eh_ext(void*);\n"
def emit(va, A, N):
    k = (N[0] - 0x10) // 4
    body = "uint32_t buf[%d]; eh_ext(buf);" % k if k > 0 else "eh_ext(this);"
    c = "C_%08x" % va
    src = ("struct B_%08x { uint32_t x; B_%08x(); ~B_%08x(); };\n"
           "struct %s : B_%08x { %s(); };\n%s::%s() { %s }" % (va, va, va, c, va, c, c, c, body))
    return src, "__unwindfunclet$??0%s@@QAE@XZ$0" % c
