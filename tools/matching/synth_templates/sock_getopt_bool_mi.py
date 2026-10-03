# getsockopt(SOL_SOCKET, opt) bool getter in a secondary base (this-8 = primary with vcall slot 1 on error)
PATTERN = 'sub esp, N ; push esi ; mov esi, ecx ; mov edx, dword ptr [esi + N] ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; push ecx ; push N ; push N ; push edx ; mov dword ptr [esp + N], N ; call dword ptr [A] ; test eax, eax ; je +N ; push edi ; mov edi, dword ptr [esi - N] ; add esi, -N ; push N ; call dword ptr [A] ; push eax ; mov eax, dword ptr [edi + N] ; mov ecx, esi ; call eax ; pop edi ; xor al, al ; pop esi ; add esp, N ; ret N ; cmp dword ptr [esp + N], N ; mov edx, dword ptr [esp + N] ; setne cl ; mov byte ptr [edx], cl ; mov al, N ; pop esi ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP"]
PRELUDE = """
extern "C" {
__declspec(dllimport) int __stdcall getsockopt(unsigned s, int level, int optname, char* optval, int* optlen);
__declspec(dllimport) int __stdcall WSAGetLastError(int);
}
struct SockPrimary { virtual void v0(); virtual void OnError(int code); };
struct SockOpt { unsigned pad; unsigned s; };
"""
def emit(va, A, N):
    opt = N[4]
    return ("""struct SockOpt_%08x : SockOpt { bool __thiscall Get(bool* out); };
bool __thiscall SockOpt_%08x::Get(bool* out) {
    int val; int len = 4;
    if (getsockopt(s, %d, %d, (char*)&val, &len)) {
        ((SockPrimary*)((char*)this - 8))->OnError(WSAGetLastError(0));
        return false;
    }
    *out = val != 0;
    return true;
}""" % (va, va, N[5], opt)), "?Get@SockOpt_%08x@@QAE_NPA_N@Z" % va
