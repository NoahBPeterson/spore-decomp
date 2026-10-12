#!/usr/bin/env python3
"""Capture the game's own window (even when other windows cover it) and say whether it is black.

usage: winshot.py <out.png> [owner-substring=SporeApp]
Prints: "<window id> <w>x<h> dark=<fraction> mean=<brightness>" or "no window".
Exit 0 = window found and not black, 2 = black (dark fraction > 0.97), 1 = no window.

Uses CoreGraphics through ctypes (no PyObjC): CGWindowListCopyWindowInfo to find the window id by
owner name, then `screencapture -l<id>`, which reads the window server's backing store, so the
capture is the window's content regardless of what is in front of it. PIL measures the result.
"""
import ctypes, ctypes.util, subprocess, sys

cf = ctypes.CDLL(ctypes.util.find_library("CoreFoundation"))
cg = ctypes.CDLL(ctypes.util.find_library("CoreGraphics"))
cf.CFArrayGetCount.restype = ctypes.c_long
cf.CFArrayGetCount.argtypes = [ctypes.c_void_p]
cf.CFArrayGetValueAtIndex.restype = ctypes.c_void_p
cf.CFArrayGetValueAtIndex.argtypes = [ctypes.c_void_p, ctypes.c_long]
cf.CFDictionaryGetValue.restype = ctypes.c_void_p
cf.CFDictionaryGetValue.argtypes = [ctypes.c_void_p, ctypes.c_void_p]
cf.CFStringCreateWithCString.restype = ctypes.c_void_p
cf.CFStringCreateWithCString.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_uint32]
cf.CFStringGetCString.restype = ctypes.c_bool
cf.CFStringGetCString.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_long, ctypes.c_uint32]
cf.CFNumberGetValue.restype = ctypes.c_bool
cf.CFNumberGetValue.argtypes = [ctypes.c_void_p, ctypes.c_int, ctypes.c_void_p]
cg.CGWindowListCopyWindowInfo.restype = ctypes.c_void_p
cg.CGWindowListCopyWindowInfo.argtypes = [ctypes.c_uint32, ctypes.c_uint32]
UTF8 = 0x08000100
kCFNumberIntType = 9


def cfstr(s):
    return cf.CFStringCreateWithCString(None, s.encode(), UTF8)


def pystr(ref):
    if not ref:
        return ""
    buf = ctypes.create_string_buffer(512)
    return buf.value.decode(errors="replace") if cf.CFStringGetCString(ref, buf, 512, UTF8) else ""


def pyint(ref):
    v = ctypes.c_int(0)
    return v.value if ref and cf.CFNumberGetValue(ref, kCFNumberIntType, ctypes.byref(v)) else None


def find_window(owner_sub):
    arr = cg.CGWindowListCopyWindowInfo(0, 0)   # kCGWindowListOptionAll
    k_owner, k_num, k_on, k_bounds = cfstr("kCGWindowOwnerName"), cfstr("kCGWindowNumber"), cfstr("kCGWindowIsOnscreen"), cfstr("kCGWindowBounds")
    best = None
    for i in range(cf.CFArrayGetCount(arr)):
        d = cf.CFArrayGetValueAtIndex(arr, i)
        owner = pystr(cf.CFDictionaryGetValue(d, k_owner))
        if owner_sub.lower() not in owner.lower():
            continue
        if not pyint(cf.CFDictionaryGetValue(d, k_on)):
            continue   # Wine's hidden helper windows; the game window is on screen (any layer)
        b = cf.CFDictionaryGetValue(d, k_bounds)
        w = pyint(cf.CFDictionaryGetValue(b, cfstr("Width"))) or 0
        h = pyint(cf.CFDictionaryGetValue(b, cfstr("Height"))) or 0
        wid = pyint(cf.CFDictionaryGetValue(d, k_num))
        if wid and w * h > (best[1] * best[2] if best else 0):
            best = (wid, w, h)
    return best


def main():
    out = sys.argv[1]
    owner = sys.argv[2] if len(sys.argv) > 2 else "SporeApp"
    win = find_window(owner)
    if not win:
        print("no window")
        return 1
    wid, w, h = win
    subprocess.run(["screencapture", "-x", "-o", "-l%d" % wid, out], check=False)
    from PIL import Image
    im = Image.open(out).convert("L")
    im.thumbnail((400, 400))
    px = list(im.getdata())
    dark = sum(1 for p in px if p < 16) / max(1, len(px))
    mean = sum(px) / max(1, len(px))
    print("%d %dx%d dark=%.3f mean=%.1f" % (wid, w, h, dark, mean))
    return 2 if dark > 0.97 else 0


if __name__ == "__main__":
    sys.exit(main())
