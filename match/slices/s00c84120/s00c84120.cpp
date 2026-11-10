// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
struct PropertyList;
extern PropertyList** gStarProperties; // 0x01694c54
extern float gDefault;                 // 0x014853bc
extern float gCase1;                   // 0x01477fc0
extern float gCase23;                  // 0x013ec4d0
void __cdecl ReadFloat(PropertyList* pl, unsigned int id, float* out); // 0x0040cf10

// @ 0x00c84120
float __cdecl GetStarRadius(int type)
{
    float result = gDefault;
    switch (type) {
    case 2:
    case 3:
        result = gCase23;
        break;
    case 4:
    case 5:
    case 6:
        ReadFloat(gStarProperties[type], 0x383cd6f, &result);
        break;
    case 1:
        result = gCase1;
        break;
    }
    return result;
}
