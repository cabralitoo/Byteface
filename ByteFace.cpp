#include <algorithm>
#include <chrono>
#include <conio.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <thread>
#include <windows.h>
#include <ctype.h>

using namespace std;

//player
string nome = "";
int estado = 0;
int fome = 0;
long moedas = 0;
double emocao_normal; //temporario, prescisa está menos que 20% para aparecer as emoçoes
double emocao_felicidade = 0.0;
double emocao_tristeza = 0.0;
double emocao_bravo = 0.0;
string normal[] = { "(OwO)" };
string falando[] = { "(OoO)", "(O=O)", "(OAO)" };
string feliz[] = { "(^U^)", "(OuO)", "(>u<)" };
string bravo[] = { ">:(", "(>n<)", "(-n-)" };
string triste[] = { "(TnT)", "(QnQ)", "(;-;)", "(OnO)" };
string argument_init[] = { "Ola como vai vc???", "Nossa como e bom te conhecer, como estais???", "Olá senhor.......... ou senhora........ Pois bem, você tá bem???" };
string argument_normal[] = { "Ola!!!", "Nossa como e bom te conhecer!!!", "Olá senhor.......... ou senhora........ Pois bem, Bem-vindo!!!" };
string argument_feliz[] = { "OLAAAAAAAA, sua prezenca me faz bem, como estais? ", "BOOOOOMMMM DIAAAAAAA, OU BOA TARDE OU NOITEEEEEE, como vocá esta???" };
string argument_bravo[] = { "O que você quer???", "O quê queres desta vez???", "O que foi bobalhão???" };
string argumento_triste[] = { "...", "como vai...", "olá...", "que???......." };
string argument_nulo[] = { "pode repetir?", "E oq???", "Errrrr..... nao entendi nada, mas concordo" };
string frase;
//controles
string tecla = "";
bool inicial = true;
bool startup = true;
int tempo = 1;
int tempo_max = 3700; //3700 = 1 minuto
bool parar = false;
bool idleB = false;
int tempo_fome = 0;
bool tempo_fome_E = true;
int selec = 0;
int a[3][3], t, y, game = 1;
char name[30];
bool sair_velha = false;
bool conversas = false;
//compras
string escolha;
int quantidade = 0;
int valor = 0;

int Maçã = 0;
int Pera = 0;
int Abacaxi = 0;
int Uva = 0;
int Melancia = 0;
int Melão = 0;
int Mamão = 0;
int Banana = 0;
int Manga = 0;
int Morango = 0;
int Durian = 0;

int Alfaçe = 0;
int Brocolis = 0;
int Cenour = 0;
int Pimentao = 0;
int Batata = 0;
int Pepino = 0;
int Espinafre = 0;
int Couveflor = 0;
int Pimenta = 0;
int Cebola = 0;
int tomate = 0;

int Arroz = 0;
int Granola = 0;
int Paofrances = 0;
int Croissant = 0;
int Farro = 0;
int BarraCereal = 0;
int CerealChocolate = 0;
int PãoIntegral = 0;
int Pretzel = 0;
int Brioche = 0;
int Panetone = 0;
//aleatorio
int indiceFalando = 0; //colocar em cada frase argumentativa isto aqui ---> rand() % (sizeof(falando) / sizeof(falando[0]))
int indiceArgumento = rand() % (sizeof(argument_init) / sizeof(argument_init[0]));
int indiceFeliz = rand() % (sizeof(argument_feliz) / sizeof(argument_feliz[0]));
int indiceFelizReacao = rand() % (sizeof(feliz) / (sizeof(feliz[0])));
int indiceBravo = rand() % (sizeof(argument_bravo) / (sizeof(argument_bravo[0])));
int indiceBravoReacao = rand() % (sizeof(bravo) / (sizeof(bravo[0])));
int indiceTriste = rand() % (sizeof(argumento_triste) / (sizeof(argumento_triste[0])));
int indiceTristeReacao = rand() % (sizeof(triste) / (sizeof(triste[0])));
int indiceNulo = rand() % (sizeof(argument_nulo) / (sizeof(argument_nulo[0])));
int indiceNormal = rand() % (sizeof(argument_normal) / (sizeof(argument_normal[0])));
//métodos
void Sem_argumento();
void Save();
void Load();
void Zerar();
int comparar_emocao();
void ajustar_emocao();
string exibir_emocao();
string funcao_argmuento(string fala);
void hub();
void idle();
void temporizador();
string respostas();
void gameP();
void temporizador_fome();
void print();
void pin();
void ai(int b);
int check();
bool edigito();
void verificar_compra(long valor);
void aviso(int erro_type);
bool edigito2();
void consumir(int& string);

int main(int a, char* b[]) {
    //aleatorio
    srand(static_cast<unsigned int>(time(0)));
    //permisao para usar acentuação
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, "");
    system("chcp 1252 > nul");

    Load();

    // Se o inicial for true, exibe a mensagem
    if (inicial && estado == 0) {
        startup = true;
        emocao_normal = 50;
        for (int i = 0; i < argument_init[indiceArgumento].length(); i++) {
            this_thread::sleep_for(chrono::milliseconds(30));
            system("cls");
            indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
            cout << falando[indiceFalando] << endl;
            frase = argument_init[indiceArgumento].substr(0, i + 1);//frase local
            cout << frase;
        }
        system("cls");
        cout << normal[0] << "\n";//reacao
        cout << frase << endl;//frase
        while (true) {
            cout << "(1) - 'Bem, é com vc???' (2) - 'Não, estou mal...' - (3) - 'Fica na sua!!!'" << endl;
            getline(cin, tecla);
            if (tecla == "1") {
                //GOOD 
                emocao_felicidade += 2.5;
                emocao_normal -= 4;
                frase = "Fico feliz que esteja bem!!! Se voce esta bem eu tambem estou";
                for (int i = 0; i < frase.length(); i++) {
                    this_thread::sleep_for(chrono::milliseconds(30));
                    indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
                    system("cls");
                    string exibir = frase.substr(0, i + 1);
                    cout << falando[indiceFalando] << endl;
                    cout << exibir;
                }
                system("cls");
                cout << feliz[0] << endl;
                cout << frase << endl;
                cout << "Aperte a tecla 'Enter' para pular....";
                getline(cin, tecla);
                break;
                system("cls");
                cout << feliz[indiceFeliz] << endl;
                cout << frase << endl;
            }
            else if (tecla == "2") {
                //BAD
                emocao_tristeza += 2;
                emocao_normal -= 4;
                frase = "Puxa... Lamento por voce esta assim, espero que melhore";
                for (int i = 0; i < frase.length(); i++) {
                    this_thread::sleep_for(chrono::milliseconds(30));
                    system("cls");
                    indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
                    string exibir = frase.substr(0, i + 1);
                    cout << falando[indiceFalando] << endl;
                    cout << exibir;
                }
                system("cls");
                cout << triste[3] << endl;
                cout << frase << endl;
                cout << "Aperte 'Enter' para pular....";
                getline(cin, tecla);
                break;
            }
            else if (tecla == "3") {
                //MORE BAD
                emocao_tristeza += 4;
                emocao_bravo += 1;
                emocao_normal -= 5;
                frase = "Puxa, como voce e sem coração.... Espero que agente de certo mais para frente...";
                for (int i = 0; i < frase.length(); i++) {
                    this_thread::sleep_for(chrono::milliseconds(40));
                    system("cls");
                    indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
                    cout << falando[indiceFalando] << endl;
                    string exibir = frase.substr(0, i + 1);
                    cout << exibir;
                }
                system("cls");
                cout << triste[2] << endl;
                cout << frase << endl;
                cout << "Aperte 'Enter' para pular.....";
                getline(cin, tecla);
                break;
            }
            else {
                Sem_argumento();
            }
        }
        system("cls");
        frase = "Eu sou um emoticom, mas voce pode definir um nome para mim";
        for (int i = 0; i < frase.length(); i++) {
            this_thread::sleep_for(chrono::milliseconds(30));
            system("cls");
            string exibir = frase.substr(0, i + 1);
            indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
            cout << falando[indiceFalando] << endl;
            cout << exibir;
        }
        system("cls");
        cout << normal[0] << endl;
        cout << frase << endl;
        while (true) {
            cout << "(1) - Definir nome (2) - Nao definir nome (nome padrao)" << endl;
            getline(cin, tecla);
            if (tecla == "1") {
                system("cls");
                while (true) {
                    cout << "Como ele se chamara???" << endl;
                    getline(cin, nome);
                    if (nome.find_first_not_of(" ") == nome.npos) {
                        frase = "Eu presciso ter um nome, pelo menos 1 letrinha, eu nao sou besta";
                        for (int i = 0; i < frase.length(); i++) {
                            this_thread::sleep_for(chrono::milliseconds(30));
                            system("cls");
                            string exibir = frase.substr(0, i + 1);
                            indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
                            cout << falando[indiceFalando] << endl;
                            cout << exibir;
                        }
                        system("cls");
                        cout << bravo[0] << endl;
                        cout << frase << endl;
                    }
                    else {
                        break;
                    }
                }
                frase = nome + " parece um nome bonito...................... So espero que nao seja palavra feia";
                for (int i = 0; i < frase.length(); i++) {
                    this_thread::sleep_for(chrono::milliseconds(30));
                    system("cls");
                    indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
                    cout << falando[indiceFalando] << endl;
                    string exibir = frase.substr(0, i + 1);
                    cout << exibir;
                }
                system("cls");
                cout << bravo[2] << endl;
                cout << frase << endl;
                cout << "Aperte 'Enter' para pular...";
                getline(cin, tecla);
                break;
            }
            else if (tecla == "2") {
                nome = "Byte";
                frase = "Uhmmm... pois bem meu nome sera...................... BYTE!!!!! isso por que sou um caractere feito aparti de zeros e uns HAHAHA";
                for (int i = 0; i < frase.length(); i++) {
                    this_thread::sleep_for(chrono::milliseconds(30));
                    system("cls");
                    indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
                    cout << falando[indiceFalando] << endl;
                    string exibir = frase.substr(0, i + 1);
                    cout << exibir;
                }
                system("cls");
                cout << feliz[2] << endl;
                cout << frase << endl;
                cout << "Aperte 'Enter' para continuar...";
                getline(cin, tecla);
                break;
            }
            else {
                Sem_argumento();
            }
        }
        system("cls");
        cout << "\033[43mAtenção:\nesse jogo foi feito em C++ e não por uma engine, com isso tenha em mente que pode ocorrer varios bugs.\033[0m" << endl;
        cout << "Quer começar tutorial???" << endl;
        getline(cin, tecla);
    }
    else if (inicial && estado != 0) {
        cout << "\033[41mHouve um erro no estado do jogo\033[0m" << endl;
        cout << "\033[44mVerifique o estado do jogo e modifique a Room para 0, ou Re-installe no site oficial https://facegaming.com.br/Download\033[0m";
        while (true)
        {

        }
    }
    system("cls");

    inicial = false;
    emocao_normal = 0;

    Save();
    gameP();

    return 0;
}

