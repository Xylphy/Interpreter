#include "generateAst.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void defineAst(std::string outputDir, std::string &&baseName,
			   std::initializer_list<std::string> types) {
	// Header files that contain information (bag of data) about the AST nodes

	// File writer
	std::ofstream headerFile(outputDir + "/" + baseName + ".hpp");
	if (!headerFile) {
		std::cerr << "Could not open file for writing"
				  << "\n";
		return;
	}

	// Subclasses
	// E.g. Binary, Grouping, Literal, Unary
	std::vector<std::string> subclasses;
	for (const std::string &type : types) {
		std::string className = type.substr(0, type.find(":") - 1);
		// Remove spaces after the class name, e.g. "Unary   " -> "Unary"
		className = className.substr(className.find_first_not_of(" "),
									 className.find_last_not_of(" ") + 1);
		subclasses.push_back(className);
	}

	// Includes
	headerFile << "#ifndef " << baseName << "_HPP"
			   << "\n";
	headerFile << "#define " << baseName << "_HPP"
			   << "\n\n";
	headerFile << "#include \"Token.hpp\""
			   << "\n";
	headerFile << "#include \"Expr.hpp\""
			   << "\n";
	headerFile << "#include <memory>"
			   << "\n\n";

	// Forward declarations
	// e.g. class Binary; class Grouping; class Literal; class Unary;
	for (const std::string &subclassName : subclasses) {
		headerFile << "class " << subclassName << ";"
				   << "\n";
	}

	// ExprVisitor or StmtVisitor
	headerFile << "class " << baseName << "Visitor{"
			   << "\n";
	headerFile << "public:"
			   << "\n";
	for (const std::string &subclassName : subclasses) {
		// e.g. virtual void visitBinaryExpr(const Binary &expr) = 0;
		// e.g. virtual void visitPrintStmt(const Print &stmt) = 0;
		headerFile << "virtual void visit" << subclassName << baseName
				   << "(const " << subclassName << " &" << baseName << ") = 0;"
				   << "\n";
	}
	headerFile << " };"
			   << "\n";

	// Start of abstract class definition
	headerFile << "class " << baseName << "{"
			   << "\n";
	// Define the public section of the class
	headerFile << "public:"
			   << "\n";
	headerFile << "virtual ~" << baseName << "() = default;"
			   << "\n";
	headerFile << "virtual void accept(" << baseName << "Visitor &visitor) = 0;"
			   << "\n";
	// End of abstract class definition
	headerFile << "};"
			   << "\n";

	// Define the subclasses
	// For each type in the vector
	// Types = subclasses, fields = params of subclasses constructors
	// E.g. Binary : Expr left, Token op, Expr right
	for (const std::string &type : types) {
		std::string className = type.substr(0, type.find(":") - 1);
		std::string fields = type.substr(type.find(":") + 1);
		defineType(headerFile, baseName, className, fields);
	}

	// End of guard (end of file)
	headerFile << "#endif"
			   << "\n";

	// Close the file
	headerFile.close();
}

void defineType(std::ofstream &file, std::string &baseName,
				std::string &className, std::string &fields) {
	file << "class " << className << " : public " << baseName << " {\n";
	file << "public:\n";

	size_t start = 0;
	size_t end = fields.find(", ");

	std::vector<std::string> fieldNames;

	while (end != std::string::npos) {
		fieldNames.push_back(
			fields.substr(start, end - start).substr(fields.find(" ") + 1));
		start = end + 2;
		end = fields.find(", ", start);
	}

	file << "\t" << fields.substr(start) << ";\n";
	/* 	file << "\t" << className << "(" << fields << ") : " << fields << "
	   {}\n"; file << "\t" << fields << ";\n"; file << "};\n\n"; */
}