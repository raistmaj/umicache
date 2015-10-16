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
#ifndef UMI_CACHE_CONFIG_REDIS_HPP
#define UMI_CACHE_CONFIG_REDIS_HPP

#include "../umicache_config.hpp"
#include <string>

namespace umi {
namespace redis{
/**
 * File to configure the connection against a Redis cache
 */
class CacheConfigRedis : public umi::CacheConfig {
  public:
    /**
     * Default consturctor of the redis configuration file
     * takes the default parameters to configure a valid connection
     * against a redis cache
     */
    CacheConfigRedis();
    /**
     * Release the resources used by the redis cache
     */
    virtual ~CacheConfigRedis();
    /**
     * Gets the Password
     */
    const std::string &GetPassword() const;
    /**
     * Sets the password
     */
    void SetPassword(const std::string &val);

  private:
    /**
     * Some redis nodes may require additional authentication before
     * we start sending commands. This is the default system password
     */
    std::string m_password;
};
}
}

#endif
