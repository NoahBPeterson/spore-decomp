// slice s00f523a0 -- SP camera-controller / map emit-colour helpers

typedef unsigned int u32;

// ---- globals ----
struct EmitColourEntry { const char* m_name; void* m_value; };
extern EmitColourEntry g_mapEmitColour[];

// @ 0x00f52b70
void FUN_00f52b70(int index, const char* name)
{
    g_mapEmitColour[index].m_name = name;
}

// ---- classes ----
struct cLocalInputState {
    u32 OnMouseWheel(int a, float b, float c, int d);
};

struct cGameCameraController {
    char  pad00[0x12];
    char  m_12;                 // +0x12
    char  pad13[0x114 - 0x13];
    float m_114;                // +0x114
    char  pad118[0x294 - 0x118];
    float m_294;                // +0x294
    char  pad298[0x2a0 - 0x298];
    float m_2a0;                // +0x2a0
    char  pad2a4[0x319 - 0x2a4];
    char  m_319;                // +0x319
    char  pad31a[0x31c - 0x31a];
    cLocalInputState m_input;   // +0x31c

    u32 MoveCamera(float a, float b, float c, float d);
    bool FUN_00f52af0(int a, float b, float c, int d);
};

// @ 0x00f52af0
bool cGameCameraController::FUN_00f52af0(int a, float b, float c, int d)
{
    m_input.OnMouseWheel(a, b, c, d);
    if (m_319 == 0) {
        MoveCamera(0.0f, 0.0f, (float)a * m_2a0, 0.0f);
        m_294 = m_114;
        m_12 = 1;
    }
    return false;
}

// ---- ArgScript effect-option parsing ----
namespace EA { namespace ArgScript {
struct cArguments {
    const char** OptionArguments(const char* name, int* count, int min, int max);
    const char** OptionArguments(const char* name, int min);
    bool HasFlag(const char* name);
};
}}

struct cIArgEvaluator {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37();
    virtual float EvalFloat(const char* s);             // vtable 0x98
    virtual void v39();
    virtual unsigned short EvalUShort(const char* s);   // vtable 0xa0
};

float* ParseVector2(float* out, cIArgEvaluator* eval, const char*** p, int count);

struct EffectParams {
    char  pad00[8];
    unsigned m_flags;       // +0x08
    char  pad0c[0x18 - 0x0c];
    float m_delayX;         // +0x18
    float m_delayY;         // +0x1c
    float m_triggerX;       // +0x20
    float m_triggerY;       // +0x24
    char  pad28[0x78 - 0x28];
    float m_value;          // +0x78
    unsigned short m_7c;    // +0x7c
    char  pad7e[2];
    float m_speedScale;     // +0x80
};

// @ 0x00f52b80
void FUN_00f52b80(EA::ArgScript::cArguments* args, EffectParams& out, cIArgEvaluator& eval)
{
    int count;
    const char** p;
    unsigned short u16;

    p = args->OptionArguments("loop", &count, 1, 2);
    if (p != 0) {
        out.m_value = eval.EvalFloat(p[0]);
        if (count > 1) u16 = eval.EvalUShort(p[1]);
        else u16 = 0;
    }
    else {
        p = args->OptionArguments("single", &count, 0, 1);
        if (p != 0) {
            if (count > 0) out.m_value = eval.EvalFloat(p[0]);
            else out.m_value = 0.01f;
            u16 = 1;
        }
        else {
            p = args->OptionArguments("sustain", &count, 1, 2);
            if (p == 0) {
                p = args->OptionArguments("hold", &count, 1, 2);
                if (p == 0) {
                    p = args->OptionArguments("kill", &count, 1, 2);
                    if (p == 0) goto after_mode;
                    out.m_flags |= 0x8000000;
                }
                else {
                    out.m_flags |= 0x10000000;
                }
            }
            else {
                out.m_flags |= 4;
            }
            out.m_value = eval.EvalFloat(p[0]);
            if (count > 1) u16 = eval.EvalUShort(p[1]);
            else u16 = 1;
        }
    }
    out.m_7c = u16;

after_mode:
    if (args->HasFlag("sizeScale"))   out.m_flags |= 0x100;
    if (args->HasFlag("areaScale"))   out.m_flags |= 0x200;
    if (args->HasFlag("volumeScale")) out.m_flags |= 0x400;

    p = args->OptionArguments("speedScale", 1);
    if (p != 0) out.m_speedScale = eval.EvalFloat(p[0]);

    const char** q;
    q = args->OptionArguments("delay", &count, 1, 0x7fffffff);
    if (q != 0) {
        float vec[2];
        float* v = ParseVector2(vec, &eval, &q, count);
        out.m_delayX = v[0];
        out.m_delayY = v[1];
    }
    q = args->OptionArguments("trigger", &count, 1, 0x7fffffff);
    if (q != 0) {
        float vec[2];
        float* v = ParseVector2(vec, &eval, &q, count);
        out.m_triggerX = v[0];
        out.m_triggerY = v[1];
    }
}

