#include<iostream>
#include<stdio.h>
#include<cstring>
#include<fstream>
#include<sstream>
#include<stdlib.h>


using namespace std;

struct ogrenci
{
    char ogrno[15];
    char ad[30];
    char soyad[30];
    struct ders* dersdugumu;
    struct ogrenci* sonraki;
};

struct ders
{
    char derskodu[10];
    char dersadi[50];
    struct ders* sonraki;
};

int bul(struct ogrenci** dugum, char numara[30]);
struct ogrenci* kisi_ekle(struct ogrenci** dugum, char numara[30], char isim[30], char soyad[30],char derskodu[30], char dersadi[30]);
struct ogrenci* listeKur(struct ogrenci** dugum);
struct ogrenci* ara(struct ogrenci* dugum,char key[30]);
struct ogrenci* ogrenciSil(struct ogrenci** dugum,char numara[30]);
struct ogrenci* dersSil(struct ogrenci** dugum, char numara[30],char kod[10]);
void listele(struct ogrenci* dugum);
void kesisimBul(struct ogrenci* dugum,char kod1[10],char kod2[10]);
void dosyayaYaz(struct ogrenci* dugum);

int main()
{
    struct ogrenci* dugum = nullptr;
    dugum = listeKur(&dugum);
    struct ogrenci* test = dugum;

    char secim;
    bool cikis = true;
    char key[30], kod[30];
    while (cikis)
    {
        cout<<"\n\n\n\t***ISLEM MENUSU***\n";
        cout<<"Yapmak istediginiz islem icin asagidaki durumlardan birini giriniz.\n";
        cout<<"Arama yapma: 1\nDers silme : 2\nKesisim bulma : 3\nListeyi ekrana yazdirma : 4\n";
        cout<<"Ogrenci silme : 5\nDosyaya yazma : 6\nCikis yapma : 7\n\n";
        cin>>secim;
        switch (secim)
        {
        case '1':
            system("CLS");
            cout<<"Arama yapmak icin ogrenci numarasi veya soyadi giriniz : ";
            cin>>key;
            test = ara(dugum, key);

            if (test == nullptr)
            {
                cout<<"\nBulunamadi";
                test = dugum;
            }
            else
            {
                if (atoi(dugum->ogrno) == atoi(test->ogrno))
                {
                    test = test;
                    struct ders* temp;
                    temp = test->dersdugumu;
                    cout<<endl;
                    cout << test->ogrno <<" ";
                    cout << test->ad    <<" ";
                    cout << test->soyad <<" ";
                    while (temp != nullptr)
                    {
                    cout << temp->dersadi <<" ";
                    cout << temp->derskodu<<" ";
                    temp = temp->sonraki;
                    }
                    test = dugum;
                }
                else
                {
                    test = test->sonraki;
                    struct ders* temp;
                    temp = test->dersdugumu;
                    cout<<endl;
                    cout << test->ogrno <<" ";
                    cout << test->ad    <<" ";
                    cout << test->soyad <<" ";
                    while (temp != nullptr)
                    {
                    cout << temp->dersadi <<" ";
                    cout << temp->derskodu<<" ";
                    temp = temp->sonraki;
                    }
                    test = dugum;
                }
            }

            break;
        case '2':
            system("CLS");
            cout<<"Ders silmek icin ogrenci numarasi veya soyadi giriniz : ";
            cin>>key;
            cout<<"Ders kodu giriniz : ";
            cin>>kod;
            test = dersSil(&test,key,kod);

            if (test == nullptr)
            {
                cout<<"\nBulunamadi";
                test = dugum;
            }
            else
            {
                dugum = test;
                cout<<"Basari ile silindi.\n";
            }
            break;
        case '3':
            system("CLS");
            cout<<"Kesisim icin ilk kodu giriniz : ";
            cin>>key;
            cout<<"Kesisim icin ikinci kodu giriniz : ";
            cin>>kod;
            kesisimBul(dugum, key, kod);
            break;
        case '4':
            system("CLS");
            listele(dugum);
            break;
        case '5':
            system("CLS");
            cout<<"Ogrenci silmek icin ogrenci numarasi giriniz : ";
            cin>>key;
            test = ogrenciSil(&test,key);

            if (test == nullptr)
            {
                cout<<"\nBulunamadi";
                test = dugum;
            }
            else
            {
                dugum = test;
                cout<<"Basari ile silindi.\n";
            }

            break;
        case '6':
            system("CLS");
            dosyayaYaz(dugum);
            cout<<"Basari ile dosya olusturuldu.\n";
            break;
        case '7':
            cikis = false;
            break;
        default:
            cout<<"Yanlis secim yaptiniz tekrar deneyin !";
            break;
        }
    }
    return 0;
}

