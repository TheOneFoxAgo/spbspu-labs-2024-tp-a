#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
#include "commands.hpp"
#include "geometry.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    return -1;
  }
  std::ifstream inputFile{ argv[2] };
  std::vector< demidenko::Polygon > polygons;
  if (demidenko::readPolygons(inputFile, polygons).fail())
  {
    return -1;
  }
  std::string cmd;
  using namespace std::placeholders;
  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands{
    { "AREA", std::bind(demidenko::area, _1, _2, std::ref(polygons)) },
    { "MAX", std::bind(demidenko::max, _1, _2, std::ref(polygons)) },
    { "MIN", std::bind(demidenko::min, _1, _2, std::ref(polygons)) },
    { "COUNT", std::bind(demidenko::count, _1, _2, std::ref(polygons)) },
    { "ECHO", std::bind(demidenko::echo, _1, _2, std::ref(polygons)) },
    { "RIGHTSHAPES", std::bind(demidenko::rightShapes, _1, _2, std::ref(polygons)) },
  };
  while (!std::cin.eof())
  {
    std::cin >> cmd;
    try
    {
      commands.at(cmd)(std::cin, std::cout);
    }
    catch (...)
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}