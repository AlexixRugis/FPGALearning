grammar MyLanguage;

options { language=Cpp; }

prog			: stmts;

stmt			: if_stmt | while_stmt | var_decl_stmt | assign_stmt | print_stmt | LBRA stmts RBRA;
stmts			: stmt*;

if_stmt			: IF LPAR expr RPAR stmt (ELSE stmt)?;
while_stmt		: WHILE LPAR expr RPAR stmt;

var_decl_stmt	: VAR IDENT ASSIGN expr SEMICOLON;
assign_stmt		: IDENT ASSIGN expr SEMICOLON;
print_stmt		: PRINT LPAR expr RPAR SEMICOLON;

expr			: summa LESS summa | summa;
summa			: summa PLUS term | summa MINUS term | term;
term			: term MULT factor | term DIV factor | factor;
factor			: NUMBER | IDENT | LPAR expr RPAR;

VAR				: 'var';
PRINT			: 'print';
IF				: 'if';
ELSE			: 'else';
WHILE			: 'while';
LBRA			: '{';
RBRA			: '}';
LPAR			: '(';
RPAR			: ')';
PLUS			: '+';
MINUS			: '-';
MULT			: '*';
DIV				: '/';
LESS			: '<';
ASSIGN			: '=';
SEMICOLON		: ';';

IDENT	: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER	: [0-9]+;
WS		: [ \t\r\n] -> skip;