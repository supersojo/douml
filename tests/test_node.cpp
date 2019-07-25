#include "node.h"
#include "point.h"
#include <iostream>
class MyVisitor : public douml::NodeVisitor {
public:
    void Visit(douml::Node* n)
    {
        std::cout<<"MyVisitor:"<<n->GetLocation().ToString()<<std::endl;
    }
};
int main(int argc, char* args[]) {
    douml::Node* n1 = new douml::Node;
    n1->SetLocation(douml::Point(10,10));
    douml::Node* n2 = new douml::Node;
    n2->SetLocation(douml::Point(23,46));
    douml::Node* n3 = new douml::Node;
    n3->SetLocation(douml::Point(100,100));
    n1->SetParent(n2);
    n2->SetParent(n3);
    std::cout<<n1->GetLocationOnGraph().ToString()<<std::endl;
    std::cout<<n2->GetLocationOnGraph().ToString()<<std::endl;
    MyVisitor v;
    n3->VisitChildren(&v);
    std::cout<<n1->HasParent()<<std::endl;
    std::cout<<n2->HasParent()<<std::endl;
    std::cout<<n3->HasParent()<<std::endl;
    return 0;
}