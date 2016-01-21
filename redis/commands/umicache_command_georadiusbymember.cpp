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
#include "umicache_command_georadiusbymember.hpp"
#include "../umicache_type_redis.hpp"
#include "../../umicache_exception.hpp"
#include <boost/lexical_cast.hpp>

static const char *const __g_command_geo_radiusbymember__[] = {"m", "km", "mi", "ft"};

umi::redis::CommandGeoRADIUSByMember::CommandGeoRADIUSByMember(
    const std::string &key, const std::string &member, double radius,
    CommandGeoRADIUSByMemberUnit unit, int coords, int count) try : umi
  ::redis::CommandRedis("GEORADIUSBYMEMBER",
                        {key, member, boost::lexical_cast<std::string>(radius),
                         __g_command_geo_radiusbymember__[static_cast<int>(unit)]}) {
    if (coords & WITHCOORD) {
      m_parameters.push_back("WITHCOORD");
    }
    if (coords & WITHDIST) {
      m_parameters.push_back("WITHDIST");
    }
    if (coords & WITHHASH) {
      m_parameters.push_back("WITHHASH");
    }
    if (count >= 0) {
      m_parameters.push_back("COUNT");
      m_parameters.push_back(boost::lexical_cast<std::string>(count));
    }
  }
catch (boost::bad_lexical_cast &) {
}

umi::redis::CommandGeoRADIUSByMember::~CommandGeoRADIUSByMember() {}

std::vector<uint8_t> umi::redis::CommandGeoRADIUSByMember::Serialize() const {
  size_t i = 0;
  umi::redis::RedisTypeArray append_command;
  append_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>(m_operation));
  while (i < m_parameters.size()) {
    if (m_parameters[i] != "COUNT") {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[i]));
    } else {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[i]));
      ++i;
      break;
    }
    ++i;
  }
  // Count case
  if (i < m_parameters.size()) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeInteger>(m_parameters[i]));
  }
  return append_command.Serialize();
}
