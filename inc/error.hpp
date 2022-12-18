#pragma once

#include <cstdint>
#include <cstring>

namespace ec {

class error {
public:
  uint32_t argument : 24;
  uint8_t code;

  /**
   * Default constructor.
   * This initializes all the parameters to 0.
   */
  constexpr error() : argument(0), code(0) {}

  /**
   * Constructor for initializing an error from full error code
   * which also includes the argument to the error
   */
  constexpr error(uint32_t full) : argument(full), code(full >> 24) {}

  /**
   * Constructor for initializing an error with an error code
   * and an argument.
   */
  constexpr error(uint8_t code, uint32_t argument) : argument(argument), code(code) {}

  /**
   * Constructor for initializing an error with an error code
   * and another error as an argument.
   *
   * Note that 8 LSBs of the argument error will be lost.
   */
  constexpr error(uint8_t code, const error &other) : argument((static_cast<uint32_t>(other.code) << 16) | (other.argument >> 8)), code(code) {}

  /**
   * Copy constructor
   */
  constexpr error(const error &other) : argument(other.argument), code(other.code) {}

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
    return this->code || this->argument;
  }

  /**
   * Assignment operator for ec::error
   */
  error& operator =(const error &other) = default;

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
