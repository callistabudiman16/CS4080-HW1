from parsimonious.grammar import Grammar
from parsimonious.nodes import NodeVisitor

GRAMMAR = r"""
Expr    = Sum
Sum     = Product (("+" / "-") Product)*
Product = Primary (("*" / "/") Primary)*
Primary = Number / "(" Expr ")"
Number  = ~"[0-9]+(\\.[0-9]+)?"
"""

class CalcVisitor(NodeVisitor):
    def visit_expr(self, node, visited_children):
        return visited_children[0]

    def visit_sum(self, node, visited_children):
        left = visited_children[0]
        rest = visited_children[1]
        val = left
        for op, right in rest:
            if op == '+':
                val += right
            else:
                val -= right
        return val

    def visit_product(self, node, visited_children):
        left = visited_children[0]
        rest = visited_children[1]
        val = left
        for op, right in rest:
            if op == '*':
                val *= right
            else:
                val /= right
        return val

    def visit_primary(self, node, visited_children):
        child = visited_children[0]
        if isinstance(child, float):
            return child
        return child[1]  # "(" Expr ")"

    def visit_number(self, node, visited_children):
        return float(node.text)

    def generic_visit(self, node, visited_children):
        return visited_children or node

if __name__ == "__main__":
    grammar = Grammar(GRAMMAR)
    visitor = CalcVisitor()

    while True:
        try:
            s = input("expr> ")
        except EOFError:
            break
        if not s.strip():
            continue
        tree = grammar.parse(s)
        result = visitor.visit(tree)
        print(result)