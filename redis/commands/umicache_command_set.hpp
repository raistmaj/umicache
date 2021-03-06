/**
  Copyright 2016 José Gerardo Palma Durán. All rights reserved.

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
  policies, either expressed or implied, of José Gerardo Palma Durán.
*/
#ifndef UMICACHE_UMICACHE_COMMAND_SET_HPP
#define UMICACHE_UMICACHE_COMMAND_SET_HPP

#include "../umicache_command_redis.hpp"

namespace umi {
    namespace redis {
        /**
         * Basic command to get set a key value pair
         */
        class CommandSet : public umi::redis::CommandRedis {
        public:
            enum CommandSetOption {
                NO_OPTION,
                NX,
                XX
            };

            /**
             * Constructor of the command
             */
            CommandSet(const std::string &key,
                       const std::string &value,
                       int expireSeconds = -1,
                       int expiremilliseconds = -1,
                       CommandSetOption op = NO_OPTION);

            /**
             * Release the resources used by the command
             */
            ~CommandSet();

            /**
             * Serializes the command into a vector
             * @return A vector of bytes with the full serialized command
             * prepared to be sent by the network
             */
            std::vector<uint8_t> Serialize() const;

        private:
            bool m_hasSeconds = false;
            bool m_hasMilliseconds = false;
            bool m_hasOp = false;
        };
    }
}


#endif //UMICACHE_UMICACHE_COMMAND_SET_HPP
