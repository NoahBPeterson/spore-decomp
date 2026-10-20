// Slice s009c2ef0 -- the resize/walk helpers behind the creature animation data.
//
//   009c2ef0  vector<ik_constraint (0x10c)>::resize(n)           __thiscall, ret 4
//   009c3040  vector<creature_body_wiggle_instance_data (700)>::resize(n)   ret 4
//   009c3150  recursive body-tree walk: gathers the bool flags of every child
//             body into the parent's bit vector and accumulates a total
//   009c3210  small_vector ctor: point begin/end at the inline 0x3fc buffer
//   009c3240  vector<dynamics_phasegroup (0x104)>::DoDestroyValues(first, last)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Both resize() bodies have the same shape: grow through the matching
// insert-fill helper (009c1790 for 0x10c-byte elements, 009c1980 for the
// 700-byte ones), or destroy the tail and rewind mpEnd by the whole-element
// count.  The rewind keeps any partial trailing element, exactly like the
// `mpEnd -= mpEnd - newEnd` source form.
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int u32;

// ---------------------------------------------------------------------------
// out-of-line helpers (all present in the original image)
// ---------------------------------------------------------------------------
void FUN_009bf540(void* newEnd, void* first, void* last);      // 0x10c range destroy
void FUN_009bf5c0(void* newEnd, void* first, void* last);      // 700-byte range destroy
void FUN_009c1b70(void* pos, void* first, void* last, void* owner);  // bit-vector insert

// ---------------------------------------------------------------------------
// 009c2ef0  vector<ik_constraint>::resize
// ---------------------------------------------------------------------------
struct V3 {                             // a checkerlib vector_3
    float x1, x2, x3;
};

// The two padding blocks are spelled out as scalars (never as arrays): the
// original carries no /GS stack cookie even though it passes the address of
// this temporary to the fill helper, so the temporary must not contain an
// array member.
struct PadFirst {                       // 0x1c bytes
    float a, b, c, d, e, f, g;
};
struct PadLast {                        // 0x84 bytes
    float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w,
          x, y, z, aa, ab, ac, ad, ae, af, ag;
};

struct IkConstraint {                   // 0x10c bytes
    PadFirst p0;
    V3 v0, v1, v2, v3, v4, v5, v6, v7, v8;   // 0x1c .. 0x88 -- reset to zero
    PadLast p1;
};

struct IKVec {                          // vector<ik_constraint>
    IkConstraint* begin;                // 0x00
    IkConstraint* end;                  // 0x04
    IkConstraint* cap;                  // 0x08

    void InsertFill(IkConstraint* pos, unsigned n, const IkConstraint* value);  // 0x009c1790
    void Resize(unsigned n);            // 009c2ef0
};

// @ 0x009c2ef0
void IKVec::Resize(unsigned n) {
    IkConstraint* e = end;
    IkConstraint* b = begin;
    unsigned have = (unsigned)(e - b);

    if (n > have) {
        IkConstraint t;
        t.v0.x1 = t.v0.x2 = t.v0.x3 = 0.0f;
        t.v1.x1 = t.v1.x2 = t.v1.x3 = 0.0f;
        t.v2.x1 = t.v2.x2 = t.v2.x3 = 0.0f;
        t.v3.x1 = t.v3.x2 = t.v3.x3 = 0.0f;
        t.v4.x1 = t.v4.x2 = t.v4.x3 = 0.0f;
        t.v5.x1 = t.v5.x2 = t.v5.x3 = 0.0f;
        t.v6.x1 = t.v6.x2 = t.v6.x3 = 0.0f;
        t.v7.x1 = t.v7.x2 = t.v7.x3 = 0.0f;
        t.v8.x1 = t.v8.x2 = t.v8.x3 = 0.0f;
        InsertFill(e, n - have, &t);
    } else {
        IkConstraint* newEnd = b + n;
        FUN_009bf540(e, e, newEnd);
        end -= e - newEnd;
    }
}

// ---------------------------------------------------------------------------
// 009c3040  vector<creature_body_wiggle_instance_data>::resize
// ---------------------------------------------------------------------------
// 700-byte temporary block.  Spelled out as scalars only (never as an array):
// the original carries no /GS stack cookie although it takes the address of
// this temporary and hands it to the constructor.
struct F25 { float a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t,
                   u, v, w, x, y; };   // 100 bytes
struct BodyAnimC {                      // 0x2bc = 700 bytes; ctor 0x009bf680
    F25 p0, p1, p2, p3, p4, p5, p6;

    BodyAnimC* Ctor();                  // 0x009bf680 -- returns this
};

struct WiggleVec {
    BodyAnimC* begin;                   // 0x00
    BodyAnimC* end;                     // 0x04
    BodyAnimC* cap;                     // 0x08

