// Same shape as s00432830's HandlerFunctor::Init (0x00432dc0): mFn is the callback
// at 0x005672d0 (the donor used 0x00432e40) and mOwner the argument.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE

// @ 0x00564f70
void FUN_005672d0();                                 // 0x005672d0 (the callback)

struct HandlerFunctor_00564f70 {
    void (*mFn)();
    unsigned int mOwner;
    void Init(unsigned int owner);
};

void HandlerFunctor_00564f70::Init(unsigned int owner)
{
    mFn = FUN_005672d0;
    mOwner = owner;
}
