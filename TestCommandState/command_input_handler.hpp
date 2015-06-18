/*
 *  command_input_handler.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 1/16/10.
 *  Copyright 2010 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_command_input_handler_hpp
#define iTrek_command_input_handler_hpp

#include <deque>
#include <string>

#include <boost/shared_ptr.hpp>

#include "command_input_event.hpp"
#include "command_data.hpp"

namespace iTrek {
  
// forward declaration of command_state
class command_state;

/** context in state pattern
 */
class command_input_handler {
 public:
  /** Initializes the command state and command data. 
   */
  command_input_handler();
  
  /** Client interface to handles command input events using the command 
   *  state machine. This method tokenizes the command input event (string)
   *  and pushes the tokens to a fifo queue. It then forwards the request
   *  to handle these tokens to the current command state. The command state
   *  is responsible for determining whether it can handle the command 
   *  token(s) in the queue. On success, the state is responsible for
   *  transitioning the current state to the next state, and this method 
   *  will continue to forward the request to the current state until
   *  i) the command data is complete, or
   *  ii) more command inputs are needed to complete the command data
   *  In the first case, this method returns true indicating that the
   *  command data is complete. The client then accesses this command data
   *  using the command_data interface. In the second case, this method 
   *  returns false indicating that more inputs are needed to complete the 
   *  command. The client then accesses the current state using the 
   *  current_state inteface and use it to get the corresponding prompt
   *  for the next command input needed to complete the command data.
   *  While processing the command input, a state may also post events to 
   *  the EventQueue.
   */
  bool handle(command_input_event & cmd_str);
  
  /// const accessor for command data
  command_data const& get_command_data() const { return command_data_; }
  
  /// reset the command data to an empty string
  void clear_command_data() { command_data_.clear(); }
  
  /// const accessor for the display events
  std::string const& get_display_events() const { return disp_events_; }
  
  /// clear the display events
  void clear_display_events() { disp_events_.clear(); }
  
  /// const accessor for current command state
  command_state const& current_state() const { return *state_; }
  
private:
  
  /** command_state is a friend of this class so that it
   *  can call change_state() to change the state.
   */
  friend class command_state;
  
  /// change the command_state to state
  void change_state(boost::shared_ptr<command_state> state) { 
    state_ = state; 
  }
  
  /** Reference to the current command_state object. 
   *  This should be a smart pointer (or we must explicitly manage its
   *  destruction on transitions) if the states are not singletons.
   */
  boost::shared_ptr<command_state> state_;
  
  /// fifo queue for cmannd input tokens
  std::deque<command_input_event> command_tokens_;
  
  /// maintain the command data
  command_data command_data_;
  
  /// maintain the display events
  std::string disp_events_;
};
  
} // end namesoace iTrek

#endif
