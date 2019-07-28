/*
 *  warp_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/17/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_warp_command_hpp
#define iTrek_warp_command_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class warp_command : public command_state {
 public:
  /** This method always transitions the state to warp_factor and returns
   *  handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
