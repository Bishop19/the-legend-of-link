CFLAGS = -Wall -O2 
OBJS = $(patsubst %.c ,%.o ,$(wildcard *.c))
EXEC = Rogue
$(EXEC):	$(OBJS)
			$(CC)	$(CFLAGS)	-o $(EXEC)	$(OBJS)
			sudo cp $(EXEC) /usr/lib/cgi-bin
			sudo cp player.png /var/www/html
			sudo cp enemy1.png /var/www/html
			sudo cp enemy2.png /var/www/html
			sudo cp enemy3.png /var/www/html
			sudo cp menu.png /var/www/html
			sudo cp floor.png /var/www/html
			sudo cp door.png /var/www/html
			sudo cp rangeMov10.png /var/www/html
			sudo cp wall.png /var/www/html
			sudo cp rangeAttack.png /var/www/html
			sudo cp tesouro.png /var/www/html
			sudo cp vida.png /var/www/html
			sudo cp mana.png /var/www/html
			sudo cp vida_Drop.png /var/www/html
			sudo cp mana_Drop.png /var/www/html
			sudo cp sword.png /var/www/html
			sudo cp crit.png /var/www/html
			sudo cp score5.png /var/www/html
			sudo cp score10.png /var/www/html
			sudo cp score25.png /var/www/html
			sudo cp lama.png /var/www/html
			sudo cp vida_inimigo.png /var/www/html
			sudo cp floor_hex.png /var/www/html


clean:
	rm	$(EXEC)	*.o