    void InsertFill(BodyAnimC* pos, unsigned n, const BodyAnimC* value);  // 0x009c1980
    void Resize(unsigned n);            // 009c3040
};

// @ 0x009c3040
void WiggleVec::Resize(unsigned n) {
    BodyAnimC* e = end;
    BodyAnimC* b = begin;
    unsigned have = (unsigned)(e - b);

    if (n > have) {
        BodyAnimC t;
        BodyAnimC* src = t.Ctor();
        InsertFill(end, n - (unsigned)(end - begin), src);
    } else {
        BodyAnimC* newEnd = b + n;
        FUN_009bf5c0(e, e, newEnd);
        end -= e - newEnd;
    }
}

// ---------------------------------------------------------------------------
// 009c3150  recursive body-tree walk
// ---------------------------------------------------------------------------
struct BodyNode {                       // 0x468-byte creature_body_static_data
    u8 pad000[0x204];
    unsigned prevCount;                 // 0x204
    unsigned count;                     // 0x208
    int      total;                     // 0x20c
    u8 pad210[0x468 - 0x210];
};

struct AnimOwner {
    u8 pad000[0x384];
    BodyNode* bodies;                   // 0x384
};

struct WordVec {                        // the dword-backed bit vector
    u32* begin;                         // 0x00
    u32* end;                           // 0x04
    u32* cap;                           // 0x08

    void Insert(u32* pos, u32* first, u32* last, void* owner);  // 0x009c1b70
};

int FUN_009c3150(AnimOwner* a, WordVec* v, u32** base, unsigned idx);

// @ 0x009c3150
int FUN_009c3150(AnimOwner* a, WordVec* v, u32** base, unsigned idx) {
    BodyNode* node = &a->bodies[idx];

    unsigned prev = node->prevCount;
    node->prevCount = (unsigned)(((char*)v->end - (char*)v->begin) >> 2);
    unsigned n = node->count;
    node->total = (int)n;
    if (n == 0) return 0;

    unsigned off = prev * 4;
    v->Insert(v->end, (u32*)((char*)*base + off),
              (u32*)((char*)*base + off + n * 4), a);

    for (unsigned i = 0; i < node->count; i++) {
        node->total += FUN_009c3150(a, v, base, *(u32*)((char*)*base + off));
        off += 4;
    }
    return node->total;
}

// ---------------------------------------------------------------------------
// 009c3210  small_vector ctor with an inline 0x3fc-byte buffer
// ---------------------------------------------------------------------------
struct FixedVec {
    void*     begin;                    // 0x00
    void*     end;                      // 0x04
    void*     cap;                      // 0x08
    void*     pad0c;                    // 0x0c
    u8*       buf;                      // 0x10
    void*     pad14;                    // 0x14
    u8        storage[0x3fc];           // 0x18

    FixedVec* Init(void* a, void* b);   // 009c3210 -- __thiscall, ret 8
    void      Setup(void* a, void* b);  // 0x009c30f0
};

// @ 0x009c3210
FixedVec* FixedVec::Init(void* a, void* b) {
    u8* s = storage;
    buf = s;
    end = s;
    begin = s;
    cap = s + 0x3fc;
    Setup(a, b);
    return this;
}

// ---------------------------------------------------------------------------
// 009c3240  vector<dynamics_phasegroup>::DoDestroyValues
// ---------------------------------------------------------------------------
struct PhaseGroup {                     // 0x104 bytes
    u8 pad00[0x4c];
    void* subBegin;                     // 0x4c
    void* subEnd;                       // 0x50
    u8 pad54[0xbc - 0x54];
    void* block;                        // 0xbc
    u8 padc0[0x104 - 0xc0];
};

struct PhaseGroupVec {
    void* begin;                        // 0x00
    void* end;                          // 0x04
    void* cap;                          // 0x08

    void DestroyValues(PhaseGroup* first, PhaseGroup* last);   // 009c3240
};

// @ 0x009c3240
void PhaseGroupVec::DestroyValues(PhaseGroup* p, PhaseGroup* e) {
    for (; p < e; ++p) {
        void* b = p->block;
        if (b != 0 && *(int*)((char*)b - 4) != 0)
            operator delete(b);

        char* qe = (char*)p->subEnd;
        for (char* q = (char*)p->subBegin; q < qe; q += 0x38) {
            void* sub = *(void**)(q + 4);
            if (sub != 0 && *(int*)((char*)sub - 4) != 0)
                operator delete(sub);
        }

        void* r = p->subBegin;
        if (r != 0 && *(int*)((char*)r - 4) != 0)
            operator delete(r);
    }
}
