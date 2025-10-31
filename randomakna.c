#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    srand(time(NULL));
    int m[9][9] = {0};
    int aknaszam = 10;
    int i = 0;
    while (i < aknaszam){
        int random = rand() % 81;
        if ( m[random/9][random%9] != 8){
            m[random/9][random%9] = 8;
            i += 1;
            }
    }
    for (int sor = 0; sor < 9; sor++){
        for (int oszlop = 0; oszlop < 9; oszlop++){
            if (m[sor][oszlop] != 8){
            if (sor == 0 && oszlop == 0){
                if(m[sor+1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
            }
            else if (sor == 0 && oszlop == 8){
                if(m[sor+1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
            }
            else if (sor == 9 && oszlop == 0){
                if(m[sor][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop] == -1)
                    m[sor][oszlop] += 1;
            }
            else if (sor == 8 && oszlop == 8){
                if(m[sor-1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
            }
            else if(sor == 0 && oszlop != 0){
                if(m[sor+1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
            }
            else if(sor == 8 && oszlop != 0){
                if(m[sor-1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
            }
            else if(oszlop == 0 && sor != 0){
                if(m[sor][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
            }
            else if(oszlop == 8 && sor != 0){
                if(m[sor][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
            }
            else{   
                if(m[sor+1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor+1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor-1][oszlop+1] == 8)
                    m[sor][oszlop] += 1;
                if(m[sor][oszlop-1] == 8)
                    m[sor][oszlop] += 1;
                }
    }}
}
    
    
    for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                printf("%d  ", m[i][j]);
            }
            printf("\n");
        }
}