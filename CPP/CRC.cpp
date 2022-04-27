#include <iostream>
#include <string>
using namespace std;

class CRC {

    string input,divisor,divident,result;
    int len_divident,len_generator,len_input;

    public:
    string fun_xor(string a,string b)
    {
        string result = "";
        if(a[0]=='0')
        {
            return a.substr(1);
        }
        else
        {
            for (int i=0;i<len_generator;i++)
            {
                result = result + (a[i]==b[i] ? '0':'1');
            }
            return result.substr(1);
        }
    }

    void modulo_div()
    {
        string temp_div = divisor;
        string temp_divident = divident.substr(0,len_generator);
        int j = len_generator;
        while(j<len_divident)
        {
            temp_divident = fun_xor(temp_divident,temp_div);
            temp_divident = temp_divident+divident[j];
            j++;
        }
        result = input+fun_xor(temp_divident,temp_div);
    }

    void getdata()
    {
        cout<<"Enter Input : ";
        cin>>input;
        cout<<"Enter coefficients of generator polynomial : ";
        cin>>divisor;

        len_generator = divisor.length();
        len_input = input.length();
        divident = input;
        int r = len_generator-1;
        for(int i=0;i<r;i++)
        {
            divident = divident + '0';
        }
        len_divident = divident.length();
        modulo_div();
    }

    void sender_side()
    {
        cout<<"\nInput : "<<input<<endl;
        cout<<"Polynomial : "<<divisor<<endl;
        cout<<"Divident : "<<divident<<endl;
        cout<<"Data to send : "<<result<<endl;
    }

    void reciever_side()
    {
        string data_recieved;
        cout<<"\nEnter Data Recieved : ";
        cin>>data_recieved;

        string temp_divisor = divisor;
        string temp_divident = data_recieved.substr(0,len_generator);
        int j = len_generator;
        while(j<data_recieved.length())
        {
            temp_divident = fun_xor(temp_divident,temp_divisor);
            temp_divident = temp_divident + data_recieved[j];
            j++;
        }
        string error = fun_xor(temp_divident,temp_divisor);
        cout<<"Reminder is : "<<error;

        bool flag=0;
        for(int i=0;i<len_generator-1;i++)
        {
            if(error[i]=='1')
            {
                flag = 1;
                break;
            }
        }
        if(flag == 0)
        {
            cout<<"\nCorrect Data Recieved Without Any Error.";
        }
        else
        {
            cout<<"\nData Recieved Contain Some Error";
        }
    }
};

int main()
{
    CRC crc;
    crc.getdata();
    crc.sender_side();
    crc.reciever_side();
    return 0;
}