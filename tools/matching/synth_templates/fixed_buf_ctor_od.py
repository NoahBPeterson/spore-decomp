# Fixed-capacity inline-buffer container ctor in /Od module: begin/end/cap = 0, [5]=0,
# then begin=this+0x18, end=begin, cap=begin+bytes. Returns this.
PATTERN = 'push ebp ; mov ebp, esp ; sub esp, N ; mov dword ptr [ebp - N], ecx ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax], N ; mov ecx, dword ptr [ebp - N] ; mov dword ptr [ecx + N], N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], N ; mov eax, dword ptr [ebp - N] ; mov dword ptr [eax + N], N ; mov ecx, dword ptr [ebp - N] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx], ecx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [ebp - N] ; mov edx, dword ptr [ecx] ; mov dword ptr [eax + N], edx ; mov eax, dword ptr [ebp - N] ; mov ecx, dword ptr [eax] ; add ecx, N ; mov edx, dword ptr [ebp - N] ; mov dword ptr [edx + N], ecx ; mov eax, dword ptr [ebp - N] ; mov esp, ebp ; pop ebp ; ret '
FLAGS = ["/Od", "/Ob1", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = ""
def emit(va, A, N):
    cap = N[-4]
    c = "FixedBuf_%08x" % va
    return ("struct %s { char* b; char* e; char* c; int p3; int p4; int x; %s(); };\n"
            "%s::%s() {\n  char* unused; b = 0; e = 0; c = 0; x = 0;\n"
            "  b = (char*)this + 0x18; e = b; c = b + %d;\n}" % (c, c, c, c, cap)), "??0%s@@QAE@XZ" % c
