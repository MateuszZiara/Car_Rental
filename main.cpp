#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>
struct user
{
    char login[100];
    char password[100];
    int id;
};
struct car
{

    char model[100];
    int id;
    int owner;
    bool rented;
    int daily;
    char rent_date[12];
    bool rent_bufor;
    char rent_login[100];
};
int loginMenu(int x)
{
    printf("[1] Zaloguj sie \n");
    printf("[2] Zarejestruj sie \n");
    printf("[3] Wyjdz \n");
    scanf("%d",&x);
    return x;
}
int checkLogin(char *login, char *pass, struct user *userList, int userNumber)
{
    int i;
    for(i = 0; i < userNumber; ++i)
    {
        if((strcmp(userList[i].login,login) == 0)  && (strcmp(userList[i].password,pass) == 0))
            return i;
    }
    return -1;
}

struct user add(char *login, char *pass, struct user *userList, int userNumber)
{
    struct user bufor;
    strcpy(bufor.login,login);
    strcpy(bufor.password,pass);
    bufor.id = userNumber - 1;
    return bufor;
};
void loginSet(char *login, char *pass)
{
    printf("Login: ");
    scanf("%s",login);
    printf("Haslo: ");
    scanf("%s",pass);
}

int carMenu(int x)
{
    printf("[1] Dodaj samochod \n");
    printf("[2] Usun samochod \n");
    printf("[3] Lista samochodow \n");
    printf("[4] Wyszukaj samochod \n");
    printf("[5] Dane samochodu \n");
    printf("[6] Wypozycz samochod \n");
    printf("[7] Zaakceptuj wypozyczenie / Zobacz wypozyczone samochody\n");
    printf("[8] Wyloguj sie \n");
    scanf("%d",&x);
    return x;
}
void carSet(char *model, int *daily)
{
    printf("Model: ");
    scanf("%s",model);
    printf("Cena za dzien: ");
    scanf("%d",daily);
}
struct car addCar(char *model, struct car *carList, int carNumber, int loginID, int daily)
{
    struct car bufor;
    strcpy(bufor.model,model);
    bufor.id = carNumber - 1;
    bufor.owner = loginID;
    bufor.rented = false;
    bufor.rent_bufor = false;
    bufor.daily = daily;
    return bufor;
};
bool carDelete(struct car *carList, int carNumber, int loginID)
{
    int i;
    for(i = 0; i < carNumber; ++i)
    {
        if(carList[i].owner == loginID)
        {
            printf("%d: Model samochodu: %s ID samochodu: %d \n",i,carList[i].model,carList[i].id);
        }
    }
    printf("Podaj ID samochodu, ktory chcesz usunac (wpisz -1 aby anulowac): ");
    int x;
    scanf("%d",&x);
    if(x >= 0)
    {
        if(carList[x].owner == loginID)
        {
                for(i = x; i < carNumber; ++i)
                {
                    carList[x] = carList[x+1];
                }
                carList[x].id -= 1;
                free(&carList[carNumber - 1]);
                return true;
        }
    }
    return false;
}
void carPrint(struct car *carList, int carNumber, struct user *userList)
{
    int i;
    for(i = 0; i < carNumber; ++i)
    {
        printf("%d. Model: %s Wlasciciel: %s ID: %d \n",i+1,carList[i].model,userList[carList[i].owner].login,carList[i].id);
    }
}
bool checkUsername(char *login, struct user *userList, int userNumber)
{
    int i;
    for(i = 0; i < userNumber; ++i)
    {
        if(strcmp(userList[i].login,login) == 0)
        {
            return false;
        }
    }
    return true;
}
void carSarch(struct car *carList, int carNumber, struct user *userList)
{
    printf("Po czym chcesz wyszukac samochod? \n");
    printf("[1] Model \n");
    int x,i;
    scanf("%d",&x);
    switch(x)
    {
    case 1:
        {
            char bufor[100];
            system("CLS");
            printf("Podaj model: ");
            scanf("%s",bufor);
            for(i = 0; i < carNumber; ++i)
            {
                if(strcmp(bufor,carList[i].model) == 0)
                {
                    printf("Model: %s Wlasciciel: %s ID: %d \n",carList[i].model, userList[carList[i].owner].login,carList[i].id);
                }
            }
            break;
        }
    }
}
void carDetails(struct car* carList, struct user *userList, int carNumber)
{
    printf("Podaj ID samochodu: ");
    int x;
    scanf("%d",&x);
    system("CLS");
    if(x < carNumber)
    {
    printf("Model: %s\n",carList[x].model);
    printf("ID: %d\n",carList[x].id);
    printf("Wlasciciel: %s\n",userList[carList[x].owner].login);
    printf("Cena za dzien: %d\n",carList[x].daily);
    if(carList[x].rented == false)
    {
        printf("Wypozyczony: Nie \n");
    }
    if(carList[x].rented == true)
    {
        printf("Wypozyczony: Tak \n");
    }
    system("PAUSE");
    system("CLS");

    }
}
void rentCar(struct car* carList, struct user *userList, int loginID,int carNumber)
{
    printf("Podaj ID samochodu: ");
    int x;
    scanf("%d",&x);
if(x < carNumber)
{
    if(carList[x].rented == false)
    {
        printf("Do kiedy chcesz wynajac samochod (poprawny zapis dd-mm-rrrr): ");
        scanf("%s",carList[x].rent_date);
        carList[x].rent_bufor = true;
        strcpy( carList[x].rent_login,userList[loginID].login);
        system("CLS");
        printf("Prosba o wypozyczenie samochodu wyslana do wlasciciela. Prosimy o cierpliwosc. Status mozesz zobaczyc pod numerem 7.\n");
    }
    else
        printf("Nie mozesz wypozyczyc tego samomochdu \n");
}
}
void showRent(struct car* carList, int carNumber, struct user *userList, int loginID)
{
    printf("Twoje wypozyczone samochody:\n");
    int x;
    for(x = 0; x < carNumber; ++x)
    {
        if(carList[x].rented == true || carList[x].rent_bufor == true)
        {
            if(strcmp(userList[loginID].login,carList[x].rent_login) == 0)
            {
                if(carList[x].rent_bufor == true)
                {
                    printf("%d Model: %s ID: %d Status: Oczekujacy \n",x,carList[x].model,carList[x].id);
                }
                else
                {
                    printf("%d Model: %s ID: %d Status: Zatwierdzony do: %s \n",x,carList[x].model,carList[x].id,carList[x].rent_date);
                }
            }
        }
    }
    system("PAUSE");
    system("CLS");
    bool ready = false;
while(ready == false)
{
    printf("Samochody ktore wypozyczasz / czekaja na zaakceptowanie: \n");
    for(x = 0; x < carNumber; ++x)
    {
        if(carList[x].owner == loginID)
        {
            if(carList[x].rent_bufor == true || carList[x].rented == true)
            {
                if(carList[x].rent_bufor == true )
                    printf("%d Model: %s ID: %d Status: Oczekujacy Login: %s Do dnia: %s\n",x,carList[x].model,carList[x].id,carList[x].rent_login,carList[x].rent_date);
                else
                    printf("%d Model: %s ID: %d Status: Zaakceptowany Login: %s Do dnia: %s\n",x,carList[x].model,carList[x].id,carList[x].rent_login,carList[x].rent_date);
            }
        }
    }
    printf("[1] Zaakceptuj samochod \n");
    printf("[2] Wyjdz \n");
    int choose, id;
    scanf("%d",&choose);
    switch(choose)
    {
    case 1:
        {
            printf("Podaj ID samochodu: ");
            scanf("%d",&id);
            if(id < carNumber)
            {
            if(carList[id].owner == loginID)
            {
                if(carList[id].rent_bufor == true)
                {
                    system("CLS");
                    carList[id].rent_bufor = false;
                    carList[id].rented = true;
                    printf("Udalo sie zaakceptowac samochod \n");
                }
            }
            break;
            }
        }
    case 2:
        {
            ready = true;
            system("CLS");
            break;
        }
    }

}


}
int main()
{

    //Wczytywanie z pliku

    struct user *userList;
    struct car *carList;
    int choose,userNumber = 0,i,loginID, carNumber = 0;
    bool logTrue = false;
    char login[100], model[100];
    char pass[100];
    int daily;
    //Wczytywanie z pliku
    FILE *userFile;
    userFile = fopen("zmienne.txt", "r+");

    fscanf(userFile,"Liczba danych: %d",&userNumber);
    fscanf(userFile,"Liczba samochodow: %d",&carNumber);
    fclose(userFile);
    printf("Liczba danych: %d \n",userNumber);
    printf("Liczba samochodow: %d \n",carNumber);
    system("PAUSE");
    userFile = fopen("user.txt", "r+");
    if(userNumber > 0)
    {
        userList = (user *)malloc(userNumber * sizeof(struct user));
        fread(userList, sizeof(struct user) * userNumber, 1, userFile);
    }
    fclose(userFile);
    userFile = fopen("cars.txt","r+");
    if(carNumber > 0)
    {
        carList = (car*) malloc(carNumber * sizeof(struct car));
        fread(carList, sizeof(struct car) * carNumber, 1, userFile);
    }
    fclose(userFile);
for(;;)
{
    while(!logTrue)
    {
        choose = loginMenu(choose);
        system("CLS");
        switch(choose)
        {
        case 1:
            loginSet(login,pass);
            loginID = checkLogin(login,pass,userList,userNumber);
            if(loginID > -1)
            {
                logTrue = true;
            }
            else
                printf("Logowanie nie powiodlo sie \n");
            break;

        case 2:
            {
            loginSet(login,pass);
            if(checkUsername(login,userList,userNumber))
            {
                userNumber++;
                //userList = addMem(userNumber);
                if(userNumber == 1)
                {
                    userList = (user *) malloc(sizeof(struct user));
                }

                if(userNumber > 1)
                {
                    userList = (user *) realloc(userList, userNumber * sizeof(struct user));
                    //userList = rea(sizeof(struct user)*userNumber);
                }
                userList[userNumber-1] = add(login,pass,userList,userNumber);
                system("CLS");
            }
            else
                printf("Nazwa uzytkownika zajeta \n");

            break;
            }
        case 3:
            {
                userFile = fopen("zmienne.txt", "w+");
                fprintf(userFile,"Liczba danych: %d",userNumber);
                fprintf(userFile,"Liczba samochodow: %d",carNumber);
                fclose(userFile);
                userFile = fopen("user.txt", "w+");
                fwrite(userList,sizeof(struct user) * userNumber,1,userFile);
                fclose(userFile);
                userFile = fopen("cars.txt", "w+");
                fwrite(carList,sizeof(struct car) * carNumber,1,userFile);
                fclose(userFile);
                free(userList);
                free(carList);
                return 0;
            }
        }


    }
    choose = carMenu(choose);
    switch(choose)
    {
        case 1:
            {
                carSet(model,&daily);
                carNumber++;
                if(carNumber == 1)
                {
                    carList = (car *) malloc(sizeof(struct car));
                }
                else if(carNumber > 1)
                {
                    carList = (car *) realloc(carList,carNumber * sizeof(struct car));
                }

                carList[carNumber - 1] = addCar(model,carList,carNumber,loginID,daily);
                system("CLS");
                break;
            }
        case 2:
            {
                if(carDelete(carList,carNumber,loginID))
                    carNumber--;
                system("CLS");
                break;
            }
        case 3:
            {
                carPrint(carList,carNumber,userList);
                system("PAUSE");
                system("CLS");
                break;
            }
        case 4:
            {
                carSarch(carList,carNumber,userList);
                system("PAUSE");
                system("CLS");
                break;
            }
        case 5:
            {
                carDetails(carList,userList,carNumber);
                break;
            }
        case 6:
            {
                rentCar(carList,userList,loginID,carNumber);
                break;
            }
        case 7:
            {
                showRent(carList,carNumber,userList,loginID);
                break;
            }
        case 8:
            {
                logTrue = false;
                break;
            }
    }
}
return 0;
}
