/****************************************************************************
 * LANG.H                                                                   *
 *                                                                          *
 *  Language tables for ASTEROID.  Only ASCII characters may be used: the    *
 *  in-game display uses custom bitmap fonts with a limited character set    *
 *  and the source files must stay pure ASCII + CRLF.  Accents are spelled   *
 *  out (e.g. "Espanol", "APPTYEZ"), umlauts use ae/oe/ue transliteration.   *
 ****************************************************************************/

/* Languages */
#define LANG_ENGLISH	0
#define LANG_GERMAN	1
#define LANG_SPANISH	2
#define LANG_DUTCH	3
#define LANG_FRENCH	4
#define LANG_COUNT	5

/* String identifiers, kept in menu order first (see ApplyLanguage) */
enum {
    STR_MENU_GAME=0, STR_MENU_NEW, STR_MENU_1PLAYER, STR_MENU_2PLAYER,
    STR_MENU_FRAME, STR_MENU_BACKGRND, STR_MENU_PAUSE, STR_MENU_STOP,
    STR_MENU_EXIT, STR_MENU_OPTIONS, STR_MENU_SHIPS, STR_MENU_PHOTONS,
    STR_MENU_RAPIDFIRE, STR_MENU_FIRERATE, STR_MENU_SLOW, STR_MENU_MEDIUM,
    STR_MENU_FAST, STR_MENU_SHIELD, STR_MENU_MOUSE, STR_MENU_KEYS,
    STR_MENU_LANGUAGE, STR_MENU_HELP, STR_MENU_HELPFORHELP,
    STR_MENU_EXTENDEDHELP, STR_MENU_KEYSHELP, STR_MENU_HELPINDEX,
    STR_MENU_ABOUT,
    STR_ABOUT_BY, STR_ABOUT_OK, STR_ABOUT_EXIT,
    STR_KEYS_CAPTION, STR_KEYS_SEL1, STR_KEYS_SEL2, STR_KEYS_LEFT,
    STR_KEYS_RIGHT, STR_KEYS_THRUST, STR_KEYS_HYPER, STR_KEYS_FIRE,
    STR_KEYS_SHIELD, STR_KEYS_OK, STR_KEYS_CANCEL,
    STR_ERR_DLL1, STR_ERR_DLL2, STR_ERR_HLP1, STR_ERR_HLP2,
    STR_HS_TABLE, STR_PRESS1, STR_PRESS2, STR_GAMEOVER, STR_PLAYER,
    STR_HS_1, STR_HS_2, STR_HS_3, STR_HS_4,
    STR_COUNT
};

/* Current language (English by default) */
extern INT uiLang;

