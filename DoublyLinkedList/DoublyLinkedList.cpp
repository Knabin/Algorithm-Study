#include <iostream>

using namespace std;

template<typename T>
struct Node
{
	T data;				// 데이터
	Node<T>* prevNode;	// 이전 노드를 가리키는 포인터
	Node<T>* nextNode;	// 다음 노드를 가리키는 포인터

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

		// head가 NULL이라면 현재 Linked List는 비어 있는 상태
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
		// 삭제될 Node를 가리키는 포인터
		Node<T>* deleteNode = head;

		while (deleteNode != NULL)
		{
			if (deleteNode->data == data)
				break;
			deleteNode = deleteNode->nextNode;
		}

		// nullptr이면 해당 데이터를 찾지 못함
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
		// index가 DLL 사이즈보다 크거나 음수인 경우 예외 처리
		if (index > size || index < 0)
		{
			cout << "invalid index : " << index << endl;
			return;
		}

		Node<T>* newNode = new Node<T>(data);

		// head에 추가
		if (index == 0)
		{
			// 만약 비어 있다면
			if (head == NULL)
				tail = newNode;

			head->prevNode = newNode;
			newNode->nextNode = head;
			head = newNode;
		}
		// tail에 추가
		else if (index == size)
		{
			// 만약 비어 있다면
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