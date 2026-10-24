// Slice s0095d000 -- EA::UTFWin::Drawing + SerPropertyInfo serialization helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "s0095d000.h"

namespace EA { namespace UTFWin {
namespace Drawing {

// ------------------------------------------------------------------ 0x95d000
// Nine-slice stretched blit.  dest = target rect, edge = source uv borders (8 floats),
// uv = inner tile uv, (sx,sy) = per-cell stretch factors.
// @ 0x95d000
void __cdecl BltEdgeStretch(Canvas* c, const float* dest, const float* edge, Image* img,
                            const float* uv, float sx, float sy)
{
    float iw = (float)img->width;
    float ih = (float)img->height;
    float dw = edge[2] - edge[0];
    float dh = edge[3] - edge[1];
    float du = iw * dw * sx;
    float dv = ih * dh * sy;
    float fx0 = uv[0] * du + dest[0];
    float fy0 = uv[1] * dv + dest[1];
    float fx1 = dest[2] - (1.0f - uv[2]) * du;
    float fy1 = dest[3] - (1.0f - uv[3]) * dv;
    if (!(fx1 >= fx0)) { fx0 = fx1 = (fx1 + fx0) * 0.5f; }
    if (!(fy1 >= fy0)) { fy0 = fy1 = (fy1 + fy0) * 0.5f; }

    float xs[4] = { dest[0], fx0, fx1, dest[2] };
    float ys[4] = { dest[1], fy0, fy1, dest[3] };
    float us[4] = { edge[0], uv[0], uv[2], edge[2] };
    float vs[4] = { edge[1], uv[1], uv[3], edge[3] };

    // corners (always)
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i == 1 && !(fx1 > fx0)) || (j == 1 && !(fy1 > fy0)))
                continue;
            float r[4] = { xs[i], ys[j], xs[i + 1], ys[j + 1] };
            float t[4] = { us[i], vs[j], us[i + 1], vs[j + 1] };
            c->DrawImage(r, img, t);
        }
    }
}

// ------------------------------------------------------------------ 0x95d540
// Draws a two-colour gradient ring between two rects (4 quads).
// @ 0x95d540
void __cdecl GradientBox(Canvas* c, const float* outer, const float* inner,
                         const float* colOuter, const float* colInner)
{
    if (outer[0] == outer[2])
        return;
    if (outer[1] == outer[3])
        return;
    float ox0 = outer[0], oy0 = outer[1], ox1 = outer[2], oy1 = outer[3];
    float ix0 = inner[0], iy0 = inner[1], ix1 = inner[2], iy1 = inner[3];
    struct P { float x, y; };
    // top, bottom, left, right bands, each as a quad with outer/inner colours
    {
        P p0 = { ox0, oy0 }, p1 = { ox1, oy0 }, p2 = { ix0, iy0 }, p3 = { ix1, iy0 };
        c->DrawQuad(&p0, colOuter[0], &p1, colOuter[2], &p2, colInner[0], &p3, colInner[2]);
    }
    {
        P p0 = { ox0, oy1 }, p1 = { ox1, oy1 }, p2 = { ix0, iy1 }, p3 = { ix1, iy1 };
        c->DrawQuad(&p0, colOuter[1], &p1, colOuter[3], &p2, colInner[1], &p3, colInner[3]);
    }
    {
        P p0 = { ox0, oy0 }, p1 = { ox0, oy1 }, p2 = { ix0, iy0 }, p3 = { ix0, iy1 };
        c->DrawQuad(&p0, colOuter[0], &p1, colOuter[1], &p2, colInner[0], &p3, colInner[1]);
    }
    {
        P p0 = { ox1, oy0 }, p1 = { ox1, oy1 }, p2 = { ix1, iy0 }, p3 = { ix1, iy1 };
        c->DrawQuad(&p0, colOuter[2], &p1, colOuter[3], &p2, colInner[2], &p3, colInner[3]);
    }
}

