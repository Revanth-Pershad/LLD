#include <bits/stdc++.h>

using namespace std;

class LinkedNode{
    public:
        int key, val;
        LinkedNode *prev, *next;

        LinkedNode(int k, int v){
            key = k;
            val = v;
            prev = next = NULL;
        }
};

class DLL{
    LinkedNode *head, *tail;

    public:
        DLL(){
            head = new LinkedNode(-1, -1);
            tail = new LinkedNode(-1, -1);

            head->next = tail;
            tail->prev = head;
        }

        LinkedNode* insert(int k, int v){
            LinkedNode* temp = new LinkedNode(k, v);
            
            temp->prev = head;
            temp->next = head->next;
            head->next->prev = temp;
            head->next = temp;

            return temp;
        }

        void delNode(LinkedNode *root){
            root->next->prev = root->prev;
            root->prev->next = root->next;

            delete(root);
        }

        LinkedNode* getLast(){
            return tail->prev;
        }
};

class LRU_Cache{
    DLL LinkedList;
    unordered_map<int, LinkedNode*> mp;
    int capacity, curr;

    public:
        LRU_Cache(int cap){
            capacity = cap;
            LinkedList = DLL();
            curr = 0;
        }

        void put(int key, int val){
            if(mp.find(key) != mp.end()){
                LinkedList.delNode(mp[key]);
                mp.erase(mp.find(key));
                curr--;
            }

            if(curr == capacity){
                LinkedNode *temp = LinkedList.getLast();
                mp.erase(mp.find(temp->key));
                LinkedList.delNode(temp);
                curr--;
            }

            LinkedNode *temp = LinkedList.insert(key, val);
            mp[key] = temp;
            curr++;
        }

        int get(int key){
            if(mp.find(key) == mp.end())
                return -1;

            LinkedNode *temp = mp[key];
            int vl = temp->val;
            LinkedList.delNode(temp);
            mp[key] = LinkedList.insert(key, vl);

            return vl;
        }
};

int main(){
    LRU_Cache lr = LRU_Cache(2);
    lr.put(1, 2);
    lr.put(2, 3);

    cout << lr.get(2) << endl;

    lr.put(3, 4);
    cout << lr.get(1);

}