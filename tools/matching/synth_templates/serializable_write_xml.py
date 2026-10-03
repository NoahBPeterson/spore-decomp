# ISimulatorSerializable::WriteToXML-style forwarder: a __thiscall member taking one pointer arg
# calls a shared __thiscall helper (0x695b40) on that arg, passing this, a field-descriptor table
# and a class-name wide string literal:
#   push L"name"; push offset desc; push ecx; mov ecx, [esp+0x10]; call Writer::Write; ret 4
# Both addresses are masked relocations, so the string is modelled as an extern wchar_t array.
PATTERN = "push A ; push A ; push ecx ; mov ecx, dword ptr [esp + N] ; call EXT ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ("struct XmlWriter { void Write(void* obj, const void* desc, const wchar_t* name); };\n")

def emit(va, A, N):
    s, d = "g_%08x" % A[0], "g_%08x" % A[1]
    src = ("extern const wchar_t %s[];\nextern const char %s;\n"
           "struct C_%08x { void WriteToXML(XmlWriter* w); };\n"
           "void C_%08x::WriteToXML(XmlWriter* w) { w->Write(this, &%s, %s); }"
           % (s, d, va, va, d, s))
    return src, "?WriteToXML@C_%08x@@QAEXPAUXmlWriter@@@Z" % va
