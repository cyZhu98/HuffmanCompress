//
// Created by tlh on 2016/4/27.
//
// Modified by cyZhu 2023.04.26
#ifndef ALGRITHMHW_HUFFMANTREE_H
#define ALGRITHMHW_HUFFMANTREE_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

struct HuffmanTreeNode {
    int weight;
    int data;
    HuffmanTreeNode *left;
    HuffmanTreeNode *right;

    HuffmanTreeNode() { }

    HuffmanTreeNode(int w, int d) : weight(w), data(d), left(nullptr), right(nullptr){ }

    HuffmanTreeNode(int w) : weight(w), data('#'), left(nullptr), right(nullptr) { }

    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }
};

// 自定义最小堆比较方式
class compare {
public:
    bool operator()(const HuffmanTreeNode *left, const HuffmanTreeNode *right) {
        return left->weight > right->weight;
    }
};

class HuffmanTree {
public:
    HuffmanTree(vector<HuffmanTreeNode*>& nodes);

    HuffmanTreeNode *getRoot() { return root; }

    static void decode(FILE* fin, FILE *fout);

    void buildCodeBook();

    static void encode(FILE *fin, FILE *fout);

    static HuffmanTree *readWeightAndBuildTree(FILE *fin);

    ~HuffmanTree();

    // 编码表
    unordered_map<int, string> codeBook;
private:
    HuffmanTreeNode *root;

    void _deleteTree(HuffmanTreeNode *p);

    void buildCode(HuffmanTreeNode* node, string s);

    void writeCode(vector<int>& binaryData, FILE *fout);

    void writeWeight(vector<int>& weight, FILE *fout);

};

#endif //ALGRITHMHW_HUFFMANTREE_H
