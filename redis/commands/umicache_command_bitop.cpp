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
#include "umicache_command_bitop.hpp"
#include "../umicache_type_redis.hpp"

const std::vector<std::string> umi::redis::CommandBitop::__command__bit__op__ = {
    "AND", "OR", "XOR", "NOT"};

umi::redis::CommandBitop::CommandBitop(
    operation op, const std::string &destkey, const std::string &singleValue,
    std::initializer_list<std::string> &&values)
    : umi::redis::CommandRedis(
          "BITOP", {__command__bit__op__[static_cast<int>(op)], destkey, singleValue}) {
  if (values.size() > 0) {
    m_parameters.insert(m_parameters.end(), values.begin(), values.end());
  }
}

umi::redis::CommandBitop::~CommandBitop() {}

std::vector<uint8_t> umi::redis::CommandBitop::Serialize() const {
  umi::redis::RedisTypeArray append_command;
  if (!m_parameters.empty()) {
    append_command.redis_array.push_back(
        std::make_unique<RedisTypeBulkString>(m_operation));
    for (auto &&i : m_parameters) {
      append_command.redis_array.push_back(
          std::make_unique<RedisTypeBulkString>(i));
    }
  }
  return append_command.Serialize();
}
