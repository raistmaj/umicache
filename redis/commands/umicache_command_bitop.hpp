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
#ifndef UMI_CACHE_COMMAND_REDIS_BITOP_H
#define UMI_CACHE_COMMAND_REDIS_BITOP_H

#include "../umicache_command_redis.hpp"

namespace umi {
namespace redis {

/**
 * Basic append command used for the redis infraestructure
 */
class CommandBitop : public umi::redis::CommandRedis {
  static const std::vector<std::string> __command__bit__op__;

public:
  /**
   * Allowed operations on the bit op
   */
  enum class operation : int { AND = 0, OR = 1, XOR = 2, NOT = 3 };

  /**
   * Constructor of the command
   *
   * @param operation we want to do with the values
   * @param destination key to store the result
   * @param one value is required
   * @param list of possible values
   */
  CommandBitop(operation op, const std::string &destkey,
               const std::string &singleValue,
               std::initializer_list<std::string> &&values);

  /**
   * Release the resources used by the command
   */
  ~CommandBitop();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  std::vector<uint8_t> Serialize() const;
};
}
}

#endif