/**#*#*#*#*#*#*#*##**#*##*#*#*#*#*#**#*#*#*#*#*#*##*#*#*#*#*#*#**#*#*#*#**##*#*#*#*#*#*#**#*#*#*#*#*#*#*#*#*#*#*#*#*#**#*#*#*#*#*#**#*#*#*#*#*#**#*#*#*#*#*#*#*#**#*#*#*#*#*#*#*##**#*#*/

void gameP() {
    while (true)
    {//PS: para mudar a emoção, (lembrando que o estado e constantemente 0) coloque condiçoes de argumento e emoção
        conversas = false;
        tempo_fome_E = true;
        idleB = false;
        parar = false;
        sair_velha = false;
        selec = 0;
        if (!startup) {
            indiceNormal = rand() % (sizeof(argument_nulo) / (sizeof(argument_nulo[0])));
            funcao_argmuento(argument_normal[indiceNormal]);
            system("cls");
            hub();
        }
        if (startup) {
            hub();
        }
        
        startup = true;
        cout << "Versão Beta 1.0 " << endl;
        thread input_respostas(respostas);
        thread input_tempo(temporizador);
        thread input_fome(temporizador_fome);
        input_tempo.join();
        input_fome.join();
        input_respostas.join();
        if (tecla == "1") {
            tempo_fome_E = true;
            idleB = false;
            system("cls");
            selec++;
            hub();
            thread input_fome(temporizador_fome);
            thread input_respostas(respostas);
            input_fome.join();
            input_respostas.join();
            if (tecla == "1") {
                tempo_fome_E = true;
                selec++;
                funcao_argmuento("Puxa isso e tão bom....");
                emocao_felicidade += 5;
                emocao_normal -= 0.2;
                system("cls");
                cout << feliz[2] << endl;
                cout << frase << endl;
                cout << "'Enter' para continuar...";
                getline(cin, tecla);
            }
            else if (tecla == "2") {
                tempo_fome_E = true;
                selec++;
                funcao_argmuento("A quanto tempo não recebo um abraço virtual, muito obrigado...");
                emocao_felicidade += 3;
                emocao_normal -= 0.2;
                system("cls");
                cout << feliz[2] << endl;
                cout << frase << endl;
                cout << "'Enter' para continuar...";
                getline(cin, tecla);
            }
            else if (tecla == "3") {
                conversas = true;
                string conversa[] = { "Uma vez, eu estava passeando por microprocessadores, e vi um um componente eletronico passando, daí ele chamou minha atenção, quando fui até ele, ele perguntou onde fica a raiz do processador, como não sabia disse que não, daí ele saiu e falou baixinho \" Caramba, um viruz como eu num tem sorte na vida um segundo...\" depois foi embora. O mais esquisito e que ele saiu apressado, parece que alguns anti-viruz estava atras dele.... só isso mesmo",
                "A internet ta cheio de piadas e memes, como eu sou um caractere formado por 0 e 1 (Bytes) as vezes posso ter sentimentos por parte do meu criador, sei lá, tudo isso já e programavel, até parece que a pessoa que me criou tem alguma alma no coração.......... a desculpe saí do assunto, mas emfim, na internet e cheio de memes e videos interessantes, eu mesmo queria poder criar meu proprio canal, ao menos se eu tivesse vida.",
                "Você não tem noção como era ter um computador antigamente, era um saco...... tinha que selecionar coisas aleatorias pelo teclado, e nem era exibidas imagens e som, e é até louco pensar que a primeira menssagem via computador foi um simples (\"lo\")...... AHHHH sim.... e a antiga internet discada, Um simples video demorava 1 semana e um jogo 2 decadas, ainda bem que foi possivel evoluir isso que hoje chamamos de informatica/tecnologia",
                "Saindo da tecnologia, você sabia que o sol que vemos era ele a 8 minutos atrás??? A luz e rapida mas o universo e grando, fazendo com que a luz demore anos ate chegar...... no fim do universo..... se exitir!!!!",
                "Cara assim... você percebeu que eu repito as mesmas frases as vezes??? Pois é, esses argumentos que você ta lendo ai e basicamente uma lista de frases aleatorias geradas por outra variavel, seria muito bom se empresas de jogos pudesser gerar conversas como essas mais interessante.... como por exemplo a utilização do ChatGPT, iria ficar mais intuitiva e melhores..... Aliás você realmente gosta de interagir comigo??? meu criador só me fez pra aprender C++",
                "Eu percebi que existe varios caracteres graças ao unicode.... Eu basicamente só existo graças ao seu computador.... Já que a linguagem C++ utiliza unicode, se não fosse por ele eu iria ficar mais ou menos assim oia só (ßŒøæþÐÞ§)",
                "\"Eu nunca pensei que leoninos iriam dá tão certos com peixes, Percebi que as energias de ambos se entrelaçam muito bem criando uma sifonia selestial[...]\" puxa essa historia dessas 2 pessoas que eu estou vendo são bem lindos, espero que eles deêm certos no futuro e se conhecam vejam....",
                "Uma vez navegando por ai, descobiri uma especie de arte na internete que é apaixonada por personagens antropomórficos, Devido a isso não posso comentar nada sobre isso já que e uma comunidade bem controversa hoje em dia... mas..... por que toquei nisso??? por que de acordo com o 'pedro video games' eu sou um caractere muito proximo dessa comunidade , e isso não tem nada háver",
                "Houve uma vebre esses dias sobre um cara chamado 'Carlinhos' aparentemente é um cara apaixonado por cavalos é tambem tem uma afinidade especial pela companhia masculina, e otimo saber que pessoas adoram os animais e apreciar o companheirismo.... ele realmente vai quebrar o recorde mundial da pessoa mais feliz que já viveu na face da terra",
                "É real que já existiu um personagem que adorava livros??? ele mé dava muito medo por ser muito estranho, muito \"Gordo\" e muito elastíco, parecia uma minhoca, ainda bem que ele não está mais no auge como antes, senão, iria ficar traumatizado em pleno pós-milenium...",
                "A ideia de um circo na internet não é um problema certo??? pós se for, como pode dá tão certo uma animação onde pessoas aleatorias chegam em um circo cheio de brinquedos onde nem lembram os proprios nome dá tão certo ainda mais no pleno piloto??? um dia vou tentar ser um dos binários que compõem cada particula das animaçõse 3D, assim vou ser bem notavel",
                "Eu não entendo como o python ficou tão popular..... ecredito que devido a sua sintaxe bem simples de serem entendida, em quanto em linnguagens de programação mais complexas tipo C++ ou o proprio java você cria uma calculadora por aproximadamente em média certa de 300 linhas de codigo ou mais, em python vc faz em menos de 20 depedendo de algumas bibliotecas \"API\" que tem nela, um dia vou tentar ser um Elon Musk mas dos programas HAHAHAHAHAHA",
                "Você consegue entender o quê eu falo??? Pois não, vou resumir, nada de mais, só algumas observações do meu dia-a-dia, não e presciso entender e sim ler oq eu falo, sou so um programa de computador, e com certeza você pode ser o ultimo ou uma das 4 pessoas que jogaram isso, então posso até arriscar é dizer parabens, você pode ter chgado no fundo no poço da internet para ter encontrado esse programinha que é eu",
                "Eu quebro muito a 4ª parede, na verdade não sei ao certo oq devo fazer, como eu disse (caso for a segunda ou tripla vez que eu falo isso) meu criador me fez para aprender C++, então ele só não se importou no que eu posso ou não posso dizer, mas provavelmente você só deve está tentando me deixar feliz, e eu agradeco muito por vc está sendo gentil comigo, <3",
                "Assembly pode ser minha tatara-tatara-tatara-avó, ela criou o fortan, que criou o cobol, que criou a fortran, que criou o ADAm que criou o C, que criou o C++, que criou o Java, que criou o Python, que criou o C# que criou o GO, que criou o Rust, que criou o Sift.... Uma verdadeira arvore genealogica computacional",
                "Um dia..... Um dia eu vou criar minha propria linguagem de programação chamada " + nome + " language... Eu espero que um dia ele seja bem popular e revolucione toda a industria e o marketin.... Ao menos se eu soubesse como fazer isso..."};
                int indice_Conversa = rand() % (sizeof(conversa)) / (sizeof(conversa[0]));
                funcao_argmuento(conversa[indice_Conversa]);
                tempo_fome_E = true;
                selec++;
                emocao_felicidade += 0.4;
                emocao_normal -= 0.2;
                system("cls");
                cout << normal[0] << endl; //Criar reaçoes diferentes por parte da posição do array selecionada aleatoriamente (condição)
                cout << frase << endl;
                cout << "\n\n'Enter' para continuar..." << endl;
                getline(cin, tecla);
            }
        }
        else if (tecla == "2") {
            tempo_fome_E = true;
            idleB = false;
            system("cls");
            selec = 2;
            hub();
            thread input_fome(temporizador_fome);
            thread input_respostas(respostas);
            input_fome.join();
            input_respostas.join();
            if (tecla == "1") {
                system("cls");
                char palavra[30], secreta[30];
                string letra;
                int tam, i, acertos, chances;
                bool acerto;

                chances = 3;
                tam = 0;
                i = 0;
                acertos = 0;
                acerto = false;

                while (true) {
                    system("cls");
                    cout << "Tente adivinhar a frase aseguir.\n\nAperte 'Enter' para pular... " << endl;
                    getline(cin, tecla);
                    if (tecla == "\0") {
                        break;
                    }
                }

                string aleatoria[] = { "computador", "relogio", "cafeteira" };
                int ale = rand() % (sizeof(aleatoria) / sizeof(aleatoria[0]));
                strcpy_s(palavra, sizeof(palavra), aleatoria[ale].c_str());
                system("cls");

                while (palavra[i] != '\0') {
                    i++;
                    tam++;
                }

                for (i = 0; i < 30; i++) {
                    secreta[i] = '-';
                }

                while (chances > 0 && acertos < tam) {
                    cout << "chances restantes " << chances << "\n\n";
                    cout << "Palavra secreta " << endl;
                    for (i = 0; i < tam; i++) {
                        cout << secreta[i];
                    }
                    cout << "\n\nDigite letra: ";
                    getline(cin, letra);
                    if (letra == palavra) {
                        acertos = 666;
                        break;
                    }
                    else if (letra.length() > 1 && letra != palavra) {
                        system("cls");
                        cout << "digite apenas 1 letra ou a frase está errada " << endl;
                        chances--;
                    }
                    else {
                        for (i = 0; i < tam; i++) {
                            if (palavra[i] == letra[0]) {
                                acertos++;
                                acerto = true;
                                secreta[i] = letra[0];
                            }
                        }
                        if (!acerto) {
                            chances--;
                        }
                        acerto = false;
                        system("cls");
                    }

                }
                if (acertos >= tam) {
                    int moedas_aleatorias = rand() % 25 + 1;
                    moedas += moedas_aleatorias;
                    cout << "Parabens você venceu!!! " << endl;
                    cout << "\nVocê ganhou " << moedas_aleatorias << " Moedas" << endl;

                    cout << "Aperte 'Enter' para pular...";
                    getline(cin, tecla);
                }
                else {
                    cout << "Fracassado " << endl;
                    cout << "Aperte 'Enter' para pular...";
                    getline(cin, tecla);
                }
            }
            else if (tecla == "2") {
                system("cls");

                int i, j;
                for (i = 0; i < 3; i++)
                    for (j = 0; j < 3; j++)
                        a[i][j] = 0;

                while (!sair_velha) {
                    t = 1;
                    y = (t == 1) ? 2 : 1;

                    cout << "\nSeu simbolo é " << ((t == 1) ? "X" : "O") << ".Do computador é " << ((t == 1) ? "O" : "X") << ".\n";
                    cout << "vamos começar\n";
                    print();

                    for (i = 0; i < 9; i++) {
                        if (i % 2 == 0) {
                            pin();
                        }
                        else {
                            ai(i);
                        }

                        print();

                        if (i >= 4 && check()) {
                            cout << ((i % 2 == 0) ? "Você" : "Seu computador") << " ganhou\n";
                            break;
                        }

                        if (i == 8) {
                            cout << "Deu velha!\n";
                            break;
                        }
                    }

                    while (true) {
                        string playAgain;
                        int moedas_aleatorias = rand() % 25 + 1;
                        moedas += moedas_aleatorias;
                        cout << "\nVocê ganhou " << moedas_aleatorias << " Moedas" << endl;
                        cout << "Quer jogar novamente? (s/n): ";
                        cin >> playAgain;

                        if (playAgain == "s" || playAgain == "S") {
                            system("cls");
                            int i, j;
                            for (i = 0; i < 3; i++)
                                for (j = 0; j < 3; j++)
                                    a[i][j] = 0;
                            break;
                        }
                        else if (playAgain == "n" || playAgain == "N") {
                            sair_velha = true;
                            break;
                        }
                        else {
                            system("cls");
                            cout << "O que???" << endl;
                        }
                    }
                }
            }
        }
        else if (tecla == "3") {
            tempo_fome_E = true;
            idleB = false;
            system("cls");
            selec = 3;
            hub();
        }
        else if (tecla == "4") {
            tempo_fome_E = true;
            idleB = false;
            system("cls");
            selec = 4;
            hub();
        }
        else if (tecla == "0") {
            cout << funcao_argmuento("Ahhhhhh tudo bem, até mais tarde");
            system("cls");
            cout << feliz[0] << endl;
            cout << frase;
            break; //ou exit(0);
        }
        else {
            idleB = false;
        }


        //Modulação Devloper
        if (tecla == "i") {
            emocao_bravo += 5;
        }
        else if (tecla == "$define to 0") {
            Zerar();
            cout << "O jogo foi zerado reinicie o programa";
            break;
        }
        else if (tecla == "$define emot 2") {
            getline(cin, tecla);

            // Substitui ',' por '.' se existir
            for (char& c : tecla) {
                if (c == ',') {
                    c = '.';
                }
            }

            // Tentar converter a string para double
            double value;
            istringstream stream(tecla);

            if (stream >> value && stream.eof()) {
                emocao_bravo = floor(value * 10.0) / 10.0;
                std::cout << std::fixed << std::setprecision(1) << "Emoção brava definida para: " << emocao_bravo << std::endl;
                if (emocao_bravo > emocao_normal) {
                    cout << "Valor maior" << endl;
                    cout << emocao_bravo << emocao_normal;
                    getline(cin, tecla);
                }
                else {
                    cout << "Valor menor";
                    cout << "Valor maior" << endl;
                    cout << emocao_bravo << " " << emocao_normal;
                    getline(cin, tecla);
                }
            }
        }
        else if (tecla == "$define money") {
            bool add_money = false;
            cout << "Defina sua moeda (cheat)" << endl;
            getline(cin, tecla);
            for (char c : tecla) {
                if (!isdigit(c)) {
                    cout << "Digite um numero valido";
                    getline(cin, tecla);
                    add_money = false;
                    break;
                }
                else {
                    add_money = true;
                }
            }
            if (add_money) {
                moedas = stoi(tecla);
            }
        }



        system("cls");
        Save();
    }
}

