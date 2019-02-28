#include <bits/stdc++.h>


using namespace std;

size_t size = 99173, node_size=143;

struct Node {

    string key;
    Node *next = NULL;

};

struct MapNode {

    string key;
    vector<Node *> values = vector<Node *>(node_size, NULL);
    MapNode *next = NULL;

    MapNode() {

        this->values = vector<Node *>(node_size, NULL);

    };

};


string cmd, key, val;
vector<MapNode *> table(size, NULL);
ifstream in("multimap.in");
ofstream out("multimap.out");


size_t hashf(string key, int size) {

    size_t sum = 0;
    for (int i = 0; i < key.length(); i++) {

        sum += int(key[i]);
        sum += (sum << 10);
        sum ^= (sum >> 6);

    }

    sum += (sum << 3);
    sum ^= (sum >> 11);
    sum += (sum << 15);

    return sum % size;
}


void insert_to_node(MapNode *ptr) {

    size_t h = hashf(val, node_size);

    if (ptr->values[h] == NULL) {

        ptr->values[h] = new Node;
        ptr->values[h]->key = val;

    } else {

        Node *cur = ptr->values[h], *prev;
        do {

            if (cur->key == val)
                return;

            prev = cur;
            cur = cur->next;

        } while (cur != NULL);

        prev->next = new Node;
        (prev->next)->key = val;

    }

}

void put() {

    size_t h = hashf(key, size);


    if (table[h] == NULL) {

        table[h] = new MapNode;
        table[h]->key = key;
        insert_to_node(table[h]);

    } else {

        MapNode *cur = table[h], *prev;
        do {

            if (cur->key == key) {

                insert_to_node(cur);
                return;

            }

            prev = cur;
            cur = cur->next;

        } while (cur != NULL);

        prev->next = new MapNode;
        (prev->next)->key = key;
        insert_to_node(prev->next);

    }
}

bool exists(MapNode *cur) {

    for (int i = 0; i < node_size; i++)
        if (cur->values[i] != NULL)
            return true;
    return false;

}

void del_node_value(MapNode *ptr) {

    size_t h = hashf(val, node_size);
    Node *cur = ptr->values[h], *prev;

    if (cur == NULL)
        return;

    else if (cur->key == val) {

        if (cur->next == NULL)
            ptr->values[h] = NULL;

        else
            ptr->values[h] = cur->next;

    } else {

        while (true) {

            if (cur->key == val) {

                prev->next = cur->next;
                return;

            } else if (cur->next == NULL && cur->key != val)
                return;

            prev = cur;
            cur = cur->next;

        }

    }

}


void del_value() {

    size_t h = hashf(key, size);
    MapNode *cur = table[h], *prev;

    if (table[h] == NULL)
        return;

    else if (cur->key == key) {

        del_node_value(cur);

        if (cur->next == NULL && (!exists(cur))) {

            table[h] = NULL;
            delete cur;

        } else if (cur->next != NULL && (!exists(cur))) {

            table[h] = cur->next;
            delete cur;

        }

    } else {

        while (true) {

            if (cur->key == key) {

                del_node_value(cur);

                if (!exists(cur)) {

                    prev->next = cur->next;
                    delete cur;

                }

                return;

            } else if (cur->next == NULL && cur->key != key)
                return;

            prev = cur;
            cur = cur->next;

        }

    }

}


void get() {

    size_t h = hashf(key, size), count = 0;
    MapNode *cur = table[h];
    string result = "";

    while (cur != NULL) {

        if (cur->key == key) {

            for (int i = 0; i < node_size; i++) {

                Node *ptr = cur->values[i];

                while (ptr != NULL) {

                    result += ptr->key + " ";
                    count++;
                    ptr = ptr->next;

                }

            }
            break;

        }
        cur = cur->next;

    }

    out << count << ' ' << result << endl;

    return;

}

void deleteall() {

    size_t h = hashf(key, size);
    MapNode *cur = table[h], *prev;

    if (table[h] == NULL)
        return;

    else if (cur->key == key) {

        if (cur->next == NULL)
            table[h] = NULL;

        else
            table[h] = cur->next;

    } else {

        while (true) {

            if (cur->key == key) {

                prev->next = cur->next;
                return;

            } else if (cur->next == NULL && cur->key != key)
                return;

            prev = cur;
            cur = cur->next;

        }

    }
}


int main() {
    while (in >> cmd) {

        in >> key;

        if (cmd == "put") {
            in >> val;
            put();
        } else if (cmd == "get") {
            get();
        } else if (cmd == "deleteall")
            deleteall();
        else {

            in >> val;
            del_value();
        }
    }

    return 0;
}
