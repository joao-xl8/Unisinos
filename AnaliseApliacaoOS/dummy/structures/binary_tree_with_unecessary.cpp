#include <memory>

struct node
{
    int value;
    std::shared_ptr<node> left;
    std::shared_ptr<node> right;
};

using node_ptr = std::shared_ptr<node>;

class binary_tree
{
public:
    binary_tree();
    ~binary_tree();

    void insert(int value);
    node_ptr search(int value);
    void destroy_tree();

private:
    void remove_leaf(node_ptr leaf);
    void insert(node_ptr leaf, int value);
    node_ptr search(node_ptr leaf, int value);

    node_ptr root;
};

binary_tree::binary_tree()
{
    root = nullptr;
}

binary_tree::~binary_tree()
{
    remove_leaf(root);
}

void binary_tree::remove_leaf(node_ptr leaf)
{
    if (leaf != nullptr)
    {
        remove_leaf(leaf->left);
        remove_leaf(leaf->right);
    }
}

void binary_tree::insert(node_ptr leaf, int value)
{
    if (value < leaf->value)
    {
        if (leaf->left != nullptr)
        {
            insert(leaf->left, value);
        }
        else
        {
            leaf->left = std::make_shared<node>();
            leaf->left->value = value;
            leaf->left->left = nullptr;
            leaf->left->right = nullptr;
        }
    }
    else if (value >= leaf->value)
    {
        if (leaf->right != nullptr)
        {
            insert(leaf->right, value);
        }
        else
        {
            leaf->right = std::make_shared<node>();
            leaf->right->value = value;
            leaf->right->left = nullptr;
            leaf->right->right = nullptr;
        }
    }
}

node_ptr binary_tree::search(node_ptr leaf, int value)
{
    if (leaf != nullptr)
    {
        if (value == leaf->value)
            return leaf;
        if (value < leaf->value)
            return search(leaf->left, value);
        else
            return search(leaf->right, value);
    }
    else
        return nullptr;
}

void binary_tree::insert(int value)
{
    if (root != nullptr)
    {
        insert(root, value);
    }
    else
    {
        root = std::make_shared<node>();
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
    }
}

node_ptr binary_tree::search(int value)
{
    return search(root, value);
}

void binary_tree::destroy_tree()
{
    remove_leaf(root);
}


int main()
{
    binary_tree bt;
    bt.insert(10);
    return 0;
}