#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <ctime>
using namespace std;

int login(string &nume, int &highScore, int &highScoreInitial)
{
  highScoreInitial = 0;
  cout << "Introduceti-va numele pentru a va loga: ";
  string potentialNume;
  cin >> nume;
  system("cls");
  ifstream file("info.txt");
  if (!file.is_open())
  {
    cout << "Nu s-a putut deschide fisierul.";
    return 0;
  }
  while (!file.eof())
  {
    file >> potentialNume >> highScore;
    if (nume == potentialNume)
    {
      nume = potentialNume;
      cout << "Te-ai logat cu succes " << nume << ". "
           << "Scorul tau maxim este " << highScore << "." << endl;
      file.close();
      return 1;
    }
  }
  file.close();
  return 0;
}

int signin(string &nume, int &highScore, int &highScoreInitial)
{
  highScore = 0;
  cout << "Introduceti-va numele: ";
  string potentialNume;
  cin >> nume;
  system("cls");
  highScore = 0;
  ifstream file("info.txt");
  if (!file.is_open())
  {
    cout << "Nu s-a putut deschide fisierul.";
    return 0;
  }
  while (!file.eof())
  {
    file >> potentialNume >> highScore;
    if (nume == potentialNume)
    {
      nume = potentialNume;
      cout << "Esti deja inregistrat." << endl;
      file.close();
      return 0;
    }
  }
  if (file.is_open())
    file.close();
  fstream file2;
  file2.open("info.txt", ios::app);
  if (!file2.is_open())
  {
    cout << "Nu s-a putut deschide fisierul.";
    return 0;
  }
  file2 << nume << " " << 0 << endl;
  cout << "Te-ai inregistrat cu succes.";
  file2.close();
  cout << endl;
  login(nume, highScore, highScoreInitial);
  return 1;
}

int interfataLogare(string &nume, int &highScore, int &highScoreInitial)
{
  system("cls");
  cout << "Bine ai venit!" << endl;
  cout << "Pentru a-ti da login scrie 'l'." << endl;
  cout << "Pentru a-ti da signin scrie 's'." << endl;
  char a;
  cin >> a;
  system("cls");
  if (a == 'l')
  {
    if (login(nume, highScore, highScoreInitial) == 1)
      return 1;
    else
    {
      cout << "Nu ai fost gasit in baza de date." << endl;
      return 0;
    }
  }
  else if (a == 's')
  {
    highScoreInitial = 0;
    signin(nume, highScore, highScoreInitial);
    return 1;
  }
  else
  {
    cout << "Nu ai introdus un caracter valid." << endl;
    return 0;
  }
}

void afisareharta(int harta[5][5], string nume, int highScore)
{
  system("cls");
  cout << "Nume: " << nume << "    "
       << "scor: " << highScore << endl;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (harta[j][i] < 10)
        cout << harta[j][i] << "    ";
      else if (harta[j][i] < 100)
        cout << harta[j][i] << "   ";
      else if (harta[j][i] < 1000)
        cout << harta[j][i] << "  ";
      else if (harta[j][i] < 10000)
        cout << harta[j][i] << " ";
    }
    cout << endl
         << endl;
  }
}

int jos(int harta[5][5])
{
  for (int i = 0; i < 5; i++)
  {
    int valGasite = 0, pozVal;
    for (int j = 4; j > -1; j--)
    {
      if (harta[i][j] == 0)
        j = j;
      else if (valGasite == 0)
      {
        valGasite++;
        pozVal = j;
      }
      else
      {
        if (harta[i][pozVal] == harta[i][j])
        {
          harta[i][j] *= 2;
          harta[i][pozVal] = 0;
          valGasite = 0;
        }
        else
        {
          valGasite = 1;
          pozVal = j;
        }
      }
    }
    int cj;
    for (int j = 4; j > -1; j--)
    {
      cj = j;
      if (harta[i][j] != 0)
      {
        while (cj + 1 < 5 && harta[i][cj + 1] == 0)
          cj++;
        swap(harta[i][j], harta[i][cj]);
      }
    }
  }
  return 1;
}

int sus(int harta[5][5])
{
  for (int i = 0; i < 5; i++)
  {
    int valGasite = 0, pozVal;
    for (int j = 0; j < 5; j++)
    {
      if (harta[i][j] == 0)
        j = j;
      else if (valGasite == 0)
      {
        valGasite++;
        pozVal = j;
      }
      else
      {
        if (harta[i][pozVal] == harta[i][j])
        {
          harta[i][j] *= 2;
          harta[i][pozVal] = 0;
          valGasite = 0;
        }
        else
        {
          valGasite = 1;
          pozVal = j;
        }
      }
    }
    int cj;
    for (int j = 0; j < 5; j++)
    {
      cj = j;
      if (harta[i][j] != 0)
      {
        while (cj - 1 >= 0 && harta[i][cj - 1] == 0)
          cj--;
        swap(harta[i][j], harta[i][cj]);
      }
    }
  }
  return 1;
}

