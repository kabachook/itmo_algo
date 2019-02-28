#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node
{
    string key;
    vector<string> values;
    Node *next;
};

struct List
{
    Node *start;

    List()
    {
        start = new Node();
        start->key = "";
        start->next = nullptr;
    }

    void insert(string key, string value)
    {
        Node *newNode = search(key);
        if (search(key) == nullptr)
        {
            newNode = new Node;
            newNode->key = key;
            newNode->values.push_back(value);
            newNode->next = start->next;
            start->next = newNode;
        }
        else
        {
            for (int i = 0; i < newNode->values.size(); ++i)
            {
                if (newNode->values[i] == value)
                    return;
            }
            newNode->values.push_back(value);
        }
    }

    void deleteall(string key)
    {
        Node *curNode = start;
        while (curNode->next != nullptr)
        {
            if (curNode->next->key == key)
            {
                Node *nodeToDel = curNode->next;
                curNode->next = curNode->next->next;
                delete nodeToDel;
                return;
            }
            else
            {
                curNode = curNode->next;
            }
        }
    }

    void delete_val(string key, string value)
    {
        Node *curNode = start;
        while (curNode->next != nullptr)
        {
            if (curNode->next->key == key)
            {
                for (int i = 0; i < curNode->next->values.size(); ++i)
                    if (curNode->next->values[i] == value)
                    {
                        swap(curNode->next->values[i], curNode->next->values[curNode->next->values.size() - 1]);
                        curNode->next->values.resize(curNode->next->values.size() - 1);
                    }
                return;
            }
            else
            {
                curNode = curNode->next;
            }
        }
    }

    Node* search(string K)
    {
        Node *curNode = start;
        while (curNode->next != nullptr)
        {
            if (curNode->next->key == K)
            {
                return curNode->next;
            }
            else
            {
                curNode = curNode->next;
            }
        }
        return nullptr;
    }
};

struct MultiMap
{
    vector<List> table;

    MultiMap()
    {
        table.resize(1000);
    }

    size_t hash(string key)
    {
        size_t res = 0, pow = 1, p = 31, s = table.size();
        for (int i = 0; i < key.length(); ++i)
        {
            res += (key[i] - 'A') * pow;
            pow *= p;
        }
        return res % s;
    }

    void insert(string key, string value)
    {
        table[hash(key)].insert(key, value);
    }

    void deleteall(string key)
    {
        table[hash(key)].deleteall(key);
    }

    void delete_val(string key, string value)
    {
        table[hash(key)].delete_val(key, value);
    }


    vector<string> get(string key)
    {
        Node *res = table[hash(key)].search(key);
        if (res == nullptr)
            return {};
        else
            return res->values;
    }
};
int main()
{
    ifstream fin("multimap.in");
    ofstream fout("multimap.out");
    MultiMap mmap;
    string cmd;
    while (fin >> cmd)
    {
        string key, value;
        if (cmd == "put")
        {
            fin >> key >> value;
            mmap.insert(key, value);
        }
        else if (cmd == "delete")
        {
            fin >> key >> value;
            mmap.delete_val(key, value);
        }
        else if (cmd == "deleteall")
        {
            fin >> key;
            mmap.deleteall(key);
        }
        else if (cmd == "get")
        {
            fin >> key;
            vector<string> result = mmap.get(key);
            fout << result.size();
            for (int i = 0; i < result.size(); ++i)
                fout << " " << result[i];
            fout << "\n";
        }
    }
    return 0;
}