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
#include "umicache_command_zrevrange.hpp"
#include "../umicache_type_redis.hpp"
#include <boost/lexical_cast.hpp>

umi::redis::CommandZRevRange::CommandZRevRange(const std::string &key, int start, int stop, bool score) try
    : umi::redis::CommandRedis("ZREVRANGE",
                               {key, boost::lexical_cast<std::string>(start), boost::lexical_cast<std::string>(stop)}) {
  m_hasScore = score;
} catch (boost::bad_lexical_cast &ex) {
  m_parameters.clear();
}

umi::redis::CommandZRevRange::~CommandZRevRange() { }

std::vector<uint8_t> umi::redis::CommandZRevRange::Serialize() const {
  umi::redis::RedisTypeArray append_command;
  if (!m_parameters.empty()) {
    append_command.redis_array.emplace_back(
        std::make_unique<RedisTypeBulkString>(m_operation));
    append_command.redis_array.emplace_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[0]));
    append_command.redis_array.emplace_back(
        std::make_unique<RedisTypeInteger>(m_parameters[1]));
    append_command.redis_array.emplace_back(
        std::make_unique<RedisTypeInteger>(m_parameters[2]));
    if (m_hasScore) {
      append_command.redis_array.emplace_back(
          std::make_unique<RedisTypeBulkString>("WITHSCORES"));
    }
  }
  return append_command.Serialize();
}