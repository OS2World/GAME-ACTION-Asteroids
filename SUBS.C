/****************************************************************************
 * SUBS.C     							            *
 *									    *
 *   PM unrelated game subroutines.  Only the draw routines rely on PM.     *
 *   Most information is modified through the use of global variables.      *
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

#include "asteroid.h"                     /* Include game data, #def's, etc */
#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
#endif
#define sgn(a) (((a)<0)?(-1):(1))

/****************************************************************************
 *			     General Routines				    *
 ****************************************************************************/

/****************************************************************************
 * smax                                                                     *
 *  - Returns the max of absolute value of 2 integers, signed according to  *
 *      the first parameter (basically).                                    *
 *  - Accepts two LONGs and returns a LONG as described.                    *
 ****************************************************************************/
LONG smax(LONG a,LONG b)
{
    if (a < 0)
	return max(a/100L,-b);
    else
	return max(a/100L,b);
}

/****************************************************************************
 * isqrt                                                                    *
 *  - Returns the integer square root of an integer.			    *
 *  - Accepts one LONG and returns a LONG as described.                     *
 ****************************************************************************/
LONG isqrt(LONG val)
{
    LONG x, y, z;

    x = y = val;
    if (val > 1) {
	while (x > 0) {
	    x >>= 2;
	    y >>= 1;
	    }
	do {
	    x = y;
	    z = val / y;
	    y = (z + y) >> 1;
	    } while ((x-z) < -1 || (x-z) > 1);
	}

    return(y);		
}


/****************************************************************************
 *			     Text Routines				    *
 ****************************************************************************/

/****************************************************************************
 * AddScore                                                                 *
 *  - Given an object type, increments current player's score appropriately *
 *  - Inputs object type.                                                   *
 ****************************************************************************/
void AddScore(INT type)
{
    LONG value;

    /* Determine object's value */
    switch (type) {
      case ASTEROID_L:
	value = 20;
	break;
      case ASTEROID_M:
	value = 50;
	break;
      case ASTEROID_S:
	value = 100;
	break;
      case ENEMY_L:
	value = 250;
	break;
      case ENEMY_S:
	value = 1000;
	break;
      }

    /* Check to see if the player gets another ship */
    if ((Score[Player] % 10000L) + value >= 10000L)
	Ships[Player]++;

    /* Add the value of the destroyed object to the player's score */
    Score[Player] += value;

    /* Make sure score is reinitialized, not just refreshed */
    bChangeScore = TRUE;
}

/****************************************************************************
 * DrawScore                                                                *
 *  - Updates score on screen.  Mode of display depends on game mode and    *
 *    refresh mode.                                                         *
 *  - Inputs HPS, X & Y screen dimensions, and refresh mode.                *
 *                                                                          *
 * Notes:                                                                   *
 *  - There are five possible ways to draw the scores:                      *
 *      o GAME_MODE_INIT1                                                   *
 *      o GAME_MODE_INIT2                                                   *
 *      o GAME_MODE_NEXT                                                    *
 *      o GAME_MODE_OVER                                                    *
 *      o All other game modes                                              *
 *    Each of the scoring modes requires diffent text, a different number   *
 *    of lines of text, and a different placement of text.                  *
 *  - Part of the score output is handled by DrawHighScore (below)          *
 *  - I'm not sure why I chose not to separate DrawScore into a UpdateScore *
 *    and a DrawScore routine as I did for the other "objects".             *
 ****************************************************************************/
void DrawScore(HPS hps, INT iMaxx, INT iMaxy, INT iMode)
{
	   INT    i = 0;                /* Index variable                   */
	   INT    iFontSize;            /* Assigned font size at execution  */

    static CHAR   szString[11][17];     /* Score text, updated by DRAW_INIT */
    static INT    cLen[11];             /* Text line length,        "       */
    static POINTL ptl[11];              /* Text position,           "       */
    static INT    cLines = 0;           /* Number of text lines,    "       */

    /* If screen is too small to support score, don't draw it */
    if ((iMaxx < 24 * iSizeSmall) || (iMaxy < 20 * iSizeSmall))
	return;

    switch (iMode) {

      /* Erase any old scores */
      case DRAW_ERASE: case DRAW_REINIT:
	GpiSetColor(hps,CLR_BLACK);
	GpiSetCharSet(hps,LCID_SMALL);

        /* If not in GAME_MODE_INIT2 mode, erase the high score (always *
         *   drawn in small font).                                      */
	if (cLines < 11) {
	    GpiCharStringAt(hps,&ptl[0],strlen(szString[0]),szString[0]);
	    i=1;
	    }

        /* Pick size of text to make sure everything will fit */
	if ((iMaxx > 32 * iSizeLarge) && (iMaxy > 20 * iSizeLarge))
	    GpiSetCharSet(hps,LCID_LARGE);
	for (;i<cLines;i++)
	    GpiCharStringAt(hps,&ptl[i], cLen[i], szString[i]);

	if (iMode == DRAW_ERASE)
	    return;

      /* Recalculate and draw all text strings for current game mode. */
      case DRAW_INIT:
        /* GAME_MODE_INIT2 (High Scores table) requires the most lines,     *
         *   following lines initialize a title and the 10 best score lines */
	if (iGameMode == GAME_MODE_INIT2) {
	    cLines = 11;
	    strcpy(szString[0],"HIGH SCORES");
	    for (i=1;i<11;i++)
		sprintf(szString[i],"%2d. %5ld %3s", i,
		    prfProfile.lSCORES[i-1], prfProfile.szINIT[i-1]);
	    }

        /* All other modes have the high score, the scores for each player, *
         *   the number of ships they have, and the copyright message.      */
	else {
	    sprintf(szString[0], "%ld", prfProfile.lSCORES[0]);
	    sprintf(szString[1], "%ld", Score[0]);
	    sprintf(szString[2], "%ld", Score[1]);
	    strcpy(szString[3],"??????????");
	    strcpy(szString[4],"??????????");
	    szString[3][(Ships[0] < 11) ? Ships[0] : 10] = 0;
	    szString[4][(Ships[1] < 11) ? Ships[1] : 10] = 0;
	    sprintf(szString[5],"@1993 TODD CROWE");

            /* Other game modes have further refinements */
	    switch (iGameMode) {
              /* Screen to prompt for game selection */
	      case GAME_MODE_INIT1:
		cLines = 8;
		strcpy(szString[6],"PRESS 1 OR 2");
		strcpy(szString[7],"TO START GAME");
		break;
              /* Screen to signal next player's turn */
	      case GAME_MODE_NEXT:
		if (cPlayers == 2) {
		    cLines = 7;
		    sprintf(szString[6],"PLAYER %d",Player+1);
		    }
		else
		    cLines = 6;
		break;
              /* Game over screen */
	      case GAME_MODE_OVER:
		cLines = 8;
		sprintf(szString[6],"GAME OVER");
		sprintf(szString[7],"PLAYER %d",Player+1);
		break;
	      default:
		cLines = 6;
	      }
	    }

        /* Line length is required for GpiCharStringAt function */
	for (i=0;i<cLines;i++)
	    cLen[i] = strlen(szString[i]);

        /* Pick size of text to make sure everything will fit */
	if ((iMaxx > 32 * iSizeLarge) && (iMaxy > 20 * iSizeLarge))
	    iFontSize = iSizeLarge;
	else
	    iFontSize = iSizeSmall;

        /* Format text string positions for high score table */
	if (iGameMode == GAME_MODE_INIT2) {
	    ptl[0].x = (LONG) (iMaxx - cLen[0]*iFontSize) / 2L;
	    ptl[0].y = (LONG) (iMaxy/2 + 10*iFontSize);
	    for (i=1;i<11;i++) {
		ptl[i].x = (LONG) (iMaxx - cLen[i]*iFontSize) / 2L;
		ptl[i].y = ptl[i-1].y - ((LONG) 2*iFontSize);
		}
	    ptl[0].y += (LONG) (iFontSize);
	    }

        /* Format text string positions for all other game modes.  (All *
         *   just tedious calculations.                                 */
	else {
	    ptl[0].x = (LONG) (iMaxx - cLen[0]*iSizeSmall) / 2L;
	    ptl[0].y = (LONG) (iMaxy - 3*iSizeSmall);
	    ptl[1].x = (LONG) iFontSize;
	    ptl[1].y = (LONG) (iMaxy - 2*iFontSize);
	    ptl[2].x = (LONG) (iMaxx - (cLen[2]+1)*iFontSize);
	    ptl[2].y = ptl[1].y;
	    ptl[4].x = (LONG) (iMaxx - (cLen[4]+1)*iFontSize);
	    ptl[4].y = (LONG) (iMaxy - 3*iFontSize-4);
	    ptl[3].x = (LONG) iFontSize;
	    ptl[3].y = ptl[4].y;
	    ptl[5].x = (LONG) (iMaxx/2 - 8*iFontSize);
	    ptl[5].y = (LONG) iFontSize;
	    switch (iGameMode) {
	      case GAME_MODE_INIT1: case GAME_MODE_OVER:
		ptl[6].x = (LONG) (iMaxx - cLen[6]*iFontSize) / 2L;
		ptl[6].y = (LONG) (iMaxy/2 + iFontSize);
		ptl[7].x = (LONG) (iMaxx - cLen[7]*iFontSize) / 2L;
		ptl[7].y = (LONG) (iMaxy/2 - iFontSize);
		break;
	      case GAME_MODE_NEXT:
		ptl[6].x = (LONG) (iMaxx - cLen[6]*iFontSize) / 2L;
		ptl[6].y = (LONG) (iMaxy/2);
		ptl[7].x = 0L;
		ptl[7].y = 0L;
		break;
	      }
	    }

      /* Refresh score text strings previously calculated by DRAW_INIT. */
      case DRAW_REFRESH:
	GpiSetColor(hps,CLR_WHITE);
	GpiSetCharSet(hps,LCID_SMALL);

        /* Draw the high score if game is not in GAME_MODE_INIT2 mode.  *
         * In GAME_MODE_INIT2 all text lines are drawn in the largest   *
         *   font size possible, other modes always draw the high score *
         *   in the small font.                                         */
	if (cLines < 11) {
	    GpiCharStringAt(hps,&ptl[0],strlen(szString[0]),szString[0]);
	    i=1;
	    }
	else
	    i=0;

        /* Select large font if it will fit. */
	if ((iMaxx > 32 * iSizeLarge) && (iMaxy > 20 * iSizeLarge))
	    GpiSetCharSet(hps,LCID_LARGE);

        /* Draw scores */
	for (;i<cLines;i++)
	    GpiCharStringAt(hps,&ptl[i],cLen[i],szString[i]);
      }
}

