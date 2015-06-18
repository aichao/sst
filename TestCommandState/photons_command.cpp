/*
 *  photons_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "photons_command.hpp"

#include <sstream>

#include "global_state.hpp"
#include "command_state_factory.hpp"

namespace iTrek { 
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_photons_command_state() {
  return new photons_command();
}
// Define the identifier
const std::string photons_command_state_id("photons");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    photons_command_state_id, create_photons_command_state);

}

boost::logic::tribool photons_command::handle(command_input_handler* handler) const {
  // if photons are damaged, say so and ignore the command
  if (damage[DPHOTON]) {
    add_display_event(handler, "Photon tubes damaged.");
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
    return handled_but_incomplete;
  }
  // if there are no torpedoes left, say so and ignore command
  if (torps == 0) {
    add_display_event(handler, "No torpedoes left.");
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
    return handled_but_incomplete;
  }
  // display number of torpedoes left.
  std::ostringstream num_photons_avail_sstrm;
  num_photons_avail_sstrm << torps << " torpedoes left.";
  add_display_event(handler, num_photons_avail_sstrm.str());
  // add the command name "Photons" to command data
  append_command_data(handler, "photons");
  // transition the command state to _num_photons
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_num_photons")));
  // return handled_but_incomplete
  return handled_but_incomplete;  
}
  
} // end namespace command_input_state
} // end namespace iTrek
