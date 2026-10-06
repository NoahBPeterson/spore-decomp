// /arch:SSE matrix initializers of slice s013ac650 (rows {1,0,0,1},{0,1,0,0},{0,0,1,0},{0,0,0,0}).
struct __declspec(align(16)) Vector4c {
    float x, y, z, w;
    Vector4c(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
};
struct Matrix4c {
    Vector4c r[4];
    __forceinline Matrix4c& SetIdentity() {
        r[0] = Vector4c(1.0f, 0.0f, 0.0f, 1.0f);
        r[1] = Vector4c(0.0f, 1.0f, 0.0f, 0.0f);
        r[2] = Vector4c(0.0f, 0.0f, 1.0f, 0.0f);
        r[3] = Vector4c(0.0f, 0.0f, 0.0f, 0.0f);
        return *this;
    }
};
extern Matrix4c g_01718aa0, g_01718a60, g_01718a20;
// @ 0x013B8E50
void FUN_013b8e50() { g_01718aa0.SetIdentity(); }
// @ 0x013B8EF0
void FUN_013b8ef0() { g_01718a60.SetIdentity(); }
// @ 0x013B8F90
void FUN_013b8f90() { g_01718a20.SetIdentity(); }
