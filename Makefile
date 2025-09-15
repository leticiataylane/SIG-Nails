#CRÉDITOS AO CHATGPT 
all:
	gcc main.c tela_inicial.c tela_final.c tela_sobre.c tela_ajuda.c \
	    tela_atendentes.c tela_cores.c \
	    tela_edição_remoção.c -Iinclude -o sig_nails