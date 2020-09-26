#include <iostream>

using namespace std;

template<typename T>
struct Node
{
	T data;				// ������
	Node<T>* nextNode;	// ���� ��带 ����Ű�� ������

	Node<T>(T value) : data(value), nextNode(NULL) {}
};

template<typename T>
class LinkedList
{
	Node<T>* head;
	Node<T>* tail;
	int size = 0;

public:
	LinkedList() : head(NULL), tail(NULL) {}
	~LinkedList()
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
		tail = newNode;
	}

	void showList() const
	{
		Node<T>* findNode = head;

		cout << "size of SLL: " << size << endl;

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

		while(searchNode != NULL && --index >= 0)
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
		// Ž���� ������, ������ Node�� ���� Node�� ������
		Node<T>* findNode = head;
		// ������ Node�� �ӽ÷� ������ ������
		Node<T>* deleteNode;

		while (findNode != NULL)
		{
			if (findNode->nextNode != NULL && findNode->nextNode->data == data)
				break;
			findNode = findNode->nextNode;
		}

		// nullptr�̸� �ش� �����͸� ã�� ����
		if (findNode != NULL)
		{
			deleteNode = findNode->nextNode;
			findNode->nextNode = deleteNode->nextNode;
			--size;
			
			delete deleteNode;
		}
	}

	void insertNode(T data, int index)
	{
		// index�� SLL ������� ũ�ų� ������ ��� ���� ó��
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
				tail->nextNode = newNode;
				tail = newNode;
			}
		}
		else
		{
			Node<T>* findNode = head;
			Node<T>* nextNode = findNode->nextNode;


			for (int i = 1; i < index; ++i)
			{
				findNode = nextNode;
				nextNode = findNode->nextNode;
			}

			newNode->nextNode = nextNode;
			findNode->nextNode = newNode;
		}

		++size;
	}
};

int main(void)
{
	LinkedList<int> SLL;

	SLL.addNode(1);
	SLL.addNode(2);
	SLL.addNode(3);
	SLL.showList();

	SLL.removeNode(0);
	SLL.showList();

	SLL.removeNode(2);
	SLL.showList();

	SLL.insertNode(10, 1);
	SLL.insertNode(11, 1);
	SLL.insertNode(11, 10);
	SLL.insertNode(11, 4);
	SLL.showList();

	cout << SLL.findNode(0)->data << endl;
	cout << SLL.findNodeData(1) << endl;

	return 0;
}