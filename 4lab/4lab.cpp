#include <iostream>
#include <initializer_list>

template <typename T>
struct Element
{
    T number;
    Element* next;
    Element* prev;
};

template <typename T> class QueueBasedOnBidirectionalCyclicLinkedList
{
private:
    Element<T>* head;
    Element<T>* tail;

public:

    // Конструкторы и деструктор
    QueueBasedOnBidirectionalCyclicLinkedList();
    QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList& _object);
    QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& _object);
    QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<int> _ilist);
    ~QueueBasedOnBidirectionalCyclicLinkedList();

    // Операторы присваивания
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(const QueueBasedOnBidirectionalCyclicLinkedList& _object);
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(QueueBasedOnBidirectionalCyclicLinkedList&& _object);
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(std::initializer_list<int> _ilist);

    // Дружественная функция вывода в поток
    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const QueueBasedOnBidirectionalCyclicLinkedList<T>& _object);

    // Методы для работы с очередью
    int GetSize();
    void InsertAt(int _value, int _index);
    int RemoveAt(int _index);
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);
};
// Реализация конструктора по умолчанию
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList()
{
    head = tail = NULL;
}
// Реализация конструктора копирования
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList& _object)
{
    if (_object.head == NULL)
    {
        head = tail = NULL;
        return;
    }
    Element<T>* temp = _object.head;
    while (temp != _object.tail)
    {
        this->Push(temp->number);
        temp = temp->prev;
    }
    this->Push(temp->number);
}
// Реализация конструктора перемещения
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& _object)
{
    if (_object.head == NULL)
    {
        head = tail = NULL;
        return;
    }
    head = _object.head;
    tail = _object.tail;
    _object.head = _object.tail = NULL;
}
// Реализация конструктора с использованием списка инициализации
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<int> _ilist)
{
    for (const auto& element : _ilist)
        this->Push(element);
}

// Реализация деструктора
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::~QueueBasedOnBidirectionalCyclicLinkedList()
{
    if (head == NULL) return;
    int temp;
    while (this->GetSize() > 0)
    {
        this->Pop(temp);
    }
    head = tail = NULL;
}
// Реализация оператора присваивания для копирования
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(const QueueBasedOnBidirectionalCyclicLinkedList& _object)
{
    if (this == &_object || _object.head == NULL)
        return *this;
    int pop;
    for (int size = this->GetSize(); size > 0; size--)
        this->Pop(pop);
    Element<T>* temp = _object.head;
    while (temp != _object.tail)
    {
        this->Push(temp->number);
        temp = temp->prev;
    }
    this->Push(temp->number);
    return *this;
}
// Реализация оператора присваивания для перемещения
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(QueueBasedOnBidirectionalCyclicLinkedList&& _object)
{
    if (this == &_object || _object.head == NULL)
        return *this;
    head = _object.head;
    tail = _object.tail;
    _object.head = _object.tail = NULL;
    return *this;
}
// Реализация оператора присваивания с использованием списка инициализации
template<typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>& QueueBasedOnBidirectionalCyclicLinkedList<T>::operator=(std::initializer_list<int> _ilist)
{
    int temp;
    for (int size = this->GetSize(); size > 0; size--)
        this->Pop(temp);
    for (const auto& element : _ilist)
        this->Push(element);
    return *this;
}

// Реализация метода получения размера очереди
template<typename T>
int QueueBasedOnBidirectionalCyclicLinkedList<T>::GetSize()
{
    int i = 0;
    Element<T>* temp = tail;
    if (head == NULL) return 0;
    while (temp != head)
    {
        i++;
        temp = temp->next;
    }
    return i + 1;
}
// Реализация метода вставки элемента по указанному индексу
template<typename T>
void QueueBasedOnBidirectionalCyclicLinkedList<T>::InsertAt(int _value, int _index)
{
    int size = this->GetSize() + 1;
    QueueBasedOnBidirectionalCyclicLinkedList<int>* temp_obj{ std::move(this) };
    int tmp;
    if (_index <= size)
        for (int i = 0; i < size; i++)
        {
            if (_index == i)
            {
                this->Push(_value);
                continue;
            }
            temp_obj->Pop(tmp);
            this->Push(tmp);
        }
}
// Реализация метода удаления элемента по указанному индексу
template<typename T>
int QueueBasedOnBidirectionalCyclicLinkedList<T>::RemoveAt(int _index)
{
    int size = this->GetSize();
    QueueBasedOnBidirectionalCyclicLinkedList<int>* temp_obj{ std::move(this) };
    int removedElement = 0;
    int tmp;
    if (_index <= size)
        for (int i = 0; i < size; i++)
        {
            if (_index == i)
            {
                temp_obj->Pop(removedElement);
                continue;
            }
            temp_obj->Pop(tmp);
            this->Push(tmp);
        }
    return removedElement;
}
// Реализация метода добавления элемента в конец очереди
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Push(const T& element)
{
    Element<T>* temp = new Element<int>;
    temp->number = element;

    if (head != NULL)
    {
        temp->next = tail;
        temp->prev = head;

        tail->prev = temp;
        head->next = temp;
        tail = temp;
    }
    else temp->next = temp->prev = head = tail = temp;
    return true;
}

