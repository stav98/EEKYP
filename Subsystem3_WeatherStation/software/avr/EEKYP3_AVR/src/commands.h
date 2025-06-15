void init_commands(void);
void printErr1(void);
void printErr2(void);
void soft_reset(int, char**);
void print_version(int, char**);
void help(int, char**);

const char PROGMEM 
   //        1         |           2         |         3            |         4            |          5          |
   ct01[] = "rst"      , ct02[] = "version"  , ct03[] = "?";

//Δομή συνδεδεμένης λίστας
const L_cmd PROGMEM cmd03 = {(char*) ct03   , help,             NULL}; //? Παρουσίασε εντολές
const L_cmd PROGMEM cmd02 = {(char*) ct02   , print_version,  &cmd03}; //Έκδοση λογισμικού
const L_cmd PROGMEM cmd01 = {(char*) ct01   , soft_reset,     &cmd02}; //Κάνει reset

void init_commands(void)
{
 cmd_tbl = (L_cmd*) &cmd01;
}

void printErr1()
{
 Serial.println(F("Too few arguments"));
}

void printErr2()
{
 Serial.println(F("Syntax error"));
}

void soft_reset(int arg_cnt, char **args)
{
 resetFunc();
}

void print_version(int arg_cnt, char **args)
{
 Serial.print(F("Version: "));
 Serial.println(VERSION);
}

void help(int arg_cnt, char **args)
{
 char buf[10];
 L_cmd *cmd_entry;
 for (cmd_entry = cmd_tbl; cmd_entry != NULL; cmd_entry = (L_cmd*)pgm_read_word(&cmd_entry->next))
     {
      strcpy_P(buf, (char*)pgm_read_word(&cmd_entry->cmd));
      Serial.println(buf);
     }
}