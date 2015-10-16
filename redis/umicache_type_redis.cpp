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
#include "umicache_type_redis.hpp"
#include <sstream>
#include <cstring>
#include <boost/lexical_cast.hpp>

std::vector<uint8_t> umi::redis::RedisType::Serialize() const {
  return std::vector<uint8_t>();
}

umi::redis::RedisTypeSimpleString::RedisTypeSimpleString(
    const std::string &text)
    : simple_string(text) {}

umi::redis::RedisTypeSimpleString::~RedisTypeSimpleString() {}

std::vector<uint8_t> umi::redis::RedisTypeSimpleString::Serialize() const {
  std::vector<uint8_t> retval;
  retval.reserve(128);
  retval.push_back(static_cast<uint8_t>('+'));
  retval.insert(retval.end(), simple_string.begin(), simple_string.end());
  retval.push_back(static_cast<uint8_t>('\r'));
  retval.push_back(static_cast<uint8_t>('\n'));
  return retval;
}

umi::redis::RedisTypeError::RedisTypeError(const std::string &error)
    : error_string(error) {}

umi::redis::RedisTypeError::~RedisTypeError() {}

std::vector<uint8_t> umi::redis::RedisTypeError::Serialize() const {
  std::vector<uint8_t> retval;
  retval.reserve(128);
  retval.push_back(static_cast<uint8_t>('-'));
  retval.insert(retval.end(), error_string.begin(), error_string.end());
  retval.push_back(static_cast<uint8_t>('\r'));
  retval.push_back(static_cast<uint8_t>('\n'));
  return retval;
}

umi::redis::RedisTypeInteger::RedisTypeInteger(int64_t valueI) try
    : integer(boost::lexical_cast<std::string>(valueI)) {
} catch (boost::bad_lexical_cast &) {
}

umi::redis::RedisTypeInteger::RedisTypeInteger(const std::string &value)
    : integer(value) {}

umi::redis::RedisTypeInteger::~RedisTypeInteger() {}

std::vector<uint8_t> umi::redis::RedisTypeInteger::Serialize() const {
  std::vector<uint8_t> retval;
  retval.reserve(128);
  retval.push_back(static_cast<uint8_t>(':'));
  retval.insert(retval.end(), integer.begin(), integer.end());
  retval.push_back(static_cast<uint8_t>('\r'));
  retval.push_back(static_cast<uint8_t>('\n'));
}

umi::redis::RedisTypeBulkString::RedisTypeBulkString(const std::string &data)
    : bulk_string(data) {}

umi::redis::RedisTypeBulkString::RedisTypeBulkString(const char *data)
    : bulk_string(data, data + strlen(data)) {}

umi::redis::RedisTypeBulkString::RedisTypeBulkString(
    const std::vector<uint8_t> &data)
    : bulk_string(data.begin(), data.end()) {}

umi::redis::RedisTypeBulkString::~RedisTypeBulkString() {}

std::vector<uint8_t> umi::redis::RedisTypeBulkString::Serialize() const {
  std::vector<uint8_t> retval;
  try {
    retval.reserve(bulk_string.size() + 64);
    retval.push_back(static_cast<uint8_t>('$'));
    if (isNull) {
      retval.push_back('-');
      retval.push_back('1');
    } else {
      {
        std::string valueToInsert(
            boost::lexical_cast<std::string>(bulk_string.size()));
        retval.insert(retval.end(), valueToInsert.begin(), valueToInsert.end());
      }
      retval.push_back(static_cast<uint8_t>('\r'));
      retval.push_back(static_cast<uint8_t>('\n'));
      retval.insert(retval.end(), bulk_string.begin(), bulk_string.end());
    }
    retval.push_back(static_cast<uint8_t>('\r'));
    retval.push_back(static_cast<uint8_t>('\n'));
  } catch (boost::bad_lexical_cast &) {
    retval.clear();
  }
  return retval;
}

umi::redis::RedisTypeArray::RedisTypeArray() {}

umi::redis::RedisTypeArray::~RedisTypeArray() {}

std::vector<uint8_t> umi::redis::RedisTypeArray::Serialize() const {
  std::vector<uint8_t> retval;
  try {
    retval.reserve(1024);
    retval.push_back(static_cast<uint8_t>('*'));
    {
      std::string final_integer(
          boost::lexical_cast<std::string>(redis_array.size()));
      retval.insert(retval.end(), final_integer.begin(), final_integer.end());
    }
    retval.push_back('\r');
    retval.push_back('\n');
    for (auto &&element : redis_array) {
      std::vector<uint8_t> auxSerialization(element->Serialize());
      std::string single(auxSerialization.begin(), auxSerialization.end());
      retval.insert(retval.end(), single.begin(), single.end());
    }
  } catch (boost::bad_lexical_cast &ex) {
    retval.clear();
  }

  return retval;
}
