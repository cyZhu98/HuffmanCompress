#include <iostream>
#include <fstream>
#include <string>
#include "HuffmanTree.h"
#include <sys/stat.h>

using namespace std;

// ͨ��stat�ṹ�� ����ļ���С����λ�ֽ�
size_t getFileSize(string& fileName) {

    if (fileName.empty()) {
        return 0;
    }
    // ����һ���洢�ļ�(��)��Ϣ�Ľṹ�壬�������ļ���С�ʹ���ʱ�䡢����ʱ�䡢�޸�ʱ���
    struct stat statbuf;
    // �ṩ�ļ����ַ���������ļ����Խṹ��
    stat(fileName.c_str(), &statbuf);
    // ��ȡ�ļ���С
    size_t filesize = statbuf.st_size;

    return filesize;
}

void encode(string& src, string& dst) {
    //�Զ��������ķ�ʽ��IO��
    FILE *fin = fopen(src.c_str(), "rb");
    if (fin == nullptr) {
        cout << "Դ�ļ�·������" << endl;
        return;
    }
    FILE *fout = fopen(dst.c_str(), "wb+");
    if (fout == nullptr) {
        cout << "Ŀ���ļ�·������" << endl;
        return;
    }
    HuffmanTree::encode(fin, fout);
    int srcSize = getFileSize(src);
    int dstSize = getFileSize(dst);
    cout << "ԭ�ļ���СΪ: " << srcSize << " �ֽ�;" << endl;
    cout << "ѹ�����ļ���СΪ: " << dstSize << " �ֽ�;" << endl;
    cout << "ѹ����Ϊ: " << (double)srcSize / (double)dstSize << endl;
}

void decode(string& src, string& dst) {
    //�Զ��������ķ�ʽ��IO��
    FILE *fin = fopen(src.c_str(), "rb");
    if (fin == nullptr) {
        cout << "Դ�ļ�·������" << endl;
        return;
    }
    FILE *fout = fopen(dst.c_str(), "wb+");
    if (fout == nullptr) {
        cout << "Ŀ���ļ�·������" << endl;
        return;
    }
    HuffmanTree::decode(fin, fout);

}


bool help(int &op) {
    system("cls");
    cout<<"|����������ʵ���ļ�ѹ��|"<<endl;
    cout<<"����: "<<endl;
    cout<<"_________________________________ "<<endl;
    cout<<"|����1��ѹ���ļ�|"<<endl;
    cout<<"|����2����ѹ�ļ�|"<<endl;
    cout<<"|����0���˳�     |"<<endl;
    cout<<"--------------------------------- "<<endl;
    do {
        cout<<"��ѡ��"<<endl;
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
                cout << "�������ѹ���ļ�·��,���������ļ�������׺��" << endl;
//                srcFile = "D:\\Projects\\test.txt";
                cin >> srcFile;
                cout << "������ѹ���ļ�·��,���������ļ�������׺��" << endl;
                cin >> dstFile;
//                dstFile = "D:\\Projects\\test.encode";
                encode(srcFile, dstFile);
                cout << "ѹ����ɣ�" << endl;
                break;
            case 2:
                cout<<"���������ѹ�ļ�·��,���������ļ�������׺��"<<endl;
                cin >> srcFile;
//                srcFile = "D:\\Projects\\test.encode";
                cout<<"�������ѹ���ļ�·��,���������ļ�������׺��"<<endl;
                cin >> dstFile;
//                dstFile = "D:\\Projects\\test.encode.txt";
                decode(srcFile, dstFile);
                cout << "��ѹ��ɣ�" << endl;
                break;
        }
        cout<<"�����������..."<<endl;
        getchar();
        getchar();
    }
    return 0;
}