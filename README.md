<div align="center">

<img src="icons/onigiri.svg" width="96" alt="Kohada logo">

# Kohada

**A repair & tuning toolkit for the PlayStation 3 system controller (syscon)**

Talks to Mullion and Sherwood syscon controllers over UART

</div>

---

> [!WARNING]
> **Kohada is early-stage software that reads and *writes* the syscon EEPROM.**
> Incorrect writes can **permanently brick your console.** The author is **not
> responsible** for any damage, data loss, or other issues resulting from use of
> this tool. Use entirely at your own risk, and **always dump your EEPROM and
> keep multiple backups in a safe location before changing anything.**

---

## Demo

![Demo](assets/demo.gif)

## Features

- **EEPROM dump** - self sizing dump of the full syscon NVS (20 KB / 32 KB auto detected) plus the secondary 0x48xxx pages, saved to a single self describing container file.
- **Console identity restore guard** - before a restore, Kohada reads the QA token + platform ID + manufacturing strings from the live console and compares them to the backup, so you can't accidentally flash one console's EEPROM onto another.
- **EEPROM hex editor** with named region map and automatic checksum fix-up.
- **Fan curve editor** - drag to edit fan curves per thermal zone, with factory presets.
- **Voltage tuner** - Cell/RSX VID editor with a safety-gated range.
- **CELL / XDR overclocking** - clock generator configuration.
- **XDR memory timing override** - full 46-entry MIC descriptor editor.
- **Config ring editor** - Cell BE config-ring patch sources + scatter table.
- **NVS tweak panel** - typed editors for the documented syscon NVS fields.
- **Error-log decoder** - reads and decodes the syscon error log against a community maintained code database.

## Platform support

| Family | Status |
|--------|--------|
| **Mullion** (CXR713 / CXR714 early fat consoles) | Primary target. Well supported. |
| **Sherwood** (late fat / slim / super slim) | **Very limited.** Some features may not work or may be **broken entirely.** Treat Sherwood support as experimental. |

## Download & run

Builds are distributed as archives outside this repository (this repo does not
host binaries). Windows and Linux (x64) builds are provided.

### Windows

1. You **MUST** extract Kohada to a dedicated directory. Kohada requires the Qt libraries provided to function properly and will **NOT** not run from a archive utility such as 7Zip. 
2. Run `kohada.exe` and accept the disclaimer.

### Linux (x64)

1. The same premise applies as the Windows build. Extract the archive to a dedicated folder, then make the binary executable: `chmod +x kohada`.
2. Run it: `./kohada`.
3. **Serial access:** to talk to the syscon over USB you need read/write on the serial device (e.g. `/dev/ttyUSB0`). Add yourself to the `dialout` group once: `sudo usermod -aG dialout $USER`, then log out and back in.

## Safety: dump first, always

The golden rule. Before touching any value:

1. Dump your EEPROM (**EEPROM Dump** tab).
2. Save the `.scdump` somewhere safe, on more than one device.
3. Only then make changes.

That dump is your only way back if a write goes wrong.

> Note: **Full Restore rewrites main NVS only.** The secondary 0x48xxx pages
> (including the QA token) are archived in your backup for reference but are
> **not** written back during a restore.

## Contributing error definitions

Kohada is **not open source**, but the error-code database ([`src/core/error_codes.h`](src/core/error_codes.h)) **is** published here so the community can improve it. If you've decoded a syscon error the tool doesn't recognise, or have better repair context for an existing one, contributions to that file are welcome via pull request.

This is the only source file in the repository, the rest of the application is closed source.

## Disclaimer

This software is provided "as is", without warranty of any kind. You assume all risk for any damage to your hardware or data. Not affiliated with or endorsed by Sony Interactive Entertainment.