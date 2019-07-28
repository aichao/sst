/*
 *  warp_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/17/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "warp_command.hpp"
#include "command_state_factory.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_warp_command_state() {
  return new warp_command();
}
// Define the identifier
const std::string warp_command_state_id("warp");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    warp_command_state_id, create_warp_command_state);

}

boost::logic::tribool warp_command::handle(command_input_handler* handler) const {
  // add the command name "warp" to command data
  append_command_data(handler, "warp");
  // transition to the _warp_factor state
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_warp_factor")));
  // in all cases, return handled_but_incomplete
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
