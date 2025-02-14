#include "generateAst.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void defineAst(std::string outputDir, std::string &&baseName,
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
	for (const std::string &type : types) {
		// Remove spaces after the class name, e.g. "Unary   " -> "Unary"
		subClasses.push_back(type.substr(0, type.find(":"))
								 .substr(type.find_first_not_of(""),
										 type.find_last_not_of(" ") + 1));
	}

	// Includes
	headerFile << "#pragma once\n\n";
	headerFile << "#include \"Token.hpp\"\n";

	// Forward declarations
	// e.g. class Binary; class Grouping; class Literal; class Unary;
	for (const std::string &subclassName : subClasses) {
		headerFile << "class " << subclassName << ";" << '\n';
	}

	// ExprVisitor or StmtVisitor
	headerFile << "class " << baseName << "Visitor{" << '\n';
	headerFile << "public:" << '\n';

	for (const std::string &subclassName : subClasses) {
		// e.g. virtual void visitBinaryExpr(const Binary &expr) = 0;
		// e.g. virtual void visitPrintStmt(const Print &stmt) = 0;
		headerFile << "virtual std::string visit" << subclassName << baseName
				   << "(const " << subclassName << " &" << baseName << ") = 0;"
				   << "\n";
	}
	headerFile << "};\n\n";

	headerFile << "class " << baseName << "{"
			   << "\n";
	headerFile << "public:"
			   << "\n";
	headerFile << "virtual ~" << baseName << "() = default;"
			   << "\n";
	headerFile << "virtual std::string accept(" << baseName
			   << "Visitor &visitor) = 0;"
			   << "\n";
	headerFile << "};"
			   << "\n";

	for (const std::string &type : types) {
		std::string className = type.substr(0, type.find(":"));
		std::string fields = type.substr(type.find(":") + 1);
		defineType(headerFile, baseName, className, fields);
	}

	headerFile.close();
}

void defineType(std::ofstream &headerFile, std::string &baseName,
				std::string &className, std::string &fieldList) {
	// Extract the fields
	// Vector of <type, name>, e.g. {Expr, left}, {Token, op}, {Expr, right}
	std::vector<std::pair<std::string, std::string>> fields;
	std::istringstream iss(fieldList);
	std::string field;

	while (std::getline(iss, field, ','))  // Takes in params by reference
	{
		// Remove leading/trailing whitespaces
		field = field.substr(field.find_first_not_of(" "),
							 field.find_last_not_of(" ") + 1);
		fields.push_back(std::make_pair(field.substr(0, field.find(" ")),
										field.substr(field.find(" ") + 1)));
	}

	std::string constructorParams;
	std::string initializationParams;

	// Start class
	headerFile << "class " << className << " : public " << baseName << " {"
			   << "\n";
	headerFile << "public:"
			   << "\n";

	// Define the fields
	// E.g. Expr left; Token op; Expr right;
	for (const std::pair<std::string, std::string> &field : fields) {
		// NOTE: Structured bindings
		auto &[type, name] = field;
		headerFile << type << " " << name << ";"
				   << "\n";

		constructorParams += type + " " + name;
		// If raw ptr then don't do *ptr( *ptr ), just ptr(ptr)
		// Example: void *literal; -> literal(literal)
		if (name.find("*") != std::string::npos) {
			std::string temp = name.substr(1);
			initializationParams += temp + "(" + temp + ")";
		} else
			initializationParams += name + "(" + name + ")";

		// Add commas if not the last field
		if (field != fields.back()) {
			constructorParams += ", ";
			initializationParams += ", ";
		}
	}
	headerFile << "\n";

	// E.g Binary(Expr *left, Token op, Expr *right) : left(left), op(op),
	// right(right) {}
	headerFile << className << "(" << constructorParams
			   << ") : " << initializationParams << " {}"
			   << "\n";

	// void accept(Visitor &visitor) override {
	// visitor.visit[className][baseName](*this); }
	headerFile << "std::string accept( " << baseName
			   << "Visitor &visitor) override { return visitor.visit"
			   << className << baseName << "(*this); }"
			   << "\n";

	// End class
	headerFile << "};" << "\n";
}
