# Небольшой репозиторий с несложными задачами на языке Си

:one: **Guess the Number (Угадай число)** :ballot_box_with_check:

:two: **To-Do-List (Список дел)** :ballot_box_with_check:

:three: **Unit Converter (Преобразователь единиц измерения)** :ballot_box_with_check:

:four: **TCP echoClientServer (Эхо Клинет Сервер)** :ballot_box_with_check:

## TCP Echo Client Server
**Установка опции на незамедлительное освобождение порта после использования в server.c**
```
opt = 1;
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
```
Переменная **opt** нужна для храненния значения опции **SO_REUSEADDR**. Функция **setsockopt** ожидает указатель на значение.

Данную опцию нужно устанавливать **ДО** вызова bind(), иначе она не будет иметь эффекта.

**Использование двух сокетов**
```
while(1){
    int valread = read(client_socket, buffer, 1024);
    printf("Messager from client: %s\n", buffer);

    send(client_socket, buffer, strlen(buffer), 0);
    printf("Message was sended\n"); 
}
```
В коде **server.c** используется два сокета, такие как: sockfd и client_socket.

sockfd является **"слушающим"** сокетом, его единственная задача - **принимать новые соединения** через accept()

accept() возвращает совершенно новый сокет **client_socket**, который:
1. Связан с конкретным клиентом.
2. Содержит уникальный идентификатор соединения.
3. Используется для всех операций ввода-вывода с этим клиентом.

