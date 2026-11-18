// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };

#define VT(obj, slot) (*(void***)(obj))[(slot) / 4]

// 0x008105b0 (cSPUILayout::FindWindowByID)
struct UILayout {
    void* FindWindowByID(unsigned int nID, int nFlag);
};
void* App();                                              // 0x0067dd10
void  GetMainWindowArea(float* pOut);                     // 0x00805ea0
struct Viewer {
    void ProjectToScreen(Vec3* pOut, const Vec3* pIn) const;  // 0x007c4180
};
struct SpatialObj {
    Vec3* GetPosition();                                  // 0x005c65e0
};
struct SimObj {
    char* GetAvatar();                                    // 0x00b1fdb0
};
void*         FUN_00b3d240();                             // simulator
unsigned int  FUN_00b5b800();                             // current game mode
int           FUN_01021080();                             // universe context
void*         FUN_01002bd0();                             // simulator
void*         FUN_00e06770(void* pElem);                   // 0x00e06770
void*         FUN_00c9f020(void* pElem);                   // 0x00c9f020

struct Meter {
    void*         mpVt;        // 0x00
    char          pad04[8];    // 0x04
    unsigned char mb0c;        // 0x0c
    char          pad0d[3];
    UILayout*     mpLayout;    // 0x10
    void*         mpElem;      // 0x14
    unsigned int  mWindowId;   // 0x18
    char          pad1c[0x10]; // 0x1c
    void*         mp2c;        // 0x2c
    char          pad30[0x0c]; // 0x30
    int           mMode;       // 0x3c
    bool          mb40;        // 0x40
    char          pad41[3];
    float         mf44;        // 0x44
    float         mf48;        // 0x48
    void Draw();
};

// @ 0x00e07540
void Meter::Draw()
{
    void* window = mpLayout->FindWindowByID(mWindowId, 1);
    Vec2 p;

    if (mp2c) {
        if (mb40) {
            ((void (__thiscall*)(void*, float, float))VT(window, 0x64))(window, mf44, mf48);
            return;
        }

        void* app = App();
        void* viewer = ((void* (__thiscall*)(void*))VT(app, 0x58))(app);
        Vec3 v;
        ((Viewer*)viewer)->ProjectToScreen(&v, ((SpatialObj*)mp2c)->GetPosition());

        float area[4];
        GetMainWindowArea(area);

        p.y = ((1.0f - v.y) * area[3]) * 0.5f;
        p.x = ((v.x + 1.0f) * area[2]) * 0.5f;
        ((void (__thiscall*)(void*, float, float))VT(window, 0x64))(window, p.x, p.y - 60.0f);
        return;
    }

    if (mpLayout && mpElem) {
        void* elem = mpElem;
        if (((bool (__thiscall*)(void*, int, Vec2*))VT(elem, 0x7c))(elem, mb0c, &p)) {
            if (window) {
                float off = 0.0f;
                switch (mMode) {
                case 0: off = 60.0f; break;
                case 1: off = 40.0f; break;
                case 2:
                case 3: off = 20.0f; break;
                }

                void* sim = FUN_00b3d240();
                void* owner = ((void* (__thiscall*)(void*))VT(sim, 0x30))(sim);
                if (owner) {
                    void* a = FUN_00e06770(&mpElem);
                    void* b = FUN_00c9f020(&mpElem);
                    if ((a != 0 && a == owner) || (b != 0 && b == owner)) {
                        int special = FUN_00b5b800() == 0x1654c05u && a != 0 && a == owner &&
                                      FUN_01021080() == 0 &&
                                      ((SimObj*)FUN_01002bd0())->GetAvatar()[0x14] != 0;
                        if (!special)
                            off += 145.0f;
                        else
                            off += 25.0f;
                    }
                }

                ((void (__thiscall*)(void*, float, float))VT(window, 0x64))(window, p.x, p.y - off);
            }
        }
    }
}
