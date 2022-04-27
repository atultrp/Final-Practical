#include <iostream>
using namespace std;
int lenght;
void rev(int num[], int len)
{
        int temp;
        for (int i1 = 0, i2 = len - 1; i1 < len / 2; i1++, i2--)
        {
                temp = num[i2];
                num[i2] = num[i1];
                num[i1] = temp;
        }
        return;
}
void dec_to_bin(int dec, int bin_ary[])
{
        int tmp, i = 0;
        tmp = dec;
        while (tmp != 0)
        {
                bin_ary[i] = tmp % 2;
                tmp = tmp / 2;
                i++;
        }
        rev(bin_ary, i);
        lenght = i;
        for (int a = 0; a < i; a++)
                cout << bin_ary[a];
        cout << endl;
        return;
}
int sub_xor_bin(int divt[], int divr[], int len_div, int len)
{
        int j = 0, k;

        while (divt[j] != 1)
                j++;
        if ((len - j) < len_div)
                return 0;
        for (int i = j, k = 0; i < (len_div + j); i++, k++)
        {
                if (divt[i] == divr[k])
                        divt[i] = 0;
                else
                        divt[i] = 1;
        }
        return 1;
}

void app_end(int num[], int app, int &norm)
{
        lenght = (norm + app) - 1;
        for (int i = norm - 1; i < lenght; i++)
                num[i] = 0;
        cout << "The number after appending is:\n";
        for (int i = 0; i < lenght; i++)
                cout << num[i] << " ";
        cout << endl;

        norm = lenght;
}

void division(int msg[], int &len_msg, int gn[], int len_gn)
{
        int flag;
        app_end(msg, len_gn, len_msg);
        for (int i = 0; i < len_msg - 2; i++)
        {
                flag = sub_xor_bin(msg, gn, len_gn, len_msg);
                if (flag == 0)
                        break;
        }
        cout << "The msg now after dividing:\n";
        for (int i = 0; i < len_msg; i++)
                cout << msg[i] << " ";
        cout << endl;
}
int gen, msg;
int main()
{
        int msg_pass[20], msg_temp[20], chc, i = 0, lenght_msg, lenght_gen, rem[6], ori_msg_len;
        cout << "Enter the message to be passed(in decimal):\n";
        cin >> msg;
        cout << "The message in binary code:\n";
        dec_to_bin(msg, msg_pass);
        lenght_msg = lenght;
        cout << "Enter the generator number i.e, the divisor:(in decimal)\n";
        cin >> gen;
        cout << "the binary value of generator is:\n";
        int genr[6];
        dec_to_bin(gen, genr);
        lenght_gen = lenght;
        for (int j = 0; j < lenght_msg; j++)
                msg_temp[j] = msg_pass[j];
        ori_msg_len = lenght_msg;
        division(msg_pass, lenght_msg, genr, lenght_gen);
        i = 0;
        while (msg_pass[i] != 1)
        {
                i++;
                if (i >= lenght_msg)
                        break;
        }
        int r = ori_msg_len;
        if (i < lenght_msg)
        {
                cout << "The crc remainder is:\n";
                for (int j = i; j < lenght_msg; j++)
                {
                        cout << msg_pass[j] << " ";
                        msg_temp[r] = msg_pass[j];
                        r++;
                }
                cout << endl;
        }
        cout << "The msg to be passed:\n";
        for (i = 0; i < r; i++)
                cout << msg_temp[i] << " ";
        cout << endl;
        return 0;
}
