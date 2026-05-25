#include <iostream>
#include <iomanip>
#include <sstream>

#include "commands.h"
#include "methods.h"

std::vector<std::string> parseComand(const std::string& line)
{
  std::istringstream iss(line);
  std::vector<std::string> words;
  std::string word;

  while (iss >> word)
  {
    words.push_back(word);
  }

  return words;
}

void processCommands(std::vector<Polygon>& polygons)
{
  std::string line;
  while (std::getline(std::cin, line))
  {
    if (line.empty())
    {
      continue;
    }

    std::vector<std::string> words = parseComand(line);
    if (words.empty())
    {
      continue;
    }

    const std::string& cmd = words[0];

    try
    {
      if (cmd == "COUNT")
      {
        if (words.size() != 2)
        {
          throw std::runtime_error("");
        }
        const std::string& arg = words[1];
        if (arg == "EVEN")
        {
          std::cout << countEven(polygons) << "\n";
        }
        else if (arg == "ODD")
        {
          std::cout << countOdd(polygons) << "\n";
        }
        else
        {
          int vertexCount = std::stoi(arg);
          if (vertexCount < 3)
          {
            throw std::runtime_error("");
          }
          std::cout << countByVertexCount(polygons, vertexCount) << "\n";
        }
      }
      else if (cmd == "AREA")
      {
        if (words.size() != 2)
        {
          throw std::runtime_error("");
        }
        const std::string arg = words[1];
        std::cout << std::fixed << std::setprecision(1);
        if (arg == "EVEN")
        {
          std::cout << sumAreaEven(polygons) << "\n";
        }
        else if (arg == "ODD")
        {
          std::cout << sumAreaOdd(polygons) << "\n";
        }
        else if (arg == "MEAN")
        {
          std::cout << meanArea(polygons) << "\n";
        }
        else
        {
          int vertexCount = std::stoi(arg);
          if (vertexCount < 3)
          {
            throw std::runtime_error("");
          }
          std::cout << sumAreaByVertexCount(polygons, vertexCount) << "\n";
        }
      }
      else if (cmd == "MAX")
      {
        if (words.size() != 2)
        {
          throw std::runtime_error("");
        }
        const std::string& arg = words[1];
        if (arg == "AREA")
        {
          std::cout << std::fixed << std::setprecision(1) << maxArea(polygons) << "\n";
        }
        else if (arg == "VERTEXES")
        {
          std::cout << maxVertexCount(polygons) << "\n";
        }
        else
        {
          std::cout << "<INVALID COMMAND>" << "\n";
        }
      }
      else if (cmd == "MIN")
      {
        if (words.size() != 2)
        {
          throw std::runtime_error("");
        }
        const std::string& arg = words[1];
        if (arg == "AREA")
        {
          std::cout << std::fixed << std::setprecision(1) << minArea(polygons) << "\n";
        }
        else if (arg == "VERTEXES")
        {
          std::cout << minVertexCount(polygons) << "\n";
        }
        else
        {
          std::cout << "<INVALID COMMAND>" << "\n";
        }
      }
      else if (cmd == "MAXSEQ") {
        if (words.size() < 2)
        {
          throw std::runtime_error("");
        }

        std::string polygonStr;
        for (size_t i = 1; i < words.size(); ++i)
        {
          if (i != 1)
          {
            polygonStr += " ";
          }
          polygonStr += words[i];
        }
        Polygon target = parsePolygon(polygonStr);
        std::cout << maxConsecutiveEqual(polygons, target) << "\n";
      }
      else if (cmd == "ECHO")
      {
        if (words.size() < 2)
        {
          throw std::runtime_error("");
        }

        std::string polygonStr;
        for (size_t i = 1; i < words.size(); ++i)
        {
          if (i != 1)
          {
            polygonStr += " ";
          }
          polygonStr += words[i];
        }
        Polygon target = parsePolygon(polygonStr);
        int result = duplicateEcho(polygons, target);
        std::cout << result << "\n";
      }
      else
      {
        std::cout << "<INVALID COMMAND>" << "\n";
      }
    }
    catch (const std::exception&)
    {
      std::cout << "<INVALID COMMAND>" << "\n";
    }
  }
}
