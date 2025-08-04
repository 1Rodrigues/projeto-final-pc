#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

void iniciarNotas(int (&notas)[1000][5], int &totalAlunos)
{
  ifstream leitura("notas.txt");
  if(!leitura.is_open())
  {
    cerr << "Erro ao abrir arquivo, reinicie o programa!" << endl;
    return;
  }
    string linha;
}
void mostrarMenu()
{
  cout << "Escolha a opção desejada: " << endl;
  cout << "1: Cadastrar novo aluno" << endl;
  cout << "2: Cadastrar nova disciplina" << endl;
  cout << "3: inserir notas" << endl;
  cout << "4: Calcular média" << endl;
  cout << "5: Consultar notas" << endl;
  cout << "6: Relatório" << endl;
  cout << "7: Encerrar programa" << endl;
}

bool apenasLetras(const string &str)
{
  for (char c : str)
  {
    if (!isalpha(c) && c != ' ')
      return false;
  }
  return true;
}

bool apenasNumeros(const string &str)
{
  for (char c : str)
  {
    if (!isdigit(c))
      return false;
  }
  return true;
}

string cadastrarAluno()
{
  ofstream arquivo("alunos.txt", ios::app);
  if (!arquivo.is_open())
  {
    cerr << "Erro ao abrir o arquivo\n";
    return "";
  }

  cin.ignore();
  string entrada;
  cout << "Digite no formato nome-matricula-turma: ";
  getline(cin, entrada);

  stringstream ss(entrada);
  string nome, matricula, turma;

  if (!getline(ss, nome, '-') || !getline(ss, matricula, '-') || !getline(ss, turma, '-'))
  {
    cout << "Formato inválido. Use nome-matricula-turma\n";
    return "";
  }

  if (!apenasLetras(nome))
  {
    cout << "Nome inválido. Deve conter apenas letras.\n";
    return "";
  }

  if (!apenasNumeros(matricula))
  {
    cout << "Matrícula inválida. Deve conter apenas números.\n";
    return "";
  }

  arquivo << entrada << endl;
  arquivo.close();
  cout << "Aluno cadastrado com sucesso.\n";

  return entrada;
}
string cadastrarTurma()
{
  ofstream arquivo("disciplinas.txt", ios::app);
  if(!arquivo.is_open())
  {
    cerr << "Erro ao abrir arquivo!" << endl;
    return "";
  }
  string turma;
  cin.ignore();
  cout << "Digite a disciplina para cadstro no modelo 'nome-codigo': " << endl;
  getline(cin, turma);
  arquivo << turma << endl;
  arquivo.close();
  cout << "Disciplina adicionada com sucesso!" << endl;
  return turma;
}
void armazenarNotas(int (&notas)[][5], int totalAlunos)
{
  ofstream arquivo("notas.txt", ios::app);
  if(!arquivo.is_open())
  {
    cerr << "Erro ao acessar notas, reinicie o programa!" << endl;
    return;
  }
  for(int i = totalAlunos; i < totalAlunos + 1; i++)
  {
    cout << "Preencha o campo de notas (turma-aluno-n1-n2-n3): " << endl;
    for(int j = 0; j < 5; j++)
    {
      cin >> notas[i][j];
      arquivo << notas[i][j] << " ";
    }
    arquivo << endl;
  }
  arquivo.close();
  cout << "Notas armazenadas!" << endl;
}
int main()
{
  int totalAlunos = 0;
  int notas[1000][5];
  iniciarNotas(notas, totalAlunos);
  int menu;
  do
  {
    mostrarMenu();
    cin >> menu;

    switch (menu)
    {
    case 1:
      cadastrarAluno();
      break;
    case 2:
      cadastrarTurma();
      break;
    case 3:
      armazenarNotas(notas, totalAlunos);
      break;
    case 7:
      cout << "Encerrando programa.\n";
      break;
    }
  } while (menu != 7);

  return 0;
}
