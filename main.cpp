#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <windows.h>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, numerTelefonu, adresEmail, adresZamieszkania;
};

string pobierzLinie()
{
    string linia;
    getline(cin, linia);

    return linia;
}

int pobierzLiczbe()
{
    int liczba;
    string wejscie;

    while (true)
    {
        wejscie = pobierzLinie();
        stringstream strumien(wejscie);
        if (strumien >> liczba)
        {
            break;
        }
        cout << "Wprowadzona wartosc nie jest liczba! Sprobuj ponownie: ";
    }
    return liczba;
}

string pobierzWpisDoBazyDanych()
{
	string wpis = pobierzLinie();

    for (size_t i = 0; i < wpis.size(); i++)
    {
        if (wpis[i] == '|')
        {
            i = -1;
            cout << endl << "Wprowadzono zastrzezony znak: |" << endl;
            cout << "Uzyj innego znaku i sprobuj ponownie: ";
			wpis = pobierzLinie();
        }
    }
    return wpis;
}

bool takCzyNie()
{
	bool takCzyNie;
	string wybor;
	char wyborChar;

	cout << "Wybierz [T]ak lub [N]ie: ";

    while (true)
	{
		wybor = pobierzLinie();
		transform(wybor.begin(), wybor.end(), wybor.begin(), ::toupper);
		wyborChar = wybor[0];
		switch (wyborChar)
		{
			case 'T':
				takCzyNie = true;
				break;
			case 'N':
				takCzyNie = false;
				break;
			default:
				cout << endl << "Nieprawidlowy wybor! Sprobuj ponownie: ";
		}
		if (wybor == "T" || wybor == "N")
		{
			break;
		}
	}
	return takCzyNie;
}

bool czyIdIstniejeWBazie(int idKontaktu, vector<Kontakt> kontakty)
{
	bool czyIstnieje;

	for (size_t i = 0; i < kontakty.size(); i++)
	{
		if (idKontaktu == kontakty[i].id)
		{
			czyIstnieje = true;
			break;
		}
		else
		{
			czyIstnieje = false;
		}
	}
	return czyIstnieje;
}

bool czyBazaDanychJestPusta(vector<Kontakt> kontakty)
{
    bool czyBazaDanychJestPusta;

    if (kontakty.size() == 0)
    {
        czyBazaDanychJestPusta = true;
        system("cls");
        cout << "Baza danych jest pusta." << endl;
        system("pause");
    }
    else
    {
        czyBazaDanychJestPusta = false;
    }
    return czyBazaDanychJestPusta;
}

int konwerterRozmiaruWektoraDoInt(vector<Kontakt> kontakty)
{
    size_t rozmiarWektora;
    int wyjscie;

    rozmiarWektora = kontakty.size();
    wyjscie = static_cast<int>(rozmiarWektora);

    return wyjscie;
}

int znajdzElementWektoraPoId(vector<Kontakt> kontakty, int idKontaktu)
{
	int nrElementu;
	int rozmiarBazyDanych;

	rozmiarBazyDanych = konwerterRozmiaruWektoraDoInt(kontakty);

	for (int i = 0; i < rozmiarBazyDanych; i++)
    {
        if (idKontaktu == kontakty[i].id)
        {
            nrElementu = i;
            break;
        }
    }
    return nrElementu;
}

Kontakt zaladujStrukture(string rekord)
{
    Kontakt osoba;
    string schowek = "";
    char *wsk = &rekord[0];

    while (*wsk != '|')
    {
        schowek += *wsk;
        wsk++;
    }
    osoba.id = atoi(schowek.c_str());
    wsk++;
    schowek = "";

    for (int i = 0; i < 5; i++)
    {
        while (*wsk != '|')
        {
            schowek += *wsk;
            wsk++;
        }
        switch(i)
        {
        case 0:
            osoba.imie = schowek;
            wsk++;
            schowek = "";
            break;
        case 1:
            osoba.nazwisko = schowek;
            wsk++;
            schowek = "";
            break;
        case 2:
            osoba.numerTelefonu = schowek;
            wsk++;
            schowek = "";
            break;
        case 3:
            osoba.adresEmail = schowek;
            wsk++;
            schowek = "";
            break;
        case 4:
            osoba.adresZamieszkania = schowek;
            wsk++;
            schowek = "";
            break;
        }
    }
    wsk = nullptr;

    return osoba;
}

