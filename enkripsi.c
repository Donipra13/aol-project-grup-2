#include <stdio.h>
#include <string.h>
void enkrip(char str[], int shiftKey){
    for (int i=0; str[i]!='\0'; i++) {
        char ch=str[i];
        str[i]= ((ch-32+shiftKey)%95)+32;  //Geser character dengan ditambahkan sebanyak shiftkey

    }
}

void dekrip(char str[], int shiftKey){
    for (int i=0; str[i]!='\0'; i++) {          //character digeser dengan dikurangkan sebanyak shiftkey
        char ch=str[i];
        str[i]= ((ch-32-shiftKey+95)%95)+32;

    }
}

void display_enk(){                 //tampilkan hasil enkripsi
    printf("Masukkan string: ");
    char string[101];
    fgets(string,sizeof(string),stdin);
    string[strcspn(string,"\n")]='\0';

    enkrip(string, 3);

    printf("\nEnkripsi String: %s\n\n",string);
}

void display_dek(){                //tampilkan hasil dekripsi
    printf("Masukkan string: ");
    char string[101];
    fgets(string,sizeof(string),stdin);
    string[strcspn(string,"\n")]='\0';

    dekrip(string, 3);

    printf("\nDekripsi String: %s\n\n",string);
}

int main(){
    int menu;
    printf("=========================================\n          Enkripsi dan Dekripsi          \n=========================================\n");
    do{
        printf("Pilih Menu: \n1. Enkripsi\n2. Dekripsi\n3. Keluar\n");
        scanf("%d",&menu);getchar();
        switch(menu){
            case 1:
                display_enk();  //lakukan ekripsi
            break;

            case 2:
                display_dek();  //lakukan dekripsi
            break;
            case 3 :
                return 0;   //keluar menu
            break;
        }
        if(menu>3||menu<1){
            printf("\nAngka tidak valid\n");
        }
    }while(menu!=3);
}
