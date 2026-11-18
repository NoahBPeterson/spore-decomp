// Slice s00c64bf0: constructor of a game object derived from a base with three vtables
// (+0x00, +0x04, +0x34): colours copied from the global defaults, a named member, a zero
// offset, an up vector, and the base at +0x34 is given its name.

struct ColorRGB_s00c6_4bf0 {
    float r, g, b;

    ColorRGB_s00c6_4bf0(const ColorRGB_s00c6_4bf0& o) : r(o.r), g(o.g), b(o.b) {}
};

struct Vector3_s00c6_4bf0 {
    float x, y, z;

    Vector3_s00c6_4bf0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct Flags_s00c6_4bf0 {
    unsigned short mFlags;  // +0x0
    unsigned short mState;  // +0x2

    Flags_s00c6_4bf0()
    {
        mFlags = 0;
        mState = 0;
    }
};

struct Name_s00c6_4bf0 {
    char pad00[0x24];

    Name_s00c6_4bf0(const Name_s00c6_4bf0& o);  // 0x0041cb40
};

extern const ColorRGB_s00c6_4bf0 g_DefaultTint_s00c6_4bf0;    // 0x01693d74
extern const Name_s00c6_4bf0 g_DefaultName_s00c6_4bf0;        // 0x01693da4
extern const ColorRGB_s00c6_4bf0 g_DefaultColorA_s00c6_4bf0;  // 0x01693dc8
extern const ColorRGB_s00c6_4bf0 g_DefaultColorB_s00c6_4bf0;  // 0x01693dd4
extern const char g_TypeName_s00c6_4bf0[];                    // 0x015777f0

struct Base0_s00c6_4bf0 { virtual void v00(); };
struct Base4_s00c6_4bf0 { virtual void v00(); char pad04[0x34 - 8]; };
struct Base34_s00c6_4bf0 {
    virtual void v00();
    char pad04[0x118 - 0x38];

    void SetTypeName(const char* name);  // 0x00c88810
};

struct Base_s00c6_4bf0 : Base0_s00c6_4bf0, Base4_s00c6_4bf0, Base34_s00c6_4bf0 {
    Base_s00c6_4bf0();  // 0x00c63be0
};

struct Object_s00c6_4bf0 : Base_s00c6_4bf0 {
    Flags_s00c6_4bf0 mFlags;              // +0x118
    ColorRGB_s00c6_4bf0 mTint;            // +0x11c
    float mScale;                         // +0x128
    Name_s00c6_4bf0 mName;                // +0x12c
    Vector3_s00c6_4bf0 mOffset;           // +0x150
    ColorRGB_s00c6_4bf0 mColorA;          // +0x15c
    ColorRGB_s00c6_4bf0 mColorB;          // +0x168
    Vector3_s00c6_4bf0 mUp;               // +0x174

    Object_s00c6_4bf0();
    virtual void v00();
};

// @ 0x00c64bf0
Object_s00c6_4bf0::Object_s00c6_4bf0()
    : mTint(g_DefaultTint_s00c6_4bf0), mScale(1.0f), mName(g_DefaultName_s00c6_4bf0),
      mOffset(0.0f, 0.0f, 0.0f), mColorA(g_DefaultColorA_s00c6_4bf0), mColorB(g_DefaultColorB_s00c6_4bf0),
      mUp(0.0f, 1.0f, 0.0f)
{
    SetTypeName(g_TypeName_s00c6_4bf0);
}