vector<Kontakt> zaladujWektor(vector<Kontakt>& kontakty)
{
    fstream odczytZBazy;
    string schowek;
    Kontakt rekord;

    odczytZBazy.open("baza.txt", ios::in);
    if ( !odczytZBazy.good() )
    {
        cerr << "Wystapil problem z baza danych!";
        exit(0);
    }

    while ( getline(odczytZBazy, schowek) )
    {
        rekord = zaladujStrukture(schowek);
        kontakty.push_back(rekord);
    }
    odczytZBazy.close();

    return kontakty;
}

void pokazWybranyKontakt(vector<Kontakt> kontakty, int idKontaktu)
{
    for (size_t i = 0; i < kontakty.size(); i++)
    {
        if (idKontaktu == kontakty[i].id)
        {
            cout << kontakty[i].id << " | ";
            cout << kontakty[i].imie << " | ";
            cout << kontakty[i].nazwisko << " | ";
            cout << kontakty[i].numerTelefonu << " | ";
            cout << kontakty[i].adresEmail << " | ";
            cout << kontakty[i].adresZamieszkania << endl;
            break;
        }
    }
}

void pokazWszystkieKontakty(vector<Kontakt> kontakty)
{
    for (auto kontakt : kontakty)
    {
        cout << kontakt.id << " | ";
        cout << kontakt.imie << " | ";
        cout << kontakt.nazwisko << " | ";
        cout << kontakt.numerTelefonu << " | ";
        cout << kontakt.adresEmail << " | ";
        cout << kontakt.adresZamieszkania << endl;
    }
    cout << endl;
}

int wybierzID(vector<Kontakt>& kontakty)
{
	int wybor;

	pokazWszystkieKontakty(kontakty);
	cout << "Aby wyjsc do menu glownego, wprowadz [0]." << endl;
    cout << "Wpisz ID kontaktu, ktory Cie interesuje: ";
    wybor = pobierzLiczbe();

	return wybor;
}

void nadpiszBazeDanych(vector<Kontakt> kontakty)
{
    fstream nadpiszBaze;

    nadpiszBaze.open("baza.txt", ios::out | ios::trunc);
    if ( !nadpiszBaze.good() )
    {
        cerr << "Wystapil problem z baza danych!";
        exit(0);
    }

    for (auto rekord : kontakty)
    {
        nadpiszBaze << rekord.id << "|";
        nadpiszBaze << rekord.imie << "|";
        nadpiszBaze << rekord.nazwisko << "|";
        nadpiszBaze << rekord.numerTelefonu << "|";
        nadpiszBaze << rekord.adresEmail << "|";
        nadpiszBaze << rekord.adresZamieszkania << "|" << endl;
    }
    nadpiszBaze.close();
}

void wyszukajKontakty(vector<Kontakt> kontakty)
{
    bool czyZnaleziono = false;
    int wybor;
    string frazaDoWyszukiwarki;
    map<int, string> wyszukiwanaWartosc;

    wyszukiwanaWartosc[1] = "imie";
    wyszukiwanaWartosc[2] = "nazwisko";

    cout << "Dostepne opcje wyszukiwania:" << endl;
    cout << "[1] Po imieniu" << endl;
    cout << "[2] Po nazwisku" << endl;
    cout << "Wybierz: ";
    wybor = pobierzLiczbe();

    cout << endl << "Wyszukaj " << wyszukiwanaWartosc[wybor] << ": ";
    frazaDoWyszukiwarki = pobierzLinie();
    cout << endl << ".: Wyniki :." << endl;

    for (size_t i = 0; i < kontakty.size(); i++)
    {
        if (frazaDoWyszukiwarki == kontakty[i].imie && wybor == 1)
        {
            pokazWybranyKontakt(kontakty, kontakty[i].id);
            czyZnaleziono = true;
        }
        else if (frazaDoWyszukiwarki == kontakty[i].nazwisko && wybor == 2)
        {
            pokazWybranyKontakt(kontakty, kontakty[i].id);
            czyZnaleziono = true;
        }
    }

    if (czyZnaleziono == true)
    {
       cout << endl << "Wyszukiwanie zakonczone." << endl;
    }
    else
    {
        cout << endl << "Brak wynikow wyszukiwania." << endl;
    }
    system("pause");
}

void dodajKontakt(vector<Kontakt>& kontakty)
{
    Kontakt nowyKontakt;

    cout << "Dodajesz nowy kontakt. Uzupelnij ponizsze dane." << endl;
    cout << endl;

    if (kontakty.size() == 0)
    {
        nowyKontakt.id = 1;
    }
    else
    {
        nowyKontakt.id = kontakty.back().id + 1;
    }

    cout << "Imie: ";
    nowyKontakt.imie = pobierzWpisDoBazyDanych();
    cout << "Nazwisko: ";
    nowyKontakt.nazwisko = pobierzWpisDoBazyDanych();
    cout << "Numer telefonu: ";
    nowyKontakt.numerTelefonu = pobierzWpisDoBazyDanych();
    cout << "Adres e-mail: ";
    nowyKontakt.adresEmail = pobierzWpisDoBazyDanych();
    cout << "Adres zamieszkania: ";
    nowyKontakt.adresZamieszkania = pobierzWpisDoBazyDanych();

    kontakty.push_back(nowyKontakt);
    nadpiszBazeDanych(kontakty);

    system("cls");
    cout << "Kontakt zapisano pomyslnie!" << endl;
    system("pause");
    system("cls");
}

