/*
 *  shields_query.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "shields_query.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_shields_query_state() {
  return new shields_query();
}
// Define the identifier
const std::string shields_query_state_id("_shields_query");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    shields_query_state_id, create_shields_query_state);

}

boost::logic::tribool shields_query::handle(command_input_handler* handler) const {
  // get the answer to the query
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data ans = tokens[0];

  if (is_partial_match("yes", ans)) {
    append_command_data(handler, "transfer");
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_shields_transfer")));
  } else if (is_partial_match("no", ans)) {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_shields_toggle")));
  } else {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
    return handled_but_incomplete;
  }
  // clear token queue
  clear_token_queue(handler);
  return false;
}

} // end namespace command_input_state
} // end namespace iTrek
