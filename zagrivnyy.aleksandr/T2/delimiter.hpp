#ifndef DELIMITER_HPP
#define DELIMITER_HPP
#include <iostream>

namespace zagrivnyy
{
  struct DelimiterI
  {
    DelimiterI(const char *expected);

    const char *expected;

    size_t length() const
    {
      return size;
    };

  private:
    size_t size;
  };

  std::istream &operator>>(std::istream &in, DelimiterI &&exp);
}     // namespace zagrivnyy

#endif
