// 0x00c44c30: getter for the int at +0x16c (owning class not identified yet; Obj00c44c30 is a stand-in).
struct Obj00c44c30 { char pad[0x16c]; int value; int Get(); };

// @ 0x00c44c30
int Obj00c44c30::Get() { return value; }
