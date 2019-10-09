# 3 часть курсовой работы 
 Приложение для ввода, хранения и отображения кривых, которые
задаются уравнением не выше второй степени.
Имеет классический оконный интерфейс,
содержащим меню, древовидный список (например, слева) и область вывода (центральная часть окна) информации.
В древовидном списке отображается информация о кривых. Каждый листовой элемент представляет единичную кривую, 
при выборе которой отображается ее график, выводится уравнение и инварианты этой кривой в соответствующих областях вывода.
Каждый узловой элемент древовидного элемента управления объединяет некоторый набор кривых или представляет собой объединение 
наборов кривых. Древовидный элемент поддерживает стандартное ожидаемое поведение (добавление/удаление элемента с помощью 
контекстного меню и так далее). Области вывода предназначены для отображения формулы, отображения графика и инвариантов кривой. 
При этом раздел, где выводятся инварианты не является редактируемым. Разделы для вывода формулы и графика могут быть редактируемыми.

Примечание.
Будем считать, что кривые задаются уравнением, которое содержит знак равенства, переменные и константы. 
При вводе уравнение не обязано быть упрощенным и может содержать произвольные комбинации констант и мономов. 

Приведение уравнения к реализовано на Python.
