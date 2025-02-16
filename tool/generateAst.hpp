#pragma once

#include <initializer_list>
#include <string>

struct TypeInfo {
  std::string className;
  std::string fieldList;
};

void defineAst(std::string outputDir, std::string&& baseName,
               std::initializer_list<std::string> types);

void defineType(std::ofstream& file, std::string& baseName, TypeInfo&& typeInfo);
