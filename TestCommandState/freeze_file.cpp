/*
 *  freeze_file.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "freeze_file.hpp"

#include "command_state_factory.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_freeze_file_state() {
  return new freeze_file();
}
// Define the identifier
const std::string freeze_file_state_id("_freeze_file");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    freeze_file_state_id, create_freeze_file_state);

}

boost::logic::tribool freeze_file::handle(command_input_handler* handler) const {
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data filename = tokens[0];
  if (filename.empty()) return false;

  // append to command data
  append_command_data(handler, filename);
  // clear token queue
  clear_token_queue(handler);
  // transition the command state to get_command
  change_state(handler, boost::shared_ptr<command_state>(
      command_state_factory::instance().create_command_state("_getcmd")));
  // return true (complete)
  return true;
}

} // end namespace command_input_state
} // end namespace iTrek
