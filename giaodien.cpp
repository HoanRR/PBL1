#include <stdio.h>
#include <windows.h>

void veKhung(int x, int y, int width, int height, short color, int offsetX, int offsetY) {
    x += offsetX;
    y += offsetY;
    setColor(color, 0);

    //Ranh gioi tren
    gotoxy(x, y);
    printf("+"); //Goc tren ben trai
    for (int i = 0; i < width - 2; i++) printf("-"); //Duong ke ngang
    printf("+"); //Goc tren ben phai

    //Cac ranh gioi 2 ben
    for (int i = 1; i < height - 1; i++) {
        gotoxy(x, y + i);
        printf("|"); //Duong thang
        gotoxy(x + width - 1, y + i);
        printf("|"); //Duong thang
    }

    //Ranh gioi duoi
    gotoxy(x, y + height - 1);
    printf("+"); //Goc duoi ben trai
    for (int i = 0; i < width - 2; i++) printf("-"); //Duong ke ngang
    printf("+"); //Goc duoi ben phai

    setColor(15, 0);
}

int main(){
    veKhung(5,5,5,2,11,5,5);
}