void edytujKontakt(vector<Kontakt>& kontakty, int idKontaktu)
{
    int wybor;
    int nrElementuWektora;
    map<int, string> danaDoEdycji;

    danaDoEdycji[1] = "imie";
    danaDoEdycji[2] = "nazwisko";
    danaDoEdycji[3] = "numer telefonu";
    danaDoEdycji[4] = "adres e-mail";
    danaDoEdycji[5] = "adres zamieszkania";

    system("cls");
    cout << "Edytujesz kontakt: " << endl;
    pokazWybranyKontakt(kontakty, idKontaktu);
    nrElementuWektora = znajdzElementWektoraPoId(kontakty, idKontaktu);
    cout << endl << "Jaki parametr chcesz edytowac?" << endl;

    for (int i = 1; i <= 5; i++)
    {
        cout << "[" << i << "] " << danaDoEdycji[i] << endl;
    }

    cout << "Twoj wybor: ";
    wybor = pobierzLiczbe();

    switch (wybor)
    {
    case 1:
        cout << "Wprowadz nowe imie: " << endl;
        kontakty[nrElementuWektora].imie = pobierzLinie();
        break;
    case 2:
        cout << "Wprowadz nowe nazwisko: " << endl;
        kontakty[nrElementuWektora].nazwisko = pobierzLinie();
        break;
    case 3:
        cout << "Wprowadz nowy numer telefonu: " << endl;
        kontakty[nrElementuWektora].numerTelefonu = pobierzLinie();
        break;
    case 4:
        cout << "Wprowadz nowy adres e-mail: " << endl;
        kontakty[nrElementuWektora].adresEmail = pobierzLinie();
        break;
    case 5:
        cout << "Wprowadz nowy adres zamieszkania: " << endl;
        kontakty[nrElementuWektora].adresZamieszkania = pobierzLinie();
        break;
    case 0:
        system("cls");
        exit(0);
        break;
    default:
        system("cls");
        cout << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
        system("pause");
        system("cls");
    }
}

void usunKontakt(vector<Kontakt>& kontakty, int idKontaktu)
{
	int rozmiarBazyDanych;
    int nrElementu;

    rozmiarBazyDanych = konwerterRozmiaruWektoraDoInt(kontakty);
    nrElementu = znajdzElementWektoraPoId(kontakty, idKontaktu);

	for (int i = nrElementu + 1; i < rozmiarBazyDanych; i++)
	{
		kontakty[i - 1] = kontakty[i];
	}
	kontakty.pop_back();
}

