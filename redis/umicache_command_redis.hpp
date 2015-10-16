/**
  Copyright 2015 Jose Gerardo Palma Duran. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY <COPYRIGHT HOLDER> ''AS IS'' AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
  EVENT SHALL <COPYRIGHT HOLDER> OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of Jose Gerardo Palma Duran.
*/
#ifndef UMI_CACHE_COMMAND_REDIS_HPP
#define UMI_CACHE_COMMAND_REDIS_HPP

#include "../umicache_command.hpp"
#include <cstdint>
#include <vector>
#include <string>
#include <initializer_list>

namespace umi {
namespace redis {
/**
 * Command redis implements the common interface for the full
 * list of redis commands
 */
class CommandRedis : public umi::Command {
public:
  /**
   * Desturctor of the Redis command release its resources
   */
  virtual ~CommandRedis();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  virtual std::vector<uint8_t> Serialize() const = 0;
  /**
   * Get the list of parameters of the Command
   * @return List of parameters used in the Command
   */
  const std::vector<std::string> &GetParameters() const;

protected:
  /**
   * Creates a command with a full list of parameters
   * @param operation with the operation we want to
   * execute with this parameter
   * @param parameters with the list of elements we want to
   * use
   */
  CommandRedis(const std::string &operation,
               const std::vector<std::string> &&parameters);
  /**
   * Creates a command with a initializer list of parameters
   * @param parameters with the list of parameters we want to
   * use, the first one is the operation
   */
  CommandRedis(std::initializer_list<std::string> &&parameters);

protected:
  /**
   * The actual operation we want to use on the command
   */
  std::string m_operation;
  /**
   * List of parameters we will use in the serialization
   */
  std::vector<std::string> m_parameters;
};
}
}

#endif
