from pug_yacc import parser
import bs4

print("---------------------------------------")
print("|     CONVERSOR DE PUG PARA HTML      |")
print("---------------------------------------")

try:
    file = open(input("Introduza a diretoria do ficheiro Pug:\n"), "r")
    data = file.read()

    if data[-1] != '\n':
        data += '\n'

    tree = parser.parse(data)

    html = tree.pug_to_html()

    formatter = bs4.formatter.HTMLFormatter(indent=4)
    formatted_html = bs4.BeautifulSoup(html, "html.parser").prettify(formatter=formatter)

    output = open("output.html", "w")
    output.write(formatted_html)

    print("\noutput.html gerado com sucesso!")

except FileNotFoundError:
    print("\nFicheiro não encontrado!")

