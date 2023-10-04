#include <string>
#include <algorithm>
#include <iterator>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

template <typename T> 
class myVector
{
    private:
        std::size_t my_size = 0;
        unsigned int capacity = 1;
        T* arr;

    public:
        myVector() : my_size(0), capacity(1), arr(new T[1])//works
        {
        }

        myVector(unsigned int new_cap) : my_size(0), capacity(new_cap), arr(new T[capacity])//maybe
        {
        }

        myVector(unsigned int new_cap, T content) : my_size(new_cap), capacity(new_cap), arr(new T[capacity])//works
        {
            std::fill_n(arr, new_cap, content);
        }

        myVector(myVector &t) : my_size(t.my_size), capacity(t.capacity)//copy cstr
        {
            arr = new T[t.my_size];
            std::copy(t.arr, t.arr + t.my_size, arr);
        }

        myVector(myVector&& t) : my_size(t.my_size), capacity(t.capacity), arr(t.arr)//move cstr
        {
            t.my_size = 0;
            t.capacity = 0;
            t.arr = nullptr;
        }

        myVector(std::initializer_list<T> list)
        {
            my_size = list.size();
            capacity = my_size;
            arr = new T[my_size];
            for(int i = 0; i < my_size; i++)
            {
                *(arr + i) = *(list.begin() + i);
            }
        }

        myVector& operator=(std::initializer_list<T> list)
        {
            my_size = list.size();
            capacity = my_size;
            delete[] arr;
            arr = new T[my_size];
            for(int i = 0; i < my_size; i++)
            {
                *(arr + i) = *(list.begin() + i);
            }

            return *this;
        }

        myVector& operator=(myVector& t) noexcept//copy assign
        {
            T* local_arr = new T[t.my_size];
            std::copy(t.arr, t.arr + t.my_size, local_arr);
            delete[] arr;
            arr = local_arr;
            my_size = t.my_size;
            capacity = t.capacity;
            
            return *this;
        }

        myVector& operator=(myVector&& t) noexcept
        {
            T* local_arr = new T[t.my_size];
            std::copy(t.arr, t.arr + t.my_size, local_arr);
            delete[] arr;
            arr = local_arr;
            my_size = t.my_size;
            capacity = t.capacity;

            t.arr = nullptr;
            t.my_size = 0;
            t.capacity = 0;

            return *this;
        }

        ~ myVector()//maybe
        {
            delete[] arr;
        }

        void reserve(unsigned int extra)//maybe
        {
            T* temp = new T[my_size + extra];
            std::copy(arr, arr + my_size, temp);
            delete[] arr;
            arr = temp;
            temp = NULL;
        }

        void push_back(T const & value)//works
        {
            if(my_size >= capacity)
            {
                capacity += (capacity + 1) / 2;
                T* temp = new T[capacity];
                std::copy(arr, arr + my_size, temp);
                delete[] arr;
                arr = temp;
                temp = NULL;
            }
            arr[my_size++] = value;
        }

        int size()//works
        {
            return my_size;
        }

        T front()//works
        {
            return arr[0];
        }

        T back()//works
        {
            return arr[my_size - 1];
        }
 
        T* begin()//should work
        {
            return arr;
        }

        T* end()//should work
        {
            return arr + size();
        }

        T& operator[](unsigned int index)//works
        {
            return arr[index];
        }

        void pop_back()//works
        {
            my_size--;
        }


};

int main()
{
    myVector<int> poggers(5, 78);
    myVector<int> gaming = poggers;
    gaming = {1, 2, 3};
    myVector<int> yippie = {1, 2, 3};
    poggers.push_back(100);
    poggers.push_back(20);
    std::cout << poggers.size() << std::endl;
    std::cout << poggers[0] << std::endl << poggers[1] << std::endl;
    std::cout << poggers.back() << std::endl;
    poggers.pop_back();
    for(int i = 0; i < yippie.size(); i++)
    {
        std::cout << yippie[i] << std::endl;
    }
    poggers.reserve(10);
    std::sort(poggers.begin(), poggers.end());

}
