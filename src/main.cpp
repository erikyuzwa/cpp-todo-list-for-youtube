#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <memory>
#include <algorithm>

class TodoItem {
private:
    int id;
    std::string description;
    bool completed;

public:

    TodoItem() : id(0), description(""), completed(false) {}


    ~TodoItem() = default;

    bool create(std::string new_description) {
        // generates a random integer between 1 and 100
        id = rand() % 100 + 1;
        description = new_description;
        return true;
    }

    int getId() const { return id; }

    // std::string getDescription() { return description; }

    const std::string& getDescription() const { return description; }
    bool isCompleted() const { return completed; }

    void setCompleted(bool val) { completed = val; }

};

int main()
{
    char input_option;
    int input_id;
    std::string input_description;
    std::string version = "v0.2.0";
    //std::list<TodoItem> todoItems;
    std::vector<std::unique_ptr<TodoItem>> todoItems;

    // srand(time(NULL));
    // Avoid warning 
    srand(static_cast<unsigned int>(time(NULL)));


    todoItems.clear();

    while (1) {
        system("cls");
        std::cout << "Todo List Maker - " << version << std::endl;
        std::cout << std::endl << std::endl;

        for (const auto& item : todoItems) {

            std::string completed = item->isCompleted() ? "done" : "not done";

            std::cout << item->getId() << " | " << item->getDescription() << " | "
                << completed << std::endl;
        }

        if (todoItems.empty()) {
            std::cout << "Add your first todo!" << std::endl;
        }

        std::cout << std::endl << std::endl;

        std::cout << "[a]dd a new Todo" << std::endl;
        std::cout << "[c]omplete a Todo" << std::endl;
        std::cout << "[q]uit" << std::endl;

        std::cout << "choice: ";

        std::cin >> input_option;

        if (input_option == 'q') {
            std::cout << "Have a great day now!" << std::endl;
            break;
        }
        else if (input_option == 'a') {
            std::cout << "Add a new description: ";
            std::cin.clear();
            std::cin.ignore();
            std::getline(std::cin, input_description);

            //TodoItem newItem;
            //newItem.create(input_description);
            //todoItems.push_back(newItem);

            std::unique_ptr<TodoItem> newItem = std::make_unique<TodoItem>();
            newItem->create(input_description);
            todoItems.push_back(std::move(newItem));

        }
        else if (input_option == 'c') {
            std::cout << "Enter id to mark completed: ";
            std::cin >> input_id;

            //for (it = todoItems.begin(); it != todoItems.end(); it++) {

            //    if (input_id == it->getId()) {
            //        it->setCompleted(true);
            //        break;
            //    }
            //}

            auto it = std::find_if(todoItems.begin(), todoItems.end(), [input_id](const auto& item)
                {
                    return input_id == item->getId();
                });

            if (it != todoItems.end()) {
                (*it)->setCompleted(true);
            }
        }


    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


//-Use** const** and **reference * *modifiers for your getter methods.This will prevent unnecessary copying and modification of your class members.For example, instead of `std: :string getDescription()`, you can write `const std::string& getDescription() const`.
//- Use * *smart pointers * *instead of raw pointers.This will help you avoid memory leaks and simplify memory management.For example, instead of `TodoItem* newItem = new TodoItem(); `, you can write `std::unique_ptr<TodoItem> newItem = std::make_unique<TodoItem>(); `.
//- Use * *std::vector * *instead of std::list.This will improve your performance and reduce memory fragmentation.For example, instead of `std::list<TodoItem> todoItems; `, you can write `std::vector<TodoItem> todoItems; `.
//- Use * *std::find_if * *instead of manual iteration.This will make your code more readable and expressive.For example, instead of `for (it = todoItems.begin(); it != todoItems.end(); it++) { 
// if (input_id == it->getId()) { it->setCompleted(true); break; } }`,
// you can write `auto it = std::find_if(todoItems.begin(), todoItems.end(), [input_id](const TodoItem& item)  
// { return input_id == item.getId(); }); if (it != todoItems.end()) 
// { it->setCompleted(true); }`.

