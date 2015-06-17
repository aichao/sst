/*
 *  move_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_move_command_hpp
#define iTrek_move_command_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class move_command : public command_state {
public:
  /** This method ....
   *  This method always return handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
