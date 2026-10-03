# __thiscall(this, arg): zero two u16 fields at +0x10/+0x12, call an external member with arg, return this.
PATTERN = 'mov edx, dword ptr [esp + N] ; push esi ; mov esi, ecx ; xor ecx, ecx ; xor eax, eax ; mov word ptr [esi + N], cx ; push edx ; mov ecx, esi ; mov word ptr [esi + N], ax ; call EXT ; mov eax, esi ; pop esi ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    t = "T%08x" % va
    src = ("struct %s { short pad[8]; unsigned short a, b; void Init(int); %s* FUN_%08x(int x); };\n"
           "%s* %s::FUN_%08x(int x) { a = 0; b = 0; Init(x); return this; }" % (t, t, va, t, t, va))
    return src, "?FUN_%08x@%s@@QAEPAU1@H@Z" % (va, t)