void dosyayaYaz(struct ogrenci* dugum)
{
    ofstream dosya("ogrenciler.txt");
    int count;
    struct ogrenci* iter = dugum;
    struct ders* temp;
    string satir;
    if ( ! dosya.is_open())
        cout<<"\ndosya acilamadi\n";

    while (iter != nullptr)
    {
        satir = "";
        temp = iter->dersdugumu;
        count = 0;
        while (temp != nullptr)
        {
            if(count == 0)
            {
                satir.append(iter->ogrno);
                satir.append(" ");
                satir.append(iter->ad);
                satir.append(" ");
                satir.append(iter->soyad);
                satir.append(" ");
                count = 1;
            }
            satir.append(temp->dersadi);
            satir.append(" ");
            satir.append(temp->derskodu);
            satir.append(" ");
            temp = temp->sonraki;
        }
        satir.append("\n");
        dosya << satir;
        iter = iter->sonraki;
    }
    dosya.close();
}

int bul(struct ogrenci** dugum, char numara[30])
{
    struct ogrenci* current = *dugum;
    while (current != nullptr)
    {
        if (atoi(current->ogrno) == atoi(numara))
            return 1;
        current = current->sonraki;
    }
    return 0;
}

struct ogrenci* kisi_ekle(struct ogrenci** dugum, char numara[30], char isim[30], char soyad[30],char derskodu[30], char dersadi[30])
{
    //cout<<numara<<" "<<isim<<" "<<soyad<<" "<<derskodu<<" "<<dersadi<<endl;
    struct ogrenci* iter;

    // var mi varsa ders ekle
    if (bul(dugum, numara))
    {
        iter = *dugum;
        while (strcmp(iter->ogrno, numara)!=0)
            iter = iter->sonraki;
        struct ders* temp = iter->dersdugumu;
        while (temp->sonraki != nullptr)
        {
            temp = temp->sonraki;
        }
        temp->sonraki = new struct ders;
        strcpy(temp->sonraki->dersadi,dersadi);
        strcpy(temp->sonraki->derskodu,derskodu);
        temp->sonraki->sonraki = nullptr;
    }

    // yoksa yeni ogrenci olustur siraya sok
    else
    {
        struct ogrenci* yeni = new struct ogrenci;
        iter = *dugum;
        strcpy(yeni->ogrno, numara);
        strcpy(yeni->ad, isim);
        strcpy(yeni->soyad, soyad);
        yeni->sonraki = nullptr;

        yeni->dersdugumu = new struct ders;
        strcpy(yeni->dersdugumu->dersadi,dersadi);
        strcpy(yeni->dersdugumu->derskodu,derskodu);
        yeni->dersdugumu->sonraki = nullptr;

        // siraya sok
        if (iter == nullptr) // ilk ogrenci
        {
            *dugum = yeni;
        }
        else
        {
            while (iter->sonraki != nullptr && atoi(iter->sonraki->ogrno) < atoi(numara))
                iter = iter->sonraki;

            yeni->sonraki = iter->sonraki;
            iter->sonraki = yeni;
        }
    }
    return *dugum;
}

struct ogrenci* listeKur(struct ogrenci** dugum)
{
    fstream read;
    string satir, kelime;
    int i=0;
    char files[3][50] = {"mat101.txt","fiz101.txt","eng101.txt"};
    char derskod[50], dersad[50], ad[50], soyad[50], numara[50];

    for ( i = 0; i < 3; i++)
    {
        read.open(files[i]);

        getline(read, satir);
        stringstream s(satir);
        s>>derskod;
        s>>dersad;

        while (getline(read, satir))
        {
            stringstream s(satir);
            s>>numara;
            s>>ad;
            s>>soyad;
            *dugum = kisi_ekle(dugum, numara,ad, soyad, derskod, dersad);
            ogrenci** temp = dugum;
        }
        read.close();
    }
    return *dugum;
}

struct ogrenci* ara(struct ogrenci* dugum,char anahtar[30])
{
    int i = 0;
    if (anahtar[0] <= '9' && anahtar[0] >= '0')
    {
        if (atoi(dugum->ogrno) == atoi(anahtar))
            return dugum;

        while (dugum->sonraki != nullptr)
        {
            if (atoi(dugum->sonraki->ogrno) == atoi(anahtar))
                return dugum;

            dugum = dugum->sonraki;
        }
    }
    else
    {
        for (i = 0; i < strlen(anahtar);i++)
        {
            anahtar[i] = toupper(anahtar[i]);

        }
        while (dugum->sonraki != nullptr)
        {
            if (strcmp(dugum->sonraki->soyad,anahtar) == 0)
                return dugum;

            dugum = dugum->sonraki;
        }
    }
    return nullptr;
}

