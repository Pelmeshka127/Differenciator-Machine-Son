# Differenciator Machine, Son

## Описание проекта

Дифференциатор - программа, предназначенная для математических вычислений: нахождение значения функции в точке, поиск производной функции и разложение функции в ряд Маклорена.

Проект основан на бинарном дереве, которое считывается с текста при момощи рекурсивного спуска. Для просмотра дерева функции испольуется графическая библиотека [graphviz](https://graphviz.org). При взятии производных и поиске значения функции в точке используется функция упрощения бинарного дерева,
```C
/// @brief Function makes three easier
/// @param cur_node is ptr on the current node of tree
/// @param simplified_flag is flag of simplify
/// @return No_Error; makes simplified_flag = 1, if there's simplifiers, 0, if it's simplified
int Diff_Simplifier(tree_node * const cur_node, int *simplified_flag);
``` 
основанная на простейших математических преобразованиях, таких как умножеие на 1, умножение на 0, прибавление 0 и арифметические операции над числами.

![image](https://github.com/Pelmeshka127/Differenciator-Machine-Son/raw/main/graphics/graph1.png)

При заупске программы пользователю дается на выбор несколько вариантов работы с математической функцией, считываемой из файла
```
    Enter 1 to check the tree.
    Enter 2 to get value of the function at the point.
    Enter 3 to get the derivative of your function.
    Enter 4 to get value of the derivative at the point.
    Enter 5 to get the the tree of derivative.
    Enter 6 to get the Maclaurin formula of function.
    Enter 10 to live the programm.
```
Результатом работы программы является файл в формате pdf, текст которого генерируется при помощи языка Latex. Пример: [My_Exapmle](https://github.com/Pelmeshka127/Differenciator-Machine-Son/blob/main/main.pdf)

## Запуск проекта

Мой дифференциатор был написан на операционной системе macOS. Чтобы запустить проект надо установить graphviz и Latex.
Для установки потребутеся homebrew.

В терминале:
```
brew install graphviz 

brew install latex
```

Далее для запуска:
```
git clone git@github.com:Pelmeshka127/Differenciator-Machine-Son.git

make

./diff trees/6.txt
```
