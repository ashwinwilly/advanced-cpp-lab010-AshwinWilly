# Lab 10 — Hash Tables and Collision Handling

## Course
CS 20 — Advanced Programming with C++

## Objective
This lab focuses on implementing a hash table using open addressing with quadratic probing, one of the most important data structures for fast lookup in software systems.

## Required tasks
Students must implement a hash table that stores string keys and integer values. The implementation should support:

- insertion of key-value pairs;
- lookup by key;
- deletion by key;
- update of existing values;
- collision handling using quadratic probing;
- resizable capacity with rehashing;
- calculation of load factor and capacity growth;
- ability to list keys and values.

## Required analysis
Students must also provide a concise but rigorous analysis of:

- time complexity of insertion, lookup, and deletion;
- effect of load factor on performance;
- collision resolution strategies;
- pros and cons of open addressing vs. chaining;
- rehashing cost and table resizing strategy;
- how a poor hash function or high load factor affects performance.

## Required deliverables
Students must submit:

- all C++ source and header files;
- the hash table implementation;
- unit tests covering normal, collision, deletion, and resize behavior;
- a complexity analysis document.

## Quality expectations

- meaningful names;
- clear comments for hashing and probing logic;
- correct handling of collisions and tombstones/delayed deletes where relevant;
- memory-safe implementation;
- no unnecessary globals;
- clean modular design.

## Important note
The starter project intentionally contains function stubs and failing tests. Students must complete the actual implementation and explain the trade-offs in hash-table design.
