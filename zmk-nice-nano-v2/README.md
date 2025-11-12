# ZMK Custom Keyboard for Nice Nano V2

Custom 60-key keyboard with analog potentiometers running ZMK firmware on Nice Nano V2 (nRF52840).

## Hardware Specifications

- **MCU**: nRF52840 (Nice Nano V2)
- **Layout**: 5 rows × 12 columns (60 keys)
- **Analog Controls**: 2 potentiometers (P0.29, P0.31)
- **Connectivity**: USB-C and Bluetooth 5.0

### Pin Mapping

**Rows:**
- R1: P0.10
- R2: P1.11
- R3: P1.13
- R4: P1.15
- R5: P0.02

**Columns:**
- C1: P1.00, C2: P0.11, C3: P1.04, C4: P0.22
- C5: P0.24, C6: P1.06, C7: P0.09, C8: P1.01
- C9: P1.02, C10: P0.20, C11: P0.17, C12: P1.07

**Analog Inputs:**
- Knob 1: P0.29 (AIN1)
- Knob 2: P0.31 (AIN3)

## Project Structure

```
zmk-nice-nano-v2/
├── .github/workflows/
│   └── build.yml                    # GitHub Actions build automation
├── app/
│   ├── boards/arm/nice_nano_v2/
│   │   ├── board.c                  # Board initialization
│   │   ├── board.cmake              # Build configuration
│   │   ├── board.dts                # Device tree (pin config, matrix)
│   │   ├── Kconfig.board            # Board Kconfig
│   │   ├── Kconfig.defconfig        # Default configs
│   │   ├── nice_nano_v2_defconfig   # Board defaults
│   │   └── nice_nano_v2-pinctrl.dtsi # Pin control definitions
│   ├── keymaps/default/
│   │   └── keymap.keymap            # Key bindings and layers
│   ├── src/
│   │   └── layout.c                 # Custom layout code
│   └── prj.conf                     # ZMK project configuration
├── config/
│   └── overlay.conf                 # Additional configurations
├── build.yaml                       # Build targets
├── CMakeLists.txt                   # CMake build file
├── west.yml                         # West manifest
└── README.md                        # This file
```

## Building the Firmware

### Option 1: GitHub Actions Build (RECOMMENDED for Windows)

This is the easiest method - no local setup required!

1. **Push to GitHub:**
   ```powershell
   git add .
   git commit -m "Update ZMK configuration"
   git push
   ```

2. **Download firmware:**
   - Go to your repository's "Actions" tab on GitHub
   - Click on the latest workflow run
   - Download the firmware artifact (`nice_nano_v2.uf2`)

3. **Flash to board:**
   - Put Nice Nano V2 into bootloader mode (double-tap reset button)
   - Copy the `.uf2` file to the USB drive that appears (named "NICENANO")

### Option 2: Local Build with Docker (Windows/Linux/Mac)

Using Docker avoids complex local setup:

