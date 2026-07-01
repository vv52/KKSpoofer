# KKSpoofer
## A pico-based Konami Keyboard spoofer

This project is intended to facilitate use of any USB keyboard with Beatmania Da Da Da on PlayStaion 2 hardware by spoofing HID information.

Beatmania Da Da Da is much stricter with its keyboard check than most PS2 games that look for any keyboard. BDDD checks PID, VID, and vendor strings. The pico bitbangs the events from the keyboard input to the keyboard output, so latency should be as minimal as is possible.