/****************************************************************************
 * UpdateHighScores                                                         *
 *  - Updates high score table, effectively through an insertion sort.      *
 *  - No Input.  (Global variables)                                         *
 ****************************************************************************/
void UpdateHighScores(void)
{
    /* Since this routine is only called when a valid high score exists *
     *   start the search at the nineth highest score.                  */
    INT i=8, j;

    /* Update the high score table, which is part of the profile info. */
    while ((i >= 0) && (Score[Player] > prfProfile.lSCORES[i])) {
	prfProfile.lSCORES[i+1] = prfProfile.lSCORES[i];
        for (j = 0;j < 3;j++)
	    prfProfile.szINIT[i+1][j] = prfProfile.szINIT[i][j];
        prfProfile.szINIT[i+1][3] = '\0';
	i--;
	}

    /* Fill the high score entry with the player's score and set of default *
     *   initials.  In cases where the screen is too small, the player will *
     *   not be prompted for his initials.                                  */
    prfProfile.lSCORES[i+1] = Score[Player];
    for (j = 0;j < 3;j++)
	prfProfile.szINIT[i+1][j] = ' ';
    prfProfile.szINIT[i+1][3] = '\0';

    /* Set the player's score to his position in the new high score list, *
     *   this is partly a feature and a programming simplification; the   *
     *   latter because DrawHighScore needs the players position and      *
     *   overloading the players' scores eliminating adding a variable    */
    Score[Player] = i+2;
}

/****************************************************************************
 * DrawHighScores                                                           *
 *  - This routine is used instead of DrawScore at the completion of a game.*
 *      Players with high scores are prompted to enter their intializes.    *
 *      Because of the way input is centralized in the PM input loop the    *
 *      easiest way to implement this was to have this routine completely   *
 *      take over the WM_TIMER message.                                     *
 *  - Inputs HPS, X & Y screen dimensions, and refresh mode.                *
 ****************************************************************************/
void DrawHighScore(HPS hps, INT iMaxx, INT iMaxy, INT iMode)
{
	   INT    i = 0;                /* Index variable                   */
	   INT    iFontSize;            /* Assigned font size at execution  */

    static POINTL ptl[2];
    static INT    iIndex = 0;               /* Position in array of initials*/
    static CHAR   szPlyr[9] = "        ";   /* Contains "Player %d",Player  */
    static CHAR   szInit[6] = "_ _ _";      /* For plotting initials        */
    static CHAR   szText[4][39] = { "YOUR SCORE IS ONE OF THE TEN BEST     ",
				    "PLEASE ENTER YOUR INITIALS            ",
				    "PUSH ROTATE TO SELECT LETTER          ",
				    "PUSH HYPERSPACE WHEN LETTER IS CORRECT" };

    /* Pick size of text to make sure everything will fit */
    if ((iMaxx > 40 * iSizeLarge) && (iMaxy > 16*iSizeLarge)) {
	GpiSetCharSet(hps,LCID_LARGE);
	iFontSize = iSizeLarge;
	}
    else if ((iMaxx > 40 * iSizeSmall) && (iMaxy > 16 * iSizeSmall)) {
	GpiSetCharSet(hps,LCID_SMALL);
	iFontSize = iSizeSmall;
	}
    /* If the text won't fit then don't prompt for the player's initials */
    else {
	Score[Player] = 0;
	iIndex = 0;
	return;
	}

    switch (iMode) {
      /* DRAW_ERASE is never required, the screen is simply erased.  *
       *   If a second player is prompted for initials, however, the *
       *   old information must be removed.                          */
      case DRAW_REINIT:
	GpiSetColor(hps,CLR_BLACK);
	GpiCharStringAt(hps,&ptl[0],8,szPlyr);
	GpiCharStringAt(hps,&ptl[1],5,szInit);

      /* Set up text strings for current player, and draw them on the screen */
      case DRAW_INIT:
	GpiSetColor(hps,CLR_WHITE);
	ptl[0].x = (LONG) (iMaxx/2 - 19*iFontSize);
	ptl[0].y = (LONG) (iMaxy/2 + 4*iFontSize);
	for (i=0;i<4;i++) {
	    ptl[0].y -= (LONG) (2*iFontSize);
	    GpiCharStringAt(hps,&ptl[0],38,szText[i]);
	    }

	sprintf(szPlyr,"PLAYER %d",Player+1);
	ptl[0].x = (LONG) (iMaxx/2 - 4*iFontSize);
	ptl[0].y = (LONG) (iMaxy/2 + 7*iFontSize);
	GpiCharStringAt(hps,&ptl[0],8,szPlyr);

	/* SHIELD mode is ignored, this is used basically to "zero" the *
         *   input queue.                                               */
	iShipMode[Player] = SHIELD;

      /* Because the input method is basically stupid/blind, for simplicity *
       *   the following relies on the same messages as the ship does.      *
       * While left and right may intuitively seem backward, they are       *
       *   faithful to the arcade game.                                     *
       * For simplicity the high score table is modified directly.          */
      case DRAW_REFRESH:
	/* Cycle up through the alphabet on TURN_LEFT. */
	if (iShipMode[Player] & TURN_LEFT) {
	    if (prfProfile.szINIT[Score[Player]-1][iIndex] == ' ')
		prfProfile.szINIT[Score[Player]-1][iIndex] = 'A';
	    else if (++prfProfile.szINIT[Score[Player]-1][iIndex] > 'Z')
		prfProfile.szINIT[Score[Player]-1][iIndex] = ' ';
	    }

	/* Cycle down through the alphabet on TURN_RIGHT. */
	else if (iShipMode[Player] & TURN_RIGHT) {
	    if (prfProfile.szINIT[Score[Player]-1][iIndex] == ' ')
		prfProfile.szINIT[Score[Player]-1][iIndex] = 'Z';
	    else if (--prfProfile.szINIT[Score[Player]-1][iIndex] < 'A')
		prfProfile.szINIT[Score[Player]-1][iIndex] = ' ';
	    }

	/* HYPERSPACE is used to request the completion of one character *
	 *   of input by the player.					 */
	else if (iShipMode[Player] == HYPERSPACE ||
         	 iShipMode[Player] & FIREPHOTON) {
	    if (++iIndex == 3) {
		Score[Player] = 0;
		iIndex = 0;
		return;
		}
	    else
		iShipMode[Player] = NONE;
	    }

	else if (iShipMode[Player] != SHIELD) {
	    iShipMode[Player] = NONE;
	    return;
	    }

	iShipMode[Player] = NONE;

        /* Erase old initials */
	GpiSetColor(hps,CLR_BLACK);
	GpiCharStringAt(hps,&ptl[1],5,szInit);

        /* Set up text for new initials */
	for (i=0;i<3;i++)
	    if (prfProfile.szINIT[Score[Player]-1][i] == ' ' &&
            	i <= iIndex)
		szInit[i*2] = '_';
	    else
		szInit[i*2] = prfProfile.szINIT[Score[Player]-1][i];

	ptl[1].x = (LONG) (iMaxx/2 - 3*iFontSize);
	ptl[1].y = (LONG) (iMaxy/2 - 7*iFontSize);

        /* Draw new initials */
	GpiSetColor(hps,CLR_WHITE);
	GpiCharStringAt(hps,&ptl[1],5,szInit);
      }
}



