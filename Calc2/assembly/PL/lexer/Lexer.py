import sys

class Lexer:
    NUM, ID, PRINT, IF, ELSE, WHILE, LBRA, RBRA, LPAR, RPAR, PLUS, MINUS, MULT, DIV, LESS, \
    EQUAL, SEMICOLON, EOF = range(18)

    # специальные символы языка
    SYMBOLS = {'{': LBRA, '}': RBRA, '=': EQUAL, ';': SEMICOLON, '(': LPAR,
               ')': RPAR, '+': PLUS, '-': MINUS, '*': MULT, '/': DIV, '<': LESS}

    # ключевые слова
    WORDS = {'print': PRINT, 'if': IF, 'else': ELSE, 'while': WHILE}

    def __init__(self, file):
        self.file = file
        self.ch = ' '
        self.str_num = 1
        self.ch_num = 1

    def error(self, msg):
        print(f'Lexer error at {(self.str_num, self.ch_num)}: {msg}')
        sys.exit(1)

    def getc(self):
        self.ch = self.file.read(1)
        
        self.ch_num += 1
        if self.ch == '\n':
            self.str_num += 1
            self.ch_num = 1
    
    def parse_number(self):
        intval = 0
        while self.ch.isdigit():
            intval = intval * 10 + int(self.ch)
            self.getc()
        return intval
    
    def parse_identifier(self):
        ident = ''
        while self.ch.isalnum() or self.ch == '_':
            ident += self.ch.lower()
            self.getc()
            
        return ident

    def next_tok(self):
        self.value = None
        self.sym = None
        self.pos = (self.str_num, self.ch_num)
        while self.sym == None:
            if len(self.ch) == 0:
                self.sym = Lexer.EOF
            elif self.ch.isspace():
                self.getc()
            elif self.ch in Lexer.SYMBOLS:
                self.sym = Lexer.SYMBOLS[self.ch]
                self.getc()
            elif self.ch.isdigit():
                self.value = self.parse_number()
                self.sym = Lexer.NUM
            elif self.ch.isalpha() or self.ch == '_':
                ident = self.parse_identifier()
                if ident in Lexer.WORDS:
                    self.sym = Lexer.WORDS[ident]
                else:
                    self.sym = Lexer.ID
                    self.value = ident
            else:
                self.error('Unexpected symbol: ' + self.ch)
        return [self.sym, self.value]