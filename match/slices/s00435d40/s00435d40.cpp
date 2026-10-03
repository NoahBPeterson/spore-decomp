// Scene-entity helpers (flag bitset at +0xDC8, parent/link at +0x33C) and
// event-recorder helpers. Built /Od /Ob1 /arch:SSE.
#include "types.h"

#define VS1(p) virtual void p##_a();
#define VS2(p) VS1(p##0) VS1(p##1)
#define VS4(p) VS2(p##0) VS2(p##1)
#define VS8(p) VS4(p##0) VS4(p##1)

struct Vector3 { float x, y, z; };
template<int N> inline void Slots(){ uint32_t s[N]; }
struct Matrix3 {
    Vector3 r0, r1, r2;
    void Assign(const Matrix3* o);               // 0x0041CB40
};

struct Transform {
    uint16_t mFlags, mVersion;
    Vector3 mPos;
    float mScale;
    Matrix3 mRot;
    Transform();                                  // 0x00409930
    Transform(const Transform& o);                // 0x0040CE80
    void Accumulate(const void* parent);          // 0x0040CCB0
};

struct Property {
    uint8_t pad[0x12];
    uint16_t mType;
    bool* GetBool();                              // 0x0041E920
};

struct PropertyOwner {
    VS8(a) VS8(b) VS8(c) VS8(d)                   // slots 0..31 (placeholder)
};
struct PropertyOwnerBase {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8();
    virtual bool GetProperty(uint32_t hash, Property** out);   // slot 9 (+0x24)
};

struct TransformSource {
    uint32_t pad0[2];
    Transform mXform;                             // +8
};
struct TransformSourceView {
    uint32_t pad0[3];
    Vector3 mPos;                                 // +0x0C
    uint32_t pad18;
    Matrix3 mRot;                                 // +0x1C
};

struct Counted {
    virtual void s0();
    virtual void AddRef();                        // +4
    virtual void Release();                       // +8
};

template <class T> struct Ref {
    T* mp;
    Ref& operator=(T* v) {
        if (v != mp) {
            T* old = mp;
            if (v)
                v->AddRef();
            mp = v;
            if (old)
                old->Release();
        }
        return *this;
    }
};

struct TransformManager {
    VS8(a) VS8(b) VS8(c) VS8(d) VS8(e) VS8(f) VS8(g) VS8(h) VS2(i)   // slots 0..65
    virtual const void* GetWorldTransform(TransformSource* src);   // +0x108
};

struct Bits60 {
    uint32_t mWord[2];
    bool Test(unsigned n) const {
        if (n < 60) {
            uint32_t w = mWord[n >> 5];
            return (w & (1u << (n % 32))) != 0;
        }
        return false;
    }
};

struct Entity {
    uint32_t pad0[3];
    PropertyOwnerBase* mpProps;                   // +0x0C
    TransformSource* mpSource;                    // +0x10
    uint32_t pad14;
    TransformManager* mpManager;                  // +0x18
    uint32_t pad1c[(0x48 - 0x1C) / 4];
    Vector3 mPos;                                 // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];
    Matrix3 mRot;                                 // +0x60
    uint32_t pad84[(0x33C - 0x84) / 4];
    Ref<Counted> mRefLink;                        // +0x33C
    uint32_t pad340[(0xDC8 - 0x340) / 4];
    Bits60 mFlags;                                // +0xDC8

    bool HasAnyBlockFlag();                       // 0x00435D40
    void SetLink(Counted* link);                  // 0x00435FD0
    void InitDefaultFlags();                      // 0x00436060
    void SyncFlagsFromProps();                    // 0x004360F0
    Matrix3* GetRotation(Matrix3* out);                      // 0x004361C0
    Vector3* GetPosition(Vector3* out);                      // 0x00436210
    Transform GetWorldTransform();              // 0x004362A0
    Transform GetLocalTransform();              // 0x00436380
    Transform GetAccumulatedTransform();        // 0x004363D0
    void SetFlag(int bit, bool value);            // 0x00435A10
    TransformSource* GetSource() const { TransformSource* s = mpSource; return s; }
    Counted* GetLink() const { Counted* l = mRefLink.mp; return l; }
    PropertyOwnerBase* GetProps() const { PropertyOwnerBase* p = mpProps; return p; }
};

// @ 0x00435D40
bool Entity::HasAnyBlockFlag() {
    Entity* e = this;
    int depth = 0;
    while (e && depth < 100) {
        if (e->mFlags.Test(7) || e->mFlags.Test(8) || e->mFlags.Test(35))
            return true;
        e = (Entity*)e->mRefLink.mp;
        ++depth;
    }
    return false;
}

