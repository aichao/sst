/*
 *  PhotonTargetSector.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/19/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef PHOTON_TARGET_SECTOR_HPP
#define PHOTON_TARGET_SECTOR_HPP

#include "PromptCommandState.hpp"

namespace iTrek { namespace CommandInputState
{   
  
  /** 
   */
  class PhotonTargetSector : public PromptCommandState
  {
  public:
    
    /** Constructor initializes the loopCount for this photon target sector state.
     *  The loop count refers to the count on the number of photons to fire. When
     *  this count is 1, then this is the last photon to fire.
     */
    PhotonTargetSector( unsigned iTgt, unsigned nTgts );
    
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
    
  private:
    
    unsigned iTgt_;
    unsigned nTgts_;
    
  };
  
} } // end namesoace iTrek::CommandInputState

#endif
