/*
 *  manual_phaser_units.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/23/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef MANUAL_PHASER_UNITS_HPP
#define MANUAL_PHASER_UNITS_HPP

#include "PromptCommandState.hpp"
#include "target_location.hpp"

namespace iTrek { 
namespace CommandInputState {   
    
/** 
*/
class manual_phaser_units : public PromptCommandState {
 public:
  
  /** Constructor sets the location of the target that is being targeted by
   *  the manual phaser mode. It also looks up the remaining energy of that 
   *  target.
   */
  manual_phaser_units(unsigned i_tgt, unsigned n_tgts);
  
  /** Interface to execute the state action. State specific processing
   *  is implemented in the derived class. This method is responsible 
   *  for transitioning the state after executing the state action. 
   *  While executing the state action, this method may also post 
   *  events to the EventQueue.
   */
  virtual void executeAction(CommandInputHandler * handler);
  
  /** Interface to return the prompt corresponding to the state. State 
   *  specific prompt is implemented in the derived class.
   */
  virtual std::string getPrompt() const;
  
 private:
  
  unsigned i_tgt_;
  unsigned n_tgts_;
  target_location loc_;
  double tgt_energy_;
  std::string tgt_type_;
};
    
} // end namespace CommandInputState
} // end namesoace iTrek

#endif