#ifdef MAIN
CHAR *apLang[LANG_COUNT][STR_COUNT] = {
  {
    /* English */
    "~Game", "~New", "~1 Player Game\t1", "~2 Player Game\t2",
    "~Frame Controls\t^F", "~Background\t^B", "~Pause Game\t^P",
    "S~top Game", "E~xit\tF3", "~Options", "~Ships", "~Photons",
    "~Rapid Fire", "~Fire Rate", "~Slow", "~Medium", "~Fast",
    "S~hield", "~Mouse\t^M", "Keys...\t^K", "~Language",
    "~Help", "~Help for help...", "~Extended help...", "~Keys help...",
    "Help ~index...", "~About...",
    "BY", "OK", "EXIT",
    "Key Definitions", "Select key to change, then",
    "press new key combination.", "Turn Left", "Turn Right", "Thrust",
    "Hyperspace", "Fire", "Shield", "Ok", "Cancel",
    "Please put ASTEROID.DLL in a directory in your LIBPATH.",
    "Error reading ASTEROID.DLL",
    "Please put ASTEROID.HLP in a directory pointed to by the HELP "
    "environment variable or in the ASTEROID working directory.",
    "Could not find help file",
    "HIGH SCORES", "PRESS 1 OR 2", "TO START GAME", "GAME OVER",
    "PLAYER %d",
    "YOUR SCORE IS ONE OF THE TEN BEST",
    "PLEASE ENTER YOUR INITIALS",
    "PUSH ROTATE TO SELECT LETTER",
    "PUSH HYPERSPACE WHEN LETTER IS CORRECT"
  },
  {
    /* Deutsch */
    "~Spiel", "~Neu", "~1-Spieler-Spiel\t1", "~2-Spieler-Spiel\t2",
    "~Rahmensteuerung\t^F", "~Hintergrund\t^B", "~Pause\t^P",
    "Spiel st~oppen", "~Beenden\tF3", "~Optionen", "S~chiffe",
    "~Photonen", "~Dauerfeuer", "Feuer~rate", "~Langsam", "~Mittel",
    "~Schnell", "~Schild", "~Maus\t^M", "T~asten...\t^K",
    "Sp~rache", "~Hilfe", "Hil~fe zur Hilfe...", "~Erweiterte Hilfe...",
    "T~astenhilfe...", "Hilfe~index...", "~Info...",
    "VON", "OK", "BEENDEN",
    "Tastenzuordnung", "Zum Aendern Taste waehlen,",
    "dann neue Taste druecken.", "Nach links drehen",
    "Nach rechts drehen", "Antrieb", "Hyperraum", "Feuern", "Schild",
    "OK", "Abbrechen",
    "Bitte legen Sie ASTEROID.DLL in ein Verzeichnis Ihrer "
    "LIBPATH-Einstellung.",
    "Fehler beim Lesen von ASTEROID.DLL",
    "Bitte legen Sie ASTEROID.HLP in ein Verzeichnis, auf das die "
    "HELP-Umgebungsvariable zeigt, oder in das Verzeichnis von ASTEROID.",
    "Hilfedatei nicht gefunden",
    "RANGLISTE", "DRUECKE 1 ODER 2", "ZUM SPIELSTART", "SPIEL VORBEI",
    "SPIELER %d",
    "IHRE PUNKTZAHL IST UNTER DEN BESTEN",
    "BITTE GEBEN SIE IHRE INITIALEN EIN",
    "DREHEN ZUM WAEHLEN DES BUCHSTABENS",
    "HYPERSPACE BEI RICHTIGEM BUCHSTABEN"
  },
  {
    /* Espanol */
    "~Juego", "~Nuevo", "~1 Jugador\t1", "~2 Jugadores\t2",
    "~Marco\t^F", "~Fondo\t^B", "~Pausa\t^P", "D~etener",
    "~Salir\tF3", "~Opciones", "~Naves", "~Fotones", "~Tiro Rapido",
    "Velocidad de ~disparo", "~Lento", "~Medio", "~Rapido",
    "~Escudo", "~Raton\t^M", "T~eclas...\t^K", "~Idioma",
    "~Ayuda", "Ay~uda para ayuda...", "Ayuda e~xtendida...",
    "Ayuda de te~clas...", "Ayuda in~dice...", "~Acerca de...",
    "POR", "ACEPTAR", "SALIR",
    "Definicion de Teclas", "Elija la tecla a cambiar,",
    "luego presione la nueva.", "Girar a la izquierda",
    "Girar a la derecha", "Propulsion", "Hiperespacio", "Disparar",
    "Escudo", "Aceptar", "Cancelar",
    "Ponga ASTEROID.DLL en un directorio de su LIBPATH.",
    "Error al leer ASTEROID.DLL",
    "Ponga ASTEROID.HLP en un directorio indicado por la variable "
    "HELP o en el directorio de trabajo de ASTEROID.",
    "No se encontro el archivo de ayuda",
    "MEJORES PUNTUACIONES", "PULSA 1 O 2", "PARA EMPEZAR",
    "FIN DE PARTIDA", "JUGADOR %d",
    "SU PUNTUACION ESTA ENTRE LAS MEJORES",
    "POR FAVOR ESCRIBA SUS INICIALES",
    "GIRE PARA SELECCIONAR LA LETRA",
    "PULSE HIPERESPACIO SI LETRA CORRECTA"
  },
  {
    /* Nederlands */
    "~Spel", "~Nieuw", "~1 Speler\t1", "~2 Spelers\t2",
    "~Frame besturing\t^F", "~Achtergrond\t^B", "~Pauze\t^P",
    "Spel st~oppen", "Afsl~uiten\tF3", "~Opties", "~Schepen",
    "~Fotonen", "S~nelvuur", "Vu~urtempo", "~Langzaam", "~Gemiddeld",
    "~Snel", "Sc~hild", "~Muis\t^M", "T~oetsen...\t^K", "~Taal",
    "~Handleiding", "~Handleiding voor hulp...",
    "~Uitgebreide handleiding...", "Toetsenh~ulp...",
    "Hand~leidingsindex...", "~Over...",
    "DOOR", "OK", "AFSLUITEN",
    "Toetsen definieren", "Kies de te wijzigen toets,",
    "druk dan de nieuwe in.", "Naar links draaien",
    "Naar rechts draaien", "Aandrijving", "Hyperruimte", "Vuren",
    "Schild", "OK", "Annuleren",
    "Zet ASTEROID.DLL in een map in uw LIBPATH.",
    "Fout bij het lezen van ASTEROID.DLL",
    "Zet ASTEROID.HLP in een map die wordt aangewezen door de "
    "HELP-omgevingsvariabele of in de ASTEROID-werkmap.",
    "Hulpbestand niet gevonden",
    "HOOGSTE SCORES", "DRUK OP 1 OF 2", "OM TE STARTEN",
    "SPEL AFGELOPEN", "SPELER %d",
    "UW SCORE IS EEN VAN DE TIEN BESTE",
    "VUL ALSTUBLIEFT UW INITIALEN IN",
    "DRAAI OM EEN LETTER TE KIEZEN",
    "DRUK HYPERSPACE ALS DE LETTER KLOPT"
  },
  {
    /* Francais */
    "~Jeu", "~Nouveau", "~1 Joueur\t1", "~2 Joueurs\t2",
    "~Cadre\t^F", "~Arriere-plan\t^B", "~Pause\t^P", "A~rreter",
    "~Quitter\tF3", "~Options", "~Vaisseaux", "~Photons",
    "~Tir rapide", "~Cadence", "~Lent", "~Moyen", "~Rapide",
    "~Bouclier", "~Souris\t^M", "Tou~ches...\t^K", "~Langue",
    "~Aide", "~Aide pour aider...", "Aide e~tendue...",
    "Aide sur les t~ouches...", "Aide in~dex...", "A ~propos...",
    "PAR", "OK", "QUITTER",
    "Definition des touches", "Choisir la touche a changer,",
    "appuyez ensuite sur la nouvelle.", "Tourner a gauche",
    "Tourner a droite", "Propulsion", "Hyperespace", "Tirer",
    "Bouclier", "OK", "Annuler",
    "Placez ASTEROID.DLL dans un repertoire de votre LIBPATH.",
    "Erreur de lecture de ASTEROID.DLL",
    "Placez ASTEROID.HLP dans un repertoire indique par la variable "
    "HELP ou dans le repertoire de travail d'ASTEROID.",
    "Fichier d'aide introuvable",
    "MEILLEURS SCORES", "APPUYEZ SUR 1 OU 2", "POUR COMMENCER",
    "PARTIE TERMINEE", "JOUEUR %d",
    "VOTRE SCORE EST PARMI LES MEILLEURS",
    "MERCI D'ENTRER VOS INITIALES",
    "TOURNEZ POUR CHOISIR LA LETTRE",
    "HYPERSPACE SI LA LETTRE EST CORRECTE"
  }
};
#else
extern CHAR *apLang[LANG_COUNT][STR_COUNT];
#endif

/* Access the current language's string */
#define GetText(i) apLang[uiLang][(i)]
