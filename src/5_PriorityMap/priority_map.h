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
    template<typename Key, typename Value, typename KeyHash = std::hash<Key>, typename ValueComp = std::less<Value>>
    class priority_map
    {
    public:
        // public struct
        struct Node
        {
            Node(const Key* keyPtr, const Value& value)
            : keyPtr(keyPtr), value(value)
            {
            }
            Node(const Node& node)
            : keyPtr(node.keyPtr), value(node.value)
            {
            }
            Node(Node&& node) noexcept
            : keyPtr(node.keyPtr), value(std::move_if_noexcept(node.value))
            {
            }

            Node& operator=(const Node& node){
                this->keyPtr = node.keyPtr;
                this->value = node.value;
                return *this;
            }
            Node& operator=(Node&& node) noexcept {
                this->keyPtr = node.keyPtr;
                this->value = std::move_if_noexcept(node.value);
                return *this;
            }

            const Key* __restrict__ keyPtr;
            Value value;
        };
    public:
        using HeapIndex = size_t;

        /* Iterator */
        struct Iterator
        {
        public:
            const priority_map<Key, Value, KeyHash, ValueComp>* __restrict__ map = nullptr;
            HeapIndex index = 0u;
            
            Iterator() noexcept = default;
            Iterator(const priority_map<Key, Value, KeyHash, ValueComp>* map, HeapIndex index)
            : map(map), index(index)
            {
            }

            const std::pair<const Key&, const Value&> operator*() const {
                assert(map);
                assert(index < map->ap.size());
                const Node& node = map->heap[index];
                return {*node.keyPtr, node.value};
            }
            const std::pair<const Key&, const Value&>* operator->() = delete;

            Iterator& operator++() noexcept {
                ++index;
                return *this;
            }
            Iterator operator++(int) noexcept {
                Iterator temp = *this;
                ++index;
                return temp;
            }
            Iterator& operator--() noexcept {
                --index;
                return *this;
            }
            Iterator operator--(int) noexcept {
                Iterator temp = *this;
                --index;
                return temp;
            }

            friend Iterator operator+(Iterator iter, HeapIndex diff) noexcept {
                return Iterator(iter.map, iter.index + diff);
            }
            friend Iterator operator-(Iterator iter, HeapIndex diff) noexcept {
                return Iterator(iter.map, iter.index - diff);
            }
            Iterator& operator+=(HeapIndex diff) noexcept {
                index += diff;
                return *this;
            }
            Iterator& operator-=(HeapIndex diff) noexcept {
                index += diff;
                return *this;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept {
                return lhs.map == rhs.map && lhs.index == rhs.index;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs) noexcept {
                return !(lhs == rhs);
            }
        };

    public:
        using HeapContainer = std::vector<Node>;
        using iterator = Iterator;

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
            assert(ap.size() > 0);
            return *heap[0].keyPtr;
        }
        const Value& top() const{
            assert(ap.size() > 0);
            return heap[0].value;
        }

        iterator insert(const Key& key, const Value& value)
        {
            HeapIndex hid;
            auto mapIter = ap.find(key);

            if(mapIter == ap.end()){
                hid = static_cast<HeapIndex>(ap.size());
                auto newIter = ap.insert(mapIter, {key, hid});
                heap.emplace_back(&newIter->first, value);
            }
            else{
                hid = mapIter->second;
                heap[hid].value = value;
            }
            __update(hid);

            return begin() + (ap[key]);
        }
        void erase(const Key& key){
            pop(key);
        }
        void pop(){
            if(ap.size() == 0)return;
            __pop(0);
        }
        void pop(const Key& key){
            if(ap.count(key) == 0)return;
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
            assert(ap.size() > 0);
            const HeapIndex lastHl = static_cast<HeapIndex>(ap.size()-1);
            if(hid != lastHl){
                HeapIndex rid = lastHl;
                std::swap(heap[hid], heap[rid]);
                ap[*heap[hid].keyPtr] = hid;
                ap[*heap[rid].keyPtr] = rid;
            }
            ap.erase(*heap[lastHl].keyPtr);
            heap.pop_back();
            __update(hid);
        }
        void __update(HeapIndex hid){
            const size_t hl = ap.size();
            const Key* __restrict__ lastKeyPtr = nullptr;

            while(hid > 0){
                HeapIndex rid = (hid+1)/2-1;
                if(ValueComp()(heap[rid].value, heap[hid].value)){
                    std::swap(heap[hid], heap[rid]);
                    ap[*heap[hid].keyPtr] = hid;
                    hid = rid;
                    lastKeyPtr = heap[hid].keyPtr;
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
                    ap[*heap[hid].keyPtr] = hid;
                    hid = rid;
                    lastKeyPtr = heap[hid].keyPtr;
                }
                else{
                    break;
                }
            }

            if(lastKeyPtr != nullptr)
            {
                ap[*lastKeyPtr] = hid;
            }
        }

    private:
        MapContainer ap{};
        HeapContainer heap{};
    public:
        iterator begin(){
            return Iterator(this, 0);
        }

        iterator end(){
            return Iterator(this, ap.size());
        }
    };
} // namespace std

#endif // __PICHULIA_PRIORITY_MAP_H__