// Flags: /O2 /MD /Gy /TP
struct Elem16 {
    float x, y, z;
    int w;
};
struct Vec16 {
    Elem16* mpBegin;
    Elem16* mpEnd;
    Elem16* mpCapacity;
    void Slow(Elem16* pos, const Elem16* v); // 0x00c43cc0
    Elem16* FUN_00c43f20(Elem16* pos, const Elem16* v);
};

// @ 0x00c43f20
Elem16* Vec16::FUN_00c43f20(Elem16* pos, const Elem16* v)
{
    Elem16* end = mpEnd;
    int index = (int)(pos - mpBegin);
    if (pos == end && end != mpCapacity) {
        Elem16* snap = end;
        mpEnd = end + 1;
        if (snap) {
            snap->x = v->x;
            snap->y = v->y;
            snap->z = v->z;
            snap->w = v->w;
        }
        return mpBegin + index;
    }
    Slow(pos, v);
    return mpBegin + index;
}
