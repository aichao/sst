/*
 *  probe_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_probe_command_hpp
#define iTrek_probe_command_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class probe_command : public command_state {
 public:
  /** This method peeks at the next token. If it is empty, it transitions 
   *  the command state to probe_query and returns false. If the token 
   *  matches exactly the optional "armed" command, then this token is 
   *  retrieved from the queue and added to the command. In any case that 
   *  the next token is not empty, the state is transitioned to move_mode 
   *  and this method returns handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
