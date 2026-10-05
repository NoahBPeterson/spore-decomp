// s0046d660 -- /arch:SSE region

extern "C" float* QuaternionFromMatrix33(float* out, const float* m, float v);

// @ 0x0046d660
float* FUN_0046d660(float* out, const float* m)
{
    float tmp[4];
    float* q = QuaternionFromMatrix33(tmp, m, 0.0f);
    out[0] = q[0];
    out[1] = q[1];
    out[2] = q[2];
    out[3] = q[3];
    return out;
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x0046d6c0
void F_0046d6c0() {}

// @ 0x0046d840
void F_0046d840() {}

// @ 0x0046dad0
void F_0046dad0() {}

// @ 0x0046de70
void F_0046de70() {}
