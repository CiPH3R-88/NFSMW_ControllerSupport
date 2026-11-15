# NFSMW_Controller Support

A lightweight, modern standalone controller plugin for **Need for Speed: Most Wanted (2005) v1.3**, built from the ground up with clean C++ and reverse engineering in IDA Pro.

Adds full native gamepad support, high-resolution Xbox and PlayStation button glyphs, console-accurate menu navigation, deadzone filtering, in-game options menu integration, and seamless hotplugging.

---

## Features

### 🎮 Dynamic Controller Icons & Glyphs

- **Xbox & PlayStation Layouts:** Injects authentic high-resolution button icons for Xbox (A, B, X, Y, LB, RB, LT, RT, D-pad, Start, Back) and PlayStation (Cross, Circle, Square, Triangle, L1, R1, L2, R2, D-pad, Start, Select).
- **Hardware Auto-Detection:** Automatically detects connected gamepads via USB/Bluetooth Vendor ID (`0x045E` = Microsoft Xbox, `0x054C` = Sony PlayStation) with optional manual override in the INI.
- **Dynamic Input Switching:** Automatically switches between Controller and Keyboard prompts on the fly the moment you press a button or move the mouse/keyboard.
- **High-Resolution Textures:** Button assets are packaged into a standalone `.bin` (TPK format) and injected directly into the game's FEng UI engine.

### 🧭 Console-Accurate Menu Navigation

- **Console Layout:** Restores authentic console controls across all menus (A / Cross = Accept, B / Circle = Back, Y / Triangle = Secondary).
- **Full Menu Button Actions:**
  - **X / Square:** Toggle Basic/Advanced tab in Video Options, Clear keybind in Controls Options, "Max Performance" quick upgrade in Performance Shops, and View Tutorial in Custom Race.
  - **Start:** Pause game during races, and toggle "View Cart" open/close in car lots and performance shops.
  - **Select / Back:** Trigger vehicle Showcase in customization menus.
  - **Stick Click:** Pressing Left Stick + Right Stick simultaneously resets the car on track.

### ⚙️ Controls Menu Integration

- **Friendly Button Names:** Replaces generic DirectInput numbers (`" 1"`, `" 2"`, `" 3"`, `" 4"`) with clean controller button names (`"A"`, `"B"`, `"X"`, `"Y"`, `"LB"`, `"RB"`, etc. or PlayStation equivalents) directly inside the in-game **Options &rarr; Controls** screen.
- **100% Stable:** Preserves the game's internal input pipeline — no crashes, no disabled menus, and no custom external mapping tools needed.

### 🎯 Analog Deadzone & Calibration

- **Stick Deadzone Elimination:** Independently configurable percentage deadzones for both Left Stick and Right Stick (`LeftStickDeadzone`, `RightStickDeadzone`) to eliminate stick drift on worn controllers.
- **Trigger Resting Filter:** Applies a resting filter on analog triggers (LT / RT) to prevent digital actions (such as Look Behind) from misfiring accidentally.

### 🕹️ In-Game Gameplay Options Toggle

- **Dynamic Menu Integration:** Appends a native **Controller** setting (`Off`, `Xbox`, `PlayStation`) directly into the in-game **Gameplay Options** screen when running in Auto mode (`ControllerSupport = 3`), allowing on-the-fly switching without editing INI files.

### 🔌 Hotplugging & Disconnect Handling

- **Plug-and-Play:** Connect, disconnect, or switch controllers at any time before or during gameplay. The game dynamically adapts its input polling, icons, and menus without freezing or crashing.
- **Simultaneous Input:** Blended input handling ensures keyboard and `Esc` pause functions remain responsive even while a gamepad is in active use.

---

## Installation

1. Copy `NFSMW_ControllerSupport.asi`, `NFSMW_ControllerSupport.ini` into your game's `scripts/` and `NFSMW_ControllerSupport.bin` into your game's `global/` folder (requires an ASI Loader - [`dinput8.dll`](https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases)).
2. Configure settings inside `NFSMW_ControllerSupport.ini` to your preference.

> [!NOTE]
> `NFSMW_ControllerSupport.bin` must be placed in the same folder as `NFSMW_ControllerSupport.asi` (or the game root) to load the button icons.

---

## Configuration Overview

All options can be configured in `scripts/NFSMW_ControllerSupport.ini`:

### `[CONTROLLER]`

| Setting              | Default | Description                                                                                                        |
| :------------------- | :------ | :----------------------------------------------------------------------------------------------------------------- |
| `ControllerSupport`  | `3`     | `0` = Off (Keyboard only) \| `1` = Force Xbox \| `2` = Force PlayStation \| `3` = Auto-detect connected controller |
| `LeftStickDeadzone`  | `10.0`  | Deadzone percentage for the left analog stick (e.g. `10.0` = 10%)                                                  |
| `RightStickDeadzone` | `10.0`  | Deadzone percentage for the right analog stick (e.g. `10.0` = 10%)                                                 |

---

## Mod Compatibility

- Fully compatible with **NFSMW_WideScreenMode** out of the box.
- Fully compatible with **X360Stuff**, **Sunset Mod**, and other script mods.

---

## Credits

- **nlg** — Providing the IDA Pro database for NFS Most Wanted.
- **ThirteenAG** — Referred to for initial research on DirectInput hooks and texture injection.
