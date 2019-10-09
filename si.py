from sympy.parsing.sympy_parser import (parse_expr, standard_transformations, implicit_multiplication_application)
from sympy import *
from sympy.abc import x,y



with open("in.txt") as f1:
    s12=f1.readlines()[0:2] 
f1.close()
s1=s12[0]
s2=s12[1]

transformations = standard_transformations + (implicit_multiplication_application,)
#print(expand(parse_expr(s1, transformations=transformations))-expand(parse_expr(s2, transformations=transformations)))
s=expand(parse_expr(s1, transformations=transformations))-expand(parse_expr(s2, transformations=transformations))
q=sympify(s)

f = open('simpli.txt', 'w')
f.write(str(q)+'\n')
f.write(str(q.coeff(x**2))+'\n')#x^2
f.write(str(q.coeff(y**2) )+'\n')#y^2
f.write(str((q.coeff(x)).coeff(y))+'\n')#x*y
f.write(str((q.coeff(x)).as_leading_term(y))+'\n')#x
f.write(str((q.coeff(y)).as_leading_term(x))+'\n')#y
f.write(str(q.as_leading_term(x,y))+'\n')#какаято цифра
f.close()
