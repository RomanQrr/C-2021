#pragma once
#include "HashTable.h"

template <typename K, typename V>
class LinckedHT : public HashTable<K, V>
{
private:
	HashEntries<K, V>* list;
public:
	LinckedHT(int size = 10) : HashTable<K, V>(size) {
		list = new HashEntries<K, V>();
	}

	LinckedHT(const LinckedHT<K, V>& linkedTable);

	LinckedHT(LinckedHT<K, V>&& linkedTable);

	LinckedHT& operator= (const LinckedHT<K, V>& linkedTable);

	LinckedHT& operator=(LinckedHT<K, V>&& linkedTable);

	void add(const V& key, const V& value) {
		HashTable<K, V>::add(key, value);
		list->add(key, value);
	}

	const V& remove(const K& key) {
		HashTable<K, V>::remove(key);
		return list->remove(key);
	}

	void doEmpty() {
		HashTable<K, V>::doEmpty();
		list->doEmpty();
	}

	bool isEmpty() const { return list->isEmpty(); }

	EntriesIterator<K, V>* iterator() { return list->iterator(); }

	~LinckedHT() { delete list; }
};

template<typename K, typename V>
inline LinckedHT<K, V>::LinckedHT(const LinckedHT<K, V>& linkedTable) :
	HashTable<K, V>(linkedTable)
{
	list = new HashEntries<K, V>(linkedTable.list);
}

template<typename K, typename V>
inline LinckedHT<K, V>::LinckedHT(LinckedHT<K, V>&& linkedTable) :
	HashTable<K, V>(linkedTable)
{
	list = new HashEntries<K, V>(linkedTable.list);
	linkedTable.list = nullptr;
}

template<typename K, typename V>
inline LinckedHT<K, V>& LinckedHT<K, V>::operator=(const LinckedHT<K, V>& linkedTable)
{
	if (this == &linkedTable) { return *this; }
	doEmpty();
	HashTable<K, V>:: operator=(linkedTable);
	*list = *linkedTable.list;
	return *this;
}

template<typename K, typename V>
inline LinckedHT<K, V>& LinckedHT<K, V>::operator=(LinckedHT<K, V>&& linkedTable)
{
	if (this == &linkedTable) { return *this; }
	HashTable<K, V>:: operator=(linkedTable);
	*list = *linkedTable.list;
	return *this;
}
