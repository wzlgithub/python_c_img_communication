#include "clientNet.h"
#include <iostream>
#include <fstream>
#include <string>



int main()
{

    CClientNet cct;
    cct.Connect(21567,"127.0.0.1");

    std::cout<< "connecting "<<std::endl;
        
    std::ifstream file("/home/wzl/design/communication/c_commu/src/a.tif",std::ifstream::in| std::ifstream::binary);

    if(!file.is_open())
    {
        std::cout<<"open failed!"<<std::endl;
    }

    file.seekg(0, std::ifstream::cur);
    int i=file.tellg();

    std::cout<<"i= "<<i<<std::endl;

    while(file.tellg() != -1)
    {
        char *p = new char[1024];

        bzero(p, 1024);
        file.read(p, 1024);

        printf("%ld\n", file.gcount());
        bool send_res=cct.SendMsg(p,1024);
        
        if(send_res==1)
        {
            std::cout<<"send failed!"<<std::endl;
        }else{
            std::cout<<"send successfully!"<<std::endl;
        }
        delete p;
    }
 
    file.close();

    cct.Close();

    return 0;
}