/***************************************************************************
 *			     Asteroid Routines				   *
 ***************************************************************************/

/****************************************************************************
 * InitAsteroids                                                            *
 *  - Creates number of asteroids appropriate to the level, initializes     *
 *      them to make sure there a specific distance or greater from the     *
 *      player, and gives them a random speed.                              *
 *    Asteroids are given a discrete speed from the ASPEEDS table.          *
 *  - No I/O.                                                               *
 ****************************************************************************/
void InitAsteroids(void)
{
    INT   i;                        /* Index variable                       */
    LONG  dx,dy,d;                  /* Used for distance calcuations        */

    /* Find the number of asteroids appropriate to this level */
    Acnt[Player] = Level[Player] * 2 + 2;
    if (Acnt[Player] > MAXINITASTEROIDS) Acnt[Player] = MAXINITASTEROIDS;

    /* For each asteroid, make it large, make sure it's not to close to the *
     *   player, and give it a speed.                                       */
    for (i=0;i<Acnt[Player];i++) {
	Asiz[Player][i] = ASTEROID_L;

        /* Distance calculation is optimized such that a sqrt is not req'd  */
	do {
	    Apos[Player][i].x = (INT) (rand() % MAXCOORD);
	    Apos[Player][i].y = (INT) (rand() % MAXCOORD);
	    dx = (LONG) (Apos[Player][i].x - Spos[Player].x);
	    dy = (LONG) (Apos[Player][i].y - Spos[Player].y);
	    d  = ((LONG) ((ASTEROID_L+4) * ASTEROID_MAX + DIR_MAX));
	} while ((Level[Player] > 1) && ((dx * dx + dy * dy) < (d * d)));

        /* Find a speed.  The table is symetric about zero at the middle */
	Aacc[Player][i].x = ASPEEDS[(rand() % (SPEEDS-6)) + 3];
	Aacc[Player][i].y = ASPEEDS[(rand() % (SPEEDS-6)) + 3];
        }
}

/****************************************************************************
 * UpdateAsteroids                                                          *
 *  - Called from WM_TIMER.  Updates the position of all asteroids or       *
 *      decrements a timer count at the end of each level.                  *
 *  - Inputs HPS, X & Y screen dimensions.                                  *
 ****************************************************************************/
void UpdateAsteroids(HPS hps, INT iMaxx, INT iMaxy)
{
    /* Timer count, decremented to zero before the display of each new set  */
    /*   of asteroids.                                                      */
    static INT iAsteroidAdjCnt[MAXPLAYERS] = { ASTEROID_TIME, ASTEROID_TIME };

    /* If there are asteroids on the screen asteroids are updated normally. *
     * If there are no asteroids, the DrawAsteroids routine is given a      *
     *   chance to erase all the old ones.  Theoretically this method       *
     *   contains a bug, if the last >4 asteroids are destroyed during the  *
     *   last tick, DrawAsteroids may not have enough time to erase them.   *
     * The IF statement relies on shortcircuiting.                          */
    if ((Acnt[Player] > 0) || (iAsteroidAdjCnt[Player]-- == ASTEROID_TIME)) {
	MoveAsteroids();
	DrawAsteroids(hps,iMaxx,iMaxy,DRAW_REFRESH);
	}

    /* There are no asteroids and the count has expired. Start next level.  */
    /* If conditional added 1/15/90 - A bug I hadn't noticed!               */
    else if (iAsteroidAdjCnt[Player] == 0) {
	iAsteroidAdjCnt[Player] = ASTEROID_TIME;
	Level[Player]++;
	InitAsteroids();
	if (iEnemyMode[Player] == NONE)
	    InitEnemy();
	}
}

/****************************************************************************
 * MoveAsteroids                                                            *
 *  - Recalculates position of each asteroid every tick (actually because   *
 *      asteroids take so long to draw - every other tick).  This routine   *
 *      updates every asteroid even if DrawAsteroids does not.              *
 *  - No I/O.                                                               *
 ****************************************************************************/
void MoveAsteroids(void)
{
    INT i;

    for (i=0;i<Acnt[Player];i++) {
        /* Calculate new X coordinate, make sure it's within range. */
	Apos[Player][i].x += Aacc[Player][i].x;
	if (Apos[Player][i].x < 0) Apos[Player][i].x += MAXCOORD;
	else if (Apos[Player][i].x > MAXCOORD) Apos[Player][i].x -= MAXCOORD;

        /* Calculate new Y coordinate, make sure it's within range. */
	Apos[Player][i].y += Aacc[Player][i].y;
	if (Apos[Player][i].y < 0) Apos[Player][i].y += MAXCOORD;
	else if (Apos[Player][i].y > MAXCOORD) Apos[Player][i].y -= MAXCOORD;
	}
}

/****************************************************************************
 * DrawAsteroids                                                            *
 *  - Updates asteroids on screen. Mode of display depends on game mode and *
 *    refresh mode.                                                         *
 *  - Inputs HPS, X & Y screen dimensions, and drawing mode.                *
 *    iMaxy is overloaded - used to specify erasure of a particular asteroid*
 *  - Unlike the other drawing routines, because it takes so long to draw   *
 *    all of the asteroids, 4 asteroids are drawn, the timer is checked, and*
 *    then if time remains more asteroids are drawn.                        *
 ****************************************************************************/
