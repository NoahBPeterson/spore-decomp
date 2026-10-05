// w1g1 slice s004e5050 -- editor verb-icon helpers around 0x4e5050.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

// An object exposing a property test virtual at vtable offset 0x1c.
struct VerbObject {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual bool HasCategory(int key); // +0x1c
};

bool GetPropertyAsKeyInstance(VerbObject* p, int key, int* out); // 0x006a12a0, cdecl

// @ 0x004e58c0
// SP::EditorUtils::GetVerbCategory: if the object advertises the category key,
// read it back as a key instance and return it, else 0.
int GetVerbCategory(VerbObject* p)
{
    if (p->HasCategory(0x4abbb0d)) {
        int local = 0;
        if (GetPropertyAsKeyInstance(p, 0x4abbb0d, &local))
            return local;
    }
    return 0;
}

// @ 0x004e5910
// SP::EditorUtils::IsDietCategory: true for a fixed set of category hashes.
bool IsDietCategory(int id)
{
    return (id == (int)0xa28a67e8 || id == 0x2dfb4f9f || id == (int)0xdfa0d6bf ||
            id == (int)0xd9bcb9f0 || id == 0x521a15d5);
}

// ---------------------------------------------------------------------------
// Skeletons for the remaining /Od bodies.
// ---------------------------------------------------------------------------

// @ 0x004e5050
// 293-byte /Od editor verb-icon key builder.  Skeleton.
void GetVerbIconKeyForModelType(void* modelType, void* out)
{
    (void)modelType; (void)out;
}

// @ 0x004e5180
// 646-byte /Od body.  Skeleton.
void VerbIconBody5180(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e5410
// 991-byte /Od body.  Skeleton.
void VerbIconBody5410(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e57f0
// 207-byte /Od bit-set predicate.  Skeleton.
bool VerbIconPredicate57f0(void* self)
{
    (void)self;
    return false;
}

// @ 0x004e5960
// 915-byte /Od body.  Skeleton.
void VerbIconBody5960(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
