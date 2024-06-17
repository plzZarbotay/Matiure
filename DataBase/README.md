#### Цель

Цель данной задачи — определить, в какой группе студентки имеют максимальный средний балл по всем предметам на основании данных об успеваемости студентов.

#### Структура файла

Файл содержит информацию об успеваемости студентов, включая следующие поля:
- Фамилия студента (SURNAME)
- Инициалы (INITIALS)
- Группа (GROUP)
- Пол (GENDER)
- Баллы по математике (MATH)
- Баллы по физике (PHYS)
- Баллы по литературе (LIT)

#### Подход к решению задачи

Для выполнения задачи были разработаны две программы на языке C. Первая программа генерирует данные и сохраняет их в текстовый файл. Вторая программа считывает данные из файла, выполняет анализ и выводит результаты.

#### Программа генерации данных

Программа генерации данных создаёт файл, содержащий записи с информацией о студентах. Каждая запись включает информацию о фамилии, инициалах, группе, поле и баллах по предметам.

#### Программа анализа данных

Вторая программа считывает данные из файла, выполняет вычисление среднего балла для студенток каждой группы и определяет группу с максимальным средним баллом.

### Оценка сложности

Пространственная сложность:
- Программа генерации данных требует O(1) памяти для хранения каждой записи.
- Программа анализа данных требует O(n) памяти для хранения информации о группах, где n — количество различных групп.

Временная сложность:
- Программа генерации данных имеет временную сложность O(n), где n — количество записей.
- Программа анализа данных имеет временную сложность O(n * g), где n — количество записей, а g — количество различных групп.