struct Recorder {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual int GetState();                               // +0x20
    virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12();
    virtual void s13();
    virtual void Begin(uint32_t tag);                     // +0x38
    virtual void WriteFloat(uint32_t tag, float v);       // +0x3C
    virtual void WriteInt(uint32_t tag, uint32_t v);      // +0x40
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20();
    virtual void s21();
    virtual void End();                                   // +0x58
};
Recorder* GetRecorder();                                  // 0x00A206F0

// @ 0x00435E90
int GetRecorderState() {
    Recorder* rec = GetRecorder();
    int result;
    if (rec)
        result = rec->GetState();
    else
        result = 0;
    return result;
}

// @ 0x00435ED0
void RecordEvent2(uint32_t a, uint32_t b) {
    Recorder* r = GetRecorder();
    if (r) {
        r->Begin(0x3475365);
        r->WriteInt(0x3475381, a);
        r->WriteInt(0x3475385, b);
        r->End();
    }
}

// @ 0x00435F40
void RecordEvent4(uint32_t a, uint32_t b, float c, uint32_t d) {
    Recorder* r = GetRecorder();
    if (r) {
        r->Begin(0x3475376);
        r->WriteInt(0x3475385, a);
        r->WriteInt(0x34753A7, b);
        r->WriteFloat(0x34753AA, c);
        r->WriteInt(0x34753AD, d);
        r->End();
    }
}

// @ 0x00435FD0
void Entity::SetLink(Counted* link) {
    mRefLink = link;
    if (GetLink() && GetProps())
        SyncFlagsFromProps();
}

// @ 0x00436060
void Entity::InitDefaultFlags() {
    if (!mFlags.Test(35) && GetLink() == 0) {
        SetFlag(35, true);
        SetFlag(51, false);
    }
}

// @ 0x004360F0
void Entity::SyncFlagsFromProps() {
    bool a;
    bool f;
    PropertyOwnerBase* owner = mpProps;
    if (owner) {
        f = false;
        {
            PropertyOwnerBase* o = mpProps;
            if (o) {
                Property* p;
                if (o->GetProperty(0x8E31D974, &p) && p->mType == 1)
                    f = *p->GetBool();
            }
            Slots<1>();
        }
        SetFlag(35, f);
        a = false;
        {
            PropertyOwnerBase* o2 = mpProps;
            if (o2) {
                Property* p2;
                if (o2->GetProperty(0x0538A895, &p2) && p2->mType == 1)
                    a = *p2->GetBool();
            }
            Slots<1>();
        }
        SetFlag(51, a);
    }
}

// @ 0x004361C0
Matrix3* Entity::GetRotation(Matrix3* out) {
    TransformSource* src = mpSource;
    if (src) {
        TransformSourceView* s = (TransformSourceView*)mpSource;
        Slots<22>();
        out->Assign(&s->mRot);
        return out;
    } else {
        out->Assign(&mRot);
        return out;
    }
}

// @ 0x00436210
Vector3* Entity::GetPosition(Vector3* out) {
    TransformSource* src = mpSource;
    if (src) {
        TransformSourceView* view = (TransformSourceView*)mpSource;
        Vector3* pos = &view->mPos;
        out->x = pos->x;
        out->y = pos->y;
        out->z = pos->z;
        return out;
    } else {
        Vector3* v2 = &mPos;
        out->x = v2->x;
        out->y = v2->y;
        out->z = v2->z;
        return out;
    }
}

extern const Matrix3 g_IdentityMatrix;                    // 0x015D2428
extern const float g_UnitScale;                           // 0x01485720
extern const Vector3 g_ZeroVector;                        // 0x015D255C

// @ 0x004362A0
Transform Entity::GetWorldTransform() {
    TransformSource* src = mpSource;
    if (src) {
        TransformManager* m = mpManager;
        return *(const Transform*)m->GetWorldTransform(mpSource);
    } else {
        Transform t;
        t.mRot = g_IdentityMatrix;
        t.mScale = g_UnitScale;
        t.mPos = g_ZeroVector;
        t.mFlags = 0;
        t.mVersion = 0;
        return t;
    }
}

// @ 0x00436380
Transform Entity::GetLocalTransform() {
    TransformSource* src = mpSource;
    if (src) {
        TransformSource* s = mpSource;
        Slots<27>();
        return s->mXform;
    } else {
        return Transform();
    }
}

// @ 0x004363D0
Transform Entity::GetAccumulatedTransform() {
    TransformSource* src = mpSource;
    TransformManager* mgr;
    if (src && (mgr = mpManager) != 0) {
        TransformManager* m = mpManager;
        TransformSource* s = mpSource;
        const void* w = m->GetWorldTransform(s);
        Transform t(s->mXform);
        t.Accumulate(w);
        return t;
    } else {
        return Transform();
    }
}
