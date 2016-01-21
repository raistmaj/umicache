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
#ifndef UMI_CACHE_TYPE_REDIS_HPP
#define UMI_CACHE_TYPE_REDIS_HPP

#include <vector>
#include <cstdint>
#include <string>
#include <memory>

namespace umi {
namespace redis{
/**
  In RESP, the type of some data depends on the first byte:
  For Simple Strings the first byte of the reply is "+"
  For Errors the first byte of the reply is "-"
  For Integers the first byte of the reply is ":"
  For Bulk Strings the first byte of the reply is "$"
  For Arrays the first byte of the reply is "*"
*/

/**
 * Base type used in the redis protocol
 * */
struct RedisType {
  public:
    /**
    * Destructor of the base class for types used int he protocol
    */
    virtual ~RedisType() {}
    /**
     * Serializes the type
     */
    virtual std::vector<uint8_t> Serialize() const;
    /**
     * Flag used to identify if the actual parameter is Null(nil)
     */
    bool isNull = false;
};

/**
 * Simple String type
 */
struct RedisTypeSimpleString : public RedisType {
  public:
    /**
     * Constructor of the simple string, it just copy internally
     * that content
     *
     * @param text with the text we want to use
     */
    RedisTypeSimpleString(const std::string &text);
    /**
     * Destructor of the simple string
     */
    ~RedisTypeSimpleString();
    /**
     * For simple strings the first byte of the reply is +
     * Followed by the text we want to send
     * Ended in \r\n
     */
    std::vector<uint8_t> Serialize() const;
    /**
     * Internal text we want to send
     */
    std::string simple_string;
};

/**
 * Used for errors, the first byte of the reply is -
 */
struct RedisTypeError : public RedisType {
  public:
    /**
     * Error string used in the type definition
     *
     * @error used in the communication
     */
    RedisTypeError(const std::string &error);
    /**
     * Desturctor of the class
     */
    ~RedisTypeError();
    /**
     * Serializes the text "-" + "error" + "\r\n"
     */
    std::vector<uint8_t> Serialize() const;
    /**
     * Internal text used for errors
     */
    std::string error_string;
};

/**
 * Type to represent any integer the first by is :
 */
struct RedisTypeInteger : public RedisType {
  public:
    /**
     * Used in responses to send integers
     * @param value with the integer we want to use
     */
    RedisTypeInteger(int64_t value);
    /**
     * Used in responses to send integers
     * @param value with the integer we want to use
     */
    RedisTypeInteger(const std::string &value);
    /**
     * Clean the resources used by the integer
     */
    ~RedisTypeInteger();
    /**
     * Serializes the integer
     */
    std::vector<uint8_t> Serialize() const;
    /**
     * Integer value we want to use in the communication
     */
    std::string integer = "0";
};

/**
 * Used to send bulk strings $size\r\ntext\r\n
 */
struct RedisTypeBulkString : public RedisType {
  public:
    /**
     * Used to manage big strings or string with special characters
     */
    RedisTypeBulkString(const std::string &data);
    /**
     * Used to manage big strings or string with special characters
     */
    RedisTypeBulkString(const char *data);
    /**
     * Used to manage big strings or string with special characters
     */
    RedisTypeBulkString(const std::vector<uint8_t> &data);
    /**
    * Destructor release its resources
    */
    ~RedisTypeBulkString();
    /**
     * Serializes the bulk string
     */
    std::vector<uint8_t> Serialize() const;
    /**
     * The bulk string itself
     */
    std::string bulk_string;
};
/**
 * Used to store Arrays
 */
struct RedisTypeArray : public RedisType {
  public:
    /**
     * Constructor of the array
     */
    RedisTypeArray();
    /**
     * Clean the resources used by the array
     */
    ~RedisTypeArray();
    /**
     * Serializes the array
     */
    std::vector<uint8_t> Serialize() const;
    /**
     * Internal array of elements
     */
    std::vector<std::unique_ptr<RedisType>> redis_array;
};
}
}

#endif
