// Creature-editor part-list module, 0x0040EB70..0x0040F49B.
//
// Built unoptimized like its neighbours: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast
// (no /EHsc: no EH frames even around the smart-pointer locals).
// /fp:fast is what turns `1.0f / x` into movss/divss instead of fld1/fdivrp.

#include "types.h"
#include <intrin.h>

// Skip N virtual slots of a stub class (each use needs a unique prefix p).
#define VS1(p) virtual void p##_a();
#define VS2(p) VS1(p##0) VS1(p##1)
#define VS4(p) VS2(p##0) VS2(p##1)
#define VS8(p) VS4(p##0) VS4(p##1)
#define VS16(p) VS8(p##0) VS8(p##1)
#define VS32(p) VS16(p##0) VS16(p##1)
#define VS64(p) VS32(p##0) VS32(p##1)

// ---------------------------------------------------------------------------
// Math
// ---------------------------------------------------------------------------
struct M9 {
    float m[9];
};
struct Matrix3 : M9 {
    Matrix3& operator=(const Matrix3& o) {
        M9::operator=(o);
        return *this;
    }
};

struct Vector3 {
    float x, y, z;
    Vector3& operator=(const Vector3& o) {
        x = o.x;
        y = o.y;
        z = o.z;
        return *this;
    }
    Vector3& MulAssign(const Matrix3& m);  // v = v * m
};

Vector3 operator*(const Vector3& v, const Matrix3& m);        // 0x0041DAF0
Vector3& operator*=(Vector3& v, const float& s);              // 0x0041DBA0
Matrix3* Matrix3Inverse(Matrix3* out, const Matrix3* m);      // 0x0041DED0
extern const float kOne;                                      // 0x01485720 (1.0f)

inline Vector3& Vector3::MulAssign(const Matrix3& m) {
    *this = *this * m;
    return *this;
}

// ---------------------------------------------------------------------------
// Per-part transform (0x7C bytes per entry): position, scale, rotation.
// ---------------------------------------------------------------------------
struct Source;

struct PartTransform {
    uint32_t pad0;
    Vector3 mPosition;   // +0x04
    float mScale;        // +0x10
    Matrix3 mRotation;   // +0x14
    uint32_t pad1[(0x74 - 0x38) / 4];
    Source* mpSource;    // +0x74
    uint32_t pad2[(0x7C - 0x78) / 4];

    void Invert();                       // 0x0040EFA0
    Source* GetSource() { return mpSource; }
    void Rebuild(const void* xform);     // 0x00537DC0
};

// @ 0x0040EFA0
void PartTransform::Invert() {
    mScale = kOne / mScale;
    Matrix3 tmp;
    mRotation = *Matrix3Inverse(&tmp, &mRotation);
    mPosition *= -mScale;
    mPosition.MulAssign(mRotation);
}

// ---------------------------------------------------------------------------
// Owner / bitset-flagged refcounted object (0x0040F360)
// ---------------------------------------------------------------------------
struct Counted;
struct CountedOwner {
    VS64(a) VS16(b) VS8(c) VS4(d)             // 92 slots
    virtual void SetBit(Counted* obj, bool bit);  // slot 92 (+0x170)
};

struct Bits32 {
    uint32_t mWord;
    bool Test(unsigned n) const {
        if (n < 32) {
            uint32_t w = mWord;
            return (w & (1u << (n % 32))) != 0;
        }
        return false;
    }
};

struct Counted {
    CountedOwner* mpOwner;
    Bits32 mBits;
    uint32_t pad[(0x40 - 8) / 4];
    int mRefCount;  // +0x40, plain (non-atomic)

    int Release();
};

// @ 0x0040F360
int Counted::Release() {
    if (mRefCount > 1) {
        --mRefCount;
        return mRefCount;
    }
    mpOwner->SetBit(this, mBits.Test(31));
    return 0;
}

