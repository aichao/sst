/*
 *  number_of_photons.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "number_of_photons.hpp"

#include <sstream>

#include <boost/lexical_cast.hpp>

#include "global_state.hpp"
#include "command_input_utilities.hpp"
#include "command_state_factory.hpp"
#include "photon_target_sector.hpp"

namespace iTrek { 
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_number_of_photons_state() {
  return new number_of_photons();
}
// Define the identifier
const std::string number_of_photons_state_id("_num_photons");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    number_of_photons_state_id, create_number_of_photons_state);

}

boost::logic::tribool number_of_photons::handle(command_input_handler* handler) const {
  // Pop number of photo torpedoes input from the command token queue
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data num_photons_str = tokens[0];
  // if num_photons_str is empty return false to signal need for prompt
  if (num_photons_str.empty()) return false;
  // if the token is not an unsigned integer, then it is an error
  if (!is_unsigned(num_photons_str)) {
    // transition to command error state
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
    return handled_but_incomplete;
  }
  // lexical_cast to unsigned. (this should ALWAYS succeed)
  unsigned num_photons = boost::lexical_cast<unsigned>(num_photons_str);
  if (num_photons == 0) {
    // if request is zero torpedoes, ignore the command since user aborted
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
  } else if (num_photons <= std::min(3, torps)) {
    // if request is less than or equal min(3, number available), 
    // add the number requested to command data
    append_command_data(handler, num_photons_str);
    // then see if there are two more tokens on the queue
    if (number_of_tokens_in_queue(handler) == 2U) {
      // get these tokens
      get_command_inputs(handler, 2, tokens);
      if (is_number(tokens[0]) && is_number(tokens[1])) {
        // if both tokens are numbers, lexical_cast each token to double. 
        // (this should always succeed)
        double ySect = boost::lexical_cast<double>(tokens[0]);
        double xSect = boost::lexical_cast<double>(tokens[1]);
        // see if target sector is in range [ 1, 10 ].
        if (xSect >= MIN_SECTOR_X && xSect <= MAX_SECTOR_X && 
            ySect >= MIN_SECTOR_Y && ySect <= MAX_SECTOR_Y) {
          // this is the special case where all torpedoes are targeted 
          // to same sector coordinates. In this case, the command is 
          // complete
          append_command_data(handler, tokens[0] + " " + tokens[1]);
          // clear token queue
          clear_token_queue(handler);
          // transition the command state to get_command
          change_state(handler, boost::shared_ptr<command_state>(
              command_state_factory::instance().create_command_state("_getcmd")));
          // subtract the number requested from the number available, note this is for simulation only
          // @todo: remove this later.
          torps -= num_photons;
          // return true (complete)
          return true;
        }
      }        
    }
    // transition the command state to photo_target_sector initialized 
    // to first torpedo out of num_photons
    change_state(handler, boost::shared_ptr<photon_target_sector>(
        new photon_target_sector(1, num_photons)));
  } else {
    // if not and if request is more than 3, then send message of 
    // "Maximum of 3 torpedoes per burst.\n"
    if (num_photons > 3U) {
      add_display_event(handler, "Maximum of 3 torpedoes per burst.");
    } else {
      std::ostringstream num_photons_avail_sstrm;
      num_photons_avail_sstrm << "Uh, Captain...  we only have " << torps << " " 
                              << ((torps == 1) ? "torpedo" : "torpedoes") 
                              << " left.\n";
      add_display_event(handler, num_photons_avail_sstrm.str());          
    }
    // clear command queue but not the command data to try again (same state)
    clear_token_queue(handler);
    // return false to signal need for prompt
    return false;
  }
  // return handled_but_incomplete in all cases where state transition is made
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
