<img src="Screenshots/ModelRenderScreenshot.PNG" alt="Screenshot of render"/>

# HolyGL (Previously Gr2)
A divinely inspired realtime graphics library for the TempleOS distro [ZenithOS](https://github.com/ZenithOS/ZenithOS).
It aims to stay true to Terry's objectives by being simple, easy to understand, and transparent.

# Features in Development
* SSE/AVX accelerated math library.
* Multicore rendering.
* New software renderering pipeline for real time games.

# Features Implemented
* Half-Life WAD texture loading.
* BMP texture loading.
* Draw library for 2D primitives.
* Software rasterizer with custom shader support.
    * currently being rewritten, you can use an older commit if you would like to experiment with this (the new renderer will have the same user interface).

# Installation
This library can be compiled by your project or by the operating system on boot. Compiling the
library at boot is useful because it provides syntax highlighting for the library.

The library can be compiled by including `MakeHolyGL.CC`, found in the root of the library. To compile on boot, append `#include "Path/To/MakeHolyGL"` to the end of `Zenith/MakeZenith.CC` If you are a developer though, it is recommended that you comment out #includes in the makefile for math files
that use assembly, as the OS will not let you compile an assembly "function" if it was already compiled
earlier.

# Documentation
This library uses more verbose function/class documentation than standard TempleOS function comments. The autogenerated HTML Doxygen documentation is in `docs/`, and viewable [here](https://templeprogramming.github.io/HolyGL/).

DolDoc documentation with sprite diagrams is available in `HolyGL/Docs`.