void DrawAsteroids(HPS hps, INT iMaxx, INT iMaxy, INT iMode)
{
    static INT    i = 0;                            /* Main Index. Note: static */
	   INT    j, cnt;                           /* Indexes              */
	   LONG   lCenterX,lCenterY,lSizeX,lSizeY;  /* Size calculations    */
    static POINTL Asteroids[MAXASTEROIDS][ASIDES];  /* structs - GpiPolyLine*/

    switch (iMode) {
      /* Deletes one asteroid from screen.  iMaxy is overloaded and contains*
       *   the number of the asteroid to erase.                             *
       * Usually called just before the asteroid explodes.                  */
      case DRAW_DELETE:
	GpiSetColor(hps,CLR_BLACK);
	GpiMove(hps,&Asteroids[iMaxy][ASIDES-1]);
	GpiPolyLine(hps,ASIDES,Asteroids[iMaxy]);
	break;

      /* Erase all asteroids, irreguardless of the time it takes. */
      case DRAW_ERASE:
	for (i=0;i<Acnt[Player];i++) {
	    GpiSetColor(hps,CLR_BLACK);
	    GpiMove(hps,&Asteroids[i][ASIDES-1]);
	    GpiPolyLine(hps,ASIDES,Asteroids[i]);
	    }
        /* Make sure asteroid index is zeroed. */
	i = 0;
	break;

      /* On refresh, start from first asteroid. */
      case DRAW_INIT:
	i = 0;

      /* Probably 90% of the CPU time used by ASTEROID is spent in the  *
       *   following few lines drawing the asteroids.                   */
      case DRAW_REFRESH:
	for (cnt=0;i<Acnt[Player];) {
	    /* Erase the old asteroid image */
	    GpiSetColor(hps,CLR_BLACK);
	    GpiMove(hps,&Asteroids[i][ASIDES-1]);
	    GpiPolyLine(hps,ASIDES,Asteroids[i]);

	    /* Set up POINTL array structure for GpiPolyLine */
	    lCenterX = (LONG) Apos[Player][i].x * (LONG) iMaxx;
	    lCenterY = (LONG) Apos[Player][i].y * (LONG) iMaxy;
	    lSizeX   = (LONG) Asiz[Player][i]	* (LONG) iMaxx;
	    lSizeY   = (LONG) Asiz[Player][i]	* (LONG) iMaxy;

	    for (j=0;j<ASIDES;j++) {
		Asteroids[i][j].x = (lCenterX + lSizeX *
		    (LONG) ASTEROID[j][0]) >> MAXCOORDSHIFT;
		Asteroids[i][j].y = (lCenterY + lSizeY *
		    (LONG) ASTEROID[j][1]) >> MAXCOORDSHIFT;
		}

	    /* Draw new asteroid image.  These 3 lines are the CPU hogs. */
	    GpiSetColor(hps,CLR_WHITE);
	    GpiMove(hps,&Asteroids[i][ASIDES-1]);
	    GpiPolyLine(hps,ASIDES,Asteroids[i]);

	    /* Done drawing Asteroid[i], do next asteroid (if any) */
	    i++;

	    /* After every 4th asteroid check to see if the timer has ticked *
	     *	 again, if so stop redrawing asteroids for now.              *
             * If in DRAW_INIT mode, all asteroids must be drawn.            */
	    if ((++cnt >= 4) && (i != Acnt[Player]) && (iMode != DRAW_INIT)) {
                /* If tick has expired immediately terminate. */
		if (NewTimerTick())
                    return;
		else
                    cnt=0;
		}
	    }
	i = 0;
	break;
      }
}

/****************************************************************************
 * ExplodeAsteroid                                                          *
 *  - Simulates the explosion of an asteroid.  Currently the asteroid is    *
 *      simply erased from the screen.  If the asteroid was not a small one *
 *      new asteroids are created.                                          *
 *  - HPS and index of asteroid that has been destroyed.                    *
 ****************************************************************************/
void ExplodeAsteroid(HPS hps, INT i)
{
    INT size, x, y;		  /* Temporary storage variables.           */
    INT xacc, yacc;

    /* Save the size and position of the asteroid. */
    size = Asiz[Player][i];
    x    = Apos[Player][i].x;y    = Apos[Player][i].y;
    xacc = Aacc[Player][i].x;yacc = Aacc[Player][i].y;

    /* Erase the asteroid that was hit - do it now to be neat, *
     *	 otherwise it won't be drawn until the next refresh.   */
    DrawAsteroids(hps,0,i,DRAW_DELETE);

    /* Delete old asteroid. Move the asteroid at the end of the list into the *
     *   position emptied by the destroyed asteroid.                          */
    if (i < --Acnt[Player]) {
	Asiz[Player][i] = Asiz[Player][Acnt[Player]];
	Apos[Player][i].x = Apos[Player][Acnt[Player]].x;
	Apos[Player][i].y = Apos[Player][Acnt[Player]].y;
	Aacc[Player][i].x = Aacc[Player][Acnt[Player]].x;
	Aacc[Player][i].y = Aacc[Player][Acnt[Player]].y;

	/* Erase the last asteroid in the list, otherwise it won't be erased. */
	DrawAsteroids(hps,0,Acnt[Player],DRAW_DELETE);
	}

    /* If the old asteroid was not small, create two new "half"-sized ones. */
    if (size != ASTEROID_S) {
        /* Put the 2 new asteroids at the (new) end of the asteroid list.   */
	for (i=Acnt[Player];i<Acnt[Player]+2;i++) {
	    Apos[Player][i].x = x + ((rand()%size)-(size>>1))*ASTEROID_MAX;
	    Apos[Player][i].y = y + ((rand()%size)-(size>>1))*ASTEROID_MAX;
	    if (size == ASTEROID_L) {
                Asiz[Player][i] = ASTEROID_M;
	    } else {
		Asiz[Player][i] = ASTEROID_S;
            }
                
            /* Calculate the new x-vector speed value based on the old.     */
	    Aacc[Player][i].x = (xacc * (rand() % 150 + 50)) / 100;
            if (abs(Aacc[Player][i].x) < MINASPEED)
                Aacc[Player][i].x = sgn(Aacc[Player][i].x) * MINASPEED;
            else if (abs(Aacc[Player][i].x) >
                     MAXASPEED + (MAXASPEED * (Level[Player]-1))/8)
                Aacc[Player][i].x = sgn(Aacc[Player][i].x) * MAXASPEED;
            if (rand() % 100 < 15)
             	Aacc[Player][i].x *= -1;
                
            /* Calculate the new y-vector speed value based on the old.     */
	    Aacc[Player][i].y = (yacc * (rand() % 150 + 50)) / 100;
            if (abs(Aacc[Player][i].y) < MINASPEED)
                Aacc[Player][i].y = sgn(Aacc[Player][i].y) * MINASPEED;
            else if (abs(Aacc[Player][i].y) > 
            	     MAXASPEED + (MAXASPEED * (Level[Player]-1))/8)
                Aacc[Player][i].y = sgn(Aacc[Player][i].y) * MAXASPEED;
            if (rand() % 100 < 15)
             	Aacc[Player][i].y *= -1;
	    }

        /* Increment the count of asteroids. */
	Acnt[Player] += 2;
	}
}

/***************************************************************************
 *			  Player's Ship Routines                           *
 *                                                                         *
 * NOTE: procedure headers have been excluded on the standard routines,    *
 *   see the corresponding procedure header under the Asteroid routines.   *
 ***************************************************************************/

void InitShip(void)
{
    /* Center ship's position, zero the ship's speed and direction. */
    Spos[Player].x = MAXCOORD >> 1;
    Spos[Player].y = MAXCOORD >> 1;
    Sacc[Player].x = 0;
    Sacc[Player].y = 0;
    Sdir[Player] = 0;
    iShipMode[Player] = INITIALIZE;
    iShipShieldCnt[Player] = SHIELD_ON_TIME;

    /* Set photon count to zero */
    Pcnt[Player] = 0;
}

/***************************************************************************
 * Accelerate                                                              *
 *  - Accelerates player's ship according to the ships direction.  Speed   *
 *    limited to the range between 0 and MAXACC.                           *
 *  - No I/O.                                                              *
 ***************************************************************************/
void Accelerate(void)
{
    Sacc[Player].x += ACC[Sdir[Player]][0] * 3;
    Sacc[Player].x = max(Sacc[Player].x,-1*MAXACC);
    Sacc[Player].x = min(Sacc[Player].x,MAXACC);
    Sacc[Player].y += ACC[Sdir[Player]][1] * 3;
    Sacc[Player].y = max(Sacc[Player].y,-1*MAXACC);
    Sacc[Player].y = min(Sacc[Player].y,MAXACC);
}

/***************************************************************************
 * Hyperspace                                                              *
 *  - Randomly calculates a new position for the ship.  The ship is        *
 *    randomly destroyed 1 out of 8 times.                                 *
 *  - No I/O.                                                              *
 ***************************************************************************/
