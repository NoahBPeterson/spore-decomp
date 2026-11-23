// Same shape as s0041f940's Wrapper ctor (0x00420090): stores this, calls Init(0, b)
// (here 0x00514640), returns this.
// Flags: /Od /Ob1 /MD /Gy /TP

// @ 0x00513e20
struct Wrapper_00513e20 {
    void Init_00514640(int a, int b);            // 0x00514640 (__thiscall)
    Wrapper_00513e20(int b);
};

Wrapper_00513e20::Wrapper_00513e20(int b) { Init_00514640(0, b); }
