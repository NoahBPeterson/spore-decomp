// Startup-module accessors for a block of 11 global settings at 0x015D0C00..0x015D0C28,
// plus small vector initializers returning their output pointer.
// Built without optimization: /Od /Ob1 /arch:SSE (frame pointer, movss float copies).

struct Vector2 { float x, y; };
struct Vector3 { float x, y, z; };

int g_Setting0, g_Setting1, g_Setting2, g_Setting3, g_Setting4, g_Setting5,
    g_Setting6, g_Setting7, g_Setting8, g_Setting9, g_Setting10;

// @ 0x00401000
int GetSetting0() { return g_Setting0; }

// @ 0x00401010
int GetSetting1() { return g_Setting1; }

// @ 0x00401020
int GetSetting2() { return g_Setting2; }

// @ 0x00401030
int GetSetting3() { return g_Setting3; }

// @ 0x00401040
int GetSetting4() { return g_Setting4; }

// @ 0x00401050
int GetSetting5() { return g_Setting5; }

// @ 0x00401060
int GetSetting6() { return g_Setting6; }

// @ 0x00401070
int GetSetting7() { return g_Setting7; }

// @ 0x00401080
int GetSetting8() { return g_Setting8; }

// @ 0x00401090
int GetSetting9() { return g_Setting9; }

// @ 0x004010A0
int GetSetting10() { return g_Setting10; }

// @ 0x004010B0
void SetSetting0(int value) { g_Setting0 = value; }

// @ 0x004010C0
void SetSetting1(int value) { g_Setting1 = value; }

// @ 0x004010D0
void SetSetting2(int value) { g_Setting2 = value; }

// @ 0x004010E0
void SetSetting3(int value) { g_Setting3 = value; }

// @ 0x004010F0
void SetSetting4(int value) { g_Setting4 = value; }

// @ 0x00401100
void SetSetting5(int value) { g_Setting5 = value; }

// @ 0x00401110
void SetSetting6(int value) { g_Setting6 = value; }

// @ 0x00401120
void SetSetting7(int value) { g_Setting7 = value; }

// @ 0x00401130
void SetSetting8(int value) { g_Setting8 = value; }

// @ 0x00401140
void SetSetting9(int value) { g_Setting9 = value; }

// @ 0x00401150
void SetSetting10(int value) { g_Setting10 = value; }

// @ 0x00401160
Vector2* Vector2_SetZero(Vector2* v)
{
    v->x = 0.0f;
    v->y = 0.0f;
    return v;
}

// @ 0x00401190
Vector2* Vector2_SetOne(Vector2* v)
{
    v->x = 1.0f;
    v->y = 1.0f;
    return v;
}

// @ 0x004011C0
Vector3* Vector3_SetUnitX(Vector3* v)
{
    v->x = 1.0f;
    v->y = 0.0f;
    v->z = 0.0f;
    return v;
}