// ================= 00f523a0 : camera-controller transform update =================
struct Vec3f { float x, y, z; };
struct Matrix33 { float m[9]; };

struct cTransform {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3f          mTranslation;        // +0x04
    float          mScale;              // +0x10
    Matrix33       mRotation;           // +0x14
};

struct cSPTransform {
    unsigned short mFlags;              // +0x00
    unsigned short mModificationCount;  // +0x02
    Vec3f          mTranslation;        // +0x04
    float          mScale;              // +0x10
    Matrix33       mRotation;           // +0x14
};

struct cQuaternion { float x, y, z, w; };

extern float DAT_016c9058, DAT_016c905c, DAT_016c9060;
extern float DAT_016c91a4, DAT_016c91a8, DAT_016c91ac;
extern float DAT_016c9170;
extern float DAT_016c91b4, DAT_016c91b8, DAT_016c91bc;
extern unsigned DAT_016c91c0;
extern Matrix33 DAT_016c9174;

void Matrix3_Assign(Matrix33* dst, const Matrix33* src);
void Matrix3FromQuaternion(Matrix33* dst, const cQuaternion* q);
void ComposeTransforms(cTransform* t);
void XForm2_PreRotateX(cTransform* t, float angle);
void XForm2_PreRotateY(cTransform* t, float angle);
void cXform_PreRotateX(cTransform* t, float angle);
void EA_Swarm_cTransform_PreRotateY(cTransform* t, float angle);
void cSPTransformOps_Assign(cSPTransform* dst, const void* src);

// @ 0x00f523a0
void FUN_00f523a0(int param_1)
{
    cTransform   local_a8;
    cSPTransform local_38;
    Matrix33     local_5c;
    Matrix33     local_24;
    float        local_6c, local_68, local_64;
    unsigned     local_60;
    unsigned short local_70, local_6e;

    local_a8.mTranslation.x = DAT_016c9058;
    local_a8.mTranslation.y = DAT_016c905c;
    local_a8.mModificationCount = 0;
    local_a8.mTranslation.z = DAT_016c9060;
    local_a8.mFlags = 0;
    local_a8.mScale = 1.0f;
    Matrix3_Assign(&local_a8.mRotation, &DAT_016c9174);

    local_a8.mFlags |= 4;
    local_a8.mModificationCount++;

    float f = -*(float*)(param_1 + 0x10c);
    local_a8.mTranslation.x += DAT_016c91a4 * f;
    local_a8.mTranslation.y += DAT_016c91a8 * f;
    local_a8.mTranslation.z += DAT_016c91ac * f;

    XForm2_PreRotateX(&local_a8, *(float*)(param_1 + 0x130));
    XForm2_PreRotateY(&local_a8, *(float*)(param_1 + 0x154));

    if (*(float*)(param_1 + 0xb8) <= 1.0f && *(float*)(param_1 + 0xb8) != 1.0f) {
        local_6c = DAT_016c9058;
        local_68 = DAT_016c905c;
        local_70 = 0;
        local_6e = 0;
        local_64 = DAT_016c9060;
        local_60 = 0x3f800000;
        Matrix3_Assign(&local_5c, &DAT_016c9174);
        Matrix3FromQuaternion(&local_38.mRotation, (const cQuaternion*)(param_1 + 0xac));
        for (int i = 0; i < 9; ++i)
            local_5c.m[i] = local_38.mRotation.m[i];
        local_70 |= 2;
        local_38.mTranslation.x = local_6c;
        local_6e++;
        local_38.mTranslation.y = local_68;
        local_38.mTranslation.z = local_64;
        local_38.mScale = *(float*)&local_60;
        local_38.mFlags = local_70;
        local_38.mModificationCount = local_6e;
        Matrix3_Assign(&local_24, &local_5c);
        ComposeTransforms(&local_a8);
        cSPTransformOps_Assign((cSPTransform*)&local_a8, &local_38);
    }

    if ((DAT_016c91c0 & 1) == 0) DAT_016c91c0 |= 1;

    DAT_016c91b4 = *(float*)(param_1 + 0x28);
    local_a8.mFlags |= 4;
    local_a8.mModificationCount++;
    DAT_016c91b8 = *(float*)(param_1 + 0x58) * DAT_016c91b4;
    DAT_016c91bc = *(float*)(param_1 + 0x5c) * DAT_016c91b4;
    DAT_016c91b4 = DAT_016c91b4 * *(float*)(param_1 + 0x54);
    local_a8.mTranslation.x += DAT_016c91b4;
    local_a8.mTranslation.y += DAT_016c91b8;
    local_a8.mTranslation.z += DAT_016c91bc;

    cXform_PreRotateX(&local_a8, *(float*)(param_1 + 0x26c));
    EA_Swarm_cTransform_PreRotateY(&local_a8, *(float*)(param_1 + 0x270));
    cSPTransformOps_Assign((cSPTransform*)(param_1 + 0x2cc), &local_a8);
    *(unsigned char*)(param_1 + 0x304) = 0;
}