void Hyperspace(void)
{
    Spos[Player].x = rand() % MAXCOORD;
    Spos[Player].y = rand() % MAXCOORD;
    Sacc[Player].x = 0;
    Sacc[Player].y = 0;

    /* Make the ship blow up randomly, depending on shield energy level. *
     *	 Odds are at best 1/8, worse if the shield is depleted. 	 */
    if (!(rand() % (iShipShieldCnt[Player] / (SHIELD_ON_TIME >> 2) + 4))) {
	iShipMode[Player] = EXPLOSION;
	iShipModeCnt[Player] = EXPLOSION_TIME;
    } else if (prfProfile.bSHIELD) {
	    iShipShieldCnt[Player] = 0;		  /* Empty shield reserves */
    }
}

void UpdateShip(HPS hps, INT iMaxx, INT iMaxy)
{
	   INT  i;
	   LONG dx,dy,d;
    static INT  cFireWait = 0;

    switch (iShipMode[Player]) {
      case INITIALIZE:
	/* Check to see if there any asteroids near the initial ship pos. */
	for (i=0;i<Acnt[Player];i++) {
	    dx = (LONG) (Apos[Player][i].x - Spos[Player].x);
	    dy = (LONG) (Apos[Player][i].y - Spos[Player].y);
	    d  = ((LONG) (12 * ASTEROID_MAX + DIR_MAX));
	    if ((dx * dx + dy * dy) < (d * d))
		i = Acnt[Player]+1;
	    }

	/* If not then go ahead and start the ship. */
	if (i == Acnt[Player]) {
	    iShipMode[Player] = NONE;
	    DrawShip(hps,iMaxx,iMaxy,DRAW_INIT);
	    }
	break;

      case EXPLOSION:
	/* If the ship is (still) exploding then update the explosion */
	if (iShipModeCnt[Player] > 0) {
	    iShipModeCnt[Player]--;
	    ExplodeShip(hps,iMaxx,iMaxy);
	    }

	/* If the enemy ship is off screen then reinit the ship/game, *
	 *   otherwise wait for it to leave.                          */
	else if ((iEnemyMode[Player] == NONE) && (Pcnt[Player] == 0)) {
	    if (--Ships[Player])
		iGameMode = GAME_MODE_NEXT;
	    else
		iGameMode = GAME_MODE_OVER;
	    iGameModeCnt = GAME_PAUSE_TIME;
	    }
	break;

      case HYPERSPACE:
        /* Hyperspace just entered, delete the image of the ship. */
	if (iShipModeCnt[Player] == HYPERSPACE_TIME) {
	    iShipModeCnt[Player]--;
	    DrawShip(hps,iMaxx,iMaxy,DRAW_ERASE);
	    }
        /* If true, ship has exited hyperspace.  Calculate new position. */
	else if (--iShipModeCnt[Player] <= 0) {
	    iShipMode[Player] = NONE;
	    Hyperspace();
	    DrawShip(hps,iMaxx,iMaxy,DRAW_INIT);
	    }
	break;

      default:
	/* Fire a photon if available and if fire rate counter clear*/
	if (iShipMode[Player] & FIREPHOTON) {
	    if ((Pcnt[Player] < prfProfile.iPHOTONS) && (cFireWait-- <= 0)) {
		cFireWait = prfProfile.iFIRERATE;
		InitPhoton();
		}
	    if (!prfProfile.bRAPIDFIRE) {
            	iShipMode[Player] &= ~FIREPHOTON;
		iShipMode[Player] |= FIRERELEASE;
                }
	    }
	else
	    cFireWait = 0;

        /* Normal mode.  Calculate new position of ship. */
	MoveShip(hps);
	iShipShieldCnt[Player] = min(iShipShieldCnt[Player]+1,SHIELD_ON_TIME);

        /* If the ship has moved redraw it.  Otherwise don't bother. */
	if ((Sacc[Player].x != 0) || (Sacc[Player].y != 0) ||
	    (iShipMode[Player] & CLEARNON) || (iShipMode[Player] == SHIELD) ||
            (iShipMode[Player] & EXPLOSION)) {

	    switch (iShipMode[Player]) {
	      case EXPLOSION:
		/* Check for an explosion. */
		DrawShip(hps,iMaxx,iMaxy,DRAW_ERASE);
		break;

	      case SHIELD:
		/* Check for shield on */
		iShipShieldCnt[Player] -= 
                    SHIELD_RATIO_1 + (SHIELD_RATIO_1 * (Level[Player]-1)) / 8;
		if (iShipShieldCnt[Player] < 0)
		    iShipMode[Player] &= CLEARNON;

	      default:
		/* Normal condition. */
		DrawShip(hps,iMaxx,iMaxy,DRAW_REFRESH);
		if (iShipMode[Player] != SHIELD)
		    iShipMode[Player] &= CLEARNON;
		}
	    }
      }
}

void MoveShip(HPS hps)
{
    INT i;
    LONG  dx,dy,d;

    /* Adjust ship's direction and velocity. */
    if (iShipMode[Player] & TURN_LEFT)
	Sdir[Player] = (Sdir[Player] == DIRS-1) ? 0 : ++Sdir[Player];
    if (iShipMode[Player] & TURN_RIGHT)
	Sdir[Player] = (Sdir[Player] == 0) ? DIRS-1 : --Sdir[Player];
    if (iShipMode[Player] & THRUST)
	Accelerate();

    /* Update the ship's position according to the current velocity. */
    Spos[Player].x += Sacc[Player].x>>3;
    Spos[Player].y += Sacc[Player].y>>3;

    /* Check to see if the ship has gone outside the coordinate system, *
     *   if so wrap it back on.                                         */
    if (Spos[Player].x < 0) Spos[Player].x += MAXCOORD;
    else if (Spos[Player].x > MAXCOORD) Spos[Player].x -= MAXCOORD;
    if (Spos[Player].y < 0) Spos[Player].y += MAXCOORD;
    else if (Spos[Player].y > MAXCOORD) Spos[Player].y -= MAXCOORD;

    /* Slowly decelerate the player, automatically. */
    if (Sacc[Player].x > 0)
	Sacc[Player].x -= max(1,Sacc[Player].x/256);
    else if (Sacc[Player].x < 0)
	Sacc[Player].x += max(1,-Sacc[Player].x/256);
    if (Sacc[Player].y > 0)
	Sacc[Player].y -= max(1,Sacc[Player].y/256);
    else if (Sacc[Player].y < 0)
	Sacc[Player].y += max(1,-Sacc[Player].y/256);

    /* Check to see if the player has collided with an asteroid.      *
     * It is important to check here, because the ship moves twice as *
     *	 often as the asteroids.				      */
    if (iShipMode[Player] != SHIELD)
	for (i=0;i<Acnt[Player];i++) {
	    d  = (LONG) (Asiz[Player][i] * ASTEROID_MAX + DIR_MAX);
	    dx = (LONG) (Apos[Player][i].x - Spos[Player].x);

	    /* If the distance is too great vertically or horizontally, *
	     *	 abort the calculation. 				*/
	    if (dx <= d) {
		dy = (LONG) (Apos[Player][i].y - Spos[Player].y);
		if (dy <= d) {
		    if ((dx * dx + dy * dy) < (d * d)) {

			/* Collision!  Update the ship, score, asteroid. */
			iShipMode[Player] = EXPLOSION;
			iShipModeCnt[Player] = EXPLOSION_TIME;
			AddScore(Asiz[Player][i]);
			ExplodeAsteroid(hps,i);

			/* The ship has exploded, terminate the loop. */
			i = Acnt[Player];
			}
		    }
		}
	    }
}

