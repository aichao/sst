/*
 *  command_state.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "command_state.hpp"

#include <iostream>

#include "command_input_handler.hpp"
//#include "EventQueue.hpp"
//#include "DisplayEvent.hpp"

namespace iTrek {

void command_state::change_state(command_input_handler* handler, 
                                 boost::shared_ptr<command_state> state) const {
  // forwards state to handler
  handler->change_state(state);
}

command_data const& command_state::get_command_data(
    command_input_handler* handler) const {
  return handler->get_command_data();
}

void command_state::append_command_data(command_input_handler* handler, 
                                        command_data const& data) const {
  // forwards data to handler
  handler->command_data_ += 
      (handler->get_command_data().length() == 0 ? data : (std::string(" ") + data)); 
}

void command_state::clear_command_data(command_input_handler* handler) const {
  handler->clear_command_data();
}

void command_state::clear_token_queue(command_input_handler* handler) const {
  handler->command_tokens_.clear();
}

std::size_t command_state::number_of_tokens_in_queue(
    command_input_handler* handler) const {
  return handler->command_tokens_.size();
}
  
command_data command_state::peek_at_token_queue(command_input_handler* handler) const {
    if (!(handler->command_tokens_.empty()))
      return handler->command_tokens_.front();
    return command_data("");
}

void command_state::get_command_inputs(
    command_input_handler* handler,
    std::size_t n, command_inputs & tokens) const {
  tokens.clear();
  // loop over the n requested tokens or the number of available tokens, which ever is smaler
  n = n < handler->command_tokens_.size() ? n : handler->command_tokens_.size();
  for (std::size_t i = 0; i < n; ++i ) {
    tokens.push_back(handler->command_tokens_.front());
    handler->command_tokens_.pop_front();
  }
  // if tokens is still empty (queue is empty), insert an empty string
  if (tokens.empty()) tokens.push_back(command_data(""));
}

void command_state::add_display_event(command_input_handler* handler, 
                                      std::string const& msg) const {
  // forwards message to handler
  handler->add_display_event(msg);
}

} // end namespace iTrek
