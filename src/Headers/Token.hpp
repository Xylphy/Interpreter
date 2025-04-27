#pragma once

#include <any>
#include <ostream>

enum TokenType : std::uint8_t {
  // Single-character tokens
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACE,
  RIGHT_BRACE,
  COMMA,
  DOT,
  MINUS,
  PLUS,
  SLASH,
  STAR,
  SEMICOLON,
  MODULO,
  NEW_LINE,
  CONCATENATOR,
  ESCAPE_CHARACTER,
  COLON,

  // One or two character tokens
  BANG,
  BANG_EQUAL,
  EQUAL,
  EQUAL_EQUAL,
  GREATER,
  GREATER_EQUAL,
  LESS,
  LESS_EQUAL,
  INCREMENT,

  // Literals
  IDENTIFIER,
  STRING_LITERAL,
  NUMBER,
  DECIMAL_NUMBER,
  BOOL_TRUE,
  BOOL_FALSE,
  CHARACTER_LITERAL,
  UNITIALIZED,

  // Keywords
  AND,
  CLASS,
  ELSE,
  FALSE,
  FUN,
  FOR,
  NIL,
  OR,
  PRINT,
  RETURN,
  SUPER,
  THIS,
  TRUE,
  VAR,
  WHILE,
  INPUT,
  START,
  END,
  INTEGER,
  DECIMAL,
  BOOL,
  CHAR,
  IF,
  STRING,
  BLOCK,

  END_OF_FILE
};

class Token {
 public:
  TokenType type;
  std::string lexeme;
  std::any literal;
  size_t line;

  Token(TokenType type, std::string lexeme, std::any literal, int line);
  Token(const Token & other);

  [[nodiscard]] auto toString() const -> std::string;

  friend auto operator<<(std::ostream& ostream, const Token& token)
      -> std::ostream&;
};

auto operator<<(std::ostream& ostream, const Token& token) -> std::ostream&;

template <>
struct std::formatter<TokenType> {
  static constexpr auto parse(std::format_parse_context& ctx)
      -> std::format_parse_context::iterator {
    return ctx.begin();
  }

  static auto format(const TokenType& obj, format_context& ctx)
      -> std::format_context::iterator {
    return std::format_to(ctx.out(), "{}", static_cast<int>(obj));
  }
};

template <>
struct std::formatter<Token> {
  static constexpr auto parse(std::format_parse_context& ctx)
      -> std::format_parse_context::iterator {
    return ctx.begin();
  }

  static auto format(const Token& obj, format_context& ctx)
      -> std::format_context::iterator {
    return std::format_to(ctx.out(), "{} {}", obj.type, obj.lexeme);
  }
};
