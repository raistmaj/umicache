/**
  Copyright 2015 Jose Gerardo Palma Duran. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY José Gerardo Palma Durán ''AS IS'' AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
  EVENT SHALL José Gerardo Palma Durán OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
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
#ifndef UMI_CACHE_COMMAND_REDIS_CLUSTER_FORGET_H
#define UMI_CACHE_COMMAND_REDIS_CLUSTER_FORGET_H

#include "../umicache_command_redis.hpp"

namespace umi {
namespace redis {

/**
 * Basic command to get our actual name
 */
class CommandClusterForget : public umi::redis::CommandRedis {
public:
  /**
   * Constructor of the command
   */
  CommandClusterForget(const std::string &nodeid);
  /**
   * Release the resources used by the command
   */
  ~CommandClusterForget();
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
