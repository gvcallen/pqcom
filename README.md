# PocketQube Satellite Communication System

## Overview
This repository holds code, datasheets, PCB schematics and other files related to the design and development of a PocketQube Satellite Communication System. This was done by Gary Allen in  partial fulfilment of the requirements of the module Project (E) 448 for the degree Baccalaureus in Engineering in the Department of Electrical and Electronic Engineering at the University of Stellenbosch, South Africa. PocketQubes are miniaturised satellites, and this project aimed to develop prototypes for the unit to be placed on the satellite, the ground station, and the PC interface.

## Code
This folder contains the relevant code for the project. Inside are 5 sub-folders. All embedded development was done using the *PlatformIO* extension on VS code, and all desktop GUI development was done using the *Qt* C++ library, both under WSL (Windows Subsystem for Linux). I highly recommend a linux install due to the ease of installation of the Qt libraries.
- ***gel*** is another Github repository created by myself containing the core embedded C++ classes used by the other projects. Even though it was developed solely for this project, I decided to make it an independent library so that it can be self-standing and potentially be used outside of the PocketQube project in the future.
- ***pqcu*** is the folder housing the code for the *PocketQube Communication Unit* i.e. the module to be placed on the PQ itself. It is very simple since it only "spits out" its GPS location via LoRa (i.e only downlink communication was implemented) however "gel" theoretically has an almost-ready foundation for dual-link communication (which was not implemented due to time constraints).
- ***pqgs*** contains code for the *PocketQube Ground Station*. This includes communication with the PQ unit, motor drive control, GPS tracking and serial control via a "TNC" (a.k.a a laptop connected via USB).
- ***pqui*** contains desktop GUI code to control the GS via USB and a PC. Theoretically, all control can be done via the terminal, however the GUI was implemented to make things slightly easier. It implements the SUNCQ protocol under ***Documents***.
- ***radiosonde_auto_rx*** was an extension of the project to receive data from a commercial Radiosonde via a software-defined radio (SDR). This is used by ***pqui***. Although the Radiosonde receiving is functional, it is currently implemented is a bit "messy", since a Python script is called and controlled from Qt, and this causes issues from time-to-time. If only "custom" communication is needed, this can be ignored.

## Other
The rest of the contents are relatively self-explanatory:
- ***datasheets*** contains various used (and not used) datasheets for ICs and modules.
- ***documents*** contains the SUNCQ protocol for PC to GS communication.
- ***images*** contains images taken throughout the project, such as during testing and final deployment.
- ***kicad*** contains the schematics developed for the PQ and the GS. The final Gerber files are also present in zip format. Note that some folders in here are old and need to be cleaned up.
- ***link-budget*** contains a pre-liminary link-budget done with free Python software.
- ***report*** contains the final report files for Latex. The final PDF is in the root of this folder.
- ***testing*** contains test results and data.