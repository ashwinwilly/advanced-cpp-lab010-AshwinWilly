# Hash Table Analysis Laboratory

## Core goals
Students must implement a hash table that stores key-value pairs using open addressing and quadratic probing.

## Required behaviors
Students must implement:

- insertion with collision handling;
- lookup and retrieval;
- update of existing entries;
- deletion while preserving probe correctness;
- capacity growth and rehashing;
- hash function design;
- complex-key scenarios with many collisions.

## Required analysis
Students should write a short comparison and complexity analysis of:

- average-case insertion, lookup, and removal;
- best-case and worst-case behavior;
- collision resolution strategies;
- load factor and rehashing costs;
- open addressing vs. chaining;
- how clustering can affect performance.

## Big-O expectations
Students should identify and explain the Big-Oh for:

- `insert`
- `remove`
- `get`
- `update`
- `rehash`
- `contains`

Expected average-case: O(1) for insert, lookup, and update under a reasonable load factor; worst case can degrade to O(n) when many collisions occur or the table becomes badly loaded.
