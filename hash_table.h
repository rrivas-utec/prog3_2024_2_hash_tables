//
// Created by rrivas on 28/11/2024.
//

#ifndef PROG3_2024_2_HASH_TABLES_HASH_TABLE_H
#define PROG3_2024_2_HASH_TABLES_HASH_TABLE_H

#include <vector>
#include <forward_list>
#include <array>
#include <numeric>
#include <algorithm>

namespace utec {
    template <
            typename KeyType,
            typename ValueType,
            typename HashType = std::hash<KeyType>,
            typename KeyEqualType = std::equal_to<KeyType>
            >
    class hash_table {
        // Tipos internos
        using ItemType = std::pair<KeyType, ValueType>;
        using BucketType = std::forward_list<ItemType>;
        // Atributos
        std::vector<BucketType> buckets_;
        HashType pre_hash_fun_;
        double max_load_factor_;
        static constexpr std::array<size_t, 8> prime_sizes = {13, 29, 59, 127, 257, 541, 1109, 2357};

        static size_t get_next_prime(size_t sz) {
            auto it = std::lower_bound(prime_sizes.begin(), prime_sizes.end(), sz);
            if (it != prime_sizes.end()) {
                return *it;
            }
            else {
                return prime_sizes.back();
            }
        }
        static size_t division_hash(size_t pre_index, size_t m) {
            return pre_index % m;
        }

        static size_t multiple_hash(size_t pre_index, size_t m) {
            auto a = (std::sqrt(5) - 1) / 2;
            return std::floor(std::fmod(static_cast<double>(pre_index) * a, 1.0) * static_cast<double>(m));
        }
    public:
        hash_table(): max_load_factor_(1), buckets_(get_next_prime(0)) {}
        size_t bucket_count() { return buckets_.size(); }
        size_t size() {
            return std::accumulate(buckets_.begin(), buckets_.end(), size_t{0},
            [](auto current, auto next) {
                return current + std::distance(next.begin(), next.end());
            });
        }
        void insert(ItemType item) {
            // Verificar el load_factor vs max_load_factor
            // Si el load_factor > max_load_factor realizar un rehash

            // Sino
            auto pre_index = pre_hash_fun_(item.first);
            auto index = multiple_hash(pre_index, bucket_count());
            auto it = std::find_if(buckets_[index].begin(), buckets_[index].end(),
                [key=item.first](auto item) {
                    return KeyEqualType()(key, item.first);
                });
            if (it == buckets_[index].end()) {
                buckets_[index].push_front(item);
            }
        }
    };

}

#endif //PROG3_2024_2_HASH_TABLES_HASH_TABLE_H