int dreapta(int harta[5][5])
{
  for (int j = 0; j < 5; j++)
  {
    int valGasite = 0, pozVal;
    for (int i = 4; i > -1; i--)
    {
      if (harta[i][j] == 0)
        j = j;
      else if (valGasite == 0)
      {
        valGasite++;
        pozVal = i;
      }
      else
      {
        if (harta[pozVal][j] == harta[i][j])
        {
          harta[i][j] *= 2;
          harta[pozVal][j] = 0;
          valGasite = 0;
        }
        else
        {
          valGasite = 1;
          pozVal = i;
        }
      }
    }
    int ci;
    for (int i = 4; i > -1; i--)
    {
      ci = i;
      if (harta[i][j] != 0)
      {
        while (ci + 1 < 5 && harta[ci + 1][j] == 0)
          ci++;
        swap(harta[i][j], harta[ci][j]);
      }
    }
  }
  return 1;
}

int stanga(int harta[5][5])
{
  for (int j = 0; j < 5; j++)
  {
    int valGasite = 0, pozVal;
    for (int i = 0; i < 5; i++)
    {
      if (harta[i][j] == 0)
        j = j;
      else if (valGasite == 0)
      {
        valGasite++;
        pozVal = i;
      }
      else
      {
        if (harta[pozVal][j] == harta[i][j])
        {
          harta[i][j] *= 2;
          harta[pozVal][j] = 0;
          valGasite = 0;
        }
        else
        {
          valGasite = 1;
          pozVal = i;
        }
      }
    }
    int ci;
    for (int i = 0; i < 5; i++)
    {
      ci = i;
      if (harta[i][j] != 0)
      {
        while (ci - 1 > -1 && harta[ci - 1][j] == 0)
          ci--;
        swap(harta[i][j], harta[ci][j]);
      }
    }
  }
  return 1;
}

int adaugareElement(int harta[5][5], int &highScore)
{
  int a[25][2], nrElemente = 0;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 5; j++)
    {
      if (harta[i][j] == 0)
      {
        a[nrElemente][0] = i;
        a[nrElemente][1] = j;
        nrElemente++;
      }
    }
  }
  if (nrElemente == 0)
    return 0;
  srand(static_cast<unsigned int>(std::time(nullptr)));
  int numarAleatoriu = rand() % nrElemente;
  harta[a[numarAleatoriu][0]][a[numarAleatoriu][1]] = 2;
  highScore++;
  return 1;
}

void adaugareHighscore(string userName, int &highScore)
{
  const int MAX_USERS = 50;
  int scores[MAX_USERS];
  string names[MAX_USERS];
  int numUsers = 0;

  ifstream inputFile("info.txt");
  if (!inputFile.is_open())
  {
    throw runtime_error("Could not open file for reading.");
  }

  while (numUsers < MAX_USERS && inputFile >> names[numUsers] >> scores[numUsers])
  {
    if (userName == names[numUsers])
    {
      scores[numUsers] = highScore;
    }
    numUsers++;
  }

  inputFile.close();

  ofstream outputFile("info.txt");
  if (!outputFile.is_open())
  {
    throw runtime_error("Could not open file for writing.");
  }

  for (int i = 0; i < numUsers; i++)
  {
    outputFile << names[i] << " " << scores[i] << endl;
  }

  outputFile.close();
}

int joc(int harta[5][5], int &highScore, string numeUtilizator, int &highScoreInitial)
{
  afisareharta(harta, numeUtilizator, highScore);
  char a;
  cin >> a;
  if (a == 'a')
  {
    int x;
    stanga(harta);
    x = adaugareElement(harta, highScore);
    if (x == 0)
    {
      cout << "Jocul s-a incheiat." << endl;
      if (highScore > highScoreInitial)
        adaugareHighscore(numeUtilizator, highScore);
      return 0;
    }
    else if (x == 1)
      joc(harta, highScore, numeUtilizator, highScoreInitial);
  }
  else if (a == 's')
  {
    int x;
    jos(harta);
    x = adaugareElement(harta, highScore);
    if (x == 0)
    {
      cout << "Jocul s-a incheiat." << endl;
      if (highScore > highScoreInitial)
        adaugareHighscore(numeUtilizator, highScore);
      return 0;
    }
    else if (x == 1)
      joc(harta, highScore, numeUtilizator, highScoreInitial);
  }
  else if (a == 'd')
  {
    int x;
    dreapta(harta);
    x = adaugareElement(harta, highScore);
    if (x == 0)
    {
      cout << "Jocul s-a incheiat." << endl;
      if (highScore > highScoreInitial)
        adaugareHighscore(numeUtilizator, highScore);
      return 0;
    }
    else if (x == 1)
      joc(harta, highScore, numeUtilizator, highScoreInitial);
  }
  else if (a == 'w')
  {
    int x;
    sus(harta);
    x = adaugareElement(harta, highScore);
    if (x == 0)
    {
      cout << "Jocul s-a incheiat." << endl;
      if (highScore > highScoreInitial)
        adaugareHighscore(numeUtilizator, highScore);
      return 0;
    }
    else if (x == 1)
      joc(harta, highScore, numeUtilizator, highScoreInitial);
  }
  else
  {
    cout << "Ai introdus un caracter invalid.";
    joc(harta, highScore, numeUtilizator, highScoreInitial);
  }
}

int main()
{
  string numeUtilizator;
  int harta[5][5] = {{0}};
  harta[0][0] = 2;
  int highScore, coordonateCaracter[4], highScoreInitial;
  if (interfataLogare(numeUtilizator, highScore, highScoreInitial) == 0)
  {
    cout << "Jocul s-a incheiat." << endl;
    return 0;
  }
  this_thread::sleep_for(std::chrono::seconds(2));
  highScoreInitial = highScore;
  highScore = 0;
  joc(harta, highScore, numeUtilizator, highScoreInitial);
}