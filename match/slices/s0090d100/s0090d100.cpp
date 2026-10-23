// Slice s0090d100 -- GFx/Scaleform-style XML markup scanner (character-class
// driven tokeniser).  The parser object holds a 256-entry character class table
// at +0x4c and a bank of per-class character handlers at +0x14c .. +0x16c.
//
//  0x0090d100  scan one markup element / tag body (cdecl: parser, cur, end, out)
//  0x0090d320  scan an attribute / text run (cursor in EAX, parser in EBX)
//  0x0090d580  skip XML whitespace, stop at '>' (cursor EAX, parser EDX)
//  0x0090d5d0  scan a numeric/entity reference (cursor EAX, parser EDX)
//  0x0090d630  scan an element name (cursor in EAX, parser in EBX)
//  0x0090d830  scan an element body / comment (cursor in EAX, parser in EBX)
//
// Only FUN_0090d100 passes every argument on the stack; the others follow the
// module's whole-program register ABI (cursor in EAX, parser in EBX or EDX),
// so their reconstructions below take those values as ordinary parameters.

typedef unsigned char byte;

// Per-class character handler: (parser, cursor) -> nonzero when the character
// sequence starting at cursor is a valid token of that class.
typedef int (__cdecl *CharHandler)(void* parser, const byte* p);

static inline int cls_of(const void* parser, byte c)
{
    return ((const byte*)parser)[0x4c + c];
}

static inline int call_handler(void* parser, int off, const byte* p)
{
    return (*(CharHandler*)((char*)parser + off))(parser, p);
}

int FUN_0090d100(void* parser, const byte* begin, const byte* end, const byte** out);
int FUN_0090d320(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d580(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d5d0(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d630(void* parser, const byte* cur, const byte* end, const byte** out);
int FUN_0090d830(void* parser, const byte* cur, const byte* end, const byte** out);

// @ 0x0090d100
int FUN_0090d100(void* parser, const byte* begin, const byte* end, const byte** out)
{
    const byte* p = begin;
    const byte* pb;

    if (p == end)
        return -4;

    switch (((const byte*)parser)[0x4c + *p]) {
    case 4:
        p++;
        if (p == end)
            return -1;
        if (*p == ']') {
            p++;
            if (p == end)
                return -1;
            if (*p != '>') {
                p--;
                break;
            }
            *out = p + 1;
            return 0x28;
        }
        break;
    case 9:
        p++;
        if (p == end)
            return -1;
        if (((const byte*)parser)[0x4c + *p] == 10)
            p++;
        *out = p;
        return 7;
    case 10:
        *out = p + 1;
        return 7;
    case 5:
        if (end - p < 2)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x164))(parser, p) != 0) {
            *out = p;
            return 0;
        }
        p += 2;
        break;
    case 6:
        if (end - p < 3)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x168))(parser, p) != 0) {
            *out = p;
            return 0;
        }
        p += 3;
        break;
    case 7:
        if (end - p < 4)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x16c))(parser, p) != 0) {
            *out = p;
            return 0;
        }
        p += 4;
        break;
    case 0:
    case 1:
    case 8:
        *out = p;
        return 0;
    default:
        p++;
        break;
    }

    if (p != end) {
        int rem = (int)(end - p);
        do {
            switch (((const byte*)parser)[0x4c + *p]) {
            case 5:
                if (rem < 2) {
                    *out = p;
                    return 6;
                }
                if ((*(CharHandler*)((char*)parser + 0x164))(parser, p) != 0) {
                    *out = p;
                    return 6;
                }
                p += 2;
                rem -= 2;
                break;
            case 6:
                if (rem < 3) {
                    *out = p;
                    return 6;
                }
                if ((*(CharHandler*)((char*)parser + 0x168))(parser, p) != 0) {
                    *out = p;
                    return 6;
                }
                p += 3;
                rem -= 3;
                break;
            case 7:
                if (rem < 4) {
                    *out = p;
                    return 6;
                }
                if ((*(CharHandler*)((char*)parser + 0x16c))(parser, p) != 0) {
                    *out = p;
                    return 6;
                }
                p += 4;
                rem -= 4;
                break;
            case 0:
            case 1:
            case 4:
            case 8:
            case 9:
            case 10:
                *out = p;
                return 6;
            default:
                p++;
                rem--;
                break;
            }
        } while (p != end);
    }
    *out = p;
    return 6;
}

