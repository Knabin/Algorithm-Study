#include <iostream>

using namespace std;

template<typename T>
struct Node
{
	T data;				// 데이터
	Node<T>* nextNode;	// 다음 노드를 가리키는 포인터

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

		// head가 NULL이라면 현재 Linked List는 비어 있는 상태
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
		// 탐색용 포인터, 삭제할 Node의 이전 Node를 저장함
		Node<T>* findNode = head;
		// 삭제될 Node를 임시로 저장할 포인터
		Node<T>* deleteNode;

		while (findNode != NULL)
		{
			if (findNode->nextNode != NULL && findNode->nextNode->data == data)
				break;
			findNode = findNode->nextNode;
		}

		// nullptr이면 해당 데이터를 찾지 못함
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
		// index가 SLL 사이즈보다 크거나 음수인 경우 예외 처리
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