string respostas() {
    getline(cin, tecla);
    parar = true;
    tempo_fome_E = false;
    tempo = 1;
    return tecla;
}

void temporizador() {
    while (!parar) {
        if (tempo <= tempo_max) {
            this_thread::sleep_for(chrono::milliseconds(1));
            tempo++;
        }
        else {
            idle();
            break;
        }

    }
}

void temporizador_fome() {
    //esse metodo so continua no jogo quando incrementar a variavel
    while (tempo_fome_E) {
        if (tempo_fome < 750) {
            this_thread::sleep_for(chrono::milliseconds(1));
            tempo_fome++;
        }
        else {
            fome++;
            tempo_fome = 0;
            system("cls");
            hub();
            Save();
        }
    }
}

void Sem_argumento() {
    indiceNulo = rand() % (sizeof(argument_nulo) / (sizeof(argument_nulo[0])));
    for (int i = 0; i < argument_nulo[indiceNulo].length(); i++) {
        this_thread::sleep_for(chrono::milliseconds(30));
        system("cls");
        indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
        frase = argument_nulo[indiceNulo].substr(0, 1 + i);
        cout << falando[indiceFalando] << endl;
        cout << frase;
    }
    system("cls");
    cout << normal[0] << endl;
    cout << frase << endl;
    cin.clear();
}