// ---------------------------------------------------------------------------
// Part holder object (0x58 bytes, allocated from the "Editor" EASTL pool)
// ---------------------------------------------------------------------------
struct Field0 { uint32_t d[5]; Field0(const Field0&); };   // 0x0041F6C0
struct Field1 { uint32_t d[5]; Field1(const Field1&); };   // 0x0041F840
struct Field2 { uint32_t d[5]; Field2(const Field2&); };   // 0x00535DA0
struct Field3 { uint32_t d[5]; Field3(const Field3&); };   // 0x0041FA20

struct HolderBase {
    virtual void BaseV0();
    long mRefCount;  // +4
    HolderBase() {
        long* target = &mRefCount;
        {
            uint32_t dead[32];  // dead local of the original inline expansion (frame size)
        }
        _InterlockedExchange(target, 0);
    }
};

struct PartHolder : HolderBase {
    Field0 mA;   // +0x08
    Field1 mB;   // +0x1C
    Field2 mC;   // +0x30
    Field3 mD;   // +0x44

    PartHolder(const PartHolder* src);   // 0x0040F070
    virtual void HolderV0();
    void Release();                      // 0x00404F90 (ThreadedObject::Release)
    void AddRef() { _InterlockedIncrement(&mRefCount); }
};

// @ 0x0040F070
PartHolder::PartHolder(const PartHolder* src)
    : mA(src->mA), mB(src->mB), mC(src->mC), mD(src->mD) {}

// ---------------------------------------------------------------------------
// Editor part list (the object whose methods follow)
// ---------------------------------------------------------------------------
struct Messenger {
    VS4(a) VS2(b)                                            // 6 slots
    virtual void Post(unsigned msg, int a, int b, int c);    // slot 6 (+0x18)
};
struct Service2 {
    VS16(a) VS1(b)                                           // 17 slots
    virtual void Run(unsigned id);                           // slot 17 (+0x44)
};
Messenger* GetMessenger();   // 0x0067DCC0
Service2* GetService2();     // 0x0067DDB0

struct PropList;
void __cdecl GetProp(PropList* p, unsigned id, void* out);       // 0x006A12A0
void __cdecl GetBoolProp(PropList* p, unsigned id, bool* out);   // 0x00407190
struct PropList {
    VS8(a) VS1(b)                                            // 9 slots
    virtual bool Find(unsigned id, struct PropValue** out);  // slot 9 (+0x24)
    void Get(unsigned id, void* out) { GetProp(this, id, out); }
    void GetBool(unsigned id, bool* out) { GetBoolProp(this, id, out); }
};
struct PropValue {
    uint32_t pad0[0x12 / 4];
    uint16_t pad1;
    uint16_t mType;  // +0x12
    bool* GetBool();  // 0x0041E920
};

struct Source {
    VS2(a) VS1(b)                                                 // 3 slots
    virtual Counted* Lookup(unsigned a, unsigned b, int c);  // slot 3 (+0x0C)
};

struct Key;  // part resource key
struct Vec8 {
    uint32_t d[3];
};

// pointer vector (begin, end, capacity)
template <class T> struct PtrVec {
    T** mpBegin;
    T** mpEnd;
    T** mpCap;
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    T* At(unsigned i) const {
        T** p = mpBegin + i;
        return *p;
    }
};

struct AllocTag {
    AllocTag() {}
};
struct Alloc {
    uint32_t d[2];
    Alloc() {}
    Alloc(const AllocTag&);            // 0x00429360
};
// small int vector at 0x0041D590
struct IntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCap;
    Alloc mAlloc;
    uint32_t mPad[3];
    IntVec();                       // 0x0041D590
    ~IntVec();                      // 0x004209B0
    void push_back(const int& v);   // 0x00422380
    bool empty() const;             // 0x00526430
    int* data() const {
        uint32_t dead[8];
        {
            int* r = mpBegin;
            return r;
        }
    }
};

struct PartXform38 {
    uint32_t d[0x38 / 4];
};

