# Static class-registration thunk: obj.Register(name, &desc, FNVHash(name, 0x811c9dc5, 1), size, 0,0,0,0,0,0)
# FNVHash is cdecl (3 args); Register is a __thiscall member on a global object, 10 args.
PATTERN = 'push N ; push N ; push N ; push N ; push N ; push N ; push N ; push N ; push A ; push A ; call EXT ; add esp, N ; push eax ; push A ; push A ; mov ecx, A ; call EXT ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''
typedef unsigned int u32;
extern "C++" u32 FNVHash(const char* s, u32 seed, int flags);
struct ClassRegistry {
    void Register(const char* name, void* desc, u32 hash, u32 size, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f);
};
'''
def emit(va, A, N):
    seed, s, d, s2, o = A
    z = N[:6]
    size, flag = N[6], N[7]
    gs, gd, go = "g_%08x" % s, "g_%08x" % d, "g_%08x" % o
    src = ("extern const char %s_%08x[];\nextern char %s_%08x;\nextern ClassRegistry %s_%08x;\n"
           "void FUN_%08x() { %s_%08x.Register(%s_%08x, &%s_%08x, FNVHash(%s_%08x, 0x%xu, %d), 0x%x, %d, %d, %d, %d, %d, %d); }"
           % (gs, va, gd, va, go, va, va, go, va, gs, va, gd, va, gs, va, seed, flag, size,
              z[5], z[4], z[3], z[2], z[1], z[0]))
    return src, "?FUN_%08x@@YAXXZ" % va
