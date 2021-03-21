#include <iostream>
#include <bitset>
#include <string>
#include <vector>
using namespace std;

const int PC_1[56] = { 
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4 
};

const int shiftBits[16] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

const int PC_2[48] = { 
    14, 17, 11, 24,  1,  5,
    3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9,  1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

const int E[48] = { 
    32,  1,  2,  3,  4,  5,
    4,  5,  6,  7,  8,  9,
    8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1 
};

const int S_BOX[8][4][16] = {
		{
			{ 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7 },
	{ 0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8 },
	{ 4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0 },
	{ 15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13 }
		},
	{
		{ 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10 },
	{ 3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5 },
	{ 0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15 },
	{ 13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9 }
	},
	{
		{ 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8 },
	{ 13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1 },
	{ 13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7 },
	{ 1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12 }
	},
	{
		{ 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15 },
	{ 13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9 },
	{ 10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4 },
	{ 3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14 }
	},
	{
		{ 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9 },
	{ 14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6 },
	{ 4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14 },
	{ 11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3 }
	},
	{
		{ 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11 },
	{ 10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8 },
	{ 9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6 },
	{ 4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13 }
	},
	{
		{ 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1 },
	{ 13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6 },
	{ 1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2 },
	{ 6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12 }
	},
	{
		{ 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7 },
	{ 1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2 },
	{ 7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8 },
	{ 2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11 }
	}
};

const int P[32] = { 
    16,  7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};

const int IP_1[64] = {  
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25 
};


int sBoxEvaluate(int box, string fl, string mid) {
    int row, col;
    if (fl == "00")
        row = 0;
    else if (fl == "01")
        row = 1;
    else if (fl == "10")
        row = 2;
    else 
        row = 3;
    
    if (mid == "0000")
        col = 0;
    else if (mid == "0001")
        col = 1;
    else if (mid == "0010")
        col = 2;
    else if (mid == "0011")
        col = 3;
    else if (mid == "0100")
        col = 4;
    else if (mid == "0101")
        col = 5;
    else if (mid == "0110")
        col = 6;
    else if (mid == "0111")
        col = 7;
    else if (mid == "1000")
        col = 8;
    else if (mid == "1001")
        col = 9;
    else if (mid == "1010")
        col = 10;
    else if (mid == "1011")
        col = 11;
    else if (mid == "1100")
        col = 12;
    else if (mid == "1101")
        col = 13;
    else if (mid == "1110")
        col = 14;
    else
        col = 15;
    return S_BOX[box][row][col];
}


class DES {
public:
    void getPlaintextString(string);
    void getKeyString(string);
    void transferToBinaryString();
    void generateRealKeySet();
    void encryptText();
    void showResult();

    string plaintextString;
    string keyString;
    bitset<64> plaintextBitset;
    bitset<64> keyBitset;
    bitset<48> realKeySet[16];
    vector<char> hexStringResult;
};

void DES::getPlaintextString(string s) {
    plaintextString = s;
}

void DES::getKeyString(string s) {
    keyString = s;
}

void DES::transferToBinaryString() {
    int head = 0;
    for(int i = 0;i < plaintextString.length();i++){
        bitset<8> temp(plaintextString[i]);
        for(int j = head;j < head + 8;j++){
            plaintextBitset[63 - j] = temp[7 - (j % 8)];
        }
        head += 8;
    } 

    head = 0;
    for(int i = 0;i < keyString.length();i++){
        bitset<8> temp(keyString[i]);
        for(int j = head;j < head + 8;j++){
            keyBitset[63 - j] = temp[7 - (j % 8)];
        }
        head += 8;
    }
    plaintextString = plaintextBitset.to_string();
    keyString =  keyBitset.to_string();
}

//ascii 0 = 48 decimal
void DES::generateRealKeySet() {
    //重新排列並選出 56bits 的 key在分左右
    bitset<28> permutedKeyLeft;
    bitset<28> permutedKeyRight;
    for(int i = 0; i < 56;i++) {
        if (i <= 27) {
            permutedKeyLeft[27 - i] = int(keyString[PC_1[i] - 1]) - 48;
        } else {
            permutedKeyRight[55 - i] = int(keyString[PC_1[i] - 1]) - 48;
        }
    }

    //左移操作 + PC_2
    for(int i = 0;i < 16;i++){
        bitset<28> prevLeft = permutedKeyLeft;
        bitset<28> prevRight = permutedKeyRight;
        permutedKeyLeft = permutedKeyLeft << shiftBits[i];
        permutedKeyRight = permutedKeyRight << shiftBits[i];
        for(int x = 28 - shiftBits[i], y = 0;x < 28;x++, y++) {
            permutedKeyLeft[y] = prevLeft[x];
            permutedKeyRight[y] = prevRight[x];
        }

        string temp = permutedKeyLeft.to_string() + permutedKeyRight.to_string();
        for(int j = 0;j < 48;j++){
            realKeySet[i][47 - j] = int(temp[PC_2[j]-1]) - 48;
        }
    }

}

void DES::encryptText() {
    //IP permutation for plaintext
    bitset<32> leftIpResult;
    bitset<32> rightIpResult;

    for(int i = 0;i < 64;i++){
        if(i < 32) {
            leftIpResult[31 - i] = int(plaintextString[IP[i]-1]) - 48;
        } else {
            rightIpResult[31 - (i % 32)] = int(plaintextString[IP[i]-1]) - 48;
        }
    }
    
    //16 round Feistel
    for(int i = 0;i < 16;i++){
        //extend right
        bitset<48> extendRight;

        for(int j = 0;j < 48;j++){
            extendRight[47 - j] = rightIpResult[31 - (E[j] - 1)];
        }

        extendRight = extendRight ^ realKeySet[i];

        //S - Box
        string extendRightString = extendRight.to_string();
        string resultString = "";
        int box = 0;
        for(int j = 0;j < 48;j += 6){
            string fl = extendRightString.substr(j, 1) + extendRightString.substr(j+5, 1);
            string mid = extendRightString.substr(j+1, 4);
            int sValueDecimal = sBoxEvaluate(box, fl, mid);
            resultString = resultString + bitset<4>(sValueDecimal).to_string();
            box++;
        }

        //p permutation
        bitset<32> pResult;
        for(int j = 0;j < 32;j++){
            pResult[31 - j] = int(resultString[P[j] - 1]) - 48;
        }

        //swap
        bitset<32> prevRight = rightIpResult;
        rightIpResult = leftIpResult ^ pResult;
        leftIpResult = prevRight;
    }

    bitset<64> resultBitset(rightIpResult.to_string() + leftIpResult.to_string());
    string finalString(64, '0');
    //IP -1 permutation
    for(int i = 0;i < 64;i++){
        finalString[i] = resultBitset[63 - (IP_1[i]-1)] + 48;
    }

    //transfer to hex string
    for(int i = 0;i < 64;i += 4){
        string temp = finalString.substr(i, 4);
        int summ = 8*(int(temp[0]) - 48) + 4*(int(temp[1]) - 48) + 2*(int(temp[2]) - 48) + int(temp[3]) - 48;
        if (summ == 10)
            hexStringResult.push_back('A');
        else if (summ == 11)
            hexStringResult.push_back('B');
        else if (summ == 12)
            hexStringResult.push_back('C'); 
        else if (summ == 13)
            hexStringResult.push_back('D');
        else if (summ == 14)
            hexStringResult.push_back('E');
        else if (summ == 15)
            hexStringResult.push_back('F');
        else
            hexStringResult.push_back(summ + 48);
    }
}

void DES::showResult() {
    cout << endl;
    cout << "The encryption result is: ";
    for(auto a : hexStringResult)
        cout << a;
    cout << endl;
}

int main () {
    string plaintext;
    string key;
    cout << "Please enter the plaintext: " << endl;
    cin >> plaintext;
    cout << "Please enter the key: " << endl;
    cin >> key;
    DES d;
    d.getKeyString(key);
    d.getPlaintextString(plaintext);
    d.transferToBinaryString();
    //test
    // d.plaintextString = "0000000100100011010001010110011110001001101010111100110111101111";
    // d.keyString = "0001001100110100010101110111100110011011101111001101111111110001";
    //test
    d.generateRealKeySet();
    d.encryptText();
    d.showResult();
}



