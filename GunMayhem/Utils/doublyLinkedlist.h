#pragma once
#include "pch.h"

using std::string;

template<class T>
struct Node
{
	T data;
	Node* next;
	Node* prev;
	Node(T data);
	~Node();
};

template <class T>
Node<T> ::Node(T data) : data(data), next(nullptr), prev(nullptr) { }
template <class T>
Node<T> :: ~Node<T>() {};

template <class T>
class DoublyLinkedList
{
private:
	Node<T>* head;
	size_t length = 0;

public:
	DoublyLinkedList() : head(nullptr) {}
	DoublyLinkedList(std::initializer_list<T> list)
	{
		head = nullptr;
		for (auto const& i : list)
		{
			push_back(i);
		}
			
	}
	~DoublyLinkedList()
	{
		this->clear();
	}
 
	void push_front(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);
		if (!head) head = newNode;
		else
		{
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		++length;
	}
	void push_back(const T& data)
	{
		Node<T>* newNode = new Node<T>(data);

		if (head == nullptr) {
			newNode->prev = NULL;
			head = newNode;
			++length;
			return;
		}
		Node<T>* last = head;
		while (last->next)
			last = last->next;

		last->next = newNode;

		newNode->prev = last;
		++length;
	}

	void insert(const size_t& pos, const T& data)
	{
		if (pos == 1)
		{
			push_front(data);
			return;
		}
		else
		{
			Node<T>* newNode = new Node<T>(data);
			Node<T>* thru_ = head;
			for (int i = 1; i < pos - 1; i++)
				if (thru_) thru_ = thru_->next;

			if (thru_)
			{
				newNode->next = thru_->next;
				newNode->prev = thru_;
				thru_->next = newNode;
				if (newNode->next) newNode->next->prev = newNode;
			}
		}
		++length;
	}
	void erase(size_t index)
	{
		if (!head) return;
		Node<T>* delNode = head;
		while (index && delNode->next)
		{
			delNode = delNode->next;
			--index;
		}
		if (!delNode) return;

		if (head == delNode)
			head = delNode->next;

		if (delNode->next)
			delNode->next->prev = delNode->prev;
		
		if (delNode->prev)
			delNode->prev->next = delNode->next;

		delete delNode;
		delNode = nullptr;
		--length;
	}

	void replace(const size_t index, const T& data)
	{
		erase(index);
		insert(index, data);
	}

	void clear()
	{
		Node<T>* temp = head;
		while (head)
		{
			temp = head;
			head = head->next;
			delete temp;
			temp = nullptr;
		}
		length = 0;
	}

	const bool& empty() const
	{
		return (length == 0);
	}

	const size_t& size() const
	{
		return length;
	}

	T& operator[](size_t index) const
	{
		Node<T>* node = head;
		while (index && node->next)
		{
			node = node->next;
			--index;
		}
		return node->data;
	}

	T& end() const
	{
		return this->operator[](length - 1);
	}

	void operator=(const DoublyLinkedList& l)
	{
		this->clear();
		for (size_t i = 0; i < l.size(); i++)
			this->push_back(l[i]);			
	}
};