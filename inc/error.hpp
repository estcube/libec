#pragma once

#include <cstdint>
#include <cstring>

namespace ec {

class error {
public:
  const uint8_t code;
  const uint32_t argument : 24;

  /**
   * Default constructor.
   * This initializes all the parameters to 0.
   */
  constexpr error() : code(0), argument(0) {}

  /**
   * Constructor for initializing an error from full error code
   * which also includes the argument to the error
   */
  constexpr error(uint32_t full) : code(full & 0xFF), argument(full >> 8) {}

  /**
   * Constructor for initializing an error with an error code
   * and an argument.
   */
  constexpr error(uint8_t code, uint32_t argument) : code(code), argument(argument) {}

  /**
   * Constructor for initializing an error with an error code
   * and another error as an argument.
   *
   * Note that 8 MSBs of the argument error will be lost.
   */
  constexpr error(uint8_t code, const error &other) : code(code), argument(other.code | other.argument << 8) {}

  /**
   * Copy constructor
   */
  constexpr error(const error &other) : code(other.code), argument(other.argument) {}

  /**
   * This is used to create an error class which indicates
   * that no error has occurred.
   */
  constexpr static error ok() noexcept {
    return error();
  }

  /**
   * Cast operator from ec::error to uint32_t.
   * This produces a bitfield, where 8 most significant
   * bits hold the error code and the other bits hold
   * the argument to the error.
   */
  constexpr operator uint32_t() const {
    uint32_t full = 0;
    memcpy(&full, this, 4);
    return full;
  }

  /**
   * Cast operator from ec::error to uint8_t.
   * This returns only the error code.
   * The argument will be lost.
   */
  constexpr operator uint8_t() const {
    return this->code;
  }

  /**
   * Cast operator for bool
   */
  constexpr operator bool() const {
    return this->code != 0 || this->argument != 0;
  }

  /**
   * Assignment operator for ec::error
   */
  constexpr const error operator =(const error &other) const {
    return error(other);
  }

  /**
   * Comparison operator for ec::error
   */
  constexpr bool operator ==(const error &other) const {
    return this->code == other.code && this->argument == other.argument;
  }

  /**
   * Negative comparison operator for ec::error
   */
  constexpr bool operator !=(const error &other) const {
    return !(*this == other);
  }
};

} // namespace ec
