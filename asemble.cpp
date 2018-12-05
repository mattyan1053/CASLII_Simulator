#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
using namespace std;

string memory[3000];

int SF = 0;
int ZF = 0;
int OF = 0;

int GR[8];

int PR = 0;
vector<int> SP;

map<string, int> label;

// 実装されている命令
map<string,int> cmdList = {
    {"START", 1},
    {"LD", 3},
    {"LAD", 3},
    {"ST", 3},
    {"ADDA", 3},
    {"SUBA", 3},
    {"AND", 3},
    {"OR", 3},
    {"XOR", 3},
    {"SLA", 3},
    {"SRA", 3},
    {"SLL", 3},// 中身はSLA
    {"SRL", 3},// 中身はSRA
    {"CPA", 3},
    {"JPL", 2},
    {"JMI", 2},
    {"JNZ", 2},
    {"JZE", 2},
    {"JUMP", 2},
    {"RET", 1},
    {"END", 1}
};

void printStatus(){
    cout << "| ";
    for(int i=0;i<8;i++){
        cout << "GR" << i << ":" << GR[i] << " | ";
    }
    cout << endl;
    cout << "SF:" << SF << " ZF:" << ZF << " OF:" << OF << endl;
    cout << "PR:" << PR << endl;

    for(auto i: label){
        cout << i.first << ":(" << i.second << ")" << memory[i.second] << endl;
    }

    return;
}

void START(){
    // cout << "START!!" << endl;
    cout << memory[PR] << endl;
    PR+=cmdList["START"];
    return;
}

void LD(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        GR[memory[PR+1][2] - '0'] = GR[memory[PR+2][2] - '0'];
    }else GR[memory[PR+1][2] - '0'] = stoi(memory[stoi(memory[PR+2])]);
    cout << "GR" << memory[PR+1][2] - '0' << " ← (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    PR+=cmdList["LD"];
    return;
}

void ST(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    memory[stoi(memory[PR+2])] = to_string(GR[memory[PR+1][2] - '0']);
    cout << "(" << memory[PR+2] << ") ← (GR" << memory[PR+1][2] << ")" << endl;
    PR += cmdList["ST"];
    return;
}

void LAD(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    GR[memory[PR+1][2] - '0'] = stoi(memory[PR+2]);
    cout << "(" << memory[PR+1] << ")  ← " << memory[PR+2] << endl;
    PR += cmdList["LAD"];
    return;
}

void ADDA(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        GR[memory[PR+1][2] - '0'] += GR[memory[PR+2][2] - '0'];
    }else GR[memory[PR+1][2] - '0'] += stoi(memory[stoi(memory[PR+2])]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") + (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    PR += cmdList["ADDA"];
    return;
}

void SUBA(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        GR[memory[PR+1][2] - '0'] -= GR[memory[PR+2][2] - '0'];
    }else GR[memory[PR+1][2] - '0'] -= stoi(memory[stoi(memory[PR+2])]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") - (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    if(GR[memory[PR+1][2] - '0'] < 0) SF = 1;
    else SF = 0;
    PR += cmdList["SUBA"];
    return;
}

void AND(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        GR[memory[PR+1][2] - '0'] &= GR[memory[PR+2][2] - '0'];
    }else GR[memory[PR+1][2] - '0'] &= stoi(memory[stoi(memory[PR+2])]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") and (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    if(GR[memory[PR+1][2] - '0'] < 0) SF = 1;
    else SF = 0;
    PR += cmdList["AND"];
    return;
}

void OR(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        GR[memory[PR+1][2] - '0'] |= GR[memory[PR+2][2] - '0'];
    }else GR[memory[PR+1][2] - '0'] |= stoi(memory[stoi(memory[PR+2])]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") or (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    if(GR[memory[PR+1][2] - '0'] < 0) SF = 1;
    else SF = 0;
    PR += cmdList["OR"];
    return;
}

void XOR(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        GR[memory[PR+1][2] - '0'] ^= GR[memory[PR+2][2] - '0'];
    }else GR[memory[PR+1][2] - '0'] ^= stoi(memory[stoi(memory[PR+2])]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") xor (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    if(GR[memory[PR+1][2] - '0'] < 0) SF = 1;
    else SF = 0;
    PR += cmdList["XOR"];
    return;
}

