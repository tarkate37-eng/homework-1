#pragma once

#include <iterator>
#include <functional>
#include <utility>

namespace detail {

    // Сортировка вставками для маленьких массивов (<= 16 элементов)
    template <typename It, typename Compare>
    void insertionSort(It first, It last, Compare comp) {
        if (first == last) return;
        for (auto cur = first + 1; cur != last; ++cur) {
            auto val = std::move(*cur);
            auto prev = cur;
            while (prev != first && comp(val, *(prev - 1))) {
                *prev = std::move(*(prev - 1));
                --prev;
            }
            *prev = std::move(val);
        }
    }

    // Выбор медианы из трех: первого, среднего и последнего элемента
    template <typename It, typename Compare>
    void medianOfThree(It a, It b, It c, Compare comp) {
        if (comp(*b, *a)) std::iter_swap(a, b);
        if (comp(*c, *b)) {
            std::iter_swap(b, c);
            if (comp(*b, *a)) std::iter_swap(a, b);
        }
    }

    // Быстрая сортировка с разбиением Хоара и устранением хвостовой рекурсии
    template <typename It, typename Compare>
    void quickSortInternal(It first, It last, Compare comp) {
        while (last - first > 16) {
            auto mid = first + (last - first) / 2;
            medianOfThree(first, mid, last - 1, comp);

            auto pivot_val = *mid;
            auto left = first;
            auto right = last - 1;

            while (true) {
                while (comp(*left, pivot_val)) ++left;
                while (comp(pivot_val, *right)) --right;

                if (left >= right) break;

                std::iter_swap(left, right);
                ++left;
                --right;
            }

            auto split = right + 1;
            // Рекурсивно вызываем для меньшей части, большую крутим в цикле
            if (split - first < last - split) {
                quickSortInternal(first, split, comp);
                first = split;
            }
            else {
                quickSortInternal(split, last, comp);
                last = split;
            }
        }
        insertionSort(first, last, comp);
    }

} // namespace detail

template <
    typename It,
    typename Compare = std::less<typename std::iterator_traits<It>::value_type>
>
void mySort(It first, It last, Compare comp = Compare{}) {
    if (first == last || first + 1 == last) return;
    detail::quickSortInternal(first, last, comp);
}