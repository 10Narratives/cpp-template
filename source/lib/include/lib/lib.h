#pragma once

namespace lib {
/// Represent calculator with add and remove options
class Calculator final {
 public:
  /**
   * @brief Adds x to y
   *
   * @param[in] x value x
   * @param[in] y value y
   * @return Adding result
   */
  [[nodiscard]] static int add(int x, int y) noexcept;

  /**
   * @brief Removes y from x
   *
   * @param x value x
   * @param y value y
   * @return Removing result
   */
  [[nodiscard]] static int remove(int x, int y) noexcept;
};
}  // namespace lib