# ISimulatorSerializable::ReadFromXML-style member (counterpart of serializable_write_xml):
# a __thiscall member taking one pointer arg first calls a base/sibling __thiscall member on the
# same arg (result kept in bl), then builds a large stack-local reader object (ctor takes this,
# a field-descriptor table and a class-name wide string), calls its Read(arg) and returns
# `Read(arg) && base` as int (mov eax,1 / xor eax,eax). The reader has no destructor.
# Local size = the `sub esp` immediate (object sits at [esp+0]). Plain /O2.
PATTERN = 'sub esp, N ; push ebx ; push esi ; push edi ; mov edi, dword ptr [esp + N] ; push edi ; mov esi, ecx ; call EXT ; push A ; push A ; push esi ; lea ecx, [esp + N] ; mov bl, al ; call EXT ; push edi ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; test bl, bl ; je +N ; pop edi ; pop esi ; mov eax, N ; pop ebx ; add esp, N ; ret N ; pop edi ; pop esi ; xor eax, eax ; pop ebx ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    s, d = "g_%08x" % A[0], "g_%08x" % A[1]
    size = N[0]
    src = ("extern const wchar_t %s[];\nextern const char %s;\n"
           "struct R_%08x { R_%08x(void* o, const void* d, const wchar_t* n); bool Read(void* x);"
           " unsigned int pad[%d]; };\n"
           "struct C_%08x { bool Base(void* x); int ReadFromXML(void* x); };\n"
           "int C_%08x::ReadFromXML(void* x) { bool b = Base(x); R_%08x r(this, &%s, %s);"
           " return r.Read(x) && b; }"
           % (s, d, va, va, size // 4, va, va, va, d, s))
    return src, "?ReadFromXML@C_%08x@@QAEHPAX@Z" % va
