import ply.lex as lex

states = (
    ('textblock', 'exclusive'),
    ('text', 'exclusive'),
    ('attributes', 'exclusive'),
    ('attributescontent', 'exclusive'),
    ('conditional', 'exclusive'),
    ('attribution', 'exclusive'),
    ('interpolation', 'exclusive'),
    ('vardefinition', 'exclusive'),
    ('eachiteration', 'exclusive'),
    ('whileiteration', 'exclusive'),
    ('list', 'exclusive')
)

tokens = (
    'EACH',
    'IN',
    'WHILE',
    'UNLESS',
    'IF',
    'ELSE',
    'INDENT',
    'DEDENT',
    'TAG',
    'ATTRIBUTENAME',
    'ATTRIBUTESPACE',
    'ATTRIBUTE',
    'TEXT',
    'ID',
    'CLASS',
    'VAR',
    'ITEM',
    'VARDEF',
    'JSEXPRESSION',
    'INTERPOLATION',
    'COMMENT',
    'LBRACKET',
    'RBRACKET',
    'LSQBRACKET',
    'RSQBRACKET',
    'DOT',
    'COMMA',
    'ASSIGN',
    'QUOTE'
)


def t_textblock_newline(t):
    r'\n[ ]*'
    n = len(t.value[1:])  # tirar o \n

    if n > t.lexer.indents[-1] and t.lexer.tb_indent:
        t.type = 'INDENT'
        t.value = t.value[1:]
        t.lexer.indents.append(n)
        t.lexer.tb_indent = False

        return t
    elif n < t.lexer.indents[-1]:  # Só muda o estada para initial se for DEDENT
        t.type = 'DEDENT'
        t.lexer.indents.pop()
        t.lexer.skip(-n-1)
        t.lexer.tb_indent = True

        t.lexer.begin('INITIAL')
        return t
    else:
        pass



def t_ANY_newline(t):
    r'\n[ ]*'
    n = len(t.value[1:])
    t.lexer.begin('INITIAL')

    if n > t.lexer.indents[-1]:
        t.type = 'INDENT'
        t.value = t.value[1:]
        t.lexer.indents.append(n)

        return t
    elif n < t.lexer.indents[-1]:
        t.type = 'DEDENT'
        t.lexer.indents.pop()
        t.lexer.skip(-n-1)

        return t
    else:
        pass



def t_pug_comment(t):
    r"\/\/-[^\n]+"
    pass


def t_COMMENT(t):
    r"\/\/[^\n]+"
    t.value = t.value[2:]
    return t


def t_WHILE(t):
    r"while\b"
    t.lexer.begin('whileiteration')
    return t


def t_whileiteration_JSEXPRESSION(t):
    r"[^\n]+"
    return t


def t_EACH(t):
    r"each\b|for\b"
    t.lexer.begin('eachiteration')
    return t


def t_eachiteration_IN(t):
    r"in"
    return t


def t_eachiteration_LSQBRACKET(t):
    r"\["
    t.lexer.begin('list')
    return t


def t_eachiteration_VAR(t):
    r"\w+"
    return t


def t_list_RSQBRACKET(t):
    r"\]"
    t.lexer.begin('eachiteration')
    return t


def t_list_COMMA(t):
    r","
    return t


def t_list_ITEM(t):
    r"[^\,\]]+"
    return t


def t_textblock_TEXT(t):
    r'.*?\#{|.+'
    if t.value[-2:] == "#{":
        t.value = t.value[:-2]
        t.lexer.push_state('interpolation')
    else:
        t.value += '\n'
    
    if t.value != "":
        return t


def t_text_TEXT(t):
    r'.*?\#{|.+'
    if t.value[-2:] == "#{":
        t.value = t.value[:-2]
        t.lexer.push_state('interpolation')
    
    if t.value != "":
        return t


def t_interpolation_INTERPOLATION(t):
    r'.*?\}'
    t.value = t.value[:-1]
    t.lexer.pop_state()
    return t


def t_UNLESS(t):
    r"unless"
    t.lexer.begin('conditional')
    return t


def t_IF(t):
    r"if"
    t.lexer.begin('conditional')
    return t


def t_ELSE(t):
    r"else"
    return t


def t_VARDEF(t):
    r"\-[ ]*var\b"
    t.lexer.begin('vardefinition')
    return t


def t_vardefinition_ASSIGN(t):
    r"\="
    return t


def t_vardefinition_VAR(t):
    r"\w+[ ]*(?=\=)"
    t.value = t.value.strip()
    return t


def t_vardefinition_JSEXPRESSION(t):
    r"[^\n]+"
    return t


def t_enter_textblock(t):
    r'\.[ ]*(?=\n)'
    t.lexer.begin('textblock')
    t.type = 'DOT'
    t.value = t.value[0]
    return t


def t_enter_text(t):
    r'\ '
    t.lexer.begin('text')
    pass


def t_div(t):
    r'(?<=\s)[\#\.]|^[\.\#]'
    t.type = 'TAG'
    t.value = 'div'
    return t


def t_CLASS(t):
    r'(\.[\w\-]+)|((?<=\.)[\w\-]+)'
    if t.value[0] == '.':
        t.value = t.value[1:]
    return t


def t_ID(t):
    r'(\#[\w\-]+)|((?<=\#)[\w\-]+)'
    if t.value[0] == '#':
        t.value = t.value[1:]
    return t


def t_DOT(t):
    r"\."
    return t


def t_LBRACKET(t):
    r'\('
    t.lexer.begin('attributes')
    return t


def t_TAG(t):
    r'(?<=\s)\w+|^\w+'
    return t


def t_attributes_ASSIGN(t):
    r"\="
    return t


def t_ASSIGN(t):
    r"\="
    t.lexer.begin('attribution')
    return t


def t_attribution_JSEXPRESSION(t):
    r"[^\n]+"
    return t


def t_conditional_JSEXPRESSION(t):
    r'[^\n]+'
    return t


def t_attributes_RBRACKET(t):
    r'\)'
    t.lexer.begin('INITIAL')
    return t


def t_attributes_ID(t):
    r"id[ ]*=[ ]*[\"\'][^\"\']*[\"\']"
    t.value = t.value.replace(" ", "")
    t.value = t.value[4:len(t.value)-1]
    return t


def t_attributes_ATTRIBUTESPACE(t):
    r"[\ ]+"
    return t


def t_attributes_ATTRIBUTENAME(t):
    r'[\w/\-]+'
    return t


def t_attributes_QUOTE(t):
    r'[\'\"]'
    t.lexer.begin('attributescontent')
    return t


def t_attributescontent_QUOTE(t):
    r'[\'\"]'
    t.lexer.begin('attributes')
    return t


def t_attributescontent_ATTRIBUTE(t):
    r'[^\'\"]+'
    return t


def t_ANY_error(t):
    print(f"Caracter ilegal : '{t.value[0]}'")
    t.lexer.skip(1)


t_vardefinition_eachiteration_attribution_conditional_ignore = "\t "

lexer = lex.lex()
lexer.indents = [0]
lexer.tb_indent = True

