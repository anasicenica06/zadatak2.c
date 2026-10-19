#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>

using namespace std;

#define MAX_SIZE 50

// Definiranje strukture i pokazivača
struct _Person;
typedef struct _Person* Position;

typedef struct _Person {
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    int godina;
    Position next;
} Person;

// Deklaracije funkcija
int insertBegin(char* name, char* surname, int year, Position p);
int insertAfter(Position p, Position newP);
int printList(Position p);
int insertEnd(char* name, char* surname, int year, Position p);
Position findLastName(char* lastName, Position p);
int deletePerson(char* lastName, Position p);

int main() {
    // Inicijalizacija Head (glave) liste u mainu bez globalnih varijabli
    Person Head = {
        .ime = { 0 },
        .prezime = { 0 },
        .godina = 0,
        .next = NULL
    };
    Position p = &Head;

    // Testiranje funkcionalnosti (A, B, C, D, E)
    insertBegin((char*)"Ana", (char*)"Anic", 1995, p);     // Pod A
    insertBegin((char*)"Ivo", (char*)"Ivic", 1990, p);     // Pod A
    insertEnd((char*)"Pero", (char*)"Peric", 2000, p);     // Pod C

    cout << "--- Ispis liste (Pod B) ---" << endl;
    printList(p);

    cout << "\n--- Trazenje elementa po prezimenu 'Ivic' (Pod D) ---" << endl;
    Position found = findLastName((char*)"Ivic", p);
    if (found != NULL) {
        cout << "Pronaden: " << found->ime << " " << found->prezime << ", godina rodenja: " << found->godina << endl;
    }
    else {
        cout << "Osoba nije pronadena." << endl;
    }


    cout << "\n--- Brisanje elementa s prezimenom 'Ivic' (Pod E) ---" << endl;
    deletePerson((char*)"Ivic", p);

    cout << "\n--- Ispis liste nakon brisanja ---" << endl;
    printList(p);

    return 0;
}

// Pomoćna funkcija za umetanje nakon određenog elementa
int insertAfter(Position p, Position newP) {
    newP->next = p->next;
    p->next = newP;
    return 0;
}

// Pod A: Dinamički dodaje novi element na početak liste
int insertBegin(char* name, char* surname, int year, Position p) {
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (newPerson == NULL) {
        cout << "Greska pri alokaciji memorije!" << endl;
        return -1;
    }

    strcpy_s(newPerson->ime, name);
    strcpy_s(newPerson->prezime, surname);
    newPerson->godina = year;
    newPerson->next = NULL;

    insertAfter(p, newPerson);
    return 0;
}

// Pod B: Ispisuje cijelu listu
int printList(Position p) {
    Position q = p->next;
    if (q == NULL) {
        cout << "Lista je prazna." << endl;
        return 0;
    }

    while (q != NULL) {
        cout << "Ime: " << q->ime << " | Prezime: " << q->prezime << " | Godina rodenja: " << q->godina << endl;
        q = q->next;
    }
    return 0;
}

// Pod C: Dinamički dodaje novi element na kraj liste
int insertEnd(char* name, char* surname, int year, Position p) {
    Position newPerson = NULL;

    newPerson = (Position)malloc(sizeof(Person));
    if (newPerson == NULL) {
        cout << "Greska pri alokaciji memorije!" << endl;
        return -1;
    }

    strcpy_s(newPerson->ime, name);
    strcpy(newPerson->prezime, surname);
    newPerson->godina = year;
    newPerson->next = NULL;

    // Vrtimo se do zadnjeg elementa liste
    while (p->next != NULL) {
        p = p->next;
    }

    insertAfter(p, newPerson);
    return 0;
}

// Pod D: Pronalazi element u listi po prezimenu
Position findLastName(char* lastName, Position p) {
    Position q = p->next;
    while (q != NULL) {
        if (strcmp(q->prezime, lastName) == 0) {
            return q;
        }
        q = q->next;
    }
    return NULL;
}

// Pod E: Briše određeni element iz liste po prezimenu
int deletePerson(char* lastName, Position p) {
    Position current = p;
    Position temp = NULL;

    while (current->next != NULL && strcmp(current->next->prezime, lastName) != 0) {
        current = current->next;
    }

    if (current->next == NULL) {
        cout << "Osoba s prezimenom '" << lastName << "' ne postoji u listi." << endl;
        return -1;
    }

    temp = current->next;
    current->next = temp->next;
    free(temp);

    cout << "Osoba s prezimenom '" << lastName << "' uspjesno izbrisana." << endl;
    return 0;
}