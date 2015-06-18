/*
 *  probe_command.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "probe_command.hpp"

#include <sstream>

#include "command_state_factory.hpp"
#include "global_state.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_probe_command_state() {
  return new probe_command();
}
// Define the identifier
const std::string probe_command_state_id("probe");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    probe_command_state_id, create_probe_command_state);

}

boost::logic::tribool probe_command::handle(command_input_handler* handler) const {
  // first check with global state to see if there are any probes left.
  // if so, add display event # probe(s) left, else add display event no probes
  // left and ignore command
  // @todo: the check and display should be the responsibility of the global
  // state, which should return an error status from which this method will
  // transition to ignorecmd
  if (nprobes == 0) {
    add_display_event(handler, "No probes left, Captain.");
    // transition to _ignorecmd
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
    return handled_but_incomplete;
  }
  
  // add the command name "phasers" to command data
  append_command_data(handler, "probe");
  command_data next_cmd = peek_at_token_queue(handler);
  if (next_cmd.empty()) {
    // if next_cmd is empty, display number of probes left, transition state to
    // probe_query and return false
    std::ostringstream display_msg;
    display_msg << nprobes << " probe" << (nprobes == 1 ? " " : "s ") << "left";
    // add display message as an event on the display queue
    add_display_event(handler, display_msg.str());
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_probe_query")));
    return false;
  } else if (next_cmd == "armed") {
    // if next_cmd is "armed", then get this command and add to command data
    command_inputs tokens;
    get_command_inputs(handler, 1, tokens);
    append_command_data(handler, tokens[0]);
    // AIC_DEBUG: simulate firing of probe
    --nprobes;
  }
  // transition to move_mode and return handled_but_incomplete
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_move_mode")));
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
