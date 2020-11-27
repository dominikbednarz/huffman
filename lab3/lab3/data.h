#pragma once

namespace data_structures {
	template <class T>
	class Element {
	private:
		T x;
		Element <T> * next;
	public:
		Element<T>(T x) : x(x), next(nullptr) {};

		void setNext(Element<T> *x) {
			next = x;
		};

		Element<T>* getNext() { return next; };

		T& operator*() { return x; };
	};

	template <class T>
	class list {
	private:
		Element<T> *front, *back;
		unsigned counter;
	public:
		list() : front(nullptr), back(nullptr), counter(0) { };
		~list() {
			while (front != nullptr)
			{
				Element<T> * tmp = front;
				front = tmp->getNext();
				delete tmp;
			}
		};

		Element<T>* head() { return this->front; };
		Element<T>* tail() { return this->back; };
		int count() { return counter; }

		void add(T tmp) {
			Element<T>* p = new Element<T>(tmp);

			if (front == nullptr) {
				front = back = p;
			}
			else {
				back->setNext(p);
				back = p;
			};
			
			counter++;
		}
	};
};