struct ogrenci* ogrenciSil(struct ogrenci** dugum,char numara[30])
{
    struct ogrenci* kontrol = ara(*dugum,numara) ;
    if (kontrol != nullptr && kontrol->sonraki != nullptr)
    {
        struct ogrenci* temp;
        //Ilk öðrenci ise
        if (atoi((*dugum)->ogrno) == atoi(numara) )
        {
            while ((*dugum)->dersdugumu != nullptr)
            {
                struct ders* gecici = (*dugum)->dersdugumu;
                (*dugum)->dersdugumu = (*dugum)->dersdugumu->sonraki;
                delete gecici;
            }
            temp = (*dugum);
            (*dugum) = (*dugum)->sonraki;
            delete temp;
            return *dugum;
        }
        else
        {
            while (kontrol->sonraki->dersdugumu != nullptr)
            {
                struct ders* gecici = kontrol->sonraki->dersdugumu;
                kontrol->sonraki->dersdugumu = kontrol->sonraki->dersdugumu->sonraki;
                delete gecici;
            }
            temp = kontrol->sonraki;
            kontrol->sonraki = kontrol->sonraki->sonraki;
            delete temp;
            return *dugum;
        }
    }
    return nullptr;
}

struct ogrenci* dersSil(struct ogrenci** dugum, char numara[30],char kod[10])
{
    struct ogrenci* kontrol = ara(*dugum,numara) ;
    if (kontrol != nullptr && kontrol->sonraki != nullptr)
    {
        struct ders* temp;
        struct ders* iter;
        if (atoi((*dugum)->ogrno) == atoi(numara))
        {
            if (strcmp((*dugum)->dersdugumu->derskodu,kod) == 0)
            {
                temp = (*dugum)->dersdugumu;
                (*dugum)->dersdugumu = (*dugum)->dersdugumu->sonraki;
                delete temp;
                return ogrenciSil(dugum,numara);
            }
            else
            {
                iter = (*dugum)->dersdugumu;
                while (iter->sonraki != nullptr && strcmp(iter->sonraki->derskodu,kod) != 0)
                    iter = iter->sonraki;
                if (iter->sonraki == nullptr)
                    return nullptr;
                temp = iter->sonraki;
                iter->sonraki = iter->sonraki->sonraki;
                delete temp;
                return *dugum;
            }
        }

        if (strcmp(kontrol->sonraki->dersdugumu->derskodu,kod) == 0)
        {
            temp = kontrol->sonraki->dersdugumu;
            kontrol->sonraki->dersdugumu = kontrol->sonraki->dersdugumu->sonraki;
            delete temp;
            return ogrenciSil(dugum,numara);
        }
        else
        {
            iter = kontrol->sonraki->dersdugumu;
            while (iter->sonraki != nullptr && strcmp(iter->sonraki->derskodu,kod) != 0)
                iter = iter->sonraki;
            if (iter->sonraki == nullptr)
                return nullptr;
            temp = iter->sonraki;
            iter->sonraki = iter->sonraki->sonraki;
            delete temp;
            return *dugum;
        }
    }
    return nullptr;
}
void listele(struct ogrenci* dugum)
{
    int count;
    struct ogrenci* iter = dugum;
    struct ders* temp;
    while (iter != nullptr)
    {
        temp = iter->dersdugumu;
        count = 0;
        while (temp != nullptr)
        {
            if(count == 0)
            {
                cout<<endl;
                cout << iter->ogrno <<" ";
                cout << iter->ad    <<" ";
                cout << iter->soyad <<" ";
                count = 1;
            }
            cout << temp->dersadi <<" ";
            cout << temp->derskodu<<" ";
            temp = temp->sonraki;
        }
        iter = iter->sonraki;
    }
}
void kesisimBul(struct ogrenci* dugum,char kod1[10],char kod2[10])
{
    int count,kontrol;
    struct ogrenci* iter = dugum;
    struct ders* temp;
    while (iter != nullptr)
    {
        temp = iter->dersdugumu;
        count = 0;
        kontrol = 0;
        while (temp != nullptr)
        {
            if ((strcmp(temp->derskodu,kod1) == 0) || (strcmp(temp->derskodu,kod2) == 0))
                kontrol++;

            if(kontrol == 2 && count == 0)
            {
                cout<<endl;
                cout << iter->ogrno <<" ";
                cout << iter->ad    <<" ";
                cout << iter->soyad <<" ";
                count = 1;
            }
            temp = temp->sonraki;
        }
        iter = iter->sonraki;
    }
}
