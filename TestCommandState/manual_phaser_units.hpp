/*
 *  manual_phaser_units.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 10/23/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_manual_phaser_units_hpp
#define iTrek_manual_phaser_units_hpp

#include "command_state.hpp"
#include "target_location.hpp"

namespace iTrek { 
namespace command_input_state {   
    
/** 
*/
class manual_phaser_units : public command_state {
 public:
  /** Constructor sets the location of the target that is being targeted by
   *  the manual phaser mode. It also looks up the remaining energy of that 
   *  target.
   */
  manual_phaser_units(unsigned i_tgt, unsigned n_tgts);
  
  /** This method .... 
   *  This method always return handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
  
  /// Return the prompt corresponding to the manual_phaser_units state.
  virtual boost::optional<std::string> prompt() const;
  
 private:
  mutable unsigned i_tgt_;
  unsigned n_tgts_;
  target_location loc_;
  double tgt_energy_;
  std::string tgt_type_;
};
    
} // end namespace command_input_state
} // end namespace iTrek

#endif