void Save() {
    //of salva
    ofstream saveEstado("estado.txt");
    if (saveEstado.is_open()) {
        saveEstado << estado;
        saveEstado.close();
    }
    ofstream saveFeliz("Feliz_emocao.txt");
    // Verifica se o arquivo foi aberto com sucesso
    if (saveFeliz.is_open()) {
        saveFeliz << emocao_felicidade;
        saveFeliz.close();
    }
    ofstream saveNormal("Normal_emocao.txt");

    if (saveNormal.is_open()) {
        saveNormal << emocao_normal;
        saveNormal.close();
    }
    ofstream saveTriste("Triste_emocao.txt");
    // Verifica se o arquivo foi aberto com sucesso
    if (saveTriste.is_open()) {
        saveTriste << emocao_tristeza;
        saveTriste.close();
    }
    ofstream saveBravo("Bravo_emocao.txt");
    // Verifica se o arquivo foi aberto com sucesso
    if (saveBravo.is_open()) {
        saveBravo << emocao_bravo;
        saveBravo.close();
    }
    ofstream saveNome("Nome.txt");
    if (saveNome.is_open()) {
        saveNome << nome;
        saveNome.close();
    }

    ofstream saveMoedas("Moedas.txt");
    if (saveMoedas.is_open()) {
        saveMoedas << moedas;
        saveMoedas.close();
    }

    ofstream saveInicial("inicial.txt");
    if (saveInicial.is_open()) {
        saveInicial << inicial;
        saveInicial.close();
    }

    ofstream saveStartup("Nao_mexa.txt");
    if (saveStartup.is_open()) {
        saveStartup << 0;
        saveStartup.close();
    }
    ofstream saveFome("Fome.txt");
    if (saveFome.is_open()) {
        saveFome << fome;
        saveFome.close();
    }

    //compras
    string local = "comidas";
    ofstream frutamaça(local + "\\Maca.txt");
    if (frutamaça.is_open()) {
        frutamaça << Maçã;
        frutamaça.close();
    }
    ofstream frutapera(local + "\\Pera.txt");
    if (frutapera.is_open()) {
        frutapera << Pera;
        frutapera.close();
    }
    ofstream frutaabacaxi(local + "\\abacaxi.txt");
    if (frutaabacaxi.is_open()) {
        frutaabacaxi << Abacaxi;
        frutaabacaxi.close();
    }
    ofstream frutauva(local + "\\Uva.txt");
    if (frutauva.is_open()) {
        frutauva << Uva;
        frutauva.close();
    }
    ofstream frutamelancia(local + "\\Melancia.txt");
    if (frutamelancia.is_open()) {
        frutamelancia << Melancia;
        frutamelancia.close();
    }
    ofstream frutamelao(local + "\\Melao.txt");
    if (frutamelao.is_open()) {
        frutamelao << Melão;
        frutamelao.close();
    }
    ofstream frutamamao(local + "\\Mamao.txt");
    if (frutamamao.is_open()) {
        frutamamao << Mamão;
        frutamamao.close();
    }
    ofstream frutabanana(local + "\\Banana.txt");
    if (frutabanana.is_open()) {
        frutabanana << Banana;
        frutabanana.close();
    }
    ofstream frutamanga(local + "\\Manga.txt");
    if (frutamanga.is_open()) {
        frutamanga << Manga;
        frutamanga.close();
    }
    ofstream frutamorango(local + "\\Morango.txt");
    if (frutamorango.is_open()) {
        frutamorango << Morango;
        frutamorango.close();
    }
    ofstream frutadurian(local + "\\Durian.txt");
    if (frutadurian.is_open()) {
        frutadurian << Durian;
        frutadurian.close();
    }

    ofstream testealface(local + "\\Alfaçe.txt");
    if (testealface.is_open()) {
        testealface << Alfaçe;
        testealface.close();
    }
    ofstream testebrocolis(local + "\\Brocolis.txt");
    if (testebrocolis.is_open()) {
        testebrocolis << Brocolis;
        testebrocolis.close();
    }
    ofstream testecenoura(local + "\\Cenoura.txt");
    if (testecenoura.is_open()) {
        testecenoura << Cenour;
        testecenoura.close();
    }
    ofstream testepimentao(local + "\\Pimentao.txt");
    if (testepimentao.is_open()) {
        testepimentao << Pimentao;
        testepimentao.close();
    }
    ofstream testebatata(local + "\\Batata.txt");
    if (testebatata.is_open()) {
        testebatata << Batata;
        testebatata.close();
    }
    ofstream testepepino(local + "\\Pepino.txt");
    if (testepepino.is_open()) {
        testepepino << Pepino;
        testepepino.close();
    }
    ofstream testeespinafre(local + "\\Espinafre.txt");
    if (testeespinafre.is_open()) {
        testeespinafre << Espinafre;
        testeespinafre.close();
    }
    ofstream testecouve(local + "\\Couve-Flor.txt");
    if (testecouve.is_open()) {
        testecouve << Couveflor;
        testecouve.close();
    }
    ofstream testepimenta(local + "\\Pimenta.txt");
    if (testepimenta.is_open()) {
        testepimenta << Pimenta;
        testepimenta.close();
    }
    ofstream testecebola(local + "\\Cebola.txt");
    if (testecebola.is_open()) {
        testecebola << Cebola;
        testecebola.close();
    }
    ofstream testetomate(local + "\\Tomate.txt");
    if (testetomate.is_open()) {
        testetomate << tomate;
        testetomate.close();
    }
    ofstream testegranola(local + "\\Granola.txt");
    if (testegranola.is_open()) {
        testegranola << Granola;
        testegranola.close();
    }
    ofstream testepaofrances(local + "\\Pao frances.txt");
    if (testepaofrances.is_open()) {
        testepaofrances << Paofrances;
        testepaofrances.close();
    }
    ofstream testecroissant(local + "\\Croissant.txt");
    if (testecroissant.is_open()) {
        testecroissant << Croissant;
        testecroissant.close();
    }
    ofstream testefarro(local + "\\Farro.txt");
    if (testefarro.is_open()) {
        testefarro << Farro;
        testefarro.close();
    }
    ofstream testebarracereal(local + "\\Barra de cereal.txt");
    if (testebarracereal.is_open()) {
        testebarracereal << BarraCereal;
        testebarracereal.close();
    }
    ofstream testecerealchocolate(local + "\\Cereal de chocolate.txt");
    if (testecerealchocolate.is_open()) {
        testecerealchocolate << CerealChocolate;
        testecerealchocolate.close();
    }
    ofstream testepaointegral(local + "\\Pao integral.txt");
    if (testepaointegral.is_open()) {
        testepaointegral << PãoIntegral;
        testepaointegral.close();
    }
    ofstream testepretzel(local + "\\Pretzel.txt");
    if (testepretzel.is_open()) {
        testepretzel << tomate;
        testepretzel.close();
    }
    ofstream testebrioches(local + "\\Brioche.txt");
    if (testebrioches.is_open()) {
        testebrioches << Brioche;
        testebrioches.close();
    }
    ofstream testepanetone(local + "\\Panetone.txt");
    if (testepanetone.is_open()) {
        testepanetone << Panetone;
        testepanetone.close();
    }
}

