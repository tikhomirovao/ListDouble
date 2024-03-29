﻿#include <iostream>
#include <string>
#include <windows.h>
#include <stdlib.h>

using namespace std;

//Структура элемента(узла) списка
struct Element
{
    //Данные
    double Data;
    //Связь с другими узлами
    //указатель на следующий элемнт(узел) списка
    Element* Next = nullptr;
};

//Класс односвязный(однонаправленный) список
class List
{
    //Поле, хранящее адрес первого элемента(головного узла), указатель на "голову" списка
    Element* Head;
    //Поле, хранящее адрес последнего элемента(хвостового узла), указатель на "хвост" списка
    Element* Tail;
    //Текущее кол-во элементов(узлов) в списке
    int Count;

public:
    //Прототипы методов:
    //Конструктор по умолчанию
    List();
    //Деструктор
    ~List();
    //Метод добавления узла в конец списка
    void PushBack(double);
    //Метод добавления узла в указанное место списка
    //Добавляем элемент после указанного, по умолчанию в начало списка
    void Push(double, Element* = nullptr);
    //Метод удаления головного узла
    void DelHead();
    //Метод удаления указанного узла
    void Del(int);
    //Метод очитски всего списка
    void Clear();
    //Метод получения текущего кол-ва узлов в списке
    int GetCount()const;
    //Метод показа содержимого списка
    void Show()const;
    //Метод получения адреса указанного узла
    Element* GetElement(int)const;
};

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    List Weather;
    Weather.Show();
    Weather.PushBack(32.6);
    Weather.PushBack(30.4);
    Weather.PushBack(28.1);
    Weather.Show();
    cout << endl;
    Weather.Push(25.8, Weather.GetElement(2));
    Weather.Show();
    cout << endl;
    Weather.DelHead();
    Weather.Show();
    cout << endl;
    Weather.Del(2);
    Weather.Show();
    cout << endl;
    Weather.Clear();
    Weather.Show();
    cout << endl;
    Weather.PushBack(32.6);
    Weather.PushBack(30.4);
    Weather.PushBack(28.1);
    Weather.Show();
    cout << endl;
    cout << Weather.GetCount() << endl;
    cout << endl;
    cout << Weather.GetElement(1);
    cout << endl;
}
//Конструктор по умолчанию
//List::List():Head{nullptr},Tail{nullptr},Count{0}{}
List::List()
{
    //При создании список пуст
    Head = Tail = nullptr; //голова и хвост никуда не указывают
    Count = 0;
}
//Деструктор
List::~List()
{
    //Вызывает метод удаления всех узлов из списка Clear()
    Clear();
}
//Метод добавления узла в конец списка
void List::PushBack(double data)
{
    //создаем новый элемент(выделяем память)
    Element* New = new Element{}; //проверка выделения памяти!
    //заполняем узел данными
    New->Data = data;
    //следующий элемент отстутсвует, так как узел добавляется в конец списка
    New->Next = nullptr;
    //если новый узел единственный в списке(то есть до него не было узлов),
    if (Head == nullptr)//if(!Head) //if(Tail==nullptr) //if(Count==0)
    {
        Head = Tail = New; //то на него будут указывать и голова и хвост списка
    }
    else //иначе узел не единственный
    {
        Tail->Next = New; //бывший последним узел, теперь указвает на новый узел,
        //как на следующий за собой
        Tail = New; //указатель на хвост списка теперь указывает на новый узел
    }
    Count++; //увеличиваем текущее кол-во узлов в списке
}
//Метод добавления узла в указанное место списка
//Добавляем элемент после указанного, по умолчанию в начало списка
void List::Push(double data, Element* Node)
{
    //создаем новый элемент(выделяем память)
    Element* New = new Element{}; //проверка выделения памяти!
    //заполняем узел данными
    New->Data = data;
    //Если добавляем узел в начало списка(новый головной элемент)
    if (Node == nullptr) //if(!Node)
    {
        //если новый узел единственный в списке(то есть до него не было узлов),
        if (Head == nullptr)//if(!Head) //if(Tail==nullptr) //if(Count==0)
        {
            New->Next = nullptr; //то после него нет узлов 
            Head = Tail = New; //и на него будут указывать и голова и хвост списка
        }
        else //иначе узел не единственный, то есть уже есть головной узел, помещаем новый узел пред головным
        {
            New->Next = Head; //новый узел будет указывать на бывший головным узел, как следующий за собой,
            Head = New; //а сам становится головным
        }
    }
    else //иначе добавляем узел после указанного узла
    {
        New->Next = Node->Next; //новый узел(New->Next) указывает на тот узел(Node->Next), на которой указывал узел(Node), после которого довляется новый(New)
        Node->Next = New; //узел(Node), после которого добавляется новый узел(New), указывает на новый узел(New), как на следующий за собой(Node->Next)
        if (Node == Tail)Tail = New; //если добавляем узел после последнего узла, то новый узел становиться хвостом
    }
    Count++; //увеличиваем текущее кол-во узлов в списке
}
//Метод удаления головного узла
void List::DelHead()
{
    //Если в списке есть узлы
    if (Head != nullptr) //if(Head)
    {
        //запоминаем адрес головного(удаляемого) узла
        Element* Del = Head;
        //if(Count==1)
        if (Head == Tail) //если удаляемый узел единственный,
        {
            Head = Tail = nullptr; //то список стане пустым
        }
        else //иначе в списке есть другие узлы, кроме удаляемого
        {
            Head = Head->Next; //передаем "голову" следующему за удаляемым(головным) узлу
        }
        Count--; //уменьшаем кол-во узлов в списке
        delete Del; //освобождаем память, выделенную под удаляемый узел
    }
    else cout << "Список пуст!" << endl;
}
//Метод удаления указанного узла
void List::Del(int number) //number порядковый номер узла в списке
{
    //прверка порядкового номера узла в списке
    if (number > 0 && number <= Count)
    {
        //если хотя удалить головной узел
        if (number == 1)
        {
            DelHead(); //вызываем метод удаления головного узла
        }
        else //иначе удаляем не голову
        {
            //Определяем адрес узла, перед удаляемым
            Element* PrevDel = GetElement(number - 1);
            //сохраняем адрес удаляемого узла, полученный из поля Next узла перед удаляемым
            Element* Del = PrevDel->Next;
            PrevDel->Next = Del->Next; //теперь узел перед удаляемым указывает на узел после удляемого
            if (Tail == Del) //если удаляется хвост, то укзатель Tail будет указывать на узел перед удаляемым
                Tail = PrevDel;
            Count--; //уменьшаем кол-во узлов в списке
            delete Del; //освобождаем память, выделенную под удаляемый узел
        }
    }
    else cout << "Элемента с таким номером нет в списке!" << endl;
}
//Метод очитски всего списка
void List::Clear()
{
    //пока в списке есть узлы
    do
    {
        DelHead(); //удаляем по одному элементу из начала списка
        //Del(Count); //удаляем по одному элементы из хвоста списка
    } while (Head != nullptr); //while(Head); //while(Count!=0); while(Tail!=nullptr);
}
//Метод получения текущего кол-ва узлов в списке
int List::GetCount() const
{
    return Count;
}
//Метод показа содержимого списка
void List::Show() const
{
    //Создаем указатель на элемент списка для перемещения по списку и 
    //помещаем в него адрес головного элемента
    Element* temp = Head;
    //пока не дошли до конца списка
    while (temp != nullptr)
    {
        //выводим данные узла на экран
        cout << temp->Data << endl;
        //переходим к следующему узлу
        temp = temp->Next;
    }
}
//Метод получения адреса указанного узла
Element* List::GetElement(int number) const
{
    //прверка порядкового номера узла в списке
    if (number > 0 && number <= Count)
    {
        //если указан номер первого узла, вернем адрес головного элемента, 
        if (number == 1) return Head; //который хранит указатель Head
        //если указан номер последнего узла, вернем адрес хвостового элемента, 
        if (number == Count) return Tail; //который хранит указатель Tail
        //Создаем указатель на элемент списка для перемещения по списку и 
        //помещаем в него адрес головного элемента
        Element* temp = Head;
        for (int i = 1; i < number - 1; i++) //чтобы узнать адрес 3-го узла нужно дойти до 2-го
        {
            temp = temp->Next;  //переходим к следующему узлу
        }
        return temp->Next; //возвращаем адрес из поля Next узла перед искомым(из 2-го, если ищем 3-й)
    }
    else
    {
        cout << "Элемента с таким номером нет в списке!" << endl;
        return nullptr; //можно использовать исключения
    }
}