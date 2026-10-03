// Small container/vector helpers and a Catmull-Rom spline evaluator.
// Built without optimization: /Od /Ob1 /arch:SSE (frame pointer, movss float copies).
#include "types.h"
#include <new>

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) { x = a; y = b; z = c; }
    Vector3(const Vector3& o) { x = o.x; y = o.y; z = o.z; }
};

// Out-of-line Vector3 operators implemented elsewhere in the image.
Vector3 operator+(const Vector3& a, const Vector3& b);   // 0x0041dc10
Vector3 operator-(const Vector3& a, const Vector3& b);   // 0x0041db10
Vector3 operator*(const float& s, const Vector3& v);     // 0x0041de40
Vector3 operator*(const Vector3& v, const float& s);     // 0x0041dca0

// @ 0x00422020
Vector3 operator-(const Vector3& v)
{
    Vector3 r(-v.x, -v.y, -v.z);
    return r;
}

// ---- vector<T>::push_back for various element types ----------------------

struct Item24 { uint32_t d[6]; Item24(const Item24& o) throw(); };   // copy ctor at 0x00511140
struct Item12 { float x, y, z; Item12(const Item12& o) throw() : x(o.x), y(o.y), z(o.z) {} };
struct Item20 { uint32_t d[5]; };

struct Item24Vec {
    Item24* mpBegin; Item24* mpEnd; Item24* mpCapacity;
    void DoPushBackAux(Item24* pos, const Item24& v);        // 0x00427640
    void ReleaseScratch() { int unused0, unused1; }
    void push_back(const Item24& v);
};

// @ 0x00421fb0
void Item24Vec::push_back(const Item24& v)
{
    if (mpEnd < mpCapacity) {
        ::new(mpEnd++) Item24(v);
        ReleaseScratch();
    } else
        DoPushBackAux(mpEnd, v);
}

struct Item12Vec {
    Item12* mpBegin; Item12* mpEnd; Item12* mpCapacity;
    void DoPushBackAux(Item12* pos, const Item12& v);        // 0x00427c70
    void push_back(const Item12& v);
};

// @ 0x004220b0
void Item12Vec::push_back(const Item12& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) Item12(v);
    else
        DoPushBackAux(mpEnd, v);
}

struct IntVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCapacity;
    void DoPushBackAux(uint32_t* pos, const uint32_t& v);    // 0x004281d0
    void push_back(const uint32_t& v);
};

// @ 0x00422380
void IntVec::push_back(const uint32_t& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) uint32_t(v);
    else
        DoPushBackAux(mpEnd, v);
}

struct Item20Vec {
    Item20* mpBegin; Item20* mpEnd; Item20* mpCapacity;
    void DoPushBackAux(Item20* pos, const Item20& v);        // 0x00428900
    void push_back(const Item20& v);
};

// @ 0x004227f0
void Item20Vec::push_back(const Item20& v)
{
    if (mpEnd < mpCapacity)
        ::new(mpEnd++) Item20(v);
    else
        DoPushBackAux(mpEnd, v);
}

// ---- 48-byte element vector -------------------------------------------------

struct Item48 { uint32_t d[12]; Item48() {} };
struct Dummy12 { uint32_t a, b, c; };

struct Item48Vec {
    Item48* mpBegin; Item48* mpEnd; Item48* mpCapacity;
    void DestroyRange();
    void DoFree();                                           // 0x00428130
    void DoInsert(Item48* pos, uint32_t n, const Item48& v); // 0x0042b600
    void EraseRange(Item48* first, Item48* last);            // 0x00501d70
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void insert(Item48* pos, uint32_t n, const Item48& v) { DoInsert(pos, n, v); }
    void ReleaseScratch() { int u0, u1, u2, u3, u4, u5; }
    void resize(uint32_t n);
};

// @ 0x004222a0
void Item48Vec::DestroyRange()
{
    for (Item48* p = mpBegin; p < mpEnd; ++p) { Dummy12 d; }
    DoFree();
}

// @ 0x004222e0
void Item48Vec::resize(uint32_t n)
{
    if (n > size()) {
        insert(mpEnd, n - size(), Item48());
        ReleaseScratch();
    } else
        EraseRange(mpBegin + n, mpEnd);
}

// ---- callback registration thunks ------------------------------------------

void Callback_004280f0();
void Callback_00428190();

struct Registry {
    void Register(void (*fn)(), int arg);                    // 0x0068f9f0
    void AddA(int arg);
    void AddB(int arg);
};

// @ 0x00422280
void Registry::AddA(int arg) { Register(Callback_004280f0, arg); }

// @ 0x00422360
void Registry::AddB(int arg) { Register(Callback_00428190, arg); }

// ---- tiny polymorphic holders ----------------------------------------------

void Handler_00428410();
void Handler_00428490();
void Handler_004288c0();
struct HolderA { void (*mpHandler)(); int m; void Init(int v); };
struct HolderB { void (*mpHandler)(); int m; void Init(int v); };
struct HolderC { void (*mpHandler)(); int m; void Init(int v); };

// @ 0x004223f0
void HolderA::Init(int v) { mpHandler = Handler_00428410; m = v; }

