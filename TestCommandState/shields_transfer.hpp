/*
 *  shields_transfer.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_shields_transfer_hpp
#define iTrek_shields_transfer_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class shields_transfer : public command_state {
 public:
  /** This method...
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Energy to transfer to shields- ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
