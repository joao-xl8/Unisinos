#include <memory>

struct node
{
    int value;
    std::shared_ptr<node> left;
    std::shared_ptr<node> right;
};

class binary_tree 
{
public:
    binary_tree();
    ~binary_tree();

    void insert(int value);
    std::shared_ptr<node> search(int value);
    void remove();

private: 
    void remove_tree(std::shared_ptr<node> leaf);
    void insert_tree(std::shared_ptr<node> leaf, int value);
    std::shared_ptr<node> search_tree(std::shared_ptr<node> leaf, int value);

    std::shared_ptr<node> root;
};

binary_tree::binary_tree()
{
    root = NULL;
}

binary_tree::~binary_tree()
{
    remove_tree(root);
}

void binary_tree::remove_tree(std::shared_ptr<node> leaf)
{
    if (leaf != NULL)
    {
        remove_tree(leaf->left);
        remove_tree(leaf->right);
        delete leaf.get();
    }
    
}