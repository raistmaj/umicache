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
#include "umicache_command_geoadd.hpp"
#include "../umicache_type_redis.hpp"
#include "../../umicache_exception.hpp"
#include <boost/lexical_cast.hpp>

umi::redis::CommandGeoADD::CommandGeoADD(
    const std::string &key, const std::vector<CommandGeoContent> &data) try
    : umi
  ::redis::CommandRedis("GEOADD", {key}) {
    if (!data.empty()) {
      for (auto &&i : data) {
        m_parameters.push_back(boost::lexical_cast<std::string>(i.longitude));
        m_parameters.push_back(boost::lexical_cast<std::string>(i.latitude));
        m_parameters.push_back(i.member);
      }
    } else {
      m_parameters.clear();
      throw umi::CacheCommandException("GEOADD", "No data provided");
    }
  }
catch (boost::bad_lexical_cast &) {
}

umi::redis::CommandGeoADD::~CommandGeoADD() {}

std::vector<uint8_t> umi::redis::CommandGeoADD::Serialize() const {
  umi::redis::RedisTypeArray append_command;
  append_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>(m_operation));
  if (!m_parameters.empty()) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[0]));
    for (int i = 1; i < m_parameters.size() && i + 2 <= m_parameters.size();
         i += 3) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeSimpleString>(m_parameters[i]));
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeSimpleString>(m_parameters[i + 1]));
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[i + 2]));
    }
  }
  return append_command.Serialize();
}
