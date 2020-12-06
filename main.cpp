#include <iostream>
#include <iterator>
#include <algorithm>
#include <memory>
#include <cmath>

using namespace std;

typedef double TP;

const int VECTOR_EXTRA_SIZE = 5;

template <typename T>
struct Figure
{
private:
    int oir;
};

template <typename T>
struct Triangle : public Figure<T>
{
private:
    bool MakeTr(TP x, TP y, TP x1, TP y1)
    {
        double angle = 3.14 / 180.0 * (360 / 3);
        for (int i = 0; i < 3; i++)
        {
            this->a[i].first = x;
            this->a[i].second = y;
            T nextX = ((x1 - x) * cos(angle) + (y1 - y) * -sin(angle)) + x1;
            T nextY = ((x1 - x) * sin(angle) + (y1 - y) * cos(angle)) + y1;
            x = x1;
            y = y1;
            x1 = nextX;
            y1 = nextY;
        }
    }

public:
    int count = 3;
    std::pair<T, T> a[3];

    Triangle()
    {
        this->MakeTr(0, 0, 1, 1);
    }
    Triangle(T x, T y, T x1, T y1)
    {
        this->MakeTr(x, y, x1, y1);
    }

    Triangle(Triangle<T> &tr)
    {
        this->a[0] = tr.a[0];
        this->a[1] = tr.a[1];
        this->a[2] = tr.a[2];
    }

    void Print()
    {
        for (int i = 0; i < 3; i++)
        {
            cout << "Вершина " << i + 1 << " x = " << this->a[i].first << " y = " << this->a[i].second << endl;
        }
    }

    double Square()
    {
        double s, a, h;
        a = sqrt((double)((this->a[0].first - this->a[1].first) * (this->a[0].first - this->a[1].first) + (this->a[0].second - this->a[1].second) * (this->a[0].second - this->a[1].second)));
        //a = sqrt((x1-x2)^2+(y1-y2)^2)
        h = a * sin(3.14 / 3);
        s = (a * h) / 2;
        return s;
    }

    void operator=(Triangle<TP> tr)
    {
        for (int i = 0; i < 3; i++)
        {
            this->a[i].first = tr.a[i].first;
            this->a[i].second = tr.a[i].second;
        }
    }

    ~Triangle() {}
};

template <class T>
class vector
{
public:
    int size;
    int capacity;
    T *data;

    vector()
    {
        this->size = 0;
        this->capacity = 3;
        this->data = new T[3];
    }

    vector(const vector<T> &v)
    {
        this->size = v.size;
        this->capacity = v.capacity;

        this->data = new T[v.capacity];
        for (int i = 0; i < this->size; i++)
        {
            this->data[i] = v.data[i];
        }
    }

    vector(int x)
    {
        this->size = 0;
        this->capacity = x;

        this->data = new T[x];
    }

    void PushEnd(T x)
    {
        if (this->size >= this->capacity)
        {

            int oldcap = this->capacity;
            this->capacity += VECTOR_EXTRA_SIZE;

            T *buf = new T[this->capacity];

            for (int i = 0; i < oldcap; i++)
            {
                buf[i] = this->data[i];
            }

            delete[] this->data;

            this->data = buf;

            buf = 0;
        }

        this->data[this->size] = x;

        this->size++;
    }

    void PopEnd()
    {
        if (this->size <= 0)
        {
            printf("Vector is empty.\n");
        }
        else
        {

            this->size--;
        }
    }

    void Erase(int i)
    {
        if (this->size <= 0)
        {
            printf("Vector is empty.\n");
        }
        else
        {
            if ((i < this->size) && (i >= 0))
            {
                this->size--;
                for (i; i < this->size; i++)
                {
                    //if(i != )
                    this->data[i] = this->data[i + 1];
                }
            }
            else
            {
                printf("В векторе нет элемента под индексом %d\n", i);
            }
        }
    }

    void insert(int i, T tr)
    {
        if ((i <= this->size) && (i >= 0))
        {
            this->PushEnd(tr);
            for (int j = this->size - 1; j > i; j--)
            {
                this->data[j].Print();
                this->data[j] = this->data[j - 1];
            }
            this->data[i] = tr;
        }
    }

