#define INCLUDED	// Define externs here
#include "sst.h"
#include <ctype.h>
#ifdef MSDOS
#include <dos.h>
#endif
#include <time.h>
	
/*int getch(void);
*/

static char line[128], *linep = line;
static int linecount;	/* for paging */

static void clearscreen(void);

#define NUMCOMMANDS 34

/* Compared to original version, I've changed the "help" command to
   "call" and the "terminate" command to "quit" to better match
   user expectations. The DECUS version apparently made those changes
   as well as changing "freeze" to "save". However I like "freeze".

   When I got a later version of Super Star Trek that I was converting
   from, I added the emexit command.

   That later version also mentions srscan and lrscan working when
   docked (using the starbase's scanners), so I made some changes here
   to do this (and indicating that fact to the player), and then realized
   the base would have a subspace radio as well -- doing a Chart when docked
   updates the star chart, and all radio reports will be heard. The Dock
   command will also give a report if a base is under attack.

   Movecom no longer reports movement if sensors are damaged so you wouldn't
   otherwise know it.

   Also added:

   1. Better base positioning at startup

   2. deathray improvement (but keeping original failure alternatives)

   3. Tholian Web

   4. Enemies can ram the Enterprise. Regular Klingons and Romulans can
      move in Expert and Emeritus games. This code could use improvement.

   5. The deep space probe looks interesting! DECUS version

   6. Perhaps cloaking to be added later? BSD version


   */


static char *commands[NUMCOMMANDS] = {
	"srscan",
	"lrscan",
	"phasers",
	"photons",
	"move",
	"shields",
	"dock",
	"damages",
	"chart",
	"impulse",
	"rest",
	"warp",
	"status",
	"sensors",
	"orbit",
	"transport",
	"mine",
	"crystals",
	"shuttle",
	"planets",
	"request",
	"report",
	"computer",
	"commands",
    "emexit",
    "probe",
	"abandon",
	"destruct",
	"freeze",
	"deathray",
	"debug",
	"call",
	"quit",
	"help"
};

static void listCommands(int x) {
	prout("   SRSCAN    MOVE      PHASERS   CALL\n"
		  "   STATUS    IMPULSE   PHOTONS   ABANDON\n"
		  "   LRSCAN    WARP      SHIELDS   DESTRUCT\n"
		  "   CHART     REST      DOCK      QUIT\n"
		  "   DAMAGES   REPORT    SENSORS   ORBIT\n"
		  "   TRANSPORT MINE      CRYSTALS  SHUTTLE\n"
		  "   PLANETS   REQUEST   DEATHRAY  FREEZE\n"
		  "   COMPUTER  EMEXIT    PROBE     COMMANDS");
	if (x) prout("   HELP");
}

static void helpme(void) {
	int i, j;
	char cmdbuf[32];
	char linebuf[132];
	FILE *fp;
	/* Give help on commands */
	int key;
	key = scan();
	while (TRUE) {
		if (key == IHEOL) {
			proutn("Help on what command?");
			key = scan();
		}
		if (key == IHEOL) return;
		for (i = 0; i < NUMCOMMANDS; i++) {
			if (strcmp(commands[i], citem)==0) break;
		}
		if (i != NUMCOMMANDS) break;
		skip(1);
		prout("Valid commands:");
		listCommands(FALSE);
		key = IHEOL;
		chew();
		skip(1);
	}
	if (i == 23) {
		strcpy(cmdbuf, " ABBREV");
	}
	else {
		strcpy(cmdbuf, "  Mnemonic:  ");
		j = 0;
		while ((cmdbuf[j+13] = toupper(commands[i][j])) != 0) j++;
	}
	fp = fopen("sst.doc", "r");
	if (fp == NULL) {
		prout("Spock-  \"Captain, that information is missing from the");
		prout("   computer. You need to find SST.DOC and put it in the");
		prout("   current directory.\"");
		return;
	}
	i = strlen(cmdbuf);
	do {
		if (fgets(linebuf, 132, fp) == NULL) {
			prout("Spock- \"Captain, there is no information on that command.\"");
			fclose(fp);
			return;
		}
	} while (strncmp(linebuf, cmdbuf, i) != 0);

	skip(1);
	prout("Spock- \"Captain, I've found the following information:\"");
	skip(1);

	do {
		if (linebuf[0]!=12) { // ignore page break lines 
			linebuf[strlen(linebuf)-1] = '\0'; // No \n at end
			prout(linebuf);
		}
		fgets(linebuf,132,fp);
	} while (strstr(linebuf, "******")==NULL);
	fclose(fp);
}

