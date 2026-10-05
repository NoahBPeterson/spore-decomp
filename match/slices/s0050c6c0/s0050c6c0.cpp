// w1g1 slice s0050c6c0 -- small vector/lane helpers plus vector<float>::operator=.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE where floats are copied with movss.

typedef unsigned int uint32_t;

// @ 0x0050cfb0  (2-component subtract: out = a - b)
float* __cdecl Sub2(float* out, float* a, float* b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    return out;
}

// @ 0x0050d020  (2-component scale: out *= s)
float* __cdecl Scale2(float* out, float* s)
{
    out[0] = out[0] * s[0];
    out[1] = out[1] * s[0];
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x0050cec0  (fixed_vector<float,400> constructor)
// ---------------------------------------------------------------------------
void FixedVecInit(void* p);   // 0x0050e310

int* __fastcall VecConstruct(int* p, int param)
{
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    p[4] = (int)(p + 6);
    p[1] = (int)(p + 6);
    p[0] = p[1];
    p[2] = p[0] + 0x640;
    FixedVecInit(&param);
    return p;
}

// ---------------------------------------------------------------------------
// @ 0x0050d4e0  eastl::vector<float,sp_vector_allocator>::operator=
// ---------------------------------------------------------------------------
void ea_delete(void* p);
uint32_t GrowCopy(uint32_t n, uint32_t* first, uint32_t* last);   // 0x0042e5b0
void MoveInto(void* dst, void* src, int bytes);                   // vector<bool>::DoInsertValue

uint32_t* __fastcall FloatVec_Assign(uint32_t* self, uint32_t* x)
{
    if (x != self) {
        uint32_t n = (uint32_t)((int)x[1] - (int)*x) >> 2;
        if ((uint32_t)(((int)self[2] - (int)*self) >> 2) < n) {
            uint32_t pNew = GrowCopy(n, (uint32_t*)*x, (uint32_t*)x[1]);
            for (uint32_t p = *self; p < self[1]; p += 4) {}
            if (*self != 0 && *(int*)(*self - 4) != 0)
                ea_delete((void*)*self);
            *self = pNew;
            self[2] = *self + n * 4;
        } else if ((uint32_t)(((int)self[1] - (int)*self) >> 2) < n) {
            MoveInto((void*)*self, (void*)*x, (int)(x[1] - *x));
        } else {
            for (uint32_t d = *self, s = *x; d < self[1]; d += 4, s += 4)
                *(uint32_t*)d = *(uint32_t*)s;
        }
        self[1] = *self + n * 4;
    }
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x0050c6c0 (2 KB) and @ 0x0050d070 (0.8 KB): PARTIAL skeletons
// ---------------------------------------------------------------------------
void __fastcall ProcessC(int self) { (void)self; }
void __fastcall ProcessD(int self) { (void)self; }
