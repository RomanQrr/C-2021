#pragma once
#include "HashEntries.h"


template <typename K, typename V>
class HashTable
{
private:
	HashEntries<K, V>* table;
	int size;

public:

	template <typename K, typename V>
	class Iterator {
	private:
		const HashTable<K, V>* hashTable;
		EntriesIterator<K, V>* it;
		int count;

	public:
		Iterator() : hashTable(nullptr), it(nullptr), count(0) {}

		Iterator(const HashTable<K, V>& hashTable) : hashTable(&hashTable), it(nullptr), count(0) {}

		void start() {
			if (hashTable == nullptr) throw new std::exception("Table doesn't exist.");
			it = hashTable->table[0].iterator();
		}

		void next() {
			if (it->isFinish()) {
				count++;
				it = hashTable->table[count].iterator();
			}
			else
			{
				it->next();
			}

		}

		bool isFinish() const {
			return count == hashTable->getSize() - 1 && it->isFinish();
		}

		const V& getValue() const { return it->getValue(); }

		const K& getKey() const { return it->getKey(); }
	};

	Iterator<K, V>* iterator();

	HashTable(int size = 10) : size(size) {
		table = new HashEntries<K, V>[size];
	}
	HashTable(const HashTable& hashTable);
	HashTable(HashTable&& hashTable);
	HashTable& operator=(const HashTable& hashTable);
	HashTable& operator=(HashTable&& hashTable);

	void add(const K& key, const V& value);
	V& remove(const K& key);
	V& find(const K& key);
	void doEmpty();
	bool isEmpty();
	int getSize() const { return size; }

	int hashFunction(const K& key) const {
		std::hash<K> hashFunc;
		return hashFunc(key) % size;
	}
};

template<typename K, typename V>
inline HashTable<K, V>::Iterator<K, V>* HashTable<K, V>::iterator()
{
	Iterator<K, V>* iter = new Iterator<K, V>(*this);
	iter->start();
	return iter;
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(const HashTable& hashTable) : size(hashTable.size)
{
	table = new HashEntries<K, V>[size];
	for (int i = 0; i < size; i++) {
		table[i] = hashTable.table[i];
	}
}

template<typename K, typename V>
inline HashTable<K, V>::HashTable(HashTable&& hashTable) : size(hashTable.size), table(hashTable.table)
{
	hashTable.table = nullptr;
}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(const HashTable& hashTable)
{
	if (this == &hashTable) { return *this; }
	doEmpty();
	HashTable<K, V> copy(hashTable);
	std::swap(size, copy.size);
	std::swap(table, copy.table);
	return *this;
}

template<typename K, typename V>
inline HashTable<K, V>& HashTable<K, V>::operator=(HashTable&& hashTable)
{
	if (this == &hashTable) { return *this; }
	std::swap(size, hashTable.size);
	std::swap(table, hashTable.table);
	return *this;
}

template<typename K, typename V>
inline void HashTable<K, V>::add(const K& key, const V& value)
{
	table[hashFunction(key)].add(key, value);
}

template<typename K, typename V>
inline V& HashTable<K, V>::remove(const K& key)
{
	return table[hashFunction(key)].remove(key);
}

template<typename K, typename V>
inline V& HashTable<K, V>::find(const K& key)
{
	return table[hashFunction(key)].find(key);
}

template<typename K, typename V>
inline void HashTable<K, V>::doEmpty()
{
	delete[] table;
	table = nullptr;
	table = new HashEntries<K, V>[size];
}

template<typename K, typename V>
inline bool HashTable<K, V>::isEmpty()
{
	for (int i = 0; i < size; i++) {
		if (!table[i].isEmpty()) {
			return false;
		}
	}
	return true;
}
