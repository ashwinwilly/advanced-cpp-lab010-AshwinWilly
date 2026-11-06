#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

struct HashEntry {
    std::string key;
    int value;
    bool occupied;
    bool deleted;

    HashEntry(const std::string& k = "", int v = 0, bool occ = false, bool del = false)
        : key(k), value(v), occupied(occ), deleted(del) {}
};

class HashTable {
public:
    explicit HashTable(std::size_t capacity = 17);
    ~HashTable();

    bool insert(const std::string& key, int value);
    bool remove(const std::string& key);
    bool contains(const std::string& key) const;
    int get(const std::string& key) const;
    bool update(const std::string& key, int newValue);
    std::size_t size() const noexcept;
    std::size_t capacity() const noexcept;
    bool empty() const noexcept;
    double loadFactor() const noexcept;

    std::vector<std::string> keys() const;
    std::vector<int> values() const;

private:
    std::vector<HashEntry> table_;
    std::size_t size_;

    std::size_t hashFunction(const std::string& key) const;
    std::size_t probe(const std::string& key) const;
    void rehash();
    bool isPrime(std::size_t value) const;
    std::size_t nextPrime(std::size_t value) const;
};