    class iterator
    {
    public:
        int index = -1;
        vector<T> *vect;
        //std::iterator_traits<vector<T>::iterator> difference_type = int;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using iterator_category = std::forward_iterator_tag;
        std::shared_ptr<T> ptr;

        iterator()
        {
            index = 0;
        }

        iterator(const iterator &it)
        {
            this->vect = it.vect;
            this->ptr = it.ptr;
            this->index = it.index;
        }

        iterator(int ind, vector<T> *vect)
        {
            this->ptr = std::make_shared<T>((vect->data[ind]));
            this->index = ind;
            this->vect = vect;
        }

        iterator operator++()
        {
            //cout<<this<<" "<<this->index<<" "<<this->vect->size<<endl;
            if ((this->index + 1) > this->vect->size)
            {
                //printf("Iterator cannot be incremented past the end of range.%d %d\n", this->index, this->vect->size);
                throw std::out_of_range("Iterator cannot be incremented past the end of range.");
                return *this;
            }
            this->index++;
            this->ptr = std::make_shared<T>(this->vect->data[this->index]);
            
            return *this;
        }

        iterator &operator++(int)
        {
            if ((this->index + 1) > (this->vect->size))
            {
                //printf("Iterator cannot be incremented past the end of range.\n");
                throw std::out_of_range("Iterator cannot be incremented past the end of range.");
                return *this;
            }
            this->index++;
            this->ptr = std::make_shared<T>(this->vect->data[this->index]);
            return *this;
        }

        iterator operator=(iterator x)
        {
            //printf("=\n");
            this->ptr = x.ptr;
            return *this;
        }

        bool operator!=(const iterator &x)
        {//printf("!=\n");
            if (index != x.index)
                return true;
            //printf("false\n ");
            /* if(ptr != x.ptr) return true;
            printf("\t !=\n "); */
            return false;
        }

        bool operator>=(iterator x)
        {
            return this->ptr >= x.ptr;
        }

        int operator-(iterator x)
        {
            //printf("-\n");
            return this->index - x.index;
        }

        bool operator==(const iterator &x)
        {
            //printf("\t ==\n ");
            if (index == x.index)
                return true;
            if (ptr == x.ptr)
                return true;
            return false;
        }
        /*         bool operator==(iterator x){
            return this->ptr == x.ptr;
        } */

        /* bool operator>(iterator x){
            return this->ptr > x.ptr;
        }

        bool operator<(iterator x){
            return this->ptr < x.ptr;
        } */

        T operator*()
        {
            return *(this->ptr);
        }

        T *operator->()
        {
            return this->ptr;
        }

        ~iterator() {}
    };

    /* struct iterator {
    using value_type = T;
    using difference_type = int;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    using size_type = std::size_t;

    bool compatible(self_type const &other) const {
        return container == other.container;
    }

    iterator(value_type *ptr, container_type *container, size_type index) : container(container), index(index) {
        this->ptr = ptr;
    }

    iterator() = default;

    iterator(self_type const &o) = default;

    iterator &operator=(self_type const &o) = default;

    ~iterator() = default;

    self_type &operator++() {
        if (++index > container->size()) {
            throw std::out_of_range("Iterator cannot be incremented past the end of range.");
        }
        return *this;
    }

    self_type operator++(vector<T>::iterator it) {
        self_type tmp = *this;
        ++*this;
        return tmp;
    }

    bool operator==(self_type const &other) const {
        assert(compatible(other));
        return index == other.index;
    }

    bool operator!=(self_type const &other) const {
        return !(*this == other);
    }

    reference operator*() const {
        if (ptr == nullptr) {
            throw std::bad_function_call();
        }
        return *(ptr + index);
    }

reference operator->() const {
        if (ptr == nullptr) {
            throw std::bad_function_call();
        }
        return *(ptr->get() + index);
    }

    value_type *ptr = nullptr;
    container_type *container = nullptr;
    size_type index = 0;

    }; */

    iterator begin()
    {
        vector<T>::iterator it(0, this);
        return it;
    }

    iterator end()
    {
        vector<T>::iterator it(this->size, this);
        return it;
    }

    void Printing()
    {
        printf(">>>>>>>>\n");
        for (int i = 0; i < this->size; i++)
        {
            cout << this->data[i] << " ";
        }
        cout << endl;
        printf(">>>>>>>>size %d | cap %d\n", this->size, this->capacity);
    }

