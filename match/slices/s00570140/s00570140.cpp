struct Inner0_00570140 {
    int a;
    int b;
};

struct Inner2_00570140 {
    int a;
    int b;

    void Assign_00423650(int a, int b);

    Inner2_00570140& operator=(const Inner2_00570140& rhs) {
        if (&rhs != this) {
            Assign_00423650(rhs.a, rhs.b);
        }
        return *this;
    }
};

struct Inner1_00570140 {
    float f;
    Inner2_00570140 y;

    Inner1_00570140& operator=(const Inner1_00570140& rhs) {
        f = rhs.f;
        y = rhs.y;
        return *this;
    }
};

struct Obj_00570140 {
    Inner0_00570140 m0;
    Inner1_00570140 m8;

    Obj_00570140& Match_00570140(const Obj_00570140& rhs);
};

// @ 0x00570140
Obj_00570140& Obj_00570140::Match_00570140(const Obj_00570140& rhs) {
    m0 = rhs.m0;
    m8 = rhs.m8;
    return *this;
}