static void makemoves(void) {
	int i, hitme;
	char ch;
	while (TRUE) { /* command loop */
		hitme = FALSE;
		justin = 0;
		Time = 0.0;
		i = -1;
		while (TRUE)  { /* get a command */
			chew();
			skip(1);
			proutn("COMMAND> ");
      // Use of scan() here (after chew) will get a new line of input
      // and will return IHEOL iff new line of input contains nothing
      // or a numeric input is detected but conversion fails.
			if (scan() == IHEOL) continue;
			for (i=0; i < 26; i++)
				if (isit(commands[i]))
					break;
			if (i < 26) break;
			for (; i < NUMCOMMANDS; i++)
				if (strcmp(commands[i], citem) == 0) break;
			if (i < NUMCOMMANDS) break;
      // we get here iff the first parsed input from the line does not 
      // match one of the commands. In this case, the rest of the line
      // is discarded, the below message is printed, and we go back to 
      // get a new command.
			if (skill <= 2)  {
				prout("UNRECOGNIZED COMMAND. LEGAL COMMANDS ARE:");
				listCommands(TRUE);
			}
			else prout("UNRECOGNIZED COMMAND.");
		} // end get command loop
    // we get here iff the first parsed input from the line matches one
    // of the commands (i.e., command i). We use i to dispatch the 
    // handling of the command. The line may still contain additional
    // inputs (i.e., parameters of the command) that is to be parsed by
    // the dispatched command handler. If the line does not contain
    // all the necessary parameters, the dispatched command handler is 
    // responsible to get additional input(s) interactively using scan().
    // The dispatched command handler is also responsible to handle any 
    // input errors.
		switch (i) { /* command switch */
			case 0:			// srscan
				srscan(1);
				break;
			case 1:			// lrscan
				lrscan();
				break;
			case 2:			// phasers
				phasers();
				if (ididit) hitme = TRUE;
				break;
			case 3:			// photons
				photon();
				if (ididit) hitme = TRUE;
				break;
			case 4:			// move
				warp(1);
				break;
			case 5:			// shields
				sheild(1);
				if (ididit) {
					attack(2);
					shldchg = 0;
				}
				break;
			case 6:			// dock
				dock();
				break;
			case 7:			// damages
				dreprt();
				break;
			case 8:			// chart
				chart(0);
				break;
			case 9:			// impulse
				impuls();
				break;
			case 10:		// rest
				waiting();
				if (ididit) hitme = TRUE;
				break;
			case 11:		// warp
				setwrp();
				break;
			case 12:		// status
				srscan(3);
				break;
			case 13:			// sensors
				sensor();
				break;
			case 14:			// orbit
				orbit();
				if (ididit) hitme = TRUE;
				break;
			case 15:			// transport "beam"
				beam();
				break;
			case 16:			// mine
				mine();
				if (ididit) hitme = TRUE;
				break;
			case 17:			// crystals
				usecrystals();
				break;
			case 18:			// shuttle
				shuttle();
				if (ididit) hitme = TRUE;
				break;
			case 19:			// Planet list
				preport();
				break;
			case 20:			// Status information
				srscan(2);
				break;
			case 21:			// Game Report 
				report(0);
				break;
			case 22:			// use COMPUTER!
				eta();
				break;
			case 23:
				listCommands(TRUE);
				break;
			case 24:		// Emergency exit
				clearscreen();	// Hide screen
				freeze(TRUE);	// forced save
				exit(1);		// And quick exit
				break;
			case 25:
				probe();		// Launch probe
				break;
			case 26:			// Abandon Ship
				abandn();
				break;
			case 27:			// Self Destruct
				dstrct();
				break;
			case 28:			// Save Game
				freeze(FALSE);
				if (skill > 3)
					prout("WARNING--Frozen games produce no plaques!");
				break;
			case 29:			// Try a desparation measure
				deathray();
				if (ididit) hitme = TRUE;
				break;
			case 30:			// What do we want for debug???
#ifdef DEBUG
				debugme();
#endif
				break;
			case 31:		// Call for help
				help();
				break;
			case 32:
				alldone = 1;	// quit the game
#ifdef DEBUG
				if (idebug) score();
#endif
				break;
			case 33:
				helpme();	// get help
				break;
		} // end command switch
		for (;;) {
			if (alldone) break;		// Game has ended
#ifdef DEBUG
			if (idebug) prout("2500");
#endif
			if (Time != 0.0) {
				events();
				if (alldone) break;		// Events did us in
			}
			if (d.galaxy[quadx][quady] == 1000) { // Galaxy went Nova!
				atover(0);
				continue;
			}
			if (nenhere == 0) movetho();
			if (hitme && justin==0) {
				attack(2);
				if (alldone) break;
				if (d.galaxy[quadx][quady] == 1000) {	// went NOVA! 
					atover(0);
					hitme = TRUE;
					continue;
				}
			}
			break;
		} // end event loop
		if (alldone) break;
	} // end command loop
}


