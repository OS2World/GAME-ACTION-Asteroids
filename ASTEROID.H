/****************************************************************************
 * ASTEROID.H								    *
 *									    *
 *  Primary include file containing the universal #define's, #include's,    *
 *  and data declaration.						    *
 *									    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
 *									    *
 *  -- ASTEROID is an OS/2 v2.0 Presentation Manager implementation of the  *
 *  -- Atari coin-op arcade game Asteroids.				    *
 *									    *
 * ASTEROID is copyright (c) 1991-1993 by Todd B. Crowe.  There is no       *
 * warrantee implied or otherwise.  You may copy the program freely but it  *
 * must be accompanied by this notice.	The program may not be sold or      *
 * distributed commercially or otherwise for profit.  I reserve all rights  *
 * and privileges to this program.					    *
 *									    *
 ****************************************************************************/

/* Include files, assoc. #defines */
#define INCL_GPILCIDS
#define INCL_GPIBITMAPS
#define INCL_GPIPRIMITIVES
#define INCL_WIN

#include <os2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Important game constants (pseudo constants are in profile) */
#define MAXPHOTONS	 8	    /* Max photons (actually an option)    */
#define MAXPLAYERS	 2	    /* Max players (not used much)	   */
#define MAXINITASTEROIDS 8	    /* Max asteroids at any level init.    */
#define MAXASTEROIDS	 32	    /* Max asteroids ever		   */

/* Lookup table and coordinate system constants */
#define DIRS		 28	    /* # directions in acceleration	   *
				     * table, also used for drawing ship   */
#define SSIDES		 3	    /* # sides of ship			   */
#define ASIDES		 8	    /* # sides/entries in asteroid table   */
#define ESIDES		 7	    /* # sides/entries in enemy table	   */
#define MAXPHOTONDIST	 42	    /* Distance photons can travel	   */
#define MAXINT		 (1<<((sizeof(int)*8)-1))-1 /* Max integer value   */
#define MAXCOORD	 32767	    /* Max allowable coordinate 	   */
#define MAXCOORD2	 16384	    /* half of MAXCOORD			   */
#define MAXCOORDSHIFT	 15	    /* Optimization for coordinate math    */
#define MAXACC		 3800	    /* Max ship speed, scaled by 8 for	   */
				    /*	 decelleration calculations	   */
#define MAXASPEED        325        /* Maximum and minimum asteroid speeds */
#define MINASPEED	 75         /* (absolute values)		   */

/* Constants for hidden speeds */
#define	SPEED_NORMAL	 0
#define SPEED_WINDOWS	 1
#define	SPEED_OS2	 2

/* Scaling factors for drawing functions and distance calculations */
#define ASTEROID_S  1		    /* Scale factor for small asteroids    */
#define ASTEROID_M  4		    /* Scale factor for medium asteroids   */
#define ASTEROID_L  8		    /* Scale factor for large asteroids    */
#define ENEMY_S     16		    /* Scale factor for small enemy ship   */
#define ENEMY_L     32		    /* Scale factor for large enemy ship   */

/* Ship states (enumerated) */
#define NONE	    0x0000	    /* Normal state			   */
#define INITIALIZE  0x0001	    /* Invisible state at each new ship    */
#define HYPERSPACE  0x0002	    /* Input request to enter hyperspace   */
#define SHIELD	    0x0003	    /* Ship is shielded 		   */
#define EXPLOSION   0x0004	    /* Explosion state			   */
#define TURN_LEFT   0x0010	    /* Input request to turn ship left	   */
#define TURN_RIGHT  0x0020	    /* Input request to turn ship right    */
#define THRUST	    0x0040	    /* Input request to accelerate ship    */
#define FIREPHOTON  0x0080	    /* Input request to fire photon	   */
#define	FIRERELEASE 0x0100          /* Non-rapid fire, after photon fired  */
#define CLEARNON    0xFFF0	    /* Used to clear non-additive modes    */
#define CLEARADD    0x000F	    /* Used to clear additive modes	   */

/* Game States (enumerated) */
#define GAME_MODE_INIT1 0	    /* "Press 1 or 2" initial state	   */
#define GAME_MODE_INIT2 1	    /* "High Score" initial state	   */
#define GAME_MODE_PLAY	2	    /* Normal play state		   */
#define GAME_MODE_NEXT	3	    /* Temp. state between player switch   */
#define GAME_MODE_OVER	4	    /* "Game Over" state		   */
#define GAME_MODE_HIGH	5	    /* "Enter your initials" state	   */