// ================= 00f526c0 : SendZoomChangedMessage =================
namespace SP {
    struct cTerrainMapSet { float GetHeightAt(float* v); };
    int* cDistGrid_DebugDrawGrid();
    int* MessageServer();
}

float sqrtf(float);
void  FUN_00f4fb80(float);
void  FUN_00f502b0(float);
void  FUN_00f4fb00();
float FUN_00f987f0();
void  FUN_006f32e0(int, float);
void  FUN_007c4d00(void*);
void  FUN_007c4ba0(int);
void  FUN_007c4bc0(int);
void  LOCK();
void  UNLOCK();
extern void* PTR_FUN_013eb844;
struct MessageBasicRC5 { ~MessageBasicRC5(); };

// @ 0x00f526c0
void FUN_00f526c0(int param_1, float param_2)
{
    char* base = (char*)param_1;
    int*  p    = (int*)param_1;

    float fVar10 = (float)(int)param_2;
    if ((int)param_2 < 0) fVar10 += 4.2949673e+09f;

    float  fStack_5c = 0.1f;
    float* pfVar4 = &param_2;
    param_2 = fVar10 * 0.001f;
    if (0.1f <= fVar10 * 0.001f) pfVar4 = &fStack_5c;
    param_2 = *pfVar4;

    FUN_00f4fb80(param_2);

    fVar10 = DAT_016c9170;
    float* pfVar7 = (float*)(base + 0x154);   // param_1[0x55]
    float* pfVar8;
    float* pfVar1 = (float*)(base + 0x28c);   // param_1[0xa3]
    pfVar4 = (float*)(base + 0x15c);          // param_1[0x57]
    pfVar8 = pfVar4;
    if (*pfVar7 < *pfVar4 || *pfVar7 == *pfVar4) pfVar8 = pfVar7;
    if (*pfVar1 <= *pfVar8 && *pfVar8 != *pfVar1) pfVar8 = pfVar1;
    if (*pfVar8 <= DAT_016c9170) {
        pfVar8 = pfVar4;
        if (*pfVar4 < *pfVar7 || *pfVar4 == *pfVar7) pfVar8 = pfVar7;
        if (*pfVar8 <= *pfVar1 && *pfVar1 != *pfVar8) pfVar8 = pfVar1;
        if (*pfVar8 <= -DAT_016c9170 && -DAT_016c9170 != *pfVar8) {
            *pfVar7 += DAT_016c9170;
            *pfVar4 += fVar10;
            *pfVar1 += fVar10;
        }
    }
    else {
        *pfVar7 -= DAT_016c9170;
        *pfVar4 -= fVar10;
        *pfVar1 -= fVar10;
    }

    if (0.0f < param_2) FUN_00f502b0(param_2);

    int* piVar2 = SP::cDistGrid_DebugDrawGrid();
    if (piVar2 != 0) {
        float a = *(float*)(base + 0x2d0);   // param_1[0xb4]
        float b = *(float*)(base + 0x2d4);   // param_1[0xb5]
        float c = *(float*)(base + 0x2d8);   // param_1[0xb6]
        fStack_5c = sqrtf(a * a + b * b + c * c);
        float fVar9 = FUN_00f987f0();
        p[0x9d] = (int)(fStack_5c - fVar9);
        FUN_006f32e0(p[0xc3], fStack_5c - fVar9);
    }

    FUN_00f523a0(param_1);

    if (*(char*)(base + 0x365) != 0)
        (**(void (__thiscall**)(void*, float))(*p + 0x58))(p, param_2);

    if (*(char*)(base + 0x31a) != 0) {
        *(char*)(base + 0x31a) = 0;
        FUN_00f4fb00();
    }

    if (piVar2 != 0) {
        float fStack_58 = *(float*)(base + 0x2d0);
        float fStack_54 = *(float*)(base + 0x2d4);
        float fStack_50 = *(float*)(base + 0x2d8);
        float* pf4 = &fStack_58;
        SP::cTerrainMapSet* pcVar3 =
            (SP::cTerrainMapSet*)(**(void* (__thiscall**)(void*, float*))(*piVar2 + 0xc))(piVar2, pf4);
        float hv = pcVar3->GetHeightAt(pf4);
        float hz = FUN_00f987f0();
        float* sel = &hz;
        if (hz <= hv) sel = &hv;
        float fVar10b = *(float*)(base + 0x2b4) + *sel;   // param_1[0xad]
        float len = sqrtf(fStack_58 * fStack_58 + (fStack_54 * fStack_54 + fStack_50 * fStack_50));
        if (len < fVar10b) {
            *(unsigned short*)(base + 0x2cc) |= 4;        // param_1[0xb3]
            *(short*)(base + 0x2ce) += 1;
            float inv = 1.0f / len;
            float nx = (inv * fStack_58) * fVar10b;
            float ny = (fStack_54 * inv) * fVar10b;
            float nz = (fStack_50 * inv) * fVar10b;
            *(float*)(base + 0x2d0) = nx;
            *(float*)(base + 0x2d4) = ny;
            *(float*)(base + 0x2d8) = nz;
            float d = fVar10b - len;
            if (*(float*)(base + 0x20) <= *(float*)(base + 0x1c)) {
                d = *(float*)(base + 0x30) + d;
                *(float*)(base + 0x30) = d;
                *(float*)(base + 0x2c) = d;
                *(float*)(base + 0x28) = d;
                *(float*)(base + 0x24) = d;
                *(float*)(base + 0x34) = d * 0.0f;
                *(float*)(base + 0x38) = d * 0.0f;
                *(char*)(base + 0x18) = 0;
                *(char*)(base + 0x19) = 0;
            }
            else {
                int n = (*(int*)(base + 0x184) - *(int*)(base + 0x180)) >> 2;
                for (int i = 0; i < n; ++i) {
                    float* e = (float*)(*(int*)(base + 0x180) + i * 4);
                    *e = d + *e;
                }
                *(float*)(base + 0x28) = *(float*)(base + 0x28) + d;
                *(float*)(base + 0x2c) = *(float*)(base + 0x2c) + d;
                *(float*)(base + 0x30) = *(float*)(base + 0x30) + d;
                float zero = 0.0f;
                float* pfD = (float*)(base + 0x34);
                float* sel2 = pfD;
                if (*pfD <= 0.0f) sel2 = &zero;
                *pfD = *sel2;
            }
        }
    }

    FUN_007c4d00(base + 0x2cc);
    FUN_007c4ba0(p[0xc4]);
    FUN_007c4bc0(p[0xc5]);

    piVar2 = SP::MessageServer();
    if (piVar2 != 0) {
        char msg[0x30];
        LOCK();
        *(unsigned*)&msg[0] = 0;
        UNLOCK();
        *(int*)&msg[4] = p[0x43];
        *(void**)&msg[8] = &PTR_FUN_013eb844;
        *(unsigned*)&msg[0xc] = 0;
        *(unsigned*)&msg[0x14] = 0x44bb8000;
        (**(void (__thiscall**)(void*, unsigned, void*, int))(*piVar2 + 0x14))(piVar2, 0x60e4e46e, &msg[8], 0);
        ((MessageBasicRC5*)&msg[0])->~MessageBasicRC5();
    }
}
