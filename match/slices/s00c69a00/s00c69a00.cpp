// Slice s00c69a00: the type-id cast of a game object with several bases: its own two ids give
// the object itself, one id gives the base at +0x108, and other ids are asked of the bases at
// +0x00, +0x120 and +0x34 in turn.

struct Base00_s00c6_9a00 {
    char pad00[0x34];
    void* Cast(unsigned int type);  // 0x00b18460
};

struct Base34_s00c6_9a00 {
    char pad00[0x108 - 0x34];
    void* Cast(unsigned int type);  // 0x00c884f0
};

struct Base108_s00c6_9a00 {
    char pad00[0x120 - 0x108];
};

struct Base120_s00c6_9a00 {
    char pad00[4];
    void* Cast(unsigned int type);  // 0x00bfc380
};

struct Object_s00c6_9a00 : Base00_s00c6_9a00, Base34_s00c6_9a00, Base108_s00c6_9a00, Base120_s00c6_9a00 {
    void* Cast(unsigned int type);
};

// @ 0x00c69a00
void* Object_s00c6_9a00::Cast(unsigned int type)
{
    if (type == 0xee3f516e || type == 0x02a0349a)
        return this;
    if (type != 0x102a041a) {
        if (void* p = Base00_s00c6_9a00::Cast(type))
            return p;
        if (void* p = Base120_s00c6_9a00::Cast(type))
            return p;
        return Base34_s00c6_9a00::Cast(type);
    }
    return static_cast<Base108_s00c6_9a00*>(this);
}