/* Drawing modes */
#define DRAW_DELETE  0		    /* Asteroids only, erase current one   */
#define DRAW_ERASE   1		    /* Erase all of object type 	   */
#define DRAW_INIT    2		    /* Draw object(s)			   */
#define DRAW_REINIT  3		    /* Erase then draw object(s)	   */
#define DRAW_REFRESH 4		    /* Redraw object(s) 		   */

/* Timer constants */
#define ASTEROID_TIME	30	    /* Ticks before asteroids appear	   */
#define HYPERSPACE_TIME 40	    /* Ticks before ship appears after	   */
#define SHIELD_ON_TIME	960	    /* Ticks*RATIO shield can stay on	   */
#define SHIELD_RATIO_1	9	    /* Ratio of recharge vs. on time + 1   */
#define SHIELD_LVL_MIN	240	    /* Minimum energy level below which    *
				     *	 shield will not come on.	   */
#define EXPLOSION_TIME	10	    /* Ticks ship/enemy explodes	   */
#define GAME_PAUSE_TIME 80	    /* Ticks for pause between player 1&2  */
#define GAME_INIT_TIME	800	    /* Ticks between screen swaps -	   *
				     *	 high score list and press 1 or 2  */
#define TIMER_TICK_LENGTH 30	    /* # msecs between ticks, actually	   *
				     *	 about 32.5 on most computers	   */

/* Font local identifiers - used in both ASTEROID.C and SUBS.C */
#define LCID_LARGE   1
#define LCID_SMALL   2

/* Global function prototyping - see SUBS.C for more info */
void AddScore(INT);
void DrawScore(HPS, INT, INT, INT);
void UpdateHighScores(void);
void DrawHighScore(HPS, INT, INT, INT);
BOOL NewTimerTick(VOID);

void InitAsteroids(void);
void UpdateAsteroids(HPS, INT, INT);
void MoveAsteroids(void);
void DrawAsteroids(HPS, INT, INT, INT);
void ExplodeAsteroid(HPS, INT);

void InitShip(void);
void Accelerate(void);
void Hyperspace(void);
void UpdateShip(HPS, INT, INT);
void MoveShip(HPS);
void DrawShip(HPS, INT, INT, INT);
void ExplodeShip(HPS, INT, INT);

void InitEnemy(void);
void UpdateEnemy(HPS, INT, INT);
void MoveEnemy(HPS);
void DrawEnemy(HPS, INT, INT, INT);
void ExplodeEnemy(HPS, INT, INT);

void DeletePhotons(void);
void InitPhoton(void);
void InitEnemyPhoton(void);
void UpdatePhotons(HPS, INT, INT);
void MovePhotons(HPS);
void DrawPhotons(HPS, INT, INT, INT);

/* Macros */
#define UPDATE_FIRE(mode, addmode)\
{\
    if (!(mode & CLEARADD) || (mode == SHIELD)) {\
	if (addmode) {\
            mode &= CLEARNON;\
	    mode |= FIREPHOTON;\
	} else {\
    	    mode &= ~FIREPHOTON;\
        }\
    }\
}

#define UPDATE_LEFT(mode, addmode)\
{\
    if (!(mode & CLEARADD) || (mode == SHIELD)) {\
        if (addmode) {\
       	    mode &= CLEARNON;\
            mode &= ~TURN_RIGHT;\
            mode |= TURN_LEFT;\
  	} else {\
    	    mode &= ~TURN_LEFT;\
        }\
    }\
}

#define UPDATE_RIGHT(mode, addmode)\
{\
    if (!(mode & CLEARADD) || (mode == SHIELD)) {\
	if (addmode) {\
            mode &= CLEARNON;\
            mode &= ~TURN_LEFT;\
            mode |= TURN_RIGHT;\
    	} else {\
    	    mode &= ~TURN_RIGHT;\
        }\
    }\
}

#define UPDATE_THRUST(mode, addmode)\
{\
    if (!(mode & CLEARADD) || (mode == SHIELD)) {\
	if (addmode) {\
    	    mode &= CLEARNON;\
            mode |= THRUST;\
    	} else {\
    	    mode &= ~THRUST;\
        }\
    }\
}

