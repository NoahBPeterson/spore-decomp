// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct V {
    virtual void v0();
    virtual void Release();
    virtual void v8();
    virtual void Stop(int); // slot +0x0c
};
struct Node {
    void* mp0;
    V* mp4;
};
struct Blob {
    char mPad[0xa5c];
    int mCount;
};
struct Creature {
    char mPad[0xfb8];
    Blob* mpBlob; // +0xfb8
    void SetSprinting(int); // 0x00c1ad10
};
typedef void (__thiscall* TailFn)(void* self);

// @ 0x00d95680
void FUN_00d95680(Creature* self, int, int, int, int, Node* h)
{
    if (h->mp4) {
        h->mp4->Stop(0);
        V* q = h->mp4;
        h->mp4 = 0;
        if (q)
            q->Release();
    }
    --self->mpBlob->mCount;
    self->SetSprinting(0);
    if (h->mp4)
        h->mp4->Release();
    void* o = h->mp0;
    if (o)
        (*(TailFn**)o)[0x64 / 4](o);
}
