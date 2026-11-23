// Same shape as s0041f940's Wrapper ctor (0x00420090): stores this, calls
// Init(0, b) (here 0x00569210), returns this.
// Flags: /Od /Ob1 /MD /Gy /TP

// @ 0x00567680
struct Wrapper_00567680 {
    void Init_00569210(int a, int b);            // 0x00569210 (__thiscall)
    Wrapper_00567680(int b);
};

Wrapper_00567680::Wrapper_00567680(int b) { Init_00569210(0, b); }