1. **Install Docker Desktop:**
   - Download from [docker.com](https://www.docker.com/products/docker-desktop)

2. **Build firmware:**
   ```powershell
   cd zmk-nice-nano-v2
   docker run --rm -v ${PWD}:/workspace zmkfirmware/zmk-build-arm:stable west build -s /workspace/zmk/app -b nice_nano_v2 -- -DZMK_CONFIG="/workspace/config"
   ```

3. **Find firmware:**
   - Output: `build/zephyr/zmk.uf2`

### Option 3: Local Build with West (Advanced)

For advanced users who want a native development environment:

#### Prerequisites

1. **Install Python 3.8+** (you have 3.11 ✓)
2. **Install West:**
   ```powershell
   pip install west
   ```

3. **Install Zephyr SDK:**
   - Download [Zephyr SDK](https://github.com/zephyrproject-rtos/sdk-ng/releases)
   - Extract to `C:\zephyr-sdk-0.16.x`
   - Run: `C:\zephyr-sdk-0.16.x\setup.cmd`

4. **Install CMake and Ninja:**
   ```powershell
   winget install Kitware.CMake
   winget install Ninja-build.Ninja
   ```

#### Build Steps

1. **Create workspace:**
   ```powershell
   cd C:\Users\tigey\Documents\GitHub\lgk-zmk
   mkdir zmk-workspace
   cd zmk-workspace
   ```

2. **Initialize ZMK:**
   ```powershell
   west init -l ..\zmk-nice-nano-v2
   west update
   west zephyr-export
   pip install -r zephyr\scripts\requirements.txt
   ```

3. **Build firmware:**
   ```powershell
   west build -s zmk\app -b nice_nano_v2 -- -DZMK_CONFIG="${PWD}\..\zmk-nice-nano-v2\config"
   ```

4. **Find firmware:**
   - Output: `build\zephyr\zmk.uf2`

### Flashing

1. Double-tap reset button on Nice Nano V2 (LED should pulse)
2. USB drive named "NICENANO" appears
3. Copy `zmk.uf2` to the drive
4. Drive auto-ejects and keyboard is ready!

## Keymap

### Default Layer
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬──────┐
│ ESC │  1  │  2  │  3  │ VDN │ VUP │ PLY │  7  │  8  │  9  │  0  │ BKSP │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│ TAB │  Q  │  W  │  E  │  4  │  5  │  6  │  U  │  I  │  O  │  P  │  \   │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│ CLK │  A  │  S  │  D  │  R  │  T  │  Y  │  J  │  K  │  L  │ ENT │      │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│ SFT │  Z  │  X  │  C  │  F  │  G  │  H  │  M  │  .  │  ↑  │ SFT │      │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│ CTL │ FN  │ WIN │ SPC │  V  │  B  │  N  │ ALT │  ←  │  ↓  │  →  │      │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴──────┘
```

### Function Layer (Hold FN)
```
┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┬──────┐
│  `  │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ DEL  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│     │ BT1 │ BT2 │ BT3 │ BT4 │ BT5 │     │     │     │     │ F11 │ F12  │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│     │     │     │     │     │     │     │     │     │     │     │      │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│     │     │     │     │     │     │     │     │     │PGUP │     │      │
├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┼──────┤
│     │     │     │     │     │BTCLR│     │     │HOME │PGDN │ END │      │
└─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴─────┴──────┘
```

## Customization

### Modifying Keymap

Edit `app/keymaps/default/keymap.keymap` to change key bindings. See [ZMK keycodes documentation](https://zmk.dev/docs/codes).

### Changing Pin Assignments

Modify `app/boards/arm/nice_nano_v2/board.dts` to change GPIO pin mappings.

### Configuration Options

Add configuration options to `config/overlay.conf` or `app/prj.conf`.

## Features

- ✅ 5×12 key matrix scanning
- ✅ USB HID keyboard
- ✅ Bluetooth LE (up to 5 devices)
- ✅ Two-layer keymap
- ✅ Media keys (volume, play/pause)
- ✅ Function layer with F-keys and Bluetooth controls
- ⚠️ Analog potentiometers (requires custom implementation)

## Troubleshooting

### Build Errors
- Ensure West and Zephyr SDK are properly installed
- Run `west update` to sync dependencies
- Check that all paths in `west.yml` are correct

### Flashing Issues
- Verify Nice Nano V2 is in bootloader mode (LED should pulse)
- Try a different USB cable or port
- Check USB drive appears as "NICENANO"

### Keys Not Working
- Verify pin assignments in `board.dts`
- Check diode direction setting in device tree
- Test with multimeter or oscilloscope

## Resources

- [ZMK Documentation](https://zmk.dev/docs)
- [Nice Nano V2 Documentation](https://nicekeyboards.com/docs/nice-nano/)
- [Zephyr Project](https://docs.zephyrproject.org/)
- [nRF52840 Datasheet](https://www.nordicsemi.com/products/nrf52840)

## License

MIT License - See LICENSE file for details

## Contributing

Feel free to contribute to this project by submitting issues or pull requests. Your feedback and improvements are welcome!

## License

This project is licensed under the MIT License. See the LICENSE file for more details.