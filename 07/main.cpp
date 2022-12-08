// code7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// un-comment the part you want to resolve.
#define PART1
#define PART2

#define INPUT "input"

void GotLS(std::ifstream& ifs);
void GotCD(std::ifstream& ifs);
void GotPrompt(std::ifstream& ifs, const std::string& notPrompt);

#ifdef PART1
int64_t sum = 0;
#endif

#ifdef PART2
int64_t totalspace = 70000000;
int64_t minimalspace = 30000000;
int64_t smallest = 0;
#endif

class Node
{
public:

    bool isDir = false;
    std::vector<Node*> children;
    Node* parent = nullptr;
    std::string entry;
    int64_t filesize = 0;
    int64_t totalsize = 0;

    Node() { }

    virtual ~Node()
    {
        for (Node* child : children)
        {
            delete child;
        }
    }
};

Node* root = nullptr;
Node* currentNode = nullptr;

#ifdef PART2
void GetSmallest(Node* current)
{
    if (!current->isDir)
        return;

    if (totalspace - root->totalsize + current->totalsize > minimalspace)
    {
        if (current->totalsize < smallest)
            smallest = current->totalsize;
    }

    for (Node* n : current->children)
        GetSmallest(n);
}
#endif

int64_t GetSizes(Node* current, size_t offset)
{
   for (size_t i = 0; i < offset; i++)
    {
        std::cout << " ";
    }

    std::cout << "- " << current->entry;
    
    if (current->isDir)
    {
        std::cout << " (dir)\n";

        for (Node* n : current->children)
            current->totalsize += GetSizes(n, offset + 4);

#ifdef PART1
        if (current->totalsize && current->totalsize <= 100000)
        {
            std::cout << current->entry << ": " << current->totalsize << "\n";
            sum += current->totalsize;
        }
#endif
#ifdef PART2
            std::cout << current->entry << ": " << current->totalsize << "\n";
#endif
    }
    else
    {
        std::cout << " (file, size=" << current->filesize << ")\n";
        return current->filesize;
    }

    return current->totalsize;
}

void GotLS(std::ifstream& ifs)
{
    std::string listed;

    do
    {
        ifs >> listed;

        if (ifs.eof())
            break;

        if (listed != "$")
        {
            Node* node = new Node();
            node->parent = currentNode;
            currentNode->children.push_back(node);

            if (listed == "dir")
                node->isDir = true;
            else
                node->filesize = atoi(listed.c_str());

            ifs >> node->entry;
        }

    } while (listed != "$");
}

void GotCD(std::ifstream& ifs)
{
    std::string location;

    ifs >> location;

    if (location == "/")
    {
        if (root == nullptr)
        {
            root = new Node();
            root->isDir = true;
            root->entry = "/";
        }

        currentNode = root;
    }
    else if (location == "..")
    {
        currentNode = currentNode->parent;
    }
    else
    {
        for (auto c : currentNode->children)
        {
            if (c->entry == location)
            {
                currentNode = c;
                break;
            }
        }
    }
}

void GotPrompt(std::ifstream& ifs, const std::string& notPrompt)
{
    std::string promptOrNot, cmd, to;

    if (!notPrompt.size())
    {
        ifs >> cmd;
    }
    else
    {
        cmd = notPrompt;
    }

    if (cmd == "cd")
    {
        GotCD(ifs);
    }
    else if (cmd == "ls")
    {
        GotLS(ifs);
    }
}

void Part()
{
    std::ifstream ifs(INPUT);

    try
    {
        if (!ifs)
            throw("Could not open input");

        do
        {
            std::string cmd;

            ifs >> cmd;

            if (ifs.eof())
                break;         
                
            GotPrompt(ifs, (cmd == "$") ? "" : cmd);

        } while (1);

        GetSizes(root, 0);
#ifdef PART1
        std::cout << "Sum = " << sum << "\n";
#endif
#ifdef PART2
        smallest = totalspace;
        GetSmallest(root);
        std::cout << "smallest = " << smallest << "\n";
#endif
    }
    catch (const char* err)
    {
        std::cerr << err << "\n";
    }

    if (root)
        delete root;
}

int main()
{
    Part();
}
