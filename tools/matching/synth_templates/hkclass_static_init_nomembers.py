# Dynamic initializer of a file-scope Havok hkClass with a parent but no members/enums/ifaces
# (e.g. hkParametricCurveClass): seven zero pushes, size, parent, name, then ctor call.
# Source shape: `hkClass g("name", &parent, size, 0,0, 0,0, 0,0, 0);` at /O2, out-of-line ctor.
PATTERN = 'push N ; push N ; push N ; push N ; push N ; push N ; push N ; push N ; push A ; push A ; mov ecx, A ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """struct hkClassMember; struct hkClassEnum;
class hkClass {
public:
    hkClass(const char* name, const hkClass* parent, int objectSize,
            const hkClass** implementedInterfaces, int numImplementedInterfaces,
            const hkClassEnum* declaredEnums, int numDeclaredEnums,
            const hkClassMember* declaredMembers, int numDeclaredMembers,
            const void* defaults);
    void* m_data[10];
};
"""
def emit(va, A, N):
    parent, name, this = A
    defaults, nmem, members, nenum, enums, nif, ifs, size = N
    src = ("extern hkClass g_%08x;\nextern const char g_%08x[];\n"
           "hkClass g_%08x(g_%08x, &g_%08x, %d, (const hkClass**)%d, %d, (const hkClassEnum*)%d, %d, (const hkClassMember*)%d, %d, (const void*)%d);"
           % (parent, name, this, name, parent, size, ifs, nif, enums, nenum, members, nmem, defaults))
    return src, "??__Eg_%08x@@YAXXZ" % this
