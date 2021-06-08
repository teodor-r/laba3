#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

template<typename T>
class tree_elem{
public:
    T m_data;
    tree_elem* m_left;
    tree_elem* m_right;

    tree_elem(T key){
        m_data = key;
        m_left = NULL;
        m_right = NULL;
    }
    tree_elem(T key,tree_elem<T>* left,tree_elem<T>* right){
        m_data = key;
        m_left = left;
        m_right = right;
    }
};

template<typename T>
void sqr(tree_elem<T>* curr){
    curr->m_data = curr->m_data * curr->m_data;
}

template<typename T>
bool is_more_than_12(tree_elem<T>* curr){
    if(curr->m_data >= 12)
        return true;
    return false;
}

template<typename T>
T sum(tree_elem<T>* curr,T curr_sum){
    return curr_sum + curr->m_data;
}

template<typename T>
class binary_tree{
private:

    tree_elem<T>* m_root;

    int size;

    void Map_help(void(*func)(tree_elem<T>*),tree_elem<T>* curr){
        if(curr){
            Map_help(func ,curr->m_left);
            func(curr);
            Map_help(func,curr->m_right);
        }
    }

    void Where_help(bool(*func)(tree_elem<T>*),tree_elem<T>* curr){
        if(curr){
            Where_help(func,curr->m_left);

            if(func(curr)){
                delete_elem(curr->m_data);
            }

            Where_help(func,curr->m_right);
        }
    }

    void Reduce_help(T(*func)(tree_elem<T>*,T),tree_elem<T>* curr,T& curr_sum){
        if(curr){
            Reduce_help(func,curr->m_left,curr_sum);
            curr_sum = func(curr,curr_sum);
            Reduce_help(func,curr->m_right,curr_sum);
        }
    }

    void upgrade_sub_tree(binary_tree<T>* result,tree_elem<T>* curr){
        if(curr){
            upgrade_sub_tree(result,curr->m_left);
            result->insert(curr->m_data);
            upgrade_sub_tree(result,curr->m_right);
        }
    }

    void tree_to_string_help(tree_elem<T>* curr,std::vector<std::string>& curr_str){
        if(curr){
            tree_to_string_help(curr->m_left,curr_str);
            curr_str.push_back(std::to_string(curr->m_data));
            tree_to_string_help(curr->m_right,curr_str);
        }
    }

    void print_tree(tree_elem<T>* curr){
        if(curr){
            print_tree(curr->m_left);
            std::cout << curr->m_data << " ";
            print_tree(curr->m_right);
        }
    }
public:

    binary_tree(){
        m_root = nullptr;
        size = 0;
    }

    binary_tree(int key){
        m_root = new tree_elem<T>(key);
        size = 1;
    }
    ~binary_tree(){
        delete_tree(m_root);
    }
    int get_size(){return size;}

    binary_tree<T>* get_sub_tree(T key){

        tree_elem<T>* curr = m_root;
        while(curr && curr->m_data!=key)
            if(curr->m_data < key)
                curr = curr->m_right;
            else
                curr = curr->m_left;
        binary_tree<T>* result = new binary_tree<T>(curr->m_data);
        upgrade_sub_tree(result,curr);

        return result;
    }

    void print(){
        print_tree(m_root);
        std::cout << std::endl;
    }


    void delete_tree(tree_elem<T>* curr){
        if(curr){
            delete_tree(curr->m_left);
            delete[] curr;
            delete_tree(curr->m_right);
        }
    }


    bool find(int key){

        tree_elem<T>* curr = m_root;
        while(curr && curr->m_data != key){
            if(curr->m_data > key)
                curr = curr->m_left;
            else
                curr = curr->m_right;
        }
        return (bool)curr;
    }