void Load() {
    //if aplica
    ifstream loadEstado("estado.txt");

    if (loadEstado.is_open()) {
        loadEstado >> estado;
        loadEstado.close();
    }

    ifstream loadNormal("Normal_emocao.txt");

    if (loadNormal.is_open()) {
        loadNormal >> emocao_normal;
        loadNormal.close();
    }
    ifstream loadFeliz("Feliz_emocao.txt");

    if (loadFeliz.is_open()) {
        loadFeliz >> emocao_felicidade;
        loadFeliz.close();
    }

    ifstream loadTriste("Triste_emocao.txt");

    if (loadTriste.is_open()) {
        loadTriste >> emocao_tristeza;
        loadTriste.close();
    }

    ifstream loadBravo("Bravo_emocao.txt");

    if (loadBravo.is_open()) {
        loadBravo >> emocao_bravo;
        loadBravo.close();
    }

    ifstream loadNome("Nome.txt");
    if (loadNome.is_open()) {
        getline(loadNome, nome);
        loadNome.close();
    }

    ifstream loadMoedas("Moedas.txt");
    if (loadMoedas.is_open()) {
        loadMoedas >> moedas;
        loadMoedas.close();
    }

    ifstream loadInicial("inicial.txt");
    if (loadInicial.is_open()) {
        loadInicial >> inicial;
        loadInicial.close();
    }

    ifstream loadStartup("Nao_mexa.txt");
    if (loadStartup.is_open()) {
        loadStartup >> startup;
        loadStartup.close();
    }

    ifstream loadFome("Fome.txt");
    if (loadFome.is_open()) {
        loadFome >> fome;
        loadFome.close();
    }

    //comida
    string local = "comidas";
    ifstream frutamaça(local + "\\Maca.txt");
    if (frutamaça.is_open()) {
        frutamaça >> Maçã;
        frutamaça.close();
    }
    ifstream frutapera(local + "\\Pera.txt");
    if (frutapera.is_open()) {
        frutapera >> Pera;
        frutapera.close();
    }
    ifstream frutaabacaxi(local + "\\abacaxi.txt");
    if (frutaabacaxi.is_open()) {
        frutaabacaxi >> Abacaxi;
        frutaabacaxi.close();
    }
    ifstream frutauva(local + "\\Uva.txt");
    if (frutauva.is_open()) {
        frutauva >> Uva;
        frutauva.close();
    }
    ifstream frutamelancia(local + "\\Melancia.txt");
    if (frutamelancia.is_open()) {
        frutamelancia >> Melancia;
        frutamelancia.close();
    }
    ifstream frutamelao(local + "\\Melao.txt");
    if (frutamelao.is_open()) {
        frutamelao >> Melão;
        frutamelao.close();
    }
    ifstream frutamamao(local + "\\Mamao.txt");
    if (frutamamao.is_open()) {
        frutamamao >> Mamão;
        frutamamao.close();
    }
    ifstream frutabanana(local + "\\Banana.txt");
    if (frutabanana.is_open()) {
        frutabanana >> Banana;
        frutabanana.close();
    }
    ifstream frutamanga(local + "\\Manga.txt");
    if (frutamanga.is_open()) {
        frutamanga >> Manga;
        frutamanga.close();
    }
    ifstream frutamorango(local + "\\Morango.txt");
    if (frutamorango.is_open()) {
        frutamorango >> Morango;
        frutamorango.close();
    }
    ifstream frutadurian(local + "\\Durian.txt");
    if (frutadurian.is_open()) {
        frutadurian >> Durian;
        frutadurian.close();
    }

    ifstream testealface(local + "\\Alfaçe.txt");
    if (testealface.is_open()) {
        testealface >> Alfaçe;
        testealface.close();
    }
    ifstream testebrocolis(local + "\\Brocolis.txt");
    if (testebrocolis.is_open()) {
        testebrocolis >> Brocolis;
        testebrocolis.close();
    }
    ifstream testecenoura(local + "\\Cenoura.txt");
    if (testecenoura.is_open()) {
        testecenoura >> Cenour;
        testecenoura.close();
    }
    ifstream testepimentao(local + "\\Pimentao.txt");
    if (testepimentao.is_open()) {
        testepimentao >> Pimentao;
        testepimentao.close();
    }
    ifstream testebatata(local + "\\Batata.txt");
    if (testebatata.is_open()) {
        testebatata >> Batata;
        testebatata.close();
    }
    ifstream testepepino(local + "\\Pepino.txt");
    if (testepepino.is_open()) {
        testepepino >> Pepino;
        testepepino.close();
    }
    ifstream testeespinafre(local + "\\Espinafre.txt");
    if (testeespinafre.is_open()) {
        testeespinafre >> Espinafre;
        testeespinafre.close();
    }
    ifstream testecouve(local + "\\Couve-Flor.txt");
    if (testecouve.is_open()) {
        testecouve >> Couveflor;
        testecouve.close();
    }
    ifstream testepimenta(local + "\\Pimenta.txt");
    if (testepimenta.is_open()) {
        testepimenta >> Pimenta;
        testepimenta.close();
    }
    ifstream testecebola(local + "\\Cebola.txt");
    if (testecebola.is_open()) {
        testecebola >> Cebola;
        testecebola.close();
    }
    ifstream testetomate(local + "\\Tomate.txt");
    if (testetomate.is_open()) {
        testetomate >> tomate;
        testetomate.close();
    }
    ifstream testegranola(local + "\\Granola.txt");
    if (testegranola.is_open()) {
        testegranola >> Granola;
        testegranola.close();
    }
    ifstream testepaofrances(local + "\\Pao frances.txt");
    if (testepaofrances.is_open()) {
        testepaofrances >> Paofrances;
        testepaofrances.close();
    }
    ifstream testecroissant(local + "\\Croissant.txt");
    if (testecroissant.is_open()) {
        testecroissant >> Croissant;
        testecroissant.close();
    }
    ifstream testefarro(local + "\\Farro.txt");
    if (testefarro.is_open()) {
        testefarro >> Farro;
        testefarro.close();
    }
    ifstream testebarracereal(local + "\\Barra de cereal.txt");
    if (testebarracereal.is_open()) {
        testebarracereal >> BarraCereal;
        testebarracereal.close();
    }
    ifstream testecerealchocolate(local + "\\Cereal de chocolate.txt");
    if (testecerealchocolate.is_open()) {
        testecerealchocolate >> CerealChocolate;
        testecerealchocolate.close();
    }
    ifstream testepaointegral(local + "\\Pao integral.txt");
    if (testepaointegral.is_open()) {
        testepaointegral >> PãoIntegral;
        testepaointegral.close();
    }
    ifstream testepretzel(local + "\\Pretzel.txt");
    if (testepretzel.is_open()) {
        testepretzel >> tomate;
        testepretzel.close();
    }
    ifstream testebrioches(local + "\\Brioche.txt");
    if (testebrioches.is_open()) {
        testebrioches >> Brioche;
        testebrioches.close();
    }
    ifstream testepanetone(local + "\\Panetone.txt");
    if (testepanetone.is_open()) {
        testepanetone >> Panetone;
        testepanetone.close();
    }
}

void Zerar() {
    //of salva
    ofstream zerarEstado("estado.txt");
    if (zerarEstado.is_open()) {
        zerarEstado << 0;
        zerarEstado.close();
    }
    ofstream zerarFeliz("Feliz_emocao.txt");
    // Verifica se o arquivo foi aberto com sucesso
    if (zerarFeliz.is_open()) {
        zerarFeliz << 0;
        zerarFeliz.close();
    }
    ofstream zerarTriste("Triste_emocao.txt");
    // Verifica se o arquivo foi aberto com sucesso
    if (zerarTriste.is_open()) {
        zerarTriste << 0;
        zerarTriste.close();
    }
    ofstream zerarBravo("Bravo_emocao.txt");
    // Verifica se o arquivo foi aberto com sucesso
    if (zerarBravo.is_open()) {
        zerarBravo << 0;
        zerarBravo.close();
    }
    ofstream ZerarNormal("Normal_emocao.txt");
    if (ZerarNormal.is_open()) {
        ZerarNormal << 0;
        ZerarNormal.close();
    }
    ofstream zerarNome("Nome.txt");
    if (zerarNome.is_open()) {
        zerarNome << "";
        zerarNome.close();
    }

    ofstream zerarMoedas("Moedas.txt");
    if (zerarMoedas.is_open()) {
        zerarMoedas << 0;
        zerarMoedas.close();
    }

    ofstream zerarInicial("inicial.txt");
    if (zerarInicial.is_open()) {
        zerarInicial << 1;
        zerarInicial.close();
    }

    ofstream zerarStartup("Nao_mexa.txt");
    if (zerarStartup.is_open()) {
        zerarStartup << 1;
        zerarStartup.close();
    }

    ofstream zerarFome("Fome.txt");
    if (zerarFome.is_open()) {
        zerarFome << 0;
        zerarFome.close();
    }

    //compras
    string local = "comidas";
    ofstream frutamaça(local + "\\Maca.txt");
    if (frutamaça.is_open()) {
        frutamaça << 0;
        frutamaça.close();
    }
    ofstream frutapera(local + "\\Pera.txt");
    if (frutapera.is_open()) {
        frutapera << 0;
        frutapera.close();
    }
    ofstream frutaabacaxi(local + "\\abacaxi.txt");
    if (frutaabacaxi.is_open()) {
        frutaabacaxi << 0;
        frutaabacaxi.close();
    }
    ofstream frutauva(local + "\\Uva.txt");
    if (frutauva.is_open()) {
        frutauva << 0;
        frutauva.close();
    }
    ofstream frutamelancia(local + "\\Melancia.txt");
    if (frutamelancia.is_open()) {
        frutamelancia << 0;
        frutamelancia.close();
    }
    ofstream frutamelao(local + "\\Melao.txt");
    if (frutamelao.is_open()) {
        frutamelao << 0;
        frutamelao.close();
    }
    ofstream frutamamao(local + "\\Mamao.txt");
    if (frutamamao.is_open()) {
        frutamamao << 0;
        frutamamao.close();
    }
    ofstream frutabanana(local + "\\Banana.txt");
    if (frutabanana.is_open()) {
        frutabanana << 0;
        frutabanana.close();
    }
    ofstream frutamanga(local + "\\Manga.txt");
    if (frutamanga.is_open()) {
        frutamanga << 0;
        frutamanga.close();
    }
    ofstream frutamorango(local + "\\Morango.txt");
    if (frutamorango.is_open()) {
        frutamorango << 0;
        frutamorango.close();
    }
    ofstream frutadurian(local + "\\Durian.txt");
    if (frutadurian.is_open()) {
        frutadurian << 0;
        frutadurian.close();
    }

    ofstream testealface(local + "\\Alfaçe.txt");
    if (testealface.is_open()) {
        testealface << 0;
        testealface.close();
    }
    ofstream testebrocolis(local + "\\Brocolis.txt");
    if (testebrocolis.is_open()) {
        testebrocolis << 0;
        testebrocolis.close();
    }
    ofstream testecenoura(local + "\\Cenoura.txt");
    if (testecenoura.is_open()) {
        testecenoura << 0;
        testecenoura.close();
    }
    ofstream testepimentao(local + "\\Pimentao.txt");
    if (testepimentao.is_open()) {
        testepimentao << 0;
        testepimentao.close();
    }
    ofstream testebatata(local + "\\Batata.txt");
    if (testebatata.is_open()) {
        testebatata << 0;
        testebatata.close();
    }
    ofstream testepepino(local + "\\Pepino.txt");
    if (testepepino.is_open()) {
        testepepino << 0;
        testepepino.close();
    }
    ofstream testeespinafre(local + "\\Espinafre.txt");
    if (testeespinafre.is_open()) {
        testeespinafre << 0;
        testeespinafre.close();
    }
    ofstream testecouve(local + "\\Couve-Flor.txt");
    if (testecouve.is_open()) {
        testecouve << 0;
        testecouve.close();
    }
    ofstream testepimenta(local + "\\Pimenta.txt");
    if (testepimenta.is_open()) {
        testepimenta << 0;
        testepimenta.close();
    }
    ofstream testecebola(local + "\\Cebola.txt");
    if (testecebola.is_open()) {
        testecebola << 0;
        testecebola.close();
    }
    ofstream testetomate(local + "\\Tomate.txt");
    if (testetomate.is_open()) {
        testetomate << 0;
        testetomate.close();
    }
    ofstream testegranola(local + "\\Granola.txt");
    if (testegranola.is_open()) {
        testegranola << 0;
        testegranola.close();
    }
    ofstream testepaofrances(local + "\\Pao frances.txt");
    if (testepaofrances.is_open()) {
        testepaofrances << 0;
        testepaofrances.close();
    }
    ofstream testecroissant(local + "\\Croissant.txt");
    if (testecroissant.is_open()) {
        testecroissant << 0;
        testecroissant.close();
    }
    ofstream testefarro(local + "\\Farro.txt");
    if (testefarro.is_open()) {
        testefarro << 0;
        testefarro.close();
    }
    ofstream testebarracereal(local + "\\Barra de cereal.txt");
    if (testebarracereal.is_open()) {
        testebarracereal << 0;
        testebarracereal.close();
    }
    ofstream testecerealchocolate(local + "\\Cereal de chocolate.txt");
    if (testecerealchocolate.is_open()) {
        testecerealchocolate << 0;
        testecerealchocolate.close();
    }
    ofstream testepaointegral(local + "\\Pao integral.txt");
    if (testepaointegral.is_open()) {
        testepaointegral << 0;
        testepaointegral.close();
    }
    ofstream testepretzel(local + "\\Pretzel.txt");
    if (testepretzel.is_open()) {
        testepretzel << 0;
        testepretzel.close();
    }
    ofstream testebrioches(local + "\\Brioche.txt");
    if (testebrioches.is_open()) {
        testebrioches << 0;
        testebrioches.close();
    }
    ofstream testepanetone(local + "\\Panetone.txt");
    if (testepanetone.is_open()) {
        testepanetone << 0;
        testepanetone.close();
    }

}

