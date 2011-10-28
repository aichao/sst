/*
 *  CommandQueue.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 2/13/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef COMMAND_QUEUE_HPP
#define COMMAND_QUEUE_HPP

#include <string>
#include <deque>
#include <boost/pool/detail/singleton.hpp>

#include <ACIP/Util/MTSafeQueue.hpp>
#include "CommandData.hpp"

namespace iTrek 
{
  
  /// The CommandQueue is a ACIP::Util::MTSafeQueue of CommandData. The CommandQueue is a singleton.
  typedef boost::details::pool::singleton_default< ACIP::Util::MTSafeQueue< CommandData > > CommandQueue;
  
} // end namespace iTrek

#endif
