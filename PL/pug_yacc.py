import ply.yacc as yacc
from pug_lex import tokens
from tree import *


def p_pug(p):
    """pug : expression_list"""
    p[0] = TagNode(blocks=p[1])


def p_expression_list(p):
    """expression_list : expression
                       | expression_list expression
    """
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = p[1] + [p[2]]


def p_expression_tag(p):
    """expression : TAG
                  | TAG INDENT expression_list DEDENT
    """
    if len(p) == 2:
        p[0] = TagNode(tag=p[1])
    else:
        p[0] = TagNode(tag=p[1], blocks=p[3])


def p_expression_text(p):
    """expression : TAG text
                  | TAG text INDENT expression_list DEDENT
    """
    if len(p) == 3:
        p[0] = TagNode(tag=p[1], text=p[2])
    else:
        p[0] = TagNode(tag=p[1], text=p[2], blocks=p[4])


def p_expression_attributes(p):
    """expression : TAG attributes
                  | TAG attributes INDENT expression_list DEDENT
    """
    if len(p) == 3:
        p[0] = TagNode(tag=p[1], attributes=p[2])
    else:
        p[0] = TagNode(tag=p[1], attributes=p[2], blocks=p[4])


def p_expression_attributes_text(p):
    """expression : TAG attributes text
                  | TAG attributes text INDENT expression_list DEDENT
    """
    if len(p) == 4:
        p[0] = TagNode(tag=p[1], attributes=p[2], text=p[3])
    else:
        p[0] = TagNode(tag=p[1], attributes=p[2],
                       text=p[3], blocks=p[5])


def p_expression_dot(p):
    """expression : TAG DOT INDENT text DEDENT
                  | TAG attributes DOT INDENT text DEDENT
    """
    if len(p) == 6:
        p[0] = TagNode(tag=p[1], text=p[4])
    else:
        p[0] = TagNode(tag=p[1], attributes=p[2], text=p[5])


def p_expression_assign_expression(p):
    """expression : TAG ASSIGN JSEXPRESSION
                  | TAG ASSIGN JSEXPRESSION INDENT expression_list DEDENT
    """

    if len(p) == 4:
        p[0] = TagNode(tag=p[1], expression=p[3])
    else:
        p[0] = TagNode(tag=p[1], expression=p[3], blocks=p[5])


def p_expression_attributes_assign_expression(p):
    """expression : TAG attributes ASSIGN JSEXPRESSION
                  | TAG attributes ASSIGN JSEXPRESSION INDENT expression_list DEDENT
    """

    if len(p) == 5:
        p[0] = TagNode(tag=p[1], attributes=p[2], expression=p[4])
    else:
        p[0] = TagNode(tag=p[1], attributes=p[2],
                       expression=p[4], blocks=p[6])


def p_expression_if_condition(p):
    """expression : IF JSEXPRESSION INDENT expression_list DEDENT
                  | IF JSEXPRESSION INDENT expression_list DEDENT ELSE INDENT expression_list DEDENT
    """
    if len(p) == 6:
        p[0] = IfNode(p[2], p[4], None)
    elif len(p) == 10:
        p[0] = IfNode(p[2], p[4], p[8])


def p_expression_unless_condition(p):
    """expression : UNLESS JSEXPRESSION INDENT expression_list DEDENT"""
    if len(p) == 6:
        p[0] = UnlessNode(p[2], p[4])


def p_expression_vardef(p):
    """expression : VARDEF VAR ASSIGN JSEXPRESSION"""
    p[0] = VarNode(p[2], p[4])


def p_expression_iteration(p):
    """expression : EACH VAR IN list INDENT expression_list DEDENT
                  | WHILE JSEXPRESSION INDENT expression_list DEDENT"""
    if len(p) == 6:
        p[0] = WhileNode(p[2], p[4])
    else:
        p[0] = EachNode(p[2], p[6], p[4])


def p_expression_comment(p):
    """expression : COMMENT"""
    p[0] = CommentNode(p[1])


def p_text_interp(p):
    """text : INTERPOLATION text
            | INTERPOLATION"""
    if len(p) == 2:
        p[0] = [('i', p[1])]
    else:
        p[0] = [('i', p[1])] + p[2]


def p_text_text(p):
    """text : TEXT text
            | TEXT"""
    if len(p) == 2:
        p[0] = [('t', p[1])]
    else:
        p[0] = [('t', p[1])] + p[2]


def p_attributes(p):
    """attributes : attribute_list
                  | attribute_list ID
                  | attribute_list ID attribute_list
    """
    if len(p) == 2:
        p[0] = p[1]
    elif len(p) == 3:
        p[1].update({"id": p[2]})
        p[0] = p[1]
    else:
        p[1].update({"id": p[2]})
        if "class" not in p[1] or "class" not in p[3]:
            p[1].update(p[3])
        else:
            p[1]["class"] += p[3]["class"]

        p[0] = p[1]


def p_attributes_id(p):
    """attributes : ID
                  | ID attribute_list
    """
    if len(p) == 2:
        p[0] = {"id": p[1]}
    elif len(p) == 3:
        p[2].update({"id": p[1]})
        p[0] = p[2]


def p_attribute_list(p):
    """attribute_list : CLASS
                      | LBRACKET RBRACKET
                      | LBRACKET attributecont RBRACKET
    """
    if len(p) == 2:
        p[0] = {"class": [p[1]]}
    elif len(p) == 3:
        p[0] = {}
    else:
        p[0] = p[2]


def p_attribute_list_list(p):
    """attribute_list : attribute_list CLASS
                      | attribute_list LBRACKET RBRACKET
                      | attribute_list LBRACKET attributecont RBRACKET
    """
    if len(p) == 3:
        if "class" not in p[1]:
            p[1]["class"] = []
        p[1]["class"].append(p[2])
        p[0] = p[1]
    elif len(p) == 4:
        p[0] = p[1]
    else:
        if "class" not in p[1] or "class" not in p[3]:
            p[1].update(p[3])
        else:
            p[1]["class"] += p[3]["class"]

        p[0] = p[1]


def p_attributecont(p):
    """attributecont : ATTRIBUTENAME ASSIGN QUOTE ATTRIBUTE QUOTE
                     | attributecont ATTRIBUTESPACE ATTRIBUTENAME ASSIGN QUOTE ATTRIBUTE QUOTE
    """
    if len(p) == 6:
        if p[1] == "class":
            p[4] = [p[4]]

        p[0] = {p[1]: p[4]}
    else:
        if p[3] == "class" and "class" in p[1]:
            p[1]["class"] += [p[6]]
        elif p[3] == "class":
            p[1].update({p[3]: [p[6]]})
        else:
            p[1].update({p[3]: p[6]})

        p[0] = p[1]


def p_list(p):
    """ list : LSQBRACKET RSQBRACKET
             | LSQBRACKET listcontent RSQBRACKET
    """
    if len(p) == 3:
        p[0] = []
    else:
        p[0] = p[2]


def p_listcontent(p):
    """listcontent : ITEM
               | ITEM COMMA listcontent
    """
    if len(p) == 2:
        p[0] = [p[1]]
    else:
        p[0] = [p[1]] + p[3]


def p_error(p):
    # print("Erro sintÃ¡tico!")
    # parser.restart()
    if p is not None:
        print(
            f"Erro sintático no input!{p.type}({p.value}) on line {p.lineno}")
    else:
        print('Unexpected end of input')


parser = yacc.yacc(debug=True)