# Scalar deleting destructor (??_G) of a class with an inline empty virtual dtor whose base has an
# out-of-line dtor: push esi; mov esi,ecx; mov [esi],vftable; call ~Base; test [esp+8],1; je; push esi; call operator delete ...
PATTERN = 'push esi ; mov esi, ecx ; mov dword ptr [esi], A ; call EXT ; test byte ptr [esp + N], N ; je +N ; push esi ; call EXT ; add esp, N ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = "struct Base { Base(); virtual ~Base(); };\n"

def emit(va, A, N):
    c = "C_%08x" % va
    src = ("struct %s : Base { %s(); virtual ~%s() {} };\n"
           "%s::%s() {}" % (c, c, c, c, c))
    return src, "??_G%s@@UAEPAXI@Z" % c
