# Dynamic initializer of a file-scope Havok hkClass with both declared enums and members
# (e.g. hkConstraintDataClass): ten pushed ctor args then mov ecx,&g; call hkClass::hkClass; ret.
# Source shape: `hkClass g("name", &parent, size, 0,0, enums, nEnums, members, nMembers, 0);` at /O2,
# out-of-line hkClass ctor. Sibling of hkclass_static_init (which has no enums).
PATTERN = 'push N ; push N ; push A ; push N ; push A ; push N ; push N ; push N ; push A ; push A ; mov ecx, A ; call EXT ; ret '
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
    members, enums, parent, name, this = A
    defaults, nmem, nenum, nif, ifs, size = N
    src = ("extern const hkClassMember g_%08x[];\nextern const hkClassEnum g_%08x[];\nextern hkClass g_%08x;\nextern const char g_%08x[];\n"
           "hkClass g_%08x(g_%08x, &g_%08x, %d, (const hkClass**)%d, %d, g_%08x, %d, g_%08x, %d, (const void*)%d);"
           % (members, enums, parent, name, this, name, parent, size, ifs, nif, enums, nenum, members, nmem, defaults))
    return src, "??__Eg_%08x@@YAXXZ" % this
