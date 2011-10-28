/*
 *  EventQueue.hpp
 *  TestCommandState
 *
 *  Created by Alan Chao on 1/17/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef EVENT_QUEUE_HPP
#define EVENT_QUEUE_HPP

#include <string>
#include <deque>
#include <boost/pool/detail/singleton.hpp>
#include <boost/shared_ptr.hpp>

#include <ACIP/Util/MTSafeQueue.hpp>
#include "Event.hpp"

namespace iTrek 
{
  
  /// The EventQueue is a ACIP::Util::MTSafeQueue of boost::shared_ptr of Events. The EventQueue is a singleton.
  typedef boost::details::pool::singleton_default< ACIP::Util::MTSafeQueue< boost::shared_ptr< Event > > > EventQueue;
  
} // end namespace iTrek

#endif
