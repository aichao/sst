/*
 *  rest_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/18/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_rest_command_hpp
#define iTrek_rest_command_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class rest_command : public command_state {
 public:
  /** This method always transitions the state to rest_duration and returns
   *  handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
