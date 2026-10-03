// Slice s00437400: a scene object's transform-sync routine and its "dirty/ownership state" helpers.
// Built without optimization: /Od /Ob1 /EHsc /arch:SSE (frame pointer, every local in memory).
#include "types.h"

// Fixed-size flag set (bit i lives in word i/32).  Out-of-range reads give false.
template <unsigned N> struct Bitset {
    uint32_t w[(N + 31) / 32];
    inline bool test(unsigned i) const {
        if (i < N) { uint32_t word = w[i >> 5]; return (word & (1u << (i % 32))) != 0; }
        return false;
    }
    inline uint32_t& Word(unsigned i) { return w[0]; }
    inline void set(unsigned i, bool v = true) {
        if (i < 32) { if (v) Word(i) |= 1u << (i % 32); else Word(i) &= ~(1u << (i % 32)); }
    }
};

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix3 {
    float f[3][3];
    Vector3& Row(int i) { return *(Vector3*)f[i]; }
    Matrix3() {}
    void Assign(const Matrix3& o);  // @ 0x0041cb40
    Matrix3(const Matrix3& o) { Assign(o); }
};

struct IOwner {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool Query(const void* id);  // slot 7
};

struct StateNode {                // pointed to by SceneObject::node
    int pad0;
    Bitset<32> flags;             // bit 8 = state valid
    char pad[0x55];
    uint8_t state;                // +0x5d
};

struct Anchor {                   // pointed to by SceneObject::anchor
    int pad;
    int ref;
    int Ref() { return ref; }
    void Compute(Vector3* v, Matrix3* m);  // @ 0x004e95e0
};

extern const char g_QueryId[];  // @ 0x00f9efc0

struct SceneObject {
    int pad0[3];
    IOwner* owner;                // +0x0c
    StateNode* node;              // +0x10
    char pad1[0x33c - 0x14];
    SceneObject* target;          // +0x33c
    char pad2[0x378 - 0x340];
    Anchor* anchor;               // +0x378
    char pad3[0xdc8 - 0x37c];
    Bitset<60> flags;             // +0xdc8

    StateNode* Nd() { return node; }
    Bitset<32>* NodeFlags() { return &Nd()->flags; }
    SceneObject* Target() { return target; }
    bool QueryOwner(IOwner* o) { o = owner; return o->Query(g_QueryId); }
    int GetStateA();              // @ 0x0044aa60
    int GetStateB();              // @ 0x0044aa80
    int GetId();                  // @ 0x0044e7e0
    void Apply1(Matrix3* m, int z);  // @ 0x00449420
    void Apply2(Vector3* v, int z);  // @ 0x00448e90

    void SyncTransform(bool p);          // @ 0x00437400
    void ClearNodeState();               // @ 0x00437890
    void SetNodeState(int s);            // @ 0x00437990
    void SetNodeStateChecked(int s, bool b);  // @ 0x00437a60
};

extern Vector3* Vector3_Negate(Vector3* out, const Vector3* in);               // @ 0x00422020
extern Matrix3 BuildMatrix(SceneObject* o, Vector3 v);                         // @ 0x0049c210
extern void ApplyTarget(SceneObject* target, Vector3 v, Matrix3 m, Vector3* pv, Matrix3* pm, int id);  // @ 0x004928d0
extern bool Check(SceneObject* o, Vector3* v, Matrix3* m, Vector3 vv, int a, int b);  // @ 0x004942b0
extern void Finish(SceneObject* o, Vector3 v, Matrix3 m, int z);               // @ 0x0049fbd0

// @ 0x00437400
void SceneObject::SyncTransform(bool p) {
    bool locked = flags.test(12) && flags.test(31);
    if (!locked && anchor->Ref() && Target() && !Target()->flags.test(10)) {
        Matrix3 m;
        Vector3 v;
        anchor->Compute(&v, &m);
        if (flags.test(0)) {
            Vector3 neg;
            m = BuildMatrix(this, *Vector3_Negate(&neg, &m.Row(1)));
        }
        int id = GetId();
        bool flag = false;
        if (id != -2) {
            ApplyTarget(Target(), v, m, &v, &m, id);
            flag = true;
        }
        Matrix3 m2 = m;
        bool r = Check(this, &v, &m, v, 0, 0);
        flag = r || flag;
        if (p) {
            Finish(this, v, m, 0);
        } else {
            Apply1(&m, 0);
            Apply2(&v, 0);
        }
    }
}

// @ 0x00437890
void SceneObject::ClearNodeState() {
    StateNode* n = node;
    if (n) {
        if (flags.test(46)) SetNodeState(GetStateA());
        else { NodeFlags()->set(8, false); }
    }
}

// @ 0x00437990
void SceneObject::SetNodeState(int s) {
    IOwner* x;
    if (s == 2) {
        if (!QueryOwner(x)) s = 4;
    }
    NodeFlags()->set(8, true);
    Nd()->state = (uint8_t)s;
}

// @ 0x00437a60
void SceneObject::SetNodeStateChecked(int s, bool b) {
    StateNode* n = node;
    if (n) {
        if (!b && flags.test(47)) SetNodeState(GetStateB());
        else SetNodeState(s);
    }
}
