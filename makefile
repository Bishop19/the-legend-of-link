CFLAGS = -Wall -Wextra -pedantic -O2
OBJS = $(patsubst %.c ,%.o ,$(wildcard *.c))
EXEC = Rogue
$(EXEC):	$(OBJS)
			$(CC)	$(CFLAGS)	-o $(EXEC)	$(OBJS)

			sudo mkdir -p /var/www/html/imagens
			sudo chmod a+rw /var/www/html/imagens
			sudo cp $(EXEC) /usr/lib/cgi-bin
			sudo cp player.png /var/www/html/imagens
			sudo cp enemy1.png /var/www/html/imagens
			sudo cp enemy2.png /var/www/html/imagens
			sudo cp enemy3.png /var/www/html/imagens
			sudo cp menu1.png /var/www/html/imagens
			sudo cp door.png /var/www/html/imagens
			sudo cp rangeMove.png /var/www/html/imagens
			sudo cp wall.png /var/www/html/imagens
			sudo cp rangeAttack.png /var/www/html/imagens
			sudo cp tesouro.png /var/www/html/imagens
			sudo cp vida.png /var/www/html/imagens
			sudo cp mana.png /var/www/html/imagens
			sudo cp vida_Drop.png /var/www/html/imagens
			sudo cp mana_Drop.png /var/www/html/imagens
			sudo cp sword.png /var/www/html/imagens
			sudo cp crit.png /var/www/html/imagens
			sudo cp score5.png /var/www/html/imagens
			sudo cp score10.png /var/www/html/imagens
			sudo cp score25.png /var/www/html/imagens
			sudo cp vida_inimigo.png /var/www/html/imagens
			sudo cp floor_hex.png /var/www/html/imagens
			sudo cp shield.png /var/www/html/imagens
			sudo cp sword_PU.png /var/www/html/imagens
			sudo cp sword_PU_inv.png /var/www/html/imagens
			sudo cp vida_inv.png /var/www/html/imagens
			sudo cp mana_inv.png /var/www/html/imagens
			sudo cp shield_inv.png /var/www/html/imagens
			sudo cp Title_Screen.png /var/www/html/imagens
			sudo cp start_button.png /var/www/html/imagens
			sudo cp back_button.png /var/www/html/imagens
			sudo cp square_link.png /var/www/html/imagens
			sudo cp toggle_range.png /var/www/html/imagens
			sudo cp toggle_vida.png /var/www/html/imagens
			sudo cp topScore_button.png /var/www/html/imagens
			sudo cp boss_symbol.png /var/www/html/imagens
			sudo cp dead_screen.png /var/www/html/imagens
			sudo cp no_mana.png /var/www/html/imagens

			sudo mkdir -p /var/www/html/estado
			sudo chmod a+rw /var/www/html/estado

clean:		
	rm	$(EXEC)	*.o
