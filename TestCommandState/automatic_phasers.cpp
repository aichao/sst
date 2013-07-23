/*
 *  automatic_phasers.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#include "automatic_phasers.hpp"

#include "command_state_factory.hpp"
#include "global_state.hpp"

namespace iTrek { 
namespace command_input_state {
    
namespace {

// Factory method to create the concrete command_state object
command_state* create_automatic_phasers_state() {
  return new automatic_phasers();
}
// Define the identifier
const std::string automatic_phasers_state_id("_automatic_phasers");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    automatic_phasers_state_id, create_automatic_phasers_state);

}

boost::logic::tribool automatic_phasers::handle(command_input_handler* handler) const {
  if ((damage[DCOMPTR] == 0 && damage[DSRSENS] == 0) || nenhere == 0) {
    // if no damage or no enemies, transition to automatic_phaser_units
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_automatic_phaser_units")));      
  } else if (nenhere > 0 && (damage[DCOMPTR] != 0 || damage[DSRSENS] != 0)) {
    // else if enemies and damage to computers or sensors, transition to forced manual_phasers
    // clear the command token queue first
    clear_token_queue(handler);
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_manual_phasers")));      
  } else {
    // else we have an error in the input, this should never happen
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));      
  }
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;
}
    
} // end namespace command_input_state
} // end namespace iTrek
