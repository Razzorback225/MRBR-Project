# The Model Railroad Bluetooth Router Project

## Why this project?
I recently started this project in order to control my old Marklin Model Railroad (M tracks) or, at least, some parts of it (such as the switch tracks, some parts of the diorama, crossing, etc).

This project is inspired of the URB project (https://arduinorailwaycontrol.com/) that I will not explain here, go check the website this project is super cool.

I wanted to create a similar concept that Mr Massiker (Founder of URB) did but with my point of view and that's what I did.

## What's the MRBR?
For now, it is nothing else than an idea (and some schematics, PCB files and a bit of Arduino code).

The idea is to have an ESP32 that will communicate Wirelessly or Wiredly (I'm not sure these words exist in English) with a control device (Smartphone, PC, ...).

This control peripheral (CP) will send command to the ESP32 that will do several thing with it.

### 1. Check the Network ID (NID) included in the header of the command
This NID is just an hex value.

### 2. If the NID from the command doesn't match its NID, the MRBR search in its routing table to matching routeur for this NID
The MRBR work mostely like a LAN Network but with the I2C and UART protocols. Every router of the project (MRBR or MRSR) have their own I2C "Network". The MRBR and the MRSR communicate via UART together.

### 3. The command is forwarded to the right router that will deliver the command to the Peripheral Controler (PCtrl) matching the I2C address (SID) included in the header.
The MRBR command frame is illustrated in the next picture.

![Typical MRBR I2C frame](MRBR_frame.png)