// @ 0x00422410
void HolderB::Init(int v) { mpHandler = Handler_00428490; m = v; }

// @ 0x004227d0
void HolderC::Init(int v) { mpHandler = Handler_004288c0; m = v; }

// ---- lower_bound on 12-byte records keyed by first dword -------------------

struct KeyRec { uint32_t key, a, b; };

inline bool KeyLess(uint32_t a, uint32_t b) { return a < b; }

// @ 0x00422430
KeyRec* LowerBound(KeyRec* first, KeyRec* last, const KeyRec& value)
{
    int n = (int)(last - first);
    while (n > 0) {
        KeyRec* mid = first;
        int half = n >> 1;
        mid += half;
        int unused;
        if (KeyLess(mid->key, value.key)) {
            ++mid;
            first = mid;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// ---- Catmull-Rom spline ----------------------------------------------------

// @ 0x004224b0
Vector3 CatmullRom(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Vector3& p3, float t)
{
    return Vector3(0.5f * (2.0f * p1
                   + (-p0 + p2) * t
                   + (2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t
                   + (-p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t));
}

// ---- wide string helpers ---------------------------------------------------

struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd;
    void DoAssign(wchar_t* dst, const wchar_t* b, const wchar_t* e);   // 0x00428b90
    void DoErase(wchar_t* b, wchar_t* e);                              // 0x0042e2f0
    WString& Replace(uint32_t pos, const wchar_t* s);
    WString& Erase(uint32_t pos, uint32_t n);
};

// @ 0x00422880
WString& WString::Replace(uint32_t pos, const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e) ++e;
    int len = (int)(e - s);
    DoAssign(mpBegin + pos, s, s + len);
    return *this;
}

// @ 0x004228e0
WString& WString::Erase(uint32_t pos, uint32_t n)
{
    uint32_t rem = (uint32_t)(mpEnd - mpBegin) - pos;
    const uint32_t* m = (rem < n) ? &rem : &n;
    DoErase(mpBegin + pos, mpBegin + pos + *m);
    return *this;
}

// ---- fixed-capacity vector constructor -------------------------------------

struct FixedAllocator {
    uint32_t mFlags;
    void* mpPool;
    uint32_t mReserved;
    FixedAllocator(void* const& pool) { mpPool = pool; }
};

inline uint32_t* NullPtr() { int unused0, unused1; return 0; }

struct FixedVecBase {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    FixedAllocator mAllocator;
    FixedVecBase(void* const& pool)
        : mpBegin(NullPtr()), mpEnd(0), mpCapacity(0), mAllocator(pool) {}
    void DoInit(uint32_t n, const uint32_t& value);          // 0x0042bfa0
    void Init(uint32_t n, int value) { DoInit(n, value); }
};

struct FixedVec64 : FixedVecBase {
    uint32_t mBuffer[64];
    FixedVec64(uint32_t n, int value);
};

// @ 0x00422740
FixedVec64::FixedVec64(uint32_t n, int value)
    : FixedVecBase(mBuffer)
{
    mpBegin = mpEnd = mBuffer;
    mpCapacity = mpBegin + 64;
    Init(n, value);
}

// ---- filtered iteration over 20-byte records --------------------------------

struct Key3 { uint32_t x, y, z; };

struct Rec {
    Key3 key;            // +0x00
    uint32_t id;         // +0x0c
    uint16_t pad;        // +0x10
    uint16_t tag;        // +0x12
};

struct Head {            // identity block compared against Rec::id / Rec::tag
    uint32_t id;         // +0x00
    uint16_t pad;        // +0x04
    uint16_t tag;        // +0x06
};

inline bool KeyEqual(const Key3& a, const Key3& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

struct RecMatcher {
    const Head* mpHead;
    const Key3* mpKey;
    bool operator()(const Rec* r) const;
};

// @ 0x004221f0
bool RecMatcher::operator()(const Rec* r) const
{
    return r->id == mpHead->id && r->tag == mpHead->tag && KeyEqual(r->key, *mpKey);
}

struct Cursor {
    Rec* cur;
    uint32_t a, b, c;
    Cursor(const Cursor& o);                                  // 0x00420050
    Rec* Deref() const;                                       // 0x005658b0
    bool operator==(const Cursor& o) const { return cur == o.cur; }
};

struct RecIter {
    Rec* node;
    Cursor cursor;
    Rec* mpEnd0;
    Rec* mpEnd1;
    RecIter(const RecIter& o) : node(o.node), cursor(o.cursor), mpEnd0(o.mpEnd0), mpEnd1(o.mpEnd1) {}
    RecIter& operator++();                                    // 0x00421f00
    Rec* operator*() const { return cursor.Deref(); }
};

inline bool IterEqual(const RecIter& a, const RecIter& b)
{
    return a.node == b.node && (a.node == a.mpEnd1 || a.cursor == b.cursor);
}

inline bool IterNotEqual(const RecIter& a, const RecIter& b) { return !IterEqual(a, b); }

inline void Advance(RecIter& it) { int unused; ++it; }

// @ 0x00422140
RecIter FindIf(RecIter first, RecIter last, RecMatcher pred)
{
    while (IterNotEqual(first, last) && !pred(*first))
        Advance(first);
    return first;
}
