#include <iostream>
#include "gameran.h"
#define MAX 100
using namespace std;
int toadox[MAX]={0};
int toadoy[MAX]={0};
int soluongdot =4;
int xqua=-1;
int yqua=-1;
//nguyên mẫu hàm
void ve_tuong();
bool game_over();
void play();
void khoi_tao_ran();
void ve_ran();
void di_chuyen_ran(int x,int y);
void khoi_tao_qua();
void ve_qua();
bool kiemtrarananqua();
void ran_an_qua();
bool ran_de_qua();
bool ran_can_than();
bool qua_dung_tuong();
int main(){
    srand(time(NULL));//tạo chỉ số mới cho rand()
    play();
    _getch();
}
//build game
void ve_tuong(){
for (int x=10;x<=100;x++){
    gotoXY(x,1);
    cout << "+";
    gotoXY(x,24);
    cout << "+";
}
for (int y=1;y<=24;y++){
    gotoXY(10,y);
    cout << "+";
    gotoXY(100,y);
    cout << "+";
}
}
void play(){
    ShowCur(0);
    SetColor(2);
    ve_tuong();
    khoi_tao_ran();
    khoi_tao_qua();
    ve_qua();
    int x=toadox[0];
    int y=toadoy[0];
    int check;//0 đi xuống
              //1 đi lên
              // 2 qua phải
              //3 qua trái
    while(true){
        gotoXY(toadox[soluongdot],toadoy[soluongdot]);
        cout << " ";
        ve_ran();
        // tạo bảng điều khiển rắn
        if (_kbhit()){
            char c = _getch();
            if (c==-32){
                c=_getch();
                if (c==72 && check !=0){
                    check =1;
                }else if (c==80 && check!=1){
                    check=0;
                }else if (c==75 && check!=2){
                    check =3;
                }else if (c==77 && check!=3){
                    check=2;
                }
            }

        }
        if (check==0){
            y++;
        }else if (check==1){
            y--;
        }else if (check==2){
            x++;
        }else if (check==3){
            x--;
        }
        //kết thúc game
        if (game_over()){
            gotoXY(50,13);
                cout << "Game over";
            break;
        }
        ran_an_qua();// xử lý cho rắn ăn quả
        di_chuyen_ran(x,y);//tốc độ rắn
        Sleep(100);//tốc độ rắn
}
}
void khoi_tao_ran(){//tạo số lượng đốt và vị trí tọa độ ban đầu của rắn
    SetColor(11);
    int x_khoi_tao=50;
    int y_khoi_tao=12;
    for (int i=0;i<soluongdot;i++){
        toadox[i]=--x_khoi_tao;
        toadoy[i]=y_khoi_tao;
    }
}
void ve_ran(){// vẽ rắn
    for (int i=0;i<soluongdot;i++){
    gotoXY(toadox[i],toadoy[i]);
    if (i==0){
        cout << char (219);
    }else{
        cout << "o";
    }
}
}
void di_chuyen_ran(int x,int y){
    for (int i=soluongdot;i>0;i--){
        toadox[i]=toadox[i-1];
        toadoy[i]=toadoy[i-1];
    }
    toadox[0]=x;
    toadoy[0]=y;
}
bool game_over(){// kiểm tra khi nào thua
    if (toadox[0]==10 || toadox[0]==100 || toadoy[0]==1 || toadoy[0]==24){// khi đụng tường
        return true;
    }
    return false;
    if (ran_can_than()){//khi rắn tự cắn bản thân
        return true;
    }
    return false;
}
void khoi_tao_qua(){// sử dụng công thức (b-a+1)+1 trong hàm rand để tạo ngẫu nhiên vị trí của quả
    do{
    xqua=rand()%(100-10+1)+10;
    yqua=rand()%(24-1+1)+1;
}while (ran_de_qua() && qua_dung_tuong()) ;// trong khi một trong 2 điều kiện này đúng thì sẽ thực hiện vòng do bên trên
}
void ve_qua(){// vẽ quả
    gotoXY(xqua,yqua); cout << "o";
}
bool kiemtrarananqua(){//kiểm tra tọa độ đầu của rắn có trùng với tọa độ của quả hay không
    if (toadox[0]==xqua && toadoy[0]==yqua){
        return true;
}
return false;
}
void ran_an_qua(){//tăng số lượng đốt khi rắn ăn quả đồng thời tạo ra mồi mới
    if (kiemtrarananqua()){
        soluongdot++;// điều kiện đúng thì số lượng đốt tăng lên
        khoi_tao_qua();// tạo quả mới
        ve_qua();// tăng đốt
}
}
bool ran_de_qua(){//để quả không xuất hiện trùng với các đốt của rắn
    for (int i=0;i<soluongdot;i++){
    if(xqua==toadox[i]&&yqua==toadoy[i]){
        return true;
    }
}
return false;
}
bool ran_can_than(){// kiểm tra khi rắn cắn trúng bản thân nó
    for (int i=0;i<soluongdot;i++){
        if (toadox[0]==toadox[i] && toadoy[0]==toadoy[i]){
            return true;
        }
    }
    return false;
}
bool qua_dung_tuong(){// kiểm tra quả có xuất hiện ở tường hay không (fix lỗi sau test)
        if (xqua==10 || xqua==100 || yqua==1 || yqua==24 ){
            return true;
        }
        return false;
}
