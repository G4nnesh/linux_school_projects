DESTDIR?=/usr
PREFIX?=/local


CC = gcc

SRC = src
INC = include
BIN = bin
BLD = build
LIB = lib
EXPL = examples


CFLAGS = -Wall -std=gnu99 -I$(INC)

VERT = \033[1;32m
BLEU = \033[1;34m
JAUNE = \033[1;33m
NC = \033[1;0m



all : 	julius examples
examples : cesar cipher cipher_file 


########################## librairie Julius ############################

julius : $(LIB)/libjulius.a $(LIB)/libjulius.so

# lib statique lib<julius>.a
$(BLD)/julius.o : $(SRC)/julius.c
	$(CC) $(CFLAGS) -c $< -o $@
	
$(LIB)/libjulius.a : $(BLD)/julius.o
	ar qvs $@ $^

# lib dynamique lib<julius>.so
$(BLD)/julius_fpic.o : $(SRC)/julius.c
	$(CC) -c $< -o $@

$(LIB)/libjulius.so : $(BLD)/julius_fpic.o
	$(CC) -shared $< -o $@
#########################################################################
##############Exemple 1 : cesar #########################################
#Mot à coder :
MOT= -DMOT='"Bonjour !"'
#CLE :
CLE= -DCLE='15'

cesar : $(BIN)/cesar_statique $(BIN)/cesar_dynamique

#édition de liens statiques:
$(BIN)/cesar_statique : $(EXPL)/cesar.c
	$(CC) -I$(INC) -L$(LIB) -static $(MOT) $(CLE) $^ -o $@ -ljulius

#édition de liens dynamiques:
$(BIN)/cesar_dynamique : $(EXPL)/cesar.c $(LIB)/libjulius.so
	$(CC) -I$(INC) $(MOT) $(CLE) $< -o $@ -L$(LIB) -ljulius
#########################################################################
##############Exemple 2 : cipher ########################################

cipher : $(BIN)/cipher_statique $(BIN)/cipher_dynamique

#édition de liens statiques:
$(BIN)/cipher_statique : $(EXPL)/cipher.c
	$(CC) -I$(INC) -L$(LIB) -static $^ -o $@ -ljulius

#édition de liens dynamiques:
$(BIN)/cipher_dynamique : $(EXPL)/cipher.c
	$(CC) -I$(INC) $< -o $@ -L$(LIB) -ljulius
#########################################################################
##############Exemple 3 : cipher_file ###################################

cipher_file : $(BIN)/cipher_file_statique $(BIN)/cipher_file_dynamique

#édition de liens statiques:
$(BIN)/cipher_file_statique : $(EXPL)/cipher_file.c
	$(CC) -I$(INC) -L$(LIB) -static $^ -o $@ -ljulius	 
#édition de liens dynamiques:
$(BIN)/cipher_file_dynamique : $(EXPL)/cipher_file.c
	$(CC) -I$(INC) $< -o $@ -L$(LIB) -ljulius
#########################################################################



.PHONY : clean all
	
	
clean :
	rm -f $(LIB)/*.a $(LIB)/*.so $(BLD)/*.o $(BIN)/* 

	
	
.PHONY : install
install : julius cesar cipher cipher_file
	@echo "$(JAUNE)Compilation...$(NC)"
	$Q make all
	
	@echo "$(JAUNE)Installation des fichiers d'entête...$(NC)"
	$Q sudo install -m 0755 -d					$(DESTDIR)$(PREFIX)/include
	$Q sudo install -m 0644 $(INC)/julius.h			$(DESTDIR)$(PREFIX)/include
	
	@echo "$(JAUNE)Installation de la librairie dynamique...$(NC)"
	#Les librairies sont directement copiées vers usr/lib car usr/local/lib n'est pas inclus dansle path par défaut.
	$Q sudo install -m 0755 -d					$(DESTDIR)/lib
	$Q sudo install -m 0755 $(PWD)/$(LIB)/libjulius.so		$(DESTDIR)/lib
	
	@echo "$(JAUNE)Installation des exemples...$(NC)"	
	$Q sudo ln -sf $(PWD)/$(BIN)/*				$(DESTDIR)$(PREFIX)/bin
	@echo "$(VERT)Installation terminée.$(NC)"	
			

	
.PHONY : uninstall
uninstall :
	@echo "$(VERT)Désinstallation...$(NC)"
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/include/julius.h		
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/bin/cesar_statique
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/bin/cesar_dynamique
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/bin/cipher_statique
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/bin/cipher_dynamique
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/bin/cipher_file_statique
	$Q sudo rm -f $(DESTDIR)$(PREFIX)/bin/cipher_file_dynamique
	$Q sudo rm -f $(DESTDIR)/lib/libjulius.so
	$Q make clean	
	@echo "$(BLEU)Désinstallation terminée.$(NC)"