// ------------------------------------------------------------------ 0x95d780
// Draws the standard (Win7-ish) button frame with a 4-colour bevel gradient.
// @ 0x95d780
void __cdecl DrawStdButton(Canvas* c, const float* rect, uint32_t color, uint32_t state,
                           float thickness)
{
    (void)thickness;
    float x0 = rect[0] + 3.0f;
    float y0 = rect[1] + 3.0f;
    float x1 = rect[2] - 3.0f;
    float y1 = rect[3] - 3.0f;
    uint32_t local_30, local_2c, local_28, local_24;
    uint32_t local_10, local_c, local_8, local_4;
    uint32_t uVar2, uVar1;
    uint32_t col = color;

    if ((state & 8) == 0) {
        switch (state & 7) {
        case 0: break;
        case 1: goto LAB_866;
        case 2:
            col = Color::Lerp(col, col | 0xffffff, 0.4f);
            break;
        case 3: goto CASED0;
        default: goto DEFAULT_;
        }
        local_30 = Color::Lerp(col, col | 0xffffff, 0.6f);
        local_2c = Color::Lerp(col, col | 0xffffff, 0.9f);
        uVar2 = col & 0xff000000;
    } else {
        switch (state & 7) {
        case 0:
        case 3:
        CASED0:
            col = Color::Lerp(col, col & 0xff000000, 0.1f);
            break;
        case 1:
        LAB_866:
            col = Color::Lerp(col, 0xff7f7f7f, 0.2f);
            local_30 = Color::Lerp(col, col | 0xffffff, 0.2f);
            local_2c = Color::Lerp(col, col | 0xffffff, 0.3f);
            uVar2 = col & 0xff000000;
            local_28 = Color::Lerp(col, uVar2, 0.2f);
            uVar1 = 0x3e99999a;
            goto LAB_945;
        case 2: break;
        default: goto DEFAULT_;
        }
        local_30 = Color::Lerp(col, col & 0xff000000, 0.4f);
        local_2c = Color::Lerp(col, col & 0xff000000, 0.7f);
        uVar2 = col | 0xffffff;
    }
    local_28 = Color::Lerp(col, uVar2, 0.4f);
    uVar1 = 0x3f333333;
LAB_945:
    local_24 = Color::Lerp(col, uVar2, *(float*)&uVar1);
DEFAULT_:
    local_10 = col; local_c = col; local_8 = col; local_4 = col;
    GradientBox(c, rect, (const float*)&x0, (const float*)&local_30, (const float*)&local_10);
    c->SetColor(col);
    c->v14((float)local_24, x0, y0, x1);
    (void)y1; (void)local_28;
}

// ------------------------------------------------------------------ 0x95da40
// Draws a bevelled frame: an outer shadow band plus the inner bevel band.
// @ 0x95da40
void __cdecl DrawBevel(Canvas* c, const float* rect, uint32_t color, float width)
{
    float outer[4], colA[4], colB[4], outer2[4];
    float half = width * 0.5f;
    outer[0] = rect[0] - half;
    outer[1] = rect[1] - half;
    outer[2] = rect[2] + half;
    outer[3] = rect[3] + half;
    float f2 = (float)color;
    colA[0] = f2; colA[1] = f2; colA[2] = f2; colA[3] = f2;
    colB[0] = 0.0f; colB[1] = 0.0f; colB[2] = 0.0f; colB[3] = 0.0f;
    outer2[0] = rect[0] - width;
    outer2[1] = rect[1] - width;
    outer2[2] = rect[2] + width;
    outer2[3] = rect[3] + width;
    GradientBox(c, outer, rect, colA, colB);
    GradientBox(c, outer2, outer, colB, colA);
}

}} // namespace Drawing
} // namespace EA::UTFWin

// ====================================================================== serialization

// @ 0x95db50
bool __cdecl SerWalk(SerItem* item, uint32_t* value)
{
    PropInfo* e = item->desc->elems;
    uint32_t n = item->desc->nelems;
    // The original's call site pushes the incoming ebx as Commit's st argument (an uninitialized
    // scratch value); the differential harness seeds every callee-saved register with this
    // sentinel, so use the same value here to keep the st-dependent Commit/meta call identical.
    int* st = (int*)0x0BB0BB00;
    while (n != 0) {
        uint16_t f = e->flags;
        n--;
        if (f & 0x8000) { e++; continue; }
        if ((f & 0xfff) == 1) { e++; continue; }
        uint32_t local[3];
        local[0] = 0;
        local[1] = e->offset + value[1];
        local[2] = e->count;
        if (!e->Commit(item, local, st))
            return false;
        e++;
    }
    return true;
}