// Реализация метода удаления элемента из начала очереди
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Pop(T& element)
{
    if (head == tail)
    {
        if (head == NULL) return false;
        element = head->number;
        delete head;
        head = tail = NULL;
        return true;
    }
    element = head->number;
    head = head->prev;
    delete head->next;
    head->next = tail;
    tail->prev = head;
    return true;
}

// Реализация метода просмотра элемента в начале очереди
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Peek(T& element)
{
    if (head == NULL) return false;
    element = head->number;
    return true;
}


// Реализация дружественной функции вывода в поток
template<typename T>
std::ostream& operator<<(std::ostream& stream, const QueueBasedOnBidirectionalCyclicLinkedList<T>& _object)
{
    if (_object.head == NULL) return stream << "Queue is empty!";
    Element<T>* temp = _object.head;
    while (temp != _object.tail)
    {
        stream << temp->number << " ";
        temp = temp->prev;
    }
    return stream << temp->number << std::endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int peekElement = 0;
    int popElement = 0;

    QueueBasedOnBidirectionalCyclicLinkedList<int> default_queue;  // Создание очереди с использованием конструктора по умолчанию
    QueueBasedOnBidirectionalCyclicLinkedList<int> initialization_queue = { 1, 2, 3, 4, 5 };  // Создание очереди с инициализацией из списка
    QueueBasedOnBidirectionalCyclicLinkedList<int> copy_queue{ initialization_queue };  // Создание очереди с использованием конструктора копирования
    QueueBasedOnBidirectionalCyclicLinkedList<int> temp_queue{ copy_queue };  // Создание временной очереди с использованием конструктора копирования
    QueueBasedOnBidirectionalCyclicLinkedList<int> move_queue{ std::move(temp_queue) };  // Создание очереди с использованием конструктора перемещения

    std::cout << "Размер default_queue (конструктор по умолчанию): " << default_queue.GetSize() << std::endl;
    std::cout << "Размер initialization_queue (инициализация списком): " << initialization_queue.GetSize() << std::endl;
    std::cout << "Размер copy_queue (копирующий конструктор): " << copy_queue.GetSize() << std::endl;
    std::cout << "Размер move_queue (конструктор перемещения): " << move_queue.GetSize() << std::endl << std::endl;

    default_queue = initialization_queue;  // Присваивание значений с использованием оператора присваивания

    std::cout << default_queue;

    std::cout << "Элементы из списка инициализации: " << initialization_queue << std::endl;

    default_queue = { 1,2,3,4 };  // Присваивание новых значений с использованием оператора присваивания
    copy_queue = { 2,3,4 };  // Присваивание новых значений с использованием оператора присваивания

    std::cout << "Заполненные новые элементы default_queue: ";
    std::cout << default_queue;
    std::cout << "Заполненные новые элементы copy_queue: ";
    std::cout << copy_queue << std::endl;

    std::cout << "Push >> Peek >> Pop:" << std::endl;
    std::cout << "Все элементы default_queue до Push: ";
    std::cout << default_queue;
    default_queue.Push(15);
    std::cout << "Все элементы default_queue после Push: ";
    std::cout << default_queue;
    std::cout << "Загруженный элемент default_queue: ";
    default_queue.Peek(peekElement);
    std::cout << peekElement << std::endl;
    default_queue.Pop(popElement);
    std::cout << "Извлеченный элемент default_queue: ";
    std::cout << popElement << std::endl;
    std::cout << "Все элементы default_queue после Pop: ";
    std::cout << default_queue << std::endl;

    std::cout << "InsertAt >> RemoveAt:" << std::endl;
    std::cout << "Все элементы default_queue до InsertAt(1): ";
    std::cout << default_queue;
    std::cout << "Все элементы default_queue после InsertAt(500, 1): ";
    default_queue.InsertAt(500, 1);
    std::cout << default_queue;
    std::cout << "Все элементы default_queue после RemoveAt(2): ";
    default_queue.RemoveAt(3);
    std::cout << default_queue;

    return 0;
}