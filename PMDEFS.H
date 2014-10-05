/* PM defined constants */
#define ASTEROID_VER	  "ASTEROID 2.30"

#define ID_RESOURCE	  1
#define ID_OBJECT	  2
#define ID_TIMER	  3
#define ID_HELPTABLE	  4

#define ID_CLIENTWND	  ID_RESOURCE
#define IDD_ABOUT	  2
#define IDD_KEY 	  3

#define IDM_GAME	  5
#define IDM_START	  10
#define IDM_START1	  11	    /* These values, relative to IDM_START, */
#define IDM_START2	  12	    /* 	 are important to the program       */
#define IDM_FRAME	  13
#define IDM_BACKGRND	  14
#define IDM_PAUSE	  15
#define IDM_STOP	  16
#define IDM_EXIT	  17

#define IDM_OPTION	  18

#define IDM_SHIPS	  20
#define IDM_3SHIPS	  23	    /* These values, relative to IDM_SHIPS, */
#define IDM_4SHIPS	  24	    /*	 are important to the program       */
#define IDM_5SHIPS	  25

#define IDM_PHOTONS	  30
#define IDM_3PHOTONS	  33	    /* These values, relative to IDM_PHOTONS,*/
#define IDM_4PHOTONS	  34	    /*	 are important to the program        */
#define IDM_6PHOTONS	  36
#define IDM_8PHOTONS	  38
#define IDM_RAPIDFIRE	  40

#define IDM_FIRERATE	  50
#define IDM_FASTRATE	  52	    /* These values, relative to IDM_FIRERATE,*/
#define IDM_MEDRATE	  54	    /*	 are important to the program         */
#define IDM_SLOWRATE	  58

#define IDM_SHIELD	  70
#define IDM_MOUSE	  71
#define IDM_KEYS	  72

#define IDM_HELPMENU	  80
#define IDM_HELPFORHELP   81
#define IDM_EXTENDEDHELP  82
#define IDM_KEYSHELP	  83
#define IDM_HELPINDEX	  84
#define IDM_ABOUT	  85

/* Help window defines */
#define IDH_CLIENT	  1
#define IDH_CLIENTEXTEND  2
#define IDH_CLIENTKEYS	  3
#define IDH_GAME	  100
#define IDH_START	  110
#define IDH_FRAME	  120
#define IDH_BACKGRND	  121
#define IDH_PAUSE	  122
#define IDH_STOP	  123
#define IDH_EXIT	  124
#define IDH_OPTION	  200
#define IDH_SHIPS	  210
#define IDH_PHOTONS	  220
#define IDH_RAPIDFIRE	  230
#define IDH_FIRERATE	  240
#define IDH_SHIELD	  250
#define IDH_MOUSE	  260
#define IDH_KEYS	  270
#define IDH_HELPMENU	  300
#define IDH_HELPFORHELP   310
#define IDH_EXTENDEDHELP  311
#define IDH_KEYSHELP	  312
#define IDH_HELPINDEX	  313
#define IDH_ABOUT	  320

#define KEY_LEFT	  10	    /* Key definitions dialog box */
#define KEY_RIGHT	  11
#define KEY_THRUST	  12
#define KEY_HYPER	  13
#define KEY_FIRE	  14
#define KEY_SHIELD	  15
#define KEY_HELP	  16
#define TEXT_LEFT	  20
#define TEXT_RIGHT	  21
#define TEXT_THRUST	  22
#define TEXT_HYPER	  23
#define TEXT_FIRE	  24
#define TEXT_SHIELD	  25


/* TogglePause options */
#define TOGGLE		  0
#define CHECK		  1
#define SUSPEND_ON	  2
#define SUSPEND_OFF	  3
#define FORCE_PAUSE	  4
#define FORCE_UNPAUSE	  5

#ifndef IPFC
/* Virtual key table */
#define MAXVKEY 43
struct {
  SHORT code;
  CHAR	name[10];
  } VKEY[MAXVKEY] = {
    0x01, "Button1  ", 0x02, "Button2  ", 0x03, "Button3  ",
    0x04, "Break    ", 0x05, "Backspace", 0x06, "Tab      ",
    0x07, "Backtab  ", 0x08, "Return   ", 0x09, "Shift    ",
    0x0A, "Ctrl     ", 0x0B, "Alt      ", 0x0C, "Altgraf  ",
    0x0D, "Pause    ", 0x0E, "Caps Lock", 0x0F, "Esc      ",
    0x10, "Space    ", 0x11, "Page Up  ", 0x12, "Page Down",
    0x13, "End      ", 0x14, "Home     ", 0x15, "Left     ",
    0x16, "Up       ", 0x17, "Right    ", 0x18, "Down     ",
    0x19, "PrintScrn", 0x1A, "Insert   ", 0x1B, "Delete   ",
    0x1C, "ScrlLock ", 0x1D, "Num Lock ", 0x1E, "Enter    ",
    0x1F, "SysRq    ", 0x20, "F1       ", 0x21, "F2       ",
    0x22, "F3       ", 0x23, "F4       ", 0x24, "F5       ",
    0x25, "F6       ", 0x26, "F7       ", 0x27, "F8       ",
    0x28, "F9       ", 0x29, "F10      ", 0x30, "F11      ",
    0x31, "F12      " };


#define WM_INITGAME	  WM_USER
#define WM_STARTGAME	  WM_USER+1

/* Macros */
#define EnableMenuItem(hwnd,idm,b) \
	    WinSendMsg(hwnd, MM_SETITEMATTR, \
		       MPFROM2SHORT(idm, TRUE), \
		       MPFROM2SHORT(MIA_DISABLED, (b) ? 0 : MIA_DISABLED))
#define CheckMenuItem(hwnd,idm,b) \
	    WinSendMsg(hwnd, MM_SETITEMATTR, \
		       MPFROM2SHORT(idm, TRUE), \
		       MPFROM2SHORT(MIA_CHECKED, (b) ? MIA_CHECKED : 0))

/* External procedures */
MRESULT EXPENTRY ClientWndProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY AboutDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY HelpDlgProc(HWND, ULONG, MPARAM, MPARAM);
MRESULT EXPENTRY KeyDlgProc(HWND, ULONG, MPARAM, MPARAM);
#endif