void menuUsuwaniaIEdycjiKontaktu(vector<Kontakt>& kontakty, int wybor)
{
    int idKontaktu;
    bool czyZnaleziono;
    bool czyZmienic;
    string jakaCzynnoscWykonac;

    if (wybor == 4)
    {
        jakaCzynnoscWykonac = "edytowanie";
    }
    else if (wybor == 5)
    {
        jakaCzynnoscWykonac = "usuniecie";
    }

	while (true)
	{
		cout << ".: Menu - " << jakaCzynnoscWykonac << " kontaktu :." << endl << endl;
		idKontaktu = wybierzID(kontakty);
		if (idKontaktu == 0)
		{
			break;
		}
		czyZnaleziono = czyIdIstniejeWBazie(idKontaktu, kontakty);
		if (czyZnaleziono == true)
		{
			cout << endl << "Czy na pewno chcesz wykonac " << jakaCzynnoscWykonac;
			cout << " kontaktu o ID " << idKontaktu << "?" << endl;
			czyZmienic = takCzyNie();
			if (czyZmienic == true && wybor == 4)
			{
				edytujKontakt(kontakty, idKontaktu);
				nadpiszBazeDanych(kontakty);
				transform(jakaCzynnoscWykonac.begin(), jakaCzynnoscWykonac.begin() + 1, jakaCzynnoscWykonac.begin(), ::toupper);
				cout << jakaCzynnoscWykonac << " kontaktu przebieglo pomyslnie!" << endl;
				system("pause");
				system("cls");
				break;
			}
			else if (czyZmienic == true && wybor == 5)
			{
				usunKontakt(kontakty, idKontaktu);
				nadpiszBazeDanych(kontakty);
				transform(jakaCzynnoscWykonac.begin(), jakaCzynnoscWykonac.begin() + 1, jakaCzynnoscWykonac.begin(), ::toupper);
				cout << jakaCzynnoscWykonac << " kontaktu przebieglo pomyslnie!" << endl;
				system("pause");
				system("cls");
				break;
			}
			else if (czyZmienic == false)
			{
				cout << "Anulowano " << jakaCzynnoscWykonac << " kontaktu." << endl;
				cout << "Kontakt pozostal w bazie danych." << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		else if (czyZnaleziono == false)
		{
			cout << endl << "Nie znaleziono kontaktu o podanym ID. Sprobuj ponownie." << endl;
			system("pause");
			system("cls");
		}
	}
}

int menuGlowne()
{
    vector<Kontakt> kontakty;
    fstream bazaDanych;

    bazaDanych.open("baza.txt", ios::out | ios::app);
    if ( !bazaDanych.good() )
    {
        cerr << "Wystapil problem z baza danych!";
        exit(0);
    }
    zaladujWektor(kontakty);

    while (true)
    {
        int wybor;

        system("cls");
        cout << ">>> Ksiazka adresowa <<<" << endl;
        cout << "Liczba zapisanych kontaktow: " << kontakty.size() << endl;
        cout << endl;
        cout << "Wybierz jedna z opcji:" << endl;
        cout << "[1] Pokaz wszystkie kontakty" << endl;
        cout << "[2] Wyszukaj" << endl;
        cout << "[3] Dodaj kontakt" << endl;
        cout << "[4] Edytuj kontakt" << endl;
        cout << "[5] Usun kontakt" << endl;
        cout << "[0] Zamknij program" << endl;
        cout << endl;

        cout << "Twoj wybor: ";
        wybor = pobierzLiczbe();

        switch (wybor)
        {
        case 1:
            system("cls");
            if ( !czyBazaDanychJestPusta(kontakty) )
            {
                pokazWszystkieKontakty(kontakty);
                system("pause");
            }
            break;
        case 2:
            system("cls");
            if ( !czyBazaDanychJestPusta(kontakty) )
            {
                wyszukajKontakty(kontakty);
            }
            break;
        case 3:
            system("cls");
            dodajKontakt(kontakty);
            break;
        case 4:
            system("cls");
            if ( !czyBazaDanychJestPusta(kontakty) )
            {
                menuUsuwaniaIEdycjiKontaktu(kontakty, wybor);
            }
            break;
        case 5:
            system("cls");
            if ( !czyBazaDanychJestPusta(kontakty) )
            {
                menuUsuwaniaIEdycjiKontaktu(kontakty, wybor);
            }
            break;
        case 0:
            system("cls");
            exit(0);
            break;
        default:
            system("cls");
            cout << "Nieprawidlowy wybor! Sprobuj ponownie." << endl;
            system("pause");
            system("cls");
        }
    }
    bazaDanych.close(); // Dla zasady
}

void menuRejestracji()
{
    fstream bazaUzytkownikow;
    string login, haslo, powtorzenieHasla;

    bazaUzytkownikow.open ("uzytkownicy.txt", ios::in | ios::app);
    if ( !bazaUzytkownikow.good() )
    {
        cerr << "Wystapil problem z baza uzytkownikow!" << endl;
        exit(0);
    }

    cout << ".: Menu rejestracji :." << endl;
    cout << "W trakcie budowy - dzialasz na wlasna odpowiedzialnosc" << endl;
    cout << endl << "Wprowadz nazwe uzytkownika: ";
    login = pobierzLinie();
    // tu bedzie funkcja sprawdzajaca czy nazwa uzytkownika istnieje w bazie
    cout << "Wprowadz swoje haslo: ";
    haslo = pobierzLinie();
    // tu bedzie funkcja zapisujaca uzytkownika w bazie
    cout << "Rejestracja nowego uzytkownika przebiegla pomyslnie!";
    system("pause");
}

int main()
{
    int wybor;

    while (true)
    {
        system("cls");
        cout << "[1] Logowanie" << endl;
        cout << "[2] Rejestracja" << endl;
        cout << "[0] Zamknij program" << endl;
        cout << endl << "Twoj wybor: ";

        wybor = pobierzLiczbe();

        switch (wybor)
        {
        case 2:
            system("cls");
            menuRejestracji();
            break;
        case 0:
            system("cls");
            exit(0);
            break;
        }
    }
    return 0;
}