void main(int argc, char **argv) {
	int i;
	int hitme;
	char ch;
	prelim();

	if (argc > 1) {
		fromcommandline = 1;
		line[0] = '\0';
		while (--argc > 0) {
			strcat(line, *(++argv));
			strcat(line, " ");
		}
	}
	else fromcommandline = 0;


	while (TRUE) { /* Play a game */
		setup();
		if (alldone) {
			score();
			alldone = 0;
		}
		else makemoves();
		skip(2);
		stars();
		skip(1);

		if (tourn && alldone) {
			printf("Do you want your score recorded?");
			if (ja()) {
				chew2();
				freeze(FALSE);
			}
		}
		printf("Do you want to play again?");
		if (!ja()) break;
	}
	skip(1);
	prout("May the Great Bird of the Galaxy roost upon your home planet.");
}


void cramen(int i) {
	/* return an enemy */
	char *s;
	
	switch (i) {
		case IHR: s = "Romulan"; break;
		case IHK: s = "Klingon"; break;
		case IHC: s = "Commander"; break;
		case IHS: s = "Super-commander"; break;
		case IHSTAR: s = "Star"; break;
		case IHP: s = "Planet"; break;
		case IHB: s = "Starbase"; break;
		case IHBLANK: s = "Black hole"; break;
		case IHT: s = "Tholean"; break;
		case IHWEB: s = "Tholean web"; break;
		default: s = "Unknown??"; break;
	}
	proutn(s);
}

void cramlc(int key, int x, int y) {
	if (key == 1) proutn(" Quadrant");
	else if (key == 2) proutn(" Sector");
	proutn(" ");
	crami(x, 1);
	proutn(" - ");
	crami(y, 1);
}

void crmena(int i, int enemy, int key, int x, int y) {
	if (i == 1) proutn("***");
	cramen(enemy);
	proutn(" at");
	cramlc(key, x, y);
}

void crmshp(void) {
	char *s;
	switch (ship) {
		case IHE: s = "Enterprise"; break;
		case IHF: s = "Faerie Queene"; break;
		default:  s = "Ship???"; break;
	}
	proutn(s);
}

void stars(void) {
	prouts("******************************************************");
	skip(1);
}

double expran(double avrage) {
	return -avrage*log(1e-7 + Rand());
}

double Rand(void) {
	return rand()/(1.0 + (double)RAND_MAX);
}

void iran8(int *i, int *j) {
	*i = Rand()*8.0 + 1.0;
	*j = Rand()*8.0 + 1.0;
}

void iran10(int *i, int *j) {
	*i = Rand()*10.0 + 1.0;
	*j = Rand()*10.0 + 1.0;
}

void chew(void) {
	linecount = 0;
	linep = line;
	*linep = 0;
}

void chew2(void) {
	/* return IHEOL next time */
	linecount = 0;
	linep = line+1;
	*linep = 0;
}

