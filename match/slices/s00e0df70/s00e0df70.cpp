// Slice s00e0df70 (batch bfs1 #39).  cSPUIMinimapWin helpers.
// 32-bit MSVC 2008 SP1, /O2 /arch:SSE.
//
// The large inlined functions are stubbed (see partial.txt).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

static inline void Release(void* p) {
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[4 / 4])(p);
}
static inline void AddRef(void* p) {
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[0 / 4])(p);
}

// ===========================================================================
//  0x00e0e9a0  destructor over an array of 0x14-byte records
// ===========================================================================
// @ 0x00e0e9a0
void __stdcall e0e9a0(u32 begin, u32 end) {
    if (begin < end) {
        u32 n = ((end - begin) - 1) / 0x14 + 1;
        char* e = (char*)begin + 0xc;
        do {
            void* p1 = *(void**)(e + 4);
            if (p1) Release(p1);
            void* p0 = *(void**)(e + 0);
            if (p0) Release(p0);
            e += 0x14;
            --n;
        } while (n != 0);
    }
}

// ===========================================================================
//  0x00e0e9f0  eastl::lower_bound<SP::cDataSerializationInfo>
// ===========================================================================
struct DataInfo {
    u32   mKey;                  // +0x00
    char  pad_04[0x10];
};
// @ 0x00e0e9f0
DataInfo* __cdecl lower_bound_DataInfo(DataInfo* first, DataInfo* last, u32* value) {
    int n = (int)(last - first);
    while (n > 0) {
        int half = n >> 1;
        DataInfo* mid = first + half;
        if (mid->mKey < *value) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// ===========================================================================
//  0x00e0ea40  copy-assign with two refcounted members
// ===========================================================================
struct RefHolder {
    void* mp0;                   // +0x00
    u8    b4;                    // +0x04
    char  pad_05[3];
    void* mp8;                   // +0x08
    void* mpc;                   // +0x0c
    RefHolder* operator=(const RefHolder& o);
};
// @ 0x00e0ea40
RefHolder* RefHolder::operator=(const RefHolder& o) {
    mp0 = o.mp0;
    b4 = o.b4;
    if (o.mp8 != mp8) {
        AddRef(o.mp8);
        void* old = mp8;
        mp8 = o.mp8;
        Release(old);
    }
    if (o.mpc != mpc) {
        AddRef(o.mpc);
        void* old = mpc;
        mpc = o.mpc;
        Release(old);
    }
    return this;
}

// ===========================================================================
//  Stubs for the large / complex functions (partial)
// ===========================================================================
// @ 0x00e0df70
bool __fastcall e0df70_code(void* self, int a, int b, int c) { (void)self; (void)a; (void)b; (void)c; return false; }
// @ 0x00e0e0e0
void __cdecl e0e0e0_code(float* out, int* obj) { (void)out; (void)obj; }
// @ 0x00e0e1a0
void __fastcall e0e1a0_code(void* self, int a, int b) { (void)self; (void)a; (void)b; }
// @ 0x00e0e840
void __fastcall build_edge_offsets(void* self) { (void)self; }
// @ 0x00e0eab0
void __fastcall cSPUIMinimapWin_Init(void* self, int a, int b) { (void)self; (void)a; (void)b; }
