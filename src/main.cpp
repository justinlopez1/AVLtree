#include <iostream>
#include <string>            //we have to leave comments??? why
#include "AVL.h"   //test

int main() {

    AVLTree tree; //tree object

    std::string temp;
    int count = 0;
    getline(std::cin, temp);
    if (is_number(temp)) count = stoi(temp);
    else std::cout << "invalid argument count" << std::endl;  //command count

    for (int i = 0; i < count; i++) {
        getline(std::cin, temp);
        std::string one = temp.substr(0, temp.find(' '));
        temp = temp.substr(temp.find(' ')+1);

        std::string two;
        std::string three;
        if (temp.find('"') != std::string::npos) {
            std::string x = temp.substr(1);
            //std::cout << x << std::endl;
            int pos = (int)x.find('"');
            two = temp.substr(0,pos+2);
            temp = temp.substr(pos+2);

            if (temp.find(' ') != std::string::npos) {
                three = temp.substr(1);
            }
            else {
                three = temp;
            }

        }
        else {
            if (temp.find(' ') != std::string::npos) {
                two = temp.substr(0, temp.find(' '));
                three = temp.substr(temp.find(' ')+1);

            }
            else {
                two = temp;
                three = temp;
            }
        }

        //std::cout << one << "|" << two << "|" << three << std::endl;

        if (one == "insert") {
            if (is_valid_name(two) and is_valid_id(three)) tree.insert(three, remove_quotes(two));
            else std::cout << "unsuccessful" << std::endl;
        }

        else if (one == "remove") {
            if (is_valid_id(two)) tree.remove(two);
            else std::cout << "unsuccessful" << std::endl;
        }

        else if (one == "search") {
            if (is_valid_id(two)) {
                tree.search_id(two);
            }
            else if (is_valid_name(two)) {
                 tree.search_name(remove_quotes(two));
            }
            else {
                std::cout << "unsuccessful" << std::endl;
            }
        }

        else if (one == "printInorder") {
            tree.print_inorder();
        }

        else if (one == "printPostorder") {
            tree.print_postorder();
        }

        else if (one == "printPreorder") {
            tree.print_preorder();
        }

        else if (one == "printLevelCount") {
            std::cout << tree.get_level_count() << std::endl;
        }

        else if (one == "removeInorder") {
            if (is_number(two)) tree.remove_inorder_N(stoi(two));
            else std::cout << "unsuccessful" << std::endl;
        }
        else {
            std::cout << "unsuccessful" << std::endl;
        }
    }



    return 0;
}
