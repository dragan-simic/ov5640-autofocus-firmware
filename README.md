# OV5640 Autofocus Firmware

This repository contains some C code that converts publicly available variants of the OV5640 autofocus firmware to the .bin files expected by the Linux kernel.

Already converted .bin files, together with the accompanying .regs files, if any, can be found in the "bin" directory.  The .regs files contain additional register values that were found in the publicly available variants of the OV5640 autofocus firmware.  Those register values should also be configured as part of the firmware loading.

Each .h file that contains an original variant of the OV5640 autofocus firmware is annotated with the source URL.
