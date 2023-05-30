/* ---------------------------------------------------------------------
 * LPVL - Linear Algebra, Plotting and Visualisation Library
 * Copyright (C) 2023 whs31.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero Public License version 3 as
 * published by the Free Software Foundation.
 * http://www.gnu.org/licenses.
 *
 * github.com/whs31/lpvl
 * ---------------------------------------------------------------------- */

#pragma once
#include "LPVL/Global"
#include <vector>
#include <algorithm>

LPVL_UNIMPLEMENTED

template <typename T>
class LPVL_EXPORT List
{
    public:
        void add(T item);
        void addRange(List<T> collection);
        int binarySearch(T item);
        bool contains(T item);
        void clear();
        // find
        // findlast
        // findall
        int indexOf(T item);
        int lastIndexOf(T item);
        List<T> getRange(int index, int count);
        void insert(int index, T item);
        void insertRange(int index, List<T> collection);
        bool remove(T item);
        void removeAt(int index);
        void removeRange(int index, int count);
        // removeall
        void reverse();
        void reverse(int index, int count);
        void sort();
        T at(int index);
        // sort with compare
        int count() const;
        bool isEmpty() const;
        void resize(int size);
        int capacity() const;
        void reserve(int size);

        T &operator[](int i);
        const T &operator[](int i) const;

//        typedef typename Data::iterator iterator;
//        typedef typename Data::const_iterator const_iterator;
//        typedef std::reverse_iterator<iterator> reverse_iterator;
//        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
//        inline iterator begin() { detach(); return d->begin(); }
//        inline const_iterator begin() const noexcept { return d->constBegin(); }
//        inline const_iterator cbegin() const noexcept { return d->constBegin(); }
//        inline const_iterator constBegin() const noexcept { return d->constBegin(); }
//        inline iterator end() { detach(); return d->end(); }
//        inline const_iterator end() const noexcept { return d->constEnd(); }
//        inline const_iterator cend() const noexcept { return d->constEnd(); }
//        inline const_iterator constEnd() const noexcept { return d->constEnd(); }
//        reverse_iterator rbegin() { return reverse_iterator(end()); }
//        reverse_iterator rend() { return reverse_iterator(begin()); }
//        const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
//        const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
//        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }
//        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }
//        iterator insert(iterator before, int n, const T &x);
//        inline iterator insert(iterator before, const T &x) { return insert(before, 1, x); }
//        inline iterator insert(iterator before, T &&x);
//        iterator erase(iterator begin, iterator end);
//        inline iterator erase(iterator pos) { return erase(pos, pos+1); }

    private:
        std::vector<T> vec;
};
