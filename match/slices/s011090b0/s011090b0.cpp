// Slice s011090b0: cSlotScatter::Place -- slot-ring scatter builder.
// Replaces the earlier byte-transcription shim with real C++.
// Flags: /O2 /MD /Gy /TP /fp:fast /GS- (no /EHsc, no /arch:SSE -- the original
// is pure x87 and carries no /GS cookie).
#include "types.h"
#include <math.h>

// 4-byte entry of the fixed 8-slot ring.
struct Slot {
    uint8_t  m00;       // +0x00  slot kind (0..6 selects the matrix / commit helper)
    uint8_t  m01;       // +0x01  slot flags (hashed from the entry mask)
    uint16_t m02;       // +0x02  handle returned by the sink
};

struct Req {
    uint8_t  m00;       // +0x00  kind (low byte of the caller key)
    uint8_t  m01;       // +0x01  flags
    uint16_t m02;       // +0x02  id (high word of the caller key)
    int32_t  m04;       // +0x04  reserved handle
};

// the four header bytes are filled from the raw 32-bit caller key in one move
union Key {
    int32_t mKey;
    Req     mReq;
};

struct SlotSet {
    Slot    mSlots[8];                                     // +0x00
    uint8_t m20;                                           // +0x20  added counter
    uint8_t m21;                                           // +0x21  used slot count
    int32_t Reserve(uint32_t a, uint32_t b, Req* req);      // 0x010ec540
    void    Release(int32_t handle);                        // 0x010ec4a0
};

// 0x30-byte spatial node. A node's position is its own +0x00 triple; the
// triple at +0x10 is what the neighbouring dot product uses.
struct Node {
    float    m00;       // +0x00
    float    m04;       // +0x04
    float    m08;       // +0x08
    uint8_t  pad0C[4];  // +0x0c
    float    m10;       // +0x10
    float    m14;       // +0x14
    float    m18;       // +0x18
    uint8_t  pad1C[4];  // +0x1c
    uint16_t m20;       // +0x20
    uint8_t  pad22[0x0e];
};

struct Cursor {
    Node* mpNode;       // +0x00
};

// 3x4 affine matrix (rows of 4 floats) followed by the 3 translation floats.
struct Mat34 {
    float m[15];
};

// record filled by QuerySlot (0x01108ac0). 16-byte aligned: its four-float
// components are aligned vectors, which is what forces the aligned frame.
struct __declspec(align(16)) Hit {
    float   m00[4];     // +0x00
    float   m10[4];     // +0x10
    float   m20[4];     // +0x20
    float   m30;        // +0x30
    float   m34;        // +0x34
    int32_t m38;        // +0x38  index into m00 / the m60 table
    uint8_t pad3C[4];   // +0x3c
};

struct SlotScatter {
    uint32_t m00;       // +0x00
    uint32_t m04;       // +0x04
    uint32_t m08;       // +0x08
    void*    m0C;       // +0x0c  sink object, vtable slot +0x08 adds a node
    Cursor*  m10;       // +0x10
    Mat34*   m14;       // +0x14  matrix for slot kinds 3..6
    Mat34*   m18;       // +0x18  matrix for slot kinds 0..2
    uint8_t  pad1C[0x60 - 0x1c];
    float    m60[4];    // +0x60  per-component offsets
    uint8_t  pad70[0xa0 - 0x70];
    float    mA0[4];    // +0xa0  per-component extents
    float    mB0;       // +0xb0  clearance radius

    void Place(SlotSet* set, int32_t key, uint32_t mask, float limit);   // 0x011090b0
    void QuerySlot(Hit* out, Req* req);                                  // 0x01108ac0
    void CommitA(Node* node, int32_t* handle, Hit* out);                 // 0x01108a10
    void CommitB(Node* node, int32_t* handle, Hit* out);                 // 0x01108b80
    void CommitC(Node* node, int32_t* handle, Hit* out);                 // 0x01108c30
};

// group masks tested against the caller's mask, in scan order
extern const uint16_t g_14a5f70[7];   // 0x014a5f70
extern float          g_14a5f80;      // 0x014a5f80  epsilon
extern float          g_1485378;      // 0x01485378  neighbour dot threshold

