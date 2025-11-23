grammar MyLanguage;

options { language=Cpp; }

prog			: top_level*;

top_level		: func_decl | var_decl_stmt;
func_decl		: FUNC IDENT LBRA stmts RBRA;

stmt			: if_stmt | while_stmt | var_decl_stmt | assign_stmt | print_stmt | call_stmt | LBRA stmts RBRA;
stmts			: stmt*;

if_stmt			: IF LPAR expr RPAR stmt (ELSE stmt)?;
while_stmt		: WHILE LPAR expr RPAR stmt;
call_stmt		: CALL IDENT SEMICOLON;

var_decl_stmt	: VAR IDENT ASSIGN expr SEMICOLON;
assign_stmt		: IDENT ASSIGN expr SEMICOLON;
print_stmt		: PRINT LPAR expr RPAR SEMICOLON;

expr			: summa LESS summa | summa LESSEQUAL summa | summa GREATER summa | summa GREATEREQUAL summa | summa EQUAL summa | summa NOTEQUAL summa | summa;
summa			: summa PLUS term | summa MINUS term | term;
term			: term MULT factor | term DIV factor | term REM factor | factor;
factor			: NUMBER | IDENT | LPAR expr RPAR;

FUNC			: 'func';
CALL			: 'call';
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
REM				: '%';
LESS			: '<';
LESSEQUAL		: '<=';
GREATER			: '>';
GREATEREQUAL	: '>=';
EQUAL			: '==';
NOTEQUAL		: '!=';
ASSIGN			: '=';
SEMICOLON		: ';';

IDENT	: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER	: [0-9]+;
WS		: [ \t\r\n] -> skip;