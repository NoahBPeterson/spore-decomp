// Slice s01010190: eastl __adjust_heap over ref-counted game-noun elements, ordered by the
// distance comparator 0x0100dc20 (its 'this' is the 12-byte reference position); it is the
// same algorithm as 0x00fff440 (slice s00ffe860_g7) with the nouns' comparator and push-heap.

struct Vector3_s0101_0190 {
    float x, y, z;
    Vector3_s0101_0190() {}
    Vector3_s0101_0190(const Vector3_s0101_0190& o) : x(o.x), y(o.y), z(o.z) {}
};

struct RefObj_s0101_0190 {
    virtual void AddRef();   // +0x00
    virtual void Release();  // +0x04
};

struct AutoRef_s0101_0190 {
    RefObj_s0101_0190* mpObject;

    AutoRef_s0101_0190(const AutoRef_s0101_0190& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef_s0101_0190() { if (mpObject) mpObject->Release(); }

    AutoRef_s0101_0190& operator=(const AutoRef_s0101_0190& o)
    {
        RefObj_s0101_0190* pNew = o.mpObject;
        RefObj_s0101_0190* old = mpObject;
        if (pNew != old) {
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (old) old->Release();
        }
        return *this;
    }
};

// Distance comparator: 'this' is the reference position (0x0100dc20).
struct NounDistanceLess_s0101_0190 {
    bool Less(RefObj_s0101_0190* a, RefObj_s0101_0190* b) const;
};

static inline bool LessAt_s0101_0190(const Vector3_s0101_0190& pos, RefObj_s0101_0190* a, RefObj_s0101_0190* b)
{
    return ((const NounDistanceLess_s0101_0190*)&pos)->Less(a, b);
}

// Push-heap (0x0100f130); cdecl.
void PushHeap_s0101_0190(AutoRef_s0101_0190* base, int top, int hole, AutoRef_s0101_0190 value, Vector3_s0101_0190 pos);

// @ 0x01010190
void AdjustHeap_s0101_0190(AutoRef_s0101_0190* first, int top, int len, int hole, AutoRef_s0101_0190 value,
                           Vector3_s0101_0190 pos)
{
    int child = hole * 2 + 2;
    while (child < len) {
        if (LessAt_s0101_0190(pos, first[child].mpObject, first[child - 1].mpObject))
            --child;
        first[hole] = first[child];
        hole = child;
        child = child * 2 + 2;
    }
    if (child == len) {
        first[hole] = first[child - 1];
        hole = child - 1;
    }
    PushHeap_s0101_0190(first, top, hole, value, pos);
}
