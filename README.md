Game-Asteroid
==============

Asteroids game clone for OS/2. Black &amp; White and linear shapes.

![Asteroids ScreenShot](/doc/Asteroids.png)

LICENSE
========
GNU GPL V2


BUILD (Open Watcom 1.9, OS/2)
=============================
Set `WATCOM` in `compile.cmd` to the Open Watcom installation, then:

    compile.cmd            ; or: compile.cmd [clean|app|fontdll|help]

This runs `wmake -h` on `makefile.wat` and produces, under `bin-wat\`:

    ASTEROID.EXE   PM application (ASTEROID.RC bound at link time)
    ASTEROID.DLL   16-bit font module for GpiLoadFonts(hab, "ASTEROID")
    ASTEROID.HLP   IPF help (from help\ASTEROID.IPF)

Source layout: `src\` holds the main app, `src\font\` the font module
(ASM stub + DEF + FAT fonts), `help\` the IPF sources, `doc\` the
original docs, `legacy\` the untouched original tree.

RELEASE 2.40
============
Changes in the OS/2 port release 2.40 (see `doc\Changelog.TXT`):
- No startup popup; the game opens directly into the game window.
- The "@1993 TODD CROWE" line is gone from the game window.
- The window always starts at a 1024x768 client, centered on screen.
- The title bar reads "ASTEROID" (no version).
- Help - About reports version 2.40.
- Clean compile with no warnings under Open Watcom (wcc386 -w4 and
  wipfc both warning-free).
- The executable carries a BLDLEVEL 2.40 signature; on OS/2,
  `bldlevel bin-wat\ASTEROID.EXE` reports vendor "ASTEROID" revision
  2.40 (embedded as an RCDATA resource in src\ASTEROID.RC, resource
  ID_BLDLEVEL = 900 in src\PMDEFS.H).
- New Options - Language menu switches the interface among English,
  Deutsch, Espanol, Nederlands and Francais; the choice persists
  between sessions.  All text is accent-free ASCII (the game draws
  with its own bitmap fonts).  Language tables live in src\LANG.H;
  the current language is stored in the OS/2 INI under the
  application name, key "Language".
- Fixed the Options menu layout: the "Fire Rate" submenu was declared
  with Borland-style "-1, MIA_DISABLED" arguments that Open Watcom
  compiles into a hidden column-break separator, which pushed Shield,
  Mouse, Keys and Language into a second column.  The declaration is
  now plain "SUBMENU \"~Fire Rate\", IDM_FIRERATE" and the item is
  disabled at startup in code when rapid fire is not selected.

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
`wrc -bt=os2 [..] src\font\ASTEROID.RES bin-wat\ASTEROID.DLL`.


AUTHORS
=============
- Todd B. Crowe
- Martin Iturbide (2026)

LINKS
=============
- https://github.com/OS2World/GAME-ACTION-Asteroids
