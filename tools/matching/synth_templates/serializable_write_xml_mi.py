# ISimulatorSerializable::WriteToXML forwarder overridden in a class whose serializable interface
# is a non-primary base at offset N. MSVC compiles the override expecting this == that base
# subobject, so converting this to the full object (for the void* arg) emits `add ecx,-N` inline:
#   push L"name"; add ecx,-N; push offset desc; push ecx; mov ecx,[esp+0x10]; call Writer::Write; ret 4
# B0 is padded so that the serializable base B1 sits at exactly offset N.
PATTERN = "push A ; add ecx, -N ; push A ; push ecx ; mov ecx, dword ptr [esp + N] ; call EXT ; ret N"
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ("struct XmlWriter { void Write(void* obj, const void* desc, const wchar_t* name); };\n")

def emit(va, A, N):
    s, d = "g_%08x" % A[0], "g_%08x" % A[1]
    n = (-N[0]) & 0xffffffff if N[0] > 0x7fffffff else N[0]
    t = "%08x" % va
    pad = " char pad[%d];" % (n - 4) if n > 4 else ""
    packed = n % 4 != 0
    src = "extern const wchar_t %s[];\nextern const char %s;\n" % (s, d)
    if packed: src += "#pragma pack(push, 1)\n"
    src += ("struct B0_%s { virtual void g();%s };\n"
            "struct B1_%s { virtual void WriteToXML(XmlWriter* w); };\n"
            "struct D_%s : B0_%s, B1_%s { void WriteToXML(XmlWriter* w); };\n" % (t, pad, t, t, t, t))
    if packed: src += "#pragma pack(pop)\n"
    src += "void D_%s::WriteToXML(XmlWriter* w) { w->Write(this, &%s, %s); }" % (t, d, s)
    return src, "?WriteToXML@D_%s@@UAEXPAUXmlWriter@@@Z" % t