#define UPDATE_HYPERSPACE(mode, modecnt)\
{\
    if (!(mode & CLEARADD) || (mode == SHIELD)) {\
        mode = HYPERSPACE;\
    	modecnt = HYPERSPACE_TIME;\
    }\
}

#define UPDATE_SHIELD(mode, shieldcnt)\
{\
    if (!(mode & CLEARADD)) {\
    	if (prfProfile.bSHIELD && shieldcnt > SHIELD_LVL_MIN)\
	    	mode = SHIELD;\
    }\
}

/* Keyboard key structure - used to save key definitions */
#define KEYS	6
typedef struct _KEY {
    CHAR   vk, chr;			    /* Virtual key code, ASCII chr */
} KEY;

/* Profile record structure */
typedef struct _PROFILEREC {
    BOOL   bCONTROLS;			    /* Are frame controls visible  */
    BOOL   bBACKGRND;			    /* Execute in the background?  */
    ULONG  ulMINMAX;			    /* Is app iconized? 	   */
    LONG   cy,cx,y,x;			    /* Screen size and position    */
    UINT   uiSEED;			    /* Random # seed		   */
    INT    iSHIPS, iPHOTONS;		    /* Initial Ships, max photons  */
    BOOL   bSHIELD;			    /* Does the shield work?	   */
    BOOL   bRAPIDFIRE;			    /* Is rapid fire enabled	   */
    INT    iFIRERATE;			    /* Rapid fire rate		   */
    BOOL   bMOUSECONTROL;		    /* Use mouse to controll mvmnt?*/
    KEY    keyDEFS[KEYS];		    /* Key definitions		   */
    LONG   lSCORES[10]; 		    /* Top 10 high scores	   */
    CHAR   szINIT[10][4]; 		    /*	 and player initials	   */
} PROFILEREC;


/* Data definitions for ASTEROID.C */
#ifdef MAIN

/* Global */
PROFILEREC prfProfile =
   { TRUE, FALSE, 0L,
     0L, 0L, 0L, 0L, 17,
     3, 4, TRUE, TRUE, 8, FALSE,
     VK_LEFT-1,  0,
     VK_RIGHT-1, 0,
     VK_UP-1,    0,
     VK_DOWN-1,  0,
     VK_SPACE-1, 0,
     0, 's',
     0,  0,  0,  0,  0,
     0,  0,  0,  0,  0 };

INT    Player;				    /* Keeps track of current plyr */
INT    cPlayers;			    /* # of players		   */
INT    Ships[2];			    /* # ships each player has	   */
INT    Level[2];			    /* Level each player is on	   */
LONG   Score[2];			    /* Score of each player	   */
UINT   uiSpeed = SPEED_NORMAL;		    /* Play speed.		   */

INT    iGameMode, iGameModeCnt;		    /* Game mode and counter	   */
UINT   iShipMode[2] = { 0, 0 }; 	    /* Ships modes and counts	   */
INT    iShipModeCnt[2] = { 0, 0 },
       iShipShieldCnt[2] = { 0, 0 };
INT    iEnemyMode[2] = { 0, 0 },	    /* Enemy modes and counts	   */
       iEnemyModeCnt[2] = { 0, 0 };
INT    iSizeLarge, iSizeSmall;		    /* Size of small & large fonts */
BOOL   bChangeScore = FALSE;		    /* Should score be redrawn?    */

/* Data definitions for SUBS.C */
#else

/* Global */
extern PROFILEREC prfProfile;

extern INT    Player;
extern INT    cPlayers;
extern INT    Ships[2];
extern INT    Level[2];
extern LONG   Score[2];
extern UINT   uiSpeed;

extern INT    iGameMode, iGameModeCnt;
extern UINT   iShipMode[2];
extern INT    iShipModeCnt[2], iShipShieldCnt[2];
extern INT    iEnemyMode[2], iEnemyModeCnt[2];
extern INT    iSizeLarge, iSizeSmall;
extern BOOL   bChangeScore;

/* Local */
INT    Acnt[2] = { 0, 0 };		    /* Count of asteroids	   */
INT    Asiz[2][MAXASTEROIDS];		    /* Size of each asteroid	   */
POINTL Apos[2][MAXASTEROIDS],		    /* Position of each asteroid   */
       Aacc[2][MAXASTEROIDS];		    /* Speed of each asteroid	   */
