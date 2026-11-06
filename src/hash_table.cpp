#include "project/hash_table.h"

#include <cmath>
#include <stdexcept>
#include <utility>

HashTable::HashTable(std::size_t capacity)
    : table_(capacity), size_(0) {
    if (capacity == 0) {
        throw std::invalid_argument("Hash table capacity must be greater than zero");
    }
    for (std::size_t i = 0; i < table_.size(); ++i) {
        table_[i] = HashEntry();
    }
}

HashTable::~HashTable() = default;

std::size_t HashTable::hashFunction(const std::string& key) const {
    std::size_t hash = 2166136261u;
    for (unsigned char ch : key) {
        hash ^= ch;
        hash *= 16777619u;
    }
    return hash % table_.size();
}

std::size_t HashTable::probe(const std::string& key) const {
    std::size_t index = hashFunction(key);
    std::size_t original = index;
    std::size_t step = 1;

    while (table_[index].occupied && table_[index].key != key) {
        index = (original + step * step) % table_.size();
        ++step;
    }
    return index;
}
bool HashTable::insert(const std::string& key, int value) {
    std::size_t original = hashFunction(key);
    std::size_t index = original;
    std::size_t step = 1;
    std::size_t firstDeleted = table_.size();

    for (std::size_t i = 0; i < table_.size(); i++) {

        // Check for duplicate key
        if (table_[index].occupied &&
            !table_[index].deleted &&
            table_[index].key == key) {
            return false;
        }

        // Remember the first deleted slot
        if (table_[index].deleted &&
            firstDeleted == table_.size()) {
            firstDeleted = index;
        }

        // Found a never-used slot
        if (!table_[index].occupied) {

            // Prefer reusing a deleted slot
            if (firstDeleted != table_.size()) {
                index = firstDeleted;
            }

            table_[index].key = key;
            table_[index].value = value;
            table_[index].occupied = true;
            table_[index].deleted = false;
            ++size_;

            if (loadFactor() > 0.5) {
                rehash();
            }

            return true;
        }

        // Quadratic probing
        index = (original + step * step) % table_.size();
        ++step;
    }

    // No empty slot found, but a tombstone exists
    if (firstDeleted != table_.size()) {
        table_[firstDeleted].key = key;
        table_[firstDeleted].value = value;
        table_[firstDeleted].occupied = true;
        table_[firstDeleted].deleted = false;
        ++size_;

        if (loadFactor() > 0.5) {
            rehash();
        }

        return true;
    }

    // No available slot was found
    rehash();
    return insert(key, value);
}

bool HashTable::remove(const std::string& key) {
    std::size_t index = hashFunction(key);
    std::size_t original = index;
    std::size_t step = 1;

    for (std::size_t i = 0; i < table_.size(); i++) {
        if (!table_[index].occupied && !table_[index].deleted) {
            return false;
        }

        if (!table_[index].deleted &&
            table_[index].key == key) {
            table_[index].deleted=true;
            size_--;
            return true;
        }

        index = (original + step * step) % table_.size();
        ++step;
    }

    return false;
}

bool HashTable::contains(const std::string& key) const {
    std::size_t index = hashFunction(key);
    std::size_t original = index;
    std::size_t step = 1;

    for (std::size_t i = 0; i < table_.size(); i++) {
        if (!table_[index].occupied && !table_[index].deleted) {
            return false;
        }

        if (!table_[index].deleted &&
            table_[index].key == key) {
            return true;
        }

        index = (original + step * step) % table_.size();
        ++step;
    }

    return false;
}

int HashTable::get(const std::string& key) const {
    std::size_t index = hashFunction(key);
    std::size_t original = index;
    std::size_t step = 1;

    for (std::size_t i = 0; i < table_.size(); i++) {
        if (!table_[index].occupied && !table_[index].deleted) {
            throw std::logic_error("Index not in map");
        }

        if (!table_[index].deleted && table_[index].occupied 
            && table_[index].key == key) {
            return table_[index].value;
        }

        index = (original + step * step) % table_.size();
        ++step;
    }

    throw std::logic_error("Index not in map");
    
}

bool HashTable::update(const std::string& key, int newValue) {
    std::size_t index = hashFunction(key);
    std::size_t original = index;
    std::size_t step = 1;

    for (std::size_t i = 0; i < table_.size(); i++) {
        if (!table_[index].occupied && !table_[index].deleted) {
            return false;
        }

        if (!table_[index].deleted &&
            table_[index].key == key) {
            table_[index].value=newValue;
            return true;
        }

        index = (original + step * step) % table_.size();
        ++step;
    }

    return false;
}

std::size_t HashTable::size() const noexcept {
    return size_;
}

std::size_t HashTable::capacity() const noexcept {
    return table_.size();
}

bool HashTable::empty() const noexcept {
    return size_ == 0;
}

double HashTable::loadFactor() const noexcept {
    return static_cast<double>(size_) / static_cast<double>(table_.size());
}

std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> result;
    for (const auto& entry : table_) {
        if (entry.occupied && !entry.deleted) {
            result.push_back(entry.key);
        }
    }
    return result;
}

std::vector<int> HashTable::values() const {
    std::vector<int> result;
    for (const auto& entry : table_) {
        if (entry.occupied && !entry.deleted) {
            result.push_back(entry.value);
        }
    }
    return result;
}
void HashTable::rehash() {
    // Save the old table
    std::vector<HashEntry> oldTable = std::move(table_);

    // Calculate a larger prime capacity
    std::size_t newCapacity = nextPrime(oldTable.size() * 2);

    // Create a new empty table
    table_ = std::vector<HashEntry>(newCapacity);

    // Reset size
    size_ = 0;

    // Reinsert active entries
    for (const auto& entry : oldTable) {
        if (entry.occupied && !entry.deleted) {
            insert(entry.key, entry.value);
        }
    }
}
bool HashTable::isPrime(std::size_t value) const {
    if (value < 2) {
        return false;
    }
    if (value == 2) {
        return true;
    }
    if (value % 2 == 0) {
        return false;
    }
    for (std::size_t i = 3; i * i <= value; i += 2) {
        if (value % i == 0) {
            return false;
        }
    }
    return true;
}

std::size_t HashTable::nextPrime(std::size_t value) const {
    if (value <= 2) {
        return 2;
    }
    std::size_t candidate = value % 2 == 0 ? value + 1 : value;
    while (!isPrime(candidate)) {
        candidate += 2;
    }
    return candidate;
}
