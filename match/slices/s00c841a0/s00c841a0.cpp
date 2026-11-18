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

// Reads a float property by name hash; defined elsewhere (0x0040cf10).
bool GetFloatProperty(PropertyList* list, unsigned int id, float* out);

// @ 0x00c841a0
float __cdecl GetStarTuning(int type)
{
    float result = 1.0f;
    switch (type) {
    case 1:
    case 2:
        result = 100.0f;
        break;
    case 3:
        result = 1.0f;
        break;
    case 4:
    case 5:
    case 6:
        GetFloatProperty(gStarProperties[type], 0x383cd7c, &result);
        break;
    case 7:
        return GetStarTuning(5) * 2.0f;
    case 8:
        return GetStarTuning(5) + GetStarTuning(4);
    case 9:
        return GetStarTuning(6) + GetStarTuning(5);
    case 10:
        return GetStarTuning(4) * 2.0f;
    case 11:
        return GetStarTuning(6) + GetStarTuning(4);
    case 12:
        return GetStarTuning(6) * 2.0f;
    }
    return result;
}
