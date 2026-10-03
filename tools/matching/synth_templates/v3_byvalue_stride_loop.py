# Loop calling a cdecl callee(first,last,Vector3 by value) while ((last-first)&-4) > 4, last -= 4.
# Needs /arch:SSE (movss copies) and the condition recomputed in the loop header (spelling 'e').
PATTERN = 'push ebx ; mov ebx, dword ptr [esp + N] ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, esi ; sub edi, ebx ; mov eax, edi ; and eax, A ; cmp eax, N ; jle +N ; lea esp, [esp] ; movss xmm0, dword ptr [esp + N] ; sub esp, N ; mov eax, esp ; movss dword ptr [eax], xmm0 ; movss xmm0, dword ptr [esp + N] ; movss dword ptr [eax + N], xmm0 ; movss xmm0, dword ptr [esp + N] ; push esi ; push ebx ; movss dword ptr [eax + N], xmm0 ; call EXT ; sub edi, N ; mov ecx, edi ; and ecx, A ; add esp, N ; sub esi, N ; cmp ecx, N ; jg +N ; pop edi ; pop esi ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/arch:SSE"]
PRELUDE = "struct V3 { float x,y,z; V3(const V3&o):x(o.x),y(o.y),z(o.z){} };\n"
def emit(va, A, N):
    return ("void callee_%08x(int first,int last,V3 v);\n"
            "void FUN_%08x(int first,int last,V3 v){\n"
            "  for(; ((last-first)&-4)>4; ){ callee_%08x(first,last,v); last-=4; }\n}" % (va, va, va)), "?FUN_%08x@@YAXHHUV3@@@Z" % va
