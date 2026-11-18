// Slice s00c52fa0: constructor of a game object derived from a base with three vtables
// (+0x00, +0x04, +0x34): an id pair, four positions and one colour taken from the global
// defaults, and two empty vectors.

struct Vector3_s00c5_2fa0 {
    float x, y, z;
};

struct ColorRGB_s00c5_2fa0 {
    float r, g, b;

    ColorRGB_s00c5_2fa0(const ColorRGB_s00c5_2fa0& o) : r(o.r), g(o.g), b(o.b) {}
};

extern const ColorRGB_s00c5_2fa0 g_DefaultColor_s00c5_2fa0;      // 0x016907c8
extern const Vector3_s00c5_2fa0 g_DefaultPosition_s00c5_2fa0;    // 0x016907d4

struct Vector_s00c5_2fa0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    int mAllocator[2];

    Vector_s00c5_2fa0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

struct Base0_s00c5_2fa0 { virtual void v00(); };
struct Base4_s00c5_2fa0 { virtual void v00(); char pad04[0x34 - 8]; };
struct Base34_s00c5_2fa0 { virtual void v00(); char pad04[0x1f0 - 0x38]; };

struct Base_s00c5_2fa0 : Base0_s00c5_2fa0, Base4_s00c5_2fa0, Base34_s00c5_2fa0 {
    Base_s00c5_2fa0();  // 0x00c48e90
};

struct Object_s00c5_2fa0 : Base_s00c5_2fa0 {
    int mIndex;                               // +0x1f0
    int mId;                                  // +0x1f4
    Vector3_s00c5_2fa0 mPosition;             // +0x1f8
    ColorRGB_s00c5_2fa0 mColor;               // +0x204
    Vector3_s00c5_2fa0 mTarget;               // +0x210
    Vector3_s00c5_2fa0 mStart;                // +0x21c
    Vector3_s00c5_2fa0 mEnd;                  // +0x228
    Vector_s00c5_2fa0 mItems;                 // +0x234
    bool mbDirty;                             // +0x248
    char pad249[0x250 - 0x249];
    Vector_s00c5_2fa0 mPending;               // +0x250

    Object_s00c5_2fa0();
    virtual void v00();
};

// @ 0x00c52fa0
Object_s00c5_2fa0::Object_s00c5_2fa0()
    : mIndex(0), mId(-1),
      mPosition(g_DefaultPosition_s00c5_2fa0), mColor(g_DefaultColor_s00c5_2fa0),
      mTarget(g_DefaultPosition_s00c5_2fa0), mStart(g_DefaultPosition_s00c5_2fa0),
      mEnd(g_DefaultPosition_s00c5_2fa0), mbDirty(false)
{
}
