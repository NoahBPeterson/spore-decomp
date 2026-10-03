# int f(S* p, int id): switch(id){K0: K1; K2: *p=fnA, K3} then inline base(p,id){ !p->f && id==K4 -> K5; *p=basefn; -1 }
# A[0]=base fn ptr, A[1]=-1 (or eax,-1), A[2]=specific fn ptr.
PATTERN = 'mov ecx, dword ptr [esp + N] ; cmp ecx, N ; je +N ; mov eax, dword ptr [esp + N] ; cmp ecx, N ; je +N ; cmp dword ptr [eax + N], N ; jne +N ; cmp ecx, N ; jne +N ; mov eax, N ; ret  ; mov dword ptr [eax], A ; or eax, A ; ret  ; mov dword ptr [eax], A ; mov eax, N ; ret  ; mov eax, N ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    # switch(id){15,27} then an inlined base handler (p[4]==0 && id==28 -> 59; else *p=base vptr, -1).
    # The switch + inline-base split is what hoists the p load above the 27 compare.
    src = ("struct S_%08x { void* vp; int a, b, c; int f; };\n"
           "inline int base_%08x(S_%08x* p, int id) {\n"
           "  if (p->f == 0 && id == %d) return %d;\n"
           "  p->vp = (void*)0x%08xu; return -1;\n}\n"
           "int FUN_%08x(S_%08x* p, int id) {\n"
           "  switch (id) {\n"
           "  case %d: return %d;\n"
           "  case %d: p->vp = (void*)0x%08xu; return %d;\n"
           "  }\n"
           "  return base_%08x(p, id);\n}\n"
           % (va, va, va, N[6], N[7], A[0], va, va, N[1], N[9], N[3], A[2], N[8], va))
    return src, "?FUN_%08x@@YAHPAUS_%08x@@H@Z" % (va, va)
