// Same shape as s00432830's SpriteGrid::ReleaseThunk (0x00432c00): the three pad
// locals make the 0x10-byte frame, and the base call goes to 0x00453540 here.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE

// @ 0x0045aab0
struct Base_0045aab0 {
    int Release();                                   // 0x00453540 (__thiscall)
};

struct T_0045aab0 : Base_0045aab0 {
    int ReleaseThunk();
};

int T_0045aab0::ReleaseThunk()
{
    int pad1, pad2, pad3;
    return Base_0045aab0::Release();
}
