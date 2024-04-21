#include "polygon.hpp"
#include <iterator>
#include <vector>
#include <delimiterI.hpp>

std::istream& kravchenko::operator>>(std::istream& in, Point& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  using cDel = DelimiterI< false >;
  Point temp{ 0, 0 };
  in >> cDel{ '(' } >> temp.x >> cDel{ ';' } >> temp.y >> cDel{ ')' };
  if (in)
  {
    p = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Point& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << '(' << p.x << ';' << p.y << ')';
  return out;
}

std::istream& kravchenko::operator>>(std::istream& in, Polygon& p)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  std::size_t nVertex = 0;
  in >> nVertex;

  std::vector< Point > temp;
  temp.reserve(nVertex);

  // don't know how to replace it w/o cycle
  for (std::size_t i = 0; in && i < nVertex; ++i)
  {
    Point p{ 0, 0 };
    if (in >> p)
    {
      temp.push_back(p);
    }
  }

  if (in)
  {
    p.points = temp;
  }
  return in;
}

std::ostream& kravchenko::operator<<(std::ostream& out, const Polygon& p)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  using outputIt = std::ostream_iterator< Point >;
  out << p.points.size() << ' ';
  std::copy(p.points.cbegin(), p.points.cend(), outputIt{ out, " " });
  return out;
}