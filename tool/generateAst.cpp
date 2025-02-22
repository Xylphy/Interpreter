#include "generateAst.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void defineAst(std::string&& outputDir, std::string&& baseName,
               std::initializer_list<std::string> types) {
  // Header files that contain information (bag of data) about the AST nodes

  // File writer
  std::ofstream headerFile("../src/" + outputDir + "/" + baseName + ".hpp");
  if (!headerFile.is_open()) {
    std::cerr << "Could not open file for writing: "
              << outputDir + "/" + baseName + ".hpp" << '\n';
    exit(1);
  }

  // Subclasses
  // E.g. Binary, Grouping, Literal, Unary
  std::vector<std::string> subClasses;
  for (const std::string& type : types) {
    // Remove spaces after the class name, e.g. "Unary   " -> "Unary"
    subClasses.push_back(type.substr(0, type.find(':'))
                             .substr(type.find_first_not_of(' '),
                                     type.find_last_not_of(' ') + 1));
  }

  // Includes
  headerFile << "#pragma once\n\n";
  headerFile << "#include <vector>\n";

  if (baseName == "Expr") {
    headerFile << "#include \"Token.hpp\"\n";
  } else if (baseName == "Stmt") {
    headerFile << "#include \"Expr.hpp\"\n";
  }
  headerFile << '\n';

  // Forward declarations
  // e.g. class Binary; class Grouping; class Literal; class Unary;
  for (const std::string& subclassName : subClasses) {
    headerFile << "class " << subclassName << ";" << '\n';
  }

  // ExprVisitor or StmtVisitor
  headerFile << "class " << baseName << "Visitor{" << '\n';
  headerFile << "public:" << '\n';

  for (const std::string& subclassName : subClasses) {
    // e.g. virtual void visitBinaryExpr(const Binary &expr) = 0;
    // e.g. virtual void visitPrintStmt(const Print &stmt) = 0;
    headerFile << "virtual auto visit" << subclassName << baseName << "(const "
               << subclassName << " &" << baseName << ") -> void = 0;"
               << "\n";
  }
  headerFile << "virtual ~" << baseName << "Visitor() = default;"
             << "\n";

  headerFile << "};\n\n";

  headerFile << "class " << baseName << "{"
             << "\n";
  headerFile << "public:"
             << "\n";
  headerFile << "virtual ~" << baseName << "() = default;"
             << "\n";
  headerFile << "virtual auto accept(" << baseName
             << "Visitor &visitor) -> void = 0;"
             << "\n";
  headerFile << "};"
             << "\n";

  for (const std::string& type : types) {
    std::string className = type.substr(0, type.find(':'));
    std::string fields = type.substr(type.find(':') + 1);
    defineType(headerFile, baseName,
               {.className = className, .fieldList = fields});
  }

  headerFile.close();
}

void defineType(std::ofstream& file, const std::string& baseName,
                const TypeInfo&& typeInfo) {
  // Extract the fields
  // Vector of <type, name>, e.g. {Expr, left}, {Token, op}, {Expr, right}
  std::vector<std::pair<std::string, std::string>> fields;
  std::istringstream iss(typeInfo.fieldList);
  std::string field;

  while (std::getline(iss, field, ','))  // Takes in params by reference
  {
    // Remove leading/trailing whitespaces
    field = field.substr(field.find_first_not_of(' '),
                         field.find_last_not_of(' ') + 1);
    fields.emplace_back(field.substr(0, field.find(' ')),
                        field.substr(field.find(' ') + 1));
  }

  std::string constructorParams;
  std::string initializationParams;

  // Start class
  file << "class " << typeInfo.className << " : public " << baseName << " {"
       << "\n";
  file << "public:"
       << "\n";

  // Define the fields
  // E.g. Expr left; Token op; Expr right;
  for (std::pair<std::string, std::string>& field : fields) {
    // NOTE: Structured bindings
    auto& [type, name] = field;
    file << type << " " << name << ";"
         << "\n";

    constructorParams.append(type).append(" ").append(name);
    // If raw ptr then don't do *ptr( *ptr ), just ptr(ptr)
    // Example: void *literal; -> literal(literal)
    if (name.find('*') != std::string::npos) {
      name = name.substr(1);
    }
    initializationParams.append(name).append("(").append(name).append(")");

    // Add commas if not the last field
    if (field != fields.back()) {
      constructorParams.append(", ");
      initializationParams.append(", ");
    }
  }
  file << "\n";

  // E.g Binary(Expr *left, Token op, Expr *right) : left(left), op(op),
  // right(right) {}
  file << typeInfo.className << "(" << constructorParams
       << ") : " << initializationParams << " {}"
       << "\n";

  // void accept(Visitor &visitor) override {
  // visitor.visit[className][baseName](*this); }
  file << "auto accept( " << baseName
       << "Visitor &visitor) -> void override { visitor.visit"
       << typeInfo.className << baseName << "(*this); }"
       << "\n";

  // End class
  file << "};" << "\n";
}
