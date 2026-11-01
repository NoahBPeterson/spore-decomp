"""wgc.py OUT: one frame of the SPORE(TM) window through Windows.Graphics.Capture (sees Direct3D content, also over RDP)."""
import sys, threading, time
from windows_capture import WindowsCapture
out = sys.argv[1]
done = threading.Event()
cap = WindowsCapture(cursor_capture=False, draw_border=False, window_name="SPORE(TM)")

@cap.event
def on_frame_arrived(frame, control):
    frame.save_as_image(out)
    done.set()
    control.stop()

@cap.event
def on_closed():
    done.set()

try:
    c = cap.start_free_threaded()
except Exception as e:
    print("capture failed:", e); sys.exit(1)
ok = done.wait(8)
print("saved" if ok else "no frame in 8 s")
try:
    c.stop()
except Exception:
    pass
