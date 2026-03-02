#include <memory>
#include <iostream>
#include <stack>

struct node
{
    int value;
    std::unique_ptr<node> left;
    std::unique_ptr<node> right;

    node(int v) : value(v) {}
};

using node_ptr = std::unique_ptr<node>;

class binary_tree
{
public:

    void insert(int value);
    node* search(int value) const;
    void print_in_order() const;
    void print_in_order_iterative() const;

private:
    void insert(node_ptr& leaf, int value);
    node* search(const node_ptr& leaf, int value) const;
    void print_in_order(const node_ptr& leaf) const;

    node_ptr root;
};


void binary_tree::insert(node_ptr& leaf, int value)
{
    if (!leaf)
    {
        leaf = std::make_unique<node>(value);
        return;
    }

    if (value < leaf->value)
        insert(leaf->left, value);
    else 
        insert(leaf->right, value);
}


void binary_tree::insert(int value)
{
    insert(root, value);
}

node* binary_tree::search(const node_ptr& leaf, int value) const
{
    if (!leaf)
        return nullptr;
    if (value == leaf->value)
        return leaf.get();
    if (value < leaf->value)
        return search(leaf->left, value);
    else
        return search(leaf->right, value);
}

node* binary_tree::search(int value) const
{
    return search(root, value);
}

void binary_tree::print_in_order() const
{
    print_in_order(root);
    std::cout << "\n";
}

void binary_tree::print_in_order(const std::unique_ptr<node>& leaf) const
{
    if (!leaf)
        return;

    print_in_order(leaf->left);
    std::cout << leaf->value << " ";
    print_in_order(leaf->right);
}


void binary_tree::print_in_order_iterative() const
{
    std::stack<node*> s;
    node* current = root.get();

    while (current || !s.empty())
    {
        while (current)
        {
            s.push(current);
            current = current->left.get();
        }

        current = s.top();
        s.pop();

        std::cout << current->value << " ";

        current = current->right.get();
    }

    std::cout << "\n";
}

int main()
{
    binary_tree bt;

    bt.insert(10);
    bt.insert(5);
    bt.insert(15);
    bt.insert(3);
    bt.insert(7);
    bt.insert(12);
    bt.insert(20);

    int value_to_find = 7;

    node* result = bt.search(value_to_find);

    if (result)
        std::cout << "Found: " << result->value << "\n";
    else
        std::cout << "Not found\n";

    std::cout << "In-order recursive: ";
    bt.print_in_order();

    std::cout << "In-order iterative: ";
    bt.print_in_order_iterative();

    return 0;
}