CFLAGS = -Wall -Wextra -pedantic -O2 -std=c99
OBJS = $(patsubst %.c ,%.o ,$(wildcard *.c))
EXEC = Rogue
$(EXEC):	$(OBJS)
			$(CC)	$(CFLAGS)	-o $(EXEC)	$(OBJS)

			sudo mkdir -p /var/www/html/imagens
			sudo chmod a+rw /var/www/html/imagens
			
			sudo cp $(EXEC) /usr/lib/cgi-bin
			sudo cp imagens/* /var/www/html/imagens

			sudo mkdir -p /var/www/html/estado
			sudo chmod a+rw /var/www/html/estado

clean:		
	rm	$(EXEC)	*.o
