import js2py
import copy


class TagNode:
    def __init__(self, tag=None, attributes=[], text=None, expression=None, blocks=[]):
        self.tag = tag
        self.attributes = attributes
        self.text = text
        self.expression = expression
        self.blocks = blocks

    def pug_to_html(self, string="", context=js2py.EvalJs()):
        if self.tag is not None:

            attributes = ""
            for attribute in self.attributes:
                if attribute == "id":
                    attributes += ' id="' + self.attributes[attribute] + '"'

                elif attribute == "class":
                    attributes += ' class="'
                    for classifier in self.attributes["class"]:
                        attributes += classifier + ' '
                    attributes = ' ' + attributes.strip() + '"'

                else:
                    attributes += ' ' + attribute + '="' + \
                        self.attributes[attribute] + '"'

            string += '<' + self.tag + attributes + '>'

            if self.text is not None:
                for elem in self.text:
                    if elem[0] == 't':
                        string += elem[1]
                    elif elem[0] == 'i':
                        try:
                            string += str(context.eval(elem[1]))
                        except:
                            string += ""

            elif self.expression is not None:
                try:
                    string += str(context.eval(self.expression))
                except:
                    string += ""

            if len(self.blocks) > 0:
                for block in self.blocks:
                    string = block.pug_to_html(string, context)

            string += '</' + self.tag + '>'

        elif self.blocks is not None:
            if len(self.blocks) > 0:
                for block in self.blocks:
                    string = block.pug_to_html(string, context)

        return string



class CommentNode:
    def __init__(self, comment):
        self.comment = comment

    def pug_to_html(self, string="", context=js2py.EvalJs()):
        string += "<!--" + self.comment + "-->"

        return string


class VarNode:
    def __init__(self, name, value):
        self.name = name
        self.value = value

    def pug_to_html(self, string="", context=js2py.EvalJs()):
        try:
            context.execute(f"var {self.name} = {self.value}")
        except: 
            context.execute(f"var {self.name} = '{self.value}'")

        return string


class IfNode:
    def __init__(self, condition=None, true_block=None, false_block=None):
        self.condition = condition
        self.true_block = true_block
        self.false_block = false_block


    def pug_to_html(self, string="", context=js2py.EvalJs()):
        try:
            condition = context.eval(self.condition)
        except:
            condition = False

        if condition:
            for elem in self.true_block:
                string = elem.pug_to_html(string, context)

        elif self.false_block is not None:
            for elem in self.false_block:
                string = elem.pug_to_html(string, context)

        return string


class UnlessNode:
    def __init__(self, condition=None, block=None):
        self.condition = condition
        self.block = block


    def pug_to_html(self, string="", context=js2py.EvalJs()):
        try:
            condition = context.eval(self.condition)
        except:
            condition = False

        if not condition:
            for elem in self.block:
                string = elem.pug_to_html(string, context)

        return string


class EachNode:
    def __init__(self, var=None, blocks=[], struct=None):
        self.var = var
        self.blocks = blocks
        self.struct = struct

    def pug_to_html(self, string="", context=js2py.EvalJs()):
        for var in self.struct:
            #context_copy = copy.deepcopy(context)
            try:
                context.execute(f"var {self.var} = {var}")
            except:  # Por causa das strings
                context.execute(f"var {self.var} = '{var}'")

            for elem in self.blocks:
                string = elem.pug_to_html(string, context)

        return string


class WhileNode:
    def __init__(self, expression=None, blocks=[]):
        self.expression = expression
        self.blocks = blocks


    def pug_to_html(self, string="", context=js2py.EvalJs()):
        try:
            condition = context.eval(self.expression)
        except:
            condition = False

        while condition:
            for elem in self.blocks:
                string = elem.pug_to_html(string, context)

            try:
                condition = context.eval(self.expression)
            except:
                condition = False

        return string
