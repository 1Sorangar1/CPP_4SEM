#include <memory>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <cassert>
//
//
//template<typename T>
//class StackThreadStack {
//private:
//    struct node {
//        T data;
//        std::shared_ptr<node> next;
//
//        explicit node(T const& data_) : data(data_) {}
//    };
//
//    std::shared_ptr<node> head;
//    mutable std::mutex mut;
//    std::condition_variable data_cond;
//
//public:
//    StackThreadStack() : head(nullptr) {}
//
//    void push(T const& new_value) {
//        auto new_node = std::make_shared<node>(new_value);
//        {
//            std::lock_guard<std::mutex> lk(mut);
//            new_node->next = head;
//            head = new_node;
//        }
//        data_cond.notify_one();
//    }
//
//    std::shared_ptr<T> pop() {
//        std::lock_guard<std::mutex> lk(mut);
//        if (!head) {
//            return nullptr;
//        }
//        auto old_head = head;
//        head = old_head->next;
//        return std::make_shared<T>(old_head->data);
//    }
//
//    std::shared_ptr<T> top() const {
//        std::lock_guard<std::mutex> lk(mut);
//        if (!head) {
//            return std::shared_ptr<T>();
//        }
//        return std::make_shared<T>(head->data);
//    }
//
//    bool isempty() const {
//        std::lock_guard<std::mutex> lk(mut);
//        return head == nullptr;
//    }
//};
//
//struct TestStruct {
//    int id;
//    std::string name;
//
//    TestStruct(int i, const std::string& n) : id(i), name(n) {}
//};
//
//
//void test_stack() {
//    StackThreadStack<int> stack;
//
//    std::thread t1([&]() {
//        stack.push(12);
//        std::cout << "Thread 1: pushed 12" << std::endl;
//        });
//
//    std::thread t2([&]() {
//        stack.push(123);
//        std::cout << "Thread 2: pushed 123" << std::endl;
//        });
//
//    std::thread t3([&]() {
//        auto item = stack.pop();
//        if (item) {
//            std::cout << "Thread 3: popped " << *item << std::endl;
//        }
//        });
//
//    std::thread t4([&]() {
//        auto item = stack.pop();
//        if (item) {
//            std::cout << "Thread 4: popped " << *item << std::endl;
//        }
//        });
//
//    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();
//}
//
//int main() {
//    StackThreadStack<int> stack;
//
//    std::cout << "test 1" << std::endl;
//    // test1
//    stack.push(1);
//    stack.push(2);
//    stack.push(3);
//    std::cout << *stack.pop() << std::endl;
//    std::cout << *stack.pop() << std::endl;
//    std::cout << *stack.pop() << std::endl;
//    std::cout << "Stack empty: " << stack.isempty() << std::endl;
//
//    // test 2
//    std::cout << "test 2" << std::endl;
//    StackThreadStack<TestStruct> struct_stack;
//    struct_stack.push(TestStruct(1, "123"));
//    struct_stack.push(TestStruct(2, "456"));
//    auto popped = struct_stack.pop();
//    std::cout << "pop: id, name = " << popped->id << " " << popped->name << std::endl;
//    auto top = struct_stack.top();
//    std::cout << "top: id, name = " << top->id << " " << top->name << std::endl;
//
//    // test 3
//    std::cout << "test 3" << std::endl;
//    StackThreadStack<int> empty_stack;
//    std::cout << "empty stack pop: " << empty_stack.pop() << std::endl;
//
//    // test 4
//    test_stack();
//
//    return 0;
//}


template <class T>
void f(T ); // (a) primary template
template <class T>
void f (T*); // (b) overloads (a), primary template
template <>
void f<int>(int *); // (c),  specification of (b)
// …
int * p;
f(p); // (c) ?
