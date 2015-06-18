/*
 *  probe_query.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#include "probe_query.hpp"

#include "command_state_factory.hpp"
#include "command_input_utilities.hpp"

namespace iTrek {
namespace command_input_state {

namespace {

// Factory method to create the concrete command_state object
command_state* create_probe_query_state() {
  return new probe_query();
}
// Define the identifier
const std::string probe_query_state_id("_probe_query");
// Register
const bool registered = command_state_factory::instance().register_command_state(
    probe_query_state_id, create_probe_query_state);

}

boost::logic::tribool probe_query::handle(command_input_handler* handler) const {
  // get the answer to the query
  command_inputs tokens;
  get_command_inputs(handler, 1, tokens);
  command_data ans = tokens[0];

  if (is_partial_match("yes", ans)) {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_probe_armed")));
    // clear token queue
    clear_token_queue(handler);
    return false;
  } else if (is_partial_match("no", ans)) {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_ignorecmd")));
  } else {
    change_state(handler, boost::shared_ptr<command_state>(
        command_state_factory::instance().create_command_state("_cmderr")));
  }
  return handled_but_incomplete;
}

} // end namespace command_input_state
} // end namespace iTrek
