# Hash Tables in C++

A Hash Table in C/C++ (Associative array) is a data structure that maps keys to values. This uses a hash function to compute indexes for a key.

Based on the Hash Table index, we can store the value at the appropriate location.

If two different keys get the same index, we need to use other data structures (buckets) to account for these collisions.

![hash table](./img/img1.png)

### Typical questions that rely on hash tables contain phrases like:

- Search for elements within a large data set

- Find duplicate elements in a data set

- Quickly store and retrieve elements from a large data set

The whole benefit of using a Hash Table is due to it’s very fast access time. While there can be a collision, if we choose a very good hash function, this chance is almost zero.

So, on average, the time complexity is a constant **O(1)** access time. This is called **Amortized Time Complexity**.

> In computer science, amortized analysis is a method for analyzing a given algorithm's complexity, or how much of a resource, especially time or memory, it takes to execute. The motivation for amortized analysis is that looking at the worst-case run time per operation, rather than per algorithm, can be too pessimistic.

The C++ STL (**Standard Template Library**) has the ```std::unordered_map()``` data structure which implements all these hash table functions.

However, knowing how to construct a hash table from scratch is a crucial skill, and that is indeed what we aim to show you.

Let us understand more about the implementation details.

Any Hash Table implementation has the following three components:

- A good Hash function to map keys to values

- A Hash Table Data Structure that supports insert, search and delete operations.

- A Data Structure to account for collision of keys

## Choose a Hash Function

The first step is to choose a reasonably good hash function that has a low chance of collision. But, since this is for illustration, I will be doing the opposite! Reverse Psychology, eh?

A very simple hash function, that simply sums the ASCII value of the string:

```
#define CAPACITY 50000 // Size of the Hash Table
 
unsigned long hash_function(char* str) {
    unsigned long i = 0;
    for (int j=0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}
```

You can test this for different strings and check if they collide or not. For example, the strings “Hel” and “Cau” will collide, since they have the same ASCII value.

> NOTE: We must return a number within the capacity of the hash table. Otherwise, we may access an unbound memory location, leading to an error.

## Define the Hash Table data structures

A Hash table is an array of items, which themselves are a ```{key: value}``` pair.

Let’s define our item structure first.

```
typedef struct Ht_item Ht_item;
 
// Define the Hash Table Item here
struct Ht_item {
    char* key;
    char* value;
};
```

Now, the Hash table has an array of pointers which themselves point to **Ht_item**, so it is a double-pointer.

Other than that, we will also keep track of the number of elements in the Hash table using **count**, and store the size of the table in **size**.

```
typedef struct HashTable HashTable;
 
// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    int size;
    int count;
};
```

