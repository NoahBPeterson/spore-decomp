// Slice s00f2b3d0: EASTL container internals (vector/hashtable instantiations for
// EA::ResourceMan::Key and a ~0x188-byte element type).  Optimized module:
//   /O2 /MD /Gy /EHsc /TP
//
// FUN_00f2b3d0..FUN_00f2c330 are template instantiations of eastl::vector,
// eastl::hashtable and the range algorithms over a 0x188-byte element.  The exact
// element/allocator types are not recovered here; the two self-contained functions
// (FUN_00f2bd10, FUN_00f2bcb0) are reconstructed, the rest are skeletons.
typedef unsigned int uint32_t;
void operator_delete__(void*);
void FUN_00dfaaf0(void*, void*);

// ---------------------------------------------------------------------------
// @ 0x00f2bd10  Constructor of a 0x188-byte container with a 0x154-byte inline
// buffer at +0x30 (begin/end/capacity at +0x18/+0x1c/+0x20).
// ---------------------------------------------------------------------------
struct Container188 {
    int f0; int f4; int f8; int fc;
    char f10; int f14; void* b18; void* e1c; void* c20; int f24; int f28; int f2c;
    char buf[0x154];
    int f184;
    Container188();
};

// @ 0x00f2bd10
Container188::Container188() {
    int neg = -1;
    f0 = 0;
    fc = 0;
    f4 = neg;
    f8 = neg;
    f10 = 1;
    f14 = 0;
    f2c = 0;
    b18 = buf;
    e1c = b18;
    c20 = (char*)b18 + 0x154;
    f184 = neg;
}

// ---------------------------------------------------------------------------
// @ 0x00f2bcb0  Range destructor/relocate over a contiguous array of 0x188-byte
// elements: destroys the member vector at +0x18 and frees its buffer.
// ---------------------------------------------------------------------------
struct Big188 {
    char pad0[0x18];
    void* f18;
    void* f1c;
    char pad1[0x188 - 0x20];
};

// @ 0x00f2bcb0
char* FUN_00f2bcb0(Big188* first, Big188* last, char* out) {
    while (first != last) {
        FUN_00dfaaf0(first->f18, first->f1c);
        void* q = first->f18;
        if (q != 0 && *(int*)((char*)q - 4) != 0) {
            operator_delete__(q);
        }
        first = (Big188*)((char*)first + 0x188);
        out += 0x188;
    }
    return out;
}

// ---------------------------------------------------------------------------
// Remaining EASTL instantiations.  Reconstructed at skeleton level only: the exact
// container/element types were not recovered, so these are listed in partial.txt.
// ---------------------------------------------------------------------------
// @ 0x00f2b3d0
char FUN_00f2b3d0() { return 0; }

// @ 0x00f2b4f0
void FUN_00f2b4f0() {}

// @ 0x00f2b690
void FUN_00f2b690() {}

// @ 0x00f2b790
void FUN_00f2b790() {}

// @ 0x00f2b8d0
void FUN_00f2b8d0() {}

// @ 0x00f2b9f0
void* FUN_00f2b9f0(void*) { return 0; }

// @ 0x00f2ba80
void FUN_00f2ba80() {}

// @ 0x00f2bbd0
void FUN_00f2bbd0() {}

// @ 0x00f2bd50
void FUN_00f2bd50() {}

// @ 0x00f2c070
void FUN_00f2c070() {}

// @ 0x00f2c330
void FUN_00f2c330() {}
