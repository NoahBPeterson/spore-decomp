// Same shape as s0041d490's ExtRef::Reset (0x0041d940); the destroy call goes to
// 0x00402420 here.
// Flags: /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE /fp:fast

// @ 0x00472b00
void __fastcall ExtDestroy_00402420(void* obj);      // 0x00402420

struct ExtRef_00472b00 {
    void* p;
    ExtRef_00472b00* Reset();
};

ExtRef_00472b00* ExtRef_00472b00::Reset()
{
    if (p) {
        void* o = p;
        p = 0;
        ExtDestroy_00402420(o);
    }
    return this;
}