INT    Sdir[2]; 			    /* Direction of ship	   */
POINTL Spos[2],Sacc[2]; 		    /* Position & speed of ship    */
INT    Esiz[2]; 			    /* Enemy size		   */
POINTL Epos[2],Eacc[2]; 		    /* Position & speed of enemy   */
INT    Pcnt[2]; 			    /* Photon count		   */
POINTL Ppos[2][MAXPHOTONS+1],		    /* Photon position		   */
       Pacc[2][MAXPHOTONS+1];		    /* Photon speed		   */
INT    Pdst[2][MAXPHOTONS+1];		    /* Distance photon has traveled*/


/* Data tables and calculated acceleration tables (scaled) */

/* Possible asteroid speeds, based on normal of MAXCOORD */
#define SPEEDS 16
INT ASPEEDS[SPEEDS] = { -325, -300, -262, -225, -187, -150, -112,  -75,
			  75,  112,  150,  187,  225,  262,  300,  325 };

/* Table for vertices of asteroid and asteroid scale factor for distance *
 *   calculations (corresponds to max absolute value in table). 	 *
 * The values of ASTEROID and ASTEROID_MAX have been scaled by 3	 *
 *   to optimize out a scale factor of 3 in the Drawing and Collision	 *
 *   checking of asteroids.						 */
#define ASTEROID_MAX 300
INT ASTEROID[ASIDES][2] = {
      300,    0,
      213,  213,
	0,  300,
     -213,  213 ,
     -300,    0,
     -213, -213,
	0, -300,
      213, -213 };

/* Table for vertices of ship and ship scale factor for distance	*
 *   calculations							*
 * The value DIR_MAX has been scaled by 3 for optimization in Collision *
 *   checking.								*/
#define DIR_MAX 480
INT DIR[DIRS][SSIDES][2] = {
    -100, -100,    0,  200,  100, -100,
     -75, -120,  -45,  195,  120,  -75,
     -47, -133,  -87,  180,  133,  -47,
     -16, -141, -125,  156,  141,  -16,
      16, -141, -156,  125,  141,   16,
      47, -133, -180,	87,  133,   47,
      75, -120, -195,	45,  120,   75,
     100, -100, -200,	-0,  100,  100,
     120,  -75, -195,  -45,   75,  120,
     133,  -47, -180,  -87,   47,  133,
     141,  -16, -156, -125,   16,  141,
     141,   16, -125, -156,  -16,  141,
     133,   47,  -87, -180,  -47,  133,
     120,   75,  -45, -195,  -75,  120,
     100,  100,    0, -200, -100,  100,
      75,  120,   45, -195, -120,   75,
      47,  133,   87, -180, -133,   47,
      16,  141,  125, -156, -141,   16,
     -16,  141,  156, -125, -141,  -16,
     -47,  133,  180,  -87, -133,  -47,
     -75,  120,  195,  -45, -120,  -75,
    -100,  100,  200,	 0, -100, -100,
    -120,   75,  195,	45,  -75, -120,
    -133,   47,  180,	87,  -47, -133,
    -141,   16,  156,  125,  -16, -141,
    -141,  -16,  125,  156,   16, -141,
    -133,  -47,   87,  180,   47, -133,
    -120,  -75,   45,  195,   75, -120 };

/* Table for vertices of enemy and enemy scale factor for distance    *
 *   calculations (corresponds to max absolute value in table).       *
 * The values of ENEMY and ENEMY_MAX have been scaled by 3	      *
 *   to optimize out a scale factor of 3 in the Drawing and Collision *
 *   checking of asteroids.					      */
#define ENEMY_MAX 300
INT ENEMY[ESIDES][2] = {
     -300,    0,
     -150, -150,
      150, -150,
      300,    0,
       75,  225,
      -75,  225,
     -300,    0 };

/* Acceleration table for calculating x/y speed vectors based on direction *
 *   and thrust.							   *
 * This table has not been scaled					   */
INT ACC[DIRS][2] = {
	0,  50,
      -11,  49,
      -22,  45,
      -31,  39,
      -39,  31,
      -45,  22,
      -49,  11,
      -50,  -0,
      -49, -11,
      -45, -22,
      -39, -31,
      -31, -39,
      -22, -45,
      -11, -49,
	0, -50,
       11, -49,
       22, -45,
       31, -39,
       39, -31,
       45, -22,
       49, -11,
       50,   0,
       49,  11,
       45,  22,
       39,  31,
       31,  39,
       22,  45,
       11,  49 };

#endif
