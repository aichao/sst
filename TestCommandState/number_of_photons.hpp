/*
 *  number_of_photons.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_number_of_photons_hpp
#define iTrek_number_of_photons_hpp

#include "command_state.hpp"

namespace iTrek { 
namespace command_input_state {   

/** 
 */
class number_of_photons : public command_state {
 public:
  /** This method .... 
   *  This method always return handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
  
  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Number of torpedoes to fire- ");
  }       
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
