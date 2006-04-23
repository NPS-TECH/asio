//
// basic_resolver_query.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2006 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef ASIO_IP_BASIC_RESOLVER_QUERY_HPP
#define ASIO_IP_BASIC_RESOLVER_QUERY_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include "asio/detail/push_options.hpp"

#include "asio/detail/push_options.hpp"
#include <string>
#include "asio/detail/pop_options.hpp"

namespace asio {
namespace ip {

/// An query produced by a resolver.
/**
 * The asio::ip::basic_resolver_query class template describes an query as
 * returned by a resolver.
 *
 * @par Thread Safety:
 * @e Distinct @e objects: Safe.@n
 * @e Shared @e objects: Unsafe.
 *
 * @par Concepts:
 * Endpoint.
 */
template <typename Protocol>
class basic_resolver_query
{
public:
  /// The protocol type associated with the endpoint query.
  typedef Protocol protocol_type;

#if defined(GENERATING_DOCUMENTATION)
  /// Determine the canonical name of the host specified in the query.
  static const int canonical_name = implementation_defined;

  /// Host name should be treated as a numeric string defining an IPv4 or IPv6
  /// address and no name resolution should be attempted.
  static const int numeric_host = implementation_defined;

  /// Indicate that returned endpoint is intended for use as a locally bound
  /// socket endpoint.
  static const int passive = implementation_defined;
#else
  BOOST_STATIC_CONSTANT(int, canonical_name = AI_CANONNAME);
  BOOST_STATIC_CONSTANT(int, numeric_host = AI_NUMERICHOST);
  BOOST_STATIC_CONSTANT(int, passive = AI_PASSIVE);
#endif

  /// Construct with specified host name and service name for any protocol.
  basic_resolver_query(const std::string& service_name, int flags = passive)
    : hints_(),
      host_name_(),
      service_name_(service_name)
  {
    typename Protocol::endpoint endpoint;
    hints_.ai_flags = flags;
    hints_.ai_family = PF_UNSPEC;
    hints_.ai_socktype = endpoint.protocol().type();
    hints_.ai_protocol = endpoint.protocol().protocol();
  }

  /// Construct with specified host name and service name for any protocol.
  basic_resolver_query(const protocol_type& protocol,
      const std::string& service_name, int flags = passive)
    : hints_(),
      host_name_(),
      service_name_(service_name)
  {
    hints_.ai_flags = flags;
    hints_.ai_family = protocol.family();
    hints_.ai_socktype = protocol.type();
    hints_.ai_protocol = protocol.protocol();
  }

  /// Construct with specified host name and service name for any protocol.
  basic_resolver_query(const std::string& host_name,
      const std::string& service_name, int flags = 0)
    : hints_(),
      host_name_(host_name),
      service_name_(service_name)
  {
    typename Protocol::endpoint endpoint;
    hints_.ai_flags = flags;
    hints_.ai_family = PF_UNSPEC;
    hints_.ai_socktype = endpoint.protocol().type();
    hints_.ai_protocol = endpoint.protocol().protocol();
  }

  /// Construct with specified host name and service name for a given protocol.
  basic_resolver_query(const protocol_type& protocol,
      const std::string& host_name, const std::string& service_name,
      int flags = 0)
    : hints_(),
      host_name_(host_name),
      service_name_(service_name)
  {
    hints_.ai_flags = flags;
    hints_.ai_family = protocol.family();
    hints_.ai_socktype = protocol.type();
    hints_.ai_protocol = protocol.protocol();
  }

  /// Get the hints associated with the query.
  const ::addrinfo& hints() const
  {
    return hints_;
  }

  /// Get the host name associated with the query.
  std::string host_name() const
  {
    return host_name_;
  }

  /// Get the service name associated with the query.
  std::string service_name() const
  {
    return service_name_;
  }

private:
  ::addrinfo hints_;
  std::string host_name_;
  std::string service_name_;
};

} // namespace ip
} // namespace asio

#include "asio/detail/pop_options.hpp"

#endif // ASIO_IP_BASIC_RESOLVER_QUERY_HPP
