// Same shape as s00422950's CallbackRegistry::RegisterA (0x004229f0): pushes the
// callback 0x00567310 (the donor pushed 0x00428f80) then the argument, and calls the
// same Register at 0x0068f9f0.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE

// @ 0x00564f90
void FUN_00567310();                                     // the callback

struct CallbackRegistry_00564f90 {
    void Register(void (*fn)(), unsigned int arg);   // 0x0068f9f0
    void RegisterX(unsigned int arg);
};

void CallbackRegistry_00564f90::RegisterX(unsigned int arg) { Register(FUN_00567310, arg); }
