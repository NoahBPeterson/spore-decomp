# Double global initialized from a per-TU double constant (always +inf in this binary), in an
# unoptimized (/Od /Ob1) module:
#   push ebp; mov ebp,esp; fld qword ptr [src]; fstp qword ptr [dst]; pop ebp; ret
# This is the real compiler-generated dynamic initializer ??__E<dst>@@YAXXZ of
#   static const double kInf = 1e300 * 1e300;   // per-TU copy (65 distinct source addresses)
#   double dst = kInf;
# /Od keeps the copy at runtime. (std::numeric_limits<double>::infinity() would be a dllimport call.)
PATTERN = "push ebp ; mov ebp, esp ; fld qword ptr [A] ; fstp qword ptr [A] ; pop ebp ; ret "
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
_defined = set()
def emit(va, A, N):
    src, dst = A[0], A[1]
    s = ""
    if src not in _defined:
        _defined.add(src)
        s += "static const double g_%08x = 1e300 * 1e300;\n" % src
    s += "double g_%08x = g_%08x;" % (dst, src)
    return s, "??__Eg_%08x@@YAXXZ" % dst
