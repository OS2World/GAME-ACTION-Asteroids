Game-Asteroid
==============

Asteroids game clone for OS/2. Black &amp; White and linear shapes.

![Asteroids ScreenShot](/doc/Asteroids.png)

LICENSE
========
GNU GPL V2


BUILD (Open Watcom 1.9, OS/2)
=============================
Open Watcom is auto-detected (C:\WATCOM or D:\WATCOM). Run:

    compile.cmd

This runs `wmake` on `makefile.wat` and produces, under `bin\`:

    ASTEROID.EXE   PM application (ASTEROID.RC bound at link time)
    ASTEROID.DLL   16-bit font module for GpiLoadFonts(hab, "ASTEROID")
    ASTEROID.HLP   IPF help (from help\ASTEROID.IPF)

Source layout: `src\` holds the main app, `src\font\` the font module
(ASM stub + DEF + FAT fonts), `help\` the IPF sources, `doc\` the
original docs, `legacy\` the untouched original tree.

RELEASE 2.41
============
Changes in the OS/2 port release 2.41 (see `doc\Changelog.TXT`):
- Italian (Italiano) added to the Language menu; now six languages:
  English, Deutsch, Espanol, Nederlands, Francais, Italiano.
- Stack size raised from 12288 to 65536 bytes.
- Build flags: -bm removed, optimised release flags (-Oaxt -d0).
- compile.cmd auto-detects WATCOM, logs to compile-wat.log, exits
  non-zero on failure.
- Output directory is now `bin\` (was `bin-wat\`).
- BLDLEVEL updated to 2.41.

RELEASE 2.40
============
Changes in the OS/2 port release 2.40 (see `doc\Changelog.TXT`):
- No startup popup; the game opens directly into the game window.
- The "@1993 TODD CROWE" line is gone from the game window.
- The window always starts at a 1024x768 client, centered on screen.
- The title bar reads "ASTEROID" (no version).
- Help - About reports version 2.41.
- Clean compile with no warnings under Open Watcom (wcc386 -w4 and
  wipfc both warning-free).
- The executable carries a BLDLEVEL signature (RCDATA resource,
  ID_BLDLEVEL = 900 in src\PMDEFS.H).
- Options - Language menu switches the interface among six languages;
  the choice persists between sessions.  All text is accent-free
  ASCII.  Language tables live in src\LANG.H; the current language
  is stored in the OS/2 INI under the application name, key
  "Language".
- Fixed the Options menu layout (Fire Rate submenu column-break).

FONT MODULE
===========
GpiLoadFonts() in ASTEROID.C looks up the module's private fonts.  The
DLL must carry a FONTDIRECTORY (resource type 6, name 1) plus one
resource per face whose NAME equals the FONTDIR index.  The faces are
stored as type 1000, names 100 (small.fnt) and 200 (large.fnt).

Open Watcom's wrc cannot compile these from RC `FONT` statements (it
writes a Windows FontInfo header into the payload and rejects .fnt
input), so the binary resource file is generated instead:

    python fontdll_res.py src\font\SMALL.FNT src\font\LARGE.FNT src\font\ASTEROID.RES

    (fontdll_res.py lives in the claude-os2-toolkit workspace; the
     checked-in src\font\ASTEROID.RES is up to date.)

`makefile.wat` then binds that .RES into `ASTEROID.DLL` with
`wrc -bt=os2 [..] src\font\ASTEROID.RES bin\ASTEROID.DLL`.


AUTHORS
=============
- Todd B. Crowe
- Martin Iturbide (2026)

LINKS
=============
- https://github.com/OS2World/GAME-ACTION-Asteroids
