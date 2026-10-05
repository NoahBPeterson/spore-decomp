// Slice s007b49f0 - cThumbnailManager helpers and a bounds-expansion helper.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (SSE1, comiss, no movq).

struct Vector3 { float x, y, z; };

struct Bounds6 {
    Vector3 mn;
    Vector3 mx;
    void Expand(const Vector3* p, int n, int stride);
};

// @ 0x007b4c10
void Bounds6::Expand(const Vector3* p, int n, int stride)
{
    n = n - 1;
    if (n >= 0) {
        do {
            if (mn.x > mx.x) {
                mn = *p;
                mx = *p;
            } else {
                if (mn.x > p->x) mn.x = p->x; else if (p->x > mx.x) mx.x = p->x;
                if (mn.y > p->y) mn.y = p->y; else if (p->y > mx.y) mx.y = p->y;
                if (mn.z > p->z) mn.z = p->z; else if (p->z > mx.z) mx.z = p->z;
            }
            p = (const Vector3*)((const char*)p + stride);
            n = n - 1;
        } while (n >= 0);
    }
}

struct IItem {
    virtual void a0();
    virtual void a1();
    virtual void a2();
    virtual void a3();
    virtual void* Get();
};

struct IOut {
    virtual void b0();
    virtual void b1();
    virtual void b2();
    virtual void Run(int a, int b, int c, int d);
};

struct ItemList {
    char pad0[0xc];
    IItem** begin;      // +0xc
    IItem** end;        // +0x10
    void Fn(int a, int b, int c, int d);
};

// @ 0x007b49f0
void ItemList::Fn(int a, int b, int c, int d)
{
    int n = end - begin;
    for (unsigned i = 0; i < (unsigned)n; i++) {
        IItem* item = begin[i];
        IOut* out = (IOut*)item->Get();
        out->Run(a, b, c, d);
    }
}

// ---------------------------------------------------------------------------
// The remaining functions of this slice are large EH constructors/destructors
// and refcount-heavy cThumbnailManager methods; their skeletons live in
// partial.txt.  Nothing below is claimed byte-exact.
// ---------------------------------------------------------------------------

// @ 0x007b4a50  (partial - refcounted render-target helper; not reconstructed)
void partial_007b4a50(void) {}

// @ 0x007b4b10  (partial - terrain filter setup; not reconstructed)
void partial_007b4b10(void) {}

// @ 0x007b4cd0  (partial - EH destructor; not reconstructed)
void partial_007b4cd0(void) {}

// @ 0x007b4d70  (partial - EH destructor; not reconstructed)
void partial_007b4d70(void) {}

// @ 0x007b4e10  (partial - EH constructor; not reconstructed)
void partial_007b4e10(void) {}

// @ 0x007b4ee0  (partial - cThumbnailManager constructor; not reconstructed)
void partial_007b4ee0(void) {}

// @ 0x007b5090  (partial - ~cThumbnailManager; not reconstructed)
void partial_007b5090(void) {}

// @ 0x007b5320  (partial - FrameBoundingBoxPalette; not reconstructed)
void partial_007b5320(void) {}

