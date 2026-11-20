// Slice s00c9ae30 -- cTribe hot-spot weight query.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (tribe module).
#include "types.h"

#define VPAD(n) virtual void vpad##n()

struct Vector3 {
    float x, y, z;
};

// --------------------------------------------------------------------- property lists
struct IRefCounted { virtual void AddRef(); virtual void Release(); };

struct Property {
    uint32_t pad0[4];
    uint16_t mFlags;                    // +0x10 (0x30 = data behind a pointer)
    uint16_t mType;                     // +0x12 (0xd float, 0x10 void)
    float* GetValueFloat();
};
extern float kDefaultFloat;             // 0x015d9c6c
inline float* Property::GetValueFloat()
{
    if (mType == 0xd || mType == 0x10) {
        if (mFlags & 0x30)
            return *(float**)this;
        return mType ? (float*)this : 0;
    }
    return &kDefaultFloat;
}
struct PropertyList : IRefCounted {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6);   // +0x08 .. +0x20
    virtual bool GetProperty(uint32_t id, Property*& out);                     // +0x24
};
extern PropertyList* g_pTribeTuning;    // 0x0158128c

// --------------------------------------------------------------------- hot spots
// One 0x60-byte hot-spot node.
struct cHotSpotNode {
    Vector3 mPosition;                                             // +0x00
    float   mField0c;                                              // +0x0c
    float   mField10;                                              // +0x10
    uint8_t pad14[0x39 - 0x14];
    uint8_t mField39;                                              // +0x39
    uint8_t pad3a[0x60 - 0x3a];
};

struct HotSpotMap {
    cHotSpotNode* mpBegin;                                         // +0x00
    union {
        cHotSpotNode* mpEnd;                                       // +0x04
        uint32_t      mpEndRaw;
    };
    uint8_t pad08[0xc18 - 0x08];
    uint8_t mField0c18;                                            // +0xc18
    cHotSpotNode* operator[](const Vector3** key);                 // 0x00c9aa10 (ret 4)
};
extern HotSpotMap g_hotSpots;               // 0x0157abb0

// The game's float min/max helpers return a reference, so both operands are memory.
template <class T> inline const T& Max(const T& a, const T& b) { return (a > b) ? a : b; }
template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }

// @ 0x00c9ae30
void HotSpotWeight(const Vector3* pos, float height)
{
    cHotSpotNode* node = g_hotSpots[&pos];
    height += node->mField0c;
    height = Max(height, 0.0f);

    float limit;
    {
        Property* prop;
        if (g_pTribeTuning && g_pTribeTuning->GetProperty(0x200ad1cd, prop))
            limit = *prop->GetValueFloat();
        else
            limit = 50.0f;
    }

    if (height < 1.0f)
        node->mField39 = 1;
    else if (height >= limit)
        node->mField39 = 0;

    node->mField0c = Min(node->mField10, height);
}