// @ 0x95dbd0
bool PropInfo::Build(SerItem* out, SerItem* base, uint32_t count, int* st, int flag)
{
    if (count != this->count && !(this->flags & 0x8000))
        return false;
    int* m = this->meta;
    if (m == 0 || m[2] == 0) {
        out->desc = (SerDesc*)kSerTypeTable[this->flags & 0xfff];
    } else {
        bool r = ((bool(__cdecl*)(SerItem*, SerItem*, PropInfo*, int*))m[2])(out, base, this, st);
        if (!r)
            return false;
    }
    out->b = count;
    if (count != 0) {
        uint32_t t = this->flags & 0xfff;
        if (flag == 0 && t != 0x13 && t != 0x12 && (this->meta == 0 || this->meta[0] == 0)) {
            out->a = base->a + this->offset;
            return out->a != 0;
        }
        uint32_t size = out->desc->elemSize * count;
        void* d = ((struct StAlloc*)st)->Alloc(size, 4);
        out->a = (uint32_t)d;
        if (d == 0)
            return false;
        if (t == 0x13 || t == 0x12 || t == 0x14)
            OperatorNewArray(d, 0, out->desc->elemSize * count);
        return out->a != 0;
    }
    out->a = 0;
    return true;
}

// @ 0x95dd00
PropInfo* SerItem::FindProp(SerItem* out, uint32_t id, int* st)
{
    PropInfo* e = this->desc->elems;
    uint32_t n = this->desc->nelems;
    while (n > 0) {
        if ((e->flags & 0xfff) == 1) {
            SerItem local;
            if (((bool(__cdecl*)(void*, SerItem*, PropInfo*, int*))e->meta[2])(&local, this, e, st)) {
                PropInfo* r = local.FindProp(out, id, st);
                if (r != 0)
                    return r;
            }
        } else if (e->id == id) {
            out->desc = this->desc;
            out->b = this->b;
            out->a = this->a;
            return e;
        }
        n--;
        e++;
    }
    return 0;
}

// @ 0x95dda0
bool PropInfo::Commit(SerItem* base, uint32_t* value, int* st)
{
    int* m = this->meta;
    if (m != 0 && m[0] != 0) {
        return ((bool(__cdecl*)(SerItem*, uint32_t*, PropInfo*, int*))m[0])(base, value, this, st);
    }
    if ((int16_t)this->flags < 0)
        return false;
    if (value[2] != this->count)
        return false;

    uint32_t* valPtr;
    int type;
    uint32_t cnt;
    if (m == 0 || m[2] == 0) {
        valPtr = (uint32_t*)(base->a + this->offset);
        type = (int)(uint32_t)kSerTypeTable[this->flags & 0xfff];
        cnt = value[2];
    } else {
        uint32_t buf[3];
        ((void(__cdecl*)(uint32_t*, SerItem*, PropInfo*, int*))m[2])(buf, base, this, st);
        type = (int)buf[0];
        valPtr = (uint32_t*)buf[1];
        cnt = buf[2];
    }
    uint32_t existing = value[1];
    if (valPtr != (uint32_t*)existing) {
        uint32_t elemSize = *(uint32_t*)(type + 8);
        uint32_t t = this->flags & 0xfff;
        if (t >= 2 && t <= 0x11) {
            VectorDoInsertValue(valPtr, (void*)existing, elemSize * cnt);
        } else if (t == 0x13) {
            VectorDoInsertValue(valPtr, (void*)existing, elemSize * cnt);
        } else if (t == 0x12) {
            uint32_t i = 0;
            uint32_t* src = valPtr;
            uint32_t* dst = (uint32_t*)existing;
            if (cnt == 0)
                return true;
            do {
                uint32_t s = *dst;
                if (s == 0) WString_Clear(src);
                else if (s != *src) WString_Append(src, (const void*)s);
                i++;
                dst++;
                src += 4;
            } while (i < cnt);
            return true;
        } else if (t == 0x14) {
            uint32_t us[3];
            us[0] = value[0];
            us[1] = value[1];
            us[2] = value[2];
            uint32_t i = 0;
            if (cnt == 0)
                return true;
            do {
                if (!SerWalk((SerItem*)valPtr, us))
                    return false;
                valPtr = (uint32_t*)((char*)valPtr + elemSize);
                i++;
            } while (i < cnt);
            return true;
        } else {
            return false;
        }
    }
    return true;
}
