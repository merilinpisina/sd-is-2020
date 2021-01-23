#ifndef HASH_TABLE
#define HASH_TABLE

#include <iostream>
#include <exception>
#include <cstring>

#define CAPACITY 500 // Size of the Hash Table

unsigned long hash_function(char *str)
{
    unsigned long i = 0;
    for (int j = 0; str[j]; j++)
        i += str[j];
    return i % CAPACITY;
}

struct HashTableItem
{
    char *key;
    char *value;

    ~HashTableItem()
    {
        delete[] key;
        delete[] value;
    }
};

HashTableItem *createItem(char *key, char *value)
{
    // Creates a pointer to a new hash table item
    HashTableItem *item = new (std::nothrow) HashTableItem;
    if (item == nullptr)
    {
        throw std::bad_alloc();
    }

    item->key = new (std::nothrow) char[strlen(key) + 1];
    if (item->key == nullptr)
    {
        throw std::bad_alloc();
    }

    item->value = new (std::nothrow) char[strlen(value) + 1];
    if (item->value == nullptr)
    {
        throw std::bad_alloc();
    }

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

struct HashTableNode
{
    HashTableItem *item;
    HashTableNode *next;
};

HashTableNode *createNewNode(HashTableItem *item)
{
    HashTableNode *newNode = new (std::nothrow) HashTableNode;
    if (newNode == nullptr)
    {
        throw std::bad_alloc();
    }

    newNode->item = item;
    newNode->next = nullptr;
    return newNode;
}

HashTableNode *insert(HashTableNode *root, HashTableItem *item)
{
    // If list does not exist
    if (!root)
    {
        HashTableNode *head = createNewNode(item);
        root = head;
        return root;
    }

    if (root->next == nullptr)
    {
        HashTableNode *head = createNewNode(item);
        root->next = head;
        return root;
    }

    HashTableNode *temp = root;
    while (temp->next->next != nullptr)
    {
        temp = temp->next;
    }

    HashTableNode *head = createNewNode(item);
    temp->next = head;
    return root;
}

HashTableItem *remove(HashTableNode *root)
{
    // Removes the head of the linked list and returns the popped element
    if (root == nullptr || root->next == nullptr)
    {
        return nullptr;
    }

    HashTableNode *node = root->next;
    HashTableNode *temp = root;
    temp->next = nullptr;
    root = node;
    delete temp;
    return root;
}

void freeList(HashTableNode *root)
{
    HashTableNode *temp = root;
    while (root)
    {
        temp = root;
        root = root->next;
        delete (temp);
    }
}

struct HashTable
{
    HashTableItem **items;
    HashTableNode **overflowBuckets;
    size_t capacity, size;

    HashTable(size_t capacity = CAPACITY) : capacity(capacity), size(0)
    {
        items = new (std::nothrow) HashTableItem *[capacity];
        if (items == nullptr)
        {
            throw std::bad_alloc();
        }

        for (size_t i = 0; i < capacity; ++i)
        {
            items[i] = nullptr;
        }

        overflowBuckets = createOverflowBuckets(this);
    }

    // copy constructor
    HashTable(const HashTable &other) = delete;

    // operator =
    HashTable &operator=(const HashTable &other) = delete;

    ~HashTable()
    {
        for (int i = 0; i < size; ++i)
        {
            delete items[i];
            if (overflowBuckets[i] != nullptr)
            {
                delete overflowBuckets[i];
            }
        }
        delete[] items;
        delete[] overflowBuckets;
    }
};

HashTableNode **createOverflowBuckets(HashTable *ht)
{
    // Create the overflow bucketa -> an array of linked lists
    HashTableNode **buckets = new (std::nothrow) HashTableNode *[ht->capacity];
    if (buckets == nullptr)
    {
        throw std::bad_alloc();
    }
    for (size_t i = 0; i < ht->capacity; ++i)
    {
        buckets[i] = nullptr;
    }
    return buckets;
}

void handleCollision(HashTable *ht, HashTableItem *item)
{
    return;
}

void insert(HashTable *ht, char *key, char *value)
{
    // Create the new item
    HashTableItem *item = createItem(key, value);

    // Determine the new index
    unsigned long index = hash_function(key);

    if (ht->items[index] == nullptr)
    {
        // Key & index do not exist
        if (ht->size == ht->capacity)
        {
            // Hash table is full (possible dealing decision - dynamic array)
            throw std::invalid_argument("Insert error: Hash table is full\n");
        }
        // Insert directly
        ht->items[index] = item;
        ht->size++;
        return;
    }

    if (strcmp(ht->items[index]->key, key) == 0)
    {
        delete[] ht->items[index]->value;
        ht->items[index]->value = new (std::nothrow) char[strlen(value) + 1];
        if (ht->items[index]->value == nullptr)
        {
            throw std::bad_alloc();
        }

        strcpy(ht->items[index]->value, value);
        return;
    }

    // Collision
    handleCollision(ht, item);
    return;
}

char *search(HashTable *ht, char *key)
{
    unsigned long index = hash_function(key);
    HashTableItem *item = ht->items[index];
    if (item != nullptr)
    {
        if (strcmp(item->key, key) == 0)
            return item->value;
        // We found the index, but not the item -> error (due to prev collision)
    }
    return nullptr;
}

void remove(HashTable *ht, char *key)
{
    unsigned long index = hash_function(key);
    HashTableItem *item = ht->items[index];
    if (item != nullptr)
    {
        delete item;
        return;
    }
    throw std::invalid_argument("Delete Error: Trying to delete a non-existant item");
}

#endif