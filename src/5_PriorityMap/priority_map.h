#ifndef __PICHULIA_PRIORITY_MAP_H__
#define __PICHULIA_PRIORITY_MAP_H__

#include<map>
#include<algorithm>
#include<vector>
#include<assert.h>

namespace wahaha
{
    template<typename Key, typename Value>
    class priority_map
    {
    public:
        priority_map(){
            clear();
        }
        void clear(){
            ap.clear();
            hl = 1;
            heap.resize(hl);
        }
        size_t size() const{
            return ap.size();
        }
        const Value& top() const{
            assert(hl > 1);
            return heap[1].value;
        }

        void insert(const Key& key, const Value& value)
        {
            int hid;
            if(ap.count(key) == 0){
                if(hl == heap.size()){
                    heap.resize(2*hl);
                }
                hid = hl++;
                heap[hid].key = key;
                heap[hid].value = value;
                ap[key] = hid;
            }
            else{
                hid = ap[key];
                heap[hid].value = value;
            }
            __update(hid);
        }
        void erase(const Key& key){
            pop(key);
        }
        void pop(){
            if(hl == 1)return;
            __pop(1);
        }
        void pop(const Key& key){
            if(ap.count(key) == 0)return;
            __pop(ap[key]);
        }
        
        const Value& operator[](Key key) const{
            if(ap.count(key) == 0){
                return Value();
            }
            int hid = ap[key];
            return heap[hid].value;
        }
    private:
        void __pop(int hid){
            hl--;
            if(hid != hl){
                int rid = hl;
                std::swap(heap[hid], heap[rid]);
                ap[heap[hid].key] = hid;
                ap[heap[rid].key] = rid;
            }
            ap.erase(heap[hl].key);
            __update(hid);
        }
        void __update(int hid){
            while(hid / 2 > 0){
                int rid = hid/2;
                if(heap[rid].value < heap[hid].value){
                    std::swap(heap[hid], heap[rid]);
                    ap[heap[hid].key] = hid;
                    ap[heap[rid].key] = rid;
                    hid = rid;
                }
                else{
                    break;
                }
            }
            while(hid * 2 < hl){
                int pid = hid*2;
                int qid = hid*2+1;
                int rid = pid;
                if(qid < hl){
                    if(heap[rid].value < heap[qid].value){
                        rid = qid;
                    }
                }
                if(heap[hid].value < heap[rid].value){
                    std::swap(heap[hid], heap[rid]);
                    ap[heap[hid].key] = hid;
                    ap[heap[rid].key] = rid;
                    hid = rid;
                }
                else{
                    break;
                }
            }
        }

    private:
        struct Node{
            Key key;
            Value value;
        };
        std::map<Key, int> ap;
        std::vector<Node> heap;
        int hl;
    /* Iterator */
    public:
    };
} // namespace std

#endif // __PICHULIA_PRIORITY_MAP_H__