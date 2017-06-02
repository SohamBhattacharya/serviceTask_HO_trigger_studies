# include <iostream>


int main()
{
    int *a;
    int *b;
    int *c = 0;
    
    a = (int*) malloc(sizeof(int));
    b = (int*) malloc(sizeof(int));
    c = (int*) malloc(sizeof(int));
    
    *a = 5;
    *b = 10;
    
    c = a;
    
    std::cout << *a << "\n";
    std::cout << *b << "\n";
    std::cout << *c << "\n";
    std::cout << "\n";
    
    c = b;
    *c = 15;
    //delete c;
    std::cout << *a << "\n";
    std::cout << *b << "\n";
    std::cout << *c << "\n";
    std::cout << "\n";
    
    return 0;
}
