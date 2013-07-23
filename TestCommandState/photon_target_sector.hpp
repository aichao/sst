/*
 *  photon_target_sector.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_photon_target_sector_hpp
#define iTrek_photon_target_sector_hpp

#include "command_state.hpp"

namespace iTrek { 
namespace command_input_state {   

/** 
 */
class photon_target_sector : public command_state {
 public:
  /** Constructor initializes the i_tgt count with respect to the total 
   *  targets n_tgts for this photon target sector state. When i_tgt is
   *  equal to n_tgts, then this is the last photon to target. After 
   *  handling this last target, the command is complete; otherwise, this
   *  transition is to the photon_target_sector state with i_tgt incremented.
   */
  photon_target_sector(unsigned i_tgt, unsigned n_tgts);
  
  /** This method .... 
   *  This method always return handled_but_incomplete.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;
  
  /// Return the prompt corresponding to the manual_phaser_units state.
  virtual boost::optional<std::string> prompt() const;
  
 private:
  mutable unsigned i_tgt_;
  unsigned n_tgts_;
};

} // end namesoace command_input_state
} // end namesoace iTrek

#endif
