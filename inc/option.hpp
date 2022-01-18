#pragma once

#include <variant>
#include <cassert>

#include "error.hpp"

namespace ec {

template<typename T = uint8_t>
class option {
protected:
  const std::variant<T, error> var;

public:
  /**
   * Constructor for storing an actual value
   * inside the option.
   */
  constexpr option(T real) : var(real) {}

  /**
   * Constructor for storing an error
   * inside the option.
   */
  constexpr option(error err) : var(err) {}

  /**
   * Cast operator for converting the option
   * to an error. If there was no error
   * stored in the option, OK is returned.
   */
  operator error() const {
    const auto ptr = std::get_if<error>(&this->var);

    if (ptr == nullptr) [[likely]]
      return error::ok();

    return *ptr;
  }

  /**
   * Class method alias for casting the
   * option to an error.
   * See overloaded error cast operator
   * for more info.
   */
  constexpr error err() const {
    return static_cast<error>(*this);
  }

  /**
   * Cast operator for converting the option
   * into the desireable value. If there was no
   * actual value inside the option, the
   * assert fails and the program should exit.
   *
   * Do not use this cast if not sure about
   * what is in the option. Before using this
   * cast, one has to always check if there
   * is an error in the option istead with
   * (ec::error) cast operator.
   */
  operator T() const {
    const auto ptr = std::get_if<T>(&this->var);

    assert(ptr);

    return *ptr;
  }

  /**
   * Class method alias for casting the
   * option to the desireable value.
   * See overloaded value cast operator
   * for more info.
   */
  constexpr T val() const {
    return static_cast<T>(*this);
  }

  /**
   * Cast operator for converting the option
   * into a boolean. This returns true when there is
   * an error inside, otherwise returns false.
   */
  operator bool() const {
    const auto ptr = std::get_if<error>(&this->var);

    return ptr != nullptr;
  }
};

} // namespace ec
