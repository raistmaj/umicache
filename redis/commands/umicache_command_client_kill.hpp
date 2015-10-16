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
#ifndef UMI_CACHE_COMMAND_REDIS_CLIENT_KILL_H
#define UMI_CACHE_COMMAND_REDIS_CLIENT_KILL_H

#include "../umicache_command_redis.hpp"
#include <memory>

namespace umi {
namespace redis {

/**
 * The commands we can send to the ClientKill command
 */
class CommandClientKillType {
public:
  /**
   * Destructor
   */
  virtual ~CommandClientKillType() = 0;
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  virtual std::vector<uint8_t> Serialize() const = 0;
};

/**
 * The ADDR Type
 */
class CommandClientKillTypeAddres : public CommandClientKillType {
public:
  /**
   * Constructor of the class
   *
   * @param ip With the ip we want to kill
   * @param port we use to communicate with that client
   */
  CommandClientKillTypeAddres(const std::string &ip, const std::string &port);
  /**
   * Destructor of the class
   */
  ~CommandClientKillTypeAddres();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  std::vector<uint8_t> Serialize() const;

protected:
  /**
   * Ip of the client we want to kill
   */
  std::string m_ip;
  /**
   * Port of the client we want to kill
   */
  std::string m_port;
};

/**
 * The ADDR Type
 */
class CommandClientKillTypeID : public CommandClientKillType {
public:
  /**
   * Constructor of the class
   *
   * @param id With the id we want to kill
   */
  CommandClientKillTypeID(const std::string &id);
  /**
   * Destructor of the class
   */
  ~CommandClientKillTypeID();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  std::vector<uint8_t> Serialize() const;

protected:
  /**
   * ID of the client we want to kill
   */
  std::string m_id;
};

/**
 * The TYPE Type
 */
class CommandClientKillTypeType : public CommandClientKillType {
public:
  enum class CommandClientKillTypeTypeEnum : int {
    normal = 0,
    slave = 1,
    pubsub = 2
  };

public:
  /**
   * Constructor of the class
   *
   * @param id With the id we want to kill
   */
  CommandClientKillTypeType(CommandClientKillTypeTypeEnum id);
  /**
   * Destructor of the class
   */
  ~CommandClientKillTypeType();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  std::vector<uint8_t> Serialize() const;

protected:
  /**
   * ID of the client we want to kill
   */
  CommandClientKillTypeTypeEnum m_type;
};

/**
 * The TYPE Type
 */
class CommandClientKillTypeSkipme : public CommandClientKillType {
public:
  enum class CommandClientKillTypeSkipmeEnum : int { no = 0, yes = 1 };

public:
  /**
   * Constructor of the class
   *
   * @param id With the id we want to kill
   */
  CommandClientKillTypeSkipme(CommandClientKillTypeSkipmeEnum id);
  /**
   * Destructor of the class
   */
  ~CommandClientKillTypeSkipme();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  std::vector<uint8_t> Serialize() const;

protected:
  /**
   * ID of the client we want to kill
   */
  CommandClientKillTypeSkipmeEnum m_type;
};

/**
 * Basic Block Pop command used for the redis infraestructure
 */
class CommandClientKill : public umi::redis::CommandRedis {
public:
  /**
   * Constructor of the command
   *
   * @param Source conaints elements
   * @param Destination
   * @param timeout to block
   */
  CommandClientKill(const std::vector<std::shared_ptr<CommandClientKillType>> &data);
  /**
   * Release the resources used by the command
   */
  ~CommandClientKill();
  /**
   * Serializes the command into a vector
   * @return A vector of bytes with the full serialized command
   * prepared to be sent by the network
   */
  std::vector<uint8_t> Serialize() const;
protected:
  /**
   * Array of elements we want to send with the client kill command
   */
  std::vector<std::shared_ptr<CommandClientKillType>> m_data;
};
}
}

#endif