void SLA(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    GR[memory[PR+1][2] - '0'] <<= stoi(memory[PR+2]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") << (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    if(GR[memory[PR+1][2] - '0'] < 0) SF = 1;
    else SF = 0;
    PR += cmdList["SLA"];
    return;
}

void SRA(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    GR[memory[PR+1][2] - '0'] >>= stoi(memory[PR+2]);
    cout << "(" << memory[PR+1] << ") ← (" << memory[PR+1] << ") >> (" << memory[PR+2] << ")" << endl;
    if(GR[memory[PR+1][2] - '0'] == 0) ZF = 1;
    else ZF = 0;
    if(GR[memory[PR+1][2] - '0'] < 0) SF = 1;
    else SF = 0;
    PR += cmdList["SRA"];
    return;
}

void CPA(){
    cout << memory[PR] << " " << memory[PR+1] << " " << memory[PR+2] << endl;
    if(memory[PR+2][0] == 'G' && memory[PR+2][1] == 'R'){
        if(GR[memory[PR+1][2] - '0'] >= GR[memory[PR+2][2] - '0']){
            SF = 0;
        }else{
            SF = 1;
        }
        if(GR[memory[PR+1][2] - '0'] == GR[memory[PR+2][2] - '0']) ZF = 1;
        else ZF = 0;
    }else {
        if(GR[memory[PR+1][2] - '0'] >= stoi(memory[stoi(memory[PR+2])])){
            SF = 0;
        }else{
            SF = 1;
        }
        if(GR[memory[PR+1][2] - '0'] == stoi(memory[stoi(memory[PR+2])])) ZF = 1;
        else ZF = 0;
    }

    cout << "Checked ? (" << memory[PR+1] << ") > (" << memory[PR+2] << ")" << endl;
    PR += cmdList["SUBA"];
    return;
}

void JPL(){
    cout << memory[PR] << " " << memory[PR+1] << endl;
    if(SF == 0 && ZF == 0) {
        cout << "Jumped (" << memory[PR+1] << ")" << endl;
        PR = stoi(memory[PR+1]);
    }else {
        PR += cmdList["JPL"];
        cout << "Skipped JPL" << endl;
    }
    return;
}

void JMI(){
    cout << memory[PR] << " " << memory[PR+1] << endl;
    if(SF == 1) {
        cout << "Jumped (" << memory[PR+1] << ")" << endl;
        PR = stoi(memory[PR+1]);
    }else {
        PR += cmdList["JMI"];
        cout << "Skipped JMI" << endl;
    }
    return;
}

void JNZ(){
    cout << memory[PR] << " " << memory[PR+1] << endl;
    if(ZF == 0) {
        cout << "Jumped (" << memory[PR+1] << ")" << endl;
        PR = stoi(memory[PR+1]);
    }else {
        PR += cmdList["JNZ"];
        cout << "Skipped JNZ" << endl;
    }
    return;
}

void JZE(){
    cout << memory[PR] << " " << memory[PR+1] << endl;
    if(ZF == 1) {
        cout << "Jumped (" << memory[PR+1] << ")" << endl;
        PR = stoi(memory[PR+1]);
    }else {
        PR += cmdList["JZE"];
        cout << "Skipped JZE" << endl;
    }
    return;
}

void JUMP(){
    cout << memory[PR] << " " << memory[PR+1] << endl;
    PR = stoi(memory[PR+1]);
    return;
}

bool RET(){
    cout << memory[PR] << endl;
    if(SP.empty()){
        return true;
    }
    PR = SP.back();
    SP.pop_back();
    return false;
}

int main(int argc, char *argv[]){

    if(argc != 2){
        cerr << "Usage: " << argv[0] << " inputfile" << endl;
        return -1;
    }

    ifstream fp(argv[1]);
    if(fp.fail()){
        cerr << "Failed to open file." << endl;
        return -1;
    }

    // ファイル読み込み
    for(int i = 0; !fp.eof();i++){
        fp >> memory[i];
    }

    // ラベル検出
    for(int i = 0; memory[i] != "END"; i++){
        bool flag = false;
        // cout << memory[i] << endl;
        for(auto j: cmdList){
            if(memory[i] == j.first){
                i+=j.second - 1;
                flag = true;
                break;
            }
        }
        if(flag) continue;
        if(memory[i] == "DC" || memory[i] == "DS"){
            label[memory[i-1]] = i + 1;
            i+=2 - 1;
            continue;
        }
        label[memory[i]] = i;
    }

    // ラベル置換
    int cnt = 0;
    for(int i=0; cnt == 0 && memory[i] != "RET";i++){
        if(memory[i] == "CALL") cnt++;
        if(memory[i] == "RET") cnt--;
        for(auto j: label){
            if(j.first == memory[i]){
                memory[i] = to_string(j.second);
            }
        }
    }

    // メモリ番地と中身の表示
    for(int i=0;memory[i] != "END";i++){
        cout << i << " " << memory[i] << endl;
    }

    // 実行
    bool endFlag = false;
    while(!endFlag){

        printStatus();

        cout << "--------------------------------------------------------------" << endl;
        // START
        if(memory[PR] == "START") {
            START();
            continue;
        }

        // LD
        if(memory[PR] == "LD") {
            LD();
            continue;
        }

        // ST
        if(memory[PR] == "ST") {
            ST();
            continue;
        }

        // LAD
        if(memory[PR] == "LAD") {
            LAD();
            continue;
        }

        // ADDA
        if(memory[PR] == "ADDA"){
            ADDA();
            continue;
        }

        // SUBA
        if(memory[PR] == "SUBA"){
            SUBA();
            continue;
        }

        // AND
        if(memory[PR] == "AND"){
            AND();
            continue;
        }

        // OR
        if(memory[PR] == "OR"){
            OR();
            continue;
        }

        // XOR
        if(memory[PR] == "XOR"){
            XOR();
            continue;
        }

        // SLA
        if(memory[PR] == "SLA" || memory[PR] == "SLL"){
            SLA();
            continue;
        }

        // SRA
        if(memory[PR] == "SRA" || memory[PR] == "SRL"){
            SRA();
            continue;
        }

        // CPA
        if(memory[PR] == "CPA"){
            CPA();
            continue;
        }

        // JPL
        if(memory[PR] == "JPL"){
            JPL();
            continue;
        }

        // JMI
        if(memory[PR] == "JMI"){
            JMI();
            continue;
        }

        // JNZ
        if(memory[PR] == "JNZ"){
            JNZ();
            continue;
        }

        // JZE
        if(memory[PR] == "JZE"){
            JZE();
            continue;
        }

        // JUMP
        if(memory[PR] == "JUMP"){
            JUMP();
            continue;
        }

        // RET
        if(memory[PR] == "RET") {
            endFlag = RET();
            continue;
        }

        // ラベル

        PR++;
    }

    printStatus();

    cout << "End." << endl;

    return 0;
}
