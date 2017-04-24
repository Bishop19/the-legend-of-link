Alterações:
-itemInimigo - apenas faz a parte aleatoria da atruibuicao do item(devolde um numero simplesmente)
-NOVA isItem - dado uma casa com item retorna o inimigo que o possui para saber a posicao ou caso nao tenha item retorna -1
-catchItem- recebe o tipo item e o Estado e altera como antigamente
- A atribuicao dos items passou a ser feita mal o inimigo é criado na inicializar com a funcao itemInimigo
--NOVA print_specific_item para fazer o href de um so item e manter a print_item a fazer a impressao dos restantes caso nao estejamos perto deles
-- novas condicoes na enemyMove porque como associei o item ao inimigo so joga quem esta vivo ou entao os items andariam atras de nos
-- introcucao da isItem na casa livre

Verificar:
- porta escondida por parede/monstros;

Ideias:
- Score (DONE);
- Crit Chance;
- Mudar imagem conforme último movimento;
- Itens para aumentar dano e defesas;
- Inimigos dropam items;
- Tesouro - items;
- Lama - quando o jogador passar aqui fica sem jogar um turno;
- Escadas em vez de porta;
- no ficheiro de scores mostrar nome, score, monstros mortos, bosses derrotados e ouro apanhado;
- mana para ataques e movimentos especiais (quadradinhos pequenos de lado);
