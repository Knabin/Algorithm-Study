#include <iostream>

using namespace std;

template<typename T>
struct Node
{
	T data;				// ������
	Node<T>* prevNode;	// ���� ��带 ����Ű�� ������
	Node<T>* nextNode;	// ���� ��带 ����Ű�� ������

	Node<T>(T value) : data(value), prevNode(NULL), nextNode(NULL) {}
};

template<typename T>
class DoublyLinkedList
{
	Node<T>* head;
	Node<T>* tail;
	int size = 0;

public:
	DoublyLinkedList() : head(NULL), tail(NULL) {}
	~DoublyLinkedList()
	{
		Node<T>* deleteNode;
		while (head->nextNode != NULL)
		{
			deleteNode = head;
			head = head->nextNode;
			delete deleteNode;
		}
	}

	void addNode(T data)
	{
		Node<T>* newNode = new Node<T>(data);
		++size;

		// head�� NULL�̶�� ���� Linked List�� ��� �ִ� ����
		if (head == NULL)
		{
			head = tail = newNode;
			return;
		}

		tail->nextNode = newNode;
		newNode->prevNode = tail;
		tail = newNode;
	}

	void showList() const
	{
		Node<T>* findNode = head;

		cout << "size of DLL: " << size << endl;

		while (findNode != NULL)
		{
			cout << findNode->data << " ";
			findNode = findNode->nextNode;
		}
		cout << endl;
	}

	Node<T>* findNode(int location) const
	{
		Node<T>* searchNode = head;
		int index = location;

		while (searchNode != NULL && --index >= 0)
		{
			searchNode = searchNode->nextNode;
		}

		return searchNode;
	}

	T findNodeData(int location) const
	{
		Node<T>* searchNode = head;
		int index = location;

		while (searchNode != NULL && --index >= 0)
		{
			searchNode = searchNode->nextNode;
		}

		return searchNode->data;
	}

	void removeNode(T data)
	{
		// ������ Node�� ����Ű�� ������
		Node<T>* deleteNode = head;

		while (deleteNode != NULL)
		{
			if (deleteNode->data == data)
				break;
			deleteNode = deleteNode->nextNode;
		}

		// nullptr�̸� �ش� �����͸� ã�� ����
		if (deleteNode != NULL)
		{
			if (deleteNode->prevNode != NULL)
				deleteNode->prevNode->nextNode = deleteNode->nextNode;
			if (deleteNode->nextNode != NULL)
				deleteNode->nextNode->prevNode = deleteNode->prevNode;
			--size;

			delete deleteNode;
		}
	}

	void insertNode(T data, int index)
	{
		// index�� DLL ������� ũ�ų� ������ ��� ���� ó��
		if (index > size || index < 0)
		{
			cout << "invalid index : " << index << endl;
			return;
		}

		Node<T>* newNode = new Node<T>(data);

		// head�� �߰�
		if (index == 0)
		{
			// ���� ��� �ִٸ�
			if (head == NULL)
				tail = newNode;

			head->prevNode = newNode;
			newNode->nextNode = head;
			head = newNode;
		}
		// tail�� �߰�
		else if (index == size)
		{
			// ���� ��� �ִٸ�
			if (head == NULL)
				head = tail = newNode;
			else
			{
				newNode->prevNode = tail;
				tail->nextNode = newNode;
				tail = newNode;
			}
		}
		else
		{
			Node<T>* findNode = head;

			for (int i = 1; i < index; ++i)
			{
				findNode = findNode->nextNode;
			}

			newNode->nextNode = findNode->nextNode;
			newNode->prevNode = findNode;
			findNode->nextNode = newNode;
		}

		++size;
	}
};

int main(void)
{
	DoublyLinkedList<int> DLL;

	DLL.addNode(1);
	DLL.addNode(2);
	DLL.addNode(3);
	DLL.showList();

	DLL.removeNode(0);
	DLL.showList();

	DLL.removeNode(2);
	DLL.showList();

	DLL.insertNode(10, 1);
	DLL.insertNode(11, 1);
	DLL.insertNode(11, 10);
	DLL.insertNode(11, 4);
	DLL.showList();

	cout << DLL.findNode(0)->data << endl;
	cout << DLL.findNodeData(1) << endl;

	return 0;
}