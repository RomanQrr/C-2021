#pragma once
#include <exception>

template <typename K, typename V>
struct Entry {
	Entry(const K& key = K(), const V& value = V(), Entry* next = nullptr) :
		key(key), value(value), next(next) {}

	K key;
	V value;
	Entry* next;
};

template <typename K, typename V>
class EntriesIterator;

template <typename K, typename V>
class HashEntries
{
private:
	Entry<K, V>* tail;

public:
	HashEntries() : tail(nullptr) {}
	HashEntries(const HashEntries& hash);
	HashEntries(HashEntries&& hash);
	~HashEntries() { doEmpty(); }
	HashEntries& operator = (const HashEntries& hash);
	HashEntries& operator = (HashEntries&& hash);

	void add(const K& key, const V& value);
	V& remove(const K& key);
	V& find(const K& key);
	void doEmpty();
	bool isEmpty() { return tail == nullptr; }

	EntriesIterator<K, V>* iterator() {
		EntriesIterator<K, V>* iter = new EntriesIterator<K, V>(*this);
		iter->start();
		return iter;
	}

	Entry<K, V>* getTail() const { return tail; }

};

template<typename K, typename V>

class EntriesIterator
{
private:
	friend class HashEntries<K, V>;

	const HashEntries<K, V>* entries;
	Entry<K, V>* current;
public:
	EntriesIterator() : entries(nullptr), current(nullptr) {}

	EntriesIterator(const HashEntries<K, V>& theEntries) : entries(&theEntries) {}

	void start() {
		current = entries->getTail();
	}

	void next() { current = current->next; }

	bool isFinish() const { return current == nullptr || current->next == nullptr; }

	V& getValue() const { return current->value; }

	K& getKey() const { return current->key; }

	~EntriesIterator() {}
};

template<typename K, typename V>
inline HashEntries<K, V>::HashEntries(const HashEntries& hash)
{
	if (hash.tail == nullptr) tail = nullptr;
	else {
		EntriesIterator<K, V> iter(hash);
		for (iter.start(); !iter.isFinish(); iter.next()) {
			add(iter.getKey(), iter.getValue());
		}
		add(iter.getKey(), iter.getValue());
	}
}

template<typename K, typename V>
inline HashEntries<K, V>::HashEntries(HashEntries&& hash) : tail(hash.tail)
{
	hash.tail = nullptr;
}

template<typename K, typename V>
inline HashEntries<K, V>& HashEntries<K, V>::operator=(const HashEntries& hash)
{
	if (this == &hash) { return *this; }
	doEmpty();
	HashEntries<K, V> copy(hash);
	std::swap(tail, copy.tail);
	return *this;
}

template<typename K, typename V>
inline HashEntries<K, V>& HashEntries<K, V>::operator=(HashEntries&& hash)
{
	if (this == hash) return *this;
	doEmpty();
	this->tail = hash.tail;
	hash.tail = nullptr;
	return *this;
}

template<typename K, typename V>
inline void HashEntries<K, V>::add(const K& key, const V& value)
{
	if (isEmpty()) {
		tail = new Entry<K, V>(key, value);
	}
	else {
		EntriesIterator<K, V>iter(*this);
		for (iter.start(); !iter.isFinish(); iter.next()) {
			if (iter.getKey() == key) {
				iter.current->value = value;
				return;
			}
		}
		if (iter.getKey() == key) {
			iter.current->value = value;
		}
		else {
			iter.current->next = new Entry<K, V>(key, value);
		}
	}
}

template<typename K, typename V>
inline V& HashEntries<K, V>::remove(const K& key)
{
	if (isEmpty()) {
		throw std::exception("List is empty.");
	}
	else {
		if (tail->key == key) {
			Entry<K, V>* temp = tail;
			V value = temp->value;
			tail = tail->next;
			delete temp; temp = nullptr;
			return value;
		}
		else {
			EntriesIterator<K, V> iter(*this);
			for (iter.start(); !iter.isFinish(); iter.next()) {
				if (iter.current->next->key == key) {
					Entry<K, V>* temp = iter.current->next;
					V value = temp->value;
					iter.current->next = iter.current->next->next;
					delete temp; temp = nullptr;
					return value;
				}
			}
		}
		throw std::exception("Key is not present in the list.");
	}
}

template<typename K, typename V>
inline V& HashEntries<K, V>::find(const K& key)
{
	if (isEmpty()) {
		throw std::exception("Key not found.");
	}
	EntriesIterator<K, V> it(*this);
	for (it.start(); !it.isFinish(); it.next()) {
		if (it.current->key == key) {
			return it.getValue();
		}
	}

	if (it.current->key == key) {
		return it.getValue();
	}
	throw std::exception("Key not found.");
}

template<typename K, typename V>
inline void HashEntries<K, V>::doEmpty()
{
	while (!isEmpty())
	{
		Entry<K, V>* temp = tail->next;
		delete tail;
		tail = temp;
		temp = nullptr;
	}
}
