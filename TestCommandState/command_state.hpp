/*
 *  command_state.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_command_state_hpp
#define iTrek_command_state_hpp

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <boost/logic/tribool.hpp>
BOOST_TRIBOOL_THIRD_STATE(handled_but_incomplete)

#include "command_data.hpp"
#include "command_inputs.hpp"

namespace iTrek {   

// forward declaration of command_input_handler
class command_input_handler;

/** state in state pattern
 */
class command_state {
 public:
  /** base class needs a virtual destructor
   */
  virtual ~command_state() {}
  
  /** Interface to execute the state action. State specific processing
   *  is implemented in the derived class. This method is responsible 
   *  for transitioning the state after executing the state action. 
   *  While executing the state action, this method may also post 
   *  events to the EventQueue.
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const = 0;
  
  /** Optional interface to return a prompt string. The default 
   *  implementation in this base class returns a NULL 
   *  boost::optional<std::string>(). Derived state classes that 
   *  provide a prompt to the user interface for more command input
   *  when they failed to handle the input tokens need to override 
   *  this method with an implementation that returns the prompt 
   *  string.
   */
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>();
  }
  
 protected:
  /** Change the command_state to state. This is called by the subclass to 
   *  transition the state.
   */
  void change_state(command_input_handler* handler, 
                    boost::shared_ptr<command_state> state) const;
    
  /// Const accessor for the command data
  command_data const& get_command_data(command_input_handler* handler) const;
  
  /** Append the command data. This is called by the concrete state to append 
   *  its processed input data to the command data.
   */
  void append_command_data(command_input_handler* handler, 
                           command_data const& data) const;
  
  /** Clear the command data. This is called by the concrete command state to 
   *  reset the command data to empty.
   */
  void clear_command_data(command_input_handler* handler) const;
  
  /// Clear the command token queue
  void clear_token_queue(command_input_handler* handler) const;
  
  /// Returns the number of command tokens in the command token queue
  std::size_t number_of_tokens_in_queue(command_input_handler* handler) const;
  
  /** Peek at the next element in the command token queue. If the queue is 
   *  empty, the returned command_data is empty
   */
  command_data peek_at_token_queue(command_input_handler* handler) const;
  
  /** Get a specified number of command data tokens from the command queue. If 
   *  the commandvqueue is empty, this method first inserts a prompt event onto 
   *  the event queue using the state's prompt message. Then it waits on the 
   *  command queue for inputs. This method is guaranteed to return with at 
   *  least one token, even if that token is an empty string. This method can 
   *  return less than the requested number of tokens if the command queue does 
   *  not have the requested number of tokens. This usually results from an 
   *  error in command input, which is to be handled by the concrete state. 
   *  Furthermore, the command queue can have more tokens than requested in the 
   *  queue. In this case, only the specified number is popped from the queue 
   *  and returned. This method should only be called by concrete states that 
   *  requires command data from the command queue.
   */
  virtual void get_command_inputs(command_input_handler* handler, 
                                  std::size_t n, command_inputs & tokens) const;
  
  /// Add a DisplayEvent to the EventQueue with the message.
  void add_display_event(command_input_handler* handler, 
                         std::string const& msg) const;
};

} // end namesoace iTrek

#endif
