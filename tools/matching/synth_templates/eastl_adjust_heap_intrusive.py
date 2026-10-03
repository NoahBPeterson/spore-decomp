# eastl::adjust_heap over intrusive_ptr<T> (vtable[0]=AddRef, [1]=Release) with an empty by-value comparator.
# Source shape: EASTL adjust_heap(first, top, heapSize, position, value, compare); no EH (/EHsc off).
PATTERN = 'push ebx ; push ebp ; mov ebp, dword ptr [esp + N] ; push esi ; lea esi, [ebp + ebp + N] ; cmp esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; jge +N ; mov eax, dword ptr [edi + esi*N - N] ; mov ecx, dword ptr [edi + esi*N] ; push eax ; push ecx ; lea ecx, [esp + N] ; call EXT ; test al, al ; je +N ; dec esi ; mov ecx, dword ptr [edi + ebp*N] ; mov ebx, dword ptr [edi + esi*N] ; mov dword ptr [esp + N], ecx ; cmp ebx, ecx ; je +N ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax] ; mov ecx, ebx ; call edx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [edi + ebp*N], ebx ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; mov ebp, esi ; lea esi, [esi + esi + N] ; cmp esi, dword ptr [esp + N] ; jl +N ; jne +N ; mov ecx, dword ptr [edi + ebp*N] ; mov ebx, dword ptr [edi + esi*N - N] ; mov dword ptr [esp + N], ecx ; cmp ebx, ecx ; je +N ; test ebx, ebx ; je +N ; mov eax, dword ptr [ebx] ; mov edx, dword ptr [eax] ; mov ecx, ebx ; call edx ; mov ecx, dword ptr [esp + N] ; mov dword ptr [edi + ebp*N], ebx ; test ecx, ecx ; je +N ; mov eax, dword ptr [ecx] ; mov edx, dword ptr [eax + N] ; call edx ; lea ebp, [esi - N] ; mov eax, dword ptr [esp + N] ; push eax ; push ecx ; mov ecx, dword ptr [esp + N] ; mov eax, esp ; mov dword ptr [eax], ecx ; mov ecx, dword ptr [esp + N] ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx] ; call eax ; mov ecx, dword ptr [esp + N] ; push ebp ; push ecx ; push edi ; call EXT ; mov ecx, dword ptr [esp + N] ; add esp, N ; test ecx, ecx ; je +N ; mov edx, dword ptr [ecx] ; mov eax, dword ptr [edx + N] ; pop edi ; pop esi ; pop ebp ; pop ebx ; jmp eax ; pop edi ; pop esi ; pop ebp ; pop ebx ; ret '
FLAGS = ["/O2", "/MD", "/Gy", "/TP"]
PRELUDE = """struct Obj { virtual void AddRef(); virtual void Release(); };
struct P {
  Obj* p;
  P(Obj* o=0):p(o){ if(p) p->AddRef(); }
  P(const P& o):p(o.p){ if(p) p->AddRef(); }
  ~P(){ if(p) p->Release(); }
  P& operator=(const P& o){ Obj* n=o.p; Obj* const t=p; if(n!=t){ if(n) n->AddRef(); p=n; if(t) t->Release(); } return *this; }
  operator Obj*() const { return p; }
};
struct Cmp { bool operator()(Obj* a, Obj* b) const; };
"""
def emit(va, A, N):
    s = """void promote_%08x(P* first, int top, int pos, P v, Cmp c);
void FUN_%08x(P* first, int top, int heap, int position, P value, Cmp compare)
{
  int child = 2*position+2;
  while(child < heap){
    if(compare(first[child], first[child-1])) --child;
    first[position] = first[child];
    position = child;
    child = 2*child+2;
  }
  if(child == heap){
    first[position] = first[child-1];
    position = child-1;
  }
  promote_%08x(first, top, position, value, compare);
}""" % (va, va, va)
    return s, "?FUN_%08x@@YAXPAUP@@HHHU1@UCmp@@@Z" % va
