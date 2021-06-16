#include <random>
#include <ctime>
#include <vector>
#include <iostream>
template <typename Comparable>
const Comparable& median3(std::vector<Comparable> & a, int left, int right){
    int mid = (left + right) / 2;
    if(a[left] > a[mid])
        std::swap(a[left], a[mid]);
    if(a[left] > a[right])
        std::swap(a[left], a[right]);
    if(a[mid] > a[right])
        std::swap(a[mid], a[right]);

    std::swap(a[mid], a[right-1]);
    return a[right-1];
}

template < typename Comparable>
void quickSort(std::vector<Comparable> &a, int left, int right){
    const int pivot = median3(a, left, right);
    int l = left, r = right-1;
    for(;;){
        while(a[++l] < pivot){}
        while(a[--r] > pivot){}
        if(l < r)
            std::swap(a[l], a[r]);
        else
            break;
    }
    std::swap(a[l], a[right-1]);

    quickSort(a, left, l-1);
    quickSort(a, l+1, right);
}

template <typename T>
T initContainer(int size)
{
    T contr(size);
    std::default_random_engine e(time(NULL));
    //generate random number between 0 and 1000
    std::uniform_int_distribution<int> u(0, 100);
    for(auto i=contr.begin(); i!=contr.end(); i++)
    {
        *i = u(e);
    }
    return contr;
}

template<typename T>
std::ostream& operator << (std::ostream& o, std::vector<T>& a){
    o << "[ ";
    for(auto & x : a){
        o <<  x << ' ';
    }
    o << "]";
    return o;
}


template <typename Comparable>
void quickSort2( std::vector<Comparable> & a, int left, int right)
{
        if(left >= right)
            return;

        if(left == right - 1){
            if(a[left] > a[right])
                std::swap(a[left], a[right]);
            return;
        }

        const Comparable &pivot = median3(a, left, right);
        printf("left: %d, right: %d, pivot: %d   ", left, right, pivot);
        /**begin partitioning**/
        int i = left, j = right - 1;

        for (;;) {
            //move i right, skipping over elements that are smaller than the pivot.
            while (a[++i] < pivot) {}
            //move j left, skipping over elements that are larger than the pivot.
            while (pivot < a[--j]) {}

            // When i and j have stopped, i is pointing at a large element
            // and j is pointing at a small element.
            // if i is to the left of j, those elements are swapped.
            if (i < j)
                std::swap(a[i], a[j]);
                // repeat the above process until i and j cross
            else
                break;
        }
        std::swap(a[i], a[right - 1]); // restore pivot
        std:: cout << a << std::endl;
        /**end partitioning**/
        quickSort2(a, left, i - 1); // sort smaller group
        quickSort2(a, i + 1, right); // sort larger group

}

int main(){
    std::vector<int> a = initContainer<std::vector<int>>(10);
    std::cout << a << std::endl;
    quickSort2(a, 0, a.size()-1);
    std::cout << a << std::endl;
    return 0;
}
