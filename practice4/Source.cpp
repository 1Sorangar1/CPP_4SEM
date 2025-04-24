#include <iostream>
#include <memory>
#include <string>
#include <sstream>

class Node {
private:
    std::string data;
    std::shared_ptr<Node> next;

public:
    Node(const std::string& element) : data(element), next(nullptr) {}
    ~Node() = default;

    const std::string& getData() const {
        return data;
    }
    void setData(const std::string& element) {
        data = element;
    }
    std::shared_ptr<Node> getNext() const {
        return next;
    }
    void setNext(const std::shared_ptr<Node>& nextNode) {
        next = nextNode;
    }
};

class List {
private:
    std::shared_ptr<Node> head;

public:
    List() : head(nullptr) {}
    ~List() = default;
      
    template <typename T>
    std::string serialize(const T& value) {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    template <typename T>
    void insert(const T& element) {
        auto newNode = std::make_shared<Node>(serialize(element));
        newNode->setNext(head);
        head = newNode;
    }

    template <typename T>
    void pushback(const T& element) {
        auto newNode = std::make_shared<Node>(serialize(element));
        if (!head) {
            head = newNode;
        }
        else {
            auto current = head;
            while (current->getNext()) {
                current = current->getNext();
            }
            current->setNext(newNode);
        }
    }

    template <typename T>
    void deleteValue(const T& value) {
        std::string serialized_value = serialize(value);

        if (!head) {
            std::cerr << "empty list on input!" << std::endl;
            std::exit(1);
        }

        if (head->getData() == serialized_value) {
            head = head->getNext();
            return;
        }

        auto current = head;
        while (current->getNext() && current->getNext()->getData() != serialized_value) {
            current = current->getNext();
        }

        if (current->getNext()) {
            current->setNext(current->getNext()->getNext());
        }
        else {
            std::cerr << "Element not found" << std::endl;
            std::exit(1);
        }
    }


    void iterate(void (*func)(const std::string&)) const {
        auto current = head;
        while (current) {
            func(current->getData());
            current = current->getNext();
        }
    }
};

void printElement(const std::string& element) {
    std::cout << element << " ";
}

int main() {
    List list;
    list.insert(42);   
    list.insert(3.0);      
    list.pushback("wergbqerig");  
    list.deleteValue(42);

    list.iterate(printElement);
    std::cout << std::endl;

    return 0;
}
