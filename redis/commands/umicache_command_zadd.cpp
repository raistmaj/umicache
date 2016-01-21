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
#include "umicache_command_zadd.hpp"
#include "../umicache_type_redis.hpp"
#include <boost/lexical_cast.hpp>

umi::redis::CommandZAdd::CommandZAdd(const std::string &key, CommandZAddBehavior bh, CommandZAddModify modify,
                                     CommandZAddIncr incr, const std::vector<int> &score,
                                     const std::vector<std::string> &member)
    : umi::redis::CommandRedis("ZADD", {}) {
  if (score.size() != member.size() || score.empty()) { return; }
  m_parameters.push_back(key);
  if (bh != CommandZAddBehavior::NON_SPECIFIED) {
    m_hasBH = true;
    m_parameters.emplace_back(((bh == CommandZAddBehavior::NX) ? "NX" : "XX"));
  }
  if (modify == CommandZAddModify::CH) {
    m_hasModify = true;
    m_parameters.emplace_back("CH");
  }
  if (incr == CommandZAddIncr::INCR) {
    m_hashIncr = true;
    m_parameters.emplace_back("INCR");
  }
  for (std::size_t i = 0; i < score.size(); ++i) {
    try {
      m_parameters.emplace_back(boost::lexical_cast<std::string>(score[i]));
    } catch (boost::bad_lexical_cast &ex) {
      m_parameters.clear();
      return;
    }
    m_parameters.push_back(member[i]);
  }
}

umi::redis::CommandZAdd::~CommandZAdd() { }

std::vector<uint8_t> umi::redis::CommandZAdd::Serialize() const {
  umi::redis::RedisTypeArray append_command;
  if (!m_parameters.empty()) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_operation));
    std::size_t pos = 0;
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
    pos++;
    if (m_hasBH) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
    }
    if (m_hasModify) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
    }
    if (m_hashIncr) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
    }
    while (pos < m_parameters.size()) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeInteger>(m_parameters[pos]));
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos + 1]));
      pos += 2;
    }
  }
  return append_command.Serialize();
}