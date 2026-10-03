# Dynamic initializer of a file-scope Havok hkClass reflection object (e.g. hkBvShapeClass):
# ten pushed ctor args then mov ecx,&g; call hkClass::hkClass; ret (no atexit: trivial dtor).
# Source shape: `hkClass g("name", &parentClass, size, 0,0, 0,0, members, nMembers, 0);` at /O2,
# with an out-of-line hkClass ctor. Push order (reversed): defaults, nMembers, members, nEnums,
# enums, nIfaces, ifaces, size, parent, name.
PATTERN = 'push N ; push N ; push A ; push N ; push N ; push N ; push N ; push N ; push A ; push A ; mov ecx, A ; call EXT ; ret '
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
    members, parent, name, this = A
    defaults, nmem, nenum, enums, nif, ifs, size = N
    src = ("extern const hkClassMember g_%08x[];\nextern hkClass g_%08x;\nextern const char g_%08x[];\n"
           "hkClass g_%08x(g_%08x, &g_%08x, %d, (const hkClass**)%d, %d, (const hkClassEnum*)%d, %d, g_%08x, %d, (const void*)%d);"
           % (members, parent, name, this, name, parent, size, ifs, nif, enums, nenum, members, nmem, defaults))
    return src, "??__Eg_%08x@@YAXXZ" % this
