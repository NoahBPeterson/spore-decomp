// Same shape as s00432830's HandlerFunctor::Init (0x00432dc0): mFn is the __cdecl
// handler at 0x004782c0 (the donor used 0x00432e40) and mOwner the argument.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE

// @ 0x00475650
void __cdecl CallHandler_004782c0(int arg, void* obj);   // 0x004782c0

struct HandlerFunctor_00475650 {
    void (__cdecl* mFn)(int, void*);
    int  mOwner;
    void Init(int owner);
};

void HandlerFunctor_00475650::Init(int owner)
{
    mFn = CallHandler_004782c0;
    mOwner = owner;
}
