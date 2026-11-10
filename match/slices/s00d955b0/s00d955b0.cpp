// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct IFace {
    virtual void v0();
    virtual void Release();
};
struct Vec {
    void Insert(void* key); // 0x00c43fe0
};
struct Creature {
    char mPad00[0xc0];
    Vec mCallbacks;          // +0xc0
    char mPadC4[0xfb8 - 0xc0 - 4];
    char* mpByte;            // +0xfb8
    void SetSprinting(int on); // 0x00c1ad10
};

// @ 0x00d955b0
void FUN_00d955b0(Creature* self, int, int, int, int, IFace** holder)
{
    if (holder && *holder)
        (*holder)->Release();
    self->SetSprinting(0);
    self->mpByte[0xa51] = 0;
    self->mCallbacks.Insert((void*)0x00b3e5e0);
}
