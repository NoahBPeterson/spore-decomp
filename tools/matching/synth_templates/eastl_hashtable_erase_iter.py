# EASTL hashtable erase(iterator) returning next iterator (hidden ret ptr), /O2.
PATTERN = 'mov edx, dword ptr [esp + N] ; mov eax, dword ptr [edx + N] ; push ebx ; push esi ; mov esi, dword ptr [esp + N] ; push edi ; mov edi, dword ptr [esp + N] ; mov ebx, ecx ; mov dword ptr [esi + N], edi ; mov dword ptr [esi], eax ; test eax, eax ; jne +N ; mov ecx, N ; add dword ptr [esi + N], ecx ; mov eax, dword ptr [esi + N] ; mov eax, dword ptr [eax] ; mov dword ptr [esi], eax ; test eax, eax ; je +N ; mov ecx, dword ptr [edi] ; cmp ecx, edx ; jne +N ; mov ecx, dword ptr [ecx + N] ; push edx ; mov dword ptr [edi], ecx ; call EXT ; add esp, N ; dec dword ptr [ebx + N] ; pop edi ; mov eax, esi ; pop esi ; pop ebx ; ret N ; mov eax, dword ptr [ecx + N] ; cmp eax, edx ; je +N ; mov ecx, eax ; mov eax, dword ptr [eax + N] ; cmp eax, edx ; jne +N ; mov eax, dword ptr [eax + N] ; push edx ; mov dword ptr [ecx + N], eax ; call EXT ; dec dword ptr [ebx + N] ; add esp, N ; pop edi ; mov eax, esi ; pop esi ; pop ebx ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = r'''void EASTL_allocator_deallocate(void* p);
'''
# Best so far: 16 bytes differ (callee-saved regs ebx/edi swapped: orig this=ebx,bucket=edi).
def emit(va, A, N):
    off = N[1]
    t = "HT_%08x" % va
    src = ("struct %s {\n"
           "  struct node { char pad[%d]; node* mpNext; };\n"
           "  struct iterator { node* mpNode; node** mpBucket; };\n"
           "  int pad0[3]; unsigned mnElementCount;\n"
           "  iterator erase(iterator i);\n};\n"
           "%s::iterator %s::erase(iterator i) {\n"
           "  node* const n = i.mpNode; node** const b = i.mpBucket;\n"
           "  iterator next; next.mpBucket = b; next.mpNode = n->mpNext;\n"
           "  while(next.mpNode == 0) { ++next.mpBucket; next.mpNode = *next.mpBucket; }\n"
           "  node* pNode = *b;\n"
           "  if(pNode == n) { *b = pNode->mpNext; EASTL_allocator_deallocate(n); --mnElementCount; return next; }\n"
           "  node* pNext = pNode->mpNext;\n"
           "  while(pNext != n) { pNode = pNext; pNext = pNext->mpNext; }\n"
           "  pNode->mpNext = pNext->mpNext;\n"
           "  EASTL_allocator_deallocate(n); --mnElementCount;\n"
           "  return next;\n}") % (t, off, t, t)
    return src, "?erase@%s@@QAE?AUiterator@1@U21@@Z" % t
