// Slice s00a3af80: 00a3b640. eastl::hash_map<uint32, wstring>-style lookup-or-insert.
// Returns a pointer to the pair's value; inserts a default entry when the key is absent.

typedef unsigned int uint32;

struct WStrPair {
    uint32 first;               // key (+0)
    wchar_t* begin;             // wstring data (+4)
    wchar_t* end;               // (+8)
    wchar_t* cap;               // (+0xc)
};

struct StrMap {
    char pad[4];
    void** mpBucketArray;       // +4
    uint32 mnBucketCount;       // +8
    // hashtable::find(key) returns the node pointer in its first word (+0 of sret)
    void Find(void** outNode, uint32 key);      // thiscall, sret + key, callee pops 8
    // FUN_00b209f0: thiscall on a tmp object, arguments (wstring*, key); returns pointer
    void* Make(wchar_t** strOut, uint32 key);    // placeholder: see notes
    // FUN_00a3b580: thiscall insert, args (out*, ptr, flag byte)
    void Insert(void* out, void* p, unsigned char flag);
};

void operator_delete_(void* p);  // operator delete (FUN_00f47380), cdecl

// @ 0x00a3b640
WStrPair* LookupOrInsert(StrMap* self, uint32 key) {
    void* node = 0;
    self->Find(&node, key);
    if (node != self->mpBucketArray[self->mnBucketCount]) {
        return (WStrPair*)((char*)node + 4);
    }
    wchar_t* sBegin = (wchar_t*)0x1667bac;
    wchar_t* sEnd = (wchar_t*)0x1667bac;
    wchar_t* sCap = (wchar_t*)0x1667bad;
    (void)sEnd; (void)sCap;
    void* tmp = self->Make(&sBegin, key);
    (void)tmp;
    return 0;
}
