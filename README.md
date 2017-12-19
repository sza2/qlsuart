# qlsuart
Lists available serial ports (UARTs)

The basic function of this simple tool is to search for serial port and list them. Additionally, there are configurable command lines to set up multiple terminal programs to execute:

- No modifiers + double click
- CTRL + double click
- SHIFT + double click

It can replace the following strings with the actual port related values:

- {devicename} replaced by device name ex.: COM10 (Windows) or ttyS10 (Linux)
- {devicelocation} replaced by device location ex.: \\.\COM10 or /dev/ttyS10
- {devicenumber} replaced by device number ex.: 10 - makes sense only for teraterm, this was introduced due to teraterm's unlogical command line parameter (/C=10 instead of /C=COM10)

Command line examples:

- xterm -e minicom -D {devicelocation}
- "c:\Program Files (x86)\teraterm\ttermpro.exe" /BAUDRATE=115200 /C={devicenumber}
