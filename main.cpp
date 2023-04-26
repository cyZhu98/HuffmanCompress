#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanTree.h"
#include <sys/stat.h>

using namespace std;

// 通过stat结构体 获得文件大小，单位字节
size_t getFileSize(string& fileName) {

    if (fileName.empty()) {
        return 0;
    }
    // 这是一个存储文件(夹)信息的结构体，其中有文件大小和创建时间、访问时间、修改时间等
    struct stat statbuf;
    // 提供文件名字符串，获得文件属性结构体
    stat(fileName.c_str(), &statbuf);
    // 获取文件大小
    size_t filesize = statbuf.st_size;

    return filesize;
}

void encode(string& src, string& dst) {
    //以二进制流的方式打开IO流
    FILE *fin = fopen(src.c_str(), "rb");
    if (fin == nullptr) {
        cout << "源文件路径错误" << endl;
        return;
    }
    FILE *fout = fopen(dst.c_str(), "wb+");
    if (fout == nullptr) {
        cout << "目标文件路径错误" << endl;
        return;
    }
    HuffmanTree::encode(fin, fout);
    int srcSize = getFileSize(src);
    int dstSize = getFileSize(dst);
    cout << "原文件大小为: " << srcSize << " 字节;" << endl;
    cout << "压缩后文件大小为: " << dstSize << " 字节;" << endl;
    cout << "压缩比为: " << (double)srcSize / (double)dstSize << endl;
}

void decode(string& src, string& dst) {
    //以二进制流的方式打开IO流
    FILE *fin = fopen(src.c_str(), "rb");
    if (fin == nullptr) {
        cout << "源文件路径错误" << endl;
        return;
    }
    FILE *fout = fopen(dst.c_str(), "wb+");
    if (fout == nullptr) {
        cout << "目标文件路径错误" << endl;
        return;
    }
    HuffmanTree::decode(fin, fout);

}


bool help(int &op) {
    system("cls");
    cout<<"|哈夫曼编码实现文件压缩|"<<endl;
    cout<<"功能: "<<endl;
    cout<<"_________________________________ "<<endl;
    cout<<"|输入1：压缩文件|"<<endl;
    cout<<"|输入2、解压文件|"<<endl;
    cout<<"|输入0、退出     |"<<endl;
    cout<<"--------------------------------- "<<endl;
    do {
        cout<<"请选择："<<endl;
        cin >> op;
    } while (op < 0 || op > 3);
    return op != 0;
}

int main() {
    int op;
    string srcFile, dstFile;
    while (help(op)) {
        switch (op) {
            case 1:
                cout << "请输入待压缩文件路径,包含完整文件名及后缀：" << endl;
//                srcFile = "D:\\Projects\\test.txt";
                cin >> srcFile;
                cout << "请输入压缩文件路径,包含完整文件名及后缀：" << endl;
                cin >> dstFile;
//                dstFile = "D:\\Projects\\test.encode";
                encode(srcFile, dstFile);
                cout << "压缩完成！" << endl;
                break;
            case 2:
                cout<<"请输入待解压文件路径,包含完整文件名及后缀："<<endl;
                cin >> srcFile;
//                srcFile = "D:\\Projects\\test.encode";
                cout<<"请输入解压后文件路径,包含完整文件名及后缀："<<endl;
                cin >> dstFile;
//                dstFile = "D:\\Projects\\test.encode.txt";
                decode(srcFile, dstFile);
                cout << "解压完成！" << endl;
                break;
        }
        cout<<"按任意键继续..."<<endl;
        getchar();
        getchar();
    }
    return 0;
}