void DrawShip(HPS hps, INT iMaxx, INT iMaxy, INT iMode)
{
	   INT    i;
    static POINTL tmp[SSIDES];
	   LONG   lCenterX,lCenterY,lSizeX,lSizeY;

    switch (iMode) {
      case DRAW_ERASE: case DRAW_REFRESH:
        /* Erase the old image of the ship */
	GpiSetColor(hps,CLR_BLACK);
	GpiMove(hps,&tmp[SSIDES-1]);
	GpiPolyLine(hps,SSIDES,tmp);

	if (iMode == DRAW_ERASE)
	    return;

      case DRAW_INIT:
	/* Set up POINTL array structure for GpiPolyLine */
	lCenterX = (LONG) Spos[Player].x * (LONG) iMaxx;
	lCenterY = (LONG) Spos[Player].y * (LONG) iMaxy;
	lSizeX	 = (LONG) iMaxx  * 3L;
	lSizeY	 = (LONG) iMaxy  * 3L;

        /* Calculate structure for GpiPolyLine. */
	for (i=0;i<SSIDES;i++) {
	    tmp[i].x = (lCenterX + lSizeX *
			(LONG) DIR[Sdir[Player]][i][0]) >> MAXCOORDSHIFT;
	    tmp[i].y = (lCenterY + lSizeY *
			(LONG) DIR[Sdir[Player]][i][1]) >> MAXCOORDSHIFT;
	    }

        /* Draw the new image of the ship. */
	GpiSetColor(hps,CLR_WHITE);
	if (iShipMode[Player] == SHIELD)
	    GpiSetLineType(hps,LINETYPE_ALTERNATE);
	GpiMove(hps,&tmp[SSIDES-1]);
	GpiPolyLine(hps,SSIDES,tmp);
	if (iShipMode[Player] == SHIELD)
	    GpiSetLineType(hps,LINETYPE_DEFAULT);
	}
}

/****************************************************************************
 * ExplodeShip                                                              *
 *  - Simulates the explosion of the ship.                                  *
 *    ExplodeShip is called in place of MoveShip and DrawShip.              *
 *  - HPS and size of screen.                                               *
 ****************************************************************************/
void ExplodeShip(HPS hps, INT iMaxx, INT iMaxy)
{
	   INT  i;
    static POINTL tmp[6];
    static BOOL   bInit = TRUE;

    /* Is this the first tick in which the ship is exploding?  *
     * If so, initialize all of the necessary data structures. */
    if (bInit) {
	LONG   lCenterX,lCenterY,lSizeX,lSizeY;

	bInit = FALSE;
	lCenterX = (LONG) Spos[Player].x * (LONG) iMaxx;
	lCenterY = (LONG) Spos[Player].y * (LONG) iMaxy;
	lSizeX	 = (LONG) iMaxx  * 3L;
	lSizeY	 = (LONG) iMaxy  * 3L;

	for (i=0;i<3;i++) {
	    tmp[i*2].x = (lCenterX + lSizeX *
			  (LONG) DIR[Sdir[Player]][i][0]) >> MAXCOORDSHIFT;
	    tmp[i*2].y = (lCenterY + lSizeY *
			  (LONG) DIR[Sdir[Player]][i][1]) >> MAXCOORDSHIFT;
	    }
	tmp[1].x = tmp[2].x;tmp[1].y = tmp[2].y;
	tmp[3].x = tmp[4].x;tmp[3].y = tmp[4].y;
	tmp[5].x = tmp[0].x;tmp[5].y = tmp[0].y;
	}

    /* Erase previous explosion image */
    GpiSetColor(hps,CLR_BLACK);
    for (i=0;i<6;i+=2) {
       GpiMove(hps,&tmp[i]);
       GpiLine(hps,&tmp[i+1]);
	}

    /* Is the ship exploding?  Yes, update shard positions and plot image. */
    if (iShipModeCnt[Player] != 0) {
	for (i=0;i<6;i++) {
	    tmp[i].x += smax(((LONG)iMaxx *
		(LONG)DIR[Sdir[Player]][i/2][0] * 200L) >> MAXCOORDSHIFT,1L);
	    tmp[i].y += smax(((LONG)iMaxy *
		(LONG)DIR[Sdir[Player]][i/2][1] * 200L) >> MAXCOORDSHIFT,1L);
	    }

	GpiSetColor(hps,CLR_WHITE);
	for (i=0;i<6;i+=2) {
	    GpiMove(hps,&tmp[i]);
	    GpiLine(hps,&tmp[i+1]);
	    }
	}
    /* No, set up flag for next explosion. */
    else
	bInit = TRUE;
}


/***************************************************************************
 *			    Enemy Ship Routines 			   *
 *                                                                         *
 * NOTE: procedure headers have been excluded on the standard routines,    *
 *   see the corresponding procedure header under the Asteroid routines.   *
 ***************************************************************************/

void InitEnemy(void)
{
    /* If this is the first level then the enemy ship is always large */
    if (Level[Player] == 1)
	Esiz[Player] = 2;
    /*	 else, progressively make it more likely for it to be small.  */
    else {
	Esiz[Player] = rand() % Level[Player] + 1;
	if (Esiz[Player] > 2)
	    Esiz[Player] = 1;
	}

    /* Randomly determine the direction from which the enemy will appear. */
    if (rand() % 2) {
	Epos[Player].x = MAXCOORD;
	Eacc[Player].x = -MAXCOORD / 192;
	}
    else {
	Epos[Player].x = 0;
	Eacc[Player].x = MAXCOORD / 192;
	}
    Epos[Player].y = rand() % MAXCOORD;

    /* Find a vertical velocity. */
    Eacc[Player].y = ASPEEDS[rand() % SPEEDS];

    /* Set up for wait before appearance on screen. */
    iEnemyMode[Player] = NONE;
    iEnemyModeCnt[Player] = (rand() % 100) + 200;

    /* Make sure there are no enemy photons left */
    Pdst[Player][0] = MAXPHOTONDIST;
}

void UpdateEnemy(HPS hps, INT iMaxx, INT iMaxy)
{
    switch (iEnemyMode[Player]) {
      case NONE:
	/* Decrement wait til appearance of enemy ship */
	if (--iEnemyModeCnt[Player] == 0) {
	    /* Start enemy ship */
	    iEnemyMode[Player] = THRUST;
	    /* Set up wait for next change in direction */
	    iEnemyModeCnt[Player] = rand()%(Esiz[Player]*64);
	    DrawEnemy(hps,iMaxx,iMaxy,DRAW_INIT);
	    }
	break;

      case EXPLOSION:
	/* Erase image/progress explosion/restart enemy from wait */
	if (iEnemyModeCnt[Player]-- == EXPLOSION_TIME)
	    /* Erase Enemy ship image */
	    DrawEnemy(hps,iMaxx,iMaxy,DRAW_ERASE);
	if (iEnemyModeCnt[Player] >= 0)
	    /* Continue explosion */
	    ExplodeEnemy(hps,iMaxx,iMaxy);
	else
	    /* Explosion finished start enemy wait */
	    InitEnemy();

	break;

      case THRUST:
	/* Does enemy ship need to turn? */
	if (--iEnemyModeCnt[Player] == 0) {
	    /* Yes, find new Y-speed */
	    Eacc[Player].y = ASPEEDS[rand() % SPEEDS];
	    /* Set up for next change */
	    iEnemyModeCnt[Player] = rand()%(Esiz[Player]*64);
	    }

	/* Move and redraw enemy ship's image */
	MoveEnemy(hps);
	if (iEnemyMode[Player] == THRUST)
	    DrawEnemy(hps,iMaxx,iMaxy,DRAW_REFRESH);
	else
	    DrawEnemy(hps,iMaxx,iMaxy,DRAW_ERASE);
      }
}

