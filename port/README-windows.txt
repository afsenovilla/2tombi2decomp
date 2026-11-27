Tomba! 2: The Evil Swine Return - PC port, Windows build (experimental)
======================================================================

This is a fan-made native port built from the 2tombi2decomp decompilation project. It contains NO game data:
it runs YOUR OWN copy of the game, read straight from a disc image you made of your own disc.

What you need
-------------
- Windows 10 or 11, 64-bit (the game is a 32-bit program that needs the 4 GB address space a 64-bit Windows
  gives it; a 32-bit Windows cannot map the PlayStation memory where the game expects it).
- A disc image of Tomba! 2: The Evil Swine Return, USA version (SCUS-94454):
  a raw .bin (with or without its .cue), an .img, or an .iso. A raw .bin/.cue is best: an .iso has no
  music or voices (the XA audio is not in a 2048-byte image). The European / Spanish "Tombi! 2" discs are
  not supported yet: the port says so if you pick one.
- If the image is in a .zip / .7z, unpack it first.

Starting the game
-----------------
1. Unzip this whole folder anywhere you can write to (Desktop, Documents, a games folder).
2. Double-click tomba2-launcher.exe.
3. The first time it asks for your disc image: pick the .cue, .bin, .img or .iso file. It remembers it.
   To pick another image later, hold Shift while you double-click tomba2-launcher.exe.

The game window opens; closing it (or Escape) quits. Your memory cards are saved in the "saves" folder next
to the launcher (tomba2_mc0.mcd, tomba2_mc1.mcd: the usual 128 KB card format of PlayStation emulators).
The launcher's settings are in tomba2-launcher.ini and the game's log in tomba2.log, in the same folder
(or in %APPDATA%\Tomba2-port if the folder is not writable). If something goes wrong, the launcher shows
the error and tomba2.log has the details.

Windows SmartScreen may warn about an unknown program the first time ("More info" -> "Run anyway"): the
executables are not signed.

Controls
--------
Keyboard              PlayStation
  Arrow keys          D-pad
  X                   Cross
  Z                   Square
  S                   Triangle
  D                   Circle
  Q / W               L1 / R1
  A / E               L2 / R2
  Return              Start
  Backspace           Select
  F                   window size (2x / 3x)
  F11                 fullscreen on / off
  F12                 screenshot (tomba2_shot_000.bmp, ... next to the launcher)
  Escape              quit

A game controller (Xbox / XInput and most others) works too: d-pad or left stick, A = Cross, B = Circle,
X = Square, Y = Triangle, LB / RB = L1 / R1, LT / RT = L2 / R2, Start, Back = Select.

Options (advanced)
------------------
Edit the options= line of tomba2-launcher.ini, for example:
  options=--fullscreen
  options=--renderer software      (if the picture looks wrong: also direct3d, direct3d11, opengl)
  options=--linear                 (smooth scaling instead of sharp pixels)
  options=--viewer-arg --scale --viewer-arg 3
  options=--viewer-arg --keys --viewer-arg cross=Space,circle=LShift
(--keys takes SDL key names for up, down, left, right, cross, square, triangle, circle, l1, r1, l2, r2,
start, select.) tomba2.exe can also be run from a command prompt: tomba2.exe --disc "D:\Games\Tomba2.cue"
--window (tomba2.exe --help lists the options).

What works, what does not (yet)
-------------------------------
Works: the title screen, the attract demos, New Game into the first area (A00) and free play there, music,
voices and sound effects, saving and loading on the memory cards. Most of the game's code is native, the
rest runs in a built-in interpreter of the original code. The intro and ending movies are skipped. Later areas are not tested much
yet: if the game stops, the launcher shows the error; please report it with tomba2.log.

Report a problem
----------------
Please send:
- tomba2.log (next to the launcher, or in %APPDATA%\Tomba2-port): it names your Windows graphics driver
  (the "tomba2-view:" lines), the disc image and where the game was; if the sound stutters, its
  "audio underrun" / "XA queue ran dry" lines say when and why;
- screenshots of what looks wrong: F12 in the game window (tomba2_shot_NNN.bmp next to the launcher),
  or Print Screen / Win+Shift+S;
- what you did just before (area, menu, how long you played), and your saves folder if it is about saving.

Credits and licences
--------------------
The port's code comes from the 2tombi2decomp project and its sister project for the first game
(Tombi-Decomp), MIT licence. SDL2 (SDL2.dll, the window, sound and controllers) is (c) Sam Lantinga,
zlib licence (see LICENSE-SDL2.txt). Tomba! 2 is (c) Whoopee Camp / Sony Computer Entertainment; this port
contains none of its data.