void* EASTL_allocator_allocate(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00F473A0
inline void* operator new(unsigned size, const char* name) {
    uint32_t dead[1];
    return EASTL_allocator_allocate(size, name, 0, 0, 0, 0);
}

void __cdecl ApplyPart(Key* key, PartXform38* xf, int mode);     // 0x006DBED0
void __cdecl FitPart(PartXform38* xf, Key* key);                 // 0x00734D00
void __cdecl TouchPart(Key* key, int a, int mode);               // 0x007541B0
int __cdecl QueryPart(Key* key, int a, int b, int c, int d);     // 0x0071DDC0
void __cdecl ApplyShapes(Key* key, unsigned count, int* data);   // 0x00738610
void __cdecl Collect(void* vec, Source* src, unsigned key, int flag);  // 0x004303E0
void __cdecl Merge(void* vec, unsigned a, unsigned b, int c, void* d, int e);  // 0x00755810

struct HolderVec {
    uint32_t d[3];
    void push_back(PartHolder** p);   // 0x0041EF20
};
struct KeyVec {
    Key** mpBegin;
    Key** mpEnd;
    Key** mpCap;
    Alloc mAlloc;
    KeyVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    KeyVec(const AllocTag& t) : mpBegin(0), mpEnd(0), mpCap(0), mAlloc(t) {
        {
            uint32_t dead[3];
        }
    }
    ~KeyVec();                         // 0x0041EB80
    void reserve(unsigned n);          // 0x004E0880
    void push_back(Key** p);           // 0x0041EF20
};

template <class T> struct HolderPtr {
    T* mp;
    HolderPtr(T* p) : mp(p) {
        if (mp)
            mp->AddRef();
    }
    ~HolderPtr() {
        if (mp)
            mp->Release();
    }
};

template <class T> struct IntrusivePtr {
    T* mp;
    IntrusivePtr& operator=(T* p) {
        if (p != mp) {
            T* old = mp;
            {
                uint32_t dead[2];
            }
            if (p)
                ++p->mRefCount;
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct EditorPartList {
    uint32_t pad0[0x74 / 4];
    Source* mpSource;                  // +0x074
    Source* GetSource() {
        {
            uint32_t dead[3];
        }
        return mpSource;
    }
    Source* GetSourcePlain() { return mpSource; }
    Source* GetSourceWide() {
        {
            uint32_t dead[4];
        }
        return mpSource;
    }
    uint32_t pad1[(0x238 - 0x78) / 4];
    uint16_t mFlags;                   // +0x238
    uint16_t pad2;
    uint32_t pad3[(0x24C - 0x23C) / 4];
    PropList* mpProps;                 // +0x24C
    uint32_t pad4[(0x338 - 0x250) / 4];
    PtrVec<Key> mKeys;                 // +0x338
    uint32_t pad5[(0x34C - 0x344) / 4];
    HolderVec mHolders;                // +0x34C
    uint32_t pad6[(0x360 - 0x358) / 4];
    unsigned char* mpEnabled;          // +0x360
    uint32_t pad7[(0x374 - 0x364) / 4];
    PartXform38* mpXf38;               // +0x374
    uint32_t pad8[(0x388 - 0x378) / 4];
    PartTransform* mpXf7C;             // +0x388
    uint32_t pad9[(0x3F0 - 0x38C) / 4];
    IntrusivePtr<Counted> mpCached;    // +0x3F0
    uint32_t pad10;
    int mStart;                        // +0x3F8
    int mCount;                        // +0x3FC

    PartTransform* At7c(int i) { return &mpXf7C[i]; }
    PartXform38* At38(int i) {
        PartXform38* p = &mpXf38[i];
        return p;
    }
    __forceinline void ReadFlag(bool& out) {
        uint32_t dead[16];
        PropList* props = mpProps;
        if (props) {
            PropValue* value;
            if (props->Find(0x521FC0E, &value) && value->mType == 1)
                out = *value->GetBool();
        }
        {
            uint32_t dead2[1];
        }
    }
    bool ProcessBatch();               // 0x0040EB70
    bool Rescan();                     // 0x0040F110
};

// @ 0x0040EB70
bool EditorPartList::ProcessBatch() {
    int n = mKeys.size();
    int stop = n;
    if (stop - mStart > mCount)
        stop = mStart + mCount;
    bool pro = (mFlags & 0x100) != 0;
    for (int i = mStart; i < stop; ++i) {
        Key* key = mKeys.At(i);
        PartXform38* xf = &mpXf38[i];
        int b;
        if (pro)
            ApplyPart(key, xf, 2);
        FitPart(&mpXf38[i], mKeys.At(i));
        if (pro) {
            HolderPtr<PartHolder> hold(new ("Editor") PartHolder((const PartHolder*)key));
            TouchPart((Key*)hold.mp, 0, 2);
            mHolders.push_back(&hold.mp);
            IntVec vec;
            int x0 = QueryPart(key, 0x14, 0, 0, 0xe);
            if (x0 >= 0)
                vec.push_back(x0);
            b = QueryPart(key, 8, 2, 0, 0xe);
            if (b >= 0)
                vec.push_back(b);
            if (!vec.empty()) {
                ApplyShapes(key, (unsigned)(vec.mpEnd - vec.mpBegin), vec.data());
            }
        }
        TouchPart(mKeys.At(i), 0, 1);
        if (At7c(i)->GetSource()) {
            mpXf7C[i].Rebuild(At38(i));
            mpXf7C[i].Invert();
        }
    }
    if (stop < n) {
        mStart = stop;
        GetMessenger()->Post(0x67B65F1, 0, 0, 0);
    } else {
        bool ok = true;
        ReadFlag(ok);
        if (ok)
            GetMessenger()->Post(0x67B65F2, 0, 0, 0);
        else
            GetService2()->Run(0x245801E);
    }
    return true;
}

// @ 0x0040F110
bool EditorPartList::Rescan() {
    unsigned filter = 0x40B1A842;
    bool found = false;
    mpProps->Get(0x5B9A4FB, &filter);
    mpProps->GetBool(0x5B9A1EC, &found);
    if (!found) {
        KeyVec keys((AllocTag()));
        keys.reserve(mKeys.size());
        for (unsigned idx = 0; idx < mKeys.size(); ++idx) {
            if (mpEnabled[idx])
                keys.push_back(&mKeys.mpBegin[idx]);
        }
        Merge(&keys, 0x2E9E052, 0x2E9E05E, 0, &mpXf7C, 0);
        mpCached = GetSource()->Lookup(0x2E9E052, 0x2E9E05E, 0);
        KeyVec w;
        Collect(&w, GetSourcePlain(), filter, 0);
    } else {
        Collect(&mKeys, GetSourceWide(), filter, 1);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x0040F3F0: issue the selection command
// ---------------------------------------------------------------------------
struct KeyId {
    int a, b;
};
struct SelService {
    VS32(a) VS8(b) VS4(c) VS2(d) VS1(e)                      // 47 slots
    virtual void QueryAlt(KeyId* out);                       // slot 47 (+0xBC)
    VS2(f)                                                   // 48,49
    virtual void QueryPrimary(KeyId* out);                   // slot 50 (+0xC8)
};
struct FactoryService {
    VS4(a) VS2(b) VS1(c)                                     // 7 slots
    virtual int Create(int a, int b, int c, int d, int e);   // slot 7 (+0x1C)
};
struct SinkService {
    VS16(a) VS4(b) VS2(c) VS1(d)                             // 23 slots
    virtual void Accept(int h);                              // slot 23 (+0x5C)
};
struct Settings {
    bool Has(unsigned id);                                   // 0x006A25A0
};
extern Settings* g_pSettings;                                // 0x015FD918
SelService* GetSelService();         // 0x0067DD40
FactoryService* GetFactory();        // 0x0067DDA0
SinkService* GetSink();              // 0x0067DD60

struct SelectCommand {
    bool Execute(int unused);        // 0x0040F3F0
};

// @ 0x0040F3F0
bool SelectCommand::Execute(int unused) {
    KeyId id;
    id.a = -1;
    id.b = -1;
    Settings* s = g_pSettings;
    if (s->Has(0x1A91189C))
        GetSelService()->QueryPrimary(&id);
    else
        GetSelService()->QueryAlt(&id);
    GetSink()->Accept(GetFactory()->Create(id.a, id.b, 0, 1, 0));
    return true;
}
