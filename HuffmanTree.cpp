//
// Created by tlh on 2016/4/27.
//
// Modified by cyZhu 2023.04.26
#include <string>
#include <queue>
#include "HuffmanTree.h"
#include "BitStream.hpp"

HuffmanTree::~HuffmanTree() {
    _deleteTree(root);
}

void HuffmanTree::_deleteTree(HuffmanTreeNode *p) {
    if (p != nullptr) {
        _deleteTree(p->left);
        _deleteTree(p->right);
        delete p;
    }
}

/**
 * 通过传入HuffmanTreeNode的数组建立哈夫曼树
 */
HuffmanTree::HuffmanTree(vector<HuffmanTreeNode*>& nodes) {
    priority_queue<HuffmanTreeNode*, vector<HuffmanTreeNode*>, compare>minHeap;
    for (int i = 0; i < nodes.size(); i++) {
        minHeap.push(nodes[i]);
    }
    HuffmanTreeNode *left = nullptr;
    HuffmanTreeNode *right = nullptr;
    HuffmanTreeNode *parent = nullptr;

    while(minHeap.size() > 1) {
        //从堆中取出最小两个的节点，
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        //new一个父节点，父节点的值为两个子节点的值之和
        parent = new HuffmanTreeNode(left->weight + right->weight);
        //连接刚才取出的两个节点，合并两棵子树
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }
    root = parent;
}

//
void HuffmanTree::buildCodeBook() {
    buildCode(root, "");
}

void HuffmanTree::buildCode(HuffmanTreeNode* node, string s) {
    if (node == nullptr) {
        return;
    }
    if (!node->left && !node->right) {
        codeBook.insert({node->data, s});
    }
    buildCode(node->left, s + '0');
    buildCode(node->right, s + '1');
}

void HuffmanTree::writeCode(vector<int>& binaryData, FILE *fout) {
    if (binaryData.size() == 0) return;
    fpos_t startPos;//记录初始写入的位置
    fgetpos(fout, &startPos);
    // 计数，满八位则写入文件
    // 记录写入压缩文件的比特数 long和long long 在64位下占8位
    long long bits = 0;
    // 缓存
    int buffer = 0;
    // 需要写入到压缩文件的字节数组
    vector<int> codes;
    // 遍历待编码的数组
    for (int i = 0; i < binaryData.size(); ++i) {
        // 根据码表编码，这个codeBook的key是字节，value是字符数组
        string code = codeBook[binaryData[i]];
        //对字符数组code遍历，转化成0或1，放入缓存字节当中
        for (int j = 0; j < code.size(); j++) {
            buffer <<= 1;
            if (code[j] == '1')
                buffer += 1;
            bits++;
            if (bits % 8 == 0) {
                //满8位，则将字节存入codes数组，将缓存字节置零
                //cout << buffer << endl;
                codes.push_back(buffer);
                buffer = 0;
            }
        }
    }
    // 刚好没有剩余的bit
    if (bits % 8 == 0) {
        // 存入8表示最后一个字节8位都是有用的编码
        fputc(8, fout);
        int lastCodeBitsCount = bits % 8;
        fputc(lastCodeBitsCount, fout);
        //写入编码后的数据
        for (int i = 0; i < codes.size(); i++){
            fputc(codes[i], fout);
        }
        return;
    }
    // 存入lastCodeBitsCount表示最后一个字节只有后lastCodeBitsCount位才是有用的编码
    int lastCodeBitsCount = bits % 8;
    fputc(lastCodeBitsCount, fout);
    // 写入编码后的数据
    for (int i = 0; i < codes.size(); i++){
        fputc(codes[i],fout);
    }
    fputc(buffer, fout);
}

void HuffmanTree::encode(FILE *fin, FILE *fout) {
    // 统计字节出现的频率
    // 一个字节的表示范围是0-255，声明权值数组
    vector<int>weight(256, 0);
    if (fin == nullptr) {
        cout << "file not found" << endl;
        return;
    }
    int c;
    // 将读取的直接存入动态可调数组内
    vector<int> binaryData;
    while (true) {
        c = fgetc(fin);
        if (feof(fin)) break;
        weight[c]++;
        binaryData.push_back(c);
    }
    fclose(fin);
    // 指向一个指针数组的指针
    vector<HuffmanTreeNode*>treeNodes;
    for (int i = 0; i < 256; i++) {
        if (weight[i] == 0) {
            continue;
        }
        treeNodes.push_back(new HuffmanTreeNode(weight[i], i));
    }
    //建立哈夫曼树
    HuffmanTree tree(treeNodes);
    //向文件写入权值数组
    tree.writeWeight(weight, fout);
    tree.buildCodeBook();
    tree.writeCode(binaryData, fout);
    fclose(fout);
}

void HuffmanTree::writeWeight(vector<int>& weight, FILE *fout) {
    int weightCopy[256];
    for (int i = 0; i < 256; ++i) {
        weightCopy[i]=weight[i];
    }
    //将权值数组写入到压缩文件当中
    fwrite(&weightCopy, sizeof(weight[0]), 256, fout);
    //for (int i = 0; i < 256; ++i) {
    //   // fputc(weight[i], fout);
    //}
}

HuffmanTree *HuffmanTree::readWeightAndBuildTree(FILE *fin) {
    vector<HuffmanTreeNode*>treeNodes;
    int weight[256];
    // 从压缩文件读取权值数组
    fread(&weight, sizeof(weight[0]), 256, fin);
    // 建树
    for (int i = 0; i < 256; i++) {
        if (weight[i] == 0) {
            continue;
        }
        treeNodes.push_back(new HuffmanTreeNode(weight[i], i));
    }
    return new HuffmanTree(treeNodes);
}

void HuffmanTree::decode(FILE *fin, FILE *fout) {
    HuffmanTree *tree = readWeightAndBuildTree(fin);
    int lastCodeBitsCount = fgetc(fin);
    BitStream stream(fin, lastCodeBitsCount);
    bool bit;
    HuffmanTreeNode *p = tree->getRoot();
    while (stream.getBit(bit)) {
        if (bit == 0) p = p->left;
        else p = p->right;
        if (p != nullptr && p->isLeaf()) {
            fputc(p->data, fout);
            p = tree->getRoot();
        }
    }
    fclose(fin);
    fclose(fout);
}