// @ 0x0090d320
int FUN_0090d320(void* parser, const byte* cur, const byte* end, const byte** out)
{
    const byte* pb;

    if (cur == end)
        return -1;

    switch (((const byte*)parser)[0x4c + *cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x158))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x15c))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x160))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 4;
        break;
    case 0x16:
    case 0x18:
        pb = cur + 1;
        break;
    default:
        *out = cur;
        return 0;
    }

    if (pb == end)
        return -1;

    for (;;) {
        int rem = (int)(end - pb);
        switch (((const byte*)parser)[0x4c + *pb]) {
        case 5:
            if (rem < 2)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x14c))(parser, pb) != 0) {
                pb += 2;
                rem -= 2;
                break;
            }
            *out = pb;
            return 0;
        case 6:
            if (rem < 3)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x150))(parser, pb) != 0) {
                pb += 3;
                rem -= 3;
                break;
            }
            *out = pb;
            return 0;
        case 7:
            if (rem < 4)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x154))(parser, pb) != 0) {
                pb += 4;
                rem -= 4;
                break;
            }
            *out = pb;
            return 0;
        case 9:
        case 10:
        case 0x15:
            pb++;
            if (pb == end)
                return -1;
            for (;;) {
                int c = ((const byte*)parser)[0x4c + *pb];
                if (c == 9 || c == 10 || c == 0x15) {
                    pb++;
                    if (pb == end)
                        return -1;
                    continue;
                }
                if (c == 0xb) {
                    *out = pb + 1;
                    return 5;
                }
                *out = pb;
                return 0;
            }
        case 0xb:
            *out = pb + 1;
            return 5;
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            pb++;
            rem--;
            break;
        default:
            *out = pb;
            return 0;
        }
        if (pb == end)
            return -1;
    }
}

// @ 0x0090d580
int FUN_0090d580(void* parser, const byte* cur, const byte* end, const byte** out)
{
    int c;

    if (cur == end)
        return -1;

    for (;;) {
        c = ((const byte*)parser)[0x4c + *cur];
        if ((byte)(c - 0x18) > 1) {
            *out = cur;
            return 0;
        }
        cur++;
        if (cur == end)
            return -1;
        c = ((const byte*)parser)[0x4c + *cur];
        if (c == 0x12) {
            *out = cur + 1;
            return 10;
        }
        if ((byte)(c - 0x18) > 1) {
            *out = cur;
            return 0;
        }
        cur++;
        if (cur == end)
            return -1;
    }
}

// @ 0x0090d5d0
int FUN_0090d5d0(void* parser, const byte* cur, const byte* end, const byte** out)
{
    int c;

    if (cur == end)
        return -1;

    if (*cur == 'x')
        return FUN_0090d580(parser, cur + 1, end, out);

    for (;;) {
        c = ((const byte*)parser)[0x4c + *cur];
        if (c != 0x19) {
            *out = cur;
            return 0;
        }
        cur++;
        if (cur == end)
            return -1;
        c = ((const byte*)parser)[0x4c + *cur];
        if (c == 0x12) {
            *out = cur + 1;
            return 10;
        }
    }
}

// @ 0x0090d630
int FUN_0090d630(void* parser, const byte* cur, const byte* end, const byte** out)
{
    const byte* pb;
    int c;

    if (cur == end)
        return -1;

    switch (((const byte*)parser)[0x4c + *cur]) {
    case 5:
        if (end - cur < 2)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x158))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 2;
        break;
    case 6:
        if (end - cur < 3)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x15c))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 3;
        break;
    case 7:
        if (end - cur < 4)
            return -2;
        if ((*(CharHandler*)((char*)parser + 0x160))(parser, cur) == 0) {
            *out = cur;
            return 0;
        }
        pb = cur + 4;
        break;
    case 0x13:
        return FUN_0090d5d0(parser, cur, end, out);
    case 0x16:
    case 0x18:
        pb = cur + 1;
        break;
    default:
        *out = cur;
        return 0;
    }

    if (pb == end)
        return -1;

    for (;;) {
        int rem = (int)(end - pb);
        switch (((const byte*)parser)[0x4c + *pb]) {
        case 5:
            if (rem < 2)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x14c))(parser, pb) != 0) {
                pb += 2;
                rem -= 2;
                break;
            }
            *out = pb;
            return 0;
        case 6:
            if (rem < 3)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x150))(parser, pb) != 0) {
                pb += 3;
                rem -= 3;
                break;
            }
            *out = pb;
            return 0;
        case 7:
            if (rem < 4)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x154))(parser, pb) != 0) {
                pb += 4;
                rem -= 4;
                break;
            }
            *out = pb;
            return 0;
        case 0x12:
            *out = pb + 1;
            return 9;
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            pb++;
            rem--;
            break;
        default:
            *out = pb;
            return 0;
        }
        if (pb == end)
            return -1;
    }
}

