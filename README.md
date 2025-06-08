# ��������� ����������� � ���������� �������� �� ����� ��

:one: **Guess the Number (������ �����)** :ballot_box_with_check:

:two: **To-Do-List (������ ���)** :ballot_box_with_check:

:three: **Unit Converter (��������������� ������ ���������)** :ballot_box_with_check:

:four: **TCP echoClientServer (��� ������ ������)** :ballot_box_with_check:

## TCP Echo Client Server
**��������� ����� �� ���������������� ������������ ����� ����� ������������� � server.c**
```
opt = 1;
setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
```
���������� **opt** ����� ��� ��������� �������� ����� **SO_REUSEADDR**. ������� **setsockopt** ������� ��������� �� ��������.

������ ����� ����� ������������� **��** ������ bind(), ����� ��� �� ����� ����� �������.

**������������� ���� �������**
```
while(1){
    int valread = read(client_socket, buffer, 1024);
    printf("Messager from client: %s\n", buffer);

    send(client_socket, buffer, strlen(buffer), 0);
    printf("Message was sended\n"); 
}
```
� ���� **server.c** ������������ ��� ������, ����� ���: sockfd � client_socket.

sockfd �������� **"���������"** �������, ��� ������������ ������ - **��������� ����� ����������** ����� accept()

accept() ���������� ���������� ����� ����� **client_socket**, �������:
1. ������ � ���������� ��������.
2. �������� ���������� ������������� ����������.
3. ������������ ��� ���� �������� �����-������ � ���� ��������.

