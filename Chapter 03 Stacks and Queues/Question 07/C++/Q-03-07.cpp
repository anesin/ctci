// Q-03-07.cpp
//   An animal shelter holds only dogs and cats, and operates on a strictly
//   "first in, first out" basis. People must adopt either the "oldest"
//   (based on arrival time) of all animals at the shelter,
//   or they can select whether they would prefer a dog or a cat
//   (and will receive the oldest animal of that type).
//   They cannot select which specific animal they would like.
//   Create the data structures to maintain this system and implement operations
//   such as enqueue, dequeueAny, dequeueDog and dequeueCat.
//   You may use the built-in LinkedList data structure.
//

#include "stdafx.h"
#include <list>
#include <iostream>
#include "time.h"

using namespace std;


typedef enum { kDog, kCat, kNone } AnimalType;
typedef struct {
	AnimalType kind;
	int number;

	void print() const {
		if (kind == kDog)
			cout << "Dog_" << number;
		else if (kind == kCat)
			cout << "Cat_" << number;
		else
			cout << "It's not ANIMAL!!!";
	}
} Animal;

static const Animal NONE_ANIMAL = {kNone, INT_MIN};


class Shelter {
private:
	list<Animal> data_;

public:
	void enqueue(const Animal &animal) {
		if (animal.kind == kDog || animal.kind == kCat)
			data_.push_back(animal);
	}
	Animal dequeueAny() {
		if (data_.empty())
			return NONE_ANIMAL;
		return dequeue(data_.begin());
	}
	Animal dequeueDog() {
		return dequeue(kDog);
	}
	Animal dequeueCat() {
		return dequeue(kCat);
	}

private:
	Animal dequeue(list<Animal>::iterator it) {
		Animal animal = *it;
		data_.erase(it);
		return animal;
	}

	// time complexity: O(N)
	// space complexity: O(N)
	Animal dequeue(AnimalType kind) {
		list<Animal>::iterator it;
		for (it = data_.begin(); it != data_.end(); ++it) {
			if (it->kind == kind)
				return dequeue(it);
		}
		return NONE_ANIMAL;
	}
};


void print(const char *title, const Animal &animal) {
	cout << title;
	animal.print();
	cout << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Shelter shelter;
	Animal animal;

	srand((unsigned)time(NULL));
	size_t size = 15 + rand() % 10;
	while (--size) {
		if (size % 3 == 0) {
			animal = shelter.dequeueDog();
			print("dequeueDog: ", animal);
		} else if (size % 5 == 0) {
			animal = shelter.dequeueCat();
			print("dequeueCat: ", animal);
		} else if (size % 7 == 0) {
			animal = shelter.dequeueAny();
			print("dequeueAny: ", animal);
		} else {
			animal.number = (unsigned)rand();
			animal.kind = (AnimalType)((unsigned)rand() % kNone);
			shelter.enqueue(animal);
			print("enqueue: ", animal);
		}
	}
	return 0;
}

