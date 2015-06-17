/*
 *  shields_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_shields_command_hpp
#define iTrek_shields_command_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class shields_command : public command_state {
 public:
  /** This method returns true if the "up" or "down" command is included. This 
   *  method transitions the state to shields_transfer and returns 
   *  handled_but_incomplete if the "transfer" command is included. Otherwise, 
   *  this method transitions the state to shields_query and returns false.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
