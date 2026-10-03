# Dynamic initializer of a file-scope Havok hkClass reflection object with no parent class
# (e.g. hkClassEnumItemClass): ten pushed ctor args (parent = 0) then mov ecx,&g; call
# hkClass::hkClass; ret (no atexit: trivial dtor).
# Source shape: `hkClass g("name", 0, size, 0,0, 0,0, members, nMembers, 0);` at /O2 with an
# out-of-line hkClass ctor. Sibling of hkclass_static_init (which has a non-null parent).
PATTERN = 'push N ; push N ; push A ; push N ; push N ; push N ; push N ; push N ; push N ; push A ; mov ecx, A ; call EXT ; ret '
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
    members, name, this = A
    defaults, nmem, nenum, enums, nif, ifs, size, parent = N
    src = ("extern const hkClassMember g_%08x[];\nextern const char g_%08x[];\n"
           "hkClass g_%08x(g_%08x, (const hkClass*)%d, %d, (const hkClass**)%d, %d, (const hkClassEnum*)%d, %d, g_%08x, %d, (const void*)%d);"
           % (members, name, this, name, parent, size, ifs, nif, enums, nenum, members, nmem, defaults))
    return src, "??__Eg_%08x@@YAXXZ" % this