// @ 0x011090b0
void SlotScatter::Place(SlotSet* set, int32_t key, uint32_t mask, float limit)
{
    for (int32_t g = 0; g < 7; ++g) {
        uint16_t group = g_14a5f70[g];
        if (((uint32_t)group & mask) != 0)
            continue;

        Key keyhdr;
        keyhdr.mKey = key;
        Req& req = keyhdr.mReq;
        {
            uint8_t hi = (uint8_t)(((uint32_t)key >> 8) & 0xff);
            req.m01 = (uint8_t)((uint8_t)(group & 0xff) ^ hi) | (hi & 0x0f);
        }

        // already recorded in the ring?
        bool present = false;
        for (int32_t i = (int32_t)set->m21 - 1; i >= 0; --i) {
            if (set->mSlots[i].m00 == req.m00 && set->mSlots[i].m01 == req.m01) {
                present = true;
                break;
            }
        }
        if (present)
            continue;

        Hit hit;
        QuerySlot(&hit, &req);

        // req.m10[3] is compared by the original as well, but its flag is
        // masked out of the branch, so only the first three components gate.
        if (!(fabsf(hit.m10[0]) < mA0[0] &&
              fabsf(hit.m10[1]) < mA0[1] &&
              fabsf(hit.m10[2]) < mA0[2]))
            continue;

        float depth = -(hit.m30 * hit.m00[hit.m38]) - m60[hit.m38];
        hit.m34 = depth;
        if (depth < limit - g_14a5f80)
            continue;

        bool transformed = false;
        float rx = 0.0f, ry = 0.0f, rz = 0.0f;
        if ((uint8_t)key <= 2) {
            const float* p = hit.m10;
            const Mat34* m = m18;
            rx = p[0] * m->m[0] + p[1] * m->m[4] + p[2] * m->m[8] + m->m[12];
            ry = p[0] * m->m[1] + p[1] * m->m[5] + p[2] * m->m[9] + m->m[13];
            rz = p[0] * m->m[2] + p[1] * m->m[6] + p[2] * m->m[10] + m->m[14];
            transformed = true;
        } else if ((uint8_t)key <= 6) {
            const float* p = hit.m00;
            const Mat34* m = m14;
            rx = p[0] * m->m[0] + p[1] * m->m[4] + p[2] * m->m[8] + m->m[12];
            ry = p[0] * m->m[1] + p[1] * m->m[5] + p[2] * m->m[9] + m->m[13];
            rz = p[0] * m->m[2] + p[1] * m->m[6] + p[2] * m->m[10] + m->m[14];
            transformed = true;
        }
        if (transformed) {
            // reject the placement when it lands inside the radius of an
            // already committed node
            Node* node = m10->mpNode;
            float clearance = mB0 * mB0;
            bool blocked = false;
            for (uint32_t i = 0; i < set->m21; ++i) {
                if (set->mSlots[i].m00 > 6)
                    continue;
                const Node* nb = node + 1 + i;
                float dx = rx - nb->m00;
                float dy = ry - nb->m04;
                float dz = rz - nb->m08;
                if (dx * dx + dy * dy + dz * dz <= clearance + g_14a5f80) {
                    blocked = true;
                    break;
                }
            }
            if (blocked)
                continue;
        }

        if (set->m21 >= 8)
            continue;

        req.m04 = set->Reserve(m00, m04, &req);
        if (req.m04 < 0)
            continue;

        Node* node = m10->mpNode;
        if (hit.m38 <= 2)
            CommitA(node, &req.m04, &hit);
        else if (hit.m38 <= 6)
            CommitB(node, &req.m04, &hit);
        else
            CommitC(node, &req.m04, &hit);

        if (set->m21 > 1) {
            const Node* prev = node - 1;
            float dot = prev->m10 * node->m10 +
                        prev->m14 * node->m14 +
                        prev->m18 * node->m18;
            if (!(dot > g_1485378)) {
                set->Release(req.m04);
                continue;
            }
        }

        uint16_t handle = ((uint16_t(__thiscall*)(void*, uint32_t, uint32_t, uint32_t, Node*))
                           (*((char**)*(void**)m0C + 2)))(m0C, m00, m04, m08, node);
        set->mSlots[req.m04].m02 = handle;
        if (handle == 0xffff) {
            set->Release(req.m04);
            continue;
        }

        m10->mpNode = node + 1;
        node->m20 = set->mSlots[req.m04].m02;
        if (req.m00 <= 6)
            ++set->m20;
    }
}
