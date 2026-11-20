// Slice s00e24a50: destructor of an object with two polymorphic bases: deletes its owned
// object, then its members go: a wide string (EASTL basic_string<wchar_t> layout), a member
// object, a fixed vector (EASTL fixed_vector layout) and one more member object.

struct Owned_s00e2_4a50 {
    virtual ~Owned_s00e2_4a50();
};

struct WString_s00e2_4a50 {
    wchar_t* mpBegin;     // +0x0
    wchar_t* mpEnd;       // +0x4
    wchar_t* mpCapacity;  // +0x8

    ~WString_s00e2_4a50()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator delete(mpBegin);
        }
    }
};

struct Element_s00e2_4a50 {
    char pad00[0x10];
};

struct FixedVector_s00e2_4a50 {
    Element_s00e2_4a50* mpBegin;      // +0x00
    Element_s00e2_4a50* mpEnd;        // +0x04
    Element_s00e2_4a50* mpCapacity;   // +0x08
    int mOverflowAllocator;           // +0x0c
    Element_s00e2_4a50* mpPoolBegin;  // +0x10
    char mBuffer[0x1bc - 0xa4 - 0x14];

    ~FixedVector_s00e2_4a50()
    {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && mpBegin != mpPoolBegin)
            operator delete(mpBegin);
    }
    void DoDestroyValues(Element_s00e2_4a50* first, Element_s00e2_4a50* last);  // 0x00e23870
};

struct Member0c_s00e2_4a50 {
    char pad00[0xa4 - 0xc];
    ~Member0c_s00e2_4a50();  // 0x008e2b20
};

struct Member1bc_s00e2_4a50 {
    char pad00[0x1f8 - 0x1bc];
    ~Member1bc_s00e2_4a50();  // 0x00811fe0
};

struct BaseA_s00e2_4a50 {
    virtual ~BaseA_s00e2_4a50() {}
};

struct BaseB_s00e2_4a50 {
    virtual ~BaseB_s00e2_4a50() {}
};

struct Object_s00e2_4a50 : BaseA_s00e2_4a50, BaseB_s00e2_4a50 {
    char pad08[4];
    Member0c_s00e2_4a50 m0c;           // +0x00c
    FixedVector_s00e2_4a50 mItems;     // +0x0a4
    Member1bc_s00e2_4a50 m1bc;         // +0x1bc
    WString_s00e2_4a50 mName;          // +0x1f8
    char pad204[4];
    Owned_s00e2_4a50* mpOwned;         // +0x208

    virtual ~Object_s00e2_4a50();
};

// @ 0x00e24a50
Object_s00e2_4a50::~Object_s00e2_4a50()
{
    delete mpOwned;
    mpOwned = 0;
}
