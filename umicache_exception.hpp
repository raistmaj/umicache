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
#ifndef UMI_CACHE_EXCEPTION_HPP
#define UMI_CACHE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace umi {
/**
 * Class used for the exception management on the
 * cache library
 *
 * It is compatible with stl exception class
 */
class CacheException : public std::exception {
  public:
    /**
     * Destructor of the cache exception
     * */
    virtual ~CacheException() = 0;
    /**
     * what happened
     * */
    virtual const char *what() const noexcept = 0;
};

/**
 * Class used for exceptions under the command
 * */
class CacheCommandException : public CacheException {
  public:
    /**
     * Constructor of the cache command exception
     *
     * @param command the command we are going to use
     * @param message test
     * */
    CacheCommandException(const std::string &command,
			  const std::string &message);
    /**
     * The Destructor of the command exception
     * */
    virtual ~CacheCommandException();
    /**
     * Returns c string with the description of what happened
     * */
    virtual const char *what() const noexcept;

  protected:
    /**
     * Buffer used to store the content of the message
     * */
    std::string m_buffer;
};
}

#endif
