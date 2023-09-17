#ifndef __PICHULIA_PRIORITY_MAP_H__
#define __PICHULIA_PRIORITY_MAP_H__

#include<unordered_map>
#include<algorithm>
#include<vector>
#include<stdint.h>
#include<assert.h>
#include<functional>

namespace wahaha
{
    // Liteweight priority_map without iterator and assert.
    template<typename Key, typename Value, typename KeyHash = std::hash<Key>, typename ValueComp = std::less<Value>>
    class priority_map
    {
    public:
        // public struct
        struct Node
        {
            Node(const Key& key, const Value& value)
            : key(key), value(value)
            {
            }
            Node(const Node& node)
            : key(node.key), value(node.value)
            {
            }
            Node(Node&& node) noexcept
            : key(std::move_if_noexcept(node.key)), value(std::move_if_noexcept(node.value))
            {
            }

            Node& operator=(const Node& node){
                this->key = node.key;
                this->value = node.value;
                return *this;
            }
            Node& operator=(Node&& node) noexcept {
                this->key = std::move_if_noexcept(node.key);
                this->value = std::move_if_noexcept(node.value);
                return *this;
            }

            Key key;
            Value value;
        };
    public:
        using HeapIndex = int;

    public:
        using HeapContainer = std::vector<Node>;

        using MapContainer = std::unordered_map<Key, HeapIndex, KeyHash>; // Helper of key-index

        priority_map(){
        }
        ~priority_map(){
        }
        void clear(){
            ap.clear();
            ap.rehash(0);
            heap.clear();
            heap.shrink_to_fit();
        }
        void reserve(int size)
        {
            ap.rehash(size*2);
            heap.reserve(size);
        }
        size_t size() const{
            return ap.size();
        }
        bool empty() const{
            return ap.empty();
        }
        const Key& topKey() const{
            //assert(ap.size() > 0);
            return heap[0].key;
        }
        const Value& top() const{
            //assert(ap.size() > 0);
            return heap[0].value;
        }

        void insert(const Key& key, const Value& value)
        {
            HeapIndex hid;
            auto mapIter = ap.find(key);

            if(mapIter == ap.end()){
                hid = static_cast<HeapIndex>(ap.size());
                auto newIter = ap.insert(mapIter, {key, hid});
                heap.emplace_back(key, value);
            }
            else{
                hid = mapIter->second;
                heap[hid].value = value;
            }
            __update(hid);

            //return begin() + (ap[key]);
        }
        void erase(const Key& key){
            pop(key);
        }
        void pop(){
            //if(ap.size() == 0)return;
            __pop(0);
        }
        void pop(const Key& key){
            //if(ap.count(key) == 0)return;
            __pop(ap[key]);
        }

        const Value& operator[](Key key) {
            if(ap.count(key) == 0){
                insert(key, Value());
            }
            HeapIndex hid = ap[key];
            return heap[hid].value;
        }
        const Value& operator[](Key key) const{
            if(ap.count(key) == 0){
                return Value();
            }
            HeapIndex hid = ap[key];
            return heap[hid].value;
        }
    private:
        void __pop(HeapIndex hid){
            //assert(ap.size() > 0);
            const HeapIndex lastHl = static_cast<HeapIndex>(ap.size()-1);
            if(hid != lastHl){
                HeapIndex rid = lastHl;
                std::swap(heap[hid], heap[rid]);
                ap[heap[hid].key] = hid;
                ap[heap[rid].key] = rid;
            }
            ap.erase(heap[lastHl].key);
            heap.pop_back();
            __update(hid);
        }
        void __update(HeapIndex hid){
            const size_t hl = ap.size();
            bool swapOnce = false;
            Key lastKey;

            while(hid > 0){
                HeapIndex rid = (hid+1)/2-1;
                if(ValueComp()(heap[rid].value, heap[hid].value)){
                    std::swap(heap[hid], heap[rid]);
                    ap[heap[hid].key] = hid;
                    //ap[heap[rid].key] = rid;
                    hid = rid;
                    swapOnce = true;
                    lastKey = heap[hid].key;
                }
                else{
                    break;
                }
            }
            while(hid * 2 + 1 < hl){
                HeapIndex pid = hid*2 + 1;
                HeapIndex qid = hid*2 + 2;
                HeapIndex rid = pid;
                if(qid < hl){
                    if(ValueComp()(heap[rid].value, heap[qid].value)){
                        rid = qid;
                    }
                }

                if(ValueComp()(heap[hid].value, heap[rid].value)){
                    std::swap(heap[hid], heap[rid]);
                    ap[heap[hid].key] = hid;
                    //ap[heap[rid].key] = rid;
                    hid = rid;
                    swapOnce = true;
                    lastKey = heap[hid].key;
                }
                else{
                    break;
                }
            }
            if(swapOnce)
            {
                ap[lastKey] = hid;
            }
        }

    private:
        MapContainer ap{};
        HeapContainer heap{};
    public:
    };
} // namespace std

#endif // __PICHULIA_PRIORITY_MAP_H__
