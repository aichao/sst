/*
 *  shields_query.hpp
 *  iTrek
 *
 *  Created by Alan Chao on 6/14/15.
 *  Copyright 2010-2015 Alan I Chao. All rights reserved.
 *
 */

#ifndef iTrek_shields_query_hpp
#define iTrek_shields_query_hpp

#include "command_state.hpp"

namespace iTrek {
namespace command_input_state {

/**
 */
class shields_query : public command_state {
 public:
  /** This method transitions the state to shields_transfer if the response 
   *  to the query is "yes" and to shields_toggle if the response to the query 
   *  is "no". In these cases, this method returns false and all further 
   *  command tokens are ignored. This method does not prompt the use to answer 
   *  only yes or no as in the original sst. If the response cannot be matched 
   *  to "yes" or "no", then the command is deemed an error. 
   */
  virtual boost::logic::tribool handle(command_input_handler* handler) const;

  /// Return the prompt corresponding to the get_command state.
  virtual boost::optional<std::string> prompt() const {
    return boost::optional<std::string>("Do you wish to change shield energy? ");
  }
};

} // end namespace command_input_state
} // end namespace iTrek

#endif
