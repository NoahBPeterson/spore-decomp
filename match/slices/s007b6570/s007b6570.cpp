// Slice s007b6570 - cThumbnailManager job plumbing (refcounted render jobs).

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

struct ItemList2 {
    char pad0[0x20];
    IItem** begin;      // +0x20
    IItem** end;        // +0x24
    void Other();
    void Fn(int a, int b, int c, int d);
};

// @ 0x007b6a90
void ItemList2::Fn(int a, int b, int c, int d)
{
    if (begin != end) {
        int n = end - begin;
        for (unsigned i = 0; i < (unsigned)n; i++) {
            IItem* item = begin[i];
            IOut* out = (IOut*)item->Get();
            out->Run(a, b, c, d);
        }
    }
    Other();
}

// ---------------------------------------------------------------------------
// Remaining functions are EH constructors/destructors or refcount-heavy job
// helpers; recorded as partial skeletons in partial.txt.
// ---------------------------------------------------------------------------

// @ 0x007b6570  (partial)
void partial_007b6570(void) {}
// @ 0x007b6730  (partial)
void partial_007b6730(void) {}
// @ 0x007b68f0  (partial)
void partial_007b68f0(void) {}
// @ 0x007b6980  (partial)
void partial_007b6980(void) {}
// @ 0x007b6b60  (partial)
void partial_007b6b60(void) {}
// @ 0x007b6bd0  (partial)
void partial_007b6bd0(void) {}
// @ 0x007b6c70  (partial)
void partial_007b6c70(void) {}
// @ 0x007b6d50  (partial)
void partial_007b6d50(void) {}
// @ 0x007b7270  (partial)
void partial_007b7270(void) {}
