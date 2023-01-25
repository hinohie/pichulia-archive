#ifndef __PICHULIA_ORDERED_MAP_H__
#define __PICHULIA_ORDERED_MAP_H__

#include<unordered_map>
#include<algorithm>
#include<list>
#include<stdint.h>
#include<assert.h>
#include<functional>

namespace wahaha
{
    template<typename Key, typename Value, typename KeyHash = std::hash<Key>>
    class ordered_map
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
        using ListContainer = std::list<Node>;
        using ListIterator = typename ListContainer::iterator;
    public:
        /* Iterator */
        struct Iterator
        {
        public:
            const ordered_map<Key, Value, KeyHash>* __restrict__ map{nullptr};
            ListIterator iter{};
            
            Iterator() noexcept = default;
            Iterator(const ordered_map<Key, Value, KeyHash>* map, ListIterator iter)
            : map(map), iter(iter)
            {
            }

            const std::pair<const Key&, const Value&> operator*() const {
                assert(map);
                const Node& node = *iter;
                return {*node.keyPtr, node.value};
            }
            const std::pair<const Key&, const Value&>* operator->() = delete;

            Iterator& operator++() noexcept {
                ++iter;
                return *this;
            }
            Iterator operator++(int) noexcept {
                Iterator temp = *this;
                ++iter;
                return temp;
            }
            Iterator& operator--() noexcept {
                --iter;
                return *this;
            }
            Iterator operator--(int) noexcept {
                Iterator temp = *this;
                --iter;
                return temp;
            }

            friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept {
                return lhs.map == rhs.map && lhs.iter == rhs.iter;
            }

            friend bool operator!=(const Iterator& lhs, const Iterator& rhs) noexcept {
                return !(lhs == rhs);
            }
        };

    public:
        using iterator = Iterator;

        using MapContainer = std::unordered_map<Key, ListIterator, KeyHash>; // Helper of key-index

        ordered_map(){
        }
        ~ordered_map(){
        }
        void clear(){
            ap.clear();
            list.clear();
        }
        size_t size() const{
            return list.size();
        }

        iterator insert(const Key& key, const Value& value)
        {
            auto mapIter = ap.find(key);

            if(mapIter == ap.end()){
                // Insert null iter first
                mapIter = ap.insert({key, list.begin()}).first;

                auto listIter = list.insert(list.end(), Node(&mapIter->first, value));
                //Replace iterator
                mapIter->second = listIter;
            }
            else{
                // Do nothing.
            }

            return Iterator(this, mapIter->second);
        }
        iterator erase(const Key& key){
            auto mapIter = ap.find(key);
            if(mapIter == ap.end()){
                return end();
            }

            auto listIter = mapIter->second;
            auto ret = list.erase(listIter);
            ap.erase(mapIter);

            return Iterator(this, ret);
        }

        iterator find(const Key& key)
        {
            auto mapIter = ap.find(key);
            if(mapIter == ap.end()){
                return end();
            }

            return Iterator(this, mapIter->second);
        }
        Value& operator[](Key key) {
            auto mapIter = ap.find(key);
            if(mapIter == ap.end()){
                insert(key, Value());
            }

            auto listIter = ap[key];
            return (*listIter).value;
        }
        const Value& operator[](Key key) const{
            auto mapIter = ap.find(key);
            if(mapIter == ap.end()){
                return Value();
            }

            auto listIter = ap[key];
            return (*listIter).value;
        }
    private:

    private:
        MapContainer ap{};
        ListContainer list{};
    public:
        iterator begin(){
            return Iterator(this, list.begin());
        }

        iterator end(){
            return Iterator(this, list.end());
        }
    };
} // namespace std

#endif // __PICHULIA_ORDERED_MAP_H__