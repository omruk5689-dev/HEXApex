<img width="713" height="643" alt="Screenshot 2026-10-11 002511" src="https://github.com/user-attachments/assets/a9fb662c-952c-4d89-a086-142ef56faf0e" />

<img width="527" height="530" alt="Screenshot 2026-10-10 142509" src="https://github.com/user-attachments/assets/c9ddd32c-890e-47ef-96e8-e3b67ec25796" />
# HEXApex

A 3x3 macropad with three rotary encoders (RP2040, board name MACROPeX / HEXAPEX).

| File | What it is |
| --- | --- |
| `hexapex_simulator.html` | 3D simulator of the pad (keys, encoders, RGB) |
| `hexapex_bridge.py` | Helper that lets the simulator press real shortcuts in EasyEDA / VS Code |
| `macropex_qmk/` | QMK firmware for the real board (`keyboard.json`, `keymaps/default/keymap.c`) |

## Run the simulator with the helper (Windows)

1. Install Python 3 (python.org, tick "Add Python to PATH").
2. In PowerShell: `pip install pynput`
3. Put `hexapex_bridge.py` and `hexapex_simulator.html` in the same folder.
4. In that folder run: `python hexapex_bridge.py` (use `py` if `python` is not found).
5. The simulator opens at `http://127.0.0.1:8765`. Drag the tab into its own window next to EasyEDA or VS Code. The "Connection to your PC" box should show a green dot.
6. Click into EasyEDA or VS Code once, then click a pad key. The shortcut is pressed there. The helper switches back with Alt+Tab, so the window flickers briefly.

Stop the helper with Ctrl+C in its window. Opening the HTML file directly (or the preview link) only gives the visual preview, with no control of other apps.

## Firmware (QMK)

Copy `keyboard.json` to `keyboards/voltedge/macropex/` and `keymap.c` to `keyboards/voltedge/macropex/keymaps/default/`, then:

```
qmk compile -kb voltedge/macropex -km default
```

Hold BOOT while plugging in USB and copy the `.uf2` to the `RPI-RP2` drive.

Pins (from the schematic): columns GP0-GP2, rows GP8-GP10 (COL2ROW), encoders GP15/16, GP17/18, GP19/20, key RGB data GP24, user LED GP25, user RGB LED GP26/27/28.

