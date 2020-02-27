#include<bits/stdc++.h>
using namespace std;
// Function for finding sum of larger numbers
string findSum(string str1, string str2)
{
    // Before proceeding further, make sure length
    // of str2 is larger.
    if (str1.length() > str2.length())
        swap(str1, str2);

    // Take an empty string for storing result
    string str = "";

    // Calculate length of both string
    int n1 = str1.length(), n2 = str2.length();

    // Reverse both of strings
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());

    int carry = 0;
    for (int i=0; i<n1; i++)
    {
        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');

        // Calculate carry for next step
        carry = sum/10;
    }

    // Add remaining digits of larger number
    for (int i=n1; i<n2; i++)
    {
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }

    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');

    // reverse resultant string
    reverse(str.begin(), str.end());

    return str;
}
// Multiplies str1 and str2, and prints result.
string multiply(string num1, string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";

    // will keep the result number in vector
    // in reverse order
    vector<int> result(len1 + len2, 0);

    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;

    // Go from right to left in num1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';

        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;

        // Go from right to left in num2
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';

            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;

            // Carry for next iteration
            carry = sum/10;

            // Store result
            result[i_n1 + i_n2] = sum % 10;

            i_n2++;
        }

        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;

        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }

    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;

    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
    return "0";

    // generate the result string
    string s = "";

    while (i >= 0)
        s += std::to_string(result[i--]);

    return s;
}


int main()
{
    //Define variables to read input file
ifstream infile;
string line1,line2;
//Open and read input file
infile.open("input.txt");
if(infile.is_open()){
    if(infile.good()){
        getline(infile,line1);
        getline(infile,line2);
    }
}
infile.close();
//Check length of strings, make sure they are of equal length
    int length1 = line1.size();
    int length2 = line2.size();
    if (length1 < length2)
    {
        for (int i = 0 ; i < length2 - length1 ; i++)
            line1 = '0' + line1;
    }
    else if (length1 > length2)
    {
        for (int i = 0 ; i < length1 - length2 ; i++)
            line2 = '0' + line2;
    }
//Make sure the strings are of an even length for the main algorithm
    if((line1.size()%2)!=0)
    {   line1 = '0' + line1;
        line2 = '0' + line2;
    }
   string str1=line1,str2=line2;


  //  cout << multiply(str1, str2);

  char char_array1[line1.size()];
  char char_array2[line2.size()];

  strcpy(char_array1,str1.c_str());
  strcpy(char_array2,str2.c_str());


  int half=(line2.size())/2;


  char msb1[half];
  char lsb1[half];
  char msb2[half];
  char lsb2[half];

memcpy(msb1, char_array1+ 0 , half );
msb1[half]=0;//null terminate destination
memcpy(lsb1, char_array1+ half, half );
lsb1[half]=0;
memcpy(msb2, char_array2+ 0, half );
msb2[half]=0;
memcpy(lsb2, char_array2+ half , half );
lsb2[half]=0;

string msb1_str;
msb1_str += msb1;

string lsb1_str;
 lsb1_str += lsb1;

string msb2_str;
msb2_str += msb2;

string lsb2_str;
 lsb2_str += lsb2;

string A0B0=multiply(lsb1_str, lsb2_str);
string A1B0=multiply(lsb2_str, msb1_str);
string A0B1=multiply(lsb1_str, msb2_str);
string A1B1=multiply(msb1_str, msb2_str);
string SumAB=findSum(A1B0,A0B1);


char zero='0';
for(int v=0;v<(half*2);v++)
A1B1+=zero;
for(int z=0;z<half;z++)
SumAB+=zero;

string soln=findSum(A1B1,SumAB);
       soln=findSum(soln,A0B0);

       // open a file in write mode.
   ofstream outfile;
   outfile.open("output_naiv2way.txt");

   // write inputted data into the file.
   outfile <<soln<<endl ;

   // close the opened file.
   outfile.close();

    return 0;
}
