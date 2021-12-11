#include <My_SharedPtr.h>
#include <iostream>

class Item {
 public:
  Item() {
    std::cout << "Item created" << std::endl;
  }
  ~Item() {
    std::cout << "Item deleted" << std::endl;
  }
};

int main() {
  My_SharedPtr<Item> item1(new Item);
  if (true) {
    My_SharedPtr<Item> item2(std::move(item1));
  }
  My_SharedPtr<Item> item3(item1.get());
}
