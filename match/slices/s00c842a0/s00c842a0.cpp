// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct Property {
    char pad[0x12];
    unsigned short type; // +0x12, 0xd = float
    float* GetFloat();   // 0x0041ea70
};
struct PropertyList {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(unsigned int id, Property** out); // slot +0x24
};
extern PropertyList** gStarProperties; // 0x01694c54
extern float gDefault;                 // 0x01488874
extern float gScale;                   // 0x01473464

// @ 0x00c842a0
float __cdecl GetStarRotationRate(int type)
{
    float result = gDefault;
    switch (type) {
    case 4:
    case 5:
    case 6: {
        PropertyList* pl = gStarProperties[type];
        if (pl && pl->GetProperty(0x383cd8d, (Property**)&type) && ((Property*)type)->type == 0xd) {
            float* p = ((Property*)type)->GetFloat();
            result = *p * gScale;
        }
        break;
    }
    }
    return result;
}
