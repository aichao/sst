/*
 *  phasers_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_phasers_command_hpp
#define iTrek_phasers_command_hpp

#include "command_state.hpp"

namespace iTrek { 
namespace command_input_state {   

/** 
 */
class phasers_command : public command_state {
 public:
  /** This method .... 
   *  This method always return handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
