/*
 *  phasers_mode.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 10/22/11.
 *  Copyright 2011 Alan I Chao. All rights reserved.
 *
 */

#ifndef PHASERS_MODE_HPP
#define PHASERS_MODE_HPP

#include "PromptCommandState.hpp"

namespace iTrek { 
namespace CommandInputState {   
  
/** 
 */
class phasers_mode : public PromptCommandState {
 public:
  
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
};
  
} // end namespace CommandInputState
} // end namesoace iTrek

#endif
