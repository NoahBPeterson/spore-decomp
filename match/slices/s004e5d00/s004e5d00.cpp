// w1g1 slice s004e5d00 -- editor capability/property id helpers.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

// 12-byte vector of refcounted elements; dtor at 0x004b5440.
struct RefVec {
    void* mBegin;
    void* mEnd;
    void* mCap;
    RefVec() { mBegin = 0; mEnd = 0; mCap = 0; }
    ~RefVec();
};

struct VerbSink {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void Deliver(RefVec* v); // vtable +0x14
};

void FillRefVec6720(void* owner, RefVec* out); // 0x004e6720
void FillRefVec6a10(void* owner, RefVec* out); // 0x004e6a10

// @ 0x004e6920
// Maps a capability/ability hash to its property-id hash (0 if unknown).
uint32_t GetPropIDForAbilityHash(uint32_t id)
{
    switch (id) {
    case 0xab97cd36: return 0x66783b4;
    case 0x91c3bf70: return 0x11b79302;
    case 0x9052db45: return 0x4d18efd;
    case 0x8a30ddc4: return 0x11b79a71;
    case 0xefd1720c: return 0x11b79a72;
    case 0x2d94dcd7: return 0x32f92e6;
    case 0xb40fb63b: return 0x11b79a75;
    case 0x6701d2bb: return 0x11b79a76;
    case 0x2b2d090b: return 0x11b79a77;
    case 0x2bfee57a: return 0xb3e30313;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Skeletons for the remaining /Od bodies.
// ---------------------------------------------------------------------------

// @ 0x004e5d00
// 2585-byte /Od editor verb/capability builder.  Skeleton.
void BuildVerbCapabilities(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e6720
// 506-byte /Od collector into a vector.  Skeleton.
void Collect6720(void* owner, void* vec)
{
    (void)owner; (void)vec;
}

// @ 0x004e6a10
// 431-byte /Od per-entry updater.  Skeleton.
void UpdateEntry6a10(void* owner, void* vec)
{
    (void)owner; (void)vec;
}

// @ 0x004e6bc0
// Builds a refcounted vector from the owner and dispatches it through a sink.
void BuildDispatch6bc0(void* owner, VerbSink* sink)
{
    RefVec vec;
    FillRefVec6720(owner, &vec);
    sink->Deliver(&vec);
}

// @ 0x004e6c10
// Guarded variant of the above.
void BuildDispatch6c10(void* owner, VerbSink* sink)
{
    if (owner != 0) {
        RefVec vec;
        FillRefVec6a10(owner, &vec);
        sink->Deliver(&vec);
    }
}
