# ★ SIG-Nails
Sistema de agendamento e gestão de serviços de manicure e pedicure.

Universidade Federal do Rio Grande do Norte
Centro de Ensino Superior do Seridó
Departamento de Computação e Tecnologia
Bacharelado em Sistemas de Informação

Desenvolvido por:

- Letícia Taylane (1)
  
- Flávia Juliana (2)
  
Desde Ago, 2025
# ★ ★ ★ ★ ★ ★
SIG-Nails é um software educativo desenvolvido em linguagem C para prática de programação.

O programa permite:

- Registrar novos agendamentos de serviços★

- Editar, remover e confirmar agendamentos

- Validar datas e horários automaticamente

- Consultar tabela de preços

- Acessar telas de ajuda e informações sobre o sistema

- Acompanhar qual profissional irá atendê-lo(a)

- Inspirar em cores de esmalte pelo próprio sistema

**OBS.:**
Todos os dados utilizados são fictícios, e o sistema serve apenas para fins didáticos.


# ★ Atualizações do Projeto:

SEMANAS 1 e 2:

- Tela de edição de agendamento implementada

- Validação de datas e horários corrigida

- Ajustes nas telas de confirmação e remoção

- Pequenos ajustes no menu principal

- Criação das telas iniciais

- Cadastro de agendamento básico

- Implementação das telas de ajuda e sobre

SEMANAS 3 e 4:

- Novos módulos de atendentes e cores
  
- Nova validação de hora

- Nova validação de data
  
- Mudanças estéticas

SEMANA 5:

- Modularização, adição dos headers

- Adição do Makefile


# ★ Pré-requisitos:

Antes de compilar, verifique se você tem instalado:

GCC (compilador C)

Make (para usar o Makefile)

Git (opcional, para clonar o repositório)

No Linux, você pode instalar com:

sudo apt update
sudo apt install build-essential


# ★ Como compilar
LINUX (Ubuntu/Debian):

Clone o repositório (ou baixe os arquivos):

git clone https://github.com/SEU-USUARIO/sig-nails.git
cd sig-nails


Compile o projeto (usando o Makefile):

make


Isso vai gerar o executável:

./sig-nails


Execute o programa:

./sig-nails


Para limpar arquivos compilados:

make clean

# ★ Executar no Windows (usando WSL)

O SIG-Nails foi desenvolvido para Linux, e não funciona nativamente no Windows.
Para executar no Windows, use o WSL (Windows Subsystem for Linux).

1. Instalar o WSL

Abra o PowerShell como Administrador e execute:

wsl --install


Isso instala o WSL 2 e o Ubuntu automaticamente.

Reinicie o computador quando solicitado.

Quando o Ubuntu abrir pela primeira vez, crie um usuário e senha.

2. Atualizar e preparar o ambiente Linux dentro do WSL

Abra o Ubuntu (pelo menu Iniciar) e execute:

sudo apt update && sudo apt upgrade -y
sudo apt install build-essential git -y

3. Mover o código para o WSL

Você pode:

Clonar o repositório diretamente dentro do WSL:

git clone https://github.com/SEU-USUARIO/sig-nails.git
cd sig-nails


Ou acessar a pasta do Windows dentro do WSL:

cd /mnt/c/Users/SEU_USUARIO/Documents/sig-nails

4. Compilar e executar no WSL

Dentro do terminal Ubuntu (WSL):

make
./sig-nails

# ★ Estrutura do Projeto:
SIG-Nails/
│
├── Agendamento/
│   ├── agendamentos.c
│   └── agendamentos.h
│
├── cliente/
│   ├── clientes.c
│   └── clientes.h
│
├── funcionarios/
│   ├── funcionarios.c
│   └── funcionarios.h
│
├── geral/
│   ├── cores.h
│   ├── erros.c
│   ├── erros.h
│   ├── telas_gerais.c
│   └── telas_gerais.h
│
├── servicos/
│   ├── servicos.c
│   └── servicos.h
│
├── utils/
│   ├── ler_dados.c
│   ├── ler_dados.h
│   ├── limpeza.c
│   ├── limpeza.h
│   ├── validacoes.c
│   └── validacoes.h
│
├── main.c
├── Makefile
├── README.md
├── clientes.dat
├── servicos.dat
└── .gitignore

# ★ Dicas Extras

Se quiser usar o VS Code no Windows com o WSL:

Instale a extensão Remote - WSL

Abra o terminal Ubuntu dentro do VS Code

Compile e execute com:

make
./sig-nails


Para limpar os arquivos compilados:

make clean

# ★ Observações

O projeto deve ser executado em Linux ou WSL (Windows Subsystem for Linux).

Todos os dados são fictícios e usados apenas para fins educacionais.

O executável padrão gerado é ./sig-nails.

O Makefile gerencia automaticamente a compilação de todos os módulos do sistema.