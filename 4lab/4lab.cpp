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

    // ������������ � ����������
    QueueBasedOnBidirectionalCyclicLinkedList();
    QueueBasedOnBidirectionalCyclicLinkedList(const QueueBasedOnBidirectionalCyclicLinkedList& _object);
    QueueBasedOnBidirectionalCyclicLinkedList(QueueBasedOnBidirectionalCyclicLinkedList&& _object);
    QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<int> _ilist);
    ~QueueBasedOnBidirectionalCyclicLinkedList();

    // ��������� ������������
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(const QueueBasedOnBidirectionalCyclicLinkedList& _object);
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(QueueBasedOnBidirectionalCyclicLinkedList&& _object);
    QueueBasedOnBidirectionalCyclicLinkedList& operator=(std::initializer_list<int> _ilist);

    // ������������� ������� ������ � �����
    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const QueueBasedOnBidirectionalCyclicLinkedList<T>& _object);

    // ������ ��� ������ � ��������
    int GetSize();
    void InsertAt(int _value, int _index);
    int RemoveAt(int _index);
    bool Push(const T& element);
    bool Pop(T& element);
    bool Peek(T& element);
};
// ���������� ������������ �� ���������
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList()
{
    head = tail = NULL;
}
// ���������� ������������ �����������
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
// ���������� ������������ �����������
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
// ���������� ������������ � �������������� ������ �������������
template <typename T>
QueueBasedOnBidirectionalCyclicLinkedList<T>::QueueBasedOnBidirectionalCyclicLinkedList(std::initializer_list<int> _ilist)
{
    for (const auto& element : _ilist)
        this->Push(element);
}

// ���������� �����������
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
// ���������� ��������� ������������ ��� �����������
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
// ���������� ��������� ������������ ��� �����������
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
// ���������� ��������� ������������ � �������������� ������ �������������
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

// ���������� ������ ��������� ������� �������
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
// ���������� ������ ������� �������� �� ���������� �������
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
// ���������� ������ �������� �������� �� ���������� �������
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
// ���������� ������ ���������� �������� � ����� �������
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

// ���������� ������ �������� �������� �� ������ �������
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

// ���������� ������ ��������� �������� � ������ �������
template <typename T>
bool QueueBasedOnBidirectionalCyclicLinkedList<T>::Peek(T& element)
{
    if (head == NULL) return false;
    element = head->number;
    return true;
}


// ���������� ������������� ������� ������ � �����
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

    QueueBasedOnBidirectionalCyclicLinkedList<int> default_queue;  // �������� ������� � �������������� ������������ �� ���������
    QueueBasedOnBidirectionalCyclicLinkedList<int> initialization_queue = { 1, 2, 3, 4, 5 };  // �������� ������� � �������������� �� ������
    QueueBasedOnBidirectionalCyclicLinkedList<int> copy_queue{ initialization_queue };  // �������� ������� � �������������� ������������ �����������
    QueueBasedOnBidirectionalCyclicLinkedList<int> temp_queue{ copy_queue };  // �������� ��������� ������� � �������������� ������������ �����������
    QueueBasedOnBidirectionalCyclicLinkedList<int> move_queue{ std::move(temp_queue) };  // �������� ������� � �������������� ������������ �����������

    std::cout << "������ default_queue (����������� �� ���������): " << default_queue.GetSize() << std::endl;
    std::cout << "������ initialization_queue (������������� �������): " << initialization_queue.GetSize() << std::endl;
    std::cout << "������ copy_queue (���������� �����������): " << copy_queue.GetSize() << std::endl;
    std::cout << "������ move_queue (����������� �����������): " << move_queue.GetSize() << std::endl << std::endl;

    default_queue = initialization_queue;  // ������������ �������� � �������������� ��������� ������������

    std::cout << default_queue;

    std::cout << "�������� �� ������ �������������: " << initialization_queue << std::endl;

    default_queue = { 1,2,3,4 };  // ������������ ����� �������� � �������������� ��������� ������������
    copy_queue = { 2,3,4 };  // ������������ ����� �������� � �������������� ��������� ������������

    std::cout << "����������� ����� �������� default_queue: ";
    std::cout << default_queue;
    std::cout << "����������� ����� �������� copy_queue: ";
    std::cout << copy_queue << std::endl;

    std::cout << "Push >> Peek >> Pop:" << std::endl;
    std::cout << "��� �������� default_queue �� Push: ";
    std::cout << default_queue;
    default_queue.Push(15);
    std::cout << "��� �������� default_queue ����� Push: ";
    std::cout << default_queue;
    std::cout << "����������� ������� default_queue: ";
    default_queue.Peek(peekElement);
    std::cout << peekElement << std::endl;
    default_queue.Pop(popElement);
    std::cout << "����������� ������� default_queue: ";
    std::cout << popElement << std::endl;
    std::cout << "��� �������� default_queue ����� Pop: ";
    std::cout << default_queue << std::endl;

    std::cout << "InsertAt >> RemoveAt:" << std::endl;
    std::cout << "��� �������� default_queue �� InsertAt(1): ";
    std::cout << default_queue;
    std::cout << "��� �������� default_queue ����� InsertAt(500, 1): ";
    default_queue.InsertAt(500, 1);
    std::cout << default_queue;
    std::cout << "��� �������� default_queue ����� RemoveAt(2): ";
    default_queue.RemoveAt(3);
    std::cout << default_queue;

    return 0;
}