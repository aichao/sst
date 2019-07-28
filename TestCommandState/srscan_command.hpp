/*
 *  srscan_command.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/17/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_srscan_command_hpp
#define iTrek_srscan_command_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class srscan_command : public command_state {
 public:
  /** This method checks if the optional "no" or "chart" is included with the 
   *  command. This method always completes the command and returns true.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