int scan(void) {
	int i;
	char *cp;

	linecount = 0;

	// Init result
	aaitem = 0.0;
	*citem = 0;

	// Read a line if nothing here
	if (*linep == 0) {
		if (linep != line) {
      // Reached EOL when parsing last read line
      // call chew which resets line = '\0' and linep to
      // point to start of line. and return EOL flag.
			chew();
			return IHEOL;
		}
    // Read next line: this is reached when line = '\0' and 
    // linep points to start of line. This occurs after call to 
    // chew()
		gets(line);
		linep = line;
	}
	// Skip leading white space
	while (*linep == ' ') linep++;
	// Nothing left
	if (*linep == 0) {
    // This occurs if newly gotten line has nothing but spaces or 
    // when last read line has only spaces left. In either case,
    // call chew to reset line and linep and return EOL flag.
		chew();
		return IHEOL;
	}
  // This point is reach iff there is a string or number in the
  // currently read line to be parsed.
	if (isdigit(*linep) || *linep=='+' || *linep=='-' || *linep=='.') {
		// treat as a number
    if (sscanf(linep, "%lf%n", &aaitem, &i) < 1) {
      // if sscanf does not convert a double, reset line and linep 
      // (i.e., equivalent to calling chew()) and return EOL.
      linep = line; // Invalid numbers are ignored
      *linep = 0;
      return IHEOL;
    }
    else {
      // i returns the number of characters converted to a double!
      // skip to end of converted characters in line and return REAL flag
      linep += i;
      return IHREAL;
    }
	}
	// Treat as alpha
	cp = citem;
	while (*linep && *linep!=' ') {
    // copy characters (convert to lower case) from line to citem
    // length of string is limited to 9 characters
		if ((cp - citem) < 9) *cp++ = tolower(*linep);
		linep++;
	}
  // terminate with '\0' and return STRING flag
	*cp = 0;
	return IHALPHA;
}

/** parse is like scan except it does not retrieve a new
 *  line of input when the current line reaches EOL.
 *  Instead, it just returns IHEOL.
 *
 *  Precondition: line contains input(s) to be parsed and linep 
 *  points to the current position within the input in line to 
 *  parse the next input separated by space.
 *  Postconditions: linep points to position within line after
 *  the parsed input. If EOL is encountered during parsing, line
 *  is reset to '\0' and linep is reset to point to the start of 
 *  line. If the parsed input is a character string, the input 
 *  (limited to 9 chars) is copied to the global variable citem. If 
 *  the parsed input is numeric, the input is copied to the global
 *  variable aaitem. The global variable linecount is set to zero.
 *  The function returns IHEOL if EOL is encountered during parsing,
 *  IHREAL if the parsed input is numeric, and IHALPHA if the 
 *  parsed input is a character string.
 *  Exception: If the next input is detected to be numeric, but an
 *  error occured in parsing the input, line is reset to '\0', linep
 *  is reset to point to the start of line, and IHEOL is returned.
 *
 *  Usage: parse is used by Command execution functions to parse
 *  the input command with parameters separated by spaces. The 
 *  parsing logic should parallel the current logic in handling 
 *  interactive input except that no further prompting for 
 *  parameters is necessary since all parameters are assumed to
 *  be contained in the global variable line for this Command.
 *  In addition, no error handling is necessary since the global
 *  variable line is assumed to contain the complete command, and
 *  all error handling is assumed to have occurred in assembling
 *  this Command interactively in the get<Command>Params() 
 *  function for the command.
 */
int parse(void) 
{
	int i;
	char *cp;
  
	linecount = 0;
  
	// Init result
	aaitem = 0.0;
	*citem = 0;
  
	// Skip leading white space
	while (*linep == ' ') linep++;
	// Nothing left
	if (*linep == 0) {
    // This occurs if newly gotten line has nothing but spaces or 
    // when last read line has only spaces left. In either case,
    // call chew to reset line and linep and return EOL flag.
		chew();
		return IHEOL;
	}
  // This point is reach iff there is a string or number in the
  // currently read line to be parsed.
	if (isdigit(*linep) || *linep=='+' || *linep=='-' || *linep=='.') {
		// treat as a number
    if (sscanf(linep, "%lf%n", &aaitem, &i) < 1) {
      // if sscanf does not convert a double, reset line and linep 
      // (i.e., equivalent to calling chew()) and return EOL.
      linep = line; // Invalid numbers are ignored
      *linep = 0;
      return IHEOL;
    }
    else {
      // i returns the number of characters converted to a double!
      // skip to end of converted characters in line and return REAL flag
      linep += i;
      return IHREAL;
    }
	}
	// Treat as alpha
	cp = citem;
	while (*linep && *linep!=' ') {
    // copy characters (convert to lower case) from line to citem
    // length of string is limited to 9 characters
		if ((cp - citem) < 9) *cp++ = tolower(*linep);
		linep++;
	}
  // terminate with '\0' and return STRING flag
	*cp = 0;
	return IHALPHA;
}

