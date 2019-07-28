/*
 *  shields_toggle.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "shields_toggle.hpp"

#include <sstream>

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"
#include "global_state.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_shields_toggle_state() {
  return new shields_toggle();
}
// Define the identifier
const std::string shields_toggle_state_id("_shields_toggle");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    shields_toggle_state_id, create_shields_toggle_state);

}

boost::logic::tribool shields_toggle::handle(command_input_handler* handler) const {
  // get the answer to the question
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data ans = tokens[0];

  if (is_partial_match("yes", ans)) {
    std::string shield_cmd = (shldup) ? "down" : "up";
    append_command_data(handler, shield_cmd);
    // clear token queue
    clear_token_queue(handler);
    // transition the command state to get_command
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_getcmd")));
    // AIC_DEBUG: simulate change in game state
    shldup = is_partial_match("up", shield_cmd) ? 1 : 0;
    // return true (complete)
    return true;    
  } else if (is_partial_match("no", ans)) {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
  } else {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
    return handled_but_incomplete;
  }
  return handled_but_incomplete;
}

boost::optional<std::string> shields_toggle::prompt() const {
  std::ostringstream prompt_sstrm;
  prompt_sstrm << "Shields are " << (shldup ? "up" : "down")
               << ". Do you want them " << (shldup ? "down" : "up") << "? ";
  return prompt_sstrm.str();
}

} // end namespace command_input_state
} // end namespace iTrek