int comparar_emocao() {
    if (emocao_normal >= emocao_bravo && emocao_normal >= emocao_felicidade && emocao_normal >= emocao_tristeza) {
        ajustar_emocao();
        return 0;
    }
    else if (emocao_felicidade >= emocao_bravo && emocao_felicidade >= emocao_normal && emocao_felicidade >= emocao_tristeza) {
        ajustar_emocao();
        return 1;
    }
    else if (emocao_bravo >= emocao_normal && emocao_bravo >= emocao_felicidade && emocao_bravo >= emocao_tristeza) {
        ajustar_emocao();
        return 2;
    }
    else if (emocao_tristeza >= emocao_normal && emocao_tristeza >= emocao_felicidade && emocao_tristeza >= emocao_bravo) {
        ajustar_emocao();
        return 3;
    }
}


string exibir_emocao() {
    comparar_emocao();
    if (comparar_emocao() == 0) {
        return normal[0];
    }
    else if (comparar_emocao() == 1) {
        return feliz[1];
    }
    else if (comparar_emocao() == 2) {
        return bravo[0];
    }
    else if (comparar_emocao() == 3) {
        return triste[0];
    }
    ajustar_emocao();
}

void ajustar_emocao() {
    emocao_normal = max(0.0, min(100.0, emocao_normal));
    emocao_tristeza = max(0.0, min(100.0, emocao_tristeza));
    emocao_bravo = max(0.0, min(100.0, emocao_bravo));
    emocao_felicidade = max(0.0, min(100, emocao_felicidade));
    fome = max(0.0, min(100, fome));
}

string funcao_argmuento(string fala) {
    frase = fala;
    if (!conversas) {
        for (int i = 0; i < frase.length(); i++) {
            this_thread::sleep_for(chrono::milliseconds(30));
            system("cls");
            string exibir = frase.substr(0, i + 1);
            indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
            cout << falando[indiceFalando] << endl;
            cout << exibir;
        }
    }
    else {
        for (int i = 0; i < 50 ; i++) {
            this_thread::sleep_for(chrono::milliseconds(30));
            system("cls");
            indiceFalando = rand() % (sizeof(falando) / sizeof(falando[0]));
            cout << falando[indiceFalando] << endl;
        }
    }
    return fala;
}