    void insert(int key){
        if(m_root == nullptr){
            m_root = new tree_elem<T>(key);
            size = 1;
        }else{
            tree_elem<T>* curr = m_root;
            while(curr && curr->m_data != key){
                if(curr->m_data > key){
                    if(curr->m_left)
                        curr = curr->m_left;
                    else{
                        curr->m_left = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }
                else{
                    if(curr->m_right)
                        curr = curr->m_right;
                    else{
                        curr->m_right = new tree_elem<T>(key);
                        size++;
                        return;
                    }
                }
            }
        }
    }

    void delete_elem(T key){
        tree_elem<T>* curr = m_root;
        tree_elem<T>* prev = nullptr;

        while(curr && curr->m_data != key){
            prev = curr;
            if(curr->m_data > key){
                curr = curr->m_left;
            }
            else
                curr = curr->m_right;
        }
        if(!curr)
            return;

        if(prev != nullptr){
            if(prev->m_right == curr){
                if(curr->m_right == nullptr && curr->m_left == nullptr){
                    prev->m_right = nullptr;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->m_left == nullptr){
                    prev->m_right = curr->m_right;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->m_right == nullptr){
                    prev->m_right = curr->m_left;
                    delete[] curr;
                    size--;
                    return;
                }
            }

            if(prev->m_left == curr){
                if(curr->m_right == nullptr && curr->m_left == nullptr){
                    prev->m_left = nullptr;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->m_left == nullptr){
                    prev->m_left = curr->m_right;
                    delete[] curr;
                    size--;
                    return;
                }
                if(curr->m_right == nullptr){
                    prev->m_left = curr->m_left;
                    delete[] curr;
                    size--;
                    return;
                }
            }



            tree_elem<T>* tmp = curr->m_right;
            while(tmp->m_left)
                tmp = tmp->m_left;

            T minimum = tmp->m_data;


            if(prev->m_left == curr){
                delete_elem(tmp->m_data);
                prev->m_left = new tree_elem<T>(minimum,curr->m_left,curr->m_right);
                delete[] curr;
                size--;
                return;
            }
            if(prev->m_right == curr){
                delete_elem(tmp->m_data);
                prev->m_right = new tree_elem<T>(minimum,curr->m_left,curr->m_right);
                delete[] curr;
                size--;
                return;
            }
        }

    }



    //map,where,reduce
    void Map(void(*func)(tree_elem<T>*)){
        tree_elem<T>* curr = m_root;
        Map_help(func,curr);
    }

    void Where(bool(*func)(tree_elem<T>*)){
        tree_elem<T>* curr = m_root;
        Where_help(func,curr);
    }

    T Reduce(T(*func)(tree_elem<T>*,T)){
        tree_elem<T>* curr = m_root;
        T curr_sum = 0;
        Reduce_help(func,curr,curr_sum);
        return curr_sum;
    }

    std::string tree_to_string(){

        tree_elem<T>* curr = m_root;
        std::vector<std::string> result;
        tree_to_string_help(curr,result);

        std::string result_str = "";
        for (int i = 0; i < result.size(); ++i) {
            result_str += result[i] + " ";
        }
        return result_str;
    }


};


int main(){

    int n;
    std::cout << "Enter count of values in your first tree :\n";

    if(!(std::cin >> n)){
        std::cout << "Invalid input\n";
        return -1;
    }

    int* values = new int [n];
    int value;
    std::cout << "Enter "<< n <<" elements for your first tree :\n";

    for (int i = 0; i < n; ++i)
    {	if(std::cin >> value)
            values[i] = value;
        else{
            delete[] values;
            std::cout << "Invalid input\n";
            return -1;
        }
    }
    binary_tree<int> first;
    for (int i = 0; i < n; ++i)
    {
        first.insert(values[i]);
    }

    std::cout << "First tree :\n";
    first.print();
    //===========================================================//
    std::cout << "Enter count of values in your second tree :\n";

    if(!(std::cin >> n)){
        delete[] values;
        std::cout << "Invalid input\n";
        return -1;
    }

    int* another_values = new int [n];
    std::cout << "Enter "<< n <<" elements for your second tree :\n";
    for (int i = 0; i < n; ++i)
    {	if(std::cin >> value)
            another_values[i] = value;
        else{
            delete[] values;
            delete[] another_values;
            std::cout << "Invalid input\n";
            return -1;
        }
    }
    binary_tree<int> second;
    for (int i = 0; i < n; ++i)
    {
        second.insert(another_values[i]);
    }
    std::cout << "Second tree :\n";
    second.print();

    first.Map(sqr);
    std::cout << "First tree after squaring each element :\n";
    first.print();

    second.Where(is_more_than_12);
    std::cout << "All items less than 12 that belong to the second tree :\n";
    second.print();

    std::cout << "The sum of the elements of the modified first tree = " << first.Reduce(sum) << std::endl;


    delete[] values;
    delete[] another_values;

    int flag;
    std::cout << "Start stress test Y/N ? (1/2) \n";
    std::cin >> flag;
    if(flag == 1){
        std::cout << "For the range 10,000 - 100,000, press 1\n"
                     "For the range 10,000,000 - 100,000,000 press 2\n";
        std::cin >> flag;
        if(flag == 1){
            std::cout << "||============================================ 10 000 - 100 000 elements ===========================================||\n";
            int size;

            size = 10000;
            unsigned int start_time =  clock(); // начальное время
            binary_tree<int> first1;
            for (int i = 0; i < size; ++i)
            {
                first1.insert(rand()%10);
            }
            first1.Map(sqr);
            unsigned int end_time = clock(); // конечное время
            unsigned int search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 20000;
            start_time =  clock(); // начальное время
            binary_tree<int> first2;
            for (int i = 0; i < size; ++i)
            {
                first2.insert(rand()%10);
            }
            first2.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 30000;
            start_time =  clock(); // начальное время
            binary_tree<int> first3;
            for (int i = 0; i < size; ++i)
            {
                first3.insert(rand()%10);
            }
            first3.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 40000;
            start_time =  clock(); // начальное время
            binary_tree<int> first4;
            for (int i = 0; i < size; ++i)
            {
                first4.insert(rand()%10);
            }
            first4.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time<< " mls" << std::endl;

            size = 50000;
            start_time =  clock(); // начальное время
            binary_tree<int> first5;
            for (int i = 0; i < size; ++i)
            {
                first5.insert(rand()%10);
            }
            first5.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 60000;
            start_time =  clock(); // начальное время
            binary_tree<int> first6;
            for (int i = 0; i < size; ++i)
            {
                first6.insert(rand()%10);
            }
            first6.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 70000;
            start_time =  clock(); // начальное время
            binary_tree<int> first7;
            for (int i = 0; i < size; ++i)
            {
                first7.insert(rand()%10);
            }
            first7.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 80000;
            start_time =  clock(); // начальное время
            binary_tree<int> first8;
            for (int i = 0; i < size; ++i)
            {
                first8.insert(rand()%10);
            }
            first8.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 90000;
            start_time =  clock(); // начальное время
            binary_tree<int> first9;
            for (int i = 0; i < size; ++i)
            {
                first9.insert(rand()%10);
            }
            first9.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            size = 100000;
            start_time =  clock(); // начальное время
            binary_tree<int> first10;
            for (int i = 0; i < size; ++i)
            {
                first10.insert(rand()%10);
            }
            first10.Map(sqr);
            end_time = clock(); // конечное время
            search_time = end_time - start_time; // искомое время
            std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

            std::cout << "||==================================================================================================================||\n\n";
        }
        else{
            if(flag == 2){
                std::cout << "||==================================== 10 000 000 - 100 000 000 elements =============================================||\n";
                int size;

                size = 10000000;
                unsigned int start_time =  clock(); // начальное время
                binary_tree<int> first1;
                for (int i = 0; i < size; ++i)
                {
                    first1.insert(rand()%10);
                }
                first1.Map(sqr);
                unsigned int end_time = clock(); // конечное время
                unsigned int search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 20000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first2;
                for (int i = 0; i < size; ++i)
                {
                    first2.insert(rand()%10);
                }
                first2.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 30000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first3;
                for (int i = 0; i < size; ++i)
                {
                    first3.insert(rand()%10);
                }
                first3.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 40000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first4;
                for (int i = 0; i < size; ++i)
                {
                    first4.insert(rand()%10);
                }
                first4.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time<< " mls" << std::endl;

                size = 50000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first5;
                for (int i = 0; i < size; ++i)
                {
                    first5.insert(rand()%10);
                }
                first5.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 60000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first6;
                for (int i = 0; i < size; ++i)
                {
                    first6.insert(rand()%10);
                }
                first6.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 70000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first7;
                for (int i = 0; i < size; ++i)
                {
                    first7.insert(rand()%10);
                }
                first7.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 80000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first8;
                for (int i = 0; i < size; ++i)
                {
                    first8.insert(rand()%10);
                }
                first8.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 90000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first9;
                for (int i = 0; i < size; ++i)
                {
                    first9.insert(rand()%10);
                }
                first9.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                size = 100000000;
                start_time =  clock(); // начальное время
                binary_tree<int> first10;
                for (int i = 0; i < size; ++i)
                {
                    first10.insert(rand()%10);
                }
                first10.Map(sqr);
                end_time = clock(); // конечное время
                search_time = end_time - start_time; // искомое время
                std::cout << "Execution time for " << size << " elements is " << search_time << " mls" << std::endl;

                std::cout << "||==================================================================================================================||\n\n";
            }
        }

    }


    return 0;
}