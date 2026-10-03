# Member getter: it = (this+OFF).find(key); return it != end() ? it->second : 0, where find() is an
# external hashtable method returning iterator (node, bucket) via hidden pointer; key by value (4 or 8 bytes).
PATTERN = 'sub esp, N ; push esi ; lea esi, [ecx + N] ; lea eax, [esp + N] ; push eax ; lea ecx, [esp + N] ; push ecx ; mov ecx, esi ; call EXT ; mov edx, dword ptr [esi + N] ; mov ecx, dword ptr [esi + N] ; mov eax, dword ptr [esp + N] ; pop esi ; cmp eax, dword ptr [ecx + edx*N] ; je +N ; mov eax, dword ptr [eax + N] ; add esp, N ; ret N ; xor eax, eax ; add esp, N ; ret N'
FLAGS = ["/O2", "/MD", "/Gy", "/EHsc", "/TP", "/GR-"]
PRELUDE = ""
def emit(va, A, N):
    off, voff, ks = N[1], N[8], N[10]
    t = "Owner_%08x" % va
    src = '''
typedef %(kt)s Key_%(v)08x;
struct %(t)s {
    struct node { unsigned pad[%(p)d]; unsigned v; };
    struct iterator { node* mpNode; node** mpBucket; };
    struct HT {
        int f; node** mpBucketArray; unsigned mnBucketCount; unsigned cnt;
        iterator end() { iterator i; i.mpNode = mpBucketArray[mnBucketCount]; i.mpBucket = mpBucketArray + mnBucketCount; return i; }
        iterator find(const Key_%(v)08x& k);
    };
    char pad[%(off)d]; HT ht;
    unsigned get(Key_%(v)08x k);
};
unsigned %(t)s::get(Key_%(v)08x k) {
    %(t)s::iterator it = ht.find(k);
    if (it.mpNode != ht.end().mpNode) return it.mpNode->v;
    return 0;
}
''' % dict(v=va, t=t, kt='unsigned' if ks == 4 else 'unsigned __int64', p=voff // 4, off=off)
    return src, "?get@%s@@QAE%sI%s@Z" % (t, "I" if ks == 4 else "_K", "") if False else "?get@%s@@QAEI%s@Z" % (t, "I" if ks == 4 else "_K")
