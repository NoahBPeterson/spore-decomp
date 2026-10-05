// s00470bd0

struct V4 {
    float v[4];
    float& operator[](int i) { return v[i]; }
};

// @ 0x00470f20
float FUN_00470f20(V4* p)
{
    float local_10;
    float local_14;
    float local_18;
    if ((*p)[0] < (*p)[1])
        local_10 = (*p)[1];
    else
        local_10 = (*p)[0];
    if ((*p)[2] < (*p)[3])
        local_14 = (*p)[3];
    else
        local_14 = (*p)[2];
    if (local_10 < local_14)
        local_18 = local_14;
    else
        local_18 = local_10;
    return local_18;
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x00470bd0
void F_00470bd0() {}

// @ 0x00471000
void F_00471000() {}

// @ 0x00471830
void F_00471830() {}
