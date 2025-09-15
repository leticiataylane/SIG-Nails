# ★ SIG-Nails
Sistema de agendamento e gestão de serviços de manicure e pedicure.

Universidade Federal do Rio Grande do Norte
Centro de Ensino Superior do Seridó
Departamento de Computação e Tecnologia
Bacharelado em Sistemas de Informação

Desenvolvido por Letícia Taylane - Desde Ago, 2025
# ★ ★ ★ ★ ★ ★ ★ ★ 
SIG-Nails é um software educativo desenvolvido em linguagem C para prática de programação.

O programa permite:

- Registrar novos agendamentos de serviços

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

Git (opcional, para clonar o repositório)

- No Linux, você pode instalar com:

sudo apt update

sudo apt install build-essential

# ★ Como compilar
**LINUX (UBUNTU/DEBIAN):**
1. Clone o repositório (ou baixe os arquivos)
   
git clone https://github.com/SEU-USUARIO/sig-nails.git

cd SIG-Nails

3. Compile o projeto

- Se estiver usando o Makefile:

make


Isso vai gerar o executável sig_nails.

- Se preferir compilar manualmente:

gcc main.c tela_inicial.c tela_final.c tela_sobre.c tela_ajuda.c \
tela_edição_remoção.c tela_cores.c tela_atendentes.c \
-Iinclude -o sig_nails

3. Execute o programa
./sig_nails

**WINDOWS (MinGW):**

1. Instale o compilador MinGW

- Baixe em: MinGW

- Durante a instalação, selecione o pacote mingw32-gcc-g++.

2. Adicione o caminho do bin do MinGW à variável de ambiente PATH.

- Abra o terminal do MinGW (ou CMD/PowerShell configurado)

3. Compile o projeto

gcc main.c tela_inicial.c tela_final.c tela_sobre.c tela_ajuda.c ^
tela_edição_remoção.c tela_cores.c tela_atendentes.c ^
-Iinclude -o sig_nails.exe

**OBS.:** No Windows, as quebras de linha no terminal usam ^ (não \).

4. Execute o programa

sig_nails.exe

# ★ Observações

- Todos os arquivos .h estão na pasta include.

- Se ocorrer erro com acentos no nome do arquivo (tela_edicao_remoção.c), verifique se o seu sistema suporta UTF-8 corretamente.

  


