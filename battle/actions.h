struct Player;

/* Actions layer */
void selectTile(int x,int y);
void selectMenuItem(int item);

/* Display layer */
void showMenu(int items, char **text);
void showStats(struct Player *player);
void showMessage(const char *message);

