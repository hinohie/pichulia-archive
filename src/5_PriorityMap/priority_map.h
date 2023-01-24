#ifndef __PICHULIA_PRIORITY_MAP_H__
#define __PICHULIA_PRIORITY_MAP_H__

#include<map>
#include<algorithm>
#include<vector>
#include<stdint.h>
#include<assert.h>

namespace wahaha
{
    template<typename Key, typename Value>
    class priority_map
    {
    public:
        // public struct
        // TODO : Can we make Node's key as const Key& instead of Key?
        using Node = std::pair<Key, Value>;

        using HeapContainer = std::vector<Node>;
        using iterator = typename HeapContainer::iterator;
        using const_iterator = typename HeapContainer::const_iterator;

        using HeapIndex = size_t;

        using MapContainer = std::map<Key, HeapIndex>; // Helper of key-index

        priority_map(){
        }
        ~priority_map(){
        }
        void clear(){
            ap.clear();
            heap.clear();
            heap.shrink_to_fit();
        }
        size_t size() const{
            return ap.size();
        }
        const Value& top() const{
            assert(ap.size() > 0);
            return heap[0].second;
        }

        iterator insert(const Key& key, const Value& value)
        {
            HeapIndex hid;
            auto mapIter = ap.lower_bound(key);

            if(mapIter == ap.end() || std::less<Key>()(key, mapIter->first)){
                hid = static_cast<HeapIndex>(ap.size());
                auto newIter = ap.insert(mapIter, {key, hid});
                heap.emplace_back(newIter->first, value);
            }
            else{
                hid = ap[key];
                heap[hid].second = value;
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
        
        const Value& operator[](Key key) const{
            if(ap.count(key) == 0){
                return Value();
            }
            HeapIndex hid = ap[key];
            return heap[hid].second;
        }
    private:
        void __pop(HeapIndex hid){
            assert(ap.size() > 0);
            const HeapIndex lastHl = static_cast<HeapIndex>(ap.size()-1);
            if(hid != lastHl){
                HeapIndex rid = lastHl;
                std::swap(heap[hid], heap[rid]);
                ap[heap[hid].first] = hid;
                ap[heap[rid].first] = rid;
            }
            ap.erase(heap[lastHl].first);
            __update(hid);
        }
        void __update(HeapIndex hid){
            while(hid > 0){
                HeapIndex rid = (hid+1)/2-1;
                if(heap[rid].second < heap[hid].second){
                    std::swap(heap[hid], heap[rid]);
                    ap[heap[hid].first] = hid;
                    ap[heap[rid].first] = rid;
                    hid = rid;
                }
                else{
                    break;
                }
            }
            while(hid * 2 + 1 < ap.size()){
                int pid = hid*2 + 1;
                int qid = hid*2 + 2;
                int rid = pid;
                if(qid < ap.size()){
                    if(heap[rid].second < heap[qid].second){
                        rid = qid;
                    }
                }

                if(heap[hid].second < heap[rid].second){
                    std::swap(heap[hid], heap[rid]);
                    ap[heap[hid].first] = hid;
                    ap[heap[rid].first] = rid;
                    hid = rid;
                }
                else{
                    break;
                }
            }
        }

    private:
        MapContainer ap{};
        HeapContainer heap{};
    public:
        /* Iterator */
        iterator begin(){
            return heap.begin();
        }
        const_iterator begin() const {
            return heap.begin();
        }
        const_iterator cbegin(){
            return heap.cbegin();
        }

        iterator end(){
            return heap.end();
        }
        const_iterator end() const {
            return heap.end();
        }
        const_iterator cend(){
            return heap.cend();
        }
    };
} // namespace std

#endif // __PICHULIA_PRIORITY_MAP_H__