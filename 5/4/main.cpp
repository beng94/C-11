#include <vector>
#include <string>
#include <iostream>
#include <memory>

class Node
{
    private:
        std::vector<std::shared_ptr<Node>> children;

    protected:
        std::string tag;

    public:
        Node(std::string str) : tag{str} {}

        void add_child (Node* a)
        {
            this->children.push_back(a);
        }

        void print()
        {
            std::cout << "<" + tag + ">";

            for(auto node: children)
                node->print();

            std::cout << "</" + tag + ">";
        }
};

class Body : public Node
{
    public:
        Body () : Node{"body"} {}
};

class Paragraph : public Node
{
    public:
        Paragraph () : Node{"p"} {}
};

class UnorderedList : public Node
{
    public:
        UnorderedList () : Node{"ul"} {}
};

class ListItem : public Node
{
    public:
        ListItem () : Node{"li"} {}
};

int main()
{
    Body* b = new Body();
    Paragraph* p1 = new Paragraph();
    UnorderedList* ul = new UnorderedList();
    Paragraph* p2 = new Paragraph();
    ListItem* l1 = new ListItem();
    ListItem* l2 = new ListItem();

    b->add_child(p1);
    b->add_child(ul);
    b->add_child(p2);
    ul->add_child(l1);
    ul->add_child(l2);

    b->print();

    return 0;
}
