## Задание 4.

То же самое, что в задании 2, но с совмещенной бло-
кирующей отправкой и приемом сообщений

## Задание 6.

Задание 6. Написать программу, иллюстрирующую возможности
организации схемы «ведущий процесс – ведомые процессы (master-
slave)» стандартными средствами MPI. Процесс с номером 0 считать ве-
дущим, а остальные – ведомыми. В ведущем процессе использовать не-
блокирующий прием сообщений и функцию MPI_WAITSOME
(MPI::Request::Waitsome). В «ведомых» процессах использовать блоки-
рующую передачу сообщений

## Задание 8(2)

Задание 2. Написать программу, в которой происходит обмен ин-
формацией между процессами с соседними номерами в соответствии с
топологией кольца. Использовать неблокирующую буферизованную пе-
редачу сообщений, блокирующий прием сообщений и функции присо-
единения и отсоединения буфера для передачи сообщений.
