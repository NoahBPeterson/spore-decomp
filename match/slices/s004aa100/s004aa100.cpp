// Same shape as s0041f940's Wrapper ctor (0x00420090): stores this, calls
// Init(0, b) (here 0x004ab1c0), returns this.
// Flags: /Od /Ob1 /MD /Gy /TP

// @ 0x004aa100
struct Wrapper_004aa100 {
    void Init_004ab1c0(int a, int b);            // 0x004ab1c0 (__thiscall)
    Wrapper_004aa100(int b);
};

Wrapper_004aa100::Wrapper_004aa100(int b) { Init_004ab1c0(0, b); }
