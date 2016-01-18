/**
  Copyright 2016 José Gerardo Palma Durán. All rights reserved.

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
  policies, either expressed or implied, of José Gerardo Palma Durán.
*/
#include "umicache_command_sort.hpp"
#include "../umicache_type_redis.hpp"
#include <boost/lexical_cast.hpp>

umi::redis::CommandSort::CommandSort(const std::string &key, const std::string &bypattern,
                                     const umi::redis::CommandSort::CommandSortLimit &lim,
                                     const std::vector<std::string> &getpattern,
                                     CommandSortType t,
                                     bool alpha,
                                     const std::string &destination)
    : umi::redis::CommandRedis("SORT", {key}) {
  if (!bypattern.empty()) {
    m_hasPattern = true;
    m_parameters.push_back("BY");
    m_parameters.push_back(bypattern);
  }
  if (lim.m_init) {
    m_hasLimit = true;
    m_parameters.push_back("LIMIT");
    try {
      m_parameters.push_back(boost::lexical_cast<std::string>(lim.m_offset));
      m_parameters.push_back(boost::lexical_cast<std::string>(lim.m_count));
    } catch (boost::bad_lexical_cast &ex) { }
  }
  for (auto &i :getpattern) {
    m_parameters.push_back("GET");
    m_parameters.push_back(i);
  }
  if (t != CommandSortType::NONE) {
    if (t == CommandSortType::ASC) {
      m_parameters.push_back("ASC");
    } else {
      m_parameters.push_back("DESC");
    }
  }
  if (alpha) {
    m_parameters.push_back("ALPHA");
  }
  if (!destination.empty()) {
    m_parameters.push_back("STORE");
    m_parameters.push_back(destination);
  }
}

umi::redis::CommandSort::~CommandSort() { }

std::vector<uint8_t> umi::redis::CommandSort::Serialize() const {
  umi::redis::RedisTypeArray append_command;
  append_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>(m_operation));
  std::size_t i = 0;
  if (m_hasPattern) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[i]));
    i++;
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[i]));
    i++;
  }
  if (m_hasLimit) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[i]));
    i++;
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeInteger>(m_parameters[i]));
    i++;
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeInteger>(m_parameters[i]));
    i++;
  }
  while (i < m_parameters.size()) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_parameters[i]));
    i++;
  }

  return append_command.Serialize();
}