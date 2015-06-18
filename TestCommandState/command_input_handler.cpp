/*
 *  command_input_handler.cpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#include "command_input_handler.hpp"

#include <boost/logic/tribool.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/case_conv.hpp>

#include "command_state.hpp"
#include "command_state_factory.hpp"

namespace iTrek {

command_input_handler::command_input_handler()
    : state_(command_state_factory::instance().create_command_state("_getcmd")),
      command_data_(""), disp_events_("") {}

bool command_input_handler::handle(command_input_event & cmd_str) {
  // convert to lower case
  boost::to_lower(cmd_str);
  // tokenize with space delimiter
  boost::char_separator<char> sep(" ");
  boost::tokenizer<boost::char_separator<char> > tokens(cmd_str, sep);
  std::size_t i = 0;
  for(boost::tokenizer<boost::char_separator<char> >::iterator it = tokens.begin(); 
      it != tokens.end(); ++it, ++i) {
    command_tokens_.push_back(*it);
  }
  if (i == 0) command_tokens_.push_back(command_input_event(""));
  boost::logic::tribool status;
  while(handled_but_incomplete(status = state_->handle(this)));
  return (status == true ? true : false);
}
  
} // end namespace iTrek