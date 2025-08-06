#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;

void iniciarNotas(int (&notas)[1000][5], int &totalAlunos)
{
    ifstream leitura("notas.txt");
    if (!leitura.is_open())
    {
        cerr << "Erro ao abrir arquivo, reinicie o programa!" << endl;
        return;
    }

    string linha;
    totalAlunos = 0;

    while (getline(leitura, linha))
    {
        stringstream ss(linha);
        for (int j = 0; j < 5; j++)
        {
            ss >> notas[totalAlunos][j];
        }
        totalAlunos++;
    }

    leitura.close();
}
void mostrarMenu()
{
  cout << "Escolha a opcao desejada: " << endl;
  cout << "1: Cadastrar novo aluno" << endl;
  cout << "2: Cadastrar nova disciplina" << endl;
  cout << "3: inserir notas" << endl;
  cout << "4: Calcular media" << endl;
  cout << "5: Consultar notas" << endl;
  cout << "6: Relatorio" << endl;
  cout << "7: Mostrar relatorio criado" << endl;
  cout << "8: Encerrar programa" << endl;
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

string cadastrarAluno(int& totalAlunos)
{
  ofstream arquivo("alunos.txt", ios::app);
  if (!arquivo.is_open())
  {
    cerr << "Erro ao abrir o arquivo" << endl;
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
    cout << "Formato invalido. Use nome-matricula-turma\n";
    return "";
  }

  if (!apenasLetras(nome))
  {
    cout << "Nome invalido. Deve conter apenas letras.\n";
    return "";
  }

  if (!apenasNumeros(matricula))
  {
    cout << "Matricula invalida. Deve conter apenas números.\n";
    return "";
  }

  arquivo << entrada << endl;
  arquivo.close();
  cout << "Aluno cadastrado com sucesso.\n";
  totalAlunos++;

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
void armazenarNotas(int (&notas)[1000][5], int totalAlunos)
{
  ofstream arquivo("notas.txt", ios::app);
  if(!arquivo.is_open())
  {
    cerr << "Erro ao acessar notas, reinicie o programa!" << endl;
    return;
  }
  for(int i = totalAlunos; i < totalAlunos + 1; i++)
  {
    cout << "Preencha o campo de notas (cod da materia cod aluno n1 n2 n3): " << endl;
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

double calcularMedia(int n1, int n2, int n3)
{
  return (n1+n2+n3) / 3.0;
}

void mediasPorAluno(int codAluno)
{
  ifstream leitura("notas.txt");
  if(!leitura.is_open())
  {
    cerr << "Erro ao abrir arquivo de notas!";
    return;
  }
  int codDisciplina, codaluno, n1, n2, n3;
  double media;
  bool achou = false;

  cout << "O aluno " << codAluno << " tem medias: " << endl;
  while(leitura >> codDisciplina >> codaluno >> n1 >> n2 >> n3)
  {
    if(codaluno == codAluno)
    {
      media = calcularMedia(n1, n2, n3);
      cout << "Disciplina " << codDisciplina
             << " - Notas: " << n1 << ", " << n2 << ", " << n3
             << " - Media: " << media << endl;
      achou = true;
    }
  }
  if(!achou)
  {
    cout << "O codigo nao corresponde a um aluno cadastrado!";
  }

  leitura.close();
}
void notasPorDisciplina(int codDisciplina)
{
  ifstream leitura("notas.txt");
  if(!leitura.is_open())
  {
    cerr << "Erro ao abrir notas";
    return;
  }
  int coddisc, codalumn, n1, n2, n3;
  int soma = 0;
  int totalNotas = 0;
  double media;

  while(leitura >> coddisc >> codalumn >> n1 >> n2 >> n3)
  {
    if(coddisc == codDisciplina)
    {
      soma += n1;
      soma += n2;
      soma += n3;
      totalNotas += 3;
    }
  }
  media = soma / totalNotas;
  cout << "A disciplina " << codDisciplina << " tem media: " << media << endl;

}

  void consultarnotasAlunoDiciplinas(int codAluno) {
    
  ifstream leitura("notas.txt");
  if(!leitura.is_open())
  {
    cerr << "Erro ao abrir notas";
    return;
  }
  int coddisc, codalumn,n1,n2,n3;
  bool achou=false;
  
  cout << "o aluno " << codAluno << " na diciplina " << coddisc << " possui as notas:" << endl;
    while (leitura >>coddisc >> codalumn >> n1 >> n2 >> n3) {
      if (codalumn == codAluno ) {
        cout << "diciplinas " << coddisc << "-Notas: " << n1 << ", " << n2 << ", " << n3 << endl;
        cout << "media: " << calcularMedia(n1,n2,n3) << endl;
        achou = true;
      }
    }
    if (!achou) {
      cout << "nenhum aluno cadastrado com o codigo informado " << codalumn <<endl;
    }
   leitura.close();
  }
  void consultarNotasDiciplinas(int codDisciplina) {
     ifstream leitura("notas.txt");
  if(!leitura.is_open())
  {
    cerr << "Erro ao abrir notas";
    return;
  }
  int coddisc, codalumn,n1,n2,n3;
  bool achou=false;
  
  cout << "A disciplina "  << codDisciplina << " possui as notas dos alunos:" << endl;
    while (leitura >>coddisc >> codalumn >> n1 >> n2 >> n3) {
      if (coddisc == codDisciplina ) {
        cout << "alunos " << codalumn << "-Notas: " << n1 << ", " << n2 << ", " << n3 << endl;
        cout << "media: " << calcularMedia(n1,n2,n3) << endl;
        achou = true;
      }
    }
    if (!achou) {
      cout << "nenhuma nota para essa disciplina " << coddisc << endl;
    }
   leitura.close();
  

  }

  void criarRelatorio(){ 
    ifstream leituraNotas("notas.txt");
    ifstream leituraAlunos("alunos.txt");
    ifstream leituraDisciplinas("disciplinas.txt");

    if (!leituraNotas.is_open() || !leituraAlunos.is_open() || !leituraDisciplinas.is_open()) {
        cerr << "Erro ao abrir os arquivos necessários." << endl;
        return;
    }

    string nomesAlunos[1000];
    int codigosAlunos[1000];
    int totalAlunos = 0;

    string linha;
    while (getline(leituraAlunos, linha)) {
        stringstream ss(linha);
        string nome, matricula, turma;
        getline(ss, nome, '-');
        getline(ss, matricula, '-');
        getline(ss, turma, '-');
        codigosAlunos[totalAlunos] = stoi(matricula);
        nomesAlunos[totalAlunos] = nome;
        totalAlunos++;
    }

    string nomesDisciplinas[1000];
    int codigosDisciplinas[1000];
    int totalDisciplinas = 0;

    while (getline(leituraDisciplinas, linha)) {
        stringstream ss(linha);
        string nome, codigo;
        getline(ss, nome, '-');
        getline(ss, codigo, '-');
        codigosDisciplinas[totalDisciplinas] = stoi(codigo);
        nomesDisciplinas[totalDisciplinas] = nome;
        totalDisciplinas++;
    }

    int codDisc, codAluno, n1, n2, n3;
    string relatorio = "";

    while (leituraNotas >> codDisc >> codAluno >> n1 >> n2 >> n3) {
        string nomeAluno = "Desconhecido";
        string nomeDisc = "Desconhecida";

        for (int i = 0; i < totalAlunos; i++) {
            if (codigosAlunos[i] == codAluno) {
                nomeAluno = nomesAlunos[i];
                break;
            }
        }

        for (int i = 0; i < totalDisciplinas; i++) {
            if (codigosDisciplinas[i] == codDisc) {
                nomeDisc = nomesDisciplinas[i];
                break;
            }
        }

        float media = calcularMedia(n1, n2, n3);

        relatorio += "Disciplina: " + nomeDisc + " (" + to_string(codDisc) + ")\n";
        relatorio += "  Aluno: " + nomeAluno + " (" + to_string(codAluno) + ")\n";
        relatorio += "    Notas: " + to_string(n1) + ", " + to_string(n2) + ", " + to_string(n3) + "\n";
        relatorio += "    Média: " + to_string(media).substr(0, 5) + "\n\n";
    }

    leituraNotas.close();
    leituraAlunos.close();
    leituraDisciplinas.close();

    int gerarouexibir;
    cout << "digite 1 se voce quiser exibir o relatorio, 2 se quiser transformar em txt" << endl;
    cin >> gerarouexibir;
    if (gerarouexibir==1){
      cout << " " << relatorio << endl;
    }
    if(gerarouexibir==2){
      ofstream saida("relatorio.txt");
      if (!saida.is_open()){
        cerr << "erro ao abrir arquivo de saida" << endl;
        return;
      }
      saida << relatorio;
      saida.close();
      cout << "relaorio salvo com sucesso em relatorio.txt" << endl;
    }
    if (gerarouexibir != 1 && gerarouexibir!=2) 
    { cout << "digite uma opcao valida" << endl; }

  }
  void mostrarRelatorio()
  {
    ifstream leitura("relatorio.txt");
    if (!leitura.is_open()){
      cerr << "erro ao abrir o arquivo dos  relatorios" << endl;
      return;
    }
    string linha;
    while (getline(leitura, linha))
    {
      cout << linha << endl;
    }
    leitura.close();
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
      cadastrarAluno(totalAlunos);
      break;
    case 2:
      cadastrarTurma();
      break;
    case 3:
      armazenarNotas(notas, totalAlunos);
      break;
    case 4:
    {
      int opcao, codA, codD;
      cout << "Digite 1 para  ver as medias de um aluno ou 2 para ver as medias de uma diciplina ";
      cin >> opcao;
      if(opcao == 1)
      {
        cout << "Qual o código do aluno buscado? ";
        cin >> codA;
        mediasPorAluno(codA);
      }
      if(opcao == 2)
      {
        cout << "Qual o código da disciplina buscada? ";
        cin >> codD;

        notasPorDisciplina(codD);
      }
    }
    break;

    case 5 :
{
    int opcao=0;
    int codA, codD;
    cout << "digite 1 para ver todas as notas de uma diciplina em especifico" << endl;
     cout << "digite 2 para ver a nota de todos os alunos de uma diciplina" << endl;
     cin >> opcao;
     if (opcao==1)
     {
      cout << "digite o codigo do aluno: " << endl;
      cin >>codA;
      consultarnotasAlunoDiciplinas(codA);
     }
     if (opcao == 2) {
      cout << "digite o codigo da diciplina: " << endl;
      cin >>codD;
      consultarNotasDiciplinas(codD);
     }

     if (opcao != 1 && opcao != 2){
     cerr << "opcao selecionada invalida" << endl;
     }
   
  }
  break;
  case 6: 
    criarRelatorio();
  break;
  case 7:
 mostrarRelatorio();
  break;
    case 8:
      cout << "Encerrando programa." << endl;
      break;
    }
  } while (menu != 8);

  return 0;
}
