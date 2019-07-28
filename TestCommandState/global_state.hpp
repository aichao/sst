/*
 *  global_state.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_global_state_hpp
#define iTrek_global_state_hpp

#include <string>

namespace iTrek {

// Number of devices
#define ndevice (15)
#define phasefac (2.0)
  
// Define devices
#define DSRSENS 1
#define DLRSENS 2
#define DPHASER 3
#define DPHOTON 4
#define DLIFSUP 5
#define DWARPEN 6
#define DIMPULS 7
#define DSHIELD 8
#define DRADIO  9
#define DSHUTTL 10
#define DCOMPTR 11
#define DTRANSP 12
#define DSHCTRL 13
#define DDRAY   14  // Added deathray
#define DDSP    15  // Added deep space probe
  
// Define tactical conditions
#define IHGREEN 'G'
#define IHYELLOW 'Y'
#define IHRED 'R'
#define IHDOCKED 'D'
  
// Global variables to define min/max sector coordinates
extern double MAX_SECTOR_X;
extern double MIN_SECTOR_X;
extern double MAX_SECTOR_Y;
extern double MIN_SECTOR_Y;

// Global variable for contents of current quadrant
extern char quad[11][11];

// Global variable for damage status
extern double damage[ndevice+1];		// damage encountered

// Global variable for tactical condition
extern int condit;

// Global variable for number of torpedoes available
extern int torps;

// Global variables for current sector location
extern int sectx;
extern int secty;

// Global variable for number of enemies in the quadrant
extern int nenhere;

// Global variables for the enemy sector coordinates
// Note that these arrays are filled from index 1 so there
// is a maximum of 20 enemies per quadrant in the game.
extern int kx[21];
extern int ky[21];

// Global variable for the enemy energy level
extern double kpower[21];

// Global variable for whether shields are up (1) or down (0)
extern double shldup;

// Global variable for energy level
extern double energy;

// Global variable for number of probes (left)
extern int nprobes;

// computes the distance between two sector locations in a quadrant
double compute_distance(double s1_x, double s1_y, double s2_x, double s2_y);

// returns a string describing the object whose character icon is c
std::string get_object_type(char c);

// returns the estimated phaser energy required to kill target with index i_tgt
int compute_phaser_kill_energy(unsigned i_tgt);
  
} // end namespace iTrek

#endif