void hub() {
    ajustar_emocao();
    exibir_emocao();
    if (fome > 40) {
        cout << triste[2] << endl;
    }
    else {
        cout << exibir_emocao() << endl;
    }
    if (!startup) {
        cout << frase << endl;
    }
    cout << "Feliz " << emocao_felicidade << "%" << " Triste " << emocao_tristeza << "%" << " Bravo " << emocao_bravo << "%" << " Fome " << fome << "%" << " Moedas " << moedas << endl << endl;

    if (selec == 0) {
        cout << "(1) Interagir - Minigames (2) - Comer (3) - Loja (4) - Despedir (0)" << endl;
        if (fome > 40) {
            cout << "\n"; aviso(2);
        }
    }
    else if (selec == 1) {

        cout << "(1) * acariciar * - * Abraçar * (2) - * Conversar * (3)" << endl;
    }
    else if (selec == 2) {
        cout << "(1) Jogo da forca - Jogo da velha (2)" << endl;
    }
    else if (selec == 3) {
        int escolha_ali = 0;
        int f1 = 0;//maça
        int f2 = 0;//pera
        int f3 = 0;//abacaxi
        int f4 = 0;//uva
        int f5 = 0;//melancia
        int f6 = 0;//melao
        int f7 = 0;//mamao
        int f8 = 0;//banana
        int f9 = 0;//manga
        int f10 = 0;//morango
        int f11 = 0;//durian
        int f12 = 0;//alfaçe
        int f13 = 0;//brocolis
        int f14 = 0;//cenoura
        int f15 = 0;//pimentao
        int f16 = 0;//batata
        int f17 = 0;//pepino
        int f18 = 0;//espinafre
        int f19 = 0;//couveflor
        int f20 = 0;//pimenta
        int f21 = 0;//cebola
        int f22 = 0;//tomate
        int f23 = 0;//arroz
        int f24 = 0;//granola
        int f25 = 0;//paofrances
        int f26 = 0;//croissant
        int f27 = 0;//farro
        int f28 = 0;//barracereal
        int f29 = 0;//cerealchocolate
        int f30 = 0;//paointegral
        int f31 = 0;//pretzel
        int f32 = 0;//brioce
        int f33 = 0;//panetone
        if (Maçã > 0||   Pera  > 0||   Abacaxi  > 0||   Uva  > 0||   Melancia > 0 ||  
            Melão  > 0 ||   Mamão  > 0||   Banana  > 0||   Manga  > 0||   Morango  > 0||  
            Durian  > 0||   Alfaçe  > 0||   Brocolis > 0 ||   Cenour  > 0||   Pimentao > 0 ||  
            Batata  > 0||   Pepino  > 0||   Espinafre  > 0||   Couveflor > 0 ||   Pimenta > 0 ||  
            Cebola  > 0||   tomate  > 0||   Arroz > 0 ||  Granola  > 0||   Paofrances > 0 ||  
            Croissant  > 0||   Farro  > 0||   BarraCereal > 0 ||   CerealChocolate > 0 ||  
            PãoIntegral  > 0||  Pretzel  > 0||   Brioche  > 0||   Panetone > 0) {

            if (Maçã > 0) {
                escolha_ali++;
                f1 = escolha_ali;
                cout << "Maçã: " << Maçã << " (" << f1 << ")" << std::endl;
            }
            if (Pera > 0) {
                escolha_ali++;
                f2 = escolha_ali;
                std::cout << "Pera: " << Pera << " (" << f2 << ")" << std::endl;
            }
            if (Abacaxi > 0) {
                escolha_ali++;
                f3 = escolha_ali;
                cout << "Abacaxi: " << Abacaxi << " (" << f3 << ")" << std::endl;
            }
            if (Uva > 0) {
                escolha_ali++;
                f4 = escolha_ali;
                cout << "Uva: " << Uva << " (" << f4 << ")" << std::endl;
            }
            if (Melancia > 0) {
                escolha_ali++;
                f5 = escolha_ali;
                cout << "Melancia: " << Melancia << " (" << f5 << ")" << std::endl;
            }
            if (Melão > 0) {
                escolha_ali++;
                f6 = escolha_ali;
                cout << "Melão: " << Melão << " (" << f6 << ")" << std::endl;
            }
            if (Mamão > 0) {
                escolha_ali++;
                f7 = escolha_ali;
                cout << "Mamão: " << Mamão << " (" << f7 << ")" << std::endl;
            }
            if (Banana > 0) {
                escolha_ali++;
                f8 = escolha_ali;
                cout << "Banana: " << Banana << " (" << f8 << ")" << std::endl;
            }
            if (Manga > 0) {
                escolha_ali++;
                f9 = escolha_ali;
                cout << "Manga: " << Manga << " (" << f9 << ")" << std::endl;
            }
            if (Morango > 0) {
                escolha_ali++;
                f10 = escolha_ali;
                cout << "Morango: " << Morango << " (" << f10 << ")" << std::endl;
            }
            if (Durian > 0) {
                escolha_ali++;
                f11 = escolha_ali;
                cout << "Durian: " << Durian << " (" << f11 << ")" << std::endl;
            }

            if (Alfaçe > 0) {
                f12 = 0;
                escolha_ali++;
                cout << "Alface: " << Alfaçe << " (" << f12 << ")" << std::endl;
            }
            if (Brocolis > 0) {
                escolha_ali++;
                int f13 = escolha_ali;
                cout << "Brocolis: " << Brocolis << " (" << f13 << ")" << std::endl;
            }
            if (Cenour > 0) {
                escolha_ali++;
                f14 = escolha_ali;
                cout << "Cenour: " << Cenour << " (" << f14 << ")" << std::endl;
            }
            if (Pimentao > 0) {
                escolha_ali++;
                f15 = escolha_ali;
                cout << "Pimentao: " << Pimentao << " (" << f15 << ")" << std::endl;
            }
            if (Batata > 0) {
                escolha_ali++;
                f16 = escolha_ali;
                cout << "Batata: " << Batata << " (" << f16 << ")" << std::endl;
            }
            if (Pepino > 0) {
                escolha_ali++;
                f17 = escolha_ali;
                cout << "Pepino: " << Pepino << " (" << f17 << ")" << std::endl;
            }
            if (Espinafre > 0) {
                escolha_ali++;
                f18 = escolha_ali;
                cout << "Espinafre: " << Espinafre << " (" << f18 << ")" << std::endl;
            }
            if (Couveflor > 0) {
                escolha_ali++;
                f19 = escolha_ali;
                cout << "Couveflor: " << Couveflor << " (" << f19 << ")" << std::endl;
            }
            if (Pimenta > 0) {
                escolha_ali++;
                f20 = escolha_ali;
                cout << "Pimenta: " << Pimenta << " (" << f20 << ")" << std::endl;
            }
            if (Cebola > 0) {
                escolha_ali++;
                f21 = escolha_ali;
                cout << "Cebola: " << Cebola << " (" << f21 << ")" << std::endl;
            }
            if (tomate > 0) {
                escolha_ali++;
                f22 = escolha_ali;
                cout << "tomate: " << tomate << " (" << f22 << ")" << std::endl;
            }

            if (Arroz > 0) {
                escolha_ali++;
                f23 = escolha_ali;
                cout << "Arroz: " << Arroz << " (" << f23 << ")" << std::endl;
            }
            if (Granola > 0) {
                escolha_ali++;
                f24 = escolha_ali;
                cout << "Granola: " << Granola << " (" << f24 << ")" << std::endl;
            }
            if (Paofrances > 0) {
                f25 = 0;
                escolha_ali;
                cout << "Paofrances: " << Paofrances << " (" << f25 << ")" << std::endl;
            }
            if (Croissant > 0) {
                escolha_ali++;
                f26 = escolha_ali;
                cout << "Croissant: " << Croissant << " (" << f26 << ")" << std::endl;
            }
            if (Farro > 0) {
                escolha_ali++;
                f27 = escolha_ali;
                cout << "Farro: " << Farro << " (" << f27 << ")" << std::endl;
            }
            if (BarraCereal > 0) {
                escolha_ali++;
                f28 = escolha_ali;
                cout << "BarraCereal: " << BarraCereal << " (" << f28 << ")" << std::endl;
            }
            if (CerealChocolate > 0) {
                escolha_ali++;
                f29 = escolha_ali;
                cout << "CerealChocolate: " << CerealChocolate << " (" << f29 << ")" << std::endl;
            }
            if (PãoIntegral > 0) {
                escolha_ali++;
                f30 = escolha_ali;
                cout << "PãoIntegral: " << PãoIntegral << " (" << f30 << ")" << std::endl;
            }
            if (Pretzel > 0) {
                escolha_ali++;
                f31 = escolha_ali;
                cout << "Pretzel: " << Pretzel << " (" << f31 << ")" << std::endl;
            }
            if (Brioche > 0) {
                escolha_ali++;
                f32 = escolha_ali;
                cout << "Brioche: " << Brioche << " (" << f32 << ")" << std::endl;
            }
            if (Panetone > 0) {
                escolha_ali++;
                f33 = escolha_ali;
                cout << "Panetone: " << Panetone << " (" << f33 << ")"  << std::endl;
            }
            getline(cin, tecla);
            if (!tecla.empty()) {
                if (edigito2()) {
                    if (stoi(tecla) == f1) {
                        consumir(Maçã);
                    }
                    else if (stoi(tecla) == f2) {
                        consumir(Pera);
                    }
                    else if (stoi(tecla) == f3) {
                        consumir(Abacaxi);
                    }

                    else if (stoi(tecla) == f4) {
                        consumir(Uva);
                    }
                    else if (stoi(tecla) == f5) {
                        consumir(Melancia);
                    }
                    else if (stoi(tecla) == f6) {
                        consumir(Melão);
                    }
                    else if (stoi(tecla) == f7) {
                        consumir(Mamão);
                    }
                    else if (stoi(tecla) == f8) {
                        consumir(Banana);
                    }
                    else if (stoi(tecla) == f9) {
                        consumir(Manga);
                    }
                    else if (stoi(tecla) == f10) {
                        consumir(Morango);
                    }
                    else if (stoi(tecla) == f11) {
                        consumir(Durian);
                    }
                    else if (stoi(tecla) == f12) {
                        consumir(Alfaçe);
                    }
                    else if (stoi(tecla) == f13) {
                        consumir(Brocolis);
                    }
                    else if (stoi(tecla) == f14) {
                        consumir(Cenour);
                    }
                    else if (stoi(tecla) == f15) {
                        consumir(Pimentao);
                    }
                    else if (stoi(tecla) == f16) {
                        consumir(Batata);
                    }
                    else if (stoi(tecla) == f17) {
                        consumir(Pepino);
                    }
                    else if (stoi(tecla) == f18) {
                        consumir(Espinafre);
                    }
                    else if (stoi(tecla) == f19) {
                        consumir(Couveflor);
                    }
                    else if (stoi(tecla) == f20) {
                        consumir(Pimenta);
                    }
                    else if (stoi(tecla) == f21) {
                        consumir(Cebola);
                    }
                    else if (stoi(tecla) == f22) {
                        consumir(tomate);
                    }
                    else if (stoi(tecla) == f23) {
                        consumir(Arroz);
                    }
                    else if (stoi(tecla) == f24) {
                        consumir(Granola);
                    }
                    else if (stoi(tecla) == f25) {
                        consumir(Paofrances);
                    }
                    else if (stoi(tecla) == f26) {
                        consumir(Croissant);
                    }
                    else if (stoi(tecla) == f27) {
                        consumir(Farro);
                    }
                    else if (stoi(tecla) == f28) {
                        consumir(BarraCereal);
                    }
                    else if (stoi(tecla) == f29) {
                        consumir(CerealChocolate);
                    }
                    else if (stoi(tecla) == f30) {
                        consumir(PãoIntegral);
                    }
                    else if (stoi(tecla) == f31) {
                        consumir(Pretzel);
                    }
                    else if (stoi(tecla) == f32) {
                        consumir(Brioche);
                    }
                    else if (stoi(tecla) == f33) {
                        consumir(Panetone);
                    }
                }
            }
        }
else {
    cout << "Nenhuma fruta disponivel..." << endl;
    getline(cin, tecla);
        }
    }
    else if (selec == 4) {
        cout << "Escolha a sua seção de compras" << endl;
        cout << "(1) Frutas - Vegetais (2) - Pães e cereais (3)";
        getline(cin, tecla);
        if (tecla == "1") {
            cout << "Maçã ($20) - (1)" << endl;
            cout << "Pera ($30) - (2)" << endl;
            cout << "Abacaxi ($25) - (3)" << endl;
            cout << "Uva ($35) - (4)" << endl;
            cout << "Melancia ($50) - (5)" << endl;
            cout << "Melão ($40) - (6)" << endl;
            cout << "Mamão ($35) - (7)" << endl;
            cout << "Banana ($30) - (8)" << endl;
            cout << "Manga ($30) - (9)" << endl;
            cout << "Morango ($30) - (10)" << endl;
            cout << "Durian ($15) - (11)" << endl;
            tecla = "";
            getline(cin, tecla);
            if (tecla == "1") {
                if (Maçã >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da maçã: ";
                verificar_compra(20);  // maçã
                    Maçã += quantidade;
                }
            }
            else if (tecla == "2") {
                if (Pera >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da pera: ";
                verificar_compra(30);  // pera
                    Pera += quantidade;
                }
            }
            else if (tecla == "3") {
                if (Abacaxi >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade do abacaxi: ";
                verificar_compra(25);  // abacaxi
                    Abacaxi += quantidade;
                }
            }
            else if (tecla == "4") {
                if (Uva >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da uva: ";
                verificar_compra(35);  // uva
                    Uva += quantidade;
                }
            }
            else if (tecla == "5") {
                if (Melancia >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da melancia: ";
                verificar_compra(50);  // melancia
                    Melancia += quantidade;
                }
            }
            else if (tecla == "6") {
                if (Melão >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade do melão: ";
                verificar_compra(40);  // melão
                    Melão += quantidade;
                }
            }
            else if (tecla == "7") {
                if (~Mamão >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade do mamão: ";
                verificar_compra(35);  // mamão
                    Mamão += quantidade;
                }
            }
            else if (tecla == "8") {
                if (Banana >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da banana: ";
                verificar_compra(30);  // banana
                    Banana += quantidade;
                }
            }
            else if (tecla == "9") {
                if (Manga >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da manga: ";
                verificar_compra(30);  // manga
                    Manga += quantidade;
                }
            }
            else if (tecla == "10") {
                if (Morango >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade do morango: ";
                verificar_compra(30);  // morango
                    Morango += quantidade;
                }
            }
            else if (tecla == "11") {
                if (Durian >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade do durian: ";
                verificar_compra(15);  // durian
                    Durian += quantidade;
                }
            }
            
        }
        else if (tecla == "2") {
            cout << "Alfaçe ($10) - (1)" << endl;
            cout << "Brocolis ($10) - (2)" << endl;
            cout << "Cenoura ($5) - (3)" << endl;
            cout << "Pimentão ($5) - (4)" << endl;
            cout << "Batata ($10) - (5)" << endl;
            cout << "Penino ($10) - (6)" << endl;
            cout << "Espinafre ($20) - (7)" << endl;
            cout << "Couve-flor ($10) - (8)" << endl;
            cout << "Pimenta ($10) - (9)" << endl;
            cout << "Cebola ($10) - (10)" << endl;
            cout << "Tomate ($10) - (11)" << endl;
            getline(cin, tecla);
            if (tecla == "1") {
                if (Alfaçe >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade da alface: ";
                verificar_compra(10);  // alface
                    Alfaçe += quantidade;
                }
            }
            else if (tecla == "2") {
                if (Brocolis >= 99999999) {
                    aviso(1);
                }
                else {
                std::cout << "Quantidade do brócolis: ";
                verificar_compra(10);  // brócolis
                    Brocolis += quantidade;
                }
            }
            else if (tecla == "3") {
                if (Cenour >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade da cenoura: ";
                    verificar_compra(5);  // cenoura
                    Cenour += quantidade;
                }
            }
            else if (tecla == "4") {
                if (Pimentao >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do pimentão: ";
                    verificar_compra(5);  // pimentão
                    Pimentao += quantidade;
                }
            }
            else if (tecla == "5") {
                if (Batata >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade da batata: ";
                    verificar_compra(10);  // batata
                    Batata += quantidade;
                }
            }
            else if (tecla == "6") {
                if (Pepino >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do pepino: ";
                    verificar_compra(10);  // pepino
                    Pepino += quantidade;
                }
            }
            else if (tecla == "7") {
                if (Espinafre >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do espinafre: ";
                    verificar_compra(20);  // espinafre
                    Espinafre += quantidade;
                }
            }
            else if (tecla == "8") {
                if (Couveflor >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do couve-flor: ";
                    verificar_compra(10);  // couve-flor
                    Couveflor += quantidade;
                }
            }
            else if (tecla == "9") {
                if (Pimenta >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade da pimenta: ";
                    verificar_compra(18);  // pimenta
                    Pimenta += quantidade;
                }
            }
            else if (tecla == "10") {
                if (Cebola >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade da cebola: ";
                    verificar_compra(10);  // cebola
                    Cebola += quantidade;
                }
            }
            else if (tecla == "11") {
                if (tomate >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do tomate: ";
                    verificar_compra(10);  // tomate
                    tomate += quantidade;
                }
            }
        }
        else if (tecla == "3") {
            cout << "Arroz ($5) - (1)" << endl;
            cout << "Granola ($15) - (2) " << endl;
            cout << "Pão frances ($20) - (3)" << endl;
            cout << "Croissant ($50) - (4)" << endl;
            cout << "Farro ($10) - (5)" << endl;
            cout << "Barra de Cereal ($20) - (6)" << endl;
            cout << "Cereal de Chocolate ($30) - (7)" << endl;
            cout << "Pão Integral ($5) - (8)" << endl;
            cout << "Pretzel ($30) - (9)" << endl;
            cout << "Brioche ($20) - (10)" << endl;
            cout << "Panetone ($40) - (11)" << endl;
            getline(cin, tecla);

            if (tecla == "1") {
                if (Arroz >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do arroz: ";
                    verificar_compra(5);  // arroz
                    Arroz += quantidade;
                }
            }
            else if (tecla == "2") {
                if (Granola >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade da granola: ";
                    verificar_compra(15);  // granola
                    Granola += quantidade;
                }
            }
            else if (tecla == "3") {
                if (Paofrances >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do pão francês: ";
                    verificar_compra(20);  // pão francês
                    Paofrances += quantidade;
                }
            }
            else if (tecla == "4") {
                if (Croissant >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do croissant: ";
                    verificar_compra(50);  // croissant
                    Croissant += quantidade;
                }
            }
            else if (tecla == "5") {
                if (Farro >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do farro: ";
                    verificar_compra(10);  // farro
                    Farro += quantidade;
                }
            }
            else if (tecla == "6") {
                if (BarraCereal >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade da barra de cereal: ";
                    verificar_compra(20);  // barra de cereal
                    BarraCereal += quantidade;
                }
            }
            else if (tecla == "7") {
                if (CerealChocolate >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do cereal de chocolate: ";
                    verificar_compra(30);  // cereal de chocolate
                    CerealChocolate += quantidade;
                }
            }
            else if (tecla == "8") {
                if (PãoIntegral >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do pão integral: ";
                    verificar_compra(5);  // pão integral
                    PãoIntegral += quantidade;
                }
            }
            else if (tecla == "9") {
                if (Pretzel >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do pretzel: ";
                    verificar_compra(30);  // pretzel
                    Pretzel += quantidade;
                }
            }
            else if (tecla == "10") {
                if (Brioche >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do brioche: ";
                    verificar_compra(20);  // brioche
                    Brioche += quantidade;
                }
            }
            else if (tecla == "11") {
                if (Panetone >= 99999999) {
                    aviso(1);
                }
                else {
                    std::cout << "Quantidade do panetone: ";
                    verificar_compra(40);
                    Panetone += quantidade;
                }
            }
        }
    }
    if (idleB) {
        tempo = 1;
        string pensamentos[] = { "Já se passaram 1 minuto é ele continua parado!!!" };
        int indice_Pensamentos = rand() % (sizeof(pensamentos) / (sizeof(pensamentos[0])));
        cout << "O " << nome << " está pensando: " << pensamentos[indice_Pensamentos] << endl;
        idleB = true;
    }
}

