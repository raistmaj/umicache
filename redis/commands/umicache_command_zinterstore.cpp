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
#include "umicache_command_zinterstore.hpp"
#include "../umicache_type_redis.hpp"
#include <boost/lexical_cast.hpp>

umi::redis::CommandZInterStore::CommandZInterStore(const std::string &destination, const std::vector<std::string> &keys,
                                                   const std::vector<int> &weights, CommandZInterStoreAggregate agg) try
    : umi::redis::CommandRedis("ZINTERSTORE",
                               {destination}) {
  if (keys.empty()) { return; }
  if (!weights.empty() && weights.size() != keys.size()) { return; }
  else { m_hasWeights = true; }

  m_numkeys = keys.size();
  m_parameters.push_back(destination);
  m_parameters.emplace_back(boost::lexical_cast<std::string>(m_numkeys));
  m_parameters.insert(m_parameters.end(), keys.begin(), keys.end());
  if (m_hasWeights) {
    m_parameters.emplace_back("WEIGHTS");
    for (auto i : weights) {
      m_parameters.emplace_back(boost::lexical_cast<std::string>(i));
    }
  }
  if (agg != CommandZInterStoreAggregate::NO_AGGREGATE) {
    m_hasAgg = true;
    m_parameters.emplace_back("AGGREGATE");
    if (agg == CommandZInterStoreAggregate::SUM) {
      m_parameters.emplace_back("SUM");
    } else if (agg == CommandZInterStoreAggregate::MIN) {
      m_parameters.emplace_back("MIN");
    } else if (agg == CommandZInterStoreAggregate::MAX) {
      m_parameters.emplace_back("MAX");
    }
  }
} catch (boost::bad_lexical_cast &ex) {
  m_parameters.clear();
}

umi::redis::CommandZInterStore::~CommandZInterStore() { }

std::vector<uint8_t> umi::redis::CommandZInterStore::Serialize() const {
  umi::redis::RedisTypeArray append_command;
  if (!m_parameters.empty()) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_operation));
    std::size_t pos = 0;
    // Destination
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
    pos++;
    // Numkeys
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeInteger>(m_parameters[pos]));
    pos++;
    // Keys
    for (std::size_t i = 0; i < m_numkeys; ++i) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
    }
    if (m_hasWeights) {
      // WEIGHTS
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
      // Actual weight
      for (std::size_t i = 0; i < m_numkeys; ++i) {
        append_command.redis_array.push_back(
            std::make_unique<RedisTypeInteger>(m_parameters[pos]));
        pos++;
      }
    }
    if (m_hasAgg) {
      // AGGREGATE
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
      // Actual value
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(m_parameters[pos]));
      pos++;
    }

  }
  return append_command.Serialize();
}