// @ 0x0090d830
int FUN_0090d830(void* parser, const byte* cur, const byte* end, const byte** out)
{
    const byte* pb;
    const byte* pb2;
    int c;
    int seen;

    if (cur == end)
        return -1;

    seen = 0;
    for (;;) {
        switch (((const byte*)parser)[0x4c + *cur]) {
        case 5:
            if (end - cur < 2)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x14c))(parser, cur) == 0) {
                *out = cur;
                return 0;
            }
            cur += 2;
            break;
        case 6:
            if (end - cur < 3)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x150))(parser, cur) == 0) {
                *out = cur;
                return 0;
            }
            cur += 3;
            break;
        case 7:
            if (end - cur < 4)
                return -2;
            if ((*(CharHandler*)((char*)parser + 0x154))(parser, cur) != 0) {
                cur += 4;
                break;
            }
            *out = cur;
            return 0;
        case 9:
        case 10:
        case 0x15:
            for (;;) {
                cur++;
                if (cur == end)
                    return -1;
                c = ((const byte*)parser)[0x4c + *cur];
                if (c == 0xe)
                    goto scan_name;
                if (c < 9 || c > 10)
                    if (c != 0x15) {
                        *out = cur;
                        return 0;
                    }
            }
        case 0xe:
scan_name:
            seen = 0;
            for (;;) {
                cur++;
                if (cur == end)
                    return -1;
                c = ((const byte*)parser)[0x4c + *cur];
                if (c == 0xc || c == 0xd)
                    break;
                if (c < 9 || c > 10)
                    if (c != 0x15) {
                        *out = cur;
                        return 0;
                    }
            }
            for (;;) {
                cur++;
                if (cur == end)
                    return -1;
                c = ((const byte*)parser)[0x4c + *cur];
                if (c == 0xc || c == 0xd) {
                    pb2 = cur + 1;
                    if (pb2 == end)
                        return -1;
                    c = ((const byte*)parser)[0x4c + *pb2];
                    if (c == 9 || c == 10 || c == 0x15) {
                        cur = pb2;
                        break;
                    }
                    if (c == 0xb) {
                        *out = pb2 + 1;
                        return 1;
                    }
                    if (c == 0x11) {
                        pb = pb2 + 1;
                        if (pb == end)
                            return -1;
                        if (*pb == '>') {
                            *out = pb2 + 2;
                            return 3;
                        }
                        *out = pb;
                        return 0;
                    }
                    *out = pb2;
                    return 0;
                }
                if (c == 0) {
                    *out = cur;
                    return 0;
                }
                if (c == 1) {
                    *out = cur;
                    return 0;
                }
                if (c == 8) {
                    *out = cur;
                    return 0;
                }
                if (c == 2) {
                    *out = cur;
                    return 0;
                }
                if (c == 3) {
                    int r = FUN_0090d630(parser, cur + 1, end, &cur);
                    if (r == 0) {
                        *out = cur;
                        return 0;
                    }
                    if (r < 0)
                        return r;
                    break;
                }
                if (c == 5) {
                    if (end - cur < 2)
                        return -2;
                    if ((*(CharHandler*)((char*)parser + 0x164))(parser, cur) != 0) {
                        *out = cur;
                        return 0;
                    }
                    cur += 2;
                    break;
                }
                if (c == 6) {
                    if (end - cur < 3)
                        return -2;
                    if ((*(CharHandler*)((char*)parser + 0x168))(parser, cur) != 0) {
                        *out = cur;
                        return 0;
                    }
                    cur += 3;
                    break;
                }
                if (c == 7) {
                    if (end - cur < 4)
                        return -2;
                    if ((*(CharHandler*)((char*)parser + 0x16c))(parser, cur) == 0) {
                        *out = cur;
                        return 0;
                    }
                    cur += 4;
                    break;
                }
            }
            break;
        case 0x16:
        case 0x18:
        case 0x19:
        case 0x1a:
        case 0x1b:
            cur++;
            break;
        case 0x17:
            if (seen != 0) {
                *out = cur;
                return 0;
            }
            seen = 1;
            cur++;
            if (cur == end)
                return -1;
            switch (((const byte*)parser)[0x4c + *cur]) {
            case 5:
                if (end - cur < 2)
                    return -2;
                if ((*(CharHandler*)((char*)parser + 0x158))(parser, cur) == 0) {
                    *out = cur;
                    return 0;
                }
                cur += 2;
                break;
            case 6:
                if (end - cur < 3)
                    return -2;
                if ((*(CharHandler*)((char*)parser + 0x15c))(parser, cur) == 0) {
                    *out = cur;
                    return 0;
                }
                cur += 3;
                break;
            case 7:
                if (end - cur < 4)
                    return -2;
                if ((*(CharHandler*)((char*)parser + 0x160))(parser, cur) == 0) {
                    *out = cur;
                    return 0;
                }
                cur += 4;
                break;
            case 0x16:
            case 0x18:
                cur++;
                break;
            default:
                *out = cur;
                return 0;
            }
            break;
        default:
            *out = cur;
            return 0;
        }
        if (cur == end)
            return -1;
    }
}
