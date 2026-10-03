# float F(Owner* o): r = o->sub.Lookup(0, 0x40000); return r && r->state == K ? 1.0f : 0.0f
# cdecl, x87 return (fld1/fldz), thiscall callee on embedded subobject at +8 of field at 0xb4c.
PATTERN = 'mov eax, dword ptr [esp + N] ; mov ecx, dword ptr [eax + N] ; push N ; push N ; add ecx, N ; call EXT ; test eax, eax ; je +N ; cmp dword ptr [eax + N], N ; jne +N ; fld1  ; ret  ; fldz  ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""

def emit(va, A, N):
    # N: [4, field_off, 0x40000, 0, sub_off, state_off, k]
    fo, sub, so, k = N[1], N[4], N[5], N[6]
    s = "%08x" % va
    src = ("#pragma pack(push, 1)\n"
           "struct Rec_%s { char pad[0x%x]; int state; };\n"
           "struct Sub_%s { Rec_%s* Lookup(int a, int b); };\n"
           "struct Own_%s { char pad[0x%x]; char* base; };\n"
           "#pragma pack(pop)\n"
           "float FUN_%s(Own_%s* o) {\n"
           "  Rec_%s* r = ((Sub_%s*)(o->base + 0x%x))->Lookup(0, 0x40000);\n"
           "  if (r && r->state == %d) return 1.0f;\n"
           "  return 0.0f;\n}" % (s, so, s, s, s, fo, s, s, s, s, sub, k))
    return src, "?FUN_%s@@YAMPAUOwn_%s@@@Z" % (s, s)
