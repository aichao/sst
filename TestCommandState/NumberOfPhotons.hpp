/*
 *  NumberOfPhotons.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef NUMBER_OF_PHOTONS_HPP
#define NUMBER_OF_PHOTONS_HPP

#include "PromptCommandState.hpp"

namespace iTrek { namespace CommandInputState
{   
  
  /** 
   */
  class NumberOfPhotons : public PromptCommandState
  {
  public:
    
    /** Interface to execute the state action. State specific processing
     *  is implemented in the derived class. This method is responsible 
     *  for transitioning the state after executing the state action. 
     *  While executing the state action, this method may also post 
     *  events to the EventQueue.
     */
    virtual void executeAction( CommandInputHandler * handler );
    
    /** Interface to return the prompt corresponding to the state. State 
     *  specific prompt is implemented in the derived class.
     */
    virtual std::string getPrompt() const;
    
  };
  
} } // end namesoace iTrek::CommandInputState

#endif
