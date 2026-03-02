#include <memory>
#include <iostream>

struct node {
  int x;
  std::shared_ptr<node> next;
};
 
int main()
{
    std::shared_ptr<node> root = std::make_shared<node>();     
    std::shared_ptr<node> conductor;  

    root->next = NULL;   
    root->x = 12;

    conductor = root; 

    while ( conductor != NULL ) {
        std::cout<< conductor->x << std::endl;
        conductor = conductor->next;
    }
}