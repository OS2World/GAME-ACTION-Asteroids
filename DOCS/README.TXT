Beta testers:

ASTEROID 2.3 includes the following fixes:
	+ Player's ship is properly erased when it is turning but not
	  moving and explodes.
	+ Hitting 1 or 2 during a game no longer starts a new game
	  (with the old score).
	+ The small enemy ship only fired at the player's ship 25% of
	  the time.  This was due to a bug in my calculations.  The small
	  enemy ship now always fires in the direction of the player's
	  ship.
	+ Options and screen information were not saved if you used the
	  exit button in the "Copyright" dialog.
	+ Under OS/2 2.0, ASTEROID 2.21 did not restore to the saved size
	  and position the last time it was played.
	- One bug reported but not fixed was that the acceleration table
	  keys did not work when ASTEROID was maximized.  I have not been
	  able to reproduce this problem.  Is it really a problem (still)?

ASTEROID 2.3 include the following new features:
	* 32-bit (there doesn't appear to be any speed improvement, however)
	* Mouse ship control
	  - Please tell me what you think of this.  The way I do this is
	    by comparing the position of the pointer at each timer tick
	    to the position at the previous timer tick; if the controls
	    seem too touchy let me know.  I've thought of allowing the user
	    to configure sensitivity, but I'm using the finest granularity
	    available now and even the smallest change makes the mouse very
	    sluggish).
	  - The pointer is hidden when mouse control is enabled during a
	    game.
	* Enhanced internal algorithms:
	  - In the arcade game Asteroids the "child" asteroids inherit part
	    of their parent's direction.  In ASTEROID 2.2 the direction
	    of the child asteroids was random; their direction is now based
	    on their parent's direction.
	  - In ASTEROID 2.2 child asteroids directly inherited their initial
	    position from their parent (since the "position" of an asteroid is
	    at the center, the childrens' initial position was always at the
	    dead center of their parent).  Their initial position is now
	    randomly adjusted to be somewhere within the area occupied by the
	    parent (i.e. the two children asteroid will most likely start at
	    different positions).  This limits the destructive effect of firing
	    a volley of photons at the center of an asteroid.
	  - The maximum possible speed of an asteroid increases progressively
	    at higher levels.  Previously the maximum speed was fixed for
	    all levels.
	  - In ASTEROID 2.2 hyperspacing set the shield/hyperspace energy
	    level to zero.  This meant hyperspacing twice in quick succession
	    was relatively dangerous.  To give an advantage to games where the
	    shield is not enabled, if the the shield option is off hyperspacing
	    does not reset the energy level to zero (in this case there is
	    always 1 in 8 chance of exploding on reentry even if the player
	    hyperspaces two or more times in a row).
	  - The shield now regenerates progressively slower at higher levels.

Thanks, for volunteering for the ASTEROID 2.3 beta.  It'll be tough, I'm
sure, but worth the effort.  :-)

- Todd