int ja(void) {
	chew();
	while (TRUE) {
		scan();
		chew();
		if (*citem == 'y') return TRUE;
		if (*citem == 'n') return FALSE;
		proutn("Please answer with \"Y\" or \"N\":");
	}
}

void cramf(double x, int w, int d) {
	char buf[64];
	sprintf(buf, "%*.*f", w, d, x);
	proutn(buf);
}

void crami(int i, int w) {
	char buf[16];
	sprintf(buf, "%*d", w, i);
	proutn(buf);
}

double square(double i) { return i*i; }
									
static void clearscreen(void) {
	/* Somehow we need to clear the screen */
	proutn("\033[2J\033[0;0H");	/* Hope for an ANSI display */
}

/* We will pull these out in case we want to do something special later */

void pause(int i) {
	putchar('\n');
	if (i==1) {
		if (skill > 2)
			prout("[ANOUNCEMENT ARRIVING...]");
		else
			prout("[IMPORTANT ANNOUNCEMENT ARRIVING -- HIT SPACE BAR TO CONTINUE]");
		getch();
	}
	else {
		if (skill > 2)
			proutn("[CONTINUE?]");
		else
			proutn("[HIT SPACE BAR TO CONTINUE]");
		getch();
		proutn("\r                           \r");
	}
	if (i != 0) {
		clearscreen();
	}
	linecount = 0;
}


void skip(int i) {
	while (i-- > 0) {
		linecount++;
		if (linecount >= 23)
			pause(0);
		else
			putchar('\n');
	}
}


void proutn(char *s) {
	fputs(s, stdout);
}

void prout(char *s) {
	proutn(s);
	skip(1);
}

void prouts(char *s) {
	clock_t endTime;
	/* print slowly! */
	while (*s) {
		endTime = clock() + CLOCKS_PER_SEC*0.05;
		while (clock() < endTime) ;
		putchar(*s++);
		fflush(stdout);
	}
}

void huh(void) {
	chew();
	skip(1);
	prout("Beg your pardon, Captain?");
}

int isit(char *s) {
	/* New function -- compares s to scaned citem and returns true if it
	   matches to the length of s */

	return strncmp(s, citem, max(1, strlen(citem))) == 0;

}

#ifdef DEBUG
void debugme(void) {
	proutn("Reset levels? ");
	if (ja() != 0) {
		if (energy < inenrg) energy = inenrg;
		shield = inshld;
		torps = intorps;
		lsupres = inlsr;
	}
	proutn("Reset damage? ");
	if (ja() != 0) {
		int i;
		for (i=0; i <= ndevice; i++) if (damage[i] > 0.0) damage[i] = 0.0;
		stdamtim = 1e30;
	}
	proutn("Toggle idebug? ");
	if (ja() != 0) {
		idebug = !idebug;
		if (idebug) prout("Debug output ON");
		else prout("Debug output OFF");
	}
	proutn("Cause selective damage? ");
	if (ja() != 0) {
		int i, key;
		for (i=1; i <= ndevice; i++) {
			proutn("Kill ");
			proutn(device[i]);
			proutn("? ");
			chew();
			key = scan();
			if (key == IHALPHA &&  isit("y")) {
				damage[i] = 10.0;
				if (i == DRADIO) stdamtim = d.date;
			}
		}
	}
	proutn("Examine/change events? ");
	if (ja() != 0) {
		int i;
		for (i = 1; i < NEVENTS; i++) {
			int key;
			if (future[i] == 1e30) continue;
			switch (i) {
				case FSNOVA:  proutn("Supernova       "); break;
				case FTBEAM:  proutn("T Beam          "); break;
				case FSNAP:   proutn("Snapshot        "); break;
				case FBATTAK: proutn("Base Attack     "); break;
				case FCDBAS:  proutn("Base Destroy    "); break;
				case FSCMOVE: proutn("SC Move         "); break;
				case FSCDBAS: proutn("SC Base Destroy "); break;
			}
			cramf(future[i]-d.date, 8, 2);
			chew();
			proutn("  ?");
			key = scan();
			if (key == IHREAL) {
				future[i] = d.date + aaitem;
			}
		}
		chew();
	}
}
			

#endif
