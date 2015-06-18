/*
 *  global_state.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "global_state.hpp"

#include <cstdlib>
#include <cmath>

namespace iTrek {

// Global variables to define min/max sector coordinates
double MAX_SECTOR_X = 10.;
double MIN_SECTOR_X = 1.;
double MAX_SECTOR_Y = 10.;
double MIN_SECTOR_Y = 1.;

// Global variable for contents of current quadrant
char quad[11][11] = { {'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X'},
                      {'X', '.', '.', '.', 'K', '.', '.', '.', '*', '.', '.'},
                      {'X', '.', '.', 'R', '.', '.', '.', '.', '.', '.', '.'},
                      {'X', '*', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
                      {'X', '.', '.', '.', '.', 'E', '.', '.', '.', '*', '.'},
                      {'X', '.', 'C', '.', '.', '.', ' ', '.', '.', '.', '.'},
                      {'X', '.', '.', 'P', '.', '.', '.', '.', 'K', '.', '.'},
                      {'X', '.', '.', '*', '.', '.', 'S', '.', '.', '.', '.'},
                      {'X', '.', '.', '.', '.', '.', '.', '.', '.', '*', '.'},
                      {'X', '.', '.', 'K', '.', '.', 'B', '*', '.', '.', '.'},
                      {'X', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'} };

// Global variable for damage status
double damage[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

// Global variable for tactical condition
int condit = IHGREEN;

// Global variable for number of torpedoes available
int torps = 10;

// global variables for current sector location
int sectx = 4;
int secty = 5;

// Global variable for number of enemies in the quadrant
int nenhere = 4;

// Global variables for the enemy sector coordinates
// Note that these arrays are filled from index 1 so there
// is a maximum of 20 enemies per quadrant in the game.
int kx[] = { 0, 1, 5, 7, 2, 6, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int ky[] = { 0, 4, 2, 6, 3, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };  

// Global variable for the enemy energy level
double kpower[] = { 0., 550., 425., 500., 475., 525., 450., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

// Global variable for whether shields are up (1) or down (0)
double shldup = 0.;

// Global variable for energy level
double energy = 5000.;

// Global variable for number of probes (left)
int nprobes = 3;

// computes the distance between two sector locations in a quadrant
double compute_distance(double s1_x, double s1_y, double s2_x, double s2_y) {
  return std::sqrt((s1_x - s2_x) * (s1_x - s2_x) + (s1_y - s2_y) * (s1_y - s2_y));
}

std::string get_object_type(char c) {
  switch (c) {
    case 'R': return std::string("Romulan"); break;
    case 'K': return std::string("Klingon"); break;
    case 'C': return std::string("Commander"); break;
    case 'S': return std::string("Super-commander"); break;
    case '*': return std::string("Star"); break;
    case 'P': return std::string("Planet"); break;
    case 'B': return std::string("Starbase"); break;
    case ' ': return std::string("Black hole"); break;
    case 'T': return std::string("Tholean"); break;
    case '#': return std::string("Tholean web"); break;
    default: return std::string("Unknown??"); break;
  }
}

int compute_phaser_kill_energy(unsigned i_tgt) {
  return static_cast<int>(fabs(kpower[i_tgt]) / 
      (phasefac * std::pow(0.9, compute_distance(sectx, secty, kx[i_tgt], ky[i_tgt]))) * 
      (1.01 + 0.05 * std::rand()/(1.0 + (double)RAND_MAX)) + 1.0);
}
  
} // end namespace iTrek
