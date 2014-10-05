.*
.* ASTEROID.IPP
.*
.* IPF tag file for ASTEROID 2.30.
.*
.* Copyright (C) 1992-1993 Todd Crowe,  All Rights Reserved
.*
.*
#define  IPFC
.*
.*
:userdoc.
:title.Help for ASTEROID
:body.
.*
.*
:h1 res=3.Help for Keys
:i1 id=Keys.Keys
:p.ASTEROID allows the user to select which keys control the
ship.  To change the default keys select the "Keys..." menu item
in the "Options" menu.
:p.The game play functions have the following default key definitions:
:dl tsize=5 break=all.
:dt.<Left Arrow>
:dd.Rotate Left
:dt.<Right Arrow>
:dd.Rotate Right
:dt.<Up Arrow>
:dd.Thrust
:dt.<Down Arrow>
:dd.Hyperspace
:dt.<Space>
:dd.Fire
:dt.s
:dd.Shield
:edl.
:p.The following keys may not be redefined:
:dl tsize=5 break=all.
:dt.F1
:dd.Help
:dt.1
:dd.Select 1 Player Game
:dt.2
:dd.Select 2 Player Game
:dt.<CTRL> + f
:dd.Hide Frame Controls
:dt.<CTRL> + k
:dd.Redefine Keys
:dt.<CTRL> + p
:dd.Pause Game
:dt.F3 or <CTRL> + x
:dd.Exit Game
:edl.
:p.When the :hp2.Mouse:ehp2. option is off, the game is paused, or ASTEROID
is in attract mode, the mouse has the following functions:
:dl tsize=5 break=all.
:dt.Double Click Left Button
:dd.Hide/Show Frame Controls
:dt.Double Click Right Button
:dd.Pop up About dialog box
:dt.Left Button + Drag
:dd.Move screen without title bar
:edl.
:p.During game play when the :hp2.Mouse:ehp2. option is on, the mouse has
the following functions:
:dl tsize=5 break=all.
:dt.Left
:dd.Rotate left
:dt.Right
:dd.Rotate right
:dt.Up
:dd.Thrust
:dt.Left Button
:dd.Fire Photon
:dt.Click Right Button
:dd.Hyperspace
:dt.Click and Hold Right Button
:dd.Engage shield
:edl.
.*
.*
:h1 res=100.Help for Game Control
:i1 id=Game.Game control
:p.The :hp2.Game:ehp2. menu allows you to start a new game or affect a game
in progress.
:dl tsize=5 break=all.
:dt.:hp2.New:ehp2.
:dd.Starts a new 1 or 2 player game.
:dt.:hp2.Frame Controls:ehp2.
:dd.Hides/shows the frame controls (titlebar, menu, etc.).
:dt.:hp2.Background:ehp2.
:dd.Allows ASTEROID to run in the background and when iconized.
:dt.:hp2.Pause:ehp2.
:dd.Suspends all screen action until unpaused.
:dt.:hp2.Stop:ehp2.
:dd.Stops the game in process and returns ASTEROID to attract mode.
:dt.:hp2.Exit:ehp2.
:dd.Exits ASTEROID.
:edl.
.*
.*
:h2 res=110.Help for New Game
:i2 refid=Game.Start New Game
:dl tsize=5 break=all.
:dt.:hp2.1 Player Game:ehp2.
:dd.Starts a new one player game.
:dt.:hp2.2 Player Game:ehp2.
:dd.Starts a new two player game.
:edl.
:p.In two player games players alternate turns after each ship.
:p.If a game is already in progress, :hp2.New:ehp2. will be disabled.
.*
.*
:h2 res=120.Help for Frame Controls
:i2 refid=Game.Toggle Frame Controls
:p.If the frame controls are visible, selecting :hp2.Frame Controls:ehp2.
will make them invisible; if the frame controls are already hidden it will
make them visible.
:p.The frame controls are the system menu, the title bar, the minimize and
maximize buttons, and the application menu.
.*
.*
:h2 res=121.Help for Background
:i2 refid=Game.Background
:p.When enabled, screen action will continue unless explicitly paused.
:p.Normally game play is automatically paused when ASTEROID is iconized,
when it is not the foreground process, or when the user is accessing the
menus or a dialog box.
:p.The :hp2.Background:ehp2. option allows ASTEROID to be used as a backdrop
and to be played in iconic form.
.*
.*
:h2 res=122.Help for Pause
:i2 refid=Game.Pause Game
:p.:hp2.Pause:ehp2. pauses (or unpauses) ASTEROID.  If a game is in progress
all action will be stopped until the game is unpaused.
:p.ASTEROID may also be paused by pressing <CTRL> + p.
:p.You may unpause a game by selecting :hp2.Pause:ehp2., or by pressing
<CTRL> + p.
.*
.*
:h2 res=123.Help for Stop Game
:i2 refid=Game.Stop Game
:p.If a game is in progress :hp2.Stop:ehp2. will terminate it.
:p.If a game is not in progress, :hp2.Stop:ehp2. will be disabled.
.*
.*
:h2 res=124.Help for Exit
:i2 refid=Game.Exit
:p.Select :hp2.Exit:ehp2. or press F3 to exit ASTEROID.
.*
.*
:h1 res=200.Help for Options
:i1 id=Options.Options
:p.The :hp2.Options:ehp2.menu allows you to adjust game play parameters
and options.
:dl tsize=5 break=all.
:dt.:hp2.Ships:ehp2.
:dd.Sets the number of ships you start each game with.
:dt.:hp2.Photons:ehp2.
:dd.Sets the number of photons avaible.
:dt.:hp2.Rapid Fire:ehp2.
:dd.Enable or disables rapid fire.
:dt.:hp2.Fire Rate:ehp2.
:dd.Sets the rapid fire rate.
:dt.:hp2.Shield:ehp2.
:dd.Enables or disables the shield.
:dt.:hp2.Mouse:ehp2.
:dd.Enables or disables the use of the mouse for controlling the ship.
:dt.:hp2.Keys:ehp2.
:dd.Lets you redefine the ship control keys.
:edl.
.*
.*
:h2 res=210.Help for Ships
:i2 refid=Options.Ships
:p.The :hp2.Ships:ehp2. submenu allows you to select the number of ships
each player initially receives.
:p.(It may be set to :hp2.3:ehp2., :hp2.4:ehp2., or :hp2.5:ehp2., the default
is :hp2.3:ehp2.)
.*
.*
:h2 res=220.Help for Photons
:i2 refid=Options.Photons
:p.The :hp2.Photons:ehp2. submenu allows you to select the maximum number
of photons available at any one time.
:p.(It may be set to to :hp2.3:ehp2., :hp2.4:ehp2., :hp2.6:ehp2., or
:hp2.8:ehp2., the default is :hp2.4:ehp2.)
.*
.*
:h2 res=230.Help for Rapid Fire
:i2 refid=Options.Rapid Fire
:p.The :hp2.Rapid Fire:ehp2. option allows you to enable or disable the rapid
fire feature.
:p.When enabled, rapid fire lets you fire multiple photons by
simply holding down the :hp2.Fire:ehp2. key.
:p.(By default, rapid fire is enabled)
.*
.*
:h2 res=240.Help for Fire Rate
:i2 refid=Options.Fire Rate
:p.The :hp2.Fire Rate:ehp2. submenu allows you to set the rate of rapid fire.
:p.:hp2.Fire Rate:ehp2. is disabled unless :hp2.Rapid Fire:ehp2. is enabled.
:p.(The default rapid fire rate is :hp2.Slow:ehp2.)
.*
.*
:h2 res=260.Help for Mouse
:i2 refid=Options.Mouse
:p.The :hp2.Mouse:ehp2. allows you to use a mouse or other pointing device
to control the ship.
:p.When :hp2.Mouse:ehp2. is enabled the mouse has the following functions:
:dl tsize=5 break=all.
:dt.Left
:dd.Rotate left
:dt.Right
:dd.Rotate right
:dt.Up
:dd.Thrust
:dt.Left Button
:dd.Fire Photon
:dt.Click Right Button
:dd.Hyperspace
:dt.Click and Hold Right Button
:dd.Engage shield
:edl.
.*
.*
:h2 res=270.Help for Keys
:i2 refid=Options.Redefine Keys
:p.:hp2.Keys...:ehp2. pops up the Key Definition dialog box which allows you
to redefine which keys control the ship.
:p.You need a mouse or some other pointing device to select different
fields.  If you do not have a mouse you will not be able to redefine the keys.
:p.You may press F3 to cancel any changes and exit the :hp2.Keys...:ehp2.
dialog box.
.*
.*
:h1 res=300.Help for Help
:i1 id=Help.Help
:p.Get help on how to use help, get extended help, look at the help index,
or to look at copyright information.
:dl tsize=5 break=all.
:dt.:hp2.Help for help:ehp2.
:dd.Provides detailed information on the kinds of help available and how
to use help.
:dt.:hp2.Extended help:ehp2.
:dd.Displays general help.
:dt.:hp2.Keys help:ehp2.
:dd.Displays a list of keys.
:dt.:hp2.Help index:ehp2.
:dd.Displays the help index.
:dt.:hp2.About:ehp2.
:dd.Displays copyright information.
:edl.
.*
.*
:h2 res=310.Help for Help
:i2 refid=Help.Help for Help
:p.:hp2.Help for Help:ehp2. shows what kind of help is available and how to
use the available help.
:p.In general, help is provided for every menu, command, and other selections.
:p.To get detailed information on help, click on :hp2.Help for help...:ehp2., or
select it and press <Enter>.
.*
.*
:h2 res=311.Extended Help
:i2 refid=Help.Extended help
:p.:hp2.Extended Help:ehp2. provides general information about ASTEROID
:p.To get extended help, click on :hp2.Extended help...:ehp2.
.*
.*
:h2 res=312.Help Keys
:p.Display a list of keys and mouse functions.
:p.To display the list of keys, click on :hp2.Keys help...:ehp2.
.*
.*
:h2 res=313.Help for Help index
:i2 refid=Help.Help index
:p.Display the help index.
:p.The help index lists titles for all available help by subject.
:p.To display the help index, click on :hp2.Help index...:ehp2..
.*
.*
:h2 res=320.Help for About
:i2 refid=Help.About
:p.Display copyright information.
:p.To display the copyright information, click on :hp2.About:ehp2 or
double-click the right mouse button.
.*
.*
:h1 res=2.Help for ASTEROID
:i1 id=ASTERIOD.ASTEROID
:p.ASTEROID is an OS/2 Presentation Manager implementation of the 1979
arcade game Asteroids(tm) by Atari.
:p.Additional information about ASTEROID is available on the following
subjects:
:ul compact.
:li.:link reftype=hd refid=installation.Installation:elink.
:li.:link reftype=hd refid=features.Features:elink.
:li.:link reftype=hd refid=scoring.Scoring:elink.
:li.:link reftype=hd refid=history.A Brief History of ASTEROID:elink.
:li.:link reftype=hd refid=notes.Important Notes:elink.
:eul.
:p.ASTEROID is copyright (c) 1990-1993 by Todd B. Crowe.  You may copy
ASTEROID freely.  There is no warranty implied or otherwise.  You may not
modify any of the code or any of the accompanying files without my
permission.  ASTEROID may not be sold or distributed commercially or
otherwise for profit.  I reserve all rights and privileges to ASTEROID.
.*
.*
:h1 id=installation hide.Installing ASTEROID
:p.
:hp2.
.ce Installation
:ehp2.
:p.To run ASTEROID from a full screen prompt simply type:
.br
.ce ASTEROID
:p.No parameters are required.
:p.The file ASTEROID.HLP (this file) should be in the ASTEROID working
directory or in a directory pointed to by the HELP environment variable.
ASTEROID.HLP contains all of the help information for ASTEROID.
:p.The file ASTEROID.DLL must be in a directory in your LIBPATH
(e.g. C&colon.\OS2\DLL); if it is not ASTEROID.EXE will display an
error message box and then terminate.  ASTEROID.DLL contains the
two custom fonts used by ASTEROID.EXE.
:p.On slower machines asteroid movement may look very jumpy. In
fact, everything moves at the same rate on a slow computer as a fast
computer. On a slow computer the asteroids are just redrawn less often.
.*
.*
:h1 id=features hide.Features
:p.
:hp2.
.ce Features
:ehp2.
:p.ASTEROID resembles very closely the arcade game Asteroids.  It
supports the player attraction modes, the high score entry
screen, a high score table, a custom font, and 2 player mode.
Enemy space ships appear on the screen and fire directly at the
player's ship.  The player may hyperspace, but, as in the arcade
game, the player's ship randomly blows up on reentry.
:p.Beginning in ASTEROID 2.0 high scores, window size and position
information, and frame control status were saved in a profile.
ASTEROID 2.1 added a system menu, a help screen, and the ability
to customize the number of ships per game, the number photons
that may be fired simultaneously, the use of the shield, and
the keys for controlling the ship.  ASTEROID 2.3 adds mouse input
for ship control.
:p.In version 2.1 a new game play feature was added to ASTEROID.
The player's ships may be equipped with a shield.  The shield protects a
ship from asteroids, the enemy ships, and photons.  It does, however,
have a drawback.  The shield operates off of the hyperspace
drive, which has a limited energy reserve.  When the shield is on
it draws energy from the hyperspace drive energy reserve.
Eventually, the reserve supply will become exhausted and the
shield will power down.  When the hyperspace energy reserve is
low hyperspacing is more dangerous.  If the shield is left off,
the hyperspace drive will slowly recharge the energy reserve.
:p.Finally, this wonderful online help was added with ASTEROID 2.2.
.*
.*
:h1 id=scoring hide.Scoring
:p.
:hp2.
.ce Scoring
:ehp2.
:p.Scoring is the same as in the original arcade game:
:sl compact.
:li.Large Asteroids = 20 points
:li.Medium Asteroids = 40 points
:li.Small Asteroids = 100 points
:li.Large Enemy Spaceships = 200 points
:li.Small Enemy Spaceships = 1000 points
:esl.
:p.A free ship is awarded at 10,000 points and every 10,000 points thereafter.
.*
.*
:h1 id=history hide.A Brief History of ASTEROID
:p.
:hp2.
.ce A Brief History of ASTEROID
:ehp2.
:sl compact.
:li.:hp5.ASTEROID 1.0 - June 1990:ehp5.
:li. Basic Asteroids game
:li. Limited customization
:li. Variable speed settings
:li. Simple scalable screen display
:li. Integer math for speed
:esl.
:sl compact.
:li.:hp5.ASTEROID 2.0 Changes - September 1990:ehp5.
:li. New custom fonts
:li. Asteroids-like screen display
:li. Automatic play speed selection
:li. 1/2 Player games
:li. High score table
:li. Use of profile to save information
:li. Complete rewrite of code
:esl.
:sl compact.
:li.:hp5.ASTEROID 2.1 Changes - May 1991:ehp5.
:li. Minor bug fixes from 2.0
:li. Menu bar, key definition, help screen
:li. Customize options
:li. Shield option
:esl.
:sl compact.
:li.:hp5.ASTEROID 2.2 Changes - June 1991:ehp5.
:li. Minor bug fixes from 2.1
:li. Rapid fire
:li. Improved keyboard input
:li. On-line help
:esl.
:sl compact.
:li.:hp5.ASTEROID 2.3 Changes - January 1993:ehp5.
:li. Minor bug fixes from 2.2
:li. Enhanced internal algorithms to improve playability
:li. Mouse ship control
:li. OS/2 2.0 version (32-bit)
:esl.
.*
.*
:h1 id=notes hide.Important Notes
:p.:hp2.
.ce Important Notes
:ehp2.
:p.
As with previous versions, ASTEROID v2.30 is released as free software.
I ask for no payments.  If you enjoy ASTEROID, however, I would appreciate
hearing from you.  Comments and suggests are welcome.
:p.
To contact me write or email: 
:sl compact.
:li.:lm margin=5.Todd Crowe
:li.:lm margin=5.3318 - 75th Court East
:li.:lm margin=5.Inver Grove Heights, MN 55076
:li.:lm margin=5.Internet Address: toddc@cray.com
:esl.
:p.
Finally, I would like to thank those who have helped me with ASTEROID
in the past.  Many thanks go to Larry Saloman, Harald Boegeholz, Sean
Purcell, Timur Tabi, and especially to Bert Moshier.
.*
.*
:index.
:euserdoc.