    void Show()
    {
        printf(">>>>>>>>\n");
        for (int i = 0; i < this->capacity; i++)
        {
            cout << this->data[i] << " ";
        }
        cout << endl;
        printf(">>>>>>>>size %d | cap %d\n", this->size, this->capacity);
    }

    ~vector()
    {
        this->size = 0;
        this->capacity = 0;
        delete[] this->data;
    }

    T operator[](int i)
    {
        return this->data[i];
    }

    T *operator++(int x)
    {
        return this->data[x + 1];
    }

    T *operator--(int x)
    {
        return this->data[x - 1];
    }

    void operator=(vector<T> vec)
    {
        for (int i = 0; i < this->size; i++)
        {
            this->data[i] = vec.data[i];
        }
    }
};

void help()
{
    printf("Для выполнения операции введите соответствующую цифру:\n ");
    printf("\t 1 - Добавить фигуру\n ");
    printf("\t 2 - Удалить фигуру\n ");
    printf("\t 3 - Вывести все фигуры на экран\n ");
    printf("\t 4 - Вывести все фигуры, у которых площадь меньше, заданной, на экран\n ");
    printf("\t 0 - Выйти из программы\n ");
}

/* void help()
void help()
{
    printf("Для выполнения операции введите соответствующую цифру:\n ");
    printf("\t 1 - Добавить фигуру в хранилище\n ");
    printf("\t 2 - Удалить последнюю добавленную фигуру из хранилища\n ");
    printf("\t 3 - Вывести Геом.Центр. для всех фигур\n ");
    printf("\t 4 - Вывести Координаты всех вершин для всех фигур\n ");
    printf("\t 5 - Вывести площади всех фигур\n ");
    printf("\t 6 - Вычислить общую площадь всех фигур\n ");
    printf("\t 7 - Удалить фигуру по индексу\n ");
    printf("\t 8 - Закрыть программу\n ");
    printf("\t 9 - Показать вектор\n ");
    printf("\t 0 - Вывести справку\n ");
} */

TP Print(vector<Triangle<TP>> vec)
{
    int j = 1;
    cout << "Фигура номер " << j << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "x " << vec.data[j].a[i].first << endl;
        cout << "y " << vec.data[j].a[i].second << endl;
        return 0;
    }
}

int main()
{

    int i = 1;
    char enter = -1;
    TP xl, yl, xr, yr;
    int c;
    vector<Triangle<TP>> vec;
    help();
    std::cin >> enter;
    while (isdigit(enter))
    {
        switch (enter - 48)
        {

        case 1:
        {
            cout << "Введите координаты двух вершин вашей фигуры в направлении против часовой стрелки." << endl;
            std::cin >> xl >> yl >> xr >> yr;
            //Triangle<TP> tr(xl, yl, xr, yr);
            Triangle<TP> *ptr = new Triangle<TP>(xl, yl, xr, yr);
            //*ptr = tr;
            vec.insert(vec.size, *ptr);
            //vec.PushEnd(*ptr);
            ptr = NULL;
            delete ptr;
            cout << "Элемент вставлен." << endl;
            break;
        }
        case 2:
        {
            cout << "Введите номер удаляемой фигуры " << endl;
            int numb;
            std::cin >> numb;
            vec.Erase(numb - 1);
            cout << "Фигура удалена\n Текущий размер хранилища :Size = " << vec.size << endl;
            break;
        }
        case 3:
        { //вывод всех фигур
            for_each(vec.begin(), vec.end(), [&](Triangle<TP> &&tr) {
                printf("Фигура №%d\n", i);
                i++;
                tr.Print();
            });
            i = 1;
            
            break;
        }
        case 4:
        {
            TP square = 0;
            printf("Введите площадь больше площадей только тех фигур , которые надо вывести\n");
            std::cin >> square;
            //вывод если прлощадь меньше заданной
            int r = std::count_if(vec.begin(), vec.end(), [&](Triangle<TP> &&tr) { return tr.Square() < square; });
            cout << r << endl;
            break;
        }
        case 0:
        {
            cout << "Выход из программы..." << endl;
            return 0;
        }
        default:
        {
            help();
            break;
        }
        }
        enter = 0;
        std::cin >> enter;
    }
    cout << "Похоже введена буква, ну в другой раз не промахнётесь по клавиатуре ;-) \n\n"
         << endl;
    return 0;
}