void idle() {
    tempo = 1;
    string pensamentos[] = { "Já se passaram 1 minuto é ele continua parado!!!" };
    int indice_Pensamentos = rand() % (sizeof(pensamentos) / (sizeof(pensamentos[0])));
    cout << "O " << nome << " está pensando: " << pensamentos[indice_Pensamentos] << endl;
    idleB = true;
}

//jogo da velha
void print() {
    int i, j;
    cout << "\n";
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (a[i][j] == 0)
                cout << ".\t";
            else if (a[i][j] == 1)
                cout << "X\t";
            else
                cout << "O\t";
        }
        cout << endl;
    }
}

int check() {
    for (int i = 0; i < 3; i++)
        if ((a[i][0] != 0 && a[i][0] == a[i][1] && a[i][1] == a[i][2]) || (a[0][i] != 0 && a[0][i] == a[1][i] && a[1][i] == a[2][i]))
            return 1;

    if (a[0][0] != 0 && a[0][0] == a[1][1] && a[1][1] == a[2][2])
        return 1;
    else if (a[0][2] != 0 && a[0][2] == a[1][1] && a[1][1] == a[2][0])
        return 1;
    else
        return 0;
}

void pin() {
    int r = 0, c = 0;
    cout << "Enter row: ";
    cin >> r;
    cout << "Enter column: ";
    cin >> c;
    r--;
    c--;
    if (r > 2 || c > 2 || r < 0 || c < 0 || a[r][c] != 0) {
        cout << "Invalid input. Try again.\n";
        pin();
    }
    else {
        a[r][c] = t;
    }
}

void ai(int b) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (a[i][j] == 0) {
                a[i][j] = y;
                cout << "Computer turn: " << i + 1 << " " << j + 1 << endl;
                return;
            }
        }
    }
}

bool edigito() {
    for (char& c : escolha) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool edigito2() {
    for (char& c : tecla) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

void verificar_compra(long valor) {
    getline(cin, escolha);
    if (stoi(escolha) > 99999999) {
        cout << "Numero muito grande, tente colocar valores menor que 99999999 (no caso 8 numeros 9)";
        getline(cin, tecla);
    }
    else {
        if (edigito()) {
            quantidade = stoi(escolha);
            if (moedas < valor) {
                cout << "Desculpe, Mas você tem poucas moedas" << endl;
                getline(cin, tecla);
            }
            else {
                valor *= stoi(escolha);
                cout << "Irá custar " << valor << " Vai comprar mesmo assim??? (s/'enter')" << endl;
                getline(cin, tecla);
                if (tecla == "s" || tecla == "S") {
                    if (valor < moedas) {
                        moedas -= valor;
                    }
                    else {
                        cout << "Acariciou, tente de novo" << endl;
                        getline(cin, tecla);
                    }
                }
                else {

                }
            }
        }
        else {
            cout << "Digite um valor valido" << endl;
            getline(cin, tecla);
        }
    }
}

void aviso(int erro_type) {
    if (erro_type == 1) {
        cout << "\033[41mDevido a limitações do C++ você não pode comprar mais esse produto, com isso você não obteve prejuizos\033[0m";
        getline(cin, tecla);
    }
    if (erro_type == 2) {
        if (fome > 40 && fome < 60) {
            cout << "O seu " + nome + " está com fomem, dé o que comer a ele" << endl;
        }
        else {
            cout << "O seu " + nome + " está morrendo de fomem, dé o que comer a ele com urgencia" << endl;
        }
    }

}

void consumir(int& string){
    cout << "Se quiser comsumir quantidade digite '(a)' para comer tudo";
    getline(cin, tecla);
    if (edigito2()) {
        if (stoi(tecla) > string) {
            cout << "Muita quantidade para pouco alimento" << endl;
            getline(cin, tecla);
        }
        else {
            string -= stoi(tecla);
            fome = fome - 4 * stoi(tecla);
            tempo_fome = 0;
        }
    }
    else {
        if (tecla == "a" || tecla == "A") {
            fome = fome - 4 * string;
            string = 0;
            tempo_fome = 0;
        }
    }
}
//transform(tecla.begin(), tecla.end(), tecla.begin(), ::tolower); para getline maiusculo e minusculo