void MoveEnemy(HPS hps)
{
    int i;
    LONG dx,dy,d;

    /* Increment X position, exit if off the side of the screen */
    Epos[Player].x += Eacc[Player].x;Epos[Player].y += Eacc[Player].y;
    if (Epos[Player].y < 0) Epos[Player].y += MAXCOORD;
    else if (Epos[Player].y > MAXCOORD) Epos[Player].y -= MAXCOORD;

    /* Is the enemy ship still on screen? */
    if ((Epos[Player].x > MAXCOORD) || (Epos[Player].x < 0))
	/* No, reinitialize it */
	InitEnemy();
    else {
	/* Check for a collision with any of the asteroids */
	for (i=0;i<Acnt[Player];i++) {
	    d  = (LONG) (Asiz[Player][i] * ASTEROID_MAX +
		 Esiz[Player] * ENEMY_MAX);
	    dx = (LONG) (Apos[Player][i].x - Epos[Player].x);
	    if (dx <= d) {
		dy = (LONG) (Apos[Player][i].y - Epos[Player].y);
		if (dy <= d) {
		    if ((dx * dx + dy * dy) < (d * d)) {
			iEnemyMode[Player] = EXPLOSION;
			iEnemyModeCnt[Player] = EXPLOSION_TIME;
			ExplodeAsteroid(hps,i);
			i = Acnt[Player];
			}
		    }
		}
	    }

	/* Check for a collision with the player's ship.  Cannot occur if *
	 *   the player is already exploding, shielded, or hyperspacing.  */
	if ((iGameMode == GAME_MODE_PLAY) &&
	    (iShipMode[Player] != EXPLOSION) &&
	    (iShipMode[Player] != HYPERSPACE) &&
	    (iShipMode[Player] != SHIELD)) {
	    dx = (LONG) (Spos[Player].x - Epos[Player].x);
	    dy = (LONG) (Spos[Player].y - Epos[Player].y);
	    d  = (LONG) (Esiz[Player] * ENEMY_MAX + DIR_MAX);
	    if ((dx * dx + dy * dy) < (d * d)) {
		iEnemyMode[Player] = EXPLOSION;
		iEnemyModeCnt[Player] = EXPLOSION_TIME;
		iShipMode[Player] = EXPLOSION;
		iShipModeCnt[Player] = EXPLOSION_TIME;
		AddScore((Esiz[Player] == 1) ? ENEMY_S : ENEMY_L);
		}
	    }
	}

}

void DrawEnemy(HPS hps, INT iMaxx, INT iMaxy, INT iMode)
{
	   INT  i;
    static POINTL tmp[ESIDES];
	   LONG   lCenterX,lCenterY,lSizeX,lSizeY;

    switch (iMode) {
      case DRAW_ERASE: case DRAW_REFRESH:
	/* Erase last image of enemy ship */
	GpiSetColor(hps,CLR_BLACK);
	GpiMove(hps,&tmp[3]);
	GpiPolyLine(hps,ESIDES,tmp);

	if (iMode == DRAW_ERASE)
	    return;

      case DRAW_INIT:
	/* Set up POINTL array structure for GpiPolyLine */
	lCenterX = (LONG) Epos[Player].x * (LONG) iMaxx;
	lCenterY = (LONG) Epos[Player].y * (LONG) iMaxy;
	lSizeX	 = (LONG) Esiz[Player]	 * (LONG) iMaxx;
	lSizeY	 = (LONG) Esiz[Player]	 * (LONG) iMaxy;

	for (i=0;i<ESIDES;i++) {
	    tmp[i].x = (lCenterX + lSizeX *
		(LONG) ENEMY[i][0]) >> MAXCOORDSHIFT;
	    tmp[i].y = (lCenterY + lSizeY *
		(LONG) ENEMY[i][1]) >> MAXCOORDSHIFT;
	    }

        /* Draw new image. */
	GpiSetColor(hps,CLR_WHITE);
	GpiMove(hps,&tmp[3]);
	GpiPolyLine(hps,ESIDES,tmp);
	}
}

void ExplodeEnemy(HPS hps, INT iMaxx, INT iMaxy)
{
    static BOOL   bInit = TRUE;
    static POINTL ptlShpos[16];
    static POINTL ptlShacc[16];
    static POINTL ptl[16];
	   INT  i;


    /* Erase last shard position */
    if (!bInit) {
	GpiSetColor(hps,CLR_BLACK);
	for (i=0;i<16;i++)
	    GpiSetPel(hps,&ptl[i]);
	}
    /* Initialize enemy ship explosion */
    else {
	bInit = FALSE;
	for (i=0;i<16;i++) {
	    ptlShpos[i].x = Epos[Player].x;
	    ptlShpos[i].y = Epos[Player].y;
	    ptlShacc[i].x = ASPEEDS[rand() % SPEEDS];
	    ptlShacc[i].y = ASPEEDS[rand() % SPEEDS];
            }
	}


    /* If explosion is not over then recalc/redraw shards */
    if (iEnemyModeCnt[Player] != 0) {
        GpiSetColor(hps,CLR_WHITE);
	for (i=0;i<16;i++) {
	    ptlShpos[i].x += ptlShacc[i].x;
	    ptlShpos[i].y += ptlShacc[i].y;
	    ptlShacc[i].x -= ptlShacc[i].x / 16;
	    ptlShacc[i].y -= ptlShacc[i].y / 16;

	    if (ptlShpos[i].x < 0) ptlShpos[i].x += MAXCOORD;
	    else if (ptlShpos[i].x > MAXCOORD) ptlShpos[i].x -= MAXCOORD;
	    if (ptlShpos[i].y < 0) ptlShpos[i].y += MAXCOORD;
	    else if (ptlShpos[i].y > MAXCOORD) ptlShpos[i].y -= MAXCOORD;

	    ptl[i].x = ((LONG) ptlShpos[i].x * (LONG) iMaxx) >> MAXCOORDSHIFT;
	    ptl[i].y = ((LONG) ptlShpos[i].y * (LONG) iMaxy) >> MAXCOORDSHIFT;

	    GpiSetPel(hps,&ptl[i]);
            }
	}
    /*	 otherwise set up for reinitialization on next explosion */
    else
	bInit = TRUE;
}

/***************************************************************************
 *			     Photon Routines				   *
 *                                                                         *
 * NOTE: procedure headers have been excluded on the standard routines,    *
 *   see the corresponding procedure header under the Asteroid routines.   *
 ***************************************************************************/

/* Sets photon count to zero for current player */
void DeletePhotons(void)
{
    Pcnt[Player] = 0;
}

void InitPhoton(void)
{
    /* Set up photon position, speed, and direction, according to ship. */
    Pcnt[Player]++;
    Pdst[Player][Pcnt[Player]] = 0;
    Ppos[Player][Pcnt[Player]].x = Spos[Player].x;
    Ppos[Player][Pcnt[Player]].y = Spos[Player].y;
    Pacc[Player][Pcnt[Player]].x = ACC[Sdir[Player]][0]*8 + Sacc[Player].x/16;
    Pacc[Player][Pcnt[Player]].y = ACC[Sdir[Player]][1]*8 + Sacc[Player].y/16;
}

