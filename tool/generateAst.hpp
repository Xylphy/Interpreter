#pragma once

#include <initializer_list>
#include <string>

void defineAst(std::string                        outputDir,
               std::string&&                      baseName,
               std::initializer_list<std::string> types);

void defineType(std::ofstream& file,
                std::string&   baseName,
                std::string&   className,
                std::string&   fields);
