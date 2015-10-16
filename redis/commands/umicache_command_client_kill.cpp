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
#include "umicache_command_client_kill.hpp"
#include "../umicache_type_redis.hpp"
#include <boost/lexical_cast.hpp>

umi::redis::CommandClientKillType::~CommandClientKillType() {}

umi::redis::CommandClientKillTypeAddres::CommandClientKillTypeAddres(
    const std::string &ip, const std::string &port)
    : m_ip(ip), m_port(port) {}

umi::redis::CommandClientKillTypeAddres::~CommandClientKillTypeAddres() {}

std::vector<uint8_t>
umi::redis::CommandClientKillTypeAddres::Serialize() const {
  umi::redis::RedisTypeArray serialized_command;
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>("ADDR"));
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>(m_ip + ":" + m_port));
  return serialized_command.Serialize();
}

umi::redis::CommandClientKillTypeID::CommandClientKillTypeID(
    const std::string &id)
    : m_id(id) {}

umi::redis::CommandClientKillTypeID::~CommandClientKillTypeID() {}

std::vector<uint8_t> umi::redis::CommandClientKillTypeID::Serialize() const {
  umi::redis::RedisTypeArray serialized_command;
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>("ID"));
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>(m_id));
  return serialized_command.Serialize();
}

static const std::vector<std::string> __command_client_kill_type_type_values__ =
    {"normal", "slave", "pubsub"};

umi::redis::CommandClientKillTypeType::CommandClientKillTypeType(
    CommandClientKillTypeTypeEnum id)
    : m_type(id) {}

umi::redis::CommandClientKillTypeType::~CommandClientKillTypeType() {}

std::vector<uint8_t> umi::redis::CommandClientKillTypeType::Serialize() const {
  umi::redis::RedisTypeArray serialized_command;
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>("TYPE"));
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>(
          __command_client_kill_type_type_values__[static_cast<int>(m_type)]));
  return serialized_command.Serialize();
}

static const std::vector<std::string>
    __command_client_kill_type_skipme_values__ = {"no", "yes"};

umi::redis::CommandClientKillTypeSkipme::CommandClientKillTypeSkipme(
    CommandClientKillTypeSkipmeEnum id)
    : m_type(id) {}

umi::redis::CommandClientKillTypeSkipme::~CommandClientKillTypeSkipme() {}

std::vector<uint8_t>
umi::redis::CommandClientKillTypeSkipme::Serialize() const {
  umi::redis::RedisTypeArray serialized_command;
  serialized_command.redis_array.push_back(
      std::make_unique<RedisTypeBulkString>("SKIPME"));
  serialized_command.redis_array.push_back(std::make_unique<
      RedisTypeBulkString>(
      __command_client_kill_type_skipme_values__[static_cast<int>(m_type)]));
  return serialized_command.Serialize();
}

umi::redis::CommandClientKill::CommandClientKill(
    const std::vector<std::shared_ptr<CommandClientKillType>> &data)
    : umi::redis::CommandRedis("", {}), m_data(data) {}

umi::redis::CommandClientKill::~CommandClientKill() {}

std::vector<uint8_t> umi::redis::CommandClientKill::Serialize() const {
  // This parameters requires additional work as
  // doesnt follow the normal rules of commands
  std::vector<uint8_t> retval;
  retval.reserve(1024);
  retval.push_back('*');
  {
    std::string integer(boost::lexical_cast<std::string>(1 + m_data.size()));
    retval.insert(retval.end(), integer.begin(), integer.end());
    retval.push_back('\r');
    retval.push_back('\n');
  }
  retval.push_back('$');
  retval.push_back('6');
  retval.push_back('\r');
  retval.push_back('\n');
  {
    std::string client_kill("CLIENT");
    retval.insert(retval.end(), client_kill.begin(), client_kill.end());
    retval.push_back('\r');
    retval.push_back('\n');
  }
  retval.push_back('$');
  retval.push_back('4');
  retval.push_back('\r');
  retval.push_back('\n');
  {
    std::string client_kill("KILL");
    retval.insert(retval.end(), client_kill.begin(), client_kill.end());
    retval.push_back('\r');
    retval.push_back('\n');
  }
  for (auto &&i : m_data) {
    std::vector<uint8_t> actual_data(i->Serialize());
    retval.insert(retval.end(), actual_data.begin(), actual_data.end());
  }
  return retval;
}