void InitEnemyPhoton(void)
{
    INT  i;
    BOOL bShootPlayer;

    /* Set distance photon has traveled to 0, set initial position */
    Pdst[Player][0] = 0;
    Ppos[Player][0].x = Epos[Player].x;
    Ppos[Player][0].y = Epos[Player].y;

    /* If this is a small enemy ship and its not its first shot, aim     */
    /* for the player's ship based on the following:			 */
    /*     - current enemy ship position				 */
    /*     - current player's ship position				 */
    /*     - player's ship's current velocity (in x/y)			 */
    /*     - photon velocity						 */
    /* If the player's ship isn't visible, this is the first shot, or    */
    /* the current level is greater than 2 aim for an asteroid.		 */
    bShootPlayer = (iGameMode == GAME_MODE_PLAY) &&
		    (iShipMode[Player] != HYPERSPACE) &&
		    (iShipMode[Player] != EXPLOSION) &&
		    (Epos[Player].x != 0) && (Epos[Player].x != MAXCOORD);
    if (   (Esiz[Player] == 1)
	&& (   bShootPlayer
	    || ((Level[Player] > 2) && (Acnt[Player] > 0)))) {   
	LONG approx, delta = MAXINT, ndelta;
	LONG ax, sx, pdx, dx, ay, sy, pdy, dy;

	/* If player's ship is a valid target (visible and not the first */
	/* shot, aim for it					         */
	if (bShootPlayer) {
	    /* Ship's speed is scaled by 8 (for smooth deceleration) */
	    ax = Sacc[Player].x>>3;
	    ay = Sacc[Player].y>>3;
	    sx = Spos[Player].x;
	    sy = Spos[Player].y;
	/* Otherwise, pick an asteroid at random and aim for it */
	} else /* Level[Player] > 2 */ {
	    i = rand() % Acnt[Player];
	    ax = Aacc[Player][i].x;
	    ay = Aacc[Player][i].y;
	    sx = Apos[Player][i].x;
	    sy = Apos[Player][i].y;
	    /* Asteroids normally move half as often as photons */
	    if (uiSpeed != SPEED_OS2)
		ax >>= 1;
		ay >>= 1;
	    }

	/* Find intersection point (best guess based on player's current    */
	/* position, velocity, and enemy ship's position.		    */
	/* This algorithm iteratively searches for the intersection between */
	/* the (as yet unknown) photon vector and the player's ship vector. */
	for (i = 1, approx = 0; i < MAXPHOTONDIST; i++, approx += 400) {
            sx += ax;
	    sy += ay;

	    /* Get distance/guess for next time interval */
	    if (abs(dx = sx - Epos[Player].x) > MAXCOORD2)
		dx -= sgn(dx)*MAXCOORD;
	    if (abs(dy = sy - Epos[Player].y) > MAXCOORD2)
		dy -= sgn(dy)*MAXCOORD;
	    ndelta = abs(isqrt(dx*dx + dy*dy) - approx);

	    /* If the last guess was better than the current one, then it */
	    /* was the intersection.					  */
	    if (delta <= ndelta)
		break;

	    /* Save values for current interval/guess */
	    delta = ndelta;
	    pdx = dx;pdy = dy;
	    }

	/* Interpolate x/y velocities based on the distance from the current */
	/* position to the intersection point and the number of updates      */
	/* needed to get there.						     */
	/* If delta > 400 the player is too far away, resort to a random     */
	/* shot.							     */
	if (delta <= 400) {
	    Pacc[Player][0].x = pdx/(i-1);
	    Pacc[Player][0].y = pdy/(i-1);
	    return;
	    }
        }

	/* For large enemy ships, the first shot for small enemy ships, or */
	/* a guaranteed miss, randomly choose a direction and fire.	   */
	i = rand() % DIRS;
	Pacc[Player][0].x = ACC[i][0]*8;
	Pacc[Player][0].y = ACC[i][1]*8;
}

void UpdatePhotons(HPS hps, INT iMaxx, INT iMaxy)
{
    MovePhotons(hps);
    DrawPhotons(hps,iMaxx,iMaxy,DRAW_REFRESH);
}

void MovePhotons(HPS hps)
{
    INT i,j;
    LONG  dx,dy,d;

    /* The enemy shoots photon 0, if the enemy has fired then update photon *
     *   0, otherwise start with 1.                                         */
    i = ((iEnemyMode[Player] == NONE) &&
         (Pdst[Player][0] == MAXPHOTONDIST)) ? 1 : 0;

    for (;i<=Pcnt[Player];i++) {

        /* Has the current photon gone out of range? */
	if (++Pdst[Player][i] > MAXPHOTONDIST) {

            /* If the photon is the enmey photon, start the next one. */
	    if ((!i) && (iEnemyMode[Player] != NONE))
		InitEnemyPhoton();
            /* Otherwise, delete the players photon and clean up the list. */
	    else if (i < Pcnt[Player]--) {
		Pdst[Player][i]   = Pdst[Player][Pcnt[Player]+1];
		Ppos[Player][i].x = Ppos[Player][Pcnt[Player]+1].x;
		Ppos[Player][i].y = Ppos[Player][Pcnt[Player]+1].y;
		Pacc[Player][i].x = Pacc[Player][Pcnt[Player]+1].x;
		Pacc[Player][i].y = Pacc[Player][Pcnt[Player]+1].y;
		}
	    }

        /* Photon is still in valid range. */
        else {
            /* Calculate new postion. */
	    Ppos[Player][i].x += Pacc[Player][i].x;
	    Ppos[Player][i].y += Pacc[Player][i].y;

            /* Make sure position is within coordinate system, else wrap. */
	    if (Ppos[Player][i].x < 0)
		Ppos[Player][i].x += MAXCOORD;
	    else if (Ppos[Player][i].x > MAXCOORD)
		Ppos[Player][i].x -= MAXCOORD;
	    if (Ppos[Player][i].y < 0)
		Ppos[Player][i].y += MAXCOORD;
	    else if (Ppos[Player][i].y > MAXCOORD)
		Ppos[Player][i].y -= MAXCOORD;

            /* Check to see if the photon hit an asteroid. */
	    for (j=0;j<Acnt[Player];j++) {
		d  = (LONG) (Asiz[Player][j] * ASTEROID_MAX) + 3L;
		dx = (LONG) (Apos[Player][j].x - Ppos[Player][i].x);
		if (dx <= d) {
		    dy = (LONG) (Apos[Player][j].y - Ppos[Player][i].y);
		    if (dy <= d) {
			if ((dx * dx + dy * dy) < (d * d)) {
			    Pdst[Player][i] = MAXPHOTONDIST;

                            /* If the photon was fired by the enemy, don't *
                             *   update the player's score.                */
			    if (i != 0)
				AddScore(Asiz[Player][j]);
			    ExplodeAsteroid(hps,j);
			    j = Acnt[Player];
			    }
			}
		    }
		}

            /* If the current photon was enemy fired, the game is in normal *
	     *	 play mode, and the ship is not exploding, shielded, or in  *
	     *	 hyperspace, check for a hit.				    */
	    if ((i == 0) && (iGameMode == GAME_MODE_PLAY) &&
		(iShipMode[Player] != EXPLOSION) &&
		(iShipMode[Player] != HYPERSPACE) &&
		(iShipMode[Player] != SHIELD)) {
		dx = (LONG) (Spos[Player].x - Ppos[Player][0].x);
		dy = (LONG) (Spos[Player].y - Ppos[Player][0].y);
		d  = (LONG) DIR_MAX + 3L;
		if ((dx * dx + dy * dy) < (d * d)) {
		    Pdst[Player][0] = MAXPHOTONDIST;
		    iShipMode[Player] = EXPLOSION;
		    iShipModeCnt[Player] = EXPLOSION_TIME;
		    }
		}

            /* Check player photons to see if they hit the enemy. */
	    if ((i) && (iEnemyMode[Player] == THRUST)) {
		dx = (LONG) (Epos[Player].x - Ppos[Player][i].x);
		dy = (LONG) (Epos[Player].y - Ppos[Player][i].y);
		d  = (LONG) (Esiz[Player] * ENEMY_MAX) + 3L;
		if ((dx * dx + dy * dy) < (d * d)) {
		    Pdst[Player][i] = MAXPHOTONDIST;
		    AddScore((Esiz[Player] == 1) ? ENEMY_S : ENEMY_L);
		    iEnemyMode[Player] = EXPLOSION;
		    iEnemyModeCnt[Player] = EXPLOSION_TIME;
		    }
		}
	    }
	}
}

void DrawPhotons(HPS hps, INT iMaxx, INT iMaxy, INT iMode)
{
    static INT    i = 0;
    static INT    j = 0;
    static POINTL tmp[MAXPHOTONS+1];

    switch (iMode) {
      case DRAW_ERASE: case DRAW_REFRESH:
        /* Erase old photon images */
	GpiSetColor(hps,CLR_BLACK);
	for (;i<j;i++)
	    GpiSetPel(hps,&tmp[i]);

	if (iMode == DRAW_ERASE)
	    return;

      case DRAW_INIT:
        /* The enemy shoots photon 0, if the enemy has fired then update *
         *   photon 0, otherwise start with 1.                           */
	j = ((iEnemyMode[Player] == NONE) &&
	     (Pdst[Player][0] == MAXPHOTONDIST)) ? 1 : 0;i=j;

        /* Draw new photon images. */
	GpiSetColor(hps,CLR_WHITE);
	for (;j<=Pcnt[Player];j++) {
	    tmp[j].x = ((LONG) Ppos[Player][j].x *
			(LONG) iMaxx) >> MAXCOORDSHIFT;
	    tmp[j].y = ((LONG) Ppos[Player][j].y *
			(LONG) iMaxy) >> MAXCOORDSHIFT;
	    GpiSetPel(hps,&tmp[j]);
	    }
	}
}
